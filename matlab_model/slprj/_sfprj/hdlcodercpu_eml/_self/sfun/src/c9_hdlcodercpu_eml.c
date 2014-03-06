/* Include files */

#include "blascompat32.h"
#include "hdlcodercpu_eml_sfun.h"
#include "c9_hdlcodercpu_eml.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "hdlcodercpu_eml_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const mxArray *c9_eml_mx;
static const char * c9_debug_family_names[6] = { "hdl_fm", "nargin", "nargout",
  "jmp_offset", "PC_current", "PC_next" };

static const mxArray *c9_b_eml_mx;
static const mxArray *c9_c_eml_mx;

/* Function Declarations */
static void initialize_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initialize_params_c9_hdlcodercpu_eml
  (SFc9_hdlcodercpu_emlInstanceStruct *chartInstance);
static void enable_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void disable_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c9_update_debugger_state_c9_hdlcodercpu_eml
  (SFc9_hdlcodercpu_emlInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c9_hdlcodercpu_eml
  (SFc9_hdlcodercpu_emlInstanceStruct *chartInstance);
static void set_sim_state_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c9_st);
static void finalize_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void sf_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c9_chartstep_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initSimStructsc9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber);
static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData);
static uint8_T c9_emlrt_marshallIn(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c9_PC_next, const char_T *c9_identifier);
static uint8_T c9_b_emlrt_marshallIn(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static real_T c9_c_emlrt_marshallIn(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_e_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static void c9_info_helper(c9_ResolvedFunctionInfo c9_info[16]);
static const mxArray *c9_f_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static int32_T c9_d_emlrt_marshallIn(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_g_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static uint8_T c9_e_emlrt_marshallIn(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c9_b_is_active_c9_hdlcodercpu_eml, const char_T
  *c9_identifier);
static uint8_T c9_f_emlrt_marshallIn(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void init_dsm_address_info(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  chartInstance->c9_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c9_is_active_c9_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c9_c_eml_mx, sf_mex_call_debug("numerictype", 1U, 10U, 15,
    "WordLength", 6, 8.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c9_b_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 8.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c9_eml_mx, sf_mex_call_debug("fimath", 1U, 38U, 15, "RoundMode",
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

static void initialize_params_c9_hdlcodercpu_eml
  (SFc9_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void enable_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c9_update_debugger_state_c9_hdlcodercpu_eml
  (SFc9_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c9_hdlcodercpu_eml
  (SFc9_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c9_st;
  const mxArray *c9_y = NULL;
  uint8_T c9_hoistedGlobal;
  uint8_T c9_u;
  const mxArray *c9_b_y = NULL;
  uint8_T c9_b_u;
  const mxArray *c9_c_y = NULL;
  uint8_T c9_b_hoistedGlobal;
  uint8_T c9_c_u;
  const mxArray *c9_d_y = NULL;
  uint8_T *c9_PC_next;
  c9_PC_next = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c9_st = NULL;
  c9_st = NULL;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_createcellarray(2));
  c9_hoistedGlobal = *c9_PC_next;
  c9_u = c9_hoistedGlobal;
  c9_b_y = NULL;
  c9_b_u = c9_u;
  c9_c_y = NULL;
  sf_mex_assign(&c9_c_y, sf_mex_create("y", &c9_b_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c9_b_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c9_eml_mx), 15, "numerictype", 14, sf_mex_dup(c9_b_eml_mx), 15,
    "simulinkarray", 14, c9_c_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c9_y, 0, c9_b_y);
  c9_b_hoistedGlobal = chartInstance->c9_is_active_c9_hdlcodercpu_eml;
  c9_c_u = c9_b_hoistedGlobal;
  c9_d_y = NULL;
  sf_mex_assign(&c9_d_y, sf_mex_create("y", &c9_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c9_y, 1, c9_d_y);
  sf_mex_assign(&c9_st, c9_y);
  return c9_st;
}

static void set_sim_state_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct *
  chartInstance, const mxArray *c9_st)
{
  const mxArray *c9_u;
  uint8_T *c9_PC_next;
  c9_PC_next = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c9_doneDoubleBufferReInit = TRUE;
  c9_u = sf_mex_dup(c9_st);
  *c9_PC_next = c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c9_u, 0)), "PC_next");
  chartInstance->c9_is_active_c9_hdlcodercpu_eml = c9_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 1)),
     "is_active_c9_hdlcodercpu_eml");
  sf_mex_destroy(&c9_u);
  c9_update_debugger_state_c9_hdlcodercpu_eml(chartInstance);
  sf_mex_destroy(&c9_st);
}

static void finalize_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&c9_eml_mx);
  sf_mex_destroy(&c9_b_eml_mx);
  sf_mex_destroy(&c9_c_eml_mx);
}

