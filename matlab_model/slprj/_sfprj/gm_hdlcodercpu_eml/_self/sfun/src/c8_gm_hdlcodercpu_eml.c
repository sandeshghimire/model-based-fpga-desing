/* Include files */

#include <stddef.h>
#include "blas.h"
#include "gm_hdlcodercpu_eml_sfun.h"
#include "c8_gm_hdlcodercpu_eml.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "gm_hdlcodercpu_eml_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const mxArray *c8_eml_mx;
static const char * c8_debug_family_names[13] = { "hdl_fm", "overflow", "c_out",
  "sign_bit", "is_zero", "zero_ufix1", "nargin", "nargout", "select", "input",
  "in_flags", "out_flags", "shift_out" };

static const mxArray *c8_b_eml_mx;
static const mxArray *c8_c_eml_mx;
static const mxArray *c8_d_eml_mx;
static const mxArray *c8_e_eml_mx;

/* Function Declarations */
static void initialize_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static void initialize_params_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static void enable_c8_gm_hdlcodercpu_eml(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void disable_c8_gm_hdlcodercpu_eml(SFc8_gm_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void c8_update_debugger_state_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static void set_sim_state_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance, const mxArray *c8_st);
static void finalize_c8_gm_hdlcodercpu_eml(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void sf_gateway_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static void c8_chartstep_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static void initSimStructsc8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber, uint32_T c8_instanceNumber);
static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData);
static int8_T c8_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_b_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static uint8_T c8_b_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_c_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static real_T c8_c_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_e_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static uint8_T c8_d_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_f_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static uint8_T c8_e_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_is_zero, const char_T *c8_identifier);
static uint8_T c8_f_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_g_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static uint8_T c8_g_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_h_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static void c8_info_helper(const mxArray **c8_info);
static const mxArray *c8_emlrt_marshallOut(const char * c8_u);
static const mxArray *c8_b_emlrt_marshallOut(const uint32_T c8_u);
static void c8_b_info_helper(const mxArray **c8_info);
static void c8_c_info_helper(const mxArray **c8_info);
static uint8_T c8_uint8(SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c8_A);
static int8_T c8_bitsra(SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c8_ain);
static int8_T c8_bitsll(SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c8_ain);
static uint8_T c8_bitxor(SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c8_a, uint8_T c8_b);
static boolean_T c8_all(SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c8_x);
static const mxArray *c8_i_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int32_T c8_h_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_j_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static uint8_T c8_i_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_out_flags, const char_T *c8_identifier);
static uint8_T c8_j_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static const mxArray *c8_k_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static const mxArray *c8_l_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData);
static int8_T c8_k_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_shift_out, const char_T *c8_identifier);
static int8_T c8_l_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId);
static void c8_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData);
static void init_dsm_address_info(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  chartInstance->c8_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c8_is_active_c8_gm_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c8_e_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 1.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c8_d_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 2.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c8_c_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 4.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c8_b_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 10U, 15, "WordLength", 6, 8.0, 15, "FractionLength", 6,
    0.0, 15, "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6,
    0.0), true);
  sf_mex_assign(&c8_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
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

static void initialize_params_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c8_gm_hdlcodercpu_eml(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c8_gm_hdlcodercpu_eml(SFc8_gm_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c8_update_debugger_state_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
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
  c8_shift_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c8_st = NULL;
  c8_st = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_createcellmatrix(3, 1), false);
  c8_hoistedGlobal = *c8_out_flags;
  c8_u = c8_hoistedGlobal;
  c8_b_y = NULL;
  c8_b_u = c8_u;
  c8_c_y = NULL;
  sf_mex_assign(&c8_c_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c8_b_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_c_eml_mx), 15,
    "simulinkarray", 14, c8_c_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c8_y, 0, c8_b_y);
  c8_b_hoistedGlobal = *c8_shift_out;
  c8_c_u = c8_b_hoistedGlobal;
  c8_d_y = NULL;
  c8_d_u = c8_c_u;
  c8_e_y = NULL;
  sf_mex_assign(&c8_e_y, sf_mex_create("y", &c8_d_u, 2, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c8_d_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_b_eml_mx), 15,
    "simulinkarray", 14, c8_e_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c8_y, 1, c8_d_y);
  c8_c_hoistedGlobal = chartInstance->c8_is_active_c8_gm_hdlcodercpu_eml;
  c8_e_u = c8_c_hoistedGlobal;
  c8_f_y = NULL;
  sf_mex_assign(&c8_f_y, sf_mex_create("y", &c8_e_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c8_y, 2, c8_f_y);
  sf_mex_assign(&c8_st, c8_y, false);
  return c8_st;
}

static void set_sim_state_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance, const mxArray *c8_st)
{
  const mxArray *c8_u;
  uint8_T *c8_out_flags;
  int8_T *c8_shift_out;
  c8_shift_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c8_doneDoubleBufferReInit = true;
  c8_u = sf_mex_dup(c8_st);
  *c8_out_flags = c8_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c8_u, 0)), "out_flags");
  *c8_shift_out = c8_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c8_u, 1)), "shift_out");
  chartInstance->c8_is_active_c8_gm_hdlcodercpu_eml = c8_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c8_u, 2)),
     "is_active_c8_gm_hdlcodercpu_eml");
  sf_mex_destroy(&c8_u);
  c8_update_debugger_state_c8_gm_hdlcodercpu_eml(chartInstance);
  sf_mex_destroy(&c8_st);
}

static void finalize_c8_gm_hdlcodercpu_eml(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
  sf_mex_destroy(&c8_eml_mx);
  sf_mex_destroy(&c8_b_eml_mx);
  sf_mex_destroy(&c8_c_eml_mx);
  sf_mex_destroy(&c8_d_eml_mx);
  sf_mex_destroy(&c8_e_eml_mx);
}

static void sf_gateway_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
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
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
  chartInstance->c8_sfEvent = CALL_EVENT;
  c8_chartstep_c8_gm_hdlcodercpu_eml(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_gm_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK((real_T)*c8_out_flags, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c8_select, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c8_shift_out, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*c8_input, 3U);
  _SFD_DATA_RANGE_CHECK((real_T)*c8_in_flags, 4U);
}

static void c8_chartstep_c8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
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
  uint8_T c8_a1;
  uint8_T c8_slice_temp;
  uint8_T c8_b_a;
  uint8_T c8_b_a1;
  uint8_T c8_b_slice_temp;
  int8_T c8_c_a;
  int8_T c8_c_a1;
  uint8_T c8_c_slice_temp;
  int8_T c8_d_a;
  int8_T c8_d_a1;
  uint8_T c8_d_slice_temp;
  uint8_T c8_c;
  int8_T c8_e_a;
  int8_T c8_e_a1;
  uint8_T c8_e_slice_temp;
  uint8_T c8_b_c;
  int8_T c8_f_a;
  const mxArray *c8_T = NULL;
  const mxArray *c8_F = NULL;
  const mxArray *c8_val = NULL;
  const mxArray *c8_unusedU2 = NULL;
  const mxArray *c8_unusedU3 = NULL;
  const mxArray *c8_isfimathlocal = NULL;
  uint8_T c8_f_slice_temp;
  uint8_T c8_varargin_1;
  uint8_T c8_b_varargin_1;
  uint8_T c8_var1;
  const mxArray *c8_b_T = NULL;
  const mxArray *c8_b_F = NULL;
  const mxArray *c8_b_val = NULL;
  const mxArray *c8_isautoscaled = NULL;
  const mxArray *c8_pvpairsetdata = NULL;
  const mxArray *c8_b_isfimathlocal = NULL;
  uint8_T c8_c_varargin_1;
  uint8_T c8_varargin_2;
  uint8_T c8_d_varargin_1;
  uint8_T c8_b_varargin_2;
  uint8_T c8_varargout_2;
  uint8_T c8_c_c;
  uint8_T c8_e_varargin_1;
  uint8_T c8_c_varargin_2;
  uint8_T c8_f_varargin_1;
  uint8_T c8_d_varargin_2;
  uint8_T c8_b_varargout_2;
  uint8_T c8_d_c;
  uint8_T c8_g_varargin_1;
  uint8_T c8_e_varargin_2;
  uint8_T c8_h_varargin_1;
  uint8_T c8_f_varargin_2;
  uint8_T c8_c_varargout_2;
  int8_T c8_i_varargin_1;
  int8_T c8_j_varargin_1;
  const mxArray *c8_c_T = NULL;
  const mxArray *c8_c_F = NULL;
  const mxArray *c8_c_val = NULL;
  const mxArray *c8_b_isautoscaled = NULL;
  const mxArray *c8_b_pvpairsetdata = NULL;
  const mxArray *c8_c_isfimathlocal = NULL;
  int8_T c8_b_var1;
  uint8_T *c8_b_select;
  int8_T *c8_b_input;
  uint8_T *c8_b_in_flags;
  uint8_T *c8_b_out_flags;
  int8_T *c8_b_shift_out;
  c8_b_in_flags = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c8_b_input = (int8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c8_b_shift_out = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c8_b_select = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c8_b_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
  c8_hoistedGlobal = *c8_b_select;
  c8_b_hoistedGlobal = *c8_b_input;
  c8_c_hoistedGlobal = *c8_b_in_flags;
  c8_select = c8_hoistedGlobal;
  c8_input = c8_b_hoistedGlobal;
  c8_in_flags = c8_c_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 13U, c8_debug_family_names,
    c8_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_hdl_fm, 0U, c8_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_overflow, 1U, c8_g_sf_marshallOut,
    c8_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_c_out, 2U, c8_g_sf_marshallOut,
    c8_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_sign_bit, 3U, c8_g_sf_marshallOut,
    c8_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_is_zero, 4U, c8_f_sf_marshallOut,
    c8_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_zero_ufix1, 5U, c8_e_sf_marshallOut,
    c8_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargin, 6U, c8_d_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_nargout, 7U, c8_d_sf_marshallOut,
    c8_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_select, 8U, c8_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_input, 9U, c8_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c8_in_flags, 10U, c8_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_out_flags, 11U, c8_b_sf_marshallOut,
    c8_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c8_shift_out, 12U, c8_sf_marshallOut,
    c8_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 8);
  c8_hdl_fm = c8_eml_mx;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 16);
  c8_a = c8_in_flags;
  c8_overflow = 0U;
  c8_a1 = c8_a;
  c8_slice_temp = (uint8_T)((uint8_T)((uint32_T)c8_a1 >> 1) & 1U);
  c8_overflow = c8_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 19);
  c8_b_a = c8_in_flags;
  c8_c_out = 0U;
  c8_b_a1 = c8_b_a;
  c8_b_slice_temp = (uint8_T)((uint8_T)((uint32_T)c8_b_a1 >> 3) & 1U);
  c8_c_out = c8_b_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 21);
  switch (c8_uint8(chartInstance, c8_select)) {
   case 1U:
    CV_EML_SWITCH(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 25);
    c8_shift_out = c8_bitsll(chartInstance, c8_input);
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 27);
    c8_c_a = c8_input;
    c8_c_out = 0U;
    c8_c_a1 = c8_c_a;
    c8_c_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
      (uint8_T)c8_c_a1 >> 7) & 1) & 1U);
    c8_c_out = c8_c_slice_temp;
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 29);
    c8_d_a = c8_input;
    c8_d_a1 = c8_d_a;
    c8_d_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
      (uint8_T)c8_d_a1 >> 7) & 1) & 1U);
    c8_c = c8_d_slice_temp;
    c8_e_a = c8_input;
    c8_e_a1 = c8_e_a;
    c8_e_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
      (uint8_T)c8_e_a1 >> 6) & 1) & 1U);
    c8_b_c = c8_e_slice_temp;
    c8_overflow = c8_bitxor(chartInstance, c8_c, c8_b_c);
    break;

   case 2U:
    CV_EML_SWITCH(0, 1, 0, 2);
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 32);
    c8_shift_out = c8_bitsra(chartInstance, c8_input);
    break;

   default:
    CV_EML_SWITCH(0, 1, 0, 0);
    _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 35);
    c8_i_varargin_1 = c8_input;
    c8_j_varargin_1 = c8_i_varargin_1;
    c8_b_var1 = c8_j_varargin_1;
    c8_shift_out = c8_b_var1;
    sf_mex_destroy(&c8_c_T);
    sf_mex_destroy(&c8_c_F);
    sf_mex_destroy(&c8_c_val);
    sf_mex_destroy(&c8_b_isautoscaled);
    sf_mex_destroy(&c8_b_pvpairsetdata);
    sf_mex_destroy(&c8_c_isfimathlocal);
    break;
  }

  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 39);
  c8_f_a = c8_shift_out;
  sf_mex_destroy(&c8_T);
  sf_mex_destroy(&c8_F);
  sf_mex_destroy(&c8_val);
  sf_mex_destroy(&c8_unusedU2);
  sf_mex_destroy(&c8_unusedU3);
  sf_mex_destroy(&c8_isfimathlocal);
  c8_sign_bit = 0U;
  c8_f_slice_temp = (uint8_T)((uint8_T)(int8_T)((int8_T)(uint8_T)((uint32_T)
    (uint8_T)c8_f_a >> 7) & 1) & 1U);
  c8_sign_bit = c8_f_slice_temp;
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 42);
  c8_is_zero = (uint8_T)!c8_all(chartInstance, c8_shift_out);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 43);
  c8_varargin_1 = c8_is_zero;
  c8_b_varargin_1 = c8_varargin_1;
  c8_var1 = c8_b_varargin_1;
  c8_zero_ufix1 = (uint8_T)(c8_var1 & 1U);
  sf_mex_destroy(&c8_b_T);
  sf_mex_destroy(&c8_b_F);
  sf_mex_destroy(&c8_b_val);
  sf_mex_destroy(&c8_isautoscaled);
  sf_mex_destroy(&c8_pvpairsetdata);
  sf_mex_destroy(&c8_b_isfimathlocal);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, 46);
  c8_c_varargin_1 = c8_c_out;
  c8_varargin_2 = c8_sign_bit;
  c8_d_varargin_1 = c8_c_varargin_1;
  c8_b_varargin_2 = c8_varargin_2;
  c8_varargout_2 = c8_b_varargin_2;
  c8_c_c = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)(c8_d_varargin_1 &
    3U) << 1) & 3U) | (uint8_T)(c8_varargout_2 & 3U)) & 3U);
  c8_e_varargin_1 = c8_c_c;
  c8_c_varargin_2 = c8_overflow;
  c8_f_varargin_1 = c8_e_varargin_1;
  c8_d_varargin_2 = c8_c_varargin_2;
  c8_b_varargout_2 = c8_d_varargin_2;
  c8_d_c = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)(c8_f_varargin_1 &
    7U) << 1) & 7U) | (uint8_T)(c8_b_varargout_2 & 7U)) & 7U);
  c8_g_varargin_1 = c8_d_c;
  c8_e_varargin_2 = c8_zero_ufix1;
  c8_h_varargin_1 = c8_g_varargin_1;
  c8_f_varargin_2 = c8_e_varargin_2;
  c8_c_varargout_2 = c8_f_varargin_2;
  c8_out_flags = (uint8_T)((uint8_T)((uint8_T)((uint8_T)((uint8_T)
    (c8_h_varargin_1 & 15U) << 1) & 15U) | (uint8_T)(c8_c_varargout_2 & 15U)) &
    15U);
  _SFD_EML_CALL(0U, chartInstance->c8_sfEvent, -46);
  _SFD_SYMBOL_SCOPE_POP();
  *c8_b_out_flags = c8_out_flags;
  *c8_b_shift_out = c8_shift_out;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c8_sfEvent);
}

