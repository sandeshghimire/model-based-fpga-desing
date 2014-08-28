/* Include files */

#include <stddef.h>
#include "blas.h"
#include "hdlcodercpu_eml_sfun.h"
#include "c4_hdlcodercpu_eml.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "hdlcodercpu_eml_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const mxArray *c4_eml_mx;
static const char * c4_debug_family_names[14] = { "hdl_fm", "carry", "overflow",
  "sign_bit", "is_zero", "zero_ufix1", "nargin", "nargout", "in_flags", "func",
  "alu_in", "AC", "alu_out", "out_flags" };

static const mxArray *c4_b_eml_mx;
static const mxArray *c4_c_eml_mx;
static const mxArray *c4_d_eml_mx;
static const mxArray *c4_e_eml_mx;
static const char * c4_b_debug_family_names[14] = { "hdl_fm", "temp_u1",
  "temp_u2", "temp_sum", "sign_bit", "overflow_int", "nargin", "nargout", "u1",
  "u2", "c_in", "sum", "carry", "overflow" };

static const mxArray *c4_f_eml_mx;
static const char * c4_c_debug_family_names[8] = { "nargin", "nargout", "u1",
  "u2", "b_in", "diff", "carry", "overflow" };

/* Function Declarations */
static void initialize_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initialize_params_c4_hdlcodercpu_eml
  (SFc4_hdlcodercpu_emlInstanceStruct *chartInstance);
static void enable_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void disable_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c4_update_debugger_state_c4_hdlcodercpu_eml
  (SFc4_hdlcodercpu_emlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c4_hdlcodercpu_eml
  (SFc4_hdlcodercpu_emlInstanceStruct *chartInstance);
static void set_sim_state_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c4_st);
static void finalize_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void sf_gateway_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c4_chartstep_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initSimStructsc4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static uint8_T c4_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int8_T c4_b_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_alu_out, const char_T *c4_identifier);
static int8_T c4_c_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static real_T c4_d_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static uint8_T c4_e_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_g_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static uint8_T c4_f_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_is_zero, const char_T *c4_identifier);
static uint8_T c4_g_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_h_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static uint8_T c4_h_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_i_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int8_T c4_i_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_j_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int16_T c4_j_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_info_helper(const mxArray **c4_info);
static const mxArray *c4_emlrt_marshallOut(const char * c4_u);
static const mxArray *c4_b_emlrt_marshallOut(const uint32_T c4_u);
static void c4_b_info_helper(const mxArray **c4_info);
static void c4_c_info_helper(const mxArray **c4_info);
static void c4_eml_fi_checkforconst(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static uint8_T c4_uint8(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c4_A);
static void c4_b_eml_fi_checkforconst(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static uint8_T c4_bitcmp(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c4_a);
static int8_T c4_b_bitcmp(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_a);
static void c4_sub_w_borrow(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_u1, int8_T c4_u2, uint8_T c4_b_in, int8_T *c4_diff, uint8_T
  *c4_carry, uint8_T *c4_overflow);
static void c4_sum_w_carry(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_u1, int8_T c4_u2, uint8_T c4_c_in, int8_T *c4_sum, uint8_T *c4_carry,
  uint8_T *c4_overflow);
static uint16_T c4_bitconcat(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c4_varargin_1, int8_T c4_varargin_2);
static void c4_c_eml_fi_checkforconst(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static int16_T c4_plus(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int16_T c4_a0, int16_T c4_b0);
static int16_T c4_b_plus(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int16_T c4_a0, uint8_T c4_b0);
static int8_T c4_bitand(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_a, int8_T c4_b);
static boolean_T c4_all(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_x);
static const mxArray *c4_k_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_k_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_l_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_m_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static uint8_T c4_l_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_out_flags, const char_T *c4_identifier);
static uint8_T c4_m_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void init_dsm_address_info(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c4_is_active_c4_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c4_f_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 10U, 15, "WordLength", 6, 9.0, 15, "FractionLength", 6,
    0.0, 15, "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6,
    0.0), true);
  sf_mex_assign(&c4_e_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 1.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c4_d_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 3.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c4_c_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 10U, 15, "WordLength", 6, 8.0, 15, "FractionLength", 6,
    0.0, 15, "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6,
    0.0), true);
  sf_mex_assign(&c4_b_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 4.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c4_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "fimath", 1U, 42U, 15, "RoundMode", 15, "floor", 15, "RoundingMethod", 15,
    "Floor", 15, "OverflowMode", 15, "wrap", 15, "OverflowAction", 15, "Wrap",
    15, "ProductMode", 15, "FullPrecision", 15, "ProductWordLength", 6, 32.0, 15,
    "MaxProductWordLength", 6, 65535.0, 15, "ProductFractionLength", 6, 30.0, 15,
    "ProductFixedExponent", 6, -30.0, 15, "ProductSlope", 6,
    9.3132257461547852E-10, 15, "ProductSlopeAdjustmentFactor", 6, 1.0, 15,
    "ProductBias", 6, 0.0, 15, "SumMode", 15, "FullPrecision", 15,
    "SumWordLength", 6, 32.0, 15, "MaxSumWordLength", 6, 65535.0, 15,
    "SumFractionLength", 6, 30.0, 15, "SumFixedExponent", 6, -30.0, 15,
    "SumSlope", 6, 9.3132257461547852E-10, 15, "SumSlopeAdjustmentFactor", 6,
    1.0, 15, "SumBias", 6, 0.0, 15, "CastBeforeSum", 3, true), true);
}

static void initialize_params_c4_hdlcodercpu_eml
  (SFc4_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c4_update_debugger_state_c4_hdlcodercpu_eml
  (SFc4_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c4_hdlcodercpu_eml
  (SFc4_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  int8_T c4_hoistedGlobal;
  int8_T c4_u;
  const mxArray *c4_b_y = NULL;
  int8_T c4_b_u;
  const mxArray *c4_c_y = NULL;
  uint8_T c4_b_hoistedGlobal;
  uint8_T c4_c_u;
  const mxArray *c4_d_y = NULL;
  uint8_T c4_d_u;
  const mxArray *c4_e_y = NULL;
  uint8_T c4_c_hoistedGlobal;
  uint8_T c4_e_u;
  const mxArray *c4_f_y = NULL;
  int8_T *c4_alu_out;
  uint8_T *c4_out_flags;
  c4_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c4_alu_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellmatrix(3, 1), false);
  c4_hoistedGlobal = *c4_alu_out;
  c4_u = c4_hoistedGlobal;
  c4_b_y = NULL;
  c4_b_u = c4_u;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_b_u, 2, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_b_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_c_eml_mx), 15,
    "simulinkarray", 14, c4_c_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_b_hoistedGlobal = *c4_out_flags;
  c4_c_u = c4_b_hoistedGlobal;
  c4_d_y = NULL;
  c4_d_u = c4_c_u;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_d_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_b_eml_mx), 15,
    "simulinkarray", 14, c4_e_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c4_y, 1, c4_d_y);
  c4_c_hoistedGlobal = chartInstance->c4_is_active_c4_hdlcodercpu_eml;
  c4_e_u = c4_c_hoistedGlobal;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 2, c4_f_y);
  sf_mex_assign(&c4_st, c4_y, false);
  return c4_st;
}

static void set_sim_state_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c4_st)
{
  const mxArray *c4_u;
  int8_T *c4_alu_out;
  uint8_T *c4_out_flags;
  c4_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c4_alu_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c4_doneDoubleBufferReInit = true;
  c4_u = sf_mex_dup(c4_st);
  *c4_alu_out = c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c4_u, 0)), "alu_out");
  *c4_out_flags = c4_l_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c4_u, 1)), "out_flags");
  chartInstance->c4_is_active_c4_hdlcodercpu_eml = c4_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 2)),
     "is_active_c4_hdlcodercpu_eml");
  sf_mex_destroy(&c4_u);
  c4_update_debugger_state_c4_hdlcodercpu_eml(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
  sf_mex_destroy(&c4_eml_mx);
  sf_mex_destroy(&c4_b_eml_mx);
  sf_mex_destroy(&c4_c_eml_mx);
  sf_mex_destroy(&c4_d_eml_mx);
  sf_mex_destroy(&c4_e_eml_mx);
  sf_mex_destroy(&c4_f_eml_mx);
}

static void sf_gateway_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  uint8_T *c4_in_flags;
  uint8_T *c4_func;
  int8_T *c4_alu_in;
  int8_T *c4_AC;
  int8_T *c4_alu_out;
  uint8_T *c4_out_flags;
  c4_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c4_alu_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c4_AC = (int8_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c4_alu_in = (int8_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c4_func = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c4_in_flags = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c4_in_flags, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c4_func, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c4_alu_in, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*c4_AC, 3U);
  chartInstance->c4_sfEvent = CALL_EVENT;
  c4_chartstep_c4_hdlcodercpu_eml(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK((real_T)*c4_alu_out, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)*c4_out_flags, 5U);
}

static void c4_chartstep_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  uint8_T c4_hoistedGlobal;
  uint8_T c4_b_hoistedGlobal;
  int8_T c4_c_hoistedGlobal;
  int8_T c4_d_hoistedGlobal;
  uint8_T c4_in_flags;
  uint8_T c4_func;
  int8_T c4_alu_in;
  int8_T c4_AC;
  uint32_T c4_debug_family_var_map[14];
  const mxArray *c4_hdl_fm = NULL;
  uint8_T c4_carry;
  uint8_T c4_overflow;
  uint8_T c4_sign_bit;
  uint8_T c4_is_zero;
  uint8_T c4_zero_ufix1;
  real_T c4_nargin = 4.0;
  real_T c4_nargout = 2.0;
  int8_T c4_alu_out;
  uint8_T c4_out_flags;
  uint8_T c4_a;
  uint8_T c4_a1;
  uint8_T c4_slice_temp;
  uint8_T c4_b_a;
  uint8_T c4_b_a1;
  uint8_T c4_b_slice_temp;
  int8_T c4_varargin_1;
  int8_T c4_b_varargin_1;
  int8_T c4_var1;
  const mxArray *c4_T = NULL;
  const mxArray *c4_F = NULL;
  const mxArray *c4_val = NULL;
  const mxArray *c4_isautoscaled = NULL;
  const mxArray *c4_pvpairsetdata = NULL;
  const mxArray *c4_isfimathlocal = NULL;
  uint8_T c4_b_overflow;
  uint8_T c4_b_carry;
  int8_T c4_b_alu_out;
  uint8_T c4_c_overflow;
  uint8_T c4_c_carry;
  int8_T c4_c_alu_out;
  int8_T c4_c_varargin_1;
  int8_T c4_d_varargin_1;
  int8_T c4_b_var1;
  const mxArray *c4_b_T = NULL;
  const mxArray *c4_b_F = NULL;
  const mxArray *c4_b_val = NULL;
  const mxArray *c4_b_isautoscaled = NULL;
  const mxArray *c4_b_pvpairsetdata = NULL;
  const mxArray *c4_b_isfimathlocal = NULL;
  int8_T c4_e_varargin_1;
  int8_T c4_f_varargin_1;
  int8_T c4_c_var1;
  const mxArray *c4_c_T = NULL;
  const mxArray *c4_c_F = NULL;
  const mxArray *c4_c_val = NULL;
  const mxArray *c4_c_isautoscaled = NULL;
  const mxArray *c4_c_pvpairsetdata = NULL;
  const mxArray *c4_c_isfimathlocal = NULL;
  const mxArray *c4_d_T = NULL;
  const mxArray *c4_d_F = NULL;
  const mxArray *c4_d_val = NULL;
  const mxArray *c4_unusedU2 = NULL;
  const mxArray *c4_unusedU3 = NULL;
  const mxArray *c4_d_isfimathlocal = NULL;
  int8_T c4_c_a;
  const mxArray *c4_e_T = NULL;
  const mxArray *c4_e_F = NULL;
  const mxArray *c4_e_val = NULL;
  const mxArray *c4_b_unusedU2 = NULL;
  const mxArray *c4_b_unusedU3 = NULL;
  const mxArray *c4_e_isfimathlocal = NULL;
  uint8_T c4_c_slice_temp;
  uint8_T c4_g_varargin_1;
  uint8_T c4_h_varargin_1;
  uint8_T c4_d_var1;
  const mxArray *c4_f_T = NULL;
  const mxArray *c4_f_F = NULL;
  const mxArray *c4_f_val = NULL;
  const mxArray *c4_d_isautoscaled = NULL;
  const mxArray *c4_d_pvpairsetdata = NULL;
  const mxArray *c4_f_isfimathlocal = NULL;
  uint8_T c4_i_varargin_1;
  uint8_T c4_varargin_2;
  uint8_T c4_j_varargin_1;
  uint8_T c4_b_varargin_2;
  uint8_T c4_varargout_2;
  uint8_T c4_c;
  uint8_T c4_k_varargin_1;
  uint8_T c4_c_varargin_2;
  uint8_T c4_l_varargin_1;
  uint8_T c4_d_varargin_2;
  uint8_T c4_b_varargout_2;
  uint8_T c4_b_c;
  uint8_T c4_m_varargin_1;
  uint8_T c4_e_varargin_2;
  uint8_T c4_n_varargin_1;
  uint8_T c4_f_varargin_2;
  uint8_T c4_c_varargout_2;
  uint8_T *c4_b_in_flags;
  uint8_T *c4_b_func;
  int8_T *c4_b_alu_in;
  int8_T *c4_b_AC;
  int8_T *c4_d_alu_out;
  uint8_T *c4_b_out_flags;
  c4_b_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c4_d_alu_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c4_b_AC = (int8_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c4_b_alu_in = (int8_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c4_b_func = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c4_b_in_flags = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  c4_hoistedGlobal = *c4_b_in_flags;
  c4_b_hoistedGlobal = *c4_b_func;
  c4_c_hoistedGlobal = *c4_b_alu_in;
  c4_d_hoistedGlobal = *c4_b_AC;
  c4_in_flags = c4_hoistedGlobal;
  c4_func = c4_b_hoistedGlobal;
  c4_alu_in = c4_c_hoistedGlobal;
  c4_AC = c4_d_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 14U, 14U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_hdl_fm, 0U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_carry, 1U, c4_h_sf_marshallOut,
    c4_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_overflow, 2U, c4_h_sf_marshallOut,
    c4_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_sign_bit, 3U, c4_f_sf_marshallOut,
    c4_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_is_zero, 4U, c4_g_sf_marshallOut,
    c4_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_zero_ufix1, 5U, c4_f_sf_marshallOut,
    c4_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 6U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 7U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_in_flags, 8U, c4_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_func, 9U, c4_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_alu_in, 10U, c4_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_AC, 11U, c4_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_alu_out, 12U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_out_flags, 13U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 8);
  c4_hdl_fm = c4_eml_mx;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 16);
  c4_a = c4_in_flags;
  c4_carry = 0U;
  c4_a1 = c4_a;
  c4_slice_temp = (uint8_T)((uint8_T)((uint32_T)c4_a1 >> 3) & 1U);
  c4_carry = c4_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 19);
  c4_b_a = c4_in_flags;
  c4_overflow = 0U;
  c4_b_a1 = c4_b_a;
  c4_b_slice_temp = (uint8_T)((uint8_T)((uint32_T)c4_b_a1 >> 1) & 1U);
  c4_overflow = c4_b_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 22);
  c4_varargin_1 = c4_AC;
  c4_b_varargin_1 = c4_varargin_1;
  c4_eml_fi_checkforconst(chartInstance);
  c4_var1 = c4_b_varargin_1;
  c4_alu_out = c4_var1;
  sf_mex_destroy(&c4_T);
  sf_mex_destroy(&c4_F);
  sf_mex_destroy(&c4_val);
  sf_mex_destroy(&c4_isautoscaled);
  sf_mex_destroy(&c4_pvpairsetdata);
  sf_mex_destroy(&c4_isfimathlocal);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 26);
  switch (c4_uint8(chartInstance, c4_func)) {
   case 0U:
    CV_EML_SWITCH(0, 1, 0, 1);
    break;

   case 1U:
    CV_EML_SWITCH(0, 1, 0, 2);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 31);
    c4_alu_out = c4_bitand(chartInstance, c4_alu_in, c4_AC);
    break;

   case 2U:
    CV_EML_SWITCH(0, 1, 0, 3);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 34);
    c4_sum_w_carry(chartInstance, c4_AC, c4_alu_in, c4_carry, &c4_b_alu_out,
                   &c4_b_carry, &c4_b_overflow);
    c4_alu_out = c4_b_alu_out;
    c4_carry = c4_b_carry;
    c4_overflow = c4_b_overflow;
    break;

   case 3U:
    CV_EML_SWITCH(0, 1, 0, 4);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 37);
    c4_sub_w_borrow(chartInstance, c4_AC, c4_alu_in, c4_carry, &c4_c_alu_out,
                    &c4_c_carry, &c4_c_overflow);
    c4_alu_out = c4_c_alu_out;
    c4_carry = c4_c_carry;
    c4_overflow = c4_c_overflow;
    break;

   case 4U:
    CV_EML_SWITCH(0, 1, 0, 5);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 40);
    c4_c_varargin_1 = c4_b_bitcmp(chartInstance, c4_AC);
    c4_d_varargin_1 = c4_c_varargin_1;
    c4_eml_fi_checkforconst(chartInstance);
    c4_b_var1 = c4_d_varargin_1;
    c4_alu_out = c4_b_var1;
    sf_mex_destroy(&c4_b_T);
    sf_mex_destroy(&c4_b_F);
    sf_mex_destroy(&c4_b_val);
    sf_mex_destroy(&c4_b_isautoscaled);
    sf_mex_destroy(&c4_b_pvpairsetdata);
    sf_mex_destroy(&c4_b_isfimathlocal);
    break;

   case 5U:
    CV_EML_SWITCH(0, 1, 0, 6);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 43);
    c4_carry = c4_bitcmp(chartInstance, c4_carry);
    break;

   case 6U:
    CV_EML_SWITCH(0, 1, 0, 7);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 46);
    c4_e_varargin_1 = c4_alu_in;
    c4_f_varargin_1 = c4_e_varargin_1;
    c4_eml_fi_checkforconst(chartInstance);
    c4_c_var1 = c4_f_varargin_1;
    c4_alu_out = c4_c_var1;
    sf_mex_destroy(&c4_c_T);
    sf_mex_destroy(&c4_c_F);
    sf_mex_destroy(&c4_c_val);
    sf_mex_destroy(&c4_c_isautoscaled);
    sf_mex_destroy(&c4_c_pvpairsetdata);
    sf_mex_destroy(&c4_c_isfimathlocal);
    break;

   case 7U:
    CV_EML_SWITCH(0, 1, 0, 8);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 49);
    c4_b_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c4_d_T);
    sf_mex_destroy(&c4_d_F);
    sf_mex_destroy(&c4_d_val);
    sf_mex_destroy(&c4_unusedU2);
    sf_mex_destroy(&c4_unusedU3);
    sf_mex_destroy(&c4_d_isfimathlocal);
    c4_carry = 0U;
    break;

   default:
    CV_EML_SWITCH(0, 1, 0, 0);
    break;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 53);
  c4_c_a = c4_alu_out;
  sf_mex_destroy(&c4_e_T);
  sf_mex_destroy(&c4_e_F);
  sf_mex_destroy(&c4_e_val);
  sf_mex_destroy(&c4_b_unusedU2);
  sf_mex_destroy(&c4_b_unusedU3);
  sf_mex_destroy(&c4_e_isfimathlocal);
  c4_sign_bit = 0U;
  c4_c_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
    (uint8_T)c4_c_a >> 7) & 1) & 1U);
  c4_sign_bit = c4_c_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 56);
  c4_is_zero = (uint8_T)!c4_all(chartInstance, c4_alu_out);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 57);
  c4_g_varargin_1 = c4_is_zero;
  c4_h_varargin_1 = c4_g_varargin_1;
  c4_b_eml_fi_checkforconst(chartInstance);
  c4_d_var1 = c4_h_varargin_1;
  c4_zero_ufix1 = (uint8_T)(c4_d_var1 & 1U);
  sf_mex_destroy(&c4_f_T);
  sf_mex_destroy(&c4_f_F);
  sf_mex_destroy(&c4_f_val);
  sf_mex_destroy(&c4_d_isautoscaled);
  sf_mex_destroy(&c4_d_pvpairsetdata);
  sf_mex_destroy(&c4_f_isfimathlocal);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 60);
  c4_i_varargin_1 = c4_carry;
  c4_varargin_2 = c4_sign_bit;
  c4_j_varargin_1 = c4_i_varargin_1;
  c4_b_varargin_2 = c4_varargin_2;
  c4_varargout_2 = c4_b_varargin_2;
  c4_c = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)(c4_j_varargin_1 & 3U)
    << 1) & 3U) | (uint8_T)(c4_varargout_2 & 3U)) & 3U);
  c4_k_varargin_1 = c4_c;
  c4_c_varargin_2 = c4_overflow;
  c4_l_varargin_1 = c4_k_varargin_1;
  c4_d_varargin_2 = c4_c_varargin_2;
  c4_b_varargout_2 = c4_d_varargin_2;
  c4_b_c = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)(c4_l_varargin_1 &
    7U) << 1) & 7U) | (uint8_T)(c4_b_varargout_2 & 7U)) & 7U);
  c4_m_varargin_1 = c4_b_c;
  c4_e_varargin_2 = c4_zero_ufix1;
  c4_n_varargin_1 = c4_m_varargin_1;
  c4_f_varargin_2 = c4_e_varargin_2;
  c4_c_varargout_2 = c4_f_varargin_2;
  c4_out_flags = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)
    (c4_n_varargin_1 & 15U) << 1) & 15U) | (uint8_T)(c4_c_varargout_2 & 15U)) &
    15U);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -60);
  _SFD_SYMBOL_SCOPE_POP();
  *c4_d_alu_out = c4_alu_out;
  *c4_b_out_flags = c4_out_flags;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
}

