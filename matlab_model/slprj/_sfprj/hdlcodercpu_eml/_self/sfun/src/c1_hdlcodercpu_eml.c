/* Include files */

#include "blascompat32.h"
#include "hdlcodercpu_eml_sfun.h"
#include "c1_hdlcodercpu_eml.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "hdlcodercpu_eml_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const mxArray *c1_eml_mx;
static const char * c1_debug_family_names[6] = { "hdl_fm", "nargin", "nargout",
  "u", "enable", "y" };

static const mxArray *c1_b_eml_mx;
static const mxArray *c1_c_eml_mx;

/* Function Declarations */
static void initialize_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initialize_params_c1_hdlcodercpu_eml
  (SFc1_hdlcodercpu_emlInstanceStruct *chartInstance);
static void enable_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void disable_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c1_update_debugger_state_c1_hdlcodercpu_eml
  (SFc1_hdlcodercpu_emlInstanceStruct *chartInstance);
static void ext_mode_exec_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static const mxArray *get_sim_state_c1_hdlcodercpu_eml
  (SFc1_hdlcodercpu_emlInstanceStruct *chartInstance);
static void set_sim_state_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c1_st);
static void finalize_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void sf_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c1_chartstep_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initSimStructsc1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static int8_T c1_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_b_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_c_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int8_T c1_d_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_y, const char_T *c1_identifier);
static int8_T c1_e_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_f_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_is_active_c1_hdlcodercpu_eml, const char_T
  *c1_identifier);
static uint8_T c1_g_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  int32_T *c1_sfEvent;
  uint8_T *c1_is_active_c1_hdlcodercpu_eml;
  c1_is_active_c1_hdlcodercpu_eml = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c1_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  *c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  *c1_is_active_c1_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c1_c_eml_mx, sf_mex_call_debug("fimath", 1U, 38U, 15,
    "RoundMode", 15, "floor", 15, "OverflowMode", 15, "wrap", 15, "ProductMode",
    15, "KeepLSB", 15, "ProductWordLength", 6, 32.0, 15, "MaxProductWordLength",
    6, 128.0, 15, "ProductFractionLength", 6, 30.0, 15, "ProductFixedExponent",
    6, -30.0, 15, "ProductSlope", 6, 9.3132257461547852E-10, 15,
    "ProductSlopeAdjustmentFactor", 6, 1.0, 15, "ProductBias", 6, 0.0, 15,
    "SumMode", 15, "KeepLSB", 15, "SumWordLength", 6, 32.0, 15,
    "MaxSumWordLength", 6, 128.0, 15, "SumFractionLength", 6, 30.0, 15,
    "SumFixedExponent", 6, -30.0, 15, "SumSlope", 6, 9.3132257461547852E-10, 15,
    "SumSlopeAdjustmentFactor", 6, 1.0, 15, "SumBias", 6, 0.0, 15,
    "CastBeforeSum", 3, TRUE));
  sf_mex_assign(&c1_b_eml_mx, sf_mex_call_debug("numerictype", 1U, 10U, 15,
    "WordLength", 6, 8.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c1_eml_mx, sf_mex_call_debug("fimath", 1U, 38U, 15, "RoundMode",
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

static void initialize_params_c1_hdlcodercpu_eml
  (SFc1_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void enable_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_hdlcodercpu_eml
  (SFc1_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void ext_mode_exec_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
  c1_update_debugger_state_c1_hdlcodercpu_eml(chartInstance);
}

static const mxArray *get_sim_state_c1_hdlcodercpu_eml
  (SFc1_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int8_T c1_hoistedGlobal;
  int8_T c1_u;
  const mxArray *c1_b_y = NULL;
  int8_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  uint8_T c1_b_hoistedGlobal;
  uint8_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  int8_T *c1_e_y;
  uint8_T *c1_is_active_c1_hdlcodercpu_eml;
  c1_e_y = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_is_active_c1_hdlcodercpu_eml = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(2));
  c1_hoistedGlobal = *c1_e_y;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  c1_b_u = c1_u;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 2, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_b_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c1_c_eml_mx), 15, "numerictype", 14, sf_mex_dup(c1_b_eml_mx), 15,
    "simulinkarray", 14, c1_c_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *c1_is_active_c1_hdlcodercpu_eml;
  c1_c_u = c1_b_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c1_y, 1, c1_d_y);
  sf_mex_assign(&c1_st, c1_y);
  return c1_st;
}

static void set_sim_state_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  boolean_T *c1_doneDoubleBufferReInit;
  int8_T *c1_y;
  uint8_T *c1_is_active_c1_hdlcodercpu_eml;
  c1_y = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_is_active_c1_hdlcodercpu_eml = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c1_doneDoubleBufferReInit = (boolean_T *)ssGetDWork(chartInstance->S, 2);
  *c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  *c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
    "y");
  *c1_is_active_c1_hdlcodercpu_eml = c1_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 1)), "is_active_c1_hdlcodercpu_eml");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_hdlcodercpu_eml(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&c1_eml_mx);
  sf_mex_destroy(&c1_b_eml_mx);
  sf_mex_destroy(&c1_c_eml_mx);
}

