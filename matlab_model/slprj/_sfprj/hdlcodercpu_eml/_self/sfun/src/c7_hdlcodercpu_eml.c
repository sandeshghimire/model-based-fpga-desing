/* Include files */

#include "blascompat32.h"
#include "hdlcodercpu_eml_sfun.h"
#include "c7_hdlcodercpu_eml.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "hdlcodercpu_eml_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const mxArray *c7_eml_mx;
static const char * c7_debug_family_names[7] = { "hdl_fm", "nargin", "nargout",
  "func", "addr_in", "addr_out", "PC_value" };

static const mxArray *c7_b_eml_mx;
static const mxArray *c7_c_eml_mx;

/* Function Declarations */
static void initialize_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initialize_params_c7_hdlcodercpu_eml
  (SFc7_hdlcodercpu_emlInstanceStruct *chartInstance);
static void enable_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void disable_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c7_update_debugger_state_c7_hdlcodercpu_eml
  (SFc7_hdlcodercpu_emlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c7_hdlcodercpu_eml
  (SFc7_hdlcodercpu_emlInstanceStruct *chartInstance);
static void set_sim_state_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c7_st);
static void finalize_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void sf_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c7_chartstep_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initSimStructsc7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber);
static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData);
static uint8_T c7_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_b_PC_value, const char_T *c7_identifier);
static uint8_T c7_b_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static uint8_T c7_c_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_addr_out, const char_T *c7_identifier);
static uint8_T c7_d_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static const mxArray *c7_d_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static const mxArray *c7_e_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static real_T c7_e_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_f_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static void c7_info_helper(c7_ResolvedFunctionInfo c7_info[18]);
static uint8_T c7_uint8(SFc7_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c7_A);
static const mxArray *c7_g_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static int32_T c7_f_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void c7_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData);
static const mxArray *c7_h_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData);
static uint8_T c7_g_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_b_is_active_c7_hdlcodercpu_eml, const char_T
  *c7_identifier);
static uint8_T c7_h_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId);
static void init_dsm_address_info(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  chartInstance->c7_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c7_PC_value_not_empty = FALSE;
  chartInstance->c7_is_active_c7_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c7_c_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 2.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c7_b_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 8.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c7_eml_mx, sf_mex_call_debug("fimath", 1U, 38U, 15, "RoundMode",
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

static void initialize_params_c7_hdlcodercpu_eml
  (SFc7_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void enable_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c7_update_debugger_state_c7_hdlcodercpu_eml
  (SFc7_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c7_hdlcodercpu_eml
  (SFc7_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c7_st;
  const mxArray *c7_y = NULL;
  uint8_T c7_hoistedGlobal;
  uint8_T c7_u;
  const mxArray *c7_b_y = NULL;
  uint8_T c7_b_u;
  const mxArray *c7_c_y = NULL;
  uint8_T c7_b_hoistedGlobal;
  uint8_T c7_c_u;
  const mxArray *c7_d_y = NULL;
  uint8_T c7_d_u;
  const mxArray *c7_e_y = NULL;
  uint8_T c7_c_hoistedGlobal;
  uint8_T c7_e_u;
  const mxArray *c7_f_y = NULL;
  uint8_T *c7_addr_out;
  c7_addr_out = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c7_st = NULL;
  c7_st = NULL;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_createcellarray(3));
  c7_hoistedGlobal = *c7_addr_out;
  c7_u = c7_hoistedGlobal;
  c7_b_y = NULL;
  c7_b_u = c7_u;
  c7_c_y = NULL;
  sf_mex_assign(&c7_c_y, sf_mex_create("y", &c7_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c7_b_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c7_eml_mx), 15, "numerictype", 14, sf_mex_dup(c7_b_eml_mx), 15,
    "simulinkarray", 14, c7_c_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c7_y, 0, c7_b_y);
  c7_b_hoistedGlobal = chartInstance->c7_PC_value;
  c7_c_u = c7_b_hoistedGlobal;
  c7_d_y = NULL;
  if (!chartInstance->c7_PC_value_not_empty) {
    sf_mex_assign(&c7_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    c7_d_u = c7_c_u;
    c7_e_y = NULL;
    sf_mex_assign(&c7_e_y, sf_mex_create("y", &c7_d_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c7_d_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c7_eml_mx), 15, "numerictype", 14, sf_mex_dup(c7_b_eml_mx), 15,
      "simulinkarray", 14, c7_e_y, 15, "fimathislocal", 3, TRUE));
  }

  sf_mex_setcell(c7_y, 1, c7_d_y);
  c7_c_hoistedGlobal = chartInstance->c7_is_active_c7_hdlcodercpu_eml;
  c7_e_u = c7_c_hoistedGlobal;
  c7_f_y = NULL;
  sf_mex_assign(&c7_f_y, sf_mex_create("y", &c7_e_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c7_y, 2, c7_f_y);
  sf_mex_assign(&c7_st, c7_y);
  return c7_st;
}

static void set_sim_state_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c7_st)
{
  const mxArray *c7_u;
  uint8_T *c7_addr_out;
  c7_addr_out = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c7_doneDoubleBufferReInit = TRUE;
  c7_u = sf_mex_dup(c7_st);
  *c7_addr_out = c7_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c7_u, 0)), "addr_out");
  chartInstance->c7_PC_value = c7_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c7_u, 1)), "PC_value");
  chartInstance->c7_is_active_c7_hdlcodercpu_eml = c7_g_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c7_u, 2)),
     "is_active_c7_hdlcodercpu_eml");
  sf_mex_destroy(&c7_u);
  c7_update_debugger_state_c7_hdlcodercpu_eml(chartInstance);
  sf_mex_destroy(&c7_st);
}

