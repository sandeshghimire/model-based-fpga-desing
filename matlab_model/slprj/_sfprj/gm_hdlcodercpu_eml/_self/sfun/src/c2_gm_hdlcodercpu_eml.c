/* Include files */

#include <stddef.h>
#include "blas.h"
#include "gm_hdlcodercpu_eml_sfun.h"
#include "c2_gm_hdlcodercpu_eml.h"
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
static void initialize_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static void initialize_params_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static void enable_c2_gm_hdlcodercpu_eml(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void disable_c2_gm_hdlcodercpu_eml(SFc2_gm_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void c2_update_debugger_state_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static void set_sim_state_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance, const mxArray *c2_st);
static void finalize_c2_gm_hdlcodercpu_eml(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void sf_gateway_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static void c2_chartstep_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static void initSimStructsc2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static uint8_T c2_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_indirect_address, const char_T
  *c2_identifier);
static uint8_T c2_b_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_c_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_address_data, const char_T *c2_identifier);
static uint8_T c2_d_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_e_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_minor_opcode, const char_T *c2_identifier);
static uint8_T c2_f_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_g_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_major_opcode, const char_T *c2_identifier);
static uint8_T c2_h_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_i_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_previous_CPU_state, const char_T
  *c2_identifier);
static uint8_T c2_j_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_k_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_b_CPU_state, const char_T *c2_identifier);
static uint8_T c2_l_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_m_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_hlt, const char_T *c2_identifier);
static uint8_T c2_n_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_o_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_IM_read, const char_T *c2_identifier);
static uint8_T c2_p_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int8_T c2_q_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_addr_inc, const char_T *c2_identifier);
static int8_T c2_r_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_s_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_PC_func, const char_T *c2_identifier);
static uint8_T c2_t_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_k_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_u_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_AC_func, const char_T *c2_identifier);
static uint8_T c2_v_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_l_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static boolean_T c2_w_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_print_data, const char_T *c2_identifier);
static boolean_T c2_x_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_m_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_y_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_n_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_o_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_p_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_ab_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_q_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_bb_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_r_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int8_T c2_cb_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_s_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_t_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_info_helper(const mxArray **c2_info);
static const mxArray *c2_emlrt_marshallOut(const char * c2_u);
static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u);
static void c2_b_info_helper(const mxArray **c2_info);
static void c2_c_info_helper(const mxArray **c2_info);
static void c2_eml_fi_checkforconst(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c2_b_eml_fi_checkforconst(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c2_c_eml_fi_checkforconst(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c2_d_eml_fi_checkforconst(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c2_e_eml_fi_checkforconst(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static boolean_T c2_logical(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_a);
static uint8_T c2_uint8(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c2_A);
static uint8_T c2_b_uint8(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_A);
static uint8_T c2_c_uint8(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_A);
static boolean_T c2_b_logical(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, uint8_T c2_a);
static void c2_eml_scalar_eg(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static int8_T c2_minus(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c2_a0);
static uint16_T c2_bitsrl(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint16_T c2_ain);
static void c2_eml_switch_helper(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static uint16_T c2_eml_feval(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, uint16_T c2_varargin_1, int32_T c2_varargin_2);
static void c2_f_eml_fi_checkforconst(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static uint16_T c2_b_bitsrl(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint16_T c2_ain);
static uint16_T c2_bitand(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint16_T c2_a, uint16_T c2_b);
static const mxArray *c2_u_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_db_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_v_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_eb_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_out_flags, const char_T *c2_identifier);
static uint8_T c2_fb_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void init_dsm_address_info(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_CPU_state_not_empty = false;
  chartInstance->c2_previous_CPU_state_not_empty = false;
  chartInstance->c2_major_opcode_not_empty = false;
  chartInstance->c2_minor_opcode_not_empty = false;
  chartInstance->c2_address_data_not_empty = false;
  chartInstance->c2_indirect_address_not_empty = false;
  chartInstance->c2_is_active_c2_gm_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c2_i_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 10U, 15, "WordLength", 6, 7.0, 15, "FractionLength", 6,
    0.0, 15, "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6,
    0.0), true);
  sf_mex_assign(&c2_h_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 12.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c2_g_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 4.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c2_f_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 3.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c2_e_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 2.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c2_d_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 10U, 15, "WordLength", 6, 8.0, 15, "FractionLength", 6,
    0.0, 15, "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6,
    0.0), true);
  sf_mex_assign(&c2_c_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 1.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c2_b_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
    "numerictype", 1U, 14U, 15, "SignednessBool", 3, false, 15, "Signedness", 15,
    "Unsigned", 15, "WordLength", 6, 8.0, 15, "FractionLength", 6, 0.0, 15,
    "BinaryPoint", 6, 0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0),
                true);
  sf_mex_assign(&c2_eml_mx, sf_mex_call_debug(sfGlobalDebugInstanceStruct,
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

static void initialize_params_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_gm_hdlcodercpu_eml(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_gm_hdlcodercpu_eml(SFc2_gm_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
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
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(20, 1), false);
  c2_hoistedGlobal = *c2_AC_data;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  c2_b_u = c2_u;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 2, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_b_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_d_eml_mx), 15,
    "simulinkarray", 14, c2_c_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = *c2_AC_func;
  c2_c_u = c2_b_hoistedGlobal;
  c2_d_y = NULL;
  c2_d_u = c2_c_u;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_d_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_f_eml_mx), 15,
    "simulinkarray", 14, c2_e_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c2_y, 1, c2_d_y);
  c2_c_hoistedGlobal = *c2_ALU_func;
  c2_e_u = c2_c_hoistedGlobal;
  c2_f_y = NULL;
  c2_f_u = c2_e_u;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_f_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_f_eml_mx), 15,
    "simulinkarray", 14, c2_g_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c2_y, 2, c2_f_y);
  c2_d_hoistedGlobal = *c2_DM_addr;
  c2_g_u = c2_d_hoistedGlobal;
  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", &c2_g_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 3, c2_h_y);
  c2_e_hoistedGlobal = *c2_DM_r_w;
  c2_h_u = c2_e_hoistedGlobal;
  c2_i_y = NULL;
  c2_i_u = c2_h_u;
  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", &c2_i_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_i_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_c_eml_mx), 15,
    "simulinkarray", 14, c2_j_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c2_y, 4, c2_i_y);
  c2_f_hoistedGlobal = *c2_IM_read;
  c2_j_u = c2_f_hoistedGlobal;
  c2_k_y = NULL;
  c2_k_u = c2_j_u;
  c2_l_y = NULL;
  sf_mex_assign(&c2_l_y, sf_mex_create("y", &c2_k_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_k_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_c_eml_mx), 15,
    "simulinkarray", 14, c2_l_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c2_y, 5, c2_k_y);
  c2_g_hoistedGlobal = *c2_IR_func;
  c2_l_u = c2_g_hoistedGlobal;
  c2_m_y = NULL;
  c2_m_u = c2_l_u;
  c2_n_y = NULL;
  sf_mex_assign(&c2_n_y, sf_mex_create("y", &c2_m_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_m_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_e_eml_mx), 15,
    "simulinkarray", 14, c2_n_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c2_y, 6, c2_m_y);
  c2_h_hoistedGlobal = *c2_PC_func;
  c2_n_u = c2_h_hoistedGlobal;
  c2_o_y = NULL;
  c2_o_u = c2_n_u;
  c2_p_y = NULL;
  sf_mex_assign(&c2_p_y, sf_mex_create("y", &c2_o_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_o_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_e_eml_mx), 15,
    "simulinkarray", 14, c2_p_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c2_y, 7, c2_o_y);
  c2_i_hoistedGlobal = *c2_addr_inc;
  c2_p_u = c2_i_hoistedGlobal;
  c2_q_y = NULL;
  c2_q_u = c2_p_u;
  c2_r_y = NULL;
  sf_mex_assign(&c2_r_y, sf_mex_create("y", &c2_q_u, 2, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_q_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_d_eml_mx), 15,
    "simulinkarray", 14, c2_r_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c2_y, 8, c2_q_y);
  c2_j_hoistedGlobal = *c2_hlt;
  c2_r_u = c2_j_hoistedGlobal;
  c2_s_y = NULL;
  sf_mex_assign(&c2_s_y, sf_mex_create("y", &c2_r_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 9, c2_s_y);
  c2_k_hoistedGlobal = *c2_out_flags;
  c2_s_u = c2_k_hoistedGlobal;
  c2_t_y = NULL;
  c2_t_u = c2_s_u;
  c2_u_y = NULL;
  sf_mex_assign(&c2_u_y, sf_mex_create("y", &c2_t_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_t_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_g_eml_mx), 15,
    "simulinkarray", 14, c2_u_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c2_y, 10, c2_t_y);
  c2_l_hoistedGlobal = *c2_print_data;
  c2_u_u = c2_l_hoistedGlobal;
  c2_v_y = NULL;
  sf_mex_assign(&c2_v_y, sf_mex_create("y", &c2_u_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 11, c2_v_y);
  c2_m_hoistedGlobal = *c2_shifter_sel;
  c2_v_u = c2_m_hoistedGlobal;
  c2_w_y = NULL;
  c2_w_u = c2_v_u;
  c2_x_y = NULL;
  sf_mex_assign(&c2_x_y, sf_mex_create("y", &c2_w_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_w_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
    (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_e_eml_mx), 15,
    "simulinkarray", 14, c2_x_y, 15, "fimathislocal", 3, true), false);
  sf_mex_setcell(c2_y, 12, c2_w_y);
  c2_n_hoistedGlobal = chartInstance->c2_CPU_state;
  c2_x_u = c2_n_hoistedGlobal;
  c2_y_y = NULL;
  if (!chartInstance->c2_CPU_state_not_empty) {
    sf_mex_assign(&c2_y_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_y_y, sf_mex_create("y", &c2_x_u, 3, 0U, 0U, 0U, 0), false);
  }

  sf_mex_setcell(c2_y, 13, c2_y_y);
  c2_o_hoistedGlobal = chartInstance->c2_address_data;
  c2_y_u = c2_o_hoistedGlobal;
  c2_ab_y = NULL;
  if (!chartInstance->c2_address_data_not_empty) {
    sf_mex_assign(&c2_ab_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    c2_ab_u = c2_y_u;
    c2_bb_y = NULL;
    sf_mex_assign(&c2_bb_y, sf_mex_create("y", &c2_ab_u, 3, 0U, 0U, 0U, 0),
                  false);
    sf_mex_assign(&c2_ab_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx), 15,
      "simulinkarray", 14, c2_bb_y, 15, "fimathislocal", 3, true), false);
  }

  sf_mex_setcell(c2_y, 14, c2_ab_y);
  c2_p_hoistedGlobal = chartInstance->c2_indirect_address;
  c2_bb_u = c2_p_hoistedGlobal;
  c2_cb_y = NULL;
  if (!chartInstance->c2_indirect_address_not_empty) {
    sf_mex_assign(&c2_cb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_cb_y, sf_mex_create("y", &c2_bb_u, 3, 0U, 0U, 0U, 0),
                  false);
  }

  sf_mex_setcell(c2_y, 15, c2_cb_y);
  c2_q_hoistedGlobal = chartInstance->c2_major_opcode;
  c2_cb_u = c2_q_hoistedGlobal;
  c2_db_y = NULL;
  if (!chartInstance->c2_major_opcode_not_empty) {
    sf_mex_assign(&c2_db_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    c2_db_u = c2_cb_u;
    c2_eb_y = NULL;
    sf_mex_assign(&c2_eb_y, sf_mex_create("y", &c2_db_u, 3, 0U, 0U, 0U, 0),
                  false);
    sf_mex_assign(&c2_db_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx), 15,
      "simulinkarray", 14, c2_eb_y, 15, "fimathislocal", 3, true), false);
  }

  sf_mex_setcell(c2_y, 16, c2_db_y);
  c2_r_hoistedGlobal = chartInstance->c2_minor_opcode;
  c2_eb_u = c2_r_hoistedGlobal;
  c2_fb_y = NULL;
  if (!chartInstance->c2_minor_opcode_not_empty) {
    sf_mex_assign(&c2_fb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    c2_fb_u = c2_eb_u;
    c2_gb_y = NULL;
    sf_mex_assign(&c2_gb_y, sf_mex_create("y", &c2_fb_u, 3, 0U, 0U, 0U, 0),
                  false);
    sf_mex_assign(&c2_fb_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx), 15,
      "simulinkarray", 14, c2_gb_y, 15, "fimathislocal", 3, true), false);
  }

  sf_mex_setcell(c2_y, 17, c2_fb_y);
  c2_s_hoistedGlobal = chartInstance->c2_previous_CPU_state;
  c2_gb_u = c2_s_hoistedGlobal;
  c2_hb_y = NULL;
  if (!chartInstance->c2_previous_CPU_state_not_empty) {
    sf_mex_assign(&c2_hb_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  false);
  } else {
    sf_mex_assign(&c2_hb_y, sf_mex_create("y", &c2_gb_u, 3, 0U, 0U, 0U, 0),
                  false);
  }

  sf_mex_setcell(c2_y, 18, c2_hb_y);
  c2_t_hoistedGlobal = chartInstance->c2_is_active_c2_gm_hdlcodercpu_eml;
  c2_hb_u = c2_t_hoistedGlobal;
  c2_ib_y = NULL;
  sf_mex_assign(&c2_ib_y, sf_mex_create("y", &c2_hb_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 19, c2_ib_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance, const mxArray *c2_st)
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
  chartInstance->c2_doneDoubleBufferReInit = true;
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
  chartInstance->c2_is_active_c2_gm_hdlcodercpu_eml = c2_m_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 19)),
     "is_active_c2_gm_hdlcodercpu_eml");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_gm_hdlcodercpu_eml(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_gm_hdlcodercpu_eml(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
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

static void sf_gateway_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
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
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_data_in, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_in_flags, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c2_master_rst, 2U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_gm_hdlcodercpu_eml(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_gm_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
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
}

static void c2_chartstep_c2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
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
  const mxArray *c2_T = NULL;
  const mxArray *c2_F = NULL;
  const mxArray *c2_val = NULL;
  const mxArray *c2_unusedU2 = NULL;
  const mxArray *c2_unusedU3 = NULL;
  const mxArray *c2_isfimathlocal = NULL;
  const mxArray *c2_b_T = NULL;
  const mxArray *c2_b_F = NULL;
  const mxArray *c2_b_val = NULL;
  const mxArray *c2_b_unusedU2 = NULL;
  const mxArray *c2_b_unusedU3 = NULL;
  const mxArray *c2_b_isfimathlocal = NULL;
  const mxArray *c2_c_T = NULL;
  const mxArray *c2_c_F = NULL;
  const mxArray *c2_c_val = NULL;
  const mxArray *c2_c_unusedU2 = NULL;
  const mxArray *c2_c_unusedU3 = NULL;
  const mxArray *c2_c_isfimathlocal = NULL;
  const mxArray *c2_d_T = NULL;
  const mxArray *c2_d_F = NULL;
  const mxArray *c2_d_val = NULL;
  const mxArray *c2_d_unusedU2 = NULL;
  const mxArray *c2_d_unusedU3 = NULL;
  const mxArray *c2_d_isfimathlocal = NULL;
  const mxArray *c2_e_T = NULL;
  const mxArray *c2_e_F = NULL;
  const mxArray *c2_e_val = NULL;
  const mxArray *c2_e_unusedU2 = NULL;
  const mxArray *c2_e_unusedU3 = NULL;
  const mxArray *c2_e_isfimathlocal = NULL;
  const mxArray *c2_f_T = NULL;
  const mxArray *c2_f_F = NULL;
  const mxArray *c2_f_val = NULL;
  const mxArray *c2_f_unusedU2 = NULL;
  const mxArray *c2_f_unusedU3 = NULL;
  const mxArray *c2_f_isfimathlocal = NULL;
  const mxArray *c2_g_T = NULL;
  const mxArray *c2_g_F = NULL;
  const mxArray *c2_g_val = NULL;
  const mxArray *c2_g_unusedU2 = NULL;
  const mxArray *c2_g_unusedU3 = NULL;
  const mxArray *c2_g_isfimathlocal = NULL;
  const mxArray *c2_h_T = NULL;
  const mxArray *c2_h_F = NULL;
  const mxArray *c2_h_val = NULL;
  const mxArray *c2_h_unusedU2 = NULL;
  const mxArray *c2_h_unusedU3 = NULL;
  const mxArray *c2_h_isfimathlocal = NULL;
  const mxArray *c2_i_T = NULL;
  const mxArray *c2_i_F = NULL;
  const mxArray *c2_i_val = NULL;
  const mxArray *c2_i_unusedU2 = NULL;
  const mxArray *c2_i_unusedU3 = NULL;
  const mxArray *c2_i_isfimathlocal = NULL;
  const mxArray *c2_j_T = NULL;
  const mxArray *c2_j_F = NULL;
  const mxArray *c2_j_val = NULL;
  const mxArray *c2_j_unusedU2 = NULL;
  const mxArray *c2_j_unusedU3 = NULL;
  const mxArray *c2_j_isfimathlocal = NULL;
  const mxArray *c2_k_T = NULL;
  const mxArray *c2_k_F = NULL;
  const mxArray *c2_k_val = NULL;
  const mxArray *c2_k_unusedU2 = NULL;
  const mxArray *c2_k_unusedU3 = NULL;
  const mxArray *c2_k_isfimathlocal = NULL;
  const mxArray *c2_l_T = NULL;
  const mxArray *c2_l_F = NULL;
  const mxArray *c2_l_val = NULL;
  const mxArray *c2_l_unusedU2 = NULL;
  const mxArray *c2_l_unusedU3 = NULL;
  const mxArray *c2_l_isfimathlocal = NULL;
  const mxArray *c2_m_T = NULL;
  const mxArray *c2_m_F = NULL;
  const mxArray *c2_m_val = NULL;
  const mxArray *c2_m_unusedU2 = NULL;
  const mxArray *c2_m_unusedU3 = NULL;
  const mxArray *c2_m_isfimathlocal = NULL;
  const mxArray *c2_n_T = NULL;
  const mxArray *c2_n_F = NULL;
  const mxArray *c2_n_val = NULL;
  const mxArray *c2_n_unusedU2 = NULL;
  const mxArray *c2_n_unusedU3 = NULL;
  const mxArray *c2_n_isfimathlocal = NULL;
  const mxArray *c2_o_T = NULL;
  const mxArray *c2_o_F = NULL;
  const mxArray *c2_o_val = NULL;
  const mxArray *c2_o_unusedU2 = NULL;
  const mxArray *c2_o_unusedU3 = NULL;
  const mxArray *c2_o_isfimathlocal = NULL;
  const mxArray *c2_p_T = NULL;
  const mxArray *c2_p_F = NULL;
  const mxArray *c2_p_val = NULL;
  const mxArray *c2_p_unusedU2 = NULL;
  const mxArray *c2_p_unusedU3 = NULL;
  const mxArray *c2_p_isfimathlocal = NULL;
  const mxArray *c2_q_T = NULL;
  const mxArray *c2_q_F = NULL;
  const mxArray *c2_q_val = NULL;
  const mxArray *c2_q_unusedU2 = NULL;
  const mxArray *c2_q_unusedU3 = NULL;
  const mxArray *c2_q_isfimathlocal = NULL;
  const mxArray *c2_r_T = NULL;
  const mxArray *c2_r_F = NULL;
  const mxArray *c2_r_val = NULL;
  const mxArray *c2_r_unusedU2 = NULL;
  const mxArray *c2_r_unusedU3 = NULL;
  const mxArray *c2_r_isfimathlocal = NULL;
  const mxArray *c2_s_T = NULL;
  const mxArray *c2_s_F = NULL;
  const mxArray *c2_s_val = NULL;
  const mxArray *c2_s_unusedU2 = NULL;
  const mxArray *c2_s_unusedU3 = NULL;
  const mxArray *c2_s_isfimathlocal = NULL;
  uint16_T c2_varargin_1;
  uint16_T c2_b_varargin_1;
  uint16_T c2_var1;
  uint8_T c2_hfi;
  const mxArray *c2_t_T = NULL;
  const mxArray *c2_t_F = NULL;
  const mxArray *c2_t_val = NULL;
  const mxArray *c2_isautoscaled = NULL;
  const mxArray *c2_pvpairsetdata = NULL;
  const mxArray *c2_t_isfimathlocal = NULL;
  const mxArray *c2_u_T = NULL;
  const mxArray *c2_u_F = NULL;
  const mxArray *c2_u_val = NULL;
  const mxArray *c2_t_unusedU2 = NULL;
  const mxArray *c2_t_unusedU3 = NULL;
  const mxArray *c2_u_isfimathlocal = NULL;
  uint16_T c2_c_varargin_1;
  uint16_T c2_d_varargin_1;
  uint16_T c2_b_var1;
  uint8_T c2_b_hfi;
  const mxArray *c2_v_T = NULL;
  const mxArray *c2_v_F = NULL;
  const mxArray *c2_v_val = NULL;
  const mxArray *c2_b_isautoscaled = NULL;
  const mxArray *c2_b_pvpairsetdata = NULL;
  const mxArray *c2_v_isfimathlocal = NULL;
  const mxArray *c2_w_T = NULL;
  const mxArray *c2_w_F = NULL;
  const mxArray *c2_w_val = NULL;
  const mxArray *c2_u_unusedU2 = NULL;
  const mxArray *c2_u_unusedU3 = NULL;
  const mxArray *c2_w_isfimathlocal = NULL;
  uint16_T c2_e_varargin_1;
  uint16_T c2_f_varargin_1;
  uint16_T c2_c_var1;
  uint8_T c2_c_hfi;
  const mxArray *c2_x_T = NULL;
  const mxArray *c2_x_F = NULL;
  const mxArray *c2_x_val = NULL;
  const mxArray *c2_c_isautoscaled = NULL;
  const mxArray *c2_c_pvpairsetdata = NULL;
  const mxArray *c2_x_isfimathlocal = NULL;
  const mxArray *c2_y_T = NULL;
  const mxArray *c2_y_F = NULL;
  const mxArray *c2_y_val = NULL;
  const mxArray *c2_v_unusedU2 = NULL;
  const mxArray *c2_v_unusedU3 = NULL;
  const mxArray *c2_y_isfimathlocal = NULL;
  const mxArray *c2_ab_T = NULL;
  const mxArray *c2_ab_F = NULL;
  const mxArray *c2_ab_val = NULL;
  const mxArray *c2_w_unusedU2 = NULL;
  const mxArray *c2_w_unusedU3 = NULL;
  const mxArray *c2_ab_isfimathlocal = NULL;
  const mxArray *c2_bb_T = NULL;
  const mxArray *c2_bb_F = NULL;
  const mxArray *c2_bb_val = NULL;
  const mxArray *c2_x_unusedU2 = NULL;
  const mxArray *c2_x_unusedU3 = NULL;
  const mxArray *c2_bb_isfimathlocal = NULL;
  const mxArray *c2_cb_T = NULL;
  const mxArray *c2_cb_F = NULL;
  const mxArray *c2_cb_val = NULL;
  const mxArray *c2_y_unusedU2 = NULL;
  const mxArray *c2_y_unusedU3 = NULL;
  const mxArray *c2_cb_isfimathlocal = NULL;
  uint8_T c2_e_hoistedGlobal;
  uint8_T c2_a;
  uint8_T c2_a1;
  uint8_T c2_slice_temp;
  uint8_T c2_f_hoistedGlobal;
  uint8_T c2_g_varargin_1;
  uint8_T c2_h_varargin_1;
  uint8_T c2_d_var1;
  int8_T c2_i0;
  const mxArray *c2_db_T = NULL;
  const mxArray *c2_db_F = NULL;
  const mxArray *c2_db_val = NULL;
  const mxArray *c2_d_isautoscaled = NULL;
  const mxArray *c2_d_pvpairsetdata = NULL;
  const mxArray *c2_db_isfimathlocal = NULL;
  int8_T c2_i_varargin_1;
  int8_T c2_j_varargin_1;
  int8_T c2_e_var1;
  const mxArray *c2_eb_T = NULL;
  const mxArray *c2_eb_F = NULL;
  const mxArray *c2_eb_val = NULL;
  const mxArray *c2_e_isautoscaled = NULL;
  const mxArray *c2_e_pvpairsetdata = NULL;
  const mxArray *c2_eb_isfimathlocal = NULL;
  const mxArray *c2_fb_T = NULL;
  const mxArray *c2_fb_F = NULL;
  const mxArray *c2_fb_val = NULL;
  const mxArray *c2_ab_unusedU2 = NULL;
  const mxArray *c2_ab_unusedU3 = NULL;
  const mxArray *c2_fb_isfimathlocal = NULL;
  uint8_T c2_g_hoistedGlobal;
  uint8_T c2_k_varargin_1;
  uint8_T c2_l_varargin_1;
  uint8_T c2_f_var1;
  const mxArray *c2_gb_T = NULL;
  const mxArray *c2_gb_F = NULL;
  const mxArray *c2_gb_val = NULL;
  const mxArray *c2_f_isautoscaled = NULL;
  const mxArray *c2_f_pvpairsetdata = NULL;
  const mxArray *c2_gb_isfimathlocal = NULL;
  const mxArray *c2_hb_T = NULL;
  const mxArray *c2_hb_F = NULL;
  const mxArray *c2_hb_val = NULL;
  const mxArray *c2_bb_unusedU2 = NULL;
  const mxArray *c2_bb_unusedU3 = NULL;
  const mxArray *c2_hb_isfimathlocal = NULL;
  uint8_T c2_h_hoistedGlobal;
  uint8_T c2_b_a;
  uint8_T c2_b_a1;
  uint8_T c2_b_slice_temp;
  const mxArray *c2_ib_T = NULL;
  const mxArray *c2_ib_F = NULL;
  const mxArray *c2_ib_val = NULL;
  const mxArray *c2_cb_unusedU2 = NULL;
  const mxArray *c2_cb_unusedU3 = NULL;
  const mxArray *c2_ib_isfimathlocal = NULL;
  const mxArray *c2_jb_T = NULL;
  const mxArray *c2_jb_F = NULL;
  const mxArray *c2_jb_val = NULL;
  const mxArray *c2_db_unusedU2 = NULL;
  const mxArray *c2_db_unusedU3 = NULL;
  const mxArray *c2_jb_isfimathlocal = NULL;
  uint8_T c2_i_hoistedGlobal;
  uint8_T c2_c_a;
  uint8_T c2_c_a1;
  uint8_T c2_c_slice_temp;
  uint8_T c2_d_a;
  uint8_T c2_d_a1;
  uint8_T c2_d_slice_temp;
  uint8_T c2_j_hoistedGlobal;
  uint8_T c2_m_varargin_1;
  uint8_T c2_n_varargin_1;
  uint8_T c2_g_var1;
  int8_T c2_i1;
  const mxArray *c2_kb_T = NULL;
  const mxArray *c2_kb_F = NULL;
  const mxArray *c2_kb_val = NULL;
  const mxArray *c2_g_isautoscaled = NULL;
  const mxArray *c2_g_pvpairsetdata = NULL;
  const mxArray *c2_kb_isfimathlocal = NULL;
  int8_T c2_o_varargin_1;
  int8_T c2_p_varargin_1;
  int8_T c2_h_var1;
  const mxArray *c2_lb_T = NULL;
  const mxArray *c2_lb_F = NULL;
  const mxArray *c2_lb_val = NULL;
  const mxArray *c2_h_isautoscaled = NULL;
  const mxArray *c2_h_pvpairsetdata = NULL;
  const mxArray *c2_lb_isfimathlocal = NULL;
  const mxArray *c2_mb_T = NULL;
  const mxArray *c2_mb_F = NULL;
  const mxArray *c2_mb_val = NULL;
  const mxArray *c2_eb_unusedU2 = NULL;
  const mxArray *c2_eb_unusedU3 = NULL;
  const mxArray *c2_mb_isfimathlocal = NULL;
  uint8_T c2_e_a;
  uint8_T c2_e_a1;
  uint8_T c2_e_slice_temp;
  uint8_T c2_k_hoistedGlobal;
  uint8_T c2_q_varargin_1;
  uint8_T c2_r_varargin_1;
  uint8_T c2_i_var1;
  int8_T c2_i2;
  const mxArray *c2_nb_T = NULL;
  const mxArray *c2_nb_F = NULL;
  const mxArray *c2_nb_val = NULL;
  const mxArray *c2_i_isautoscaled = NULL;
  const mxArray *c2_i_pvpairsetdata = NULL;
  const mxArray *c2_nb_isfimathlocal = NULL;
  int8_T c2_s_varargin_1;
  int8_T c2_t_varargin_1;
  int8_T c2_j_var1;
  const mxArray *c2_ob_T = NULL;
  const mxArray *c2_ob_F = NULL;
  const mxArray *c2_ob_val = NULL;
  const mxArray *c2_j_isautoscaled = NULL;
  const mxArray *c2_j_pvpairsetdata = NULL;
  const mxArray *c2_ob_isfimathlocal = NULL;
  const mxArray *c2_pb_T = NULL;
  const mxArray *c2_pb_F = NULL;
  const mxArray *c2_pb_val = NULL;
  const mxArray *c2_fb_unusedU2 = NULL;
  const mxArray *c2_fb_unusedU3 = NULL;
  const mxArray *c2_pb_isfimathlocal = NULL;
  uint8_T c2_l_hoistedGlobal;
  uint8_T c2_f_a;
  uint8_T c2_f_a1;
  uint8_T c2_f_slice_temp;
  uint8_T c2_m_hoistedGlobal;
  uint8_T c2_g_a;
  uint8_T c2_g_a1;
  uint8_T c2_g_slice_temp;
  uint8_T c2_h_a;
  uint8_T c2_h_a1;
  uint8_T c2_h_slice_temp;
  uint8_T c2_n_hoistedGlobal;
  uint8_T c2_u_varargin_1;
  uint8_T c2_v_varargin_1;
  uint8_T c2_k_var1;
  int8_T c2_i3;
  const mxArray *c2_qb_T = NULL;
  const mxArray *c2_qb_F = NULL;
  const mxArray *c2_qb_val = NULL;
  const mxArray *c2_k_isautoscaled = NULL;
  const mxArray *c2_k_pvpairsetdata = NULL;
  const mxArray *c2_qb_isfimathlocal = NULL;
  int8_T c2_w_varargin_1;
  int8_T c2_x_varargin_1;
  int8_T c2_l_var1;
  const mxArray *c2_rb_T = NULL;
  const mxArray *c2_rb_F = NULL;
  const mxArray *c2_rb_val = NULL;
  const mxArray *c2_l_isautoscaled = NULL;
  const mxArray *c2_l_pvpairsetdata = NULL;
  const mxArray *c2_rb_isfimathlocal = NULL;
  const mxArray *c2_sb_T = NULL;
  const mxArray *c2_sb_F = NULL;
  const mxArray *c2_sb_val = NULL;
  const mxArray *c2_gb_unusedU2 = NULL;
  const mxArray *c2_gb_unusedU3 = NULL;
  const mxArray *c2_sb_isfimathlocal = NULL;
  uint8_T c2_i_a;
  uint8_T c2_i_a1;
  uint8_T c2_i_slice_temp;
  uint8_T c2_o_hoistedGlobal;
  uint8_T c2_y_varargin_1;
  uint8_T c2_ab_varargin_1;
  uint8_T c2_m_var1;
  int8_T c2_i4;
  const mxArray *c2_tb_T = NULL;
  const mxArray *c2_tb_F = NULL;
  const mxArray *c2_tb_val = NULL;
  const mxArray *c2_m_isautoscaled = NULL;
  const mxArray *c2_m_pvpairsetdata = NULL;
  const mxArray *c2_tb_isfimathlocal = NULL;
  int8_T c2_bb_varargin_1;
  int8_T c2_cb_varargin_1;
  int8_T c2_n_var1;
  const mxArray *c2_ub_T = NULL;
  const mxArray *c2_ub_F = NULL;
  const mxArray *c2_ub_val = NULL;
  const mxArray *c2_n_isautoscaled = NULL;
  const mxArray *c2_n_pvpairsetdata = NULL;
  const mxArray *c2_ub_isfimathlocal = NULL;
  const mxArray *c2_vb_T = NULL;
  const mxArray *c2_vb_F = NULL;
  const mxArray *c2_vb_val = NULL;
  const mxArray *c2_hb_unusedU2 = NULL;
  const mxArray *c2_hb_unusedU3 = NULL;
  const mxArray *c2_vb_isfimathlocal = NULL;
  const mxArray *c2_wb_T = NULL;
  const mxArray *c2_wb_F = NULL;
  const mxArray *c2_wb_val = NULL;
  const mxArray *c2_ib_unusedU2 = NULL;
  const mxArray *c2_ib_unusedU3 = NULL;
  const mxArray *c2_wb_isfimathlocal = NULL;
  const mxArray *c2_xb_T = NULL;
  const mxArray *c2_xb_F = NULL;
  const mxArray *c2_xb_val = NULL;
  const mxArray *c2_jb_unusedU2 = NULL;
  const mxArray *c2_jb_unusedU3 = NULL;
  const mxArray *c2_xb_isfimathlocal = NULL;
  const mxArray *c2_yb_T = NULL;
  const mxArray *c2_yb_F = NULL;
  const mxArray *c2_yb_val = NULL;
  const mxArray *c2_kb_unusedU2 = NULL;
  const mxArray *c2_kb_unusedU3 = NULL;
  const mxArray *c2_yb_isfimathlocal = NULL;
  const mxArray *c2_ac_T = NULL;
  const mxArray *c2_ac_F = NULL;
  const mxArray *c2_ac_val = NULL;
  const mxArray *c2_lb_unusedU2 = NULL;
  const mxArray *c2_lb_unusedU3 = NULL;
  const mxArray *c2_ac_isfimathlocal = NULL;
  const mxArray *c2_bc_T = NULL;
  const mxArray *c2_bc_F = NULL;
  const mxArray *c2_bc_val = NULL;
  const mxArray *c2_mb_unusedU2 = NULL;
  const mxArray *c2_mb_unusedU3 = NULL;
  const mxArray *c2_bc_isfimathlocal = NULL;
  const mxArray *c2_cc_T = NULL;
  const mxArray *c2_cc_F = NULL;
  const mxArray *c2_cc_val = NULL;
  const mxArray *c2_nb_unusedU2 = NULL;
  const mxArray *c2_nb_unusedU3 = NULL;
  const mxArray *c2_cc_isfimathlocal = NULL;
  const mxArray *c2_dc_T = NULL;
  const mxArray *c2_dc_F = NULL;
  const mxArray *c2_dc_val = NULL;
  const mxArray *c2_ob_unusedU2 = NULL;
  const mxArray *c2_ob_unusedU3 = NULL;
  const mxArray *c2_dc_isfimathlocal = NULL;
  const mxArray *c2_ec_T = NULL;
  const mxArray *c2_ec_F = NULL;
  const mxArray *c2_ec_val = NULL;
  const mxArray *c2_pb_unusedU2 = NULL;
  const mxArray *c2_pb_unusedU3 = NULL;
  const mxArray *c2_ec_isfimathlocal = NULL;
  const mxArray *c2_fc_T = NULL;
  const mxArray *c2_fc_F = NULL;
  const mxArray *c2_fc_val = NULL;
  const mxArray *c2_qb_unusedU2 = NULL;
  const mxArray *c2_qb_unusedU3 = NULL;
  const mxArray *c2_fc_isfimathlocal = NULL;
  const mxArray *c2_gc_T = NULL;
  const mxArray *c2_gc_F = NULL;
  const mxArray *c2_gc_val = NULL;
  const mxArray *c2_rb_unusedU2 = NULL;
  const mxArray *c2_rb_unusedU3 = NULL;
  const mxArray *c2_gc_isfimathlocal = NULL;
  const mxArray *c2_hc_T = NULL;
  const mxArray *c2_hc_F = NULL;
  const mxArray *c2_hc_val = NULL;
  const mxArray *c2_sb_unusedU2 = NULL;
  const mxArray *c2_sb_unusedU3 = NULL;
  const mxArray *c2_hc_isfimathlocal = NULL;
  const mxArray *c2_ic_T = NULL;
  const mxArray *c2_ic_F = NULL;
  const mxArray *c2_ic_val = NULL;
  const mxArray *c2_tb_unusedU2 = NULL;
  const mxArray *c2_tb_unusedU3 = NULL;
  const mxArray *c2_ic_isfimathlocal = NULL;
  const mxArray *c2_jc_T = NULL;
  const mxArray *c2_jc_F = NULL;
  const mxArray *c2_jc_val = NULL;
  const mxArray *c2_ub_unusedU2 = NULL;
  const mxArray *c2_ub_unusedU3 = NULL;
  const mxArray *c2_jc_isfimathlocal = NULL;
  const mxArray *c2_kc_T = NULL;
  const mxArray *c2_kc_F = NULL;
  const mxArray *c2_kc_val = NULL;
  const mxArray *c2_vb_unusedU2 = NULL;
  const mxArray *c2_vb_unusedU3 = NULL;
  const mxArray *c2_kc_isfimathlocal = NULL;
  const mxArray *c2_lc_T = NULL;
  const mxArray *c2_lc_F = NULL;
  const mxArray *c2_lc_val = NULL;
  const mxArray *c2_wb_unusedU2 = NULL;
  const mxArray *c2_wb_unusedU3 = NULL;
  const mxArray *c2_lc_isfimathlocal = NULL;
  const mxArray *c2_mc_T = NULL;
  const mxArray *c2_mc_F = NULL;
  const mxArray *c2_mc_val = NULL;
  const mxArray *c2_xb_unusedU2 = NULL;
  const mxArray *c2_xb_unusedU3 = NULL;
  const mxArray *c2_mc_isfimathlocal = NULL;
  const mxArray *c2_nc_T = NULL;
  const mxArray *c2_nc_F = NULL;
  const mxArray *c2_nc_val = NULL;
  const mxArray *c2_yb_unusedU2 = NULL;
  const mxArray *c2_yb_unusedU3 = NULL;
  const mxArray *c2_nc_isfimathlocal = NULL;
  const mxArray *c2_oc_T = NULL;
  const mxArray *c2_oc_F = NULL;
  const mxArray *c2_oc_val = NULL;
  const mxArray *c2_ac_unusedU2 = NULL;
  const mxArray *c2_ac_unusedU3 = NULL;
  const mxArray *c2_oc_isfimathlocal = NULL;
  uint8_T c2_p_hoistedGlobal;
  uint8_T c2_j_a;
  uint8_T c2_j_a1;
  uint8_T c2_j_slice_temp;
  const mxArray *c2_pc_T = NULL;
  const mxArray *c2_pc_F = NULL;
  const mxArray *c2_pc_val = NULL;
  const mxArray *c2_bc_unusedU2 = NULL;
  const mxArray *c2_bc_unusedU3 = NULL;
  const mxArray *c2_pc_isfimathlocal = NULL;
  const mxArray *c2_qc_T = NULL;
  const mxArray *c2_qc_F = NULL;
  const mxArray *c2_qc_val = NULL;
  const mxArray *c2_cc_unusedU2 = NULL;
  const mxArray *c2_cc_unusedU3 = NULL;
  const mxArray *c2_qc_isfimathlocal = NULL;
  const mxArray *c2_rc_T = NULL;
  const mxArray *c2_rc_F = NULL;
  const mxArray *c2_rc_val = NULL;
  const mxArray *c2_dc_unusedU2 = NULL;
  const mxArray *c2_dc_unusedU3 = NULL;
  const mxArray *c2_rc_isfimathlocal = NULL;
  uint8_T c2_q_hoistedGlobal;
  uint8_T c2_k_a;
  uint8_T c2_k_a1;
  uint8_T c2_k_slice_temp;
  const mxArray *c2_sc_T = NULL;
  const mxArray *c2_sc_F = NULL;
  const mxArray *c2_sc_val = NULL;
  const mxArray *c2_ec_unusedU2 = NULL;
  const mxArray *c2_ec_unusedU3 = NULL;
  const mxArray *c2_sc_isfimathlocal = NULL;
  const mxArray *c2_tc_T = NULL;
  const mxArray *c2_tc_F = NULL;
  const mxArray *c2_tc_val = NULL;
  const mxArray *c2_fc_unusedU2 = NULL;
  const mxArray *c2_fc_unusedU3 = NULL;
  const mxArray *c2_tc_isfimathlocal = NULL;
  const mxArray *c2_uc_T = NULL;
  const mxArray *c2_uc_F = NULL;
  const mxArray *c2_uc_val = NULL;
  const mxArray *c2_gc_unusedU2 = NULL;
  const mxArray *c2_gc_unusedU3 = NULL;
  const mxArray *c2_uc_isfimathlocal = NULL;
  uint8_T c2_r_hoistedGlobal;
  uint8_T c2_l_a;
  uint8_T c2_l_a1;
  uint8_T c2_l_slice_temp;
  const mxArray *c2_vc_T = NULL;
  const mxArray *c2_vc_F = NULL;
  const mxArray *c2_vc_val = NULL;
  const mxArray *c2_hc_unusedU2 = NULL;
  const mxArray *c2_hc_unusedU3 = NULL;
  const mxArray *c2_vc_isfimathlocal = NULL;
  const mxArray *c2_wc_T = NULL;
  const mxArray *c2_wc_F = NULL;
  const mxArray *c2_wc_val = NULL;
  const mxArray *c2_ic_unusedU2 = NULL;
  const mxArray *c2_ic_unusedU3 = NULL;
  const mxArray *c2_wc_isfimathlocal = NULL;
  const mxArray *c2_xc_T = NULL;
  const mxArray *c2_xc_F = NULL;
  const mxArray *c2_xc_val = NULL;
  const mxArray *c2_jc_unusedU2 = NULL;
  const mxArray *c2_jc_unusedU3 = NULL;
  const mxArray *c2_xc_isfimathlocal = NULL;
  uint8_T c2_s_hoistedGlobal;
  uint8_T c2_m_a;
  uint8_T c2_m_a1;
  uint8_T c2_m_slice_temp;
  const mxArray *c2_yc_T = NULL;
  const mxArray *c2_yc_F = NULL;
  const mxArray *c2_yc_val = NULL;
  const mxArray *c2_kc_unusedU2 = NULL;
  const mxArray *c2_kc_unusedU3 = NULL;
  const mxArray *c2_yc_isfimathlocal = NULL;
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
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 35U, 35U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_hdl_fm, 0U, c2_t_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_mask, 1U, c2_s_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_minor_opcode_bit6, 2U,
    c2_h_sf_marshallOut, c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_temp_address_data, 3U,
    c2_r_sf_marshallOut, c2_p_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_indirect_bit, 4U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c, 5U, c2_q_sf_marshallOut,
    c2_o_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_n, 6U, c2_q_sf_marshallOut,
    c2_o_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_minor_opcode_bit4, 7U,
    c2_h_sf_marshallOut, c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_v, 8U, c2_q_sf_marshallOut,
    c2_o_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_z, 9U, c2_q_sf_marshallOut,
    c2_o_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 10U, c2_p_sf_marshallOut,
    c2_n_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 11U, c2_p_sf_marshallOut,
    c2_n_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_data_in, 12U, c2_o_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_in_flags, 13U, c2_m_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_master_rst, 14U, c2_l_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_IR_in, 15U, c2_n_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_shifter_sel, 16U, c2_j_sf_marshallOut,
    c2_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_out_flags, 17U, c2_m_sf_marshallOut,
    c2_m_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_ALU_func, 18U, c2_k_sf_marshallOut,
    c2_k_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_print_data, 19U, c2_l_sf_marshallOut,
    c2_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_DM_addr, 20U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_DM_r_w, 21U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_AC_func, 22U, c2_k_sf_marshallOut,
    c2_k_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_AC_data, 23U, c2_i_sf_marshallOut,
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_IR_func, 24U, c2_j_sf_marshallOut,
    c2_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_PC_func, 25U, c2_j_sf_marshallOut,
    c2_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_addr_inc, 26U, c2_i_sf_marshallOut,
    c2_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_IM_read, 27U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_hlt, 28U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_CPU_state, 29U,
    c2_f_sf_marshallOut, c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_previous_CPU_state,
    30U, c2_e_sf_marshallOut, c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_major_opcode, 31U,
    c2_d_sf_marshallOut, c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_minor_opcode, 32U,
    c2_c_sf_marshallOut, c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_address_data, 33U,
    c2_b_sf_marshallOut, c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c2_indirect_address, 34U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 63);
  c2_hdl_fm = c2_eml_mx;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 71);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 72);
  if (CV_EML_IF(0, 1, 0, !chartInstance->c2_CPU_state_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 73);
    chartInstance->c2_CPU_state = 0U;
    chartInstance->c2_CPU_state_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 76);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 77);
  if (CV_EML_IF(0, 1, 1, !chartInstance->c2_previous_CPU_state_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 78);
    chartInstance->c2_previous_CPU_state = 0U;
    chartInstance->c2_previous_CPU_state_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 81);
  if (CV_EML_IF(0, 1, 2, c2_master_rst)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 82);
    chartInstance->c2_CPU_state = 0U;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 85);
  c2_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c2_T);
  sf_mex_destroy(&c2_F);
  sf_mex_destroy(&c2_val);
  sf_mex_destroy(&c2_unusedU2);
  sf_mex_destroy(&c2_unusedU3);
  sf_mex_destroy(&c2_isfimathlocal);
  c2_shifter_sel = 0U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 86);
  c2_b_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c2_b_T);
  sf_mex_destroy(&c2_b_F);
  sf_mex_destroy(&c2_b_val);
  sf_mex_destroy(&c2_b_unusedU2);
  sf_mex_destroy(&c2_b_unusedU3);
  sf_mex_destroy(&c2_b_isfimathlocal);
  c2_ALU_func = 0U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 87);
  c2_out_flags = c2_in_flags;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 88);
  c2_b_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c2_c_T);
  sf_mex_destroy(&c2_c_F);
  sf_mex_destroy(&c2_c_val);
  sf_mex_destroy(&c2_c_unusedU2);
  sf_mex_destroy(&c2_c_unusedU3);
  sf_mex_destroy(&c2_c_isfimathlocal);
  c2_AC_func = 4U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 89);
  c2_c_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c2_d_T);
  sf_mex_destroy(&c2_d_F);
  sf_mex_destroy(&c2_d_val);
  sf_mex_destroy(&c2_d_unusedU2);
  sf_mex_destroy(&c2_d_unusedU3);
  sf_mex_destroy(&c2_d_isfimathlocal);
  c2_AC_data = 0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 90);
  c2_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c2_e_T);
  sf_mex_destroy(&c2_e_F);
  sf_mex_destroy(&c2_e_val);
  sf_mex_destroy(&c2_e_unusedU2);
  sf_mex_destroy(&c2_e_unusedU3);
  sf_mex_destroy(&c2_e_isfimathlocal);
  c2_IR_func = 3U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 91);
  c2_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c2_f_T);
  sf_mex_destroy(&c2_f_F);
  sf_mex_destroy(&c2_f_val);
  sf_mex_destroy(&c2_f_unusedU2);
  sf_mex_destroy(&c2_f_unusedU3);
  sf_mex_destroy(&c2_f_isfimathlocal);
  c2_PC_func = 3U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 92);
  c2_d_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c2_g_T);
  sf_mex_destroy(&c2_g_F);
  sf_mex_destroy(&c2_g_val);
  sf_mex_destroy(&c2_g_unusedU2);
  sf_mex_destroy(&c2_g_unusedU3);
  sf_mex_destroy(&c2_g_isfimathlocal);
  c2_IM_read = 0U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 93);
  c2_DM_addr = 0U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 94);
  c2_d_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c2_h_T);
  sf_mex_destroy(&c2_h_F);
  sf_mex_destroy(&c2_h_val);
  sf_mex_destroy(&c2_h_unusedU2);
  sf_mex_destroy(&c2_h_unusedU3);
  sf_mex_destroy(&c2_h_isfimathlocal);
  c2_DM_r_w = 0U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 95);
  c2_c_eml_fi_checkforconst(chartInstance);
  sf_mex_destroy(&c2_i_T);
  sf_mex_destroy(&c2_i_F);
  sf_mex_destroy(&c2_i_val);
  sf_mex_destroy(&c2_i_unusedU2);
  sf_mex_destroy(&c2_i_unusedU3);
  sf_mex_destroy(&c2_i_isfimathlocal);
  c2_addr_inc = 0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 96);
  c2_print_data = false;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 97);
  c2_hlt = 0U;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 105);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 106);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 107);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 108);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 110);
  if (CV_EML_IF(0, 1, 3, !chartInstance->c2_major_opcode_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 111);
    c2_e_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_j_T);
    sf_mex_destroy(&c2_j_F);
    sf_mex_destroy(&c2_j_val);
    sf_mex_destroy(&c2_j_unusedU2);
    sf_mex_destroy(&c2_j_unusedU3);
    sf_mex_destroy(&c2_j_isfimathlocal);
    chartInstance->c2_major_opcode = 0U;
    chartInstance->c2_major_opcode_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 112);
    c2_e_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_k_T);
    sf_mex_destroy(&c2_k_F);
    sf_mex_destroy(&c2_k_val);
    sf_mex_destroy(&c2_k_unusedU2);
    sf_mex_destroy(&c2_k_unusedU3);
    sf_mex_destroy(&c2_k_isfimathlocal);
    chartInstance->c2_minor_opcode = 0U;
    chartInstance->c2_minor_opcode_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 113);
    c2_e_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_l_T);
    sf_mex_destroy(&c2_l_F);
    sf_mex_destroy(&c2_l_val);
    sf_mex_destroy(&c2_l_unusedU2);
    sf_mex_destroy(&c2_l_unusedU3);
    sf_mex_destroy(&c2_l_isfimathlocal);
    chartInstance->c2_address_data = 0U;
    chartInstance->c2_address_data_not_empty = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 114);
    chartInstance->c2_indirect_address = 0U;
    chartInstance->c2_indirect_address_not_empty = true;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 117);
  switch (chartInstance->c2_CPU_state) {
   case 0U:
    CV_EML_SWITCH(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 122);
    c2_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_m_T);
    sf_mex_destroy(&c2_m_F);
    sf_mex_destroy(&c2_m_val);
    sf_mex_destroy(&c2_m_unusedU2);
    sf_mex_destroy(&c2_m_unusedU3);
    sf_mex_destroy(&c2_m_isfimathlocal);
    c2_PC_func = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 123);
    c2_b_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_n_T);
    sf_mex_destroy(&c2_n_F);
    sf_mex_destroy(&c2_n_val);
    sf_mex_destroy(&c2_n_unusedU2);
    sf_mex_destroy(&c2_n_unusedU3);
    sf_mex_destroy(&c2_n_isfimathlocal);
    c2_AC_func = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 124);
    c2_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_o_T);
    sf_mex_destroy(&c2_o_F);
    sf_mex_destroy(&c2_o_val);
    sf_mex_destroy(&c2_o_unusedU2);
    sf_mex_destroy(&c2_o_unusedU3);
    sf_mex_destroy(&c2_o_isfimathlocal);
    c2_IR_func = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 125);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 126);
    chartInstance->c2_CPU_state = 1U;
    break;

   case 1U:
    CV_EML_SWITCH(0, 1, 0, 2);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 133U);
    c2_d_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_p_T);
    sf_mex_destroy(&c2_p_F);
    sf_mex_destroy(&c2_p_val);
    sf_mex_destroy(&c2_p_unusedU2);
    sf_mex_destroy(&c2_p_unusedU3);
    sf_mex_destroy(&c2_p_isfimathlocal);
    c2_IM_read = 1U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 135U);
    c2_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_q_T);
    sf_mex_destroy(&c2_q_F);
    sf_mex_destroy(&c2_q_val);
    sf_mex_destroy(&c2_q_unusedU2);
    sf_mex_destroy(&c2_q_unusedU3);
    sf_mex_destroy(&c2_q_isfimathlocal);
    c2_PC_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 137U);
    c2_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_r_T);
    sf_mex_destroy(&c2_r_F);
    sf_mex_destroy(&c2_r_val);
    sf_mex_destroy(&c2_r_unusedU2);
    sf_mex_destroy(&c2_r_unusedU3);
    sf_mex_destroy(&c2_r_isfimathlocal);
    c2_IR_func = 1U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 139U);
    chartInstance->c2_CPU_state = 2U;
    break;

   case 2U:
    CV_EML_SWITCH(0, 1, 0, 3);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 143U);
    c2_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_s_T);
    sf_mex_destroy(&c2_s_F);
    sf_mex_destroy(&c2_s_val);
    sf_mex_destroy(&c2_s_unusedU2);
    sf_mex_destroy(&c2_s_unusedU3);
    sf_mex_destroy(&c2_s_isfimathlocal);
    c2_IR_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 146U);
    chartInstance->c2_CPU_state = 3U;
    break;

   case 3U:
    CV_EML_SWITCH(0, 1, 0, 4);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 150U);
    c2_varargin_1 = c2_bitsrl(chartInstance, c2_IR_in);
    c2_b_varargin_1 = c2_varargin_1;
    c2_e_eml_fi_checkforconst(chartInstance);
    c2_var1 = c2_b_varargin_1;
    c2_hfi = (uint8_T)c2_var1;
    sf_mex_destroy(&c2_t_T);
    sf_mex_destroy(&c2_t_F);
    sf_mex_destroy(&c2_t_val);
    sf_mex_destroy(&c2_isautoscaled);
    sf_mex_destroy(&c2_pvpairsetdata);
    sf_mex_destroy(&c2_t_isfimathlocal);
    chartInstance->c2_major_opcode = c2_hfi;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 151U);
    c2_f_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_u_T);
    sf_mex_destroy(&c2_u_F);
    sf_mex_destroy(&c2_u_val);
    sf_mex_destroy(&c2_t_unusedU2);
    sf_mex_destroy(&c2_t_unusedU3);
    sf_mex_destroy(&c2_u_isfimathlocal);
    c2_mask = 63U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 153U);
    c2_c_varargin_1 = c2_bitand(chartInstance, c2_b_bitsrl(chartInstance,
      c2_IR_in), 63U);
    c2_d_varargin_1 = c2_c_varargin_1;
    c2_e_eml_fi_checkforconst(chartInstance);
    c2_b_var1 = c2_d_varargin_1;
    c2_b_hfi = (uint8_T)c2_b_var1;
    sf_mex_destroy(&c2_v_T);
    sf_mex_destroy(&c2_v_F);
    sf_mex_destroy(&c2_v_val);
    sf_mex_destroy(&c2_b_isautoscaled);
    sf_mex_destroy(&c2_b_pvpairsetdata);
    sf_mex_destroy(&c2_v_isfimathlocal);
    chartInstance->c2_minor_opcode = c2_b_hfi;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 154U);
    c2_f_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_w_T);
    sf_mex_destroy(&c2_w_F);
    sf_mex_destroy(&c2_w_val);
    sf_mex_destroy(&c2_u_unusedU2);
    sf_mex_destroy(&c2_u_unusedU3);
    sf_mex_destroy(&c2_w_isfimathlocal);
    c2_mask = 255U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 156U);
    c2_e_varargin_1 = c2_bitand(chartInstance, c2_IR_in, 255U);
    c2_f_varargin_1 = c2_e_varargin_1;
    c2_e_eml_fi_checkforconst(chartInstance);
    c2_c_var1 = c2_f_varargin_1;
    c2_c_hfi = (uint8_T)c2_c_var1;
    sf_mex_destroy(&c2_x_T);
    sf_mex_destroy(&c2_x_F);
    sf_mex_destroy(&c2_x_val);
    sf_mex_destroy(&c2_c_isautoscaled);
    sf_mex_destroy(&c2_c_pvpairsetdata);
    sf_mex_destroy(&c2_x_isfimathlocal);
    chartInstance->c2_address_data = c2_c_hfi;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 159U);
    chartInstance->c2_CPU_state = 4U;
    break;

   case 4U:
    CV_EML_SWITCH(0, 1, 0, 5);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 165U);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 166U);
    switch (c2_b_uint8(chartInstance, chartInstance->c2_major_opcode)) {
     case 0U:
      CV_EML_SWITCH(0, 1, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 170U);
      c2_DM_addr = c2_b_uint8(chartInstance, chartInstance->c2_address_data);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 172U);
      c2_d_eml_fi_checkforconst(chartInstance);
      sf_mex_destroy(&c2_y_T);
      sf_mex_destroy(&c2_y_F);
      sf_mex_destroy(&c2_y_val);
      sf_mex_destroy(&c2_v_unusedU2);
      sf_mex_destroy(&c2_v_unusedU3);
      sf_mex_destroy(&c2_y_isfimathlocal);
      c2_DM_r_w = 0U;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 174U);
      chartInstance->c2_CPU_state = 13U;
      break;

     case 1U:
      CV_EML_SWITCH(0, 1, 1, 2);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 178U);
      c2_DM_addr = c2_b_uint8(chartInstance, chartInstance->c2_address_data);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 180U);
      c2_d_eml_fi_checkforconst(chartInstance);
      sf_mex_destroy(&c2_ab_T);
      sf_mex_destroy(&c2_ab_F);
      sf_mex_destroy(&c2_ab_val);
      sf_mex_destroy(&c2_w_unusedU2);
      sf_mex_destroy(&c2_w_unusedU3);
      sf_mex_destroy(&c2_ab_isfimathlocal);
      c2_DM_r_w = 0U;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 182U);
      chartInstance->c2_CPU_state = 15U;
      break;

     case 2U:
      CV_EML_SWITCH(0, 1, 1, 3);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 186U);
      c2_DM_addr = c2_b_uint8(chartInstance, chartInstance->c2_address_data);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 188U);
      c2_d_eml_fi_checkforconst(chartInstance);
      sf_mex_destroy(&c2_bb_T);
      sf_mex_destroy(&c2_bb_F);
      sf_mex_destroy(&c2_bb_val);
      sf_mex_destroy(&c2_x_unusedU2);
      sf_mex_destroy(&c2_x_unusedU3);
      sf_mex_destroy(&c2_bb_isfimathlocal);
      c2_DM_r_w = 0U;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 190U);
      chartInstance->c2_CPU_state = 17U;
      break;

     case 3U:
      CV_EML_SWITCH(0, 1, 1, 4);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 194U);
      c2_DM_addr = c2_b_uint8(chartInstance, chartInstance->c2_address_data);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 196U);
      c2_d_eml_fi_checkforconst(chartInstance);
      sf_mex_destroy(&c2_cb_T);
      sf_mex_destroy(&c2_cb_F);
      sf_mex_destroy(&c2_cb_val);
      sf_mex_destroy(&c2_y_unusedU2);
      sf_mex_destroy(&c2_y_unusedU3);
      sf_mex_destroy(&c2_cb_isfimathlocal);
      c2_DM_r_w = 0U;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 198U);
      chartInstance->c2_CPU_state = 19U;
      break;

     case 4U:
      CV_EML_SWITCH(0, 1, 1, 5);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 201U);
      c2_e_hoistedGlobal = chartInstance->c2_minor_opcode;
      c2_a = c2_e_hoistedGlobal;
      c2_minor_opcode_bit6 = 0U;
      c2_a1 = c2_a;
      c2_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_a1 >> 5) & 1U);
      c2_minor_opcode_bit6 = c2_slice_temp;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 202U);
      switch (c2_c_uint8(chartInstance, c2_minor_opcode_bit6)) {
       case 0U:
        CV_EML_SWITCH(0, 1, 2, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 205U);
        c2_f_hoistedGlobal = chartInstance->c2_address_data;
        c2_g_varargin_1 = c2_f_hoistedGlobal;
        c2_h_varargin_1 = c2_g_varargin_1;
        c2_d_var1 = c2_h_varargin_1;
        c2_i0 = (int8_T)c2_d_var1;
        if ((int8_T)(c2_i0 & 64) != 0) {
          c2_temp_address_data = (int8_T)(c2_i0 | -64);
        } else {
          c2_temp_address_data = (int8_T)(c2_i0 & 63);
        }

        sf_mex_destroy(&c2_db_T);
        sf_mex_destroy(&c2_db_F);
        sf_mex_destroy(&c2_db_val);
        sf_mex_destroy(&c2_d_isautoscaled);
        sf_mex_destroy(&c2_d_pvpairsetdata);
        sf_mex_destroy(&c2_db_isfimathlocal);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 206U);
        c2_i_varargin_1 = c2_minus(chartInstance, c2_temp_address_data);
        c2_j_varargin_1 = c2_i_varargin_1;
        c2_c_eml_fi_checkforconst(chartInstance);
        c2_e_var1 = c2_j_varargin_1;
        c2_addr_inc = c2_e_var1;
        sf_mex_destroy(&c2_eb_T);
        sf_mex_destroy(&c2_eb_F);
        sf_mex_destroy(&c2_eb_val);
        sf_mex_destroy(&c2_e_isautoscaled);
        sf_mex_destroy(&c2_e_pvpairsetdata);
        sf_mex_destroy(&c2_eb_isfimathlocal);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 207U);
        c2_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_fb_T);
        sf_mex_destroy(&c2_fb_F);
        sf_mex_destroy(&c2_fb_val);
        sf_mex_destroy(&c2_ab_unusedU2);
        sf_mex_destroy(&c2_ab_unusedU3);
        sf_mex_destroy(&c2_fb_isfimathlocal);
        c2_PC_func = 1U;
        break;

       case 1U:
        CV_EML_SWITCH(0, 1, 2, 2);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 211U);
        c2_g_hoistedGlobal = chartInstance->c2_address_data;
        c2_k_varargin_1 = c2_g_hoistedGlobal;
        c2_l_varargin_1 = c2_k_varargin_1;
        c2_c_eml_fi_checkforconst(chartInstance);
        c2_f_var1 = c2_l_varargin_1;
        c2_AC_data = (int8_T)c2_f_var1;
        sf_mex_destroy(&c2_gb_T);
        sf_mex_destroy(&c2_gb_F);
        sf_mex_destroy(&c2_gb_val);
        sf_mex_destroy(&c2_f_isautoscaled);
        sf_mex_destroy(&c2_f_pvpairsetdata);
        sf_mex_destroy(&c2_gb_isfimathlocal);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 212U);
        c2_b_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_hb_T);
        sf_mex_destroy(&c2_hb_F);
        sf_mex_destroy(&c2_hb_val);
        sf_mex_destroy(&c2_bb_unusedU2);
        sf_mex_destroy(&c2_bb_unusedU3);
        sf_mex_destroy(&c2_hb_isfimathlocal);
        c2_AC_func = 1U;
        break;

       default:
        CV_EML_SWITCH(0, 1, 2, 0);
        break;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 215U);
      chartInstance->c2_CPU_state = 1U;
      break;

     case 5U:
      CV_EML_SWITCH(0, 1, 1, 6);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 220U);
      c2_DM_addr = c2_b_uint8(chartInstance, chartInstance->c2_address_data);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 221U);
      c2_h_hoistedGlobal = chartInstance->c2_minor_opcode;
      c2_b_a = c2_h_hoistedGlobal;
      c2_indirect_bit = 0U;
      c2_b_a1 = c2_b_a;
      c2_b_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_b_a1 >> 5) & 1U);
      c2_indirect_bit = c2_b_slice_temp;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 222U);
      if (CV_EML_IF(0, 1, 4, c2_logical(chartInstance, c2_indirect_bit))) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 225U);
        c2_d_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_ib_T);
        sf_mex_destroy(&c2_ib_F);
        sf_mex_destroy(&c2_ib_val);
        sf_mex_destroy(&c2_cb_unusedU2);
        sf_mex_destroy(&c2_cb_unusedU3);
        sf_mex_destroy(&c2_ib_isfimathlocal);
        c2_DM_r_w = 0U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 226U);
        chartInstance->c2_CPU_state = 21U;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 229U);
        c2_d_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_jb_T);
        sf_mex_destroy(&c2_jb_F);
        sf_mex_destroy(&c2_jb_val);
        sf_mex_destroy(&c2_db_unusedU2);
        sf_mex_destroy(&c2_db_unusedU3);
        sf_mex_destroy(&c2_jb_isfimathlocal);
        c2_DM_r_w = 1U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 231U);
        chartInstance->c2_CPU_state = 25U;
      }
      break;

     case 6U:
      CV_EML_SWITCH(0, 1, 1, 7);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 235U);
      c2_i_hoistedGlobal = chartInstance->c2_minor_opcode;
      c2_c_a = c2_i_hoistedGlobal;
      c2_minor_opcode_bit6 = 0U;
      c2_c_a1 = c2_c_a;
      c2_c_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_c_a1 >> 5) & 1U);
      c2_minor_opcode_bit6 = c2_c_slice_temp;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 236U);
      switch (c2_c_uint8(chartInstance, c2_minor_opcode_bit6)) {
       case 0U:
        CV_EML_SWITCH(0, 1, 3, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 240U);
        c2_d_a = c2_in_flags;
        c2_c = 0U;
        c2_d_a1 = c2_d_a;
        c2_d_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_d_a1 >> 3) & 1U);
        c2_c = c2_d_slice_temp;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 241U);
        if (CV_EML_IF(0, 1, 5, c2_b_logical(chartInstance, c2_c))) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 242U);
          c2_j_hoistedGlobal = chartInstance->c2_address_data;
          c2_m_varargin_1 = c2_j_hoistedGlobal;
          c2_n_varargin_1 = c2_m_varargin_1;
          c2_g_var1 = c2_n_varargin_1;
          c2_i1 = (int8_T)c2_g_var1;
          if ((int8_T)(c2_i1 & 64) != 0) {
            c2_temp_address_data = (int8_T)(c2_i1 | -64);
          } else {
            c2_temp_address_data = (int8_T)(c2_i1 & 63);
          }

          sf_mex_destroy(&c2_kb_T);
          sf_mex_destroy(&c2_kb_F);
          sf_mex_destroy(&c2_kb_val);
          sf_mex_destroy(&c2_g_isautoscaled);
          sf_mex_destroy(&c2_g_pvpairsetdata);
          sf_mex_destroy(&c2_kb_isfimathlocal);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 243U);
          c2_o_varargin_1 = c2_minus(chartInstance, c2_temp_address_data);
          c2_p_varargin_1 = c2_o_varargin_1;
          c2_c_eml_fi_checkforconst(chartInstance);
          c2_h_var1 = c2_p_varargin_1;
          c2_addr_inc = c2_h_var1;
          sf_mex_destroy(&c2_lb_T);
          sf_mex_destroy(&c2_lb_F);
          sf_mex_destroy(&c2_lb_val);
          sf_mex_destroy(&c2_h_isautoscaled);
          sf_mex_destroy(&c2_h_pvpairsetdata);
          sf_mex_destroy(&c2_lb_isfimathlocal);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 244U);
          c2_eml_fi_checkforconst(chartInstance);
          sf_mex_destroy(&c2_mb_T);
          sf_mex_destroy(&c2_mb_F);
          sf_mex_destroy(&c2_mb_val);
          sf_mex_destroy(&c2_eb_unusedU2);
          sf_mex_destroy(&c2_eb_unusedU3);
          sf_mex_destroy(&c2_mb_isfimathlocal);
          c2_PC_func = 1U;
        }
        break;

       case 1U:
        CV_EML_SWITCH(0, 1, 3, 2);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 249U);
        c2_e_a = c2_in_flags;
        c2_n = 0U;
        c2_e_a1 = c2_e_a;
        c2_e_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_e_a1 >> 2) & 1U);
        c2_n = c2_e_slice_temp;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 250U);
        if (CV_EML_IF(0, 1, 6, c2_b_logical(chartInstance, c2_n))) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 251U);
          c2_k_hoistedGlobal = chartInstance->c2_address_data;
          c2_q_varargin_1 = c2_k_hoistedGlobal;
          c2_r_varargin_1 = c2_q_varargin_1;
          c2_i_var1 = c2_r_varargin_1;
          c2_i2 = (int8_T)c2_i_var1;
          if ((int8_T)(c2_i2 & 64) != 0) {
            c2_temp_address_data = (int8_T)(c2_i2 | -64);
          } else {
            c2_temp_address_data = (int8_T)(c2_i2 & 63);
          }

          sf_mex_destroy(&c2_nb_T);
          sf_mex_destroy(&c2_nb_F);
          sf_mex_destroy(&c2_nb_val);
          sf_mex_destroy(&c2_i_isautoscaled);
          sf_mex_destroy(&c2_i_pvpairsetdata);
          sf_mex_destroy(&c2_nb_isfimathlocal);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 252U);
          c2_s_varargin_1 = c2_minus(chartInstance, c2_temp_address_data);
          c2_t_varargin_1 = c2_s_varargin_1;
          c2_c_eml_fi_checkforconst(chartInstance);
          c2_j_var1 = c2_t_varargin_1;
          c2_addr_inc = c2_j_var1;
          sf_mex_destroy(&c2_ob_T);
          sf_mex_destroy(&c2_ob_F);
          sf_mex_destroy(&c2_ob_val);
          sf_mex_destroy(&c2_j_isautoscaled);
          sf_mex_destroy(&c2_j_pvpairsetdata);
          sf_mex_destroy(&c2_ob_isfimathlocal);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 253U);
          c2_eml_fi_checkforconst(chartInstance);
          sf_mex_destroy(&c2_pb_T);
          sf_mex_destroy(&c2_pb_F);
          sf_mex_destroy(&c2_pb_val);
          sf_mex_destroy(&c2_fb_unusedU2);
          sf_mex_destroy(&c2_fb_unusedU3);
          sf_mex_destroy(&c2_pb_isfimathlocal);
          c2_PC_func = 1U;
        }
        break;

       default:
        CV_EML_SWITCH(0, 1, 3, 0);
        break;
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 257);
      chartInstance->c2_CPU_state = 15U;
      break;

     case 7U:
      CV_EML_SWITCH(0, 1, 1, 8);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 261);
      chartInstance->c2_CPU_state = 1U;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 262);
      c2_l_hoistedGlobal = chartInstance->c2_minor_opcode;
      c2_f_a = c2_l_hoistedGlobal;
      c2_minor_opcode_bit4 = 0U;
      c2_f_a1 = c2_f_a;
      c2_f_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_f_a1 >> 3) & 1U);
      c2_minor_opcode_bit4 = c2_f_slice_temp;
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 263);
      if (CV_EML_IF(0, 1, 7, (real_T)c2_logical(chartInstance,
            c2_minor_opcode_bit4) == 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 265);
        c2_m_hoistedGlobal = chartInstance->c2_minor_opcode;
        c2_g_a = c2_m_hoistedGlobal;
        c2_minor_opcode_bit6 = 0U;
        c2_g_a1 = c2_g_a;
        c2_g_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_g_a1 >> 5) & 1U);
        c2_minor_opcode_bit6 = c2_g_slice_temp;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 266);
        switch (c2_c_uint8(chartInstance, c2_minor_opcode_bit6)) {
         case 0U:
          CV_EML_SWITCH(0, 1, 4, 1);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 269);
          c2_h_a = c2_in_flags;
          c2_v = 0U;
          c2_h_a1 = c2_h_a;
          c2_h_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_h_a1 >> 1) & 1U);
          c2_v = c2_h_slice_temp;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 270);
          if (CV_EML_IF(0, 1, 8, c2_b_logical(chartInstance, c2_v))) {
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 271);
            c2_n_hoistedGlobal = chartInstance->c2_address_data;
            c2_u_varargin_1 = c2_n_hoistedGlobal;
            c2_v_varargin_1 = c2_u_varargin_1;
            c2_k_var1 = c2_v_varargin_1;
            c2_i3 = (int8_T)c2_k_var1;
            if ((int8_T)(c2_i3 & 64) != 0) {
              c2_temp_address_data = (int8_T)(c2_i3 | -64);
            } else {
              c2_temp_address_data = (int8_T)(c2_i3 & 63);
            }

            sf_mex_destroy(&c2_qb_T);
            sf_mex_destroy(&c2_qb_F);
            sf_mex_destroy(&c2_qb_val);
            sf_mex_destroy(&c2_k_isautoscaled);
            sf_mex_destroy(&c2_k_pvpairsetdata);
            sf_mex_destroy(&c2_qb_isfimathlocal);
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 272);
            c2_w_varargin_1 = c2_minus(chartInstance, c2_temp_address_data);
            c2_x_varargin_1 = c2_w_varargin_1;
            c2_c_eml_fi_checkforconst(chartInstance);
            c2_l_var1 = c2_x_varargin_1;
            c2_addr_inc = c2_l_var1;
            sf_mex_destroy(&c2_rb_T);
            sf_mex_destroy(&c2_rb_F);
            sf_mex_destroy(&c2_rb_val);
            sf_mex_destroy(&c2_l_isautoscaled);
            sf_mex_destroy(&c2_l_pvpairsetdata);
            sf_mex_destroy(&c2_rb_isfimathlocal);
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 273);
            c2_eml_fi_checkforconst(chartInstance);
            sf_mex_destroy(&c2_sb_T);
            sf_mex_destroy(&c2_sb_F);
            sf_mex_destroy(&c2_sb_val);
            sf_mex_destroy(&c2_gb_unusedU2);
            sf_mex_destroy(&c2_gb_unusedU3);
            sf_mex_destroy(&c2_sb_isfimathlocal);
            c2_PC_func = 1U;
          }
          break;

         case 1U:
          CV_EML_SWITCH(0, 1, 4, 2);
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 278);
          c2_i_a = c2_in_flags;
          c2_z = 0U;
          c2_i_a1 = c2_i_a;
          c2_i_slice_temp = (uint8_T)(c2_i_a1 & 1U);
          c2_z = c2_i_slice_temp;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 279);
          if (CV_EML_IF(0, 1, 9, c2_b_logical(chartInstance, c2_z))) {
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 280);
            c2_o_hoistedGlobal = chartInstance->c2_address_data;
            c2_y_varargin_1 = c2_o_hoistedGlobal;
            c2_ab_varargin_1 = c2_y_varargin_1;
            c2_m_var1 = c2_ab_varargin_1;
            c2_i4 = (int8_T)c2_m_var1;
            if ((int8_T)(c2_i4 & 64) != 0) {
              c2_temp_address_data = (int8_T)(c2_i4 | -64);
            } else {
              c2_temp_address_data = (int8_T)(c2_i4 & 63);
            }

            sf_mex_destroy(&c2_tb_T);
            sf_mex_destroy(&c2_tb_F);
            sf_mex_destroy(&c2_tb_val);
            sf_mex_destroy(&c2_m_isautoscaled);
            sf_mex_destroy(&c2_m_pvpairsetdata);
            sf_mex_destroy(&c2_tb_isfimathlocal);
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 281);
            c2_bb_varargin_1 = c2_minus(chartInstance, c2_temp_address_data);
            c2_cb_varargin_1 = c2_bb_varargin_1;
            c2_c_eml_fi_checkforconst(chartInstance);
            c2_n_var1 = c2_cb_varargin_1;
            c2_addr_inc = c2_n_var1;
            sf_mex_destroy(&c2_ub_T);
            sf_mex_destroy(&c2_ub_F);
            sf_mex_destroy(&c2_ub_val);
            sf_mex_destroy(&c2_n_isautoscaled);
            sf_mex_destroy(&c2_n_pvpairsetdata);
            sf_mex_destroy(&c2_ub_isfimathlocal);
            _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 282);
            c2_eml_fi_checkforconst(chartInstance);
            sf_mex_destroy(&c2_vb_T);
            sf_mex_destroy(&c2_vb_F);
            sf_mex_destroy(&c2_vb_val);
            sf_mex_destroy(&c2_hb_unusedU2);
            sf_mex_destroy(&c2_hb_unusedU3);
            sf_mex_destroy(&c2_vb_isfimathlocal);
            c2_PC_func = 1U;
          }
          break;

         default:
          CV_EML_SWITCH(0, 1, 4, 0);
          break;
        }
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 287);
      switch (c2_b_uint8(chartInstance, chartInstance->c2_minor_opcode)) {
       case 8U:
        CV_EML_SWITCH(0, 1, 5, 1);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 291);
        c2_hlt = 1U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 292);
        chartInstance->c2_CPU_state = 22U;
        break;

       case 9U:
        CV_EML_SWITCH(0, 1, 5, 2);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 295);
        c2_b_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_wb_T);
        sf_mex_destroy(&c2_wb_F);
        sf_mex_destroy(&c2_wb_val);
        sf_mex_destroy(&c2_ib_unusedU2);
        sf_mex_destroy(&c2_ib_unusedU3);
        sf_mex_destroy(&c2_wb_isfimathlocal);
        c2_AC_func = 0U;
        break;

       case 10U:
        CV_EML_SWITCH(0, 1, 5, 3);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 299);
        c2_b_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_xb_T);
        sf_mex_destroy(&c2_xb_F);
        sf_mex_destroy(&c2_xb_val);
        sf_mex_destroy(&c2_jb_unusedU2);
        sf_mex_destroy(&c2_jb_unusedU3);
        sf_mex_destroy(&c2_xb_isfimathlocal);
        c2_ALU_func = 4U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 300);
        c2_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_yb_T);
        sf_mex_destroy(&c2_yb_F);
        sf_mex_destroy(&c2_yb_val);
        sf_mex_destroy(&c2_kb_unusedU2);
        sf_mex_destroy(&c2_kb_unusedU3);
        sf_mex_destroy(&c2_yb_isfimathlocal);
        c2_shifter_sel = 3U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 301);
        chartInstance->c2_CPU_state = 6U;
        break;

       case 11U:
        CV_EML_SWITCH(0, 1, 5, 4);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 305);
        c2_b_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_ac_T);
        sf_mex_destroy(&c2_ac_F);
        sf_mex_destroy(&c2_ac_val);
        sf_mex_destroy(&c2_lb_unusedU2);
        sf_mex_destroy(&c2_lb_unusedU3);
        sf_mex_destroy(&c2_ac_isfimathlocal);
        c2_ALU_func = 5U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 306);
        c2_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_bc_T);
        sf_mex_destroy(&c2_bc_F);
        sf_mex_destroy(&c2_bc_val);
        sf_mex_destroy(&c2_mb_unusedU2);
        sf_mex_destroy(&c2_mb_unusedU3);
        sf_mex_destroy(&c2_bc_isfimathlocal);
        c2_shifter_sel = 3U;
        break;

       case 12U:
        CV_EML_SWITCH(0, 1, 5, 5);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 310);
        c2_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_cc_T);
        sf_mex_destroy(&c2_cc_F);
        sf_mex_destroy(&c2_cc_val);
        sf_mex_destroy(&c2_nb_unusedU2);
        sf_mex_destroy(&c2_nb_unusedU3);
        sf_mex_destroy(&c2_cc_isfimathlocal);
        c2_shifter_sel = 1U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 311);
        chartInstance->c2_CPU_state = 6U;
        break;

       case 13U:
        CV_EML_SWITCH(0, 1, 5, 6);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 315);
        c2_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_dc_T);
        sf_mex_destroy(&c2_dc_F);
        sf_mex_destroy(&c2_dc_val);
        sf_mex_destroy(&c2_ob_unusedU2);
        sf_mex_destroy(&c2_ob_unusedU3);
        sf_mex_destroy(&c2_dc_isfimathlocal);
        c2_shifter_sel = 2U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 316);
        chartInstance->c2_CPU_state = 6U;
        break;

       case 14U:
        CV_EML_SWITCH(0, 1, 5, 7);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 320);
        c2_DM_addr = MAX_uint8_T;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 322);
        c2_d_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_ec_T);
        sf_mex_destroy(&c2_ec_F);
        sf_mex_destroy(&c2_ec_val);
        sf_mex_destroy(&c2_pb_unusedU2);
        sf_mex_destroy(&c2_pb_unusedU3);
        sf_mex_destroy(&c2_ec_isfimathlocal);
        c2_DM_r_w = 0U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 324);
        chartInstance->c2_CPU_state = 12U;
        break;

       case 15U:
        CV_EML_SWITCH(0, 1, 5, 8);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 328);
        c2_b_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_fc_T);
        sf_mex_destroy(&c2_fc_F);
        sf_mex_destroy(&c2_fc_val);
        sf_mex_destroy(&c2_qb_unusedU2);
        sf_mex_destroy(&c2_qb_unusedU3);
        sf_mex_destroy(&c2_fc_isfimathlocal);
        c2_ALU_func = 7U;
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 329);
        c2_eml_fi_checkforconst(chartInstance);
        sf_mex_destroy(&c2_gc_T);
        sf_mex_destroy(&c2_gc_F);
        sf_mex_destroy(&c2_gc_val);
        sf_mex_destroy(&c2_rb_unusedU2);
        sf_mex_destroy(&c2_rb_unusedU3);
        sf_mex_destroy(&c2_gc_isfimathlocal);
        c2_shifter_sel = 3U;
        break;

       default:
        CV_EML_SWITCH(0, 1, 5, 0);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 333);
        chartInstance->c2_CPU_state = 1U;
        break;
      }
      break;

     default:
      CV_EML_SWITCH(0, 1, 1, 0);
      break;
    }
    break;

   case 6U:
    CV_EML_SWITCH(0, 1, 0, 6);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 343);
    c2_b_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_hc_T);
    sf_mex_destroy(&c2_hc_F);
    sf_mex_destroy(&c2_hc_val);
    sf_mex_destroy(&c2_sb_unusedU2);
    sf_mex_destroy(&c2_sb_unusedU3);
    sf_mex_destroy(&c2_hc_isfimathlocal);
    c2_AC_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 344);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 346);
    chartInstance->c2_CPU_state = 1U;
    break;

   case 7U:
    CV_EML_SWITCH(0, 1, 0, 7);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 352);
    c2_DM_addr = chartInstance->c2_indirect_address;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 354);
    c2_d_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_ic_T);
    sf_mex_destroy(&c2_ic_F);
    sf_mex_destroy(&c2_ic_val);
    sf_mex_destroy(&c2_tb_unusedU2);
    sf_mex_destroy(&c2_tb_unusedU3);
    sf_mex_destroy(&c2_ic_isfimathlocal);
    c2_DM_r_w = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 356);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 357);
    chartInstance->c2_CPU_state = 13U;
    break;

   case 8U:
    CV_EML_SWITCH(0, 1, 0, 8);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 362);
    c2_DM_addr = chartInstance->c2_indirect_address;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 364);
    c2_d_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_jc_T);
    sf_mex_destroy(&c2_jc_F);
    sf_mex_destroy(&c2_jc_val);
    sf_mex_destroy(&c2_ub_unusedU2);
    sf_mex_destroy(&c2_ub_unusedU3);
    sf_mex_destroy(&c2_jc_isfimathlocal);
    c2_DM_r_w = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 366);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 367);
    chartInstance->c2_CPU_state = 15U;
    break;

   case 9U:
    CV_EML_SWITCH(0, 1, 0, 9);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 372);
    c2_DM_addr = chartInstance->c2_indirect_address;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 374);
    c2_d_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_kc_T);
    sf_mex_destroy(&c2_kc_F);
    sf_mex_destroy(&c2_kc_val);
    sf_mex_destroy(&c2_vb_unusedU2);
    sf_mex_destroy(&c2_vb_unusedU3);
    sf_mex_destroy(&c2_kc_isfimathlocal);
    c2_DM_r_w = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 376);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 377);
    chartInstance->c2_CPU_state = 17U;
    break;

   case 10U:
    CV_EML_SWITCH(0, 1, 0, 10);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 382);
    c2_DM_addr = chartInstance->c2_indirect_address;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 384);
    c2_d_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_lc_T);
    sf_mex_destroy(&c2_lc_F);
    sf_mex_destroy(&c2_lc_val);
    sf_mex_destroy(&c2_wb_unusedU2);
    sf_mex_destroy(&c2_wb_unusedU3);
    sf_mex_destroy(&c2_lc_isfimathlocal);
    c2_DM_r_w = 0U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 386);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 387);
    chartInstance->c2_CPU_state = 19U;
    break;

   case 11U:
    CV_EML_SWITCH(0, 1, 0, 11);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 392);
    c2_DM_addr = c2_uint8(chartInstance, c2_data_in);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 394);
    c2_d_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_mc_T);
    sf_mex_destroy(&c2_mc_F);
    sf_mex_destroy(&c2_mc_val);
    sf_mex_destroy(&c2_xb_unusedU2);
    sf_mex_destroy(&c2_xb_unusedU3);
    sf_mex_destroy(&c2_mc_isfimathlocal);
    c2_DM_r_w = 1U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 395);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 396);
    chartInstance->c2_CPU_state = 1U;
    break;

   case 12U:
    CV_EML_SWITCH(0, 1, 0, 12);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 400);
    c2_print_data = true;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 401);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 402);
    chartInstance->c2_CPU_state = 1U;
    break;

   case 13U:
    CV_EML_SWITCH(0, 1, 0, 13);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 407);
    c2_b_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_nc_T);
    sf_mex_destroy(&c2_nc_F);
    sf_mex_destroy(&c2_nc_val);
    sf_mex_destroy(&c2_yb_unusedU2);
    sf_mex_destroy(&c2_yb_unusedU3);
    sf_mex_destroy(&c2_nc_isfimathlocal);
    c2_ALU_func = 6U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 408);
    c2_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_oc_T);
    sf_mex_destroy(&c2_oc_F);
    sf_mex_destroy(&c2_oc_val);
    sf_mex_destroy(&c2_ac_unusedU2);
    sf_mex_destroy(&c2_ac_unusedU3);
    sf_mex_destroy(&c2_oc_isfimathlocal);
    c2_shifter_sel = 3U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 410);
    if (CV_EML_IF(0, 1, 10, chartInstance->c2_previous_CPU_state == 4)) {
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
    CV_EML_SWITCH(0, 1, 0, 14);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 419);
    c2_p_hoistedGlobal = chartInstance->c2_minor_opcode;
    c2_j_a = c2_p_hoistedGlobal;
    c2_indirect_bit = 0U;
    c2_j_a1 = c2_j_a;
    c2_j_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_j_a1 >> 5) & 1U);
    c2_indirect_bit = c2_j_slice_temp;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 421);
    c2_b_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_pc_T);
    sf_mex_destroy(&c2_pc_F);
    sf_mex_destroy(&c2_pc_val);
    sf_mex_destroy(&c2_bc_unusedU2);
    sf_mex_destroy(&c2_bc_unusedU3);
    sf_mex_destroy(&c2_pc_isfimathlocal);
    c2_AC_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 423);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 424);
    if (CV_EML_IF(0, 1, 11, c2_logical(chartInstance, c2_indirect_bit))) {
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
    CV_EML_SWITCH(0, 1, 0, 15);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 435);
    c2_b_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_qc_T);
    sf_mex_destroy(&c2_qc_F);
    sf_mex_destroy(&c2_qc_val);
    sf_mex_destroy(&c2_cc_unusedU2);
    sf_mex_destroy(&c2_cc_unusedU3);
    sf_mex_destroy(&c2_qc_isfimathlocal);
    c2_ALU_func = 1U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 436);
    c2_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_rc_T);
    sf_mex_destroy(&c2_rc_F);
    sf_mex_destroy(&c2_rc_val);
    sf_mex_destroy(&c2_dc_unusedU2);
    sf_mex_destroy(&c2_dc_unusedU3);
    sf_mex_destroy(&c2_rc_isfimathlocal);
    c2_shifter_sel = 3U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 438);
    if (CV_EML_IF(0, 1, 12, chartInstance->c2_previous_CPU_state == 4)) {
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
    CV_EML_SWITCH(0, 1, 0, 16);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 447);
    c2_q_hoistedGlobal = chartInstance->c2_minor_opcode;
    c2_k_a = c2_q_hoistedGlobal;
    c2_indirect_bit = 0U;
    c2_k_a1 = c2_k_a;
    c2_k_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_k_a1 >> 5) & 1U);
    c2_indirect_bit = c2_k_slice_temp;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 449);
    c2_b_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_sc_T);
    sf_mex_destroy(&c2_sc_F);
    sf_mex_destroy(&c2_sc_val);
    sf_mex_destroy(&c2_ec_unusedU2);
    sf_mex_destroy(&c2_ec_unusedU3);
    sf_mex_destroy(&c2_sc_isfimathlocal);
    c2_AC_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 451);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 452);
    if (CV_EML_IF(0, 1, 13, c2_logical(chartInstance, c2_indirect_bit))) {
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
    CV_EML_SWITCH(0, 1, 0, 17);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 462);
    c2_b_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_tc_T);
    sf_mex_destroy(&c2_tc_F);
    sf_mex_destroy(&c2_tc_val);
    sf_mex_destroy(&c2_fc_unusedU2);
    sf_mex_destroy(&c2_fc_unusedU3);
    sf_mex_destroy(&c2_tc_isfimathlocal);
    c2_ALU_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 463);
    c2_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_uc_T);
    sf_mex_destroy(&c2_uc_F);
    sf_mex_destroy(&c2_uc_val);
    sf_mex_destroy(&c2_gc_unusedU2);
    sf_mex_destroy(&c2_gc_unusedU3);
    sf_mex_destroy(&c2_uc_isfimathlocal);
    c2_shifter_sel = 3U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 465);
    if (CV_EML_IF(0, 1, 14, chartInstance->c2_previous_CPU_state == 4)) {
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
    CV_EML_SWITCH(0, 1, 0, 18);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 474);
    c2_r_hoistedGlobal = chartInstance->c2_minor_opcode;
    c2_l_a = c2_r_hoistedGlobal;
    c2_indirect_bit = 0U;
    c2_l_a1 = c2_l_a;
    c2_l_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_l_a1 >> 5) & 1U);
    c2_indirect_bit = c2_l_slice_temp;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 476);
    c2_b_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_vc_T);
    sf_mex_destroy(&c2_vc_F);
    sf_mex_destroy(&c2_vc_val);
    sf_mex_destroy(&c2_hc_unusedU2);
    sf_mex_destroy(&c2_hc_unusedU3);
    sf_mex_destroy(&c2_vc_isfimathlocal);
    c2_AC_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 478);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 479);
    if (CV_EML_IF(0, 1, 15, c2_logical(chartInstance, c2_indirect_bit))) {
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
    CV_EML_SWITCH(0, 1, 0, 19);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 489);
    c2_b_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_wc_T);
    sf_mex_destroy(&c2_wc_F);
    sf_mex_destroy(&c2_wc_val);
    sf_mex_destroy(&c2_ic_unusedU2);
    sf_mex_destroy(&c2_ic_unusedU3);
    sf_mex_destroy(&c2_wc_isfimathlocal);
    c2_ALU_func = 3U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 490);
    c2_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_xc_T);
    sf_mex_destroy(&c2_xc_F);
    sf_mex_destroy(&c2_xc_val);
    sf_mex_destroy(&c2_jc_unusedU2);
    sf_mex_destroy(&c2_jc_unusedU3);
    sf_mex_destroy(&c2_xc_isfimathlocal);
    c2_shifter_sel = 3U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 492);
    if (CV_EML_IF(0, 1, 16, chartInstance->c2_previous_CPU_state == 4)) {
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
    CV_EML_SWITCH(0, 1, 0, 20);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 501);
    c2_s_hoistedGlobal = chartInstance->c2_minor_opcode;
    c2_m_a = c2_s_hoistedGlobal;
    c2_indirect_bit = 0U;
    c2_m_a1 = c2_m_a;
    c2_m_slice_temp = (uint8_T)((uint8_T)((uint32_T)c2_m_a1 >> 5) & 1U);
    c2_indirect_bit = c2_m_slice_temp;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 503);
    c2_b_eml_fi_checkforconst(chartInstance);
    sf_mex_destroy(&c2_yc_T);
    sf_mex_destroy(&c2_yc_F);
    sf_mex_destroy(&c2_yc_val);
    sf_mex_destroy(&c2_kc_unusedU2);
    sf_mex_destroy(&c2_kc_unusedU3);
    sf_mex_destroy(&c2_yc_isfimathlocal);
    c2_AC_func = 2U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 505);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 506);
    if (CV_EML_IF(0, 1, 17, c2_logical(chartInstance, c2_indirect_bit))) {
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
    CV_EML_SWITCH(0, 1, 0, 21);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 517);
    chartInstance->c2_CPU_state = 11U;
    break;

   case 22U:
    CV_EML_SWITCH(0, 1, 0, 22);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 521);
    c2_hlt = 1U;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 522);
    chartInstance->c2_CPU_state = 22U;
    break;

   default:
    CV_EML_SWITCH(0, 1, 0, 0);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 525);
    chartInstance->c2_previous_CPU_state = chartInstance->c2_CPU_state;
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 527);
    chartInstance->c2_CPU_state = 1U;
    break;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -527);
  _SFD_SYMBOL_SCOPE_POP();
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