static void initSimStructsc8_gm_hdlcodercpu_eml
  (SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c8_machineNumber, uint32_T
  c8_chartNumber, uint32_T c8_instanceNumber)
{
  (void)c8_machineNumber;
  (void)c8_chartNumber;
  (void)c8_instanceNumber;
}

static const mxArray *c8_sf_marshallOut(void *chartInstanceVoid, void *c8_inData)
{
  const mxArray *c8_mxArrayOutData;
  int8_T c8_u;
  const mxArray *c8_y = NULL;
  int8_T c8_b_u;
  const mxArray *c8_b_y = NULL;
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(int8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 2, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c8_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_b_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c8_mxArrayOutData;
}

static int8_T c8_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int8_T c8_y;
  const mxArray *c8_mxFi = NULL;
  const mxArray *c8_mxInt = NULL;
  int8_T c8_i0;
  (void)chartInstance;
  sf_mex_check_fi(c8_parentId, c8_u, false, 0U, NULL, c8_eml_mx, c8_b_eml_mx);
  sf_mex_assign(&c8_mxFi, sf_mex_dup(c8_u), false);
  sf_mex_assign(&c8_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c8_mxFi)), false);
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(uint8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c8_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_c_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c8_mxArrayOutData;
}

static uint8_T c8_b_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  const mxArray *c8_mxFi = NULL;
  const mxArray *c8_mxInt = NULL;
  uint8_T c8_u0;
  (void)chartInstance;
  sf_mex_check_fi(c8_parentId, c8_u, false, 0U, NULL, c8_eml_mx, c8_c_eml_mx);
  sf_mex_assign(&c8_mxFi, sf_mex_dup(c8_u), false);
  sf_mex_assign(&c8_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c8_mxFi)), false);
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(uint8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c8_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_d_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c8_mxArrayOutData;
}

static const mxArray *c8_d_sf_marshallOut(void *chartInstanceVoid, void
  *c8_inData)
{
  const mxArray *c8_mxArrayOutData = NULL;
  real_T c8_u;
  const mxArray *c8_y = NULL;
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(real_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static real_T c8_c_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  real_T c8_y;
  real_T c8_d0;
  (void)chartInstance;
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(uint8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c8_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_e_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c8_mxArrayOutData;
}

static uint8_T c8_d_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  const mxArray *c8_mxFi = NULL;
  const mxArray *c8_mxInt = NULL;
  uint8_T c8_u1;
  (void)chartInstance;
  sf_mex_check_fi(c8_parentId, c8_u, false, 0U, NULL, c8_eml_mx, c8_e_eml_mx);
  sf_mex_assign(&c8_mxFi, sf_mex_dup(c8_u), false);
  sf_mex_assign(&c8_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c8_mxFi)), false);
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(uint8_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static uint8_T c8_e_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c8_f_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  uint8_T c8_u2;
  (void)chartInstance;
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(uint8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c8_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_e_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c8_mxArrayOutData;
}

static uint8_T c8_g_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  const mxArray *c8_mxFi = NULL;
  const mxArray *c8_mxInt = NULL;
  uint8_T c8_u3;
  (void)chartInstance;
  sf_mex_check_fi(c8_parentId, c8_u, false, 0U, NULL, c8_eml_mx, c8_e_eml_mx);
  sf_mex_assign(&c8_mxFi, sf_mex_dup(c8_u), false);
  sf_mex_assign(&c8_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c8_mxFi)), false);
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = sf_mex_dup(*(const mxArray **)c8_inData);
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_duplicatearraysafe(&c8_u), false);
  sf_mex_destroy(&c8_u);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

const mxArray *sf_c8_gm_hdlcodercpu_eml_get_eml_resolved_functions_info(void)
{
  const mxArray *c8_nameCaptureInfo = NULL;
  c8_nameCaptureInfo = NULL;
  sf_mex_assign(&c8_nameCaptureInfo, sf_mex_createstruct("structure", 2, 134, 1),
                false);
  c8_info_helper(&c8_nameCaptureInfo);
  c8_b_info_helper(&c8_nameCaptureInfo);
  c8_c_info_helper(&c8_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c8_nameCaptureInfo);
  return c8_nameCaptureInfo;
}

