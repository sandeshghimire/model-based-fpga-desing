/* Include files */

#include "blascompat32.h"
#include "hdlcodercpu_eml_sfun.h"
#include "c3_hdlcodercpu_eml.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "hdlcodercpu_eml_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const mxArray *c3_eml_mx;
static const char * c3_debug_family_names[8] = { "hdl_fm", "nargin", "nargout",
  "func", "AC_in1", "AC_in2", "AC_out", "AC_value" };

static const mxArray *c3_b_eml_mx;
static const mxArray *c3_c_eml_mx;

/* Function Declarations */
static void initialize_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initialize_params_c3_hdlcodercpu_eml
  (SFc3_hdlcodercpu_emlInstanceStruct *chartInstance);
static void enable_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void disable_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c3_update_debugger_state_c3_hdlcodercpu_eml
  (SFc3_hdlcodercpu_emlInstanceStruct *chartInstance);
static void ext_mode_exec_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static const mxArray *get_sim_state_c3_hdlcodercpu_eml
  (SFc3_hdlcodercpu_emlInstanceStruct *chartInstance);
static void set_sim_state_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c3_st);
static void finalize_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void sf_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c3_chartstep_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initSimStructsc3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static int8_T c3_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_AC_value, const char_T *c3_identifier);
static int8_T c3_b_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int8_T c3_c_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_AC_out, const char_T *c3_identifier);
static int8_T c3_d_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_e_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[13]);
static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_f_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static uint8_T c3_g_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_is_active_c3_hdlcodercpu_eml, const char_T
  *c3_identifier);
static uint8_T c3_h_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  int32_T *c3_sfEvent;
  boolean_T *c3_AC_value_not_empty;
  uint8_T *c3_is_active_c3_hdlcodercpu_eml;
  c3_AC_value_not_empty = (boolean_T *)ssGetDWork(chartInstance->S, 5);
  c3_is_active_c3_hdlcodercpu_eml = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c3_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  *c3_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  *c3_AC_value_not_empty = FALSE;
  *c3_is_active_c3_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c3_c_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 3.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c3_b_eml_mx, sf_mex_call_debug("numerictype", 1U, 10U, 15,
    "WordLength", 6, 8.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c3_eml_mx, sf_mex_call_debug("fimath", 1U, 38U, 15, "RoundMode",
    15, "floor", 15, "OverflowMode", 15, "wrap", 15, "ProductMode", 15,
    "FullPrecision", 15, "ProductWordLength", 6, 32.0, 15,
    "MaxProductWordLength", 6, 128.0, 15, "ProductFractionLength", 6, 30.0, 15,
    "ProductFixedExponent", 6, -30.0, 15, "ProductSlope", 6,
    9.3132257461547852E-10, 15, "ProductSlopeAdjustmentFactor", 6, 1.0, 15,
    "ProductBias", 6, 0.0, 15, "SumMode", 15, "FullPrecision", 15,
    "SumWordLength", 6, 32.0, 15, "MaxSumWordLength", 6, 128.0, 15,
    "SumFractionLength", 6, 30.0, 15, "SumFixedExponent", 6, -30.0, 15,
    "SumSlope", 6, 9.3132257461547852E-10, 15, "SumSlopeAdjustmentFactor", 6,
    1.0, 15, "SumBias", 6, 0.0, 15, "CastBeforeSum", 3, TRUE));
}

static void initialize_params_c3_hdlcodercpu_eml
  (SFc3_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void enable_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_hdlcodercpu_eml
  (SFc3_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void ext_mode_exec_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
  c3_update_debugger_state_c3_hdlcodercpu_eml(chartInstance);
}

static const mxArray *get_sim_state_c3_hdlcodercpu_eml
  (SFc3_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  int8_T c3_hoistedGlobal;
  int8_T c3_u;
  const mxArray *c3_b_y = NULL;
  int8_T c3_b_u;
  const mxArray *c3_c_y = NULL;
  int8_T c3_b_hoistedGlobal;
  int8_T c3_c_u;
  const mxArray *c3_d_y = NULL;
  int8_T c3_d_u;
  const mxArray *c3_e_y = NULL;
  uint8_T c3_c_hoistedGlobal;
  uint8_T c3_e_u;
  const mxArray *c3_f_y = NULL;
  int8_T *c3_AC_out;
  int8_T *c3_AC_value;
  boolean_T *c3_AC_value_not_empty;
  uint8_T *c3_is_active_c3_hdlcodercpu_eml;
  c3_AC_value_not_empty = (boolean_T *)ssGetDWork(chartInstance->S, 5);
  c3_AC_value = (int8_T *)ssGetDWork(chartInstance->S, 4);
  c3_AC_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_is_active_c3_hdlcodercpu_eml = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(3));
  c3_hoistedGlobal = *c3_AC_out;
  c3_u = c3_hoistedGlobal;
  c3_b_y = NULL;
  c3_b_u = c3_u;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_b_u, 2, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_b_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c3_eml_mx), 15, "numerictype", 14, sf_mex_dup(c3_b_eml_mx), 15,
    "simulinkarray", 14, c3_c_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_b_hoistedGlobal = *c3_AC_value;
  c3_c_u = c3_b_hoistedGlobal;
  c3_d_y = NULL;
  if (!*c3_AC_value_not_empty) {
    sf_mex_assign(&c3_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    c3_d_u = c3_c_u;
    c3_e_y = NULL;
    sf_mex_assign(&c3_e_y, sf_mex_create("y", &c3_d_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c3_d_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c3_eml_mx), 15, "numerictype", 14, sf_mex_dup(c3_b_eml_mx), 15,
      "simulinkarray", 14, c3_e_y, 15, "fimathislocal", 3, TRUE));
  }

  sf_mex_setcell(c3_y, 1, c3_d_y);
  c3_c_hoistedGlobal = *c3_is_active_c3_hdlcodercpu_eml;
  c3_e_u = c3_c_hoistedGlobal;
  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_e_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 2, c3_f_y);
  sf_mex_assign(&c3_st, c3_y);
  return c3_st;
}

