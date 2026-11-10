#ifndef VFP_CERTS_H
#define VFP_CERTS_H
 
#include "vfp_lib.h"
#include "vfp_types.h"
#include "core_encoding.h"
#include "core_string.h"
#include "core_certs.h"

void CORE_CALL Fox_CertGetExpiry(ParamBlk *parm);
void CORE_CALL Fox_CertSignMsg(ParamBlk *parm);

#endif // VFP_CERTS_H