static void c8_info_helper(const mxArray **c8_info)
{
  const mxArray *c8_rhs0 = NULL;
  const mxArray *c8_lhs0 = NULL;
  const mxArray *c8_rhs1 = NULL;
  const mxArray *c8_lhs1 = NULL;
  const mxArray *c8_rhs2 = NULL;
  const mxArray *c8_lhs2 = NULL;
  const mxArray *c8_rhs3 = NULL;
  const mxArray *c8_lhs3 = NULL;
  const mxArray *c8_rhs4 = NULL;
  const mxArray *c8_lhs4 = NULL;
  const mxArray *c8_rhs5 = NULL;
  const mxArray *c8_lhs5 = NULL;
  const mxArray *c8_rhs6 = NULL;
  const mxArray *c8_lhs6 = NULL;
  const mxArray *c8_rhs7 = NULL;
  const mxArray *c8_lhs7 = NULL;
  const mxArray *c8_rhs8 = NULL;
  const mxArray *c8_lhs8 = NULL;
  const mxArray *c8_rhs9 = NULL;
  const mxArray *c8_lhs9 = NULL;
  const mxArray *c8_rhs10 = NULL;
  const mxArray *c8_lhs10 = NULL;
  const mxArray *c8_rhs11 = NULL;
  const mxArray *c8_lhs11 = NULL;
  const mxArray *c8_rhs12 = NULL;
  const mxArray *c8_lhs12 = NULL;
  const mxArray *c8_rhs13 = NULL;
  const mxArray *c8_lhs13 = NULL;
  const mxArray *c8_rhs14 = NULL;
  const mxArray *c8_lhs14 = NULL;
  const mxArray *c8_rhs15 = NULL;
  const mxArray *c8_lhs15 = NULL;
  const mxArray *c8_rhs16 = NULL;
  const mxArray *c8_lhs16 = NULL;
  const mxArray *c8_rhs17 = NULL;
  const mxArray *c8_lhs17 = NULL;
  const mxArray *c8_rhs18 = NULL;
  const mxArray *c8_lhs18 = NULL;
  const mxArray *c8_rhs19 = NULL;
  const mxArray *c8_lhs19 = NULL;
  const mxArray *c8_rhs20 = NULL;
  const mxArray *c8_lhs20 = NULL;
  const mxArray *c8_rhs21 = NULL;
  const mxArray *c8_lhs21 = NULL;
  const mxArray *c8_rhs22 = NULL;
  const mxArray *c8_lhs22 = NULL;
  const mxArray *c8_rhs23 = NULL;
  const mxArray *c8_lhs23 = NULL;
  const mxArray *c8_rhs24 = NULL;
  const mxArray *c8_lhs24 = NULL;
  const mxArray *c8_rhs25 = NULL;
  const mxArray *c8_lhs25 = NULL;
  const mxArray *c8_rhs26 = NULL;
  const mxArray *c8_lhs26 = NULL;
  const mxArray *c8_rhs27 = NULL;
  const mxArray *c8_lhs27 = NULL;
  const mxArray *c8_rhs28 = NULL;
  const mxArray *c8_lhs28 = NULL;
  const mxArray *c8_rhs29 = NULL;
  const mxArray *c8_lhs29 = NULL;
  const mxArray *c8_rhs30 = NULL;
  const mxArray *c8_lhs30 = NULL;
  const mxArray *c8_rhs31 = NULL;
  const mxArray *c8_lhs31 = NULL;
  const mxArray *c8_rhs32 = NULL;
  const mxArray *c8_lhs32 = NULL;
  const mxArray *c8_rhs33 = NULL;
  const mxArray *c8_lhs33 = NULL;
  const mxArray *c8_rhs34 = NULL;
  const mxArray *c8_lhs34 = NULL;
  const mxArray *c8_rhs35 = NULL;
  const mxArray *c8_lhs35 = NULL;
  const mxArray *c8_rhs36 = NULL;
  const mxArray *c8_lhs36 = NULL;
  const mxArray *c8_rhs37 = NULL;
  const mxArray *c8_lhs37 = NULL;
  const mxArray *c8_rhs38 = NULL;
  const mxArray *c8_lhs38 = NULL;
  const mxArray *c8_rhs39 = NULL;
  const mxArray *c8_lhs39 = NULL;
  const mxArray *c8_rhs40 = NULL;
  const mxArray *c8_lhs40 = NULL;
  const mxArray *c8_rhs41 = NULL;
  const mxArray *c8_lhs41 = NULL;
  const mxArray *c8_rhs42 = NULL;
  const mxArray *c8_lhs42 = NULL;
  const mxArray *c8_rhs43 = NULL;
  const mxArray *c8_lhs43 = NULL;
  const mxArray *c8_rhs44 = NULL;
  const mxArray *c8_lhs44 = NULL;
  const mxArray *c8_rhs45 = NULL;
  const mxArray *c8_lhs45 = NULL;
  const mxArray *c8_rhs46 = NULL;
  const mxArray *c8_lhs46 = NULL;
  const mxArray *c8_rhs47 = NULL;
  const mxArray *c8_lhs47 = NULL;
  const mxArray *c8_rhs48 = NULL;
  const mxArray *c8_lhs48 = NULL;
  const mxArray *c8_rhs49 = NULL;
  const mxArray *c8_lhs49 = NULL;
  const mxArray *c8_rhs50 = NULL;
  const mxArray *c8_lhs50 = NULL;
  const mxArray *c8_rhs51 = NULL;
  const mxArray *c8_lhs51 = NULL;
  const mxArray *c8_rhs52 = NULL;
  const mxArray *c8_lhs52 = NULL;
  const mxArray *c8_rhs53 = NULL;
  const mxArray *c8_lhs53 = NULL;
  const mxArray *c8_rhs54 = NULL;
  const mxArray *c8_lhs54 = NULL;
  const mxArray *c8_rhs55 = NULL;
  const mxArray *c8_lhs55 = NULL;
  const mxArray *c8_rhs56 = NULL;
  const mxArray *c8_lhs56 = NULL;
  const mxArray *c8_rhs57 = NULL;
  const mxArray *c8_lhs57 = NULL;
  const mxArray *c8_rhs58 = NULL;
  const mxArray *c8_lhs58 = NULL;
  const mxArray *c8_rhs59 = NULL;
  const mxArray *c8_lhs59 = NULL;
  const mxArray *c8_rhs60 = NULL;
  const mxArray *c8_lhs60 = NULL;
  const mxArray *c8_rhs61 = NULL;
  const mxArray *c8_lhs61 = NULL;
  const mxArray *c8_rhs62 = NULL;
  const mxArray *c8_lhs62 = NULL;
  const mxArray *c8_rhs63 = NULL;
  const mxArray *c8_lhs63 = NULL;
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("fimath"), "name", "name", 0);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1381857498U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c8_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_fimath_constructor_helper"),
                  "name", "name", 1);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_fimath_constructor_helper.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c8_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("bitget"), "name", "name", 2);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1370017086U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c8_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 3);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c8_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 4);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 4);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c8_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 5);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 5);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 5);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c8_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 6);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfixed"), "name", "name", 6);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c8_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "context", "context", 7);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("get"), "name", "name", 7);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 7);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c8_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 8);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("all"), "name", "name", 8);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "resolved",
                  "resolved", 8);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1372589614U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c8_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  9);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 9);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c8_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  10);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 10);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c8_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  11);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("coder.internal.allOrAny"),
                  "name", "name", 11);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1372590358U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c8_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 12);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 12);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c8_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 13);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isequal"), "name", "name", 13);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1286825958U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c8_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_isequal_core"), "name",
                  "name", 14);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1286825986U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c8_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 15);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "coder.internal.constNonSingletonDim"), "name", "name", 15);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/constNonSingletonDim.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1372590360U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c8_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 16);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("numerictype"), "name", "name",
                  16);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1348199118U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c8_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m"), "context",
                  "context", 17);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("length"), "name", "name", 17);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("cell"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 17);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1303153406U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c8_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 18);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("fimath"), "name", "name", 18);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303184U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c8_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/@embedded/@fi/bitget.m!convertOneBasedBitIndexToZeroBased"),
                  "context", "context", 19);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("floor"), "name", "name", 19);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c8_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 20);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c8_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 21);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1286825926U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c8_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "context", "context", 22);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("uint8"), "name", "name", 22);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1311262522U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c8_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m"),
                  "context", "context", 23);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_fi_getRealWorldValAsDType"),
                  "name", "name", 23);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getRealWorldValAsDType.m"),
                  "resolved", "resolved", 23);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517570U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c8_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getRealWorldValAsDType.m"),
                  "context", "context", 24);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isscaledtype"), "name", "name",
                  24);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 24);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c8_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "context", "context", 25);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfixed"), "name", "name", 25);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c8_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getRealWorldValAsDType.m"),
                  "context", "context", 26);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isscalingbinarypoint"), "name",
                  "name", 26);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscalingbinarypoint.m"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c8_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscalingbinarypoint.m"),
                  "context", "context", 27);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isscaledtype"), "name", "name",
                  27);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c8_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscalingbinarypoint.m"),
                  "context", "context", 28);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_isslopebiasscaled"),
                  "name", "name", 28);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c8_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "context", "context", 29);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("get"), "name", "name", 29);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 29);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 29);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c8_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getRealWorldValAsDType.m"),
                  "context", "context", 30);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("get"), "name", "name", 30);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/get.m"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1375987886U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c8_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/get.m"),
                  "context", "context", 31);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 31);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_scalar_eg.m"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517572U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c8_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_scalar_eg.m"),
                  "context", "context", 32);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("numerictype"), "name", "name",
                  32);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303186U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c8_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_scalar_eg.m"),
                  "context", "context", 33);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("fimath"), "name", "name", 33);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303184U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c8_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/get.m"),
                  "context", "context", 34);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_getfiprop_helper"), "name",
                  "name", 34);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_getfiprop_helper.m"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c8_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "context", "context", 35);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("bitsra"), "name", "name", 35);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitsra.m"),
                  "resolved", "resolved", 35);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517566U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c8_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitsra.m"),
                  "context", "context", 36);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_fi_bitshift"), "name",
                  "name", 36);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "resolved", "resolved", 36);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363717460U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c8_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 37);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_shift_checks"), "name",
                  "name", 37);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m"),
                  "resolved", "resolved", 37);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363717460U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c8_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m"),
                  "context", "context", 38);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 38);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 38);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c8_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m"),
                  "context", "context", 39);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("numerictype"), "name", "name",
                  39);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303186U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c8_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m"),
                  "context", "context", 40);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_isslopebiasscaled"),
                  "name", "name", 40);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "resolved", "resolved", 40);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c8_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m"),
                  "context", "context", 41);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isequal"), "name", "name", 41);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 41);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1286825958U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c8_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar"),
                  "context", "context", 42);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isnan"), "name", "name", 42);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 42);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363717458U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c8_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "context",
                  "context", 43);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 43);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 43);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c8_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 44);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("floor"), "name", "name", 44);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 44);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c8_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 45);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 45);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 45);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c8_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 46);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfixed"), "name", "name", 46);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 46);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 46);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c8_rhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 47);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("numerictype"), "name", "name",
                  47);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 47);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303186U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c8_rhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 48);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 48);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 48);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 48);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1381857500U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c8_rhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs48), "lhs", "lhs",
                  48);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 49);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("fimath"), "name", "name", 49);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 49);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m"), "resolved",
                  "resolved", 49);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1381857498U), "fileTimeLo",
                  "fileTimeLo", 49);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 49);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 49);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 49);
  sf_mex_assign(&c8_rhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs49), "rhs", "rhs",
                  49);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs49), "lhs", "lhs",
                  49);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 50);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "eml_get_int_shift_or_bit_index"), "name", "name", 50);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 50);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_get_int_shift_or_bit_index.m"),
                  "resolved", "resolved", 50);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363717432U), "fileTimeLo",
                  "fileTimeLo", 50);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 50);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 50);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 50);
  sf_mex_assign(&c8_rhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs50), "rhs", "rhs",
                  50);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs50), "lhs", "lhs",
                  50);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_get_int_shift_or_bit_index.m"),
                  "context", "context", 51);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("floor"), "name", "name", 51);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 51);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 51);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 51);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 51);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 51);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 51);
  sf_mex_assign(&c8_rhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs51), "rhs", "rhs",
                  51);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs51), "lhs", "lhs",
                  51);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/@embedded/@fi/eml_fi_bitshift.m!localFixptBitshift"),
                  "context", "context", 52);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_feval"), "name", "name",
                  52);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 52);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_feval.m"),
                  "resolved", "resolved", 52);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517570U), "fileTimeLo",
                  "fileTimeLo", 52);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 52);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 52);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 52);
  sf_mex_assign(&c8_rhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs52), "rhs", "rhs",
                  52);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs52), "lhs", "lhs",
                  52);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_feval.m"),
                  "context", "context", 53);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 53);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 53);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 53);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1381857500U), "fileTimeLo",
                  "fileTimeLo", 53);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 53);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 53);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 53);
  sf_mex_assign(&c8_rhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs53), "rhs", "rhs",
                  53);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs53), "lhs", "lhs",
                  53);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "context", "context", 54);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("bitsll"), "name", "name", 54);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 54);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitsll.m"),
                  "resolved", "resolved", 54);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517566U), "fileTimeLo",
                  "fileTimeLo", 54);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 54);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 54);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 54);
  sf_mex_assign(&c8_rhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs54), "rhs", "rhs",
                  54);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs54), "lhs", "lhs",
                  54);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitsll.m"),
                  "context", "context", 55);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_fi_bitshift"), "name",
                  "name", 55);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 55);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "resolved", "resolved", 55);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363717460U), "fileTimeLo",
                  "fileTimeLo", 55);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 55);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 55);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 55);
  sf_mex_assign(&c8_rhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs55), "rhs", "rhs",
                  55);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs55), "lhs", "lhs",
                  55);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "context", "context", 56);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("bitxor"), "name", "name", 56);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 56);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitxor.m"),
                  "resolved", "resolved", 56);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363717458U), "fileTimeLo",
                  "fileTimeLo", 56);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 56);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 56);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 56);
  sf_mex_assign(&c8_rhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs56), "rhs", "rhs",
                  56);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs56), "lhs", "lhs",
                  56);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitxor.m"),
                  "context", "context", 57);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 57);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 57);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 57);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 57);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 57);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 57);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 57);
  sf_mex_assign(&c8_rhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs57), "rhs", "rhs",
                  57);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs57), "lhs", "lhs",
                  57);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitxor.m"),
                  "context", "context", 58);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfixed"), "name", "name", 58);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 58);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 58);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 58);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 58);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 58);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 58);
  sf_mex_assign(&c8_rhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs58), "rhs", "rhs",
                  58);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs58), "lhs", "lhs",
                  58);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitxor.m"),
                  "context", "context", 59);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_isslopebiasscaled"),
                  "name", "name", 59);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 59);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "resolved", "resolved", 59);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 59);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 59);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 59);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 59);
  sf_mex_assign(&c8_rhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs59), "rhs", "rhs",
                  59);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs59), "lhs", "lhs",
                  59);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitxor.m"),
                  "context", "context", 60);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isequal"), "name", "name", 60);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 60);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/isequal.m"),
                  "resolved", "resolved", 60);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517540U), "fileTimeLo",
                  "fileTimeLo", 60);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 60);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 60);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 60);
  sf_mex_assign(&c8_rhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs60), "rhs", "rhs",
                  60);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs60), "lhs", "lhs",
                  60);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitxor.m"),
                  "context", "context", 61);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_checkfimathforbinaryops"),
                  "name", "name", 61);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 61);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_checkfimathforbinaryops.m"),
                  "resolved", "resolved", 61);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517568U), "fileTimeLo",
                  "fileTimeLo", 61);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 61);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 61);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 61);
  sf_mex_assign(&c8_rhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs61), "rhs", "rhs",
                  61);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs61), "lhs", "lhs",
                  61);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitxor.m"),
                  "context", "context", 62);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 62);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 62);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 62);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 62);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 62);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 62);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 62);
  sf_mex_assign(&c8_rhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs62), "rhs", "rhs",
                  62);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs62), "lhs", "lhs",
                  62);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "context", "context", 63);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("fi_impl"), "name", "name", 63);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 63);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "resolved",
                  "resolved", 63);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1389302372U), "fileTimeLo",
                  "fileTimeLo", 63);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 63);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 63);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 63);
  sf_mex_assign(&c8_rhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs63), "rhs", "rhs",
                  63);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs63), "lhs", "lhs",
                  63);
  sf_mex_destroy(&c8_rhs0);
  sf_mex_destroy(&c8_lhs0);
  sf_mex_destroy(&c8_rhs1);
  sf_mex_destroy(&c8_lhs1);
  sf_mex_destroy(&c8_rhs2);
  sf_mex_destroy(&c8_lhs2);
  sf_mex_destroy(&c8_rhs3);
  sf_mex_destroy(&c8_lhs3);
  sf_mex_destroy(&c8_rhs4);
  sf_mex_destroy(&c8_lhs4);
  sf_mex_destroy(&c8_rhs5);
  sf_mex_destroy(&c8_lhs5);
  sf_mex_destroy(&c8_rhs6);
  sf_mex_destroy(&c8_lhs6);
  sf_mex_destroy(&c8_rhs7);
  sf_mex_destroy(&c8_lhs7);
  sf_mex_destroy(&c8_rhs8);
  sf_mex_destroy(&c8_lhs8);
  sf_mex_destroy(&c8_rhs9);
  sf_mex_destroy(&c8_lhs9);
  sf_mex_destroy(&c8_rhs10);
  sf_mex_destroy(&c8_lhs10);
  sf_mex_destroy(&c8_rhs11);
  sf_mex_destroy(&c8_lhs11);
  sf_mex_destroy(&c8_rhs12);
  sf_mex_destroy(&c8_lhs12);
  sf_mex_destroy(&c8_rhs13);
  sf_mex_destroy(&c8_lhs13);
  sf_mex_destroy(&c8_rhs14);
  sf_mex_destroy(&c8_lhs14);
  sf_mex_destroy(&c8_rhs15);
  sf_mex_destroy(&c8_lhs15);
  sf_mex_destroy(&c8_rhs16);
  sf_mex_destroy(&c8_lhs16);
  sf_mex_destroy(&c8_rhs17);
  sf_mex_destroy(&c8_lhs17);
  sf_mex_destroy(&c8_rhs18);
  sf_mex_destroy(&c8_lhs18);
  sf_mex_destroy(&c8_rhs19);
  sf_mex_destroy(&c8_lhs19);
  sf_mex_destroy(&c8_rhs20);
  sf_mex_destroy(&c8_lhs20);
  sf_mex_destroy(&c8_rhs21);
  sf_mex_destroy(&c8_lhs21);
  sf_mex_destroy(&c8_rhs22);
  sf_mex_destroy(&c8_lhs22);
  sf_mex_destroy(&c8_rhs23);
  sf_mex_destroy(&c8_lhs23);
  sf_mex_destroy(&c8_rhs24);
  sf_mex_destroy(&c8_lhs24);
  sf_mex_destroy(&c8_rhs25);
  sf_mex_destroy(&c8_lhs25);
  sf_mex_destroy(&c8_rhs26);
  sf_mex_destroy(&c8_lhs26);
  sf_mex_destroy(&c8_rhs27);
  sf_mex_destroy(&c8_lhs27);
  sf_mex_destroy(&c8_rhs28);
  sf_mex_destroy(&c8_lhs28);
  sf_mex_destroy(&c8_rhs29);
  sf_mex_destroy(&c8_lhs29);
  sf_mex_destroy(&c8_rhs30);
  sf_mex_destroy(&c8_lhs30);
  sf_mex_destroy(&c8_rhs31);
  sf_mex_destroy(&c8_lhs31);
  sf_mex_destroy(&c8_rhs32);
  sf_mex_destroy(&c8_lhs32);
  sf_mex_destroy(&c8_rhs33);
  sf_mex_destroy(&c8_lhs33);
  sf_mex_destroy(&c8_rhs34);
  sf_mex_destroy(&c8_lhs34);
  sf_mex_destroy(&c8_rhs35);
  sf_mex_destroy(&c8_lhs35);
  sf_mex_destroy(&c8_rhs36);
  sf_mex_destroy(&c8_lhs36);
  sf_mex_destroy(&c8_rhs37);
  sf_mex_destroy(&c8_lhs37);
  sf_mex_destroy(&c8_rhs38);
  sf_mex_destroy(&c8_lhs38);
  sf_mex_destroy(&c8_rhs39);
  sf_mex_destroy(&c8_lhs39);
  sf_mex_destroy(&c8_rhs40);
  sf_mex_destroy(&c8_lhs40);
  sf_mex_destroy(&c8_rhs41);
  sf_mex_destroy(&c8_lhs41);
  sf_mex_destroy(&c8_rhs42);
  sf_mex_destroy(&c8_lhs42);
  sf_mex_destroy(&c8_rhs43);
  sf_mex_destroy(&c8_lhs43);
  sf_mex_destroy(&c8_rhs44);
  sf_mex_destroy(&c8_lhs44);
  sf_mex_destroy(&c8_rhs45);
  sf_mex_destroy(&c8_lhs45);
  sf_mex_destroy(&c8_rhs46);
  sf_mex_destroy(&c8_lhs46);
  sf_mex_destroy(&c8_rhs47);
  sf_mex_destroy(&c8_lhs47);
  sf_mex_destroy(&c8_rhs48);
  sf_mex_destroy(&c8_lhs48);
  sf_mex_destroy(&c8_rhs49);
  sf_mex_destroy(&c8_lhs49);
  sf_mex_destroy(&c8_rhs50);
  sf_mex_destroy(&c8_lhs50);
  sf_mex_destroy(&c8_rhs51);
  sf_mex_destroy(&c8_lhs51);
  sf_mex_destroy(&c8_rhs52);
  sf_mex_destroy(&c8_lhs52);
  sf_mex_destroy(&c8_rhs53);
  sf_mex_destroy(&c8_lhs53);
  sf_mex_destroy(&c8_rhs54);
  sf_mex_destroy(&c8_lhs54);
  sf_mex_destroy(&c8_rhs55);
  sf_mex_destroy(&c8_lhs55);
  sf_mex_destroy(&c8_rhs56);
  sf_mex_destroy(&c8_lhs56);
  sf_mex_destroy(&c8_rhs57);
  sf_mex_destroy(&c8_lhs57);
  sf_mex_destroy(&c8_rhs58);
  sf_mex_destroy(&c8_lhs58);
  sf_mex_destroy(&c8_rhs59);
  sf_mex_destroy(&c8_lhs59);
  sf_mex_destroy(&c8_rhs60);
  sf_mex_destroy(&c8_lhs60);
  sf_mex_destroy(&c8_rhs61);
  sf_mex_destroy(&c8_lhs61);
  sf_mex_destroy(&c8_rhs62);
  sf_mex_destroy(&c8_lhs62);
  sf_mex_destroy(&c8_rhs63);
  sf_mex_destroy(&c8_lhs63);
}