static void set_sim_state_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  boolean_T *c3_doneDoubleBufferReInit;
  int8_T *c3_AC_out;
  int8_T *c3_AC_value;
  uint8_T *c3_is_active_c3_hdlcodercpu_eml;
  c3_AC_value = (int8_T *)ssGetDWork(chartInstance->S, 4);
  c3_AC_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_is_active_c3_hdlcodercpu_eml = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c3_doneDoubleBufferReInit = (boolean_T *)ssGetDWork(chartInstance->S, 2);
  *c3_doneDoubleBufferReInit = TRUE;
  c3_u = sf_mex_dup(c3_st);
  *c3_AC_out = c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c3_u, 0)), "AC_out");
  *c3_AC_value = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c3_u, 1)), "AC_value");
  *c3_is_active_c3_hdlcodercpu_eml = c3_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 2)), "is_active_c3_hdlcodercpu_eml");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_hdlcodercpu_eml(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&c3_eml_mx);
  sf_mex_destroy(&c3_b_eml_mx);
  sf_mex_destroy(&c3_c_eml_mx);
}

static void sf_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  int32_T *c3_sfEvent;
  uint8_T *c3_func;
  int8_T *c3_AC_out;
  int8_T *c3_AC_in1;
  int8_T *c3_AC_in2;
  c3_AC_in2 = (int8_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c3_AC_in1 = (int8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c3_AC_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_func = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c3_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, *c3_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c3_func, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c3_AC_out, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c3_AC_in1, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*c3_AC_in2, 3U);
  *c3_sfEvent = CALL_EVENT;
  c3_chartstep_c3_hdlcodercpu_eml(chartInstance);
  sf_debug_check_for_state_inconsistency(_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c3_chartstep_c3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  uint8_T c3_hoistedGlobal;
  int8_T c3_b_hoistedGlobal;
  int8_T c3_c_hoistedGlobal;
  uint8_T c3_func;
  int8_T c3_AC_in1;
  int8_T c3_AC_in2;
  uint32_T c3_debug_family_var_map[8];
  const mxArray *c3_hdl_fm = NULL;
  real_T c3_nargin = 3.0;
  real_T c3_nargout = 1.0;
  int8_T c3_AC_out;
  const mxArray *c3_m0 = NULL;
  const mxArray *c3_m1 = NULL;
  const mxArray *c3_m2 = NULL;
  const mxArray *c3_m3 = NULL;
  const mxArray *c3_m4 = NULL;
  const mxArray *c3_m5 = NULL;
  const mxArray *c3_m6 = NULL;
  int8_T c3_d_hoistedGlobal;
  int8_T c3_varargin_1;
  int8_T c3_b_varargin_1;
  const mxArray *c3_m7 = NULL;
  const mxArray *c3_m8 = NULL;
  const mxArray *c3_m9 = NULL;
  const mxArray *c3_m10 = NULL;
  int8_T c3_var1;
  const mxArray *c3_m11 = NULL;
  const mxArray *c3_m12 = NULL;
  const mxArray *c3_m13 = NULL;
  const mxArray *c3_m14 = NULL;
  const mxArray *c3_m15 = NULL;
  const mxArray *c3_m16 = NULL;
  const mxArray *c3_m17 = NULL;
  uint8_T c3_A;
  uint8_T c3_xfi;
  const mxArray *c3_m18 = NULL;
  const mxArray *c3_m19 = NULL;
  uint8_T c3_iA;
  const mxArray *c3_m20 = NULL;
  const mxArray *c3_m21 = NULL;
  const mxArray *c3_m22 = NULL;
  const mxArray *c3_m23 = NULL;
  const mxArray *c3_m24 = NULL;
  const mxArray *c3_m25 = NULL;
  const mxArray *c3_m26 = NULL;
  int8_T *c3_b_AC_out;
  uint8_T *c3_b_func;
  int8_T *c3_b_AC_in1;
  int8_T *c3_b_AC_in2;
  boolean_T *c3_AC_value_not_empty;
  int8_T *c3_AC_value;
  int32_T *c3_sfEvent;
  c3_AC_value_not_empty = (boolean_T *)ssGetDWork(chartInstance->S, 5);
  c3_AC_value = (int8_T *)ssGetDWork(chartInstance->S, 4);
  c3_b_AC_in2 = (int8_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c3_b_AC_in1 = (int8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c3_b_AC_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_func = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c3_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, *c3_sfEvent);
  c3_hoistedGlobal = *c3_b_func;
  c3_b_hoistedGlobal = *c3_b_AC_in1;
  c3_c_hoistedGlobal = *c3_b_AC_in2;
  c3_func = c3_hoistedGlobal;
  c3_AC_in1 = c3_b_hoistedGlobal;
  c3_AC_in2 = c3_c_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 8U, 8U, c3_debug_family_names,
    c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_hdl_fm, 0U, c3_f_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c3_nargin, 1U, c3_e_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c3_nargout, 2U, c3_e_sf_marshallOut,
    c3_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c3_func, 3U, c3_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c3_AC_in1, 4U, c3_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c3_AC_in2, 5U, c3_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c3_AC_out, 6U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c3_AC_value, 7U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, *c3_sfEvent, 11);
  c3_hdl_fm = c3_eml_mx;
  _SFD_EML_CALL(0U, *c3_sfEvent, 20);
  if (CV_EML_IF(0, 0, !*c3_AC_value_not_empty)) {
    _SFD_EML_CALL(0U, *c3_sfEvent, 21);
    sf_mex_destroy(&c3_m0);
    sf_mex_destroy(&c3_m1);
    sf_mex_destroy(&c3_m2);
    sf_mex_destroy(&c3_m3);
    sf_mex_destroy(&c3_m4);
    sf_mex_destroy(&c3_m5);
    sf_mex_destroy(&c3_m6);
    *c3_AC_value = 0;
    *c3_AC_value_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, *c3_sfEvent, 24);
  c3_d_hoistedGlobal = *c3_AC_value;
  c3_varargin_1 = c3_d_hoistedGlobal;
  c3_b_varargin_1 = c3_varargin_1;
  sf_mex_destroy(&c3_m7);
  sf_mex_destroy(&c3_m8);
  sf_mex_destroy(&c3_m9);
  sf_mex_destroy(&c3_m10);
  c3_var1 = c3_b_varargin_1;
  c3_AC_out = c3_var1;
  sf_mex_destroy(&c3_m11);
  sf_mex_destroy(&c3_m12);
  sf_mex_destroy(&c3_m13);
  sf_mex_destroy(&c3_m14);
  sf_mex_destroy(&c3_m15);
  sf_mex_destroy(&c3_m16);
  sf_mex_destroy(&c3_m17);
  _SFD_EML_CALL(0U, *c3_sfEvent, 26);
  c3_A = c3_func;
  c3_xfi = c3_A;
  sf_mex_destroy(&c3_m18);
  sf_mex_destroy(&c3_m19);
  c3_iA = c3_xfi;
  switch (c3_iA) {
   case 0U:
    CV_EML_SWITCH(0, 0, 1);
    _SFD_EML_CALL(0U, *c3_sfEvent, 29);
    sf_mex_destroy(&c3_m20);
    sf_mex_destroy(&c3_m21);
    sf_mex_destroy(&c3_m22);
    sf_mex_destroy(&c3_m23);
    sf_mex_destroy(&c3_m24);
    sf_mex_destroy(&c3_m25);
    sf_mex_destroy(&c3_m26);
    *c3_AC_value = 0;
    break;

   case 1U:
    CV_EML_SWITCH(0, 0, 2);
    _SFD_EML_CALL(0U, *c3_sfEvent, 32);
    *c3_AC_value = c3_AC_in1;
    break;

   case 2U:
    CV_EML_SWITCH(0, 0, 3);
    _SFD_EML_CALL(0U, *c3_sfEvent, 35);
    *c3_AC_value = c3_AC_in2;
    break;

   case 3U:
    CV_EML_SWITCH(0, 0, 4);
    _SFD_EML_CALL(0U, *c3_sfEvent, 38);
    c3_AC_out = *c3_AC_value;
    break;

   default:
    CV_EML_SWITCH(0, 0, 0);
    break;
  }

  _SFD_EML_CALL(0U, *c3_sfEvent, -38);
  sf_debug_symbol_scope_pop();
  *c3_b_AC_out = c3_AC_out;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, *c3_sfEvent);
}