static void initSimStructsc2_gm_hdlcodercpu_eml
  (SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_indirect_address_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static uint8_T c2_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c2_b_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_indirect_address_not_empty = false;
  } else {
    chartInstance->c2_indirect_address_not_empty = true;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    if (!chartInstance->c2_address_data_not_empty) {
      sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                    false);
    } else {
      c2_b_u = c2_u;
      c2_b_y = NULL;
      sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0),
                    false);
      sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14,
        sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx),
        15, "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, true), false);
    }

    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_c_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c2_d_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u1;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_address_data_not_empty = false;
  } else {
    chartInstance->c2_address_data_not_empty = true;
    sf_mex_check_fi(c2_parentId, c2_u, false, 0U, NULL, c2_eml_mx, c2_b_eml_mx);
    sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), false);
    sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
                   (c2_mxFi)), false);
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    if (!chartInstance->c2_minor_opcode_not_empty) {
      sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                    false);
    } else {
      c2_b_u = c2_u;
      c2_b_y = NULL;
      sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0),
                    false);
      sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14,
        sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx),
        15, "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, true), false);
    }

    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_e_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c2_f_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u2;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_minor_opcode_not_empty = false;
  } else {
    chartInstance->c2_minor_opcode_not_empty = true;
    sf_mex_check_fi(c2_parentId, c2_u, false, 0U, NULL, c2_eml_mx, c2_b_eml_mx);
    sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), false);
    sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
                   (c2_mxFi)), false);
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    if (!chartInstance->c2_major_opcode_not_empty) {
      sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                    false);
    } else {
      c2_b_u = c2_u;
      c2_b_y = NULL;
      sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0),
                    false);
      sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14,
        sf_mex_dup(c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_b_eml_mx),
        15, "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, true), false);
    }

    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_g_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c2_h_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u3;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_major_opcode_not_empty = false;
  } else {
    chartInstance->c2_major_opcode_not_empty = true;
    sf_mex_check_fi(c2_parentId, c2_u, false, 0U, NULL, c2_eml_mx, c2_b_eml_mx);
    sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), false);
    sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
                   (c2_mxFi)), false);
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_previous_CPU_state_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static uint8_T c2_i_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c2_j_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u4;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_previous_CPU_state_not_empty = false;
  } else {
    chartInstance->c2_previous_CPU_state_not_empty = true;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  if (!chartInstance->c2_CPU_state_not_empty) {
    sf_mex_assign(&c2_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  } else {
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0), false);
  }

  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static uint8_T c2_k_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c2_l_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u5;
  if (mxIsEmpty(c2_u)) {
    chartInstance->c2_CPU_state_not_empty = false;
  } else {
    chartInstance->c2_CPU_state_not_empty = true;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static uint8_T c2_m_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c2_n_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u6;
  (void)chartInstance;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_c_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_o_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c2_p_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u7;
  (void)chartInstance;
  sf_mex_check_fi(c2_parentId, c2_u, false, 0U, NULL, c2_eml_mx, c2_c_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), false);
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)), false);
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(int8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 2, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_d_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static int8_T c2_q_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static int8_T c2_r_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  int8_T c2_i5;
  (void)chartInstance;
  sf_mex_check_fi(c2_parentId, c2_u, false, 0U, NULL, c2_eml_mx, c2_d_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), false);
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)), false);
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_e_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_s_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c2_t_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u8;
  (void)chartInstance;
  sf_mex_check_fi(c2_parentId, c2_u, false, 0U, NULL, c2_eml_mx, c2_e_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), false);
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)), false);
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_f_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_u_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c2_v_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u9;
  (void)chartInstance;
  sf_mex_check_fi(c2_parentId, c2_u, false, 0U, NULL, c2_eml_mx, c2_f_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), false);
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)), false);
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(boolean_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static boolean_T c2_w_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static boolean_T c2_x_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  boolean_T c2_y;
  boolean_T c2_b0;
  (void)chartInstance;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_g_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_y_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u10;
  (void)chartInstance;
  sf_mex_check_fi(c2_parentId, c2_u, false, 0U, NULL, c2_eml_mx, c2_g_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), false);
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)), false);
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint16_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 5, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_h_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(int8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 2, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_d_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static const mxArray *c2_p_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_ab_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  (void)chartInstance;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_c_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, false), false);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_bb_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u11;
  (void)chartInstance;
  sf_mex_check_fi(c2_parentId, c2_u, false, 0U, NULL, c2_eml_mx, c2_c_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), false);
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)), false);
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(int8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 2, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_i_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static int8_T c2_cb_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  int8_T c2_i6;
  (void)chartInstance;
  sf_mex_check_fi(c2_parentId, c2_u, false, 0U, NULL, c2_eml_mx, c2_i_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), false);
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)), false);
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint16_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 5, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_h_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static const mxArray *c2_t_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  const mxArray *c2_u;
  const mxArray *c2_y = NULL;
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = sf_mex_dup(*(const mxArray **)c2_inData);
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_duplicatearraysafe(&c2_u), false);
  sf_mex_destroy(&c2_u);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