static const mxArray *c8_emlrt_marshallOut(const char * c8_u)
{
  const mxArray *c8_y = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", c8_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c8_u)), false);
  return c8_y;
}

static const mxArray *c8_b_emlrt_marshallOut(const uint32_T c8_u)
{
  const mxArray *c8_y = NULL;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 7, 0U, 0U, 0U, 0), false);
  return c8_y;
}

static void c8_b_info_helper(const mxArray **c8_info)
{
  const mxArray *c8_rhs64 = NULL;
  const mxArray *c8_lhs64 = NULL;
  const mxArray *c8_rhs65 = NULL;
  const mxArray *c8_lhs65 = NULL;
  const mxArray *c8_rhs66 = NULL;
  const mxArray *c8_lhs66 = NULL;
  const mxArray *c8_rhs67 = NULL;
  const mxArray *c8_lhs67 = NULL;
  const mxArray *c8_rhs68 = NULL;
  const mxArray *c8_lhs68 = NULL;
  const mxArray *c8_rhs69 = NULL;
  const mxArray *c8_lhs69 = NULL;
  const mxArray *c8_rhs70 = NULL;
  const mxArray *c8_lhs70 = NULL;
  const mxArray *c8_rhs71 = NULL;
  const mxArray *c8_lhs71 = NULL;
  const mxArray *c8_rhs72 = NULL;
  const mxArray *c8_lhs72 = NULL;
  const mxArray *c8_rhs73 = NULL;
  const mxArray *c8_lhs73 = NULL;
  const mxArray *c8_rhs74 = NULL;
  const mxArray *c8_lhs74 = NULL;
  const mxArray *c8_rhs75 = NULL;
  const mxArray *c8_lhs75 = NULL;
  const mxArray *c8_rhs76 = NULL;
  const mxArray *c8_lhs76 = NULL;
  const mxArray *c8_rhs77 = NULL;
  const mxArray *c8_lhs77 = NULL;
  const mxArray *c8_rhs78 = NULL;
  const mxArray *c8_lhs78 = NULL;
  const mxArray *c8_rhs79 = NULL;
  const mxArray *c8_lhs79 = NULL;
  const mxArray *c8_rhs80 = NULL;
  const mxArray *c8_lhs80 = NULL;
  const mxArray *c8_rhs81 = NULL;
  const mxArray *c8_lhs81 = NULL;
  const mxArray *c8_rhs82 = NULL;
  const mxArray *c8_lhs82 = NULL;
  const mxArray *c8_rhs83 = NULL;
  const mxArray *c8_lhs83 = NULL;
  const mxArray *c8_rhs84 = NULL;
  const mxArray *c8_lhs84 = NULL;
  const mxArray *c8_rhs85 = NULL;
  const mxArray *c8_lhs85 = NULL;
  const mxArray *c8_rhs86 = NULL;
  const mxArray *c8_lhs86 = NULL;
  const mxArray *c8_rhs87 = NULL;
  const mxArray *c8_lhs87 = NULL;
  const mxArray *c8_rhs88 = NULL;
  const mxArray *c8_lhs88 = NULL;
  const mxArray *c8_rhs89 = NULL;
  const mxArray *c8_lhs89 = NULL;
  const mxArray *c8_rhs90 = NULL;
  const mxArray *c8_lhs90 = NULL;
  const mxArray *c8_rhs91 = NULL;
  const mxArray *c8_lhs91 = NULL;
  const mxArray *c8_rhs92 = NULL;
  const mxArray *c8_lhs92 = NULL;
  const mxArray *c8_rhs93 = NULL;
  const mxArray *c8_lhs93 = NULL;
  const mxArray *c8_rhs94 = NULL;
  const mxArray *c8_lhs94 = NULL;
  const mxArray *c8_rhs95 = NULL;
  const mxArray *c8_lhs95 = NULL;
  const mxArray *c8_rhs96 = NULL;
  const mxArray *c8_lhs96 = NULL;
  const mxArray *c8_rhs97 = NULL;
  const mxArray *c8_lhs97 = NULL;
  const mxArray *c8_rhs98 = NULL;
  const mxArray *c8_lhs98 = NULL;
  const mxArray *c8_rhs99 = NULL;
  const mxArray *c8_lhs99 = NULL;
  const mxArray *c8_rhs100 = NULL;
  const mxArray *c8_lhs100 = NULL;
  const mxArray *c8_rhs101 = NULL;
  const mxArray *c8_lhs101 = NULL;
  const mxArray *c8_rhs102 = NULL;
  const mxArray *c8_lhs102 = NULL;
  const mxArray *c8_rhs103 = NULL;
  const mxArray *c8_lhs103 = NULL;
  const mxArray *c8_rhs104 = NULL;
  const mxArray *c8_lhs104 = NULL;
  const mxArray *c8_rhs105 = NULL;
  const mxArray *c8_lhs105 = NULL;
  const mxArray *c8_rhs106 = NULL;
  const mxArray *c8_lhs106 = NULL;
  const mxArray *c8_rhs107 = NULL;
  const mxArray *c8_lhs107 = NULL;
  const mxArray *c8_rhs108 = NULL;
  const mxArray *c8_lhs108 = NULL;
  const mxArray *c8_rhs109 = NULL;
  const mxArray *c8_lhs109 = NULL;
  const mxArray *c8_rhs110 = NULL;
  const mxArray *c8_lhs110 = NULL;
  const mxArray *c8_rhs111 = NULL;
  const mxArray *c8_lhs111 = NULL;
  const mxArray *c8_rhs112 = NULL;
  const mxArray *c8_lhs112 = NULL;
  const mxArray *c8_rhs113 = NULL;
  const mxArray *c8_lhs113 = NULL;
  const mxArray *c8_rhs114 = NULL;
  const mxArray *c8_lhs114 = NULL;
  const mxArray *c8_rhs115 = NULL;
  const mxArray *c8_lhs115 = NULL;
  const mxArray *c8_rhs116 = NULL;
  const mxArray *c8_lhs116 = NULL;
  const mxArray *c8_rhs117 = NULL;
  const mxArray *c8_lhs117 = NULL;
  const mxArray *c8_rhs118 = NULL;
  const mxArray *c8_lhs118 = NULL;
  const mxArray *c8_rhs119 = NULL;
  const mxArray *c8_lhs119 = NULL;
  const mxArray *c8_rhs120 = NULL;
  const mxArray *c8_lhs120 = NULL;
  const mxArray *c8_rhs121 = NULL;
  const mxArray *c8_lhs121 = NULL;
  const mxArray *c8_rhs122 = NULL;
  const mxArray *c8_lhs122 = NULL;
  const mxArray *c8_rhs123 = NULL;
  const mxArray *c8_lhs123 = NULL;
  const mxArray *c8_rhs124 = NULL;
  const mxArray *c8_lhs124 = NULL;
  const mxArray *c8_rhs125 = NULL;
  const mxArray *c8_lhs125 = NULL;
  const mxArray *c8_rhs126 = NULL;
  const mxArray *c8_lhs126 = NULL;
  const mxArray *c8_rhs127 = NULL;
  const mxArray *c8_lhs127 = NULL;
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 64);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 64);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 64);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 64);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 64);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 64);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 64);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 64);
  sf_mex_assign(&c8_rhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs64), "rhs", "rhs",
                  64);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs64), "lhs", "lhs",
                  64);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 65);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("length"), "name", "name", 65);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("cell"), "dominantType",
                  "dominantType", 65);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 65);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1303153406U), "fileTimeLo",
                  "fileTimeLo", 65);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 65);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 65);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 65);
  sf_mex_assign(&c8_rhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs65), "rhs", "rhs",
                  65);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs65), "lhs", "lhs",
                  65);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 66);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_fi_checkforconst"), "name",
                  "name", 66);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fimath"),
                  "dominantType", "dominantType", 66);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforconst.m"),
                  "resolved", "resolved", 66);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517552U), "fileTimeLo",
                  "fileTimeLo", 66);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 66);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 66);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 66);
  sf_mex_assign(&c8_rhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs66), "rhs", "rhs",
                  66);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs66), "lhs", "lhs",
                  66);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 67);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 67);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 67);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 67);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 67);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 67);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 67);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 67);
  sf_mex_assign(&c8_rhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs67), "rhs", "rhs",
                  67);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs67), "lhs", "lhs",
                  67);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 68);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfloat"), "name", "name", 68);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 68);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m"),
                  "resolved", "resolved", 68);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 68);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 68);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 68);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 68);
  sf_mex_assign(&c8_rhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs68), "rhs", "rhs",
                  68);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs68), "lhs", "lhs",
                  68);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m"),
                  "context", "context", 69);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("get"), "name", "name", 69);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 69);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 69);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 69);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 69);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 69);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 69);
  sf_mex_assign(&c8_rhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs69), "rhs", "rhs",
                  69);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs69), "lhs", "lhs",
                  69);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput"),
                  "context", "context", 70);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("castLike"), "name", "name", 70);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 70);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "resolved", "resolved", 70);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1348199122U), "fileTimeLo",
                  "fileTimeLo", 70);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 70);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 70);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 70);
  sf_mex_assign(&c8_rhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs70), "rhs", "rhs",
                  70);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs70), "lhs", "lhs",
                  70);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 71);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 71);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 71);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 71);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 71);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 71);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 71);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 71);
  sf_mex_assign(&c8_rhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs71), "rhs", "rhs",
                  71);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs71), "lhs", "lhs",
                  71);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 72);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfimathlocal"), "name",
                  "name", 72);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 72);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfimathlocal.m"),
                  "resolved", "resolved", 72);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 72);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 72);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 72);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 72);
  sf_mex_assign(&c8_rhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs72), "rhs", "rhs",
                  72);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs72), "lhs", "lhs",
                  72);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 73);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("removefimath"), "name", "name",
                  73);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 73);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/removefimath.m"), "resolved",
                  "resolved", 73);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1325034780U), "fileTimeLo",
                  "fileTimeLo", 73);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 73);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 73);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 73);
  sf_mex_assign(&c8_rhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs73), "rhs", "rhs",
                  73);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs73), "lhs", "lhs",
                  73);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 74);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("numerictype"), "name", "name",
                  74);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 74);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m"),
                  "resolved", "resolved", 74);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303186U), "fileTimeLo",
                  "fileTimeLo", 74);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 74);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 74);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 74);
  sf_mex_assign(&c8_rhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs74), "rhs", "rhs",
                  74);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs74), "lhs", "lhs",
                  74);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 75);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("fi_impl"), "name", "name", 75);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 75);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "resolved",
                  "resolved", 75);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1389302372U), "fileTimeLo",
                  "fileTimeLo", 75);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 75);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 75);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 75);
  sf_mex_assign(&c8_rhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs75), "rhs", "rhs",
                  75);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs75), "lhs", "lhs",
                  75);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 76);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 76);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 76);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 76);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 76);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 76);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 76);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 76);
  sf_mex_assign(&c8_rhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs76), "rhs", "rhs",
                  76);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs76), "lhs", "lhs",
                  76);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 77);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("get"), "name", "name", 77);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 77);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 77);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 77);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 77);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 77);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 77);
  sf_mex_assign(&c8_rhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs77), "rhs", "rhs",
                  77);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs77), "lhs", "lhs",
                  77);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 78);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("strcmpi"), "name", "name", 78);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 78);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "resolved",
                  "resolved", 78);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 78);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 78);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 78);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 78);
  sf_mex_assign(&c8_rhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs78), "rhs", "rhs",
                  78);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs78), "lhs", "lhs",
                  78);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "context",
                  "context", 79);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_assert_supported_string"),
                  "name", "name", 79);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 79);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m"),
                  "resolved", "resolved", 79);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 79);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 79);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 79);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 79);
  sf_mex_assign(&c8_rhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs79), "rhs", "rhs",
                  79);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs79), "lhs", "lhs",
                  79);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m!inrange"),
                  "context", "context", 80);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_charmax"), "name", "name",
                  80);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 80);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"),
                  "resolved", "resolved", 80);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 80);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 80);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 80);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 80);
  sf_mex_assign(&c8_rhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs80), "rhs", "rhs",
                  80);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs80), "lhs", "lhs",
                  80);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"), "context",
                  "context", 81);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("intmax"), "name", "name", 81);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 81);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 81);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 81);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 81);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 81);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 81);
  sf_mex_assign(&c8_rhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs81), "rhs", "rhs",
                  81);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs81), "lhs", "lhs",
                  81);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 82);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 82);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 82);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 82);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1381857500U), "fileTimeLo",
                  "fileTimeLo", 82);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 82);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 82);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 82);
  sf_mex_assign(&c8_rhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs82), "rhs", "rhs",
                  82);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs82), "lhs", "lhs",
                  82);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "context",
                  "context", 83);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("min"), "name", "name", 83);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 83);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 83);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1311262518U), "fileTimeLo",
                  "fileTimeLo", 83);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 83);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 83);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 83);
  sf_mex_assign(&c8_rhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs83), "rhs", "rhs",
                  83);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs83), "lhs", "lhs",
                  83);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "context",
                  "context", 84);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 84);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 84);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 84);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303184U), "fileTimeLo",
                  "fileTimeLo", 84);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 84);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 84);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 84);
  sf_mex_assign(&c8_rhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs84), "rhs", "rhs",
                  84);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs84), "lhs", "lhs",
                  84);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 85);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 85);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 85);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 85);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 85);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 85);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 85);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 85);
  sf_mex_assign(&c8_rhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs85), "rhs", "rhs",
                  85);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs85), "lhs", "lhs",
                  85);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 86);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 86);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 86);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 86);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 86);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 86);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 86);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 86);
  sf_mex_assign(&c8_rhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs86), "rhs", "rhs",
                  86);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs86), "lhs", "lhs",
                  86);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 87);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 87);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 87);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 87);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 87);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 87);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 87);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 87);
  sf_mex_assign(&c8_rhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs87), "rhs", "rhs",
                  87);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs87), "lhs", "lhs",
                  87);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 88);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 88);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 88);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 88);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 88);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 88);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 88);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 88);
  sf_mex_assign(&c8_rhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs88), "rhs", "rhs",
                  88);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs88), "lhs", "lhs",
                  88);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 89);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 89);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 89);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 89);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 89);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 89);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 89);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 89);
  sf_mex_assign(&c8_rhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs89), "rhs", "rhs",
                  89);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs89), "lhs", "lhs",
                  89);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 90);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 90);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 90);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 90);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 90);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 90);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 90);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 90);
  sf_mex_assign(&c8_rhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs90), "rhs", "rhs",
                  90);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs90), "lhs", "lhs",
                  90);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 91);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 91);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 91);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 91);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 91);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 91);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 91);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 91);
  sf_mex_assign(&c8_rhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs91), "rhs", "rhs",
                  91);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs91), "lhs", "lhs",
                  91);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 92);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 92);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 92);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 92);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 92);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 92);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 92);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 92);
  sf_mex_assign(&c8_rhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs92), "rhs", "rhs",
                  92);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs92), "lhs", "lhs",
                  92);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 93);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfimath"), "name", "name", 93);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 93);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfimath.m"), "resolved",
                  "resolved", 93);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 93);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 93);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 93);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 93);
  sf_mex_assign(&c8_rhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs93), "rhs", "rhs",
                  93);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs93), "lhs", "lhs",
                  93);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 94);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("get"), "name", "name", 94);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 94);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 94);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 94);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 94);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 94);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 94);
  sf_mex_assign(&c8_rhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs94), "rhs", "rhs",
                  94);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs94), "lhs", "lhs",
                  94);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 95);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_fi_constructor_helper"),
                  "name", "name", 95);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 95);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_fi_constructor_helper.m"),
                  "resolved", "resolved", 95);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 95);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 95);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 95);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 95);
  sf_mex_assign(&c8_rhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs95), "rhs", "rhs",
                  95);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs95), "lhs", "lhs",
                  95);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 96);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_fi_checkforerror"), "name",
                  "name", 96);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 96);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m"),
                  "resolved", "resolved", 96);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1360285946U), "fileTimeLo",
                  "fileTimeLo", 96);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 96);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 96);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 96);
  sf_mex_assign(&c8_rhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs96), "rhs", "rhs",
                  96);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs96), "lhs", "lhs",
                  96);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 97);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_fi_constructor_helper"),
                  "name", "name", 97);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 97);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_fi_constructor_helper.m"),
                  "resolved", "resolved", 97);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 97);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 97);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 97);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 97);
  sf_mex_assign(&c8_rhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs97), "rhs", "rhs",
                  97);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs97), "lhs", "lhs",
                  97);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 98);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_fi_checkforntype"), "name",
                  "name", 98);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 98);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m"),
                  "resolved", "resolved", 98);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1381857498U), "fileTimeLo",
                  "fileTimeLo", 98);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 98);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 98);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 98);
  sf_mex_assign(&c8_rhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs98), "rhs", "rhs",
                  98);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs98), "lhs", "lhs",
                  98);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m"),
                  "context", "context", 99);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("get"), "name", "name", 99);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 99);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 99);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 99);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 99);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 99);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 99);
  sf_mex_assign(&c8_rhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs99), "rhs", "rhs",
                  99);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs99), "lhs", "lhs",
                  99);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "context", "context", 100);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("getmsb"), "name", "name", 100);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 100);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m"),
                  "resolved", "resolved", 100);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1378303186U), "fileTimeLo",
                  "fileTimeLo", 100);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 100);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 100);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 100);
  sf_mex_assign(&c8_rhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs100), "rhs", "rhs",
                  100);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs100), "lhs", "lhs",
                  100);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m"),
                  "context", "context", 101);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfixed"), "name", "name", 101);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 101);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 101);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 101);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 101);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 101);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 101);
  sf_mex_assign(&c8_rhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs101), "rhs", "rhs",
                  101);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs101), "lhs", "lhs",
                  101);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m"),
                  "context", "context", 102);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_bitop_index_checks"),
                  "name", "name", 102);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 102);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_bitop_index_checks.m"),
                  "resolved", "resolved", 102);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1363717460U), "fileTimeLo",
                  "fileTimeLo", 102);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 102);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 102);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 102);
  sf_mex_assign(&c8_rhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs102), "rhs", "rhs",
                  102);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs102), "lhs", "lhs",
                  102);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_bitop_index_checks.m"),
                  "context", "context", 103);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 103);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 103);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 103);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 103);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 103);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 103);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 103);
  sf_mex_assign(&c8_rhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs103), "rhs", "rhs",
                  103);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs103), "lhs", "lhs",
                  103);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_bitop_index_checks.m"),
                  "context", "context", 104);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_isslopebiasscaled"),
                  "name", "name", 104);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 104);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "resolved", "resolved", 104);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 104);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 104);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 104);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 104);
  sf_mex_assign(&c8_rhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs104), "rhs", "rhs",
                  104);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs104), "lhs", "lhs",
                  104);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_bitop_index_checks.m"),
                  "context", "context", 105);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 105);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 105);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 105);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 105);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 105);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 105);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 105);
  sf_mex_assign(&c8_rhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs105), "rhs", "rhs",
                  105);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs105), "lhs", "lhs",
                  105);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 106);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 106);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 106);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 106);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 106);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 106);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 106);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 106);
  sf_mex_assign(&c8_rhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs106), "rhs", "rhs",
                  106);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs106), "lhs", "lhs",
                  106);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_bitop_index_checks.m"),
                  "context", "context", 107);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 107);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 107);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 107);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 107);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 107);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 107);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 107);
  sf_mex_assign(&c8_rhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs107), "rhs", "rhs",
                  107);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs107), "lhs", "lhs",
                  107);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m"),
                  "context", "context", 108);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("numerictype"), "name", "name",
                  108);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 108);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m"), "resolved",
                  "resolved", 108);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1348199118U), "fileTimeLo",
                  "fileTimeLo", 108);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 108);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 108);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 108);
  sf_mex_assign(&c8_rhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs108), "rhs", "rhs",
                  108);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs108), "lhs", "lhs",
                  108);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/getmsb.m"),
                  "context", "context", 109);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("fi_impl"), "name", "name", 109);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 109);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "resolved",
                  "resolved", 109);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1389302372U), "fileTimeLo",
                  "fileTimeLo", 109);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 109);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 109);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 109);
  sf_mex_assign(&c8_rhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs109), "rhs", "rhs",
                  109);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs109), "lhs", "lhs",
                  109);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 110);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 110);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 110);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 110);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 110);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 110);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 110);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 110);
  sf_mex_assign(&c8_rhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs110), "rhs", "rhs",
                  110);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs110), "lhs", "lhs",
                  110);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 111);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_fi_checkforconst"), "name",
                  "name", 111);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 111);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforconst.m"),
                  "resolved", "resolved", 111);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517552U), "fileTimeLo",
                  "fileTimeLo", 111);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 111);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 111);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 111);
  sf_mex_assign(&c8_rhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs111), "rhs", "rhs",
                  111);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs111), "lhs", "lhs",
                  111);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 112);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 112);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 112);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 112);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 112);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 112);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 112);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 112);
  sf_mex_assign(&c8_rhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs112), "rhs", "rhs",
                  112);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs112), "lhs", "lhs",
                  112);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 113);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_fi_checkforerror"), "name",
                  "name", 113);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 113);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m"),
                  "resolved", "resolved", 113);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1360285946U), "fileTimeLo",
                  "fileTimeLo", 113);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 113);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 113);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 113);
  sf_mex_assign(&c8_rhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs113), "rhs", "rhs",
                  113);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs113), "lhs", "lhs",
                  113);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "context", "context", 114);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("all"), "name", "name", 114);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 114);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/all.m"),
                  "resolved", "resolved", 114);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517552U), "fileTimeLo",
                  "fileTimeLo", 114);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 114);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 114);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 114);
  sf_mex_assign(&c8_rhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs114), "rhs", "rhs",
                  114);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs114), "lhs", "lhs",
                  114);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/all.m"),
                  "context", "context", 115);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_all_or_any"), "name",
                  "name", 115);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 115);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m"),
                  "resolved", "resolved", 115);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1372589616U), "fileTimeLo",
                  "fileTimeLo", 115);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 115);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 115);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 115);
  sf_mex_assign(&c8_rhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs115), "rhs", "rhs",
                  115);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs115), "lhs", "lhs",
                  115);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m"), "context",
                  "context", 116);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("coder.internal.allOrAny"),
                  "name", "name", 116);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 116);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "resolved", "resolved", 116);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1372590358U), "fileTimeLo",
                  "fileTimeLo", 116);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 116);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 116);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 116);
  sf_mex_assign(&c8_rhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs116), "rhs", "rhs",
                  116);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs116), "lhs", "lhs",
                  116);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 117);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isequal"), "name", "name", 117);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 117);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 117);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1286825958U), "fileTimeLo",
                  "fileTimeLo", 117);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 117);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 117);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 117);
  sf_mex_assign(&c8_rhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs117), "rhs", "rhs",
                  117);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs117), "lhs", "lhs",
                  117);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "context",
                  "context", 118);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_isequal_core"), "name",
                  "name", 118);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 118);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m"),
                  "resolved", "resolved", 118);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1286825986U), "fileTimeLo",
                  "fileTimeLo", 118);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 118);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 118);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 118);
  sf_mex_assign(&c8_rhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs118), "rhs", "rhs",
                  118);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs118), "lhs", "lhs",
                  118);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 119);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "coder.internal.constNonSingletonDim"), "name", "name", 119);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 119);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/constNonSingletonDim.m"),
                  "resolved", "resolved", 119);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1372590360U), "fileTimeLo",
                  "fileTimeLo", 119);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 119);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 119);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 119);
  sf_mex_assign(&c8_rhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs119), "rhs", "rhs",
                  119);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs119), "lhs", "lhs",
                  119);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 120);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("ne"), "name", "name", 120);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 120);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "resolved", "resolved", 120);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517584U), "fileTimeLo",
                  "fileTimeLo", 120);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 120);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 120);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 120);
  sf_mex_assign(&c8_rhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs120), "rhs", "rhs",
                  120);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs120), "lhs", "lhs",
                  120);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 121);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 121);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 121);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 121);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 121);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 121);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 121);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 121);
  sf_mex_assign(&c8_rhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs121), "rhs", "rhs",
                  121);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs121), "lhs", "lhs",
                  121);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 122);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 122);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 122);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 122);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 122);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 122);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 122);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 122);
  sf_mex_assign(&c8_rhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs122), "rhs", "rhs",
                  122);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs122), "lhs", "lhs",
                  122);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 123);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isscaledtype"), "name", "name",
                  123);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 123);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 123);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 123);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 123);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 123);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 123);
  sf_mex_assign(&c8_rhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs123), "rhs", "rhs",
                  123);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs123), "lhs", "lhs",
                  123);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 124);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 124);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 124);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 124);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 124);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 124);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 124);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 124);
  sf_mex_assign(&c8_rhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs124), "rhs", "rhs",
                  124);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs124), "lhs", "lhs",
                  124);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 125);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_type_relop_const"), "name",
                  "name", 125);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 125);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m"),
                  "resolved", "resolved", 125);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517574U), "fileTimeLo",
                  "fileTimeLo", 125);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 125);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 125);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 125);
  sf_mex_assign(&c8_rhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs125), "rhs", "rhs",
                  125);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs125), "lhs", "lhs",
                  125);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m"),
                  "context", "context", 126);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("all"), "name", "name", 126);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 126);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "resolved",
                  "resolved", 126);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1372589614U), "fileTimeLo",
                  "fileTimeLo", 126);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 126);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 126);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 126);
  sf_mex_assign(&c8_rhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs126), "rhs", "rhs",
                  126);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs126), "lhs", "lhs",
                  126);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 127);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_make_same_complexity"),
                  "name", "name", 127);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 127);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_make_same_complexity.m"),
                  "resolved", "resolved", 127);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 127);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 127);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 127);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 127);
  sf_mex_assign(&c8_rhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs127), "rhs", "rhs",
                  127);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs127), "lhs", "lhs",
                  127);
  sf_mex_destroy(&c8_rhs64);
  sf_mex_destroy(&c8_lhs64);
  sf_mex_destroy(&c8_rhs65);
  sf_mex_destroy(&c8_lhs65);
  sf_mex_destroy(&c8_rhs66);
  sf_mex_destroy(&c8_lhs66);
  sf_mex_destroy(&c8_rhs67);
  sf_mex_destroy(&c8_lhs67);
  sf_mex_destroy(&c8_rhs68);
  sf_mex_destroy(&c8_lhs68);
  sf_mex_destroy(&c8_rhs69);
  sf_mex_destroy(&c8_lhs69);
  sf_mex_destroy(&c8_rhs70);
  sf_mex_destroy(&c8_lhs70);
  sf_mex_destroy(&c8_rhs71);
  sf_mex_destroy(&c8_lhs71);
  sf_mex_destroy(&c8_rhs72);
  sf_mex_destroy(&c8_lhs72);
  sf_mex_destroy(&c8_rhs73);
  sf_mex_destroy(&c8_lhs73);
  sf_mex_destroy(&c8_rhs74);
  sf_mex_destroy(&c8_lhs74);
  sf_mex_destroy(&c8_rhs75);
  sf_mex_destroy(&c8_lhs75);
  sf_mex_destroy(&c8_rhs76);
  sf_mex_destroy(&c8_lhs76);
  sf_mex_destroy(&c8_rhs77);
  sf_mex_destroy(&c8_lhs77);
  sf_mex_destroy(&c8_rhs78);
  sf_mex_destroy(&c8_lhs78);
  sf_mex_destroy(&c8_rhs79);
  sf_mex_destroy(&c8_lhs79);
  sf_mex_destroy(&c8_rhs80);
  sf_mex_destroy(&c8_lhs80);
  sf_mex_destroy(&c8_rhs81);
  sf_mex_destroy(&c8_lhs81);
  sf_mex_destroy(&c8_rhs82);
  sf_mex_destroy(&c8_lhs82);
  sf_mex_destroy(&c8_rhs83);
  sf_mex_destroy(&c8_lhs83);
  sf_mex_destroy(&c8_rhs84);
  sf_mex_destroy(&c8_lhs84);
  sf_mex_destroy(&c8_rhs85);
  sf_mex_destroy(&c8_lhs85);
  sf_mex_destroy(&c8_rhs86);
  sf_mex_destroy(&c8_lhs86);
  sf_mex_destroy(&c8_rhs87);
  sf_mex_destroy(&c8_lhs87);
  sf_mex_destroy(&c8_rhs88);
  sf_mex_destroy(&c8_lhs88);
  sf_mex_destroy(&c8_rhs89);
  sf_mex_destroy(&c8_lhs89);
  sf_mex_destroy(&c8_rhs90);
  sf_mex_destroy(&c8_lhs90);
  sf_mex_destroy(&c8_rhs91);
  sf_mex_destroy(&c8_lhs91);
  sf_mex_destroy(&c8_rhs92);
  sf_mex_destroy(&c8_lhs92);
  sf_mex_destroy(&c8_rhs93);
  sf_mex_destroy(&c8_lhs93);
  sf_mex_destroy(&c8_rhs94);
  sf_mex_destroy(&c8_lhs94);
  sf_mex_destroy(&c8_rhs95);
  sf_mex_destroy(&c8_lhs95);
  sf_mex_destroy(&c8_rhs96);
  sf_mex_destroy(&c8_lhs96);
  sf_mex_destroy(&c8_rhs97);
  sf_mex_destroy(&c8_lhs97);
  sf_mex_destroy(&c8_rhs98);
  sf_mex_destroy(&c8_lhs98);
  sf_mex_destroy(&c8_rhs99);
  sf_mex_destroy(&c8_lhs99);
  sf_mex_destroy(&c8_rhs100);
  sf_mex_destroy(&c8_lhs100);
  sf_mex_destroy(&c8_rhs101);
  sf_mex_destroy(&c8_lhs101);
  sf_mex_destroy(&c8_rhs102);
  sf_mex_destroy(&c8_lhs102);
  sf_mex_destroy(&c8_rhs103);
  sf_mex_destroy(&c8_lhs103);
  sf_mex_destroy(&c8_rhs104);
  sf_mex_destroy(&c8_lhs104);
  sf_mex_destroy(&c8_rhs105);
  sf_mex_destroy(&c8_lhs105);
  sf_mex_destroy(&c8_rhs106);
  sf_mex_destroy(&c8_lhs106);
  sf_mex_destroy(&c8_rhs107);
  sf_mex_destroy(&c8_lhs107);
  sf_mex_destroy(&c8_rhs108);
  sf_mex_destroy(&c8_lhs108);
  sf_mex_destroy(&c8_rhs109);
  sf_mex_destroy(&c8_lhs109);
  sf_mex_destroy(&c8_rhs110);
  sf_mex_destroy(&c8_lhs110);
  sf_mex_destroy(&c8_rhs111);
  sf_mex_destroy(&c8_lhs111);
  sf_mex_destroy(&c8_rhs112);
  sf_mex_destroy(&c8_lhs112);
  sf_mex_destroy(&c8_rhs113);
  sf_mex_destroy(&c8_lhs113);
  sf_mex_destroy(&c8_rhs114);
  sf_mex_destroy(&c8_lhs114);
  sf_mex_destroy(&c8_rhs115);
  sf_mex_destroy(&c8_lhs115);
  sf_mex_destroy(&c8_rhs116);
  sf_mex_destroy(&c8_lhs116);
  sf_mex_destroy(&c8_rhs117);
  sf_mex_destroy(&c8_lhs117);
  sf_mex_destroy(&c8_rhs118);
  sf_mex_destroy(&c8_lhs118);
  sf_mex_destroy(&c8_rhs119);
  sf_mex_destroy(&c8_lhs119);
  sf_mex_destroy(&c8_rhs120);
  sf_mex_destroy(&c8_lhs120);
  sf_mex_destroy(&c8_rhs121);
  sf_mex_destroy(&c8_lhs121);
  sf_mex_destroy(&c8_rhs122);
  sf_mex_destroy(&c8_lhs122);
  sf_mex_destroy(&c8_rhs123);
  sf_mex_destroy(&c8_lhs123);
  sf_mex_destroy(&c8_rhs124);
  sf_mex_destroy(&c8_lhs124);
  sf_mex_destroy(&c8_rhs125);
  sf_mex_destroy(&c8_lhs125);
  sf_mex_destroy(&c8_rhs126);
  sf_mex_destroy(&c8_lhs126);
  sf_mex_destroy(&c8_rhs127);
  sf_mex_destroy(&c8_lhs127);
}