static void initSimStructsc4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber)
{
  (void)c4_machineNumber;
  (void)c4_chartNumber;
  (void)c4_instanceNumber;
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  uint8_T c4_u;
  const mxArray *c4_y = NULL;
  uint8_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c4_u = *(uint8_T *)c4_inData;
    c4_y = NULL;
    c4_b_u = c4_u;
    c4_b_y = NULL;
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c4_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_b_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c4_mxArrayOutData;
}

static uint8_T c4_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  const mxArray *c4_mxFi = NULL;
  const mxArray *c4_mxInt = NULL;
  uint8_T c4_u0;
  (void)chartInstance;
  sf_mex_check_fi(c4_parentId, c4_u, false, 0U, NULL, c4_eml_mx, c4_b_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u), false);
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)), false);
  sf_mex_import(c4_parentId, sf_mex_dup(c4_mxInt), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c4_mxFi);
  sf_mex_destroy(&c4_mxInt);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_out_flags;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  uint8_T c4_y;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c4_out_flags = sf_mex_dup(c4_mxArrayInData);
    c4_identifier = c4_varName;
    c4_thisId.fIdentifier = c4_identifier;
    c4_thisId.fParent = NULL;
    c4_y = c4_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_out_flags),
      &c4_thisId);
    sf_mex_destroy(&c4_out_flags);
    *(uint8_T *)c4_outData = c4_y;
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  int8_T c4_u;
  const mxArray *c4_y = NULL;
  int8_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c4_u = *(int8_T *)c4_inData;
    c4_y = NULL;
    c4_b_u = c4_u;
    c4_b_y = NULL;
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 2, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c4_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_c_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c4_mxArrayOutData;
}

static int8_T c4_b_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_alu_out, const char_T *c4_identifier)
{
  int8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_alu_out), &c4_thisId);
  sf_mex_destroy(&c4_alu_out);
  return c4_y;
}

static int8_T c4_c_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int8_T c4_y;
  const mxArray *c4_mxFi = NULL;
  const mxArray *c4_mxInt = NULL;
  int8_T c4_i0;
  (void)chartInstance;
  sf_mex_check_fi(c4_parentId, c4_u, false, 0U, NULL, c4_eml_mx, c4_c_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u), false);
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)), false);
  sf_mex_import(c4_parentId, sf_mex_dup(c4_mxInt), &c4_i0, 1, 2, 0U, 0, 0U, 0);
  sf_mex_destroy(&c4_mxFi);
  sf_mex_destroy(&c4_mxInt);
  c4_y = c4_i0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_alu_out;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int8_T c4_y;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c4_alu_out = sf_mex_dup(c4_mxArrayInData);
    c4_identifier = c4_varName;
    c4_thisId.fIdentifier = c4_identifier;
    c4_thisId.fParent = NULL;
    c4_y = c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_alu_out),
      &c4_thisId);
    sf_mex_destroy(&c4_alu_out);
    *(int8_T *)c4_outData = c4_y;
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  int8_T c4_u;
  const mxArray *c4_y = NULL;
  int8_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c4_u = *(int8_T *)c4_inData;
    c4_y = NULL;
    c4_b_u = c4_u;
    c4_b_y = NULL;
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 2, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c4_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_c_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c4_mxArrayOutData;
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  uint8_T c4_u;
  const mxArray *c4_y = NULL;
  uint8_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c4_u = *(uint8_T *)c4_inData;
    c4_y = NULL;
    c4_b_u = c4_u;
    c4_b_y = NULL;
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c4_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_d_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c4_mxArrayOutData;
}

static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static real_T c4_d_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_d0, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d0;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_nargout;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_nargout = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_nargout), &c4_thisId);
  sf_mex_destroy(&c4_nargout);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  uint8_T c4_u;
  const mxArray *c4_y = NULL;
  uint8_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c4_u = *(uint8_T *)c4_inData;
    c4_y = NULL;
    c4_b_u = c4_u;
    c4_b_y = NULL;
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c4_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_e_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c4_mxArrayOutData;
}

static uint8_T c4_e_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  const mxArray *c4_mxFi = NULL;
  const mxArray *c4_mxInt = NULL;
  uint8_T c4_u1;
  (void)chartInstance;
  sf_mex_check_fi(c4_parentId, c4_u, false, 0U, NULL, c4_eml_mx, c4_e_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u), false);
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)), false);
  sf_mex_import(c4_parentId, sf_mex_dup(c4_mxInt), &c4_u1, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c4_mxFi);
  sf_mex_destroy(&c4_mxInt);
  c4_y = c4_u1;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_zero_ufix1;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  uint8_T c4_y;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c4_zero_ufix1 = sf_mex_dup(c4_mxArrayInData);
    c4_identifier = c4_varName;
    c4_thisId.fIdentifier = c4_identifier;
    c4_thisId.fParent = NULL;
    c4_y = c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_zero_ufix1),
      &c4_thisId);
    sf_mex_destroy(&c4_zero_ufix1);
    *(uint8_T *)c4_outData = c4_y;
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_g_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  uint8_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(uint8_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static uint8_T c4_f_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_is_zero, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_is_zero), &c4_thisId);
  sf_mex_destroy(&c4_is_zero);
  return c4_y;
}

static uint8_T c4_g_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u2;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_u2, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u2;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_is_zero;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  uint8_T c4_y;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_is_zero = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_is_zero), &c4_thisId);
  sf_mex_destroy(&c4_is_zero);
  *(uint8_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_h_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  uint8_T c4_u;
  const mxArray *c4_y = NULL;
  uint8_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c4_u = *(uint8_T *)c4_inData;
    c4_y = NULL;
    c4_b_u = c4_u;
    c4_b_y = NULL;
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c4_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_e_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c4_mxArrayOutData;
}

static uint8_T c4_h_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  const mxArray *c4_mxFi = NULL;
  const mxArray *c4_mxInt = NULL;
  uint8_T c4_u3;
  (void)chartInstance;
  sf_mex_check_fi(c4_parentId, c4_u, false, 0U, NULL, c4_eml_mx, c4_e_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u), false);
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)), false);
  sf_mex_import(c4_parentId, sf_mex_dup(c4_mxInt), &c4_u3, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c4_mxFi);
  sf_mex_destroy(&c4_mxInt);
  c4_y = c4_u3;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_overflow;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  uint8_T c4_y;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c4_overflow = sf_mex_dup(c4_mxArrayInData);
    c4_identifier = c4_varName;
    c4_thisId.fIdentifier = c4_identifier;
    c4_thisId.fParent = NULL;
    c4_y = c4_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_overflow),
      &c4_thisId);
    sf_mex_destroy(&c4_overflow);
    *(uint8_T *)c4_outData = c4_y;
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_i_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  const mxArray *c4_u;
  const mxArray *c4_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = sf_mex_dup(*(const mxArray **)c4_inData);
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_duplicatearraysafe(&c4_u), false);
  sf_mex_destroy(&c4_u);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static int8_T c4_i_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int8_T c4_y;
  const mxArray *c4_mxFi = NULL;
  const mxArray *c4_mxInt = NULL;
  int8_T c4_i1;
  (void)chartInstance;
  sf_mex_check_fi(c4_parentId, c4_u, false, 0U, NULL, c4_eml_mx, c4_c_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u), false);
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)), false);
  sf_mex_import(c4_parentId, sf_mex_dup(c4_mxInt), &c4_i1, 1, 2, 0U, 0, 0U, 0);
  sf_mex_destroy(&c4_mxFi);
  sf_mex_destroy(&c4_mxInt);
  c4_y = c4_i1;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_u2;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int8_T c4_y;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c4_u2 = sf_mex_dup(c4_mxArrayInData);
    c4_identifier = c4_varName;
    c4_thisId.fIdentifier = c4_identifier;
    c4_thisId.fParent = NULL;
    c4_y = c4_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_u2), &c4_thisId);
    sf_mex_destroy(&c4_u2);
    *(int8_T *)c4_outData = c4_y;
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_j_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  int16_T c4_u;
  const mxArray *c4_y = NULL;
  int16_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c4_u = *(int16_T *)c4_inData;
    c4_y = NULL;
    c4_b_u = c4_u;
    c4_b_y = NULL;
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 4, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c4_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_f_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c4_mxArrayOutData;
}

