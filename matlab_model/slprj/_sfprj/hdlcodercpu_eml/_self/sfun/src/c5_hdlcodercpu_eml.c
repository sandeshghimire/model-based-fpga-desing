/* Include files */

#include <stddef.h>
#include "blas.h"
#include "hdlcodercpu_eml_sfun.h"
#include "c5_hdlcodercpu_eml.h"
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
static const mxArray *c5_eml_mx;
static const char * c5_debug_family_names[7] = { "hdl_fm", "nargin", "nargout",
  "addr", "read", "instr_out", "data" };

static const mxArray *c5_b_eml_mx;
static const mxArray *c5_c_eml_mx;

/* Function Declarations */
static void initialize_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initialize_params_c5_hdlcodercpu_eml
  (SFc5_hdlcodercpu_emlInstanceStruct *chartInstance);
static void enable_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void disable_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c5_update_debugger_state_c5_hdlcodercpu_eml
  (SFc5_hdlcodercpu_emlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c5_hdlcodercpu_eml
  (SFc5_hdlcodercpu_emlInstanceStruct *chartInstance);
static void set_sim_state_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c5_st);
static void finalize_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void sf_gateway_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c5_chartstep_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initSimStructsc5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static void c5_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_b_data, const char_T *c5_identifier,
  uint16_T c5_y[256]);
static void c5_b_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  uint16_T c5_y[256]);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static uint16_T c5_c_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_instr_out, const char_T *c5_identifier);
static uint16_T c5_d_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static real_T c5_e_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_info_helper(const mxArray **c5_info);
static const mxArray *c5_emlrt_marshallOut(const char * c5_u);
static const mxArray *c5_b_emlrt_marshallOut(const uint32_T c5_u);
static void c5_eml_fi_checkforconst(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c5_isfi(SFc5_hdlcodercpu_emlInstanceStruct *chartInstance);
static void c5_eml_fi_checkforerror(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static boolean_T c5_eq(SFc5_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c5_a0);
static const mxArray *c5_g_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static int32_T c5_f_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_h_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static uint8_T c5_g_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_hdlcodercpu_eml, const char_T
  *c5_identifier);
static uint8_T c5_h_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void init_dsm_address_info(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c5_data_not_empty = false;
  chartInstance->c5_is_active_c5_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c5_c_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 1.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c5_b_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 12.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c5_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
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

static void initialize_params_c5_hdlcodercpu_eml
  (SFc5_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c5_update_debugger_state_c5_hdlcodercpu_eml
  (SFc5_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c5_hdlcodercpu_eml
  (SFc5_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  uint16_T c5_hoistedGlobal;
  uint16_T c5_u;
  const mxArray *c5_b_y = NULL;
  uint16_T c5_b_u;
  const mxArray *c5_c_y = NULL;
  const mxArray *c5_d_y = NULL;
  int32_T c5_i0;
  uint16_T c5_c_u[256];
  const mxArray *c5_e_y = NULL;
  uint8_T c5_b_hoistedGlobal;
  uint8_T c5_d_u;
  const mxArray *c5_f_y = NULL;
  uint16_T *c5_instr_out;
  c5_instr_out = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(3, 1), false);
  c5_hoistedGlobal = *c5_instr_out;
  c5_u = c5_hoistedGlobal;
  c5_b_y = NULL;
  c5_b_u = c5_u;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_b_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c5_eml_mx), 15, "numerictype", 14, sf_mex_dup(c5_b_eml_mx), 15,
    "simulinkarray", 14, c5_c_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_d_y = NULL;
  if (!chartInstance->c5_data_not_empty) {
    sf_mex_assign(&c5_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    for (c5_i0 = 0; c5_i0 < 256; c5_i0++) {
      c5_c_u[c5_i0] = chartInstance->c5_data[c5_i0];
    }

    c5_e_y = NULL;
    sf_mex_assign(&c5_e_y, sf_mex_create("y", c5_c_u, 5, 0U, 1U, 0U, 2, 1, 256),
                  false);
    sf_mex_assign(&c5_d_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c5_eml_mx), 15, "numerictype", 14, sf_mex_dup(c5_b_eml_mx), 15,
      "simulinkarray", 14, c5_e_y, 15, "fimathislocal", 3, true), false);
  }

  sf_mex_setcell(c5_y, 1, c5_d_y);
  c5_b_hoistedGlobal = chartInstance->c5_is_active_c5_hdlcodercpu_eml;
  c5_d_u = c5_b_hoistedGlobal;
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 2, c5_f_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c5_st)
{
  const mxArray *c5_u;
  uint16_T c5_uv0[256];
  int32_T c5_i1;
  uint16_T *c5_instr_out;
  c5_instr_out = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c5_doneDoubleBufferReInit = true;
  c5_u = sf_mex_dup(c5_st);
  *c5_instr_out = c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c5_u, 0)), "instr_out");
  c5_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 1)), "data",
                      c5_uv0);
  for (c5_i1 = 0; c5_i1 < 256; c5_i1++) {
    chartInstance->c5_data[c5_i1] = c5_uv0[c5_i1];
  }

  chartInstance->c5_is_active_c5_hdlcodercpu_eml = c5_g_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 2)),
     "is_active_c5_hdlcodercpu_eml");
  sf_mex_destroy(&c5_u);
  c5_update_debugger_state_c5_hdlcodercpu_eml(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void finalize_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
  sf_mex_destroy(&c5_eml_mx);
  sf_mex_destroy(&c5_b_eml_mx);
  sf_mex_destroy(&c5_c_eml_mx);
}

static void sf_gateway_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  uint8_T *c5_addr;
  uint8_T *c5_read;
  uint16_T *c5_instr_out;
  c5_instr_out = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c5_read = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c5_addr = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c5_addr, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c5_read, 1U);
  chartInstance->c5_sfEvent = CALL_EVENT;
  c5_chartstep_c5_hdlcodercpu_eml(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK((real_T)*c5_instr_out, 2U);
}