static void initSimStructsc3_hdlcodercpu_eml(SFc3_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int8_T c3_u;
  const mxArray *c3_y = NULL;
  int8_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  boolean_T *c3_AC_value_not_empty;
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c3_AC_value_not_empty = (boolean_T *)ssGetDWork(chartInstance->S, 5);
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c3_u = *(int8_T *)c3_inData;
    c3_y = NULL;
    if (!*c3_AC_value_not_empty) {
      sf_mex_assign(&c3_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
    } else {
      c3_b_u = c3_u;
      c3_b_y = NULL;
      sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 2, 0U, 0U, 0U, 0));
      sf_mex_assign(&c3_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
        sf_mex_dup(c3_eml_mx), 15, "numerictype", 14, sf_mex_dup(c3_b_eml_mx),
        15, "simulinkarray", 14, c3_b_y, 15, "fimathislocal", 3, TRUE));
    }

    sf_mex_assign(&c3_mxArrayOutData, c3_y);
  } else {
    sf_mex_assign(&c3_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c3_mxArrayOutData;
}

static int8_T c3_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_AC_value, const char_T *c3_identifier)
{
  int8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_AC_value),
    &c3_thisId);
  sf_mex_destroy(&c3_AC_value);
  return c3_y;
}

static int8_T c3_b_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int8_T c3_y;
  const mxArray *c3_mxFi = NULL;
  const mxArray *c3_mxInt = NULL;
  int8_T c3_i0;
  boolean_T *c3_AC_value_not_empty;
  c3_AC_value_not_empty = (boolean_T *)ssGetDWork(chartInstance->S, 5);
  if (mxIsEmpty(c3_u)) {
    *c3_AC_value_not_empty = FALSE;
  } else {
    *c3_AC_value_not_empty = TRUE;
    sf_mex_check_fi(c3_parentId, c3_u, 0, 0U, 0, c3_eml_mx, c3_b_eml_mx);
    sf_mex_assign(&c3_mxFi, sf_mex_dup(c3_u));
    sf_mex_assign(&c3_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
                   (c3_mxFi)));
    sf_mex_import(c3_parentId, sf_mex_dup(c3_mxInt), &c3_i0, 1, 2, 0U, 0, 0U, 0);
    sf_mex_destroy(&c3_mxFi);
    sf_mex_destroy(&c3_mxInt);
    c3_y = c3_i0;
  }

  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_AC_value;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int8_T c3_y;
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c3_AC_value = sf_mex_dup(c3_mxArrayInData);
    c3_identifier = c3_varName;
    c3_thisId.fIdentifier = c3_identifier;
    c3_thisId.fParent = NULL;
    c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_AC_value),
      &c3_thisId);
    sf_mex_destroy(&c3_AC_value);
    *(int8_T *)c3_outData = c3_y;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int8_T c3_u;
  const mxArray *c3_y = NULL;
  int8_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c3_u = *(int8_T *)c3_inData;
    c3_y = NULL;
    c3_b_u = c3_u;
    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c3_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c3_eml_mx), 15, "numerictype", 14, sf_mex_dup(c3_b_eml_mx), 15,
      "simulinkarray", 14, c3_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c3_mxArrayOutData, c3_y);
  } else {
    sf_mex_assign(&c3_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c3_mxArrayOutData;
}

static int8_T c3_c_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_AC_out, const char_T *c3_identifier)
{
  int8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_AC_out), &c3_thisId);
  sf_mex_destroy(&c3_AC_out);
  return c3_y;
}

