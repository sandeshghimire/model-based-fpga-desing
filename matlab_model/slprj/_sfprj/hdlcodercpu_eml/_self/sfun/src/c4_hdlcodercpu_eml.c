/* Include files */

#include "blascompat32.h"
#include "hdlcodercpu_eml_sfun.h"
#include "c4_hdlcodercpu_eml.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "hdlcodercpu_eml_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
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
static void sf_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c4_chartstep_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initSimStructsc4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber);
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
static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[43]);
static uint8_T c4_uint8(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c4_A);
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
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c4_is_active_c4_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c4_f_eml_mx, sf_mex_call_debug("numerictype", 1U, 10U, 15,
    "WordLength", 6, 9.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c4_e_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 1.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c4_d_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 3.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c4_c_eml_mx, sf_mex_call_debug("numerictype", 1U, 10U, 15,
    "WordLength", 6, 8.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c4_b_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 4.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c4_eml_mx, sf_mex_call_debug("fimath", 1U, 38U, 15, "RoundMode",
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

static void initialize_params_c4_hdlcodercpu_eml
  (SFc4_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void enable_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c4_update_debugger_state_c4_hdlcodercpu_eml
  (SFc4_hdlcodercpu_emlInstanceStruct *chartInstance)
{
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
  sf_mex_assign(&c4_y, sf_mex_createcellarray(3));
  c4_hoistedGlobal = *c4_alu_out;
  c4_u = c4_hoistedGlobal;
  c4_b_y = NULL;
  c4_b_u = c4_u;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_b_u, 2, 0U, 0U, 0U, 0));
  sf_mex_assign(&c4_b_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_c_eml_mx), 15,
    "simulinkarray", 14, c4_c_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_b_hoistedGlobal = *c4_out_flags;
  c4_c_u = c4_b_hoistedGlobal;
  c4_d_y = NULL;
  c4_d_u = c4_c_u;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_d_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c4_d_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_b_eml_mx), 15,
    "simulinkarray", 14, c4_e_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c4_y, 1, c4_d_y);
  c4_c_hoistedGlobal = chartInstance->c4_is_active_c4_hdlcodercpu_eml;
  c4_e_u = c4_c_hoistedGlobal;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_e_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c4_y, 2, c4_f_y);
  sf_mex_assign(&c4_st, c4_y);
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
  chartInstance->c4_doneDoubleBufferReInit = TRUE;
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
  sf_mex_destroy(&c4_eml_mx);
  sf_mex_destroy(&c4_b_eml_mx);
  sf_mex_destroy(&c4_c_eml_mx);
  sf_mex_destroy(&c4_d_eml_mx);
  sf_mex_destroy(&c4_e_eml_mx);
  sf_mex_destroy(&c4_f_eml_mx);
}

