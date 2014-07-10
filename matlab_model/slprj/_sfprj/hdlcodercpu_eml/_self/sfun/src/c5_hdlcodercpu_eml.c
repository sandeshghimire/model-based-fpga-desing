/* Include files */

#include "blascompat32.h"
#include "hdlcodercpu_eml_sfun.h"
#include "c5_hdlcodercpu_eml.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "hdlcodercpu_eml_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
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
static void sf_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void c5_chartstep_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance);
static void initSimStructsc5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber);
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
static void c5_info_helper(c5_ResolvedFunctionInfo c5_info[16]);
static void c5_fi_helper(SFc5_hdlcodercpu_emlInstanceStruct *chartInstance);
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
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c5_data_not_empty = FALSE;
  chartInstance->c5_is_active_c5_hdlcodercpu_eml = 0U;
  sf_mex_assign(&c5_c_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 1.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c5_b_eml_mx, sf_mex_call_debug("numerictype", 1U, 14U, 15,
    "SignednessBool", 3, FALSE, 15, "Signedness", 15, "Unsigned", 15,
    "WordLength", 6, 12.0, 15, "FractionLength", 6, 0.0, 15, "BinaryPoint", 6,
    0.0, 15, "Slope", 6, 1.0, 15, "FixedExponent", 6, 0.0));
  sf_mex_assign(&c5_eml_mx, sf_mex_call_debug("fimath", 1U, 38U, 15, "RoundMode",
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

static void initialize_params_c5_hdlcodercpu_eml
  (SFc5_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void enable_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c5_update_debugger_state_c5_hdlcodercpu_eml
  (SFc5_hdlcodercpu_emlInstanceStruct *chartInstance)
{
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
  sf_mex_assign(&c5_y, sf_mex_createcellarray(3));
  c5_hoistedGlobal = *c5_instr_out;
  c5_u = c5_hoistedGlobal;
  c5_b_y = NULL;
  c5_b_u = c5_u;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_u, 5, 0U, 0U, 0U, 0));
  sf_mex_assign(&c5_b_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
    sf_mex_dup(c5_eml_mx), 15, "numerictype", 14, sf_mex_dup(c5_b_eml_mx), 15,
    "simulinkarray", 14, c5_c_y, 15, "fimathislocal", 3, TRUE));
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_d_y = NULL;
  if (!chartInstance->c5_data_not_empty) {
    sf_mex_assign(&c5_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    for (c5_i0 = 0; c5_i0 < 256; c5_i0++) {
      c5_c_u[c5_i0] = chartInstance->c5_data[c5_i0];
    }

    c5_e_y = NULL;
    sf_mex_assign(&c5_e_y, sf_mex_create("y", c5_c_u, 5, 0U, 1U, 0U, 2, 1, 256));
    sf_mex_assign(&c5_d_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c5_eml_mx), 15, "numerictype", 14, sf_mex_dup(c5_b_eml_mx), 15,
      "simulinkarray", 14, c5_e_y, 15, "fimathislocal", 3, TRUE));
  }

  sf_mex_setcell(c5_y, 1, c5_d_y);
  c5_b_hoistedGlobal = chartInstance->c5_is_active_c5_hdlcodercpu_eml;
  c5_d_u = c5_b_hoistedGlobal;
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_d_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c5_y, 2, c5_f_y);
  sf_mex_assign(&c5_st, c5_y);
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
  chartInstance->c5_doneDoubleBufferReInit = TRUE;
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
  sf_mex_destroy(&c5_eml_mx);
  sf_mex_destroy(&c5_b_eml_mx);
  sf_mex_destroy(&c5_c_eml_mx);
}