static int8_T c3_d_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int8_T c3_y;
  const mxArray *c3_mxFi = NULL;
  const mxArray *c3_mxInt = NULL;
  int8_T c3_i1;
  sf_mex_check_fi(c3_parentId, c3_u, 0, 0U, 0, c3_eml_mx, c3_b_eml_mx);
  sf_mex_assign(&c3_mxFi, sf_mex_dup(c3_u));
  sf_mex_assign(&c3_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c3_mxFi)));
  sf_mex_import(c3_parentId, sf_mex_dup(c3_mxInt), &c3_i1, 1, 2, 0U, 0, 0U, 0);
  sf_mex_destroy(&c3_mxFi);
  sf_mex_destroy(&c3_mxInt);
  c3_y = c3_i1;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_AC_out;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int8_T c3_y;
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c3_AC_out = sf_mex_dup(c3_mxArrayInData);
    c3_identifier = c3_varName;
    c3_thisId.fIdentifier = c3_identifier;
    c3_thisId.fParent = NULL;
    c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_AC_out),
      &c3_thisId);
    sf_mex_destroy(&c3_AC_out);
    *(int8_T *)c3_outData = c3_y;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int8_T c3_u;
  const mxArray *c3_y = NULL;
  int8_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c3_u = *(int8_T *)c3_inData;
    c3_y = NULL;
    c3_b_u = c3_u;
    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c3_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c3_eml_mx), 15, "numerictype", 14, sf_mex_dup(c3_b_eml_mx), 15,
      "simulinkarray", 14, c3_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c3_mxArrayOutData, c3_y);
  } else {
    sf_mex_assign(&c3_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c3_mxArrayOutData;
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  uint8_T c3_u;
  const mxArray *c3_y = NULL;
  uint8_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c3_u = *(uint8_T *)c3_inData;
    c3_y = NULL;
    c3_b_u = c3_u;
    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c3_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c3_eml_mx), 15, "numerictype", 14, sf_mex_dup(c3_c_eml_mx), 15,
      "simulinkarray", 14, c3_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c3_mxArrayOutData, c3_y);
  } else {
    sf_mex_assign(&c3_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c3_mxArrayOutData;
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

static real_T c3_e_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d0, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_nargout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c3_nargout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_nargout), &c3_thisId);
  sf_mex_destroy(&c3_nargout);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  const mxArray *c3_u;
  const mxArray *c3_y = NULL;
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = sf_mex_dup(*(const mxArray **)c3_inData);
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_duplicatearraysafe(&c3_u));
  sf_mex_destroy(&c3_u);
  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

