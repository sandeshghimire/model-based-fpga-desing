/* Include files */

#include "blascompat32.h"
#include "hdlcodercpu_eml_sfun.h"
#include "c8_hdlcodercpu_eml.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "hdlcodercpu_eml_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const mxArray *c8_eml_mx;
static const char * c8_debug_family_names[13] = { "hdl_fm", "overflow", "c_out",
  "sign_bit", "is_zero", "zero_ufix1", "nargin", "nargout", "select", "input",
  "in_flags", "out_flags", "shift_out" };

static const mxArray *c8_b_eml_mx;
static const mxArray *c8_c_eml_mx;
static const mxArray *c8_d_eml_mx;
static const mxArray *c8_e_eml_mx;

/* Function Declarations */
static void initialize_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initialize_params_c8_hdlcodercpu_eml
  (SFc8_hdlcodercpu_emlInstanceStruct *chartInstance);
static void enable_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void disable_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c8_update_debugger_state_c8_hdlcodercpu_eml
  (SFc8_hdlcodercpu_emlInstanceStruct *chartInstance);
static void ext_mode_exec_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static const mxArray *get_sim_state_c8_hdlcodercpu_eml
  (SFc8_hdlcodercpu_emlInstanceStruct *chartInstance);
static void set_sim_state_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c8_st);
static void finalize_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void sf_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c8_chartstep_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initSimStructsc8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber);
static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData);
static int8_T c8_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static uint8_T c8_b_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static real_T c8_c_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_e_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static uint8_T c8_d_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_f_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static uint8_T c8_e_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_is_zero, const char_T *c8_identifier);
static uint8_T c8_f_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_g_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static uint8_T c8_g_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_h_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static void c8_info_helper(c8_ResolvedFunctionInfo c8_info[39]);
static uint8_T c8_uint8(SFc8_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c8_A);
static int8_T c8_bitsra(SFc8_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c8_ain);
static void c8_isfloat(SFc8_hdlcodercpu_emlInstanceStruct *chartInstance);
static int8_T c8_bitsll(SFc8_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c8_ain);
static uint8_T c8_bitxor(SFc8_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c8_a, uint8_T c8_b);
static boolean_T c8_all(SFc8_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c8_x);
static const mxArray *c8_i_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int32_T c8_h_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_j_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static uint8_T c8_i_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_out_flags, const char_T *c8_identifier);
static uint8_T c8_j_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_k_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_l_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int8_T c8_k_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_shift_out, const char_T *c8_identifier);
static int8_T c8_l_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static void init_dsm_address_info(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  int32_T *c8_sfEvent;
  uint8_T *c8_is_active_c8_hdlcodercpu_eml;
  c8_is_active_c8_hdlcodercpu_eml = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c8_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  *c8_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  *c8_is_active_c8_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c8_e_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 1.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c8_d_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 2.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c8_c_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 4.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c8_b_eml_mx, sf_mex_call_debug("numerictype", 1U, 10U, 15,
    "WordLength", 6, 8.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c8_eml_mx, sf_mex_call_debug("fimath", 1U, 38U, 15, "RoundMode",
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

static void initialize_params_c8_hdlcodercpu_eml
  (SFc8_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void enable_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c8_update_debugger_state_c8_hdlcodercpu_eml
  (SFc8_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void ext_mode_exec_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
  c8_update_debugger_state_c8_hdlcodercpu_eml(chartInstance);
}

static const mxArray *get_sim_state_c8_hdlcodercpu_eml
  (SFc8_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c8_st;
  const mxArray *c8_y = NULL;
  uint8_T c8_hoistedGlobal;
  uint8_T c8_u;
  const mxArray *c8_b_y = NULL;
  uint8_T c8_b_u;
  const mxArray *c8_c_y = NULL;
  int8_T c8_b_hoistedGlobal;
  int8_T c8_c_u;
  const mxArray *c8_d_y = NULL;
  int8_T c8_d_u;
  const mxArray *c8_e_y = NULL;
  uint8_T c8_c_hoistedGlobal;
  uint8_T c8_e_u;
  const mxArray *c8_f_y = NULL;
  uint8_T *c8_out_flags;
  int8_T *c8_shift_out;
  uint8_T *c8_is_active_c8_hdlcodercpu_eml;
  c8_shift_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c8_is_active_c8_hdlcodercpu_eml = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c8_st = NULL;
  c8_st = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_createcellarray(3));
  c8_hoistedGlobal = *c8_out_flags;
  c8_u = c8_hoistedGlobal;
  c8_b_y = NULL;
  c8_b_u = c8_u;
  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c8_b_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_c_eml_mx), 15,
    "simulinkarray", 14, c8_c_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c8_y, 0, c8_b_y);
  c8_b_hoistedGlobal = *c8_shift_out;
  c8_c_u = c8_b_hoistedGlobal;
  c8_d_y = NULL;
  c8_d_u = c8_c_u;
  c8_e_y = NULL;
  sf_mex_assign(&c8_e_y, sf_mex_create("y", &c8_d_u, 2, 0U, 0U, 0U, 0));
  sf_mex_assign(&c8_d_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_b_eml_mx), 15,
    "simulinkarray", 14, c8_e_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c8_y, 1, c8_d_y);
  c8_c_hoistedGlobal = *c8_is_active_c8_hdlcodercpu_eml;
  c8_e_u = c8_c_hoistedGlobal;
  c8_f_y = NULL;
  sf_mex_assign(&c8_f_y, sf_mex_create("y", &c8_e_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c8_y, 2, c8_f_y);
  sf_mex_assign(&c8_st, c8_y);
  return c8_st;
}

static void set_sim_state_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c8_st)
{
  const mxArray *c8_u;
  boolean_T *c8_doneDoubleBufferReInit;
  uint8_T *c8_out_flags;
  int8_T *c8_shift_out;
  uint8_T *c8_is_active_c8_hdlcodercpu_eml;
  c8_shift_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c8_is_active_c8_hdlcodercpu_eml = (uint8_T *)ssGetDWork(chartInstance->S, 3);
  c8_doneDoubleBufferReInit = (boolean_T *)ssGetDWork(chartInstance->S, 2);
  *c8_doneDoubleBufferReInit = TRUE;
  c8_u = sf_mex_dup(c8_st);
  *c8_out_flags = c8_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c8_u, 0)), "out_flags");
  *c8_shift_out = c8_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c8_u, 1)), "shift_out");
  *c8_is_active_c8_hdlcodercpu_eml = c8_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c8_u, 2)), "is_active_c8_hdlcodercpu_eml");
  sf_mex_destroy(&c8_u);
  c8_update_debugger_state_c8_hdlcodercpu_eml(chartInstance);
  sf_mex_destroy(&c8_st);
}

static void finalize_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&c8_eml_mx);
  sf_mex_destroy(&c8_b_eml_mx);
  sf_mex_destroy(&c8_c_eml_mx);
  sf_mex_destroy(&c8_d_eml_mx);
  sf_mex_destroy(&c8_e_eml_mx);
}