static void c8_c_info_helper(const mxArray **c8_info)
{
  const mxArray *c8_rhs128 = NULL;
  const mxArray *c8_lhs128 = NULL;
  const mxArray *c8_rhs129 = NULL;
  const mxArray *c8_lhs129 = NULL;
  const mxArray *c8_rhs130 = NULL;
  const mxArray *c8_lhs130 = NULL;
  const mxArray *c8_rhs131 = NULL;
  const mxArray *c8_lhs131 = NULL;
  const mxArray *c8_rhs132 = NULL;
  const mxArray *c8_lhs132 = NULL;
  const mxArray *c8_rhs133 = NULL;
  const mxArray *c8_lhs133 = NULL;
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 128);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 128);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("uint8"), "dominantType",
                  "dominantType", 128);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 128);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 128);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 128);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 128);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 128);
  sf_mex_assign(&c8_rhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs128), "rhs", "rhs",
                  128);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs128), "lhs", "lhs",
                  128);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 129);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_fi_checkforntype"), "name",
                  "name", 129);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 129);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m"),
                  "resolved", "resolved", 129);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1381857498U), "fileTimeLo",
                  "fileTimeLo", 129);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 129);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 129);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 129);
  sf_mex_assign(&c8_rhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs129), "rhs", "rhs",
                  129);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs129), "lhs", "lhs",
                  129);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(""), "context", "context", 130);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("bitconcat"), "name", "name",
                  130);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 130);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitconcat.m"),
                  "resolved", "resolved", 130);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1372589614U), "fileTimeLo",
                  "fileTimeLo", 130);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 130);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 130);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 130);
  sf_mex_assign(&c8_rhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs130), "rhs", "rhs",
                  130);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs130), "lhs", "lhs",
                  130);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/@embedded/@fi/bitconcat.m!bitconcat_checkarg"),
                  "context", "context", 131);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfi"), "name", "name", 131);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 131);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 131);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 131);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 131);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 131);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 131);
  sf_mex_assign(&c8_rhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs131), "rhs", "rhs",
                  131);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs131), "lhs", "lhs",
                  131);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/@embedded/@fi/bitconcat.m!bitconcat_checkarg"),
                  "context", "context", 132);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("isfixed"), "name", "name", 132);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 132);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 132);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 132);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 132);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 132);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 132);
  sf_mex_assign(&c8_rhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs132), "rhs", "rhs",
                  132);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs132), "lhs", "lhs",
                  132);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/@embedded/@fi/bitconcat.m!bitconcat_checkarg"),
                  "context", "context", 133);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("eml_isslopebiasscaled"),
                  "name", "name", 133);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 133);
  sf_mex_addfield(*c8_info, c8_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "resolved", "resolved", 133);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 133);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 133);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 133);
  sf_mex_addfield(*c8_info, c8_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 133);
  sf_mex_assign(&c8_rhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c8_lhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_rhs133), "rhs", "rhs",
                  133);
  sf_mex_addfield(*c8_info, sf_mex_duplicatearraysafe(&c8_lhs133), "lhs", "lhs",
                  133);
  sf_mex_destroy(&c8_rhs128);
  sf_mex_destroy(&c8_lhs128);
  sf_mex_destroy(&c8_rhs129);
  sf_mex_destroy(&c8_lhs129);
  sf_mex_destroy(&c8_rhs130);
  sf_mex_destroy(&c8_lhs130);
  sf_mex_destroy(&c8_rhs131);
  sf_mex_destroy(&c8_lhs131);
  sf_mex_destroy(&c8_rhs132);
  sf_mex_destroy(&c8_lhs132);
  sf_mex_destroy(&c8_rhs133);
  sf_mex_destroy(&c8_lhs133);
}