static void sf_c4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct
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
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c4_in_flags, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c4_func, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c4_alu_in, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*c4_AC, 3U);
  _SFD_DATA_RANGE_CHECK((real_T)*c4_alu_out, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)*c4_out_flags, 5U);
  chartInstance->c4_sfEvent = CALL_EVENT;
  c4_chartstep_c4_hdlcodercpu_eml(chartInstance);
  sf_debug_check_for_state_inconsistency(_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
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
  const mxArray *c4_m0 = NULL;
  const mxArray *c4_m1 = NULL;
  uint8_T c4_a1;
  uint8_T c4_slice_temp;
  uint8_T c4_b_a;
  const mxArray *c4_m2 = NULL;
  const mxArray *c4_m3 = NULL;
  uint8_T c4_b_a1;
  uint8_T c4_b_slice_temp;
  int8_T c4_varargin_1;
  int8_T c4_b_varargin_1;
  const mxArray *c4_m4 = NULL;
  const mxArray *c4_m5 = NULL;
  const mxArray *c4_m6 = NULL;
  const mxArray *c4_m7 = NULL;
  int8_T c4_var1;
  const mxArray *c4_m8 = NULL;
  const mxArray *c4_m9 = NULL;
  const mxArray *c4_m10 = NULL;
  const mxArray *c4_m11 = NULL;
  const mxArray *c4_m12 = NULL;
  const mxArray *c4_m13 = NULL;
  const mxArray *c4_m14 = NULL;
  uint8_T c4_b_overflow;
  uint8_T c4_b_carry;
  int8_T c4_b_alu_out;
  uint8_T c4_c_overflow;
  uint8_T c4_c_carry;
  int8_T c4_c_alu_out;
  int8_T c4_c_varargin_1;
  int8_T c4_d_varargin_1;
  const mxArray *c4_m15 = NULL;
  const mxArray *c4_m16 = NULL;
  const mxArray *c4_m17 = NULL;
  const mxArray *c4_m18 = NULL;
  int8_T c4_b_var1;
  const mxArray *c4_m19 = NULL;
  const mxArray *c4_m20 = NULL;
  const mxArray *c4_m21 = NULL;
  const mxArray *c4_m22 = NULL;
  const mxArray *c4_m23 = NULL;
  const mxArray *c4_m24 = NULL;
  const mxArray *c4_m25 = NULL;
  int8_T c4_e_varargin_1;
  int8_T c4_f_varargin_1;
  const mxArray *c4_m26 = NULL;
  const mxArray *c4_m27 = NULL;
  const mxArray *c4_m28 = NULL;
  const mxArray *c4_m29 = NULL;
  int8_T c4_c_var1;
  const mxArray *c4_m30 = NULL;
  const mxArray *c4_m31 = NULL;
  const mxArray *c4_m32 = NULL;
  const mxArray *c4_m33 = NULL;
  const mxArray *c4_m34 = NULL;
  const mxArray *c4_m35 = NULL;
  const mxArray *c4_m36 = NULL;
  const mxArray *c4_m37 = NULL;
  const mxArray *c4_m38 = NULL;
  const mxArray *c4_m39 = NULL;
  const mxArray *c4_m40 = NULL;
  const mxArray *c4_m41 = NULL;
  const mxArray *c4_m42 = NULL;
  const mxArray *c4_m43 = NULL;
  int8_T c4_c_a;
  const mxArray *c4_m44 = NULL;
  const mxArray *c4_m45 = NULL;
  const mxArray *c4_m46 = NULL;
  const mxArray *c4_m47 = NULL;
  const mxArray *c4_m48 = NULL;
  const mxArray *c4_m49 = NULL;
  const mxArray *c4_m50 = NULL;
  const mxArray *c4_m51 = NULL;
  const mxArray *c4_m52 = NULL;
  uint8_T c4_c_slice_temp;
  uint8_T c4_g_varargin_1;
  uint8_T c4_h_varargin_1;
  uint8_T c4_d_var1;
  const mxArray *c4_m53 = NULL;
  const mxArray *c4_m54 = NULL;
  const mxArray *c4_m55 = NULL;
  const mxArray *c4_m56 = NULL;
  const mxArray *c4_m57 = NULL;
  const mxArray *c4_m58 = NULL;
  const mxArray *c4_m59 = NULL;
  uint8_T c4_i_varargin_1;
  uint8_T c4_varargin_2;
  uint8_T c4_j_varargin_1;
  uint8_T c4_b_varargin_2;
  const mxArray *c4_m60 = NULL;
  const mxArray *c4_m61 = NULL;
  uint8_T c4_varargout_2;
  const mxArray *c4_m62 = NULL;
  const mxArray *c4_m63 = NULL;
  uint8_T c4_c;
  uint8_T c4_k_varargin_1;
  uint8_T c4_c_varargin_2;
  uint8_T c4_l_varargin_1;
  uint8_T c4_d_varargin_2;
  const mxArray *c4_m64 = NULL;
  const mxArray *c4_m65 = NULL;
  uint8_T c4_b_varargout_2;
  const mxArray *c4_m66 = NULL;
  const mxArray *c4_m67 = NULL;
  uint8_T c4_b_c;
  uint8_T c4_m_varargin_1;
  uint8_T c4_e_varargin_2;
  uint8_T c4_n_varargin_1;
  uint8_T c4_f_varargin_2;
  const mxArray *c4_m68 = NULL;
  const mxArray *c4_m69 = NULL;
  uint8_T c4_c_varargout_2;
  const mxArray *c4_m70 = NULL;
  const mxArray *c4_m71 = NULL;
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
  sf_debug_symbol_scope_push_eml(0U, 14U, 14U, c4_debug_family_names,
    c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c4_hdl_fm, 0U, c4_i_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c4_carry, 1U, c4_h_sf_marshallOut,
    c4_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_overflow, 2U, c4_h_sf_marshallOut,
    c4_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_sign_bit, 3U, c4_f_sf_marshallOut,
    c4_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_is_zero, 4U, c4_g_sf_marshallOut,
    c4_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_zero_ufix1, 5U,
    c4_f_sf_marshallOut, c4_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_nargin, 6U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_nargout, 7U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c4_in_flags, 8U, c4_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_func, 9U, c4_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_alu_in, 10U, c4_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c4_AC, 11U, c4_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c4_alu_out, 12U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_out_flags, 13U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 8);
  c4_hdl_fm = c4_eml_mx;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 16);
  c4_a = c4_in_flags;
  sf_mex_destroy(&c4_m0);
  sf_mex_destroy(&c4_m1);
  c4_carry = 0U;
  c4_a1 = c4_a;
  c4_slice_temp = (uint8_T)((uint8_T)((uint32_T)c4_a1 >> 3) & 1U);
  c4_carry = c4_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 19);
  c4_b_a = c4_in_flags;
  sf_mex_destroy(&c4_m2);
  sf_mex_destroy(&c4_m3);
  c4_overflow = 0U;
  c4_b_a1 = c4_b_a;
  c4_b_slice_temp = (uint8_T)((uint8_T)((uint32_T)c4_b_a1 >> 1) & 1U);
  c4_overflow = c4_b_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 22);
  c4_varargin_1 = c4_AC;
  c4_b_varargin_1 = c4_varargin_1;
  sf_mex_destroy(&c4_m4);
  sf_mex_destroy(&c4_m5);
  sf_mex_destroy(&c4_m6);
  sf_mex_destroy(&c4_m7);
  c4_var1 = c4_b_varargin_1;
  c4_alu_out = c4_var1;
  sf_mex_destroy(&c4_m8);
  sf_mex_destroy(&c4_m9);
  sf_mex_destroy(&c4_m10);
  sf_mex_destroy(&c4_m11);
  sf_mex_destroy(&c4_m12);
  sf_mex_destroy(&c4_m13);
  sf_mex_destroy(&c4_m14);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 26);
  switch (c4_uint8(chartInstance, c4_func)) {
   case 0U:
    CV_EML_SWITCH(0, 0, 1);
    break;

   case 1U:
    CV_EML_SWITCH(0, 0, 2);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 31);
    c4_alu_out = c4_bitand(chartInstance, c4_alu_in, c4_AC);
    break;

   case 2U:
    CV_EML_SWITCH(0, 0, 3);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 34);
    c4_sum_w_carry(chartInstance, c4_AC, c4_alu_in, c4_carry, &c4_b_alu_out,
                   &c4_b_carry, &c4_b_overflow);
    c4_alu_out = c4_b_alu_out;
    c4_carry = c4_b_carry;
    c4_overflow = c4_b_overflow;
    break;

   case 3U:
    CV_EML_SWITCH(0, 0, 4);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 37);
    c4_sub_w_borrow(chartInstance, c4_AC, c4_alu_in, c4_carry, &c4_c_alu_out,
                    &c4_c_carry, &c4_c_overflow);
    c4_alu_out = c4_c_alu_out;
    c4_carry = c4_c_carry;
    c4_overflow = c4_c_overflow;
    break;

   case 4U:
    CV_EML_SWITCH(0, 0, 5);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 40);
    c4_c_varargin_1 = c4_b_bitcmp(chartInstance, c4_AC);
    c4_d_varargin_1 = c4_c_varargin_1;
    sf_mex_destroy(&c4_m15);
    sf_mex_destroy(&c4_m16);
    sf_mex_destroy(&c4_m17);
    sf_mex_destroy(&c4_m18);
    c4_b_var1 = c4_d_varargin_1;
    c4_alu_out = c4_b_var1;
    sf_mex_destroy(&c4_m19);
    sf_mex_destroy(&c4_m20);
    sf_mex_destroy(&c4_m21);
    sf_mex_destroy(&c4_m22);
    sf_mex_destroy(&c4_m23);
    sf_mex_destroy(&c4_m24);
    sf_mex_destroy(&c4_m25);
    break;

   case 5U:
    CV_EML_SWITCH(0, 0, 6);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 43);
    c4_carry = c4_bitcmp(chartInstance, c4_carry);
    break;

   case 6U:
    CV_EML_SWITCH(0, 0, 7);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 46);
    c4_e_varargin_1 = c4_alu_in;
    c4_f_varargin_1 = c4_e_varargin_1;
    sf_mex_destroy(&c4_m26);
    sf_mex_destroy(&c4_m27);
    sf_mex_destroy(&c4_m28);
    sf_mex_destroy(&c4_m29);
    c4_c_var1 = c4_f_varargin_1;
    c4_alu_out = c4_c_var1;
    sf_mex_destroy(&c4_m30);
    sf_mex_destroy(&c4_m31);
    sf_mex_destroy(&c4_m32);
    sf_mex_destroy(&c4_m33);
    sf_mex_destroy(&c4_m34);
    sf_mex_destroy(&c4_m35);
    sf_mex_destroy(&c4_m36);
    break;

   case 7U:
    CV_EML_SWITCH(0, 0, 8);
    _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 49);
    sf_mex_destroy(&c4_m37);
    sf_mex_destroy(&c4_m38);
    sf_mex_destroy(&c4_m39);
    sf_mex_destroy(&c4_m40);
    sf_mex_destroy(&c4_m41);
    sf_mex_destroy(&c4_m42);
    sf_mex_destroy(&c4_m43);
    c4_carry = 0U;
    break;

   default:
    CV_EML_SWITCH(0, 0, 0);
    break;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 53);
  c4_c_a = c4_alu_out;
  sf_mex_destroy(&c4_m44);
  sf_mex_destroy(&c4_m45);
  sf_mex_destroy(&c4_m46);
  sf_mex_destroy(&c4_m47);
  sf_mex_destroy(&c4_m48);
  sf_mex_destroy(&c4_m49);
  sf_mex_destroy(&c4_m50);
  sf_mex_destroy(&c4_m51);
  sf_mex_destroy(&c4_m52);
  c4_sign_bit = 0U;
  c4_c_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
    (uint8_T)c4_c_a >> 7) & 1) & 1U);
  c4_sign_bit = c4_c_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 56);
  c4_is_zero = (uint8_T)!c4_all(chartInstance, c4_alu_out);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 57);
  c4_g_varargin_1 = c4_is_zero;
  c4_h_varargin_1 = c4_g_varargin_1;
  c4_d_var1 = c4_h_varargin_1;
  c4_zero_ufix1 = (uint8_T)(c4_d_var1 & 1U);
  sf_mex_destroy(&c4_m53);
  sf_mex_destroy(&c4_m54);
  sf_mex_destroy(&c4_m55);
  sf_mex_destroy(&c4_m56);
  sf_mex_destroy(&c4_m57);
  sf_mex_destroy(&c4_m58);
  sf_mex_destroy(&c4_m59);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 60);
  c4_i_varargin_1 = c4_carry;
  c4_varargin_2 = c4_sign_bit;
  c4_j_varargin_1 = c4_i_varargin_1;
  c4_b_varargin_2 = c4_varargin_2;
  sf_mex_destroy(&c4_m60);
  sf_mex_destroy(&c4_m61);
  c4_varargout_2 = c4_b_varargin_2;
  sf_mex_destroy(&c4_m62);
  sf_mex_destroy(&c4_m63);
  c4_c = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)(c4_j_varargin_1 & 3U)
    << 1) & 3U) | (uint8_T)(c4_varargout_2 & 3U)) & 3U);
  c4_k_varargin_1 = c4_c;
  c4_c_varargin_2 = c4_overflow;
  c4_l_varargin_1 = c4_k_varargin_1;
  c4_d_varargin_2 = c4_c_varargin_2;
  sf_mex_destroy(&c4_m64);
  sf_mex_destroy(&c4_m65);
  c4_b_varargout_2 = c4_d_varargin_2;
  sf_mex_destroy(&c4_m66);
  sf_mex_destroy(&c4_m67);
  c4_b_c = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)(c4_l_varargin_1 &
    7U) << 1) & 7U) | (uint8_T)(c4_b_varargout_2 & 7U)) & 7U);
  c4_m_varargin_1 = c4_b_c;
  c4_e_varargin_2 = c4_zero_ufix1;
  c4_n_varargin_1 = c4_m_varargin_1;
  c4_f_varargin_2 = c4_e_varargin_2;
  sf_mex_destroy(&c4_m68);
  sf_mex_destroy(&c4_m69);
  c4_c_varargout_2 = c4_f_varargin_2;
  sf_mex_destroy(&c4_m70);
  sf_mex_destroy(&c4_m71);
  c4_out_flags = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)
    (c4_n_varargin_1 & 15U) << 1) & 15U) | (uint8_T)(c4_c_varargout_2 & 15U)) &
    15U);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -60);
  sf_debug_symbol_scope_pop();
  *c4_d_alu_out = c4_alu_out;
  *c4_b_out_flags = c4_out_flags;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
}