static void sf_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  int8_T *c9_jmp_offset;
  uint8_T *c9_PC_current;
  uint8_T *c9_PC_next;
  c9_PC_next = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c9_PC_current = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c9_jmp_offset = (int8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c9_jmp_offset, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c9_PC_current, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c9_PC_next, 2U);
  chartInstance->c9_sfEvent = CALL_EVENT;
  c9_chartstep_c9_hdlcodercpu_eml(chartInstance);
  sf_debug_check_for_state_inconsistency(_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c9_chartstep_c9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  int8_T c9_hoistedGlobal;
  uint8_T c9_b_hoistedGlobal;
  int8_T c9_jmp_offset;
  uint8_T c9_PC_current;
  uint32_T c9_debug_family_var_map[6];
  const mxArray *c9_hdl_fm = NULL;
  real_T c9_nargin = 2.0;
  real_T c9_nargout = 1.0;
  uint8_T c9_PC_next;
  int8_T c9_a0;
  uint8_T c9_b0;
  const mxArray *c9_m0 = NULL;
  const mxArray *c9_m1 = NULL;
  int8_T c9_a;
  uint8_T c9_b;
  const mxArray *c9_m2 = NULL;
  const mxArray *c9_m3 = NULL;
  const mxArray *c9_m4 = NULL;
  const mxArray *c9_m5 = NULL;
  const mxArray *c9_m6 = NULL;
  const mxArray *c9_m7 = NULL;
  const mxArray *c9_m8 = NULL;
  const mxArray *c9_m9 = NULL;
  const mxArray *c9_m10 = NULL;
  const mxArray *c9_m11 = NULL;
  const mxArray *c9_m12 = NULL;
  const mxArray *c9_m13 = NULL;
  const mxArray *c9_m14 = NULL;
  const mxArray *c9_m15 = NULL;
  const mxArray *c9_m16 = NULL;
  const mxArray *c9_m17 = NULL;
  int16_T c9_i0;
  int16_T c9_i1;
  int16_T c9_i2;
  int16_T c9_c;
  const mxArray *c9_m18 = NULL;
  const mxArray *c9_m19 = NULL;
  const mxArray *c9_m20 = NULL;
  const mxArray *c9_m21 = NULL;
  const mxArray *c9_m22 = NULL;
  const mxArray *c9_m23 = NULL;
  int16_T c9_varargin_1;
  int16_T c9_b_varargin_1;
  const mxArray *c9_m24 = NULL;
  const mxArray *c9_m25 = NULL;
  const mxArray *c9_m26 = NULL;
  const mxArray *c9_m27 = NULL;
  int16_T c9_var1;
  const mxArray *c9_m28 = NULL;
  const mxArray *c9_m29 = NULL;
  const mxArray *c9_m30 = NULL;
  const mxArray *c9_m31 = NULL;
  const mxArray *c9_m32 = NULL;
  const mxArray *c9_m33 = NULL;
  const mxArray *c9_m34 = NULL;
  uint8_T *c9_b_PC_next;
  int8_T *c9_b_jmp_offset;
  uint8_T *c9_b_PC_current;
  c9_b_PC_next = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c9_b_PC_current = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c9_b_jmp_offset = (int8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
  c9_hoistedGlobal = *c9_b_jmp_offset;
  c9_b_hoistedGlobal = *c9_b_PC_current;
  c9_jmp_offset = c9_hoistedGlobal;
  c9_PC_current = c9_b_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c9_debug_family_names,
    c9_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c9_hdl_fm, 0U, c9_e_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c9_nargin, 1U, c9_d_sf_marshallOut,
    c9_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c9_nargout, 2U, c9_d_sf_marshallOut,
    c9_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c9_jmp_offset, 3U, c9_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c9_PC_current, 4U, c9_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c9_PC_next, 5U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 5);
  c9_hdl_fm = c9_eml_mx;
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 12);
  c9_a0 = c9_jmp_offset;
  c9_b0 = c9_PC_current;
  sf_mex_destroy(&c9_m0);
  sf_mex_destroy(&c9_m1);
  c9_a = c9_a0;
  c9_b = c9_b0;
  sf_mex_destroy(&c9_m2);
  sf_mex_destroy(&c9_m3);
  sf_mex_destroy(&c9_m4);
  sf_mex_destroy(&c9_m5);
  sf_mex_destroy(&c9_m6);
  sf_mex_destroy(&c9_m7);
  sf_mex_destroy(&c9_m8);
  sf_mex_destroy(&c9_m9);
  sf_mex_destroy(&c9_m10);
  sf_mex_destroy(&c9_m11);
  sf_mex_destroy(&c9_m12);
  sf_mex_destroy(&c9_m13);
  sf_mex_destroy(&c9_m14);
  sf_mex_destroy(&c9_m15);
  sf_mex_destroy(&c9_m16);
  sf_mex_destroy(&c9_m17);
  c9_i0 = (int16_T)c9_a;
  c9_i1 = (int16_T)c9_b;
  c9_i2 = (int16_T)(((int16_T)(c9_i0 & 256) != 0 ? (int16_T)(c9_i0 | -256) :
                     (int16_T)(c9_i0 & 255)) + ((int16_T)(c9_i1 & 256) != 0 ?
    (int16_T)(c9_i1 | -256) : (int16_T)(c9_i1 & 255)));
  c9_c = (int16_T)(c9_i2 & 256) != 0 ? (int16_T)(c9_i2 | -256) : (int16_T)(c9_i2
    & 255);
  sf_mex_destroy(&c9_m18);
  sf_mex_destroy(&c9_m19);
  sf_mex_destroy(&c9_m20);
  sf_mex_destroy(&c9_m21);
  sf_mex_destroy(&c9_m22);
  sf_mex_destroy(&c9_m23);
  c9_varargin_1 = c9_c;
  c9_b_varargin_1 = c9_varargin_1;
  sf_mex_destroy(&c9_m24);
  sf_mex_destroy(&c9_m25);
  sf_mex_destroy(&c9_m26);
  sf_mex_destroy(&c9_m27);
  c9_var1 = c9_b_varargin_1;
  c9_PC_next = (uint8_T)c9_var1;
  sf_mex_destroy(&c9_m28);
  sf_mex_destroy(&c9_m29);
  sf_mex_destroy(&c9_m30);
  sf_mex_destroy(&c9_m31);
  sf_mex_destroy(&c9_m32);
  sf_mex_destroy(&c9_m33);
  sf_mex_destroy(&c9_m34);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, -12);
  sf_debug_symbol_scope_pop();
  *c9_b_PC_next = c9_PC_next;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c9_sfEvent);
}