static void sf_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  int32_T *c1_sfEvent;
  int8_T *c1_u;
  int8_T *c1_y;
  boolean_T *c1_enable;
  c1_enable = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_y = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_u = (int8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c1_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, *c1_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c1_u, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c1_y, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c1_enable, 2U);
  *c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_hdlcodercpu_eml(chartInstance);
  sf_debug_check_for_state_inconsistency(_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  int8_T c1_hoistedGlobal;
  boolean_T c1_b_hoistedGlobal;
  int8_T c1_u;
  boolean_T c1_enable;
  uint32_T c1_debug_family_var_map[6];
  const mxArray *c1_hdl_fm = NULL;
  real_T c1_nargin = 2.0;
  real_T c1_nargout = 1.0;
  int8_T c1_y;
  const mxArray *c1_m0 = NULL;
  const mxArray *c1_m1 = NULL;
  const mxArray *c1_m2 = NULL;
  const mxArray *c1_m3 = NULL;
  const mxArray *c1_m4 = NULL;
  const mxArray *c1_m5 = NULL;
  const mxArray *c1_m6 = NULL;
  int8_T c1_varargin_1;
  int8_T c1_b_varargin_1;
  const mxArray *c1_m7 = NULL;
  const mxArray *c1_m8 = NULL;
  const mxArray *c1_m9 = NULL;
  const mxArray *c1_m10 = NULL;
  int8_T c1_var1;
  const mxArray *c1_m11 = NULL;
  const mxArray *c1_m12 = NULL;
  const mxArray *c1_m13 = NULL;
  const mxArray *c1_m14 = NULL;
  const mxArray *c1_m15 = NULL;
  const mxArray *c1_m16 = NULL;
  const mxArray *c1_m17 = NULL;
  int8_T *c1_b_y;
  int8_T *c1_b_u;
  boolean_T *c1_b_enable;
  int32_T *c1_sfEvent;
  c1_b_enable = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_b_y = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_u = (int8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c1_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, *c1_sfEvent);
  c1_hoistedGlobal = *c1_b_u;
  c1_b_hoistedGlobal = *c1_b_enable;
  c1_u = c1_hoistedGlobal;
  c1_enable = c1_b_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c1_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c1_hdl_fm, 0U, c1_e_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 1U, c1_d_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 2U, c1_d_sf_marshallOut,
    c1_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c1_u, 3U, c1_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c1_enable, 4U, c1_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_y, 5U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, *c1_sfEvent, 5);
  c1_hdl_fm = c1_eml_mx;
  _SFD_EML_CALL(0U, *c1_sfEvent, 12);
  sf_mex_destroy(&c1_m0);
  sf_mex_destroy(&c1_m1);
  sf_mex_destroy(&c1_m2);
  sf_mex_destroy(&c1_m3);
  sf_mex_destroy(&c1_m4);
  sf_mex_destroy(&c1_m5);
  sf_mex_destroy(&c1_m6);
  c1_y = 0;
  _SFD_EML_CALL(0U, *c1_sfEvent, 14);
  if (CV_EML_IF(0, 0, c1_enable)) {
    _SFD_EML_CALL(0U, *c1_sfEvent, 15);
    c1_varargin_1 = c1_u;
    c1_b_varargin_1 = c1_varargin_1;
    sf_mex_destroy(&c1_m7);
    sf_mex_destroy(&c1_m8);
    sf_mex_destroy(&c1_m9);
    sf_mex_destroy(&c1_m10);
    c1_var1 = c1_b_varargin_1;
    c1_y = c1_var1;
    sf_mex_destroy(&c1_m11);
    sf_mex_destroy(&c1_m12);
    sf_mex_destroy(&c1_m13);
    sf_mex_destroy(&c1_m14);
    sf_mex_destroy(&c1_m15);
    sf_mex_destroy(&c1_m16);
    sf_mex_destroy(&c1_m17);
  }

  _SFD_EML_CALL(0U, *c1_sfEvent, -15);
  sf_debug_symbol_scope_pop();
  *c1_b_y = c1_y;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *c1_sfEvent);
}

