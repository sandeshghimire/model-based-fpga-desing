/* Include files */

#include "blascompat32.h"
#include "hdlcodercpu_eml_sfun.h"
#include "c2_hdlcodercpu_eml.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "hdlcodercpu_eml_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const mxArray *c2_eml_mx;
static const char * c2_debug_family_names[35] = { "hdl_fm", "mask",
  "minor_opcode_bit6", "temp_address_data", "indirect_bit", "c", "n",
  "minor_opcode_bit4", "v", "z", "nargin", "nargout", "data_in", "in_flags",
  "master_rst", "IR_in", "shifter_sel", "out_flags", "ALU_func", "print_data",
  "DM_addr", "DM_r_w", "AC_func", "AC_data", "IR_func", "PC_func", "addr_inc",
  "IM_read", "hlt", "CPU_state", "previous_CPU_state", "major_opcode",
  "minor_opcode", "address_data", "indirect_address" };

static const mxArray *c2_b_eml_mx;
static const mxArray *c2_c_eml_mx;
static const mxArray *c2_d_eml_mx;
static const mxArray *c2_e_eml_mx;
static const mxArray *c2_f_eml_mx;
static const mxArray *c2_g_eml_mx;
static const mxArray *c2_h_eml_mx;
static const mxArray *c2_i_eml_mx;

/* Function Declarations */
static void initialize_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initialize_params_c2_hdlcodercpu_eml
  (SFc2_hdlcodercpu_emlInstanceStruct *chartInstance);
static void enable_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void disable_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c2_update_debugger_state_c2_hdlcodercpu_eml
  (SFc2_hdlcodercpu_emlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_hdlcodercpu_eml
  (SFc2_hdlcodercpu_emlInstanceStruct *chartInstance);
static void set_sim_state_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c2_st);
static void finalize_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void sf_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c2_chartstep_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initSimStructsc2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static uint8_T c2_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_indirect_address, const char_T
  *c2_identifier);
static uint8_T c2_b_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_c_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_address_data, const char_T *c2_identifier);
static uint8_T c2_d_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_e_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_minor_opcode, const char_T *c2_identifier);
static uint8_T c2_f_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_g_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_major_opcode, const char_T *c2_identifier);
static uint8_T c2_h_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_i_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_previous_CPU_state, const char_T
  *c2_identifier);
static uint8_T c2_j_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_k_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_CPU_state, const char_T *c2_identifier);
static uint8_T c2_l_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_m_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_hlt, const char_T *c2_identifier);
static uint8_T c2_n_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_o_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_IM_read, const char_T *c2_identifier);
static uint8_T c2_p_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int8_T c2_q_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_addr_inc, const char_T *c2_identifier);
static int8_T c2_r_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_s_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_PC_func, const char_T *c2_identifier);
static uint8_T c2_t_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_u_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_AC_func, const char_T *c2_identifier);
static uint8_T c2_v_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static boolean_T c2_w_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_print_data, const char_T *c2_identifier);
static boolean_T c2_x_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_m_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_y_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_n_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_o_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_p_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_ab_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_q_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_bb_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_r_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int8_T c2_cb_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_s_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_t_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[39]);
static boolean_T c2_logical(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_a);
static uint8_T c2_uint8(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c2_A);
static uint8_T c2_b_uint8(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_A);
static uint8_T c2_c_uint8(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_A);
static boolean_T c2_b_logical(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_a);
static void c2_isfloat(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance);
static int16_T c2_minus(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c2_a0);
static uint16_T c2_bitsrl(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint16_T c2_ain);
static void c2_b_isfloat(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance);
static uint16_T c2_b_bitsrl(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint16_T c2_ain);
static uint16_T c2_bitand(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint16_T c2_a, uint16_T c2_b);
static const mxArray *c2_u_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_db_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_v_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_eb_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_out_flags, const char_T *c2_identifier);
static uint8_T c2_fb_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void init_dsm_address_info(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_CPU_state_not_empty = FALSE;
  chartInstance->c2_previous_CPU_state_not_empty = FALSE;
  chartInstance->c2_major_opcode_not_empty = FALSE;
  chartInstance->c2_minor_opcode_not_empty = FALSE;
  chartInstance->c2_address_data_not_empty = FALSE;
  chartInstance->c2_indirect_address_not_empty = FALSE;
  chartInstance->c2_is_active_c2_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c2_i_eml_mx, sf_mex_call_debug("numerictype", 1U, 10U, 15,
    "WordLength", 6, 7.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c2_h_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 12.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c2_g_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 4.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c2_f_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 3.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c2_e_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 2.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c2_d_eml_mx, sf_mex_call_debug("numerictype", 1U, 10U, 15,
    "WordLength", 6, 8.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c2_c_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 1.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c2_b_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 8.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c2_eml_mx, sf_mex_call_debug("fimath", 1U, 38U, 15, "RoundMode",
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

static void initialize_params_c2_hdlcodercpu_eml
  (SFc2_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void enable_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_hdlcodercpu_eml
  (SFc2_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c2_hdlcodercpu_eml
  (SFc2_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int8_T c2_hoistedGlobal;
  int8_T c2_u;
  const mxArray *c2_b_y = NULL;
  int8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  uint8_T c2_b_hoistedGlobal;
  uint8_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  uint8_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  uint8_T c2_c_hoistedGlobal;
  uint8_T c2_e_u;
  const mxArray *c2_f_y = NULL;
  uint8_T c2_f_u;
  const mxArray *c2_g_y = NULL;
  uint8_T c2_d_hoistedGlobal;
  uint8_T c2_g_u;
  const mxArray *c2_h_y = NULL;
  uint8_T c2_e_hoistedGlobal;
  uint8_T c2_h_u;
  const mxArray *c2_i_y = NULL;
  uint8_T c2_i_u;
  const mxArray *c2_j_y = NULL;
  uint8_T c2_f_hoistedGlobal;
  uint8_T c2_j_u;
  const mxArray *c2_k_y = NULL;
  uint8_T c2_k_u;
  const mxArray *c2_l_y = NULL;
  uint8_T c2_g_hoistedGlobal;
  uint8_T c2_l_u;
  const mxArray *c2_m_y = NULL;
  uint8_T c2_m_u;
  const mxArray *c2_n_y = NULL;
  uint8_T c2_h_hoistedGlobal;
  uint8_T c2_n_u;
  const mxArray *c2_o_y = NULL;
  uint8_T c2_o_u;
  const mxArray *c2_p_y = NULL;
  int8_T c2_i_hoistedGlobal;
  int8_T c2_p_u;
  const mxArray *c2_q_y = NULL;
  int8_T c2_q_u;
  const mxArray *c2_r_y = NULL;
  uint8_T c2_j_hoistedGlobal;
  uint8_T c2_r_u;
  const mxArray *c2_s_y = NULL;
  uint8_T c2_k_hoistedGlobal;
  uint8_T c2_s_u;
  const mxArray *c2_t_y = NULL;
  uint8_T c2_t_u;
  const mxArray *c2_u_y = NULL;
  boolean_T c2_l_hoistedGlobal;
  boolean_T c2_u_u;
  const mxArray *c2_v_y = NULL;
  uint8_T c2_m_hoistedGlobal;
  uint8_T c2_v_u;
  const mxArray *c2_w_y = NULL;
  uint8_T c2_w_u;
  const mxArray *c2_x_y = NULL;
  uint8_T c2_n_hoistedGlobal;
  uint8_T c2_x_u;
  const mxArray *c2_y_y = NULL;
  uint8_T c2_o_hoistedGlobal;
  uint8_T c2_y_u;
  const mxArray *c2_ab_y = NULL;
  uint8_T c2_ab_u;
  const mxArray *c2_bb_y = NULL;
  uint8_T c2_p_hoistedGlobal;
  uint8_T c2_bb_u;
  const mxArray *c2_cb_y = NULL;
  uint8_T c2_q_hoistedGlobal;
  uint8_T c2_cb_u;
  const mxArray *c2_db_y = NULL;
  uint8_T c2_db_u;
  const mxArray *c2_eb_y = NULL;
  uint8_T c2_r_hoistedGlobal;
  uint8_T c2_eb_u;
  const mxArray *c2_fb_y = NULL;
  uint8_T c2_fb_u;
  const mxArray *c2_gb_y = NULL;
  uint8_T c2_s_hoistedGlobal;
  uint8_T c2_gb_u;
  const mxArray *c2_hb_y = NULL;
  uint8_T c2_t_hoistedGlobal;
  uint8_T c2_hb_u;
  const mxArray *c2_ib_y = NULL;
  int8_T *c2_AC_data;
  uint8_T *c2_AC_func;
  uint8_T *c2_ALU_func;
  uint8_T *c2_DM_addr;
  uint8_T *c2_DM_r_w;
  uint8_T *c2_IM_read;
  uint8_T *c2_IR_func;
  uint8_T *c2_PC_func;
  int8_T *c2_addr_inc;
  uint8_T *c2_hlt;
  uint8_T *c2_out_flags;
  boolean_T *c2_print_data;
  uint8_T *c2_shifter_sel;
  c2_hlt = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 13);
  c2_IM_read = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 12);
  c2_addr_inc = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 11);
  c2_PC_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 10);
  c2_IR_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 9);
  c2_AC_data = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 8);
  c2_AC_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c2_DM_r_w = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c2_DM_addr = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c2_print_data = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c2_ALU_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c2_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c2_shifter_sel = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(20));
  c2_hoistedGlobal = *c2_AC_data;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  c2_b_u = c2_u;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 2, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_b_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_d_eml_mx), 15,
    "simulinkarray", 14, c2_c_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = *c2_AC_func;
  c2_c_u = c2_b_hoistedGlobal;
  c2_d_y = NULL;
  c2_d_u = c2_c_u;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_d_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_f_eml_mx), 15,
    "simulinkarray", 14, c2_e_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c2_y, 1, c2_d_y);
  c2_c_hoistedGlobal = *c2_ALU_func;
  c2_e_u = c2_c_hoistedGlobal;
  c2_f_y = NULL;
  c2_f_u = c2_e_u;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_f_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_f_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_f_eml_mx), 15,
    "simulinkarray", 14, c2_g_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c2_y, 2, c2_f_y);
  c2_d_hoistedGlobal = *c2_DM_addr;
  c2_g_u = c2_d_hoistedGlobal;
  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", &c2_g_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 3, c2_h_y);
  c2_e_hoistedGlobal = *c2_DM_r_w;
  c2_h_u = c2_e_hoistedGlobal;
  c2_i_y = NULL;
  c2_i_u = c2_h_u;
  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", &c2_i_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_i_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_c_eml_mx), 15,
    "simulinkarray", 14, c2_j_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c2_y, 4, c2_i_y);
  c2_f_hoistedGlobal = *c2_IM_read;
  c2_j_u = c2_f_hoistedGlobal;
  c2_k_y = NULL;
  c2_k_u = c2_j_u;
  c2_l_y = NULL;
  sf_mex_assign(&c2_l_y, sf_mex_create("y", &c2_k_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_k_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_c_eml_mx), 15,
    "simulinkarray", 14, c2_l_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c2_y, 5, c2_k_y);
  c2_g_hoistedGlobal = *c2_IR_func;
  c2_l_u = c2_g_hoistedGlobal;
  c2_m_y = NULL;
  c2_m_u = c2_l_u;
  c2_n_y = NULL;
  sf_mex_assign(&c2_n_y, sf_mex_create("y", &c2_m_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_m_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_e_eml_mx), 15,
    "simulinkarray", 14, c2_n_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c2_y, 6, c2_m_y);
  c2_h_hoistedGlobal = *c2_PC_func;
  c2_n_u = c2_h_hoistedGlobal;
  c2_o_y = NULL;
  c2_o_u = c2_n_u;
  c2_p_y = NULL;
  sf_mex_assign(&c2_p_y, sf_mex_create("y", &c2_o_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_o_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_e_eml_mx), 15,
    "simulinkarray", 14, c2_p_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c2_y, 7, c2_o_y);
  c2_i_hoistedGlobal = *c2_addr_inc;
  c2_p_u = c2_i_hoistedGlobal;
  c2_q_y = NULL;
  c2_q_u = c2_p_u;
  c2_r_y = NULL;
  sf_mex_assign(&c2_r_y, sf_mex_create("y", &c2_q_u, 2, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_q_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_d_eml_mx), 15,
    "simulinkarray", 14, c2_r_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c2_y, 8, c2_q_y);
  c2_j_hoistedGlobal = *c2_hlt;
  c2_r_u = c2_j_hoistedGlobal;
  c2_s_y = NULL;
  sf_mex_assign(&c2_s_y, sf_mex_create("y", &c2_r_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 9, c2_s_y);
  c2_k_hoistedGlobal = *c2_out_flags;
  c2_s_u = c2_k_hoistedGlobal;
  c2_t_y = NULL;
  c2_t_u = c2_s_u;
  c2_u_y = NULL;
  sf_mex_assign(&c2_u_y, sf_mex_create("y", &c2_t_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_t_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_g_eml_mx), 15,
    "simulinkarray", 14, c2_u_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c2_y, 10, c2_t_y);
  c2_l_hoistedGlobal = *c2_print_data;
  c2_u_u = c2_l_hoistedGlobal;
  c2_v_y = NULL;
  sf_mex_assign(&c2_v_y, sf_mex_create("y", &c2_u_u, 11, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 11, c2_v_y);
  c2_m_hoistedGlobal = *c2_shifter_sel;
  c2_v_u = c2_m_hoistedGlobal;
  c2_w_y = NULL;
  c2_w_u = c2_v_u;
  c2_x_y = NULL;
  sf_mex_assign(&c2_x_y, sf_mex_create("y", &c2_w_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_w_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_e_eml_mx), 15,
    "simulinkarray", 14, c2_x_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c2_y, 12, c2_w_y);
  c2_n_hoistedGlobal = chartInstance->c2_CPU_state;
  c2_x_u = c2_n_hoistedGlobal;
  c2_y_y = NULL;
  if (!chartInstance->c2_CPU_state_not_empty) {
    sf_mex_assign(&c2_y_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_y_y, sf_mex_create("y", &c2_x_u, 3, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c2_y, 13, c2_y_y);
  c2_o_hoistedGlobal = chartInstance->c2_address_data;
  c2_y_u = c2_o_hoistedGlobal;
  c2_ab_y = NULL;
  if (!chartInstance->c2_address_data_not_empty) {
    sf_mex_assign(&c2_ab_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    c2_ab_u = c2_y_u;
    c2_bb_y = NULL;
    sf_mex_assign(&c2_bb_y, sf_mex_create("y", &c2_ab_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_ab_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx), 15,
      "simulinkarray", 14, c2_bb_y, 15, "fimathislocal", 3, TRUE));
  }

  sf_mex_setcell(c2_y, 14, c2_ab_y);
  c2_p_hoistedGlobal = chartInstance->c2_indirect_address;
  c2_bb_u = c2_p_hoistedGlobal;
  c2_cb_y = NULL;
  if (!chartInstance->c2_indirect_address_not_empty) {
    sf_mex_assign(&c2_cb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_cb_y, sf_mex_create("y", &c2_bb_u, 3, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c2_y, 15, c2_cb_y);
  c2_q_hoistedGlobal = chartInstance->c2_major_opcode;
  c2_cb_u = c2_q_hoistedGlobal;
  c2_db_y = NULL;
  if (!chartInstance->c2_major_opcode_not_empty) {
    sf_mex_assign(&c2_db_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    c2_db_u = c2_cb_u;
    c2_eb_y = NULL;
    sf_mex_assign(&c2_eb_y, sf_mex_create("y", &c2_db_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_db_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx), 15,
      "simulinkarray", 14, c2_eb_y, 15, "fimathislocal", 3, TRUE));
  }

  sf_mex_setcell(c2_y, 16, c2_db_y);
  c2_r_hoistedGlobal = chartInstance->c2_minor_opcode;
  c2_eb_u = c2_r_hoistedGlobal;
  c2_fb_y = NULL;
  if (!chartInstance->c2_minor_opcode_not_empty) {
    sf_mex_assign(&c2_fb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    c2_fb_u = c2_eb_u;
    c2_gb_y = NULL;
    sf_mex_assign(&c2_gb_y, sf_mex_create("y", &c2_fb_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_fb_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx), 15,
      "simulinkarray", 14, c2_gb_y, 15, "fimathislocal", 3, TRUE));
  }

  sf_mex_setcell(c2_y, 17, c2_fb_y);
  c2_s_hoistedGlobal = chartInstance->c2_previous_CPU_state;
  c2_gb_u = c2_s_hoistedGlobal;
  c2_hb_y = NULL;
  if (!chartInstance->c2_previous_CPU_state_not_empty) {
    sf_mex_assign(&c2_hb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_hb_y, sf_mex_create("y", &c2_gb_u, 3, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c2_y, 18, c2_hb_y);
  c2_t_hoistedGlobal = chartInstance->c2_is_active_c2_hdlcodercpu_eml;
  c2_hb_u = c2_t_hoistedGlobal;
  c2_ib_y = NULL;
  sf_mex_assign(&c2_ib_y, sf_mex_create("y", &c2_hb_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 19, c2_ib_y);
  sf_mex_assign(&c2_st, c2_y);
  return c2_st;
}

static void set_sim_state_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  int8_T *c2_AC_data;
  uint8_T *c2_AC_func;
  uint8_T *c2_ALU_func;
  uint8_T *c2_DM_addr;
  uint8_T *c2_DM_r_w;
  uint8_T *c2_IM_read;
  uint8_T *c2_IR_func;
  uint8_T *c2_PC_func;
  int8_T *c2_addr_inc;
  uint8_T *c2_hlt;
  uint8_T *c2_out_flags;
  boolean_T *c2_print_data;
  uint8_T *c2_shifter_sel;
  c2_hlt = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 13);
  c2_IM_read = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 12);
  c2_addr_inc = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 11);
  c2_PC_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 10);
  c2_IR_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 9);
  c2_AC_data = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 8);
  c2_AC_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c2_DM_r_w = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c2_DM_addr = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c2_print_data = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c2_ALU_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c2_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c2_shifter_sel = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  *c2_AC_data = c2_q_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 0)), "AC_data");
  *c2_AC_func = c2_u_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 1)), "AC_func");
  *c2_ALU_func = c2_u_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 2)), "ALU_func");
  *c2_DM_addr = c2_m_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 3)), "DM_addr");
  *c2_DM_r_w = c2_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 4)), "DM_r_w");
  *c2_IM_read = c2_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 5)), "IM_read");
  *c2_IR_func = c2_s_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 6)), "IR_func");
  *c2_PC_func = c2_s_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 7)), "PC_func");
  *c2_addr_inc = c2_q_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 8)), "addr_inc");
  *c2_hlt = c2_m_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u,
    9)), "hlt");
  *c2_out_flags = c2_eb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 10)), "out_flags");
  *c2_print_data = c2_w_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 11)), "print_data");
  *c2_shifter_sel = c2_s_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 12)), "shifter_sel");
  chartInstance->c2_CPU_state = c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 13)), "CPU_state");
  chartInstance->c2_address_data = c2_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 14)), "address_data");
  chartInstance->c2_indirect_address = c2_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 15)), "indirect_address");
  chartInstance->c2_major_opcode = c2_g_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 16)), "major_opcode");
  chartInstance->c2_minor_opcode = c2_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 17)), "minor_opcode");
  chartInstance->c2_previous_CPU_state = c2_i_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 18)), "previous_CPU_state");
  chartInstance->c2_is_active_c2_hdlcodercpu_eml = c2_m_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 19)),
     "is_active_c2_hdlcodercpu_eml");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_hdlcodercpu_eml(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&c2_eml_mx);
  sf_mex_destroy(&c2_b_eml_mx);
  sf_mex_destroy(&c2_c_eml_mx);
  sf_mex_destroy(&c2_d_eml_mx);
  sf_mex_destroy(&c2_e_eml_mx);
  sf_mex_destroy(&c2_f_eml_mx);
  sf_mex_destroy(&c2_g_eml_mx);
  sf_mex_destroy(&c2_h_eml_mx);
  sf_mex_destroy(&c2_i_eml_mx);
}