static void finalize_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&c7_eml_mx);
  sf_mex_destroy(&c7_b_eml_mx);
  sf_mex_destroy(&c7_c_eml_mx);
}

static void sf_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  uint8_T *c7_func;
  uint8_T *c7_addr_out;
  uint8_T *c7_addr_in;
  c7_addr_in = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c7_addr_out = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c7_func = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 6U, chartInstance->c7_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c7_func, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c7_addr_out, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c7_addr_in, 2U);
  chartInstance->c7_sfEvent = CALL_EVENT;
  c7_chartstep_c7_hdlcodercpu_eml(chartInstance);
  sf_debug_check_for_state_inconsistency(_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c7_chartstep_c7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  uint8_T c7_hoistedGlobal;
  uint8_T c7_b_hoistedGlobal;
  uint8_T c7_func;
  uint8_T c7_addr_in;
  uint32_T c7_debug_family_var_map[7];
  const mxArray *c7_hdl_fm = NULL;
  real_T c7_nargin = 2.0;
  real_T c7_nargout = 1.0;
  uint8_T c7_addr_out;
  const mxArray *c7_m0 = NULL;
  const mxArray *c7_m1 = NULL;
  const mxArray *c7_m2 = NULL;
  const mxArray *c7_m3 = NULL;
  const mxArray *c7_m4 = NULL;
  const mxArray *c7_m5 = NULL;
  const mxArray *c7_m6 = NULL;
  uint8_T c7_c_hoistedGlobal;
  uint8_T c7_varargin_1;
  uint8_T c7_b_varargin_1;
  const mxArray *c7_m7 = NULL;
  const mxArray *c7_m8 = NULL;
  const mxArray *c7_m9 = NULL;
  const mxArray *c7_m10 = NULL;
  uint8_T c7_var1;
  const mxArray *c7_m11 = NULL;
  const mxArray *c7_m12 = NULL;
  const mxArray *c7_m13 = NULL;
  const mxArray *c7_m14 = NULL;
  const mxArray *c7_m15 = NULL;
  const mxArray *c7_m16 = NULL;
  const mxArray *c7_m17 = NULL;
  const mxArray *c7_m18 = NULL;
  const mxArray *c7_m19 = NULL;
  const mxArray *c7_m20 = NULL;
  const mxArray *c7_m21 = NULL;
  const mxArray *c7_m22 = NULL;
  const mxArray *c7_m23 = NULL;
  const mxArray *c7_m24 = NULL;
  uint8_T c7_d_hoistedGlobal;
  uint8_T c7_a0;
  const mxArray *c7_m25 = NULL;
  const mxArray *c7_m26 = NULL;
  uint8_T c7_a;
  const mxArray *c7_m27 = NULL;
  const mxArray *c7_m28 = NULL;
  const mxArray *c7_m29 = NULL;
  const mxArray *c7_m30 = NULL;
  const mxArray *c7_m31 = NULL;
  const mxArray *c7_m32 = NULL;
  const mxArray *c7_m33 = NULL;
  const mxArray *c7_m34 = NULL;
  const mxArray *c7_m35 = NULL;
  const mxArray *c7_m36 = NULL;
  const mxArray *c7_m37 = NULL;
  const mxArray *c7_m38 = NULL;
  const mxArray *c7_m39 = NULL;
  const mxArray *c7_m40 = NULL;
  const mxArray *c7_m41 = NULL;
  const mxArray *c7_m42 = NULL;
  uint16_T c7_c;
  const mxArray *c7_m43 = NULL;
  const mxArray *c7_m44 = NULL;
  uint16_T c7_c_varargin_1;
  uint16_T c7_d_varargin_1;
  const mxArray *c7_m45 = NULL;
  const mxArray *c7_m46 = NULL;
  const mxArray *c7_m47 = NULL;
  const mxArray *c7_m48 = NULL;
  uint16_T c7_b_var1;
  uint8_T c7_hfi;
  const mxArray *c7_m49 = NULL;
  const mxArray *c7_m50 = NULL;
  const mxArray *c7_m51 = NULL;
  const mxArray *c7_m52 = NULL;
  const mxArray *c7_m53 = NULL;
  const mxArray *c7_m54 = NULL;
  const mxArray *c7_m55 = NULL;
  uint8_T *c7_b_addr_out;
  uint8_T *c7_b_func;
  uint8_T *c7_b_addr_in;
  c7_b_addr_in = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c7_b_addr_out = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c7_b_func = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 6U, chartInstance->c7_sfEvent);
  c7_hoistedGlobal = *c7_b_func;
  c7_b_hoistedGlobal = *c7_b_addr_in;
  c7_func = c7_hoistedGlobal;
  c7_addr_in = c7_b_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c7_debug_family_names,
    c7_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c7_hdl_fm, 0U, c7_f_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c7_nargin, 1U, c7_e_sf_marshallOut,
    c7_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c7_nargout, 2U, c7_e_sf_marshallOut,
    c7_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c7_func, 3U, c7_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c7_addr_in, 4U, c7_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c7_addr_out, 5U, c7_b_sf_marshallOut,
    c7_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&chartInstance->c7_PC_value, 6U,
    c7_sf_marshallOut, c7_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 8);
  c7_hdl_fm = c7_eml_mx;
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 16);
  if (CV_EML_IF(0, 0, !chartInstance->c7_PC_value_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 17);
    sf_mex_destroy(&c7_m0);
    sf_mex_destroy(&c7_m1);
    sf_mex_destroy(&c7_m2);
    sf_mex_destroy(&c7_m3);
    sf_mex_destroy(&c7_m4);
    sf_mex_destroy(&c7_m5);
    sf_mex_destroy(&c7_m6);
    chartInstance->c7_PC_value = 0U;
    chartInstance->c7_PC_value_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 20);
  c7_c_hoistedGlobal = chartInstance->c7_PC_value;
  c7_varargin_1 = c7_c_hoistedGlobal;
  c7_b_varargin_1 = c7_varargin_1;
  sf_mex_destroy(&c7_m7);
  sf_mex_destroy(&c7_m8);
  sf_mex_destroy(&c7_m9);
  sf_mex_destroy(&c7_m10);
  c7_var1 = c7_b_varargin_1;
  c7_addr_out = c7_var1;
  sf_mex_destroy(&c7_m11);
  sf_mex_destroy(&c7_m12);
  sf_mex_destroy(&c7_m13);
  sf_mex_destroy(&c7_m14);
  sf_mex_destroy(&c7_m15);
  sf_mex_destroy(&c7_m16);
  sf_mex_destroy(&c7_m17);
  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 22);
  switch (c7_uint8(chartInstance, c7_func)) {
   case 0U:
    CV_EML_SWITCH(0, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 25);
    sf_mex_destroy(&c7_m18);
    sf_mex_destroy(&c7_m19);
    sf_mex_destroy(&c7_m20);
    sf_mex_destroy(&c7_m21);
    sf_mex_destroy(&c7_m22);
    sf_mex_destroy(&c7_m23);
    sf_mex_destroy(&c7_m24);
    chartInstance->c7_PC_value = 0U;
    break;

   case 1U:
    CV_EML_SWITCH(0, 0, 2);
    _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 28);
    chartInstance->c7_PC_value = c7_addr_in;
    break;

   case 2U:
    CV_EML_SWITCH(0, 0, 3);
    _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, 31);
    c7_d_hoistedGlobal = chartInstance->c7_PC_value;
    c7_a0 = c7_d_hoistedGlobal;
    sf_mex_destroy(&c7_m25);
    sf_mex_destroy(&c7_m26);
    c7_a = c7_a0;
    sf_mex_destroy(&c7_m27);
    sf_mex_destroy(&c7_m28);
    sf_mex_destroy(&c7_m29);
    sf_mex_destroy(&c7_m30);
    sf_mex_destroy(&c7_m31);
    sf_mex_destroy(&c7_m32);
    sf_mex_destroy(&c7_m33);
    sf_mex_destroy(&c7_m34);
    sf_mex_destroy(&c7_m35);
    sf_mex_destroy(&c7_m36);
    sf_mex_destroy(&c7_m37);
    sf_mex_destroy(&c7_m38);
    sf_mex_destroy(&c7_m39);
    sf_mex_destroy(&c7_m40);
    sf_mex_destroy(&c7_m41);
    sf_mex_destroy(&c7_m42);
    c7_c = (uint16_T)((uint32_T)(uint16_T)((uint16_T)c7_a << 7) + 128U);
    sf_mex_destroy(&c7_m43);
    sf_mex_destroy(&c7_m44);
    c7_c_varargin_1 = c7_c;
    c7_d_varargin_1 = c7_c_varargin_1;
    sf_mex_destroy(&c7_m45);
    sf_mex_destroy(&c7_m46);
    sf_mex_destroy(&c7_m47);
    sf_mex_destroy(&c7_m48);
    c7_b_var1 = c7_d_varargin_1;
    c7_hfi = (uint8_T)(uint16_T)(c7_b_var1 >> 7);
    sf_mex_destroy(&c7_m49);
    sf_mex_destroy(&c7_m50);
    sf_mex_destroy(&c7_m51);
    sf_mex_destroy(&c7_m52);
    sf_mex_destroy(&c7_m53);
    sf_mex_destroy(&c7_m54);
    sf_mex_destroy(&c7_m55);
    chartInstance->c7_PC_value = c7_hfi;
    break;

   default:
    CV_EML_SWITCH(0, 0, 0);
    break;
  }

  _SFD_EML_CALL(0U, chartInstance->c7_sfEvent, -31);
  sf_debug_symbol_scope_pop();
  *c7_b_addr_out = c7_addr_out;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c7_sfEvent);
}

