#include "__cf_gm_hdlcodercpu_eml.h"
#include <math.h>
#include "gm_hdlcodercpu_eml_acc.h"
#include "gm_hdlcodercpu_eml_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
static void mdlOutputs ( SimStruct * S , int_T tid ) { int8_T iiv0vknbg2 [
256 ] ; int32_T i ; n3qi1whofz * _rtB ; ew10rzwqr2 * _rtDW ; _rtDW = ( (
ew10rzwqr2 * ) ssGetRootDWork ( S ) ) ; _rtB = ( ( n3qi1whofz * )
_ssGetBlockIO ( S ) ) ; _rtB -> jxqnpmyj1d = _rtDW -> dbjbvxg23s ;
ssCallAccelRunBlock ( S , 9 , 1 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> j4tg3gvg10
= _rtDW -> boyw4d0uwn ; _rtB -> gonuz25y0l = _rtDW -> kmbjhnlkaw ; _rtB ->
ievbcyiwpt = _rtDW -> kcb5h3l2rz ; _rtB -> lp5m2voxsb = _rtDW -> hzjbagfonx ;
ssCallAccelRunBlock ( S , 2 , 0 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock
( S , 9 , 7 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 9 , 10 ,
SS_CALL_MDL_OUTPUTS ) ; if ( _rtB -> n0fxkx3igu != 0 ) { ssSetStopRequested (
S , 1 ) ; } _rtB -> irb04sikld = _rtDW -> b0w1eco2iu ; ssCallAccelRunBlock (
S , 0 , 0 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 9 , 15 ,
SS_CALL_MDL_OUTPUTS ) ; if ( _rtDW -> j3nrtien2t && kesz3x3i1i ( S ) ->
jjfnladgn2 ) { _rtB -> e5s1vpy01q = _rtDW -> l0owajfezg ; } else { _rtB ->
e5s1vpy01q = _rtDW -> hcle0rjezs ; } ssCallAccelRunBlock ( S , 1 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> icewohorxa = _rtDW -> gkfgmh3s00 [ _rtB ->
fsrguwnbra ] ; memcpy ( & iiv0vknbg2 [ 0 ] , & _rtDW -> gkfgmh3s00 [ 0 ] ,
sizeof ( int8_T ) << 8U ) ; iiv0vknbg2 [ _rtB -> fsrguwnbra ] = _rtB ->
hluwtw3z01 ; _rtB -> bo0myam1sm = ( _rtB -> nll5flirvv != 0 ) ; for ( i = 0 ;
i < 256 ; i ++ ) { if ( _rtB -> bo0myam1sm ) { _rtB -> iwjcsjdomt [ i ] =
iiv0vknbg2 [ i ] ; } else { _rtB -> iwjcsjdomt [ i ] = _rtDW -> gkfgmh3s00 [
i ] ; } } _rtB -> bn4bhgu514 = _rtDW -> ids0ty3k2c ; ssCallAccelRunBlock ( S
, 5 , 0 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 6 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 3 , 0 , SS_CALL_MDL_OUTPUTS
) ; ssCallAccelRunBlock ( S , 4 , 0 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 7 , 0 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock
( S , 8 , 0 , SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { n3qi1whofz * _rtB ;
ew10rzwqr2 * _rtDW ; _rtDW = ( ( ew10rzwqr2 * ) ssGetRootDWork ( S ) ) ; _rtB
= ( ( n3qi1whofz * ) _ssGetBlockIO ( S ) ) ; _rtDW -> dbjbvxg23s = _rtB ->
nan2ltyzvm ; _rtDW -> boyw4d0uwn = _rtB -> e5s1vpy01q ; _rtDW -> kmbjhnlkaw =
_rtB -> a2kqxl4dop ; _rtDW -> kcb5h3l2rz = _rtB -> oozsmxdfj1 ; _rtDW ->
hzjbagfonx = _rtB -> cchrrtdq1u ; _rtDW -> b0w1eco2iu = _rtB -> omnmjcqruy ;
_rtDW -> l0owajfezg = _rtB -> hluwtw3z01 ; _rtDW -> j3nrtien2t = _rtB ->
bo0myam1sm ; _rtDW -> hcle0rjezs = _rtB -> icewohorxa ; memcpy ( & _rtDW ->
gkfgmh3s00 [ 0 ] , & _rtB -> iwjcsjdomt [ 0 ] , sizeof ( int8_T ) << 8U ) ;
_rtDW -> ids0ty3k2c = _rtB -> i2uiramgaq ; UNUSED_PARAMETER ( tid ) ; }
static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 ,
510582773U ) ; ssSetChecksumVal ( S , 1 , 1541475379U ) ; ssSetChecksumVal (
S , 2 , 1993993197U ) ; ssSetChecksumVal ( S , 3 , 3701805791U ) ; { mxArray
* slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" )
; char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat ,
1 , & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat =
mxGetField ( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) {
status = 1 ; } else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; }
} mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "8.3" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( ew10rzwqr2 ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( n3qi1whofz ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } _ssSetConstBlockIO ( S , &
odcn43wyyk ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ; } static void
mdlInitializeSampleTimes ( SimStruct * S ) { { SimStruct * childS ;
SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S , 0 ) ; callSysFcns
= ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 1 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 2 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 3 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 4 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 5 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 6 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 7 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 8 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; } } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