static void sf_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  int8_T *c2_data_in;
  uint8_T *c2_in_flags;
  boolean_T *c2_master_rst;
  uint8_T *c2_shifter_sel;
  uint8_T *c2_out_flags;
  uint8_T *c2_ALU_func;
  boolean_T *c2_print_data;
  uint16_T *c2_IR_in;
  uint8_T *c2_DM_addr;
  uint8_T *c2_DM_r_w;
  uint8_T *c2_AC_func;
  int8_T *c2_AC_data;
  uint8_T *c2_IR_func;
  uint8_T *c2_PC_func;
  int8_T *c2_addr_inc;
  uint8_T *c2_IM_read;
  uint8_T *c2_hlt;
  c2_hlt = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 13);
  c2_IM_read = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 12);
  c2_addr_inc = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 11);
  c2_PC_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 10);
  c2_IR_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 9);
  c2_AC_data = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 8);
  c2_AC_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c2_DM_r_w = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c2_DM_addr = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c2_IR_in = (uint16_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c2_print_data = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c2_ALU_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c2_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c2_shifter_sel = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_master_rst = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_in_flags = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_data_in = (int8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_data_in, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_in_flags, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_master_rst, 2U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_shifter_sel, 3U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_out_flags, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_ALU_func, 5U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_print_data, 6U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_IR_in, 7U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_DM_addr, 8U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_DM_r_w, 9U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_AC_func, 10U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_AC_data, 11U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_IR_func, 12U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_PC_func, 13U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_addr_inc, 14U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_IM_read, 15U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_hlt, 16U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_hdlcodercpu_eml(chartInstance);
  sf_debug_check_for_state_inconsistency(_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  int8_T c2_hoistedGlobal;
  uint8_T c2_b_hoistedGlobal;
  boolean_T c2_c_hoistedGlobal;
  uint16_T c2_d_hoistedGlobal;
  int8_T c2_data_in;
  uint8_T c2_in_flags;
  boolean_T c2_master_rst;
  uint16_T c2_IR_in;
  uint32_T c2_debug_family_var_map[35];
  const mxArray *c2_hdl_fm = NULL;
  uint16_T c2_mask;
  uint8_T c2_minor_opcode_bit6;
  int8_T c2_temp_address_data;
  uint8_T c2_indirect_bit;
  uint8_T c2_c;
  uint8_T c2_n;
  uint8_T c2_minor_opcode_bit4;
  uint8_T c2_v;
  uint8_T c2_z;
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 13.0;
  uint8_T c2_shifter_sel;
  uint8_T c2_out_flags;
  uint8_T c2_ALU_func;
  boolean_T c2_print_data;
  uint8_T c2_DM_addr;
  uint8_T c2_DM_r_w;
  uint8_T c2_AC_func;
  int8_T c2_AC_data;
  uint8_T c2_IR_func;
  uint8_T c2_PC_func;
  int8_T c2_addr_inc;
  uint8_T c2_IM_read;
  uint8_T c2_hlt;
  const mxArray *c2_m0 = NULL;
  const mxArray *c2_m1 = NULL;
  const mxArray *c2_m2 = NULL;
  const mxArray *c2_m3 = NULL;
  const mxArray *c2_m4 = NULL;
  const mxArray *c2_m5 = NULL;
  const mxArray *c2_m6 = NULL;
  const mxArray *c2_m7 = NULL;
  const mxArray *c2_m8 = NULL;
  const mxArray *c2_m9 = NULL;
  const mxArray *c2_m10 = NULL;
  const mxArray *c2_m11 = NULL;
  const mxArray *c2_m12 = NULL;
  const mxArray *c2_m13 = NULL;
  const mxArray *c2_m14 = NULL;
  const mxArray *c2_m15 = NULL;
  const mxArray *c2_m16 = NULL;
  const mxArray *c2_m17 = NULL;
  const mxArray *c2_m18 = NULL;
  const mxArray *c2_m19 = NULL;
  const mxArray *c2_m20 = NULL;
  const mxArray *c2_m21 = NULL;
  const mxArray *c2_m22 = NULL;
  const mxArray *c2_m23 = NULL;
  const mxArray *c2_m24 = NULL;
  const mxArray *c2_m25 = NULL;
  const mxArray *c2_m26 = NULL;
  const mxArray *c2_m27 = NULL;
  const mxArray *c2_m28 = NULL;
  const mxArray *c2_m29 = NULL;
  const mxArray *c2_m30 = NULL;
  const mxArray *c2_m31 = NULL;
  const mxArray *c2_m32 = NULL;
  const mxArray *c2_m33 = NULL;
  const mxArray *c2_m34 = NULL;
  const mxArray *c2_m35 = NULL;
  const mxArray *c2_m36 = NULL;
  const mxArray *c2_m37 = NULL;
  const mxArray *c2_m38 = NULL;
  const mxArray *c2_m39 = NULL;
  const mxArray *c2_m40 = NULL;
  const mxArray *c2_m41 = NULL;
  const mxArray *c2_m42 = NULL;
  const mxArray *c2_m43 = NULL;
  const mxArray *c2_m44 = NULL;
  const mxArray *c2_m45 = NULL;
  const mxArray *c2_m46 = NULL;
  const mxArray *c2_m47 = NULL;
  const mxArray *c2_m48 = NULL;
  const mxArray *c2_m49 = NULL;
  const mxArray *c2_m50 = NULL;
  const mxArray *c2_m51 = NULL;
  const mxArray *c2_m52 = NULL;
  const mxArray *c2_m53 = NULL;
  const mxArray *c2_m54 = NULL;
  const mxArray *c2_m55 = NULL;
  const mxArray *c2_m56 = NULL;
  const mxArray *c2_m57 = NULL;
  const mxArray *c2_m58 = NULL;
  const mxArray *c2_m59 = NULL;
  const mxArray *c2_m60 = NULL;
  const mxArray *c2_m61 = NULL;
  const mxArray *c2_m62 = NULL;
  const mxArray *c2_m63 = NULL;
  const mxArray *c2_m64 = NULL;
  const mxArray *c2_m65 = NULL;
  const mxArray *c2_m66 = NULL;
  const mxArray *c2_m67 = NULL;
  const mxArray *c2_m68 = NULL;
  const mxArray *c2_m69 = NULL;
  const mxArray *c2_m70 = NULL;
  const mxArray *c2_m71 = NULL;
  const mxArray *c2_m72 = NULL;
  const mxArray *c2_m73 = NULL;
  const mxArray *c2_m74 = NULL;
  const mxArray *c2_m75 = NULL;
  const mxArray *c2_m76 = NULL;
  const mxArray *c2_m77 = NULL;
  const mxArray *c2_m78 = NULL;
  const mxArray *c2_m79 = NULL;
  const mxArray *c2_m80 = NULL;
  const mxArray *c2_m81 = NULL;
  const mxArray *c2_m82 = NULL;
  const mxArray *c2_m83 = NULL;
  const mxArray *c2_m84 = NULL;
  const mxArray *c2_m85 = NULL;
  const mxArray *c2_m86 = NULL;
  const mxArray *c2_m87 = NULL;
  const mxArray *c2_m88 = NULL;
  const mxArray *c2_m89 = NULL;
  const mxArray *c2_m90 = NULL;
  const mxArray *c2_m91 = NULL;
  const mxArray *c2_m92 = NULL;
  const mxArray *c2_m93 = NULL;
  const mxArray *c2_m94 = NULL;
  const mxArray *c2_m95 = NULL;
  const mxArray *c2_m96 = NULL;
  const mxArray *c2_m97 = NULL;
  const mxArray *c2_m98 = NULL;
  const mxArray *c2_m99 = NULL;
  const mxArray *c2_m100 = NULL;
  const mxArray *c2_m101 = NULL;
  const mxArray *c2_m102 = NULL;
  const mxArray *c2_m103 = NULL;
  const mxArray *c2_m104 = NULL;
  const mxArray *c2_m105 = NULL;
  const mxArray *c2_m106 = NULL;
  const mxArray *c2_m107 = NULL;
  const mxArray *c2_m108 = NULL;
  const mxArray *c2_m109 = NULL;
  const mxArray *c2_m110 = NULL;
  const mxArray *c2_m111 = NULL;
  const mxArray *c2_m112 = NULL;
  const mxArray *c2_m113 = NULL;
  const mxArray *c2_m114 = NULL;
  const mxArray *c2_m115 = NULL;
  const mxArray *c2_m116 = NULL;
  const mxArray *c2_m117 = NULL;
  const mxArray *c2_m118 = NULL;
  const mxArray *c2_m119 = NULL;
  const mxArray *c2_m120 = NULL;
  const mxArray *c2_m121 = NULL;
  const mxArray *c2_m122 = NULL;
  const mxArray *c2_m123 = NULL;
  const mxArray *c2_m124 = NULL;
  const mxArray *c2_m125 = NULL;
  const mxArray *c2_m126 = NULL;
  const mxArray *c2_m127 = NULL;
  const mxArray *c2_m128 = NULL;
  const mxArray *c2_m129 = NULL;
  const mxArray *c2_m130 = NULL;
  const mxArray *c2_m131 = NULL;
  const mxArray *c2_m132 = NULL;
  uint16_T c2_varargin_1;
  uint16_T c2_b_varargin_1;
  uint16_T c2_var1;
  uint8_T c2_hfi;
  const mxArray *c2_m133 = NULL;
  const mxArray *c2_m134 = NULL;
  const mxArray *c2_m135 = NULL;
  const mxArray *c2_m136 = NULL;
  const mxArray *c2_m137 = NULL;
  const mxArray *c2_m138 = NULL;
  const mxArray *c2_m139 = NULL;
  const mxArray *c2_m140 = NULL;
  const mxArray *c2_m141 = NULL;
  const mxArray *c2_m142 = NULL;
  const mxArray *c2_m143 = NULL;
  const mxArray *c2_m144 = NULL;
  const mxArray *c2_m145 = NULL;
  const mxArray *c2_m146 = NULL;
  uint16_T c2_c_varargin_1;
  uint16_T c2_d_varargin_1;
  const mxArray *c2_m147 = NULL;
  const mxArray *c2_m148 = NULL;
  const mxArray *c2_m149 = NULL;
  const mxArray *c2_m150 = NULL;
  uint16_T c2_b_var1;
  uint8_T c2_b_hfi;
  const mxArray *c2_m151 = NULL;
  const mxArray *c2_m152 = NULL;
  const mxArray *c2_m153 = NULL;
  const mxArray *c2_m154 = NULL;
  const mxArray *c2_m155 = NULL;
  const mxArray *c2_m156 = NULL;
  const mxArray *c2_m157 = NULL;
  const mxArray *c2_m158 = NULL;
  const mxArray *c2_m159 = NULL;
  const mxArray *c2_m160 = NULL;
  const mxArray *c2_m161 = NULL;
  const mxArray *c2_m162 = NULL;
  const mxArray *c2_m163 = NULL;
  const mxArray *c2_m164 = NULL;
  uint16_T c2_e_varargin_1;
  uint16_T c2_f_varargin_1;
  const mxArray *c2_m165 = NULL;
  const mxArray *c2_m166 = NULL;
  const mxArray *c2_m167 = NULL;
  const mxArray *c2_m168 = NULL;
  uint16_T c2_c_var1;
  uint8_T c2_c_hfi;
  const mxArray *c2_m169 = NULL;
  const mxArray *c2_m170 = NULL;
  const mxArray *c2_m171 = NULL;
  const mxArray *c2_m172 = NULL;
  const mxArray *c2_m173 = NULL;
  const mxArray *c2_m174 = NULL;
  const mxArray *c2_m175 = NULL;
  const mxArray *c2_m176 = NULL;
  const mxArray *c2_m177 = NULL;
  const mxArray *c2_m178 = NULL;
  const mxArray *c2_m179 = NULL;
  const mxArray *c2_m180 = NULL;
  const mxArray *c2_m181 = NULL;
  const mxArray *c2_m182 = NULL;
  const mxArray *c2_m183 = NULL;
  const mxArray *c2_m184 = NULL;
  const mxArray *c2_m185 = NULL;
  const mxArray *c2_m186 = NULL;
  const mxArray *c2_m187 = NULL;
  const mxArray *c2_m188 = NULL;
  const mxArray *c2_m189 = NULL;
  const mxArray *c2_m190 = NULL;
  const mxArray *c2_m191 = NULL;
  const mxArray *c2_m192 = NULL;
  const mxArray *c2_m193 = NULL;
  const mxArray *c2_m194 = NULL;
  const mxArray *c2_m195 = NULL;
  const mxArray *c2_m196 = NULL;
  const mxArray *c2_m197 = NULL;
  const mxArray *c2_m198 = NULL;
  const mxArray *c2_m199 = NULL;
  const mxArray *c2_m200 = NULL;
  const mxArray *c2_m201 = NULL;
  const mxArray *c2_m202 = NULL;
  const mxArray *c2_m203 = NULL;
  uint8_T c2_e_hoistedGlobal;
  uint8_T c2_a;
  const mxArray *c2_m204 = NULL;
  const mxArray *c2_m205 = NULL;
  uint8_T c2_a1;
  uint8_T c2_slice_temp;
  uint8_T c2_f_hoistedGlobal;
  uint8_T c2_g_varargin_1;
  uint8_T c2_h_varargin_1;
  uint8_T c2_d_var1;
  int8_T c2_i0;
  const mxArray *c2_m206 = NULL;
  const mxArray *c2_m207 = NULL;
  const mxArray *c2_m208 = NULL;
  const mxArray *c2_m209 = NULL;
  const mxArray *c2_m210 = NULL;
  const mxArray *c2_m211 = NULL;
  const mxArray *c2_m212 = NULL;
  int16_T c2_i_varargin_1;
  int16_T c2_j_varargin_1;
  const mxArray *c2_m213 = NULL;
  const mxArray *c2_m214 = NULL;
  const mxArray *c2_m215 = NULL;
  const mxArray *c2_m216 = NULL;
  int16_T c2_e_var1;
  const mxArray *c2_m217 = NULL;
  const mxArray *c2_m218 = NULL;
  const mxArray *c2_m219 = NULL;
  const mxArray *c2_m220 = NULL;
  const mxArray *c2_m221 = NULL;
  const mxArray *c2_m222 = NULL;
  const mxArray *c2_m223 = NULL;
  const mxArray *c2_m224 = NULL;
  const mxArray *c2_m225 = NULL;
  const mxArray *c2_m226 = NULL;
  const mxArray *c2_m227 = NULL;
  const mxArray *c2_m228 = NULL;
  const mxArray *c2_m229 = NULL;
  const mxArray *c2_m230 = NULL;
  uint8_T c2_g_hoistedGlobal;
  uint8_T c2_k_varargin_1;
  uint8_T c2_l_varargin_1;
  uint8_T c2_f_var1;
  const mxArray *c2_m231 = NULL;
  const mxArray *c2_m232 = NULL;
  const mxArray *c2_m233 = NULL;
  const mxArray *c2_m234 = NULL;
  const mxArray *c2_m235 = NULL;
  const mxArray *c2_m236 = NULL;
  const mxArray *c2_m237 = NULL;
  const mxArray *c2_m238 = NULL;
  const mxArray *c2_m239 = NULL;
  const mxArray *c2_m240 = NULL;
  const mxArray *c2_m241 = NULL;
  const mxArray *c2_m242 = NULL;
  const mxArray *c2_m243 = NULL;
  const mxArray *c2_m244 = NULL;
  uint8_T c2_h_hoistedGlobal;
  uint8_T c2_b_a;
  const mxArray *c2_m245 = NULL;
  const mxArray *c2_m246 = NULL;
  uint8_T c2_b_a1;
  uint8_T c2_b_slice_temp;
  const mxArray *c2_m247 = NULL;
  const mxArray *c2_m248 = NULL;
  const mxArray *c2_m249 = NULL;
  const mxArray *c2_m250 = NULL;
  const mxArray *c2_m251 = NULL;
  const mxArray *c2_m252 = NULL;
  const mxArray *c2_m253 = NULL;
  const mxArray *c2_m254 = NULL;
  const mxArray *c2_m255 = NULL;
  const mxArray *c2_m256 = NULL;
  const mxArray *c2_m257 = NULL;
  const mxArray *c2_m258 = NULL;
  const mxArray *c2_m259 = NULL;
  const mxArray *c2_m260 = NULL;
  uint8_T c2_i_hoistedGlobal;
  uint8_T c2_c_a;
  const mxArray *c2_m261 = NULL;
  const mxArray *c2_m262 = NULL;
  uint8_T c2_c_a1;
  uint8_T c2_c_slice_temp;
  uint8_T c2_d_a;
  const mxArray *c2_m263 = NULL;
  const mxArray *c2_m264 = NULL;
  uint8_T c2_d_a1;
  uint8_T c2_d_slice_temp;
  uint8_T c2_j_hoistedGlobal;
  uint8_T c2_m_varargin_1;
  uint8_T c2_n_varargin_1;
  uint8_T c2_g_var1;
  int8_T c2_i1;
  const mxArray *c2_m265 = NULL;
  const mxArray *c2_m266 = NULL;
  const mxArray *c2_m267 = NULL;
  const mxArray *c2_m268 = NULL;
  const mxArray *c2_m269 = NULL;
  const mxArray *c2_m270 = NULL;
  const mxArray *c2_m271 = NULL;
  int16_T c2_o_varargin_1;
  int16_T c2_p_varargin_1;
  const mxArray *c2_m272 = NULL;
  const mxArray *c2_m273 = NULL;
  const mxArray *c2_m274 = NULL;
  const mxArray *c2_m275 = NULL;
  int16_T c2_h_var1;
  const mxArray *c2_m276 = NULL;
  const mxArray *c2_m277 = NULL;
  const mxArray *c2_m278 = NULL;
  const mxArray *c2_m279 = NULL;
  const mxArray *c2_m280 = NULL;
  const mxArray *c2_m281 = NULL;
  const mxArray *c2_m282 = NULL;
  const mxArray *c2_m283 = NULL;
  const mxArray *c2_m284 = NULL;
  const mxArray *c2_m285 = NULL;
  const mxArray *c2_m286 = NULL;
  const mxArray *c2_m287 = NULL;
  const mxArray *c2_m288 = NULL;
  const mxArray *c2_m289 = NULL;
  uint8_T c2_e_a;
  const mxArray *c2_m290 = NULL;
  const mxArray *c2_m291 = NULL;
  uint8_T c2_e_a1;
  uint8_T c2_e_slice_temp;
  uint8_T c2_k_hoistedGlobal;
  uint8_T c2_q_varargin_1;
  uint8_T c2_r_varargin_1;
  uint8_T c2_i_var1;
  int8_T c2_i2;
  const mxArray *c2_m292 = NULL;
  const mxArray *c2_m293 = NULL;
  const mxArray *c2_m294 = NULL;
  const mxArray *c2_m295 = NULL;
  const mxArray *c2_m296 = NULL;
  const mxArray *c2_m297 = NULL;
  const mxArray *c2_m298 = NULL;
  int16_T c2_s_varargin_1;
  int16_T c2_t_varargin_1;
  const mxArray *c2_m299 = NULL;
  const mxArray *c2_m300 = NULL;
  const mxArray *c2_m301 = NULL;
  const mxArray *c2_m302 = NULL;
  int16_T c2_j_var1;
  const mxArray *c2_m303 = NULL;
  const mxArray *c2_m304 = NULL;
  const mxArray *c2_m305 = NULL;
  const mxArray *c2_m306 = NULL;
  const mxArray *c2_m307 = NULL;
  const mxArray *c2_m308 = NULL;
  const mxArray *c2_m309 = NULL;
  const mxArray *c2_m310 = NULL;
  const mxArray *c2_m311 = NULL;
  const mxArray *c2_m312 = NULL;
  const mxArray *c2_m313 = NULL;
  const mxArray *c2_m314 = NULL;
  const mxArray *c2_m315 = NULL;
  const mxArray *c2_m316 = NULL;
  uint8_T c2_l_hoistedGlobal;
  uint8_T c2_f_a;
  const mxArray *c2_m317 = NULL;
  const mxArray *c2_m318 = NULL;
  uint8_T c2_f_a1;
  uint8_T c2_f_slice_temp;
  uint8_T c2_m_hoistedGlobal;
  uint8_T c2_g_a;
  const mxArray *c2_m319 = NULL;
  const mxArray *c2_m320 = NULL;
  uint8_T c2_g_a1;
  uint8_T c2_g_slice_temp;
  uint8_T c2_h_a;
  const mxArray *c2_m321 = NULL;
  const mxArray *c2_m322 = NULL;
  uint8_T c2_h_a1;
  uint8_T c2_h_slice_temp;
  uint8_T c2_n_hoistedGlobal;
  uint8_T c2_u_varargin_1;
  uint8_T c2_v_varargin_1;
  uint8_T c2_k_var1;
  int8_T c2_i3;
  const mxArray *c2_m323 = NULL;
  const mxArray *c2_m324 = NULL;
  const mxArray *c2_m325 = NULL;
  const mxArray *c2_m326 = NULL;
  const mxArray *c2_m327 = NULL;
  const mxArray *c2_m328 = NULL;
  const mxArray *c2_m329 = NULL;
  int16_T c2_w_varargin_1;
  int16_T c2_x_varargin_1;
  const mxArray *c2_m330 = NULL;
  const mxArray *c2_m331 = NULL;
  const mxArray *c2_m332 = NULL;
  const mxArray *c2_m333 = NULL;
  int16_T c2_l_var1;
  const mxArray *c2_m334 = NULL;
  const mxArray *c2_m335 = NULL;
  const mxArray *c2_m336 = NULL;
  const mxArray *c2_m337 = NULL;
  const mxArray *c2_m338 = NULL;
  const mxArray *c2_m339 = NULL;
  const mxArray *c2_m340 = NULL;
  const mxArray *c2_m341 = NULL;
  const mxArray *c2_m342 = NULL;
  const mxArray *c2_m343 = NULL;
  const mxArray *c2_m344 = NULL;
  const mxArray *c2_m345 = NULL;
  const mxArray *c2_m346 = NULL;
  const mxArray *c2_m347 = NULL;
  uint8_T c2_i_a;
  const mxArray *c2_m348 = NULL;
  const mxArray *c2_m349 = NULL;
  uint8_T c2_i_a1;
  uint8_T c2_i_slice_temp;
  uint8_T c2_o_hoistedGlobal;
  uint8_T c2_y_varargin_1;
  uint8_T c2_ab_varargin_1;
  uint8_T c2_m_var1;
  int8_T c2_i4;
  const mxArray *c2_m350 = NULL;
  const mxArray *c2_m351 = NULL;
  const mxArray *c2_m352 = NULL;
  const mxArray *c2_m353 = NULL;
  const mxArray *c2_m354 = NULL;
  const mxArray *c2_m355 = NULL;
  const mxArray *c2_m356 = NULL;
  int16_T c2_bb_varargin_1;
  int16_T c2_cb_varargin_1;
  const mxArray *c2_m357 = NULL;
  const mxArray *c2_m358 = NULL;
  const mxArray *c2_m359 = NULL;
  const mxArray *c2_m360 = NULL;
  int16_T c2_n_var1;
  const mxArray *c2_m361 = NULL;
  const mxArray *c2_m362 = NULL;
  const mxArray *c2_m363 = NULL;
  const mxArray *c2_m364 = NULL;
  const mxArray *c2_m365 = NULL;
  const mxArray *c2_m366 = NULL;
  const mxArray *c2_m367 = NULL;
  const mxArray *c2_m368 = NULL;
  const mxArray *c2_m369 = NULL;
  const mxArray *c2_m370 = NULL;
  const mxArray *c2_m371 = NULL;
  const mxArray *c2_m372 = NULL;
  const mxArray *c2_m373 = NULL;
  const mxArray *c2_m374 = NULL;
  const mxArray *c2_m375 = NULL;
  const mxArray *c2_m376 = NULL;
  const mxArray *c2_m377 = NULL;
  const mxArray *c2_m378 = NULL;
  const mxArray *c2_m379 = NULL;
  const mxArray *c2_m380 = NULL;
  const mxArray *c2_m381 = NULL;
  const mxArray *c2_m382 = NULL;
  const mxArray *c2_m383 = NULL;
  const mxArray *c2_m384 = NULL;
  const mxArray *c2_m385 = NULL;
  const mxArray *c2_m386 = NULL;
  const mxArray *c2_m387 = NULL;
  const mxArray *c2_m388 = NULL;
  const mxArray *c2_m389 = NULL;
  const mxArray *c2_m390 = NULL;
  const mxArray *c2_m391 = NULL;
  const mxArray *c2_m392 = NULL;
  const mxArray *c2_m393 = NULL;
  const mxArray *c2_m394 = NULL;
  const mxArray *c2_m395 = NULL;
  const mxArray *c2_m396 = NULL;
  const mxArray *c2_m397 = NULL;
  const mxArray *c2_m398 = NULL;
  const mxArray *c2_m399 = NULL;
  const mxArray *c2_m400 = NULL;
  const mxArray *c2_m401 = NULL;
  const mxArray *c2_m402 = NULL;
  const mxArray *c2_m403 = NULL;
  const mxArray *c2_m404 = NULL;
  const mxArray *c2_m405 = NULL;
  const mxArray *c2_m406 = NULL;
  const mxArray *c2_m407 = NULL;
  const mxArray *c2_m408 = NULL;
  const mxArray *c2_m409 = NULL;
  const mxArray *c2_m410 = NULL;
  const mxArray *c2_m411 = NULL;
  const mxArray *c2_m412 = NULL;
  const mxArray *c2_m413 = NULL;
  const mxArray *c2_m414 = NULL;
  const mxArray *c2_m415 = NULL;
  const mxArray *c2_m416 = NULL;
  const mxArray *c2_m417 = NULL;
  const mxArray *c2_m418 = NULL;
  const mxArray *c2_m419 = NULL;
  const mxArray *c2_m420 = NULL;
  const mxArray *c2_m421 = NULL;
  const mxArray *c2_m422 = NULL;
  const mxArray *c2_m423 = NULL;
  const mxArray *c2_m424 = NULL;
  const mxArray *c2_m425 = NULL;
  const mxArray *c2_m426 = NULL;
  const mxArray *c2_m427 = NULL;
  const mxArray *c2_m428 = NULL;
  const mxArray *c2_m429 = NULL;
  const mxArray *c2_m430 = NULL;
  const mxArray *c2_m431 = NULL;
  const mxArray *c2_m432 = NULL;
  const mxArray *c2_m433 = NULL;
  const mxArray *c2_m434 = NULL;
  const mxArray *c2_m435 = NULL;
  const mxArray *c2_m436 = NULL;
  const mxArray *c2_m437 = NULL;
  const mxArray *c2_m438 = NULL;
  const mxArray *c2_m439 = NULL;
  const mxArray *c2_m440 = NULL;
  const mxArray *c2_m441 = NULL;
  const mxArray *c2_m442 = NULL;
  const mxArray *c2_m443 = NULL;
  const mxArray *c2_m444 = NULL;
  const mxArray *c2_m445 = NULL;
  const mxArray *c2_m446 = NULL;
  const mxArray *c2_m447 = NULL;
  const mxArray *c2_m448 = NULL;
  const mxArray *c2_m449 = NULL;
  const mxArray *c2_m450 = NULL;
  const mxArray *c2_m451 = NULL;
  const mxArray *c2_m452 = NULL;
  const mxArray *c2_m453 = NULL;
  const mxArray *c2_m454 = NULL;
  const mxArray *c2_m455 = NULL;
  const mxArray *c2_m456 = NULL;
  const mxArray *c2_m457 = NULL;
  const mxArray *c2_m458 = NULL;
  const mxArray *c2_m459 = NULL;
  const mxArray *c2_m460 = NULL;
  const mxArray *c2_m461 = NULL;
  const mxArray *c2_m462 = NULL;
  const mxArray *c2_m463 = NULL;
  const mxArray *c2_m464 = NULL;
  const mxArray *c2_m465 = NULL;
  const mxArray *c2_m466 = NULL;
  const mxArray *c2_m467 = NULL;
  const mxArray *c2_m468 = NULL;
  const mxArray *c2_m469 = NULL;
  const mxArray *c2_m470 = NULL;
  const mxArray *c2_m471 = NULL;
  const mxArray *c2_m472 = NULL;
  const mxArray *c2_m473 = NULL;
  const mxArray *c2_m474 = NULL;
  const mxArray *c2_m475 = NULL;
  const mxArray *c2_m476 = NULL;
  const mxArray *c2_m477 = NULL;
  const mxArray *c2_m478 = NULL;
  const mxArray *c2_m479 = NULL;
  const mxArray *c2_m480 = NULL;
  const mxArray *c2_m481 = NULL;
  const mxArray *c2_m482 = NULL;
  const mxArray *c2_m483 = NULL;
  const mxArray *c2_m484 = NULL;
  const mxArray *c2_m485 = NULL;
  const mxArray *c2_m486 = NULL;
  const mxArray *c2_m487 = NULL;
  const mxArray *c2_m488 = NULL;
  const mxArray *c2_m489 = NULL;
  const mxArray *c2_m490 = NULL;
  const mxArray *c2_m491 = NULL;
  const mxArray *c2_m492 = NULL;
  const mxArray *c2_m493 = NULL;
  const mxArray *c2_m494 = NULL;
  const mxArray *c2_m495 = NULL;
  const mxArray *c2_m496 = NULL;
  const mxArray *c2_m497 = NULL;
  const mxArray *c2_m498 = NULL;
  const mxArray *c2_m499 = NULL;
  const mxArray *c2_m500 = NULL;
  uint8_T c2_p_hoistedGlobal;
  uint8_T c2_j_a;
  const mxArray *c2_m501 = NULL;
  const mxArray *c2_m502 = NULL;
  uint8_T c2_j_a1;
  uint8_T c2_j_slice_temp;
  const mxArray *c2_m503 = NULL;
  const mxArray *c2_m504 = NULL;
  const mxArray *c2_m505 = NULL;
  const mxArray *c2_m506 = NULL;
  const mxArray *c2_m507 = NULL;
  const mxArray *c2_m508 = NULL;
  const mxArray *c2_m509 = NULL;
  const mxArray *c2_m510 = NULL;
  const mxArray *c2_m511 = NULL;
  const mxArray *c2_m512 = NULL;
  const mxArray *c2_m513 = NULL;
  const mxArray *c2_m514 = NULL;
  const mxArray *c2_m515 = NULL;
  const mxArray *c2_m516 = NULL;
  const mxArray *c2_m517 = NULL;
  const mxArray *c2_m518 = NULL;
  const mxArray *c2_m519 = NULL;
  const mxArray *c2_m520 = NULL;
  const mxArray *c2_m521 = NULL;
  const mxArray *c2_m522 = NULL;
  const mxArray *c2_m523 = NULL;
  uint8_T c2_q_hoistedGlobal;
  uint8_T c2_k_a;
  const mxArray *c2_m524 = NULL;
  const mxArray *c2_m525 = NULL;
  uint8_T c2_k_a1;
  uint8_T c2_k_slice_temp;
  const mxArray *c2_m526 = NULL;
  const mxArray *c2_m527 = NULL;
  const mxArray *c2_m528 = NULL;
  const mxArray *c2_m529 = NULL;
  const mxArray *c2_m530 = NULL;
  const mxArray *c2_m531 = NULL;
  const mxArray *c2_m532 = NULL;
  const mxArray *c2_m533 = NULL;
  const mxArray *c2_m534 = NULL;
  const mxArray *c2_m535 = NULL;
  const mxArray *c2_m536 = NULL;
  const mxArray *c2_m537 = NULL;
  const mxArray *c2_m538 = NULL;
  const mxArray *c2_m539 = NULL;
  const mxArray *c2_m540 = NULL;
  const mxArray *c2_m541 = NULL;
  const mxArray *c2_m542 = NULL;
  const mxArray *c2_m543 = NULL;
  const mxArray *c2_m544 = NULL;
  const mxArray *c2_m545 = NULL;
  const mxArray *c2_m546 = NULL;
  uint8_T c2_r_hoistedGlobal;
  uint8_T c2_l_a;
  const mxArray *c2_m547 = NULL;
  const mxArray *c2_m548 = NULL;
  uint8_T c2_l_a1;
  uint8_T c2_l_slice_temp;
  const mxArray *c2_m549 = NULL;
  const mxArray *c2_m550 = NULL;
  const mxArray *c2_m551 = NULL;
  const mxArray *c2_m552 = NULL;
  const mxArray *c2_m553 = NULL;
  const mxArray *c2_m554 = NULL;
  const mxArray *c2_m555 = NULL;
  const mxArray *c2_m556 = NULL;
  const mxArray *c2_m557 = NULL;
  const mxArray *c2_m558 = NULL;
  const mxArray *c2_m559 = NULL;
  const mxArray *c2_m560 = NULL;
  const mxArray *c2_m561 = NULL;
  const mxArray *c2_m562 = NULL;
  const mxArray *c2_m563 = NULL;
  const mxArray *c2_m564 = NULL;
  const mxArray *c2_m565 = NULL;
  const mxArray *c2_m566 = NULL;
  const mxArray *c2_m567 = NULL;
  const mxArray *c2_m568 = NULL;
  const mxArray *c2_m569 = NULL;
  uint8_T c2_s_hoistedGlobal;
  uint8_T c2_m_a;
  const mxArray *c2_m570 = NULL;
  const mxArray *c2_m571 = NULL;
  uint8_T c2_m_a1;
  uint8_T c2_m_slice_temp;
  const mxArray *c2_m572 = NULL;
  const mxArray *c2_m573 = NULL;
  const mxArray *c2_m574 = NULL;
  const mxArray *c2_m575 = NULL;
  const mxArray *c2_m576 = NULL;
  const mxArray *c2_m577 = NULL;
  const mxArray *c2_m578 = NULL;
  int8_T *c2_b_data_in;
  uint8_T *c2_b_in_flags;
  boolean_T *c2_b_master_rst;
  uint16_T *c2_b_IR_in;
  uint8_T *c2_b_shifter_sel;
  uint8_T *c2_b_out_flags;
  uint8_T *c2_b_ALU_func;
  boolean_T *c2_b_print_data;
  uint8_T *c2_b_DM_addr;
  uint8_T *c2_b_DM_r_w;
  uint8_T *c2_b_AC_func;
  int8_T *c2_b_AC_data;
  uint8_T *c2_b_IR_func;
  uint8_T *c2_b_PC_func;
  int8_T *c2_b_addr_inc;
  uint8_T *c2_b_IM_read;
  uint8_T *c2_b_hlt;
  c2_b_hlt = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 13);
  c2_b_IM_read = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 12);
  c2_b_addr_inc = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 11);
  c2_b_PC_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 10);
  c2_b_IR_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 9);
  c2_b_AC_data = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 8);
  c2_b_AC_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 7);
  c2_b_DM_r_w = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 6);
  c2_b_DM_addr = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 5);
  c2_b_IR_in = (uint16_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c2_b_print_data = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c2_b_ALU_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c2_b_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c2_b_shifter_sel = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_master_rst = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_b_in_flags = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_data_in = (int8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_b_data_in;
  c2_b_hoistedGlobal = *c2_b_in_flags;
  c2_c_hoistedGlobal = *c2_b_master_rst;
  c2_d_hoistedGlobal = *c2_b_IR_in;
  c2_data_in = c2_hoistedGlobal;
  c2_in_flags = c2_b_hoistedGlobal;
  c2_master_rst = c2_c_hoistedGlobal;
  c2_IR_in = c2_d_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 35U, 35U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_hdl_fm, 0U, c2_t_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_mask, 1U, c2_s_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_minor_opcode_bit6, 2U,
    c2_h_sf_marshallOut, c2_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_temp_address_data, 3U,
    c2_r_sf_marshallOut, c2_p_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_indirect_bit, 4U,
    c2_h_sf_marshallOut, c2_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_c, 5U, c2_q_sf_marshallOut,
    c2_o_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_n, 6U, c2_q_sf_marshallOut,
    c2_o_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_minor_opcode_bit4, 7U,
    c2_h_sf_marshallOut, c2_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_v, 8U, c2_q_sf_marshallOut,
    c2_o_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_z, 9U, c2_q_sf_marshallOut,
    c2_o_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 10U, c2_p_sf_marshallOut,
    c2_n_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 11U, c2_p_sf_marshallOut,
    c2_n_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c2_data_in, 12U, c2_o_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_in_flags, 13U, c2_m_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_master_rst, 14U, c2_l_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_IR_in, 15U, c2_n_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_shifter_sel, 16U,
    c2_j_sf_marshallOut, c2_j_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_out_flags, 17U,
    c2_m_sf_marshallOut, c2_m_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_ALU_func, 18U,
    c2_k_sf_marshallOut, c2_k_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_print_data, 19U,
    c2_l_sf_marshallOut, c2_l_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_DM_addr, 20U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_DM_r_w, 21U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_AC_func, 22U, c2_k_sf_marshallOut,
    c2_k_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_AC_data, 23U, c2_i_sf_marshallOut,
    c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_IR_func, 24U, c2_j_sf_marshallOut,
    c2_j_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_PC_func, 25U, c2_j_sf_marshallOut,
    c2_j_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_addr_inc, 26U,
    c2_i_sf_marshallOut, c2_i_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_IM_read, 27U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_hlt, 28U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&chartInstance->c2_CPU_state, 29U,
    c2_f_sf_marshallOut, c2_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&chartInstance->c2_previous_CPU_state,
    30U, c2_e_sf_marshallOut, c2_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&chartInstance->c2_major_opcode, 31U,
    c2_d_sf_marshallOut, c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&chartInstance->c2_minor_opcode, 32U,
    c2_c_sf_marshallOut, c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&chartInstance->c2_address_data, 33U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&chartInstance->c2_indirect_address,
    34U, c2_sf_marshallOut, c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 63);
  c2_hdl_fm = c2_eml_mx;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 72);
  if (CV_EML_IF(0, 0, !chartInstance->c2_CPU_state_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 73);
    chartInstance->c2_CPU_state = 0U;
    chartInstance->c2_CPU_state_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 77);
  if (CV_EML_IF(0, 1, !chartInstance->c2_previous_CPU_state_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 78);
    chartInstance->c2_previous_CPU_state = 0U;
    chartInstance->c2_previous_CPU_state_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 81);
  if (CV_EML_IF(0, 2, c2_master_rst)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 82);
    chartInstance->c2_CPU_state = 0U;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 85);
  sf_mex_destroy(&c2_m0);
  sf_mex_destroy(&c2_m1);
  sf_mex_destroy(&c2_m2);
  sf_mex_destroy(&c2_m3);
  sf_mex_destroy(&c2_m4);
  sf_mex_destroy(&c2_m5);
  sf_mex_destroy(&c2_m6);
  c2_shifter_sel = 0U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 86);
  sf_mex_destroy(&c2_m7);
  sf_mex_destroy(&c2_m8);
  sf_mex_destroy(&c2_m9);
  sf_mex_destroy(&c2_m10);
  sf_mex_destroy(&c2_m11);
  sf_mex_destroy(&c2_m12);
  sf_mex_destroy(&c2_m13);
  c2_ALU_func = 0U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 87);
  c2_out_flags = c2_in_flags;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 88);
  sf_mex_destroy(&c2_m14);
  sf_mex_destroy(&c2_m15);
  sf_mex_destroy(&c2_m16);
  sf_mex_destroy(&c2_m17);
  sf_mex_destroy(&c2_m18);
  sf_mex_destroy(&c2_m19);
  sf_mex_destroy(&c2_m20);
  c2_AC_func = 4U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 89);
  sf_mex_destroy(&c2_m21);
  sf_mex_destroy(&c2_m22);
  sf_mex_destroy(&c2_m23);
  sf_mex_destroy(&c2_m24);
  sf_mex_destroy(&c2_m25);
  sf_mex_destroy(&c2_m26);
  sf_mex_destroy(&c2_m27);
  c2_AC_data = 0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 90);
  sf_mex_destroy(&c2_m28);
  sf_mex_destroy(&c2_m29);
  sf_mex_destroy(&c2_m30);
  sf_mex_destroy(&c2_m31);
  sf_mex_destroy(&c2_m32);
  sf_mex_destroy(&c2_m33);
  sf_mex_destroy(&c2_m34);
  c2_IR_func = 3U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 91);
  sf_mex_destroy(&c2_m35);
  sf_mex_destroy(&c2_m36);
  sf_mex_destroy(&c2_m37);
  sf_mex_destroy(&c2_m38);
  sf_mex_destroy(&c2_m39);
  sf_mex_destroy(&c2_m40);
  sf_mex_destroy(&c2_m41);
  c2_PC_func = 3U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 92);
  sf_mex_destroy(&c2_m42);
  sf_mex_destroy(&c2_m43);
  sf_mex_destroy(&c2_m44);
  sf_mex_destroy(&c2_m45);
  sf_mex_destroy(&c2_m46);
  sf_mex_destroy(&c2_m47);
  sf_mex_destroy(&c2_m48);
  c2_IM_read = 0U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 93);
  c2_DM_addr = 0U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 94);
  sf_mex_destroy(&c2_m49);
  sf_mex_destroy(&c2_m50);
  sf_mex_destroy(&c2_m51);
  sf_mex_destroy(&c2_m52);
  sf_mex_destroy(&c2_m53);
  sf_mex_destroy(&c2_m54);
  sf_mex_destroy(&c2_m55);
  c2_DM_r_w = 0U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 95);
  sf_mex_destroy(&c2_m56);
  sf_mex_destroy(&c2_m57);
  sf_mex_destroy(&c2_m58);
  sf_mex_destroy(&c2_m59);
  sf_mex_destroy(&c2_m60);
  sf_mex_destroy(&c2_m61);
  sf_mex_destroy(&c2_m62);
  c2_addr_inc = 0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 96);
  c2_print_data = FALSE;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 97);
  c2_hlt = 0U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 110);
  if (CV_EML_IF(0, 3, !chartInstance->c2_major_opcode_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 111);
    sf_mex_destroy(&c2_m63);
    sf_mex_destroy(&c2_m64);
    sf_mex_destroy(&c2_m65);
    sf_mex_destroy(&c2_m66);
    sf_mex_destroy(&c2_m67);
    sf_mex_destroy(&c2_m68);
    sf_mex_destroy(&c2_m69);
    chartInstance->c2_major_opcode = 0U;
    chartInstance->c2_major_opcode_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 112);
    sf_mex_destroy(&c2_m70);
    sf_mex_destroy(&c2_m71);
    sf_mex_destroy(&c2_m72);
    sf_mex_destroy(&c2_m73);
    sf_mex_destroy(&c2_m74);
    sf_mex_destroy(&c2_m75);
    sf_mex_destroy(&c2_m76);
    chartInstance->c2_minor_opcode = 0U;
    chartInstance->c2_minor_opcode_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 113);
    sf_mex_destroy(&c2_m77);
    sf_mex_destroy(&c2_m78);
    sf_mex_destroy(&c2_m79);
    sf_mex_destroy(&c2_m80);
    sf_mex_destroy(&c2_m81);
    sf_mex_destroy(&c2_m82);
    sf_mex_destroy(&c2_m83);
    chartInstance->c2_address_data = 0U;
    chartInstance->c2_address_data_not_empty = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 114);
    chartInstance->c2_indirect_address = 0U;
    chartInstance->c2_indirect_address_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 117);
  switch (chartInstance->c2_CPU_state) {
   case 0U:
    CV_EML_SWITCH(0, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 122);
    sf_mex_destroy(&c2_m84);
    sf_mex_destroy(&c2_m85);
    sf_mex_destroy(&c2_m86);
    sf_mex_destroy(&c2_m87);
    sf_mex_destroy(&c2_m88);
    sf_mex_destroy(&c2_m89);
    sf_mex_destroy(&c2_m90);
    c2_PC_func = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 123);
    sf_mex_destroy(&c2_m91);
    sf_mex_destroy(&c2_m92);
    sf_mex_destroy(&c2_m93);
    sf_mex_destroy(&c2_m94);
    sf_mex_destroy(&c2_m95);
    sf_mex_destroy(&c2_m96);
    sf_mex_destroy(&c2_m97);
    c2_AC_func = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 124);
    sf_mex_destroy(&c2_m98);
    sf_mex_destroy(&c2_m99);
    sf_mex_destroy(&c2_m100);
    sf_mex_destroy(&c2_m101);
    sf_mex_destroy(&c2_m102);
    sf_mex_destroy(&c2_m103);
    sf_mex_destroy(&c2_m104);
    c2_IR_func = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 125);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 126);
    chartInstance->c2_CPU_state = 1U;
    break;

   case 1U:
    CV_EML_SWITCH(0, 0, 2);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 133U);
    sf_mex_destroy(&c2_m105);
    sf_mex_destroy(&c2_m106);
    sf_mex_destroy(&c2_m107);
    sf_mex_destroy(&c2_m108);
    sf_mex_destroy(&c2_m109);
    sf_mex_destroy(&c2_m110);
    sf_mex_destroy(&c2_m111);
    c2_IM_read = 1U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 135U);
    sf_mex_destroy(&c2_m112);
    sf_mex_destroy(&c2_m113);
    sf_mex_destroy(&c2_m114);
    sf_mex_destroy(&c2_m115);
    sf_mex_destroy(&c2_m116);
    sf_mex_destroy(&c2_m117);
    sf_mex_destroy(&c2_m118);
    c2_PC_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 137U);
    sf_mex_destroy(&c2_m119);
    sf_mex_destroy(&c2_m120);
    sf_mex_destroy(&c2_m121);
    sf_mex_destroy(&c2_m122);
    sf_mex_destroy(&c2_m123);
    sf_mex_destroy(&c2_m124);
    sf_mex_destroy(&c2_m125);
    c2_IR_func = 1U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 139U);
    chartInstance->c2_CPU_state = 2U;
    break;

   case 2U:
    CV_EML_SWITCH(0, 0, 3);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 143U);
    sf_mex_destroy(&c2_m126);
    sf_mex_destroy(&c2_m127);
    sf_mex_destroy(&c2_m128);
    sf_mex_destroy(&c2_m129);
    sf_mex_destroy(&c2_m130);
    sf_mex_destroy(&c2_m131);
    sf_mex_destroy(&c2_m132);
    c2_IR_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 146U);
    chartInstance->c2_CPU_state = 3U;
    break;

   case 3U:
    CV_EML_SWITCH(0, 0, 4);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 150U);
    c2_varargin_1 = c2_bitsrl(chartInstance, c2_IR_in);
    c2_b_varargin_1 = c2_varargin_1;
    c2_b_isfloat(chartInstance);
    c2_var1 = c2_b_varargin_1;
    c2_hfi = (uint8_T)c2_var1;
    sf_mex_destroy(&c2_m133);
    sf_mex_destroy(&c2_m134);
    sf_mex_destroy(&c2_m135);
    sf_mex_destroy(&c2_m136);
    sf_mex_destroy(&c2_m137);
    sf_mex_destroy(&c2_m138);
    sf_mex_destroy(&c2_m139);
    chartInstance->c2_major_opcode = c2_hfi;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 151U);
    sf_mex_destroy(&c2_m140);
    sf_mex_destroy(&c2_m141);
    sf_mex_destroy(&c2_m142);
    sf_mex_destroy(&c2_m143);
    sf_mex_destroy(&c2_m144);
    sf_mex_destroy(&c2_m145);
    sf_mex_destroy(&c2_m146);
    c2_mask = 63U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 153U);
    c2_c_varargin_1 = c2_bitand(chartInstance, c2_b_bitsrl(chartInstance,
      c2_IR_in), 63U);
    c2_d_varargin_1 = c2_c_varargin_1;
    sf_mex_destroy(&c2_m147);
    sf_mex_destroy(&c2_m148);
    sf_mex_destroy(&c2_m149);
    sf_mex_destroy(&c2_m150);
    c2_b_var1 = c2_d_varargin_1;
    c2_b_hfi = (uint8_T)c2_b_var1;
    sf_mex_destroy(&c2_m151);
    sf_mex_destroy(&c2_m152);
    sf_mex_destroy(&c2_m153);
    sf_mex_destroy(&c2_m154);
    sf_mex_destroy(&c2_m155);
    sf_mex_destroy(&c2_m156);
    sf_mex_destroy(&c2_m157);
    chartInstance->c2_minor_opcode = c2_b_hfi;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 154U);
    sf_mex_destroy(&c2_m158);
    sf_mex_destroy(&c2_m159);
    sf_mex_destroy(&c2_m160);
    sf_mex_destroy(&c2_m161);
    sf_mex_destroy(&c2_m162);
    sf_mex_destroy(&c2_m163);
    sf_mex_destroy(&c2_m164);
    c2_mask = 255U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 156U);
    c2_e_varargin_1 = c2_bitand(chartInstance, c2_IR_in, 255U);
    c2_f_varargin_1 = c2_e_varargin_1;
    sf_mex_destroy(&c2_m165);
    sf_mex_destroy(&c2_m166);
    sf_mex_destroy(&c2_m167);
    sf_mex_destroy(&c2_m168);
    c2_c_var1 = c2_f_varargin_1;
    c2_c_hfi = (uint8_T)c2_c_var1;
    sf_mex_destroy(&c2_m169);
    sf_mex_destroy(&c2_m170);
    sf_mex_destroy(&c2_m171);
    sf_mex_destroy(&c2_m172);
    sf_mex_destroy(&c2_m173);
    sf_mex_destroy(&c2_m174);
    sf_mex_destroy(&c2_m175);
    chartInstance->c2_address_data = c2_c_hfi;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 159U);
    chartInstance->c2_CPU_state = 4U;
    break;

   case 4U:
    CV_EML_SWITCH(0, 0, 5);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 165U);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 166U);
    switch (c2_b_uint8(chartInstance, chartInstance->c2_major_opcode)) {
     case 0U:
      CV_EML_SWITCH(0, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 170U);
      c2_DM_addr = c2_b_uint8(chartInstance, chartInstance->c2_address_data);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 172U);
      sf_mex_destroy(&c2_m176);
      sf_mex_destroy(&c2_m177);
      sf_mex_destroy(&c2_m178);
      sf_mex_destroy(&c2_m179);
      sf_mex_destroy(&c2_m180);
      sf_mex_destroy(&c2_m181);
      sf_mex_destroy(&c2_m182);
      c2_DM_r_w = 0U;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 174U);
      chartInstance->c2_CPU_state = 13U;
      break;

     case 1U:
      CV_EML_SWITCH(0, 1, 2);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 178U);
      c2_DM_addr = c2_b_uint8(chartInstance, chartInstance->c2_address_data);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 180U);
      sf_mex_destroy(&c2_m183);
      sf_mex_destroy(&c2_m184);
      sf_mex_destroy(&c2_m185);
      sf_mex_destroy(&c2_m186);
      sf_mex_destroy(&c2_m187);
      sf_mex_destroy(&c2_m188);
      sf_mex_destroy(&c2_m189);
      c2_DM_r_w = 0U;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 182U);
      chartInstance->c2_CPU_state = 15U;
      break;

     case 2U:
      CV_EML_SWITCH(0, 1, 3);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 186U);
      c2_DM_addr = c2_b_uint8(chartInstance, chartInstance->c2_address_data);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 188U);
      sf_mex_destroy(&c2_m190);
      sf_mex_destroy(&c2_m191);
      sf_mex_destroy(&c2_m192);
      sf_mex_destroy(&c2_m193);
      sf_mex_destroy(&c2_m194);
      sf_mex_destroy(&c2_m195);
      sf_mex_destroy(&c2_m196);
      c2_DM_r_w = 0U;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 190U);
      chartInstance->c2_CPU_state = 17U;
      break;

     case 3U:
      CV_EML_SWITCH(0, 1, 4);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 194U);
      c2_DM_addr = c2_b_uint8(chartInstance, chartInstance->c2_address_data);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 196U);
      sf_mex_destroy(&c2_m197);
      sf_mex_destroy(&c2_m198);
      sf_mex_destroy(&c2_m199);
      sf_mex_destroy(&c2_m200);
      sf_mex_destroy(&c2_m201);
      sf_mex_destroy(&c2_m202);
      sf_mex_destroy(&c2_m203);
      c2_DM_r_w = 0U;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 198U);
      chartInstance->c2_CPU_state = 19U;
      break;

     case 4U:
      CV_EML_SWITCH(0, 1, 5);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 201U);
      c2_e_hoistedGlobal = chartInstance->c2_minor_opcode;
      c2_a = c2_e_hoistedGlobal;
      sf_mex_destroy(&c2_m204);
      sf_mex_destroy(&c2_m205);
      c2_minor_opcode_bit6 = 0U;
      c2_a1 = c2_a;
      c2_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_a1 >> 5) & 1U);
      c2_minor_opcode_bit6 = c2_slice_temp;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 202U);
      switch (c2_c_uint8(chartInstance, c2_minor_opcode_bit6)) {
       case 0U:
        CV_EML_SWITCH(0, 2, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 205U);
        c2_f_hoistedGlobal = chartInstance->c2_address_data;
        c2_g_varargin_1 = c2_f_hoistedGlobal;
        c2_h_varargin_1 = c2_g_varargin_1;
        c2_isfloat(chartInstance);
        c2_d_var1 = c2_h_varargin_1;
        c2_i0 = (int8_T)c2_d_var1;
        c2_temp_address_data = (int8_T)(c2_i0 & 64) != 0 ? (int8_T)(c2_i0 | -64)
          : (int8_T)(c2_i0 & 63);
        sf_mex_destroy(&c2_m206);
        sf_mex_destroy(&c2_m207);
        sf_mex_destroy(&c2_m208);
        sf_mex_destroy(&c2_m209);
        sf_mex_destroy(&c2_m210);
        sf_mex_destroy(&c2_m211);
        sf_mex_destroy(&c2_m212);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 206U);
        c2_i_varargin_1 = c2_minus(chartInstance, c2_temp_address_data);
        c2_j_varargin_1 = c2_i_varargin_1;
        sf_mex_destroy(&c2_m213);
        sf_mex_destroy(&c2_m214);
        sf_mex_destroy(&c2_m215);
        sf_mex_destroy(&c2_m216);
        c2_e_var1 = c2_j_varargin_1;
        c2_addr_inc = (int8_T)(int16_T)(c2_e_var1 >> 5);
        sf_mex_destroy(&c2_m217);
        sf_mex_destroy(&c2_m218);
        sf_mex_destroy(&c2_m219);
        sf_mex_destroy(&c2_m220);
        sf_mex_destroy(&c2_m221);
        sf_mex_destroy(&c2_m222);
        sf_mex_destroy(&c2_m223);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 207U);
        sf_mex_destroy(&c2_m224);
        sf_mex_destroy(&c2_m225);
        sf_mex_destroy(&c2_m226);
        sf_mex_destroy(&c2_m227);
        sf_mex_destroy(&c2_m228);
        sf_mex_destroy(&c2_m229);
        sf_mex_destroy(&c2_m230);
        c2_PC_func = 1U;
        break;

       case 1U:
        CV_EML_SWITCH(0, 2, 2);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 211U);
        c2_g_hoistedGlobal = chartInstance->c2_address_data;
        c2_k_varargin_1 = c2_g_hoistedGlobal;
        c2_l_varargin_1 = c2_k_varargin_1;
        c2_isfloat(chartInstance);
        c2_f_var1 = c2_l_varargin_1;
        c2_AC_data = (int8_T)c2_f_var1;
        sf_mex_destroy(&c2_m231);
        sf_mex_destroy(&c2_m232);
        sf_mex_destroy(&c2_m233);
        sf_mex_destroy(&c2_m234);
        sf_mex_destroy(&c2_m235);
        sf_mex_destroy(&c2_m236);
        sf_mex_destroy(&c2_m237);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 212U);
        sf_mex_destroy(&c2_m238);
        sf_mex_destroy(&c2_m239);
        sf_mex_destroy(&c2_m240);
        sf_mex_destroy(&c2_m241);
        sf_mex_destroy(&c2_m242);
        sf_mex_destroy(&c2_m243);
        sf_mex_destroy(&c2_m244);
        c2_AC_func = 1U;
        break;

       default:
        CV_EML_SWITCH(0, 2, 0);
        break;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 215U);
      chartInstance->c2_CPU_state = 1U;
      break;

     case 5U:
      CV_EML_SWITCH(0, 1, 6);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 220U);
      c2_DM_addr = c2_b_uint8(chartInstance, chartInstance->c2_address_data);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 221U);
      c2_h_hoistedGlobal = chartInstance->c2_minor_opcode;
      c2_b_a = c2_h_hoistedGlobal;
      sf_mex_destroy(&c2_m245);
      sf_mex_destroy(&c2_m246);
      c2_indirect_bit = 0U;
      c2_b_a1 = c2_b_a;
      c2_b_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_b_a1 >> 5) & 1U);
      c2_indirect_bit = c2_b_slice_temp;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 222U);
      if (CV_EML_IF(0, 4, c2_logical(chartInstance, c2_indirect_bit))) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 225U);
        sf_mex_destroy(&c2_m247);
        sf_mex_destroy(&c2_m248);
        sf_mex_destroy(&c2_m249);
        sf_mex_destroy(&c2_m250);
        sf_mex_destroy(&c2_m251);
        sf_mex_destroy(&c2_m252);
        sf_mex_destroy(&c2_m253);
        c2_DM_r_w = 0U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 226U);
        chartInstance->c2_CPU_state = 21U;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 229U);
        sf_mex_destroy(&c2_m254);
        sf_mex_destroy(&c2_m255);
        sf_mex_destroy(&c2_m256);
        sf_mex_destroy(&c2_m257);
        sf_mex_destroy(&c2_m258);
        sf_mex_destroy(&c2_m259);
        sf_mex_destroy(&c2_m260);
        c2_DM_r_w = 1U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 231U);
        chartInstance->c2_CPU_state = 25U;
      }
      break;

     case 6U:
      CV_EML_SWITCH(0, 1, 7);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 235U);
      c2_i_hoistedGlobal = chartInstance->c2_minor_opcode;
      c2_c_a = c2_i_hoistedGlobal;
      sf_mex_destroy(&c2_m261);
      sf_mex_destroy(&c2_m262);
      c2_minor_opcode_bit6 = 0U;
      c2_c_a1 = c2_c_a;
      c2_c_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_c_a1 >> 5) & 1U);
      c2_minor_opcode_bit6 = c2_c_slice_temp;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 236U);
      switch (c2_c_uint8(chartInstance, c2_minor_opcode_bit6)) {
       case 0U:
        CV_EML_SWITCH(0, 3, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 240U);
        c2_d_a = c2_in_flags;
        sf_mex_destroy(&c2_m263);
        sf_mex_destroy(&c2_m264);
        c2_c = 0U;
        c2_d_a1 = c2_d_a;
        c2_d_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_d_a1 >> 3) & 1U);
        c2_c = c2_d_slice_temp;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 241U);
        if (CV_EML_IF(0, 5, c2_b_logical(chartInstance, c2_c))) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 242U);
          c2_j_hoistedGlobal = chartInstance->c2_address_data;
          c2_m_varargin_1 = c2_j_hoistedGlobal;
          c2_n_varargin_1 = c2_m_varargin_1;
          c2_isfloat(chartInstance);
          c2_g_var1 = c2_n_varargin_1;
          c2_i1 = (int8_T)c2_g_var1;
          c2_temp_address_data = (int8_T)(c2_i1 & 64) != 0 ? (int8_T)(c2_i1 |
            -64) : (int8_T)(c2_i1 & 63);
          sf_mex_destroy(&c2_m265);
          sf_mex_destroy(&c2_m266);
          sf_mex_destroy(&c2_m267);
          sf_mex_destroy(&c2_m268);
          sf_mex_destroy(&c2_m269);
          sf_mex_destroy(&c2_m270);
          sf_mex_destroy(&c2_m271);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 243U);
          c2_o_varargin_1 = c2_minus(chartInstance, c2_temp_address_data);
          c2_p_varargin_1 = c2_o_varargin_1;
          sf_mex_destroy(&c2_m272);
          sf_mex_destroy(&c2_m273);
          sf_mex_destroy(&c2_m274);
          sf_mex_destroy(&c2_m275);
          c2_h_var1 = c2_p_varargin_1;
          c2_addr_inc = (int8_T)(int16_T)(c2_h_var1 >> 5);
          sf_mex_destroy(&c2_m276);
          sf_mex_destroy(&c2_m277);
          sf_mex_destroy(&c2_m278);
          sf_mex_destroy(&c2_m279);
          sf_mex_destroy(&c2_m280);
          sf_mex_destroy(&c2_m281);
          sf_mex_destroy(&c2_m282);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 244U);
          sf_mex_destroy(&c2_m283);
          sf_mex_destroy(&c2_m284);
          sf_mex_destroy(&c2_m285);
          sf_mex_destroy(&c2_m286);
          sf_mex_destroy(&c2_m287);
          sf_mex_destroy(&c2_m288);
          sf_mex_destroy(&c2_m289);
          c2_PC_func = 1U;
        }
        break;

       case 1U:
        CV_EML_SWITCH(0, 3, 2);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 249U);
        c2_e_a = c2_in_flags;
        sf_mex_destroy(&c2_m290);
        sf_mex_destroy(&c2_m291);
        c2_n = 0U;
        c2_e_a1 = c2_e_a;
        c2_e_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_e_a1 >> 2) & 1U);
        c2_n = c2_e_slice_temp;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 250U);
        if (CV_EML_IF(0, 6, c2_b_logical(chartInstance, c2_n))) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 251U);
          c2_k_hoistedGlobal = chartInstance->c2_address_data;
          c2_q_varargin_1 = c2_k_hoistedGlobal;
          c2_r_varargin_1 = c2_q_varargin_1;
          c2_isfloat(chartInstance);
          c2_i_var1 = c2_r_varargin_1;
          c2_i2 = (int8_T)c2_i_var1;
          c2_temp_address_data = (int8_T)(c2_i2 & 64) != 0 ? (int8_T)(c2_i2 |
            -64) : (int8_T)(c2_i2 & 63);
          sf_mex_destroy(&c2_m292);
          sf_mex_destroy(&c2_m293);
          sf_mex_destroy(&c2_m294);
          sf_mex_destroy(&c2_m295);
          sf_mex_destroy(&c2_m296);
          sf_mex_destroy(&c2_m297);
          sf_mex_destroy(&c2_m298);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 252U);
          c2_s_varargin_1 = c2_minus(chartInstance, c2_temp_address_data);
          c2_t_varargin_1 = c2_s_varargin_1;
          sf_mex_destroy(&c2_m299);
          sf_mex_destroy(&c2_m300);
          sf_mex_destroy(&c2_m301);
          sf_mex_destroy(&c2_m302);
          c2_j_var1 = c2_t_varargin_1;
          c2_addr_inc = (int8_T)(int16_T)(c2_j_var1 >> 5);
          sf_mex_destroy(&c2_m303);
          sf_mex_destroy(&c2_m304);
          sf_mex_destroy(&c2_m305);
          sf_mex_destroy(&c2_m306);
          sf_mex_destroy(&c2_m307);
          sf_mex_destroy(&c2_m308);
          sf_mex_destroy(&c2_m309);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 253U);
          sf_mex_destroy(&c2_m310);
          sf_mex_destroy(&c2_m311);
          sf_mex_destroy(&c2_m312);
          sf_mex_destroy(&c2_m313);
          sf_mex_destroy(&c2_m314);
          sf_mex_destroy(&c2_m315);
          sf_mex_destroy(&c2_m316);
          c2_PC_func = 1U;
        }
        break;

       default:
        CV_EML_SWITCH(0, 3, 0);
        break;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 257);
      chartInstance->c2_CPU_state = 15U;
      break;

     case 7U:
      CV_EML_SWITCH(0, 1, 8);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 261);
      chartInstance->c2_CPU_state = 1U;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 262);
      c2_l_hoistedGlobal = chartInstance->c2_minor_opcode;
      c2_f_a = c2_l_hoistedGlobal;
      sf_mex_destroy(&c2_m317);
      sf_mex_destroy(&c2_m318);
      c2_minor_opcode_bit4 = 0U;
      c2_f_a1 = c2_f_a;
      c2_f_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_f_a1 >> 3) & 1U);
      c2_minor_opcode_bit4 = c2_f_slice_temp;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 263);
      if (CV_EML_IF(0, 7, (real_T)c2_logical(chartInstance, c2_minor_opcode_bit4)
                    == 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 265);
        c2_m_hoistedGlobal = chartInstance->c2_minor_opcode;
        c2_g_a = c2_m_hoistedGlobal;
        sf_mex_destroy(&c2_m319);
        sf_mex_destroy(&c2_m320);
        c2_minor_opcode_bit6 = 0U;
        c2_g_a1 = c2_g_a;
        c2_g_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_g_a1 >> 5) & 1U);
        c2_minor_opcode_bit6 = c2_g_slice_temp;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 266);
        switch (c2_c_uint8(chartInstance, c2_minor_opcode_bit6)) {
         case 0U:
          CV_EML_SWITCH(0, 4, 1);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 269);
          c2_h_a = c2_in_flags;
          sf_mex_destroy(&c2_m321);
          sf_mex_destroy(&c2_m322);
          c2_v = 0U;
          c2_h_a1 = c2_h_a;
          c2_h_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_h_a1 >> 1) & 1U);
          c2_v = c2_h_slice_temp;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 270);
          if (CV_EML_IF(0, 8, c2_b_logical(chartInstance, c2_v))) {
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 271);
            c2_n_hoistedGlobal = chartInstance->c2_address_data;
            c2_u_varargin_1 = c2_n_hoistedGlobal;
            c2_v_varargin_1 = c2_u_varargin_1;
            c2_isfloat(chartInstance);
            c2_k_var1 = c2_v_varargin_1;
            c2_i3 = (int8_T)c2_k_var1;
            c2_temp_address_data = (int8_T)(c2_i3 & 64) != 0 ? (int8_T)(c2_i3 |
              -64) : (int8_T)(c2_i3 & 63);
            sf_mex_destroy(&c2_m323);
            sf_mex_destroy(&c2_m324);
            sf_mex_destroy(&c2_m325);
            sf_mex_destroy(&c2_m326);
            sf_mex_destroy(&c2_m327);
            sf_mex_destroy(&c2_m328);
            sf_mex_destroy(&c2_m329);
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 272);
            c2_w_varargin_1 = c2_minus(chartInstance, c2_temp_address_data);
            c2_x_varargin_1 = c2_w_varargin_1;
            sf_mex_destroy(&c2_m330);
            sf_mex_destroy(&c2_m331);
            sf_mex_destroy(&c2_m332);
            sf_mex_destroy(&c2_m333);
            c2_l_var1 = c2_x_varargin_1;
            c2_addr_inc = (int8_T)(int16_T)(c2_l_var1 >> 5);
            sf_mex_destroy(&c2_m334);
            sf_mex_destroy(&c2_m335);
            sf_mex_destroy(&c2_m336);
            sf_mex_destroy(&c2_m337);
            sf_mex_destroy(&c2_m338);
            sf_mex_destroy(&c2_m339);
            sf_mex_destroy(&c2_m340);
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 273);
            sf_mex_destroy(&c2_m341);
            sf_mex_destroy(&c2_m342);
            sf_mex_destroy(&c2_m343);
            sf_mex_destroy(&c2_m344);
            sf_mex_destroy(&c2_m345);
            sf_mex_destroy(&c2_m346);
            sf_mex_destroy(&c2_m347);
            c2_PC_func = 1U;
          }
          break;

         case 1U:
          CV_EML_SWITCH(0, 4, 2);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 278);
          c2_i_a = c2_in_flags;
          sf_mex_destroy(&c2_m348);
          sf_mex_destroy(&c2_m349);
          c2_z = 0U;
          c2_i_a1 = c2_i_a;
          c2_i_slice_temp = (uint8_T)(c2_i_a1 & 1U);
          c2_z = c2_i_slice_temp;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 279);
          if (CV_EML_IF(0, 9, c2_b_logical(chartInstance, c2_z))) {
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 280);
            c2_o_hoistedGlobal = chartInstance->c2_address_data;
            c2_y_varargin_1 = c2_o_hoistedGlobal;
            c2_ab_varargin_1 = c2_y_varargin_1;
            c2_isfloat(chartInstance);
            c2_m_var1 = c2_ab_varargin_1;
            c2_i4 = (int8_T)c2_m_var1;
            c2_temp_address_data = (int8_T)(c2_i4 & 64) != 0 ? (int8_T)(c2_i4 |
              -64) : (int8_T)(c2_i4 & 63);
            sf_mex_destroy(&c2_m350);
            sf_mex_destroy(&c2_m351);
            sf_mex_destroy(&c2_m352);
            sf_mex_destroy(&c2_m353);
            sf_mex_destroy(&c2_m354);
            sf_mex_destroy(&c2_m355);
            sf_mex_destroy(&c2_m356);
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 281);
            c2_bb_varargin_1 = c2_minus(chartInstance, c2_temp_address_data);
            c2_cb_varargin_1 = c2_bb_varargin_1;
            sf_mex_destroy(&c2_m357);
            sf_mex_destroy(&c2_m358);
            sf_mex_destroy(&c2_m359);
            sf_mex_destroy(&c2_m360);
            c2_n_var1 = c2_cb_varargin_1;
            c2_addr_inc = (int8_T)(int16_T)(c2_n_var1 >> 5);
            sf_mex_destroy(&c2_m361);
            sf_mex_destroy(&c2_m362);
            sf_mex_destroy(&c2_m363);
            sf_mex_destroy(&c2_m364);
            sf_mex_destroy(&c2_m365);
            sf_mex_destroy(&c2_m366);
            sf_mex_destroy(&c2_m367);
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 282);
            sf_mex_destroy(&c2_m368);
            sf_mex_destroy(&c2_m369);
            sf_mex_destroy(&c2_m370);
            sf_mex_destroy(&c2_m371);
            sf_mex_destroy(&c2_m372);
            sf_mex_destroy(&c2_m373);
            sf_mex_destroy(&c2_m374);
            c2_PC_func = 1U;
          }
          break;

         default:
          CV_EML_SWITCH(0, 4, 0);
          break;
        }
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 287);
      switch (c2_b_uint8(chartInstance, chartInstance->c2_minor_opcode)) {
       case 8U:
        CV_EML_SWITCH(0, 5, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 291);
        c2_hlt = 1U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 292);
        chartInstance->c2_CPU_state = 22U;
        break;

       case 9U:
        CV_EML_SWITCH(0, 5, 2);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 295);
        sf_mex_destroy(&c2_m375);
        sf_mex_destroy(&c2_m376);
        sf_mex_destroy(&c2_m377);
        sf_mex_destroy(&c2_m378);
        sf_mex_destroy(&c2_m379);
        sf_mex_destroy(&c2_m380);
        sf_mex_destroy(&c2_m381);
        c2_AC_func = 0U;
        break;

       case 10U:
        CV_EML_SWITCH(0, 5, 3);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 299);
        sf_mex_destroy(&c2_m382);
        sf_mex_destroy(&c2_m383);
        sf_mex_destroy(&c2_m384);
        sf_mex_destroy(&c2_m385);
        sf_mex_destroy(&c2_m386);
        sf_mex_destroy(&c2_m387);
        sf_mex_destroy(&c2_m388);
        c2_ALU_func = 4U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 300);
        sf_mex_destroy(&c2_m389);
        sf_mex_destroy(&c2_m390);
        sf_mex_destroy(&c2_m391);
        sf_mex_destroy(&c2_m392);
        sf_mex_destroy(&c2_m393);
        sf_mex_destroy(&c2_m394);
        sf_mex_destroy(&c2_m395);
        c2_shifter_sel = 3U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 301);
        chartInstance->c2_CPU_state = 6U;
        break;

       case 11U:
        CV_EML_SWITCH(0, 5, 4);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 305);
        sf_mex_destroy(&c2_m396);
        sf_mex_destroy(&c2_m397);
        sf_mex_destroy(&c2_m398);
        sf_mex_destroy(&c2_m399);
        sf_mex_destroy(&c2_m400);
        sf_mex_destroy(&c2_m401);
        sf_mex_destroy(&c2_m402);
        c2_ALU_func = 5U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 306);
        sf_mex_destroy(&c2_m403);
        sf_mex_destroy(&c2_m404);
        sf_mex_destroy(&c2_m405);
        sf_mex_destroy(&c2_m406);
        sf_mex_destroy(&c2_m407);
        sf_mex_destroy(&c2_m408);
        sf_mex_destroy(&c2_m409);
        c2_shifter_sel = 3U;
        break;

       case 12U:
        CV_EML_SWITCH(0, 5, 5);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 310);
        sf_mex_destroy(&c2_m410);
        sf_mex_destroy(&c2_m411);
        sf_mex_destroy(&c2_m412);
        sf_mex_destroy(&c2_m413);
        sf_mex_destroy(&c2_m414);
        sf_mex_destroy(&c2_m415);
        sf_mex_destroy(&c2_m416);
        c2_shifter_sel = 1U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 311);
        chartInstance->c2_CPU_state = 6U;
        break;

       case 13U:
        CV_EML_SWITCH(0, 5, 6);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 315);
        sf_mex_destroy(&c2_m417);
        sf_mex_destroy(&c2_m418);
        sf_mex_destroy(&c2_m419);
        sf_mex_destroy(&c2_m420);
        sf_mex_destroy(&c2_m421);
        sf_mex_destroy(&c2_m422);
        sf_mex_destroy(&c2_m423);
        c2_shifter_sel = 2U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 316);
        chartInstance->c2_CPU_state = 6U;
        break;

       case 14U:
        CV_EML_SWITCH(0, 5, 7);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 320);
        c2_DM_addr = MAX_uint8_T;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 322);
        sf_mex_destroy(&c2_m424);
        sf_mex_destroy(&c2_m425);
        sf_mex_destroy(&c2_m426);
        sf_mex_destroy(&c2_m427);
        sf_mex_destroy(&c2_m428);
        sf_mex_destroy(&c2_m429);
        sf_mex_destroy(&c2_m430);
        c2_DM_r_w = 0U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 324);
        chartInstance->c2_CPU_state = 12U;
        break;

       case 15U:
        CV_EML_SWITCH(0, 5, 8);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 328);
        sf_mex_destroy(&c2_m431);
        sf_mex_destroy(&c2_m432);
        sf_mex_destroy(&c2_m433);
        sf_mex_destroy(&c2_m434);
        sf_mex_destroy(&c2_m435);
        sf_mex_destroy(&c2_m436);
        sf_mex_destroy(&c2_m437);
        c2_ALU_func = 7U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 329);
        sf_mex_destroy(&c2_m438);
        sf_mex_destroy(&c2_m439);
        sf_mex_destroy(&c2_m440);
        sf_mex_destroy(&c2_m441);
        sf_mex_destroy(&c2_m442);
        sf_mex_destroy(&c2_m443);
        sf_mex_destroy(&c2_m444);
        c2_shifter_sel = 3U;
        break;

       default:
        CV_EML_SWITCH(0, 5, 0);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 333);
        chartInstance->c2_CPU_state = 1U;
        break;
      }
      break;

     default:
      CV_EML_SWITCH(0, 1, 0);
      break;
    }
    break;

   case 6U:
    CV_EML_SWITCH(0, 0, 6);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 343);
    sf_mex_destroy(&c2_m445);
    sf_mex_destroy(&c2_m446);
    sf_mex_destroy(&c2_m447);
    sf_mex_destroy(&c2_m448);
    sf_mex_destroy(&c2_m449);
    sf_mex_destroy(&c2_m450);
    sf_mex_destroy(&c2_m451);
    c2_AC_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 344);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 346);
    chartInstance->c2_CPU_state = 1U;
    break;

   case 7U:
    CV_EML_SWITCH(0, 0, 7);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 352);
    c2_DM_addr = chartInstance->c2_indirect_address;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 354);
    sf_mex_destroy(&c2_m452);
    sf_mex_destroy(&c2_m453);
    sf_mex_destroy(&c2_m454);
    sf_mex_destroy(&c2_m455);
    sf_mex_destroy(&c2_m456);
    sf_mex_destroy(&c2_m457);
    sf_mex_destroy(&c2_m458);
    c2_DM_r_w = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 356);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 357);
    chartInstance->c2_CPU_state = 13U;
    break;

   case 8U:
    CV_EML_SWITCH(0, 0, 8);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 362);
    c2_DM_addr = chartInstance->c2_indirect_address;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 364);
    sf_mex_destroy(&c2_m459);
    sf_mex_destroy(&c2_m460);
    sf_mex_destroy(&c2_m461);
    sf_mex_destroy(&c2_m462);
    sf_mex_destroy(&c2_m463);
    sf_mex_destroy(&c2_m464);
    sf_mex_destroy(&c2_m465);
    c2_DM_r_w = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 366);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 367);
    chartInstance->c2_CPU_state = 15U;
    break;

   case 9U:
    CV_EML_SWITCH(0, 0, 9);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 372);
    c2_DM_addr = chartInstance->c2_indirect_address;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 374);
    sf_mex_destroy(&c2_m466);
    sf_mex_destroy(&c2_m467);
    sf_mex_destroy(&c2_m468);
    sf_mex_destroy(&c2_m469);
    sf_mex_destroy(&c2_m470);
    sf_mex_destroy(&c2_m471);
    sf_mex_destroy(&c2_m472);
    c2_DM_r_w = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 376);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 377);
    chartInstance->c2_CPU_state = 17U;
    break;

   case 10U:
    CV_EML_SWITCH(0, 0, 10);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 382);
    c2_DM_addr = chartInstance->c2_indirect_address;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 384);
    sf_mex_destroy(&c2_m473);
    sf_mex_destroy(&c2_m474);
    sf_mex_destroy(&c2_m475);
    sf_mex_destroy(&c2_m476);
    sf_mex_destroy(&c2_m477);
    sf_mex_destroy(&c2_m478);
    sf_mex_destroy(&c2_m479);
    c2_DM_r_w = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 386);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 387);
    chartInstance->c2_CPU_state = 19U;
    break;

   case 11U:
    CV_EML_SWITCH(0, 0, 11);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 392);
    c2_DM_addr = c2_uint8(chartInstance, c2_data_in);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 394);
    sf_mex_destroy(&c2_m480);
    sf_mex_destroy(&c2_m481);
    sf_mex_destroy(&c2_m482);
    sf_mex_destroy(&c2_m483);
    sf_mex_destroy(&c2_m484);
    sf_mex_destroy(&c2_m485);
    sf_mex_destroy(&c2_m486);
    c2_DM_r_w = 1U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 395);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 396);
    chartInstance->c2_CPU_state = 1U;
    break;

   case 12U:
    CV_EML_SWITCH(0, 0, 12);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 400);
    c2_print_data = TRUE;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 401);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 402);
    chartInstance->c2_CPU_state = 1U;
    break;

   case 13U:
    CV_EML_SWITCH(0, 0, 13);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 407);
    sf_mex_destroy(&c2_m487);
    sf_mex_destroy(&c2_m488);
    sf_mex_destroy(&c2_m489);
    sf_mex_destroy(&c2_m490);
    sf_mex_destroy(&c2_m491);
    sf_mex_destroy(&c2_m492);
    sf_mex_destroy(&c2_m493);
    c2_ALU_func = 6U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 408);
    sf_mex_destroy(&c2_m494);
    sf_mex_destroy(&c2_m495);
    sf_mex_destroy(&c2_m496);
    sf_mex_destroy(&c2_m497);
    sf_mex_destroy(&c2_m498);
    sf_mex_destroy(&c2_m499);
    sf_mex_destroy(&c2_m500);
    c2_shifter_sel = 3U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 410);
    if (CV_EML_IF(0, 10, chartInstance->c2_previous_CPU_state == 4)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 411);
      chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 412);
      chartInstance->c2_CPU_state = 14U;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 414);
      chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 415);
      chartInstance->c2_CPU_state = 6U;
    }
    break;

   case 14U:
    CV_EML_SWITCH(0, 0, 14);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 419);
    c2_p_hoistedGlobal = chartInstance->c2_minor_opcode;
    c2_j_a = c2_p_hoistedGlobal;
    sf_mex_destroy(&c2_m501);
    sf_mex_destroy(&c2_m502);
    c2_indirect_bit = 0U;
    c2_j_a1 = c2_j_a;
    c2_j_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_j_a1 >> 5) & 1U);
    c2_indirect_bit = c2_j_slice_temp;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 421);
    sf_mex_destroy(&c2_m503);
    sf_mex_destroy(&c2_m504);
    sf_mex_destroy(&c2_m505);
    sf_mex_destroy(&c2_m506);
    sf_mex_destroy(&c2_m507);
    sf_mex_destroy(&c2_m508);
    sf_mex_destroy(&c2_m509);
    c2_AC_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 423);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 424);
    if (CV_EML_IF(0, 11, c2_logical(chartInstance, c2_indirect_bit))) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 426);
      chartInstance->c2_indirect_address = c2_uint8(chartInstance, c2_data_in);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 427);
      chartInstance->c2_CPU_state = 7U;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 429);
      chartInstance->c2_CPU_state = 25U;
    }
    break;

   case 15U:
    CV_EML_SWITCH(0, 0, 15);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 435);
    sf_mex_destroy(&c2_m510);
    sf_mex_destroy(&c2_m511);
    sf_mex_destroy(&c2_m512);
    sf_mex_destroy(&c2_m513);
    sf_mex_destroy(&c2_m514);
    sf_mex_destroy(&c2_m515);
    sf_mex_destroy(&c2_m516);
    c2_ALU_func = 1U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 436);
    sf_mex_destroy(&c2_m517);
    sf_mex_destroy(&c2_m518);
    sf_mex_destroy(&c2_m519);
    sf_mex_destroy(&c2_m520);
    sf_mex_destroy(&c2_m521);
    sf_mex_destroy(&c2_m522);
    sf_mex_destroy(&c2_m523);
    c2_shifter_sel = 3U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 438);
    if (CV_EML_IF(0, 12, chartInstance->c2_previous_CPU_state == 4)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 439);
      chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 440);
      chartInstance->c2_CPU_state = 16U;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 442);
      chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 443);
      chartInstance->c2_CPU_state = 6U;
    }
    break;

   case 16U:
    CV_EML_SWITCH(0, 0, 16);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 447);
    c2_q_hoistedGlobal = chartInstance->c2_minor_opcode;
    c2_k_a = c2_q_hoistedGlobal;
    sf_mex_destroy(&c2_m524);
    sf_mex_destroy(&c2_m525);
    c2_indirect_bit = 0U;
    c2_k_a1 = c2_k_a;
    c2_k_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_k_a1 >> 5) & 1U);
    c2_indirect_bit = c2_k_slice_temp;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 449);
    sf_mex_destroy(&c2_m526);
    sf_mex_destroy(&c2_m527);
    sf_mex_destroy(&c2_m528);
    sf_mex_destroy(&c2_m529);
    sf_mex_destroy(&c2_m530);
    sf_mex_destroy(&c2_m531);
    sf_mex_destroy(&c2_m532);
    c2_AC_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 451);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 452);
    if (CV_EML_IF(0, 13, c2_logical(chartInstance, c2_indirect_bit))) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 454);
      chartInstance->c2_indirect_address = c2_uint8(chartInstance, c2_data_in);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 455);
      chartInstance->c2_CPU_state = 8U;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 457);
      chartInstance->c2_CPU_state = 25U;
    }
    break;

   case 17U:
    CV_EML_SWITCH(0, 0, 17);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 462);
    sf_mex_destroy(&c2_m533);
    sf_mex_destroy(&c2_m534);
    sf_mex_destroy(&c2_m535);
    sf_mex_destroy(&c2_m536);
    sf_mex_destroy(&c2_m537);
    sf_mex_destroy(&c2_m538);
    sf_mex_destroy(&c2_m539);
    c2_ALU_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 463);
    sf_mex_destroy(&c2_m540);
    sf_mex_destroy(&c2_m541);
    sf_mex_destroy(&c2_m542);
    sf_mex_destroy(&c2_m543);
    sf_mex_destroy(&c2_m544);
    sf_mex_destroy(&c2_m545);
    sf_mex_destroy(&c2_m546);
    c2_shifter_sel = 3U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 465);
    if (CV_EML_IF(0, 14, chartInstance->c2_previous_CPU_state == 4)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 466);
      chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 467);
      chartInstance->c2_CPU_state = 18U;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 469);
      chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 470);
      chartInstance->c2_CPU_state = 6U;
    }
    break;

   case 18U:
    CV_EML_SWITCH(0, 0, 18);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 474);
    c2_r_hoistedGlobal = chartInstance->c2_minor_opcode;
    c2_l_a = c2_r_hoistedGlobal;
    sf_mex_destroy(&c2_m547);
    sf_mex_destroy(&c2_m548);
    c2_indirect_bit = 0U;
    c2_l_a1 = c2_l_a;
    c2_l_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_l_a1 >> 5) & 1U);
    c2_indirect_bit = c2_l_slice_temp;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 476);
    sf_mex_destroy(&c2_m549);
    sf_mex_destroy(&c2_m550);
    sf_mex_destroy(&c2_m551);
    sf_mex_destroy(&c2_m552);
    sf_mex_destroy(&c2_m553);
    sf_mex_destroy(&c2_m554);
    sf_mex_destroy(&c2_m555);
    c2_AC_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 478);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 479);
    if (CV_EML_IF(0, 15, c2_logical(chartInstance, c2_indirect_bit))) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 481);
      chartInstance->c2_indirect_address = c2_uint8(chartInstance, c2_data_in);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 482);
      chartInstance->c2_CPU_state = 9U;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 484);
      chartInstance->c2_CPU_state = 25U;
    }
    break;

   case 19U:
    CV_EML_SWITCH(0, 0, 19);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 489);
    sf_mex_destroy(&c2_m556);
    sf_mex_destroy(&c2_m557);
    sf_mex_destroy(&c2_m558);
    sf_mex_destroy(&c2_m559);
    sf_mex_destroy(&c2_m560);
    sf_mex_destroy(&c2_m561);
    sf_mex_destroy(&c2_m562);
    c2_ALU_func = 3U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 490);
    sf_mex_destroy(&c2_m563);
    sf_mex_destroy(&c2_m564);
    sf_mex_destroy(&c2_m565);
    sf_mex_destroy(&c2_m566);
    sf_mex_destroy(&c2_m567);
    sf_mex_destroy(&c2_m568);
    sf_mex_destroy(&c2_m569);
    c2_shifter_sel = 3U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 492);
    if (CV_EML_IF(0, 16, chartInstance->c2_previous_CPU_state == 4)) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 493);
      chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 494);
      chartInstance->c2_CPU_state = 20U;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 496);
      chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 497);
      chartInstance->c2_CPU_state = 6U;
    }
    break;

   case 20U:
    CV_EML_SWITCH(0, 0, 20);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 501);
    c2_s_hoistedGlobal = chartInstance->c2_minor_opcode;
    c2_m_a = c2_s_hoistedGlobal;
    sf_mex_destroy(&c2_m570);
    sf_mex_destroy(&c2_m571);
    c2_indirect_bit = 0U;
    c2_m_a1 = c2_m_a;
    c2_m_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_m_a1 >> 5) & 1U);
    c2_indirect_bit = c2_m_slice_temp;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 503);
    sf_mex_destroy(&c2_m572);
    sf_mex_destroy(&c2_m573);
    sf_mex_destroy(&c2_m574);
    sf_mex_destroy(&c2_m575);
    sf_mex_destroy(&c2_m576);
    sf_mex_destroy(&c2_m577);
    sf_mex_destroy(&c2_m578);
    c2_AC_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 505);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 506);
    if (CV_EML_IF(0, 17, c2_logical(chartInstance, c2_indirect_bit))) {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 508);
      chartInstance->c2_indirect_address = c2_uint8(chartInstance, c2_data_in);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 509);
      chartInstance->c2_CPU_state = 10U;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 512);
      chartInstance->c2_CPU_state = 25U;
    }
    break;

   case 21U:
    CV_EML_SWITCH(0, 0, 21);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 517);
    chartInstance->c2_CPU_state = 11U;
    break;

   case 22U:
    CV_EML_SWITCH(0, 0, 22);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 521);
    c2_hlt = 1U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 522);
    chartInstance->c2_CPU_state = 22U;
    break;

   default:
    CV_EML_SWITCH(0, 0, 0);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 525);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 527);
    chartInstance->c2_CPU_state = 1U;
    break;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -527);
  sf_debug_symbol_scope_pop();
  *c2_b_shifter_sel = c2_shifter_sel;
  *c2_b_out_flags = c2_out_flags;
  *c2_b_ALU_func = c2_ALU_func;
  *c2_b_print_data = c2_print_data;
  *c2_b_DM_addr = c2_DM_addr;
  *c2_b_DM_r_w = c2_DM_r_w;
  *c2_b_AC_func = c2_AC_func;
  *c2_b_AC_data = c2_AC_data;
  *c2_b_IR_func = c2_IR_func;
  *c2_b_PC_func = c2_PC_func;
  *c2_b_addr_inc = c2_addr_inc;
  *c2_b_IM_read = c2_IM_read;
  *c2_b_hlt = c2_hlt;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_hdlcodercpu_eml(SFc2_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_indirect_address_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0));
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static uint8_T c2_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_indirect_address, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_indirect_address),
    &c2_thisId);
  sf_mex_destroy(&c2_b_indirect_address);
  return c2_y;
}