static void initSimStructsc7_hdlcodercpu_eml(SFc7_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c7_machineNumber, uint32_T
  c7_chartNumber)
{
}

static const mxArray *c7_sf_marshallOut(void *chartInstanceVoid, void *c7_inData)
{
  const mxArray *c7_mxArrayOutData;
  uint8_T c7_u;
  const mxArray *c7_y = NULL;
  uint8_T c7_b_u;
  const mxArray *c7_b_y = NULL;
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c7_u = *(uint8_T *)c7_inData;
    c7_y = NULL;
    if (!chartInstance->c7_PC_value_not_empty) {
      sf_mex_assign(&c7_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
    } else {
      c7_b_u = c7_u;
      c7_b_y = NULL;
      sf_mex_assign(&c7_b_y, sf_mex_create("y", &c7_b_u, 3, 0U, 0U, 0U, 0));
      sf_mex_assign(&c7_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
        sf_mex_dup(c7_eml_mx), 15, "numerictype", 14, sf_mex_dup(c7_b_eml_mx),
        15, "simulinkarray", 14, c7_b_y, 15, "fimathislocal", 3, TRUE));
    }

    sf_mex_assign(&c7_mxArrayOutData, c7_y);
  } else {
    sf_mex_assign(&c7_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c7_mxArrayOutData;
}

static uint8_T c7_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_b_PC_value, const char_T *c7_identifier)
{
  uint8_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_PC_value),
    &c7_thisId);
  sf_mex_destroy(&c7_b_PC_value);
  return c7_y;
}