static void initSimStructsc4_hdlcodercpu_eml(SFc4_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber)
{
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
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c4_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_b_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c4_mxArrayOutData, c4_y);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
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
  sf_mex_check_fi(c4_parentId, c4_u, 0, 0U, 0, c4_eml_mx, c4_b_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u));
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)));
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
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c4_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_c_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c4_mxArrayOutData, c4_y);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
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
  sf_mex_check_fi(c4_parentId, c4_u, 0, 0U, 0, c4_eml_mx, c4_c_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u));
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)));
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
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c4_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_c_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c4_mxArrayOutData, c4_y);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
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
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c4_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_d_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c4_mxArrayOutData, c4_y);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
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
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c4_mxArrayOutData, c4_y);
  return c4_mxArrayOutData;
}

static real_T c4_d_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
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
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c4_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_e_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c4_mxArrayOutData, c4_y);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
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
  sf_mex_check_fi(c4_parentId, c4_u, 0, 0U, 0, c4_eml_mx, c4_e_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u));
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)));
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
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c4_mxArrayOutData, c4_y);
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
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c4_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_e_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c4_mxArrayOutData, c4_y);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
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
  sf_mex_check_fi(c4_parentId, c4_u, 0, 0U, 0, c4_eml_mx, c4_e_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u));
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)));
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
  sf_mex_assign(&c4_y, sf_mex_duplicatearraysafe(&c4_u));
  sf_mex_destroy(&c4_u);
  sf_mex_assign(&c4_mxArrayOutData, c4_y);
  return c4_mxArrayOutData;
}

static int8_T c4_i_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int8_T c4_y;
  const mxArray *c4_mxFi = NULL;
  const mxArray *c4_mxInt = NULL;
  int8_T c4_i1;
  sf_mex_check_fi(c4_parentId, c4_u, 0, 0U, 0, c4_eml_mx, c4_c_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u));
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)));
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
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 4, 0U, 0U, 0U, 0));
    sf_mex_assign(&c4_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_f_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c4_mxArrayOutData, c4_y);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
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
  sf_mex_check_fi(c4_parentId, c4_u, 0, 0U, 0, c4_eml_mx, c4_f_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u));
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)));
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
  const mxArray *c4_nameCaptureInfo;
  c4_ResolvedFunctionInfo c4_info[43];
  const mxArray *c4_m72 = NULL;
  int32_T c4_i3;
  c4_ResolvedFunctionInfo *c4_r0;
  c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  c4_info_helper(c4_info);
  sf_mex_assign(&c4_m72, sf_mex_createstruct("nameCaptureInfo", 1, 43));
  for (c4_i3 = 0; c4_i3 < 43; c4_i3++) {
    c4_r0 = &c4_info[c4_i3];
    sf_mex_addfield(c4_m72, sf_mex_create("nameCaptureInfo", c4_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->context)), "context", "nameCaptureInfo",
                    c4_i3);
    sf_mex_addfield(c4_m72, sf_mex_create("nameCaptureInfo", c4_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c4_r0->name)), "name", "nameCaptureInfo", c4_i3);
    sf_mex_addfield(c4_m72, sf_mex_create("nameCaptureInfo", c4_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c4_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c4_i3);
    sf_mex_addfield(c4_m72, sf_mex_create("nameCaptureInfo", c4_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c4_r0->resolved)), "resolved", "nameCaptureInfo",
                    c4_i3);
    sf_mex_addfield(c4_m72, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c4_i3);
    sf_mex_addfield(c4_m72, sf_mex_create("nameCaptureInfo", &c4_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c4_i3);
    sf_mex_addfield(c4_m72, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c4_i3);
    sf_mex_addfield(c4_m72, sf_mex_create("nameCaptureInfo", &c4_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c4_i3);
  }

  sf_mex_assign(&c4_nameCaptureInfo, c4_m72);
  return c4_nameCaptureInfo;
}