static uint8_T c2_b_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_indirect_address_not_empty = FALSE;
  } else {
    chartInstance->c2_indirect_address_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
    c2_y = c2_u0;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_indirect_address;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_b_indirect_address = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_indirect_address),
    &c2_thisId);
  sf_mex_destroy(&c2_b_indirect_address);
  *(uint8_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  uint8_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    if (!chartInstance->c2_address_data_not_empty) {
      sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
    } else {
      c2_b_u = c2_u;
      c2_b_y = NULL;
      sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
      sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
        sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx),
        15, "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, TRUE));
    }

    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_c_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_address_data, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_address_data),
    &c2_thisId);
  sf_mex_destroy(&c2_b_address_data);
  return c2_y;
}

static uint8_T c2_d_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u1;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_address_data_not_empty = FALSE;
  } else {
    chartInstance->c2_address_data_not_empty = TRUE;
    sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_b_eml_mx);
    sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u));
    sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
                   (c2_mxFi)));
    sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_u1, 1, 3, 0U, 0, 0U, 0);
    sf_mex_destroy(&c2_mxFi);
    sf_mex_destroy(&c2_mxInt);
    c2_y = c2_u1;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_address_data;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_b_address_data = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_address_data),
      &c2_thisId);
    sf_mex_destroy(&c2_b_address_data);
    *(uint8_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  uint8_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    if (!chartInstance->c2_minor_opcode_not_empty) {
      sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
    } else {
      c2_b_u = c2_u;
      c2_b_y = NULL;
      sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
      sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
        sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx),
        15, "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, TRUE));
    }

    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_e_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_minor_opcode, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_minor_opcode),
    &c2_thisId);
  sf_mex_destroy(&c2_b_minor_opcode);
  return c2_y;
}

