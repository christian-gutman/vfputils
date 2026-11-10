#ifndef VFP_REQUEST_H
#define VFP_REQUEST_H

#include "vfp_lib.h"
#include "vfp_types.h"
#include "core_encoding.h"
#include "core_string.h"
#include "core_request.h"

/*
#include "core_request.h"
#include "core_rest.h"
#include "core_req_file.h"

#include "vfp_request.h"
#include "vfp_rest.h"
#include "vfp_req_file.h"
*/

#ifdef __cplusplus
extern "C"
{
#endif

    /*
     * StoreVfpResponse: Pasa el código de estado HTTP y el buffer de respuesta JSON
     * desde C hacia las variables pasadas por referencia (@) en Visual FoxPro.
     * Libera automáticamente el responseBuffer antes de terminar.
     */
    static __forceinline void StoreVfpResponse(
        BOOL bResult, DWORD statusCode, char *responseBuffer,
        Locator *pLocResponse, Locator *pLocStatusCode)
    {
        if (!pLocResponse || !pLocStatusCode)
            return;
        // ===========================================================================
        // ESCENARIO 1: EL SERVIDOR DEVOLVIÓ DATOS (Prioridad Absoluta)
        // ===========================================================================
        if (responseBuffer && responseBuffer[0] != '\0')
        {
            // 1. Guardamos el Status Code. Si bResult es FALSE pero hay buffer,
            // y statusCode quedó en 0, intentamos rescatar el GetLastError() para no dejarlo en 0.
            DWORD finalStatus = statusCode;
            if (finalStatus == 0 && !bResult)
            {
                finalStatus = GetLastError();
                if (finalStatus == 0)
                    finalStatus = ERROR_WINHTTP_INTERNAL_ERROR;
            }

            Value vStatus = {'I', 0, 0, 0, 0};
            vStatus.ev_long = (long)finalStatus;
            _Store(pLocStatusCode, &vStatus);

            // 2. Guardamos el búfer de texto real capturado
            Value vResponse = {'C', 0, 0, 0, 0};
            vResponse.ev_length = (unsigned long)strlen(responseBuffer);
            vResponse.ev_handle = _AllocHand(vResponse.ev_length);

            if (vResponse.ev_handle != 0)
            {
                _HLock(vResponse.ev_handle);
                _MemMove((char *)_HandToPtr(vResponse.ev_handle), responseBuffer, vResponse.ev_length);
                _HUnLock(vResponse.ev_handle);
                _Store(pLocResponse, &vResponse);
            }

            free(responseBuffer); // Liberación obligatoria del buffer de WinHTTP
            return;               // Terminamos de forma exitosa entregando los datos reales
        }
        if (bResult)
        {
            // ===========================================================================
            // ESCENARIO 2: ÉXITO EN RED, PERO SIN CUERPO DE RESPUESTA (Ej: HTTP 204 No Content)
            // ===========================================================================
            Value vStatus = {'I', 0, 0, 0, 0};
            vStatus.ev_long = (long)statusCode;
            _Store(pLocStatusCode, &vStatus);

            _Store(pLocResponse, &(Value){'C', 0, 0, 0, 0}); // String vacío a FoxPro
        }
        else
        {
            // ===========================================================================
            // ESCENARIO 3: FALLO TOTAL DE CONEXIÓN Y SIN RESPUESTA DEL SERVIDOR
            // ===========================================================================
            DWORD dwLastError = GetLastError();
            if (dwLastError == 0)
                dwLastError = ERROR_WINHTTP_INTERNAL_ERROR;

            // 1. Guardamos el código de error de Windows (ej: 12002, 12007)
            Value vStatus = {'I', 0, 0, 0, 0};
            vStatus.ev_long = (long)dwLastError;
            _Store(pLocStatusCode, &vStatus);

            // 2. Generamos el JSON local de diagnóstico para el prg
            char szLocalErrorJson[256] = {0};
            int jsonLen = _snprintf_s(szLocalErrorJson, sizeof(szLocalErrorJson), _TRUNCATE,
                                      "{\"error\":\"winhttp_error\",\"error_code\":%lu,\"message\":\"Falla de comunicacion de red nativa Windows\"}",
                                      dwLastError);

            if (jsonLen > 0)
            {
                Value vResponse = {'C', 0, 0, 0, 0};
                vResponse.ev_length = (unsigned long)jsonLen;
                vResponse.ev_handle = _AllocHand(vResponse.ev_length);

                if (vResponse.ev_handle != 0)
                {
                    _HLock(vResponse.ev_handle);
                    _MemMove((char *)_HandToPtr(vResponse.ev_handle), szLocalErrorJson, vResponse.ev_length);
                    _HUnLock(vResponse.ev_handle);
                    _Store(pLocResponse, &vResponse);
                }
            }
            else
            {
                _Store(pLocResponse, &(Value){'C', 0, 0, 0, 0});
            }
        }
        if (responseBuffer)
            free(responseBuffer);
    }

    // ===========================================================================
    // RECEPCIÓN: FoxPro String Binario -> HINTERNET (Manejador de red)
    // ===========================================================================
    //  Recepcion
    //  HINTERNET* ctx = FoxHandleStr2WHttpContext(parm->p[0].val);
    static __forceinline HINTERNET FoxHandleStr2HINTERNET(Value valParam)
    {
        // Validar que FoxPro nos mande un String ('C') o un Memo ('M')
        if (valParam.ev_type != 'C' && valParam.ev_type != 'M')
            return NULL;

        // El tamaño del string DEBE coincidir exactamente con el tamaño de un puntero del sistema
        if (valParam.ev_length != sizeof(HINTERNET) || valParam.ev_handle == 0)
            return NULL;

        HINTERNET hResult = NULL;

        _HLock(valParam.ev_handle);
        void *fox_ptr = _HandToPtr(valParam.ev_handle);

        if (fox_ptr != NULL)
        {
            memcpy(&hResult, fox_ptr, sizeof(HINTERNET));
        }

        _HUnLock(valParam.ev_handle);
        return hResult;
    }

    // ===========================================================================
    // ENVÍO: HINTERNET (Manejador de red) -> FoxPro String Binario
    // ===========================================================================
    // Value foxHandle = WHttpContext2FoxHandleStr(ctx);
    static __forceinline Value HINTERNET2FoxHandleStr(HINTERNET hCtx)
    {
        Value valResult = {'C', 0, 0, 0};
        if (hCtx == NULL)
            return valResult;

        int ptr_size = sizeof(HINTERNET);

        MHANDLE hAlloc = _AllocHand(ptr_size);
        if (hAlloc == 0)
        {
            _Error(182);
            return valResult;
        }

        valResult.ev_handle = hAlloc;
        valResult.ev_length = ptr_size;

        _HLock(valResult.ev_handle);
        void *fox_ptr = _HandToPtr(valResult.ev_handle);

        if (fox_ptr != NULL)
        {
            memcpy(fox_ptr, &hCtx, ptr_size);
        }
        else
        {
            _FreeHand(hAlloc);
            valResult.ev_handle = 0;
            valResult.ev_length = 0;
        }

        _HUnLock(valResult.ev_handle);
        return valResult;
    }

    // ---- Utf82Ansi / Ansi2Utf8  ----

    // FoxPro: lcTextoAnsi = WUtf8ToAnsi(lcTextoUtf8)
    void CORE_CALL Fox_WUtf8ToAnsi(ParamBlk *parm);
    // FoxPro: lcTextoUtf8 = WAnsiToUtf8(lcTextoAnsi)
    void CORE_CALL Fox_WAnsiToUtf8(ParamBlk *parm);

    void CORE_CALL Fox_WRequest(ParamBlk *parm);
    void CORE_CALL Fox_WConnect(ParamBlk *parm);
    void CORE_CALL Fox_WDisconnect(ParamBlk *parm);
    void CORE_CALL Fox_WCloseRequest(ParamBlk *parm);
    
#ifdef __cplusplus
}
#endif

#endif // VFP_REQUEST_H