static void c5_chartstep_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  uint8_T c5_hoistedGlobal;
  uint8_T c5_b_hoistedGlobal;
  uint8_T c5_addr;
  uint8_T c5_read;
  uint32_T c5_debug_family_var_map[7];
  const mxArray *c5_hdl_fm = NULL;
  real_T c5_nargin = 2.0;
  real_T c5_nargout = 1.0;
  uint16_T c5_instr_out;
  const mxArray *c5_T = NULL;
  const mxArray *c5_F = NULL;
  const mxArray *c5_val = NULL;
  const mxArray *c5_unusedU2 = NULL;
  const mxArray *c5_unusedU3 = NULL;
  const mxArray *c5_isfimathlocal = NULL;
  int32_T c5_i2;
  const mxArray *c5_b_T = NULL;
  const mxArray *c5_b_F = NULL;
  const mxArray *c5_b_val = NULL;
  const mxArray *c5_b_unusedU2 = NULL;
  const mxArray *c5_b_unusedU3 = NULL;
  const mxArray *c5_b_isfimathlocal = NULL;
  const mxArray *c5_c_T = NULL;
  const mxArray *c5_c_F = NULL;
  const mxArray *c5_c_val = NULL;
  const mxArray *c5_c_unusedU2 = NULL;
  const mxArray *c5_c_unusedU3 = NULL;
  const mxArray *c5_c_isfimathlocal = NULL;
  const mxArray *c5_d_T = NULL;
  const mxArray *c5_d_F = NULL;
  const mxArray *c5_d_val = NULL;
  const mxArray *c5_d_unusedU2 = NULL;
  const mxArray *c5_d_unusedU3 = NULL;
  const mxArray *c5_d_isfimathlocal = NULL;
  const mxArray *c5_e_T = NULL;
  const mxArray *c5_e_F = NULL;
  const mxArray *c5_e_val = NULL;
  const mxArray *c5_e_unusedU2 = NULL;
  const mxArray *c5_e_unusedU3 = NULL;
  const mxArray *c5_e_isfimathlocal = NULL;
  const mxArray *c5_f_T = NULL;
  const mxArray *c5_f_F = NULL;
  const mxArray *c5_f_val = NULL;
  const mxArray *c5_f_unusedU2 = NULL;
  const mxArray *c5_f_unusedU3 = NULL;
  const mxArray *c5_f_isfimathlocal = NULL;
  const mxArray *c5_g_T = NULL;
  const mxArray *c5_g_F = NULL;
  const mxArray *c5_g_val = NULL;
  const mxArray *c5_g_unusedU2 = NULL;
  const mxArray *c5_g_unusedU3 = NULL;
  const mxArray *c5_g_isfimathlocal = NULL;
  const mxArray *c5_h_T = NULL;
  const mxArray *c5_h_F = NULL;
  const mxArray *c5_h_val = NULL;
  const mxArray *c5_h_unusedU2 = NULL;
  const mxArray *c5_h_unusedU3 = NULL;
  const mxArray *c5_h_isfimathlocal = NULL;
  const mxArray *c5_i_T = NULL;
  const mxArray *c5_i_F = NULL;
  const mxArray *c5_i_val = NULL;
  const mxArray *c5_i_unusedU2 = NULL;
  const mxArray *c5_i_unusedU3 = NULL;
  const mxArray *c5_i_isfimathlocal = NULL;
  const mxArray *c5_j_T = NULL;
  const mxArray *c5_j_F = NULL;
  const mxArray *c5_j_val = NULL;
  const mxArray *c5_j_unusedU2 = NULL;
  const mxArray *c5_j_unusedU3 = NULL;
  const mxArray *c5_j_isfimathlocal = NULL;
  const mxArray *c5_k_T = NULL;
  const mxArray *c5_k_F = NULL;
  const mxArray *c5_k_val = NULL;
  const mxArray *c5_k_unusedU2 = NULL;
  const mxArray *c5_k_unusedU3 = NULL;
  const mxArray *c5_k_isfimathlocal = NULL;
  const mxArray *c5_l_T = NULL;
  const mxArray *c5_l_F = NULL;
  const mxArray *c5_l_val = NULL;
  const mxArray *c5_l_unusedU2 = NULL;
  const mxArray *c5_l_unusedU3 = NULL;
  const mxArray *c5_l_isfimathlocal = NULL;
  const mxArray *c5_m_T = NULL;
  const mxArray *c5_m_F = NULL;
  const mxArray *c5_m_val = NULL;
  const mxArray *c5_m_unusedU2 = NULL;
  const mxArray *c5_m_unusedU3 = NULL;
  const mxArray *c5_m_isfimathlocal = NULL;
  const mxArray *c5_n_T = NULL;
  const mxArray *c5_n_F = NULL;
  const mxArray *c5_n_val = NULL;
  const mxArray *c5_n_unusedU2 = NULL;
  const mxArray *c5_n_unusedU3 = NULL;
  const mxArray *c5_n_isfimathlocal = NULL;
  const mxArray *c5_o_T = NULL;
  const mxArray *c5_o_F = NULL;
  const mxArray *c5_o_val = NULL;
  const mxArray *c5_o_unusedU2 = NULL;
  const mxArray *c5_o_unusedU3 = NULL;
  const mxArray *c5_o_isfimathlocal = NULL;
  const mxArray *c5_p_T = NULL;
  const mxArray *c5_p_F = NULL;
  const mxArray *c5_p_val = NULL;
  const mxArray *c5_p_unusedU2 = NULL;
  const mxArray *c5_p_unusedU3 = NULL;
  const mxArray *c5_p_isfimathlocal = NULL;
  const mxArray *c5_q_T = NULL;
  const mxArray *c5_q_F = NULL;
  const mxArray *c5_q_val = NULL;
  const mxArray *c5_q_unusedU2 = NULL;
  const mxArray *c5_q_unusedU3 = NULL;
  const mxArray *c5_q_isfimathlocal = NULL;
  const mxArray *c5_r_T = NULL;
  const mxArray *c5_r_F = NULL;
  const mxArray *c5_r_val = NULL;
  const mxArray *c5_r_unusedU2 = NULL;
  const mxArray *c5_r_unusedU3 = NULL;
  const mxArray *c5_r_isfimathlocal = NULL;
  const mxArray *c5_s_T = NULL;
  const mxArray *c5_s_F = NULL;
  const mxArray *c5_s_val = NULL;
  const mxArray *c5_s_unusedU2 = NULL;
  const mxArray *c5_s_unusedU3 = NULL;
  const mxArray *c5_s_isfimathlocal = NULL;
  const mxArray *c5_t_T = NULL;
  const mxArray *c5_t_F = NULL;
  const mxArray *c5_t_val = NULL;
  const mxArray *c5_t_unusedU2 = NULL;
  const mxArray *c5_t_unusedU3 = NULL;
  const mxArray *c5_t_isfimathlocal = NULL;
  const mxArray *c5_u_T = NULL;
  const mxArray *c5_u_F = NULL;
  const mxArray *c5_u_val = NULL;
  const mxArray *c5_u_unusedU2 = NULL;
  const mxArray *c5_u_unusedU3 = NULL;
  const mxArray *c5_u_isfimathlocal = NULL;
  const mxArray *c5_v_T = NULL;
  const mxArray *c5_v_F = NULL;
  const mxArray *c5_v_val = NULL;
  const mxArray *c5_v_unusedU2 = NULL;
  const mxArray *c5_v_unusedU3 = NULL;
  const mxArray *c5_v_isfimathlocal = NULL;
  const mxArray *c5_w_T = NULL;
  const mxArray *c5_w_F = NULL;
  const mxArray *c5_w_val = NULL;
  const mxArray *c5_w_unusedU2 = NULL;
  const mxArray *c5_w_unusedU3 = NULL;
  const mxArray *c5_w_isfimathlocal = NULL;
  const mxArray *c5_x_T = NULL;
  const mxArray *c5_x_F = NULL;
  const mxArray *c5_x_val = NULL;
  const mxArray *c5_x_unusedU2 = NULL;
  const mxArray *c5_x_unusedU3 = NULL;
  const mxArray *c5_x_isfimathlocal = NULL;
  const mxArray *c5_y_T = NULL;
  const mxArray *c5_y_F = NULL;
  const mxArray *c5_y_val = NULL;
  const mxArray *c5_y_unusedU2 = NULL;
  const mxArray *c5_y_unusedU3 = NULL;
  const mxArray *c5_y_isfimathlocal = NULL;
  const mxArray *c5_ab_T = NULL;
  const mxArray *c5_ab_F = NULL;
  const mxArray *c5_ab_val = NULL;
  const mxArray *c5_ab_unusedU2 = NULL;
  const mxArray *c5_ab_unusedU3 = NULL;
  const mxArray *c5_ab_isfimathlocal = NULL;
  const mxArray *c5_bb_T = NULL;
  const mxArray *c5_bb_F = NULL;
  const mxArray *c5_bb_val = NULL;
  const mxArray *c5_bb_unusedU2 = NULL;
  const mxArray *c5_bb_unusedU3 = NULL;
  const mxArray *c5_bb_isfimathlocal = NULL;
  const mxArray *c5_cb_T = NULL;
  const mxArray *c5_cb_F = NULL;
  const mxArray *c5_cb_val = NULL;
  const mxArray *c5_cb_unusedU2 = NULL;
  const mxArray *c5_cb_unusedU3 = NULL;
  const mxArray *c5_cb_isfimathlocal = NULL;
  const mxArray *c5_db_T = NULL;
  const mxArray *c5_db_F = NULL;
  const mxArray *c5_db_val = NULL;
  const mxArray *c5_db_unusedU2 = NULL;
  const mxArray *c5_db_unusedU3 = NULL;
  const mxArray *c5_db_isfimathlocal = NULL;
  const mxArray *c5_eb_T = NULL;
  const mxArray *c5_eb_F = NULL;
  const mxArray *c5_eb_val = NULL;
  const mxArray *c5_eb_unusedU2 = NULL;
  const mxArray *c5_eb_unusedU3 = NULL;
  const mxArray *c5_eb_isfimathlocal = NULL;
  const mxArray *c5_fb_T = NULL;
  const mxArray *c5_fb_F = NULL;
  const mxArray *c5_fb_val = NULL;
  const mxArray *c5_fb_unusedU2 = NULL;
  const mxArray *c5_fb_unusedU3 = NULL;
  const mxArray *c5_fb_isfimathlocal = NULL;
  const mxArray *c5_gb_T = NULL;
  const mxArray *c5_gb_F = NULL;
  const mxArray *c5_gb_val = NULL;
  const mxArray *c5_gb_unusedU2 = NULL;
  const mxArray *c5_gb_unusedU3 = NULL;
  const mxArray *c5_gb_isfimathlocal = NULL;
  const mxArray *c5_hb_T = NULL;
  const mxArray *c5_hb_F = NULL;
  const mxArray *c5_hb_val = NULL;
  const mxArray *c5_hb_unusedU2 = NULL;
  const mxArray *c5_hb_unusedU3 = NULL;
  const mxArray *c5_hb_isfimathlocal = NULL;
  const mxArray *c5_ib_T = NULL;
  const mxArray *c5_ib_F = NULL;
  const mxArray *c5_ib_val = NULL;
  const mxArray *c5_ib_unusedU2 = NULL;
  const mxArray *c5_ib_unusedU3 = NULL;
  const mxArray *c5_ib_isfimathlocal = NULL;
  const mxArray *c5_jb_T = NULL;
  const mxArray *c5_jb_F = NULL;
  const mxArray *c5_jb_val = NULL;
  const mxArray *c5_jb_unusedU2 = NULL;
  const mxArray *c5_jb_unusedU3 = NULL;
  const mxArray *c5_jb_isfimathlocal = NULL;
  const mxArray *c5_kb_T = NULL;
  const mxArray *c5_kb_F = NULL;
  const mxArray *c5_kb_val = NULL;
  const mxArray *c5_kb_unusedU2 = NULL;
  const mxArray *c5_kb_unusedU3 = NULL;
  const mxArray *c5_kb_isfimathlocal = NULL;
  const mxArray *c5_lb_T = NULL;
  const mxArray *c5_lb_F = NULL;
  const mxArray *c5_lb_val = NULL;
  const mxArray *c5_lb_unusedU2 = NULL;
  const mxArray *c5_lb_unusedU3 = NULL;
  const mxArray *c5_lb_isfimathlocal = NULL;
  const mxArray *c5_mb_T = NULL;
  const mxArray *c5_mb_F = NULL;
  const mxArray *c5_mb_val = NULL;
  const mxArray *c5_mb_unusedU2 = NULL;
  const mxArray *c5_mb_unusedU3 = NULL;
  const mxArray *c5_mb_isfimathlocal = NULL;
  const mxArray *c5_nb_T = NULL;
  const mxArray *c5_nb_F = NULL;
  const mxArray *c5_nb_val = NULL;
  const mxArray *c5_nb_unusedU2 = NULL;
  const mxArray *c5_nb_unusedU3 = NULL;
  const mxArray *c5_nb_isfimathlocal = NULL;
  const mxArray *c5_ob_T = NULL;
  const mxArray *c5_ob_F = NULL;
  const mxArray *c5_ob_val = NULL;
  const mxArray *c5_ob_unusedU2 = NULL;
  const mxArray *c5_ob_unusedU3 = NULL;
  const mxArray *c5_ob_isfimathlocal = NULL;
  const mxArray *c5_pb_T = NULL;
  const mxArray *c5_pb_F = NULL;
  const mxArray *c5_pb_val = NULL;
  const mxArray *c5_pb_unusedU2 = NULL;
  const mxArray *c5_pb_unusedU3 = NULL;
  const mxArray *c5_pb_isfimathlocal = NULL;
  const mxArray *c5_qb_T = NULL;
  const mxArray *c5_qb_F = NULL;
  const mxArray *c5_qb_val = NULL;
  const mxArray *c5_qb_unusedU2 = NULL;
  const mxArray *c5_qb_unusedU3 = NULL;
  const mxArray *c5_qb_isfimathlocal = NULL;
  const mxArray *c5_rb_T = NULL;
  const mxArray *c5_rb_F = NULL;
  const mxArray *c5_rb_val = NULL;
  const mxArray *c5_rb_unusedU2 = NULL;
  const mxArray *c5_rb_unusedU3 = NULL;
  const mxArray *c5_rb_isfimathlocal = NULL;
  const mxArray *c5_sb_T = NULL;
  const mxArray *c5_sb_F = NULL;
  const mxArray *c5_sb_val = NULL;
  const mxArray *c5_sb_unusedU2 = NULL;
  const mxArray *c5_sb_unusedU3 = NULL;
  const mxArray *c5_sb_isfimathlocal = NULL;
  const mxArray *c5_tb_T = NULL;
  const mxArray *c5_tb_F = NULL;
  const mxArray *c5_tb_val = NULL;
  const mxArray *c5_tb_unusedU2 = NULL;
  const mxArray *c5_tb_unusedU3 = NULL;
  const mxArray *c5_tb_isfimathlocal = NULL;
  const mxArray *c5_ub_T = NULL;
  const mxArray *c5_ub_F = NULL;
  const mxArray *c5_ub_val = NULL;
  const mxArray *c5_ub_unusedU2 = NULL;
  const mxArray *c5_ub_unusedU3 = NULL;
  const mxArray *c5_ub_isfimathlocal = NULL;
  const mxArray *c5_vb_T = NULL;
  const mxArray *c5_vb_F = NULL;
  const mxArray *c5_vb_val = NULL;
  const mxArray *c5_vb_unusedU2 = NULL;
  const mxArray *c5_vb_unusedU3 = NULL;
  const mxArray *c5_vb_isfimathlocal = NULL;
  const mxArray *c5_wb_T = NULL;
  const mxArray *c5_wb_F = NULL;
  const mxArray *c5_wb_val = NULL;
  const mxArray *c5_wb_unusedU2 = NULL;
  const mxArray *c5_wb_unusedU3 = NULL;
  const mxArray *c5_wb_isfimathlocal = NULL;
  const mxArray *c5_xb_T = NULL;
  const mxArray *c5_xb_F = NULL;
  const mxArray *c5_xb_val = NULL;
  const mxArray *c5_xb_unusedU2 = NULL;
  const mxArray *c5_xb_unusedU3 = NULL;
  const mxArray *c5_xb_isfimathlocal = NULL;
  const mxArray *c5_yb_T = NULL;
  const mxArray *c5_yb_F = NULL;
  const mxArray *c5_yb_val = NULL;
  const mxArray *c5_yb_unusedU2 = NULL;
  const mxArray *c5_yb_unusedU3 = NULL;
  const mxArray *c5_yb_isfimathlocal = NULL;
  const mxArray *c5_ac_T = NULL;
  const mxArray *c5_ac_F = NULL;
  const mxArray *c5_ac_val = NULL;
  const mxArray *c5_ac_unusedU2 = NULL;
  const mxArray *c5_ac_unusedU3 = NULL;
  const mxArray *c5_ac_isfimathlocal = NULL;
  const mxArray *c5_bc_T = NULL;
  const mxArray *c5_bc_F = NULL;
  const mxArray *c5_bc_val = NULL;
  const mxArray *c5_bc_unusedU2 = NULL;
  const mxArray *c5_bc_unusedU3 = NULL;
  const mxArray *c5_bc_isfimathlocal = NULL;
  const mxArray *c5_cc_T = NULL;
  const mxArray *c5_cc_F = NULL;
  const mxArray *c5_cc_val = NULL;
  const mxArray *c5_cc_unusedU2 = NULL;
  const mxArray *c5_cc_unusedU3 = NULL;
  const mxArray *c5_cc_isfimathlocal = NULL;
  const mxArray *c5_dc_T = NULL;
  const mxArray *c5_dc_F = NULL;
  const mxArray *c5_dc_val = NULL;
  const mxArray *c5_dc_unusedU2 = NULL;
  const mxArray *c5_dc_unusedU3 = NULL;
  const mxArray *c5_dc_isfimathlocal = NULL;
  const mxArray *c5_ec_T = NULL;
  const mxArray *c5_ec_F = NULL;
  const mxArray *c5_ec_val = NULL;
  const mxArray *c5_ec_unusedU2 = NULL;
  const mxArray *c5_ec_unusedU3 = NULL;
  const mxArray *c5_ec_isfimathlocal = NULL;
  const mxArray *c5_fc_T = NULL;
  const mxArray *c5_fc_F = NULL;
  const mxArray *c5_fc_val = NULL;
  const mxArray *c5_fc_unusedU2 = NULL;
  const mxArray *c5_fc_unusedU3 = NULL;
  const mxArray *c5_fc_isfimathlocal = NULL;
  const mxArray *c5_gc_T = NULL;
  const mxArray *c5_gc_F = NULL;
  const mxArray *c5_gc_val = NULL;
  const mxArray *c5_gc_unusedU2 = NULL;
  const mxArray *c5_gc_unusedU3 = NULL;
  const mxArray *c5_gc_isfimathlocal = NULL;
  const mxArray *c5_hc_T = NULL;
  const mxArray *c5_hc_F = NULL;
  const mxArray *c5_hc_val = NULL;
  const mxArray *c5_hc_unusedU2 = NULL;
  const mxArray *c5_hc_unusedU3 = NULL;
  const mxArray *c5_hc_isfimathlocal = NULL;
  const mxArray *c5_ic_T = NULL;
  const mxArray *c5_ic_F = NULL;
  const mxArray *c5_ic_val = NULL;
  const mxArray *c5_ic_unusedU2 = NULL;
  const mxArray *c5_ic_unusedU3 = NULL;
  const mxArray *c5_ic_isfimathlocal = NULL;
  const mxArray *c5_jc_T = NULL;
  const mxArray *c5_jc_F = NULL;
  const mxArray *c5_jc_val = NULL;
  const mxArray *c5_jc_unusedU2 = NULL;
  const mxArray *c5_jc_unusedU3 = NULL;
  const mxArray *c5_jc_isfimathlocal = NULL;
  const mxArray *c5_kc_T = NULL;
  const mxArray *c5_kc_F = NULL;
  const mxArray *c5_kc_val = NULL;
  const mxArray *c5_kc_unusedU2 = NULL;
  const mxArray *c5_kc_unusedU3 = NULL;
  const mxArray *c5_kc_isfimathlocal = NULL;
  const mxArray *c5_lc_T = NULL;
  const mxArray *c5_lc_F = NULL;
  const mxArray *c5_lc_val = NULL;
  const mxArray *c5_lc_unusedU2 = NULL;
  const mxArray *c5_lc_unusedU3 = NULL;
  const mxArray *c5_lc_isfimathlocal = NULL;
  const mxArray *c5_mc_T = NULL;
  const mxArray *c5_mc_F = NULL;
  const mxArray *c5_mc_val = NULL;
  const mxArray *c5_mc_unusedU2 = NULL;
  const mxArray *c5_mc_unusedU3 = NULL;
  const mxArray *c5_mc_isfimathlocal = NULL;
  const mxArray *c5_nc_T = NULL;
  const mxArray *c5_nc_F = NULL;
  const mxArray *c5_nc_val = NULL;
  const mxArray *c5_nc_unusedU2 = NULL;
  const mxArray *c5_nc_unusedU3 = NULL;
  const mxArray *c5_nc_isfimathlocal = NULL;
  const mxArray *c5_oc_T = NULL;
  const mxArray *c5_oc_F = NULL;
  const mxArray *c5_oc_val = NULL;
  const mxArray *c5_oc_unusedU2 = NULL;
  const mxArray *c5_oc_unusedU3 = NULL;
  const mxArray *c5_oc_isfimathlocal = NULL;
  const mxArray *c5_pc_T = NULL;
  const mxArray *c5_pc_F = NULL;
  const mxArray *c5_pc_val = NULL;
  const mxArray *c5_pc_unusedU2 = NULL;
  const mxArray *c5_pc_unusedU3 = NULL;
  const mxArray *c5_pc_isfimathlocal = NULL;
  const mxArray *c5_qc_T = NULL;
  const mxArray *c5_qc_F = NULL;
  const mxArray *c5_qc_val = NULL;
  const mxArray *c5_qc_unusedU2 = NULL;
  const mxArray *c5_qc_unusedU3 = NULL;
  const mxArray *c5_qc_isfimathlocal = NULL;
  const mxArray *c5_rc_T = NULL;
  const mxArray *c5_rc_F = NULL;
  const mxArray *c5_rc_val = NULL;
  const mxArray *c5_rc_unusedU2 = NULL;
  const mxArray *c5_rc_unusedU3 = NULL;
  const mxArray *c5_rc_isfimathlocal = NULL;
  const mxArray *c5_sc_T = NULL;
  const mxArray *c5_sc_F = NULL;
  const mxArray *c5_sc_val = NULL;
  const mxArray *c5_sc_unusedU2 = NULL;
  const mxArray *c5_sc_unusedU3 = NULL;
  const mxArray *c5_sc_isfimathlocal = NULL;
  const mxArray *c5_tc_T = NULL;
  const mxArray *c5_tc_F = NULL;
  const mxArray *c5_tc_val = NULL;
  const mxArray *c5_tc_unusedU2 = NULL;
  const mxArray *c5_tc_unusedU3 = NULL;
  const mxArray *c5_tc_isfimathlocal = NULL;
  const mxArray *c5_uc_T = NULL;
  const mxArray *c5_uc_F = NULL;
  const mxArray *c5_uc_val = NULL;
  const mxArray *c5_uc_unusedU2 = NULL;
  const mxArray *c5_uc_unusedU3 = NULL;
  const mxArray *c5_uc_isfimathlocal = NULL;
  const mxArray *c5_vc_T = NULL;
  const mxArray *c5_vc_F = NULL;
  const mxArray *c5_vc_val = NULL;
  const mxArray *c5_vc_unusedU2 = NULL;
  const mxArray *c5_vc_unusedU3 = NULL;
  const mxArray *c5_vc_isfimathlocal = NULL;
  const mxArray *c5_wc_T = NULL;
  const mxArray *c5_wc_F = NULL;
  const mxArray *c5_wc_val = NULL;
  const mxArray *c5_wc_unusedU2 = NULL;
  const mxArray *c5_wc_unusedU3 = NULL;
  const mxArray *c5_wc_isfimathlocal = NULL;
  const mxArray *c5_xc_T = NULL;
  const mxArray *c5_xc_F = NULL;
  const mxArray *c5_xc_val = NULL;
  const mxArray *c5_xc_unusedU2 = NULL;
  const mxArray *c5_xc_unusedU3 = NULL;
  const mxArray *c5_xc_isfimathlocal = NULL;
  const mxArray *c5_yc_T = NULL;
  const mxArray *c5_yc_F = NULL;
  const mxArray *c5_yc_val = NULL;
  const mxArray *c5_yc_unusedU2 = NULL;
  const mxArray *c5_yc_unusedU3 = NULL;
  const mxArray *c5_yc_isfimathlocal = NULL;
  const mxArray *c5_ad_T = NULL;
  const mxArray *c5_ad_F = NULL;
  const mxArray *c5_ad_val = NULL;
  const mxArray *c5_ad_unusedU2 = NULL;
  const mxArray *c5_ad_unusedU3 = NULL;
  const mxArray *c5_ad_isfimathlocal = NULL;
  const mxArray *c5_bd_T = NULL;
  const mxArray *c5_bd_F = NULL;
  const mxArray *c5_bd_val = NULL;
  const mxArray *c5_bd_unusedU2 = NULL;
  const mxArray *c5_bd_unusedU3 = NULL;
  const mxArray *c5_bd_isfimathlocal = NULL;
  const mxArray *c5_cd_T = NULL;
  const mxArray *c5_cd_F = NULL;
  const mxArray *c5_cd_val = NULL;
  const mxArray *c5_cd_unusedU2 = NULL;
  const mxArray *c5_cd_unusedU3 = NULL;
  const mxArray *c5_cd_isfimathlocal = NULL;
  const mxArray *c5_dd_T = NULL;
  const mxArray *c5_dd_F = NULL;
  const mxArray *c5_dd_val = NULL;
  const mxArray *c5_dd_unusedU2 = NULL;
  const mxArray *c5_dd_unusedU3 = NULL;
  const mxArray *c5_dd_isfimathlocal = NULL;
  const mxArray *c5_ed_T = NULL;
  const mxArray *c5_ed_F = NULL;
  const mxArray *c5_ed_val = NULL;
  const mxArray *c5_ed_unusedU2 = NULL;
  const mxArray *c5_ed_unusedU3 = NULL;
  const mxArray *c5_ed_isfimathlocal = NULL;
  const mxArray *c5_fd_T = NULL;
  const mxArray *c5_fd_F = NULL;
  const mxArray *c5_fd_val = NULL;
  const mxArray *c5_fd_unusedU2 = NULL;
  const mxArray *c5_fd_unusedU3 = NULL;
  const mxArray *c5_fd_isfimathlocal = NULL;
  const mxArray *c5_gd_T = NULL;
  const mxArray *c5_gd_F = NULL;
  const mxArray *c5_gd_val = NULL;
  const mxArray *c5_gd_unusedU2 = NULL;
  const mxArray *c5_gd_unusedU3 = NULL;
  const mxArray *c5_gd_isfimathlocal = NULL;
  const mxArray *c5_hd_T = NULL;
  const mxArray *c5_hd_F = NULL;
  const mxArray *c5_hd_val = NULL;
  const mxArray *c5_hd_unusedU2 = NULL;
  const mxArray *c5_hd_unusedU3 = NULL;
  const mxArray *c5_hd_isfimathlocal = NULL;
  const mxArray *c5_id_T = NULL;
  const mxArray *c5_id_F = NULL;
  const mxArray *c5_id_val = NULL;
  const mxArray *c5_id_unusedU2 = NULL;
  const mxArray *c5_id_unusedU3 = NULL;
  const mxArray *c5_id_isfimathlocal = NULL;
  const mxArray *c5_jd_T = NULL;
  const mxArray *c5_jd_F = NULL;
  const mxArray *c5_jd_val = NULL;
  const mxArray *c5_jd_unusedU2 = NULL;
  const mxArray *c5_jd_unusedU3 = NULL;
  const mxArray *c5_jd_isfimathlocal = NULL;
  const mxArray *c5_kd_T = NULL;
  const mxArray *c5_kd_F = NULL;
  const mxArray *c5_kd_val = NULL;
  const mxArray *c5_kd_unusedU2 = NULL;
  const mxArray *c5_kd_unusedU3 = NULL;
  const mxArray *c5_kd_isfimathlocal = NULL;
  const mxArray *c5_ld_T = NULL;
  const mxArray *c5_ld_F = NULL;
  const mxArray *c5_ld_val = NULL;
  const mxArray *c5_ld_unusedU2 = NULL;
  const mxArray *c5_ld_unusedU3 = NULL;
  const mxArray *c5_ld_isfimathlocal = NULL;
  const mxArray *c5_md_T = NULL;
  const mxArray *c5_md_F = NULL;
  const mxArray *c5_md_val = NULL;
  const mxArray *c5_md_unusedU2 = NULL;
  const mxArray *c5_md_unusedU3 = NULL;
  const mxArray *c5_md_isfimathlocal = NULL;
  const mxArray *c5_nd_T = NULL;
  const mxArray *c5_nd_F = NULL;
  const mxArray *c5_nd_val = NULL;
  const mxArray *c5_nd_unusedU2 = NULL;
  const mxArray *c5_nd_unusedU3 = NULL;
  const mxArray *c5_nd_isfimathlocal = NULL;
  uint32_T c5_u0;
  const mxArray *c5_od_T = NULL;
  const mxArray *c5_od_F = NULL;
  const mxArray *c5_od_val = NULL;
  const mxArray *c5_od_unusedU2 = NULL;
  const mxArray *c5_od_unusedU3 = NULL;
  const mxArray *c5_od_isfimathlocal = NULL;
  uint16_T *c5_b_instr_out;
  uint8_T *c5_b_addr;
  uint8_T *c5_b_read;
  c5_b_instr_out = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c5_b_read = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c5_b_addr = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  c5_hoistedGlobal = *c5_b_addr;
  c5_b_hoistedGlobal = *c5_b_read;
  c5_addr = c5_hoistedGlobal;
  c5_read = c5_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 7U, 7U, c5_debug_family_names,
    c5_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_hdl_fm, 0U, c5_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargin, 1U, c5_e_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_nargout, 2U, c5_e_sf_marshallOut,
    c5_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_addr, 3U, c5_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c5_read, 4U, c5_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c5_instr_out, 5U, c5_b_sf_marshallOut,
    c5_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c5_data, 6U,
    c5_sf_marshallOut, c5_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 7);
  c5_hdl_fm = c5_eml_mx;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 15);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 16);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c5_data_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 17);
    c5_eml_fi_checkforconst(chartInstance);
    c5_isfi(chartInstance);
    c5_eml_fi_checkforerror(chartInstance);
    sf_mex_destroy(&c5_T);
    sf_mex_destroy(&c5_F);
    sf_mex_destroy(&c5_val);
    sf_mex_destroy(&c5_unusedU2);
    sf_mex_destroy(&c5_unusedU3);
    sf_mex_destroy(&c5_isfimathlocal);
    for (c5_i2 = 0; c5_i2 < 256; c5_i2++) {
      chartInstance->c5_data[c5_i2] = 0U;
    }

    chartInstance->c5_data_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 21);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_b_T);
  sf_mex_destroy(&c5_b_F);
  sf_mex_destroy(&c5_b_val);
  sf_mex_destroy(&c5_b_unusedU2);
  sf_mex_destroy(&c5_b_unusedU3);
  sf_mex_destroy(&c5_b_isfimathlocal);
  chartInstance->c5_data[0] = 2314U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 22);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_c_T);
  sf_mex_destroy(&c5_c_F);
  sf_mex_destroy(&c5_c_val);
  sf_mex_destroy(&c5_c_unusedU2);
  sf_mex_destroy(&c5_c_unusedU3);
  sf_mex_destroy(&c5_c_isfimathlocal);
  chartInstance->c5_data[1] = 2560U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 23);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_d_T);
  sf_mex_destroy(&c5_d_F);
  sf_mex_destroy(&c5_d_val);
  sf_mex_destroy(&c5_d_unusedU2);
  sf_mex_destroy(&c5_d_unusedU3);
  sf_mex_destroy(&c5_d_isfimathlocal);
  chartInstance->c5_data[2] = 2316U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 24);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_e_T);
  sf_mex_destroy(&c5_e_F);
  sf_mex_destroy(&c5_e_val);
  sf_mex_destroy(&c5_e_unusedU2);
  sf_mex_destroy(&c5_e_unusedU3);
  sf_mex_destroy(&c5_e_isfimathlocal);
  chartInstance->c5_data[3] = 2561U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 25);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_f_T);
  sf_mex_destroy(&c5_f_F);
  sf_mex_destroy(&c5_f_val);
  sf_mex_destroy(&c5_f_unusedU2);
  sf_mex_destroy(&c5_f_unusedU3);
  sf_mex_destroy(&c5_f_isfimathlocal);
  chartInstance->c5_data[4] = 2322U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 26);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_g_T);
  sf_mex_destroy(&c5_g_F);
  sf_mex_destroy(&c5_g_val);
  sf_mex_destroy(&c5_g_unusedU2);
  sf_mex_destroy(&c5_g_unusedU3);
  sf_mex_destroy(&c5_g_isfimathlocal);
  chartInstance->c5_data[5] = 2572U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 27);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_h_T);
  sf_mex_destroy(&c5_h_F);
  sf_mex_destroy(&c5_h_val);
  sf_mex_destroy(&c5_h_unusedU2);
  sf_mex_destroy(&c5_h_unusedU3);
  sf_mex_destroy(&c5_h_isfimathlocal);
  chartInstance->c5_data[6] = 2310U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 28);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_i_T);
  sf_mex_destroy(&c5_i_F);
  sf_mex_destroy(&c5_i_val);
  sf_mex_destroy(&c5_i_unusedU2);
  sf_mex_destroy(&c5_i_unusedU3);
  sf_mex_destroy(&c5_i_isfimathlocal);
  chartInstance->c5_data[7] = 2573U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 29);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_j_T);
  sf_mex_destroy(&c5_j_F);
  sf_mex_destroy(&c5_j_val);
  sf_mex_destroy(&c5_j_unusedU2);
  sf_mex_destroy(&c5_j_unusedU3);
  sf_mex_destroy(&c5_j_isfimathlocal);
  chartInstance->c5_data[8] = 2323U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 30);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_k_T);
  sf_mex_destroy(&c5_k_F);
  sf_mex_destroy(&c5_k_val);
  sf_mex_destroy(&c5_k_unusedU2);
  sf_mex_destroy(&c5_k_unusedU3);
  sf_mex_destroy(&c5_k_isfimathlocal);
  chartInstance->c5_data[9] = 2574U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 31);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_l_T);
  sf_mex_destroy(&c5_l_F);
  sf_mex_destroy(&c5_l_val);
  sf_mex_destroy(&c5_l_unusedU2);
  sf_mex_destroy(&c5_l_unusedU3);
  sf_mex_destroy(&c5_l_isfimathlocal);
  chartInstance->c5_data[10] = 2555U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 32);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_m_T);
  sf_mex_destroy(&c5_m_F);
  sf_mex_destroy(&c5_m_val);
  sf_mex_destroy(&c5_m_unusedU2);
  sf_mex_destroy(&c5_m_unusedU3);
  sf_mex_destroy(&c5_m_isfimathlocal);
  chartInstance->c5_data[11] = 2575U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 33);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_n_T);
  sf_mex_destroy(&c5_n_F);
  sf_mex_destroy(&c5_n_val);
  sf_mex_destroy(&c5_n_unusedU2);
  sf_mex_destroy(&c5_n_unusedU3);
  sf_mex_destroy(&c5_n_isfimathlocal);
  chartInstance->c5_data[12] = 2319U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 34);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_o_T);
  sf_mex_destroy(&c5_o_F);
  sf_mex_destroy(&c5_o_val);
  sf_mex_destroy(&c5_o_unusedU2);
  sf_mex_destroy(&c5_o_unusedU3);
  sf_mex_destroy(&c5_o_isfimathlocal);
  chartInstance->c5_data[13] = 2576U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 35);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_p_T);
  sf_mex_destroy(&c5_p_F);
  sf_mex_destroy(&c5_p_val);
  sf_mex_destroy(&c5_p_unusedU2);
  sf_mex_destroy(&c5_p_unusedU3);
  sf_mex_destroy(&c5_p_isfimathlocal);
  chartInstance->c5_data[14] = 2558U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 36);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_q_T);
  sf_mex_destroy(&c5_q_F);
  sf_mex_destroy(&c5_q_val);
  sf_mex_destroy(&c5_q_unusedU2);
  sf_mex_destroy(&c5_q_unusedU3);
  sf_mex_destroy(&c5_q_isfimathlocal);
  chartInstance->c5_data[15] = 2577U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 37);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_r_T);
  sf_mex_destroy(&c5_r_F);
  sf_mex_destroy(&c5_r_val);
  sf_mex_destroy(&c5_r_unusedU2);
  sf_mex_destroy(&c5_r_unusedU3);
  sf_mex_destroy(&c5_r_isfimathlocal);
  chartInstance->c5_data[16] = 2306U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 38);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_s_T);
  sf_mex_destroy(&c5_s_F);
  sf_mex_destroy(&c5_s_val);
  sf_mex_destroy(&c5_s_unusedU2);
  sf_mex_destroy(&c5_s_unusedU3);
  sf_mex_destroy(&c5_s_isfimathlocal);
  chartInstance->c5_data[17] = 2578U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 39);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_t_T);
  sf_mex_destroy(&c5_t_F);
  sf_mex_destroy(&c5_t_val);
  sf_mex_destroy(&c5_t_unusedU2);
  sf_mex_destroy(&c5_t_unusedU3);
  sf_mex_destroy(&c5_t_isfimathlocal);
  chartInstance->c5_data[18] = 2315U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 40);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_u_T);
  sf_mex_destroy(&c5_u_F);
  sf_mex_destroy(&c5_u_val);
  sf_mex_destroy(&c5_u_unusedU2);
  sf_mex_destroy(&c5_u_unusedU3);
  sf_mex_destroy(&c5_u_isfimathlocal);
  chartInstance->c5_data[19] = 2579U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 41);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_v_T);
  sf_mex_destroy(&c5_v_F);
  sf_mex_destroy(&c5_v_val);
  sf_mex_destroy(&c5_v_unusedU2);
  sf_mex_destroy(&c5_v_unusedU3);
  sf_mex_destroy(&c5_v_isfimathlocal);
  chartInstance->c5_data[20] = 2324U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 42);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_w_T);
  sf_mex_destroy(&c5_w_F);
  sf_mex_destroy(&c5_w_val);
  sf_mex_destroy(&c5_w_unusedU2);
  sf_mex_destroy(&c5_w_unusedU3);
  sf_mex_destroy(&c5_w_isfimathlocal);
  chartInstance->c5_data[21] = 2580U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 43);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_x_T);
  sf_mex_destroy(&c5_x_F);
  sf_mex_destroy(&c5_x_val);
  sf_mex_destroy(&c5_x_unusedU2);
  sf_mex_destroy(&c5_x_unusedU3);
  sf_mex_destroy(&c5_x_isfimathlocal);
  chartInstance->c5_data[22] = 2314U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 44);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_y_T);
  sf_mex_destroy(&c5_y_F);
  sf_mex_destroy(&c5_y_val);
  sf_mex_destroy(&c5_y_unusedU2);
  sf_mex_destroy(&c5_y_unusedU3);
  sf_mex_destroy(&c5_y_isfimathlocal);
  chartInstance->c5_data[23] = 2581U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 45);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_ab_T);
  sf_mex_destroy(&c5_ab_F);
  sf_mex_destroy(&c5_ab_val);
  sf_mex_destroy(&c5_ab_unusedU2);
  sf_mex_destroy(&c5_ab_unusedU3);
  sf_mex_destroy(&c5_ab_isfimathlocal);
  chartInstance->c5_data[24] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 46);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_bb_T);
  sf_mex_destroy(&c5_bb_F);
  sf_mex_destroy(&c5_bb_val);
  sf_mex_destroy(&c5_bb_unusedU2);
  sf_mex_destroy(&c5_bb_unusedU3);
  sf_mex_destroy(&c5_bb_isfimathlocal);
  chartInstance->c5_data[25] = 2562U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 47);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_cb_T);
  sf_mex_destroy(&c5_cb_F);
  sf_mex_destroy(&c5_cb_val);
  sf_mex_destroy(&c5_cb_unusedU2);
  sf_mex_destroy(&c5_cb_unusedU3);
  sf_mex_destroy(&c5_cb_isfimathlocal);
  chartInstance->c5_data[26] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 48);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_db_T);
  sf_mex_destroy(&c5_db_F);
  sf_mex_destroy(&c5_db_val);
  sf_mex_destroy(&c5_db_unusedU2);
  sf_mex_destroy(&c5_db_unusedU3);
  sf_mex_destroy(&c5_db_isfimathlocal);
  chartInstance->c5_data[27] = 2563U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 49);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_eb_T);
  sf_mex_destroy(&c5_eb_F);
  sf_mex_destroy(&c5_eb_val);
  sf_mex_destroy(&c5_eb_unusedU2);
  sf_mex_destroy(&c5_eb_unusedU3);
  sf_mex_destroy(&c5_eb_isfimathlocal);
  chartInstance->c5_data[28] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 50);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_fb_T);
  sf_mex_destroy(&c5_fb_F);
  sf_mex_destroy(&c5_fb_val);
  sf_mex_destroy(&c5_fb_unusedU2);
  sf_mex_destroy(&c5_fb_unusedU3);
  sf_mex_destroy(&c5_fb_isfimathlocal);
  chartInstance->c5_data[29] = 2564U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 51);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_gb_T);
  sf_mex_destroy(&c5_gb_F);
  sf_mex_destroy(&c5_gb_val);
  sf_mex_destroy(&c5_gb_unusedU2);
  sf_mex_destroy(&c5_gb_unusedU3);
  sf_mex_destroy(&c5_gb_isfimathlocal);
  chartInstance->c5_data[30] = 2U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 52);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_hb_T);
  sf_mex_destroy(&c5_hb_F);
  sf_mex_destroy(&c5_hb_val);
  sf_mex_destroy(&c5_hb_unusedU2);
  sf_mex_destroy(&c5_hb_unusedU3);
  sf_mex_destroy(&c5_hb_isfimathlocal);
  chartInstance->c5_data[31] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 53);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_ib_T);
  sf_mex_destroy(&c5_ib_F);
  sf_mex_destroy(&c5_ib_val);
  sf_mex_destroy(&c5_ib_unusedU2);
  sf_mex_destroy(&c5_ib_unusedU3);
  sf_mex_destroy(&c5_ib_isfimathlocal);
  chartInstance->c5_data[32] = 1540U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 54);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_jb_T);
  sf_mex_destroy(&c5_jb_F);
  sf_mex_destroy(&c5_jb_val);
  sf_mex_destroy(&c5_jb_unusedU2);
  sf_mex_destroy(&c5_jb_unusedU3);
  sf_mex_destroy(&c5_jb_isfimathlocal);
  chartInstance->c5_data[33] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 55);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_kb_T);
  sf_mex_destroy(&c5_kb_F);
  sf_mex_destroy(&c5_kb_val);
  sf_mex_destroy(&c5_kb_unusedU2);
  sf_mex_destroy(&c5_kb_unusedU3);
  sf_mex_destroy(&c5_kb_isfimathlocal);
  chartInstance->c5_data[34] = 1025U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 56);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_lb_T);
  sf_mex_destroy(&c5_lb_F);
  sf_mex_destroy(&c5_lb_val);
  sf_mex_destroy(&c5_lb_unusedU2);
  sf_mex_destroy(&c5_lb_unusedU3);
  sf_mex_destroy(&c5_lb_isfimathlocal);
  chartInstance->c5_data[35] = 2565U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 57);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_mb_T);
  sf_mex_destroy(&c5_mb_F);
  sf_mex_destroy(&c5_mb_val);
  sf_mex_destroy(&c5_mb_unusedU2);
  sf_mex_destroy(&c5_mb_unusedU3);
  sf_mex_destroy(&c5_mb_isfimathlocal);
  chartInstance->c5_data[36] = 261U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 58);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_nb_T);
  sf_mex_destroy(&c5_nb_F);
  sf_mex_destroy(&c5_nb_val);
  sf_mex_destroy(&c5_nb_unusedU2);
  sf_mex_destroy(&c5_nb_unusedU3);
  sf_mex_destroy(&c5_nb_isfimathlocal);
  chartInstance->c5_data[37] = 2566U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 59);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_ob_T);
  sf_mex_destroy(&c5_ob_F);
  sf_mex_destroy(&c5_ob_val);
  sf_mex_destroy(&c5_ob_unusedU2);
  sf_mex_destroy(&c5_ob_unusedU3);
  sf_mex_destroy(&c5_ob_isfimathlocal);
  chartInstance->c5_data[38] = 2U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 60);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_pb_T);
  sf_mex_destroy(&c5_pb_F);
  sf_mex_destroy(&c5_pb_val);
  sf_mex_destroy(&c5_pb_unusedU2);
  sf_mex_destroy(&c5_pb_unusedU3);
  sf_mex_destroy(&c5_pb_isfimathlocal);
  chartInstance->c5_data[39] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 61);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_qb_T);
  sf_mex_destroy(&c5_qb_F);
  sf_mex_destroy(&c5_qb_val);
  sf_mex_destroy(&c5_qb_unusedU2);
  sf_mex_destroy(&c5_qb_unusedU3);
  sf_mex_destroy(&c5_qb_isfimathlocal);
  chartInstance->c5_data[40] = 1025U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 62);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_rb_T);
  sf_mex_destroy(&c5_rb_F);
  sf_mex_destroy(&c5_rb_val);
  sf_mex_destroy(&c5_rb_unusedU2);
  sf_mex_destroy(&c5_rb_unusedU3);
  sf_mex_destroy(&c5_rb_isfimathlocal);
  chartInstance->c5_data[41] = 2567U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 63);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_sb_T);
  sf_mex_destroy(&c5_sb_F);
  sf_mex_destroy(&c5_sb_val);
  sf_mex_destroy(&c5_sb_unusedU2);
  sf_mex_destroy(&c5_sb_unusedU3);
  sf_mex_destroy(&c5_sb_isfimathlocal);
  chartInstance->c5_data[42] = 263U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 64);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_tb_T);
  sf_mex_destroy(&c5_tb_F);
  sf_mex_destroy(&c5_tb_val);
  sf_mex_destroy(&c5_tb_unusedU2);
  sf_mex_destroy(&c5_tb_unusedU3);
  sf_mex_destroy(&c5_tb_isfimathlocal);
  chartInstance->c5_data[43] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 65);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_ub_T);
  sf_mex_destroy(&c5_ub_F);
  sf_mex_destroy(&c5_ub_val);
  sf_mex_destroy(&c5_ub_unusedU2);
  sf_mex_destroy(&c5_ub_unusedU3);
  sf_mex_destroy(&c5_ub_isfimathlocal);
  chartInstance->c5_data[44] = 1542U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 66);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_vb_T);
  sf_mex_destroy(&c5_vb_F);
  sf_mex_destroy(&c5_vb_val);
  sf_mex_destroy(&c5_vb_unusedU2);
  sf_mex_destroy(&c5_vb_unusedU3);
  sf_mex_destroy(&c5_vb_isfimathlocal);
  chartInstance->c5_data[45] = 3330U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 67);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_wb_T);
  sf_mex_destroy(&c5_wb_F);
  sf_mex_destroy(&c5_wb_val);
  sf_mex_destroy(&c5_wb_unusedU2);
  sf_mex_destroy(&c5_wb_unusedU3);
  sf_mex_destroy(&c5_wb_isfimathlocal);
  chartInstance->c5_data[46] = 2055U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 68);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_xb_T);
  sf_mex_destroy(&c5_xb_F);
  sf_mex_destroy(&c5_xb_val);
  sf_mex_destroy(&c5_xb_unusedU2);
  sf_mex_destroy(&c5_xb_unusedU3);
  sf_mex_destroy(&c5_xb_isfimathlocal);
  chartInstance->c5_data[47] = 2304U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 69);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_yb_T);
  sf_mex_destroy(&c5_yb_F);
  sf_mex_destroy(&c5_yb_val);
  sf_mex_destroy(&c5_yb_unusedU2);
  sf_mex_destroy(&c5_yb_unusedU3);
  sf_mex_destroy(&c5_yb_isfimathlocal);
  chartInstance->c5_data[48] = 2563U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 70);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_ac_T);
  sf_mex_destroy(&c5_ac_F);
  sf_mex_destroy(&c5_ac_val);
  sf_mex_destroy(&c5_ac_unusedU2);
  sf_mex_destroy(&c5_ac_unusedU3);
  sf_mex_destroy(&c5_ac_isfimathlocal);
  chartInstance->c5_data[49] = 263U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 71);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_bc_T);
  sf_mex_destroy(&c5_bc_F);
  sf_mex_destroy(&c5_bc_val);
  sf_mex_destroy(&c5_bc_unusedU2);
  sf_mex_destroy(&c5_bc_unusedU3);
  sf_mex_destroy(&c5_bc_isfimathlocal);
  chartInstance->c5_data[50] = 2821U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 72);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_cc_T);
  sf_mex_destroy(&c5_cc_F);
  sf_mex_destroy(&c5_cc_val);
  sf_mex_destroy(&c5_cc_unusedU2);
  sf_mex_destroy(&c5_cc_unusedU3);
  sf_mex_destroy(&c5_cc_isfimathlocal);
  chartInstance->c5_data[51] = 6U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 73);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_dc_T);
  sf_mex_destroy(&c5_dc_F);
  sf_mex_destroy(&c5_dc_val);
  sf_mex_destroy(&c5_dc_unusedU2);
  sf_mex_destroy(&c5_dc_unusedU3);
  sf_mex_destroy(&c5_dc_isfimathlocal);
  chartInstance->c5_data[52] = 2823U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 74);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_ec_T);
  sf_mex_destroy(&c5_ec_F);
  sf_mex_destroy(&c5_ec_val);
  sf_mex_destroy(&c5_ec_unusedU2);
  sf_mex_destroy(&c5_ec_unusedU3);
  sf_mex_destroy(&c5_ec_isfimathlocal);
  chartInstance->c5_data[53] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 75);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_fc_T);
  sf_mex_destroy(&c5_fc_F);
  sf_mex_destroy(&c5_fc_val);
  sf_mex_destroy(&c5_fc_unusedU2);
  sf_mex_destroy(&c5_fc_unusedU3);
  sf_mex_destroy(&c5_fc_isfimathlocal);
  chartInstance->c5_data[54] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 76);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_gc_T);
  sf_mex_destroy(&c5_gc_F);
  sf_mex_destroy(&c5_gc_val);
  sf_mex_destroy(&c5_gc_unusedU2);
  sf_mex_destroy(&c5_gc_unusedU3);
  sf_mex_destroy(&c5_gc_isfimathlocal);
  chartInstance->c5_data[55] = 1026U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 77);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_hc_T);
  sf_mex_destroy(&c5_hc_F);
  sf_mex_destroy(&c5_hc_val);
  sf_mex_destroy(&c5_hc_unusedU2);
  sf_mex_destroy(&c5_hc_unusedU3);
  sf_mex_destroy(&c5_hc_isfimathlocal);
  chartInstance->c5_data[56] = 2562U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 78);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_ic_T);
  sf_mex_destroy(&c5_ic_F);
  sf_mex_destroy(&c5_ic_val);
  sf_mex_destroy(&c5_ic_unusedU2);
  sf_mex_destroy(&c5_ic_unusedU3);
  sf_mex_destroy(&c5_ic_isfimathlocal);
  chartInstance->c5_data[57] = 0U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 79);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_jc_T);
  sf_mex_destroy(&c5_jc_F);
  sf_mex_destroy(&c5_jc_val);
  sf_mex_destroy(&c5_jc_unusedU2);
  sf_mex_destroy(&c5_jc_unusedU3);
  sf_mex_destroy(&c5_jc_isfimathlocal);
  chartInstance->c5_data[58] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 80);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_kc_T);
  sf_mex_destroy(&c5_kc_F);
  sf_mex_destroy(&c5_kc_val);
  sf_mex_destroy(&c5_kc_unusedU2);
  sf_mex_destroy(&c5_kc_unusedU3);
  sf_mex_destroy(&c5_kc_isfimathlocal);
  chartInstance->c5_data[59] = 1538U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 81);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_lc_T);
  sf_mex_destroy(&c5_lc_F);
  sf_mex_destroy(&c5_lc_val);
  sf_mex_destroy(&c5_lc_unusedU2);
  sf_mex_destroy(&c5_lc_unusedU3);
  sf_mex_destroy(&c5_lc_isfimathlocal);
  chartInstance->c5_data[60] = 3842U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 82);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_mc_T);
  sf_mex_destroy(&c5_mc_F);
  sf_mex_destroy(&c5_mc_val);
  sf_mex_destroy(&c5_mc_unusedU2);
  sf_mex_destroy(&c5_mc_unusedU3);
  sf_mex_destroy(&c5_mc_isfimathlocal);
  chartInstance->c5_data[61] = 2271U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 83);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_nc_T);
  sf_mex_destroy(&c5_nc_F);
  sf_mex_destroy(&c5_nc_val);
  sf_mex_destroy(&c5_nc_unusedU2);
  sf_mex_destroy(&c5_nc_unusedU3);
  sf_mex_destroy(&c5_nc_isfimathlocal);
  chartInstance->c5_data[62] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 84);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_oc_T);
  sf_mex_destroy(&c5_oc_F);
  sf_mex_destroy(&c5_oc_val);
  sf_mex_destroy(&c5_oc_unusedU2);
  sf_mex_destroy(&c5_oc_unusedU3);
  sf_mex_destroy(&c5_oc_isfimathlocal);
  chartInstance->c5_data[63] = 2564U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 85);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_pc_T);
  sf_mex_destroy(&c5_pc_F);
  sf_mex_destroy(&c5_pc_val);
  sf_mex_destroy(&c5_pc_unusedU2);
  sf_mex_destroy(&c5_pc_unusedU3);
  sf_mex_destroy(&c5_pc_isfimathlocal);
  chartInstance->c5_data[64] = 3U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 86);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_qc_T);
  sf_mex_destroy(&c5_qc_F);
  sf_mex_destroy(&c5_qc_val);
  sf_mex_destroy(&c5_qc_unusedU2);
  sf_mex_destroy(&c5_qc_unusedU3);
  sf_mex_destroy(&c5_qc_isfimathlocal);
  chartInstance->c5_data[65] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 87);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_rc_T);
  sf_mex_destroy(&c5_rc_F);
  sf_mex_destroy(&c5_rc_val);
  sf_mex_destroy(&c5_rc_unusedU2);
  sf_mex_destroy(&c5_rc_unusedU3);
  sf_mex_destroy(&c5_rc_isfimathlocal);
  chartInstance->c5_data[66] = 1540U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 88);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_sc_T);
  sf_mex_destroy(&c5_sc_F);
  sf_mex_destroy(&c5_sc_val);
  sf_mex_destroy(&c5_sc_unusedU2);
  sf_mex_destroy(&c5_sc_unusedU3);
  sf_mex_destroy(&c5_sc_isfimathlocal);
  chartInstance->c5_data[67] = 3842U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 89);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_tc_T);
  sf_mex_destroy(&c5_tc_F);
  sf_mex_destroy(&c5_tc_val);
  sf_mex_destroy(&c5_tc_unusedU2);
  sf_mex_destroy(&c5_tc_unusedU3);
  sf_mex_destroy(&c5_tc_isfimathlocal);
  chartInstance->c5_data[68] = 2260U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 90);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_uc_T);
  sf_mex_destroy(&c5_uc_F);
  sf_mex_destroy(&c5_uc_val);
  sf_mex_destroy(&c5_uc_unusedU2);
  sf_mex_destroy(&c5_uc_unusedU3);
  sf_mex_destroy(&c5_uc_isfimathlocal);
  chartInstance->c5_data[69] = 2304U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 91);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_vc_T);
  sf_mex_destroy(&c5_vc_F);
  sf_mex_destroy(&c5_vc_val);
  sf_mex_destroy(&c5_vc_unusedU2);
  sf_mex_destroy(&c5_vc_unusedU3);
  sf_mex_destroy(&c5_vc_isfimathlocal);
  chartInstance->c5_data[70] = 2562U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 92);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_wc_T);
  sf_mex_destroy(&c5_wc_F);
  sf_mex_destroy(&c5_wc_val);
  sf_mex_destroy(&c5_wc_unusedU2);
  sf_mex_destroy(&c5_wc_unusedU3);
  sf_mex_destroy(&c5_wc_isfimathlocal);
  chartInstance->c5_data[71] = 257U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 93);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_xc_T);
  sf_mex_destroy(&c5_xc_F);
  sf_mex_destroy(&c5_xc_val);
  sf_mex_destroy(&c5_xc_unusedU2);
  sf_mex_destroy(&c5_xc_unusedU3);
  sf_mex_destroy(&c5_xc_isfimathlocal);
  chartInstance->c5_data[72] = 2815U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 94);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_yc_T);
  sf_mex_destroy(&c5_yc_F);
  sf_mex_destroy(&c5_yc_val);
  sf_mex_destroy(&c5_yc_unusedU2);
  sf_mex_destroy(&c5_yc_unusedU3);
  sf_mex_destroy(&c5_yc_isfimathlocal);
  chartInstance->c5_data[73] = 3696U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 95);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_ad_T);
  sf_mex_destroy(&c5_ad_F);
  sf_mex_destroy(&c5_ad_val);
  sf_mex_destroy(&c5_ad_unusedU2);
  sf_mex_destroy(&c5_ad_unusedU3);
  sf_mex_destroy(&c5_ad_isfimathlocal);
  chartInstance->c5_data[74] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 96);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_bd_T);
  sf_mex_destroy(&c5_bd_F);
  sf_mex_destroy(&c5_bd_val);
  sf_mex_destroy(&c5_bd_unusedU2);
  sf_mex_destroy(&c5_bd_unusedU3);
  sf_mex_destroy(&c5_bd_isfimathlocal);
  chartInstance->c5_data[75] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 97);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_cd_T);
  sf_mex_destroy(&c5_cd_F);
  sf_mex_destroy(&c5_cd_val);
  sf_mex_destroy(&c5_cd_unusedU2);
  sf_mex_destroy(&c5_cd_unusedU3);
  sf_mex_destroy(&c5_cd_isfimathlocal);
  chartInstance->c5_data[76] = 1025U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 98);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_dd_T);
  sf_mex_destroy(&c5_dd_F);
  sf_mex_destroy(&c5_dd_val);
  sf_mex_destroy(&c5_dd_unusedU2);
  sf_mex_destroy(&c5_dd_unusedU3);
  sf_mex_destroy(&c5_dd_isfimathlocal);
  chartInstance->c5_data[77] = 2561U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 99);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_ed_T);
  sf_mex_destroy(&c5_ed_F);
  sf_mex_destroy(&c5_ed_val);
  sf_mex_destroy(&c5_ed_unusedU2);
  sf_mex_destroy(&c5_ed_unusedU3);
  sf_mex_destroy(&c5_ed_isfimathlocal);
  chartInstance->c5_data[78] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 100);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_fd_T);
  sf_mex_destroy(&c5_fd_F);
  sf_mex_destroy(&c5_fd_val);
  sf_mex_destroy(&c5_fd_unusedU2);
  sf_mex_destroy(&c5_fd_unusedU3);
  sf_mex_destroy(&c5_fd_isfimathlocal);
  chartInstance->c5_data[79] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 101);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_gd_T);
  sf_mex_destroy(&c5_gd_F);
  sf_mex_destroy(&c5_gd_val);
  sf_mex_destroy(&c5_gd_unusedU2);
  sf_mex_destroy(&c5_gd_unusedU3);
  sf_mex_destroy(&c5_gd_isfimathlocal);
  chartInstance->c5_data[80] = 1026U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 102);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_hd_T);
  sf_mex_destroy(&c5_hd_F);
  sf_mex_destroy(&c5_hd_val);
  sf_mex_destroy(&c5_hd_unusedU2);
  sf_mex_destroy(&c5_hd_unusedU3);
  sf_mex_destroy(&c5_hd_isfimathlocal);
  chartInstance->c5_data[81] = 2562U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 103);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_id_T);
  sf_mex_destroy(&c5_id_F);
  sf_mex_destroy(&c5_id_val);
  sf_mex_destroy(&c5_id_unusedU2);
  sf_mex_destroy(&c5_id_unusedU3);
  sf_mex_destroy(&c5_id_isfimathlocal);
  chartInstance->c5_data[82] = 0U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 104);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_jd_T);
  sf_mex_destroy(&c5_jd_F);
  sf_mex_destroy(&c5_jd_val);
  sf_mex_destroy(&c5_jd_unusedU2);
  sf_mex_destroy(&c5_jd_unusedU3);
  sf_mex_destroy(&c5_jd_isfimathlocal);
  chartInstance->c5_data[83] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 105);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_kd_T);
  sf_mex_destroy(&c5_kd_F);
  sf_mex_destroy(&c5_kd_val);
  sf_mex_destroy(&c5_kd_unusedU2);
  sf_mex_destroy(&c5_kd_unusedU3);
  sf_mex_destroy(&c5_kd_isfimathlocal);
  chartInstance->c5_data[84] = 1538U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 106);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_ld_T);
  sf_mex_destroy(&c5_ld_F);
  sf_mex_destroy(&c5_ld_val);
  sf_mex_destroy(&c5_ld_unusedU2);
  sf_mex_destroy(&c5_ld_unusedU3);
  sf_mex_destroy(&c5_ld_isfimathlocal);
  chartInstance->c5_data[85] = 3842U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 107);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_md_T);
  sf_mex_destroy(&c5_md_F);
  sf_mex_destroy(&c5_md_val);
  sf_mex_destroy(&c5_md_unusedU2);
  sf_mex_destroy(&c5_md_unusedU3);
  sf_mex_destroy(&c5_md_isfimathlocal);
  chartInstance->c5_data[86] = 2289U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 108);
  c5_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c5_nd_T);
  sf_mex_destroy(&c5_nd_F);
  sf_mex_destroy(&c5_nd_val);
  sf_mex_destroy(&c5_nd_unusedU2);
  sf_mex_destroy(&c5_nd_unusedU3);
  sf_mex_destroy(&c5_nd_isfimathlocal);
  chartInstance->c5_data[87] = 3648U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 112);
  if (CV_EML_IF(0, 1, 1, c5_eq(chartInstance, c5_read))) {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 113);
    c5_u0 = (uint32_T)c5_addr + 1U;
    if (CV_SATURATION_EVAL(4, 0, 0, 0, c5_u0 > 255U)) {
      c5_u0 = 255U;
    }

    c5_instr_out = chartInstance->c5_data[(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
      "data", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("addr+1", (real_T)(uint8_T)
      c5_u0), 1, 256, 1, 0) - 1];
  } else {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 115);
    c5_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c5_od_T);
    sf_mex_destroy(&c5_od_F);
    sf_mex_destroy(&c5_od_val);
    sf_mex_destroy(&c5_od_unusedU2);
    sf_mex_destroy(&c5_od_unusedU3);
    sf_mex_destroy(&c5_od_isfimathlocal);
    c5_instr_out = 0U;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -115);
  _SFD_SYMBOL_SCOPE_POP();
  *c5_b_instr_out = c5_instr_out;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
}