static int16_T c4_j_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int16_T c4_y;
  const mxArray *c4_mxFi = NULL;
  const mxArray *c4_mxInt = NULL;
  int16_T c4_i2;
  (void)chartInstance;
  sf_mex_check_fi(c4_parentId, c4_u, false, 0U, NULL, c4_eml_mx, c4_f_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u), false);
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)), false);
  sf_mex_import(c4_parentId, sf_mex_dup(c4_mxInt), &c4_i2, 1, 4, 0U, 0, 0U, 0);
  sf_mex_destroy(&c4_mxFi);
  sf_mex_destroy(&c4_mxInt);
  c4_y = c4_i2;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_temp_sum;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int16_T c4_y;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c4_temp_sum = sf_mex_dup(c4_mxArrayInData);
    c4_identifier = c4_varName;
    c4_thisId.fIdentifier = c4_identifier;
    c4_thisId.fParent = NULL;
    c4_y = c4_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_temp_sum),
      &c4_thisId);
    sf_mex_destroy(&c4_temp_sum);
    *(int16_T *)c4_outData = c4_y;
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray *sf_c4_hdlcodercpu_eml_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  sf_mex_assign(&c4_nameCaptureInfo, sf_mex_createstruct("structure", 2, 170, 1),
                false);
  c4_info_helper(&c4_nameCaptureInfo);
  c4_b_info_helper(&c4_nameCaptureInfo);
  c4_c_info_helper(&c4_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c4_nameCaptureInfo);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(const mxArray **c4_info)
{
  const mxArray *c4_rhs0 = NULL;
  const mxArray *c4_lhs0 = NULL;
  const mxArray *c4_rhs1 = NULL;
  const mxArray *c4_lhs1 = NULL;
  const mxArray *c4_rhs2 = NULL;
  const mxArray *c4_lhs2 = NULL;
  const mxArray *c4_rhs3 = NULL;
  const mxArray *c4_lhs3 = NULL;
  const mxArray *c4_rhs4 = NULL;
  const mxArray *c4_lhs4 = NULL;
  const mxArray *c4_rhs5 = NULL;
  const mxArray *c4_lhs5 = NULL;
  const mxArray *c4_rhs6 = NULL;
  const mxArray *c4_lhs6 = NULL;
  const mxArray *c4_rhs7 = NULL;
  const mxArray *c4_lhs7 = NULL;
  const mxArray *c4_rhs8 = NULL;
  const mxArray *c4_lhs8 = NULL;
  const mxArray *c4_rhs9 = NULL;
  const mxArray *c4_lhs9 = NULL;
  const mxArray *c4_rhs10 = NULL;
  const mxArray *c4_lhs10 = NULL;
  const mxArray *c4_rhs11 = NULL;
  const mxArray *c4_lhs11 = NULL;
  const mxArray *c4_rhs12 = NULL;
  const mxArray *c4_lhs12 = NULL;
  const mxArray *c4_rhs13 = NULL;
  const mxArray *c4_lhs13 = NULL;
  const mxArray *c4_rhs14 = NULL;
  const mxArray *c4_lhs14 = NULL;
  const mxArray *c4_rhs15 = NULL;
  const mxArray *c4_lhs15 = NULL;
  const mxArray *c4_rhs16 = NULL;
  const mxArray *c4_lhs16 = NULL;
  const mxArray *c4_rhs17 = NULL;
  const mxArray *c4_lhs17 = NULL;
  const mxArray *c4_rhs18 = NULL;
  const mxArray *c4_lhs18 = NULL;
  const mxArray *c4_rhs19 = NULL;
  const mxArray *c4_lhs19 = NULL;
  const mxArray *c4_rhs20 = NULL;
  const mxArray *c4_lhs20 = NULL;
  const mxArray *c4_rhs21 = NULL;
  const mxArray *c4_lhs21 = NULL;
  const mxArray *c4_rhs22 = NULL;
  const mxArray *c4_lhs22 = NULL;
  const mxArray *c4_rhs23 = NULL;
  const mxArray *c4_lhs23 = NULL;
  const mxArray *c4_rhs24 = NULL;
  const mxArray *c4_lhs24 = NULL;
  const mxArray *c4_rhs25 = NULL;
  const mxArray *c4_lhs25 = NULL;
  const mxArray *c4_rhs26 = NULL;
  const mxArray *c4_lhs26 = NULL;
  const mxArray *c4_rhs27 = NULL;
  const mxArray *c4_lhs27 = NULL;
  const mxArray *c4_rhs28 = NULL;
  const mxArray *c4_lhs28 = NULL;
  const mxArray *c4_rhs29 = NULL;
  const mxArray *c4_lhs29 = NULL;
  const mxArray *c4_rhs30 = NULL;
  const mxArray *c4_lhs30 = NULL;
  const mxArray *c4_rhs31 = NULL;
  const mxArray *c4_lhs31 = NULL;
  const mxArray *c4_rhs32 = NULL;
  const mxArray *c4_lhs32 = NULL;
  const mxArray *c4_rhs33 = NULL;
  const mxArray *c4_lhs33 = NULL;
  const mxArray *c4_rhs34 = NULL;
  const mxArray *c4_lhs34 = NULL;
  const mxArray *c4_rhs35 = NULL;
  const mxArray *c4_lhs35 = NULL;
  const mxArray *c4_rhs36 = NULL;
  const mxArray *c4_lhs36 = NULL;
  const mxArray *c4_rhs37 = NULL;
  const mxArray *c4_lhs37 = NULL;
  const mxArray *c4_rhs38 = NULL;
  const mxArray *c4_lhs38 = NULL;
  const mxArray *c4_rhs39 = NULL;
  const mxArray *c4_lhs39 = NULL;
  const mxArray *c4_rhs40 = NULL;
  const mxArray *c4_lhs40 = NULL;
  const mxArray *c4_rhs41 = NULL;
  const mxArray *c4_lhs41 = NULL;
  const mxArray *c4_rhs42 = NULL;
  const mxArray *c4_lhs42 = NULL;
  const mxArray *c4_rhs43 = NULL;
  const mxArray *c4_lhs43 = NULL;
  const mxArray *c4_rhs44 = NULL;
  const mxArray *c4_lhs44 = NULL;
  const mxArray *c4_rhs45 = NULL;
  const mxArray *c4_lhs45 = NULL;
  const mxArray *c4_rhs46 = NULL;
  const mxArray *c4_lhs46 = NULL;
  const mxArray *c4_rhs47 = NULL;
  const mxArray *c4_lhs47 = NULL;
  const mxArray *c4_rhs48 = NULL;
  const mxArray *c4_lhs48 = NULL;
  const mxArray *c4_rhs49 = NULL;
  const mxArray *c4_lhs49 = NULL;
  const mxArray *c4_rhs50 = NULL;
  const mxArray *c4_lhs50 = NULL;
  const mxArray *c4_rhs51 = NULL;
  const mxArray *c4_lhs51 = NULL;
  const mxArray *c4_rhs52 = NULL;
  const mxArray *c4_lhs52 = NULL;
  const mxArray *c4_rhs53 = NULL;
  const mxArray *c4_lhs53 = NULL;
  const mxArray *c4_rhs54 = NULL;
  const mxArray *c4_lhs54 = NULL;
  const mxArray *c4_rhs55 = NULL;
  const mxArray *c4_lhs55 = NULL;
  const mxArray *c4_rhs56 = NULL;
  const mxArray *c4_lhs56 = NULL;
  const mxArray *c4_rhs57 = NULL;
  const mxArray *c4_lhs57 = NULL;
  const mxArray *c4_rhs58 = NULL;
  const mxArray *c4_lhs58 = NULL;
  const mxArray *c4_rhs59 = NULL;
  const mxArray *c4_lhs59 = NULL;
  const mxArray *c4_rhs60 = NULL;
  const mxArray *c4_lhs60 = NULL;
  const mxArray *c4_rhs61 = NULL;
  const mxArray *c4_lhs61 = NULL;
  const mxArray *c4_rhs62 = NULL;
  const mxArray *c4_lhs62 = NULL;
  const mxArray *c4_rhs63 = NULL;
  const mxArray *c4_lhs63 = NULL;
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("fimath"), "name", "name", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1381857498U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c4_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_fimath_constructor_helper"),
                  "name", "name", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_fimath_constructor_helper.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c4_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("bitget"), "name", "name", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1370017086U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c4_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c4_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c4_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c4_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfixed"), "name", "name", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c4_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "context", "context", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("get"), "name", "name", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c4_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("all"), "name", "name", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "resolved",
                  "resolved", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372589614U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c4_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c4_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c4_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.allOrAny"),
                  "name", "name", 11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372590358U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c4_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c4_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isequal"), "name", "name", 13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286825958U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c4_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_isequal_core"), "name",
                  "name", 14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286825986U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c4_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.constNonSingletonDim"), "name", "name", 15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/constNonSingletonDim.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372590360U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c4_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("numerictype"), "name", "name",
                  16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1348199118U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c4_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m"), "context",
                  "context", 17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("length"), "name", "name", 17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("cell"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1303153406U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c4_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("fimath"), "name", "name", 18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303184U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c4_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/@embedded/@fi/bitget.m!convertOneBasedBitIndexToZeroBased"),
                  "context", "context", 19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("floor"), "name", "name", 19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c4_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c4_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286825926U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c4_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("fi_impl"), "name", "name", 22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "resolved",
                  "resolved", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389302372U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c4_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 23);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 23);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 23);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c4_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 24);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("length"), "name", "name", 24);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("cell"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 24);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1303153406U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c4_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 25);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_fi_checkforconst"), "name",
                  "name", 25);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fimath"),
                  "dominantType", "dominantType", 25);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforconst.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517552U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c4_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 26);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 26);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 26);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c4_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 27);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfloat"), "name", "name", 27);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c4_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m"),
                  "context", "context", 28);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("get"), "name", "name", 28);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 28);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c4_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput"),
                  "context", "context", 29);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("castLike"), "name", "name", 29);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "resolved", "resolved", 29);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1348199122U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c4_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 30);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 30);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 30);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c4_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 31);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfimathlocal"), "name",
                  "name", 31);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfimathlocal.m"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c4_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 32);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("removefimath"), "name", "name",
                  32);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/removefimath.m"), "resolved",
                  "resolved", 32);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1325034780U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c4_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 33);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("numerictype"), "name", "name",
                  33);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303186U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c4_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 34);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("fi_impl"), "name", "name", 34);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "resolved",
                  "resolved", 34);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389302372U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c4_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 35);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 35);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 35);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 35);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c4_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 36);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("get"), "name", "name", 36);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 36);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 36);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c4_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 37);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("strcmpi"), "name", "name", 37);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "resolved",
                  "resolved", 37);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c4_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "context",
                  "context", 38);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_assert_supported_string"),
                  "name", "name", 38);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m"),
                  "resolved", "resolved", 38);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c4_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m!inrange"),
                  "context", "context", 39);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_charmax"), "name", "name",
                  39);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c4_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"), "context",
                  "context", 40);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmax"), "name", "name", 40);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 40);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c4_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 41);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 41);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 41);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1381857500U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c4_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "context",
                  "context", 42);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("min"), "name", "name", 42);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 42);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1311262518U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c4_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "context",
                  "context", 43);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 43);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 43);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303184U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c4_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 44);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 44);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 44);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c4_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 45);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 45);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 45);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c4_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 46);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 46);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 46);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 46);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c4_rhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 47);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 47);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 47);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c4_rhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 48);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 48);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 48);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 48);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c4_rhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs48), "lhs", "lhs",
                  48);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 49);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 49);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 49);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 49);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 49);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 49);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 49);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 49);
  sf_mex_assign(&c4_rhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs49), "rhs", "rhs",
                  49);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs49), "lhs", "lhs",
                  49);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 50);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 50);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 50);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 50);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 50);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 50);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 50);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 50);
  sf_mex_assign(&c4_rhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs50), "rhs", "rhs",
                  50);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs50), "lhs", "lhs",
                  50);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 51);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 51);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 51);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 51);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 51);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 51);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 51);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 51);
  sf_mex_assign(&c4_rhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs51), "rhs", "rhs",
                  51);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs51), "lhs", "lhs",
                  51);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 52);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfimath"), "name", "name", 52);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 52);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfimath.m"), "resolved",
                  "resolved", 52);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 52);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 52);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 52);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 52);
  sf_mex_assign(&c4_rhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs52), "rhs", "rhs",
                  52);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs52), "lhs", "lhs",
                  52);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 53);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("get"), "name", "name", 53);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 53);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 53);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 53);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 53);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 53);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 53);
  sf_mex_assign(&c4_rhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs53), "rhs", "rhs",
                  53);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs53), "lhs", "lhs",
                  53);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 54);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_fi_constructor_helper"),
                  "name", "name", 54);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 54);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_fi_constructor_helper.m"),
                  "resolved", "resolved", 54);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 54);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 54);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 54);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 54);
  sf_mex_assign(&c4_rhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs54), "rhs", "rhs",
                  54);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs54), "lhs", "lhs",
                  54);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 55);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_fi_checkforerror"), "name",
                  "name", 55);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 55);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m"),
                  "resolved", "resolved", 55);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1360285946U), "fileTimeLo",
                  "fileTimeLo", 55);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 55);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 55);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 55);
  sf_mex_assign(&c4_rhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs55), "rhs", "rhs",
                  55);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs55), "lhs", "lhs",
                  55);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 56);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_fi_constructor_helper"),
                  "name", "name", 56);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 56);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_fi_constructor_helper.m"),
                  "resolved", "resolved", 56);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 56);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 56);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 56);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 56);
  sf_mex_assign(&c4_rhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs56), "rhs", "rhs",
                  56);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs56), "lhs", "lhs",
                  56);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 57);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_fi_checkforntype"), "name",
                  "name", 57);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 57);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m"),
                  "resolved", "resolved", 57);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1381857498U), "fileTimeLo",
                  "fileTimeLo", 57);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 57);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 57);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 57);
  sf_mex_assign(&c4_rhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs57), "rhs", "rhs",
                  57);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs57), "lhs", "lhs",
                  57);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m"),
                  "context", "context", 58);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("get"), "name", "name", 58);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 58);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 58);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 58);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 58);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 58);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 58);
  sf_mex_assign(&c4_rhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs58), "rhs", "rhs",
                  58);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs58), "lhs", "lhs",
                  58);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 59);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("uint8"), "name", "name", 59);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 59);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m"),
                  "resolved", "resolved", 59);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1311262522U), "fileTimeLo",
                  "fileTimeLo", 59);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 59);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 59);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 59);
  sf_mex_assign(&c4_rhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs59), "rhs", "rhs",
                  59);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs59), "lhs", "lhs",
                  59);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m"),
                  "context", "context", 60);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_fi_getRealWorldValAsDType"),
                  "name", "name", 60);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 60);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getRealWorldValAsDType.m"),
                  "resolved", "resolved", 60);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517570U), "fileTimeLo",
                  "fileTimeLo", 60);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 60);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 60);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 60);
  sf_mex_assign(&c4_rhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs60), "rhs", "rhs",
                  60);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs60), "lhs", "lhs",
                  60);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getRealWorldValAsDType.m"),
                  "context", "context", 61);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isscaledtype"), "name", "name",
                  61);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 61);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 61);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 61);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 61);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 61);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 61);
  sf_mex_assign(&c4_rhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs61), "rhs", "rhs",
                  61);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs61), "lhs", "lhs",
                  61);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "context", "context", 62);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfixed"), "name", "name", 62);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 62);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 62);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 62);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 62);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 62);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 62);
  sf_mex_assign(&c4_rhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs62), "rhs", "rhs",
                  62);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs62), "lhs", "lhs",
                  62);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getRealWorldValAsDType.m"),
                  "context", "context", 63);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isscalingbinarypoint"), "name",
                  "name", 63);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 63);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscalingbinarypoint.m"),
                  "resolved", "resolved", 63);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 63);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 63);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 63);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 63);
  sf_mex_assign(&c4_rhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs63), "rhs", "rhs",
                  63);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs63), "lhs", "lhs",
                  63);
  sf_mex_destroy(&c4_rhs0);
  sf_mex_destroy(&c4_lhs0);
  sf_mex_destroy(&c4_rhs1);
  sf_mex_destroy(&c4_lhs1);
  sf_mex_destroy(&c4_rhs2);
  sf_mex_destroy(&c4_lhs2);
  sf_mex_destroy(&c4_rhs3);
  sf_mex_destroy(&c4_lhs3);
  sf_mex_destroy(&c4_rhs4);
  sf_mex_destroy(&c4_lhs4);
  sf_mex_destroy(&c4_rhs5);
  sf_mex_destroy(&c4_lhs5);
  sf_mex_destroy(&c4_rhs6);
  sf_mex_destroy(&c4_lhs6);
  sf_mex_destroy(&c4_rhs7);
  sf_mex_destroy(&c4_lhs7);
  sf_mex_destroy(&c4_rhs8);
  sf_mex_destroy(&c4_lhs8);
  sf_mex_destroy(&c4_rhs9);
  sf_mex_destroy(&c4_lhs9);
  sf_mex_destroy(&c4_rhs10);
  sf_mex_destroy(&c4_lhs10);
  sf_mex_destroy(&c4_rhs11);
  sf_mex_destroy(&c4_lhs11);
  sf_mex_destroy(&c4_rhs12);
  sf_mex_destroy(&c4_lhs12);
  sf_mex_destroy(&c4_rhs13);
  sf_mex_destroy(&c4_lhs13);
  sf_mex_destroy(&c4_rhs14);
  sf_mex_destroy(&c4_lhs14);
  sf_mex_destroy(&c4_rhs15);
  sf_mex_destroy(&c4_lhs15);
  sf_mex_destroy(&c4_rhs16);
  sf_mex_destroy(&c4_lhs16);
  sf_mex_destroy(&c4_rhs17);
  sf_mex_destroy(&c4_lhs17);
  sf_mex_destroy(&c4_rhs18);
  sf_mex_destroy(&c4_lhs18);
  sf_mex_destroy(&c4_rhs19);
  sf_mex_destroy(&c4_lhs19);
  sf_mex_destroy(&c4_rhs20);
  sf_mex_destroy(&c4_lhs20);
  sf_mex_destroy(&c4_rhs21);
  sf_mex_destroy(&c4_lhs21);
  sf_mex_destroy(&c4_rhs22);
  sf_mex_destroy(&c4_lhs22);
  sf_mex_destroy(&c4_rhs23);
  sf_mex_destroy(&c4_lhs23);
  sf_mex_destroy(&c4_rhs24);
  sf_mex_destroy(&c4_lhs24);
  sf_mex_destroy(&c4_rhs25);
  sf_mex_destroy(&c4_lhs25);
  sf_mex_destroy(&c4_rhs26);
  sf_mex_destroy(&c4_lhs26);
  sf_mex_destroy(&c4_rhs27);
  sf_mex_destroy(&c4_lhs27);
  sf_mex_destroy(&c4_rhs28);
  sf_mex_destroy(&c4_lhs28);
  sf_mex_destroy(&c4_rhs29);
  sf_mex_destroy(&c4_lhs29);
  sf_mex_destroy(&c4_rhs30);
  sf_mex_destroy(&c4_lhs30);
  sf_mex_destroy(&c4_rhs31);
  sf_mex_destroy(&c4_lhs31);
  sf_mex_destroy(&c4_rhs32);
  sf_mex_destroy(&c4_lhs32);
  sf_mex_destroy(&c4_rhs33);
  sf_mex_destroy(&c4_lhs33);
  sf_mex_destroy(&c4_rhs34);
  sf_mex_destroy(&c4_lhs34);
  sf_mex_destroy(&c4_rhs35);
  sf_mex_destroy(&c4_lhs35);
  sf_mex_destroy(&c4_rhs36);
  sf_mex_destroy(&c4_lhs36);
  sf_mex_destroy(&c4_rhs37);
  sf_mex_destroy(&c4_lhs37);
  sf_mex_destroy(&c4_rhs38);
  sf_mex_destroy(&c4_lhs38);
  sf_mex_destroy(&c4_rhs39);
  sf_mex_destroy(&c4_lhs39);
  sf_mex_destroy(&c4_rhs40);
  sf_mex_destroy(&c4_lhs40);
  sf_mex_destroy(&c4_rhs41);
  sf_mex_destroy(&c4_lhs41);
  sf_mex_destroy(&c4_rhs42);
  sf_mex_destroy(&c4_lhs42);
  sf_mex_destroy(&c4_rhs43);
  sf_mex_destroy(&c4_lhs43);
  sf_mex_destroy(&c4_rhs44);
  sf_mex_destroy(&c4_lhs44);
  sf_mex_destroy(&c4_rhs45);
  sf_mex_destroy(&c4_lhs45);
  sf_mex_destroy(&c4_rhs46);
  sf_mex_destroy(&c4_lhs46);
  sf_mex_destroy(&c4_rhs47);
  sf_mex_destroy(&c4_lhs47);
  sf_mex_destroy(&c4_rhs48);
  sf_mex_destroy(&c4_lhs48);
  sf_mex_destroy(&c4_rhs49);
  sf_mex_destroy(&c4_lhs49);
  sf_mex_destroy(&c4_rhs50);
  sf_mex_destroy(&c4_lhs50);
  sf_mex_destroy(&c4_rhs51);
  sf_mex_destroy(&c4_lhs51);
  sf_mex_destroy(&c4_rhs52);
  sf_mex_destroy(&c4_lhs52);
  sf_mex_destroy(&c4_rhs53);
  sf_mex_destroy(&c4_lhs53);
  sf_mex_destroy(&c4_rhs54);
  sf_mex_destroy(&c4_lhs54);
  sf_mex_destroy(&c4_rhs55);
  sf_mex_destroy(&c4_lhs55);
  sf_mex_destroy(&c4_rhs56);
  sf_mex_destroy(&c4_lhs56);
  sf_mex_destroy(&c4_rhs57);
  sf_mex_destroy(&c4_lhs57);
  sf_mex_destroy(&c4_rhs58);
  sf_mex_destroy(&c4_lhs58);
  sf_mex_destroy(&c4_rhs59);
  sf_mex_destroy(&c4_lhs59);
  sf_mex_destroy(&c4_rhs60);
  sf_mex_destroy(&c4_lhs60);
  sf_mex_destroy(&c4_rhs61);
  sf_mex_destroy(&c4_lhs61);
  sf_mex_destroy(&c4_rhs62);
  sf_mex_destroy(&c4_lhs62);
  sf_mex_destroy(&c4_rhs63);
  sf_mex_destroy(&c4_lhs63);
}