const mxArray *sf_c2_gm_hdlcodercpu_eml_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_createstruct("structure", 2, 147, 1),
                false);
  c2_info_helper(&c2_nameCaptureInfo);
  c2_b_info_helper(&c2_nameCaptureInfo);
  c2_c_info_helper(&c2_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs0 = NULL;
  const mxArray *c2_lhs0 = NULL;
  const mxArray *c2_rhs1 = NULL;
  const mxArray *c2_lhs1 = NULL;
  const mxArray *c2_rhs2 = NULL;
  const mxArray *c2_lhs2 = NULL;
  const mxArray *c2_rhs3 = NULL;
  const mxArray *c2_lhs3 = NULL;
  const mxArray *c2_rhs4 = NULL;
  const mxArray *c2_lhs4 = NULL;
  const mxArray *c2_rhs5 = NULL;
  const mxArray *c2_lhs5 = NULL;
  const mxArray *c2_rhs6 = NULL;
  const mxArray *c2_lhs6 = NULL;
  const mxArray *c2_rhs7 = NULL;
  const mxArray *c2_lhs7 = NULL;
  const mxArray *c2_rhs8 = NULL;
  const mxArray *c2_lhs8 = NULL;
  const mxArray *c2_rhs9 = NULL;
  const mxArray *c2_lhs9 = NULL;
  const mxArray *c2_rhs10 = NULL;
  const mxArray *c2_lhs10 = NULL;
  const mxArray *c2_rhs11 = NULL;
  const mxArray *c2_lhs11 = NULL;
  const mxArray *c2_rhs12 = NULL;
  const mxArray *c2_lhs12 = NULL;
  const mxArray *c2_rhs13 = NULL;
  const mxArray *c2_lhs13 = NULL;
  const mxArray *c2_rhs14 = NULL;
  const mxArray *c2_lhs14 = NULL;
  const mxArray *c2_rhs15 = NULL;
  const mxArray *c2_lhs15 = NULL;
  const mxArray *c2_rhs16 = NULL;
  const mxArray *c2_lhs16 = NULL;
  const mxArray *c2_rhs17 = NULL;
  const mxArray *c2_lhs17 = NULL;
  const mxArray *c2_rhs18 = NULL;
  const mxArray *c2_lhs18 = NULL;
  const mxArray *c2_rhs19 = NULL;
  const mxArray *c2_lhs19 = NULL;
  const mxArray *c2_rhs20 = NULL;
  const mxArray *c2_lhs20 = NULL;
  const mxArray *c2_rhs21 = NULL;
  const mxArray *c2_lhs21 = NULL;
  const mxArray *c2_rhs22 = NULL;
  const mxArray *c2_lhs22 = NULL;
  const mxArray *c2_rhs23 = NULL;
  const mxArray *c2_lhs23 = NULL;
  const mxArray *c2_rhs24 = NULL;
  const mxArray *c2_lhs24 = NULL;
  const mxArray *c2_rhs25 = NULL;
  const mxArray *c2_lhs25 = NULL;
  const mxArray *c2_rhs26 = NULL;
  const mxArray *c2_lhs26 = NULL;
  const mxArray *c2_rhs27 = NULL;
  const mxArray *c2_lhs27 = NULL;
  const mxArray *c2_rhs28 = NULL;
  const mxArray *c2_lhs28 = NULL;
  const mxArray *c2_rhs29 = NULL;
  const mxArray *c2_lhs29 = NULL;
  const mxArray *c2_rhs30 = NULL;
  const mxArray *c2_lhs30 = NULL;
  const mxArray *c2_rhs31 = NULL;
  const mxArray *c2_lhs31 = NULL;
  const mxArray *c2_rhs32 = NULL;
  const mxArray *c2_lhs32 = NULL;
  const mxArray *c2_rhs33 = NULL;
  const mxArray *c2_lhs33 = NULL;
  const mxArray *c2_rhs34 = NULL;
  const mxArray *c2_lhs34 = NULL;
  const mxArray *c2_rhs35 = NULL;
  const mxArray *c2_lhs35 = NULL;
  const mxArray *c2_rhs36 = NULL;
  const mxArray *c2_lhs36 = NULL;
  const mxArray *c2_rhs37 = NULL;
  const mxArray *c2_lhs37 = NULL;
  const mxArray *c2_rhs38 = NULL;
  const mxArray *c2_lhs38 = NULL;
  const mxArray *c2_rhs39 = NULL;
  const mxArray *c2_lhs39 = NULL;
  const mxArray *c2_rhs40 = NULL;
  const mxArray *c2_lhs40 = NULL;
  const mxArray *c2_rhs41 = NULL;
  const mxArray *c2_lhs41 = NULL;
  const mxArray *c2_rhs42 = NULL;
  const mxArray *c2_lhs42 = NULL;
  const mxArray *c2_rhs43 = NULL;
  const mxArray *c2_lhs43 = NULL;
  const mxArray *c2_rhs44 = NULL;
  const mxArray *c2_lhs44 = NULL;
  const mxArray *c2_rhs45 = NULL;
  const mxArray *c2_lhs45 = NULL;
  const mxArray *c2_rhs46 = NULL;
  const mxArray *c2_lhs46 = NULL;
  const mxArray *c2_rhs47 = NULL;
  const mxArray *c2_lhs47 = NULL;
  const mxArray *c2_rhs48 = NULL;
  const mxArray *c2_lhs48 = NULL;
  const mxArray *c2_rhs49 = NULL;
  const mxArray *c2_lhs49 = NULL;
  const mxArray *c2_rhs50 = NULL;
  const mxArray *c2_lhs50 = NULL;
  const mxArray *c2_rhs51 = NULL;
  const mxArray *c2_lhs51 = NULL;
  const mxArray *c2_rhs52 = NULL;
  const mxArray *c2_lhs52 = NULL;
  const mxArray *c2_rhs53 = NULL;
  const mxArray *c2_lhs53 = NULL;
  const mxArray *c2_rhs54 = NULL;
  const mxArray *c2_lhs54 = NULL;
  const mxArray *c2_rhs55 = NULL;
  const mxArray *c2_lhs55 = NULL;
  const mxArray *c2_rhs56 = NULL;
  const mxArray *c2_lhs56 = NULL;
  const mxArray *c2_rhs57 = NULL;
  const mxArray *c2_lhs57 = NULL;
  const mxArray *c2_rhs58 = NULL;
  const mxArray *c2_lhs58 = NULL;
  const mxArray *c2_rhs59 = NULL;
  const mxArray *c2_lhs59 = NULL;
  const mxArray *c2_rhs60 = NULL;
  const mxArray *c2_lhs60 = NULL;
  const mxArray *c2_rhs61 = NULL;
  const mxArray *c2_lhs61 = NULL;
  const mxArray *c2_rhs62 = NULL;
  const mxArray *c2_lhs62 = NULL;
  const mxArray *c2_rhs63 = NULL;
  const mxArray *c2_lhs63 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("fimath"), "name", "name", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m"), "resolved",
                  "resolved", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381857498U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c2_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m"), "context",
                  "context", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fimath_constructor_helper"),
                  "name", "name", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_fimath_constructor_helper.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c2_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("fi_impl"), "name", "name", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "resolved",
                  "resolved", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389302372U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c2_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c2_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("length"), "name", "name", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("cell"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1303153406U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c2_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fi_checkforconst"), "name",
                  "name", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fimath"),
                  "dominantType", "dominantType", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforconst.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517552U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c2_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c2_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c2_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fi_constructor_helper"),
                  "name", "name", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_fi_constructor_helper.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c2_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fi_checkforerror"), "name",
                  "name", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1360285946U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c2_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("bitget"), "name", "name", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1370017086U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c2_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c2_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c2_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "context",
                  "context", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c2_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfixed"), "name", "name", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c2_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "context", "context", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c2_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("all"), "name", "name", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372589614U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c2_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c2_rhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs17, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c2_rhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs18, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.allOrAny"),
                  "name", "name", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "resolved", "resolved", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372590358U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c2_rhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs19, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.assert"),
                  "name", "name", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/assert.m"),
                  "resolved", "resolved", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c2_rhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs20, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isequal"), "name", "name", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286825958U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c2_rhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs21, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "context",
                  "context", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isequal_core"), "name",
                  "name", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m"),
                  "resolved", "resolved", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286825986U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c2_rhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs22, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/allOrAny.m"),
                  "context", "context", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.constNonSingletonDim"), "name", "name", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/constNonSingletonDim.m"),
                  "resolved", "resolved", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372590360U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c2_rhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs23, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("numerictype"), "name", "name",
                  24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m"), "resolved",
                  "resolved", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1348199118U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c2_rhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs24, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/numerictype.m"), "context",
                  "context", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("length"), "name", "name", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("cell"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1303153406U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c2_rhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs25, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitget.m"),
                  "context", "context", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("fimath"), "name", "name", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303184U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c2_rhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs26, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/@embedded/@fi/bitget.m!convertOneBasedBitIndexToZeroBased"),
                  "context", "context", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c2_rhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs27, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c2_rhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs28, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286825926U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c2_rhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs29, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("logical"), "name", "name", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/logical.m"),
                  "resolved", "resolved", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517582U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c2_rhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs30, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/logical.m"),
                  "context", "context", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("ne"), "name", "name", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517584U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c2_rhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs31, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c2_rhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs32, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c2_rhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs33, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isscaledtype"), "name", "name",
                  34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c2_rhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs34, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "context", "context", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfixed"), "name", "name", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c2_rhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs35, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c2_rhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs36, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_type_relop_const"), "name",
                  "name", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m"),
                  "resolved", "resolved", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517574U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c2_rhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs37, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m"),
                  "context", "context", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("all"), "name", "name", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "resolved",
                  "resolved", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372589614U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c2_rhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs38, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/ne.m"),
                  "context", "context", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_make_same_complexity"),
                  "name", "name", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_make_same_complexity.m"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c2_rhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs39, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("uint8"), "name", "name", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m"),
                  "resolved", "resolved", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311262522U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c2_rhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs40, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/uint8.m"),
                  "context", "context", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fi_getRealWorldValAsDType"),
                  "name", "name", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getRealWorldValAsDType.m"),
                  "resolved", "resolved", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517570U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c2_rhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs41, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getRealWorldValAsDType.m"),
                  "context", "context", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isscaledtype"), "name", "name",
                  42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c2_rhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs42, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getRealWorldValAsDType.m"),
                  "context", "context", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isscalingbinarypoint"), "name",
                  "name", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscalingbinarypoint.m"),
                  "resolved", "resolved", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c2_rhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs43, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscalingbinarypoint.m"),
                  "context", "context", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isscaledtype"), "name", "name",
                  44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c2_rhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs44, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscalingbinarypoint.m"),
                  "context", "context", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isslopebiasscaled"),
                  "name", "name", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "resolved", "resolved", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c2_rhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs45, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "context", "context", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c2_rhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs46, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_getRealWorldValAsDType.m"),
                  "context", "context", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/get.m"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987886U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c2_rhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs47, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/get.m"),
                  "context", "context", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_scalar_eg.m"),
                  "resolved", "resolved", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517572U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c2_rhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs48, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs48), "lhs", "lhs",
                  48);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_scalar_eg.m"),
                  "context", "context", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("numerictype"), "name", "name",
                  49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m"),
                  "resolved", "resolved", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303186U), "fileTimeLo",
                  "fileTimeLo", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 49);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 49);
  sf_mex_assign(&c2_rhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs49, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs49), "rhs", "rhs",
                  49);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs49), "lhs", "lhs",
                  49);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_scalar_eg.m"),
                  "context", "context", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("fimath"), "name", "name", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m"),
                  "resolved", "resolved", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303184U), "fileTimeLo",
                  "fileTimeLo", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 50);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 50);
  sf_mex_assign(&c2_rhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs50, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs50), "rhs", "rhs",
                  50);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs50), "lhs", "lhs",
                  50);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/get.m"),
                  "context", "context", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_getfiprop_helper"), "name",
                  "name", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_getfiprop_helper.m"),
                  "resolved", "resolved", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 51);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 51);
  sf_mex_assign(&c2_rhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs51, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs51), "rhs", "rhs",
                  51);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs51), "lhs", "lhs",
                  51);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 52);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 52);
  sf_mex_assign(&c2_rhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs52, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs52), "rhs", "rhs",
                  52);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs52), "lhs", "lhs",
                  52);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfloat"), "name", "name", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m"),
                  "resolved", "resolved", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 53);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 53);
  sf_mex_assign(&c2_rhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs53, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs53), "rhs", "rhs",
                  53);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs53), "lhs", "lhs",
                  53);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m"),
                  "context", "context", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 54);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 54);
  sf_mex_assign(&c2_rhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs54, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs54), "rhs", "rhs",
                  54);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs54), "lhs", "lhs",
                  54);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput"),
                  "context", "context", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("castLike"), "name", "name", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "resolved", "resolved", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1348199122U), "fileTimeLo",
                  "fileTimeLo", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 55);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 55);
  sf_mex_assign(&c2_rhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs55, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs55), "rhs", "rhs",
                  55);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs55), "lhs", "lhs",
                  55);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 56);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 56);
  sf_mex_assign(&c2_rhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs56, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs56), "rhs", "rhs",
                  56);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs56), "lhs", "lhs",
                  56);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfimathlocal"), "name",
                  "name", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfimathlocal.m"),
                  "resolved", "resolved", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 57);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 57);
  sf_mex_assign(&c2_rhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs57, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs57), "rhs", "rhs",
                  57);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs57), "lhs", "lhs",
                  57);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("removefimath"), "name", "name",
                  58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/removefimath.m"), "resolved",
                  "resolved", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1325034780U), "fileTimeLo",
                  "fileTimeLo", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 58);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 58);
  sf_mex_assign(&c2_rhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs58, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs58), "rhs", "rhs",
                  58);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs58), "lhs", "lhs",
                  58);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("numerictype"), "name", "name",
                  59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m"),
                  "resolved", "resolved", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303186U), "fileTimeLo",
                  "fileTimeLo", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 59);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 59);
  sf_mex_assign(&c2_rhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs59, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs59), "rhs", "rhs",
                  59);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs59), "lhs", "lhs",
                  59);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("fimath"), "name", "name", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m"),
                  "resolved", "resolved", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303184U), "fileTimeLo",
                  "fileTimeLo", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 60);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 60);
  sf_mex_assign(&c2_rhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs60, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs60), "rhs", "rhs",
                  60);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs60), "lhs", "lhs",
                  60);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper"),
                  "context", "context", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fi_checkforntype"), "name",
                  "name", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m"),
                  "resolved", "resolved", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381857498U), "fileTimeLo",
                  "fileTimeLo", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 61);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 61);
  sf_mex_assign(&c2_rhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs61, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs61), "rhs", "rhs",
                  61);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs61), "lhs", "lhs",
                  61);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m"),
                  "context", "context", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 62);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 62);
  sf_mex_assign(&c2_rhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs62, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs62), "rhs", "rhs",
                  62);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs62), "lhs", "lhs",
                  62);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("minus"), "name", "name", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 63);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "resolved", "resolved", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517584U), "fileTimeLo",
                  "fileTimeLo", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 63);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 63);
  sf_mex_assign(&c2_rhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs63, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs63), "rhs", "rhs",
                  63);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs63), "lhs", "lhs",
                  63);
  sf_mex_destroy(&c2_rhs0);
  sf_mex_destroy(&c2_lhs0);
  sf_mex_destroy(&c2_rhs1);
  sf_mex_destroy(&c2_lhs1);
  sf_mex_destroy(&c2_rhs2);
  sf_mex_destroy(&c2_lhs2);
  sf_mex_destroy(&c2_rhs3);
  sf_mex_destroy(&c2_lhs3);
  sf_mex_destroy(&c2_rhs4);
  sf_mex_destroy(&c2_lhs4);
  sf_mex_destroy(&c2_rhs5);
  sf_mex_destroy(&c2_lhs5);
  sf_mex_destroy(&c2_rhs6);
  sf_mex_destroy(&c2_lhs6);
  sf_mex_destroy(&c2_rhs7);
  sf_mex_destroy(&c2_lhs7);
  sf_mex_destroy(&c2_rhs8);
  sf_mex_destroy(&c2_lhs8);
  sf_mex_destroy(&c2_rhs9);
  sf_mex_destroy(&c2_lhs9);
  sf_mex_destroy(&c2_rhs10);
  sf_mex_destroy(&c2_lhs10);
  sf_mex_destroy(&c2_rhs11);
  sf_mex_destroy(&c2_lhs11);
  sf_mex_destroy(&c2_rhs12);
  sf_mex_destroy(&c2_lhs12);
  sf_mex_destroy(&c2_rhs13);
  sf_mex_destroy(&c2_lhs13);
  sf_mex_destroy(&c2_rhs14);
  sf_mex_destroy(&c2_lhs14);
  sf_mex_destroy(&c2_rhs15);
  sf_mex_destroy(&c2_lhs15);
  sf_mex_destroy(&c2_rhs16);
  sf_mex_destroy(&c2_lhs16);
  sf_mex_destroy(&c2_rhs17);
  sf_mex_destroy(&c2_lhs17);
  sf_mex_destroy(&c2_rhs18);
  sf_mex_destroy(&c2_lhs18);
  sf_mex_destroy(&c2_rhs19);
  sf_mex_destroy(&c2_lhs19);
  sf_mex_destroy(&c2_rhs20);
  sf_mex_destroy(&c2_lhs20);
  sf_mex_destroy(&c2_rhs21);
  sf_mex_destroy(&c2_lhs21);
  sf_mex_destroy(&c2_rhs22);
  sf_mex_destroy(&c2_lhs22);
  sf_mex_destroy(&c2_rhs23);
  sf_mex_destroy(&c2_lhs23);
  sf_mex_destroy(&c2_rhs24);
  sf_mex_destroy(&c2_lhs24);
  sf_mex_destroy(&c2_rhs25);
  sf_mex_destroy(&c2_lhs25);
  sf_mex_destroy(&c2_rhs26);
  sf_mex_destroy(&c2_lhs26);
  sf_mex_destroy(&c2_rhs27);
  sf_mex_destroy(&c2_lhs27);
  sf_mex_destroy(&c2_rhs28);
  sf_mex_destroy(&c2_lhs28);
  sf_mex_destroy(&c2_rhs29);
  sf_mex_destroy(&c2_lhs29);
  sf_mex_destroy(&c2_rhs30);
  sf_mex_destroy(&c2_lhs30);
  sf_mex_destroy(&c2_rhs31);
  sf_mex_destroy(&c2_lhs31);
  sf_mex_destroy(&c2_rhs32);
  sf_mex_destroy(&c2_lhs32);
  sf_mex_destroy(&c2_rhs33);
  sf_mex_destroy(&c2_lhs33);
  sf_mex_destroy(&c2_rhs34);
  sf_mex_destroy(&c2_lhs34);
  sf_mex_destroy(&c2_rhs35);
  sf_mex_destroy(&c2_lhs35);
  sf_mex_destroy(&c2_rhs36);
  sf_mex_destroy(&c2_lhs36);
  sf_mex_destroy(&c2_rhs37);
  sf_mex_destroy(&c2_lhs37);
  sf_mex_destroy(&c2_rhs38);
  sf_mex_destroy(&c2_lhs38);
  sf_mex_destroy(&c2_rhs39);
  sf_mex_destroy(&c2_lhs39);
  sf_mex_destroy(&c2_rhs40);
  sf_mex_destroy(&c2_lhs40);
  sf_mex_destroy(&c2_rhs41);
  sf_mex_destroy(&c2_lhs41);
  sf_mex_destroy(&c2_rhs42);
  sf_mex_destroy(&c2_lhs42);
  sf_mex_destroy(&c2_rhs43);
  sf_mex_destroy(&c2_lhs43);
  sf_mex_destroy(&c2_rhs44);
  sf_mex_destroy(&c2_lhs44);
  sf_mex_destroy(&c2_rhs45);
  sf_mex_destroy(&c2_lhs45);
  sf_mex_destroy(&c2_rhs46);
  sf_mex_destroy(&c2_lhs46);
  sf_mex_destroy(&c2_rhs47);
  sf_mex_destroy(&c2_lhs47);
  sf_mex_destroy(&c2_rhs48);
  sf_mex_destroy(&c2_lhs48);
  sf_mex_destroy(&c2_rhs49);
  sf_mex_destroy(&c2_lhs49);
  sf_mex_destroy(&c2_rhs50);
  sf_mex_destroy(&c2_lhs50);
  sf_mex_destroy(&c2_rhs51);
  sf_mex_destroy(&c2_lhs51);
  sf_mex_destroy(&c2_rhs52);
  sf_mex_destroy(&c2_lhs52);
  sf_mex_destroy(&c2_rhs53);
  sf_mex_destroy(&c2_lhs53);
  sf_mex_destroy(&c2_rhs54);
  sf_mex_destroy(&c2_lhs54);
  sf_mex_destroy(&c2_rhs55);
  sf_mex_destroy(&c2_lhs55);
  sf_mex_destroy(&c2_rhs56);
  sf_mex_destroy(&c2_lhs56);
  sf_mex_destroy(&c2_rhs57);
  sf_mex_destroy(&c2_lhs57);
  sf_mex_destroy(&c2_rhs58);
  sf_mex_destroy(&c2_lhs58);
  sf_mex_destroy(&c2_rhs59);
  sf_mex_destroy(&c2_lhs59);
  sf_mex_destroy(&c2_rhs60);
  sf_mex_destroy(&c2_lhs60);
  sf_mex_destroy(&c2_rhs61);
  sf_mex_destroy(&c2_lhs61);
  sf_mex_destroy(&c2_rhs62);
  sf_mex_destroy(&c2_lhs62);
  sf_mex_destroy(&c2_rhs63);
  sf_mex_destroy(&c2_lhs63);
}