static uint8_T c7_b_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  uint8_T c7_y;
  const mxArray *c7_mxFi = NULL;
  const mxArray *c7_mxInt = NULL;
  uint8_T c7_u0;
  if (mxIsEmpty(c7_u)) {
    chartInstance->c7_PC_value_not_empty = FALSE;
  } else {
    chartInstance->c7_PC_value_not_empty = TRUE;
    sf_mex_check_fi(c7_parentId, c7_u, 0, 0U, 0, c7_eml_mx, c7_b_eml_mx);
    sf_mex_assign(&c7_mxFi, sf_mex_dup(c7_u));
    sf_mex_assign(&c7_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
                   (c7_mxFi)));
    sf_mex_import(c7_parentId, sf_mex_dup(c7_mxInt), &c7_u0, 1, 3, 0U, 0, 0U, 0);
    sf_mex_destroy(&c7_mxFi);
    sf_mex_destroy(&c7_mxInt);
    c7_y = c7_u0;
  }

  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_b_PC_value;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  uint8_T c7_y;
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c7_b_PC_value = sf_mex_dup(c7_mxArrayInData);
    c7_identifier = c7_varName;
    c7_thisId.fIdentifier = c7_identifier;
    c7_thisId.fParent = NULL;
    c7_y = c7_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_PC_value),
      &c7_thisId);
    sf_mex_destroy(&c7_b_PC_value);
    *(uint8_T *)c7_outData = c7_y;
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_b_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData;
  uint8_T c7_u;
  const mxArray *c7_y = NULL;
  uint8_T c7_b_u;
  const mxArray *c7_b_y = NULL;
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c7_u = *(uint8_T *)c7_inData;
    c7_y = NULL;
    c7_b_u = c7_u;
    c7_b_y = NULL;
    sf_mex_assign(&c7_b_y, sf_mex_create("y", &c7_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c7_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c7_eml_mx), 15, "numerictype", 14, sf_mex_dup(c7_b_eml_mx), 15,
      "simulinkarray", 14, c7_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c7_mxArrayOutData, c7_y);
  } else {
    sf_mex_assign(&c7_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c7_mxArrayOutData;
}

static uint8_T c7_c_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_addr_out, const char_T *c7_identifier)
{
  uint8_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_addr_out),
    &c7_thisId);
  sf_mex_destroy(&c7_addr_out);
  return c7_y;
}