static void initSimStructsc5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber)
{
  (void)c5_machineNumber;
  (void)c5_chartNumber;
  (void)c5_instanceNumber;
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  int32_T c5_i3;
  uint16_T c5_u[256];
  const mxArray *c5_y = NULL;
  int32_T c5_i4;
  uint16_T c5_b_u[256];
  const mxArray *c5_b_y = NULL;
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  for (c5_i3 = 0; c5_i3 < 256; c5_i3++) {
    c5_u[c5_i3] = (*(uint16_T (*)[256])c5_inData)[c5_i3];
  }

  c5_y = NULL;
  if (!chartInstance->c5_data_not_empty) {
    sf_mex_assign(&c5_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    for (c5_i4 = 0; c5_i4 < 256; c5_i4++) {
      c5_b_u[c5_i4] = c5_u[c5_i4];
    }

    c5_b_y = NULL;
    sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_b_u, 5, 0U, 1U, 0U, 2, 1, 256),
                  false);
    sf_mex_assign(&c5_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c5_eml_mx), 15, "numerictype", 14, sf_mex_dup(c5_b_eml_mx), 15,
      "simulinkarray", 14, c5_b_y, 15, "fimathislocal", 3, true), false);
  }

  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_b_data, const char_T *c5_identifier,
  uint16_T c5_y[256])
{
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_data), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_b_data);
}