static void initSimStructsc9_hdlcodercpu_eml(SFc9_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber)
{
}

static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData)
{
  const mxArray *c9_mxArrayOutData;
  uint8_T c9_u;
  const mxArray *c9_y = NULL;
  uint8_T c9_b_u;
  const mxArray *c9_b_y = NULL;
  SFc9_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc9_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c9_u = *(uint8_T *)c9_inData;
    c9_y = NULL;
    c9_b_u = c9_u;
    c9_b_y = NULL;
    sf_mex_assign(&c9_b_y, sf_mex_create("y", &c9_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c9_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c9_eml_mx), 15, "numerictype", 14, sf_mex_dup(c9_b_eml_mx), 15,
      "simulinkarray", 14, c9_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c9_mxArrayOutData, c9_y);
  } else {
    sf_mex_assign(&c9_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c9_mxArrayOutData;
}

static uint8_T c9_emlrt_marshallIn(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c9_PC_next, const char_T *c9_identifier)
{
  uint8_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_PC_next), &c9_thisId);
  sf_mex_destroy(&c9_PC_next);
  return c9_y;
}

static uint8_T c9_b_emlrt_marshallIn(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  uint8_T c9_y;
  const mxArray *c9_mxFi = NULL;
  const mxArray *c9_mxInt = NULL;
  uint8_T c9_u0;
  sf_mex_check_fi(c9_parentId, c9_u, 0, 0U, 0, c9_eml_mx, c9_b_eml_mx);
  sf_mex_assign(&c9_mxFi, sf_mex_dup(c9_u));
  sf_mex_assign(&c9_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c9_mxFi)));
  sf_mex_import(c9_parentId, sf_mex_dup(c9_mxInt), &c9_u0, 1, 3, 0U, 0, 0U, 0);
  sf_mex_destroy(&c9_mxFi);
  sf_mex_destroy(&c9_mxInt);
  c9_y = c9_u0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_PC_next;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  uint8_T c9_y;
  SFc9_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc9_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  if (sf_debug_check_fi_license()) {
    c9_PC_next = sf_mex_dup(c9_mxArrayInData);
    c9_identifier = c9_varName;
    c9_thisId.fIdentifier = c9_identifier;
    c9_thisId.fParent = NULL;
    c9_y = c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_PC_next),
      &c9_thisId);
    sf_mex_destroy(&c9_PC_next);
    *(uint8_T *)c9_outData = c9_y;
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData;
  uint8_T c9_u;
  const mxArray *c9_y = NULL;
  uint8_T c9_b_u;
  const mxArray *c9_b_y = NULL;
  SFc9_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc9_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c9_u = *(uint8_T *)c9_inData;
    c9_y = NULL;
    c9_b_u = c9_u;
    c9_b_y = NULL;
    sf_mex_assign(&c9_b_y, sf_mex_create("y", &c9_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c9_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c9_eml_mx), 15, "numerictype", 14, sf_mex_dup(c9_b_eml_mx), 15,
      "simulinkarray", 14, c9_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c9_mxArrayOutData, c9_y);
  } else {
    sf_mex_assign(&c9_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c9_mxArrayOutData;
}

static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData;
  int8_T c9_u;
  const mxArray *c9_y = NULL;
  int8_T c9_b_u;
  const mxArray *c9_b_y = NULL;
  SFc9_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc9_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c9_u = *(int8_T *)c9_inData;
    c9_y = NULL;
    c9_b_u = c9_u;
    c9_b_y = NULL;
    sf_mex_assign(&c9_b_y, sf_mex_create("y", &c9_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c9_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c9_eml_mx), 15, "numerictype", 14, sf_mex_dup(c9_c_eml_mx), 15,
      "simulinkarray", 14, c9_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c9_mxArrayOutData, c9_y);
  } else {
    sf_mex_assign(&c9_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c9_mxArrayOutData;
}

static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  real_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc9_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(real_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c9_mxArrayOutData, c9_y);
  return c9_mxArrayOutData;
}