static uint8_T c7_d_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  uint8_T c7_y;
  const mxArray *c7_mxFi = NULL;
  const mxArray *c7_mxInt = NULL;
  uint8_T c7_u1;
  sf_mex_check_fi(c7_parentId, c7_u, 0, 0U, 0, c7_eml_mx, c7_b_eml_mx);
  sf_mex_assign(&c7_mxFi, sf_mex_dup(c7_u));
  sf_mex_assign(&c7_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c7_mxFi)));
  sf_mex_import(c7_parentId, sf_mex_dup(c7_mxInt), &c7_u1, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c7_mxFi);
  sf_mex_destroy(&c7_mxInt);
  c7_y = c7_u1;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_addr_out;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  uint8_T c7_y;
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c7_addr_out = sf_mex_dup(c7_mxArrayInData);
    c7_identifier = c7_varName;
    c7_thisId.fIdentifier = c7_identifier;
    c7_thisId.fParent = NULL;
    c7_y = c7_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_addr_out),
      &c7_thisId);
    sf_mex_destroy(&c7_addr_out);
    *(uint8_T *)c7_outData = c7_y;
  }

  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_c_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData;
  uint8_T c7_u;
  const mxArray *c7_y = NULL;
  uint8_T c7_b_u;
  const mxArray *c7_b_y = NULL;
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c7_u = *(uint8_T *)c7_inData;
    c7_y = NULL;
    c7_b_u = c7_u;
    c7_b_y = NULL;
    sf_mex_assign(&c7_b_y, sf_mex_create("y", &c7_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c7_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c7_eml_mx), 15, "numerictype", 14, sf_mex_dup(c7_b_eml_mx), 15,
      "simulinkarray", 14, c7_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c7_mxArrayOutData, c7_y);
  } else {
    sf_mex_assign(&c7_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c7_mxArrayOutData;
}

static const mxArray *c7_d_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData;
  uint8_T c7_u;
  const mxArray *c7_y = NULL;
  uint8_T c7_b_u;
  const mxArray *c7_b_y = NULL;
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c7_u = *(uint8_T *)c7_inData;
    c7_y = NULL;
    c7_b_u = c7_u;
    c7_b_y = NULL;
    sf_mex_assign(&c7_b_y, sf_mex_create("y", &c7_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c7_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c7_eml_mx), 15, "numerictype", 14, sf_mex_dup(c7_c_eml_mx), 15,
      "simulinkarray", 14, c7_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c7_mxArrayOutData, c7_y);
  } else {
    sf_mex_assign(&c7_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c7_mxArrayOutData;
}

static const mxArray *c7_e_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  real_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(real_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c7_mxArrayOutData, c7_y);
  return c7_mxArrayOutData;
}

static real_T c7_e_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  real_T c7_y;
  real_T c7_d0;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_d0, 1, 0, 0U, 0, 0U, 0);
  c7_y = c7_d0;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_nargout;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  real_T c7_y;
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c7_nargout = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_nargout), &c7_thisId);
  sf_mex_destroy(&c7_nargout);
  *(real_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_f_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  const mxArray *c7_u;
  const mxArray *c7_y = NULL;
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = sf_mex_dup(*(const mxArray **)c7_inData);
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_duplicatearraysafe(&c7_u));
  sf_mex_destroy(&c7_u);
  sf_mex_assign(&c7_mxArrayOutData, c7_y);
  return c7_mxArrayOutData;
}