static void c5_b_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId,
  uint16_T c5_y[256])
{
  int32_T c5_i5;
  uint32_T c5_uv1[2];
  const mxArray *c5_mxFi = NULL;
  const mxArray *c5_mxInt = NULL;
  uint16_T c5_uv2[256];
  int32_T c5_i6;
  for (c5_i5 = 0; c5_i5 < 2; c5_i5++) {
    c5_uv1[c5_i5] = 1U + 255U * (uint32_T)c5_i5;
  }

  if (mxIsEmpty(c5_u)) {
    chartInstance->c5_data_not_empty = false;
  } else {
    chartInstance->c5_data_not_empty = true;
    sf_mex_check_fi(c5_parentId, c5_u, false, 2U, c5_uv1, c5_eml_mx, c5_b_eml_mx);
    sf_mex_assign(&c5_mxFi, sf_mex_dup(c5_u), false);
    sf_mex_assign(&c5_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
                   (c5_mxFi)), false);
    sf_mex_import(c5_parentId, sf_mex_dup(c5_mxInt), c5_uv2, 1, 5, 0U, 1, 0U, 2,
                  1, 256);
    sf_mex_destroy(&c5_mxFi);
    sf_mex_destroy(&c5_mxInt);
    for (c5_i6 = 0; c5_i6 < 256; c5_i6++) {
      c5_y[c5_i6] = c5_uv2[c5_i6];
    }
  }

  sf_mex_destroy(&c5_u);
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_data;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  uint16_T c5_y[256];
  int32_T c5_i7;
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c5_b_data = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_data), &c5_thisId, c5_y);
  sf_mex_destroy(&c5_b_data);
  for (c5_i7 = 0; c5_i7 < 256; c5_i7++) {
    (*(uint16_T (*)[256])c5_outData)[c5_i7] = c5_y[c5_i7];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  uint16_T c5_u;
  const mxArray *c5_y = NULL;
  uint16_T c5_b_u;
  const mxArray *c5_b_y = NULL;
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c5_u = *(uint16_T *)c5_inData;
    c5_y = NULL;
    c5_b_u = c5_u;
    c5_b_y = NULL;
    sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 5, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c5_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c5_eml_mx), 15, "numerictype", 14, sf_mex_dup(c5_b_eml_mx), 15,
      "simulinkarray", 14, c5_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  } else {
    sf_mex_assign(&c5_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c5_mxArrayOutData;
}

static uint16_T c5_c_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_instr_out, const char_T *c5_identifier)
{
  uint16_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_instr_out),
    &c5_thisId);
  sf_mex_destroy(&c5_instr_out);
  return c5_y;
}