static void sf_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  int32_T *c8_sfEvent;
  uint8_T *c8_out_flags;
  uint8_T *c8_select;
  int8_T *c8_shift_out;
  int8_T *c8_input;
  uint8_T *c8_in_flags;
  c8_in_flags = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c8_input = (int8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c8_shift_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_select = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c8_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c8_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 7U, *c8_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c8_out_flags, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c8_select, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c8_shift_out, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*c8_input, 3U);
  _SFD_DATA_RANGE_CHECK((real_T)*c8_in_flags, 4U);
  *c8_sfEvent = CALL_EVENT;
  c8_chartstep_c8_hdlcodercpu_eml(chartInstance);
  sf_debug_check_for_state_inconsistency(_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c8_chartstep_c8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  uint8_T c8_hoistedGlobal;
  int8_T c8_b_hoistedGlobal;
  uint8_T c8_c_hoistedGlobal;
  uint8_T c8_select;
  int8_T c8_input;
  uint8_T c8_in_flags;
  uint32_T c8_debug_family_var_map[13];
  const mxArray *c8_hdl_fm = NULL;
  uint8_T c8_overflow;
  uint8_T c8_c_out;
  uint8_T c8_sign_bit;
  uint8_T c8_is_zero;
  uint8_T c8_zero_ufix1;
  real_T c8_nargin = 3.0;
  real_T c8_nargout = 2.0;
  uint8_T c8_out_flags;
  int8_T c8_shift_out;
  uint8_T c8_a;
  const mxArray *c8_m0 = NULL;
  const mxArray *c8_m1 = NULL;
  uint8_T c8_a1;
  uint8_T c8_slice_temp;
  uint8_T c8_b_a;
  const mxArray *c8_m2 = NULL;
  const mxArray *c8_m3 = NULL;
  uint8_T c8_b_a1;
  uint8_T c8_b_slice_temp;
  int8_T c8_c_a;
  const mxArray *c8_m4 = NULL;
  const mxArray *c8_m5 = NULL;
  int8_T c8_c_a1;
  uint8_T c8_c_slice_temp;
  int8_T c8_d_a;
  const mxArray *c8_m6 = NULL;
  const mxArray *c8_m7 = NULL;
  int8_T c8_d_a1;
  uint8_T c8_d_slice_temp;
  uint8_T c8_c;
  int8_T c8_e_a;
  const mxArray *c8_m8 = NULL;
  const mxArray *c8_m9 = NULL;
  int8_T c8_e_a1;
  uint8_T c8_e_slice_temp;
  uint8_T c8_b_c;
  int8_T c8_f_a;
  const mxArray *c8_m10 = NULL;
  const mxArray *c8_m11 = NULL;
  const mxArray *c8_m12 = NULL;
  const mxArray *c8_m13 = NULL;
  const mxArray *c8_m14 = NULL;
  const mxArray *c8_m15 = NULL;
  const mxArray *c8_m16 = NULL;
  const mxArray *c8_m17 = NULL;
  const mxArray *c8_m18 = NULL;
  uint8_T c8_f_slice_temp;
  uint8_T c8_varargin_1;
  uint8_T c8_b_varargin_1;
  uint8_T c8_var1;
  const mxArray *c8_m19 = NULL;
  const mxArray *c8_m20 = NULL;
  const mxArray *c8_m21 = NULL;
  const mxArray *c8_m22 = NULL;
  const mxArray *c8_m23 = NULL;
  const mxArray *c8_m24 = NULL;
  const mxArray *c8_m25 = NULL;
  uint8_T c8_c_varargin_1;
  uint8_T c8_varargin_2;
  uint8_T c8_d_varargin_1;
  uint8_T c8_b_varargin_2;
  const mxArray *c8_m26 = NULL;
  const mxArray *c8_m27 = NULL;
  uint8_T c8_varargout_2;
  const mxArray *c8_m28 = NULL;
  const mxArray *c8_m29 = NULL;
  uint8_T c8_c_c;
  uint8_T c8_e_varargin_1;
  uint8_T c8_c_varargin_2;
  uint8_T c8_f_varargin_1;
  uint8_T c8_d_varargin_2;
  const mxArray *c8_m30 = NULL;
  const mxArray *c8_m31 = NULL;
  uint8_T c8_b_varargout_2;
  const mxArray *c8_m32 = NULL;
  const mxArray *c8_m33 = NULL;
  uint8_T c8_d_c;
  uint8_T c8_g_varargin_1;
  uint8_T c8_e_varargin_2;
  uint8_T c8_h_varargin_1;
  uint8_T c8_f_varargin_2;
  const mxArray *c8_m34 = NULL;
  const mxArray *c8_m35 = NULL;
  uint8_T c8_c_varargout_2;
  const mxArray *c8_m36 = NULL;
  const mxArray *c8_m37 = NULL;
  int8_T c8_i_varargin_1;
  int8_T c8_j_varargin_1;
  const mxArray *c8_m38 = NULL;
  const mxArray *c8_m39 = NULL;
  const mxArray *c8_m40 = NULL;
  const mxArray *c8_m41 = NULL;
  const mxArray *c8_m42 = NULL;
  const mxArray *c8_m43 = NULL;
  const mxArray *c8_m44 = NULL;
  int8_T c8_b_var1;
  uint8_T *c8_b_select;
  int8_T *c8_b_input;
  uint8_T *c8_b_in_flags;
  uint8_T *c8_b_out_flags;
  int8_T *c8_b_shift_out;
  int32_T *c8_sfEvent;
  c8_b_in_flags = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c8_b_input = (int8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c8_b_shift_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_b_select = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c8_b_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c8_sfEvent = (int32_T *)ssGetDWork(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 7U, *c8_sfEvent);
  c8_hoistedGlobal = *c8_b_select;
  c8_b_hoistedGlobal = *c8_b_input;
  c8_c_hoistedGlobal = *c8_b_in_flags;
  c8_select = c8_hoistedGlobal;
  c8_input = c8_b_hoistedGlobal;
  c8_in_flags = c8_c_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 13U, 13U, c8_debug_family_names,
    c8_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c8_hdl_fm, 0U, c8_h_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c8_overflow, 1U, c8_g_sf_marshallOut,
    c8_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c8_c_out, 2U, c8_g_sf_marshallOut,
    c8_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c8_sign_bit, 3U, c8_g_sf_marshallOut,
    c8_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c8_is_zero, 4U, c8_f_sf_marshallOut,
    c8_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c8_zero_ufix1, 5U,
    c8_e_sf_marshallOut, c8_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c8_nargin, 6U, c8_d_sf_marshallOut,
    c8_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c8_nargout, 7U, c8_d_sf_marshallOut,
    c8_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c8_select, 8U, c8_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c8_input, 9U, c8_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c8_in_flags, 10U, c8_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c8_out_flags, 11U,
    c8_b_sf_marshallOut, c8_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c8_shift_out, 12U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, *c8_sfEvent, 8);
  c8_hdl_fm = c8_eml_mx;
  _SFD_EML_CALL(0U, *c8_sfEvent, 16);
  c8_a = c8_in_flags;
  sf_mex_destroy(&c8_m0);
  sf_mex_destroy(&c8_m1);
  c8_overflow = 0U;
  c8_a1 = c8_a;
  c8_slice_temp = (uint8_T)((uint8_T)((uint32_T)c8_a1 >> 1) & 1U);
  c8_overflow = c8_slice_temp;
  _SFD_EML_CALL(0U, *c8_sfEvent, 19);
  c8_b_a = c8_in_flags;
  sf_mex_destroy(&c8_m2);
  sf_mex_destroy(&c8_m3);
  c8_c_out = 0U;
  c8_b_a1 = c8_b_a;
  c8_b_slice_temp = (uint8_T)((uint8_T)((uint32_T)c8_b_a1 >> 3) & 1U);
  c8_c_out = c8_b_slice_temp;
  _SFD_EML_CALL(0U, *c8_sfEvent, 21);
  switch (c8_uint8(chartInstance, c8_select)) {
   case 1U:
    CV_EML_SWITCH(0, 0, 1);
    _SFD_EML_CALL(0U, *c8_sfEvent, 25);
    c8_shift_out = c8_bitsll(chartInstance, c8_input);
    _SFD_EML_CALL(0U, *c8_sfEvent, 27);
    c8_c_a = c8_input;
    sf_mex_destroy(&c8_m4);
    sf_mex_destroy(&c8_m5);
    c8_c_out = 0U;
    c8_c_a1 = c8_c_a;
    c8_c_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
      (uint8_T)c8_c_a1 >> 7) & 1) & 1U);
    c8_c_out = c8_c_slice_temp;
    _SFD_EML_CALL(0U, *c8_sfEvent, 29);
    c8_d_a = c8_input;
    sf_mex_destroy(&c8_m6);
    sf_mex_destroy(&c8_m7);
    c8_d_a1 = c8_d_a;
    c8_d_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
      (uint8_T)c8_d_a1 >> 7) & 1) & 1U);
    c8_c = c8_d_slice_temp;
    c8_e_a = c8_input;
    sf_mex_destroy(&c8_m8);
    sf_mex_destroy(&c8_m9);
    c8_e_a1 = c8_e_a;
    c8_e_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
      (uint8_T)c8_e_a1 >> 6) & 1) & 1U);
    c8_b_c = c8_e_slice_temp;
    c8_overflow = c8_bitxor(chartInstance, c8_c, c8_b_c);
    break;

   case 2U:
    CV_EML_SWITCH(0, 0, 2);
    _SFD_EML_CALL(0U, *c8_sfEvent, 32);
    c8_shift_out = c8_bitsra(chartInstance, c8_input);
    break;

   default:
    CV_EML_SWITCH(0, 0, 0);
    _SFD_EML_CALL(0U, *c8_sfEvent, 35);
    c8_i_varargin_1 = c8_input;
    c8_j_varargin_1 = c8_i_varargin_1;
    c8_isfloat(chartInstance);
    c8_b_var1 = c8_j_varargin_1;
    c8_shift_out = c8_b_var1;
    sf_mex_destroy(&c8_m38);
    sf_mex_destroy(&c8_m39);
    sf_mex_destroy(&c8_m40);
    sf_mex_destroy(&c8_m41);
    sf_mex_destroy(&c8_m42);
    sf_mex_destroy(&c8_m43);
    sf_mex_destroy(&c8_m44);
    break;
  }

  _SFD_EML_CALL(0U, *c8_sfEvent, 39);
  c8_f_a = c8_shift_out;
  sf_mex_destroy(&c8_m10);
  sf_mex_destroy(&c8_m11);
  sf_mex_destroy(&c8_m12);
  sf_mex_destroy(&c8_m13);
  sf_mex_destroy(&c8_m14);
  sf_mex_destroy(&c8_m15);
  sf_mex_destroy(&c8_m16);
  sf_mex_destroy(&c8_m17);
  sf_mex_destroy(&c8_m18);
  c8_sign_bit = 0U;
  c8_f_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
    (uint8_T)c8_f_a >> 7) & 1) & 1U);
  c8_sign_bit = c8_f_slice_temp;
  _SFD_EML_CALL(0U, *c8_sfEvent, 42);
  c8_is_zero = (uint8_T)!c8_all(chartInstance, c8_shift_out);
  _SFD_EML_CALL(0U, *c8_sfEvent, 43);
  c8_varargin_1 = c8_is_zero;
  c8_b_varargin_1 = c8_varargin_1;
  c8_var1 = c8_b_varargin_1;
  c8_zero_ufix1 = (uint8_T)(c8_var1 & 1U);
  sf_mex_destroy(&c8_m19);
  sf_mex_destroy(&c8_m20);
  sf_mex_destroy(&c8_m21);
  sf_mex_destroy(&c8_m22);
  sf_mex_destroy(&c8_m23);
  sf_mex_destroy(&c8_m24);
  sf_mex_destroy(&c8_m25);
  _SFD_EML_CALL(0U, *c8_sfEvent, 46);
  c8_c_varargin_1 = c8_c_out;
  c8_varargin_2 = c8_sign_bit;
  c8_d_varargin_1 = c8_c_varargin_1;
  c8_b_varargin_2 = c8_varargin_2;
  sf_mex_destroy(&c8_m26);
  sf_mex_destroy(&c8_m27);
  c8_varargout_2 = c8_b_varargin_2;
  sf_mex_destroy(&c8_m28);
  sf_mex_destroy(&c8_m29);
  c8_c_c = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)(c8_d_varargin_1 &
    3U) << 1) & 3U) | (uint8_T)(c8_varargout_2 & 3U)) & 3U);
  c8_e_varargin_1 = c8_c_c;
  c8_c_varargin_2 = c8_overflow;
  c8_f_varargin_1 = c8_e_varargin_1;
  c8_d_varargin_2 = c8_c_varargin_2;
  sf_mex_destroy(&c8_m30);
  sf_mex_destroy(&c8_m31);
  c8_b_varargout_2 = c8_d_varargin_2;
  sf_mex_destroy(&c8_m32);
  sf_mex_destroy(&c8_m33);
  c8_d_c = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)(c8_f_varargin_1 &
    7U) << 1) & 7U) | (uint8_T)(c8_b_varargout_2 & 7U)) & 7U);
  c8_g_varargin_1 = c8_d_c;
  c8_e_varargin_2 = c8_zero_ufix1;
  c8_h_varargin_1 = c8_g_varargin_1;
  c8_f_varargin_2 = c8_e_varargin_2;
  sf_mex_destroy(&c8_m34);
  sf_mex_destroy(&c8_m35);
  c8_c_varargout_2 = c8_f_varargin_2;
  sf_mex_destroy(&c8_m36);
  sf_mex_destroy(&c8_m37);
  c8_out_flags = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)
    (c8_h_varargin_1 & 15U) << 1) & 15U) | (uint8_T)(c8_c_varargout_2 & 15U)) &
    15U);
  _SFD_EML_CALL(0U, *c8_sfEvent, -46);
  sf_debug_symbol_scope_pop();
  *c8_b_out_flags = c8_out_flags;
  *c8_b_shift_out = c8_shift_out;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, *c8_sfEvent);
}