static uint8_T c2_f_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u2;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_minor_opcode_not_empty = FALSE;
  } else {
    chartInstance->c2_minor_opcode_not_empty = TRUE;
    sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_b_eml_mx);
    sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u));
    sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
                   (c2_mxFi)));
    sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_u2, 1, 3, 0U, 0, 0U, 0);
    sf_mex_destroy(&c2_mxFi);
    sf_mex_destroy(&c2_mxInt);
    c2_y = c2_u2;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_minor_opcode;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_b_minor_opcode = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_minor_opcode),
      &c2_thisId);
    sf_mex_destroy(&c2_b_minor_opcode);
    *(uint8_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  uint8_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    if (!chartInstance->c2_major_opcode_not_empty) {
      sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
    } else {
      c2_b_u = c2_u;
      c2_b_y = NULL;
      sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
      sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
        sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx),
        15, "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, TRUE));
    }

    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_g_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_major_opcode, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_major_opcode),
    &c2_thisId);
  sf_mex_destroy(&c2_b_major_opcode);
  return c2_y;
}

static uint8_T c2_h_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u3;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_major_opcode_not_empty = FALSE;
  } else {
    chartInstance->c2_major_opcode_not_empty = TRUE;
    sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_b_eml_mx);
    sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u));
    sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
                   (c2_mxFi)));
    sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_u3, 1, 3, 0U, 0, 0U, 0);
    sf_mex_destroy(&c2_mxFi);
    sf_mex_destroy(&c2_mxInt);
    c2_y = c2_u3;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_major_opcode;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_b_major_opcode = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_major_opcode),
      &c2_thisId);
    sf_mex_destroy(&c2_b_major_opcode);
    *(uint8_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_previous_CPU_state_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0));
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static uint8_T c2_i_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_previous_CPU_state, const char_T
  *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_previous_CPU_state),
    &c2_thisId);
  sf_mex_destroy(&c2_b_previous_CPU_state);
  return c2_y;
}