static void sf_c5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
  uint8_T *c5_addr;
  uint8_T *c5_read;
  uint16_T *c5_instr_out;
  c5_instr_out = (uint16_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c5_read = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c5_addr = (uint8_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*c5_addr, 0U);
  _SFD_DATA_RANGE_CHECK((real_T)*c5_read, 1U);
  _SFD_DATA_RANGE_CHECK((real_T)*c5_instr_out, 2U);
  chartInstance->c5_sfEvent = CALL_EVENT;
  c5_chartstep_c5_hdlcodercpu_eml(chartInstance);
  sf_debug_check_for_state_inconsistency(_hdlcodercpu_emlMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
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
  int32_T c5_i2;
  const mxArray *c5_m0 = NULL;
  const mxArray *c5_m1 = NULL;
  const mxArray *c5_m2 = NULL;
  const mxArray *c5_m3 = NULL;
  const mxArray *c5_m4 = NULL;
  const mxArray *c5_m5 = NULL;
  const mxArray *c5_m6 = NULL;
  const mxArray *c5_m7 = NULL;
  const mxArray *c5_m8 = NULL;
  const mxArray *c5_m9 = NULL;
  const mxArray *c5_m10 = NULL;
  const mxArray *c5_m11 = NULL;
  const mxArray *c5_m12 = NULL;
  const mxArray *c5_m13 = NULL;
  const mxArray *c5_m14 = NULL;
  const mxArray *c5_m15 = NULL;
  const mxArray *c5_m16 = NULL;
  const mxArray *c5_m17 = NULL;
  const mxArray *c5_m18 = NULL;
  const mxArray *c5_m19 = NULL;
  const mxArray *c5_m20 = NULL;
  const mxArray *c5_m21 = NULL;
  const mxArray *c5_m22 = NULL;
  const mxArray *c5_m23 = NULL;
  const mxArray *c5_m24 = NULL;
  const mxArray *c5_m25 = NULL;
  const mxArray *c5_m26 = NULL;
  const mxArray *c5_m27 = NULL;
  const mxArray *c5_m28 = NULL;
  const mxArray *c5_m29 = NULL;
  const mxArray *c5_m30 = NULL;
  const mxArray *c5_m31 = NULL;
  const mxArray *c5_m32 = NULL;
  const mxArray *c5_m33 = NULL;
  const mxArray *c5_m34 = NULL;
  const mxArray *c5_m35 = NULL;
  const mxArray *c5_m36 = NULL;
  const mxArray *c5_m37 = NULL;
  const mxArray *c5_m38 = NULL;
  const mxArray *c5_m39 = NULL;
  const mxArray *c5_m40 = NULL;
  const mxArray *c5_m41 = NULL;
  const mxArray *c5_m42 = NULL;
  const mxArray *c5_m43 = NULL;
  const mxArray *c5_m44 = NULL;
  const mxArray *c5_m45 = NULL;
  const mxArray *c5_m46 = NULL;
  const mxArray *c5_m47 = NULL;
  const mxArray *c5_m48 = NULL;
  const mxArray *c5_m49 = NULL;
  const mxArray *c5_m50 = NULL;
  const mxArray *c5_m51 = NULL;
  const mxArray *c5_m52 = NULL;
  const mxArray *c5_m53 = NULL;
  const mxArray *c5_m54 = NULL;
  const mxArray *c5_m55 = NULL;
  const mxArray *c5_m56 = NULL;
  const mxArray *c5_m57 = NULL;
  const mxArray *c5_m58 = NULL;
  const mxArray *c5_m59 = NULL;
  const mxArray *c5_m60 = NULL;
  const mxArray *c5_m61 = NULL;
  const mxArray *c5_m62 = NULL;
  const mxArray *c5_m63 = NULL;
  const mxArray *c5_m64 = NULL;
  const mxArray *c5_m65 = NULL;
  const mxArray *c5_m66 = NULL;
  const mxArray *c5_m67 = NULL;
  const mxArray *c5_m68 = NULL;
  const mxArray *c5_m69 = NULL;
  const mxArray *c5_m70 = NULL;
  const mxArray *c5_m71 = NULL;
  const mxArray *c5_m72 = NULL;
  const mxArray *c5_m73 = NULL;
  const mxArray *c5_m74 = NULL;
  const mxArray *c5_m75 = NULL;
  const mxArray *c5_m76 = NULL;
  const mxArray *c5_m77 = NULL;
  const mxArray *c5_m78 = NULL;
  const mxArray *c5_m79 = NULL;
  const mxArray *c5_m80 = NULL;
  const mxArray *c5_m81 = NULL;
  const mxArray *c5_m82 = NULL;
  const mxArray *c5_m83 = NULL;
  const mxArray *c5_m84 = NULL;
  const mxArray *c5_m85 = NULL;
  const mxArray *c5_m86 = NULL;
  const mxArray *c5_m87 = NULL;
  const mxArray *c5_m88 = NULL;
  const mxArray *c5_m89 = NULL;
  const mxArray *c5_m90 = NULL;
  const mxArray *c5_m91 = NULL;
  const mxArray *c5_m92 = NULL;
  const mxArray *c5_m93 = NULL;
  const mxArray *c5_m94 = NULL;
  const mxArray *c5_m95 = NULL;
  const mxArray *c5_m96 = NULL;
  const mxArray *c5_m97 = NULL;
  const mxArray *c5_m98 = NULL;
  const mxArray *c5_m99 = NULL;
  const mxArray *c5_m100 = NULL;
  const mxArray *c5_m101 = NULL;
  const mxArray *c5_m102 = NULL;
  const mxArray *c5_m103 = NULL;
  const mxArray *c5_m104 = NULL;
  const mxArray *c5_m105 = NULL;
  const mxArray *c5_m106 = NULL;
  const mxArray *c5_m107 = NULL;
  const mxArray *c5_m108 = NULL;
  const mxArray *c5_m109 = NULL;
  const mxArray *c5_m110 = NULL;
  const mxArray *c5_m111 = NULL;
  const mxArray *c5_m112 = NULL;
  const mxArray *c5_m113 = NULL;
  const mxArray *c5_m114 = NULL;
  const mxArray *c5_m115 = NULL;
  const mxArray *c5_m116 = NULL;
  const mxArray *c5_m117 = NULL;
  const mxArray *c5_m118 = NULL;
  const mxArray *c5_m119 = NULL;
  const mxArray *c5_m120 = NULL;
  const mxArray *c5_m121 = NULL;
  const mxArray *c5_m122 = NULL;
  const mxArray *c5_m123 = NULL;
  const mxArray *c5_m124 = NULL;
  const mxArray *c5_m125 = NULL;
  const mxArray *c5_m126 = NULL;
  const mxArray *c5_m127 = NULL;
  const mxArray *c5_m128 = NULL;
  const mxArray *c5_m129 = NULL;
  const mxArray *c5_m130 = NULL;
  const mxArray *c5_m131 = NULL;
  const mxArray *c5_m132 = NULL;
  const mxArray *c5_m133 = NULL;
  const mxArray *c5_m134 = NULL;
  const mxArray *c5_m135 = NULL;
  const mxArray *c5_m136 = NULL;
  const mxArray *c5_m137 = NULL;
  const mxArray *c5_m138 = NULL;
  const mxArray *c5_m139 = NULL;
  const mxArray *c5_m140 = NULL;
  const mxArray *c5_m141 = NULL;
  const mxArray *c5_m142 = NULL;
  const mxArray *c5_m143 = NULL;
  const mxArray *c5_m144 = NULL;
  const mxArray *c5_m145 = NULL;
  const mxArray *c5_m146 = NULL;
  const mxArray *c5_m147 = NULL;
  const mxArray *c5_m148 = NULL;
  const mxArray *c5_m149 = NULL;
  const mxArray *c5_m150 = NULL;
  const mxArray *c5_m151 = NULL;
  const mxArray *c5_m152 = NULL;
  const mxArray *c5_m153 = NULL;
  const mxArray *c5_m154 = NULL;
  const mxArray *c5_m155 = NULL;
  const mxArray *c5_m156 = NULL;
  const mxArray *c5_m157 = NULL;
  const mxArray *c5_m158 = NULL;
  const mxArray *c5_m159 = NULL;
  const mxArray *c5_m160 = NULL;
  const mxArray *c5_m161 = NULL;
  const mxArray *c5_m162 = NULL;
  const mxArray *c5_m163 = NULL;
  const mxArray *c5_m164 = NULL;
  const mxArray *c5_m165 = NULL;
  const mxArray *c5_m166 = NULL;
  const mxArray *c5_m167 = NULL;
  const mxArray *c5_m168 = NULL;
  const mxArray *c5_m169 = NULL;
  const mxArray *c5_m170 = NULL;
  const mxArray *c5_m171 = NULL;
  const mxArray *c5_m172 = NULL;
  const mxArray *c5_m173 = NULL;
  const mxArray *c5_m174 = NULL;
  const mxArray *c5_m175 = NULL;
  const mxArray *c5_m176 = NULL;
  const mxArray *c5_m177 = NULL;
  const mxArray *c5_m178 = NULL;
  const mxArray *c5_m179 = NULL;
  const mxArray *c5_m180 = NULL;
  const mxArray *c5_m181 = NULL;
  const mxArray *c5_m182 = NULL;
  const mxArray *c5_m183 = NULL;
  const mxArray *c5_m184 = NULL;
  const mxArray *c5_m185 = NULL;
  const mxArray *c5_m186 = NULL;
  const mxArray *c5_m187 = NULL;
  const mxArray *c5_m188 = NULL;
  const mxArray *c5_m189 = NULL;
  const mxArray *c5_m190 = NULL;
  const mxArray *c5_m191 = NULL;
  const mxArray *c5_m192 = NULL;
  const mxArray *c5_m193 = NULL;
  const mxArray *c5_m194 = NULL;
  const mxArray *c5_m195 = NULL;
  const mxArray *c5_m196 = NULL;
  const mxArray *c5_m197 = NULL;
  const mxArray *c5_m198 = NULL;
  const mxArray *c5_m199 = NULL;
  const mxArray *c5_m200 = NULL;
  const mxArray *c5_m201 = NULL;
  const mxArray *c5_m202 = NULL;
  const mxArray *c5_m203 = NULL;
  const mxArray *c5_m204 = NULL;
  const mxArray *c5_m205 = NULL;
  const mxArray *c5_m206 = NULL;
  const mxArray *c5_m207 = NULL;
  const mxArray *c5_m208 = NULL;
  const mxArray *c5_m209 = NULL;
  const mxArray *c5_m210 = NULL;
  const mxArray *c5_m211 = NULL;
  const mxArray *c5_m212 = NULL;
  const mxArray *c5_m213 = NULL;
  const mxArray *c5_m214 = NULL;
  const mxArray *c5_m215 = NULL;
  const mxArray *c5_m216 = NULL;
  const mxArray *c5_m217 = NULL;
  const mxArray *c5_m218 = NULL;
  const mxArray *c5_m219 = NULL;
  const mxArray *c5_m220 = NULL;
  const mxArray *c5_m221 = NULL;
  const mxArray *c5_m222 = NULL;
  const mxArray *c5_m223 = NULL;
  const mxArray *c5_m224 = NULL;
  const mxArray *c5_m225 = NULL;
  const mxArray *c5_m226 = NULL;
  const mxArray *c5_m227 = NULL;
  const mxArray *c5_m228 = NULL;
  const mxArray *c5_m229 = NULL;
  const mxArray *c5_m230 = NULL;
  const mxArray *c5_m231 = NULL;
  const mxArray *c5_m232 = NULL;
  const mxArray *c5_m233 = NULL;
  const mxArray *c5_m234 = NULL;
  const mxArray *c5_m235 = NULL;
  const mxArray *c5_m236 = NULL;
  const mxArray *c5_m237 = NULL;
  const mxArray *c5_m238 = NULL;
  const mxArray *c5_m239 = NULL;
  const mxArray *c5_m240 = NULL;
  const mxArray *c5_m241 = NULL;
  const mxArray *c5_m242 = NULL;
  const mxArray *c5_m243 = NULL;
  const mxArray *c5_m244 = NULL;
  const mxArray *c5_m245 = NULL;
  const mxArray *c5_m246 = NULL;
  const mxArray *c5_m247 = NULL;
  const mxArray *c5_m248 = NULL;
  const mxArray *c5_m249 = NULL;
  const mxArray *c5_m250 = NULL;
  const mxArray *c5_m251 = NULL;
  const mxArray *c5_m252 = NULL;
  const mxArray *c5_m253 = NULL;
  const mxArray *c5_m254 = NULL;
  const mxArray *c5_m255 = NULL;
  const mxArray *c5_m256 = NULL;
  const mxArray *c5_m257 = NULL;
  const mxArray *c5_m258 = NULL;
  const mxArray *c5_m259 = NULL;
  const mxArray *c5_m260 = NULL;
  const mxArray *c5_m261 = NULL;
  const mxArray *c5_m262 = NULL;
  const mxArray *c5_m263 = NULL;
  const mxArray *c5_m264 = NULL;
  const mxArray *c5_m265 = NULL;
  const mxArray *c5_m266 = NULL;
  const mxArray *c5_m267 = NULL;
  const mxArray *c5_m268 = NULL;
  const mxArray *c5_m269 = NULL;
  const mxArray *c5_m270 = NULL;
  const mxArray *c5_m271 = NULL;
  const mxArray *c5_m272 = NULL;
  const mxArray *c5_m273 = NULL;
  const mxArray *c5_m274 = NULL;
  const mxArray *c5_m275 = NULL;
  const mxArray *c5_m276 = NULL;
  const mxArray *c5_m277 = NULL;
  const mxArray *c5_m278 = NULL;
  const mxArray *c5_m279 = NULL;
  const mxArray *c5_m280 = NULL;
  const mxArray *c5_m281 = NULL;
  const mxArray *c5_m282 = NULL;
  const mxArray *c5_m283 = NULL;
  const mxArray *c5_m284 = NULL;
  const mxArray *c5_m285 = NULL;
  const mxArray *c5_m286 = NULL;
  const mxArray *c5_m287 = NULL;
  const mxArray *c5_m288 = NULL;
  const mxArray *c5_m289 = NULL;
  const mxArray *c5_m290 = NULL;
  const mxArray *c5_m291 = NULL;
  const mxArray *c5_m292 = NULL;
  const mxArray *c5_m293 = NULL;
  const mxArray *c5_m294 = NULL;
  const mxArray *c5_m295 = NULL;
  const mxArray *c5_m296 = NULL;
  const mxArray *c5_m297 = NULL;
  const mxArray *c5_m298 = NULL;
  const mxArray *c5_m299 = NULL;
  const mxArray *c5_m300 = NULL;
  const mxArray *c5_m301 = NULL;
  const mxArray *c5_m302 = NULL;
  const mxArray *c5_m303 = NULL;
  const mxArray *c5_m304 = NULL;
  const mxArray *c5_m305 = NULL;
  const mxArray *c5_m306 = NULL;
  const mxArray *c5_m307 = NULL;
  const mxArray *c5_m308 = NULL;
  const mxArray *c5_m309 = NULL;
  const mxArray *c5_m310 = NULL;
  const mxArray *c5_m311 = NULL;
  const mxArray *c5_m312 = NULL;
  const mxArray *c5_m313 = NULL;
  const mxArray *c5_m314 = NULL;
  const mxArray *c5_m315 = NULL;
  const mxArray *c5_m316 = NULL;
  const mxArray *c5_m317 = NULL;
  const mxArray *c5_m318 = NULL;
  const mxArray *c5_m319 = NULL;
  const mxArray *c5_m320 = NULL;
  const mxArray *c5_m321 = NULL;
  const mxArray *c5_m322 = NULL;
  const mxArray *c5_m323 = NULL;
  const mxArray *c5_m324 = NULL;
  const mxArray *c5_m325 = NULL;
  const mxArray *c5_m326 = NULL;
  const mxArray *c5_m327 = NULL;
  const mxArray *c5_m328 = NULL;
  const mxArray *c5_m329 = NULL;
  const mxArray *c5_m330 = NULL;
  const mxArray *c5_m331 = NULL;
  const mxArray *c5_m332 = NULL;
  const mxArray *c5_m333 = NULL;
  const mxArray *c5_m334 = NULL;
  const mxArray *c5_m335 = NULL;
  const mxArray *c5_m336 = NULL;
  const mxArray *c5_m337 = NULL;
  const mxArray *c5_m338 = NULL;
  const mxArray *c5_m339 = NULL;
  const mxArray *c5_m340 = NULL;
  const mxArray *c5_m341 = NULL;
  const mxArray *c5_m342 = NULL;
  const mxArray *c5_m343 = NULL;
  const mxArray *c5_m344 = NULL;
  const mxArray *c5_m345 = NULL;
  const mxArray *c5_m346 = NULL;
  const mxArray *c5_m347 = NULL;
  const mxArray *c5_m348 = NULL;
  const mxArray *c5_m349 = NULL;
  const mxArray *c5_m350 = NULL;
  const mxArray *c5_m351 = NULL;
  const mxArray *c5_m352 = NULL;
  const mxArray *c5_m353 = NULL;
  const mxArray *c5_m354 = NULL;
  const mxArray *c5_m355 = NULL;
  const mxArray *c5_m356 = NULL;
  const mxArray *c5_m357 = NULL;
  const mxArray *c5_m358 = NULL;
  const mxArray *c5_m359 = NULL;
  const mxArray *c5_m360 = NULL;
  const mxArray *c5_m361 = NULL;
  const mxArray *c5_m362 = NULL;
  const mxArray *c5_m363 = NULL;
  const mxArray *c5_m364 = NULL;
  const mxArray *c5_m365 = NULL;
  const mxArray *c5_m366 = NULL;
  const mxArray *c5_m367 = NULL;
  const mxArray *c5_m368 = NULL;
  const mxArray *c5_m369 = NULL;
  const mxArray *c5_m370 = NULL;
  const mxArray *c5_m371 = NULL;
  const mxArray *c5_m372 = NULL;
  const mxArray *c5_m373 = NULL;
  const mxArray *c5_m374 = NULL;
  const mxArray *c5_m375 = NULL;
  const mxArray *c5_m376 = NULL;
  const mxArray *c5_m377 = NULL;
  const mxArray *c5_m378 = NULL;
  const mxArray *c5_m379 = NULL;
  const mxArray *c5_m380 = NULL;
  const mxArray *c5_m381 = NULL;
  const mxArray *c5_m382 = NULL;
  const mxArray *c5_m383 = NULL;
  const mxArray *c5_m384 = NULL;
  const mxArray *c5_m385 = NULL;
  const mxArray *c5_m386 = NULL;
  const mxArray *c5_m387 = NULL;
  const mxArray *c5_m388 = NULL;
  const mxArray *c5_m389 = NULL;
  const mxArray *c5_m390 = NULL;
  const mxArray *c5_m391 = NULL;
  const mxArray *c5_m392 = NULL;
  const mxArray *c5_m393 = NULL;
  const mxArray *c5_m394 = NULL;
  const mxArray *c5_m395 = NULL;
  const mxArray *c5_m396 = NULL;
  const mxArray *c5_m397 = NULL;
  const mxArray *c5_m398 = NULL;
  const mxArray *c5_m399 = NULL;
  const mxArray *c5_m400 = NULL;
  const mxArray *c5_m401 = NULL;
  const mxArray *c5_m402 = NULL;
  const mxArray *c5_m403 = NULL;
  const mxArray *c5_m404 = NULL;
  const mxArray *c5_m405 = NULL;
  const mxArray *c5_m406 = NULL;
  const mxArray *c5_m407 = NULL;
  const mxArray *c5_m408 = NULL;
  const mxArray *c5_m409 = NULL;
  const mxArray *c5_m410 = NULL;
  const mxArray *c5_m411 = NULL;
  const mxArray *c5_m412 = NULL;
  const mxArray *c5_m413 = NULL;
  const mxArray *c5_m414 = NULL;
  const mxArray *c5_m415 = NULL;
  const mxArray *c5_m416 = NULL;
  const mxArray *c5_m417 = NULL;
  const mxArray *c5_m418 = NULL;
  const mxArray *c5_m419 = NULL;
  const mxArray *c5_m420 = NULL;
  const mxArray *c5_m421 = NULL;
  const mxArray *c5_m422 = NULL;
  const mxArray *c5_m423 = NULL;
  const mxArray *c5_m424 = NULL;
  const mxArray *c5_m425 = NULL;
  const mxArray *c5_m426 = NULL;
  const mxArray *c5_m427 = NULL;
  const mxArray *c5_m428 = NULL;
  const mxArray *c5_m429 = NULL;
  const mxArray *c5_m430 = NULL;
  const mxArray *c5_m431 = NULL;
  const mxArray *c5_m432 = NULL;
  const mxArray *c5_m433 = NULL;
  const mxArray *c5_m434 = NULL;
  const mxArray *c5_m435 = NULL;
  const mxArray *c5_m436 = NULL;
  const mxArray *c5_m437 = NULL;
  const mxArray *c5_m438 = NULL;
  const mxArray *c5_m439 = NULL;
  const mxArray *c5_m440 = NULL;
  const mxArray *c5_m441 = NULL;
  const mxArray *c5_m442 = NULL;
  const mxArray *c5_m443 = NULL;
  const mxArray *c5_m444 = NULL;
  const mxArray *c5_m445 = NULL;
  const mxArray *c5_m446 = NULL;
  const mxArray *c5_m447 = NULL;
  const mxArray *c5_m448 = NULL;
  const mxArray *c5_m449 = NULL;
  const mxArray *c5_m450 = NULL;
  const mxArray *c5_m451 = NULL;
  const mxArray *c5_m452 = NULL;
  const mxArray *c5_m453 = NULL;
  const mxArray *c5_m454 = NULL;
  const mxArray *c5_m455 = NULL;
  const mxArray *c5_m456 = NULL;
  const mxArray *c5_m457 = NULL;
  const mxArray *c5_m458 = NULL;
  const mxArray *c5_m459 = NULL;
  const mxArray *c5_m460 = NULL;
  const mxArray *c5_m461 = NULL;
  const mxArray *c5_m462 = NULL;
  const mxArray *c5_m463 = NULL;
  const mxArray *c5_m464 = NULL;
  const mxArray *c5_m465 = NULL;
  const mxArray *c5_m466 = NULL;
  const mxArray *c5_m467 = NULL;
  const mxArray *c5_m468 = NULL;
  const mxArray *c5_m469 = NULL;
  const mxArray *c5_m470 = NULL;
  const mxArray *c5_m471 = NULL;
  const mxArray *c5_m472 = NULL;
  const mxArray *c5_m473 = NULL;
  const mxArray *c5_m474 = NULL;
  const mxArray *c5_m475 = NULL;
  const mxArray *c5_m476 = NULL;
  const mxArray *c5_m477 = NULL;
  const mxArray *c5_m478 = NULL;
  const mxArray *c5_m479 = NULL;
  const mxArray *c5_m480 = NULL;
  const mxArray *c5_m481 = NULL;
  const mxArray *c5_m482 = NULL;
  const mxArray *c5_m483 = NULL;
  const mxArray *c5_m484 = NULL;
  const mxArray *c5_m485 = NULL;
  const mxArray *c5_m486 = NULL;
  const mxArray *c5_m487 = NULL;
  const mxArray *c5_m488 = NULL;
  const mxArray *c5_m489 = NULL;
  const mxArray *c5_m490 = NULL;
  const mxArray *c5_m491 = NULL;
  const mxArray *c5_m492 = NULL;
  const mxArray *c5_m493 = NULL;
  const mxArray *c5_m494 = NULL;
  const mxArray *c5_m495 = NULL;
  const mxArray *c5_m496 = NULL;
  const mxArray *c5_m497 = NULL;
  const mxArray *c5_m498 = NULL;
  const mxArray *c5_m499 = NULL;
  const mxArray *c5_m500 = NULL;
  const mxArray *c5_m501 = NULL;
  const mxArray *c5_m502 = NULL;
  const mxArray *c5_m503 = NULL;
  const mxArray *c5_m504 = NULL;
  const mxArray *c5_m505 = NULL;
  const mxArray *c5_m506 = NULL;
  const mxArray *c5_m507 = NULL;
  const mxArray *c5_m508 = NULL;
  const mxArray *c5_m509 = NULL;
  const mxArray *c5_m510 = NULL;
  const mxArray *c5_m511 = NULL;
  const mxArray *c5_m512 = NULL;
  const mxArray *c5_m513 = NULL;
  const mxArray *c5_m514 = NULL;
  const mxArray *c5_m515 = NULL;
  const mxArray *c5_m516 = NULL;
  const mxArray *c5_m517 = NULL;
  const mxArray *c5_m518 = NULL;
  const mxArray *c5_m519 = NULL;
  const mxArray *c5_m520 = NULL;
  const mxArray *c5_m521 = NULL;
  const mxArray *c5_m522 = NULL;
  const mxArray *c5_m523 = NULL;
  const mxArray *c5_m524 = NULL;
  const mxArray *c5_m525 = NULL;
  const mxArray *c5_m526 = NULL;
  const mxArray *c5_m527 = NULL;
  const mxArray *c5_m528 = NULL;
  const mxArray *c5_m529 = NULL;
  const mxArray *c5_m530 = NULL;
  const mxArray *c5_m531 = NULL;
  const mxArray *c5_m532 = NULL;
  const mxArray *c5_m533 = NULL;
  const mxArray *c5_m534 = NULL;
  const mxArray *c5_m535 = NULL;
  const mxArray *c5_m536 = NULL;
  const mxArray *c5_m537 = NULL;
  const mxArray *c5_m538 = NULL;
  const mxArray *c5_m539 = NULL;
  const mxArray *c5_m540 = NULL;
  const mxArray *c5_m541 = NULL;
  const mxArray *c5_m542 = NULL;
  const mxArray *c5_m543 = NULL;
  const mxArray *c5_m544 = NULL;
  const mxArray *c5_m545 = NULL;
  const mxArray *c5_m546 = NULL;
  const mxArray *c5_m547 = NULL;
  const mxArray *c5_m548 = NULL;
  const mxArray *c5_m549 = NULL;
  const mxArray *c5_m550 = NULL;
  const mxArray *c5_m551 = NULL;
  const mxArray *c5_m552 = NULL;
  const mxArray *c5_m553 = NULL;
  const mxArray *c5_m554 = NULL;
  const mxArray *c5_m555 = NULL;
  const mxArray *c5_m556 = NULL;
  const mxArray *c5_m557 = NULL;
  const mxArray *c5_m558 = NULL;
  const mxArray *c5_m559 = NULL;
  const mxArray *c5_m560 = NULL;
  const mxArray *c5_m561 = NULL;
  const mxArray *c5_m562 = NULL;
  const mxArray *c5_m563 = NULL;
  const mxArray *c5_m564 = NULL;
  const mxArray *c5_m565 = NULL;
  const mxArray *c5_m566 = NULL;
  const mxArray *c5_m567 = NULL;
  const mxArray *c5_m568 = NULL;
  const mxArray *c5_m569 = NULL;
  const mxArray *c5_m570 = NULL;
  const mxArray *c5_m571 = NULL;
  const mxArray *c5_m572 = NULL;
  const mxArray *c5_m573 = NULL;
  const mxArray *c5_m574 = NULL;
  const mxArray *c5_m575 = NULL;
  const mxArray *c5_m576 = NULL;
  const mxArray *c5_m577 = NULL;
  const mxArray *c5_m578 = NULL;
  const mxArray *c5_m579 = NULL;
  const mxArray *c5_m580 = NULL;
  const mxArray *c5_m581 = NULL;
  const mxArray *c5_m582 = NULL;
  const mxArray *c5_m583 = NULL;
  const mxArray *c5_m584 = NULL;
  const mxArray *c5_m585 = NULL;
  const mxArray *c5_m586 = NULL;
  const mxArray *c5_m587 = NULL;
  const mxArray *c5_m588 = NULL;
  const mxArray *c5_m589 = NULL;
  const mxArray *c5_m590 = NULL;
  const mxArray *c5_m591 = NULL;
  const mxArray *c5_m592 = NULL;
  const mxArray *c5_m593 = NULL;
  const mxArray *c5_m594 = NULL;
  const mxArray *c5_m595 = NULL;
  const mxArray *c5_m596 = NULL;
  const mxArray *c5_m597 = NULL;
  const mxArray *c5_m598 = NULL;
  const mxArray *c5_m599 = NULL;
  const mxArray *c5_m600 = NULL;
  const mxArray *c5_m601 = NULL;
  const mxArray *c5_m602 = NULL;
  const mxArray *c5_m603 = NULL;
  const mxArray *c5_m604 = NULL;
  const mxArray *c5_m605 = NULL;
  const mxArray *c5_m606 = NULL;
  const mxArray *c5_m607 = NULL;
  const mxArray *c5_m608 = NULL;
  const mxArray *c5_m609 = NULL;
  const mxArray *c5_m610 = NULL;
  const mxArray *c5_m611 = NULL;
  const mxArray *c5_m612 = NULL;
  const mxArray *c5_m613 = NULL;
  const mxArray *c5_m614 = NULL;
  const mxArray *c5_m615 = NULL;
  uint32_T c5_u0;
  const mxArray *c5_m616 = NULL;
  const mxArray *c5_m617 = NULL;
  const mxArray *c5_m618 = NULL;
  const mxArray *c5_m619 = NULL;
  const mxArray *c5_m620 = NULL;
  const mxArray *c5_m621 = NULL;
  const mxArray *c5_m622 = NULL;
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
  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c5_debug_family_names,
    c5_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c5_hdl_fm, 0U, c5_f_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c5_nargin, 1U, c5_e_sf_marshallOut,
    c5_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c5_nargout, 2U, c5_e_sf_marshallOut,
    c5_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c5_addr, 3U, c5_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c5_read, 4U, c5_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c5_instr_out, 5U,
    c5_b_sf_marshallOut, c5_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(chartInstance->c5_data, 6U,
    c5_sf_marshallOut, c5_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 7);
  c5_hdl_fm = c5_eml_mx;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 16);
  if (CV_EML_IF(0, 0, !chartInstance->c5_data_not_empty)) {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 17);
    c5_fi_helper(chartInstance);
    for (c5_i2 = 0; c5_i2 < 256; c5_i2++) {
      chartInstance->c5_data[c5_i2] = 0U;
    }

    chartInstance->c5_data_not_empty = TRUE;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 21);
  sf_mex_destroy(&c5_m0);
  sf_mex_destroy(&c5_m1);
  sf_mex_destroy(&c5_m2);
  sf_mex_destroy(&c5_m3);
  sf_mex_destroy(&c5_m4);
  sf_mex_destroy(&c5_m5);
  sf_mex_destroy(&c5_m6);
  chartInstance->c5_data[0] = 2314U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 22);
  sf_mex_destroy(&c5_m7);
  sf_mex_destroy(&c5_m8);
  sf_mex_destroy(&c5_m9);
  sf_mex_destroy(&c5_m10);
  sf_mex_destroy(&c5_m11);
  sf_mex_destroy(&c5_m12);
  sf_mex_destroy(&c5_m13);
  chartInstance->c5_data[1] = 2560U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 23);
  sf_mex_destroy(&c5_m14);
  sf_mex_destroy(&c5_m15);
  sf_mex_destroy(&c5_m16);
  sf_mex_destroy(&c5_m17);
  sf_mex_destroy(&c5_m18);
  sf_mex_destroy(&c5_m19);
  sf_mex_destroy(&c5_m20);
  chartInstance->c5_data[2] = 2316U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 24);
  sf_mex_destroy(&c5_m21);
  sf_mex_destroy(&c5_m22);
  sf_mex_destroy(&c5_m23);
  sf_mex_destroy(&c5_m24);
  sf_mex_destroy(&c5_m25);
  sf_mex_destroy(&c5_m26);
  sf_mex_destroy(&c5_m27);
  chartInstance->c5_data[3] = 2561U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 25);
  sf_mex_destroy(&c5_m28);
  sf_mex_destroy(&c5_m29);
  sf_mex_destroy(&c5_m30);
  sf_mex_destroy(&c5_m31);
  sf_mex_destroy(&c5_m32);
  sf_mex_destroy(&c5_m33);
  sf_mex_destroy(&c5_m34);
  chartInstance->c5_data[4] = 2322U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 26);
  sf_mex_destroy(&c5_m35);
  sf_mex_destroy(&c5_m36);
  sf_mex_destroy(&c5_m37);
  sf_mex_destroy(&c5_m38);
  sf_mex_destroy(&c5_m39);
  sf_mex_destroy(&c5_m40);
  sf_mex_destroy(&c5_m41);
  chartInstance->c5_data[5] = 2572U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 27);
  sf_mex_destroy(&c5_m42);
  sf_mex_destroy(&c5_m43);
  sf_mex_destroy(&c5_m44);
  sf_mex_destroy(&c5_m45);
  sf_mex_destroy(&c5_m46);
  sf_mex_destroy(&c5_m47);
  sf_mex_destroy(&c5_m48);
  chartInstance->c5_data[6] = 2310U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 28);
  sf_mex_destroy(&c5_m49);
  sf_mex_destroy(&c5_m50);
  sf_mex_destroy(&c5_m51);
  sf_mex_destroy(&c5_m52);
  sf_mex_destroy(&c5_m53);
  sf_mex_destroy(&c5_m54);
  sf_mex_destroy(&c5_m55);
  chartInstance->c5_data[7] = 2573U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 29);
  sf_mex_destroy(&c5_m56);
  sf_mex_destroy(&c5_m57);
  sf_mex_destroy(&c5_m58);
  sf_mex_destroy(&c5_m59);
  sf_mex_destroy(&c5_m60);
  sf_mex_destroy(&c5_m61);
  sf_mex_destroy(&c5_m62);
  chartInstance->c5_data[8] = 2323U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 30);
  sf_mex_destroy(&c5_m63);
  sf_mex_destroy(&c5_m64);
  sf_mex_destroy(&c5_m65);
  sf_mex_destroy(&c5_m66);
  sf_mex_destroy(&c5_m67);
  sf_mex_destroy(&c5_m68);
  sf_mex_destroy(&c5_m69);
  chartInstance->c5_data[9] = 2574U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 31);
  sf_mex_destroy(&c5_m70);
  sf_mex_destroy(&c5_m71);
  sf_mex_destroy(&c5_m72);
  sf_mex_destroy(&c5_m73);
  sf_mex_destroy(&c5_m74);
  sf_mex_destroy(&c5_m75);
  sf_mex_destroy(&c5_m76);
  chartInstance->c5_data[10] = 2555U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 32);
  sf_mex_destroy(&c5_m77);
  sf_mex_destroy(&c5_m78);
  sf_mex_destroy(&c5_m79);
  sf_mex_destroy(&c5_m80);
  sf_mex_destroy(&c5_m81);
  sf_mex_destroy(&c5_m82);
  sf_mex_destroy(&c5_m83);
  chartInstance->c5_data[11] = 2575U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 33);
  sf_mex_destroy(&c5_m84);
  sf_mex_destroy(&c5_m85);
  sf_mex_destroy(&c5_m86);
  sf_mex_destroy(&c5_m87);
  sf_mex_destroy(&c5_m88);
  sf_mex_destroy(&c5_m89);
  sf_mex_destroy(&c5_m90);
  chartInstance->c5_data[12] = 2319U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 34);
  sf_mex_destroy(&c5_m91);
  sf_mex_destroy(&c5_m92);
  sf_mex_destroy(&c5_m93);
  sf_mex_destroy(&c5_m94);
  sf_mex_destroy(&c5_m95);
  sf_mex_destroy(&c5_m96);
  sf_mex_destroy(&c5_m97);
  chartInstance->c5_data[13] = 2576U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 35);
  sf_mex_destroy(&c5_m98);
  sf_mex_destroy(&c5_m99);
  sf_mex_destroy(&c5_m100);
  sf_mex_destroy(&c5_m101);
  sf_mex_destroy(&c5_m102);
  sf_mex_destroy(&c5_m103);
  sf_mex_destroy(&c5_m104);
  chartInstance->c5_data[14] = 2558U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 36);
  sf_mex_destroy(&c5_m105);
  sf_mex_destroy(&c5_m106);
  sf_mex_destroy(&c5_m107);
  sf_mex_destroy(&c5_m108);
  sf_mex_destroy(&c5_m109);
  sf_mex_destroy(&c5_m110);
  sf_mex_destroy(&c5_m111);
  chartInstance->c5_data[15] = 2577U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 37);
  sf_mex_destroy(&c5_m112);
  sf_mex_destroy(&c5_m113);
  sf_mex_destroy(&c5_m114);
  sf_mex_destroy(&c5_m115);
  sf_mex_destroy(&c5_m116);
  sf_mex_destroy(&c5_m117);
  sf_mex_destroy(&c5_m118);
  chartInstance->c5_data[16] = 2306U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 38);
  sf_mex_destroy(&c5_m119);
  sf_mex_destroy(&c5_m120);
  sf_mex_destroy(&c5_m121);
  sf_mex_destroy(&c5_m122);
  sf_mex_destroy(&c5_m123);
  sf_mex_destroy(&c5_m124);
  sf_mex_destroy(&c5_m125);
  chartInstance->c5_data[17] = 2578U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 39);
  sf_mex_destroy(&c5_m126);
  sf_mex_destroy(&c5_m127);
  sf_mex_destroy(&c5_m128);
  sf_mex_destroy(&c5_m129);
  sf_mex_destroy(&c5_m130);
  sf_mex_destroy(&c5_m131);
  sf_mex_destroy(&c5_m132);
  chartInstance->c5_data[18] = 2315U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 40);
  sf_mex_destroy(&c5_m133);
  sf_mex_destroy(&c5_m134);
  sf_mex_destroy(&c5_m135);
  sf_mex_destroy(&c5_m136);
  sf_mex_destroy(&c5_m137);
  sf_mex_destroy(&c5_m138);
  sf_mex_destroy(&c5_m139);
  chartInstance->c5_data[19] = 2579U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 41);
  sf_mex_destroy(&c5_m140);
  sf_mex_destroy(&c5_m141);
  sf_mex_destroy(&c5_m142);
  sf_mex_destroy(&c5_m143);
  sf_mex_destroy(&c5_m144);
  sf_mex_destroy(&c5_m145);
  sf_mex_destroy(&c5_m146);
  chartInstance->c5_data[20] = 2324U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 42);
  sf_mex_destroy(&c5_m147);
  sf_mex_destroy(&c5_m148);
  sf_mex_destroy(&c5_m149);
  sf_mex_destroy(&c5_m150);
  sf_mex_destroy(&c5_m151);
  sf_mex_destroy(&c5_m152);
  sf_mex_destroy(&c5_m153);
  chartInstance->c5_data[21] = 2580U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 43);
  sf_mex_destroy(&c5_m154);
  sf_mex_destroy(&c5_m155);
  sf_mex_destroy(&c5_m156);
  sf_mex_destroy(&c5_m157);
  sf_mex_destroy(&c5_m158);
  sf_mex_destroy(&c5_m159);
  sf_mex_destroy(&c5_m160);
  chartInstance->c5_data[22] = 2314U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 44);
  sf_mex_destroy(&c5_m161);
  sf_mex_destroy(&c5_m162);
  sf_mex_destroy(&c5_m163);
  sf_mex_destroy(&c5_m164);
  sf_mex_destroy(&c5_m165);
  sf_mex_destroy(&c5_m166);
  sf_mex_destroy(&c5_m167);
  chartInstance->c5_data[23] = 2581U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 45);
  sf_mex_destroy(&c5_m168);
  sf_mex_destroy(&c5_m169);
  sf_mex_destroy(&c5_m170);
  sf_mex_destroy(&c5_m171);
  sf_mex_destroy(&c5_m172);
  sf_mex_destroy(&c5_m173);
  sf_mex_destroy(&c5_m174);
  chartInstance->c5_data[24] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 46);
  sf_mex_destroy(&c5_m175);
  sf_mex_destroy(&c5_m176);
  sf_mex_destroy(&c5_m177);
  sf_mex_destroy(&c5_m178);
  sf_mex_destroy(&c5_m179);
  sf_mex_destroy(&c5_m180);
  sf_mex_destroy(&c5_m181);
  chartInstance->c5_data[25] = 2562U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 47);
  sf_mex_destroy(&c5_m182);
  sf_mex_destroy(&c5_m183);
  sf_mex_destroy(&c5_m184);
  sf_mex_destroy(&c5_m185);
  sf_mex_destroy(&c5_m186);
  sf_mex_destroy(&c5_m187);
  sf_mex_destroy(&c5_m188);
  chartInstance->c5_data[26] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 48);
  sf_mex_destroy(&c5_m189);
  sf_mex_destroy(&c5_m190);
  sf_mex_destroy(&c5_m191);
  sf_mex_destroy(&c5_m192);
  sf_mex_destroy(&c5_m193);
  sf_mex_destroy(&c5_m194);
  sf_mex_destroy(&c5_m195);
  chartInstance->c5_data[27] = 2563U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 49);
  sf_mex_destroy(&c5_m196);
  sf_mex_destroy(&c5_m197);
  sf_mex_destroy(&c5_m198);
  sf_mex_destroy(&c5_m199);
  sf_mex_destroy(&c5_m200);
  sf_mex_destroy(&c5_m201);
  sf_mex_destroy(&c5_m202);
  chartInstance->c5_data[28] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 50);
  sf_mex_destroy(&c5_m203);
  sf_mex_destroy(&c5_m204);
  sf_mex_destroy(&c5_m205);
  sf_mex_destroy(&c5_m206);
  sf_mex_destroy(&c5_m207);
  sf_mex_destroy(&c5_m208);
  sf_mex_destroy(&c5_m209);
  chartInstance->c5_data[29] = 2564U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 51);
  sf_mex_destroy(&c5_m210);
  sf_mex_destroy(&c5_m211);
  sf_mex_destroy(&c5_m212);
  sf_mex_destroy(&c5_m213);
  sf_mex_destroy(&c5_m214);
  sf_mex_destroy(&c5_m215);
  sf_mex_destroy(&c5_m216);
  chartInstance->c5_data[30] = 2U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 52);
  sf_mex_destroy(&c5_m217);
  sf_mex_destroy(&c5_m218);
  sf_mex_destroy(&c5_m219);
  sf_mex_destroy(&c5_m220);
  sf_mex_destroy(&c5_m221);
  sf_mex_destroy(&c5_m222);
  sf_mex_destroy(&c5_m223);
  chartInstance->c5_data[31] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 53);
  sf_mex_destroy(&c5_m224);
  sf_mex_destroy(&c5_m225);
  sf_mex_destroy(&c5_m226);
  sf_mex_destroy(&c5_m227);
  sf_mex_destroy(&c5_m228);
  sf_mex_destroy(&c5_m229);
  sf_mex_destroy(&c5_m230);
  chartInstance->c5_data[32] = 1540U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 54);
  sf_mex_destroy(&c5_m231);
  sf_mex_destroy(&c5_m232);
  sf_mex_destroy(&c5_m233);
  sf_mex_destroy(&c5_m234);
  sf_mex_destroy(&c5_m235);
  sf_mex_destroy(&c5_m236);
  sf_mex_destroy(&c5_m237);
  chartInstance->c5_data[33] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 55);
  sf_mex_destroy(&c5_m238);
  sf_mex_destroy(&c5_m239);
  sf_mex_destroy(&c5_m240);
  sf_mex_destroy(&c5_m241);
  sf_mex_destroy(&c5_m242);
  sf_mex_destroy(&c5_m243);
  sf_mex_destroy(&c5_m244);
  chartInstance->c5_data[34] = 1025U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 56);
  sf_mex_destroy(&c5_m245);
  sf_mex_destroy(&c5_m246);
  sf_mex_destroy(&c5_m247);
  sf_mex_destroy(&c5_m248);
  sf_mex_destroy(&c5_m249);
  sf_mex_destroy(&c5_m250);
  sf_mex_destroy(&c5_m251);
  chartInstance->c5_data[35] = 2565U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 57);
  sf_mex_destroy(&c5_m252);
  sf_mex_destroy(&c5_m253);
  sf_mex_destroy(&c5_m254);
  sf_mex_destroy(&c5_m255);
  sf_mex_destroy(&c5_m256);
  sf_mex_destroy(&c5_m257);
  sf_mex_destroy(&c5_m258);
  chartInstance->c5_data[36] = 261U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 58);
  sf_mex_destroy(&c5_m259);
  sf_mex_destroy(&c5_m260);
  sf_mex_destroy(&c5_m261);
  sf_mex_destroy(&c5_m262);
  sf_mex_destroy(&c5_m263);
  sf_mex_destroy(&c5_m264);
  sf_mex_destroy(&c5_m265);
  chartInstance->c5_data[37] = 2566U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 59);
  sf_mex_destroy(&c5_m266);
  sf_mex_destroy(&c5_m267);
  sf_mex_destroy(&c5_m268);
  sf_mex_destroy(&c5_m269);
  sf_mex_destroy(&c5_m270);
  sf_mex_destroy(&c5_m271);
  sf_mex_destroy(&c5_m272);
  chartInstance->c5_data[38] = 2U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 60);
  sf_mex_destroy(&c5_m273);
  sf_mex_destroy(&c5_m274);
  sf_mex_destroy(&c5_m275);
  sf_mex_destroy(&c5_m276);
  sf_mex_destroy(&c5_m277);
  sf_mex_destroy(&c5_m278);
  sf_mex_destroy(&c5_m279);
  chartInstance->c5_data[39] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 61);
  sf_mex_destroy(&c5_m280);
  sf_mex_destroy(&c5_m281);
  sf_mex_destroy(&c5_m282);
  sf_mex_destroy(&c5_m283);
  sf_mex_destroy(&c5_m284);
  sf_mex_destroy(&c5_m285);
  sf_mex_destroy(&c5_m286);
  chartInstance->c5_data[40] = 1025U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 62);
  sf_mex_destroy(&c5_m287);
  sf_mex_destroy(&c5_m288);
  sf_mex_destroy(&c5_m289);
  sf_mex_destroy(&c5_m290);
  sf_mex_destroy(&c5_m291);
  sf_mex_destroy(&c5_m292);
  sf_mex_destroy(&c5_m293);
  chartInstance->c5_data[41] = 2567U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 63);
  sf_mex_destroy(&c5_m294);
  sf_mex_destroy(&c5_m295);
  sf_mex_destroy(&c5_m296);
  sf_mex_destroy(&c5_m297);
  sf_mex_destroy(&c5_m298);
  sf_mex_destroy(&c5_m299);
  sf_mex_destroy(&c5_m300);
  chartInstance->c5_data[42] = 263U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 64);
  sf_mex_destroy(&c5_m301);
  sf_mex_destroy(&c5_m302);
  sf_mex_destroy(&c5_m303);
  sf_mex_destroy(&c5_m304);
  sf_mex_destroy(&c5_m305);
  sf_mex_destroy(&c5_m306);
  sf_mex_destroy(&c5_m307);
  chartInstance->c5_data[43] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 65);
  sf_mex_destroy(&c5_m308);
  sf_mex_destroy(&c5_m309);
  sf_mex_destroy(&c5_m310);
  sf_mex_destroy(&c5_m311);
  sf_mex_destroy(&c5_m312);
  sf_mex_destroy(&c5_m313);
  sf_mex_destroy(&c5_m314);
  chartInstance->c5_data[44] = 1542U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 66);
  sf_mex_destroy(&c5_m315);
  sf_mex_destroy(&c5_m316);
  sf_mex_destroy(&c5_m317);
  sf_mex_destroy(&c5_m318);
  sf_mex_destroy(&c5_m319);
  sf_mex_destroy(&c5_m320);
  sf_mex_destroy(&c5_m321);
  chartInstance->c5_data[45] = 3330U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 67);
  sf_mex_destroy(&c5_m322);
  sf_mex_destroy(&c5_m323);
  sf_mex_destroy(&c5_m324);
  sf_mex_destroy(&c5_m325);
  sf_mex_destroy(&c5_m326);
  sf_mex_destroy(&c5_m327);
  sf_mex_destroy(&c5_m328);
  chartInstance->c5_data[46] = 2055U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 68);
  sf_mex_destroy(&c5_m329);
  sf_mex_destroy(&c5_m330);
  sf_mex_destroy(&c5_m331);
  sf_mex_destroy(&c5_m332);
  sf_mex_destroy(&c5_m333);
  sf_mex_destroy(&c5_m334);
  sf_mex_destroy(&c5_m335);
  chartInstance->c5_data[47] = 2304U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 69);
  sf_mex_destroy(&c5_m336);
  sf_mex_destroy(&c5_m337);
  sf_mex_destroy(&c5_m338);
  sf_mex_destroy(&c5_m339);
  sf_mex_destroy(&c5_m340);
  sf_mex_destroy(&c5_m341);
  sf_mex_destroy(&c5_m342);
  chartInstance->c5_data[48] = 2563U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 70);
  sf_mex_destroy(&c5_m343);
  sf_mex_destroy(&c5_m344);
  sf_mex_destroy(&c5_m345);
  sf_mex_destroy(&c5_m346);
  sf_mex_destroy(&c5_m347);
  sf_mex_destroy(&c5_m348);
  sf_mex_destroy(&c5_m349);
  chartInstance->c5_data[49] = 263U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 71);
  sf_mex_destroy(&c5_m350);
  sf_mex_destroy(&c5_m351);
  sf_mex_destroy(&c5_m352);
  sf_mex_destroy(&c5_m353);
  sf_mex_destroy(&c5_m354);
  sf_mex_destroy(&c5_m355);
  sf_mex_destroy(&c5_m356);
  chartInstance->c5_data[50] = 2821U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 72);
  sf_mex_destroy(&c5_m357);
  sf_mex_destroy(&c5_m358);
  sf_mex_destroy(&c5_m359);
  sf_mex_destroy(&c5_m360);
  sf_mex_destroy(&c5_m361);
  sf_mex_destroy(&c5_m362);
  sf_mex_destroy(&c5_m363);
  chartInstance->c5_data[51] = 6U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 73);
  sf_mex_destroy(&c5_m364);
  sf_mex_destroy(&c5_m365);
  sf_mex_destroy(&c5_m366);
  sf_mex_destroy(&c5_m367);
  sf_mex_destroy(&c5_m368);
  sf_mex_destroy(&c5_m369);
  sf_mex_destroy(&c5_m370);
  chartInstance->c5_data[52] = 2823U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 74);
  sf_mex_destroy(&c5_m371);
  sf_mex_destroy(&c5_m372);
  sf_mex_destroy(&c5_m373);
  sf_mex_destroy(&c5_m374);
  sf_mex_destroy(&c5_m375);
  sf_mex_destroy(&c5_m376);
  sf_mex_destroy(&c5_m377);
  chartInstance->c5_data[53] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 75);
  sf_mex_destroy(&c5_m378);
  sf_mex_destroy(&c5_m379);
  sf_mex_destroy(&c5_m380);
  sf_mex_destroy(&c5_m381);
  sf_mex_destroy(&c5_m382);
  sf_mex_destroy(&c5_m383);
  sf_mex_destroy(&c5_m384);
  chartInstance->c5_data[54] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 76);
  sf_mex_destroy(&c5_m385);
  sf_mex_destroy(&c5_m386);
  sf_mex_destroy(&c5_m387);
  sf_mex_destroy(&c5_m388);
  sf_mex_destroy(&c5_m389);
  sf_mex_destroy(&c5_m390);
  sf_mex_destroy(&c5_m391);
  chartInstance->c5_data[55] = 1026U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 77);
  sf_mex_destroy(&c5_m392);
  sf_mex_destroy(&c5_m393);
  sf_mex_destroy(&c5_m394);
  sf_mex_destroy(&c5_m395);
  sf_mex_destroy(&c5_m396);
  sf_mex_destroy(&c5_m397);
  sf_mex_destroy(&c5_m398);
  chartInstance->c5_data[56] = 2562U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 78);
  sf_mex_destroy(&c5_m399);
  sf_mex_destroy(&c5_m400);
  sf_mex_destroy(&c5_m401);
  sf_mex_destroy(&c5_m402);
  sf_mex_destroy(&c5_m403);
  sf_mex_destroy(&c5_m404);
  sf_mex_destroy(&c5_m405);
  chartInstance->c5_data[57] = 0U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 79);
  sf_mex_destroy(&c5_m406);
  sf_mex_destroy(&c5_m407);
  sf_mex_destroy(&c5_m408);
  sf_mex_destroy(&c5_m409);
  sf_mex_destroy(&c5_m410);
  sf_mex_destroy(&c5_m411);
  sf_mex_destroy(&c5_m412);
  chartInstance->c5_data[58] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 80);
  sf_mex_destroy(&c5_m413);
  sf_mex_destroy(&c5_m414);
  sf_mex_destroy(&c5_m415);
  sf_mex_destroy(&c5_m416);
  sf_mex_destroy(&c5_m417);
  sf_mex_destroy(&c5_m418);
  sf_mex_destroy(&c5_m419);
  chartInstance->c5_data[59] = 1538U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 81);
  sf_mex_destroy(&c5_m420);
  sf_mex_destroy(&c5_m421);
  sf_mex_destroy(&c5_m422);
  sf_mex_destroy(&c5_m423);
  sf_mex_destroy(&c5_m424);
  sf_mex_destroy(&c5_m425);
  sf_mex_destroy(&c5_m426);
  chartInstance->c5_data[60] = 3842U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 82);
  sf_mex_destroy(&c5_m427);
  sf_mex_destroy(&c5_m428);
  sf_mex_destroy(&c5_m429);
  sf_mex_destroy(&c5_m430);
  sf_mex_destroy(&c5_m431);
  sf_mex_destroy(&c5_m432);
  sf_mex_destroy(&c5_m433);
  chartInstance->c5_data[61] = 2271U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 83);
  sf_mex_destroy(&c5_m434);
  sf_mex_destroy(&c5_m435);
  sf_mex_destroy(&c5_m436);
  sf_mex_destroy(&c5_m437);
  sf_mex_destroy(&c5_m438);
  sf_mex_destroy(&c5_m439);
  sf_mex_destroy(&c5_m440);
  chartInstance->c5_data[62] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 84);
  sf_mex_destroy(&c5_m441);
  sf_mex_destroy(&c5_m442);
  sf_mex_destroy(&c5_m443);
  sf_mex_destroy(&c5_m444);
  sf_mex_destroy(&c5_m445);
  sf_mex_destroy(&c5_m446);
  sf_mex_destroy(&c5_m447);
  chartInstance->c5_data[63] = 2564U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 85);
  sf_mex_destroy(&c5_m448);
  sf_mex_destroy(&c5_m449);
  sf_mex_destroy(&c5_m450);
  sf_mex_destroy(&c5_m451);
  sf_mex_destroy(&c5_m452);
  sf_mex_destroy(&c5_m453);
  sf_mex_destroy(&c5_m454);
  chartInstance->c5_data[64] = 3U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 86);
  sf_mex_destroy(&c5_m455);
  sf_mex_destroy(&c5_m456);
  sf_mex_destroy(&c5_m457);
  sf_mex_destroy(&c5_m458);
  sf_mex_destroy(&c5_m459);
  sf_mex_destroy(&c5_m460);
  sf_mex_destroy(&c5_m461);
  chartInstance->c5_data[65] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 87);
  sf_mex_destroy(&c5_m462);
  sf_mex_destroy(&c5_m463);
  sf_mex_destroy(&c5_m464);
  sf_mex_destroy(&c5_m465);
  sf_mex_destroy(&c5_m466);
  sf_mex_destroy(&c5_m467);
  sf_mex_destroy(&c5_m468);
  chartInstance->c5_data[66] = 1540U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 88);
  sf_mex_destroy(&c5_m469);
  sf_mex_destroy(&c5_m470);
  sf_mex_destroy(&c5_m471);
  sf_mex_destroy(&c5_m472);
  sf_mex_destroy(&c5_m473);
  sf_mex_destroy(&c5_m474);
  sf_mex_destroy(&c5_m475);
  chartInstance->c5_data[67] = 3842U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 89);
  sf_mex_destroy(&c5_m476);
  sf_mex_destroy(&c5_m477);
  sf_mex_destroy(&c5_m478);
  sf_mex_destroy(&c5_m479);
  sf_mex_destroy(&c5_m480);
  sf_mex_destroy(&c5_m481);
  sf_mex_destroy(&c5_m482);
  chartInstance->c5_data[68] = 2260U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 90);
  sf_mex_destroy(&c5_m483);
  sf_mex_destroy(&c5_m484);
  sf_mex_destroy(&c5_m485);
  sf_mex_destroy(&c5_m486);
  sf_mex_destroy(&c5_m487);
  sf_mex_destroy(&c5_m488);
  sf_mex_destroy(&c5_m489);
  chartInstance->c5_data[69] = 2304U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 91);
  sf_mex_destroy(&c5_m490);
  sf_mex_destroy(&c5_m491);
  sf_mex_destroy(&c5_m492);
  sf_mex_destroy(&c5_m493);
  sf_mex_destroy(&c5_m494);
  sf_mex_destroy(&c5_m495);
  sf_mex_destroy(&c5_m496);
  chartInstance->c5_data[70] = 2562U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 92);
  sf_mex_destroy(&c5_m497);
  sf_mex_destroy(&c5_m498);
  sf_mex_destroy(&c5_m499);
  sf_mex_destroy(&c5_m500);
  sf_mex_destroy(&c5_m501);
  sf_mex_destroy(&c5_m502);
  sf_mex_destroy(&c5_m503);
  chartInstance->c5_data[71] = 257U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 93);
  sf_mex_destroy(&c5_m504);
  sf_mex_destroy(&c5_m505);
  sf_mex_destroy(&c5_m506);
  sf_mex_destroy(&c5_m507);
  sf_mex_destroy(&c5_m508);
  sf_mex_destroy(&c5_m509);
  sf_mex_destroy(&c5_m510);
  chartInstance->c5_data[72] = 2815U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 94);
  sf_mex_destroy(&c5_m511);
  sf_mex_destroy(&c5_m512);
  sf_mex_destroy(&c5_m513);
  sf_mex_destroy(&c5_m514);
  sf_mex_destroy(&c5_m515);
  sf_mex_destroy(&c5_m516);
  sf_mex_destroy(&c5_m517);
  chartInstance->c5_data[73] = 3696U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 95);
  sf_mex_destroy(&c5_m518);
  sf_mex_destroy(&c5_m519);
  sf_mex_destroy(&c5_m520);
  sf_mex_destroy(&c5_m521);
  sf_mex_destroy(&c5_m522);
  sf_mex_destroy(&c5_m523);
  sf_mex_destroy(&c5_m524);
  chartInstance->c5_data[74] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 96);
  sf_mex_destroy(&c5_m525);
  sf_mex_destroy(&c5_m526);
  sf_mex_destroy(&c5_m527);
  sf_mex_destroy(&c5_m528);
  sf_mex_destroy(&c5_m529);
  sf_mex_destroy(&c5_m530);
  sf_mex_destroy(&c5_m531);
  chartInstance->c5_data[75] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 97);
  sf_mex_destroy(&c5_m532);
  sf_mex_destroy(&c5_m533);
  sf_mex_destroy(&c5_m534);
  sf_mex_destroy(&c5_m535);
  sf_mex_destroy(&c5_m536);
  sf_mex_destroy(&c5_m537);
  sf_mex_destroy(&c5_m538);
  chartInstance->c5_data[76] = 1025U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 98);
  sf_mex_destroy(&c5_m539);
  sf_mex_destroy(&c5_m540);
  sf_mex_destroy(&c5_m541);
  sf_mex_destroy(&c5_m542);
  sf_mex_destroy(&c5_m543);
  sf_mex_destroy(&c5_m544);
  sf_mex_destroy(&c5_m545);
  chartInstance->c5_data[77] = 2561U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 99);
  sf_mex_destroy(&c5_m546);
  sf_mex_destroy(&c5_m547);
  sf_mex_destroy(&c5_m548);
  sf_mex_destroy(&c5_m549);
  sf_mex_destroy(&c5_m550);
  sf_mex_destroy(&c5_m551);
  sf_mex_destroy(&c5_m552);
  chartInstance->c5_data[78] = 2305U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 100);
  sf_mex_destroy(&c5_m553);
  sf_mex_destroy(&c5_m554);
  sf_mex_destroy(&c5_m555);
  sf_mex_destroy(&c5_m556);
  sf_mex_destroy(&c5_m557);
  sf_mex_destroy(&c5_m558);
  sf_mex_destroy(&c5_m559);
  chartInstance->c5_data[79] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 101);
  sf_mex_destroy(&c5_m560);
  sf_mex_destroy(&c5_m561);
  sf_mex_destroy(&c5_m562);
  sf_mex_destroy(&c5_m563);
  sf_mex_destroy(&c5_m564);
  sf_mex_destroy(&c5_m565);
  sf_mex_destroy(&c5_m566);
  chartInstance->c5_data[80] = 1026U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 102);
  sf_mex_destroy(&c5_m567);
  sf_mex_destroy(&c5_m568);
  sf_mex_destroy(&c5_m569);
  sf_mex_destroy(&c5_m570);
  sf_mex_destroy(&c5_m571);
  sf_mex_destroy(&c5_m572);
  sf_mex_destroy(&c5_m573);
  chartInstance->c5_data[81] = 2562U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 103);
  sf_mex_destroy(&c5_m574);
  sf_mex_destroy(&c5_m575);
  sf_mex_destroy(&c5_m576);
  sf_mex_destroy(&c5_m577);
  sf_mex_destroy(&c5_m578);
  sf_mex_destroy(&c5_m579);
  sf_mex_destroy(&c5_m580);
  chartInstance->c5_data[82] = 0U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 104);
  sf_mex_destroy(&c5_m581);
  sf_mex_destroy(&c5_m582);
  sf_mex_destroy(&c5_m583);
  sf_mex_destroy(&c5_m584);
  sf_mex_destroy(&c5_m585);
  sf_mex_destroy(&c5_m586);
  sf_mex_destroy(&c5_m587);
  chartInstance->c5_data[83] = 3704U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 105);
  sf_mex_destroy(&c5_m588);
  sf_mex_destroy(&c5_m589);
  sf_mex_destroy(&c5_m590);
  sf_mex_destroy(&c5_m591);
  sf_mex_destroy(&c5_m592);
  sf_mex_destroy(&c5_m593);
  sf_mex_destroy(&c5_m594);
  chartInstance->c5_data[84] = 1538U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 106);
  sf_mex_destroy(&c5_m595);
  sf_mex_destroy(&c5_m596);
  sf_mex_destroy(&c5_m597);
  sf_mex_destroy(&c5_m598);
  sf_mex_destroy(&c5_m599);
  sf_mex_destroy(&c5_m600);
  sf_mex_destroy(&c5_m601);
  chartInstance->c5_data[85] = 3842U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 107);
  sf_mex_destroy(&c5_m602);
  sf_mex_destroy(&c5_m603);
  sf_mex_destroy(&c5_m604);
  sf_mex_destroy(&c5_m605);
  sf_mex_destroy(&c5_m606);
  sf_mex_destroy(&c5_m607);
  sf_mex_destroy(&c5_m608);
  chartInstance->c5_data[86] = 2289U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 108);
  sf_mex_destroy(&c5_m609);
  sf_mex_destroy(&c5_m610);
  sf_mex_destroy(&c5_m611);
  sf_mex_destroy(&c5_m612);
  sf_mex_destroy(&c5_m613);
  sf_mex_destroy(&c5_m614);
  sf_mex_destroy(&c5_m615);
  chartInstance->c5_data[87] = 3648U;
  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 112);
  if (CV_EML_IF(0, 1, c5_eq(chartInstance, c5_read))) {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 113);
    c5_u0 = (uint32_T)c5_addr + 1U;
    if (c5_u0 > 255U) {
      c5_u0 = 255U;
    }

    c5_instr_out = chartInstance->c5_data[(uint8_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
      "data", (int32_T)(uint8_T)_SFD_INTEGER_CHECK("addr+1", (real_T)(uint8_T)
      c5_u0), 1, 256, 1, 0) - 1];
  } else {
    _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, 115);
    sf_mex_destroy(&c5_m616);
    sf_mex_destroy(&c5_m617);
    sf_mex_destroy(&c5_m618);
    sf_mex_destroy(&c5_m619);
    sf_mex_destroy(&c5_m620);
    sf_mex_destroy(&c5_m621);
    sf_mex_destroy(&c5_m622);
    c5_instr_out = 0U;
  }

  _SFD_EML_CALL(0U, chartInstance->c5_sfEvent, -115);
  sf_debug_symbol_scope_pop();
  *c5_b_instr_out = c5_instr_out;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c5_sfEvent);
}