static void c4_info_helper(c4_ResolvedFunctionInfo c4_info[43])
{
  c4_info[0].context = "";
  c4_info[0].name = "fimath";
  c4_info[0].dominantType = "char";
  c4_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m";
  c4_info[0].fileTimeLo = 275520000U;
  c4_info[0].fileTimeHi = 30114375U;
  c4_info[0].mFileTimeLo = 0U;
  c4_info[0].mFileTimeHi = 0U;
  c4_info[1].context = "";
  c4_info[1].name = "bitget";
  c4_info[1].dominantType = "embedded.fi";
  c4_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c4_info[1].fileTimeLo = 235520000U;
  c4_info[1].fileTimeHi = 30114375U;
  c4_info[1].mFileTimeLo = 0U;
  c4_info[1].mFileTimeHi = 0U;
  c4_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c4_info[2].name = "isfi";
  c4_info[2].dominantType = "double";
  c4_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c4_info[2].fileTimeLo = 335520000U;
  c4_info[2].fileTimeHi = 30114375U;
  c4_info[2].mFileTimeLo = 0U;
  c4_info[2].mFileTimeHi = 0U;
  c4_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c4_info[3].name = "isnumerictype";
  c4_info[3].dominantType = "char";
  c4_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m";
  c4_info[3].fileTimeLo = 355520000U;
  c4_info[3].fileTimeHi = 30114375U;
  c4_info[3].mFileTimeLo = 0U;
  c4_info[3].mFileTimeHi = 0U;
  c4_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c4_info[4].name = "eml_scalexp_compatible";
  c4_info[4].dominantType = "embedded.fi";
  c4_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c4_info[4].fileTimeLo = 3244844544U;
  c4_info[4].fileTimeHi = 30108086U;
  c4_info[4].mFileTimeLo = 0U;
  c4_info[4].mFileTimeHi = 0U;
  c4_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c4_info[5].name = "all";
  c4_info[5].dominantType = "logical";
  c4_info[5].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c4_info[5].fileTimeLo = 3624844544U;
  c4_info[5].fileTimeHi = 30108086U;
  c4_info[5].mFileTimeLo = 0U;
  c4_info[5].mFileTimeHi = 0U;
  c4_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c4_info[6].name = "eml_all_or_any";
  c4_info[6].dominantType = "char";
  c4_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c4_info[6].fileTimeLo = 2224844544U;
  c4_info[6].fileTimeHi = 30108086U;
  c4_info[6].mFileTimeLo = 0U;
  c4_info[6].mFileTimeHi = 0U;
  c4_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c4_info[7].name = "isequal";
  c4_info[7].dominantType = "double";
  c4_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c4_info[7].fileTimeLo = 2864844544U;
  c4_info[7].fileTimeHi = 30108086U;
  c4_info[7].mFileTimeLo = 0U;
  c4_info[7].mFileTimeHi = 0U;
  c4_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c4_info[8].name = "eml_isequal_core";
  c4_info[8].dominantType = "double";
  c4_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c4_info[8].fileTimeLo = 3144844544U;
  c4_info[8].fileTimeHi = 30108086U;
  c4_info[8].mFileTimeLo = 0U;
  c4_info[8].mFileTimeHi = 0U;
  c4_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c4_info[9].name = "eml_const_nonsingleton_dim";
  c4_info[9].dominantType = "logical";
  c4_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  c4_info[9].fileTimeLo = 2244844544U;
  c4_info[9].fileTimeHi = 30108086U;
  c4_info[9].mFileTimeLo = 0U;
  c4_info[9].mFileTimeHi = 0U;
  c4_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c4_info[10].name = "isfixed";
  c4_info[10].dominantType = "embedded.fi";
  c4_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  c4_info[10].fileTimeLo = 875520000U;
  c4_info[10].fileTimeHi = 30114375U;
  c4_info[10].mFileTimeLo = 0U;
  c4_info[10].mFileTimeHi = 0U;
  c4_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  c4_info[11].name = "get";
  c4_info[11].dominantType = "embedded.numerictype";
  c4_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m";
  c4_info[11].fileTimeLo = 4170487296U;
  c4_info[11].fileTimeHi = 30114374U;
  c4_info[11].mFileTimeLo = 0U;
  c4_info[11].mFileTimeHi = 0U;
  c4_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c4_info[12].name = "numerictype";
  c4_info[12].dominantType = "double";
  c4_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m";
  c4_info[12].fileTimeLo = 435520000U;
  c4_info[12].fileTimeHi = 30114375U;
  c4_info[12].mFileTimeLo = 0U;
  c4_info[12].mFileTimeHi = 0U;
  c4_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m";
  c4_info[13].name = "length";
  c4_info[13].dominantType = "cell";
  c4_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c4_info[13].fileTimeLo = 2884844544U;
  c4_info[13].fileTimeHi = 30108086U;
  c4_info[13].mFileTimeLo = 0U;
  c4_info[13].mFileTimeHi = 0U;
  c4_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c4_info[14].name = "fimath";
  c4_info[14].dominantType = "embedded.fi";
  c4_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m";
  c4_info[14].fileTimeLo = 775520000U;
  c4_info[14].fileTimeHi = 30114375U;
  c4_info[14].mFileTimeLo = 0U;
  c4_info[14].mFileTimeHi = 0U;
  c4_info[15].context = "";
  c4_info[15].name = "fi_impl";
  c4_info[15].dominantType = "";
  c4_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m";
  c4_info[15].fileTimeLo = 275520000U;
  c4_info[15].fileTimeHi = 30114375U;
  c4_info[15].mFileTimeLo = 0U;
  c4_info[15].mFileTimeHi = 0U;
  c4_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c4_info[16].name = "isfloat";
  c4_info[16].dominantType = "embedded.fi";
  c4_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m";
  c4_info[16].fileTimeLo = 875520000U;
  c4_info[16].fileTimeHi = 30114375U;
  c4_info[16].mFileTimeLo = 0U;
  c4_info[16].mFileTimeHi = 0U;
  c4_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput";
  c4_info[17].name = "numerictype";
  c4_info[17].dominantType = "embedded.fi";
  c4_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m";
  c4_info[17].fileTimeLo = 995520000U;
  c4_info[17].fileTimeHi = 30114375U;
  c4_info[17].mFileTimeLo = 0U;
  c4_info[17].mFileTimeHi = 0U;
  c4_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c4_info[18].name = "eml_fi_checkforntype";
  c4_info[18].dominantType = "embedded.fi";
  c4_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m";
  c4_info[18].fileTimeLo = 255520000U;
  c4_info[18].fileTimeHi = 30114375U;
  c4_info[18].mFileTimeLo = 0U;
  c4_info[18].mFileTimeHi = 0U;
  c4_info[19].context = "";
  c4_info[19].name = "uint8";
  c4_info[19].dominantType = "embedded.fi";
  c4_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m";
  c4_info[19].fileTimeLo = 1115520000U;
  c4_info[19].fileTimeHi = 30114375U;
  c4_info[19].mFileTimeLo = 0U;
  c4_info[19].mFileTimeHi = 0U;
  c4_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m";
  c4_info[20].name = "eml_fi_getStoredIntValAsDType";
  c4_info[20].dominantType = "embedded.fi";
  c4_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getStoredIntValAsDType.m";
  c4_info[20].fileTimeLo = 655520000U;
  c4_info[20].fileTimeHi = 30114375U;
  c4_info[20].mFileTimeLo = 0U;
  c4_info[20].mFileTimeHi = 0U;
  c4_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c4_info[21].name = "eml_fi_checkforerror";
  c4_info[21].dominantType = "embedded.numerictype";
  c4_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m";
  c4_info[21].fileTimeLo = 255520000U;
  c4_info[21].fileTimeHi = 30114375U;
  c4_info[21].mFileTimeLo = 0U;
  c4_info[21].mFileTimeHi = 0U;
  c4_info[22].context = "";
  c4_info[22].name = "bitcmp";
  c4_info[22].dominantType = "embedded.fi";
  c4_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitcmp.m";
  c4_info[22].fileTimeLo = 235520000U;
  c4_info[22].fileTimeHi = 30114375U;
  c4_info[22].mFileTimeLo = 0U;
  c4_info[22].mFileTimeHi = 0U;
  c4_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitcmp.m";
  c4_info[23].name = "isslopebiasscaled";
  c4_info[23].dominantType = "embedded.numerictype";
  c4_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isslopebiasscaled.m";
  c4_info[23].fileTimeLo = 395520000U;
  c4_info[23].fileTimeHi = 30114375U;
  c4_info[23].mFileTimeLo = 0U;
  c4_info[23].mFileTimeHi = 0U;
  c4_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  c4_info[24].name = "isnan";
  c4_info[24].dominantType = "double";
  c4_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c4_info[24].fileTimeLo = 2884844544U;
  c4_info[24].fileTimeHi = 30108086U;
  c4_info[24].mFileTimeLo = 0U;
  c4_info[24].mFileTimeHi = 0U;
  c4_info[25].context = "";
  c4_info[25].name = "bitconcat";
  c4_info[25].dominantType = "embedded.fi";
  c4_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitconcat.m";
  c4_info[25].fileTimeLo = 235520000U;
  c4_info[25].fileTimeHi = 30114375U;
  c4_info[25].mFileTimeLo = 0U;
  c4_info[25].mFileTimeHi = 0U;
  c4_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitconcat.m!bitconcat_checkarg";
  c4_info[26].name = "eml_isslopebiasscaled";
  c4_info[26].dominantType = "embedded.fi";
  c4_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m";
  c4_info[26].fileTimeLo = 695520000U;
  c4_info[26].fileTimeHi = 30114375U;
  c4_info[26].mFileTimeLo = 0U;
  c4_info[26].mFileTimeHi = 0U;
  c4_info[27].context = "";
  c4_info[27].name = "plus";
  c4_info[27].dominantType = "embedded.fi";
  c4_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c4_info[27].fileTimeLo = 995520000U;
  c4_info[27].fileTimeHi = 30114375U;
  c4_info[27].mFileTimeLo = 0U;
  c4_info[27].mFileTimeHi = 0U;
  c4_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c4_info[28].name = "isscaledtype";
  c4_info[28].dominantType = "embedded.fi";
  c4_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m";
  c4_info[28].fileTimeLo = 895520000U;
  c4_info[28].fileTimeHi = 30114375U;
  c4_info[28].mFileTimeLo = 0U;
  c4_info[28].mFileTimeHi = 0U;
  c4_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c4_info[29].name = "eml_checkfimathforbinaryops";
  c4_info[29].dominantType = "embedded.fi";
  c4_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_checkfimathforbinaryops.m";
  c4_info[29].fileTimeLo = 615520000U;
  c4_info[29].fileTimeHi = 30114375U;
  c4_info[29].mFileTimeLo = 0U;
  c4_info[29].mFileTimeHi = 0U;
  c4_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_checkfimathforbinaryops.m";
  c4_info[30].name = "isequal";
  c4_info[30].dominantType = "embedded.fimath";
  c4_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fimath/isequal.m";
  c4_info[30].fileTimeLo = 4190487296U;
  c4_info[30].fileTimeHi = 30114374U;
  c4_info[30].mFileTimeLo = 0U;
  c4_info[30].mFileTimeHi = 0U;
  c4_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c4_info[31].name = "get";
  c4_info[31].dominantType = "embedded.fimath";
  c4_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fimath/get.m";
  c4_info[31].fileTimeLo = 4190487296U;
  c4_info[31].fileTimeHi = 30114374U;
  c4_info[31].mFileTimeLo = 0U;
  c4_info[31].mFileTimeHi = 0U;
  c4_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c4_info[32].name = "strcmpi";
  c4_info[32].dominantType = "char";
  c4_info[32].resolved = "[IXMB]$matlabroot$/toolbox/matlab/strfun/strcmpi";
  c4_info[32].fileTimeLo = 0U;
  c4_info[32].fileTimeHi = 0U;
  c4_info[32].mFileTimeLo = 0U;
  c4_info[32].mFileTimeHi = 0U;
  c4_info[33].context = "";
  c4_info[33].name = "getmsb";
  c4_info[33].dominantType = "embedded.fi";
  c4_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m";
  c4_info[33].fileTimeLo = 795520000U;
  c4_info[33].fileTimeHi = 30114375U;
  c4_info[33].mFileTimeLo = 0U;
  c4_info[33].mFileTimeHi = 0U;
  c4_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m";
  c4_info[34].name = "eml_bitop_index_checks";
  c4_info[34].dominantType = "embedded.fi";
  c4_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_bitop_index_checks.m";
  c4_info[34].fileTimeLo = 615520000U;
  c4_info[34].fileTimeHi = 30114375U;
  c4_info[34].mFileTimeLo = 0U;
  c4_info[34].mFileTimeHi = 0U;
  c4_info[35].context = "";
  c4_info[35].name = "eq";
  c4_info[35].dominantType = "embedded.fi";
  c4_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m";
  c4_info[35].fileTimeLo = 755520000U;
  c4_info[35].fileTimeHi = 30114375U;
  c4_info[35].mFileTimeLo = 0U;
  c4_info[35].mFileTimeHi = 0U;
  c4_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m";
  c4_info[36].name = "eml_check_same_bias";
  c4_info[36].dominantType = "embedded.fi";
  c4_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_check_same_bias.m";
  c4_info[36].fileTimeLo = 615520000U;
  c4_info[36].fileTimeHi = 30114375U;
  c4_info[36].mFileTimeLo = 0U;
  c4_info[36].mFileTimeHi = 0U;
  c4_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m";
  c4_info[37].name = "eml_make_same_complexity";
  c4_info[37].dominantType = "embedded.fi";
  c4_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_make_same_complexity.m";
  c4_info[37].fileTimeLo = 695520000U;
  c4_info[37].fileTimeHi = 30114375U;
  c4_info[37].mFileTimeLo = 0U;
  c4_info[37].mFileTimeHi = 0U;
  c4_info[38].context = "";
  c4_info[38].name = "ne";
  c4_info[38].dominantType = "embedded.fi";
  c4_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m";
  c4_info[38].fileTimeLo = 995520000U;
  c4_info[38].fileTimeHi = 30114375U;
  c4_info[38].mFileTimeLo = 0U;
  c4_info[38].mFileTimeHi = 0U;
  c4_info[39].context = "";
  c4_info[39].name = "bitand";
  c4_info[39].dominantType = "embedded.fi";
  c4_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m";
  c4_info[39].fileTimeLo = 215520000U;
  c4_info[39].fileTimeHi = 30114375U;
  c4_info[39].mFileTimeLo = 0U;
  c4_info[39].mFileTimeHi = 0U;
  c4_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m";
  c4_info[40].name = "isequal";
  c4_info[40].dominantType = "embedded.numerictype";
  c4_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/isequal.m";
  c4_info[40].fileTimeLo = 4190487296U;
  c4_info[40].fileTimeHi = 30114374U;
  c4_info[40].mFileTimeLo = 0U;
  c4_info[40].mFileTimeHi = 0U;
  c4_info[41].context = "";
  c4_info[41].name = "all";
  c4_info[41].dominantType = "embedded.fi";
  c4_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/all.m";
  c4_info[41].fileTimeLo = 195520000U;
  c4_info[41].fileTimeHi = 30114375U;
  c4_info[41].mFileTimeLo = 0U;
  c4_info[41].mFileTimeHi = 0U;
  c4_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m";
  c4_info[42].name = "eml_type_relop_const";
  c4_info[42].dominantType = "embedded.fi";
  c4_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m";
  c4_info[42].fileTimeLo = 735520000U;
  c4_info[42].fileTimeHi = 30114375U;
  c4_info[42].mFileTimeLo = 0U;
  c4_info[42].mFileTimeHi = 0U;
}