static const mxArray *c4_emlrt_marshallOut(const char * c4_u)
{
  const mxArray *c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c4_u)), false);
  return c4_y;
}

static const mxArray *c4_b_emlrt_marshallOut(const uint32_T c4_u)
{
  const mxArray *c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 7, 0U, 0U, 0U, 0), false);
  return c4_y;
}

static void c4_b_info_helper(const mxArray **c4_info)
{
  const mxArray *c4_rhs64 = NULL;
  const mxArray *c4_lhs64 = NULL;
  const mxArray *c4_rhs65 = NULL;
  const mxArray *c4_lhs65 = NULL;
  const mxArray *c4_rhs66 = NULL;
  const mxArray *c4_lhs66 = NULL;
  const mxArray *c4_rhs67 = NULL;
  const mxArray *c4_lhs67 = NULL;
  const mxArray *c4_rhs68 = NULL;
  const mxArray *c4_lhs68 = NULL;
  const mxArray *c4_rhs69 = NULL;
  const mxArray *c4_lhs69 = NULL;
  const mxArray *c4_rhs70 = NULL;
  const mxArray *c4_lhs70 = NULL;
  const mxArray *c4_rhs71 = NULL;
  const mxArray *c4_lhs71 = NULL;
  const mxArray *c4_rhs72 = NULL;
  const mxArray *c4_lhs72 = NULL;
  const mxArray *c4_rhs73 = NULL;
  const mxArray *c4_lhs73 = NULL;
  const mxArray *c4_rhs74 = NULL;
  const mxArray *c4_lhs74 = NULL;
  const mxArray *c4_rhs75 = NULL;
  const mxArray *c4_lhs75 = NULL;
  const mxArray *c4_rhs76 = NULL;
  const mxArray *c4_lhs76 = NULL;
  const mxArray *c4_rhs77 = NULL;
  const mxArray *c4_lhs77 = NULL;
  const mxArray *c4_rhs78 = NULL;
  const mxArray *c4_lhs78 = NULL;
  const mxArray *c4_rhs79 = NULL;
  const mxArray *c4_lhs79 = NULL;
  const mxArray *c4_rhs80 = NULL;
  const mxArray *c4_lhs80 = NULL;
  const mxArray *c4_rhs81 = NULL;
  const mxArray *c4_lhs81 = NULL;
  const mxArray *c4_rhs82 = NULL;
  const mxArray *c4_lhs82 = NULL;
  const mxArray *c4_rhs83 = NULL;
  const mxArray *c4_lhs83 = NULL;
  const mxArray *c4_rhs84 = NULL;
  const mxArray *c4_lhs84 = NULL;
  const mxArray *c4_rhs85 = NULL;
  const mxArray *c4_lhs85 = NULL;
  const mxArray *c4_rhs86 = NULL;
  const mxArray *c4_lhs86 = NULL;
  const mxArray *c4_rhs87 = NULL;
  const mxArray *c4_lhs87 = NULL;
  const mxArray *c4_rhs88 = NULL;
  const mxArray *c4_lhs88 = NULL;
  const mxArray *c4_rhs89 = NULL;
  const mxArray *c4_lhs89 = NULL;
  const mxArray *c4_rhs90 = NULL;
  const mxArray *c4_lhs90 = NULL;
  const mxArray *c4_rhs91 = NULL;
  const mxArray *c4_lhs91 = NULL;
  const mxArray *c4_rhs92 = NULL;
  const mxArray *c4_lhs92 = NULL;
  const mxArray *c4_rhs93 = NULL;
  const mxArray *c4_lhs93 = NULL;
  const mxArray *c4_rhs94 = NULL;
  const mxArray *c4_lhs94 = NULL;
  const mxArray *c4_rhs95 = NULL;
  const mxArray *c4_lhs95 = NULL;
  const mxArray *c4_rhs96 = NULL;
  const mxArray *c4_lhs96 = NULL;
  const mxArray *c4_rhs97 = NULL;
  const mxArray *c4_lhs97 = NULL;
  const mxArray *c4_rhs98 = NULL;
  const mxArray *c4_lhs98 = NULL;
  const mxArray *c4_rhs99 = NULL;
  const mxArray *c4_lhs99 = NULL;
  const mxArray *c4_rhs100 = NULL;
  const mxArray *c4_lhs100 = NULL;
  const mxArray *c4_rhs101 = NULL;
  const mxArray *c4_lhs101 = NULL;
  const mxArray *c4_rhs102 = NULL;
  const mxArray *c4_lhs102 = NULL;
  const mxArray *c4_rhs103 = NULL;
  const mxArray *c4_lhs103 = NULL;
  const mxArray *c4_rhs104 = NULL;
  const mxArray *c4_lhs104 = NULL;
  const mxArray *c4_rhs105 = NULL;
  const mxArray *c4_lhs105 = NULL;
  const mxArray *c4_rhs106 = NULL;
  const mxArray *c4_lhs106 = NULL;
  const mxArray *c4_rhs107 = NULL;
  const mxArray *c4_lhs107 = NULL;
  const mxArray *c4_rhs108 = NULL;
  const mxArray *c4_lhs108 = NULL;
  const mxArray *c4_rhs109 = NULL;
  const mxArray *c4_lhs109 = NULL;
  const mxArray *c4_rhs110 = NULL;
  const mxArray *c4_lhs110 = NULL;
  const mxArray *c4_rhs111 = NULL;
  const mxArray *c4_lhs111 = NULL;
  const mxArray *c4_rhs112 = NULL;
  const mxArray *c4_lhs112 = NULL;
  const mxArray *c4_rhs113 = NULL;
  const mxArray *c4_lhs113 = NULL;
  const mxArray *c4_rhs114 = NULL;
  const mxArray *c4_lhs114 = NULL;
  const mxArray *c4_rhs115 = NULL;
  const mxArray *c4_lhs115 = NULL;
  const mxArray *c4_rhs116 = NULL;
  const mxArray *c4_lhs116 = NULL;
  const mxArray *c4_rhs117 = NULL;
  const mxArray *c4_lhs117 = NULL;
  const mxArray *c4_rhs118 = NULL;
  const mxArray *c4_lhs118 = NULL;
  const mxArray *c4_rhs119 = NULL;
  const mxArray *c4_lhs119 = NULL;
  const mxArray *c4_rhs120 = NULL;
  const mxArray *c4_lhs120 = NULL;
  const mxArray *c4_rhs121 = NULL;
  const mxArray *c4_lhs121 = NULL;
  const mxArray *c4_rhs122 = NULL;
  const mxArray *c4_lhs122 = NULL;
  const mxArray *c4_rhs123 = NULL;
  const mxArray *c4_lhs123 = NULL;
  const mxArray *c4_rhs124 = NULL;
  const mxArray *c4_lhs124 = NULL;
  const mxArray *c4_rhs125 = NULL;
  const mxArray *c4_lhs125 = NULL;
  const mxArray *c4_rhs126 = NULL;
  const mxArray *c4_lhs126 = NULL;
  const mxArray *c4_rhs127 = NULL;
  const mxArray *c4_lhs127 = NULL;
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscalingbinarypoint.m"),
                  "context", "context", 64);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isscaledtype"), "name", "name",
                  64);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 64);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 64);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 64);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 64);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 64);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 64);
  sf_mex_assign(&c4_rhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs64), "rhs", "rhs",
                  64);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs64), "lhs", "lhs",
                  64);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscalingbinarypoint.m"),
                  "context", "context", 65);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_isslopebiasscaled"),
                  "name", "name", 65);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 65);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "resolved", "resolved", 65);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 65);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 65);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 65);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 65);
  sf_mex_assign(&c4_rhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs65), "rhs", "rhs",
                  65);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs65), "lhs", "lhs",
                  65);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "context", "context", 66);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("get"), "name", "name", 66);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 66);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 66);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 66);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 66);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 66);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 66);
  sf_mex_assign(&c4_rhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs66), "rhs", "rhs",
                  66);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs66), "lhs", "lhs",
                  66);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getRealWorldValAsDType.m"),
                  "context", "context", 67);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("get"), "name", "name", 67);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 67);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/get.m"),
                  "resolved", "resolved", 67);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375987886U), "fileTimeLo",
                  "fileTimeLo", 67);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 67);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 67);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 67);
  sf_mex_assign(&c4_rhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs67), "rhs", "rhs",
                  67);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs67), "lhs", "lhs",
                  67);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/get.m"),
                  "context", "context", 68);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 68);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 68);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_scalar_eg.m"),
                  "resolved", "resolved", 68);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517572U), "fileTimeLo",
                  "fileTimeLo", 68);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 68);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 68);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 68);
  sf_mex_assign(&c4_rhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs68), "rhs", "rhs",
                  68);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs68), "lhs", "lhs",
                  68);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_scalar_eg.m"),
                  "context", "context", 69);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("numerictype"), "name", "name",
                  69);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 69);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m"),
                  "resolved", "resolved", 69);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303186U), "fileTimeLo",
                  "fileTimeLo", 69);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 69);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 69);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 69);
  sf_mex_assign(&c4_rhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs69), "rhs", "rhs",
                  69);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs69), "lhs", "lhs",
                  69);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_scalar_eg.m"),
                  "context", "context", 70);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("fimath"), "name", "name", 70);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 70);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m"),
                  "resolved", "resolved", 70);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303184U), "fileTimeLo",
                  "fileTimeLo", 70);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 70);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 70);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 70);
  sf_mex_assign(&c4_rhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs70), "rhs", "rhs",
                  70);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs70), "lhs", "lhs",
                  70);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/get.m"),
                  "context", "context", 71);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_getfiprop_helper"), "name",
                  "name", 71);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 71);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_getfiprop_helper.m"),
                  "resolved", "resolved", 71);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 71);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 71);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 71);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 71);
  sf_mex_assign(&c4_rhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs71), "rhs", "rhs",
                  71);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs71), "lhs", "lhs",
                  71);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 72);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 72);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 72);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 72);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 72);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 72);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 72);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 72);
  sf_mex_assign(&c4_rhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs72), "rhs", "rhs",
                  72);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs72), "lhs", "lhs",
                  72);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 73);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 73);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 73);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 73);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 73);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 73);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 73);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 73);
  sf_mex_assign(&c4_rhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs73), "rhs", "rhs",
                  73);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs73), "lhs", "lhs",
                  73);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 74);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_fi_checkforerror"), "name",
                  "name", 74);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 74);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m"),
                  "resolved", "resolved", 74);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1360285946U), "fileTimeLo",
                  "fileTimeLo", 74);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 74);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 74);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 74);
  sf_mex_assign(&c4_rhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs74), "rhs", "rhs",
                  74);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs74), "lhs", "lhs",
                  74);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 75);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("bitcmp"), "name", "name", 75);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 75);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitcmp.m"),
                  "resolved", "resolved", 75);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 75);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 75);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 75);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 75);
  sf_mex_assign(&c4_rhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs75), "rhs", "rhs",
                  75);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs75), "lhs", "lhs",
                  75);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitcmp.m"),
                  "context", "context", 76);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 76);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 76);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 76);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 76);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 76);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 76);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 76);
  sf_mex_assign(&c4_rhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs76), "rhs", "rhs",
                  76);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs76), "lhs", "lhs",
                  76);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitcmp.m"),
                  "context", "context", 77);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfixed"), "name", "name", 77);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 77);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 77);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 77);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 77);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 77);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 77);
  sf_mex_assign(&c4_rhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs77), "rhs", "rhs",
                  77);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs77), "lhs", "lhs",
                  77);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitcmp.m"),
                  "context", "context", 78);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("fimath"), "name", "name", 78);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 78);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m"),
                  "resolved", "resolved", 78);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303184U), "fileTimeLo",
                  "fileTimeLo", 78);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 78);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 78);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 78);
  sf_mex_assign(&c4_rhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs78), "rhs", "rhs",
                  78);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs78), "lhs", "lhs",
                  78);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitcmp.m"),
                  "context", "context", 79);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isslopebiasscaled"), "name",
                  "name", 79);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 79);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isslopebiasscaled.m"),
                  "resolved", "resolved", 79);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517560U), "fileTimeLo",
                  "fileTimeLo", 79);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 79);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 79);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 79);
  sf_mex_assign(&c4_rhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs79), "rhs", "rhs",
                  79);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs79), "lhs", "lhs",
                  79);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isslopebiasscaled.m"),
                  "context", "context", 80);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 80);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 80);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 80);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 80);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 80);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 80);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 80);
  sf_mex_assign(&c4_rhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs80), "rhs", "rhs",
                  80);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs80), "lhs", "lhs",
                  80);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isslopebiasscaled.m"),
                  "context", "context", 81);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("get"), "name", "name", 81);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 81);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 81);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 81);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 81);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 81);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 81);
  sf_mex_assign(&c4_rhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs81), "rhs", "rhs",
                  81);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs81), "lhs", "lhs",
                  81);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isslopebiasscaled.m"),
                  "context", "context", 82);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isequal"), "name", "name", 82);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 82);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 82);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286825958U), "fileTimeLo",
                  "fileTimeLo", 82);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 82);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 82);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 82);
  sf_mex_assign(&c4_rhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs82), "rhs", "rhs",
                  82);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs82), "lhs", "lhs",
                  82);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar"),
                  "context", "context", 83);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isnan"), "name", "name", 83);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 83);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 83);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363717458U), "fileTimeLo",
                  "fileTimeLo", 83);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 83);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 83);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 83);
  sf_mex_assign(&c4_rhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs83), "rhs", "rhs",
                  83);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs83), "lhs", "lhs",
                  83);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "context",
                  "context", 84);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 84);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 84);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 84);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 84);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 84);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 84);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 84);
  sf_mex_assign(&c4_rhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs84), "rhs", "rhs",
                  84);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs84), "lhs", "lhs",
                  84);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 85);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("bitconcat"), "name", "name",
                  85);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 85);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitconcat.m"),
                  "resolved", "resolved", 85);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372589614U), "fileTimeLo",
                  "fileTimeLo", 85);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 85);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 85);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 85);
  sf_mex_assign(&c4_rhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs85), "rhs", "rhs",
                  85);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs85), "lhs", "lhs",
                  85);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/@embedded/@fi/bitconcat.m!bitconcat_checkarg"),
                  "context", "context", 86);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 86);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 86);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 86);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 86);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 86);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 86);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 86);
  sf_mex_assign(&c4_rhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs86), "rhs", "rhs",
                  86);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs86), "lhs", "lhs",
                  86);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/@embedded/@fi/bitconcat.m!bitconcat_checkarg"),
                  "context", "context", 87);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfixed"), "name", "name", 87);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 87);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 87);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 87);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 87);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 87);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 87);
  sf_mex_assign(&c4_rhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs87), "rhs", "rhs",
                  87);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs87), "lhs", "lhs",
                  87);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/@embedded/@fi/bitconcat.m!bitconcat_checkarg"),
                  "context", "context", 88);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_isslopebiasscaled"),
                  "name", "name", 88);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 88);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "resolved", "resolved", 88);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 88);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 88);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 88);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 88);
  sf_mex_assign(&c4_rhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs88), "rhs", "rhs",
                  88);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs88), "lhs", "lhs",
                  88);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 89);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("fimath"), "name", "name", 89);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 89);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m"),
                  "resolved", "resolved", 89);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303184U), "fileTimeLo",
                  "fileTimeLo", 89);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 89);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 89);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 89);
  sf_mex_assign(&c4_rhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs89), "rhs", "rhs",
                  89);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs89), "lhs", "lhs",
                  89);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 90);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("plus"), "name", "name", 90);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 90);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "resolved", "resolved", 90);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517584U), "fileTimeLo",
                  "fileTimeLo", 90);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 90);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 90);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 90);
  sf_mex_assign(&c4_rhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs90), "rhs", "rhs",
                  90);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs90), "lhs", "lhs",
                  90);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 91);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 91);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 91);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 91);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 91);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 91);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 91);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 91);
  sf_mex_assign(&c4_rhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs91), "rhs", "rhs",
                  91);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs91), "lhs", "lhs",
                  91);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 92);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 92);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 92);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 92);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 92);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 92);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 92);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 92);
  sf_mex_assign(&c4_rhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs92), "rhs", "rhs",
                  92);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs92), "lhs", "lhs",
                  92);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 93);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isscaledtype"), "name", "name",
                  93);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 93);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 93);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 93);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 93);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 93);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 93);
  sf_mex_assign(&c4_rhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs93), "rhs", "rhs",
                  93);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs93), "lhs", "lhs",
                  93);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 94);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_checkfimathforbinaryops"),
                  "name", "name", 94);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 94);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_checkfimathforbinaryops.m"),
                  "resolved", "resolved", 94);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517568U), "fileTimeLo",
                  "fileTimeLo", 94);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 94);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 94);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 94);
  sf_mex_assign(&c4_rhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs94), "rhs", "rhs",
                  94);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs94), "lhs", "lhs",
                  94);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_checkfimathforbinaryops.m"),
                  "context", "context", 95);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isFimathEqualForCodeGen"),
                  "name", "name", 95);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fimath"),
                  "dominantType", "dominantType", 95);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isFimathEqualForCodeGen.m"),
                  "resolved", "resolved", 95);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1374180272U), "fileTimeLo",
                  "fileTimeLo", 95);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 95);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 95);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 95);
  sf_mex_assign(&c4_rhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs95), "rhs", "rhs",
                  95);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs95), "lhs", "lhs",
                  95);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 96);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("get"), "name", "name", 96);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 96);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 96);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 96);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 96);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 96);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 96);
  sf_mex_assign(&c4_rhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs96), "rhs", "rhs",
                  96);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs96), "lhs", "lhs",
                  96);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 97);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("get"), "name", "name", 97);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fimath"),
                  "dominantType", "dominantType", 97);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fimath/get.m"),
                  "resolved", "resolved", 97);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 97);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 97);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 97);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 97);
  sf_mex_assign(&c4_rhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs97), "rhs", "rhs",
                  97);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs97), "lhs", "lhs",
                  97);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m"),
                  "context", "context", 98);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("strcmpi"), "name", "name", 98);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 98);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "resolved",
                  "resolved", 98);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 98);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 98);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 98);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 98);
  sf_mex_assign(&c4_rhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs98), "rhs", "rhs",
                  98);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs98), "lhs", "lhs",
                  98);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "context",
                  "context", 99);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("lower"), "name", "name", 99);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 99);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/lower.m"), "resolved",
                  "resolved", 99);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 99);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 99);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 99);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 99);
  sf_mex_assign(&c4_rhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs99), "rhs", "rhs",
                  99);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs99), "lhs", "lhs",
                  99);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/lower.m"), "context",
                  "context", 100);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_string_transform"), "name",
                  "name", 100);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 100);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "resolved", "resolved", 100);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 100);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 100);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 100);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 100);
  sf_mex_assign(&c4_rhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs100), "rhs", "rhs",
                  100);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs100), "lhs", "lhs",
                  100);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "context", "context", 101);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_assert_supported_string"),
                  "name", "name", 101);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 101);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m"),
                  "resolved", "resolved", 101);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 101);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 101);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 101);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 101);
  sf_mex_assign(&c4_rhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs101), "rhs", "rhs",
                  101);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs101), "lhs", "lhs",
                  101);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m"),
                  "context", "context", 102);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_charmax"), "name", "name",
                  102);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 102);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"),
                  "resolved", "resolved", 102);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 102);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 102);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 102);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 102);
  sf_mex_assign(&c4_rhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs102), "rhs", "rhs",
                  102);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs102), "lhs", "lhs",
                  102);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "context", "context", 103);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_charmax"), "name", "name",
                  103);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 103);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"),
                  "resolved", "resolved", 103);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 103);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 103);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 103);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 103);
  sf_mex_assign(&c4_rhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs103), "rhs", "rhs",
                  103);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs103), "lhs", "lhs",
                  103);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "context", "context", 104);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("colon"), "name", "name", 104);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 104);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 104);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303188U), "fileTimeLo",
                  "fileTimeLo", 104);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 104);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 104);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 104);
  sf_mex_assign(&c4_rhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs104), "rhs", "rhs",
                  104);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs104), "lhs", "lhs",
                  104);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 105);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("colon"), "name", "name", 105);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 105);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 105);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303188U), "fileTimeLo",
                  "fileTimeLo", 105);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 105);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 105);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 105);
  sf_mex_assign(&c4_rhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs105), "rhs", "rhs",
                  105);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs105), "lhs", "lhs",
                  105);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 106);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 106);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 106);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 106);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 106);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 106);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 106);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 106);
  sf_mex_assign(&c4_rhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs106), "rhs", "rhs",
                  106);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs106), "lhs", "lhs",
                  106);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 107);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 107);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 107);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 107);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 107);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 107);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 107);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 107);
  sf_mex_assign(&c4_rhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs107), "rhs", "rhs",
                  107);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs107), "lhs", "lhs",
                  107);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 108);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("floor"), "name", "name", 108);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 108);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 108);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 108);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 108);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 108);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 108);
  sf_mex_assign(&c4_rhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs108), "rhs", "rhs",
                  108);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs108), "lhs", "lhs",
                  108);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 109);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmin"), "name", "name", 109);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 109);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 109);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 109);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 109);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 109);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 109);
  sf_mex_assign(&c4_rhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs109), "rhs", "rhs",
                  109);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs109), "lhs", "lhs",
                  109);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "context",
                  "context", 110);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 110);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 110);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 110);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1381857500U), "fileTimeLo",
                  "fileTimeLo", 110);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 110);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 110);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 110);
  sf_mex_assign(&c4_rhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs110), "rhs", "rhs",
                  110);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs110), "lhs", "lhs",
                  110);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 111);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmax"), "name", "name", 111);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 111);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 111);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 111);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 111);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 111);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 111);
  sf_mex_assign(&c4_rhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs111), "rhs", "rhs",
                  111);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs111), "lhs", "lhs",
                  111);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 112);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmin"), "name", "name", 112);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 112);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 112);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 112);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 112);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 112);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 112);
  sf_mex_assign(&c4_rhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs112), "rhs", "rhs",
                  112);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs112), "lhs", "lhs",
                  112);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 113);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmax"), "name", "name", 113);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 113);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 113);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 113);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 113);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 113);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 113);
  sf_mex_assign(&c4_rhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs113), "rhs", "rhs",
                  113);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs113), "lhs", "lhs",
                  113);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 114);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  114);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 114);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 114);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 114);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 114);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 114);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 114);
  sf_mex_assign(&c4_rhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs114), "rhs", "rhs",
                  114);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs114), "lhs", "lhs",
                  114);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "context",
                  "context", 115);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.isaUint"),
                  "name", "name", 115);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 115);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/isaUint.p"),
                  "resolved", "resolved", 115);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 115);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 115);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 115);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 115);
  sf_mex_assign(&c4_rhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs115), "rhs", "rhs",
                  115);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs115), "lhs", "lhs",
                  115);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 116);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_unsigned_class"), "name",
                  "name", 116);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 116);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "resolved", "resolved", 116);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 116);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 116);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 116);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 116);
  sf_mex_assign(&c4_rhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs116), "rhs", "rhs",
                  116);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs116), "lhs", "lhs",
                  116);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "context", "context", 117);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.unsignedClass"),
                  "name", "name", 117);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 117);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "resolved", "resolved", 117);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389311522U), "fileTimeLo",
                  "fileTimeLo", 117);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 117);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 117);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 117);
  sf_mex_assign(&c4_rhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs117), "rhs", "rhs",
                  117);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs117), "lhs", "lhs",
                  117);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "context", "context", 118);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 118);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 118);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 118);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1381857500U), "fileTimeLo",
                  "fileTimeLo", 118);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 118);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 118);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 118);
  sf_mex_assign(&c4_rhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs118), "rhs", "rhs",
                  118);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs118), "lhs", "lhs",
                  118);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 119);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 119);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 119);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 119);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 119);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 119);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 119);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 119);
  sf_mex_assign(&c4_rhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs119), "rhs", "rhs",
                  119);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs119), "lhs", "lhs",
                  119);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 120);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmax"), "name", "name", 120);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 120);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 120);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 120);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 120);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 120);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 120);
  sf_mex_assign(&c4_rhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs120), "rhs", "rhs",
                  120);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs120), "lhs", "lhs",
                  120);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 121);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  121);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 121);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 121);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 121);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 121);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 121);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 121);
  sf_mex_assign(&c4_rhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs121), "rhs", "rhs",
                  121);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs121), "lhs", "lhs",
                  121);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 122);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 122);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 122);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 122);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372589616U), "fileTimeLo",
                  "fileTimeLo", 122);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 122);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 122);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 122);
  sf_mex_assign(&c4_rhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs122), "rhs", "rhs",
                  122);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs122), "lhs", "lhs",
                  122);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 123);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 123);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 123);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 123);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372590360U), "fileTimeLo",
                  "fileTimeLo", 123);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 123);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 123);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 123);
  sf_mex_assign(&c4_rhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs123), "rhs", "rhs",
                  123);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs123), "lhs", "lhs",
                  123);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_signed_integer_colon"),
                  "context", "context", 124);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 124);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 124);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 124);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 124);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 124);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 124);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 124);
  sf_mex_assign(&c4_rhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs124), "rhs", "rhs",
                  124);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs124), "lhs", "lhs",
                  124);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 125);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("intmax"), "name", "name", 125);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 125);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 125);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 125);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 125);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 125);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 125);
  sf_mex_assign(&c4_rhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs125), "rhs", "rhs",
                  125);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs125), "lhs", "lhs",
                  125);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "context", "context", 126);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "name", "name", 126);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 126);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m"), "resolved",
                  "resolved", 126);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1319737168U), "fileTimeLo",
                  "fileTimeLo", 126);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 126);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 126);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 126);
  sf_mex_assign(&c4_rhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs126), "rhs", "rhs",
                  126);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs126), "lhs", "lhs",
                  126);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 127);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("getmsb"), "name", "name", 127);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 127);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m"),
                  "resolved", "resolved", 127);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303186U), "fileTimeLo",
                  "fileTimeLo", 127);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 127);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 127);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 127);
  sf_mex_assign(&c4_rhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs127), "rhs", "rhs",
                  127);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs127), "lhs", "lhs",
                  127);
  sf_mex_destroy(&c4_rhs64);
  sf_mex_destroy(&c4_lhs64);
  sf_mex_destroy(&c4_rhs65);
  sf_mex_destroy(&c4_lhs65);
  sf_mex_destroy(&c4_rhs66);
  sf_mex_destroy(&c4_lhs66);
  sf_mex_destroy(&c4_rhs67);
  sf_mex_destroy(&c4_lhs67);
  sf_mex_destroy(&c4_rhs68);
  sf_mex_destroy(&c4_lhs68);
  sf_mex_destroy(&c4_rhs69);
  sf_mex_destroy(&c4_lhs69);
  sf_mex_destroy(&c4_rhs70);
  sf_mex_destroy(&c4_lhs70);
  sf_mex_destroy(&c4_rhs71);
  sf_mex_destroy(&c4_lhs71);
  sf_mex_destroy(&c4_rhs72);
  sf_mex_destroy(&c4_lhs72);
  sf_mex_destroy(&c4_rhs73);
  sf_mex_destroy(&c4_lhs73);
  sf_mex_destroy(&c4_rhs74);
  sf_mex_destroy(&c4_lhs74);
  sf_mex_destroy(&c4_rhs75);
  sf_mex_destroy(&c4_lhs75);
  sf_mex_destroy(&c4_rhs76);
  sf_mex_destroy(&c4_lhs76);
  sf_mex_destroy(&c4_rhs77);
  sf_mex_destroy(&c4_lhs77);
  sf_mex_destroy(&c4_rhs78);
  sf_mex_destroy(&c4_lhs78);
  sf_mex_destroy(&c4_rhs79);
  sf_mex_destroy(&c4_lhs79);
  sf_mex_destroy(&c4_rhs80);
  sf_mex_destroy(&c4_lhs80);
  sf_mex_destroy(&c4_rhs81);
  sf_mex_destroy(&c4_lhs81);
  sf_mex_destroy(&c4_rhs82);
  sf_mex_destroy(&c4_lhs82);
  sf_mex_destroy(&c4_rhs83);
  sf_mex_destroy(&c4_lhs83);
  sf_mex_destroy(&c4_rhs84);
  sf_mex_destroy(&c4_lhs84);
  sf_mex_destroy(&c4_rhs85);
  sf_mex_destroy(&c4_lhs85);
  sf_mex_destroy(&c4_rhs86);
  sf_mex_destroy(&c4_lhs86);
  sf_mex_destroy(&c4_rhs87);
  sf_mex_destroy(&c4_lhs87);
  sf_mex_destroy(&c4_rhs88);
  sf_mex_destroy(&c4_lhs88);
  sf_mex_destroy(&c4_rhs89);
  sf_mex_destroy(&c4_lhs89);
  sf_mex_destroy(&c4_rhs90);
  sf_mex_destroy(&c4_lhs90);
  sf_mex_destroy(&c4_rhs91);
  sf_mex_destroy(&c4_lhs91);
  sf_mex_destroy(&c4_rhs92);
  sf_mex_destroy(&c4_lhs92);
  sf_mex_destroy(&c4_rhs93);
  sf_mex_destroy(&c4_lhs93);
  sf_mex_destroy(&c4_rhs94);
  sf_mex_destroy(&c4_lhs94);
  sf_mex_destroy(&c4_rhs95);
  sf_mex_destroy(&c4_lhs95);
  sf_mex_destroy(&c4_rhs96);
  sf_mex_destroy(&c4_lhs96);
  sf_mex_destroy(&c4_rhs97);
  sf_mex_destroy(&c4_lhs97);
  sf_mex_destroy(&c4_rhs98);
  sf_mex_destroy(&c4_lhs98);
  sf_mex_destroy(&c4_rhs99);
  sf_mex_destroy(&c4_lhs99);
  sf_mex_destroy(&c4_rhs100);
  sf_mex_destroy(&c4_lhs100);
  sf_mex_destroy(&c4_rhs101);
  sf_mex_destroy(&c4_lhs101);
  sf_mex_destroy(&c4_rhs102);
  sf_mex_destroy(&c4_lhs102);
  sf_mex_destroy(&c4_rhs103);
  sf_mex_destroy(&c4_lhs103);
  sf_mex_destroy(&c4_rhs104);
  sf_mex_destroy(&c4_lhs104);
  sf_mex_destroy(&c4_rhs105);
  sf_mex_destroy(&c4_lhs105);
  sf_mex_destroy(&c4_rhs106);
  sf_mex_destroy(&c4_lhs106);
  sf_mex_destroy(&c4_rhs107);
  sf_mex_destroy(&c4_lhs107);
  sf_mex_destroy(&c4_rhs108);
  sf_mex_destroy(&c4_lhs108);
  sf_mex_destroy(&c4_rhs109);
  sf_mex_destroy(&c4_lhs109);
  sf_mex_destroy(&c4_rhs110);
  sf_mex_destroy(&c4_lhs110);
  sf_mex_destroy(&c4_rhs111);
  sf_mex_destroy(&c4_lhs111);
  sf_mex_destroy(&c4_rhs112);
  sf_mex_destroy(&c4_lhs112);
  sf_mex_destroy(&c4_rhs113);
  sf_mex_destroy(&c4_lhs113);
  sf_mex_destroy(&c4_rhs114);
  sf_mex_destroy(&c4_lhs114);
  sf_mex_destroy(&c4_rhs115);
  sf_mex_destroy(&c4_lhs115);
  sf_mex_destroy(&c4_rhs116);
  sf_mex_destroy(&c4_lhs116);
  sf_mex_destroy(&c4_rhs117);
  sf_mex_destroy(&c4_lhs117);
  sf_mex_destroy(&c4_rhs118);
  sf_mex_destroy(&c4_lhs118);
  sf_mex_destroy(&c4_rhs119);
  sf_mex_destroy(&c4_lhs119);
  sf_mex_destroy(&c4_rhs120);
  sf_mex_destroy(&c4_lhs120);
  sf_mex_destroy(&c4_rhs121);
  sf_mex_destroy(&c4_lhs121);
  sf_mex_destroy(&c4_rhs122);
  sf_mex_destroy(&c4_lhs122);
  sf_mex_destroy(&c4_rhs123);
  sf_mex_destroy(&c4_lhs123);
  sf_mex_destroy(&c4_rhs124);
  sf_mex_destroy(&c4_lhs124);
  sf_mex_destroy(&c4_rhs125);
  sf_mex_destroy(&c4_lhs125);
  sf_mex_destroy(&c4_rhs126);
  sf_mex_destroy(&c4_lhs126);
  sf_mex_destroy(&c4_rhs127);
  sf_mex_destroy(&c4_lhs127);
}

