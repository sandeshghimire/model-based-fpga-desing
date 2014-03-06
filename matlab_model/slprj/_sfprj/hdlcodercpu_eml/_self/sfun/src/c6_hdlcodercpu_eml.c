/* Include files */

#include "blascompat32.h"
#include "hdlcodercpu_eml_sfun.h"
#include "c6_hdlcodercpu_eml.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "hdlcodercpu_eml_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const mxArray *c6_eml_mx;
static const char * c6_debug_family_names[7] = { "hdl_fm", "nargin", "nargout",
  "func", "IR_in", "IR_out", "IR_value" };

static const mxArray *c6_b_eml_mx;
static const mxArray *c6_c_eml_mx;

/* Function Declarations */
static void initialize_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initialize_params_c6_hdlcodercpu_eml
  (SFc6_hdlcodercpu_emlInstanceStruct *chartInstance);
static void enable_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void disable_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c6_update_debugger_state_c6_hdlcodercpu_eml
  (SFc6_hdlcodercpu_emlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c6_hdlcodercpu_eml
  (SFc6_hdlcodercpu_emlInstanceStruct *chartInstance);
static void set_sim_state_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c6_st);
static void finalize_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void sf_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c6_chartstep_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initSimStructsc6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber);
static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData);
static uint16_T c6_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_b_IR_value, const char_T *c6_identifier);
static uint16_T c6_b_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static uint16_T c6_c_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_IR_out, const char_T *c6_identifier);
static uint16_T c6_d_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_e_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static real_T c6_e_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_f_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static const mxArray *c6_g_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static int32_T c6_f_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_h_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static uint8_T c6_g_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_b_is_active_c6_hdlcodercpu_eml, const char_T
  *c6_identifier);
static uint8_T c6_h_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void init_dsm_address_info(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c6_IR_value_not_empty = FALSE;
  chartInstance->c6_is_active_c6_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c6_c_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 2.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c6_b_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 12.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c6_eml_mx, sf_mex_call_debug("fimath", 1U, 38U, 15, "RoundMode",
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

static void initialize_params_c6_hdlcodercpu_eml
  (SFc6_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void enable_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c6_update_debugger_state_c6_hdlcodercpu_eml
  (SFc6_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c6_hdlcodercpu_eml
  (SFc6_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  uint16_T c6_hoistedGlobal;
  uint16_T c6_u;
  const mxArray *c6_b_y = NULL;
  uint16_T c6_b_u;
  const mxArray *c6_c_y = NULL;
  uint16_T c6_b_hoistedGlobal;
  uint16_T c6_c_u;
  const mxArray *c6_d_y = NULL;
  uint16_T c6_d_u;
  const mxArray *c6_e_y = NULL;
  uint8_T c6_c_hoistedGlobal;
  uint8_T c6_e_u;
  const mxArray *c6_f_y = NULL;
  uint16_T *c6_IR_out;
  c6_IR_out = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellarray(3));
  c6_hoistedGlobal = *c6_IR_out;
  c6_u = c6_hoistedGlobal;
  c6_b_y = NULL;
  c6_b_u = c6_u;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_b_u, 5, 0U, 0U, 0U, 0));
  sf_mex_assign(&c6_b_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c6_eml_mx), 15, "numerictype", 14, sf_mex_dup(c6_b_eml_mx), 15,
    "simulinkarray", 14, c6_c_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c6_y, 0, c6_b_y);
  c6_b_hoistedGlobal = chartInstance->c6_IR_value;
  c6_c_u = c6_b_hoistedGlobal;
  c6_d_y = NULL;
  if (!chartInstance->c6_IR_value_not_empty) {
    sf_mex_assign(&c6_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    c6_d_u = c6_c_u;
    c6_e_y = NULL;
    sf_mex_assign(&c6_e_y, sf_mex_create("y", &c6_d_u, 5, 0U, 0U, 0U, 0));
    sf_mex_assign(&c6_d_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c6_eml_mx), 15, "numerictype", 14, sf_mex_dup(c6_b_eml_mx), 15,
      "simulinkarray", 14, c6_e_y, 15, "fimathislocal", 3, TRUE));
  }

  sf_mex_setcell(c6_y, 1, c6_d_y);
  c6_c_hoistedGlobal = chartInstance->c6_is_active_c6_hdlcodercpu_eml;
  c6_e_u = c6_c_hoistedGlobal;
  c6_f_y = NULL;
  sf_mex_assign(&c6_f_y, sf_mex_create("y", &c6_e_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c6_y, 2, c6_f_y);
  sf_mex_assign(&c6_st, c6_y);
  return c6_st;
}