const mxArray *sf_c7_hdlcodercpu_eml_get_eml_resolved_functions_info(void)
{
  const mxArray *c7_nameCaptureInfo;
  c7_ResolvedFunctionInfo c7_info[18];
  const mxArray *c7_m56 = NULL;
  int32_T c7_i0;
  c7_ResolvedFunctionInfo *c7_r0;
  c7_nameCaptureInfo = NULL;
  c7_nameCaptureInfo = NULL;
  c7_info_helper(c7_info);
  sf_mex_assign(&c7_m56, sf_mex_createstruct("nameCaptureInfo", 1, 18));
  for (c7_i0 = 0; c7_i0 < 18; c7_i0++) {
    c7_r0 = &c7_info[c7_i0];
    sf_mex_addfield(c7_m56, sf_mex_create("nameCaptureInfo", c7_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c7_r0->context)), "context", "nameCaptureInfo",
                    c7_i0);
    sf_mex_addfield(c7_m56, sf_mex_create("nameCaptureInfo", c7_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c7_r0->name)), "name", "nameCaptureInfo", c7_i0);
    sf_mex_addfield(c7_m56, sf_mex_create("nameCaptureInfo", c7_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c7_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c7_i0);
    sf_mex_addfield(c7_m56, sf_mex_create("nameCaptureInfo", c7_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c7_r0->resolved)), "resolved", "nameCaptureInfo",
                    c7_i0);
    sf_mex_addfield(c7_m56, sf_mex_create("nameCaptureInfo", &c7_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c7_i0);
    sf_mex_addfield(c7_m56, sf_mex_create("nameCaptureInfo", &c7_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c7_i0);
    sf_mex_addfield(c7_m56, sf_mex_create("nameCaptureInfo", &c7_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c7_i0);
    sf_mex_addfield(c7_m56, sf_mex_create("nameCaptureInfo", &c7_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c7_i0);
  }

  sf_mex_assign(&c7_nameCaptureInfo, c7_m56);
  return c7_nameCaptureInfo;
}

static void c7_info_helper(c7_ResolvedFunctionInfo c7_info[18])
{
  c7_info[0].context = "";
  c7_info[0].name = "fimath";
  c7_info[0].dominantType = "char";
  c7_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m";
  c7_info[0].fileTimeLo = 275520000U;
  c7_info[0].fileTimeHi = 30114375U;
  c7_info[0].mFileTimeLo = 0U;
  c7_info[0].mFileTimeHi = 0U;
  c7_info[1].context = "";
  c7_info[1].name = "fi_impl";
  c7_info[1].dominantType = "";
  c7_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m";
  c7_info[1].fileTimeLo = 275520000U;
  c7_info[1].fileTimeHi = 30114375U;
  c7_info[1].mFileTimeLo = 0U;
  c7_info[1].mFileTimeHi = 0U;
  c7_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c7_info[2].name = "isfi";
  c7_info[2].dominantType = "double";
  c7_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c7_info[2].fileTimeLo = 335520000U;
  c7_info[2].fileTimeHi = 30114375U;
  c7_info[2].mFileTimeLo = 0U;
  c7_info[2].mFileTimeHi = 0U;
  c7_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c7_info[3].name = "isnumerictype";
  c7_info[3].dominantType = "char";
  c7_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m";
  c7_info[3].fileTimeLo = 355520000U;
  c7_info[3].fileTimeHi = 30114375U;
  c7_info[3].mFileTimeLo = 0U;
  c7_info[3].mFileTimeHi = 0U;
  c7_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c7_info[4].name = "eml_fi_checkforerror";
  c7_info[4].dominantType = "embedded.numerictype";
  c7_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m";
  c7_info[4].fileTimeLo = 255520000U;
  c7_info[4].fileTimeHi = 30114375U;
  c7_info[4].mFileTimeLo = 0U;
  c7_info[4].mFileTimeHi = 0U;
  c7_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c7_info[5].name = "isfloat";
  c7_info[5].dominantType = "embedded.fi";
  c7_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m";
  c7_info[5].fileTimeLo = 875520000U;
  c7_info[5].fileTimeHi = 30114375U;
  c7_info[5].mFileTimeLo = 0U;
  c7_info[5].mFileTimeHi = 0U;
  c7_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m";
  c7_info[6].name = "get";
  c7_info[6].dominantType = "embedded.numerictype";
  c7_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m";
  c7_info[6].fileTimeLo = 4170487296U;
  c7_info[6].fileTimeHi = 30114374U;
  c7_info[6].mFileTimeLo = 0U;
  c7_info[6].mFileTimeHi = 0U;
  c7_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput";
  c7_info[7].name = "numerictype";
  c7_info[7].dominantType = "embedded.fi";
  c7_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m";
  c7_info[7].fileTimeLo = 995520000U;
  c7_info[7].fileTimeHi = 30114375U;
  c7_info[7].mFileTimeLo = 0U;
  c7_info[7].mFileTimeHi = 0U;
  c7_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput";
  c7_info[8].name = "fimath";
  c7_info[8].dominantType = "embedded.fi";
  c7_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m";
  c7_info[8].fileTimeLo = 775520000U;
  c7_info[8].fileTimeHi = 30114375U;
  c7_info[8].mFileTimeLo = 0U;
  c7_info[8].mFileTimeHi = 0U;
  c7_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c7_info[9].name = "eml_fi_checkforntype";
  c7_info[9].dominantType = "embedded.fi";
  c7_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m";
  c7_info[9].fileTimeLo = 255520000U;
  c7_info[9].fileTimeHi = 30114375U;
  c7_info[9].mFileTimeLo = 0U;
  c7_info[9].mFileTimeHi = 0U;
  c7_info[10].context = "";
  c7_info[10].name = "uint8";
  c7_info[10].dominantType = "embedded.fi";
  c7_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m";
  c7_info[10].fileTimeLo = 1115520000U;
  c7_info[10].fileTimeHi = 30114375U;
  c7_info[10].mFileTimeLo = 0U;
  c7_info[10].mFileTimeHi = 0U;
  c7_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m";
  c7_info[11].name = "eml_fi_getStoredIntValAsDType";
  c7_info[11].dominantType = "embedded.fi";
  c7_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getStoredIntValAsDType.m";
  c7_info[11].fileTimeLo = 655520000U;
  c7_info[11].fileTimeHi = 30114375U;
  c7_info[11].mFileTimeLo = 0U;
  c7_info[11].mFileTimeHi = 0U;
  c7_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getStoredIntValAsDType.m";
  c7_info[12].name = "isfixed";
  c7_info[12].dominantType = "embedded.fi";
  c7_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  c7_info[12].fileTimeLo = 875520000U;
  c7_info[12].fileTimeHi = 30114375U;
  c7_info[12].mFileTimeLo = 0U;
  c7_info[12].mFileTimeHi = 0U;
  c7_info[13].context = "";
  c7_info[13].name = "plus";
  c7_info[13].dominantType = "embedded.fi";
  c7_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c7_info[13].fileTimeLo = 995520000U;
  c7_info[13].fileTimeHi = 30114375U;
  c7_info[13].mFileTimeLo = 0U;
  c7_info[13].mFileTimeHi = 0U;
  c7_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c7_info[14].name = "eml_scalexp_compatible";
  c7_info[14].dominantType = "embedded.fi";
  c7_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c7_info[14].fileTimeLo = 3244844544U;
  c7_info[14].fileTimeHi = 30108086U;
  c7_info[14].mFileTimeLo = 0U;
  c7_info[14].mFileTimeHi = 0U;
  c7_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c7_info[15].name = "isscaledtype";
  c7_info[15].dominantType = "embedded.fi";
  c7_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m";
  c7_info[15].fileTimeLo = 895520000U;
  c7_info[15].fileTimeHi = 30114375U;
  c7_info[15].mFileTimeLo = 0U;
  c7_info[15].mFileTimeHi = 0U;
  c7_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c7_info[16].name = "get";
  c7_info[16].dominantType = "embedded.fimath";
  c7_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fimath/get.m";
  c7_info[16].fileTimeLo = 4190487296U;
  c7_info[16].fileTimeHi = 30114374U;
  c7_info[16].mFileTimeLo = 0U;
  c7_info[16].mFileTimeHi = 0U;
  c7_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c7_info[17].name = "strcmpi";
  c7_info[17].dominantType = "char";
  c7_info[17].resolved = "[IXMB]$matlabroot$/toolbox/matlab/strfun/strcmpi";
  c7_info[17].fileTimeLo = 0U;
  c7_info[17].fileTimeHi = 0U;
  c7_info[17].mFileTimeLo = 0U;
  c7_info[17].mFileTimeHi = 0U;
}

static uint8_T c7_uint8(SFc7_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c7_A)
{
  uint8_T c7_xfi;
  const mxArray *c7_m57 = NULL;
  const mxArray *c7_m58 = NULL;
  c7_xfi = c7_A;
  sf_mex_destroy(&c7_m57);
  sf_mex_destroy(&c7_m58);
  return c7_xfi;
}

static const mxArray *c7_g_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData = NULL;
  int32_T c7_u;
  const mxArray *c7_y = NULL;
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_u = *(int32_T *)c7_inData;
  c7_y = NULL;
  sf_mex_assign(&c7_y, sf_mex_create("y", &c7_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c7_mxArrayOutData, c7_y);
  return c7_mxArrayOutData;
}

static int32_T c7_f_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  int32_T c7_y;
  int32_T c7_i1;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_i1, 1, 6, 0U, 0, 0U, 0);
  c7_y = c7_i1;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void c7_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c7_mxArrayInData, const char_T *c7_varName, void *c7_outData)
{
  const mxArray *c7_b_sfEvent;
  const char_T *c7_identifier;
  emlrtMsgIdentifier c7_thisId;
  int32_T c7_y;
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c7_b_sfEvent = sf_mex_dup(c7_mxArrayInData);
  c7_identifier = c7_varName;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c7_b_sfEvent),
    &c7_thisId);
  sf_mex_destroy(&c7_b_sfEvent);
  *(int32_T *)c7_outData = c7_y;
  sf_mex_destroy(&c7_mxArrayInData);
}