static real_T c9_c_emlrt_marshallIn(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  real_T c9_y;
  real_T c9_d0;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_d0, 1, 0, 0U, 0, 0U, 0);
  c9_y = c9_d0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_nargout;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y;
  SFc9_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc9_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c9_nargout = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_nargout), &c9_thisId);
  sf_mex_destroy(&c9_nargout);
  *(real_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_e_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  const mxArray *c9_u;
  const mxArray *c9_y = NULL;
  SFc9_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc9_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = sf_mex_dup(*(const mxArray **)c9_inData);
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_duplicatearraysafe(&c9_u));
  sf_mex_destroy(&c9_u);
  sf_mex_assign(&c9_mxArrayOutData, c9_y);
  return c9_mxArrayOutData;
}

const mxArray *sf_c9_hdlcodercpu_eml_get_eml_resolved_functions_info(void)
{
  const mxArray *c9_nameCaptureInfo;
  c9_ResolvedFunctionInfo c9_info[16];
  const mxArray *c9_m35 = NULL;
  int32_T c9_i3;
  c9_ResolvedFunctionInfo *c9_r0;
  c9_nameCaptureInfo = NULL;
  c9_nameCaptureInfo = NULL;
  c9_info_helper(c9_info);
  sf_mex_assign(&c9_m35, sf_mex_createstruct("nameCaptureInfo", 1, 16));
  for (c9_i3 = 0; c9_i3 < 16; c9_i3++) {
    c9_r0 = &c9_info[c9_i3];
    sf_mex_addfield(c9_m35, sf_mex_create("nameCaptureInfo", c9_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->context)), "context", "nameCaptureInfo",
                    c9_i3);
    sf_mex_addfield(c9_m35, sf_mex_create("nameCaptureInfo", c9_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c9_r0->name)), "name", "nameCaptureInfo", c9_i3);
    sf_mex_addfield(c9_m35, sf_mex_create("nameCaptureInfo", c9_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c9_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c9_i3);
    sf_mex_addfield(c9_m35, sf_mex_create("nameCaptureInfo", c9_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->resolved)), "resolved", "nameCaptureInfo",
                    c9_i3);
    sf_mex_addfield(c9_m35, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c9_i3);
    sf_mex_addfield(c9_m35, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c9_i3);
    sf_mex_addfield(c9_m35, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c9_i3);
    sf_mex_addfield(c9_m35, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c9_i3);
  }

  sf_mex_assign(&c9_nameCaptureInfo, c9_m35);
  return c9_nameCaptureInfo;
}