static const mxArray *c2_emlrt_marshallOut(const char * c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c2_u)), false);
  return c2_y;
}

static const mxArray *c2_b_emlrt_marshallOut(const uint32_T c2_u)
{
  const mxArray *c2_y = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 7, 0U, 0U, 0U, 0), false);
  return c2_y;
}

static void c2_b_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs64 = NULL;
  const mxArray *c2_lhs64 = NULL;
  const mxArray *c2_rhs65 = NULL;
  const mxArray *c2_lhs65 = NULL;
  const mxArray *c2_rhs66 = NULL;
  const mxArray *c2_lhs66 = NULL;
  const mxArray *c2_rhs67 = NULL;
  const mxArray *c2_lhs67 = NULL;
  const mxArray *c2_rhs68 = NULL;
  const mxArray *c2_lhs68 = NULL;
  const mxArray *c2_rhs69 = NULL;
  const mxArray *c2_lhs69 = NULL;
  const mxArray *c2_rhs70 = NULL;
  const mxArray *c2_lhs70 = NULL;
  const mxArray *c2_rhs71 = NULL;
  const mxArray *c2_lhs71 = NULL;
  const mxArray *c2_rhs72 = NULL;
  const mxArray *c2_lhs72 = NULL;
  const mxArray *c2_rhs73 = NULL;
  const mxArray *c2_lhs73 = NULL;
  const mxArray *c2_rhs74 = NULL;
  const mxArray *c2_lhs74 = NULL;
  const mxArray *c2_rhs75 = NULL;
  const mxArray *c2_lhs75 = NULL;
  const mxArray *c2_rhs76 = NULL;
  const mxArray *c2_lhs76 = NULL;
  const mxArray *c2_rhs77 = NULL;
  const mxArray *c2_lhs77 = NULL;
  const mxArray *c2_rhs78 = NULL;
  const mxArray *c2_lhs78 = NULL;
  const mxArray *c2_rhs79 = NULL;
  const mxArray *c2_lhs79 = NULL;
  const mxArray *c2_rhs80 = NULL;
  const mxArray *c2_lhs80 = NULL;
  const mxArray *c2_rhs81 = NULL;
  const mxArray *c2_lhs81 = NULL;
  const mxArray *c2_rhs82 = NULL;
  const mxArray *c2_lhs82 = NULL;
  const mxArray *c2_rhs83 = NULL;
  const mxArray *c2_lhs83 = NULL;
  const mxArray *c2_rhs84 = NULL;
  const mxArray *c2_lhs84 = NULL;
  const mxArray *c2_rhs85 = NULL;
  const mxArray *c2_lhs85 = NULL;
  const mxArray *c2_rhs86 = NULL;
  const mxArray *c2_lhs86 = NULL;
  const mxArray *c2_rhs87 = NULL;
  const mxArray *c2_lhs87 = NULL;
  const mxArray *c2_rhs88 = NULL;
  const mxArray *c2_lhs88 = NULL;
  const mxArray *c2_rhs89 = NULL;
  const mxArray *c2_lhs89 = NULL;
  const mxArray *c2_rhs90 = NULL;
  const mxArray *c2_lhs90 = NULL;
  const mxArray *c2_rhs91 = NULL;
  const mxArray *c2_lhs91 = NULL;
  const mxArray *c2_rhs92 = NULL;
  const mxArray *c2_lhs92 = NULL;
  const mxArray *c2_rhs93 = NULL;
  const mxArray *c2_lhs93 = NULL;
  const mxArray *c2_rhs94 = NULL;
  const mxArray *c2_lhs94 = NULL;
  const mxArray *c2_rhs95 = NULL;
  const mxArray *c2_lhs95 = NULL;
  const mxArray *c2_rhs96 = NULL;
  const mxArray *c2_lhs96 = NULL;
  const mxArray *c2_rhs97 = NULL;
  const mxArray *c2_lhs97 = NULL;
  const mxArray *c2_rhs98 = NULL;
  const mxArray *c2_lhs98 = NULL;
  const mxArray *c2_rhs99 = NULL;
  const mxArray *c2_lhs99 = NULL;
  const mxArray *c2_rhs100 = NULL;
  const mxArray *c2_lhs100 = NULL;
  const mxArray *c2_rhs101 = NULL;
  const mxArray *c2_lhs101 = NULL;
  const mxArray *c2_rhs102 = NULL;
  const mxArray *c2_lhs102 = NULL;
  const mxArray *c2_rhs103 = NULL;
  const mxArray *c2_lhs103 = NULL;
  const mxArray *c2_rhs104 = NULL;
  const mxArray *c2_lhs104 = NULL;
  const mxArray *c2_rhs105 = NULL;
  const mxArray *c2_lhs105 = NULL;
  const mxArray *c2_rhs106 = NULL;
  const mxArray *c2_lhs106 = NULL;
  const mxArray *c2_rhs107 = NULL;
  const mxArray *c2_lhs107 = NULL;
  const mxArray *c2_rhs108 = NULL;
  const mxArray *c2_lhs108 = NULL;
  const mxArray *c2_rhs109 = NULL;
  const mxArray *c2_lhs109 = NULL;
  const mxArray *c2_rhs110 = NULL;
  const mxArray *c2_lhs110 = NULL;
  const mxArray *c2_rhs111 = NULL;
  const mxArray *c2_lhs111 = NULL;
  const mxArray *c2_rhs112 = NULL;
  const mxArray *c2_lhs112 = NULL;
  const mxArray *c2_rhs113 = NULL;
  const mxArray *c2_lhs113 = NULL;
  const mxArray *c2_rhs114 = NULL;
  const mxArray *c2_lhs114 = NULL;
  const mxArray *c2_rhs115 = NULL;
  const mxArray *c2_lhs115 = NULL;
  const mxArray *c2_rhs116 = NULL;
  const mxArray *c2_lhs116 = NULL;
  const mxArray *c2_rhs117 = NULL;
  const mxArray *c2_lhs117 = NULL;
  const mxArray *c2_rhs118 = NULL;
  const mxArray *c2_lhs118 = NULL;
  const mxArray *c2_rhs119 = NULL;
  const mxArray *c2_lhs119 = NULL;
  const mxArray *c2_rhs120 = NULL;
  const mxArray *c2_lhs120 = NULL;
  const mxArray *c2_rhs121 = NULL;
  const mxArray *c2_lhs121 = NULL;
  const mxArray *c2_rhs122 = NULL;
  const mxArray *c2_lhs122 = NULL;
  const mxArray *c2_rhs123 = NULL;
  const mxArray *c2_lhs123 = NULL;
  const mxArray *c2_rhs124 = NULL;
  const mxArray *c2_lhs124 = NULL;
  const mxArray *c2_rhs125 = NULL;
  const mxArray *c2_lhs125 = NULL;
  const mxArray *c2_rhs126 = NULL;
  const mxArray *c2_lhs126 = NULL;
  const mxArray *c2_rhs127 = NULL;
  const mxArray *c2_lhs127 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 64);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 64);
  sf_mex_assign(&c2_rhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs64, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs64), "rhs", "rhs",
                  64);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs64), "lhs", "lhs",
                  64);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 65);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 65);
  sf_mex_assign(&c2_rhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs65, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs65), "rhs", "rhs",
                  65);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs65), "lhs", "lhs",
                  65);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isscaledtype"), "name", "name",
                  66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m"),
                  "resolved", "resolved", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517580U), "fileTimeLo",
                  "fileTimeLo", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 66);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 66);
  sf_mex_assign(&c2_rhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs66, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs66), "rhs", "rhs",
                  66);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs66), "lhs", "lhs",
                  66);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 67);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 67);
  sf_mex_assign(&c2_rhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs67, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs67), "rhs", "rhs",
                  67);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs67), "lhs", "lhs",
                  67);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fimath"),
                  "dominantType", "dominantType", 68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fimath/get.m"),
                  "resolved", "resolved", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 68);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 68);
  sf_mex_assign(&c2_rhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs68, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs68), "rhs", "rhs",
                  68);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs68), "lhs", "lhs",
                  68);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("strcmpi"), "name", "name", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "resolved",
                  "resolved", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 69);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 69);
  sf_mex_assign(&c2_rhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs69, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs69), "rhs", "rhs",
                  69);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs69), "lhs", "lhs",
                  69);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "context",
                  "context", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_assert_supported_string"),
                  "name", "name", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m"),
                  "resolved", "resolved", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 70);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 70);
  sf_mex_assign(&c2_rhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs70, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs70), "rhs", "rhs",
                  70);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs70), "lhs", "lhs",
                  70);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m!inrange"),
                  "context", "context", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_charmax"), "name", "name",
                  71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"),
                  "resolved", "resolved", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 71);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 71);
  sf_mex_assign(&c2_rhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs71, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs71), "rhs", "rhs",
                  71);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs71), "lhs", "lhs",
                  71);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"), "context",
                  "context", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 72);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 72);
  sf_mex_assign(&c2_rhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs72, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs72), "rhs", "rhs",
                  72);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs72), "lhs", "lhs",
                  72);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "context",
                  "context", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381857500U), "fileTimeLo",
                  "fileTimeLo", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 73);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 73);
  sf_mex_assign(&c2_rhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs73, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs73), "rhs", "rhs",
                  73);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs73), "lhs", "lhs",
                  73);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "context",
                  "context", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("min"), "name", "name", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1311262518U), "fileTimeLo",
                  "fileTimeLo", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 74);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 74);
  sf_mex_assign(&c2_rhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs74, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs74), "rhs", "rhs",
                  74);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs74), "lhs", "lhs",
                  74);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "context",
                  "context", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303184U), "fileTimeLo",
                  "fileTimeLo", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 75);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 75);
  sf_mex_assign(&c2_rhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs75, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs75), "rhs", "rhs",
                  75);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs75), "lhs", "lhs",
                  75);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 76);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 76);
  sf_mex_assign(&c2_rhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs76, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs76), "rhs", "rhs",
                  76);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs76), "lhs", "lhs",
                  76);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 77);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 77);
  sf_mex_assign(&c2_rhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs77, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs77), "rhs", "rhs",
                  77);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs77), "lhs", "lhs",
                  77);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 78);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 78);
  sf_mex_assign(&c2_rhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs78, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs78), "rhs", "rhs",
                  78);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs78), "lhs", "lhs",
                  78);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "context", "context", 79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.scalexpAlloc"),
                  "name", "name", 79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalexpAlloc.p"),
                  "resolved", "resolved", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 79);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 79);
  sf_mex_assign(&c2_rhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs79, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs79), "rhs", "rhs",
                  79);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs79), "lhs", "lhs",
                  79);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 80);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 80);
  sf_mex_assign(&c2_rhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs80, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs80), "rhs", "rhs",
                  80);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs80), "lhs", "lhs",
                  80);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 81);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 81);
  sf_mex_assign(&c2_rhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs81, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs81), "rhs", "rhs",
                  81);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs81), "lhs", "lhs",
                  81);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 82);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 82);
  sf_mex_assign(&c2_rhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs82, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs82), "rhs", "rhs",
                  82);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs82), "lhs", "lhs",
                  82);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/minus.m"),
                  "context", "context", 83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 83);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 83);
  sf_mex_assign(&c2_rhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs83, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs83), "rhs", "rhs",
                  83);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs83), "lhs", "lhs",
                  83);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "context",
                  "context", 84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("lower"), "name", "name", 84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/lower.m"), "resolved",
                  "resolved", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 84);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 84);
  sf_mex_assign(&c2_rhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs84, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs84), "rhs", "rhs",
                  84);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs84), "lhs", "lhs",
                  84);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/lower.m"), "context",
                  "context", 85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_string_transform"), "name",
                  "name", 85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "resolved", "resolved", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 85);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 85);
  sf_mex_assign(&c2_rhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs85, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs85), "rhs", "rhs",
                  85);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs85), "lhs", "lhs",
                  85);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "context", "context", 86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_assert_supported_string"),
                  "name", "name", 86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m"),
                  "resolved", "resolved", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 86);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 86);
  sf_mex_assign(&c2_rhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs86, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs86), "rhs", "rhs",
                  86);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs86), "lhs", "lhs",
                  86);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_assert_supported_string.m"),
                  "context", "context", 87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_charmax"), "name", "name",
                  87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"),
                  "resolved", "resolved", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 87);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 87);
  sf_mex_assign(&c2_rhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs87, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs87), "rhs", "rhs",
                  87);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs87), "lhs", "lhs",
                  87);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "context", "context", 88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_charmax"), "name", "name",
                  88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_charmax.m"),
                  "resolved", "resolved", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 88);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 88);
  sf_mex_assign(&c2_rhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs88, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs88), "rhs", "rhs",
                  88);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs88), "lhs", "lhs",
                  88);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "context", "context", 89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("colon"), "name", "name", 89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303188U), "fileTimeLo",
                  "fileTimeLo", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 89);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 89);
  sf_mex_assign(&c2_rhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs89, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs89), "rhs", "rhs",
                  89);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs89), "lhs", "lhs",
                  89);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("colon"), "name", "name", 90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303188U), "fileTimeLo",
                  "fileTimeLo", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 90);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 90);
  sf_mex_assign(&c2_rhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs90, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs90), "rhs", "rhs",
                  90);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs90), "lhs", "lhs",
                  90);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 91);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 91);
  sf_mex_assign(&c2_rhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs91, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs91), "rhs", "rhs",
                  91);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs91), "lhs", "lhs",
                  91);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 92);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 92);
  sf_mex_assign(&c2_rhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs92, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs92), "rhs", "rhs",
                  92);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs92), "lhs", "lhs",
                  92);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 93);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 93);
  sf_mex_assign(&c2_rhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs93, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs93), "rhs", "rhs",
                  93);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs93), "lhs", "lhs",
                  93);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 94);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 94);
  sf_mex_assign(&c2_rhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs94, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs94), "rhs", "rhs",
                  94);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs94), "lhs", "lhs",
                  94);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "context",
                  "context", 95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381857500U), "fileTimeLo",
                  "fileTimeLo", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 95);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 95);
  sf_mex_assign(&c2_rhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs95, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs95), "rhs", "rhs",
                  95);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs95), "lhs", "lhs",
                  95);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 96);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 96);
  sf_mex_assign(&c2_rhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs96, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs96), "rhs", "rhs",
                  96);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs96), "lhs", "lhs",
                  96);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmin"), "name", "name", 97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 97);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 97);
  sf_mex_assign(&c2_rhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs97, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs97), "rhs", "rhs",
                  97);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs97), "lhs", "lhs",
                  97);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 98);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 98);
  sf_mex_assign(&c2_rhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs98, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs98), "rhs", "rhs",
                  98);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs98), "lhs", "lhs",
                  98);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 99);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 99);
  sf_mex_assign(&c2_rhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs99, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs99), "rhs", "rhs",
                  99);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs99), "lhs", "lhs",
                  99);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "context",
                  "context", 100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.isaUint"),
                  "name", "name", 100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/isaUint.p"),
                  "resolved", "resolved", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389311520U), "fileTimeLo",
                  "fileTimeLo", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 100);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 100);
  sf_mex_assign(&c2_rhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs100, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs100), "rhs", "rhs",
                  100);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs100), "lhs", "lhs",
                  100);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_unsigned_class"), "name",
                  "name", 101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "resolved", "resolved", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 101);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 101);
  sf_mex_assign(&c2_rhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs101, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs101), "rhs", "rhs",
                  101);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs101), "lhs", "lhs",
                  101);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "context", "context", 102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.unsignedClass"),
                  "name", "name", 102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "resolved", "resolved", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389311522U), "fileTimeLo",
                  "fileTimeLo", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 102);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 102);
  sf_mex_assign(&c2_rhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs102, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs102), "rhs", "rhs",
                  102);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs102), "lhs", "lhs",
                  102);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/unsignedClass.p"),
                  "context", "context", 103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381857500U), "fileTimeLo",
                  "fileTimeLo", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 103);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 103);
  sf_mex_assign(&c2_rhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs103, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs103), "rhs", "rhs",
                  103);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs103), "lhs", "lhs",
                  103);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1323174178U), "fileTimeLo",
                  "fileTimeLo", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 104);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 104);
  sf_mex_assign(&c2_rhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs104, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs104), "rhs", "rhs",
                  104);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs104), "lhs", "lhs",
                  104);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 105);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 105);
  sf_mex_assign(&c2_rhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs105, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs105), "rhs", "rhs",
                  105);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs105), "lhs", "lhs",
                  105);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 106);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 106);
  sf_mex_assign(&c2_rhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs106, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs106), "rhs", "rhs",
                  106);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs106), "lhs", "lhs",
                  106);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372589616U), "fileTimeLo",
                  "fileTimeLo", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 107);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 107);
  sf_mex_assign(&c2_rhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs107, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs107), "rhs", "rhs",
                  107);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs107), "lhs", "lhs",
                  107);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("coder.internal.indexPlus"),
                  "name", "name", 108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexPlus.m"),
                  "resolved", "resolved", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1372590360U), "fileTimeLo",
                  "fileTimeLo", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 108);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 108);
  sf_mex_assign(&c2_rhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs108, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs108), "rhs", "rhs",
                  108);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs108), "lhs", "lhs",
                  108);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_signed_integer_colon"),
                  "context", "context", 109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987888U), "fileTimeLo",
                  "fileTimeLo", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 109);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 109);
  sf_mex_assign(&c2_rhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs109, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs109), "rhs", "rhs",
                  109);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs109), "lhs", "lhs",
                  109);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("intmax"), "name", "name", 110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1362265482U), "fileTimeLo",
                  "fileTimeLo", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 110);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 110);
  sf_mex_assign(&c2_rhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs110, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs110), "rhs", "rhs",
                  110);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs110), "lhs", "lhs",
                  110);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/eml_string_transform.m"),
                  "context", "context", 111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "name", "name", 111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("int8"), "dominantType",
                  "dominantType", 111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/char.m"), "resolved",
                  "resolved", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1319737168U), "fileTimeLo",
                  "fileTimeLo", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 111);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 111);
  sf_mex_assign(&c2_rhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs111, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs111), "rhs", "rhs",
                  111);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs111), "lhs", "lhs",
                  111);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 112);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("bitsrl"), "name", "name", 112);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 112);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitsrl.m"),
                  "resolved", "resolved", 112);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517566U), "fileTimeLo",
                  "fileTimeLo", 112);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 112);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 112);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 112);
  sf_mex_assign(&c2_rhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs112, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs112), "rhs", "rhs",
                  112);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs112), "lhs", "lhs",
                  112);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitsrl.m"),
                  "context", "context", 113);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fi_bitshift"), "name",
                  "name", 113);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 113);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "resolved", "resolved", 113);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717460U), "fileTimeLo",
                  "fileTimeLo", 113);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 113);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 113);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 113);
  sf_mex_assign(&c2_rhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs113, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs113), "rhs", "rhs",
                  113);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs113), "lhs", "lhs",
                  113);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 114);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_shift_checks"), "name",
                  "name", 114);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 114);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m"),
                  "resolved", "resolved", 114);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717460U), "fileTimeLo",
                  "fileTimeLo", 114);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 114);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 114);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 114);
  sf_mex_assign(&c2_rhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs114, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs114), "rhs", "rhs",
                  114);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs114), "lhs", "lhs",
                  114);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m"),
                  "context", "context", 115);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 115);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 115);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 115);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 115);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 115);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 115);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 115);
  sf_mex_assign(&c2_rhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs115, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs115), "rhs", "rhs",
                  115);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs115), "lhs", "lhs",
                  115);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m"),
                  "context", "context", 116);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("numerictype"), "name", "name",
                  116);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 116);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m"),
                  "resolved", "resolved", 116);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303186U), "fileTimeLo",
                  "fileTimeLo", 116);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 116);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 116);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 116);
  sf_mex_assign(&c2_rhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs116, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs116), "rhs", "rhs",
                  116);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs116), "lhs", "lhs",
                  116);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m"),
                  "context", "context", 117);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isslopebiasscaled"),
                  "name", "name", 117);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 117);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "resolved", "resolved", 117);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 117);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 117);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 117);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 117);
  sf_mex_assign(&c2_rhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs117, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs117), "rhs", "rhs",
                  117);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs117), "lhs", "lhs",
                  117);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_shift_checks.m"),
                  "context", "context", 118);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isequal"), "name", "name", 118);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 118);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 118);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286825958U), "fileTimeLo",
                  "fileTimeLo", 118);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 118);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 118);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 118);
  sf_mex_assign(&c2_rhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs118, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs118), "rhs", "rhs",
                  118);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs118), "lhs", "lhs",
                  118);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar"),
                  "context", "context", 119);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnan"), "name", "name", 119);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 119);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 119);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717458U), "fileTimeLo",
                  "fileTimeLo", 119);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 119);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 119);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 119);
  sf_mex_assign(&c2_rhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs119, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs119), "rhs", "rhs",
                  119);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs119), "lhs", "lhs",
                  119);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "context",
                  "context", 120);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 120);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 120);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 120);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363718156U), "fileTimeLo",
                  "fileTimeLo", 120);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 120);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 120);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 120);
  sf_mex_assign(&c2_rhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs120, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs120), "rhs", "rhs",
                  120);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs120), "lhs", "lhs",
                  120);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 121);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 121);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 121);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 121);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 121);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 121);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 121);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 121);
  sf_mex_assign(&c2_rhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs121, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs121), "rhs", "rhs",
                  121);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs121), "lhs", "lhs",
                  121);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 122);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 122);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 122);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 122);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 122);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 122);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 122);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 122);
  sf_mex_assign(&c2_rhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs122, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs122), "rhs", "rhs",
                  122);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs122), "lhs", "lhs",
                  122);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 123);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfixed"), "name", "name", 123);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 123);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 123);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 123);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 123);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 123);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 123);
  sf_mex_assign(&c2_rhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs123, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs123), "rhs", "rhs",
                  123);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs123), "lhs", "lhs",
                  123);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 124);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("numerictype"), "name", "name",
                  124);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 124);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m"),
                  "resolved", "resolved", 124);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303186U), "fileTimeLo",
                  "fileTimeLo", 124);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 124);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 124);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 124);
  sf_mex_assign(&c2_rhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs124, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs124), "rhs", "rhs",
                  124);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs124), "lhs", "lhs",
                  124);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 125);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 125);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 125);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 125);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381857500U), "fileTimeLo",
                  "fileTimeLo", 125);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 125);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 125);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 125);
  sf_mex_assign(&c2_rhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs125, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs125), "rhs", "rhs",
                  125);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs125), "lhs", "lhs",
                  125);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 126);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("fimath"), "name", "name", 126);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 126);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m"), "resolved",
                  "resolved", 126);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381857498U), "fileTimeLo",
                  "fileTimeLo", 126);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 126);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 126);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 126);
  sf_mex_assign(&c2_rhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs126, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs126), "rhs", "rhs",
                  126);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs126), "lhs", "lhs",
                  126);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_fi_bitshift.m"),
                  "context", "context", 127);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "eml_get_int_shift_or_bit_index"), "name", "name", 127);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 127);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_get_int_shift_or_bit_index.m"),
                  "resolved", "resolved", 127);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717432U), "fileTimeLo",
                  "fileTimeLo", 127);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 127);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 127);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 127);
  sf_mex_assign(&c2_rhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs127, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs127), "rhs", "rhs",
                  127);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs127), "lhs", "lhs",
                  127);
  sf_mex_destroy(&c2_rhs64);
  sf_mex_destroy(&c2_lhs64);
  sf_mex_destroy(&c2_rhs65);
  sf_mex_destroy(&c2_lhs65);
  sf_mex_destroy(&c2_rhs66);
  sf_mex_destroy(&c2_lhs66);
  sf_mex_destroy(&c2_rhs67);
  sf_mex_destroy(&c2_lhs67);
  sf_mex_destroy(&c2_rhs68);
  sf_mex_destroy(&c2_lhs68);
  sf_mex_destroy(&c2_rhs69);
  sf_mex_destroy(&c2_lhs69);
  sf_mex_destroy(&c2_rhs70);
  sf_mex_destroy(&c2_lhs70);
  sf_mex_destroy(&c2_rhs71);
  sf_mex_destroy(&c2_lhs71);
  sf_mex_destroy(&c2_rhs72);
  sf_mex_destroy(&c2_lhs72);
  sf_mex_destroy(&c2_rhs73);
  sf_mex_destroy(&c2_lhs73);
  sf_mex_destroy(&c2_rhs74);
  sf_mex_destroy(&c2_lhs74);
  sf_mex_destroy(&c2_rhs75);
  sf_mex_destroy(&c2_lhs75);
  sf_mex_destroy(&c2_rhs76);
  sf_mex_destroy(&c2_lhs76);
  sf_mex_destroy(&c2_rhs77);
  sf_mex_destroy(&c2_lhs77);
  sf_mex_destroy(&c2_rhs78);
  sf_mex_destroy(&c2_lhs78);
  sf_mex_destroy(&c2_rhs79);
  sf_mex_destroy(&c2_lhs79);
  sf_mex_destroy(&c2_rhs80);
  sf_mex_destroy(&c2_lhs80);
  sf_mex_destroy(&c2_rhs81);
  sf_mex_destroy(&c2_lhs81);
  sf_mex_destroy(&c2_rhs82);
  sf_mex_destroy(&c2_lhs82);
  sf_mex_destroy(&c2_rhs83);
  sf_mex_destroy(&c2_lhs83);
  sf_mex_destroy(&c2_rhs84);
  sf_mex_destroy(&c2_lhs84);
  sf_mex_destroy(&c2_rhs85);
  sf_mex_destroy(&c2_lhs85);
  sf_mex_destroy(&c2_rhs86);
  sf_mex_destroy(&c2_lhs86);
  sf_mex_destroy(&c2_rhs87);
  sf_mex_destroy(&c2_lhs87);
  sf_mex_destroy(&c2_rhs88);
  sf_mex_destroy(&c2_lhs88);
  sf_mex_destroy(&c2_rhs89);
  sf_mex_destroy(&c2_lhs89);
  sf_mex_destroy(&c2_rhs90);
  sf_mex_destroy(&c2_lhs90);
  sf_mex_destroy(&c2_rhs91);
  sf_mex_destroy(&c2_lhs91);
  sf_mex_destroy(&c2_rhs92);
  sf_mex_destroy(&c2_lhs92);
  sf_mex_destroy(&c2_rhs93);
  sf_mex_destroy(&c2_lhs93);
  sf_mex_destroy(&c2_rhs94);
  sf_mex_destroy(&c2_lhs94);
  sf_mex_destroy(&c2_rhs95);
  sf_mex_destroy(&c2_lhs95);
  sf_mex_destroy(&c2_rhs96);
  sf_mex_destroy(&c2_lhs96);
  sf_mex_destroy(&c2_rhs97);
  sf_mex_destroy(&c2_lhs97);
  sf_mex_destroy(&c2_rhs98);
  sf_mex_destroy(&c2_lhs98);
  sf_mex_destroy(&c2_rhs99);
  sf_mex_destroy(&c2_lhs99);
  sf_mex_destroy(&c2_rhs100);
  sf_mex_destroy(&c2_lhs100);
  sf_mex_destroy(&c2_rhs101);
  sf_mex_destroy(&c2_lhs101);
  sf_mex_destroy(&c2_rhs102);
  sf_mex_destroy(&c2_lhs102);
  sf_mex_destroy(&c2_rhs103);
  sf_mex_destroy(&c2_lhs103);
  sf_mex_destroy(&c2_rhs104);
  sf_mex_destroy(&c2_lhs104);
  sf_mex_destroy(&c2_rhs105);
  sf_mex_destroy(&c2_lhs105);
  sf_mex_destroy(&c2_rhs106);
  sf_mex_destroy(&c2_lhs106);
  sf_mex_destroy(&c2_rhs107);
  sf_mex_destroy(&c2_lhs107);
  sf_mex_destroy(&c2_rhs108);
  sf_mex_destroy(&c2_lhs108);
  sf_mex_destroy(&c2_rhs109);
  sf_mex_destroy(&c2_lhs109);
  sf_mex_destroy(&c2_rhs110);
  sf_mex_destroy(&c2_lhs110);
  sf_mex_destroy(&c2_rhs111);
  sf_mex_destroy(&c2_lhs111);
  sf_mex_destroy(&c2_rhs112);
  sf_mex_destroy(&c2_lhs112);
  sf_mex_destroy(&c2_rhs113);
  sf_mex_destroy(&c2_lhs113);
  sf_mex_destroy(&c2_rhs114);
  sf_mex_destroy(&c2_lhs114);
  sf_mex_destroy(&c2_rhs115);
  sf_mex_destroy(&c2_lhs115);
  sf_mex_destroy(&c2_rhs116);
  sf_mex_destroy(&c2_lhs116);
  sf_mex_destroy(&c2_rhs117);
  sf_mex_destroy(&c2_lhs117);
  sf_mex_destroy(&c2_rhs118);
  sf_mex_destroy(&c2_lhs118);
  sf_mex_destroy(&c2_rhs119);
  sf_mex_destroy(&c2_lhs119);
  sf_mex_destroy(&c2_rhs120);
  sf_mex_destroy(&c2_lhs120);
  sf_mex_destroy(&c2_rhs121);
  sf_mex_destroy(&c2_lhs121);
  sf_mex_destroy(&c2_rhs122);
  sf_mex_destroy(&c2_lhs122);
  sf_mex_destroy(&c2_rhs123);
  sf_mex_destroy(&c2_lhs123);
  sf_mex_destroy(&c2_rhs124);
  sf_mex_destroy(&c2_lhs124);
  sf_mex_destroy(&c2_rhs125);
  sf_mex_destroy(&c2_lhs125);
  sf_mex_destroy(&c2_rhs126);
  sf_mex_destroy(&c2_lhs126);
  sf_mex_destroy(&c2_rhs127);
  sf_mex_destroy(&c2_lhs127);
}