const mxArray *sf_c3_hdlcodercpu_eml_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo;
  c3_ResolvedFunctionInfo c3_info[13];
  const mxArray *c3_m27 = NULL;
  int32_T c3_i2;
  c3_ResolvedFunctionInfo *c3_r0;
  c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  c3_info_helper(c3_info);
  sf_mex_assign(&c3_m27, sf_mex_createstruct("nameCaptureInfo", 1, 13));
  for (c3_i2 = 0; c3_i2 < 13; c3_i2++) {
    c3_r0 = &c3_info[c3_i2];
    sf_mex_addfield(c3_m27, sf_mex_create("nameCaptureInfo", c3_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->context)), "context", "nameCaptureInfo",
                    c3_i2);
    sf_mex_addfield(c3_m27, sf_mex_create("nameCaptureInfo", c3_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c3_r0->name)), "name", "nameCaptureInfo", c3_i2);
    sf_mex_addfield(c3_m27, sf_mex_create("nameCaptureInfo", c3_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c3_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c3_i2);
    sf_mex_addfield(c3_m27, sf_mex_create("nameCaptureInfo", c3_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->resolved)), "resolved", "nameCaptureInfo",
                    c3_i2);
    sf_mex_addfield(c3_m27, sf_mex_create("nameCaptureInfo", &c3_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c3_i2);
    sf_mex_addfield(c3_m27, sf_mex_create("nameCaptureInfo", &c3_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c3_i2);
    sf_mex_addfield(c3_m27, sf_mex_create("nameCaptureInfo", &c3_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c3_i2);
    sf_mex_addfield(c3_m27, sf_mex_create("nameCaptureInfo", &c3_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c3_i2);
  }

  sf_mex_assign(&c3_nameCaptureInfo, c3_m27);
  return c3_nameCaptureInfo;
}

static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[13])
{
  c3_info[0].context = "";
  c3_info[0].name = "fimath";
  c3_info[0].dominantType = "char";
  c3_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m";
  c3_info[0].fileTimeLo = 275520000U;
  c3_info[0].fileTimeHi = 30114375U;
  c3_info[0].mFileTimeLo = 0U;
  c3_info[0].mFileTimeHi = 0U;
  c3_info[1].context = "";
  c3_info[1].name = "fi_impl";
  c3_info[1].dominantType = "";
  c3_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m";
  c3_info[1].fileTimeLo = 275520000U;
  c3_info[1].fileTimeHi = 30114375U;
  c3_info[1].mFileTimeLo = 0U;
  c3_info[1].mFileTimeHi = 0U;
  c3_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c3_info[2].name = "isfi";
  c3_info[2].dominantType = "double";
  c3_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c3_info[2].fileTimeLo = 335520000U;
  c3_info[2].fileTimeHi = 30114375U;
  c3_info[2].mFileTimeLo = 0U;
  c3_info[2].mFileTimeHi = 0U;
  c3_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c3_info[3].name = "isnumerictype";
  c3_info[3].dominantType = "char";
  c3_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m";
  c3_info[3].fileTimeLo = 355520000U;
  c3_info[3].fileTimeHi = 30114375U;
  c3_info[3].mFileTimeLo = 0U;
  c3_info[3].mFileTimeHi = 0U;
  c3_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c3_info[4].name = "eml_fi_checkforerror";
  c3_info[4].dominantType = "embedded.numerictype";
  c3_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m";
  c3_info[4].fileTimeLo = 255520000U;
  c3_info[4].fileTimeHi = 30114375U;
  c3_info[4].mFileTimeLo = 0U;
  c3_info[4].mFileTimeHi = 0U;
  c3_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c3_info[5].name = "isfloat";
  c3_info[5].dominantType = "embedded.fi";
  c3_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m";
  c3_info[5].fileTimeLo = 875520000U;
  c3_info[5].fileTimeHi = 30114375U;
  c3_info[5].mFileTimeLo = 0U;
  c3_info[5].mFileTimeHi = 0U;
  c3_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m";
  c3_info[6].name = "get";
  c3_info[6].dominantType = "embedded.numerictype";
  c3_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m";
  c3_info[6].fileTimeLo = 4170487296U;
  c3_info[6].fileTimeHi = 30114374U;
  c3_info[6].mFileTimeLo = 0U;
  c3_info[6].mFileTimeHi = 0U;
  c3_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput";
  c3_info[7].name = "numerictype";
  c3_info[7].dominantType = "embedded.fi";
  c3_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m";
  c3_info[7].fileTimeLo = 995520000U;
  c3_info[7].fileTimeHi = 30114375U;
  c3_info[7].mFileTimeLo = 0U;
  c3_info[7].mFileTimeHi = 0U;
  c3_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput";
  c3_info[8].name = "fimath";
  c3_info[8].dominantType = "embedded.fi";
  c3_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m";
  c3_info[8].fileTimeLo = 775520000U;
  c3_info[8].fileTimeHi = 30114375U;
  c3_info[8].mFileTimeLo = 0U;
  c3_info[8].mFileTimeHi = 0U;
  c3_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c3_info[9].name = "eml_fi_checkforntype";
  c3_info[9].dominantType = "embedded.fi";
  c3_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m";
  c3_info[9].fileTimeLo = 255520000U;
  c3_info[9].fileTimeHi = 30114375U;
  c3_info[9].mFileTimeLo = 0U;
  c3_info[9].mFileTimeHi = 0U;
  c3_info[10].context = "";
  c3_info[10].name = "uint8";
  c3_info[10].dominantType = "embedded.fi";
  c3_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m";
  c3_info[10].fileTimeLo = 1115520000U;
  c3_info[10].fileTimeHi = 30114375U;
  c3_info[10].mFileTimeLo = 0U;
  c3_info[10].mFileTimeHi = 0U;
  c3_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m";
  c3_info[11].name = "eml_fi_getStoredIntValAsDType";
  c3_info[11].dominantType = "embedded.fi";
  c3_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getStoredIntValAsDType.m";
  c3_info[11].fileTimeLo = 655520000U;
  c3_info[11].fileTimeHi = 30114375U;
  c3_info[11].mFileTimeLo = 0U;
  c3_info[11].mFileTimeHi = 0U;
  c3_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getStoredIntValAsDType.m";
  c3_info[12].name = "isfixed";
  c3_info[12].dominantType = "embedded.fi";
  c3_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  c3_info[12].fileTimeLo = 875520000U;
  c3_info[12].fileTimeHi = 30114375U;
  c3_info[12].mFileTimeLo = 0U;
  c3_info[12].mFileTimeHi = 0U;
}

static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_mxArrayOutData, c3_y);
  return c3_mxArrayOutData;
}

