#include "__cf_hdlcodercpu_eml.h"
#ifndef RTW_HEADER_hdlcodercpu_eml_h_
#define RTW_HEADER_hdlcodercpu_eml_h_
#include <string.h>
#include <stddef.h>
#include "rtw_modelmap.h"
#ifndef hdlcodercpu_eml_COMMON_INCLUDES_
#define hdlcodercpu_eml_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "hdlcodercpu_eml_types.h"
#include "multiword_types.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME hdlcodercpu_eml
#define NSAMPLE_TIMES (1) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (12) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (0)   
#elif NCSTATES != 0
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
typedef struct { uint16_T fcetjhhiex ; int8_T a5hp1ity41 ; int8_T ml1z4011om
; int8_T aepsxaam4m ; int8_T iht3vcokcy [ 256 ] ; int8_T kkvw0ptxgn ; int8_T
ahogxsodi5 ; int8_T mara0lwcgp ; uint8_T gyn0k3gkkt ; uint8_T nydvymh33o ;
boolean_T drljjcdixn ; uint8_T nr2ykwyg2x ; } B ; typedef struct { struct {
void * LoggedData ; } hio3mwober ; struct { void * LoggedData ; } buythqrmps
; uint16_T hzjbagfonx ; uint16_T m0riydqyff ; uint16_T l32z4pgrvm [ 256 ] ;
int8_T dbjbvxg23s ; int8_T boyw4d0uwn ; int8_T b0w1eco2iu ; int8_T l0owajfezg
; int8_T hcle0rjezs ; int8_T gkfgmh3s00 [ 256 ] ; uint8_T ids0ty3k2c ;
boolean_T kcb5h3l2rz ; boolean_T j3nrtien2t ; uint8_T kmbjhnlkaw ; int8_T
posk0eizok ; uint8_T aieo2sbtyk ; uint8_T gqdvjn31au ; uint8_T mpui0k5sli ;
uint8_T hithci51lt ; uint8_T ecskwlmtwq ; uint8_T pxavurktwi ; uint8_T
corjqxlsl3 ; } DW ; typedef struct { const boolean_T nvfvuebnci ; } ConstB ;
typedef struct { rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; extern const
ConstB rtrtC ; extern const char * RT_MEMORY_ALLOCATION_ERROR ; extern B rtB
; extern DW rtDW ; extern const rtwCAPI_ModelMappingStaticInfo *
hdlcodercpu_eml_GetCAPIStaticMap ( void ) ; extern SimStruct * const rtS ;
extern const int_T gblNumToFiles ; extern const int_T gblNumFrFiles ; extern
const int_T gblNumFrWksBlocks ; extern rtInportTUtable * gblInportTUtables ;
extern const char * gblInportFileName ; extern const int_T
gblNumRootInportBlks ; extern const int_T gblNumModelInputs ; extern const
int_T gblInportDataTypeIdx [ ] ; extern const int_T gblInportDims [ ] ;
extern const int_T gblInportComplex [ ] ; extern const int_T
gblInportInterpoFlag [ ] ; extern const int_T gblInportContinuous [ ] ;
extern DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ;
#endif