static uint8_T c2_j_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u4;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_previous_CPU_state_not_empty = FALSE;
  } else {
    chartInstance->c2_previous_CPU_state_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u4, 1, 3, 0U, 0, 0U, 0);
    c2_y = c2_u4;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_previous_CPU_state;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_b_previous_CPU_state = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_previous_CPU_state),
    &c2_thisId);
  sf_mex_destroy(&c2_b_previous_CPU_state);
  *(uint8_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_CPU_state_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0));
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static uint8_T c2_k_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_CPU_state, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_CPU_state),
    &c2_thisId);
  sf_mex_destroy(&c2_b_CPU_state);
  return c2_y;
}

static uint8_T c2_l_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u5;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_CPU_state_not_empty = FALSE;
  } else {
    chartInstance->c2_CPU_state_not_empty = TRUE;
    sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u5, 1, 3, 0U, 0, 0U, 0);
    c2_y = c2_u5;
  }

  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_CPU_state;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_b_CPU_state = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_CPU_state),
    &c2_thisId);
  sf_mex_destroy(&c2_b_CPU_state);
  *(uint8_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static uint8_T c2_m_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_hlt, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_hlt), &c2_thisId);
  sf_mex_destroy(&c2_hlt);
  return c2_y;
}

static uint8_T c2_n_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u6;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u6, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u6;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_hlt;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_hlt = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_hlt), &c2_thisId);
  sf_mex_destroy(&c2_hlt);
  *(uint8_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  uint8_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_c_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_o_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_IM_read, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_IM_read), &c2_thisId);
  sf_mex_destroy(&c2_IM_read);
  return c2_y;
}