static void c9_info_helper(c9_ResolvedFunctionInfo c9_info[16])
{
  c9_info[0].context = "";
  c9_info[0].name = "fimath";
  c9_info[0].dominantType = "char";
  c9_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m";
  c9_info[0].fileTimeLo = 275520000U;
  c9_info[0].fileTimeHi = 30114375U;
  c9_info[0].mFileTimeLo = 0U;
  c9_info[0].mFileTimeHi = 0U;
  c9_info[1].context = "";
  c9_info[1].name = "plus";
  c9_info[1].dominantType = "embedded.fi";
  c9_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c9_info[1].fileTimeLo = 995520000U;
  c9_info[1].fileTimeHi = 30114375U;
  c9_info[1].mFileTimeLo = 0U;
  c9_info[1].mFileTimeHi = 0U;
  c9_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c9_info[2].name = "eml_scalexp_compatible";
  c9_info[2].dominantType = "embedded.fi";
  c9_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c9_info[2].fileTimeLo = 3244844544U;
  c9_info[2].fileTimeHi = 30108086U;
  c9_info[2].mFileTimeLo = 0U;
  c9_info[2].mFileTimeHi = 0U;
  c9_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c9_info[3].name = "isfi";
  c9_info[3].dominantType = "embedded.fi";
  c9_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c9_info[3].fileTimeLo = 335520000U;
  c9_info[3].fileTimeHi = 30114375U;
  c9_info[3].mFileTimeLo = 0U;
  c9_info[3].mFileTimeHi = 0U;
  c9_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c9_info[4].name = "isnumerictype";
  c9_info[4].dominantType = "embedded.numerictype";
  c9_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m";
  c9_info[4].fileTimeLo = 355520000U;
  c9_info[4].fileTimeHi = 30114375U;
  c9_info[4].mFileTimeLo = 0U;
  c9_info[4].mFileTimeHi = 0U;
  c9_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c9_info[5].name = "isscaledtype";
  c9_info[5].dominantType = "embedded.fi";
  c9_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m";
  c9_info[5].fileTimeLo = 895520000U;
  c9_info[5].fileTimeHi = 30114375U;
  c9_info[5].mFileTimeLo = 0U;
  c9_info[5].mFileTimeHi = 0U;
  c9_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isscaledtype.m";
  c9_info[6].name = "isfixed";
  c9_info[6].dominantType = "embedded.fi";
  c9_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  c9_info[6].fileTimeLo = 875520000U;
  c9_info[6].fileTimeHi = 30114375U;
  c9_info[6].mFileTimeLo = 0U;
  c9_info[6].mFileTimeHi = 0U;
  c9_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  c9_info[7].name = "get";
  c9_info[7].dominantType = "embedded.numerictype";
  c9_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m";
  c9_info[7].fileTimeLo = 4170487296U;
  c9_info[7].fileTimeHi = 30114374U;
  c9_info[7].mFileTimeLo = 0U;
  c9_info[7].mFileTimeHi = 0U;
  c9_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c9_info[8].name = "eml_checkfimathforbinaryops";
  c9_info[8].dominantType = "embedded.fi";
  c9_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_checkfimathforbinaryops.m";
  c9_info[8].fileTimeLo = 615520000U;
  c9_info[8].fileTimeHi = 30114375U;
  c9_info[8].mFileTimeLo = 0U;
  c9_info[8].mFileTimeHi = 0U;
  c9_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c9_info[9].name = "get";
  c9_info[9].dominantType = "embedded.fimath";
  c9_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fimath/get.m";
  c9_info[9].fileTimeLo = 4190487296U;
  c9_info[9].fileTimeHi = 30114374U;
  c9_info[9].mFileTimeLo = 0U;
  c9_info[9].mFileTimeHi = 0U;
  c9_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/plus.m";
  c9_info[10].name = "strcmpi";
  c9_info[10].dominantType = "char";
  c9_info[10].resolved = "[IXMB]$matlabroot$/toolbox/matlab/strfun/strcmpi";
  c9_info[10].fileTimeLo = 0U;
  c9_info[10].fileTimeHi = 0U;
  c9_info[10].mFileTimeLo = 0U;
  c9_info[10].mFileTimeHi = 0U;
  c9_info[11].context = "";
  c9_info[11].name = "fi_impl";
  c9_info[11].dominantType = "";
  c9_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m";
  c9_info[11].fileTimeLo = 275520000U;
  c9_info[11].fileTimeHi = 30114375U;
  c9_info[11].mFileTimeLo = 0U;
  c9_info[11].mFileTimeHi = 0U;
  c9_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c9_info[12].name = "isfloat";
  c9_info[12].dominantType = "embedded.fi";
  c9_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfloat.m";
  c9_info[12].fileTimeLo = 875520000U;
  c9_info[12].fileTimeHi = 30114375U;
  c9_info[12].mFileTimeLo = 0U;
  c9_info[12].mFileTimeHi = 0U;
  c9_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput";
  c9_info[13].name = "numerictype";
  c9_info[13].dominantType = "embedded.fi";
  c9_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/numerictype.m";
  c9_info[13].fileTimeLo = 995520000U;
  c9_info[13].fileTimeHi = 30114375U;
  c9_info[13].mFileTimeLo = 0U;
  c9_info[13].mFileTimeHi = 0U;
  c9_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!local_createConstDataFromInput";
  c9_info[14].name = "fimath";
  c9_info[14].dominantType = "embedded.fi";
  c9_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/fimath.m";
  c9_info[14].fileTimeLo = 775520000U;
  c9_info[14].fileTimeHi = 30114375U;
  c9_info[14].mFileTimeLo = 0U;
  c9_info[14].mFileTimeHi = 0U;
  c9_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c9_info[15].name = "eml_fi_checkforntype";
  c9_info[15].dominantType = "embedded.fi";
  c9_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforntype.m";
  c9_info[15].fileTimeLo = 255520000U;
  c9_info[15].fileTimeHi = 30114375U;
  c9_info[15].mFileTimeLo = 0U;
  c9_info[15].mFileTimeHi = 0U;
}