static uint8_T c8_uint8(SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c8_A)
{
  uint8_T c8_xfi;
  const mxArray *c8_propValScalar = NULL;
  const mxArray *c8_pseudoData = NULL;
  const mxArray *c8_codeGenSupportFlag = NULL;
  (void)chartInstance;
  c8_xfi = c8_A;
  sf_mex_destroy(&c8_propValScalar);
  sf_mex_destroy(&c8_pseudoData);
  sf_mex_destroy(&c8_codeGenSupportFlag);
  return c8_xfi;
}

static int8_T c8_bitsra(SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c8_ain)
{
  int8_T c8_b_ain;
  int8_T c8_a;
  int8_T c8_b_a;
  int8_T c8_varargin_1;
  int8_T c8_c;
  (void)chartInstance;
  c8_b_ain = c8_ain;
  c8_a = c8_b_ain;
  c8_b_a = c8_a;
  c8_varargin_1 = c8_b_a;
  c8_c = (int8_T)(c8_varargin_1 >> 1);
  return c8_c;
}

static int8_T c8_bitsll(SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c8_ain)
{
  int8_T c8_b_ain;
  int8_T c8_a;
  int8_T c8_b_a;
  int8_T c8_varargin_1;
  int8_T c8_c;
  (void)chartInstance;
  c8_b_ain = c8_ain;
  c8_a = c8_b_ain;
  c8_b_a = c8_a;
  c8_varargin_1 = c8_b_a;
  c8_c = (int8_T)(c8_varargin_1 << 1);
  return c8_c;
}

