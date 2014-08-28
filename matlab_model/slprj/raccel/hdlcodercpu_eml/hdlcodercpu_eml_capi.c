#include "__cf_hdlcodercpu_eml.h"
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "hdlcodercpu_eml_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)    
#else
#include "builtin_typeid_types.h"
#include "hdlcodercpu_eml.h"
#include "hdlcodercpu_eml_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST                  
#define TARGET_STRING(s)               (NULL)                    
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 1 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Accumulator" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 0 } , { 1 , 3 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Control Unit" ) , TARGET_STRING ( "" ) ,
12 , 1 , 0 , 0 , 0 } , { 2 , 5 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Instruction Register" ) , TARGET_STRING
( "" ) , 0 , 2 , 0 , 1 , 0 } , { 3 , 7 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Program Counter" ) , TARGET_STRING ( ""
) , 0 , 1 , 0 , 0 , 0 } , { 4 , 8 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Shifter (8-bit)" ) , TARGET_STRING ( ""
) , 0 , 1 , 0 , 2 , 0 } , { 5 , 8 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Shifter (8-bit)" ) , TARGET_STRING ( ""
) , 1 , 0 , 0 , 0 , 0 } , { 6 , 9 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/output_enable" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 7 , 0 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Data Type Conversion" ) , TARGET_STRING
( "" ) , 0 , 3 , 0 , 0 , 0 } , { 8 , 0 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Unit Delay 6" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 0 } , { 9 , 0 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Data Memory/select" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 10 , 0 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Data Memory/Switch1" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 11 , 0 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Data Memory/switch" ) , TARGET_STRING (
"" ) , 0 , 0 , 1 , 0 , 0 } , { 12 , 0 , TARGET_STRING (
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Data Memory/is_new/Compare" ) ,
TARGET_STRING ( "" ) , 0 , 3 , 0 , 0 , 1 } , { 0 , 0 , ( NULL ) , ( NULL ) ,
0 , 0 , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . mara0lwcgp , & rtB . nydvymh33o ,
& rtB . fcetjhhiex , & rtB . gyn0k3gkkt , & rtB . nr2ykwyg2x , & rtB .
ahogxsodi5 , & rtB . kkvw0ptxgn , & rtB . drljjcdixn , & rtB . a5hp1ity41 , &
rtB . aepsxaam4m , & rtB . ml1z4011om , & rtB . iht3vcokcy [ 0 ] , ( void * )
& rtrtC . nvfvuebnci , } ; static int32_T * rtVarDimsAddrMap [ ] = { ( NULL )
} ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "signed char"
, "int8_T" , 0 , 0 , sizeof ( int8_T ) , SS_INT8 , 0 , 0 } , {
"unsigned char" , "uint8_T" , 0 , 0 , sizeof ( uint8_T ) , SS_UINT8 , 0 , 0 }
, { "unsigned short" , "uint16_T" , 0 , 0 , sizeof ( uint16_T ) , SS_UINT16 ,
0 , 0 } , { "unsigned char" , "boolean_T" , 0 , 0 , sizeof ( boolean_T ) ,
SS_BOOLEAN , 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } } ; static
const uint_T rtDimensionArray [ ] = { 1 , 1 , 256 , 1 } ; static const real_T
rtcapiStoredFloats [ ] = { 1.0 , 0.0 } ; static const rtwCAPI_FixPtMap
rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) , rtwCAPI_FIX_RESERVED , 0 , 0 , 0 }
, { ( const void * ) & rtcapiStoredFloats [ 0 ] , ( const void * ) &
rtcapiStoredFloats [ 1 ] , rtwCAPI_FIX_UNIFORM_SCALING , 12 , 0 , 0 } , { (
const void * ) & rtcapiStoredFloats [ 0 ] , ( const void * ) &
rtcapiStoredFloats [ 1 ] , rtwCAPI_FIX_UNIFORM_SCALING , 4 , 0 , 0 } } ;
static const rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( const void * )
& rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , 0
, 0 } , { ( NULL ) , ( NULL ) , - 2 , 0 } } ; static
rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals , 13 , ( NULL )
, 0 , ( NULL ) , 0 } , { ( NULL ) , 0 , ( NULL ) , 0 } , { ( NULL ) , 0 } , {
rtDataTypeMap , rtDimensionMap , rtFixPtMap , rtElementMap , rtSampleTimeMap
, rtDimensionArray } , "float" , { 2021026652U , 2154951595U , 3419749811U ,
2545354943U } , ( NULL ) , 0 } ; const rtwCAPI_ModelMappingStaticInfo *
hdlcodercpu_eml_GetCAPIStaticMap ( ) { return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void hdlcodercpu_eml_InitializeDataMapInfo ( SimStruct * const rtS ) {
rtwCAPI_SetVersion ( ( * rt_dataMapInfoPtr ) . mmi , 1 ) ;
rtwCAPI_SetStaticMap ( ( * rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ;
rtwCAPI_SetLoggingStaticMap ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetDataAddressMap ( ( * rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ;
rtwCAPI_SetVarDimsAddressMap ( ( * rt_dataMapInfoPtr ) . mmi ,
rtVarDimsAddrMap ) ; rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr )
. mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi
, ( NULL ) ) ; rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi ,
0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void hdlcodercpu_eml_host_InitializeDataMapInfo (
hdlcodercpu_eml_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , NULL ) ; rtwCAPI_SetPath (
dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