static void c2_c_info_helper(const mxArray **c2_info)
{
  const mxArray *c2_rhs128 = NULL;
  const mxArray *c2_lhs128 = NULL;
  const mxArray *c2_rhs129 = NULL;
  const mxArray *c2_lhs129 = NULL;
  const mxArray *c2_rhs130 = NULL;
  const mxArray *c2_lhs130 = NULL;
  const mxArray *c2_rhs131 = NULL;
  const mxArray *c2_lhs131 = NULL;
  const mxArray *c2_rhs132 = NULL;
  const mxArray *c2_lhs132 = NULL;
  const mxArray *c2_rhs133 = NULL;
  const mxArray *c2_lhs133 = NULL;
  const mxArray *c2_rhs134 = NULL;
  const mxArray *c2_lhs134 = NULL;
  const mxArray *c2_rhs135 = NULL;
  const mxArray *c2_lhs135 = NULL;
  const mxArray *c2_rhs136 = NULL;
  const mxArray *c2_lhs136 = NULL;
  const mxArray *c2_rhs137 = NULL;
  const mxArray *c2_lhs137 = NULL;
  const mxArray *c2_rhs138 = NULL;
  const mxArray *c2_lhs138 = NULL;
  const mxArray *c2_rhs139 = NULL;
  const mxArray *c2_lhs139 = NULL;
  const mxArray *c2_rhs140 = NULL;
  const mxArray *c2_lhs140 = NULL;
  const mxArray *c2_rhs141 = NULL;
  const mxArray *c2_lhs141 = NULL;
  const mxArray *c2_rhs142 = NULL;
  const mxArray *c2_lhs142 = NULL;
  const mxArray *c2_rhs143 = NULL;
  const mxArray *c2_lhs143 = NULL;
  const mxArray *c2_rhs144 = NULL;
  const mxArray *c2_lhs144 = NULL;
  const mxArray *c2_rhs145 = NULL;
  const mxArray *c2_lhs145 = NULL;
  const mxArray *c2_rhs146 = NULL;
  const mxArray *c2_lhs146 = NULL;
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_get_int_shift_or_bit_index.m"),
                  "context", "context", 128);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("floor"), "name", "name", 128);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 128);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 128);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 128);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 128);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 128);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 128);
  sf_mex_assign(&c2_rhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs128, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs128), "rhs", "rhs",
                  128);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs128), "lhs", "lhs",
                  128);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/@embedded/@fi/eml_fi_bitshift.m!localFixptBitshift"),
                  "context", "context", 129);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_feval"), "name", "name",
                  129);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 129);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_feval.m"),
                  "resolved", "resolved", 129);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517570U), "fileTimeLo",
                  "fileTimeLo", 129);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 129);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 129);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 129);
  sf_mex_assign(&c2_rhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs129, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs129), "rhs", "rhs",
                  129);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs129), "lhs", "lhs",
                  129);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_feval.m"),
                  "context", "context", 130);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 130);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 130);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 130);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1381857500U), "fileTimeLo",
                  "fileTimeLo", 130);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 130);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 130);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 130);
  sf_mex_assign(&c2_rhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs130, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs130), "rhs", "rhs",
                  130);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs130), "lhs", "lhs",
                  130);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/castLike.m"),
                  "context", "context", 131);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("fi_impl"), "name", "name", 131);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 131);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "resolved",
                  "resolved", 131);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1389302372U), "fileTimeLo",
                  "fileTimeLo", 131);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 131);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 131);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 131);
  sf_mex_assign(&c2_rhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs131, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs131), "rhs", "rhs",
                  131);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs131), "lhs", "lhs",
                  131);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 132);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 132);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 132);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 132);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 132);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 132);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 132);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 132);
  sf_mex_assign(&c2_rhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs132, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs132), "rhs", "rhs",
                  132);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs132), "lhs", "lhs",
                  132);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 133);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 133);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 133);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 133);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 133);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 133);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 133);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 133);
  sf_mex_assign(&c2_rhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs133, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs133), "rhs", "rhs",
                  133);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs133), "lhs", "lhs",
                  133);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m"), "context",
                  "context", 134);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("strcmpi"), "name", "name", 134);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 134);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/strfun/strcmpi.m"), "resolved",
                  "resolved", 134);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1327422710U), "fileTimeLo",
                  "fileTimeLo", 134);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 134);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 134);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 134);
  sf_mex_assign(&c2_rhs134, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs134, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs134), "rhs", "rhs",
                  134);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs134), "lhs", "lhs",
                  134);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 135);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isnumerictype"), "name",
                  "name", 135);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 135);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m"), "resolved",
                  "resolved", 135);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 135);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 135);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 135);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 135);
  sf_mex_assign(&c2_rhs135, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs135, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs135), "rhs", "rhs",
                  135);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs135), "lhs", "lhs",
                  135);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 136);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfimath"), "name", "name",
                  136);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 136);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfimath.m"), "resolved",
                  "resolved", 136);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 136);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 136);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 136);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 136);
  sf_mex_assign(&c2_rhs136, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs136, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs136), "rhs", "rhs",
                  136);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs136), "lhs", "lhs",
                  136);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 137);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("get"), "name", "name", 137);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 137);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m"),
                  "resolved", "resolved", 137);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1378303182U), "fileTimeLo",
                  "fileTimeLo", 137);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 137);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 137);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 137);
  sf_mex_assign(&c2_rhs137, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs137, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs137), "rhs", "rhs",
                  137);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs137), "lhs", "lhs",
                  137);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 138);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fi_constructor_helper"),
                  "name", "name", 138);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 138);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/fixedpoint/fixedpoint/eml_fi_constructor_helper.m"),
                  "resolved", "resolved", 138);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1375987896U), "fileTimeLo",
                  "fileTimeLo", 138);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 138);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 138);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 138);
  sf_mex_assign(&c2_rhs138, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs138, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs138), "rhs", "rhs",
                  138);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs138), "lhs", "lhs",
                  138);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!eml_fi_case2"),
                  "context", "context", 139);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_fi_checkforerror"), "name",
                  "name", 139);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 139);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m"),
                  "resolved", "resolved", 139);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1360285946U), "fileTimeLo",
                  "fileTimeLo", 139);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 139);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 139);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 139);
  sf_mex_assign(&c2_rhs139, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs139, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs139), "rhs", "rhs",
                  139);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs139), "lhs", "lhs",
                  139);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(""), "context", "context", 140);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("bitand"), "name", "name", 140);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 140);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "resolved", "resolved", 140);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1363717454U), "fileTimeLo",
                  "fileTimeLo", 140);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 140);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 140);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 140);
  sf_mex_assign(&c2_rhs140, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs140, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs140), "rhs", "rhs",
                  140);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs140), "lhs", "lhs",
                  140);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "context", "context", 141);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfi"), "name", "name", 141);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 141);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m"), "resolved",
                  "resolved", 141);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517558U), "fileTimeLo",
                  "fileTimeLo", 141);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 141);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 141);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 141);
  sf_mex_assign(&c2_rhs141, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs141, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs141), "rhs", "rhs",
                  141);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs141), "lhs", "lhs",
                  141);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "context", "context", 142);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isfixed"), "name", "name", 142);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 142);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m"),
                  "resolved", "resolved", 142);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517578U), "fileTimeLo",
                  "fileTimeLo", 142);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 142);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 142);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 142);
  sf_mex_assign(&c2_rhs142, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs142, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs142), "rhs", "rhs",
                  142);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs142), "lhs", "lhs",
                  142);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "context", "context", 143);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_isslopebiasscaled"),
                  "name", "name", 143);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 143);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_isslopebiasscaled.m"),
                  "resolved", "resolved", 143);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1289523246U), "fileTimeLo",
                  "fileTimeLo", 143);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 143);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 143);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 143);
  sf_mex_assign(&c2_rhs143, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs143, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs143), "rhs", "rhs",
                  143);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs143), "lhs", "lhs",
                  143);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "context", "context", 144);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("isequal"), "name", "name", 144);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.numerictype"),
                  "dominantType", "dominantType", 144);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/isequal.m"),
                  "resolved", "resolved", 144);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517540U), "fileTimeLo",
                  "fileTimeLo", 144);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 144);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 144);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 144);
  sf_mex_assign(&c2_rhs144, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs144, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs144), "rhs", "rhs",
                  144);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs144), "lhs", "lhs",
                  144);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "context", "context", 145);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_checkfimathforbinaryops"),
                  "name", "name", 145);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 145);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_checkfimathforbinaryops.m"),
                  "resolved", "resolved", 145);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1346517568U), "fileTimeLo",
                  "fileTimeLo", 145);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 145);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 145);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 145);
  sf_mex_assign(&c2_rhs145, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs145, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs145), "rhs", "rhs",
                  145);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs145), "lhs", "lhs",
                  145);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/bitand.m"),
                  "context", "context", 146);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 146);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut("embedded.fi"), "dominantType",
                  "dominantType", 146);
  sf_mex_addfield(*c2_info, c2_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 146);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(1286825996U), "fileTimeLo",
                  "fileTimeLo", 146);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 146);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 146);
  sf_mex_addfield(*c2_info, c2_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 146);
  sf_mex_assign(&c2_rhs146, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c2_lhs146, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_rhs146), "rhs", "rhs",
                  146);
  sf_mex_addfield(*c2_info, sf_mex_duplicatearraysafe(&c2_lhs146), "lhs", "lhs",
                  146);
  sf_mex_destroy(&c2_rhs128);
  sf_mex_destroy(&c2_lhs128);
  sf_mex_destroy(&c2_rhs129);
  sf_mex_destroy(&c2_lhs129);
  sf_mex_destroy(&c2_rhs130);
  sf_mex_destroy(&c2_lhs130);
  sf_mex_destroy(&c2_rhs131);
  sf_mex_destroy(&c2_lhs131);
  sf_mex_destroy(&c2_rhs132);
  sf_mex_destroy(&c2_lhs132);
  sf_mex_destroy(&c2_rhs133);
  sf_mex_destroy(&c2_lhs133);
  sf_mex_destroy(&c2_rhs134);
  sf_mex_destroy(&c2_lhs134);
  sf_mex_destroy(&c2_rhs135);
  sf_mex_destroy(&c2_lhs135);
  sf_mex_destroy(&c2_rhs136);
  sf_mex_destroy(&c2_lhs136);
  sf_mex_destroy(&c2_rhs137);
  sf_mex_destroy(&c2_lhs137);
  sf_mex_destroy(&c2_rhs138);
  sf_mex_destroy(&c2_lhs138);
  sf_mex_destroy(&c2_rhs139);
  sf_mex_destroy(&c2_lhs139);
  sf_mex_destroy(&c2_rhs140);
  sf_mex_destroy(&c2_lhs140);
  sf_mex_destroy(&c2_rhs141);
  sf_mex_destroy(&c2_lhs141);
  sf_mex_destroy(&c2_rhs142);
  sf_mex_destroy(&c2_lhs142);
  sf_mex_destroy(&c2_rhs143);
  sf_mex_destroy(&c2_lhs143);
  sf_mex_destroy(&c2_rhs144);
  sf_mex_destroy(&c2_lhs144);
  sf_mex_destroy(&c2_rhs145);
  sf_mex_destroy(&c2_lhs145);
  sf_mex_destroy(&c2_rhs146);
  sf_mex_destroy(&c2_lhs146);
}