static uint16_T c5_d_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint16_T c5_y;
  const mxArray *c5_mxFi = NULL;
  const mxArray *c5_mxInt = NULL;
  uint16_T c5_u1;
  (void)chartInstance;
  sf_mex_check_fi(c5_parentId, c5_u, false, 0U, NULL, c5_eml_mx, c5_b_eml_mx);
  sf_mex_assign(&c5_mxFi, sf_mex_dup(c5_u), false);
  sf_mex_assign(&c5_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c5_mxFi)), false);
  sf_mex_import(c5_parentId, sf_mex_dup(c5_mxInt), &c5_u1, 1, 5, 0U, 0, 0U, 0);
  sf_mex_destroy(&c5_mxFi);
  sf_mex_destroy(&c5_mxInt);
  c5_y = c5_u1;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_instr_out;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  uint16_T c5_y;
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c5_instr_out = sf_mex_dup(c5_mxArrayInData);
    c5_identifier = c5_varName;
    c5_thisId.fIdentifier = c5_identifier;
    c5_thisId.fParent = NULL;
    c5_y = c5_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_instr_out),
      &c5_thisId);
    sf_mex_destroy(&c5_instr_out);
    *(uint16_T *)c5_outData = c5_y;
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  uint8_T c5_u;
  const mxArray *c5_y = NULL;
  uint8_T c5_b_u;
  const mxArray *c5_b_y = NULL;
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c5_u = *(uint8_T *)c5_inData;
    c5_y = NULL;
    c5_b_u = c5_u;
    c5_b_y = NULL;
    sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c5_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c5_eml_mx), 15, "numerictype", 14, sf_mex_dup(c5_c_eml_mx), 15,
      "simulinkarray", 14, c5_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  } else {
    sf_mex_assign(&c5_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c5_mxArrayOutData;
}

static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  uint8_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(uint8_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static const mxArray *c5_e_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_e_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d0, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_nargout;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c5_nargout = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_nargout), &c5_thisId);
  sf_mex_destroy(&c5_nargout);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_f_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  const mxArray *c5_u;
  const mxArray *c5_y = NULL;
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = sf_mex_dup(*(const mxArray **)c5_inData);
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_duplicatearraysafe(&c5_u), false);
  sf_mex_destroy(&c5_u);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