static void c4_c_info_helper(const mxArray **c4_info)
{
  const mxArray *c4_rhs128 = NULL;
  const mxArray *c4_lhs128 = NULL;
  const mxArray *c4_rhs129 = NULL;
  const mxArray *c4_lhs129 = NULL;
  const mxArray *c4_rhs130 = NULL;
  const mxArray *c4_lhs130 = NULL;
  const mxArray *c4_rhs131 = NULL;
  const mxArray *c4_lhs131 = NULL;
  const mxArray *c4_rhs132 = NULL;
  const mxArray *c4_lhs132 = NULL;
  const mxArray *c4_rhs133 = NULL;
  const mxArray *c4_lhs133 = NULL;
  const mxArray *c4_rhs134 = NULL;
  const mxArray *c4_lhs134 = NULL;
  const mxArray *c4_rhs135 = NULL;
  const mxArray *c4_lhs135 = NULL;
  const mxArray *c4_rhs136 = NULL;
  const mxArray *c4_lhs136 = NULL;
  const mxArray *c4_rhs137 = NULL;
  const mxArray *c4_lhs137 = NULL;
  const mxArray *c4_rhs138 = NULL;
  const mxArray *c4_lhs138 = NULL;
  const mxArray *c4_rhs139 = NULL;
  const mxArray *c4_lhs139 = NULL;
  const mxArray *c4_rhs140 = NULL;
  const mxArray *c4_lhs140 = NULL;
  const mxArray *c4_rhs141 = NULL;
  const mxArray *c4_lhs141 = NULL;
  const mxArray *c4_rhs142 = NULL;
  const mxArray *c4_lhs142 = NULL;
  const mxArray *c4_rhs143 = NULL;
  const mxArray *c4_lhs143 = NULL;
  const mxArray *c4_rhs144 = NULL;
  const mxArray *c4_lhs144 = NULL;
  const mxArray *c4_rhs145 = NULL;
  const mxArray *c4_lhs145 = NULL;
  const mxArray *c4_rhs146 = NULL;
  const mxArray *c4_lhs146 = NULL;
  const mxArray *c4_rhs147 = NULL;
  const mxArray *c4_lhs147 = NULL;
  const mxArray *c4_rhs148 = NULL;
  const mxArray *c4_lhs148 = NULL;
  const mxArray *c4_rhs149 = NULL;
  const mxArray *c4_lhs149 = NULL;
  const mxArray *c4_rhs150 = NULL;
  const mxArray *c4_lhs150 = NULL;
  const mxArray *c4_rhs151 = NULL;
  const mxArray *c4_lhs151 = NULL;
  const mxArray *c4_rhs152 = NULL;
  const mxArray *c4_lhs152 = NULL;
  const mxArray *c4_rhs153 = NULL;
  const mxArray *c4_lhs153 = NULL;
  const mxArray *c4_rhs154 = NULL;
  const mxArray *c4_lhs154 = NULL;
  const mxArray *c4_rhs155 = NULL;
  const mxArray *c4_lhs155 = NULL;
  const mxArray *c4_rhs156 = NULL;
  const mxArray *c4_lhs156 = NULL;
  const mxArray *c4_rhs157 = NULL;
  const mxArray *c4_lhs157 = NULL;
  const mxArray *c4_rhs158 = NULL;
  const mxArray *c4_lhs158 = NULL;
  const mxArray *c4_rhs159 = NULL;
  const mxArray *c4_lhs159 = NULL;
  const mxArray *c4_rhs160 = NULL;
  const mxArray *c4_lhs160 = NULL;
  const mxArray *c4_rhs161 = NULL;
  const mxArray *c4_lhs161 = NULL;
  const mxArray *c4_rhs162 = NULL;
  const mxArray *c4_lhs162 = NULL;
  const mxArray *c4_rhs163 = NULL;
  const mxArray *c4_lhs163 = NULL;
  const mxArray *c4_rhs164 = NULL;
  const mxArray *c4_lhs164 = NULL;
  const mxArray *c4_rhs165 = NULL;
  const mxArray *c4_lhs165 = NULL;
  const mxArray *c4_rhs166 = NULL;
  const mxArray *c4_lhs166 = NULL;
  const mxArray *c4_rhs167 = NULL;
  const mxArray *c4_lhs167 = NULL;
  const mxArray *c4_rhs168 = NULL;
  const mxArray *c4_lhs168 = NULL;
  const mxArray *c4_rhs169 = NULL;
  const mxArray *c4_lhs169 = NULL;
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m"),
                  "context", "context", 128);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfixed"), "name", "name", 128);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 128);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 128);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 128);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 128);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 128);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 128);
  sf_mex_assign(&c4_rhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs128), "rhs", "rhs",
                  128);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs128), "lhs", "lhs",
                  128);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m"),
                  "context", "context", 129);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_bitop_index_checks"),
                  "name", "name", 129);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 129);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_bitop_index_checks.m"),
                  "resolved", "resolved", 129);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363717460U), "fileTimeLo",
                  "fileTimeLo", 129);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 129);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 129);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 129);
  sf_mex_assign(&c4_rhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs129), "rhs", "rhs",
                  129);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs129), "lhs", "lhs",
                  129);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_bitop_index_checks.m"),
                  "context", "context", 130);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 130);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 130);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 130);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 130);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 130);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 130);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 130);
  sf_mex_assign(&c4_rhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs130), "rhs", "rhs",
                  130);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs130), "lhs", "lhs",
                  130);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_bitop_index_checks.m"),
                  "context", "context", 131);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_isslopebiasscaled"),
                  "name", "name", 131);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 131);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "resolved", "resolved", 131);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 131);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 131);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 131);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 131);
  sf_mex_assign(&c4_rhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs131), "rhs", "rhs",
                  131);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs131), "lhs", "lhs",
                  131);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_bitop_index_checks.m"),
                  "context", "context", 132);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 132);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 132);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 132);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 132);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 132);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 132);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 132);
  sf_mex_assign(&c4_rhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs132), "rhs", "rhs",
                  132);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs132), "lhs", "lhs",
                  132);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_bitop_index_checks.m"),
                  "context", "context", 133);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 133);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 133);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 133);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 133);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 133);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 133);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 133);
  sf_mex_assign(&c4_rhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs133), "rhs", "rhs",
                  133);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs133), "lhs", "lhs",
                  133);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m"),
                  "context", "context", 134);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("numerictype"), "name", "name",
                  134);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 134);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m"), "resolved",
                  "resolved", 134);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1348199118U), "fileTimeLo",
                  "fileTimeLo", 134);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 134);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 134);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 134);
  sf_mex_assign(&c4_rhs134, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs134, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs134), "rhs", "rhs",
                  134);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs134), "lhs", "lhs",
                  134);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m"),
                  "context", "context", 135);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("fi_impl"), "name", "name", 135);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 135);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "resolved",
                  "resolved", 135);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1389302372U), "fileTimeLo",
                  "fileTimeLo", 135);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 135);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 135);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 135);
  sf_mex_assign(&c4_rhs135, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs135, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs135), "rhs", "rhs",
                  135);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs135), "lhs", "lhs",
                  135);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 136);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 136);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 136);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 136);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 136);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 136);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 136);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 136);
  sf_mex_assign(&c4_rhs136, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs136, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs136), "rhs", "rhs",
                  136);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs136), "lhs", "lhs",
                  136);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 137);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_fi_checkforconst"), "name",
                  "name", 137);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 137);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforconst.m"),
                  "resolved", "resolved", 137);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517552U), "fileTimeLo",
                  "fileTimeLo", 137);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 137);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 137);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 137);
  sf_mex_assign(&c4_rhs137, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs137, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs137), "rhs", "rhs",
                  137);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs137), "lhs", "lhs",
                  137);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 138);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eq"), "name", "name", 138);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 138);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "resolved", "resolved", 138);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517574U), "fileTimeLo",
                  "fileTimeLo", 138);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 138);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 138);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 138);
  sf_mex_assign(&c4_rhs138, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs138, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs138), "rhs", "rhs",
                  138);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs138), "lhs", "lhs",
                  138);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "context", "context", 139);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 139);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 139);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 139);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 139);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 139);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 139);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 139);
  sf_mex_assign(&c4_rhs139, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs139, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs139), "rhs", "rhs",
                  139);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs139), "lhs", "lhs",
                  139);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "context", "context", 140);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 140);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 140);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 140);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 140);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 140);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 140);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 140);
  sf_mex_assign(&c4_rhs140, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs140, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs140), "rhs", "rhs",
                  140);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs140), "lhs", "lhs",
                  140);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "context", "context", 141);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isscaledtype"), "name", "name",
                  141);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 141);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 141);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 141);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 141);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 141);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 141);
  sf_mex_assign(&c4_rhs141, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs141, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs141), "rhs", "rhs",
                  141);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs141), "lhs", "lhs",
                  141);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "context", "context", 142);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_check_same_bias"), "name",
                  "name", 142);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 142);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_check_same_bias.m"),
                  "resolved", "resolved", 142);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517568U), "fileTimeLo",
                  "fileTimeLo", 142);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 142);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 142);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 142);
  sf_mex_assign(&c4_rhs142, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs142, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs142), "rhs", "rhs",
                  142);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs142), "lhs", "lhs",
                  142);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_check_same_bias.m"),
                  "context", "context", 143);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("get"), "name", "name", 143);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 143);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 143);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 143);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 143);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 143);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 143);
  sf_mex_assign(&c4_rhs143, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs143, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs143), "rhs", "rhs",
                  143);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs143), "lhs", "lhs",
                  143);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "context", "context", 144);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_make_same_complexity"),
                  "name", "name", 144);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 144);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_make_same_complexity.m"),
                  "resolved", "resolved", 144);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 144);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 144);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 144);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 144);
  sf_mex_assign(&c4_rhs144, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs144, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs144), "rhs", "rhs",
                  144);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs144), "lhs", "lhs",
                  144);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 145);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("ne"), "name", "name", 145);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 145);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "resolved", "resolved", 145);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517584U), "fileTimeLo",
                  "fileTimeLo", 145);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 145);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 145);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 145);
  sf_mex_assign(&c4_rhs145, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs145, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs145), "rhs", "rhs",
                  145);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs145), "lhs", "lhs",
                  145);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 146);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 146);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 146);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 146);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 146);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 146);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 146);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 146);
  sf_mex_assign(&c4_rhs146, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs146, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs146), "rhs", "rhs",
                  146);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs146), "lhs", "lhs",
                  146);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 147);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 147);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 147);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 147);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 147);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 147);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 147);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 147);
  sf_mex_assign(&c4_rhs147, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs147, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs147), "rhs", "rhs",
                  147);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs147), "lhs", "lhs",
                  147);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 148);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isscaledtype"), "name", "name",
                  148);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 148);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 148);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 148);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 148);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 148);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 148);
  sf_mex_assign(&c4_rhs148, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs148, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs148), "rhs", "rhs",
                  148);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs148), "lhs", "lhs",
                  148);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 149);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_check_same_bias"), "name",
                  "name", 149);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 149);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_check_same_bias.m"),
                  "resolved", "resolved", 149);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517568U), "fileTimeLo",
                  "fileTimeLo", 149);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 149);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 149);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 149);
  sf_mex_assign(&c4_rhs149, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs149, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs149), "rhs", "rhs",
                  149);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs149), "lhs", "lhs",
                  149);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 150);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_make_same_complexity"),
                  "name", "name", 150);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 150);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_make_same_complexity.m"),
                  "resolved", "resolved", 150);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 150);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 150);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 150);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 150);
  sf_mex_assign(&c4_rhs150, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs150, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs150), "rhs", "rhs",
                  150);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs150), "lhs", "lhs",
                  150);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 151);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 151);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 151);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 151);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 151);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 151);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 151);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 151);
  sf_mex_assign(&c4_rhs151, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs151, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs151), "rhs", "rhs",
                  151);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs151), "lhs", "lhs",
                  151);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 152);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_fi_checkforntype"), "name",
                  "name", 152);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 152);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m"),
                  "resolved", "resolved", 152);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1381857498U), "fileTimeLo",
                  "fileTimeLo", 152);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 152);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 152);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 152);
  sf_mex_assign(&c4_rhs152, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs152, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs152), "rhs", "rhs",
                  152);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs152), "lhs", "lhs",
                  152);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 153);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("bitand"), "name", "name", 153);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 153);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "resolved", "resolved", 153);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 153);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 153);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 153);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 153);
  sf_mex_assign(&c4_rhs153, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs153, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs153), "rhs", "rhs",
                  153);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs153), "lhs", "lhs",
                  153);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "context", "context", 154);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 154);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 154);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 154);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 154);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 154);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 154);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 154);
  sf_mex_assign(&c4_rhs154, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs154, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs154), "rhs", "rhs",
                  154);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs154), "lhs", "lhs",
                  154);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "context", "context", 155);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfixed"), "name", "name", 155);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 155);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 155);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 155);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 155);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 155);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 155);
  sf_mex_assign(&c4_rhs155, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs155, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs155), "rhs", "rhs",
                  155);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs155), "lhs", "lhs",
                  155);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "context", "context", 156);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_isslopebiasscaled"),
                  "name", "name", 156);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 156);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "resolved", "resolved", 156);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 156);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 156);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 156);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 156);
  sf_mex_assign(&c4_rhs156, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs156, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs156), "rhs", "rhs",
                  156);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs156), "lhs", "lhs",
                  156);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "context", "context", 157);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isequal"), "name", "name", 157);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 157);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/isequal.m"),
                  "resolved", "resolved", 157);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517540U), "fileTimeLo",
                  "fileTimeLo", 157);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 157);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 157);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 157);
  sf_mex_assign(&c4_rhs157, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs157, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs157), "rhs", "rhs",
                  157);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs157), "lhs", "lhs",
                  157);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "context", "context", 158);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_checkfimathforbinaryops"),
                  "name", "name", 158);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 158);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_checkfimathforbinaryops.m"),
                  "resolved", "resolved", 158);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517568U), "fileTimeLo",
                  "fileTimeLo", 158);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 158);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 158);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 158);
  sf_mex_assign(&c4_rhs158, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs158, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs158), "rhs", "rhs",
                  158);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs158), "lhs", "lhs",
                  158);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "context", "context", 159);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 159);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 159);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 159);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 159);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 159);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 159);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 159);
  sf_mex_assign(&c4_rhs159, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs159, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs159), "rhs", "rhs",
                  159);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs159), "lhs", "lhs",
                  159);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(""), "context", "context", 160);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("all"), "name", "name", 160);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 160);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/all.m"),
                  "resolved", "resolved", 160);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517552U), "fileTimeLo",
                  "fileTimeLo", 160);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 160);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 160);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 160);
  sf_mex_assign(&c4_rhs160, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs160, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs160), "rhs", "rhs",
                  160);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs160), "lhs", "lhs",
                  160);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/all.m"),
                  "context", "context", 161);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_all_or_any"), "name",
                  "name", 161);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 161);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m"),
                  "resolved", "resolved", 161);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372589616U), "fileTimeLo",
                  "fileTimeLo", 161);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 161);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 161);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 161);
  sf_mex_assign(&c4_rhs161, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs161, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs161), "rhs", "rhs",
                  161);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs161), "lhs", "lhs",
                  161);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m"), "context",
                  "context", 162);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("coder.internal.allOrAny"),
                  "name", "name", 162);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 162);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "resolved", "resolved", 162);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372590358U), "fileTimeLo",
                  "fileTimeLo", 162);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 162);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 162);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 162);
  sf_mex_assign(&c4_rhs162, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs162, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs162), "rhs", "rhs",
                  162);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs162), "lhs", "lhs",
                  162);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 163);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isequal"), "name", "name", 163);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 163);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 163);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286825958U), "fileTimeLo",
                  "fileTimeLo", 163);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 163);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 163);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 163);
  sf_mex_assign(&c4_rhs163, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs163, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs163), "rhs", "rhs",
                  163);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs163), "lhs", "lhs",
                  163);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "context",
                  "context", 164);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_isequal_core"), "name",
                  "name", 164);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 164);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m"),
                  "resolved", "resolved", 164);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1286825986U), "fileTimeLo",
                  "fileTimeLo", 164);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 164);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 164);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 164);
  sf_mex_assign(&c4_rhs164, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs164, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs164), "rhs", "rhs",
                  164);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs164), "lhs", "lhs",
                  164);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 165);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "coder.internal.constNonSingletonDim"), "name", "name", 165);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 165);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/constNonSingletonDim.m"),
                  "resolved", "resolved", 165);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372590360U), "fileTimeLo",
                  "fileTimeLo", 165);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 165);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 165);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 165);
  sf_mex_assign(&c4_rhs165, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs165, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs165), "rhs", "rhs",
                  165);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs165), "lhs", "lhs",
                  165);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 166);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("ne"), "name", "name", 166);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 166);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "resolved", "resolved", 166);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517584U), "fileTimeLo",
                  "fileTimeLo", 166);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 166);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 166);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 166);
  sf_mex_assign(&c4_rhs166, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs166, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs166), "rhs", "rhs",
                  166);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs166), "lhs", "lhs",
                  166);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 167);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("isfi"), "name", "name", 167);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 167);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 167);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 167);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 167);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 167);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 167);
  sf_mex_assign(&c4_rhs167, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs167, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs167), "rhs", "rhs",
                  167);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs167), "lhs", "lhs",
                  167);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 168);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("eml_type_relop_const"), "name",
                  "name", 168);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 168);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m"),
                  "resolved", "resolved", 168);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1346517574U), "fileTimeLo",
                  "fileTimeLo", 168);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 168);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 168);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 168);
  sf_mex_assign(&c4_rhs168, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs168, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs168), "rhs", "rhs",
                  168);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs168), "lhs", "lhs",
                  168);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m"),
                  "context", "context", 169);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("all"), "name", "name", 169);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 169);
  sf_mex_addfield(*c4_info, c4_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "resolved",
                  "resolved", 169);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(1372589614U), "fileTimeLo",
                  "fileTimeLo", 169);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 169);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 169);
  sf_mex_addfield(*c4_info, c4_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 169);
  sf_mex_assign(&c4_rhs169, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c4_lhs169, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_rhs169), "rhs", "rhs",
                  169);
  sf_mex_addfield(*c4_info, sf_mex_duplicatearraysafe(&c4_lhs169), "lhs", "lhs",
                  169);
  sf_mex_destroy(&c4_rhs128);
  sf_mex_destroy(&c4_lhs128);
  sf_mex_destroy(&c4_rhs129);
  sf_mex_destroy(&c4_lhs129);
  sf_mex_destroy(&c4_rhs130);
  sf_mex_destroy(&c4_lhs130);
  sf_mex_destroy(&c4_rhs131);
  sf_mex_destroy(&c4_lhs131);
  sf_mex_destroy(&c4_rhs132);
  sf_mex_destroy(&c4_lhs132);
  sf_mex_destroy(&c4_rhs133);
  sf_mex_destroy(&c4_lhs133);
  sf_mex_destroy(&c4_rhs134);
  sf_mex_destroy(&c4_lhs134);
  sf_mex_destroy(&c4_rhs135);
  sf_mex_destroy(&c4_lhs135);
  sf_mex_destroy(&c4_rhs136);
  sf_mex_destroy(&c4_lhs136);
  sf_mex_destroy(&c4_rhs137);
  sf_mex_destroy(&c4_lhs137);
  sf_mex_destroy(&c4_rhs138);
  sf_mex_destroy(&c4_lhs138);
  sf_mex_destroy(&c4_rhs139);
  sf_mex_destroy(&c4_lhs139);
  sf_mex_destroy(&c4_rhs140);
  sf_mex_destroy(&c4_lhs140);
  sf_mex_destroy(&c4_rhs141);
  sf_mex_destroy(&c4_lhs141);
  sf_mex_destroy(&c4_rhs142);
  sf_mex_destroy(&c4_lhs142);
  sf_mex_destroy(&c4_rhs143);
  sf_mex_destroy(&c4_lhs143);
  sf_mex_destroy(&c4_rhs144);
  sf_mex_destroy(&c4_lhs144);
  sf_mex_destroy(&c4_rhs145);
  sf_mex_destroy(&c4_lhs145);
  sf_mex_destroy(&c4_rhs146);
  sf_mex_destroy(&c4_lhs146);
  sf_mex_destroy(&c4_rhs147);
  sf_mex_destroy(&c4_lhs147);
  sf_mex_destroy(&c4_rhs148);
  sf_mex_destroy(&c4_lhs148);
  sf_mex_destroy(&c4_rhs149);
  sf_mex_destroy(&c4_lhs149);
  sf_mex_destroy(&c4_rhs150);
  sf_mex_destroy(&c4_lhs150);
  sf_mex_destroy(&c4_rhs151);
  sf_mex_destroy(&c4_lhs151);
  sf_mex_destroy(&c4_rhs152);
  sf_mex_destroy(&c4_lhs152);
  sf_mex_destroy(&c4_rhs153);
  sf_mex_destroy(&c4_lhs153);
  sf_mex_destroy(&c4_rhs154);
  sf_mex_destroy(&c4_lhs154);
  sf_mex_destroy(&c4_rhs155);
  sf_mex_destroy(&c4_lhs155);
  sf_mex_destroy(&c4_rhs156);
  sf_mex_destroy(&c4_lhs156);
  sf_mex_destroy(&c4_rhs157);
  sf_mex_destroy(&c4_lhs157);
  sf_mex_destroy(&c4_rhs158);
  sf_mex_destroy(&c4_lhs158);
  sf_mex_destroy(&c4_rhs159);
  sf_mex_destroy(&c4_lhs159);
  sf_mex_destroy(&c4_rhs160);
  sf_mex_destroy(&c4_lhs160);
  sf_mex_destroy(&c4_rhs161);
  sf_mex_destroy(&c4_lhs161);
  sf_mex_destroy(&c4_rhs162);
  sf_mex_destroy(&c4_lhs162);
  sf_mex_destroy(&c4_rhs163);
  sf_mex_destroy(&c4_lhs163);
  sf_mex_destroy(&c4_rhs164);
  sf_mex_destroy(&c4_lhs164);
  sf_mex_destroy(&c4_rhs165);
  sf_mex_destroy(&c4_lhs165);
  sf_mex_destroy(&c4_rhs166);
  sf_mex_destroy(&c4_lhs166);
  sf_mex_destroy(&c4_rhs167);
  sf_mex_destroy(&c4_lhs167);
  sf_mex_destroy(&c4_rhs168);
  sf_mex_destroy(&c4_lhs168);
  sf_mex_destroy(&c4_rhs169);
  sf_mex_destroy(&c4_lhs169);
}