static void initSimStructsc8_hdlcodercpu_eml(SFc8_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber)
{
}

static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  int8_T c8_u;
  const mxArray *c8_y = NULL;
  int8_T c8_b_u;
  const mxArray *c8_b_y = NULL;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(int8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c8_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_b_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c8_mxArrayOutData, c8_y);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c8_mxArrayOutData;
}

static int8_T c8_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int8_T c8_y;
  const mxArray *c8_mxFi = NULL;
  const mxArray *c8_mxInt = NULL;
  int8_T c8_i0;
  sf_mex_check_fi(c8_parentId, c8_u, 0, 0U, 0, c8_eml_mx, c8_b_eml_mx);
  sf_mex_assign(&c8_mxFi, sf_mex_dup(c8_u));
  sf_mex_assign(&c8_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c8_mxFi)));
  sf_mex_import(c8_parentId, sf_mex_dup(c8_mxInt), &c8_i0, 1, 2, 0U, 0, 0U, 0);
  sf_mex_destroy(&c8_mxFi);
  sf_mex_destroy(&c8_mxInt);
  c8_y = c8_i0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_shift_out;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  int8_T c8_y;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c8_shift_out = sf_mex_dup(c8_mxArrayInData);
    c8_identifier = c8_varName;
    c8_thisId.fIdentifier = c8_identifier;
    c8_thisId.fParent = NULL;
    c8_y = c8_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_shift_out),
      &c8_thisId);
    sf_mex_destroy(&c8_shift_out);
    *(int8_T *)c8_outData = c8_y;
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  uint8_T c8_u;
  const mxArray *c8_y = NULL;
  uint8_T c8_b_u;
  const mxArray *c8_b_y = NULL;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(uint8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c8_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_c_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c8_mxArrayOutData, c8_y);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c8_mxArrayOutData;
}