static uint8_T c8_bitxor(SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c8_a, uint8_T c8_b)
{
  uint8_T c8_c_uint;
  (void)chartInstance;
  c8_c_uint = (uint8_T)((uint8_T)(c8_a ^ c8_b) & 1U);
  return c8_c_uint;
}

static boolean_T c8_all(SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c8_x)
{
  int8_T c8_b_x;
  int8_T c8_c_x;
  int8_T c8_a0;
  int8_T c8_a;
  int8_T c8_b_a0;
  int8_T c8_a1;
  int8_T c8_b_a1;
  (void)chartInstance;
  c8_b_x = c8_x;
  c8_c_x = c8_b_x;
  c8_a0 = c8_c_x;
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_u = *(int32_T *)c8_inData;
  c8_y = NULL;
  sf_mex_assign(&c8_y, sf_mex_create("y", &c8_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  return c8_mxArrayOutData;
}

static int32_T c8_h_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int32_T c8_y;
  int32_T c8_i1;
  (void)chartInstance;
  sf_mex_import(c8_parentId, sf_mex_dup(c8_u), &c8_i1, 1, 6, 0U, 0, 0U, 0);
  c8_y = c8_i1;
  sf_mex_destroy(&c8_u);
  return c8_y;
}

static void c8_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c8_mxArrayInData, const char_T *c8_varName, void *c8_outData)
{
  const mxArray *c8_b_sfEvent;
  const char_T *c8_identifier;
  emlrtMsgIdentifier c8_thisId;
  int32_T c8_y;
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_b_sfEvent = sf_mex_dup(c8_mxArrayInData);
  c8_identifier = c8_varName;
  c8_thisId.fIdentifier = c8_identifier;
  c8_thisId.fParent = NULL;
  c8_y = c8_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c8_b_sfEvent),
    &c8_thisId);
  sf_mex_destroy(&c8_b_sfEvent);
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(uint8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c8_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_c_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c8_mxArrayOutData;
}