static void c4_eml_fi_checkforconst(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static uint8_T c4_uint8(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c4_A)
{
  uint8_T c4_xfi;
  const mxArray *c4_propValScalar = NULL;
  const mxArray *c4_pseudoData = NULL;
  const mxArray *c4_codeGenSupportFlag = NULL;
  (void)chartInstance;
  c4_xfi = c4_A;
  sf_mex_destroy(&c4_propValScalar);
  sf_mex_destroy(&c4_pseudoData);
  sf_mex_destroy(&c4_codeGenSupportFlag);
  return c4_xfi;
}

static void c4_b_eml_fi_checkforconst(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static uint8_T c4_bitcmp(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c4_a)
{
  uint8_T c4_c_r;
  (void)chartInstance;
  c4_c_r = (uint8_T)((uint8_T)~c4_a & 1U);
  return c4_c_r;
}

static int8_T c4_b_bitcmp(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_a)
{
  int8_T c4_c_r;
  (void)chartInstance;
  c4_c_r = (int8_T)~c4_a;
  return c4_c_r;
}

static void c4_sub_w_borrow(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_u1, int8_T c4_u2, uint8_T c4_b_in, int8_T *c4_diff, uint8_T
  *c4_carry, uint8_T *c4_overflow)
{
  uint32_T c4_debug_family_var_map[8];
  real_T c4_nargin = 3.0;
  real_T c4_nargout = 3.0;
  uint8_T c4_b_overflow;
  uint8_T c4_b_carry;
  int8_T c4_b_diff;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 8U, 8U, c4_c_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 0U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 1U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_u1, 2U, c4_c_sf_marshallOut,
    c4_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_u2, 3U, c4_c_sf_marshallOut,
    c4_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_in, 4U, c4_h_sf_marshallOut,
    c4_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_diff, 5U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_carry, 6U, c4_f_sf_marshallOut,
    c4_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_overflow, 7U, c4_f_sf_marshallOut,
    c4_d_sf_marshallIn);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 70);
  c4_sum_w_carry(chartInstance, c4_u1, c4_b_bitcmp(chartInstance, c4_u2),
                 c4_bitcmp(chartInstance, c4_b_in), &c4_b_diff, &c4_b_carry,
                 &c4_b_overflow);
  *c4_diff = c4_b_diff;
  *c4_carry = c4_b_carry;
  *c4_overflow = c4_b_overflow;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -70);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c4_sum_w_carry(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_u1, int8_T c4_u2, uint8_T c4_c_in, int8_T *c4_sum, uint8_T *c4_carry,
  uint8_T *c4_overflow)
{
  uint32_T c4_debug_family_var_map[14];
  const mxArray *c4_hdl_fm = NULL;
  int16_T c4_temp_u1;
  int16_T c4_temp_u2;
  int16_T c4_temp_sum;
  uint8_T c4_sign_bit;
  uint8_T c4_overflow_int;
  real_T c4_nargin = 3.0;
  real_T c4_nargout = 3.0;
  const mxArray *c4_T = NULL;
  const mxArray *c4_F = NULL;
  const mxArray *c4_val = NULL;
  const mxArray *c4_unusedU2 = NULL;
  const mxArray *c4_unusedU3 = NULL;
  const mxArray *c4_isfimathlocal = NULL;
  uint16_T c4_varargin_1;
  uint16_T c4_b_varargin_1;
  uint16_T c4_var1;
  int16_T c4_i3;
  const mxArray *c4_b_T = NULL;
  const mxArray *c4_b_F = NULL;
  const mxArray *c4_b_val = NULL;
  const mxArray *c4_isautoscaled = NULL;
  const mxArray *c4_pvpairsetdata = NULL;
  const mxArray *c4_b_isfimathlocal = NULL;
  const mxArray *c4_c_T = NULL;
  const mxArray *c4_c_F = NULL;
  const mxArray *c4_c_val = NULL;
  const mxArray *c4_b_unusedU2 = NULL;
  const mxArray *c4_b_unusedU3 = NULL;
  const mxArray *c4_c_isfimathlocal = NULL;
  uint16_T c4_c_varargin_1;
  uint16_T c4_d_varargin_1;
  uint16_T c4_b_var1;
  int16_T c4_i4;
  const mxArray *c4_d_T = NULL;
  const mxArray *c4_d_F = NULL;
  const mxArray *c4_d_val = NULL;
  const mxArray *c4_b_isautoscaled = NULL;
  const mxArray *c4_b_pvpairsetdata = NULL;
  const mxArray *c4_d_isfimathlocal = NULL;
  int16_T c4_e_varargin_1;
  int16_T c4_f_varargin_1;
  int16_T c4_c_var1;
  int16_T c4_i5;
  const mxArray *c4_e_T = NULL;
  const mxArray *c4_e_F = NULL;
  const mxArray *c4_e_val = NULL;
  const mxArray *c4_c_isautoscaled = NULL;
  const mxArray *c4_c_pvpairsetdata = NULL;
  const mxArray *c4_e_isfimathlocal = NULL;
  int16_T c4_a;
  const mxArray *c4_f_T = NULL;
  const mxArray *c4_f_F = NULL;
  const mxArray *c4_f_val = NULL;
  const mxArray *c4_c_unusedU2 = NULL;
  const mxArray *c4_c_unusedU3 = NULL;
  const mxArray *c4_f_isfimathlocal = NULL;
  int16_T c4_i6;
  int16_T c4_i7;
  int16_T c4_i8;
  int16_T c4_i9;
  uint8_T c4_slice_temp;
  int16_T c4_g_varargin_1;
  int16_T c4_h_varargin_1;
  int16_T c4_d_var1;
  const mxArray *c4_g_T = NULL;
  const mxArray *c4_g_F = NULL;
  const mxArray *c4_g_val = NULL;
  const mxArray *c4_d_isautoscaled = NULL;
  const mxArray *c4_d_pvpairsetdata = NULL;
  const mxArray *c4_g_isfimathlocal = NULL;
  int8_T c4_b_a;
  const mxArray *c4_h_T = NULL;
  const mxArray *c4_h_F = NULL;
  const mxArray *c4_h_val = NULL;
  const mxArray *c4_d_unusedU2 = NULL;
  const mxArray *c4_d_unusedU3 = NULL;
  const mxArray *c4_h_isfimathlocal = NULL;
  uint8_T c4_b_slice_temp;
  int8_T c4_c_a;
  const mxArray *c4_i_T = NULL;
  const mxArray *c4_i_F = NULL;
  const mxArray *c4_i_val = NULL;
  const mxArray *c4_e_unusedU2 = NULL;
  const mxArray *c4_e_unusedU3 = NULL;
  const mxArray *c4_i_isfimathlocal = NULL;
  uint8_T c4_c_slice_temp;
  uint8_T c4_c;
  int8_T c4_d_a;
  const mxArray *c4_j_T = NULL;
  const mxArray *c4_j_F = NULL;
  const mxArray *c4_j_val = NULL;
  const mxArray *c4_f_unusedU2 = NULL;
  const mxArray *c4_f_unusedU3 = NULL;
  const mxArray *c4_j_isfimathlocal = NULL;
  uint8_T c4_d_slice_temp;
  uint8_T c4_b_c;
  uint8_T c4_a0;
  uint8_T c4_b0;
  uint8_T c4_e_a;
  uint8_T c4_b;
  uint8_T c4_b_a0;
  uint8_T c4_b_b0;
  uint8_T c4_a1;
  uint8_T c4_b1;
  uint8_T c4_b_a1;
  uint8_T c4_b_b1;
  boolean_T c4_c_c;
  int8_T c4_f_a;
  int8_T c4_c_a1;
  uint8_T c4_e_slice_temp;
  uint8_T c4_d_c;
  uint8_T c4_c_a0;
  uint8_T c4_c_b0;
  uint8_T c4_g_a;
  uint8_T c4_b_b;
  uint8_T c4_d_a0;
  uint8_T c4_d_b0;
  uint8_T c4_d_a1;
  uint8_T c4_c_b1;
  uint8_T c4_e_a1;
  uint8_T c4_d_b1;
  boolean_T c4_e_c;
  boolean_T c4_e_b0;
  uint8_T c4_i_varargin_1;
  uint8_T c4_j_varargin_1;
  uint8_T c4_e_var1;
  const mxArray *c4_k_T = NULL;
  const mxArray *c4_k_F = NULL;
  const mxArray *c4_k_val = NULL;
  const mxArray *c4_e_isautoscaled = NULL;
  const mxArray *c4_e_pvpairsetdata = NULL;
  const mxArray *c4_k_isfimathlocal = NULL;
  boolean_T guard1 = false;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 14U, 14U, c4_b_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_hdl_fm, 0U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_temp_u1, 1U, c4_j_sf_marshallOut,
    c4_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_temp_u2, 2U, c4_j_sf_marshallOut,
    c4_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_temp_sum, 3U, c4_j_sf_marshallOut,
    c4_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_sign_bit, 4U, c4_f_sf_marshallOut,
    c4_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_overflow_int, 5U, c4_g_sf_marshallOut,
    c4_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 6U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 7U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_u1, 8U, c4_c_sf_marshallOut,
    c4_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_u2, 9U, c4_c_sf_marshallOut,
    c4_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_c_in, 10U, c4_h_sf_marshallOut,
    c4_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_sum, 11U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_carry, 12U, c4_f_sf_marshallOut,
    c4_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_overflow, 13U, c4_f_sf_marshallOut,
    c4_d_sf_marshallIn);
  CV_EML_FCN(0, 2);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 79);
  c4_hdl_fm = c4_eml_mx;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 87);
  c4_b_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c4_T);
  sf_mex_destroy(&c4_F);
  sf_mex_destroy(&c4_val);
  sf_mex_destroy(&c4_unusedU2);
  sf_mex_destroy(&c4_unusedU3);
  sf_mex_destroy(&c4_isfimathlocal);
  c4_varargin_1 = c4_bitconcat(chartInstance, 0U, c4_u1);
  c4_b_varargin_1 = c4_varargin_1;
  c4_c_eml_fi_checkforconst(chartInstance);
  c4_var1 = c4_b_varargin_1;
  c4_i3 = (int16_T)c4_var1;
  if ((int16_T)(c4_i3 & 256) != 0) {
    c4_temp_u1 = (int16_T)(c4_i3 | -256);
  } else {
    c4_temp_u1 = (int16_T)(c4_i3 & 255);
  }

  sf_mex_destroy(&c4_b_T);
  sf_mex_destroy(&c4_b_F);
  sf_mex_destroy(&c4_b_val);
  sf_mex_destroy(&c4_isautoscaled);
  sf_mex_destroy(&c4_pvpairsetdata);
  sf_mex_destroy(&c4_b_isfimathlocal);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 90);
  c4_b_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c4_c_T);
  sf_mex_destroy(&c4_c_F);
  sf_mex_destroy(&c4_c_val);
  sf_mex_destroy(&c4_b_unusedU2);
  sf_mex_destroy(&c4_b_unusedU3);
  sf_mex_destroy(&c4_c_isfimathlocal);
  c4_c_varargin_1 = c4_bitconcat(chartInstance, 0U, c4_u2);
  c4_d_varargin_1 = c4_c_varargin_1;
  c4_c_eml_fi_checkforconst(chartInstance);
  c4_b_var1 = c4_d_varargin_1;
  c4_i4 = (int16_T)c4_b_var1;
  if ((int16_T)(c4_i4 & 256) != 0) {
    c4_temp_u2 = (int16_T)(c4_i4 | -256);
  } else {
    c4_temp_u2 = (int16_T)(c4_i4 & 255);
  }

  sf_mex_destroy(&c4_d_T);
  sf_mex_destroy(&c4_d_F);
  sf_mex_destroy(&c4_d_val);
  sf_mex_destroy(&c4_b_isautoscaled);
  sf_mex_destroy(&c4_b_pvpairsetdata);
  sf_mex_destroy(&c4_d_isfimathlocal);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 93);
  c4_e_varargin_1 = c4_b_plus(chartInstance, c4_plus(chartInstance, c4_temp_u1,
    c4_temp_u2), c4_c_in);
  c4_f_varargin_1 = c4_e_varargin_1;
  c4_c_eml_fi_checkforconst(chartInstance);
  c4_c_var1 = c4_f_varargin_1;
  c4_i5 = c4_c_var1;
  if ((int16_T)(c4_i5 & 256) != 0) {
    c4_temp_sum = (int16_T)(c4_i5 | -256);
  } else {
    c4_temp_sum = (int16_T)(c4_i5 & 255);
  }

  sf_mex_destroy(&c4_e_T);
  sf_mex_destroy(&c4_e_F);
  sf_mex_destroy(&c4_e_val);
  sf_mex_destroy(&c4_c_isautoscaled);
  sf_mex_destroy(&c4_c_pvpairsetdata);
  sf_mex_destroy(&c4_e_isfimathlocal);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 96);
  c4_a = c4_temp_sum;
  sf_mex_destroy(&c4_f_T);
  sf_mex_destroy(&c4_f_F);
  sf_mex_destroy(&c4_f_val);
  sf_mex_destroy(&c4_c_unusedU2);
  sf_mex_destroy(&c4_c_unusedU3);
  sf_mex_destroy(&c4_f_isfimathlocal);
  *c4_carry = 0U;
  c4_i6 = (int16_T)(uint16_T)((uint32_T)(uint16_T)((uint16_T)c4_a & 511U) >> 8);
  if ((int16_T)(c4_i6 & 256) != 0) {
    c4_i7 = (int16_T)(c4_i6 | -256);
  } else {
    c4_i7 = (int16_T)(c4_i6 & 255);
  }

  c4_i8 = (int16_T)(c4_i7 & 1);
  if ((int16_T)(c4_i8 & 256) != 0) {
    c4_i9 = (int16_T)(c4_i8 | -256);
  } else {
    c4_i9 = (int16_T)(c4_i8 & 255);
  }

  c4_slice_temp = (uint8_T)((uint8_T)c4_i9 & 1U);
  *c4_carry = c4_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 99);
  c4_g_varargin_1 = c4_temp_sum;
  c4_h_varargin_1 = c4_g_varargin_1;
  c4_eml_fi_checkforconst(chartInstance);
  c4_d_var1 = c4_h_varargin_1;
  *c4_sum = (int8_T)c4_d_var1;
  sf_mex_destroy(&c4_g_T);
  sf_mex_destroy(&c4_g_F);
  sf_mex_destroy(&c4_g_val);
  sf_mex_destroy(&c4_d_isautoscaled);
  sf_mex_destroy(&c4_d_pvpairsetdata);
  sf_mex_destroy(&c4_g_isfimathlocal);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 102);
  c4_b_a = *c4_sum;
  sf_mex_destroy(&c4_h_T);
  sf_mex_destroy(&c4_h_F);
  sf_mex_destroy(&c4_h_val);
  sf_mex_destroy(&c4_d_unusedU2);
  sf_mex_destroy(&c4_d_unusedU3);
  sf_mex_destroy(&c4_h_isfimathlocal);
  c4_sign_bit = 0U;
  c4_b_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
    (uint8_T)c4_b_a >> 7) & 1) & 1U);
  c4_sign_bit = c4_b_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 106);
  c4_c_a = c4_u1;
  sf_mex_destroy(&c4_i_T);
  sf_mex_destroy(&c4_i_F);
  sf_mex_destroy(&c4_i_val);
  sf_mex_destroy(&c4_e_unusedU2);
  sf_mex_destroy(&c4_e_unusedU3);
  sf_mex_destroy(&c4_i_isfimathlocal);
  c4_c_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
    (uint8_T)c4_c_a >> 7) & 1) & 1U);
  c4_c = c4_c_slice_temp;
  c4_d_a = c4_u2;
  sf_mex_destroy(&c4_j_T);
  sf_mex_destroy(&c4_j_F);
  sf_mex_destroy(&c4_j_val);
  sf_mex_destroy(&c4_f_unusedU2);
  sf_mex_destroy(&c4_f_unusedU3);
  sf_mex_destroy(&c4_j_isfimathlocal);
  c4_d_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
    (uint8_T)c4_d_a >> 7) & 1) & 1U);
  c4_b_c = c4_d_slice_temp;
  c4_a0 = c4_c;
  c4_b0 = c4_b_c;
  c4_e_a = c4_a0;
  c4_b = c4_b0;
  c4_b_a0 = c4_e_a;
  c4_b_b0 = c4_b;
  c4_a1 = c4_b_a0;
  c4_b1 = c4_b_b0;
  c4_b_a1 = c4_a1;
  c4_b_b1 = c4_b1;
  c4_c_c = (c4_b_a1 == c4_b_b1);
  guard1 = false;
  if (c4_c_c) {
    c4_f_a = c4_u1;
    c4_c_a1 = c4_f_a;
    c4_e_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
      (uint8_T)c4_c_a1 >> 7) & 1) & 1U);
    c4_d_c = c4_e_slice_temp;
    c4_c_a0 = c4_sign_bit;
    c4_c_b0 = c4_d_c;
    c4_g_a = c4_c_a0;
    c4_b_b = c4_c_b0;
    c4_d_a0 = c4_g_a;
    c4_d_b0 = c4_b_b;
    c4_d_a1 = c4_d_a0;
    c4_c_b1 = c4_d_b0;
    c4_e_a1 = c4_d_a1;
    c4_d_b1 = c4_c_b1;
    c4_e_c = (c4_e_a1 != c4_d_b1);
    if (c4_e_c) {
      c4_e_b0 = true;
    } else {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1 == true) {
    c4_e_b0 = false;
  }

  c4_overflow_int = (uint8_T)c4_e_b0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 110);
  c4_i_varargin_1 = c4_overflow_int;
  c4_j_varargin_1 = c4_i_varargin_1;
  c4_b_eml_fi_checkforconst(chartInstance);
  c4_e_var1 = c4_j_varargin_1;
  *c4_overflow = (uint8_T)(c4_e_var1 & 1U);
  sf_mex_destroy(&c4_k_T);
  sf_mex_destroy(&c4_k_F);
  sf_mex_destroy(&c4_k_val);
  sf_mex_destroy(&c4_e_isautoscaled);
  sf_mex_destroy(&c4_e_pvpairsetdata);
  sf_mex_destroy(&c4_k_isfimathlocal);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -110);
  _SFD_SYMBOL_SCOPE_POP();
}