static uint8_T c8_b_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  const mxArray *c8_mxFi = NULL;
  const mxArray *c8_mxInt = NULL;
  uint8_T c8_u0;
  sf_mex_check_fi(c8_parentId, c8_u, 0, 0U, 0, c8_eml_mx, c8_c_eml_mx);
  sf_mex_assign(&c8_mxFi, sf_mex_dup(c8_u));
  sf_mex_assign(&c8_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c8_mxFi)));
  sf_mex_import(c8_parentId, sf_mex_dup(c8_mxInt), &c8_u0, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c8_mxFi);
  sf_mex_destroy(&c8_mxInt);
  c8_y = c8_u0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_out_flags;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  uint8_T c8_y;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c8_out_flags = sf_mex_dup(c8_mxArrayInData);
    c8_identifier = c8_varName;
    c8_thisId.fIdentifier = c8_identifier;
    c8_thisId.fParent = NULL;
    c8_y = c8_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_out_flags),
      &c8_thisId);
    sf_mex_destroy(&c8_out_flags);
    *(uint8_T *)c8_outData = c8_y;
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  uint8_T c8_u;
  const mxArray *c8_y = NULL;
  uint8_T c8_b_u;
  const mxArray *c8_b_y = NULL;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(uint8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c8_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_d_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c8_mxArrayOutData, c8_y);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c8_mxArrayOutData;
}

static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  real_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(real_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c8_mxArrayOutData, c8_y);
  return c8_mxArrayOutData;
}

static real_T c8_c_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  real_T c8_y;
  real_T c8_d0;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_d0, 1, 0, 0U, 0, 0U, 0);
  c8_y = c8_d0;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_nargout;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  real_T c8_y;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_nargout = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_nargout), &c8_thisId);
  sf_mex_destroy(&c8_nargout);
  *(real_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_e_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  uint8_T c8_u;
  const mxArray *c8_y = NULL;
  uint8_T c8_b_u;
  const mxArray *c8_b_y = NULL;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(uint8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c8_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_e_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c8_mxArrayOutData, c8_y);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c8_mxArrayOutData;
}

static uint8_T c8_d_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  const mxArray *c8_mxFi = NULL;
  const mxArray *c8_mxInt = NULL;
  uint8_T c8_u1;
  sf_mex_check_fi(c8_parentId, c8_u, 0, 0U, 0, c8_eml_mx, c8_e_eml_mx);
  sf_mex_assign(&c8_mxFi, sf_mex_dup(c8_u));
  sf_mex_assign(&c8_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c8_mxFi)));
  sf_mex_import(c8_parentId, sf_mex_dup(c8_mxInt), &c8_u1, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c8_mxFi);
  sf_mex_destroy(&c8_mxInt);
  c8_y = c8_u1;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_zero_ufix1;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  uint8_T c8_y;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c8_zero_ufix1 = sf_mex_dup(c8_mxArrayInData);
    c8_identifier = c8_varName;
    c8_thisId.fIdentifier = c8_identifier;
    c8_thisId.fParent = NULL;
    c8_y = c8_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_zero_ufix1),
      &c8_thisId);
    sf_mex_destroy(&c8_zero_ufix1);
    *(uint8_T *)c8_outData = c8_y;
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_f_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  uint8_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(uint8_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c8_mxArrayOutData, c8_y);
  return c8_mxArrayOutData;
}

static uint8_T c8_e_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_is_zero, const char_T *c8_identifier)
{
  uint8_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_is_zero), &c8_thisId);
  sf_mex_destroy(&c8_is_zero);
  return c8_y;
}

static uint8_T c8_f_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  uint8_T c8_u2;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_u2, 1, 3, 0U, 0, 0U, 0);
  c8_y = c8_u2;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_is_zero;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  uint8_T c8_y;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_is_zero = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_is_zero), &c8_thisId);
  sf_mex_destroy(&c8_is_zero);
  *(uint8_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_g_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  uint8_T c8_u;
  const mxArray *c8_y = NULL;
  uint8_T c8_b_u;
  const mxArray *c8_b_y = NULL;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(uint8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c8_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_e_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c8_mxArrayOutData, c8_y);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c8_mxArrayOutData;
}

static uint8_T c8_g_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  const mxArray *c8_mxFi = NULL;
  const mxArray *c8_mxInt = NULL;
  uint8_T c8_u3;
  sf_mex_check_fi(c8_parentId, c8_u, 0, 0U, 0, c8_eml_mx, c8_e_eml_mx);
  sf_mex_assign(&c8_mxFi, sf_mex_dup(c8_u));
  sf_mex_assign(&c8_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c8_mxFi)));
  sf_mex_import(c8_parentId, sf_mex_dup(c8_mxInt), &c8_u3, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c8_mxFi);
  sf_mex_destroy(&c8_mxInt);
  c8_y = c8_u3;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_sign_bit;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  uint8_T c8_y;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c8_sign_bit = sf_mex_dup(c8_mxArrayInData);
    c8_identifier = c8_varName;
    c8_thisId.fIdentifier = c8_identifier;
    c8_thisId.fParent = NULL;
    c8_y = c8_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_sign_bit),
      &c8_thisId);
    sf_mex_destroy(&c8_sign_bit);
    *(uint8_T *)c8_outData = c8_y;
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_h_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  const mxArray *c8_u;
  const mxArray *c8_y = NULL;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = sf_mex_dup(*(const mxArray **)c8_inData);
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_duplicatearraysafe(&c8_u));
  sf_mex_destroy(&c8_u);
  sf_mex_assign(&c8_mxArrayOutData, c8_y);
  return c8_mxArrayOutData;
}

const mxArray *sf_c8_hdlcodercpu_eml_get_eml_resolved_functions_info(void)
{
  const mxArray *c8_nameCaptureInfo;
  c8_ResolvedFunctionInfo c8_info[39];
  const mxArray *c8_m45 = NULL;
  int32_T c8_i1;
  c8_ResolvedFunctionInfo *c8_r0;
  c8_nameCaptureInfo = NULL;
  c8_nameCaptureInfo = NULL;
  c8_info_helper(c8_info);
  sf_mex_assign(&c8_m45, sf_mex_createstruct("nameCaptureInfo", 1, 39));
  for (c8_i1 = 0; c8_i1 < 39; c8_i1++) {
    c8_r0 = &c8_info[c8_i1];
    sf_mex_addfield(c8_m45, sf_mex_create("nameCaptureInfo", c8_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->context)), "context", "nameCaptureInfo",
                    c8_i1);
    sf_mex_addfield(c8_m45, sf_mex_create("nameCaptureInfo", c8_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c8_r0->name)), "name", "nameCaptureInfo", c8_i1);
    sf_mex_addfield(c8_m45, sf_mex_create("nameCaptureInfo", c8_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c8_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c8_i1);
    sf_mex_addfield(c8_m45, sf_mex_create("nameCaptureInfo", c8_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c8_r0->resolved)), "resolved", "nameCaptureInfo",
                    c8_i1);
    sf_mex_addfield(c8_m45, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c8_i1);
    sf_mex_addfield(c8_m45, sf_mex_create("nameCaptureInfo", &c8_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c8_i1);
    sf_mex_addfield(c8_m45, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c8_i1);
    sf_mex_addfield(c8_m45, sf_mex_create("nameCaptureInfo", &c8_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c8_i1);
  }

  sf_mex_assign(&c8_nameCaptureInfo, c8_m45);
  return c8_nameCaptureInfo;
}