const mxArray *sf_c5_hdlcodercpu_eml_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_createstruct("structure", 2, 28, 1),
                false);
  c5_info_helper(&c5_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c5_nameCaptureInfo);
  return c5_nameCaptureInfo;
}

static void c5_info_helper(const mxArray **c5_info)
{
  const mxArray *c5_rhs0 = NULL;
  const mxArray *c5_lhs0 = NULL;
  const mxArray *c5_rhs1 = NULL;
  const mxArray *c5_lhs1 = NULL;
  const mxArray *c5_rhs2 = NULL;
  const mxArray *c5_lhs2 = NULL;
  const mxArray *c5_rhs3 = NULL;
  const mxArray *c5_lhs3 = NULL;
  const mxArray *c5_rhs4 = NULL;
  const mxArray *c5_lhs4 = NULL;
  const mxArray *c5_rhs5 = NULL;
  const mxArray *c5_lhs5 = NULL;
  const mxArray *c5_rhs6 = NULL;
  const mxArray *c5_lhs6 = NULL;
  const mxArray *c5_rhs7 = NULL;
  const mxArray *c5_lhs7 = NULL;
  const mxArray *c5_rhs8 = NULL;
  const mxArray *c5_lhs8 = NULL;
  const mxArray *c5_rhs9 = NULL;
  const mxArray *c5_lhs9 = NULL;
  const mxArray *c5_rhs10 = NULL;
  const mxArray *c5_lhs10 = NULL;
  const mxArray *c5_rhs11 = NULL;
  const mxArray *c5_lhs11 = NULL;
  const mxArray *c5_rhs12 = NULL;
  const mxArray *c5_lhs12 = NULL;
  const mxArray *c5_rhs13 = NULL;
  const mxArray *c5_lhs13 = NULL;
  const mxArray *c5_rhs14 = NULL;
  const mxArray *c5_lhs14 = NULL;
  const mxArray *c5_rhs15 = NULL;
  const mxArray *c5_lhs15 = NULL;
  const mxArray *c5_rhs16 = NULL;
  const mxArray *c5_lhs16 = NULL;
  const mxArray *c5_rhs17 = NULL;
  const mxArray *c5_lhs17 = NULL;
  const mxArray *c5_rhs18 = NULL;
  const mxArray *c5_lhs18 = NULL;
  const mxArray *c5_rhs19 = NULL;
  const mxArray *c5_lhs19 = NULL;
  const mxArray *c5_rhs20 = NULL;
  const mxArray *c5_lhs20 = NULL;
  const mxArray *c5_rhs21 = NULL;
  const mxArray *c5_lhs21 = NULL;
  const mxArray *c5_rhs22 = NULL;
  const mxArray *c5_lhs22 = NULL;
  const mxArray *c5_rhs23 = NULL;
  const mxArray *c5_lhs23 = NULL;
  const mxArray *c5_rhs24 = NULL;
  const mxArray *c5_lhs24 = NULL;
  const mxArray *c5_rhs25 = NULL;
  const mxArray *c5_lhs25 = NULL;
  const mxArray *c5_rhs26 = NULL;
  const mxArray *c5_lhs26 = NULL;
  const mxArray *c5_rhs27 = NULL;
  const mxArray *c5_lhs27 = NULL;
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("fimath"), "name", "name", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1381857498U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c5_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_fimath_constructor_helper"),
                  "name", "name", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_fimath_constructor_helper.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c5_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("fi_impl"), "name", "name", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1389302372U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c5_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c5_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("length"), "name", "name", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("cell"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1303153406U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c5_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_fi_checkforconst"), "name",
                  "name", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("embedded.fimath"),
                  "dominantType", "dominantType", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforconst.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1346517552U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c5_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("isfi"), "name", "name", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c5_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 7);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 7);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c5_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 8);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_fi_constructor_helper"),
                  "name", "name", 8);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_fi_constructor_helper.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c5_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 9);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_fi_checkforerror"), "name",
                  "name", 9);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 9);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1360285946U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c5_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(""), "context", "context", 10);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eq"), "name", "name", 10);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1346517574U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c5_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "context", "context", 11);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 11);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c5_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "context", "context", 12);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("isfi"), "name", "name", 12);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c5_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 13);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 13);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 13);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c5_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "context", "context", 14);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("isscaledtype"), "name", "name",
                  14);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c5_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "context", "context", 15);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("isfixed"), "name", "name", 15);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c5_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "context", "context", 16);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("get"), "name", "name", 16);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 16);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 16);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c5_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "context", "context", 17);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("isfi"), "name", "name", 17);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 17);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c5_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "context", "context", 18);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_type_relop_const"), "name",
                  "name", 18);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1346517574U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c5_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m"),
                  "context", "context", 19);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("all"), "name", "name", 19);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1372589614U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c5_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  20);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 20);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c5_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  21);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 21);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c5_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  22);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.allOrAny"),
                  "name", "name", 22);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1372590358U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c5_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 23);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 23);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 23);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c5_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 24);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("isequal"), "name", "name", 24);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 24);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286825958U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c5_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "context",
                  "context", 25);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_isequal_core"), "name",
                  "name", 25);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1286825986U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c5_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 26);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "coder.internal.constNonSingletonDim"), "name", "name", 26);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/constNonSingletonDim.m"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1372590360U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c5_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m"),
                  "context", "context", 27);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("eml_make_same_complexity"),
                  "name", "name", 27);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c5_info, c5_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_make_same_complexity.m"),
                  "resolved", "resolved", 27);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c5_info, c5_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c5_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c5_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c5_info, sf_mex_duplicatearraysafe(&c5_lhs27), "lhs", "lhs",
                  27);
  sf_mex_destroy(&c5_rhs0);
  sf_mex_destroy(&c5_lhs0);
  sf_mex_destroy(&c5_rhs1);
  sf_mex_destroy(&c5_lhs1);
  sf_mex_destroy(&c5_rhs2);
  sf_mex_destroy(&c5_lhs2);
  sf_mex_destroy(&c5_rhs3);
  sf_mex_destroy(&c5_lhs3);
  sf_mex_destroy(&c5_rhs4);
  sf_mex_destroy(&c5_lhs4);
  sf_mex_destroy(&c5_rhs5);
  sf_mex_destroy(&c5_lhs5);
  sf_mex_destroy(&c5_rhs6);
  sf_mex_destroy(&c5_lhs6);
  sf_mex_destroy(&c5_rhs7);
  sf_mex_destroy(&c5_lhs7);
  sf_mex_destroy(&c5_rhs8);
  sf_mex_destroy(&c5_lhs8);
  sf_mex_destroy(&c5_rhs9);
  sf_mex_destroy(&c5_lhs9);
  sf_mex_destroy(&c5_rhs10);
  sf_mex_destroy(&c5_lhs10);
  sf_mex_destroy(&c5_rhs11);
  sf_mex_destroy(&c5_lhs11);
  sf_mex_destroy(&c5_rhs12);
  sf_mex_destroy(&c5_lhs12);
  sf_mex_destroy(&c5_rhs13);
  sf_mex_destroy(&c5_lhs13);
  sf_mex_destroy(&c5_rhs14);
  sf_mex_destroy(&c5_lhs14);
  sf_mex_destroy(&c5_rhs15);
  sf_mex_destroy(&c5_lhs15);
  sf_mex_destroy(&c5_rhs16);
  sf_mex_destroy(&c5_lhs16);
  sf_mex_destroy(&c5_rhs17);
  sf_mex_destroy(&c5_lhs17);
  sf_mex_destroy(&c5_rhs18);
  sf_mex_destroy(&c5_lhs18);
  sf_mex_destroy(&c5_rhs19);
  sf_mex_destroy(&c5_lhs19);
  sf_mex_destroy(&c5_rhs20);
  sf_mex_destroy(&c5_lhs20);
  sf_mex_destroy(&c5_rhs21);
  sf_mex_destroy(&c5_lhs21);
  sf_mex_destroy(&c5_rhs22);
  sf_mex_destroy(&c5_lhs22);
  sf_mex_destroy(&c5_rhs23);
  sf_mex_destroy(&c5_lhs23);
  sf_mex_destroy(&c5_rhs24);
  sf_mex_destroy(&c5_lhs24);
  sf_mex_destroy(&c5_rhs25);
  sf_mex_destroy(&c5_lhs25);
  sf_mex_destroy(&c5_rhs26);
  sf_mex_destroy(&c5_lhs26);
  sf_mex_destroy(&c5_rhs27);
  sf_mex_destroy(&c5_lhs27);
}

