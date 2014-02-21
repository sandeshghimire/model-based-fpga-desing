#ifndef __c4_hdlcodercpu_eml_h__
#define __c4_hdlcodercpu_eml_h__

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
} c4_ResolvedFunctionInfo;

typedef struct {
  SimStruct *S;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  ChartInfoStruct chartInfo;
} SFc4_hdlcodercpu_emlInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c4_hdlcodercpu_eml_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c4_hdlcodercpu_eml_get_check_sum(mxArray *plhs[]);
extern void c4_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