static uint8_T c2_p_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u7;
  sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_c_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u));
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)));
  sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_u7, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_mxFi);
  sf_mex_destroy(&c2_mxInt);
  c2_y = c2_u7;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_IM_read;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_IM_read = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_IM_read),
      &c2_thisId);
    sf_mex_destroy(&c2_IM_read);
    *(uint8_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int8_T c2_u;
  const mxArray *c2_y = NULL;
  int8_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(int8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_d_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static int8_T c2_q_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_addr_inc, const char_T *c2_identifier)
{
  int8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_addr_inc),
    &c2_thisId);
  sf_mex_destroy(&c2_addr_inc);
  return c2_y;
}

static int8_T c2_r_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  int8_T c2_i5;
  sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_d_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u));
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)));
  sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_i5, 1, 2, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_mxFi);
  sf_mex_destroy(&c2_mxInt);
  c2_y = c2_i5;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_addr_inc;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_addr_inc = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_addr_inc),
      &c2_thisId);
    sf_mex_destroy(&c2_addr_inc);
    *(int8_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  uint8_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_e_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_s_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_PC_func, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_PC_func), &c2_thisId);
  sf_mex_destroy(&c2_PC_func);
  return c2_y;
}

static uint8_T c2_t_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u8;
  sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_e_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u));
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)));
  sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_u8, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_mxFi);
  sf_mex_destroy(&c2_mxInt);
  c2_y = c2_u8;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_PC_func;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_PC_func = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_PC_func),
      &c2_thisId);
    sf_mex_destroy(&c2_PC_func);
    *(uint8_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  uint8_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_f_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_u_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_AC_func, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_v_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_AC_func), &c2_thisId);
  sf_mex_destroy(&c2_AC_func);
  return c2_y;
}

static uint8_T c2_v_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u9;
  sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_f_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u));
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)));
  sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_u9, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_mxFi);
  sf_mex_destroy(&c2_mxInt);
  c2_y = c2_u9;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_AC_func;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_AC_func = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_v_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_AC_func),
      &c2_thisId);
    sf_mex_destroy(&c2_AC_func);
    *(uint8_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  boolean_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(boolean_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static boolean_T c2_w_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_print_data, const char_T *c2_identifier)
{
  boolean_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_x_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_print_data),
    &c2_thisId);
  sf_mex_destroy(&c2_print_data);
  return c2_y;
}

static boolean_T c2_x_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  boolean_T c2_y;
  boolean_T c2_b0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_b0, 1, 11, 0U, 0, 0U, 0);
  c2_y = c2_b0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_print_data;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  boolean_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_print_data = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_x_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_print_data),
    &c2_thisId);
  sf_mex_destroy(&c2_print_data);
  *(boolean_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_m_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  uint8_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_g_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_y_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u10;
  sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_g_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u));
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)));
  sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_u10, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_mxFi);
  sf_mex_destroy(&c2_mxInt);
  c2_y = c2_u10;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_out_flags;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_out_flags = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_y_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_out_flags),
      &c2_thisId);
    sf_mex_destroy(&c2_out_flags);
    *(uint8_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_n_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  uint16_T c2_u;
  const mxArray *c2_y = NULL;
  uint16_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint16_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 5, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_h_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static const mxArray *c2_o_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int8_T c2_u;
  const mxArray *c2_y = NULL;
  int8_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(int8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_d_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static const mxArray *c2_p_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static real_T c2_ab_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_ab_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout),
    &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_q_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  uint8_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_c_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_bb_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u11;
  sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_c_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u));
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)));
  sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_u11, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_mxFi);
  sf_mex_destroy(&c2_mxInt);
  c2_y = c2_u11;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_z;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_z = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_bb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_z), &c2_thisId);
    sf_mex_destroy(&c2_z);
    *(uint8_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_r_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  int8_T c2_u;
  const mxArray *c2_y = NULL;
  int8_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(int8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_i_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static int8_T c2_cb_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  int8_T c2_i6;
  sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_i_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u));
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)));
  sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_i6, 1, 2, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_mxFi);
  sf_mex_destroy(&c2_mxInt);
  c2_y = c2_i6;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_temp_address_data;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_temp_address_data = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_cb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_temp_address_data),
      &c2_thisId);
    sf_mex_destroy(&c2_temp_address_data);
    *(int8_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_s_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  uint16_T c2_u;
  const mxArray *c2_y = NULL;
  uint16_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint16_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 5, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_h_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static const mxArray *c2_t_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  const mxArray *c2_u;
  const mxArray *c2_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = sf_mex_dup(*(const mxArray **)c2_inData);
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_duplicatearraysafe(&c2_u));
  sf_mex_destroy(&c2_u);
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