static void initSimStructsc5_hdlcodercpu_eml(SFc5_hdlcodercpu_emlInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber)
{
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
    sf_mex_assign(&c5_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    for (c5_i4 = 0; c5_i4 < 256; c5_i4++) {
      c5_b_u[c5_i4] = c5_u[c5_i4];
    }

    c5_b_y = NULL;
    sf_mex_assign(&c5_b_y, sf_mex_create("y", c5_b_u, 5, 0U, 1U, 0U, 2, 1, 256));
    sf_mex_assign(&c5_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c5_eml_mx), 15, "numerictype", 14, sf_mex_dup(c5_b_eml_mx), 15,
      "simulinkarray", 14, c5_b_y, 15, "fimathislocal", 3, TRUE));
  }

  sf_mex_assign(&c5_mxArrayOutData, c5_y);
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
    chartInstance->c5_data_not_empty = FALSE;
  } else {
    chartInstance->c5_data_not_empty = TRUE;
    sf_mex_check_fi(c5_parentId, c5_u, 0, 2U, c5_uv1, c5_eml_mx, c5_b_eml_mx);
    sf_mex_assign(&c5_mxFi, sf_mex_dup(c5_u));
    sf_mex_assign(&c5_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
                   (c5_mxFi)));
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
    sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 5, 0U, 0U, 0U, 0));
    sf_mex_assign(&c5_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c5_eml_mx), 15, "numerictype", 14, sf_mex_dup(c5_b_eml_mx), 15,
      "simulinkarray", 14, c5_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c5_mxArrayOutData, c5_y);
  } else {
    sf_mex_assign(&c5_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
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
  sf_mex_check_fi(c5_parentId, c5_u, 0, 0U, 0, c5_eml_mx, c5_b_eml_mx);
  sf_mex_assign(&c5_mxFi, sf_mex_dup(c5_u));
  sf_mex_assign(&c5_mxInt, sf_mex_call("simulinkarray", 1U, 1U, 14, sf_mex_dup
    (c5_mxFi)));
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
    sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c5_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c5_eml_mx), 15, "numerictype", 14, sf_mex_dup(c5_c_eml_mx), 15,
      "simulinkarray", 14, c5_b_y, 15, "fimathislocal", 3, FALSE));
    sf_mex_assign(&c5_mxArrayOutData, c5_y);
  } else {
    sf_mex_assign(&c5_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
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
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 3, 0U, 0U, 0U, 0));
  sf_mex_assign(&c5_mxArrayOutData, c5_y);
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
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c5_mxArrayOutData, c5_y);
  return c5_mxArrayOutData;
}

