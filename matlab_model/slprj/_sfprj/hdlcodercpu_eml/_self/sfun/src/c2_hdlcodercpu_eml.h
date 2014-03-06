#ifndef __c2_hdlcodercpu_eml_h__
#define __c2_hdlcodercpu_eml_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c2_ResolvedFunctionInfo;

typedef struct {
  SimStruct *S;
  int32_T c2_sfEvent;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c2_CPU_state_not_empty;
  boolean_T c2_address_data_not_empty;
  boolean_T c2_doneDoubleBufferReInit;
  boolean_T c2_indirect_address_not_empty;
  boolean_T c2_isStable;
  boolean_T c2_major_opcode_not_empty;
  boolean_T c2_minor_opcode_not_empty;
  boolean_T c2_previous_CPU_state_not_empty;
  uint8_T c2_CPU_state;
  uint8_T c2_address_data;
  uint8_T c2_indirect_address;
  uint8_T c2_is_active_c2_hdlcodercpu_eml;
  uint8_T c2_major_opcode;
  uint8_T c2_minor_opcode;
  uint8_T c2_previous_CPU_state;
  ChartInfoStruct chartInfo;
} SFc2_hdlcodercpu_emlInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_hdlcodercpu_eml_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
extern void c2_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