static void set_sim_state_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c6_st)
{
  const mxArray *c6_u;
  uint16_T *c6_IR_out;
  c6_IR_out = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c6_doneDoubleBufferReInit = TRUE;
  c6_u = sf_mex_dup(c6_st);
  *c6_IR_out = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c6_u, 0)), "IR_out");
  chartInstance->c6_IR_value = c6_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 1)), "IR_value");
  chartInstance->c6_is_active_c6_hdlcodercpu_eml = c6_g_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 2)),
     "is_active_c6_hdlcodercpu_eml");
  sf_mex_destroy(&c6_u);
  c6_update_debugger_state_c6_hdlcodercpu_eml(chartInstance);
  sf_mex_destroy(&c6_st);
}

static void finalize_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&c6_eml_mx);
  sf_mex_destroy(&c6_b_eml_mx);
  sf_mex_destroy(&c6_c_eml_mx);
}

static void sf_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  uint8_T *c6_func;
  uint16_T *c6_IR_out;
  uint16_T *c6_IR_in;
  c6_IR_in = (uint16_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c6_IR_out = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c6_func = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c6_func, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c6_IR_out, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c6_IR_in, 2U);
  chartInstance->c6_sfEvent = CALL_EVENT;
  c6_chartstep_c6_hdlcodercpu_eml(chartInstance);
  sf_debug_check_for_state_inconsistency(_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c6_chartstep_c6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  uint8_T c6_hoistedGlobal;
  uint16_T c6_b_hoistedGlobal;
  uint8_T c6_func;
  uint16_T c6_IR_in;
  uint32_T c6_debug_family_var_map[7];
  const mxArray *c6_hdl_fm = NULL;
  real_T c6_nargin = 2.0;
  real_T c6_nargout = 1.0;
  uint16_T c6_IR_out;
  const mxArray *c6_m0 = NULL;
  const mxArray *c6_m1 = NULL;
  const mxArray *c6_m2 = NULL;
  const mxArray *c6_m3 = NULL;
  const mxArray *c6_m4 = NULL;
  const mxArray *c6_m5 = NULL;
  const mxArray *c6_m6 = NULL;
  const mxArray *c6_m7 = NULL;
  const mxArray *c6_m8 = NULL;
  const mxArray *c6_m9 = NULL;
  const mxArray *c6_m10 = NULL;
  const mxArray *c6_m11 = NULL;
  const mxArray *c6_m12 = NULL;
  const mxArray *c6_m13 = NULL;
  uint8_T c6_A;
  uint8_T c6_xfi;
  const mxArray *c6_m14 = NULL;
  const mxArray *c6_m15 = NULL;
  uint8_T c6_iA;
  const mxArray *c6_m16 = NULL;
  const mxArray *c6_m17 = NULL;
  const mxArray *c6_m18 = NULL;
  const mxArray *c6_m19 = NULL;
  const mxArray *c6_m20 = NULL;
  const mxArray *c6_m21 = NULL;
  const mxArray *c6_m22 = NULL;
  uint16_T *c6_b_IR_out;
  uint8_T *c6_b_func;
  uint16_T *c6_b_IR_in;
  c6_b_IR_in = (uint16_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c6_b_IR_out = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c6_b_func = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
  c6_hoistedGlobal = *c6_b_func;
  c6_b_hoistedGlobal = *c6_b_IR_in;
  c6_func = c6_hoistedGlobal;
  c6_IR_in = c6_b_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c6_debug_family_names,
    c6_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c6_hdl_fm, 0U, c6_f_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c6_nargin, 1U, c6_e_sf_marshallOut,
    c6_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c6_nargout, 2U, c6_e_sf_marshallOut,
    c6_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c6_func, 3U, c6_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c6_IR_in, 4U, c6_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c6_IR_out, 5U, c6_b_sf_marshallOut,
    c6_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&chartInstance->c6_IR_value, 6U,
    c6_sf_marshallOut, c6_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 9);
  c6_hdl_fm = c6_eml_mx;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 18);
  if (CV_EML_IF(0, 0, !chartInstance->c6_IR_value_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 19);
    sf_mex_destroy(&c6_m0);
    sf_mex_destroy(&c6_m1);
    sf_mex_destroy(&c6_m2);
    sf_mex_destroy(&c6_m3);
    sf_mex_destroy(&c6_m4);
    sf_mex_destroy(&c6_m5);
    sf_mex_destroy(&c6_m6);
    chartInstance->c6_IR_value = 0U;
    chartInstance->c6_IR_value_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 22);
  sf_mex_destroy(&c6_m7);
  sf_mex_destroy(&c6_m8);
  sf_mex_destroy(&c6_m9);
  sf_mex_destroy(&c6_m10);
  sf_mex_destroy(&c6_m11);
  sf_mex_destroy(&c6_m12);
  sf_mex_destroy(&c6_m13);
  c6_IR_out = 0U;
  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 24);
  c6_A = c6_func;
  c6_xfi = c6_A;
  sf_mex_destroy(&c6_m14);
  sf_mex_destroy(&c6_m15);
  c6_iA = c6_xfi;
  switch (c6_iA) {
   case 0U:
    CV_EML_SWITCH(0, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 27);
    sf_mex_destroy(&c6_m16);
    sf_mex_destroy(&c6_m17);
    sf_mex_destroy(&c6_m18);
    sf_mex_destroy(&c6_m19);
    sf_mex_destroy(&c6_m20);
    sf_mex_destroy(&c6_m21);
    sf_mex_destroy(&c6_m22);
    chartInstance->c6_IR_value = 0U;
    break;

   case 1U:
    CV_EML_SWITCH(0, 0, 2);
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 30);
    chartInstance->c6_IR_value = c6_IR_in;
    break;

   case 2U:
    CV_EML_SWITCH(0, 0, 3);
    _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, 33);
    c6_IR_out = chartInstance->c6_IR_value;
    break;

   default:
    CV_EML_SWITCH(0, 0, 0);
    break;
  }

  _SFD_EML_CALL(0U, chartInstance->c6_sfEvent, -33);
  sf_debug_symbol_scope_pop();
  *c6_b_IR_out = c6_IR_out;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c6_sfEvent);
}

