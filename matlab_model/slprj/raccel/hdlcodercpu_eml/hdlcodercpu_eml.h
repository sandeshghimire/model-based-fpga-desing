#ifndef RTW_HEADER_hdlcodercpu_eml_h_
#define RTW_HEADER_hdlcodercpu_eml_h_
#ifndef hdlcodercpu_eml_COMMON_INCLUDES_
# define hdlcodercpu_eml_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#include "rt_nonfinite.h"
#endif

#include "hdlcodercpu_eml_types.h"
#define MODEL_NAME                     hdlcodercpu_eml
#define NSAMPLE_TIMES                  (1)
#define NINPUTS                        (0)
#define NOUTPUTS                       (0)
#define NBLOCKIO                       (34)
#define NUM_ZC_EVENTS                  (0)
#ifndef NCSTATES
# define NCSTATES                      (0)
#elif NCSTATES != 0
# error Invalid specification of NCSTATES defined in compiler command
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        (NULL)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)
#endif

typedef struct {
  uint16_T UnitDelay1;
  uint16_T IR_out;
  uint16_T instr_out;
  int8_T UnitDelay6;
  int8_T feedbackforindirectaddressing;
  int8_T UnitDelay2;
  int8_T Switch1;
  int8_T select;
  int8_T switch_a[256];
  int8_T y;
  int8_T shift_out;
  int8_T AC_data;
  int8_T addr_inc;
  int8_T alu_out;
  int8_T AC_out;
  uint8_T UnitDelay4;
  uint8_T addr_out;
  uint8_T PC_next;
  uint8_T DM_addr;
  uint8_T hlt;
  boolean_T UnitDelay7;
  boolean_T DataTypeConversion;
  boolean_T print_data;
  uint8_T UnitDelay3;
  uint8_T out_flags;
  uint8_T out_flags_n;
  uint8_T out_flags_m;
  uint8_T ALU_func;
  uint8_T AC_func;
  uint8_T DM_r_w;
  uint8_T IM_read;
  uint8_T shifter_sel;
  uint8_T IR_func;
  uint8_T PC_func;
} BlockIO;

typedef struct {
  struct {
    void *LoggedData;
  } Scope_PWORK;

  struct {
    void *LoggedData;
  } Scope_PWORK_j;

  int32_T sfEvent;
  int32_T sfEvent_k;
  int32_T sfEvent_kd;
  int32_T sfEvent_e;
  int32_T sfEvent_c;
  int32_T sfEvent_p;
  int32_T sfEvent_g;
  int32_T sfEvent_n;
  int32_T sfEvent_j;
  uint16_T UnitDelay1_DSTATE;
  uint16_T IR_value;
  uint16_T data[256];
  int8_T UnitDelay6_DSTATE;
  int8_T UnitDelay5_DSTATE;
  int8_T UnitDelay2_DSTATE;
  int8_T din_d_DSTATE;
  int8_T ram_data_DSTATE;
  int8_T ram_DSTATE[256];
  uint8_T UnitDelay4_DSTATE;
  boolean_T UnitDelay7_DSTATE;
  boolean_T we_d_DSTATE;
  uint8_T UnitDelay3_DSTATE;
  int8_T AC_value;
  uint8_T is_active_c1_hdlcodercpu_eml;
  uint8_T is_active_c8_hdlcodercpu_eml;
  uint8_T is_active_c7_hdlcodercpu_eml;
  uint8_T PC_value;
  uint8_T is_active_c9_hdlcodercpu_eml;
  uint8_T is_active_c6_hdlcodercpu_eml;
  uint8_T is_active_c5_hdlcodercpu_eml;
  uint8_T is_active_c2_hdlcodercpu_eml;
  uint8_T CPU_state;
  uint8_T previous_CPU_state;
  uint8_T major_opcode;
  uint8_T minor_opcode;
  uint8_T address_data;
  uint8_T indirect_address;
  uint8_T is_active_c4_hdlcodercpu_eml;
  uint8_T is_active_c3_hdlcodercpu_eml;
  boolean_T isStable;
  boolean_T doneDoubleBufferReInit;
  boolean_T isStable_j;
  boolean_T doneDoubleBufferReInit_b;
  boolean_T isStable_jk;
  boolean_T doneDoubleBufferReInit_a;
  boolean_T PC_value_not_empty;
  boolean_T isStable_i;
  boolean_T doneDoubleBufferReInit_i;
  boolean_T isStable_i4;
  boolean_T doneDoubleBufferReInit_ad;
  boolean_T IR_value_not_empty;
  boolean_T isStable_f;
  boolean_T doneDoubleBufferReInit_e;
  boolean_T data_not_empty;
  boolean_T isStable_iq;
  boolean_T doneDoubleBufferReInit_g;
  boolean_T CPU_state_not_empty;
  boolean_T previous_CPU_state_not_empty;
  boolean_T major_opcode_not_empty;
  boolean_T minor_opcode_not_empty;
  boolean_T address_data_not_empty;
  boolean_T indirect_address_not_empty;
  boolean_T isStable_n;
  boolean_T doneDoubleBufferReInit_m;
  boolean_T isStable_o;
  boolean_T doneDoubleBufferReInit_n;
  boolean_T AC_value_not_empty;
} D_Work;

typedef struct {
  const boolean_T Compare;
} ConstBlockIO;

extern const ConstBlockIO rtrtC;
extern const char *RT_MEMORY_ALLOCATION_ERROR;
extern BlockIO rtB;
extern D_Work rtDWork;
extern SimStruct *const rtS;
extern const int_T gblNumToFiles;
extern const int_T gblNumFrFiles;
extern const int_T gblNumFrWksBlocks;
extern rtInportTUtable *gblInportTUtables;
extern const char *gblInportFileName;
extern const int_T gblNumRootInportBlks;
extern const int_T gblNumModelInputs;
extern const int_T gblInportDataTypeIdx[];
extern const int_T gblInportDims[];
extern const int_T gblInportComplex[];
extern const int_T gblInportInterpoFlag[];
extern const int_T gblInportContinuous[];

#endif
