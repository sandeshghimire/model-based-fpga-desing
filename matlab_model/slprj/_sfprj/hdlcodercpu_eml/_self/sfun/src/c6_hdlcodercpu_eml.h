#ifndef __c6_hdlcodercpu_eml_h__
#define __c6_hdlcodercpu_eml_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc6_hdlcodercpu_emlInstanceStruct
#define typedef_SFc6_hdlcodercpu_emlInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c6_sfEvent;
  boolean_T c6_isStable;
  boolean_T c6_doneDoubleBufferReInit;
  uint8_T c6_is_active_c6_hdlcodercpu_eml;
  uint16_T c6_IR_value;
  boolean_T c6_IR_value_not_empty;
} SFc6_hdlcodercpu_emlInstanceStruct;

#endif                                 /*typedef_SFc6_hdlcodercpu_emlInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c6_hdlcodercpu_eml_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c6_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
extern void c6_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