static uint8_T c4_uint8(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c4_A)
{
  uint8_T c4_xfi;
  const mxArray *c4_m73 = NULL;
  const mxArray *c4_m74 = NULL;
  c4_xfi = c4_A;
  sf_mex_destroy(&c4_m73);
  sf_mex_destroy(&c4_m74);
  return c4_xfi;
}

static uint8_T c4_bitcmp(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c4_a)
{
  const mxArray *c4_m75 = NULL;
  const mxArray *c4_m76 = NULL;
  const mxArray *c4_m77 = NULL;
  const mxArray *c4_m78 = NULL;
  const mxArray *c4_m79 = NULL;
  const mxArray *c4_m80 = NULL;
  uint8_T c4_c_r;
  sf_mex_destroy(&c4_m75);
  sf_mex_destroy(&c4_m76);
  sf_mex_destroy(&c4_m77);
  sf_mex_destroy(&c4_m78);
  sf_mex_destroy(&c4_m79);
  sf_mex_destroy(&c4_m80);
  c4_c_r = (uint8_T)((uint8_T)~c4_a & 1U);
  return c4_c_r;
}

static int8_T c4_b_bitcmp(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_a)
{
  const mxArray *c4_m81 = NULL;
  const mxArray *c4_m82 = NULL;
  const mxArray *c4_m83 = NULL;
  const mxArray *c4_m84 = NULL;
  const mxArray *c4_m85 = NULL;
  const mxArray *c4_m86 = NULL;
  int8_T c4_c_r;
  sf_mex_destroy(&c4_m81);
  sf_mex_destroy(&c4_m82);
  sf_mex_destroy(&c4_m83);
  sf_mex_destroy(&c4_m84);
  sf_mex_destroy(&c4_m85);
  sf_mex_destroy(&c4_m86);
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
  sf_debug_symbol_scope_push_eml(0U, 8U, 8U, c4_c_debug_family_names,
    c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c4_nargin, 0U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_nargout, 1U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_u1, 2U, c4_c_sf_marshallOut,
    c4_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_u2, 3U, c4_c_sf_marshallOut,
    c4_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_b_in, 4U, c4_h_sf_marshallOut,
    c4_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c4_diff, 5U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c4_carry, 6U, c4_f_sf_marshallOut,
    c4_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c4_overflow, 7U, c4_f_sf_marshallOut,
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
  sf_debug_symbol_scope_pop();
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
  const mxArray *c4_m87 = NULL;
  const mxArray *c4_m88 = NULL;
  const mxArray *c4_m89 = NULL;
  const mxArray *c4_m90 = NULL;
  const mxArray *c4_m91 = NULL;
  const mxArray *c4_m92 = NULL;
  const mxArray *c4_m93 = NULL;
  uint16_T c4_varargin_1;
  uint16_T c4_b_varargin_1;
  const mxArray *c4_m94 = NULL;
  const mxArray *c4_m95 = NULL;
  const mxArray *c4_m96 = NULL;
  const mxArray *c4_m97 = NULL;
  uint16_T c4_var1;
  int16_T c4_i4;
  const mxArray *c4_m98 = NULL;
  const mxArray *c4_m99 = NULL;
  const mxArray *c4_m100 = NULL;
  const mxArray *c4_m101 = NULL;
  const mxArray *c4_m102 = NULL;
  const mxArray *c4_m103 = NULL;
  const mxArray *c4_m104 = NULL;
  const mxArray *c4_m105 = NULL;
  const mxArray *c4_m106 = NULL;
  const mxArray *c4_m107 = NULL;
  const mxArray *c4_m108 = NULL;
  const mxArray *c4_m109 = NULL;
  const mxArray *c4_m110 = NULL;
  const mxArray *c4_m111 = NULL;
  uint16_T c4_c_varargin_1;
  uint16_T c4_d_varargin_1;
  const mxArray *c4_m112 = NULL;
  const mxArray *c4_m113 = NULL;
  const mxArray *c4_m114 = NULL;
  const mxArray *c4_m115 = NULL;
  uint16_T c4_b_var1;
  int16_T c4_i5;
  const mxArray *c4_m116 = NULL;
  const mxArray *c4_m117 = NULL;
  const mxArray *c4_m118 = NULL;
  const mxArray *c4_m119 = NULL;
  const mxArray *c4_m120 = NULL;
  const mxArray *c4_m121 = NULL;
  const mxArray *c4_m122 = NULL;
  int16_T c4_e_varargin_1;
  int16_T c4_f_varargin_1;
  const mxArray *c4_m123 = NULL;
  const mxArray *c4_m124 = NULL;
  const mxArray *c4_m125 = NULL;
  const mxArray *c4_m126 = NULL;
  int16_T c4_c_var1;
  int16_T c4_i6;
  const mxArray *c4_m127 = NULL;
  const mxArray *c4_m128 = NULL;
  const mxArray *c4_m129 = NULL;
  const mxArray *c4_m130 = NULL;
  const mxArray *c4_m131 = NULL;
  const mxArray *c4_m132 = NULL;
  const mxArray *c4_m133 = NULL;
  int16_T c4_a;
  const mxArray *c4_m134 = NULL;
  const mxArray *c4_m135 = NULL;
  const mxArray *c4_m136 = NULL;
  const mxArray *c4_m137 = NULL;
  const mxArray *c4_m138 = NULL;
  const mxArray *c4_m139 = NULL;
  const mxArray *c4_m140 = NULL;
  const mxArray *c4_m141 = NULL;
  const mxArray *c4_m142 = NULL;
  int16_T c4_i7;
  int16_T c4_i8;
  uint8_T c4_slice_temp;
  int16_T c4_g_varargin_1;
  int16_T c4_h_varargin_1;
  const mxArray *c4_m143 = NULL;
  const mxArray *c4_m144 = NULL;
  const mxArray *c4_m145 = NULL;
  const mxArray *c4_m146 = NULL;
  int16_T c4_d_var1;
  const mxArray *c4_m147 = NULL;
  const mxArray *c4_m148 = NULL;
  const mxArray *c4_m149 = NULL;
  const mxArray *c4_m150 = NULL;
  const mxArray *c4_m151 = NULL;
  const mxArray *c4_m152 = NULL;
  const mxArray *c4_m153 = NULL;
  int8_T c4_b_a;
  const mxArray *c4_m154 = NULL;
  const mxArray *c4_m155 = NULL;
  const mxArray *c4_m156 = NULL;
  const mxArray *c4_m157 = NULL;
  const mxArray *c4_m158 = NULL;
  const mxArray *c4_m159 = NULL;
  const mxArray *c4_m160 = NULL;
  const mxArray *c4_m161 = NULL;
  const mxArray *c4_m162 = NULL;
  uint8_T c4_b_slice_temp;
  int8_T c4_c_a;
  const mxArray *c4_m163 = NULL;
  const mxArray *c4_m164 = NULL;
  const mxArray *c4_m165 = NULL;
  const mxArray *c4_m166 = NULL;
  const mxArray *c4_m167 = NULL;
  const mxArray *c4_m168 = NULL;
  const mxArray *c4_m169 = NULL;
  const mxArray *c4_m170 = NULL;
  const mxArray *c4_m171 = NULL;
  uint8_T c4_c_slice_temp;
  uint8_T c4_c;
  int8_T c4_d_a;
  const mxArray *c4_m172 = NULL;
  const mxArray *c4_m173 = NULL;
  const mxArray *c4_m174 = NULL;
  const mxArray *c4_m175 = NULL;
  const mxArray *c4_m176 = NULL;
  const mxArray *c4_m177 = NULL;
  const mxArray *c4_m178 = NULL;
  const mxArray *c4_m179 = NULL;
  const mxArray *c4_m180 = NULL;
  uint8_T c4_d_slice_temp;
  uint8_T c4_b_c;
  uint8_T c4_a0;
  uint8_T c4_b0;
  const mxArray *c4_m181 = NULL;
  const mxArray *c4_m182 = NULL;
  const mxArray *c4_m183 = NULL;
  const mxArray *c4_m184 = NULL;
  const mxArray *c4_m185 = NULL;
  const mxArray *c4_m186 = NULL;
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
  const mxArray *c4_m187 = NULL;
  const mxArray *c4_m188 = NULL;
  int8_T c4_c_a1;
  uint8_T c4_e_slice_temp;
  uint8_T c4_d_c;
  uint8_T c4_c_a0;
  uint8_T c4_c_b0;
  const mxArray *c4_m189 = NULL;
  const mxArray *c4_m190 = NULL;
  const mxArray *c4_m191 = NULL;
  const mxArray *c4_m192 = NULL;
  const mxArray *c4_m193 = NULL;
  const mxArray *c4_m194 = NULL;
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
  const mxArray *c4_m195 = NULL;
  const mxArray *c4_m196 = NULL;
  const mxArray *c4_m197 = NULL;
  const mxArray *c4_m198 = NULL;
  const mxArray *c4_m199 = NULL;
  const mxArray *c4_m200 = NULL;
  const mxArray *c4_m201 = NULL;
  boolean_T guard1 = FALSE;
  sf_debug_symbol_scope_push_eml(0U, 14U, 14U, c4_b_debug_family_names,
    c4_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c4_hdl_fm, 0U, c4_i_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c4_temp_u1, 1U, c4_j_sf_marshallOut,
    c4_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_temp_u2, 2U, c4_j_sf_marshallOut,
    c4_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_temp_sum, 3U, c4_j_sf_marshallOut,
    c4_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_sign_bit, 4U, c4_f_sf_marshallOut,
    c4_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_overflow_int, 5U,
    c4_g_sf_marshallOut, c4_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_nargin, 6U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_nargout, 7U, c4_e_sf_marshallOut,
    c4_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_u1, 8U, c4_c_sf_marshallOut,
    c4_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_u2, 9U, c4_c_sf_marshallOut,
    c4_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c4_c_in, 10U, c4_h_sf_marshallOut,
    c4_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c4_sum, 11U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c4_carry, 12U, c4_f_sf_marshallOut,
    c4_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c4_overflow, 13U, c4_f_sf_marshallOut,
    c4_d_sf_marshallIn);
  CV_EML_FCN(0, 2);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 79);
  c4_hdl_fm = c4_eml_mx;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 87);
  sf_mex_destroy(&c4_m87);
  sf_mex_destroy(&c4_m88);
  sf_mex_destroy(&c4_m89);
  sf_mex_destroy(&c4_m90);
  sf_mex_destroy(&c4_m91);
  sf_mex_destroy(&c4_m92);
  sf_mex_destroy(&c4_m93);
  c4_varargin_1 = c4_bitconcat(chartInstance, 0U, c4_u1);
  c4_b_varargin_1 = c4_varargin_1;
  sf_mex_destroy(&c4_m94);
  sf_mex_destroy(&c4_m95);
  sf_mex_destroy(&c4_m96);
  sf_mex_destroy(&c4_m97);
  c4_var1 = c4_b_varargin_1;
  c4_i4 = (int16_T)c4_var1;
  c4_temp_u1 = (int16_T)(c4_i4 & 256) != 0 ? (int16_T)(c4_i4 | -256) : (int16_T)
    (c4_i4 & 255);
  sf_mex_destroy(&c4_m98);
  sf_mex_destroy(&c4_m99);
  sf_mex_destroy(&c4_m100);
  sf_mex_destroy(&c4_m101);
  sf_mex_destroy(&c4_m102);
  sf_mex_destroy(&c4_m103);
  sf_mex_destroy(&c4_m104);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 90);
  sf_mex_destroy(&c4_m105);
  sf_mex_destroy(&c4_m106);
  sf_mex_destroy(&c4_m107);
  sf_mex_destroy(&c4_m108);
  sf_mex_destroy(&c4_m109);
  sf_mex_destroy(&c4_m110);
  sf_mex_destroy(&c4_m111);
  c4_c_varargin_1 = c4_bitconcat(chartInstance, 0U, c4_u2);
  c4_d_varargin_1 = c4_c_varargin_1;
  sf_mex_destroy(&c4_m112);
  sf_mex_destroy(&c4_m113);
  sf_mex_destroy(&c4_m114);
  sf_mex_destroy(&c4_m115);
  c4_b_var1 = c4_d_varargin_1;
  c4_i5 = (int16_T)c4_b_var1;
  c4_temp_u2 = (int16_T)(c4_i5 & 256) != 0 ? (int16_T)(c4_i5 | -256) : (int16_T)
    (c4_i5 & 255);
  sf_mex_destroy(&c4_m116);
  sf_mex_destroy(&c4_m117);
  sf_mex_destroy(&c4_m118);
  sf_mex_destroy(&c4_m119);
  sf_mex_destroy(&c4_m120);
  sf_mex_destroy(&c4_m121);
  sf_mex_destroy(&c4_m122);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 93);
  c4_e_varargin_1 = c4_b_plus(chartInstance, c4_plus(chartInstance, c4_temp_u1,
    c4_temp_u2), c4_c_in);
  c4_f_varargin_1 = c4_e_varargin_1;
  sf_mex_destroy(&c4_m123);
  sf_mex_destroy(&c4_m124);
  sf_mex_destroy(&c4_m125);
  sf_mex_destroy(&c4_m126);
  c4_c_var1 = c4_f_varargin_1;
  c4_i6 = c4_c_var1;
  c4_temp_sum = (int16_T)(c4_i6 & 256) != 0 ? (int16_T)(c4_i6 | -256) : (int16_T)
    (c4_i6 & 255);
  sf_mex_destroy(&c4_m127);
  sf_mex_destroy(&c4_m128);
  sf_mex_destroy(&c4_m129);
  sf_mex_destroy(&c4_m130);
  sf_mex_destroy(&c4_m131);
  sf_mex_destroy(&c4_m132);
  sf_mex_destroy(&c4_m133);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 96);
  c4_a = c4_temp_sum;
  sf_mex_destroy(&c4_m134);
  sf_mex_destroy(&c4_m135);
  sf_mex_destroy(&c4_m136);
  sf_mex_destroy(&c4_m137);
  sf_mex_destroy(&c4_m138);
  sf_mex_destroy(&c4_m139);
  sf_mex_destroy(&c4_m140);
  sf_mex_destroy(&c4_m141);
  sf_mex_destroy(&c4_m142);
  *c4_carry = 0U;
  c4_i7 = (int16_T)(uint16_T)((uint32_T)(uint16_T)((uint16_T)c4_a & 511U) >> 8);
  c4_i8 = (int16_T)(((int16_T)(c4_i7 & 256) != 0 ? (int16_T)(c4_i7 | -256) :
                     (int16_T)(c4_i7 & 255)) & 1);
  c4_slice_temp = (uint8_T)((uint8_T)((int16_T)(c4_i8 & 256) != 0 ? (int16_T)
    (c4_i8 | -256) : (int16_T)(c4_i8 & 255)) & 1U);
  *c4_carry = c4_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 99);
  c4_g_varargin_1 = c4_temp_sum;
  c4_h_varargin_1 = c4_g_varargin_1;
  sf_mex_destroy(&c4_m143);
  sf_mex_destroy(&c4_m144);
  sf_mex_destroy(&c4_m145);
  sf_mex_destroy(&c4_m146);
  c4_d_var1 = c4_h_varargin_1;
  *c4_sum = (int8_T)c4_d_var1;
  sf_mex_destroy(&c4_m147);
  sf_mex_destroy(&c4_m148);
  sf_mex_destroy(&c4_m149);
  sf_mex_destroy(&c4_m150);
  sf_mex_destroy(&c4_m151);
  sf_mex_destroy(&c4_m152);
  sf_mex_destroy(&c4_m153);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 102);
  c4_b_a = *c4_sum;
  sf_mex_destroy(&c4_m154);
  sf_mex_destroy(&c4_m155);
  sf_mex_destroy(&c4_m156);
  sf_mex_destroy(&c4_m157);
  sf_mex_destroy(&c4_m158);
  sf_mex_destroy(&c4_m159);
  sf_mex_destroy(&c4_m160);
  sf_mex_destroy(&c4_m161);
  sf_mex_destroy(&c4_m162);
  c4_sign_bit = 0U;
  c4_b_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
    (uint8_T)c4_b_a >> 7) & 1) & 1U);
  c4_sign_bit = c4_b_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 106);
  c4_c_a = c4_u1;
  sf_mex_destroy(&c4_m163);
  sf_mex_destroy(&c4_m164);
  sf_mex_destroy(&c4_m165);
  sf_mex_destroy(&c4_m166);
  sf_mex_destroy(&c4_m167);
  sf_mex_destroy(&c4_m168);
  sf_mex_destroy(&c4_m169);
  sf_mex_destroy(&c4_m170);
  sf_mex_destroy(&c4_m171);
  c4_c_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
    (uint8_T)c4_c_a >> 7) & 1) & 1U);
  c4_c = c4_c_slice_temp;
  c4_d_a = c4_u2;
  sf_mex_destroy(&c4_m172);
  sf_mex_destroy(&c4_m173);
  sf_mex_destroy(&c4_m174);
  sf_mex_destroy(&c4_m175);
  sf_mex_destroy(&c4_m176);
  sf_mex_destroy(&c4_m177);
  sf_mex_destroy(&c4_m178);
  sf_mex_destroy(&c4_m179);
  sf_mex_destroy(&c4_m180);
  c4_d_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
    (uint8_T)c4_d_a >> 7) & 1) & 1U);
  c4_b_c = c4_d_slice_temp;
  c4_a0 = c4_c;
  c4_b0 = c4_b_c;
  sf_mex_destroy(&c4_m181);
  sf_mex_destroy(&c4_m182);
  sf_mex_destroy(&c4_m183);
  sf_mex_destroy(&c4_m184);
  sf_mex_destroy(&c4_m185);
  sf_mex_destroy(&c4_m186);
  c4_e_a = c4_a0;
  c4_b = c4_b0;
  c4_b_a0 = c4_e_a;
  c4_b_b0 = c4_b;
  c4_a1 = c4_b_a0;
  c4_b1 = c4_b_b0;
  c4_b_a1 = c4_a1;
  c4_b_b1 = c4_b1;
  c4_c_c = (c4_b_a1 == c4_b_b1);
  guard1 = FALSE;
  if (c4_c_c) {
    c4_f_a = c4_u1;
    sf_mex_destroy(&c4_m187);
    sf_mex_destroy(&c4_m188);
    c4_c_a1 = c4_f_a;
    c4_e_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
      (uint8_T)c4_c_a1 >> 7) & 1) & 1U);
    c4_d_c = c4_e_slice_temp;
    c4_c_a0 = c4_sign_bit;
    c4_c_b0 = c4_d_c;
    sf_mex_destroy(&c4_m189);
    sf_mex_destroy(&c4_m190);
    sf_mex_destroy(&c4_m191);
    sf_mex_destroy(&c4_m192);
    sf_mex_destroy(&c4_m193);
    sf_mex_destroy(&c4_m194);
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
      c4_e_b0 = TRUE;
    } else {
      guard1 = TRUE;
    }
  } else {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    c4_e_b0 = FALSE;
  }

  c4_overflow_int = (uint8_T)c4_e_b0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 110);
  c4_i_varargin_1 = c4_overflow_int;
  c4_j_varargin_1 = c4_i_varargin_1;
  c4_e_var1 = c4_j_varargin_1;
  *c4_overflow = (uint8_T)(c4_e_var1 & 1U);
  sf_mex_destroy(&c4_m195);
  sf_mex_destroy(&c4_m196);
  sf_mex_destroy(&c4_m197);
  sf_mex_destroy(&c4_m198);
  sf_mex_destroy(&c4_m199);
  sf_mex_destroy(&c4_m200);
  sf_mex_destroy(&c4_m201);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -110);
  sf_debug_symbol_scope_pop();
}