const mxArray *sf_c2_hdlcodercpu_eml_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[39];
  const mxArray *c2_m579 = NULL;
  int32_T c2_i7;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  sf_mex_assign(&c2_m579, sf_mex_createstruct("nameCaptureInfo", 1, 39));
  for (c2_i7 = 0; c2_i7 < 39; c2_i7++) {
    c2_r0 = &c2_info[c2_i7];
    sf_mex_addfield(c2_m579, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i7);
    sf_mex_addfield(c2_m579, sf_mex_create("nameCaptureInfo", c2_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i7);
    sf_mex_addfield(c2_m579, sf_mex_create("nameCaptureInfo",
      c2_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c2_i7);
    sf_mex_addfield(c2_m579, sf_mex_create("nameCaptureInfo", c2_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved",
                    "nameCaptureInfo", c2_i7);
    sf_mex_addfield(c2_m579, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i7);
    sf_mex_addfield(c2_m579, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i7);
    sf_mex_addfield(c2_m579, sf_mex_create("nameCaptureInfo",
      &c2_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c2_i7);
    sf_mex_addfield(c2_m579, sf_mex_create("nameCaptureInfo",
      &c2_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c2_i7);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m579);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[39])
{
  c2_info[0].context = "";
  c2_info[0].name = "fimath";
  c2_info[0].dominantType = "char";
  c2_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m";
  c2_info[0].fileTimeLo = 275520000U;
  c2_info[0].fileTimeHi = 30114375U;
  c2_info[0].mFileTimeLo = 0U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context = "";
  c2_info[1].name = "fi_impl";
  c2_info[1].dominantType = "";
  c2_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m";
  c2_info[1].fileTimeLo = 275520000U;
  c2_info[1].fileTimeHi = 30114375U;
  c2_info[1].mFileTimeLo = 0U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c2_info[2].name = "isfi";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c2_info[2].fileTimeLo = 335520000U;
  c2_info[2].fileTimeHi = 30114375U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c2_info[3].name = "isnumerictype";
  c2_info[3].dominantType = "char";
  c2_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m";
  c2_info[3].fileTimeLo = 355520000U;
  c2_info[3].fileTimeHi = 30114375U;
  c2_info[3].mFileTimeLo = 0U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c2_info[4].name = "eml_fi_checkforerror";
  c2_info[4].dominantType = "embedded.numerictype";
  c2_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m";
  c2_info[4].fileTimeLo = 255520000U;
  c2_info[4].fileTimeHi = 30114375U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context = "";
  c2_info[5].name = "bitget";
  c2_info[5].dominantType = "embedded.fi";
  c2_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c2_info[5].fileTimeLo = 235520000U;
  c2_info[5].fileTimeHi = 30114375U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c2_info[6].name = "eml_scalexp_compatible";
  c2_info[6].dominantType = "embedded.fi";
  c2_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c2_info[6].fileTimeLo = 3244844544U;
  c2_info[6].fileTimeHi = 30108086U;
  c2_info[6].mFileTimeLo = 0U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c2_info[7].name = "all";
  c2_info[7].dominantType = "logical";
  c2_info[7].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c2_info[7].fileTimeLo = 3624844544U;
  c2_info[7].fileTimeHi = 30108086U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c2_info[8].name = "eml_all_or_any";
  c2_info[8].dominantType = "char";
  c2_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[8].fileTimeLo = 2224844544U;
  c2_info[8].fileTimeHi = 30108086U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[9].name = "isequal";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[9].fileTimeLo = 2864844544U;
  c2_info[9].fileTimeHi = 30108086U;
  c2_info[9].mFileTimeLo = 0U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[10].name = "eml_isequal_core";
  c2_info[10].dominantType = "double";
  c2_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c2_info[10].fileTimeLo = 3144844544U;
  c2_info[10].fileTimeHi = 30108086U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c2_info[11].name = "eml_const_nonsingleton_dim";
  c2_info[11].dominantType = "logical";
  c2_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  c2_info[11].fileTimeLo = 2244844544U;
  c2_info[11].fileTimeHi = 30108086U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c2_info[12].name = "isfixed";
  c2_info[12].dominantType = "embedded.fi";
  c2_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  c2_info[12].fileTimeLo = 875520000U;
  c2_info[12].fileTimeHi = 30114375U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  c2_info[13].name = "get";
  c2_info[13].dominantType = "embedded.numerictype";
  c2_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m";
  c2_info[13].fileTimeLo = 4170487296U;
  c2_info[13].fileTimeHi = 30114374U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
  c2_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c2_info[14].name = "numerictype";
  c2_info[14].dominantType = "double";
  c2_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m";
  c2_info[14].fileTimeLo = 435520000U;
  c2_info[14].fileTimeHi = 30114375U;
  c2_info[14].mFileTimeLo = 0U;
  c2_info[14].mFileTimeHi = 0U;
  c2_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m";
  c2_info[15].name = "length";
  c2_info[15].dominantType = "cell";
  c2_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[15].fileTimeLo = 2884844544U;
  c2_info[15].fileTimeHi = 30108086U;
  c2_info[15].mFileTimeLo = 0U;
  c2_info[15].mFileTimeHi = 0U;
  c2_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m";
  c2_info[16].name = "fimath";
  c2_info[16].dominantType = "embedded.fi";
  c2_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m";
  c2_info[16].fileTimeLo = 775520000U;
  c2_info[16].fileTimeHi = 30114375U;
  c2_info[16].mFileTimeLo = 0U;
  c2_info[16].mFileTimeHi = 0U;
  c2_info[17].context = "";
  c2_info[17].name = "logical";
  c2_info[17].dominantType = "embedded.fi";
  c2_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/logical.m";
  c2_info[17].fileTimeLo = 915520000U;
  c2_info[17].fileTimeHi = 30114375U;
  c2_info[17].mFileTimeLo = 0U;
  c2_info[17].mFileTimeHi = 0U;
  c2_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/logical.m";
  c2_info[18].name = "ne";
  c2_info[18].dominantType = "embedded.fi";
  c2_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m";
  c2_info[18].fileTimeLo = 995520000U;
  c2_info[18].fileTimeHi = 30114375U;
  c2_info[18].mFileTimeLo = 0U;
  c2_info[18].mFileTimeHi = 0U;
  c2_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m";
  c2_info[19].name = "eml_type_relop_const";
  c2_info[19].dominantType = "embedded.fi";
  c2_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m";
  c2_info[19].fileTimeLo = 735520000U;
  c2_info[19].fileTimeHi = 30114375U;
  c2_info[19].mFileTimeLo = 0U;
  c2_info[19].mFileTimeHi = 0U;
  c2_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m";
  c2_info[20].name = "eml_make_same_complexity";
  c2_info[20].dominantType = "embedded.fi";
  c2_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_make_same_complexity.m";
  c2_info[20].fileTimeLo = 695520000U;
  c2_info[20].fileTimeHi = 30114375U;
  c2_info[20].mFileTimeLo = 0U;
  c2_info[20].mFileTimeHi = 0U;
  c2_info[21].context = "";
  c2_info[21].name = "uint8";
  c2_info[21].dominantType = "embedded.fi";
  c2_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m";
  c2_info[21].fileTimeLo = 1115520000U;
  c2_info[21].fileTimeHi = 30114375U;
  c2_info[21].mFileTimeLo = 0U;
  c2_info[21].mFileTimeHi = 0U;
  c2_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m";
  c2_info[22].name = "eml_fi_getStoredIntValAsDType";
  c2_info[22].dominantType = "embedded.fi";
  c2_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getStoredIntValAsDType.m";
  c2_info[22].fileTimeLo = 655520000U;
  c2_info[22].fileTimeHi = 30114375U;
  c2_info[22].mFileTimeLo = 0U;
  c2_info[22].mFileTimeHi = 0U;
  c2_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c2_info[23].name = "isfloat";
  c2_info[23].dominantType = "embedded.fi";
  c2_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m";
  c2_info[23].fileTimeLo = 875520000U;
  c2_info[23].fileTimeHi = 30114375U;
  c2_info[23].mFileTimeLo = 0U;
  c2_info[23].mFileTimeHi = 0U;
  c2_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput";
  c2_info[24].name = "numerictype";
  c2_info[24].dominantType = "embedded.fi";
  c2_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m";
  c2_info[24].fileTimeLo = 995520000U;
  c2_info[24].fileTimeHi = 30114375U;
  c2_info[24].mFileTimeLo = 0U;
  c2_info[24].mFileTimeHi = 0U;
  c2_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c2_info[25].name = "eml_fi_checkforntype";
  c2_info[25].dominantType = "embedded.fi";
  c2_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m";
  c2_info[25].fileTimeLo = 255520000U;
  c2_info[25].fileTimeHi = 30114375U;
  c2_info[25].mFileTimeLo = 0U;
  c2_info[25].mFileTimeHi = 0U;
  c2_info[26].context = "";
  c2_info[26].name = "minus";
  c2_info[26].dominantType = "embedded.fi";
  c2_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m";
  c2_info[26].fileTimeLo = 955520000U;
  c2_info[26].fileTimeHi = 30114375U;
  c2_info[26].mFileTimeLo = 0U;
  c2_info[26].mFileTimeHi = 0U;
  c2_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m";
  c2_info[27].name = "isscaledtype";
  c2_info[27].dominantType = "embedded.fi";
  c2_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m";
  c2_info[27].fileTimeLo = 895520000U;
  c2_info[27].fileTimeHi = 30114375U;
  c2_info[27].mFileTimeLo = 0U;
  c2_info[27].mFileTimeHi = 0U;
  c2_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m";
  c2_info[28].name = "get";
  c2_info[28].dominantType = "embedded.fimath";
  c2_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fimath/get.m";
  c2_info[28].fileTimeLo = 4190487296U;
  c2_info[28].fileTimeHi = 30114374U;
  c2_info[28].mFileTimeLo = 0U;
  c2_info[28].mFileTimeHi = 0U;
  c2_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m";
  c2_info[29].name = "strcmpi";
  c2_info[29].dominantType = "char";
  c2_info[29].resolved = "[IXMB]$matlabroot$/toolbox/matlab/strfun/strcmpi";
  c2_info[29].fileTimeLo = 0U;
  c2_info[29].fileTimeHi = 0U;
  c2_info[29].mFileTimeLo = 0U;
  c2_info[29].mFileTimeHi = 0U;
  c2_info[30].context = "";
  c2_info[30].name = "bitsrl";
  c2_info[30].dominantType = "embedded.fi";
  c2_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitsrl.m";
  c2_info[30].fileTimeLo = 555520000U;
  c2_info[30].fileTimeHi = 30114375U;
  c2_info[30].mFileTimeLo = 0U;
  c2_info[30].mFileTimeHi = 0U;
  c2_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitsrl.m";
  c2_info[31].name = "eml_fi_bitshift";
  c2_info[31].dominantType = "embedded.fi";
  c2_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m";
  c2_info[31].fileTimeLo = 635520000U;
  c2_info[31].fileTimeHi = 30114375U;
  c2_info[31].mFileTimeLo = 0U;
  c2_info[31].mFileTimeHi = 0U;
  c2_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m";
  c2_info[32].name = "eml_shift_checks";
  c2_info[32].dominantType = "embedded.fi";
  c2_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m";
  c2_info[32].fileTimeLo = 715520000U;
  c2_info[32].fileTimeHi = 30114375U;
  c2_info[32].mFileTimeLo = 0U;
  c2_info[32].mFileTimeHi = 0U;
  c2_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m";
  c2_info[33].name = "eml_isslopebiasscaled";
  c2_info[33].dominantType = "embedded.fi";
  c2_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m";
  c2_info[33].fileTimeLo = 695520000U;
  c2_info[33].fileTimeHi = 30114375U;
  c2_info[33].mFileTimeLo = 0U;
  c2_info[33].mFileTimeHi = 0U;
  c2_info[34].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  c2_info[34].name = "isnan";
  c2_info[34].dominantType = "double";
  c2_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c2_info[34].fileTimeLo = 2884844544U;
  c2_info[34].fileTimeHi = 30108086U;
  c2_info[34].mFileTimeLo = 0U;
  c2_info[34].mFileTimeHi = 0U;
  c2_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m!localFixptBitshift";
  c2_info[35].name = "eml_feval";
  c2_info[35].dominantType = "embedded.fi";
  c2_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_feval.m";
  c2_info[35].fileTimeLo = 635520000U;
  c2_info[35].fileTimeHi = 30114375U;
  c2_info[35].mFileTimeLo = 0U;
  c2_info[35].mFileTimeHi = 0U;
  c2_info[36].context = "";
  c2_info[36].name = "bitand";
  c2_info[36].dominantType = "embedded.fi";
  c2_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m";
  c2_info[36].fileTimeLo = 215520000U;
  c2_info[36].fileTimeHi = 30114375U;
  c2_info[36].mFileTimeLo = 0U;
  c2_info[36].mFileTimeHi = 0U;
  c2_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m";
  c2_info[37].name = "isequal";
  c2_info[37].dominantType = "embedded.numerictype";
  c2_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/isequal.m";
  c2_info[37].fileTimeLo = 4190487296U;
  c2_info[37].fileTimeHi = 30114374U;
  c2_info[37].mFileTimeLo = 0U;
  c2_info[37].mFileTimeHi = 0U;
  c2_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m";
  c2_info[38].name = "eml_checkfimathforbinaryops";
  c2_info[38].dominantType = "embedded.fi";
  c2_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_checkfimathforbinaryops.m";
  c2_info[38].fileTimeLo = 615520000U;
  c2_info[38].fileTimeHi = 30114375U;
  c2_info[38].mFileTimeLo = 0U;
  c2_info[38].mFileTimeHi = 0U;
}

static boolean_T c2_logical(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_a)
{
  uint8_T c2_a0;
  const mxArray *c2_m580 = NULL;
  const mxArray *c2_m581 = NULL;
  uint8_T c2_b_a;
  uint8_T c2_b_a0;
  uint8_T c2_a1;
  uint8_T c2_b_a1;
  c2_a0 = c2_a;
  sf_mex_destroy(&c2_m580);
  sf_mex_destroy(&c2_m581);
  c2_b_a = c2_a0;
  c2_b_a0 = c2_b_a;
  c2_a1 = c2_b_a0;
  c2_b_a1 = c2_a1;
  return c2_b_a1 != 0;
}

static uint8_T c2_uint8(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c2_A)
{
  int8_T c2_xfi;
  const mxArray *c2_m582 = NULL;
  const mxArray *c2_m583 = NULL;
  int8_T c2_i8;
  c2_xfi = c2_A;
  sf_mex_destroy(&c2_m582);
  sf_mex_destroy(&c2_m583);
  c2_i8 = c2_xfi;
  if (c2_i8 <= 0) {
    c2_i8 = 0;
  }

  return (uint8_T)c2_i8;
}

static uint8_T c2_b_uint8(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_A)
{
  uint8_T c2_xfi;
  const mxArray *c2_m584 = NULL;
  const mxArray *c2_m585 = NULL;
  c2_xfi = c2_A;
  sf_mex_destroy(&c2_m584);
  sf_mex_destroy(&c2_m585);
  return c2_xfi;
}

static uint8_T c2_c_uint8(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_A)
{
  uint8_T c2_xfi;
  const mxArray *c2_m586 = NULL;
  const mxArray *c2_m587 = NULL;
  c2_xfi = c2_A;
  sf_mex_destroy(&c2_m586);
  sf_mex_destroy(&c2_m587);
  return c2_xfi;
}

static boolean_T c2_b_logical(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_a)
{
  uint8_T c2_a0;
  const mxArray *c2_m588 = NULL;
  const mxArray *c2_m589 = NULL;
  uint8_T c2_b_a;
  uint8_T c2_b_a0;
  uint8_T c2_a1;
  uint8_T c2_b_a1;
  c2_a0 = c2_a;
  sf_mex_destroy(&c2_m588);
  sf_mex_destroy(&c2_m589);
  c2_b_a = c2_a0;
  c2_b_a0 = c2_b_a;
  c2_a1 = c2_b_a0;
  c2_b_a1 = c2_a1;
  return c2_b_a1 != 0;
}

static void c2_isfloat(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c2_m590 = NULL;
  const mxArray *c2_m591 = NULL;
  const mxArray *c2_m592 = NULL;
  const mxArray *c2_m593 = NULL;
  sf_mex_destroy(&c2_m590);
  sf_mex_destroy(&c2_m591);
  sf_mex_destroy(&c2_m592);
  sf_mex_destroy(&c2_m593);
}

static int16_T c2_minus(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c2_a0)
{
  int16_T c2_c;
  const mxArray *c2_m594 = NULL;
  const mxArray *c2_m595 = NULL;
  int8_T c2_a;
  const mxArray *c2_m596 = NULL;
  const mxArray *c2_m597 = NULL;
  const mxArray *c2_m598 = NULL;
  const mxArray *c2_m599 = NULL;
  const mxArray *c2_m600 = NULL;
  const mxArray *c2_m601 = NULL;
  const mxArray *c2_m602 = NULL;
  const mxArray *c2_m603 = NULL;
  const mxArray *c2_m604 = NULL;
  const mxArray *c2_m605 = NULL;
  const mxArray *c2_m606 = NULL;
  const mxArray *c2_m607 = NULL;
  const mxArray *c2_m608 = NULL;
  const mxArray *c2_m609 = NULL;
  const mxArray *c2_m610 = NULL;
  const mxArray *c2_m611 = NULL;
  int16_T c2_i9;
  int16_T c2_i10;
  const mxArray *c2_m612 = NULL;
  const mxArray *c2_m613 = NULL;
  sf_mex_destroy(&c2_m594);
  sf_mex_destroy(&c2_m595);
  c2_a = c2_a0;
  sf_mex_destroy(&c2_m596);
  sf_mex_destroy(&c2_m597);
  sf_mex_destroy(&c2_m598);
  sf_mex_destroy(&c2_m599);
  sf_mex_destroy(&c2_m600);
  sf_mex_destroy(&c2_m601);
  sf_mex_destroy(&c2_m602);
  sf_mex_destroy(&c2_m603);
  sf_mex_destroy(&c2_m604);
  sf_mex_destroy(&c2_m605);
  sf_mex_destroy(&c2_m606);
  sf_mex_destroy(&c2_m607);
  sf_mex_destroy(&c2_m608);
  sf_mex_destroy(&c2_m609);
  sf_mex_destroy(&c2_m610);
  sf_mex_destroy(&c2_m611);
  c2_i9 = (int16_T)((int16_T)c2_a << 5);
  c2_i10 = (int16_T)(((int16_T)(c2_i9 & 4096) != 0 ? (int16_T)(c2_i9 | -4096) :
                      (int16_T)(c2_i9 & 4095)) - 32);
  c2_c = (int16_T)(c2_i10 & 4096) != 0 ? (int16_T)(c2_i10 | -4096) : (int16_T)
    (c2_i10 & 4095);
  sf_mex_destroy(&c2_m612);
  sf_mex_destroy(&c2_m613);
  return c2_c;
}

static uint16_T c2_bitsrl(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint16_T c2_ain)
{
  uint16_T c2_b_ain;
  const mxArray *c2_m614 = NULL;
  const mxArray *c2_m615 = NULL;
  uint16_T c2_varargin_1;
  uint16_T c2_b_varargin_1;
  uint16_T c2_var1;
  uint16_T c2_a;
  const mxArray *c2_m616 = NULL;
  const mxArray *c2_m617 = NULL;
  const mxArray *c2_m618 = NULL;
  const mxArray *c2_m619 = NULL;
  const mxArray *c2_m620 = NULL;
  const mxArray *c2_m621 = NULL;
  const mxArray *c2_m622 = NULL;
  uint16_T c2_b_a;
  uint16_T c2_c_varargin_1;
  uint16_T c2_c;
  c2_b_ain = c2_ain;
  sf_mex_destroy(&c2_m614);
  sf_mex_destroy(&c2_m615);
  c2_varargin_1 = c2_b_ain;
  c2_b_varargin_1 = c2_varargin_1;
  c2_b_isfloat(chartInstance);
  c2_var1 = c2_b_varargin_1;
  c2_a = c2_var1;
  sf_mex_destroy(&c2_m616);
  sf_mex_destroy(&c2_m617);
  sf_mex_destroy(&c2_m618);
  sf_mex_destroy(&c2_m619);
  sf_mex_destroy(&c2_m620);
  sf_mex_destroy(&c2_m621);
  sf_mex_destroy(&c2_m622);
  c2_b_a = c2_a;
  c2_c_varargin_1 = c2_b_a;
  c2_c = (uint16_T)((uint32_T)c2_c_varargin_1 >> 9);
  return c2_c;
}

static void c2_b_isfloat(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c2_m623 = NULL;
  const mxArray *c2_m624 = NULL;
  const mxArray *c2_m625 = NULL;
  const mxArray *c2_m626 = NULL;
  sf_mex_destroy(&c2_m623);
  sf_mex_destroy(&c2_m624);
  sf_mex_destroy(&c2_m625);
  sf_mex_destroy(&c2_m626);
}

static uint16_T c2_b_bitsrl(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint16_T c2_ain)
{
  uint16_T c2_b_ain;
  const mxArray *c2_m627 = NULL;
  const mxArray *c2_m628 = NULL;
  uint16_T c2_varargin_1;
  uint16_T c2_b_varargin_1;
  uint16_T c2_var1;
  uint16_T c2_a;
  const mxArray *c2_m629 = NULL;
  const mxArray *c2_m630 = NULL;
  const mxArray *c2_m631 = NULL;
  const mxArray *c2_m632 = NULL;
  const mxArray *c2_m633 = NULL;
  const mxArray *c2_m634 = NULL;
  const mxArray *c2_m635 = NULL;
  uint16_T c2_b_a;
  uint16_T c2_c_varargin_1;
  uint16_T c2_c;
  c2_b_ain = c2_ain;
  sf_mex_destroy(&c2_m627);
  sf_mex_destroy(&c2_m628);
  c2_varargin_1 = c2_b_ain;
  c2_b_varargin_1 = c2_varargin_1;
  c2_b_isfloat(chartInstance);
  c2_var1 = c2_b_varargin_1;
  c2_a = c2_var1;
  sf_mex_destroy(&c2_m629);
  sf_mex_destroy(&c2_m630);
  sf_mex_destroy(&c2_m631);
  sf_mex_destroy(&c2_m632);
  sf_mex_destroy(&c2_m633);
  sf_mex_destroy(&c2_m634);
  sf_mex_destroy(&c2_m635);
  c2_b_a = c2_a;
  c2_c_varargin_1 = c2_b_a;
  c2_c = (uint16_T)((uint32_T)c2_c_varargin_1 >> 3);
  return c2_c;
}

static uint16_T c2_bitand(SFc2_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint16_T c2_a, uint16_T c2_b)
{
  const mxArray *c2_m636 = NULL;
  const mxArray *c2_m637 = NULL;
  uint16_T c2_c_uint;
  sf_mex_destroy(&c2_m636);
  sf_mex_destroy(&c2_m637);
  c2_c_uint = (uint16_T)((uint16_T)(c2_a & c2_b) & 4095U);
  return c2_c_uint;
}

static const mxArray *c2_u_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_mxArrayOutData, c2_y);
  return c2_mxArrayOutData;
}

static int32_T c2_db_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i11;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i11, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i11;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_db_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_v_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  uint8_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c2_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_g_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c2_mxArrayOutData, c2_y);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_eb_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_out_flags, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_fb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_out_flags),
    &c2_thisId);
  sf_mex_destroy(&c2_out_flags);
  return c2_y;
}