static const mxArray *c7_h_sf_marshallOut(void *chartInstanceVoid, void
  *c7_inData)
{
  const mxArray *c7_mxArrayOutData;
  uint8_T c7_u;
  const mxArray *c7_y = NULL;
  uint8_T c7_b_u;
  const mxArray *c7_b_y = NULL;
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c7_mxArrayOutData = NULL;
  c7_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c7_u = *(uint8_T *)c7_inData;
    c7_y = NULL;
    c7_b_u = c7_u;
    c7_b_y = NULL;
    sf_mex_assign(&c7_b_y, sf_mex_create("y", &c7_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c7_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c7_eml_mx), 15, "numerictype", 14, sf_mex_dup(c7_c_eml_mx), 15,
      "simulinkarray", 14, c7_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c7_mxArrayOutData, c7_y);
  } else {
    sf_mex_assign(&c7_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c7_mxArrayOutData;
}

static uint8_T c7_g_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_b_is_active_c7_hdlcodercpu_eml, const char_T
  *c7_identifier)
{
  uint8_T c7_y;
  emlrtMsgIdentifier c7_thisId;
  c7_thisId.fIdentifier = c7_identifier;
  c7_thisId.fParent = NULL;
  c7_y = c7_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c7_b_is_active_c7_hdlcodercpu_eml), &c7_thisId);
  sf_mex_destroy(&c7_b_is_active_c7_hdlcodercpu_eml);
  return c7_y;
}

