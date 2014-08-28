#ifndef __c2_gm_hdlcodercpu_eml_h__
#define __c2_gm_hdlcodercpu_eml_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_gm_hdlcodercpu_emlInstanceStruct
#define typedef_SFc2_gm_hdlcodercpu_emlInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_gm_hdlcodercpu_eml;
  uint8_T c2_CPU_state;
  boolean_T c2_CPU_state_not_empty;
  uint8_T c2_previous_CPU_state;
  boolean_T c2_previous_CPU_state_not_empty;
  uint8_T c2_major_opcode;
  boolean_T c2_major_opcode_not_empty;
  uint8_T c2_minor_opcode;
  boolean_T c2_minor_opcode_not_empty;
  uint8_T c2_address_data;
  boolean_T c2_address_data_not_empty;
  uint8_T c2_indirect_address;
  boolean_T c2_indirect_address_not_empty;
} SFc2_gm_hdlcodercpu_emlInstanceStruct;

#endif                                 /*typedef_SFc2_gm_hdlcodercpu_emlInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_gm_hdlcodercpu_eml_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c2_gm_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
extern void c2_gm_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