static void c8_info_helper(c8_ResolvedFunctionInfo c8_info[39])
{
  c8_info[0].context = "";
  c8_info[0].name = "fimath";
  c8_info[0].dominantType = "char";
  c8_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m";
  c8_info[0].fileTimeLo = 275520000U;
  c8_info[0].fileTimeHi = 30114375U;
  c8_info[0].mFileTimeLo = 0U;
  c8_info[0].mFileTimeHi = 0U;
  c8_info[1].context = "";
  c8_info[1].name = "bitget";
  c8_info[1].dominantType = "embedded.fi";
  c8_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c8_info[1].fileTimeLo = 235520000U;
  c8_info[1].fileTimeHi = 30114375U;
  c8_info[1].mFileTimeLo = 0U;
  c8_info[1].mFileTimeHi = 0U;
  c8_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c8_info[2].name = "isfi";
  c8_info[2].dominantType = "double";
  c8_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c8_info[2].fileTimeLo = 335520000U;
  c8_info[2].fileTimeHi = 30114375U;
  c8_info[2].mFileTimeLo = 0U;
  c8_info[2].mFileTimeHi = 0U;
  c8_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c8_info[3].name = "isnumerictype";
  c8_info[3].dominantType = "char";
  c8_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m";
  c8_info[3].fileTimeLo = 355520000U;
  c8_info[3].fileTimeHi = 30114375U;
  c8_info[3].mFileTimeLo = 0U;
  c8_info[3].mFileTimeHi = 0U;
  c8_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c8_info[4].name = "eml_scalexp_compatible";
  c8_info[4].dominantType = "embedded.fi";
  c8_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c8_info[4].fileTimeLo = 3244844544U;
  c8_info[4].fileTimeHi = 30108086U;
  c8_info[4].mFileTimeLo = 0U;
  c8_info[4].mFileTimeHi = 0U;
  c8_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c8_info[5].name = "all";
  c8_info[5].dominantType = "logical";
  c8_info[5].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c8_info[5].fileTimeLo = 3624844544U;
  c8_info[5].fileTimeHi = 30108086U;
  c8_info[5].mFileTimeLo = 0U;
  c8_info[5].mFileTimeHi = 0U;
  c8_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c8_info[6].name = "eml_all_or_any";
  c8_info[6].dominantType = "char";
  c8_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c8_info[6].fileTimeLo = 2224844544U;
  c8_info[6].fileTimeHi = 30108086U;
  c8_info[6].mFileTimeLo = 0U;
  c8_info[6].mFileTimeHi = 0U;
  c8_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c8_info[7].name = "isequal";
  c8_info[7].dominantType = "double";
  c8_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c8_info[7].fileTimeLo = 2864844544U;
  c8_info[7].fileTimeHi = 30108086U;
  c8_info[7].mFileTimeLo = 0U;
  c8_info[7].mFileTimeHi = 0U;
  c8_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c8_info[8].name = "eml_isequal_core";
  c8_info[8].dominantType = "double";
  c8_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c8_info[8].fileTimeLo = 3144844544U;
  c8_info[8].fileTimeHi = 30108086U;
  c8_info[8].mFileTimeLo = 0U;
  c8_info[8].mFileTimeHi = 0U;
  c8_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c8_info[9].name = "eml_const_nonsingleton_dim";
  c8_info[9].dominantType = "logical";
  c8_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  c8_info[9].fileTimeLo = 2244844544U;
  c8_info[9].fileTimeHi = 30108086U;
  c8_info[9].mFileTimeLo = 0U;
  c8_info[9].mFileTimeHi = 0U;
  c8_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c8_info[10].name = "isfixed";
  c8_info[10].dominantType = "embedded.fi";
  c8_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  c8_info[10].fileTimeLo = 875520000U;
  c8_info[10].fileTimeHi = 30114375U;
  c8_info[10].mFileTimeLo = 0U;
  c8_info[10].mFileTimeHi = 0U;
  c8_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  c8_info[11].name = "get";
  c8_info[11].dominantType = "embedded.numerictype";
  c8_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m";
  c8_info[11].fileTimeLo = 4170487296U;
  c8_info[11].fileTimeHi = 30114374U;
  c8_info[11].mFileTimeLo = 0U;
  c8_info[11].mFileTimeHi = 0U;
  c8_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c8_info[12].name = "numerictype";
  c8_info[12].dominantType = "double";
  c8_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m";
  c8_info[12].fileTimeLo = 435520000U;
  c8_info[12].fileTimeHi = 30114375U;
  c8_info[12].mFileTimeLo = 0U;
  c8_info[12].mFileTimeHi = 0U;
  c8_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m";
  c8_info[13].name = "length";
  c8_info[13].dominantType = "cell";
  c8_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c8_info[13].fileTimeLo = 2884844544U;
  c8_info[13].fileTimeHi = 30108086U;
  c8_info[13].mFileTimeLo = 0U;
  c8_info[13].mFileTimeHi = 0U;
  c8_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c8_info[14].name = "fimath";
  c8_info[14].dominantType = "embedded.fi";
  c8_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m";
  c8_info[14].fileTimeLo = 775520000U;
  c8_info[14].fileTimeHi = 30114375U;
  c8_info[14].mFileTimeLo = 0U;
  c8_info[14].mFileTimeHi = 0U;
  c8_info[15].context = "";
  c8_info[15].name = "uint8";
  c8_info[15].dominantType = "embedded.fi";
  c8_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m";
  c8_info[15].fileTimeLo = 1115520000U;
  c8_info[15].fileTimeHi = 30114375U;
  c8_info[15].mFileTimeLo = 0U;
  c8_info[15].mFileTimeHi = 0U;
  c8_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m";
  c8_info[16].name = "eml_fi_getStoredIntValAsDType";
  c8_info[16].dominantType = "embedded.fi";
  c8_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getStoredIntValAsDType.m";
  c8_info[16].fileTimeLo = 655520000U;
  c8_info[16].fileTimeHi = 30114375U;
  c8_info[16].mFileTimeLo = 0U;
  c8_info[16].mFileTimeHi = 0U;
  c8_info[17].context = "";
  c8_info[17].name = "bitsra";
  c8_info[17].dominantType = "embedded.fi";
  c8_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitsra.m";
  c8_info[17].fileTimeLo = 555520000U;
  c8_info[17].fileTimeHi = 30114375U;
  c8_info[17].mFileTimeLo = 0U;
  c8_info[17].mFileTimeHi = 0U;
  c8_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitsra.m";
  c8_info[18].name = "eml_fi_bitshift";
  c8_info[18].dominantType = "embedded.fi";
  c8_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m";
  c8_info[18].fileTimeLo = 635520000U;
  c8_info[18].fileTimeHi = 30114375U;
  c8_info[18].mFileTimeLo = 0U;
  c8_info[18].mFileTimeHi = 0U;
  c8_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m";
  c8_info[19].name = "eml_shift_checks";
  c8_info[19].dominantType = "embedded.fi";
  c8_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m";
  c8_info[19].fileTimeLo = 715520000U;
  c8_info[19].fileTimeHi = 30114375U;
  c8_info[19].mFileTimeLo = 0U;
  c8_info[19].mFileTimeHi = 0U;
  c8_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m";
  c8_info[20].name = "numerictype";
  c8_info[20].dominantType = "embedded.fi";
  c8_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m";
  c8_info[20].fileTimeLo = 995520000U;
  c8_info[20].fileTimeHi = 30114375U;
  c8_info[20].mFileTimeLo = 0U;
  c8_info[20].mFileTimeHi = 0U;
  c8_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m";
  c8_info[21].name = "eml_isslopebiasscaled";
  c8_info[21].dominantType = "embedded.fi";
  c8_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m";
  c8_info[21].fileTimeLo = 695520000U;
  c8_info[21].fileTimeHi = 30114375U;
  c8_info[21].mFileTimeLo = 0U;
  c8_info[21].mFileTimeHi = 0U;
  c8_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  c8_info[22].name = "isnan";
  c8_info[22].dominantType = "double";
  c8_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c8_info[22].fileTimeLo = 2884844544U;
  c8_info[22].fileTimeHi = 30108086U;
  c8_info[22].mFileTimeLo = 0U;
  c8_info[22].mFileTimeHi = 0U;
  c8_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m";
  c8_info[23].name = "fi_impl";
  c8_info[23].dominantType = "";
  c8_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m";
  c8_info[23].fileTimeLo = 275520000U;
  c8_info[23].fileTimeHi = 30114375U;
  c8_info[23].mFileTimeLo = 0U;
  c8_info[23].mFileTimeHi = 0U;
  c8_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c8_info[24].name = "isfloat";
  c8_info[24].dominantType = "embedded.fi";
  c8_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m";
  c8_info[24].fileTimeLo = 875520000U;
  c8_info[24].fileTimeHi = 30114375U;
  c8_info[24].mFileTimeLo = 0U;
  c8_info[24].mFileTimeHi = 0U;
  c8_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c8_info[25].name = "eml_fi_checkforntype";
  c8_info[25].dominantType = "embedded.fi";
  c8_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m";
  c8_info[25].fileTimeLo = 255520000U;
  c8_info[25].fileTimeHi = 30114375U;
  c8_info[25].mFileTimeLo = 0U;
  c8_info[25].mFileTimeHi = 0U;
  c8_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m!localFixptBitshift";
  c8_info[26].name = "eml_feval";
  c8_info[26].dominantType = "embedded.fi";
  c8_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_feval.m";
  c8_info[26].fileTimeLo = 635520000U;
  c8_info[26].fileTimeHi = 30114375U;
  c8_info[26].mFileTimeLo = 0U;
  c8_info[26].mFileTimeHi = 0U;
  c8_info[27].context = "";
  c8_info[27].name = "bitsll";
  c8_info[27].dominantType = "embedded.fi";
  c8_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitsll.m";
  c8_info[27].fileTimeLo = 535520000U;
  c8_info[27].fileTimeHi = 30114375U;
  c8_info[27].mFileTimeLo = 0U;
  c8_info[27].mFileTimeHi = 0U;
  c8_info[28].context = "";
  c8_info[28].name = "bitxor";
  c8_info[28].dominantType = "embedded.fi";
  c8_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitxor.m";
  c8_info[28].fileTimeLo = 555520000U;
  c8_info[28].fileTimeHi = 30114375U;
  c8_info[28].mFileTimeLo = 0U;
  c8_info[28].mFileTimeHi = 0U;
  c8_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitxor.m";
  c8_info[29].name = "isequal";
  c8_info[29].dominantType = "embedded.numerictype";
  c8_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/isequal.m";
  c8_info[29].fileTimeLo = 4190487296U;
  c8_info[29].fileTimeHi = 30114374U;
  c8_info[29].mFileTimeLo = 0U;
  c8_info[29].mFileTimeHi = 0U;
  c8_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitxor.m";
  c8_info[30].name = "eml_checkfimathforbinaryops";
  c8_info[30].dominantType = "embedded.fi";
  c8_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_checkfimathforbinaryops.m";
  c8_info[30].fileTimeLo = 615520000U;
  c8_info[30].fileTimeHi = 30114375U;
  c8_info[30].mFileTimeLo = 0U;
  c8_info[30].mFileTimeHi = 0U;
  c8_info[31].context = "";
  c8_info[31].name = "getmsb";
  c8_info[31].dominantType = "embedded.fi";
  c8_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m";
  c8_info[31].fileTimeLo = 795520000U;
  c8_info[31].fileTimeHi = 30114375U;
  c8_info[31].mFileTimeLo = 0U;
  c8_info[31].mFileTimeHi = 0U;
  c8_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m";
  c8_info[32].name = "eml_bitop_index_checks";
  c8_info[32].dominantType = "embedded.fi";
  c8_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_bitop_index_checks.m";
  c8_info[32].fileTimeLo = 615520000U;
  c8_info[32].fileTimeHi = 30114375U;
  c8_info[32].mFileTimeLo = 0U;
  c8_info[32].mFileTimeHi = 0U;
  c8_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c8_info[33].name = "eml_fi_checkforerror";
  c8_info[33].dominantType = "embedded.numerictype";
  c8_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m";
  c8_info[33].fileTimeLo = 255520000U;
  c8_info[33].fileTimeHi = 30114375U;
  c8_info[33].mFileTimeLo = 0U;
  c8_info[33].mFileTimeHi = 0U;
  c8_info[34].context = "";
  c8_info[34].name = "all";
  c8_info[34].dominantType = "embedded.fi";
  c8_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/all.m";
  c8_info[34].fileTimeLo = 195520000U;
  c8_info[34].fileTimeHi = 30114375U;
  c8_info[34].mFileTimeLo = 0U;
  c8_info[34].mFileTimeHi = 0U;
  c8_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c8_info[35].name = "ne";
  c8_info[35].dominantType = "embedded.fi";
  c8_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m";
  c8_info[35].fileTimeLo = 995520000U;
  c8_info[35].fileTimeHi = 30114375U;
  c8_info[35].mFileTimeLo = 0U;
  c8_info[35].mFileTimeHi = 0U;
  c8_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m";
  c8_info[36].name = "eml_type_relop_const";
  c8_info[36].dominantType = "embedded.fi";
  c8_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m";
  c8_info[36].fileTimeLo = 735520000U;
  c8_info[36].fileTimeHi = 30114375U;
  c8_info[36].mFileTimeLo = 0U;
  c8_info[36].mFileTimeHi = 0U;
  c8_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m";
  c8_info[37].name = "eml_make_same_complexity";
  c8_info[37].dominantType = "embedded.fi";
  c8_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_make_same_complexity.m";
  c8_info[37].fileTimeLo = 695520000U;
  c8_info[37].fileTimeHi = 30114375U;
  c8_info[37].mFileTimeLo = 0U;
  c8_info[37].mFileTimeHi = 0U;
  c8_info[38].context = "";
  c8_info[38].name = "bitconcat";
  c8_info[38].dominantType = "embedded.fi";
  c8_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitconcat.m";
  c8_info[38].fileTimeLo = 235520000U;
  c8_info[38].fileTimeHi = 30114375U;
  c8_info[38].mFileTimeLo = 0U;
  c8_info[38].mFileTimeHi = 0U;
}