static void initSimStructsc6_hdlcodercpu_eml(SFc6_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber)
{
}

static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  uint16_T c6_u;
  const mxArray *c6_y = NULL;
  uint16_T c6_b_u;
  const mxArray *c6_b_y = NULL;
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c6_u = *(uint16_T *)c6_inData;
    c6_y = NULL;
    if (!chartInstance->c6_IR_value_not_empty) {
      sf_mex_assign(&c6_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
    } else {
      c6_b_u = c6_u;
      c6_b_y = NULL;
      sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_b_u, 5, 0U, 0U, 0U, 0));
      sf_mex_assign(&c6_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
        sf_mex_dup(c6_eml_mx), 15, "numerictype", 14, sf_mex_dup(c6_b_eml_mx),
        15, "simulinkarray", 14, c6_b_y, 15, "fimathislocal", 3, TRUE));
    }

    sf_mex_assign(&c6_mxArrayOutData, c6_y);
  } else {
    sf_mex_assign(&c6_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c6_mxArrayOutData;
}

static uint16_T c6_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_b_IR_value, const char_T *c6_identifier)
{
  uint16_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_IR_value),
    &c6_thisId);
  sf_mex_destroy(&c6_b_IR_value);
  return c6_y;
}

static uint16_T c6_b_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint16_T c6_y;
  const mxArray *c6_mxFi = NULL;
  const mxArray *c6_mxInt = NULL;
  uint16_T c6_u0;
  if (mxIsEmpty(c6_u)) {
    chartInstance->c6_IR_value_not_empty = FALSE;
  } else {
    chartInstance->c6_IR_value_not_empty = TRUE;
    sf_mex_check_fi(c6_parentId, c6_u, 0, 0U, 0, c6_eml_mx, c6_b_eml_mx);
    sf_mex_assign(&c6_mxFi, sf_mex_dup(c6_u));
    sf_mex_assign(&c6_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
                   (c6_mxFi)));
    sf_mex_import(c6_parentId, sf_mex_dup(c6_mxInt), &c6_u0, 1, 5, 0U, 0, 0U, 0);
    sf_mex_destroy(&c6_mxFi);
    sf_mex_destroy(&c6_mxInt);
    c6_y = c6_u0;
  }

  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_IR_value;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  uint16_T c6_y;
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c6_b_IR_value = sf_mex_dup(c6_mxArrayInData);
    c6_identifier = c6_varName;
    c6_thisId.fIdentifier = c6_identifier;
    c6_thisId.fParent = NULL;
    c6_y = c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_IR_value),
      &c6_thisId);
    sf_mex_destroy(&c6_b_IR_value);
    *(uint16_T *)c6_outData = c6_y;
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  uint16_T c6_u;
  const mxArray *c6_y = NULL;
  uint16_T c6_b_u;
  const mxArray *c6_b_y = NULL;
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c6_u = *(uint16_T *)c6_inData;
    c6_y = NULL;
    c6_b_u = c6_u;
    c6_b_y = NULL;
    sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_b_u, 5, 0U, 0U, 0U, 0));
    sf_mex_assign(&c6_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c6_eml_mx), 15, "numerictype", 14, sf_mex_dup(c6_b_eml_mx), 15,
      "simulinkarray", 14, c6_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c6_mxArrayOutData, c6_y);
  } else {
    sf_mex_assign(&c6_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c6_mxArrayOutData;
}

static uint16_T c6_c_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_IR_out, const char_T *c6_identifier)
{
  uint16_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_IR_out), &c6_thisId);
  sf_mex_destroy(&c6_IR_out);
  return c6_y;
}