static uint8_T c7_h_emlrt_marshallIn(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c7_u, const emlrtMsgIdentifier *c7_parentId)
{
  uint8_T c7_y;
  uint8_T c7_u2;
  sf_mex_import(c7_parentId, sf_mex_dup(c7_u), &c7_u2, 1, 3, 0U, 0, 0U, 0);
  c7_y = c7_u2;
  sf_mex_destroy(&c7_u);
  return c7_y;
}

static void init_dsm_address_info(SFc7_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c7_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3954082246U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(924824749U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2931312351U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1914527512U);
}

mxArray *sf_c7_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(2662604010U);
    pr[1] = (double)(3254310039U);
    pr[2] = (double)(2126402155U);
    pr[3] = (double)(1541392969U);
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

static const mxArray *sf_get_sim_state_info_c7_hdlcodercpu_eml(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"addr_out\",},{M[4],M[0],T\"PC_value\",S'l','i','p'{{M1x2[371 379],M[0],}}},{M[8],M[0],T\"is_active_c7_hdlcodercpu_eml\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c7_hdlcodercpu_eml_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
    chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_hdlcodercpu_emlMachineNumber_,
           7,
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
          _SFD_SET_DATA_PROPS(1,2,0,1,"addr_out");
          _SFD_SET_DATA_PROPS(2,1,1,0,"addr_in");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,740);
        _SFD_CV_INIT_EML_IF(0,0,381,402,-1,445);

        {
          static int caseStart[] = { -1, 515, 587, 651 };

          static int caseExprEnd[] = { 8, 521, 593, 657 };

          _SFD_CV_INIT_EML_SWITCH(0,0,490,509,739,4,&(caseStart[0]),
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
          (MexFcnForType)c7_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,1,0,8,0,1,0,0,
          (MexFcnForType)c7_b_sf_marshallOut,(MexInFcnForType)c7_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,1,0,8,0,1,0,0,
          (MexFcnForType)c7_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          uint8_T *c7_func;
          uint8_T *c7_addr_out;
          uint8_T *c7_addr_in;
          c7_addr_in = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c7_addr_out = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c7_func = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c7_func);
          _SFD_SET_DATA_VALUE_PTR(1U, c7_addr_out);
          _SFD_SET_DATA_VALUE_PTR(2U, c7_addr_in);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_hdlcodercpu_emlMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c7_hdlcodercpu_eml(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc7_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c7_hdlcodercpu_eml((SFc7_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
  initialize_c7_hdlcodercpu_eml((SFc7_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c7_hdlcodercpu_eml(void *chartInstanceVar)
{
  enable_c7_hdlcodercpu_eml((SFc7_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c7_hdlcodercpu_eml(void *chartInstanceVar)
{
  disable_c7_hdlcodercpu_eml((SFc7_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c7_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_c7_hdlcodercpu_eml((SFc7_hdlcodercpu_emlInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c7_hdlcodercpu_eml(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c7_hdlcodercpu_eml
    ((SFc7_hdlcodercpu_emlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c7_hdlcodercpu_eml();/* state var info */
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

extern void sf_internal_set_sim_state_c7_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c7_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c7_hdlcodercpu_eml((SFc7_hdlcodercpu_emlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c7_hdlcodercpu_eml(SimStruct* S)
{
  return sf_internal_get_sim_state_c7_hdlcodercpu_eml(S);
}

static void sf_opaque_set_sim_state_c7_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c7_hdlcodercpu_eml(S, st);
}

static void sf_opaque_terminate_c7_hdlcodercpu_eml(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc7_hdlcodercpu_emlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c7_hdlcodercpu_eml((SFc7_hdlcodercpu_emlInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc7_hdlcodercpu_eml((SFc7_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c7_hdlcodercpu_eml(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c7_hdlcodercpu_eml((SFc7_hdlcodercpu_emlInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c7_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"hdlcodercpu_eml","hdlcodercpu_eml",7);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml","hdlcodercpu_eml",7,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml",
      "hdlcodercpu_eml",7,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",
        7,2);
      sf_mark_chart_reusable_outputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",7,1);
    }

    sf_set_rtw_dwork_info(S,"hdlcodercpu_eml","hdlcodercpu_eml",7);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1221170854U));
  ssSetChecksum1(S,(2983149449U));
  ssSetChecksum2(S,(4026934466U));
  ssSetChecksum3(S,(1364295896U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c7_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "hdlcodercpu_eml", "hdlcodercpu_eml",7);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c7_hdlcodercpu_eml(SimStruct *S)
{
  SFc7_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc7_hdlcodercpu_emlInstanceStruct *)malloc(sizeof
    (SFc7_hdlcodercpu_emlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc7_hdlcodercpu_emlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c7_hdlcodercpu_eml;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c7_hdlcodercpu_eml;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c7_hdlcodercpu_eml;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c7_hdlcodercpu_eml;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c7_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c7_hdlcodercpu_eml;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c7_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c7_hdlcodercpu_eml;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c7_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlStart = mdlStart_c7_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c7_hdlcodercpu_eml;
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

void c7_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c7_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c7_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c7_hdlcodercpu_eml(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c7_hdlcodercpu_eml_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