static real_T c5_e_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d0;
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
  sf_mex_assign(&c5_y, sf_mex_duplicatearraysafe(&c5_u));
  sf_mex_destroy(&c5_u);
  sf_mex_assign(&c5_mxArrayOutData, c5_y);
  return c5_mxArrayOutData;
}

const mxArray *sf_c5_hdlcodercpu_eml_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo;
  c5_ResolvedFunctionInfo c5_info[16];
  const mxArray *c5_m623 = NULL;
  int32_T c5_i8;
  c5_ResolvedFunctionInfo *c5_r0;
  c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  c5_info_helper(c5_info);
  sf_mex_assign(&c5_m623, sf_mex_createstruct("nameCaptureInfo", 1, 16));
  for (c5_i8 = 0; c5_i8 < 16; c5_i8++) {
    c5_r0 = &c5_info[c5_i8];
    sf_mex_addfield(c5_m623, sf_mex_create("nameCaptureInfo", c5_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c5_r0->context)), "context", "nameCaptureInfo",
                    c5_i8);
    sf_mex_addfield(c5_m623, sf_mex_create("nameCaptureInfo", c5_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c5_r0->name)), "name", "nameCaptureInfo", c5_i8);
    sf_mex_addfield(c5_m623, sf_mex_create("nameCaptureInfo",
      c5_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c5_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c5_i8);
    sf_mex_addfield(c5_m623, sf_mex_create("nameCaptureInfo", c5_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c5_r0->resolved)), "resolved",
                    "nameCaptureInfo", c5_i8);
    sf_mex_addfield(c5_m623, sf_mex_create("nameCaptureInfo", &c5_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c5_i8);
    sf_mex_addfield(c5_m623, sf_mex_create("nameCaptureInfo", &c5_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c5_i8);
    sf_mex_addfield(c5_m623, sf_mex_create("nameCaptureInfo",
      &c5_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c5_i8);
    sf_mex_addfield(c5_m623, sf_mex_create("nameCaptureInfo",
      &c5_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c5_i8);
  }

  sf_mex_assign(&c5_nameCaptureInfo, c5_m623);
  return c5_nameCaptureInfo;
}

static void c5_info_helper(c5_ResolvedFunctionInfo c5_info[16])
{
  c5_info[0].context = "";
  c5_info[0].name = "fimath";
  c5_info[0].dominantType = "char";
  c5_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fimath.m";
  c5_info[0].fileTimeLo = 275520000U;
  c5_info[0].fileTimeHi = 30114375U;
  c5_info[0].mFileTimeLo = 0U;
  c5_info[0].mFileTimeHi = 0U;
  c5_info[1].context = "";
  c5_info[1].name = "fi_impl";
  c5_info[1].dominantType = "";
  c5_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m";
  c5_info[1].fileTimeLo = 275520000U;
  c5_info[1].fileTimeHi = 30114375U;
  c5_info[1].mFileTimeLo = 0U;
  c5_info[1].mFileTimeHi = 0U;
  c5_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c5_info[2].name = "isfi";
  c5_info[2].dominantType = "double";
  c5_info[2].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c5_info[2].fileTimeLo = 335520000U;
  c5_info[2].fileTimeHi = 30114375U;
  c5_info[2].mFileTimeLo = 0U;
  c5_info[2].mFileTimeHi = 0U;
  c5_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isfi.m";
  c5_info[3].name = "isnumerictype";
  c5_info[3].dominantType = "char";
  c5_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/isnumerictype.m";
  c5_info[3].fileTimeLo = 355520000U;
  c5_info[3].fileTimeHi = 30114375U;
  c5_info[3].mFileTimeLo = 0U;
  c5_info[3].mFileTimeHi = 0U;
  c5_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/fi_impl.m!fi_helper";
  c5_info[4].name = "eml_fi_checkforerror";
  c5_info[4].dominantType = "embedded.numerictype";
  c5_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/eml_fi_checkforerror.m";
  c5_info[4].fileTimeLo = 255520000U;
  c5_info[4].fileTimeHi = 30114375U;
  c5_info[4].mFileTimeLo = 0U;
  c5_info[4].mFileTimeHi = 0U;
  c5_info[5].context = "";
  c5_info[5].name = "eq";
  c5_info[5].dominantType = "embedded.fi";
  c5_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m";
  c5_info[5].fileTimeLo = 755520000U;
  c5_info[5].fileTimeHi = 30114375U;
  c5_info[5].mFileTimeLo = 0U;
  c5_info[5].mFileTimeHi = 0U;
  c5_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m";
  c5_info[6].name = "eml_scalexp_compatible";
  c5_info[6].dominantType = "embedded.fi";
  c5_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c5_info[6].fileTimeLo = 3244844544U;
  c5_info[6].fileTimeHi = 30108086U;
  c5_info[6].mFileTimeLo = 0U;
  c5_info[6].mFileTimeHi = 0U;
  c5_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m";
  c5_info[7].name = "isfixed";
  c5_info[7].dominantType = "embedded.fi";
  c5_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  c5_info[7].fileTimeLo = 875520000U;
  c5_info[7].fileTimeHi = 30114375U;
  c5_info[7].mFileTimeLo = 0U;
  c5_info[7].mFileTimeHi = 0U;
  c5_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/isfixed.m";
  c5_info[8].name = "get";
  c5_info[8].dominantType = "embedded.numerictype";
  c5_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@numerictype/get.m";
  c5_info[8].fileTimeLo = 4170487296U;
  c5_info[8].fileTimeHi = 30114374U;
  c5_info[8].mFileTimeLo = 0U;
  c5_info[8].mFileTimeHi = 0U;
  c5_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m";
  c5_info[9].name = "eml_type_relop_const";
  c5_info[9].dominantType = "embedded.fi";
  c5_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m";
  c5_info[9].fileTimeLo = 735520000U;
  c5_info[9].fileTimeHi = 30114375U;
  c5_info[9].mFileTimeLo = 0U;
  c5_info[9].mFileTimeHi = 0U;
  c5_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_type_relop_const.m";
  c5_info[10].name = "all";
  c5_info[10].dominantType = "logical";
  c5_info[10].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c5_info[10].fileTimeLo = 3624844544U;
  c5_info[10].fileTimeHi = 30108086U;
  c5_info[10].mFileTimeLo = 0U;
  c5_info[10].mFileTimeHi = 0U;
  c5_info[11].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m";
  c5_info[11].name = "eml_all_or_any";
  c5_info[11].dominantType = "char";
  c5_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c5_info[11].fileTimeLo = 2224844544U;
  c5_info[11].fileTimeHi = 30108086U;
  c5_info[11].mFileTimeLo = 0U;
  c5_info[11].mFileTimeHi = 0U;
  c5_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c5_info[12].name = "isequal";
  c5_info[12].dominantType = "double";
  c5_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c5_info[12].fileTimeLo = 2864844544U;
  c5_info[12].fileTimeHi = 30108086U;
  c5_info[12].mFileTimeLo = 0U;
  c5_info[12].mFileTimeHi = 0U;
  c5_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c5_info[13].name = "eml_isequal_core";
  c5_info[13].dominantType = "double";
  c5_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c5_info[13].fileTimeLo = 3144844544U;
  c5_info[13].fileTimeHi = 30108086U;
  c5_info[13].mFileTimeLo = 0U;
  c5_info[13].mFileTimeHi = 0U;
  c5_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m";
  c5_info[14].name = "eml_const_nonsingleton_dim";
  c5_info[14].dominantType = "logical";
  c5_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m";
  c5_info[14].fileTimeLo = 2244844544U;
  c5_info[14].fileTimeHi = 30108086U;
  c5_info[14].mFileTimeLo = 0U;
  c5_info[14].mFileTimeHi = 0U;
  c5_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eq.m";
  c5_info[15].name = "eml_make_same_complexity";
  c5_info[15].dominantType = "embedded.fi";
  c5_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/fixedpoint/@embedded/@fi/eml_make_same_complexity.m";
  c5_info[15].fileTimeLo = 695520000U;
  c5_info[15].fileTimeHi = 30114375U;
  c5_info[15].mFileTimeLo = 0U;
  c5_info[15].mFileTimeHi = 0U;
}

static void c5_fi_helper(SFc5_hdlcodercpu_emlInstanceStruct *chartInstance)
{
  const mxArray *c5_m624 = NULL;
  const mxArray *c5_m625 = NULL;
  const mxArray *c5_m626 = NULL;
  const mxArray *c5_m627 = NULL;
  const mxArray *c5_m628 = NULL;
  const mxArray *c5_m629 = NULL;
  const mxArray *c5_m630 = NULL;
  c5_isfi(chartInstance);
  c5_eml_fi_checkforerror(chartInstance);
  sf_mex_destroy(&c5_m624);
  sf_mex_destroy(&c5_m625);
  sf_mex_destroy(&c5_m626);
  sf_mex_destroy(&c5_m627);
  sf_mex_destroy(&c5_m628);
  sf_mex_destroy(&c5_m629);
  sf_mex_destroy(&c5_m630);
}

static void c5_isfi(SFc5_hdlcodercpu_emlInstanceStruct *chartInstance)
{
}

static void c5_eml_fi_checkforerror(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
}

static boolean_T c5_eq(SFc5_hdlcodercpu_emlInstanceStruct *chartInstance,
  uint8_T c5_a0)
{
  const mxArray *c5_m631 = NULL;
  const mxArray *c5_m632 = NULL;
  uint8_T c5_a;
  uint8_T c5_b_a0;
  uint8_T c5_a1;
  uint8_T c5_b_a1;
  sf_mex_destroy(&c5_m631);
  sf_mex_destroy(&c5_m632);
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
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0));
  sf_mex_assign(&c5_mxArrayOutData, c5_y);
  return c5_mxArrayOutData;
}