static uint16_T c4_bitconcat(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c4_varargin_1, int8_T c4_varargin_2)
{
  uint8_T c4_b_varargin_1;
  int8_T c4_b_varargin_2;
  int8_T c4_varargout_2;
  uint8_T c4_slice_temp;
  (void)chartInstance;
  c4_b_varargin_1 = c4_varargin_1;
  c4_b_varargin_2 = c4_varargin_2;
  c4_varargout_2 = c4_b_varargin_2;
  c4_slice_temp = (uint8_T)c4_varargout_2;
  return (uint16_T)((uint16_T)((uint16_T)((uint16_T)((uint16_T)((uint16_T)
    c4_b_varargin_1 & 511U) << 8) & 511U) | (uint16_T)((uint16_T)c4_slice_temp &
    511U)) & 511U);
}

static void c4_c_eml_fi_checkforconst(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static int16_T c4_plus(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int16_T c4_a0, int16_T c4_b0)
{
  int16_T c4_c;
  int16_T c4_a;
  int16_T c4_b;
  int16_T c4_i10;
  int16_T c4_i11;
  int16_T c4_i12;
  int16_T c4_i13;
  int16_T c4_i14;
  const mxArray *c4_errID = NULL;
  const mxArray *c4_a2SD = NULL;
  const mxArray *c4_b2SD = NULL;
  const mxArray *c4_Tsd = NULL;
  (void)chartInstance;
  c4_a = c4_a0;
  c4_b = c4_b0;
  c4_i10 = c4_a;
  c4_i11 = c4_b;
  if ((int16_T)(c4_i10 & 512) != 0) {
    c4_i12 = (int16_T)(c4_i10 | -512);
  } else {
    c4_i12 = (int16_T)(c4_i10 & 511);
  }

  if ((int16_T)(c4_i11 & 512) != 0) {
    c4_i13 = (int16_T)(c4_i11 | -512);
  } else {
    c4_i13 = (int16_T)(c4_i11 & 511);
  }

  c4_i14 = (int16_T)(c4_i12 + c4_i13);
  if ((int16_T)(c4_i14 & 512) != 0) {
    c4_c = (int16_T)(c4_i14 | -512);
  } else {
    c4_c = (int16_T)(c4_i14 & 511);
  }

  sf_mex_destroy(&c4_errID);
  sf_mex_destroy(&c4_a2SD);
  sf_mex_destroy(&c4_b2SD);
  sf_mex_destroy(&c4_Tsd);
  return c4_c;
}

static int16_T c4_b_plus(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int16_T c4_a0, uint8_T c4_b0)
{
  int16_T c4_c;
  int16_T c4_a;
  uint8_T c4_b;
  int16_T c4_i15;
  int16_T c4_i16;
  int16_T c4_i17;
  int16_T c4_i18;
  int16_T c4_i19;
  const mxArray *c4_errID = NULL;
  const mxArray *c4_a2SD = NULL;
  const mxArray *c4_b2SD = NULL;
  const mxArray *c4_Tsd = NULL;
  (void)chartInstance;
  c4_a = c4_a0;
  c4_b = c4_b0;
  c4_i15 = c4_a;
  c4_i16 = c4_b;
  if ((int16_T)(c4_i15 & 1024) != 0) {
    c4_i17 = (int16_T)(c4_i15 | -1024);
  } else {
    c4_i17 = (int16_T)(c4_i15 & 1023);
  }

  if ((int16_T)(c4_i16 & 1024) != 0) {
    c4_i18 = (int16_T)(c4_i16 | -1024);
  } else {
    c4_i18 = (int16_T)(c4_i16 & 1023);
  }

  c4_i19 = (int16_T)(c4_i17 + c4_i18);
  if ((int16_T)(c4_i19 & 1024) != 0) {
    c4_c = (int16_T)(c4_i19 | -1024);
  } else {
    c4_c = (int16_T)(c4_i19 & 1023);
  }

  sf_mex_destroy(&c4_errID);
  sf_mex_destroy(&c4_a2SD);
  sf_mex_destroy(&c4_b2SD);
  sf_mex_destroy(&c4_Tsd);
  return c4_c;
}

static int8_T c4_bitand(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_a, int8_T c4_b)
{
  int8_T c4_c_uint;
  (void)chartInstance;
  c4_c_uint = (int8_T)(c4_a & c4_b);
  return c4_c_uint;
}

static boolean_T c4_all(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_x)
{
  int8_T c4_b_x;
  int8_T c4_c_x;
  int8_T c4_a0;
  int8_T c4_a;
  int8_T c4_b_a0;
  int8_T c4_a1;
  int8_T c4_b_a1;
  (void)chartInstance;
  c4_b_x = c4_x;
  c4_c_x = c4_b_x;
  c4_a0 = c4_c_x;
  c4_a = c4_a0;
  c4_b_a0 = c4_a;
  c4_a1 = c4_b_a0;
  c4_b_a1 = c4_a1;
  return c4_b_a1 != 0;
}

static const mxArray *c4_k_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_u;
  const mxArray *c4_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static int32_T c4_k_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i20;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i20, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i20;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_l_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  uint8_T c4_u;
  const mxArray *c4_y = NULL;
  uint8_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c4_u = *(uint8_T *)c4_inData;
    c4_y = NULL;
    c4_b_u = c4_u;
    c4_b_y = NULL;
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c4_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_b_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c4_mxArrayOutData;
}