static uint8_T c8_i_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c8_j_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  uint8_T c8_y;
  const mxArray *c8_mxFi = NULL;
  const mxArray *c8_mxInt = NULL;
  uint8_T c8_u4;
  (void)chartInstance;
  sf_mex_check_fi(c8_parentId, c8_u, false, 0U, NULL, c8_eml_mx, c8_c_eml_mx);
  sf_mex_assign(&c8_mxFi, sf_mex_dup(c8_u), false);
  sf_mex_assign(&c8_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c8_mxFi)), false);
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(uint8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c8_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_d_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c8_mxArrayOutData = NULL;
  c8_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c8_u = *(int8_T *)c8_inData;
    c8_y = NULL;
    c8_b_u = c8_u;
    c8_b_y = NULL;
    sf_mex_assign(&c8_b_y, sf_mex_create("y", &c8_b_u, 2, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c8_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c8_eml_mx), 15, "numerictype", 14, sf_mex_dup(c8_b_eml_mx), 15,
      "simulinkarray", 14, c8_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c8_mxArrayOutData, c8_y, false);
  } else {
    sf_mex_assign(&c8_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c8_mxArrayOutData;
}

static int8_T c8_k_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
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

static int8_T c8_l_emlrt_marshallIn(SFc8_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c8_u, const emlrtMsgIdentifier *c8_parentId)
{
  int8_T c8_y;
  const mxArray *c8_mxFi = NULL;
  const mxArray *c8_mxInt = NULL;
  int8_T c8_i2;
  (void)chartInstance;
  sf_mex_check_fi(c8_parentId, c8_u, false, 0U, NULL, c8_eml_mx, c8_b_eml_mx);
  sf_mex_assign(&c8_mxFi, sf_mex_dup(c8_u), false);
  sf_mex_assign(&c8_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c8_mxFi)), false);
  sf_mex_import(c8_parentId, sf_mex_dup(c8_mxInt), &c8_i2, 1, 2, 0U, 0, 0U, 0);
  sf_mex_destroy(&c8_mxFi);
  sf_mex_destroy(&c8_mxInt);
  c8_y = c8_i2;
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
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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

static void init_dsm_address_info(SFc8_gm_hdlcodercpu_emlInstanceStruct
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

void sf_c8_gm_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4220501680U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(817716410U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3404575281U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1952750228U);
}

mxArray *sf_c8_gm_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("z6cRnj2tzVGVOD0tqpTIkF");
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

mxArray *sf_c8_gm_hdlcodercpu_eml_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c8_gm_hdlcodercpu_eml_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c8_gm_hdlcodercpu_eml(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[4],T\"out_flags\",},{M[1],M[6],T\"shift_out\",},{M[8],M[0],T\"is_active_c8_gm_hdlcodercpu_eml\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c8_gm_hdlcodercpu_eml_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _gm_hdlcodercpu_emlMachineNumber_,
           8,
           1,
           1,
           0,
           5,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_gm_hdlcodercpu_emlMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_gm_hdlcodercpu_emlMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _gm_hdlcodercpu_emlMachineNumber_,
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
        _SFD_CV_INIT_EML(0,1,1,0,0,0,1,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1210);

        {
          static int caseStart[] = { 853, 536, 781 };

          static int caseExprEnd[] = { 862, 542, 787 };

          _SFD_CV_INIT_EML_SWITCH(0,1,0,510,531,940,3,&(caseStart[0]),
            &(caseExprEnd[0]));
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
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _gm_hdlcodercpu_emlMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "UpX7fahExLArbUaLDEhkiD";
}

static void sf_opaque_initialize_c8_gm_hdlcodercpu_eml(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc8_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c8_gm_hdlcodercpu_eml((SFc8_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
  initialize_c8_gm_hdlcodercpu_eml((SFc8_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c8_gm_hdlcodercpu_eml(void *chartInstanceVar)
{
  enable_c8_gm_hdlcodercpu_eml((SFc8_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c8_gm_hdlcodercpu_eml(void *chartInstanceVar)
{
  disable_c8_gm_hdlcodercpu_eml((SFc8_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c8_gm_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_gateway_c8_gm_hdlcodercpu_eml((SFc8_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c8_gm_hdlcodercpu_eml(SimStruct*
  S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c8_gm_hdlcodercpu_eml
    ((SFc8_gm_hdlcodercpu_emlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c8_gm_hdlcodercpu_eml();/* state var info */
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

extern void sf_internal_set_sim_state_c8_gm_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c8_gm_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c8_gm_hdlcodercpu_eml((SFc8_gm_hdlcodercpu_emlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c8_gm_hdlcodercpu_eml(SimStruct* S)
{
  return sf_internal_get_sim_state_c8_gm_hdlcodercpu_eml(S);
}

static void sf_opaque_set_sim_state_c8_gm_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c8_gm_hdlcodercpu_eml(S, st);
}

static void sf_opaque_terminate_c8_gm_hdlcodercpu_eml(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc8_gm_hdlcodercpu_emlInstanceStruct*) chartInstanceVar)
      ->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_gm_hdlcodercpu_eml_optimization_info();
    }

    finalize_c8_gm_hdlcodercpu_eml((SFc8_gm_hdlcodercpu_emlInstanceStruct*)
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
  initSimStructsc8_gm_hdlcodercpu_eml((SFc8_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c8_gm_hdlcodercpu_eml(SimStruct *S)
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
    initialize_params_c8_gm_hdlcodercpu_eml
      ((SFc8_gm_hdlcodercpu_emlInstanceStruct*)(chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c8_gm_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_gm_hdlcodercpu_eml_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,8);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,8,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,8,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,8);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,8,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,8,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,8);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3024035404U));
  ssSetChecksum1(S,(4209343377U));
  ssSetChecksum2(S,(1707914531U));
  ssSetChecksum3(S,(2548347521U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c8_gm_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c8_gm_hdlcodercpu_eml(SimStruct *S)
{
  SFc8_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc8_gm_hdlcodercpu_emlInstanceStruct *)utMalloc(sizeof
    (SFc8_gm_hdlcodercpu_emlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc8_gm_hdlcodercpu_emlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c8_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c8_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c8_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c8_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c8_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c8_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c8_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c8_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c8_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlStart = mdlStart_c8_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c8_gm_hdlcodercpu_eml;
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

void c8_gm_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c8_gm_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c8_gm_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c8_gm_hdlcodercpu_eml(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c8_gm_hdlcodercpu_eml_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