static int32_T c5_f_emlrt_marshallIn(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i9;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i9, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i9;
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
    sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_b_u, 3, 0U, 0U, 0U, 0));
    sf_mex_assign(&c5_y, sf_mex_call("embedded.fi", 1U, 8U, 15, "fimath", 14,
      sf_mex_dup(c5_eml_mx), 15, "numerictype", 14, sf_mex_dup(c5_c_eml_mx), 15,
      "simulinkarray", 14, c5_b_y, 15, "fimathislocal", 3, TRUE));
    sf_mex_assign(&c5_mxArrayOutData, c5_y);
  } else {
    sf_mex_assign(&c5_mxArrayOutData, sf_mex_create("mxArrayOutData",
      "Cannot display value.", 15, 0U, 0U, 0U, 2, 1, strlen(
      "Cannot display value.")));
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
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u2, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u2;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void init_dsm_address_info(SFc5_hdlcodercpu_emlInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c5_hdlcodercpu_eml_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4109103486U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1015235392U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(832864485U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2793977063U);
}

mxArray *sf_c5_hdlcodercpu_eml_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(3732582914U);
    pr[1] = (double)(3110280256U);
    pr[2] = (double)(2069472967U);
    pr[3] = (double)(2023862657U);
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
    chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (_hdlcodercpu_emlMachineNumber_,
           5,
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
        _SFD_CV_INIT_EML(0,1,2,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,4938);
        _SFD_CV_INIT_EML_IF(0,0,347,364,-1,416);
        _SFD_CV_INIT_EML_IF(0,1,4843,4856,4887,4936);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

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
      sf_debug_reset_current_state_configuration(_hdlcodercpu_emlMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
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
  sf_c5_hdlcodercpu_eml((SFc5_hdlcodercpu_emlInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c5_hdlcodercpu_eml(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
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
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c5_hdlcodercpu_eml();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
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
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c5_hdlcodercpu_eml((SFc5_hdlcodercpu_emlInstanceStruct*)
      chartInstanceVar);
    free((void *)chartInstanceVar);
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
    initialize_params_c5_hdlcodercpu_eml((SFc5_hdlcodercpu_emlInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c5_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"hdlcodercpu_eml","hdlcodercpu_eml",5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml","hdlcodercpu_eml",5,
                "RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"hdlcodercpu_eml",
      "hdlcodercpu_eml",5,"gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",
        5,2);
      sf_mark_chart_reusable_outputs(S,"hdlcodercpu_eml","hdlcodercpu_eml",5,1);
    }

    sf_set_rtw_dwork_info(S,"hdlcodercpu_eml","hdlcodercpu_eml",5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4238594478U));
  ssSetChecksum1(S,(4143684038U));
  ssSetChecksum2(S,(2923889644U));
  ssSetChecksum3(S,(1502332717U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c5_hdlcodercpu_eml(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "hdlcodercpu_eml", "hdlcodercpu_eml",5);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c5_hdlcodercpu_eml(SimStruct *S)
{
  SFc5_hdlcodercpu_emlInstanceStruct *chartInstance;
  chartInstance = (SFc5_hdlcodercpu_emlInstanceStruct *)malloc(sizeof
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
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
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