static uint16_T c4_bitconcat(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c4_varargin_1, int8_T c4_varargin_2)
{
  uint8_T c4_b_varargin_1;
  int8_T c4_b_varargin_2;
  const mxArray *c4_m202 = NULL;
  const mxArray *c4_m203 = NULL;
  int8_T c4_varargout_2;
  const mxArray *c4_m204 = NULL;
  const mxArray *c4_m205 = NULL;
  uint8_T c4_slice_temp;
  c4_b_varargin_1 = c4_varargin_1;
  c4_b_varargin_2 = c4_varargin_2;
  sf_mex_destroy(&c4_m202);
  sf_mex_destroy(&c4_m203);
  c4_varargout_2 = c4_b_varargin_2;
  sf_mex_destroy(&c4_m204);
  sf_mex_destroy(&c4_m205);
  c4_slice_temp = (uint8_T)c4_varargout_2;
  return (uint16_T)((uint16_T)((uint16_T)((uint16_T)((uint16_T)((uint16_T)
    c4_b_varargin_1 & 511U) << 8) & 511U) | (uint16_T)((uint16_T)c4_slice_temp &
    511U)) & 511U);
}

static int16_T c4_plus(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int16_T c4_a0, int16_T c4_b0)
{
  int16_T c4_c;
  const mxArray *c4_m206 = NULL;
  const mxArray *c4_m207 = NULL;
  int16_T c4_a;
  int16_T c4_b;
  const mxArray *c4_m208 = NULL;
  const mxArray *c4_m209 = NULL;
  const mxArray *c4_m210 = NULL;
  const mxArray *c4_m211 = NULL;
  const mxArray *c4_m212 = NULL;
  const mxArray *c4_m213 = NULL;
  const mxArray *c4_m214 = NULL;
  const mxArray *c4_m215 = NULL;
  const mxArray *c4_m216 = NULL;
  const mxArray *c4_m217 = NULL;
  const mxArray *c4_m218 = NULL;
  const mxArray *c4_m219 = NULL;
  const mxArray *c4_m220 = NULL;
  const mxArray *c4_m221 = NULL;
  const mxArray *c4_m222 = NULL;
  const mxArray *c4_m223 = NULL;
  int16_T c4_i9;
  int16_T c4_i10;
  int16_T c4_i11;
  const mxArray *c4_m224 = NULL;
  const mxArray *c4_m225 = NULL;
  const mxArray *c4_m226 = NULL;
  const mxArray *c4_m227 = NULL;
  const mxArray *c4_m228 = NULL;
  const mxArray *c4_m229 = NULL;
  sf_mex_destroy(&c4_m206);
  sf_mex_destroy(&c4_m207);
  c4_a = c4_a0;
  c4_b = c4_b0;
  sf_mex_destroy(&c4_m208);
  sf_mex_destroy(&c4_m209);
  sf_mex_destroy(&c4_m210);
  sf_mex_destroy(&c4_m211);
  sf_mex_destroy(&c4_m212);
  sf_mex_destroy(&c4_m213);
  sf_mex_destroy(&c4_m214);
  sf_mex_destroy(&c4_m215);
  sf_mex_destroy(&c4_m216);
  sf_mex_destroy(&c4_m217);
  sf_mex_destroy(&c4_m218);
  sf_mex_destroy(&c4_m219);
  sf_mex_destroy(&c4_m220);
  sf_mex_destroy(&c4_m221);
  sf_mex_destroy(&c4_m222);
  sf_mex_destroy(&c4_m223);
  c4_i9 = c4_a;
  c4_i10 = c4_b;
  c4_i11 = (int16_T)(((int16_T)(c4_i9 & 512) != 0 ? (int16_T)(c4_i9 | -512) :
                      (int16_T)(c4_i9 & 511)) + ((int16_T)(c4_i10 & 512) != 0 ?
                      (int16_T)(c4_i10 | -512) : (int16_T)(c4_i10 & 511)));
  c4_c = (int16_T)(c4_i11 & 512) != 0 ? (int16_T)(c4_i11 | -512) : (int16_T)
    (c4_i11 & 511);
  sf_mex_destroy(&c4_m224);
  sf_mex_destroy(&c4_m225);
  sf_mex_destroy(&c4_m226);
  sf_mex_destroy(&c4_m227);
  sf_mex_destroy(&c4_m228);
  sf_mex_destroy(&c4_m229);
  return c4_c;
}