static uint8_T c8_uint8(SFc8_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c8_A)
{
  uint8_T c8_xfi;
  const mxArray *c8_m46 = NULL;
  const mxArray *c8_m47 = NULL;
  c8_xfi = c8_A;
  sf_mex_destroy(&c8_m46);
  sf_mex_destroy(&c8_m47);
  return c8_xfi;
}

static int8_T c8_bitsra(SFc8_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c8_ain)
{
  int8_T c8_b_ain;
  const mxArray *c8_m48 = NULL;
  const mxArray *c8_m49 = NULL;
  int8_T c8_varargin_1;
  int8_T c8_b_varargin_1;
  int8_T c8_var1;
  int8_T c8_a;
  const mxArray *c8_m50 = NULL;
  const mxArray *c8_m51 = NULL;
  const mxArray *c8_m52 = NULL;
  const mxArray *c8_m53 = NULL;
  const mxArray *c8_m54 = NULL;
  const mxArray *c8_m55 = NULL;
  const mxArray *c8_m56 = NULL;
  int8_T c8_b_a;
  int8_T c8_c_varargin_1;
  int8_T c8_c;
  c8_b_ain = c8_ain;
  sf_mex_destroy(&c8_m48);
  sf_mex_destroy(&c8_m49);
  c8_varargin_1 = c8_b_ain;
  c8_b_varargin_1 = c8_varargin_1;
  c8_isfloat(chartInstance);
  c8_var1 = c8_b_varargin_1;
  c8_a = c8_var1;
  sf_mex_destroy(&c8_m50);
  sf_mex_destroy(&c8_m51);
  sf_mex_destroy(&c8_m52);
  sf_mex_destroy(&c8_m53);
  sf_mex_destroy(&c8_m54);
  sf_mex_destroy(&c8_m55);
  sf_mex_destroy(&c8_m56);
  c8_b_a = c8_a;
  c8_c_varargin_1 = c8_b_a;
  c8_c = (int8_T)(c8_c_varargin_1 >> 1);
  return c8_c;
}