static const mxArray *c4_m_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  uint8_T c4_u;
  const mxArray *c4_y = NULL;
  uint8_T c4_b_u;
  const mxArray *c4_b_y = NULL;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c4_u = *(uint8_T *)c4_inData;
    c4_y = NULL;
    c4_b_u = c4_u;
    c4_b_y = NULL;
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c4_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_d_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c4_mxArrayOutData;
}

static uint8_T c4_l_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_out_flags, const char_T *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_out_flags),
    &c4_thisId);
  sf_mex_destroy(&c4_out_flags);
  return c4_y;
}

static uint8_T c4_m_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  const mxArray *c4_mxFi = NULL;
  const mxArray *c4_mxInt = NULL;
  uint8_T c4_u4;
  (void)chartInstance;
  sf_mex_check_fi(c4_parentId, c4_u, false, 0U, NULL, c4_eml_mx, c4_b_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u), false);
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)), false);
  sf_mex_import(c4_parentId, sf_mex_dup(c4_mxInt), &c4_u4, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c4_mxFi);
  sf_mex_destroy(&c4_mxInt);
  c4_y = c4_u4;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void c4_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_out_flags;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  uint8_T c4_y;
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c4_out_flags = sf_mex_dup(c4_mxArrayInData);
    c4_identifier = c4_varName;
    c4_thisId.fIdentifier = c4_identifier;
    c4_thisId.fParent = NULL;
    c4_y = c4_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_out_flags),
      &c4_thisId);
    sf_mex_destroy(&c4_out_flags);
    *(uint8_T *)c4_outData = c4_y;
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static void init_dsm_address_info(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c4_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(422514274U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1639670460U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2242891784U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4008042978U);
}

mxArray *sf_c4_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("0RsUhPUxjRZzk6jM2C4iKF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(4));
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
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(3));
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
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

      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(11));

      {
        const char *fixptFields[] = { "isSigned", "wordLength", "bias", "slope",
          "exponent", "isScaledDouble" };

        mxArray *mxFixpt = mxCreateStructMatrix(1,1,6,fixptFields);
        mxSetField(mxFixpt,0,"isSigned",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(4));
        mxSetField(mxFixpt,0,"bias",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"slope",mxCreateDoubleScalar(1));
        mxSetField(mxFixpt,0,"exponent",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"isScaledDouble",mxCreateDoubleScalar(0));
        mxSetField(mxType,0,"fixpt",mxFixpt);
      }

      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c4_hdlcodercpu_eml_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c4_hdlcodercpu_eml_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c4_hdlcodercpu_eml(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[8],T\"alu_out\",},{M[1],M[9],T\"out_flags\",},{M[8],M[0],T\"is_active_c4_hdlcodercpu_eml\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_hdlcodercpu_eml_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _hdlcodercpu_emlMachineNumber_,
           4,
           1,
           1,
           0,
           6,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_hdlcodercpu_emlMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_hdlcodercpu_emlMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _hdlcodercpu_emlMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"in_flags");
          _SFD_SET_DATA_PROPS(1,1,1,0,"func");
          _SFD_SET_DATA_PROPS(2,1,1,0,"alu_in");
          _SFD_SET_DATA_PROPS(3,1,1,0,"AC");
          _SFD_SET_DATA_PROPS(4,2,0,1,"alu_out");
          _SFD_SET_DATA_PROPS(5,2,0,1,"out_flags");
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
        _SFD_CV_INIT_EML(0,1,3,0,0,0,1,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2182);
        _SFD_CV_INIT_EML_FCN(0,1,"sub_w_borrow",2182,-1,2502);
        _SFD_CV_INIT_EML_FCN(0,2,"sum_w_carry",2502,-1,3640);

        {
          static int caseStart[] = { -1, 903, 950, 1028, 1171, 1336, 1429, 1505,
            1606 };

          static int caseExprEnd[] = { 8, 909, 956, 1034, 1177, 1342, 1435, 1511,
            1612 };

          _SFD_CV_INIT_EML_SWITCH(0,1,0,879,898,1686,9,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,1,0,4,0,1,0,0,
          (MexFcnForType)c4_l_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,1,0,3,0,1,0,0,
          (MexFcnForType)c4_m_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)c4_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,1,0,4,0,1,0,0,
          (MexFcnForType)c4_l_sf_marshallOut,(MexInFcnForType)c4_j_sf_marshallIn);

        {
          uint8_T *c4_in_flags;
          uint8_T *c4_func;
          int8_T *c4_alu_in;
          int8_T *c4_AC;
          int8_T *c4_alu_out;
          uint8_T *c4_out_flags;
          c4_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c4_alu_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c4_AC = (int8_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c4_alu_in = (int8_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c4_func = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c4_in_flags = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c4_in_flags);
          _SFD_SET_DATA_VALUE_PTR(1U, c4_func);
          _SFD_SET_DATA_VALUE_PTR(2U, c4_alu_in);
          _SFD_SET_DATA_VALUE_PTR(3U, c4_AC);
          _SFD_SET_DATA_VALUE_PTR(4U, c4_alu_out);
          _SFD_SET_DATA_VALUE_PTR(5U, c4_out_flags);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _hdlcodercpu_emlMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "WpKUyZMujhavGZGBM31PU";
}

static void sf_opaque_initialize_c4_hdlcodercpu_eml(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c4_hdlcodercpu_eml((SFc4_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
  initialize_c4_hdlcodercpu_eml((SFc4_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c4_hdlcodercpu_eml(void *chartInstanceVar)
{
  enable_c4_hdlcodercpu_eml((SFc4_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c4_hdlcodercpu_eml(void *chartInstanceVar)
{
  disable_c4_hdlcodercpu_eml((SFc4_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c4_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_gateway_c4_hdlcodercpu_eml((SFc4_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c4_hdlcodercpu_eml(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c4_hdlcodercpu_eml
    ((SFc4_hdlcodercpu_emlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_hdlcodercpu_eml();/* state var info */
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

extern void sf_internal_set_sim_state_c4_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c4_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c4_hdlcodercpu_eml((SFc4_hdlcodercpu_emlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c4_hdlcodercpu_eml(SimStruct* S)
{
  return sf_internal_get_sim_state_c4_hdlcodercpu_eml(S);
}

static void sf_opaque_set_sim_state_c4_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c4_hdlcodercpu_eml(S, st);
}

static void sf_opaque_terminate_c4_hdlcodercpu_eml(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_hdlcodercpu_emlInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_hdlcodercpu_eml_optimization_info();
    }

    finalize_c4_hdlcodercpu_eml((SFc4_hdlcodercpu_emlInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_hdlcodercpu_eml((SFc4_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_hdlcodercpu_eml(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c4_hdlcodercpu_eml((SFc4_hdlcodercpu_emlInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_hdlcodercpu_eml_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,4,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,4,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,4);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,4,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3980601759U));
  ssSetChecksum1(S,(1612710908U));
  ssSetChecksum2(S,(1142590710U));
  ssSetChecksum3(S,(1150009411U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_hdlcodercpu_eml(SimStruct *S)
{
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)utMalloc(sizeof
    (SFc4_hdlcodercpu_emlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_hdlcodercpu_emlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c4_hdlcodercpu_eml;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c4_hdlcodercpu_eml;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c4_hdlcodercpu_eml;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_hdlcodercpu_eml;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c4_hdlcodercpu_eml;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c4_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c4_hdlcodercpu_eml;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c4_hdlcodercpu_eml;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c4_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_hdlcodercpu_eml(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_hdlcodercpu_eml_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