static const mxArray *c5_emlrt_marshallOut(const char * c5_u)
{
  const mxArray *c5_y = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c5_u)), false);
  return c5_y;
}

static const mxArray *c5_b_emlrt_marshallOut(const uint32_T c5_u)
{
  const mxArray *c5_y = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 7, 0U, 0U, 0U, 0), false);
  return c5_y;
}

static void c5_eml_fi_checkforconst(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c5_isfi(SFc5_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c5_eml_fi_checkforerror(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static boolean_T c5_eq(SFc5_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c5_a0)
{
  uint8_T c5_a;
  uint8_T c5_b_a0;
  uint8_T c5_a1;
  uint8_T c5_b_a1;
  (void)chartInstance;
  c5_a = c5_a0;
  c5_b_a0 = c5_a;
  c5_a1 = c5_b_a0;
  c5_b_a1 = c5_a1;
  return c5_b_a1 == 1;
}

static const mxArray *c5_g_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static int32_T c5_f_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i8;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i8, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i8;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent),
    &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_h_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData;
  uint8_T c5_u;
  const mxArray *c5_y = NULL;
  uint8_T c5_b_u;
  const mxArray *c5_b_y = NULL;
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c5_u = *(uint8_T *)c5_inData;
    c5_y = NULL;
    c5_b_u = c5_u;
    c5_b_y = NULL;
    sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c5_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c5_eml_mx), 15, "numerictype", 14, sf_mex_dup(c5_c_eml_mx), 15,
      "simulinkarray", 14, c5_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  } else {
    sf_mex_assign(&c5_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c5_mxArrayOutData;
}

static uint8_T c5_g_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_b_is_active_c5_hdlcodercpu_eml, const char_T
  *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_h_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_b_is_active_c5_hdlcodercpu_eml), &c5_thisId);
  sf_mex_destroy(&c5_b_is_active_c5_hdlcodercpu_eml);
  return c5_y;
}