static int16_T c4_b_plus(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int16_T c4_a0, uint8_T c4_b0)
{
  int16_T c4_c;
  const mxArray *c4_m230 = NULL;
  const mxArray *c4_m231 = NULL;
  int16_T c4_a;
  uint8_T c4_b;
  const mxArray *c4_m232 = NULL;
  const mxArray *c4_m233 = NULL;
  const mxArray *c4_m234 = NULL;
  const mxArray *c4_m235 = NULL;
  const mxArray *c4_m236 = NULL;
  const mxArray *c4_m237 = NULL;
  const mxArray *c4_m238 = NULL;
  const mxArray *c4_m239 = NULL;
  const mxArray *c4_m240 = NULL;
  const mxArray *c4_m241 = NULL;
  const mxArray *c4_m242 = NULL;
  const mxArray *c4_m243 = NULL;
  const mxArray *c4_m244 = NULL;
  const mxArray *c4_m245 = NULL;
  const mxArray *c4_m246 = NULL;
  const mxArray *c4_m247 = NULL;
  int16_T c4_i12;
  int16_T c4_i13;
  int16_T c4_i14;
  const mxArray *c4_m248 = NULL;
  const mxArray *c4_m249 = NULL;
  const mxArray *c4_m250 = NULL;
  const mxArray *c4_m251 = NULL;
  const mxArray *c4_m252 = NULL;
  const mxArray *c4_m253 = NULL;
  sf_mex_destroy(&c4_m230);
  sf_mex_destroy(&c4_m231);
  c4_a = c4_a0;
  c4_b = c4_b0;
  sf_mex_destroy(&c4_m232);
  sf_mex_destroy(&c4_m233);
  sf_mex_destroy(&c4_m234);
  sf_mex_destroy(&c4_m235);
  sf_mex_destroy(&c4_m236);
  sf_mex_destroy(&c4_m237);
  sf_mex_destroy(&c4_m238);
  sf_mex_destroy(&c4_m239);
  sf_mex_destroy(&c4_m240);
  sf_mex_destroy(&c4_m241);
  sf_mex_destroy(&c4_m242);
  sf_mex_destroy(&c4_m243);
  sf_mex_destroy(&c4_m244);
  sf_mex_destroy(&c4_m245);
  sf_mex_destroy(&c4_m246);
  sf_mex_destroy(&c4_m247);
  c4_i12 = c4_a;
  c4_i13 = (int16_T)c4_b;
  c4_i14 = (int16_T)(((int16_T)(c4_i12 & 1024) != 0 ? (int16_T)(c4_i12 | -1024) :
                      (int16_T)(c4_i12 & 1023)) + ((int16_T)(c4_i13 & 1024) != 0
    ? (int16_T)(c4_i13 | -1024) : (int16_T)(c4_i13 & 1023)));
  c4_c = (int16_T)(c4_i14 & 1024) != 0 ? (int16_T)(c4_i14 | -1024) : (int16_T)
    (c4_i14 & 1023);
  sf_mex_destroy(&c4_m248);
  sf_mex_destroy(&c4_m249);
  sf_mex_destroy(&c4_m250);
  sf_mex_destroy(&c4_m251);
  sf_mex_destroy(&c4_m252);
  sf_mex_destroy(&c4_m253);
  return c4_c;
}