static int32_T c3_f_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i3;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i3, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i3;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c3_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_sfEvent), &c3_thisId);
  sf_mex_destroy(&c3_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  uint8_T c3_u;
  const mxArray *c3_y = NULL;
  uint8_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c3_u = *(uint8_T *)c3_inData;
    c3_y = NULL;
    c3_b_u = c3_u;
    c3_b_y = NULL;
    sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c3_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c3_eml_mx), 15, "numerictype", 14, sf_mex_dup(c3_c_eml_mx), 15,
      "simulinkarray", 14, c3_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c3_mxArrayOutData, c3_y);
  } else {
    sf_mex_assign(&c3_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c3_mxArrayOutData;
}

static uint8_T c3_g_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_is_active_c3_hdlcodercpu_eml, const char_T
  *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_is_active_c3_hdlcodercpu_eml), &c3_thisId);
  sf_mex_destroy(&c3_is_active_c3_hdlcodercpu_eml);
  return c3_y;
}

static uint8_T c3_h_emlrt_marshallIn(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
static uint32_T* sf_get_sfun_dwork_checksum();
void sf_c3_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(763891459U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1545734528U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(894326394U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(730855503U);
}

mxArray *sf_c3_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(1471874133U);
    pr[1] = (double)(436519218U);
    pr[2] = (double)(4149100484U);
    pr[3] = (double)(1838143824U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(11));

      {
        const char *fixptFields[] = { "isSigned", "wordLength", "bias", "slope",
          "exponent", "isScaledDouble" };

        mxArray *mxFixpt = mxCreateStructMatrix(1,1,6,fixptFields);
        mxSetField(mxFixpt,0,"isSigned",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(3));
        mxSetField(mxFixpt,0,"bias",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"slope",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"exponent",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"isScaledDouble",mxCreateDoubleScalar(0));
        mxSetField(mxType,0,"fixpt",mxFixpt);
      }

      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(11));

      {
        const char *fixptFields[] = { "isSigned", "wordLength", "bias", "slope",
          "exponent", "isScaledDouble" };

        mxArray *mxFixpt = mxCreateStructMatrix(1,1,6,fixptFields);
        mxSetField(mxFixpt,0,"isSigned",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(8));
        mxSetField(mxFixpt,0,"bias",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"slope",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"exponent",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"isScaledDouble",mxCreateDoubleScalar(0));
        mxSetField(mxType,0,"fixpt",mxFixpt);
      }

      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(11));

      {
        const char *fixptFields[] = { "isSigned", "wordLength", "bias", "slope",
          "exponent", "isScaledDouble" };

        mxArray *mxFixpt = mxCreateStructMatrix(1,1,6,fixptFields);
        mxSetField(mxFixpt,0,"isSigned",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(8));
        mxSetField(mxFixpt,0,"bias",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"slope",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"exponent",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"isScaledDouble",mxCreateDoubleScalar(0));
        mxSetField(mxType,0,"fixpt",mxFixpt);
      }

      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(11));

      {
        const char *fixptFields[] = { "isSigned", "wordLength", "bias", "slope",
          "exponent", "isScaledDouble" };

        mxArray *mxFixpt = mxCreateStructMatrix(1,1,6,fixptFields);
        mxSetField(mxFixpt,0,"isSigned",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(8));
        mxSetField(mxFixpt,0,"bias",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"slope",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"exponent",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"isScaledDouble",mxCreateDoubleScalar(0));
        mxSetField(mxType,0,"fixpt",mxFixpt);
      }

      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c3_hdlcodercpu_eml(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"AC_out\",},{M[4],M[0],T\"AC_value\",S'l','i','p'{{M1x2[514 522],M[0],}}},{M[8],M[0],T\"is_active_c3_hdlcodercpu_eml\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_hdlcodercpu_eml_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
    chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_hdlcodercpu_emlMachineNumber_,
           3,
           1,
           1,
           4,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_hdlcodercpu_emlMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (_hdlcodercpu_emlMachineNumber_,chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_hdlcodercpu_emlMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"func");
          _SFD_SET_DATA_PROPS(1,2,0,1,"AC_out");
          _SFD_SET_DATA_PROPS(2,1,1,0,"AC_in1");
          _SFD_SET_DATA_PROPS(3,1,1,0,"AC_in2");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,1,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",218,-1,935);
        _SFD_CV_INIT_EML_IF(0,0,524,545,-1,588);

        {
          static int caseStart[] = { -1, 664, 736, 800, 867 };

          static int caseExprEnd[] = { 8, 670, 742, 806, 873 };

          _SFD_CV_INIT_EML_SWITCH(0,0,639,658,933,5,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,1,0,3,0,1,0,0,
          (MexFcnForType)c3_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          uint8_T *c3_func;
          int8_T *c3_AC_out;
          int8_T *c3_AC_in1;
          int8_T *c3_AC_in2;
          c3_AC_in2 = (int8_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c3_AC_in1 = (int8_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c3_AC_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c3_func = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c3_func);
          _SFD_SET_DATA_VALUE_PTR(1U, c3_AC_out);
          _SFD_SET_DATA_VALUE_PTR(2U, c3_AC_in1);
          _SFD_SET_DATA_VALUE_PTR(3U, c3_AC_in2);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_hdlcodercpu_emlMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_check_dwork_consistency(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    const uint32_T *sfunDWorkChecksum = sf_get_sfun_dwork_checksum();
    mxArray* mxRTWDWorkChecksum = sf_get_dwork_info_from_mat_file(S,
      "hdlcodercpu_eml", "hdlcodercpu_eml", 3, "dworkChecksum");
    if (mxRTWDWorkChecksum != NULL) {
      double *pr = mxGetPr(mxRTWDWorkChecksum);
      if ((uint32_T)pr[0] != sfunDWorkChecksum[0] ||
          (uint32_T)pr[1] != sfunDWorkChecksum[1] ||
          (uint32_T)pr[2] != sfunDWorkChecksum[2] ||
          (uint32_T)pr[3] != sfunDWorkChecksum[3]) {
        sf_mex_error_message("Code generation and simulation targets registered different sets of persistent variables for the block. "
                             "External or Rapid Accelerator mode simulation requires code generation and simulation targets to "
                             "register the same set of persistent variables for this block. "
                             "This discrepancy is typically caused by MATLAB functions that have different code paths for "
                             "simulation and code generation targets where these code paths define different sets of persistent variables. "
                             "Please identify these code paths in the offending block and rewrite the MATLAB code so that "
                             "the set of persistent variables is the same between simulation and code generation.");
      }
    }
  }
}

static void sf_opaque_initialize_c3_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc3_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S);
  chart_debug_initialization(((SFc3_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c3_hdlcodercpu_eml((SFc3_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
  initialize_c3_hdlcodercpu_eml((SFc3_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c3_hdlcodercpu_eml(void *chartInstanceVar)
{
  enable_c3_hdlcodercpu_eml((SFc3_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c3_hdlcodercpu_eml(void *chartInstanceVar)
{
  disable_c3_hdlcodercpu_eml((SFc3_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c3_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_c3_hdlcodercpu_eml((SFc3_hdlcodercpu_emlInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c3_hdlcodercpu_eml(void *chartInstanceVar)
{
  ext_mode_exec_c3_hdlcodercpu_eml((SFc3_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_hdlcodercpu_eml(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_hdlcodercpu_eml
    ((SFc3_hdlcodercpu_emlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c3_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_hdlcodercpu_eml((SFc3_hdlcodercpu_emlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_hdlcodercpu_eml(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_hdlcodercpu_eml(S);
}

static void sf_opaque_set_sim_state_c3_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c3_hdlcodercpu_eml(S, st);
}

static void sf_opaque_terminate_c3_hdlcodercpu_eml(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_hdlcodercpu_emlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c3_hdlcodercpu_eml((SFc3_hdlcodercpu_emlInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_hdlcodercpu_eml((SFc3_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_hdlcodercpu_eml(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_hdlcodercpu_eml((SFc3_hdlcodercpu_emlInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

mxArray *sf_c3_hdlcodercpu_eml_get_testpoint_info(void)
{
  const char *infoEncStr[] = {
    "100 S'varName','path'{{T\"is_active_c3_hdlcodercpu_eml\",T\"is_active_c3_hdlcodercpu_eml\"}}"
  };

  mxArray *mxTpInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 1, 10);
  return mxTpInfo;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x6'type','isSigned','wordLength','bias','slope','exponent','isComplex','size'{{T\"int32\",,,,,,M[0],M[]},{T\"boolean\",,,,,,M[0],M[]},{T\"boolean\",,,,,,M[0],M[]},{T\"uint8\",,,,,,M[0],M[]},{T\"fixpt\",M[1],M[8],M[0],M[1],M[0],M[0],M[]},{T\"boolean\",,,,,,M[0],M[]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 6, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 2729337739U, 2945853807U, 2553650998U,
    1354020709U };

  return checksum;
}

static void mdlSetWorkWidths_c3_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"hdlcodercpu_eml","hdlcodercpu_eml",3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml","hdlcodercpu_eml",3,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml",
      "hdlcodercpu_eml",3,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",
        3,3);
      sf_mark_chart_reusable_outputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",3,1);
    }

    sf_set_rtw_dwork_info(S,"hdlcodercpu_eml","hdlcodercpu_eml",3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2467238167U));
  ssSetChecksum1(S,(3275562233U));
  ssSetChecksum2(S,(2806450950U));
  ssSetChecksum3(S,(3766097500U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c3_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "hdlcodercpu_eml", "hdlcodercpu_eml",3);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_hdlcodercpu_eml(SimStruct *S)
{
  SFc3_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc3_hdlcodercpu_emlInstanceStruct *)malloc(sizeof
    (SFc3_hdlcodercpu_emlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_hdlcodercpu_emlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c3_hdlcodercpu_eml;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c3_hdlcodercpu_eml;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c3_hdlcodercpu_eml;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_hdlcodercpu_eml;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c3_hdlcodercpu_eml;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c3_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_hdlcodercpu_eml;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c3_hdlcodercpu_eml;
  chartInstance->chartInfo.extModeExec =
    sf_opaque_ext_mode_exec_c3_hdlcodercpu_eml;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c3_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_hdlcodercpu_eml(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_hdlcodercpu_eml_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