static uint8_T c5_h_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u2;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u2, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u2;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void init_dsm_address_info(SFc5_hdlcodercpu_emlInstanceStruct
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

void sf_c5_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2807916274U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(106130931U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3449456942U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(687191910U);
}

mxArray *sf_c5_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("nU9Z7PNXvB0nhKlvt3oAxB");
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
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
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(1));
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

mxArray *sf_c5_hdlcodercpu_eml_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_hdlcodercpu_eml_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c5_hdlcodercpu_eml(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[6],T\"instr_out\",},{M[4],M[0],T\"data\",S'l','i','p'{{M1x2[341 345],M[0],}}},{M[8],M[0],T\"is_active_c5_hdlcodercpu_eml\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_hdlcodercpu_eml_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _hdlcodercpu_emlMachineNumber_,
           5,
           1,
           1,
           0,
           3,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"addr");
          _SFD_SET_DATA_PROPS(1,1,1,0,"read");
          _SFD_SET_DATA_PROPS(2,2,0,1,"instr_out");
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
        _SFD_CV_INIT_EML(0,1,1,2,0,1,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,4938);
        _SFD_CV_INIT_EML_SATURATION(0,1,0,4878,-1,4884);
        _SFD_CV_INIT_EML_IF(0,1,0,347,364,-1,416);
        _SFD_CV_INIT_EML_IF(0,1,1,4843,4856,4887,4936);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,1,0,1,0,1,0,0,
          (MexFcnForType)c5_h_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT16,0,NULL,1,0,12,0,1,0,0,
          (MexFcnForType)c5_b_sf_marshallOut,(MexInFcnForType)c5_b_sf_marshallIn);

        {
          uint8_T *c5_addr;
          uint8_T *c5_read;
          uint16_T *c5_instr_out;
          c5_instr_out = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c5_read = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c5_addr = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c5_addr);
          _SFD_SET_DATA_VALUE_PTR(1U, c5_read);
          _SFD_SET_DATA_VALUE_PTR(2U, c5_instr_out);
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
  return "4duIofkJdw6JTUxjCgz1JC";
}

static void sf_opaque_initialize_c5_hdlcodercpu_eml(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c5_hdlcodercpu_eml((SFc5_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
  initialize_c5_hdlcodercpu_eml((SFc5_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c5_hdlcodercpu_eml(void *chartInstanceVar)
{
  enable_c5_hdlcodercpu_eml((SFc5_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c5_hdlcodercpu_eml(void *chartInstanceVar)
{
  disable_c5_hdlcodercpu_eml((SFc5_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c5_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_gateway_c5_hdlcodercpu_eml((SFc5_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c5_hdlcodercpu_eml(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c5_hdlcodercpu_eml
    ((SFc5_hdlcodercpu_emlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_hdlcodercpu_eml();/* state var info */
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

extern void sf_internal_set_sim_state_c5_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c5_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c5_hdlcodercpu_eml((SFc5_hdlcodercpu_emlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c5_hdlcodercpu_eml(SimStruct* S)
{
  return sf_internal_get_sim_state_c5_hdlcodercpu_eml(S);
}

static void sf_opaque_set_sim_state_c5_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c5_hdlcodercpu_eml(S, st);
}

static void sf_opaque_terminate_c5_hdlcodercpu_eml(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_hdlcodercpu_emlInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_hdlcodercpu_eml_optimization_info();
    }

    finalize_c5_hdlcodercpu_eml((SFc5_hdlcodercpu_emlInstanceStruct*)
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
  initSimStructsc5_hdlcodercpu_eml((SFc5_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_hdlcodercpu_eml(SimStruct *S)
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
    initialize_params_c5_hdlcodercpu_eml((SFc5_hdlcodercpu_emlInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c5_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_hdlcodercpu_eml_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,5,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,5,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3362384602U));
  ssSetChecksum1(S,(774813637U));
  ssSetChecksum2(S,(2362230443U));
  ssSetChecksum3(S,(920338717U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_hdlcodercpu_eml(SimStruct *S)
{
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)utMalloc(sizeof
    (SFc5_hdlcodercpu_emlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc5_hdlcodercpu_emlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c5_hdlcodercpu_eml;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c5_hdlcodercpu_eml;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c5_hdlcodercpu_eml;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_hdlcodercpu_eml;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c5_hdlcodercpu_eml;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c5_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c5_hdlcodercpu_eml;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c5_hdlcodercpu_eml;
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

void c5_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_hdlcodercpu_eml(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_hdlcodercpu_eml_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