static void initSimStructsc1_hdlcodercpu_eml(SFc1_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int8_T c1_u;
  const mxArray *c1_y = NULL;
  int8_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c1_u = *(int8_T *)c1_inData;
    c1_y = NULL;
    c1_b_u = c1_u;
    c1_b_y = NULL;
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c1_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c1_eml_mx), 15, "numerictype", 14, sf_mex_dup(c1_b_eml_mx), 15,
      "simulinkarray", 14, c1_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c1_mxArrayOutData, c1_y);
  } else {
    sf_mex_assign(&c1_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c1_mxArrayOutData;
}

static int8_T c1_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int8_T c1_y;
  const mxArray *c1_mxFi = NULL;
  const mxArray *c1_mxInt = NULL;
  int8_T c1_i0;
  sf_mex_check_fi(c1_parentId, c1_u, 0, 0U, 0, c1_eml_mx, c1_b_eml_mx);
  sf_mex_assign(&c1_mxFi, sf_mex_dup(c1_u));
  sf_mex_assign(&c1_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c1_mxFi)));
  sf_mex_import(c1_parentId, sf_mex_dup(c1_mxInt), &c1_i0, 1, 2, 0U, 0, 0U, 0);
  sf_mex_destroy(&c1_mxFi);
  sf_mex_destroy(&c1_mxInt);
  c1_y = c1_i0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_y;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int8_T c1_b_y;
  SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c1_y = sf_mex_dup(c1_mxArrayInData);
    c1_identifier = c1_varName;
    c1_thisId.fIdentifier = c1_identifier;
    c1_thisId.fParent = NULL;
    c1_b_y = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_y), &c1_thisId);
    sf_mex_destroy(&c1_y);
    *(int8_T *)c1_outData = c1_b_y;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  boolean_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(boolean_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int8_T c1_u;
  const mxArray *c1_y = NULL;
  int8_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c1_u = *(int8_T *)c1_inData;
    c1_y = NULL;
    c1_b_u = c1_u;
    c1_b_y = NULL;
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c1_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c1_c_eml_mx), 15, "numerictype", 14, sf_mex_dup(c1_b_eml_mx),
      15, "simulinkarray", 14, c1_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c1_mxArrayOutData, c1_y);
  } else {
    sf_mex_assign(&c1_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c1_mxArrayOutData;
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static real_T c1_b_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nargout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  const mxArray *c1_u;
  const mxArray *c1_y = NULL;
  SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = sf_mex_dup(*(const mxArray **)c1_inData);
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_duplicatearraysafe(&c1_u));
  sf_mex_destroy(&c1_u);
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

const mxArray *sf_c1_hdlcodercpu_eml_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[10];
  c1_ResolvedFunctionInfo (*c1_b_info)[10];
  const mxArray *c1_m18 = NULL;
  int32_T c1_i1;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_b_info = (c1_ResolvedFunctionInfo (*)[10])c1_info;
  (*c1_b_info)[0].context = "";
  (*c1_b_info)[0].name = "fimath";
  (*c1_b_info)[0].dominantType = "char";
  (*c1_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m";
  (*c1_b_info)[0].fileTimeLo = 275520000U;
  (*c1_b_info)[0].fileTimeHi = 30114375U;
  (*c1_b_info)[0].mFileTimeLo = 0U;
  (*c1_b_info)[0].mFileTimeHi = 0U;
  (*c1_b_info)[1].context = "";
  (*c1_b_info)[1].name = "fi_impl";
  (*c1_b_info)[1].dominantType = "";
  (*c1_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m";
  (*c1_b_info)[1].fileTimeLo = 275520000U;
  (*c1_b_info)[1].fileTimeHi = 30114375U;
  (*c1_b_info)[1].mFileTimeLo = 0U;
  (*c1_b_info)[1].mFileTimeHi = 0U;
  (*c1_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  (*c1_b_info)[2].name = "isfi";
  (*c1_b_info)[2].dominantType = "double";
  (*c1_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  (*c1_b_info)[2].fileTimeLo = 335520000U;
  (*c1_b_info)[2].fileTimeHi = 30114375U;
  (*c1_b_info)[2].mFileTimeLo = 0U;
  (*c1_b_info)[2].mFileTimeHi = 0U;
  (*c1_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  (*c1_b_info)[3].name = "isnumerictype";
  (*c1_b_info)[3].dominantType = "char";
  (*c1_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m";
  (*c1_b_info)[3].fileTimeLo = 355520000U;
  (*c1_b_info)[3].fileTimeHi = 30114375U;
  (*c1_b_info)[3].mFileTimeLo = 0U;
  (*c1_b_info)[3].mFileTimeHi = 0U;
  (*c1_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  (*c1_b_info)[4].name = "eml_fi_checkforerror";
  (*c1_b_info)[4].dominantType = "embedded.numerictype";
  (*c1_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m";
  (*c1_b_info)[4].fileTimeLo = 255520000U;
  (*c1_b_info)[4].fileTimeHi = 30114375U;
  (*c1_b_info)[4].mFileTimeLo = 0U;
  (*c1_b_info)[4].mFileTimeHi = 0U;
  (*c1_b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  (*c1_b_info)[5].name = "isfloat";
  (*c1_b_info)[5].dominantType = "embedded.fi";
  (*c1_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m";
  (*c1_b_info)[5].fileTimeLo = 875520000U;
  (*c1_b_info)[5].fileTimeHi = 30114375U;
  (*c1_b_info)[5].mFileTimeLo = 0U;
  (*c1_b_info)[5].mFileTimeHi = 0U;
  (*c1_b_info)[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m";
  (*c1_b_info)[6].name = "get";
  (*c1_b_info)[6].dominantType = "embedded.numerictype";
  (*c1_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m";
  (*c1_b_info)[6].fileTimeLo = 4170487296U;
  (*c1_b_info)[6].fileTimeHi = 30114374U;
  (*c1_b_info)[6].mFileTimeLo = 0U;
  (*c1_b_info)[6].mFileTimeHi = 0U;
  (*c1_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput";
  (*c1_b_info)[7].name = "numerictype";
  (*c1_b_info)[7].dominantType = "embedded.fi";
  (*c1_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m";
  (*c1_b_info)[7].fileTimeLo = 995520000U;
  (*c1_b_info)[7].fileTimeHi = 30114375U;
  (*c1_b_info)[7].mFileTimeLo = 0U;
  (*c1_b_info)[7].mFileTimeHi = 0U;
  (*c1_b_info)[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput";
  (*c1_b_info)[8].name = "fimath";
  (*c1_b_info)[8].dominantType = "embedded.fi";
  (*c1_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m";
  (*c1_b_info)[8].fileTimeLo = 775520000U;
  (*c1_b_info)[8].fileTimeHi = 30114375U;
  (*c1_b_info)[8].mFileTimeLo = 0U;
  (*c1_b_info)[8].mFileTimeHi = 0U;
  (*c1_b_info)[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  (*c1_b_info)[9].name = "eml_fi_checkforntype";
  (*c1_b_info)[9].dominantType = "embedded.fi";
  (*c1_b_info)[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m";
  (*c1_b_info)[9].fileTimeLo = 255520000U;
  (*c1_b_info)[9].fileTimeHi = 30114375U;
  (*c1_b_info)[9].mFileTimeLo = 0U;
  (*c1_b_info)[9].mFileTimeHi = 0U;
  sf_mex_assign(&c1_m18, sf_mex_createstruct("nameCaptureInfo", 1, 10));
  for (c1_i1 = 0; c1_i1 < 10; c1_i1++) {
    c1_r0 = &c1_info[c1_i1];
    sf_mex_addfield(c1_m18, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i1);
    sf_mex_addfield(c1_m18, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i1);
    sf_mex_addfield(c1_m18, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i1);
    sf_mex_addfield(c1_m18, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i1);
    sf_mex_addfield(c1_m18, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i1);
    sf_mex_addfield(c1_m18, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i1);
    sf_mex_addfield(c1_m18, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i1);
    sf_mex_addfield(c1_m18, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i1);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m18);
  return c1_nameCaptureInfo;
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_mxArrayOutData, c1_y);
  return c1_mxArrayOutData;
}

static int32_T c1_c_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i2;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i2, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i2;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c1_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_sfEvent), &c1_thisId);
  sf_mex_destroy(&c1_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  int8_T c1_u;
  const mxArray *c1_y = NULL;
  int8_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c1_u = *(int8_T *)c1_inData;
    c1_y = NULL;
    c1_b_u = c1_u;
    c1_b_y = NULL;
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c1_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c1_c_eml_mx), 15, "numerictype", 14, sf_mex_dup(c1_b_eml_mx),
      15, "simulinkarray", 14, c1_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c1_mxArrayOutData, c1_y);
  } else {
    sf_mex_assign(&c1_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c1_mxArrayOutData;
}

static int8_T c1_d_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_y, const char_T *c1_identifier)
{
  int8_T c1_b_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_y), &c1_thisId);
  sf_mex_destroy(&c1_y);
  return c1_b_y;
}

static int8_T c1_e_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int8_T c1_y;
  const mxArray *c1_mxFi = NULL;
  const mxArray *c1_mxInt = NULL;
  int8_T c1_i3;
  sf_mex_check_fi(c1_parentId, c1_u, 0, 0U, 0, c1_c_eml_mx, c1_b_eml_mx);
  sf_mex_assign(&c1_mxFi, sf_mex_dup(c1_u));
  sf_mex_assign(&c1_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c1_mxFi)));
  sf_mex_import(c1_parentId, sf_mex_dup(c1_mxInt), &c1_i3, 1, 2, 0U, 0, 0U, 0);
  sf_mex_destroy(&c1_mxFi);
  sf_mex_destroy(&c1_mxInt);
  c1_y = c1_i3;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_y;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int8_T c1_b_y;
  SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c1_y = sf_mex_dup(c1_mxArrayInData);
    c1_identifier = c1_varName;
    c1_thisId.fIdentifier = c1_identifier;
    c1_thisId.fParent = NULL;
    c1_b_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_y), &c1_thisId);
    sf_mex_destroy(&c1_y);
    *(int8_T *)c1_outData = c1_b_y;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_f_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_is_active_c1_hdlcodercpu_eml, const char_T
  *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_is_active_c1_hdlcodercpu_eml), &c1_thisId);
  sf_mex_destroy(&c1_is_active_c1_hdlcodercpu_eml);
  return c1_y;
}

static uint8_T c1_g_emlrt_marshallIn(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
static uint32_T* sf_get_sfun_dwork_checksum();
void sf_c1_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2194215384U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2339477300U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(582188289U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3272341710U);
}

mxArray *sf_c1_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(1396009273U);
    pr[1] = (double)(1987030133U);
    pr[2] = (double)(2155724274U);
    pr[3] = (double)(1750811067U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
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

static const mxArray *sf_get_sim_state_info_c1_hdlcodercpu_eml(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c1_hdlcodercpu_eml\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_hdlcodercpu_eml_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
    chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_hdlcodercpu_emlMachineNumber_,
           1,
           1,
           1,
           3,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"u");
          _SFD_SET_DATA_PROPS(1,2,0,1,"y");
          _SFD_SET_DATA_PROPS(2,1,1,0,"enable");
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
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,362);
        _SFD_CV_INIT_EML_IF(0,0,316,326,-1,362);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c1_g_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c1_g_sf_marshallOut,(MexInFcnForType)c1_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          int8_T *c1_u;
          int8_T *c1_y;
          boolean_T *c1_enable;
          c1_enable = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c1_y = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c1_u = (int8_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c1_u);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_y);
          _SFD_SET_DATA_VALUE_PTR(2U, c1_enable);
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
      "hdlcodercpu_eml", "hdlcodercpu_eml", 1, "dworkChecksum");
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

static void sf_opaque_initialize_c1_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc1_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S);
  chart_debug_initialization(((SFc1_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_hdlcodercpu_eml((SFc1_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
  initialize_c1_hdlcodercpu_eml((SFc1_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c1_hdlcodercpu_eml(void *chartInstanceVar)
{
  enable_c1_hdlcodercpu_eml((SFc1_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c1_hdlcodercpu_eml(void *chartInstanceVar)
{
  disable_c1_hdlcodercpu_eml((SFc1_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c1_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_c1_hdlcodercpu_eml((SFc1_hdlcodercpu_emlInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c1_hdlcodercpu_eml(void *chartInstanceVar)
{
  ext_mode_exec_c1_hdlcodercpu_eml((SFc1_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_hdlcodercpu_eml(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_hdlcodercpu_eml
    ((SFc1_hdlcodercpu_emlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_hdlcodercpu_eml();/* state var info */
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

extern void sf_internal_set_sim_state_c1_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_hdlcodercpu_eml((SFc1_hdlcodercpu_emlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_hdlcodercpu_eml(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_hdlcodercpu_eml(S);
}

static void sf_opaque_set_sim_state_c1_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c1_hdlcodercpu_eml(S, st);
}

static void sf_opaque_terminate_c1_hdlcodercpu_eml(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_hdlcodercpu_emlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_hdlcodercpu_eml((SFc1_hdlcodercpu_emlInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_hdlcodercpu_eml((SFc1_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_hdlcodercpu_eml(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_hdlcodercpu_eml((SFc1_hdlcodercpu_emlInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

mxArray *sf_c1_hdlcodercpu_eml_get_testpoint_info(void)
{
  const char *infoEncStr[] = {
    "100 S'varName','path'{{T\"is_active_c1_hdlcodercpu_eml\",T\"is_active_c1_hdlcodercpu_eml\"}}"
  };

  mxArray *mxTpInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 1, 10);
  return mxTpInfo;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x4'type','isSigned','wordLength','bias','slope','exponent','isComplex','size'{{T\"int32\",,,,,,M[0],M[]},{T\"boolean\",,,,,,M[0],M[]},{T\"boolean\",,,,,,M[0],M[]},{T\"uint8\",,,,,,M[0],M[]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 4, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 3851270630U, 3363230343U, 1651207761U,
    946165807U };

  return checksum;
}

static void mdlSetWorkWidths_c1_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"hdlcodercpu_eml","hdlcodercpu_eml",1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml","hdlcodercpu_eml",1,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml",
      "hdlcodercpu_eml",1,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",
        1,2);
      sf_mark_chart_reusable_outputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",1,1);
    }

    sf_set_rtw_dwork_info(S,"hdlcodercpu_eml","hdlcodercpu_eml",1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2872108169U));
  ssSetChecksum1(S,(1313570604U));
  ssSetChecksum2(S,(2054517717U));
  ssSetChecksum3(S,(1312038393U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c1_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "hdlcodercpu_eml", "hdlcodercpu_eml",1);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_hdlcodercpu_eml(SimStruct *S)
{
  SFc1_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc1_hdlcodercpu_emlInstanceStruct *)malloc(sizeof
    (SFc1_hdlcodercpu_emlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_hdlcodercpu_emlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_hdlcodercpu_eml;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_hdlcodercpu_eml;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_hdlcodercpu_eml;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_hdlcodercpu_eml;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_hdlcodercpu_eml;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_hdlcodercpu_eml;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_hdlcodercpu_eml;
  chartInstance->chartInfo.extModeExec =
    sf_opaque_ext_mode_exec_c1_hdlcodercpu_eml;
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

void c1_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_hdlcodercpu_eml(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_hdlcodercpu_eml_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