static const mxArray *c9_f_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc9_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(int32_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c9_mxArrayOutData, c9_y);
  return c9_mxArrayOutData;
}

static int32_T c9_d_emlrt_marshallIn(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  int32_T c9_y;
  int32_T c9_i4;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_i4, 1, 6, 0U, 0, 0U, 0);
  c9_y = c9_i4;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_b_sfEvent;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  int32_T c9_y;
  SFc9_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc9_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c9_b_sfEvent = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_b_sfEvent),
    &c9_thisId);
  sf_mex_destroy(&c9_b_sfEvent);
  *(int32_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_g_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData;
  int8_T c9_u;
  const mxArray *c9_y = NULL;
  int8_T c9_b_u;
  const mxArray *c9_b_y = NULL;
  SFc9_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc9_hdlcodercpu_emlInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_mxArrayOutData = NULL;
  if (sf_debug_check_fi_license()) {
    c9_u = *(int8_T *)c9_inData;
    c9_y = NULL;
    c9_b_u = c9_u;
    c9_b_y = NULL;
    sf_mex_assign(&c9_b_y, sf_mex_create("y", &c9_b_u, 2, 0U, 0U, 0U, 0));
    sf_mex_assign(&c9_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c9_eml_mx), 15, "numerictype", 14, sf_mex_dup(c9_c_eml_mx), 15,
      "simulinkarray", 14, c9_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c9_mxArrayOutData, c9_y);
  } else {
    sf_mex_assign(&c9_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
  }

  return c9_mxArrayOutData;
}