static int8_T c4_bitand(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_a, int8_T c4_b)
{
  const mxArray *c4_m254 = NULL;
  const mxArray *c4_m255 = NULL;
  int8_T c4_c_uint;
  sf_mex_destroy(&c4_m254);
  sf_mex_destroy(&c4_m255);
  c4_c_uint = (int8_T)(c4_a & c4_b);
  return c4_c_uint;
}

static boolean_T c4_all(SFc4_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c4_x)
{
  int8_T c4_b_x;
  int8_T c4_a0;
  const mxArray *c4_m256 = NULL;
  const mxArray *c4_m257 = NULL;
  int8_T c4_a;
  int8_T c4_b_a0;
  int8_T c4_a1;
  int8_T c4_b_a1;
  c4_b_x = c4_x;
  c4_a0 = c4_b_x;
  sf_mex_destroy(&c4_m256);
  sf_mex_destroy(&c4_m257);
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
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c4_mxArrayOutData, c4_y);
  return c4_mxArrayOutData;
}

static int32_T c4_k_emlrt_marshallIn(SFc4_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i15;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i15, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i15;
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
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c4_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_b_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c4_mxArrayOutData, c4_y);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
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
    sf_mex_assign(&c4_b_y, sf_mex_create("y", &c4_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c4_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c4_eml_mx), 15, "numerictype", 14, sf_mex_dup(c4_d_eml_mx), 15,
      "simulinkarray", 14, c4_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c4_mxArrayOutData, c4_y);
  } else {
    sf_mex_assign(&c4_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
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
  sf_mex_check_fi(c4_parentId, c4_u, 0, 0U, 0, c4_eml_mx, c4_b_eml_mx);
  sf_mex_assign(&c4_mxFi, sf_mex_dup(c4_u));
  sf_mex_assign(&c4_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c4_mxFi)));
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
}

/* SFunction Glue Code */
void sf_c4_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3930751794U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1539486091U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(757707865U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4016987166U);
}

mxArray *sf_c4_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(1663717889U);
    pr[1] = (double)(3176189522U);
    pr[2] = (double)(1956633767U);
    pr[3] = (double)(791771162U);
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
    chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_hdlcodercpu_emlMachineNumber_,
           4,
           1,
           1,
           6,
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
        _SFD_CV_INIT_EML(0,3,0,0,1,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2182);
        _SFD_CV_INIT_EML_FCN(0,1,"sub_w_borrow",2182,-1,2502);
        _SFD_CV_INIT_EML_FCN(0,2,"sum_w_carry",2502,-1,3640);

        {
          static int caseStart[] = { -1, 903, 950, 1028, 1171, 1336, 1429, 1505,
            1606 };

          static int caseExprEnd[] = { 8, 909, 956, 1034, 1177, 1342, 1435, 1511,
            1612 };

          _SFD_CV_INIT_EML_SWITCH(0,0,879,898,1686,9,&(caseStart[0]),
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
      sf_debug_reset_current_state_configuration(_hdlcodercpu_emlMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
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
  sf_c4_hdlcodercpu_eml((SFc4_hdlcodercpu_emlInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c4_hdlcodercpu_eml(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
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
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c4_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
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
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c4_hdlcodercpu_eml((SFc4_hdlcodercpu_emlInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
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
    initialize_params_c4_hdlcodercpu_eml((SFc4_hdlcodercpu_emlInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"hdlcodercpu_eml","hdlcodercpu_eml",4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml","hdlcodercpu_eml",4,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml",
      "hdlcodercpu_eml",4,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",
        4,4);
      sf_mark_chart_reusable_outputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",4,2);
    }

    sf_set_rtw_dwork_info(S,"hdlcodercpu_eml","hdlcodercpu_eml",4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(337941381U));
  ssSetChecksum1(S,(4278306815U));
  ssSetChecksum2(S,(1614166623U));
  ssSetChecksum3(S,(495670109U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c4_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "hdlcodercpu_eml", "hdlcodercpu_eml",4);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_hdlcodercpu_eml(SimStruct *S)
{
  SFc4_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc4_hdlcodercpu_emlInstanceStruct *)malloc(sizeof
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
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
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