static void c2_eml_fi_checkforconst(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_b_eml_fi_checkforconst(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_c_eml_fi_checkforconst(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_d_eml_fi_checkforconst(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c2_e_eml_fi_checkforconst(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static boolean_T c2_logical(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_a)
{
  uint8_T c2_a0;
  uint8_T c2_b_a;
  uint8_T c2_b_a0;
  uint8_T c2_a1;
  uint8_T c2_b_a1;
  (void)chartInstance;
  c2_a0 = c2_a;
  c2_b_a = c2_a0;
  c2_b_a0 = c2_b_a;
  c2_a1 = c2_b_a0;
  c2_b_a1 = c2_a1;
  return c2_b_a1 != 0;
}

static uint8_T c2_uint8(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c2_A)
{
  int8_T c2_xfi;
  const mxArray *c2_propValScalar = NULL;
  const mxArray *c2_pseudoData = NULL;
  const mxArray *c2_codeGenSupportFlag = NULL;
  int8_T c2_i7;
  (void)chartInstance;
  c2_xfi = c2_A;
  sf_mex_destroy(&c2_propValScalar);
  sf_mex_destroy(&c2_pseudoData);
  sf_mex_destroy(&c2_codeGenSupportFlag);
  c2_i7 = c2_xfi;
  if (c2_i7 < 0) {
    c2_i7 = 0;
  }

  return (uint8_T)c2_i7;
}

static uint8_T c2_b_uint8(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_A)
{
  uint8_T c2_xfi;
  const mxArray *c2_propValScalar = NULL;
  const mxArray *c2_pseudoData = NULL;
  const mxArray *c2_codeGenSupportFlag = NULL;
  (void)chartInstance;
  c2_xfi = c2_A;
  sf_mex_destroy(&c2_propValScalar);
  sf_mex_destroy(&c2_pseudoData);
  sf_mex_destroy(&c2_codeGenSupportFlag);
  return c2_xfi;
}

static uint8_T c2_c_uint8(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c2_A)
{
  uint8_T c2_xfi;
  const mxArray *c2_propValScalar = NULL;
  const mxArray *c2_pseudoData = NULL;
  const mxArray *c2_codeGenSupportFlag = NULL;
  (void)chartInstance;
  c2_xfi = c2_A;
  sf_mex_destroy(&c2_propValScalar);
  sf_mex_destroy(&c2_pseudoData);
  sf_mex_destroy(&c2_codeGenSupportFlag);
  return c2_xfi;
}

static boolean_T c2_b_logical(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, uint8_T c2_a)
{
  uint8_T c2_a0;
  uint8_T c2_b_a;
  uint8_T c2_b_a0;
  uint8_T c2_a1;
  uint8_T c2_b_a1;
  (void)chartInstance;
  c2_a0 = c2_a;
  c2_b_a = c2_a0;
  c2_b_a0 = c2_b_a;
  c2_a1 = c2_b_a0;
  c2_b_a1 = c2_a1;
  return c2_b_a1 != 0;
}

static void c2_eml_scalar_eg(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static int8_T c2_minus(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  int8_T c2_a0)
{
  int8_T c2_a;
  c2_a = c2_a0;
  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  return (int8_T)(c2_a - 1);
}

static uint16_T c2_bitsrl(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint16_T c2_ain)
{
  uint16_T c2_b_ain;
  uint16_T c2_a;
  uint16_T c2_b_a;
  uint16_T c2_c;
  c2_b_ain = c2_ain;
  c2_eml_switch_helper(chartInstance);
  c2_a = c2_b_ain;
  c2_b_a = c2_a;
  c2_c = c2_eml_feval(chartInstance, c2_b_a, 9);
  return c2_c;
}

static void c2_eml_switch_helper(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static uint16_T c2_eml_feval(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, uint16_T c2_varargin_1, int32_T c2_varargin_2)
{
  (void)chartInstance;
  return (uint16_T)((uint32_T)c2_varargin_1 >> _SFD_EML_ARRAY_BOUNDS_CHECK("",
    (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_varargin_2), 0, 11, 1, 1));
}

static void c2_f_eml_fi_checkforconst(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static uint16_T c2_b_bitsrl(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint16_T c2_ain)
{
  uint16_T c2_b_ain;
  uint16_T c2_a;
  uint16_T c2_b_a;
  uint16_T c2_c;
  c2_b_ain = c2_ain;
  c2_eml_switch_helper(chartInstance);
  c2_a = c2_b_ain;
  c2_b_a = c2_a;
  c2_c = c2_eml_feval(chartInstance, c2_b_a, 3);
  return c2_c;
}

static uint16_T c2_bitand(SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint16_T c2_a, uint16_T c2_b)
{
  uint16_T c2_c_uint;
  (void)chartInstance;
  c2_c_uint = (uint16_T)((uint16_T)(c2_a & c2_b) & 4095U);
  return c2_c_uint;
}

static const mxArray *c2_u_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_db_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i8;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i8, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i8;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c2_u = *(uint8_T *)c2_inData;
    c2_y = NULL;
    c2_b_u = c2_u;
    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), false);
    sf_mex_assign(&c2_y, sf_mex_call("fi", 1U, 8U, 15, "fimath", 14, sf_mex_dup
      (c2_eml_mx), 15, "numerictype", 14, sf_mex_dup(c2_g_eml_mx), 15,
      "simulinkarray", 14, c2_b_y, 15, "fimathislocal", 3, true), false);
    sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  } else {
    sf_mex_assign(&c2_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")), false);
  }

  return c2_mxArrayOutData;
}

static uint8_T c2_eb_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

static uint8_T c2_fb_emlrt_marshallIn(SFc2_gm_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  const mxArray *c2_mxFi = NULL;
  const mxArray *c2_mxInt = NULL;
  uint8_T c2_u12;
  (void)chartInstance;
  sf_mex_check_fi(c2_parentId, c2_u, false, 0U, NULL, c2_eml_mx, c2_g_eml_mx);
  sf_mex_assign(&c2_mxFi, sf_mex_dup(c2_u), false);
  sf_mex_assign(&c2_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c2_mxFi)), false);
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
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
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

static void init_dsm_address_info(SFc2_gm_hdlcodercpu_emlInstanceStruct
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

void sf_c2_gm_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3957887314U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1240459716U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(528499963U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2145752500U);
}

mxArray *sf_c2_gm_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("iQoNdPywKovccOPWnyfr9F");
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

mxArray *sf_c2_gm_hdlcodercpu_eml_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_gm_hdlcodercpu_eml_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_gm_hdlcodercpu_eml(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[15],T\"AC_data\",},{M[1],M[14],T\"AC_func\",},{M[1],M[9],T\"ALU_func\",},{M[1],M[12],T\"DM_addr\",},{M[1],M[13],T\"DM_r_w\",},{M[1],M[19],T\"IM_read\",},{M[1],M[16],T\"IR_func\",},{M[1],M[17],T\"PC_func\",},{M[1],M[18],T\"addr_inc\",},{M[1],M[20],T\"hlt\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[8],T\"out_flags\",},{M[1],M[10],T\"print_data\",},{M[1],M[7],T\"shifter_sel\",},{M[4],M[0],T\"CPU_state\",S'l','i','p'{{M1x2[2174 2183],M[0],}}},{M[4],M[0],T\"address_data\",S'l','i','p'{{M1x2[2984 2996],M[0],}}},{M[4],M[0],T\"indirect_address\",S'l','i','p'{{M1x2[3009 3025],M[0],}}},{M[4],M[0],T\"major_opcode\",S'l','i','p'{{M1x2[2932 2944],M[0],}}},{M[4],M[0],T\"minor_opcode\",S'l','i','p'{{M1x2[2958 2970],M[0],}}},{M[4],M[0],T\"previous_CPU_state\",S'l','i','p'{{M1x2[2250 2268],M[0],}}},{M[8],M[0],T\"is_active_c2_gm_hdlcodercpu_eml\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 20, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_gm_hdlcodercpu_eml_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _gm_hdlcodercpu_emlMachineNumber_,
           2,
           1,
           1,
           0,
           17,
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
        _SFD_CV_INIT_EML(0,1,1,18,0,0,6,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,17416);
        _SFD_CV_INIT_EML_IF(0,1,0,2185,2207,-1,2237);
        _SFD_CV_INIT_EML_IF(0,1,1,2270,2301,-1,2340);
        _SFD_CV_INIT_EML_IF(0,1,2,2342,2356,-1,2386);
        _SFD_CV_INIT_EML_IF(0,1,3,3028,3053,-1,3219);
        _SFD_CV_INIT_EML_IF(0,1,4,6972,6997,7213,7461);
        _SFD_CV_INIT_EML_IF(0,1,5,7783,7797,-1,8051);
        _SFD_CV_INIT_EML_IF(0,1,6,8210,8224,-1,8478);
        _SFD_CV_INIT_EML_IF(0,1,7,8807,8842,-1,9957);
        _SFD_CV_INIT_EML_IF(0,1,8,9168,9182,-1,9452);
        _SFD_CV_INIT_EML_IF(0,1,9,9629,9643,-1,9913);
        _SFD_CV_INIT_EML_IF(0,1,10,14064,14098,14186,14280);
        _SFD_CV_INIT_EML_IF(0,1,11,14510,14535,14659,14710);
        _SFD_CV_INIT_EML_IF(0,1,12,14847,14881,14969,15063);
        _SFD_CV_INIT_EML_IF(0,1,13,15285,15310,15434,15485);
        _SFD_CV_INIT_EML_IF(0,1,14,15629,15663,15751,15845);
        _SFD_CV_INIT_EML_IF(0,1,15,16067,16092,16216,16267);
        _SFD_CV_INIT_EML_IF(0,1,16,16411,16445,16533,16627);
        _SFD_CV_INIT_EML_IF(0,1,17,16849,16874,16999,17051);

        {
          static int caseStart[] = { 17231, 3354, 3679, 3943, 4139, 4703, 12034,
            12314, 12607, 12886, 13177, 13469, 13750, 13885, 14294, 14716, 15069,
            15499, 15851, 16281, 16633, 17065, 17141 };

          static int caseExprEnd[] = { 17240, 3360, 3685, 3949, 4145, 4709,
            12040, 12320, 12613, 12892, 13184, 13476, 13757, 13892, 14301, 14723,
            15076, 15506, 15858, 16288, 16640, 17072, 17148 };

          _SFD_CV_INIT_EML_SWITCH(0,1,0,3221,3238,17416,23,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        {
          static int caseStart[] = { -1, 4801, 5176, 5462, 5737, 5996, 6739,
            7491, 8618 };

          static int caseExprEnd[] = { 8, 4807, 5182, 5468, 5743, 6002, 6745,
            7497, 8624 };

          _SFD_CV_INIT_EML_SWITCH(0,1,1,4761,4788,12000,9,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        {
          static int caseStart[] = { -1, 6136, 6435 };

          static int caseExprEnd[] = { 8, 6142, 6441 };

          _SFD_CV_INIT_EML_SWITCH(0,1,2,6083,6115,6618,3,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        {
          static int caseStart[] = { -1, 7669, 8097 };

          static int caseExprEnd[] = { 8, 7675, 8103 };

          _SFD_CV_INIT_EML_SWITCH(0,1,3,7576,7608,8498,3,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        {
          static int caseStart[] = { -1, 9042, 9503 };

          static int caseExprEnd[] = { 8, 9048, 9509 };

          _SFD_CV_INIT_EML_SWITCH(0,1,4,8985,9017,9937,3,&(caseStart[0]),
            &(caseExprEnd[0]));
        }

        {
          static int caseStart[] = { 11746, 10072, 10263, 10405, 10658, 10865,
            11058, 11251, 11539 };

          static int caseExprEnd[] = { 11755, 10078, 10269, 10412, 10665, 10872,
            11065, 11258, 11546 };

          _SFD_CV_INIT_EML_SWITCH(0,1,5,10024,10051,11950,9,&(caseStart[0]),
            &(caseExprEnd[0]));
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
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _gm_hdlcodercpu_emlMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "kvFtfeYdN8pSp74NTHn3ZB";
}

static void sf_opaque_initialize_c2_gm_hdlcodercpu_eml(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c2_gm_hdlcodercpu_eml((SFc2_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
  initialize_c2_gm_hdlcodercpu_eml((SFc2_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_gm_hdlcodercpu_eml(void *chartInstanceVar)
{
  enable_c2_gm_hdlcodercpu_eml((SFc2_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c2_gm_hdlcodercpu_eml(void *chartInstanceVar)
{
  disable_c2_gm_hdlcodercpu_eml((SFc2_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c2_gm_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_gateway_c2_gm_hdlcodercpu_eml((SFc2_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_gm_hdlcodercpu_eml(SimStruct*
  S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_gm_hdlcodercpu_eml
    ((SFc2_gm_hdlcodercpu_emlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_gm_hdlcodercpu_eml();/* state var info */
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

extern void sf_internal_set_sim_state_c2_gm_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c2_gm_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_gm_hdlcodercpu_eml((SFc2_gm_hdlcodercpu_emlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_gm_hdlcodercpu_eml(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_gm_hdlcodercpu_eml(S);
}

static void sf_opaque_set_sim_state_c2_gm_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c2_gm_hdlcodercpu_eml(S, st);
}

static void sf_opaque_terminate_c2_gm_hdlcodercpu_eml(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_gm_hdlcodercpu_emlInstanceStruct*) chartInstanceVar)
      ->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_gm_hdlcodercpu_eml_optimization_info();
    }

    finalize_c2_gm_hdlcodercpu_eml((SFc2_gm_hdlcodercpu_emlInstanceStruct*)
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
  initSimStructsc2_gm_hdlcodercpu_eml((SFc2_gm_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_gm_hdlcodercpu_eml(SimStruct *S)
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
    initialize_params_c2_gm_hdlcodercpu_eml
      ((SFc2_gm_hdlcodercpu_emlInstanceStruct*)(chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_gm_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_gm_hdlcodercpu_eml_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,13);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=13; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(684395544U));
  ssSetChecksum1(S,(1090490005U));
  ssSetChecksum2(S,(3663842914U));
  ssSetChecksum3(S,(1627414773U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_gm_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_gm_hdlcodercpu_eml(SimStruct *S)
{
  SFc2_gm_hdlcodercpu_emlInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc2_gm_hdlcodercpu_emlInstanceStruct *)utMalloc(sizeof
    (SFc2_gm_hdlcodercpu_emlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_gm_hdlcodercpu_emlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c2_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c2_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c2_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_gm_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c2_gm_hdlcodercpu_eml;
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

void c2_gm_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_gm_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_gm_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_gm_hdlcodercpu_eml(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_gm_hdlcodercpu_eml_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