static uint16_T c6_d_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint16_T c6_y;
  const mxArray *c6_mxFi = NULL;
  const mxArray *c6_mxInt = NULL;
  uint16_T c6_u1;
  sf_mex_check_fi(c6_parentId, c6_u, 0, 0U, 0, c6_eml_mx, c6_b_eml_mx);
  sf_mex_assign(&c6_mxFi, sf_mex_dup(c6_u));
  sf_mex_assign(&c6_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c6_mxFi)));
  sf_mex_import(c6_parentId, sf_mex_dup(c6_mxInt), &c6_u1, 1, 5, 0U, 0, 0U, 0);
  sf_mex_destroy(&c6_mxFi);
  sf_mex_destroy(&c6_mxInt);
  c6_y = c6_u1;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_IR_out;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  uint16_T c6_y;
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c6_IR_out = sf_mex_dup(c6_mxArrayInData);
    c6_identifier = c6_varName;
    c6_thisId.fIdentifier = c6_identifier;
    c6_thisId.fParent = NULL;
    c6_y = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_IR_out),
      &c6_thisId);
    sf_mex_destroy(&c6_IR_out);
    *(uint16_T *)c6_outData = c6_y;
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  uint16_T c6_u;
  const mxArray *c6_y = NULL;
  uint16_T c6_b_u;
  const mxArray *c6_b_y = NULL;
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c6_u = *(uint16_T *)c6_inData;
    c6_y = NULL;
    c6_b_u = c6_u;
    c6_b_y = NULL;
    sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_b_u, 5, 0U, 0U, 0U, 0));
    sf_mex_assign(&c6_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c6_eml_mx), 15, "numerictype", 14, sf_mex_dup(c6_b_eml_mx), 15,
      "simulinkarray", 14, c6_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c6_mxArrayOutData, c6_y);
  } else {
    sf_mex_assign(&c6_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c6_mxArrayOutData;
}

static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  uint8_T c6_u;
  const mxArray *c6_y = NULL;
  uint8_T c6_b_u;
  const mxArray *c6_b_y = NULL;
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c6_u = *(uint8_T *)c6_inData;
    c6_y = NULL;
    c6_b_u = c6_u;
    c6_b_y = NULL;
    sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c6_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c6_eml_mx), 15, "numerictype", 14, sf_mex_dup(c6_c_eml_mx), 15,
      "simulinkarray", 14, c6_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c6_mxArrayOutData, c6_y);
  } else {
    sf_mex_assign(&c6_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c6_mxArrayOutData;
}

static const mxArray *c6_e_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  real_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(real_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c6_mxArrayOutData, c6_y);
  return c6_mxArrayOutData;
}

static real_T c6_e_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real_T c6_y;
  real_T c6_d0;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_d0, 1, 0, 0U, 0, 0U, 0);
  c6_y = c6_d0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_nargout;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y;
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c6_nargout = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_nargout), &c6_thisId);
  sf_mex_destroy(&c6_nargout);
  *(real_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_f_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  const mxArray *c6_u;
  const mxArray *c6_y = NULL;
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = sf_mex_dup(*(const mxArray **)c6_inData);
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_duplicatearraysafe(&c6_u));
  sf_mex_destroy(&c6_u);
  sf_mex_assign(&c6_mxArrayOutData, c6_y);
  return c6_mxArrayOutData;
}