static void c8_isfloat(SFc8_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c8_m57 = NULL;
  const mxArray *c8_m58 = NULL;
  const mxArray *c8_m59 = NULL;
  const mxArray *c8_m60 = NULL;
  sf_mex_destroy(&c8_m57);
  sf_mex_destroy(&c8_m58);
  sf_mex_destroy(&c8_m59);
  sf_mex_destroy(&c8_m60);
}

static int8_T c8_bitsll(SFc8_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c8_ain)
{
  int8_T c8_b_ain;
  const mxArray *c8_m61 = NULL;
  const mxArray *c8_m62 = NULL;
  int8_T c8_varargin_1;
  int8_T c8_b_varargin_1;
  int8_T c8_var1;
  int8_T c8_a;
  const mxArray *c8_m63 = NULL;
  const mxArray *c8_m64 = NULL;
  const mxArray *c8_m65 = NULL;
  const mxArray *c8_m66 = NULL;
  const mxArray *c8_m67 = NULL;
  const mxArray *c8_m68 = NULL;
  const mxArray *c8_m69 = NULL;
  int8_T c8_b_a;
  int8_T c8_c_varargin_1;
  int8_T c8_c;
  c8_b_ain = c8_ain;
  sf_mex_destroy(&c8_m61);
  sf_mex_destroy(&c8_m62);
  c8_varargin_1 = c8_b_ain;
  c8_b_varargin_1 = c8_varargin_1;
  c8_isfloat(chartInstance);
  c8_var1 = c8_b_varargin_1;
  c8_a = c8_var1;
  sf_mex_destroy(&c8_m63);
  sf_mex_destroy(&c8_m64);
  sf_mex_destroy(&c8_m65);
  sf_mex_destroy(&c8_m66);
  sf_mex_destroy(&c8_m67);
  sf_mex_destroy(&c8_m68);
  sf_mex_destroy(&c8_m69);
  c8_b_a = c8_a;
  c8_c_varargin_1 = c8_b_a;
  c8_c = (int8_T)(c8_c_varargin_1 << 1);
  return c8_c;
}

static uint8_T c8_bitxor(SFc8_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c8_a, uint8_T c8_b)
{
  const mxArray *c8_m70 = NULL;
  const mxArray *c8_m71 = NULL;
  uint8_T c8_c_uint;
  sf_mex_destroy(&c8_m70);
  sf_mex_destroy(&c8_m71);
  c8_c_uint = (uint8_T)((uint8_T)(c8_a ^ c8_b) & 1U);
  return c8_c_uint;
}

static boolean_T c8_all(SFc8_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c8_x)
{
  int8_T c8_b_x;
  int8_T c8_a0;
  const mxArray *c8_m72 = NULL;
  const mxArray *c8_m73 = NULL;
  int8_T c8_a;
  int8_T c8_b_a0;
  int8_T c8_a1;
  int8_T c8_b_a1;
  c8_b_x = c8_x;
  c8_a0 = c8_b_x;
  sf_mex_destroy(&c8_m72);
  sf_mex_destroy(&c8_m73);
  c8_a = c8_a0;
  c8_b_a0 = c8_a;
  c8_a1 = c8_b_a0;
  c8_b_a1 = c8_a1;
  return c8_b_a1 != 0;
}

static const mxArray *c8_i_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  int32_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(int32_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c8_mxArrayOutData, c8_y);
  return c8_mxArrayOutData;
}

static int32_T c8_h_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int32_T c8_y;
  int32_T c8_i2;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_i2, 1, 6, 0U, 0, 0U, 0);
  c8_y = c8_i2;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_sfEvent;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  int32_T c8_y;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_sfEvent = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_sfEvent), &c8_thisId);
  sf_mex_destroy(&c8_sfEvent);
  *(int32_T *)c8_outData = c8_y;
  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_j_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  uint8_T c8_u;
  const mxArray *c8_y = NULL;
  uint8_T c8_b_u;
  const mxArray *c8_b_y = NULL;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(uint8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c8_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_c_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c8_mxArrayOutData, c8_y);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c8_mxArrayOutData;
}

static uint8_T c8_i_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_out_flags, const char_T *c8_identifier)
{
  uint8_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_out_flags),
    &c8_thisId);
  sf_mex_destroy(&c8_out_flags);
  return c8_y;
}

static uint8_T c8_j_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  const mxArray *c8_mxFi = NULL;
  const mxArray *c8_mxInt = NULL;
  uint8_T c8_u4;
  sf_mex_check_fi(c8_parentId, c8_u, 0, 0U, 0, c8_eml_mx, c8_c_eml_mx);
  sf_mex_assign(&c8_mxFi, sf_mex_dup(c8_u));
  sf_mex_assign(&c8_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c8_mxFi)));
  sf_mex_import(c8_parentId, sf_mex_dup(c8_mxInt), &c8_u4, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c8_mxFi);
  sf_mex_destroy(&c8_mxInt);
  c8_y = c8_u4;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_out_flags;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  uint8_T c8_y;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c8_out_flags = sf_mex_dup(c8_mxArrayInData);
    c8_identifier = c8_varName;
    c8_thisId.fIdentifier = c8_identifier;
    c8_thisId.fParent = NULL;
    c8_y = c8_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_out_flags),
      &c8_thisId);
    sf_mex_destroy(&c8_out_flags);
    *(uint8_T *)c8_outData = c8_y;
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static const mxArray *c8_k_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  uint8_T c8_u;
  const mxArray *c8_y = NULL;
  uint8_T c8_b_u;
  const mxArray *c8_b_y = NULL;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(uint8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c8_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_d_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c8_mxArrayOutData, c8_y);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c8_mxArrayOutData;
}

static const mxArray *c8_l_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  int8_T c8_u;
  const mxArray *c8_y = NULL;
  int8_T c8_b_u;
  const mxArray *c8_b_y = NULL;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(int8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c8_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_b_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c8_mxArrayOutData, c8_y);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c8_mxArrayOutData;
}

static int8_T c8_k_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_shift_out, const char_T *c8_identifier)
{
  int8_T c8_y;
  emlrtMsgIdentifier c8_thisId;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_shift_out),
    &c8_thisId);
  sf_mex_destroy(&c8_shift_out);
  return c8_y;
}