static uint8_T c2_fb_emlrt_marshallIn(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u12;
  sf_mex_check_fi(c2_parentId, c2_u, 0, 0U, 0, c2_eml_mx, c2_g_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u));
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)));
  sf_mex_import(c2_parentId, sf_mex_dup(c2_mxInt), &c2_u12, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c2_mxFi);
  sf_mex_destroy(&c2_mxInt);
  c2_y = c2_u12;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_out_flags;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c2_out_flags = sf_mex_dup(c2_mxArrayInData);
    c2_identifier = c2_varName;
    c2_thisId.fIdentifier = c2_identifier;
    c2_thisId.fParent = NULL;
    c2_y = c2_fb_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_out_flags),
      &c2_thisId);
    sf_mex_destroy(&c2_out_flags);
    *(uint8_T *)c2_outData = c2_y;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void init_dsm_address_info(SFc2_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1484162736U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(848993439U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3132022286U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2112405467U);
}

mxArray *sf_c2_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(4190180718U);
    pr[1] = (double)(3978358094U);
    pr[2] = (double)(1231447358U);
    pr[3] = (double)(1924301955U);
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
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
        mxSetField(mxFixpt,0,"isSigned",mxCreateDoubleScalar(0));
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(12));
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

    mxArray *mxData = mxCreateStructMatrix(1,13,3,dataFields);

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
        mxSetField(mxFixpt,0,"wordLength",mxCreateDoubleScalar(3));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
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

      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
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

      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
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

      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
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

      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,9,"size",mxSize);
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

      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,10,"size",mxSize);
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

      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,11,"size",mxSize);
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

      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(3));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c2_hdlcodercpu_eml(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[15],T\"AC_data\",},{M[1],M[14],T\"AC_func\",},{M[1],M[9],T\"ALU_func\",},{M[1],M[12],T\"DM_addr\",},{M[1],M[13],T\"DM_r_w\",},{M[1],M[19],T\"IM_read\",},{M[1],M[16],T\"IR_func\",},{M[1],M[17],T\"PC_func\",},{M[1],M[18],T\"addr_inc\",},{M[1],M[20],T\"hlt\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[8],T\"out_flags\",},{M[1],M[10],T\"print_data\",},{M[1],M[7],T\"shifter_sel\",},{M[4],M[0],T\"CPU_state\",S'l','i','p'{{M1x2[2174 2183],M[0],}}},{M[4],M[0],T\"address_data\",S'l','i','p'{{M1x2[2984 2996],M[0],}}},{M[4],M[0],T\"indirect_address\",S'l','i','p'{{M1x2[3009 3025],M[0],}}},{M[4],M[0],T\"major_opcode\",S'l','i','p'{{M1x2[2932 2944],M[0],}}},{M[4],M[0],T\"minor_opcode\",S'l','i','p'{{M1x2[2958 2970],M[0],}}},{M[4],M[0],T\"previous_CPU_state\",S'l','i','p'{{M1x2[2250 2268],M[0],}}},{M[8],M[0],T\"is_active_c2_hdlcodercpu_eml\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 20, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_hdlcodercpu_eml_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
    chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_hdlcodercpu_emlMachineNumber_,
           2,
           1,
           1,
           17,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"data_in");
          _SFD_SET_DATA_PROPS(1,1,1,0,"in_flags");
          _SFD_SET_DATA_PROPS(2,1,1,0,"master_rst");
          _SFD_SET_DATA_PROPS(3,2,0,1,"shifter_sel");
          _SFD_SET_DATA_PROPS(4,2,0,1,"out_flags");
          _SFD_SET_DATA_PROPS(5,2,0,1,"ALU_func");
          _SFD_SET_DATA_PROPS(6,2,0,1,"print_data");
          _SFD_SET_DATA_PROPS(7,1,1,0,"IR_in");
          _SFD_SET_DATA_PROPS(8,2,0,1,"DM_addr");
          _SFD_SET_DATA_PROPS(9,2,0,1,"DM_r_w");
          _SFD_SET_DATA_PROPS(10,2,0,1,"AC_func");
          _SFD_SET_DATA_PROPS(11,2,0,1,"AC_data");
          _SFD_SET_DATA_PROPS(12,2,0,1,"IR_func");
          _SFD_SET_DATA_PROPS(13,2,0,1,"PC_func");
          _SFD_SET_DATA_PROPS(14,2,0,1,"addr_inc");
          _SFD_SET_DATA_PROPS(15,2,0,1,"IM_read");
          _SFD_SET_DATA_PROPS(16,2,0,1,"hlt");
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
        _SFD_CV_INIT_EML(0,1,18,0,6,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,17416);
        _SFD_CV_INIT_EML_IF(0,0,2185,2207,-1,2237);
        _SFD_CV_INIT_EML_IF(0,1,2270,2301,-1,2340);
        _SFD_CV_INIT_EML_IF(0,2,2342,2356,-1,2386);
        _SFD_CV_INIT_EML_IF(0,3,3028,3053,-1,3219);
        _SFD_CV_INIT_EML_IF(0,4,6972,6997,7213,7461);
        _SFD_CV_INIT_EML_IF(0,5,7783,7797,-1,8051);
        _SFD_CV_INIT_EML_IF(0,6,8210,8224,-1,8478);
        _SFD_CV_INIT_EML_IF(0,7,8807,8842,-1,9957);
        _SFD_CV_INIT_EML_IF(0,8,9168,9182,-1,9452);
        _SFD_CV_INIT_EML_IF(0,9,9629,9643,-1,9913);
        _SFD_CV_INIT_EML_IF(0,10,14064,14098,14186,14280);
        _SFD_CV_INIT_EML_IF(0,11,14510,14535,14659,14710);
        _SFD_CV_INIT_EML_IF(0,12,14847,14881,14969,15063);
        _SFD_CV_INIT_EML_IF(0,13,15285,15310,15434,15485);
        _SFD_CV_INIT_EML_IF(0,14,15629,15663,15751,15845);
        _SFD_CV_INIT_EML_IF(0,15,16067,16092,16216,16267);
        _SFD_CV_INIT_EML_IF(0,16,16411,16445,16533,16627);
        _SFD_CV_INIT_EML_IF(0,17,16849,16874,16999,17051);

        {
          static int caseStart[] = { 17231, 3354, 3679, 3943, 4139, 4703, 12034,
            12314, 12607, 12886, 13177, 13469, 13750, 13885, 14294, 14716, 15069,
            15499, 15851, 16281, 16633, 17065, 17141 };

          static int caseExprEnd[] = { 17240, 3360, 3685, 3949, 4145, 4709,
            12040, 12320, 12613, 12892, 13184, 13476, 13757, 13892, 14301, 14723,
            15076, 15506, 15858, 16288, 16640, 17072, 17148 };

          _SFD_CV_INIT_EML_SWITCH(0,0,3221,3238,17416,23,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        {
          static int caseStart[] = { -1, 4801, 5176, 5462, 5737, 5996, 6739,
            7491, 8618 };

          static int caseExprEnd[] = { 8, 4807, 5182, 5468, 5743, 6002, 6745,
            7497, 8624 };

          _SFD_CV_INIT_EML_SWITCH(0,1,4761,4788,12000,9,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        {
          static int caseStart[] = { -1, 6136, 6435 };

          static int caseExprEnd[] = { 8, 6142, 6441 };

          _SFD_CV_INIT_EML_SWITCH(0,2,6083,6115,6618,3,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        {
          static int caseStart[] = { -1, 7669, 8097 };

          static int caseExprEnd[] = { 8, 7675, 8103 };

          _SFD_CV_INIT_EML_SWITCH(0,3,7576,7608,8498,3,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        {
          static int caseStart[] = { -1, 9042, 9503 };

          static int caseExprEnd[] = { 8, 9048, 9509 };

          _SFD_CV_INIT_EML_SWITCH(0,4,8985,9017,9937,3,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        {
          static int caseStart[] = { 11746, 10072, 10263, 10405, 10658, 10865,
            11058, 11251, 11539 };

          static int caseExprEnd[] = { 11755, 10078, 10269, 10412, 10665, 10872,
            11065, 11258, 11546 };

          _SFD_CV_INIT_EML_SWITCH(0,5,10024,10051,11950,9,&(caseStart[0]),
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

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c2_i_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,1,0,4,0,1,0,0,
          (MexFcnForType)c2_v_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_l_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_UINT8,0,NULL,1,0,2,0,1,0,0,
          (MexFcnForType)c2_j_sf_marshallOut,(MexInFcnForType)c2_j_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,0,NULL,1,0,4,0,1,0,0,
          (MexFcnForType)c2_v_sf_marshallOut,(MexInFcnForType)c2_r_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,1,0,3,0,1,0,0,
          (MexFcnForType)c2_k_sf_marshallOut,(MexInFcnForType)c2_k_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_l_sf_marshallOut,(MexInFcnForType)c2_l_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_UINT16,0,NULL,1,0,12,0,1,0,0,
          (MexFcnForType)c2_s_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_g_sf_marshallOut,(MexInFcnForType)c2_g_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_UINT8,0,NULL,1,0,1,0,1,0,0,
          (MexFcnForType)c2_h_sf_marshallOut,(MexInFcnForType)c2_h_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_UINT8,0,NULL,1,0,3,0,1,0,0,
          (MexFcnForType)c2_k_sf_marshallOut,(MexInFcnForType)c2_k_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c2_i_sf_marshallOut,(MexInFcnForType)c2_i_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_UINT8,0,NULL,1,0,2,0,1,0,0,
          (MexFcnForType)c2_j_sf_marshallOut,(MexInFcnForType)c2_j_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_UINT8,0,NULL,1,0,2,0,1,0,0,
          (MexFcnForType)c2_j_sf_marshallOut,(MexInFcnForType)c2_j_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c2_i_sf_marshallOut,(MexInFcnForType)c2_i_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_UINT8,0,NULL,1,0,1,0,1,0,0,
          (MexFcnForType)c2_h_sf_marshallOut,(MexInFcnForType)c2_h_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_g_sf_marshallOut,(MexInFcnForType)c2_g_sf_marshallIn);

        {
          int8_T *c2_data_in;
          uint8_T *c2_in_flags;
          boolean_T *c2_master_rst;
          uint8_T *c2_shifter_sel;
          uint8_T *c2_out_flags;
          uint8_T *c2_ALU_func;
          boolean_T *c2_print_data;
          uint16_T *c2_IR_in;
          uint8_T *c2_DM_addr;
          uint8_T *c2_DM_r_w;
          uint8_T *c2_AC_func;
          int8_T *c2_AC_data;
          uint8_T *c2_IR_func;
          uint8_T *c2_PC_func;
          int8_T *c2_addr_inc;
          uint8_T *c2_IM_read;
          uint8_T *c2_hlt;
          c2_hlt = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 13);
          c2_IM_read = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 12);
          c2_addr_inc = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 11);
          c2_PC_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 10);
          c2_IR_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 9);
          c2_AC_data = (int8_T *)ssGetOutputPortSignal(chartInstance->S, 8);
          c2_AC_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 7);
          c2_DM_r_w = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 6);
          c2_DM_addr = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 5);
          c2_IR_in = (uint16_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c2_print_data = (boolean_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c2_ALU_func = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c2_out_flags = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c2_shifter_sel = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c2_master_rst = (boolean_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c2_in_flags = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c2_data_in = (int8_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c2_data_in);
          _SFD_SET_DATA_VALUE_PTR(1U, c2_in_flags);
          _SFD_SET_DATA_VALUE_PTR(2U, c2_master_rst);
          _SFD_SET_DATA_VALUE_PTR(3U, c2_shifter_sel);
          _SFD_SET_DATA_VALUE_PTR(4U, c2_out_flags);
          _SFD_SET_DATA_VALUE_PTR(5U, c2_ALU_func);
          _SFD_SET_DATA_VALUE_PTR(6U, c2_print_data);
          _SFD_SET_DATA_VALUE_PTR(7U, c2_IR_in);
          _SFD_SET_DATA_VALUE_PTR(8U, c2_DM_addr);
          _SFD_SET_DATA_VALUE_PTR(9U, c2_DM_r_w);
          _SFD_SET_DATA_VALUE_PTR(10U, c2_AC_func);
          _SFD_SET_DATA_VALUE_PTR(11U, c2_AC_data);
          _SFD_SET_DATA_VALUE_PTR(12U, c2_IR_func);
          _SFD_SET_DATA_VALUE_PTR(13U, c2_PC_func);
          _SFD_SET_DATA_VALUE_PTR(14U, c2_addr_inc);
          _SFD_SET_DATA_VALUE_PTR(15U, c2_IM_read);
          _SFD_SET_DATA_VALUE_PTR(16U, c2_hlt);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_hdlcodercpu_emlMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c2_hdlcodercpu_eml(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_hdlcodercpu_eml((SFc2_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
  initialize_c2_hdlcodercpu_eml((SFc2_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_hdlcodercpu_eml(void *chartInstanceVar)
{
  enable_c2_hdlcodercpu_eml((SFc2_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_hdlcodercpu_eml(void *chartInstanceVar)
{
  disable_c2_hdlcodercpu_eml((SFc2_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_c2_hdlcodercpu_eml((SFc2_hdlcodercpu_emlInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_hdlcodercpu_eml(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_hdlcodercpu_eml
    ((SFc2_hdlcodercpu_emlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_hdlcodercpu_eml();/* state var info */
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

extern void sf_internal_set_sim_state_c2_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_hdlcodercpu_eml((SFc2_hdlcodercpu_emlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_hdlcodercpu_eml(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_hdlcodercpu_eml(S);
}

static void sf_opaque_set_sim_state_c2_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c2_hdlcodercpu_eml(S, st);
}

static void sf_opaque_terminate_c2_hdlcodercpu_eml(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_hdlcodercpu_emlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_hdlcodercpu_eml((SFc2_hdlcodercpu_emlInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_hdlcodercpu_eml((SFc2_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_hdlcodercpu_eml(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_hdlcodercpu_eml((SFc2_hdlcodercpu_emlInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"hdlcodercpu_eml","hdlcodercpu_eml",2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml","hdlcodercpu_eml",2,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml",
      "hdlcodercpu_eml",2,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",
        2,4);
      sf_mark_chart_reusable_outputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",2,13);
    }

    sf_set_rtw_dwork_info(S,"hdlcodercpu_eml","hdlcodercpu_eml",2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4056389307U));
  ssSetChecksum1(S,(317891576U));
  ssSetChecksum2(S,(3318037157U));
  ssSetChecksum3(S,(3560114489U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "hdlcodercpu_eml", "hdlcodercpu_eml",2);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_hdlcodercpu_eml(SimStruct *S)
{
  SFc2_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_hdlcodercpu_emlInstanceStruct *)malloc(sizeof
    (SFc2_hdlcodercpu_emlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_hdlcodercpu_emlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_hdlcodercpu_eml;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_hdlcodercpu_eml;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_hdlcodercpu_eml;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_hdlcodercpu_eml;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_hdlcodercpu_eml;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_hdlcodercpu_eml;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_hdlcodercpu_eml;
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

void c2_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_hdlcodercpu_eml(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_hdlcodercpu_eml_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
