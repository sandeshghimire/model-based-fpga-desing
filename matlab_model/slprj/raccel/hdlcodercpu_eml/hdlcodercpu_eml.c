#include "__cf_hdlcodercpu_eml.h"
#include "rt_logging_mmi.h"
#include "hdlcodercpu_eml_capi.h"
#include <math.h>
#include "hdlcodercpu_eml.h"
#include "hdlcodercpu_eml_private.h"
#include "hdlcodercpu_eml_dt.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
const boolean_T gbl_raccel_isMultitasking = 1 ;
#else
const boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
const boolean_T gbl_raccel_tid01eq = 0 ; const int_T gbl_raccel_NumST = 1 ;
const char_T * gbl_raccel_Version = "8.6 (R2014a) 27-Dec-2013" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const char * gblSlvrJacPatternFileName =
"slprj\\raccel\\hdlcodercpu_eml\\hdlcodercpu_eml_Jpattern.mat" ; const int_T
gblNumRootInportBlks = 0 ; const int_T gblNumModelInputs = 0 ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
const int_T gblInportDataTypeIdx [ ] = { - 1 } ; const int_T gblInportDims [
] = { - 1 } ; const int_T gblInportComplex [ ] = { - 1 } ; const int_T
gblInportInterpoFlag [ ] = { - 1 } ; const int_T gblInportContinuous [ ] = {
- 1 } ;
#include "simstruc.h"
#include "fixedpoint.h"
B rtB ; DW rtDW ; static SimStruct model_S ; SimStruct * const rtS = &
model_S ; static int8_T m3r3avbztp ( int8_T a0 ) ; static void ifntsfsts4 (
int8_T u1 , int8_T u2 , uint8_T c_in , int8_T * sum , uint8_T * carry ,
uint8_T * overflow ) ; static int8_T m3r3avbztp ( int8_T a0 ) { return (
int8_T ) ( a0 - 1 ) ; } static void ifntsfsts4 ( int8_T u1 , int8_T u2 ,
uint8_T c_in , int8_T * sum , uint8_T * carry , uint8_T * overflow ) {
int16_T temp_sum ; int16_T tmp ; tmp = ( uint8_T ) u1 ; temp_sum = ( uint8_T
) u2 ; tmp = ( int16_T ) ( ( ( tmp & 512 ) != 0 ? ( int32_T ) ( int16_T ) (
tmp | - 512 ) : ( int32_T ) tmp ) + ( ( temp_sum & 512 ) != 0 ? ( int32_T ) (
int16_T ) ( temp_sum | - 512 ) : ( int32_T ) temp_sum ) ) ; tmp = ( int16_T )
( ( int16_T ) ( tmp & 512 ) != 0 ? ( int32_T ) ( int16_T ) ( tmp | - 512 ) :
( int32_T ) ( int16_T ) ( tmp & 511 ) ) ; tmp = ( int16_T ) ( ( ( int16_T ) (
tmp & 1024 ) != 0 ? ( int32_T ) ( int16_T ) ( tmp | - 1024 ) : ( int32_T ) (
int16_T ) ( tmp & 1023 ) ) + ( ( c_in & 1024 ) != 0 ? ( int32_T ) ( int16_T )
( c_in | - 1024 ) : ( int32_T ) c_in ) ) ; tmp = ( int16_T ) ( ( int16_T ) (
tmp & 1024 ) != 0 ? ( int32_T ) ( int16_T ) ( tmp | - 1024 ) : ( int32_T ) (
int16_T ) ( tmp & 1023 ) ) ; temp_sum = ( int16_T ) ( ( int16_T ) ( tmp & 256
) != 0 ? ( int32_T ) ( int16_T ) ( tmp | - 256 ) : ( int32_T ) ( int16_T ) (
tmp & 255 ) ) ; tmp = ( int16_T ) ( ( uint32_T ) ( ( uint16_T ) temp_sum &
511 ) >> 8 ) ; tmp = ( int16_T ) ( ( int16_T ) ( ( tmp & 256 ) != 0 ? (
int32_T ) ( int16_T ) ( tmp | - 256 ) : ( int32_T ) tmp ) & 1 ) ; * carry = (
uint8_T ) ( ( uint8_T ) ( ( int16_T ) ( tmp & 256 ) != 0 ? ( int32_T ) (
int16_T ) ( tmp | - 256 ) : ( int32_T ) ( int16_T ) ( tmp & 255 ) ) & 1 ) ; *
sum = ( int8_T ) temp_sum ; * overflow = ( uint8_T ) ( ( ( int32_T ) ( (
uint32_T ) ( uint8_T ) u1 >> 7 ) == ( int32_T ) ( ( uint32_T ) ( uint8_T ) u2
>> 7 ) ) && ( ( int32_T ) ( ( uint32_T ) ( uint8_T ) * sum >> 7 ) != (
int32_T ) ( ( uint32_T ) ( uint8_T ) u1 >> 7 ) ) ) ; } void MdlInitialize (
void ) { int32_T i ; rtDW . dbjbvxg23s = 0 ; rtDW . boyw4d0uwn = 0 ; rtDW .
kmbjhnlkaw = ( ( uint8_T ) 0U ) ; rtDW . kcb5h3l2rz = false ; rtDW .
hzjbagfonx = ( ( uint16_T ) 0U ) ; rtDW . gqdvjn31au = 0U ; rtDW . mpui0k5sli
= 0U ; rtDW . hithci51lt = 0U ; rtDW . ecskwlmtwq = 0U ; rtDW . pxavurktwi =
0U ; rtDW . corjqxlsl3 = 0U ; rtDW . b0w1eco2iu = 0 ; rtDW . posk0eizok = 0 ;
rtDW . l0owajfezg = 0 ; rtDW . j3nrtien2t = false ; rtDW . hcle0rjezs = 0 ;
rtDW . ids0ty3k2c = ( ( uint8_T ) 0U ) ; rtDW . aieo2sbtyk = 0U ; for ( i = 0
; i < 256 ; i ++ ) { rtDW . gkfgmh3s00 [ i ] = 0 ; rtDW . l32z4pgrvm [ i ] =
0U ; } rtDW . m0riydqyff = 0U ; } void MdlStart ( void ) { MdlInitialize ( )
; } void MdlOutputs ( int_T tid ) { uint8_T carry ; int8_T diff ; uint8_T
h42i0wdc25 ; int8_T lj3cbnwyhm [ 256 ] ; boolean_T b45akogg43 ; uint8_T
mp34tfvfq0 ; uint8_T fevmy4vdrf ; uint8_T e1gctntp1w ; uint8_T ochqahclmx ;
uint8_T jahfsrzvuj ; int8_T jklpciwtku ; uint8_T nfk0hxcimz ; uint8_T
hqxyqjot52 ; uint8_T fdv1qcr2xm ; int8_T jmalc3llir ; uint16_T pz5gvrbqli ;
int32_T i ; int16_T tmp ; rtB . a5hp1ity41 = rtDW . dbjbvxg23s ; if ( rtDW .
kcb5h3l2rz ) { rtDW . gqdvjn31au = 0U ; } fevmy4vdrf = 0U ; e1gctntp1w = 0U ;
ochqahclmx = rtDW . kmbjhnlkaw ; jahfsrzvuj = 4U ; jklpciwtku = 0 ;
nfk0hxcimz = 3U ; hqxyqjot52 = 3U ; fdv1qcr2xm = 0U ; h42i0wdc25 = 0U ;
mp34tfvfq0 = 0U ; jmalc3llir = 0 ; b45akogg43 = false ; rtB . nydvymh33o = 0U
; switch ( rtDW . gqdvjn31au ) { case 0U : hqxyqjot52 = 0U ; jahfsrzvuj = 0U
; nfk0hxcimz = 0U ; rtDW . mpui0k5sli = rtDW . gqdvjn31au ; rtDW . gqdvjn31au
= 1U ; break ; case 1U : fdv1qcr2xm = 1U ; hqxyqjot52 = 2U ; nfk0hxcimz = 1U
; rtDW . gqdvjn31au = 2U ; break ; case 2U : nfk0hxcimz = 2U ; rtDW .
gqdvjn31au = 3U ; break ; case 3U : rtDW . hithci51lt = ( uint8_T ) ( (
uint32_T ) rtDW . hzjbagfonx >> 9 ) ; rtDW . ecskwlmtwq = ( uint8_T ) ( (
int32_T ) ( ( uint32_T ) rtDW . hzjbagfonx >> 3 ) & 63 ) ; rtDW . pxavurktwi
= ( uint8_T ) ( rtDW . hzjbagfonx & 255 ) ; rtDW . gqdvjn31au = 4U ; break ;
case 4U : rtDW . mpui0k5sli = rtDW . gqdvjn31au ; switch ( rtDW . hithci51lt
) { case 0U : h42i0wdc25 = rtDW . pxavurktwi ; rtDW . gqdvjn31au = 13U ;
break ; case 1U : h42i0wdc25 = rtDW . pxavurktwi ; rtDW . gqdvjn31au = 15U ;
break ; case 2U : h42i0wdc25 = rtDW . pxavurktwi ; rtDW . gqdvjn31au = 17U ;
break ; case 3U : h42i0wdc25 = rtDW . pxavurktwi ; rtDW . gqdvjn31au = 19U ;
break ; case 4U : switch ( ( uint8_T ) ( ( int32_T ) ( ( uint32_T ) rtDW .
ecskwlmtwq >> 5 ) & 1 ) ) { case 0U : diff = ( int8_T ) rtDW . pxavurktwi ;
jmalc3llir = ( int8_T ) ( ( ( int8_T ) ( diff & 64 ) != 0 ? ( int32_T ) (
int8_T ) ( diff | - 64 ) : ( int32_T ) ( int8_T ) ( diff & 63 ) ) - 1 ) ;
hqxyqjot52 = 1U ; break ; case 1U : jklpciwtku = ( int8_T ) rtDW . pxavurktwi
; jahfsrzvuj = 1U ; break ; } rtDW . gqdvjn31au = 1U ; break ; case 5U :
h42i0wdc25 = rtDW . pxavurktwi ; if ( ( ( int32_T ) ( ( uint32_T ) rtDW .
ecskwlmtwq >> 5 ) & 1 ) != 0 ) { rtDW . gqdvjn31au = 21U ; } else {
mp34tfvfq0 = 1U ; rtDW . gqdvjn31au = 25U ; } break ; case 6U : switch ( (
uint8_T ) ( ( int32_T ) ( ( uint32_T ) rtDW . ecskwlmtwq >> 5 ) & 1 ) ) {
case 0U : if ( ( ( int32_T ) ( ( uint32_T ) rtDW . kmbjhnlkaw >> 3 ) & 1 ) !=
0 ) { diff = ( int8_T ) rtDW . pxavurktwi ; jmalc3llir = ( int8_T ) ( ( (
int8_T ) ( diff & 64 ) != 0 ? ( int32_T ) ( int8_T ) ( diff | - 64 ) : (
int32_T ) ( int8_T ) ( diff & 63 ) ) - 1 ) ; hqxyqjot52 = 1U ; } break ; case
1U : if ( ( ( int32_T ) ( ( uint32_T ) rtDW . kmbjhnlkaw >> 2 ) & 1 ) != 0 )
{ diff = ( int8_T ) rtDW . pxavurktwi ; jmalc3llir = m3r3avbztp ( ( int8_T )
( ( int8_T ) ( diff & 64 ) != 0 ? ( int32_T ) ( int8_T ) ( diff | - 64 ) : (
int32_T ) ( int8_T ) ( diff & 63 ) ) ) ; hqxyqjot52 = 1U ; } break ; } rtDW .
gqdvjn31au = 15U ; break ; case 7U : rtDW . gqdvjn31au = 1U ; if ( ( ( (
int32_T ) ( ( uint32_T ) rtDW . ecskwlmtwq >> 3 ) & 1 ) != 0 ) == 0 ) {
switch ( ( uint8_T ) ( ( int32_T ) ( ( uint32_T ) rtDW . ecskwlmtwq >> 5 ) &
1 ) ) { case 0U : if ( ( ( int32_T ) ( ( uint32_T ) rtDW . kmbjhnlkaw >> 1 )
& 1 ) != 0 ) { diff = ( int8_T ) rtDW . pxavurktwi ; jmalc3llir = m3r3avbztp
( ( int8_T ) ( ( int8_T ) ( diff & 64 ) != 0 ? ( int32_T ) ( int8_T ) ( diff
| - 64 ) : ( int32_T ) ( int8_T ) ( diff & 63 ) ) ) ; hqxyqjot52 = 1U ; }
break ; case 1U : if ( ( rtDW . kmbjhnlkaw & 1 ) != 0 ) { diff = ( int8_T )
rtDW . pxavurktwi ; jmalc3llir = m3r3avbztp ( ( int8_T ) ( ( int8_T ) ( diff
& 64 ) != 0 ? ( int32_T ) ( int8_T ) ( diff | - 64 ) : ( int32_T ) ( int8_T )
( diff & 63 ) ) ) ; hqxyqjot52 = 1U ; } break ; } } switch ( rtDW .
ecskwlmtwq ) { case 8U : rtB . nydvymh33o = 1U ; rtDW . gqdvjn31au = 22U ;
break ; case 9U : jahfsrzvuj = 0U ; break ; case 10U : e1gctntp1w = 4U ;
fevmy4vdrf = 3U ; rtDW . gqdvjn31au = 6U ; break ; case 11U : e1gctntp1w = 5U
; fevmy4vdrf = 3U ; break ; case 12U : fevmy4vdrf = 1U ; rtDW . gqdvjn31au =
6U ; break ; case 13U : fevmy4vdrf = 2U ; rtDW . gqdvjn31au = 6U ; break ;
case 14U : h42i0wdc25 = MAX_uint8_T ; rtDW . gqdvjn31au = 12U ; break ; case
15U : e1gctntp1w = 7U ; fevmy4vdrf = 3U ; break ; default : rtDW . gqdvjn31au
= 1U ; break ; } break ; } break ; case 6U : jahfsrzvuj = 2U ; rtDW .
mpui0k5sli = rtDW . gqdvjn31au ; rtDW . gqdvjn31au = 1U ; break ; case 7U :
h42i0wdc25 = rtDW . corjqxlsl3 ; rtDW . mpui0k5sli = rtDW . gqdvjn31au ; rtDW
. gqdvjn31au = 13U ; break ; case 8U : h42i0wdc25 = rtDW . corjqxlsl3 ; rtDW
. mpui0k5sli = rtDW . gqdvjn31au ; rtDW . gqdvjn31au = 15U ; break ; case 9U
: h42i0wdc25 = rtDW . corjqxlsl3 ; rtDW . mpui0k5sli = rtDW . gqdvjn31au ;
rtDW . gqdvjn31au = 17U ; break ; case 10U : h42i0wdc25 = rtDW . corjqxlsl3 ;
rtDW . mpui0k5sli = rtDW . gqdvjn31au ; rtDW . gqdvjn31au = 19U ; break ;
case 11U : diff = rtDW . boyw4d0uwn ; if ( rtDW . boyw4d0uwn < 0 ) { diff = 0
; } h42i0wdc25 = ( uint8_T ) diff ; mp34tfvfq0 = 1U ; rtDW . mpui0k5sli =
rtDW . gqdvjn31au ; rtDW . gqdvjn31au = 1U ; break ; case 12U : b45akogg43 =
true ; rtDW . mpui0k5sli = rtDW . gqdvjn31au ; rtDW . gqdvjn31au = 1U ; break
; case 13U : e1gctntp1w = 6U ; fevmy4vdrf = 3U ; if ( rtDW . mpui0k5sli == 4
) { rtDW . mpui0k5sli = rtDW . gqdvjn31au ; rtDW . gqdvjn31au = 14U ; } else
{ rtDW . mpui0k5sli = rtDW . gqdvjn31au ; rtDW . gqdvjn31au = 6U ; } break ;
case 14U : jahfsrzvuj = 2U ; rtDW . mpui0k5sli = rtDW . gqdvjn31au ; if ( ( (
int32_T ) ( ( uint32_T ) rtDW . ecskwlmtwq >> 5 ) & 1 ) != 0 ) { diff = rtDW
. boyw4d0uwn ; if ( rtDW . boyw4d0uwn < 0 ) { diff = 0 ; } rtDW . corjqxlsl3
= ( uint8_T ) diff ; rtDW . gqdvjn31au = 7U ; } else { rtDW . gqdvjn31au =
25U ; } break ; case 15U : e1gctntp1w = 1U ; fevmy4vdrf = 3U ; if ( rtDW .
mpui0k5sli == 4 ) { rtDW . mpui0k5sli = rtDW . gqdvjn31au ; rtDW . gqdvjn31au
= 16U ; } else { rtDW . mpui0k5sli = rtDW . gqdvjn31au ; rtDW . gqdvjn31au =
6U ; } break ; case 16U : jahfsrzvuj = 2U ; rtDW . mpui0k5sli = rtDW .
gqdvjn31au ; if ( ( ( int32_T ) ( ( uint32_T ) rtDW . ecskwlmtwq >> 5 ) & 1 )
!= 0 ) { diff = rtDW . boyw4d0uwn ; if ( rtDW . boyw4d0uwn < 0 ) { diff = 0 ;
} rtDW . corjqxlsl3 = ( uint8_T ) diff ; rtDW . gqdvjn31au = 8U ; } else {
rtDW . gqdvjn31au = 25U ; } break ; case 17U : e1gctntp1w = 2U ; fevmy4vdrf =
3U ; if ( rtDW . mpui0k5sli == 4 ) { rtDW . mpui0k5sli = rtDW . gqdvjn31au ;
rtDW . gqdvjn31au = 18U ; } else { rtDW . mpui0k5sli = rtDW . gqdvjn31au ;
rtDW . gqdvjn31au = 6U ; } break ; case 18U : jahfsrzvuj = 2U ; rtDW .
mpui0k5sli = rtDW . gqdvjn31au ; if ( ( ( int32_T ) ( ( uint32_T ) rtDW .
ecskwlmtwq >> 5 ) & 1 ) != 0 ) { diff = rtDW . boyw4d0uwn ; if ( rtDW .
boyw4d0uwn < 0 ) { diff = 0 ; } rtDW . corjqxlsl3 = ( uint8_T ) diff ; rtDW .
gqdvjn31au = 9U ; } else { rtDW . gqdvjn31au = 25U ; } break ; case 19U :
e1gctntp1w = 3U ; fevmy4vdrf = 3U ; if ( rtDW . mpui0k5sli == 4 ) { rtDW .
mpui0k5sli = rtDW . gqdvjn31au ; rtDW . gqdvjn31au = 20U ; } else { rtDW .
mpui0k5sli = rtDW . gqdvjn31au ; rtDW . gqdvjn31au = 6U ; } break ; case 20U
: jahfsrzvuj = 2U ; rtDW . mpui0k5sli = rtDW . gqdvjn31au ; if ( ( ( int32_T
) ( ( uint32_T ) rtDW . ecskwlmtwq >> 5 ) & 1 ) != 0 ) { diff = rtDW .
boyw4d0uwn ; if ( rtDW . boyw4d0uwn < 0 ) { diff = 0 ; } rtDW . corjqxlsl3 =
( uint8_T ) diff ; rtDW . gqdvjn31au = 10U ; } else { rtDW . gqdvjn31au = 25U
; } break ; case 21U : rtDW . gqdvjn31au = 11U ; break ; case 22U : rtB .
nydvymh33o = 1U ; rtDW . gqdvjn31au = 22U ; break ; default : rtDW .
mpui0k5sli = rtDW . gqdvjn31au ; rtDW . gqdvjn31au = 1U ; break ; } if ( rtB
. nydvymh33o != 0 ) { ssSetStopRequested ( rtS , 1 ) ; } rtB . mara0lwcgp =
rtDW . posk0eizok ; switch ( jahfsrzvuj ) { case 0U : rtDW . posk0eizok = 0 ;
break ; case 1U : rtDW . posk0eizok = jklpciwtku ; break ; case 2U : rtDW .
posk0eizok = rtDW . b0w1eco2iu ; break ; case 3U : break ; } if ( rtDW .
j3nrtien2t && rtrtC . nvfvuebnci ) { rtB . ml1z4011om = rtDW . l0owajfezg ; }
else { rtB . ml1z4011om = rtDW . hcle0rjezs ; } carry = ( uint8_T ) ( (
int32_T ) ( ( uint32_T ) ochqahclmx >> 3 ) & 1 ) ; ochqahclmx = ( uint8_T ) (
( int32_T ) ( ( uint32_T ) ochqahclmx >> 1 ) & 1 ) ; diff = rtB . mara0lwcgp
; switch ( e1gctntp1w ) { case 0U : break ; case 1U : diff = ( int8_T ) ( rtB
. ml1z4011om & rtB . mara0lwcgp ) ; break ; case 2U : ifntsfsts4 ( rtB .
mara0lwcgp , rtB . ml1z4011om , carry , & diff , & jahfsrzvuj , & ochqahclmx
) ; carry = jahfsrzvuj ; break ; case 3U : ifntsfsts4 ( rtB . mara0lwcgp , (
int8_T ) ~ rtB . ml1z4011om , ( uint8_T ) ( ( uint8_T ) ~ carry & 1 ) , &
diff , & jahfsrzvuj , & ochqahclmx ) ; carry = jahfsrzvuj ; break ; case 4U :
diff = ( int8_T ) ~ rtB . mara0lwcgp ; break ; case 5U : carry = ( uint8_T )
( ( uint8_T ) ~ carry & 1 ) ; break ; case 6U : diff = rtB . ml1z4011om ;
break ; case 7U : carry = 0U ; break ; } e1gctntp1w = ( uint8_T ) ( ( ( ( ( (
( carry & 3 ) << 1 & 3 ) | ( int32_T ) ( ( uint32_T ) ( uint8_T ) diff >> 7 )
) & 3 ) << 1 | ( ochqahclmx & 7 ) ) & 7 ) << 1 | ! ( diff != 0 ) ) ; rtB .
aepsxaam4m = rtDW . gkfgmh3s00 [ h42i0wdc25 ] ; memcpy ( & lj3cbnwyhm [ 0 ] ,
& rtDW . gkfgmh3s00 [ 0 ] , sizeof ( int8_T ) << 8U ) ; lj3cbnwyhm [
h42i0wdc25 ] = rtB . mara0lwcgp ; rtB . drljjcdixn = ( mp34tfvfq0 != 0 ) ;
for ( i = 0 ; i < 256 ; i ++ ) { if ( rtB . drljjcdixn ) { rtB . iht3vcokcy [
i ] = lj3cbnwyhm [ i ] ; } else { rtB . iht3vcokcy [ i ] = rtDW . gkfgmh3s00
[ i ] ; } } rtB . gyn0k3gkkt = rtDW . aieo2sbtyk ; switch ( hqxyqjot52 ) {
case 0U : rtDW . aieo2sbtyk = 0U ; break ; case 1U : tmp = ( int16_T ) ( ( (
int16_T ) ( jmalc3llir & 256 ) != 0 ? ( int32_T ) ( int16_T ) ( jmalc3llir |
- 256 ) : ( int32_T ) ( int16_T ) ( jmalc3llir & 255 ) ) + ( ( rtDW .
ids0ty3k2c & 256 ) != 0 ? ( int32_T ) ( int16_T ) ( rtDW . ids0ty3k2c | - 256
) : ( int32_T ) rtDW . ids0ty3k2c ) ) ; rtDW . aieo2sbtyk = ( uint8_T ) ( (
int16_T ) ( tmp & 256 ) != 0 ? ( int32_T ) ( int16_T ) ( tmp | - 256 ) : (
int32_T ) ( int16_T ) ( tmp & 255 ) ) ; break ; case 2U : rtDW . aieo2sbtyk
++ ; break ; } rtDW . l32z4pgrvm [ 0 ] = 2314U ; rtDW . l32z4pgrvm [ 1 ] =
2560U ; rtDW . l32z4pgrvm [ 2 ] = 2316U ; rtDW . l32z4pgrvm [ 3 ] = 2561U ;
rtDW . l32z4pgrvm [ 4 ] = 2322U ; rtDW . l32z4pgrvm [ 5 ] = 2572U ; rtDW .
l32z4pgrvm [ 6 ] = 2310U ; rtDW . l32z4pgrvm [ 7 ] = 2573U ; rtDW .
l32z4pgrvm [ 8 ] = 2323U ; rtDW . l32z4pgrvm [ 9 ] = 2574U ; rtDW .
l32z4pgrvm [ 10 ] = 2555U ; rtDW . l32z4pgrvm [ 11 ] = 2575U ; rtDW .
l32z4pgrvm [ 12 ] = 2319U ; rtDW . l32z4pgrvm [ 13 ] = 2576U ; rtDW .
l32z4pgrvm [ 14 ] = 2558U ; rtDW . l32z4pgrvm [ 15 ] = 2577U ; rtDW .
l32z4pgrvm [ 16 ] = 2306U ; rtDW . l32z4pgrvm [ 17 ] = 2578U ; rtDW .
l32z4pgrvm [ 18 ] = 2315U ; rtDW . l32z4pgrvm [ 19 ] = 2579U ; rtDW .
l32z4pgrvm [ 20 ] = 2324U ; rtDW . l32z4pgrvm [ 21 ] = 2580U ; rtDW .
l32z4pgrvm [ 22 ] = 2314U ; rtDW . l32z4pgrvm [ 23 ] = 2581U ; rtDW .
l32z4pgrvm [ 24 ] = 2305U ; rtDW . l32z4pgrvm [ 25 ] = 2562U ; rtDW .
l32z4pgrvm [ 26 ] = 2305U ; rtDW . l32z4pgrvm [ 27 ] = 2563U ; rtDW .
l32z4pgrvm [ 28 ] = 2305U ; rtDW . l32z4pgrvm [ 29 ] = 2564U ; rtDW .
l32z4pgrvm [ 30 ] = 2U ; rtDW . l32z4pgrvm [ 31 ] = 3704U ; rtDW . l32z4pgrvm
[ 32 ] = 1540U ; rtDW . l32z4pgrvm [ 33 ] = 3704U ; rtDW . l32z4pgrvm [ 34 ]
= 1025U ; rtDW . l32z4pgrvm [ 35 ] = 2565U ; rtDW . l32z4pgrvm [ 36 ] = 261U
; rtDW . l32z4pgrvm [ 37 ] = 2566U ; rtDW . l32z4pgrvm [ 38 ] = 2U ; rtDW .
l32z4pgrvm [ 39 ] = 3704U ; rtDW . l32z4pgrvm [ 40 ] = 1025U ; rtDW .
l32z4pgrvm [ 41 ] = 2567U ; rtDW . l32z4pgrvm [ 42 ] = 263U ; rtDW .
l32z4pgrvm [ 43 ] = 3704U ; rtDW . l32z4pgrvm [ 44 ] = 1542U ; rtDW .
l32z4pgrvm [ 45 ] = 3330U ; rtDW . l32z4pgrvm [ 46 ] = 2055U ; rtDW .
l32z4pgrvm [ 47 ] = 2304U ; rtDW . l32z4pgrvm [ 48 ] = 2563U ; rtDW .
l32z4pgrvm [ 49 ] = 263U ; rtDW . l32z4pgrvm [ 50 ] = 2821U ; rtDW .
l32z4pgrvm [ 51 ] = 6U ; rtDW . l32z4pgrvm [ 52 ] = 2823U ; rtDW . l32z4pgrvm
[ 53 ] = 2305U ; rtDW . l32z4pgrvm [ 54 ] = 3704U ; rtDW . l32z4pgrvm [ 55 ]
= 1026U ; rtDW . l32z4pgrvm [ 56 ] = 2562U ; rtDW . l32z4pgrvm [ 57 ] = 0U ;
rtDW . l32z4pgrvm [ 58 ] = 3704U ; rtDW . l32z4pgrvm [ 59 ] = 1538U ; rtDW .
l32z4pgrvm [ 60 ] = 3842U ; rtDW . l32z4pgrvm [ 61 ] = 2271U ; rtDW .
l32z4pgrvm [ 62 ] = 2305U ; rtDW . l32z4pgrvm [ 63 ] = 2564U ; rtDW .
l32z4pgrvm [ 64 ] = 3U ; rtDW . l32z4pgrvm [ 65 ] = 3704U ; rtDW . l32z4pgrvm
[ 66 ] = 1540U ; rtDW . l32z4pgrvm [ 67 ] = 3842U ; rtDW . l32z4pgrvm [ 68 ]
= 2260U ; rtDW . l32z4pgrvm [ 69 ] = 2304U ; rtDW . l32z4pgrvm [ 70 ] = 2562U
; rtDW . l32z4pgrvm [ 71 ] = 257U ; rtDW . l32z4pgrvm [ 72 ] = 2815U ; rtDW .
l32z4pgrvm [ 73 ] = 3696U ; rtDW . l32z4pgrvm [ 74 ] = 2305U ; rtDW .
l32z4pgrvm [ 75 ] = 3704U ; rtDW . l32z4pgrvm [ 76 ] = 1025U ; rtDW .
l32z4pgrvm [ 77 ] = 2561U ; rtDW . l32z4pgrvm [ 78 ] = 2305U ; rtDW .
l32z4pgrvm [ 79 ] = 3704U ; rtDW . l32z4pgrvm [ 80 ] = 1026U ; rtDW .
l32z4pgrvm [ 81 ] = 2562U ; rtDW . l32z4pgrvm [ 82 ] = 0U ; rtDW . l32z4pgrvm
[ 83 ] = 3704U ; rtDW . l32z4pgrvm [ 84 ] = 1538U ; rtDW . l32z4pgrvm [ 85 ]
= 3842U ; rtDW . l32z4pgrvm [ 86 ] = 2289U ; rtDW . l32z4pgrvm [ 87 ] = 3648U
; if ( fdv1qcr2xm == 1 ) { i = ( int32_T ) ( rtB . gyn0k3gkkt + 1U ) ; if ( (
uint32_T ) i > 255U ) { i = 255 ; } pz5gvrbqli = rtDW . l32z4pgrvm [ i - 1 ]
; } else { pz5gvrbqli = 0U ; } rtB . fcetjhhiex = 0U ; switch ( nfk0hxcimz )
{ case 0U : rtDW . m0riydqyff = 0U ; break ; case 1U : rtDW . m0riydqyff =
pz5gvrbqli ; break ; case 2U : rtB . fcetjhhiex = rtDW . m0riydqyff ; break ;
} ochqahclmx = ( uint8_T ) ( ( int32_T ) ( ( uint32_T ) e1gctntp1w >> 1 ) & 1
) ; jahfsrzvuj = ( uint8_T ) ( ( uint32_T ) e1gctntp1w >> 3 ) ; switch (
fevmy4vdrf ) { case 1U : jklpciwtku = ( int8_T ) ( diff << 1 ) ; jahfsrzvuj =
( uint8_T ) ( ( uint32_T ) ( uint8_T ) diff >> 7 ) ; ochqahclmx = ( uint8_T )
( ( ( int32_T ) ( ( uint32_T ) ( uint8_T ) diff >> 6 ) & 1 ) ^ ( int32_T ) (
( uint32_T ) ( uint8_T ) diff >> 7 ) ) ; break ; case 2U : jklpciwtku = (
int8_T ) ( diff >> 1 ) ; break ; default : jklpciwtku = diff ; break ; } rtB
. nr2ykwyg2x = ( uint8_T ) ( ( ( jahfsrzvuj << 1 | ( int32_T ) ( ( uint32_T )
( uint8_T ) jklpciwtku >> 7 ) ) << 1 | ochqahclmx ) << 1 | ! ( jklpciwtku !=
0 ) ) ; rtB . ahogxsodi5 = jklpciwtku ; rtB . kkvw0ptxgn = 0 ; if (
b45akogg43 ) { rtB . kkvw0ptxgn = rtB . ml1z4011om ; } UNUSED_PARAMETER ( tid
) ; } void MdlUpdate ( int_T tid ) { rtDW . dbjbvxg23s = rtB . kkvw0ptxgn ;
rtDW . boyw4d0uwn = rtB . ml1z4011om ; rtDW . kmbjhnlkaw = rtB . nr2ykwyg2x ;
rtDW . kcb5h3l2rz = false ; rtDW . hzjbagfonx = rtB . fcetjhhiex ; rtDW .
b0w1eco2iu = rtB . ahogxsodi5 ; rtDW . l0owajfezg = rtB . mara0lwcgp ; rtDW .
j3nrtien2t = rtB . drljjcdixn ; rtDW . hcle0rjezs = rtB . aepsxaam4m ; memcpy
( & rtDW . gkfgmh3s00 [ 0 ] , & rtB . iht3vcokcy [ 0 ] , sizeof ( int8_T ) <<
8U ) ; rtDW . ids0ty3k2c = rtB . gyn0k3gkkt ; UNUSED_PARAMETER ( tid ) ; }
void MdlTerminate ( void ) { } void MdlInitializeSizes ( void ) {
ssSetNumContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 0 ) ; ssSetNumU ( rtS , 0
) ; ssSetDirectFeedThrough ( rtS , 0 ) ; ssSetNumSampleTimes ( rtS , 1 ) ;
ssSetNumBlocks ( rtS , 44 ) ; ssSetNumBlockIO ( rtS , 12 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 1.0 ) ;
ssSetOffsetTime ( rtS , 0 , 0.0 ) ; } void raccel_set_checksum ( SimStruct *
rtS ) { ssSetChecksumVal ( rtS , 0 , 2021026652U ) ; ssSetChecksumVal ( rtS ,
1 , 2154951595U ) ; ssSetChecksumVal ( rtS , 2 , 3419749811U ) ;
ssSetChecksumVal ( rtS , 3 , 2545354943U ) ; } SimStruct *
raccel_register_model ( void ) { static struct _ssMdlInfo mdlInfo ; ( void )
memset ( ( char * ) rtS , 0 , sizeof ( SimStruct ) ) ; ( void ) memset ( (
char * ) & mdlInfo , 0 , sizeof ( struct _ssMdlInfo ) ) ; ssSetMdlInfoPtr (
rtS , & mdlInfo ) ; { static time_T mdlPeriod [ NSAMPLE_TIMES ] ; static
time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T mdlTaskTimes [
NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ; static int_T
mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T mdlTNextWasAdjustedPtr [
NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits [ NSAMPLE_TIMES *
NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [ NSAMPLE_TIMES ] ; {
int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) { mdlPeriod [ i ] = 0.0 ;
mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ; mdlTsMap [ i ] = i ;
mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS , & mdlPeriod [ 0 ] )
; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ; ssSetSampleTimeTaskIDPtr (
rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , & mdlTaskTimes [ 0 ] ) ;
ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ; ssSetTNextWasAdjustedPtr
( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ; ssSetPerTaskSampleHitsPtr ( rtS ,
& mdlPerTaskSampleHits [ 0 ] ) ; ssSetTimeOfNextSampleHitPtr ( rtS , &
mdlTimeOfNextSampleHit [ 0 ] ) ; } ssSetSolverMode ( rtS ,
SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS , ( ( void * ) & rtB ) ) ;
( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof ( B ) ) ; } { void *
dwork = ( void * ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset
( dwork , 0 , sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void
) memset ( ( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ;
ssSetModelMappingInfo ( rtS , & dtInfo ) ; dtInfo . numDataTypes = 19 ;
dtInfo . dataTypeSizes = & rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = &
rtDataTypeNames [ 0 ] ; dtInfo . B = & rtBTransTable ; }
hdlcodercpu_eml_InitializeDataMapInfo ( rtS ) ; ssSetIsRapidAcceleratorActive
( rtS , true ) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS ,
SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS , "hdlcodercpu_eml" ) ;
ssSetPath ( rtS , "hdlcodercpu_eml" ) ; ssSetTStart ( rtS , 0.0 ) ;
ssSetTFinal ( rtS , 1.0E+7 ) ; ssSetStepSize ( rtS , 1.0 ) ;
ssSetFixedStepSize ( rtS , 1.0 ) ; { static RTWLogInfo rt_DataLoggingInfo ;
ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ; } { { static int_T
rt_LoggedStateWidths [ ] = { 1 , 1 , 1 , 1 , 1 , 256 , 1 , 1 , 1 } ; static
int_T rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 }
; static int_T rt_LoggedStateDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 256 , 1 ,
1 , 1 } ; static boolean_T rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 } ; static BuiltInDTypeId rt_LoggedStateDataTypeIds [ ] = {
SS_INT8 , SS_INT8 , SS_INT8 , SS_INT8 , SS_INT8 , SS_INT8 , SS_UINT8 ,
SS_BOOLEAN , SS_BOOLEAN } ; static int_T rt_LoggedStateComplexSignals [ ] = {
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static const char_T *
rt_LoggedStateLabels [ ] = { "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" ,
"DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" , "DSTATE" } ; static const char_T
* rt_LoggedStateBlockNames [ ] = {
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Unit Delay 6" ,
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Unit Delay 5" ,
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Unit Delay2" ,
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Data Memory/din_d" ,
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Data Memory/ram_data" ,
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Data Memory/ram" ,
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Unit Delay 4" ,
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Unit Delay 7" ,
"hdlcodercpu_eml/CPU_Subsystem_8_bit/Data Memory/we_d" } ; static const
char_T * rt_LoggedStateNames [ ] = { "" , "" , "" , "" , "" , "" , "" , "" ,
"" } ; static boolean_T rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 } ; static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] =
{ { 0 , SS_INT8 , SS_INT8 , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_INT8 ,
SS_INT8 , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_INT8 , SS_INT8 , 0 , 0 , 0 ,
1.0 , 0 , 0.0 } , { 0 , SS_INT8 , SS_INT8 , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0
, SS_INT8 , SS_INT8 , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_INT8 , SS_INT8 ,
0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_UINT8 , SS_UINT8 , 0 , 0 , 0 , 1.0 , 0
, 0.0 } , { 0 , SS_BOOLEAN , SS_BOOLEAN , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_BOOLEAN , SS_BOOLEAN , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static
RTWLogSignalInfo rt_LoggedStateSignalInfo = { 9 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , { rt_LoggedStateLabels } , ( NULL )
, ( NULL ) , ( NULL ) , { rt_LoggedStateBlockNames } , { rt_LoggedStateNames
} , rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert } ; static void *
rt_LoggedStateSignalPtrs [ 9 ] ; rtliSetLogXSignalPtrs ( ssGetRTWLogInfo (
rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtDW . dbjbvxg23s ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtDW . boyw4d0uwn ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtDW . b0w1eco2iu ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtDW . l0owajfezg ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) & rtDW . hcle0rjezs ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) rtDW . gkfgmh3s00 ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) & rtDW . ids0ty3k2c ;
rt_LoggedStateSignalPtrs [ 7 ] = ( void * ) & rtDW . kcb5h3l2rz ;
rt_LoggedStateSignalPtrs [ 8 ] = ( void * ) & rtDW . j3nrtien2t ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "tmp_raccel_xout" ) ; rtliSetLogXFinal (
ssGetRTWLogInfo ( rtS ) , "xFinal" ) ; rtliSetLogVarNameModifier (
ssGetRTWLogInfo ( rtS ) , "none" ) ; rtliSetLogFormat ( ssGetRTWLogInfo ( rtS
) , 2 ) ; rtliSetLogMaxRows ( ssGetRTWLogInfo ( rtS ) , 1000 ) ;
rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS ) , 1 ) ; rtliSetLogY (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogYSignalInfo ( ssGetRTWLogInfo (
rtS ) , ( NULL ) ) ; rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL
) ) ; } { static ssSolverInfo slvrInfo ; ssSetSolverInfo ( rtS , & slvrInfo )
; ssSetSolverName ( rtS , "FixedStepDiscrete" ) ; ssSetVariableStepSolver (
rtS , 0 ) ; ssSetSolverConsistencyChecking ( rtS , 0 ) ;
ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ; ssSetSolverRobustResetMethod (
rtS , 0 ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelLogData ( rtS , rt_UpdateTXYLogVars ) ; ssSetModelUpdate ( rtS
, MdlUpdate ) ; ssSetTNextTid ( rtS , INT_MIN ) ; ssSetTNext ( rtS ,
rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ; ssSetNumNonsampledZCs ( rtS ,
0 ) ; } ssSetChecksumVal ( rtS , 0 , 2021026652U ) ; ssSetChecksumVal ( rtS ,
1 , 2154951595U ) ; ssSetChecksumVal ( rtS , 2 , 3419749811U ) ;
ssSetChecksumVal ( rtS , 3 , 2545354943U ) ; { static const sysRanDType
rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo
; static const sysRanDType * systemRan [ 10 ] ; ssSetRTWExtModeInfo ( rtS , &
rt_ExtModeInfo ) ; rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo ,
systemRan ) ; systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = &
rtAlwaysEnabled ; systemRan [ 2 ] = & rtAlwaysEnabled ; systemRan [ 3 ] = &
rtAlwaysEnabled ; systemRan [ 4 ] = & rtAlwaysEnabled ; systemRan [ 5 ] = &
rtAlwaysEnabled ; systemRan [ 6 ] = & rtAlwaysEnabled ; systemRan [ 7 ] = &
rtAlwaysEnabled ; systemRan [ 8 ] = & rtAlwaysEnabled ; systemRan [ 9 ] = &
rtAlwaysEnabled ; rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) ,
& ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo
( rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS
) , ssGetTPtr ( rtS ) ) ; } return rtS ; }