static int8_T c8_l_emlrt_marshallIn(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int8_T c8_y;
  const mxArray *c8_mxFi = NULL;
  const mxArray *c8_mxInt = NULL;
  int8_T c8_i3;
  sf_mex_check_fi(c8_parentId, c8_u, 0, 0U, 0, c8_eml_mx, c8_b_eml_mx);
  sf_mex_assign(&c8_mxFi, sf_mex_dup(c8_u));
  sf_mex_assign(&c8_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c8_mxFi)));
  sf_mex_import(c8_parentId, sf_mex_dup(c8_mxInt), &c8_i3, 1, 2, 0U, 0, 0U, 0);
  sf_mex_destroy(&c8_mxFi);
  sf_mex_destroy(&c8_mxInt);
  c8_y = c8_i3;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_shift_out;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  int8_T c8_y;
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c8_shift_out = sf_mex_dup(c8_mxArrayInData);
    c8_identifier = c8_varName;
    c8_thisId.fIdentifier = c8_identifier;
    c8_thisId.fParent = NULL;
    c8_y = c8_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_shift_out),
      &c8_thisId);
    sf_mex_destroy(&c8_shift_out);
    *(int8_T *)c8_outData = c8_y;
  }

  sf_mex_destroy(&c8_mxArrayInData);
}

static void init_dsm_address_info(SFc8_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
static uint32_T* sf_get_sfun_dwork_checksum();
void sf_c8_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3673893042U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2938180403U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(181863011U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1577539318U);
}

mxArray *sf_c8_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(1087626099U);
    pr[1] = (double)(74653550U);
    pr[2] = (double)(1803711865U);
    pr[3] = (double)(1004065245U);
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
        mxSetField(mxFixpt,0,"isSigned",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(4));
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c8_hdlcodercpu_eml(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[4],T\"out_flags\",},{M[1],M[6],T\"shift_out\",},{M[8],M[0],T\"is_active_c8_hdlcodercpu_eml\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c8_hdlcodercpu_eml_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
    chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_hdlcodercpu_emlMachineNumber_,
           8,
           1,
           1,
           5,
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
          _SFD_SET_DATA_PROPS(0,2,0,1,"out_flags");
          _SFD_SET_DATA_PROPS(1,1,1,0,"select");
          _SFD_SET_DATA_PROPS(2,2,0,1,"shift_out");
          _SFD_SET_DATA_PROPS(3,1,1,0,"input");
          _SFD_SET_DATA_PROPS(4,1,1,0,"in_flags");
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
        _SFD_CV_INIT_EML(0,1,0,0,1,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1210);

        {
          static int caseStart[] = { 853, 536, 781 };

          static int caseExprEnd[] = { 862, 542, 787 };

          _SFD_CV_INIT_EML_SWITCH(0,0,510,531,940,3,&(caseStart[0]),
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
          (MexFcnForType)c8_j_sf_marshallOut,(MexInFcnForType)c8_h_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,1,0,2,0,1,0,0,
          (MexFcnForType)c8_k_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c8_l_sf_marshallOut,(MexInFcnForType)c8_i_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c8_l_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,0,NULL,1,0,4,0,1,0,0,
          (MexFcnForType)c8_j_sf_marshallOut,(MexInFcnForType)NULL);

        {
          uint8_T *c8_out_flags;
          uint8_T *c8_select;
          int8_T *c8_shift_out;
          int8_T *c8_input;
          uint8_T *c8_in_flags;
          c8_in_flags = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c8_input = (int8_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c8_shift_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c8_select = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
          c8_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, c8_out_flags);
          _SFD_SET_DATA_VALUE_PTR(1U, c8_select);
          _SFD_SET_DATA_VALUE_PTR(2U, c8_shift_out);
          _SFD_SET_DATA_VALUE_PTR(3U, c8_input);
          _SFD_SET_DATA_VALUE_PTR(4U, c8_in_flags);
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
      "hdlcodercpu_eml", "hdlcodercpu_eml", 8, "dworkChecksum");
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

static void sf_opaque_initialize_c8_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc8_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S);
  chart_debug_initialization(((SFc8_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c8_hdlcodercpu_eml((SFc8_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
  initialize_c8_hdlcodercpu_eml((SFc8_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c8_hdlcodercpu_eml(void *chartInstanceVar)
{
  enable_c8_hdlcodercpu_eml((SFc8_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c8_hdlcodercpu_eml(void *chartInstanceVar)
{
  disable_c8_hdlcodercpu_eml((SFc8_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c8_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_c8_hdlcodercpu_eml((SFc8_hdlcodercpu_emlInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c8_hdlcodercpu_eml(void *chartInstanceVar)
{
  ext_mode_exec_c8_hdlcodercpu_eml((SFc8_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c8_hdlcodercpu_eml(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c8_hdlcodercpu_eml
    ((SFc8_hdlcodercpu_emlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_hdlcodercpu_eml();/* state var info */
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

extern void sf_internal_set_sim_state_c8_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c8_hdlcodercpu_eml((SFc8_hdlcodercpu_emlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c8_hdlcodercpu_eml(SimStruct* S)
{
  return sf_internal_get_sim_state_c8_hdlcodercpu_eml(S);
}

static void sf_opaque_set_sim_state_c8_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c8_hdlcodercpu_eml(S, st);
}

static void sf_opaque_terminate_c8_hdlcodercpu_eml(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc8_hdlcodercpu_emlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c8_hdlcodercpu_eml((SFc8_hdlcodercpu_emlInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc8_hdlcodercpu_eml((SFc8_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c8_hdlcodercpu_eml(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c8_hdlcodercpu_eml((SFc8_hdlcodercpu_emlInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

mxArray *sf_c8_hdlcodercpu_eml_get_testpoint_info(void)
{
  const char *infoEncStr[] = {
    "100 S'varName','path'{{T\"is_active_c8_hdlcodercpu_eml\",T\"is_active_c8_hdlcodercpu_eml\"}}"
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

static void mdlSetWorkWidths_c8_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"hdlcodercpu_eml","hdlcodercpu_eml",8);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml","hdlcodercpu_eml",8,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml",
      "hdlcodercpu_eml",8,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",
        8,3);
      sf_mark_chart_reusable_outputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",8,2);
    }

    sf_set_rtw_dwork_info(S,"hdlcodercpu_eml","hdlcodercpu_eml",8);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(260771307U));
  ssSetChecksum1(S,(2614045827U));
  ssSetChecksum2(S,(83519038U));
  ssSetChecksum3(S,(1647361958U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c8_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "hdlcodercpu_eml", "hdlcodercpu_eml",8);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c8_hdlcodercpu_eml(SimStruct *S)
{
  SFc8_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_hdlcodercpu_emlInstanceStruct *)malloc(sizeof
    (SFc8_hdlcodercpu_emlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc8_hdlcodercpu_emlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c8_hdlcodercpu_eml;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c8_hdlcodercpu_eml;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c8_hdlcodercpu_eml;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c8_hdlcodercpu_eml;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c8_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c8_hdlcodercpu_eml;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c8_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c8_hdlcodercpu_eml;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c8_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlStart = mdlStart_c8_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c8_hdlcodercpu_eml;
  chartInstance->chartInfo.extModeExec =
    sf_opaque_ext_mode_exec_c8_hdlcodercpu_eml;
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

void c8_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c8_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c8_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c8_hdlcodercpu_eml(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c8_hdlcodercpu_eml_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
