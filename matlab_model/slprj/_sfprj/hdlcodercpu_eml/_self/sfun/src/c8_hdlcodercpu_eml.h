#ifndef __c8_hdlcodercpu_eml_h__
#define __c8_hdlcodercpu_eml_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc8_hdlcodercpu_emlInstanceStruct
#define typedef_SFc8_hdlcodercpu_emlInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c8_sfEvent;
  boolean_T c8_isStable;
  boolean_T c8_doneDoubleBufferReInit;
  uint8_T c8_is_active_c8_hdlcodercpu_eml;
} SFc8_hdlcodercpu_emlInstanceStruct;

#endif                                 /*typedef_SFc8_hdlcodercpu_emlInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c8_hdlcodercpu_eml_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c8_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
extern void c8_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
