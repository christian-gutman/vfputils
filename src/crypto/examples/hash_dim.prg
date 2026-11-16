* ============================================================
* TABLA DE REFERENCIA - TAMAÑOS DE BUFFER POR ALGORITMO
* ============================================================
LOCAL ARRAY laAlgoSizes[10, 4]
* Columnas: 1=Algoritmo, 2=Bytes, 3=HexChars, 4=BufferMinimo

laAlgoSizes[1,1] = "MD5"          && laAlgoSizes[1,2] = 16   && laAlgoSizes[1,3] = 32   && laAlgoSizes[1,4] = 33
laAlgoSizes[2,1] = "SHA1"         && laAlgoSizes[2,2] = 20   && laAlgoSizes[2,3] = 40   && laAlgoSizes[2,4] = 41
laAlgoSizes[3,1] = "SHA256"       && laAlgoSizes[3,2] = 32   && laAlgoSizes[3,3] = 64   && laAlgoSizes[3,4] = 65
laAlgoSizes[4,1] = "SHA384"       && laAlgoSizes[4,2] = 48   && laAlgoSizes[4,3] = 96   && laAlgoSizes[4,4] = 97
laAlgoSizes[5,1] = "SHA512"       && laAlgoSizes[5,2] = 64   && laAlgoSizes[5,3] = 128  && laAlgoSizes[5,4] = 129
laAlgoSizes[6,1] = "HMAC-MD5"     && laAlgoSizes[6,2] = 16   && laAlgoSizes[6,3] = 32   && laAlgoSizes[6,4] = 33
laAlgoSizes[7,1] = "HMAC-SHA1"    && laAlgoSizes[7,2] = 20   && laAlgoSizes[7,3] = 40   && laAlgoSizes[7,4] = 41
laAlgoSizes[8,1] = "HMAC-SHA256"  && laAlgoSizes[8,2] = 32   && laAlgoSizes[8,3] = 64   && laAlgoSizes[8,4] = 65
laAlgoSizes[9,1] = "HMAC-SHA384"  && laAlgoSizes[9,2] = 48   && laAlgoSizes[9,3] = 96   && laAlgoSizes[9,4] = 97
laAlgoSizes[10,1]= "HMAC-SHA512"  && laAlgoSizes[10,2]= 64   && laAlgoSizes[10,3]= 128  && laAlgoSizes[10,4]= 129

? "============================================================"
? "TABLA DE REFERENCIA - TAMAÑOS DE BUFFER POR ALGORITMO"
? "============================================================"
? PADR("Algoritmo", 15) + PADR("Bytes", 8) + PADR("Hex chars", 12) + "Buffer min (+'\0')"
? REPLICATE("-", 60)
LOCAL i
FOR i = 1 TO ALEN(laAlgoSizes, 1)
    ? PADR(laAlgoSizes[i,1], 15) + ;
      PADR(TRANSFORM(laAlgoSizes[i,2]), 8) + ;
      PADR(TRANSFORM(laAlgoSizes[i,3]), 12) + ;
      TRANSFORM(laAlgoSizes[i,4])
ENDFOR
? "============================================================"