const mxArray *sf_c6_hdlcodercpu_eml_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo;
  c6_ResolvedFunctionInfo c6_info[9];
  c6_ResolvedFunctionInfo (*c6_b_info)[9];
  const mxArray *c6_m23 = NULL;
  int32_T c6_i0;
  c6_ResolvedFunctionInfo *c6_r0;
  c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  c6_b_info = (c6_ResolvedFunctionInfo (*)[9])c6_info;
  (*c6_b_info)[0].context = "";
  (*c6_b_info)[0].name = "fimath";
  (*c6_b_info)[0].dominantType = "char";
  (*c6_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m";
  (*c6_b_info)[0].fileTimeLo = 275520000U;
  (*c6_b_info)[0].fileTimeHi = 30114375U;
  (*c6_b_info)[0].mFileTimeLo = 0U;
  (*c6_b_info)[0].mFileTimeHi = 0U;
  (*c6_b_info)[1].context = "";
  (*c6_b_info)[1].name = "fi_impl";
  (*c6_b_info)[1].dominantType = "";
  (*c6_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m";
  (*c6_b_info)[1].fileTimeLo = 275520000U;
  (*c6_b_info)[1].fileTimeHi = 30114375U;
  (*c6_b_info)[1].mFileTimeLo = 0U;
  (*c6_b_info)[1].mFileTimeHi = 0U;
  (*c6_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  (*c6_b_info)[2].name = "isfi";
  (*c6_b_info)[2].dominantType = "double";
  (*c6_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  (*c6_b_info)[2].fileTimeLo = 335520000U;
  (*c6_b_info)[2].fileTimeHi = 30114375U;
  (*c6_b_info)[2].mFileTimeLo = 0U;
  (*c6_b_info)[2].mFileTimeHi = 0U;
  (*c6_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  (*c6_b_info)[3].name = "isnumerictype";
  (*c6_b_info)[3].dominantType = "char";
  (*c6_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m";
  (*c6_b_info)[3].fileTimeLo = 355520000U;
  (*c6_b_info)[3].fileTimeHi = 30114375U;
  (*c6_b_info)[3].mFileTimeLo = 0U;
  (*c6_b_info)[3].mFileTimeHi = 0U;
  (*c6_b_info)[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  (*c6_b_info)[4].name = "eml_fi_checkforerror";
  (*c6_b_info)[4].dominantType = "embedded.numerictype";
  (*c6_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m";
  (*c6_b_info)[4].fileTimeLo = 255520000U;
  (*c6_b_info)[4].fileTimeHi = 30114375U;
  (*c6_b_info)[4].mFileTimeLo = 0U;
  (*c6_b_info)[4].mFileTimeHi = 0U;
  (*c6_b_info)[5].context = "";
  (*c6_b_info)[5].name = "uint8";
  (*c6_b_info)[5].dominantType = "embedded.fi";
  (*c6_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m";
  (*c6_b_info)[5].fileTimeLo = 1115520000U;
  (*c6_b_info)[5].fileTimeHi = 30114375U;
  (*c6_b_info)[5].mFileTimeLo = 0U;
  (*c6_b_info)[5].mFileTimeHi = 0U;
  (*c6_b_info)[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m";
  (*c6_b_info)[6].name = "eml_fi_getStoredIntValAsDType";
  (*c6_b_info)[6].dominantType = "embedded.fi";
  (*c6_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getStoredIntValAsDType.m";
  (*c6_b_info)[6].fileTimeLo = 655520000U;
  (*c6_b_info)[6].fileTimeHi = 30114375U;
  (*c6_b_info)[6].mFileTimeLo = 0U;
  (*c6_b_info)[6].mFileTimeHi = 0U;
  (*c6_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getStoredIntValAsDType.m";
  (*c6_b_info)[7].name = "isfixed";
  (*c6_b_info)[7].dominantType = "embedded.fi";
  (*c6_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  (*c6_b_info)[7].fileTimeLo = 875520000U;
  (*c6_b_info)[7].fileTimeHi = 30114375U;
  (*c6_b_info)[7].mFileTimeLo = 0U;
  (*c6_b_info)[7].mFileTimeHi = 0U;
  (*c6_b_info)[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  (*c6_b_info)[8].name = "get";
  (*c6_b_info)[8].dominantType = "embedded.numerictype";
  (*c6_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m";
  (*c6_b_info)[8].fileTimeLo = 4170487296U;
  (*c6_b_info)[8].fileTimeHi = 30114374U;
  (*c6_b_info)[8].mFileTimeLo = 0U;
  (*c6_b_info)[8].mFileTimeHi = 0U;
  sf_mex_assign(&c6_m23, sf_mex_createstruct("nameCaptureInfo", 1, 9));
  for (c6_i0 = 0; c6_i0 < 9; c6_i0++) {
    c6_r0 = &c6_info[c6_i0];
    sf_mex_addfield(c6_m23, sf_mex_create("nameCaptureInfo", c6_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c6_r0->context)), "context", "nameCaptureInfo",
                    c6_i0);
    sf_mex_addfield(c6_m23, sf_mex_create("nameCaptureInfo", c6_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c6_r0->name)), "name", "nameCaptureInfo", c6_i0);
    sf_mex_addfield(c6_m23, sf_mex_create("nameCaptureInfo", c6_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c6_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c6_i0);
    sf_mex_addfield(c6_m23, sf_mex_create("nameCaptureInfo", c6_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c6_r0->resolved)), "resolved", "nameCaptureInfo",
                    c6_i0);
    sf_mex_addfield(c6_m23, sf_mex_create("nameCaptureInfo", &c6_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c6_i0);
    sf_mex_addfield(c6_m23, sf_mex_create("nameCaptureInfo", &c6_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c6_i0);
    sf_mex_addfield(c6_m23, sf_mex_create("nameCaptureInfo", &c6_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c6_i0);
    sf_mex_addfield(c6_m23, sf_mex_create("nameCaptureInfo", &c6_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c6_i0);
  }

  sf_mex_assign(&c6_nameCaptureInfo, c6_m23);
  return c6_nameCaptureInfo;
}

static const mxArray *c6_g_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(int32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c6_mxArrayOutData, c6_y);
  return c6_mxArrayOutData;
}

static int32_T c6_f_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_y;
  int32_T c6_i1;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i1, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i1;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_sfEvent;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c6_b_sfEvent = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_sfEvent),
    &c6_thisId);
  sf_mex_destroy(&c6_b_sfEvent);
  *(int32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_h_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData;
  uint8_T c6_u;
  const mxArray *c6_y = NULL;
  uint8_T c6_b_u;
  const mxArray *c6_b_y = NULL;
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c6_u = *(uint8_T *)c6_inData;
    c6_y = NULL;
    c6_b_u = c6_u;
    c6_b_y = NULL;
    sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c6_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c6_eml_mx), 15, "numerictype", 14, sf_mex_dup(c6_c_eml_mx), 15,
      "simulinkarray", 14, c6_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c6_mxArrayOutData, c6_y);
  } else {
    sf_mex_assign(&c6_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c6_mxArrayOutData;
}

static uint8_T c6_g_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_b_is_active_c6_hdlcodercpu_eml, const char_T
  *c6_identifier)
{
  uint8_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_is_active_c6_hdlcodercpu_eml), &c6_thisId);
  sf_mex_destroy(&c6_b_is_active_c6_hdlcodercpu_eml);
  return c6_y;
}

static uint8_T c6_h_emlrt_marshallIn(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint8_T c6_y;
  uint8_T c6_u2;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u2, 1, 3, 0U, 0, 0U, 0);
  c6_y = c6_u2;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void init_dsm_address_info(SFc6_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c6_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3285679824U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3595050719U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2194793899U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1151752607U);
}

mxArray *sf_c6_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(3364170226U);
    pr[1] = (double)(2564510118U);
    pr[2] = (double)(2434234895U);
    pr[3] = (double)(2248102270U);
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
        mxSetField(mxFixpt,0,"isSigned",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(2));
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
        mxSetField(mxFixpt,0,"isSigned",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(12));
        mxSetField(mxFixpt,0,"bias",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"slope",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"exponent",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"isScaledDouble",mxCreateDoubleScalar(0));
        mxSetField(mxType,0,"fixpt",mxFixpt);
      }

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
        mxSetField(mxFixpt,0,"isSigned",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(12));
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

static const mxArray *sf_get_sim_state_info_c6_hdlcodercpu_eml(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"IR_out\",},{M[4],M[0],T\"IR_value\",S'l','i','p'{{M1x2[472 480],M[0],}}},{M[8],M[0],T\"is_active_c6_hdlcodercpu_eml\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_hdlcodercpu_eml_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
    chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_hdlcodercpu_emlMachineNumber_,
           6,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"func");
          _SFD_SET_DATA_PROPS(1,2,0,1,"IR_out");
          _SFD_SET_DATA_PROPS(2,1,1,0,"IR_in");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,809);
        _SFD_CV_INIT_EML_IF(0,0,482,503,-1,547);

        {
          static int caseStart[] = { -1, 617, 690, 752 };

          static int caseExprEnd[] = { 8, 623, 696, 758 };

          _SFD_CV_INIT_EML_SWITCH(0,0,592,611,808,4,&(caseStart[0]),
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

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,1,0,2,0,1,0,0,
          (MexFcnForType)c6_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT16,0,NULL,1,0,12,0,1,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)c6_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT16,0,NULL,1,0,12,0,1,0,0,
          (MexFcnForType)c6_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          uint8_T *c6_func;
          uint16_T *c6_IR_out;
          uint16_T *c6_IR_in;
          c6_IR_in = (uint16_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c6_IR_out = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c6_func = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c6_func);
          _SFD_SET_DATA_VALUE_PTR(1U, c6_IR_out);
          _SFD_SET_DATA_VALUE_PTR(2U, c6_IR_in);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_hdlcodercpu_emlMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c6_hdlcodercpu_eml(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc6_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c6_hdlcodercpu_eml((SFc6_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
  initialize_c6_hdlcodercpu_eml((SFc6_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c6_hdlcodercpu_eml(void *chartInstanceVar)
{
  enable_c6_hdlcodercpu_eml((SFc6_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c6_hdlcodercpu_eml(void *chartInstanceVar)
{
  disable_c6_hdlcodercpu_eml((SFc6_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c6_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_c6_hdlcodercpu_eml((SFc6_hdlcodercpu_emlInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c6_hdlcodercpu_eml(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c6_hdlcodercpu_eml
    ((SFc6_hdlcodercpu_emlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_hdlcodercpu_eml();/* state var info */
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

extern void sf_internal_set_sim_state_c6_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c6_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c6_hdlcodercpu_eml((SFc6_hdlcodercpu_emlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c6_hdlcodercpu_eml(SimStruct* S)
{
  return sf_internal_get_sim_state_c6_hdlcodercpu_eml(S);
}

static void sf_opaque_set_sim_state_c6_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c6_hdlcodercpu_eml(S, st);
}

static void sf_opaque_terminate_c6_hdlcodercpu_eml(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_hdlcodercpu_emlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c6_hdlcodercpu_eml((SFc6_hdlcodercpu_emlInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc6_hdlcodercpu_eml((SFc6_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_hdlcodercpu_eml(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c6_hdlcodercpu_eml((SFc6_hdlcodercpu_emlInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c6_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"hdlcodercpu_eml","hdlcodercpu_eml",6);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml","hdlcodercpu_eml",6,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml",
      "hdlcodercpu_eml",6,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",
        6,2);
      sf_mark_chart_reusable_outputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",6,1);
    }

    sf_set_rtw_dwork_info(S,"hdlcodercpu_eml","hdlcodercpu_eml",6);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2184297161U));
  ssSetChecksum1(S,(2236829549U));
  ssSetChecksum2(S,(3691329435U));
  ssSetChecksum3(S,(651256155U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c6_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "hdlcodercpu_eml", "hdlcodercpu_eml",6);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c6_hdlcodercpu_eml(SimStruct *S)
{
  SFc6_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc6_hdlcodercpu_emlInstanceStruct *)malloc(sizeof
    (SFc6_hdlcodercpu_emlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc6_hdlcodercpu_emlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c6_hdlcodercpu_eml;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c6_hdlcodercpu_eml;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c6_hdlcodercpu_eml;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c6_hdlcodercpu_eml;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c6_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c6_hdlcodercpu_eml;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c6_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c6_hdlcodercpu_eml;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlStart = mdlStart_c6_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c6_hdlcodercpu_eml;
  chartInstance->chartInfo.extModeExec = NULL;
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

void c6_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c6_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_hdlcodercpu_eml(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_hdlcodercpu_eml_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