static uint8_T c9_e_emlrt_marshallIn(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c9_b_is_active_c9_hdlcodercpu_eml, const char_T
  *c9_identifier)
{
  uint8_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c9_b_is_active_c9_hdlcodercpu_eml), &c9_thisId);
  sf_mex_destroy(&c9_b_is_active_c9_hdlcodercpu_eml);
  return c9_y;
}

static uint8_T c9_f_emlrt_marshallIn(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  uint8_T c9_y;
  uint8_T c9_u1;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_u1, 1, 3, 0U, 0, 0U, 0);
  c9_y = c9_u1;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void init_dsm_address_info(SFc9_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c9_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(422619985U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2227581954U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2823400178U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2751397512U);
}

mxArray *sf_c9_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(1667724048U);
    pr[1] = (double)(586704730U);
    pr[2] = (double)(4023761296U);
    pr[3] = (double)(1764298891U);
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

static const mxArray *sf_get_sim_state_info_c9_hdlcodercpu_eml(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[6],T\"PC_next\",},{M[8],M[0],T\"is_active_c9_hdlcodercpu_eml\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c9_hdlcodercpu_eml_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc9_hdlcodercpu_emlInstanceStruct *chartInstance;
    chartInstance = (SFc9_hdlcodercpu_emlInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_hdlcodercpu_emlMachineNumber_,
           9,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"jmp_offset");
          _SFD_SET_DATA_PROPS(1,1,1,0,"PC_current");
          _SFD_SET_DATA_PROPS(2,2,0,1,"PC_next");
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
        _SFD_CV_INIT_EML(0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,390);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_INT8,0,NULL,1,1,8,0,1,0,0,
          (MexFcnForType)c9_g_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_UINT8,0,NULL,1,0,8,0,1,0,0,
          (MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_UINT8,0,NULL,1,0,8,0,1,0,0,
          (MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)c9_sf_marshallIn);

        {
          int8_T *c9_jmp_offset;
          uint8_T *c9_PC_current;
          uint8_T *c9_PC_next;
          c9_PC_next = (uint8_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c9_PC_current = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c9_jmp_offset = (int8_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c9_jmp_offset);
          _SFD_SET_DATA_VALUE_PTR(1U, c9_PC_current);
          _SFD_SET_DATA_VALUE_PTR(2U, c9_PC_next);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_hdlcodercpu_emlMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c9_hdlcodercpu_eml(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc9_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c9_hdlcodercpu_eml((SFc9_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
  initialize_c9_hdlcodercpu_eml((SFc9_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c9_hdlcodercpu_eml(void *chartInstanceVar)
{
  enable_c9_hdlcodercpu_eml((SFc9_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c9_hdlcodercpu_eml(void *chartInstanceVar)
{
  disable_c9_hdlcodercpu_eml((SFc9_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c9_hdlcodercpu_eml(void *chartInstanceVar)
{
  sf_c9_hdlcodercpu_eml((SFc9_hdlcodercpu_emlInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c9_hdlcodercpu_eml(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c9_hdlcodercpu_eml
    ((SFc9_hdlcodercpu_emlInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_hdlcodercpu_eml();/* state var info */
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

extern void sf_internal_set_sim_state_c9_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c9_hdlcodercpu_eml((SFc9_hdlcodercpu_emlInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c9_hdlcodercpu_eml(SimStruct* S)
{
  return sf_internal_get_sim_state_c9_hdlcodercpu_eml(S);
}

static void sf_opaque_set_sim_state_c9_hdlcodercpu_eml(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c9_hdlcodercpu_eml(S, st);
}

static void sf_opaque_terminate_c9_hdlcodercpu_eml(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc9_hdlcodercpu_emlInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c9_hdlcodercpu_eml((SFc9_hdlcodercpu_emlInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc9_hdlcodercpu_eml((SFc9_hdlcodercpu_emlInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c9_hdlcodercpu_eml(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c9_hdlcodercpu_eml((SFc9_hdlcodercpu_emlInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c9_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"hdlcodercpu_eml","hdlcodercpu_eml",9);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml","hdlcodercpu_eml",9,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml",
      "hdlcodercpu_eml",9,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",
        9,2);
      sf_mark_chart_reusable_outputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",9,1);
    }

    sf_set_rtw_dwork_info(S,"hdlcodercpu_eml","hdlcodercpu_eml",9);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2751929267U));
  ssSetChecksum1(S,(105192325U));
  ssSetChecksum2(S,(163756755U));
  ssSetChecksum3(S,(843920986U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c9_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "hdlcodercpu_eml", "hdlcodercpu_eml",9);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c9_hdlcodercpu_eml(SimStruct *S)
{
  SFc9_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc9_hdlcodercpu_emlInstanceStruct *)malloc(sizeof
    (SFc9_hdlcodercpu_emlInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc9_hdlcodercpu_emlInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c9_hdlcodercpu_eml;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c9_hdlcodercpu_eml;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c9_hdlcodercpu_eml;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c9_hdlcodercpu_eml;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c9_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c9_hdlcodercpu_eml;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c9_hdlcodercpu_eml;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c9_hdlcodercpu_eml;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c9_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlStart = mdlStart_c9_hdlcodercpu_eml;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c9_hdlcodercpu_eml;
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

void c9_hdlcodercpu_eml_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c9_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c9_hdlcodercpu_eml(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c9_hdlcodercpu_eml(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c9_hdlcodercpu_eml_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
