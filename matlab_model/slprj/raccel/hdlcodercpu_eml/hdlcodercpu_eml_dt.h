#include "ext_types.h"

static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(uint8_T),
  sizeof(uint8_T),
  sizeof(uint16_T),
  sizeof(uint8_T),
  sizeof(uint8_T)
};

static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "uint8_T",
  "uint8_T",
  "uint16_T",
  "uint8_T",
  "uint8_T"
};

static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&rtB.UnitDelay1), 16, 0, 3 },

  { (char_T *)(&rtB.UnitDelay6), 2, 0, 267 },

  { (char_T *)(&rtB.UnitDelay4), 3, 0, 5 },

  { (char_T *)(&rtB.UnitDelay7), 8, 0, 3 },

  { (char_T *)(&rtB.UnitDelay3), 14, 0, 4 },

  { (char_T *)(&rtB.ALU_func), 15, 0, 2 },

  { (char_T *)(&rtB.DM_r_w), 17, 0, 2 },

  { (char_T *)(&rtB.shifter_sel), 18, 0, 3 }
  ,

  { (char_T *)(&rtDWork.Scope_PWORK.LoggedData), 11, 0, 2 },

  { (char_T *)(&rtDWork.sfEvent), 6, 0, 9 },

  { (char_T *)(&rtDWork.UnitDelay1_DSTATE), 16, 0, 258 },

  { (char_T *)(&rtDWork.UnitDelay6_DSTATE), 2, 0, 261 },

  { (char_T *)(&rtDWork.UnitDelay4_DSTATE), 3, 0, 1 },

  { (char_T *)(&rtDWork.UnitDelay7_DSTATE), 8, 0, 2 },

  { (char_T *)(&rtDWork.UnitDelay3_DSTATE), 14, 0, 1 },

  { (char_T *)(&rtDWork.AC_value), 2, 0, 1 },

  { (char_T *)(&rtDWork.is_active_c1_hdlcodercpu_eml), 3, 0, 16 },

  { (char_T *)(&rtDWork.isStable), 8, 0, 28 }
};

static DataTypeTransitionTable rtBTransTable = {
  18U,
  rtBTransitions
};
