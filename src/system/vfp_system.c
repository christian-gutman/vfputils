#include "vfp_system.h"



void CORE_CALL Fox_SoLastError(ParamBlk *parm)
{
    // Capturamos el error numérico de la API de Windows
    DWORD last_err = GetLastError();

    // Estructura numérica de salida
    Value valErrorNum = {'I', 0, 0, 0};
    valErrorNum.ev_long = (long)last_err;

    // Estructura de texto de salida
    Value valErrorMsg = {'C', 0, 0, 0};

    // Si hubo una falla (código distinto de 0), armamos el buffer del mensaje descriptivo
    if (last_err != 0)
    {
        int max_buffer = 1024;
        MHANDLE hOutput = _AllocHand(max_buffer);
        if (hOutput != 0)
        {
            char *target = (char *)SafeLockHandle(hOutput);
            if (target != NULL)
            {
                int actual_len = get_system_error_message(last_err, target, max_buffer);
                SafeUnlockHandle(hOutput);
                valErrorMsg.ev_length = actual_len;
                valErrorMsg.ev_handle = hOutput;
            }
            else
            {
                _FreeHand(hOutput);
            }
        }
    }
    int rc = -1;
    if (parm && parm->pCount >= 2)
    {
        // Primer parámetro (índice 0): @error
        if (parm->p[0].loc.l_type == 'R')
        {
           rc = _Store(&parm->p[0].loc, &valErrorNum);
        }
        // Segundo parámetro (índice 1): @msg
        if (parm->p[1].loc.l_type == 'R')
        {
           rc = _Store(&parm->p[1].loc, &valErrorMsg);
        }
    }

    // La función en el IF de FoxPro retorna el estado lógico del error
    _RetLogical(last_err != 0);
}
