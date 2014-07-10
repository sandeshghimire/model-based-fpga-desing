#include <math.h>
#include "hdlcodercpu_eml.h"
#include "hdlcodercpu_eml_private.h"
#include "hdlcodercpu_eml_dt.h"

const int_T gblNumToFiles = 0;
const int_T gblNumFrFiles = 0;
const int_T gblNumFrWksBlocks = 0;

#ifdef RSIM_WITH_SOLVER_MULTITASKING

const boolean_T gbl_raccel_isMultitasking = 1;

#else

const boolean_T gbl_raccel_isMultitasking = 0;

#endif

const boolean_T gbl_raccel_tid01eq = 0;
const int_T gbl_raccel_NumST = 1;
const char_T *gbl_raccel_Version = "8.0 (R2011a) 09-Mar-2011";
void raccel_setup_MMIStateLog(SimStruct* S)
{

#ifdef UseMMIDataLogging

  rt_FillStateSigInfoFromMMI(ssGetRTWLogInfo(S),&ssGetErrorStatus(S));

#endif

}

const char *gblSlvrJacPatternFileName =
  "slprj\\raccel\\hdlcodercpu_eml\\hdlcodercpu_eml_Jpattern.mat";
const int_T gblNumRootInportBlks = 0;
const int_T gblNumModelInputs = 0;
extern rtInportTUtable *gblInportTUtables;
extern const char *gblInportFileName;
const int_T gblInportDataTypeIdx[] = { -1 };

const int_T gblInportDims[] = { -1 } ;

const int_T gblInportComplex[] = { -1 };

const int_T gblInportInterpoFlag[] = { -1 };

const int_T gblInportContinuous[] = { -1 };

#include "simstruc.h"
#include "fixedpoint.h"

BlockIO rtB;
D_Work rtDWork;
static SimStruct model_S;
SimStruct *const rtS = &model_S;
static int16_T hdlcodercpu_eml_minus(int8_T a0);
static void hdlcodercpu_eml_sum_w_carry(int8_T u1, int8_T u2, uint8_T c_in,
  int8_T *sum, uint8_T *carry, uint8_T *overflow);
static int16_T hdlcodercpu_eml_minus(int8_T a0)
{
  int16_T tmp;
  tmp = (int16_T)(a0 << 5);
  tmp = (int16_T)(((int16_T)(tmp & 4096) != 0 ? (int16_T)(tmp | -4096) :
                   (int16_T)(tmp & 4095)) - 32);
  return (int16_T)((int16_T)(tmp & 4096) != 0 ? (int16_T)(tmp | -4096) :
                   (int16_T)(tmp & 4095));
}

static void hdlcodercpu_eml_sum_w_carry(int8_T u1, int8_T u2, uint8_T c_in,
  int8_T *sum, uint8_T *carry, uint8_T *overflow)
{
  int16_T temp_sum;
  boolean_T b;
  int16_T tmp;
  tmp = (uint8_T)u1;
  tmp = (int16_T)((tmp & 256) != 0 ? (int16_T)(tmp | -256) : tmp);
  temp_sum = (uint8_T)u2;
  temp_sum = (int16_T)((temp_sum & 256) != 0 ? (int16_T)(temp_sum | -256) :
                       temp_sum);
  tmp = (int16_T)(((int16_T)(tmp & 512) != 0 ? (int16_T)(tmp | -512) : (int16_T)
                   (tmp & 511)) + ((int16_T)(temp_sum & 512) != 0 ? (int16_T)
    (temp_sum | -512) : (int16_T)(temp_sum & 511)));
  tmp = (int16_T)((int16_T)(tmp & 512) != 0 ? (int16_T)(tmp | -512) : (int16_T)
                  (tmp & 511));
  temp_sum = c_in;
  tmp = (int16_T)(((int16_T)(tmp & 1024) != 0 ? (int16_T)(tmp | -1024) :
                   (int16_T)(tmp & 1023)) + ((temp_sum & 1024) != 0 ? (int16_T)
    (temp_sum | -1024) : temp_sum));
  tmp = (int16_T)((int16_T)(tmp & 1024) != 0 ? (int16_T)(tmp | -1024) : (int16_T)
                  (tmp & 1023));
  temp_sum = (int16_T)((int16_T)(tmp & 256) != 0 ? (int16_T)(tmp | -256) :
                       (int16_T)(tmp & 255));
  tmp = (int16_T)(int32_T)((uint32_T)((uint16_T)temp_sum & 511) >> 8);
  tmp = (int16_T)((int16_T)((tmp & 256) != 0 ? (int16_T)(tmp | -256) : tmp) & 1);
  *carry = (uint8_T)((uint8_T)(int16_T)((int16_T)(tmp & 256) != 0 ? (int16_T)
    (tmp | -256) : (int16_T)(tmp & 255)) & 1);
  *sum = (int8_T)temp_sum;
  if (((int32_T)((uint32_T)(int32_T)(uint8_T)u1 >> 7) == (int32_T)((uint32_T)
        (int32_T)(uint8_T)u2 >> 7)) && ((int32_T)((uint32_T)(int32_T)(uint8_T)
        *sum >> 7) != (int32_T)((uint32_T)(int32_T)(uint8_T)u1 >> 7))) {
    b = TRUE;
  } else {
    b = FALSE;
  }

  *overflow = b;
}

void MdlInitialize(void)
{
  int32_T i;
  rtDWork.UnitDelay6_DSTATE = 0;
  rtDWork.UnitDelay5_DSTATE = 0;
  rtDWork.UnitDelay3_DSTATE = ((uint8_T)0U);
  rtDWork.UnitDelay7_DSTATE = FALSE;
  rtDWork.UnitDelay1_DSTATE = ((uint16_T)0U);
  rtDWork.sfEvent_g = CALL_EVENT;
  rtDWork.CPU_state_not_empty = FALSE;
  rtDWork.previous_CPU_state_not_empty = FALSE;
  rtDWork.major_opcode_not_empty = FALSE;
  rtDWork.minor_opcode_not_empty = FALSE;
  rtDWork.address_data_not_empty = FALSE;
  rtDWork.indirect_address_not_empty = FALSE;
  rtDWork.is_active_c2_hdlcodercpu_eml = 0U;
  rtDWork.CPU_state = 0U;
  rtDWork.previous_CPU_state = 0U;
  rtDWork.major_opcode = 0U;
  rtDWork.minor_opcode = 0U;
  rtDWork.address_data = 0U;
  rtDWork.indirect_address = 0U;
  rtDWork.UnitDelay2_DSTATE = 0;
  rtDWork.sfEvent_j = CALL_EVENT;
  rtDWork.AC_value_not_empty = FALSE;
  rtDWork.is_active_c3_hdlcodercpu_eml = 0U;
  rtDWork.AC_value = 0;
  rtDWork.din_d_DSTATE = 0;
  rtDWork.we_d_DSTATE = FALSE;
  rtDWork.ram_data_DSTATE = 0;
  rtDWork.sfEvent_n = CALL_EVENT;
  rtDWork.is_active_c4_hdlcodercpu_eml = 0U;
  rtDWork.UnitDelay4_DSTATE = ((uint8_T)0U);
  rtDWork.sfEvent_e = CALL_EVENT;
  rtDWork.is_active_c9_hdlcodercpu_eml = 0U;
  rtDWork.sfEvent_kd = CALL_EVENT;
  rtDWork.PC_value_not_empty = FALSE;
  rtDWork.is_active_c7_hdlcodercpu_eml = 0U;
  rtDWork.PC_value = 0U;
  rtDWork.sfEvent_p = CALL_EVENT;
  rtDWork.data_not_empty = FALSE;
  rtDWork.is_active_c5_hdlcodercpu_eml = 0U;
  for (i = 0; i < 256; i++) {
    rtDWork.ram_DSTATE[i] = 0;
    rtDWork.data[i] = 0U;
  }

  rtDWork.sfEvent_c = CALL_EVENT;
  rtDWork.IR_value_not_empty = FALSE;
  rtDWork.is_active_c6_hdlcodercpu_eml = 0U;
  rtDWork.IR_value = 0U;
  rtDWork.sfEvent_k = CALL_EVENT;
  rtDWork.is_active_c8_hdlcodercpu_eml = 0U;
  rtDWork.sfEvent = CALL_EVENT;
  rtDWork.is_active_c1_hdlcodercpu_eml = 0U;
}

void MdlStart(void)
{
  MdlInitialize();
}

void MdlOutputs(int_T tid)
{
  uint8_T carry;
  uint8_T overflow;
  int8_T diff;
  uint8_T c_out;
  uint16_T rtb_convert;
  int8_T rtb_wr_port[256];
  int32_T i;
  int16_T tmp;
  int16_T tmp_0;
  rtB.UnitDelay6 = rtDWork.UnitDelay6_DSTATE;
  rtB.feedbackforindirectaddressing = rtDWork.UnitDelay5_DSTATE;
  rtB.UnitDelay3 = rtDWork.UnitDelay3_DSTATE;
  rtB.UnitDelay7 = rtDWork.UnitDelay7_DSTATE;
  rtB.UnitDelay1 = rtDWork.UnitDelay1_DSTATE;
  rtDWork.sfEvent_g = CALL_EVENT;
  rtDWork.CPU_state_not_empty = TRUE;
  rtDWork.previous_CPU_state_not_empty = TRUE;
  if (rtB.UnitDelay7) {
    rtDWork.CPU_state = 0U;
  }

  rtB.shifter_sel = 0U;
  rtB.ALU_func = 0U;
  rtB.out_flags_n = rtB.UnitDelay3;
  rtB.AC_func = 4U;
  rtB.AC_data = 0;
  rtB.IR_func = 3U;
  rtB.PC_func = 3U;
  rtB.IM_read = 0U;
  rtB.DM_addr = 0U;
  rtB.DM_r_w = 0U;
  rtB.addr_inc = 0;
  rtB.print_data = FALSE;
  rtB.hlt = 0U;
  rtDWork.major_opcode_not_empty = TRUE;
  rtDWork.minor_opcode_not_empty = TRUE;
  rtDWork.address_data_not_empty = TRUE;
  rtDWork.indirect_address_not_empty = TRUE;
  switch (rtDWork.CPU_state) {
   case 0U:
    rtB.PC_func = 0U;
    rtB.AC_func = 0U;
    rtB.IR_func = 0U;
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    rtDWork.CPU_state = 1U;
    break;

   case 1U:
    rtB.IM_read = 1U;
    rtB.PC_func = 2U;
    rtB.IR_func = 1U;
    rtDWork.CPU_state = 2U;
    break;

   case 2U:
    rtB.IR_func = 2U;
    rtDWork.CPU_state = 3U;
    break;

   case 3U:
    rtDWork.major_opcode = (uint8_T)(int32_T)((uint32_T)(int32_T)rtB.UnitDelay1 >>
      9);
    rtDWork.minor_opcode = (uint8_T)((int32_T)((uint32_T)(int32_T)rtB.UnitDelay1
      >> 3) & 63);
    rtDWork.address_data = (uint8_T)(rtB.UnitDelay1 & 255);
    rtDWork.CPU_state = 4U;
    break;

   case 4U:
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    switch (rtDWork.major_opcode) {
     case 0U:
      rtB.DM_addr = rtDWork.address_data;
      rtDWork.CPU_state = 13U;
      break;

     case 1U:
      rtB.DM_addr = rtDWork.address_data;
      rtDWork.CPU_state = 15U;
      break;

     case 2U:
      rtB.DM_addr = rtDWork.address_data;
      rtDWork.CPU_state = 17U;
      break;

     case 3U:
      rtB.DM_addr = rtDWork.address_data;
      rtDWork.CPU_state = 19U;
      break;

     case 4U:
      switch ((uint8_T)((int32_T)((uint32_T)(int32_T)rtDWork.minor_opcode >> 5)
                        & 1)) {
       case 0U:
        diff = (int8_T)rtDWork.address_data;
        tmp_0 = (int16_T)(((int8_T)(diff & 64) != 0 ? (int8_T)(diff | -64) :
                           (int8_T)(diff & 63)) << 5);
        tmp_0 = (int16_T)(((int16_T)(tmp_0 & 4096) != 0 ? (int16_T)(tmp_0 |
          -4096) : (int16_T)(tmp_0 & 4095)) - 32);
        rtB.addr_inc = (int8_T)(int16_T)(((int16_T)(tmp_0 & 4096) != 0 ?
          (int16_T)(tmp_0 | -4096) : (int16_T)(tmp_0 & 4095)) >> 5);
        rtB.PC_func = 1U;
        break;

       case 1U:
        rtB.AC_data = (int8_T)rtDWork.address_data;
        rtB.AC_func = 1U;
        break;
      }

      rtDWork.CPU_state = 1U;
      break;

     case 5U:
      rtB.DM_addr = rtDWork.address_data;
      if (((int32_T)((uint32_T)(int32_T)rtDWork.minor_opcode >> 5) & 1) != 0) {
        rtDWork.CPU_state = 21U;
      } else {
        rtB.DM_r_w = 1U;
        rtDWork.CPU_state = 25U;
      }
      break;

     case 6U:
      switch ((uint8_T)((int32_T)((uint32_T)(int32_T)rtDWork.minor_opcode >> 5)
                        & 1)) {
       case 0U:
        if (((int32_T)((uint32_T)(int32_T)rtB.UnitDelay3 >> 3) & 1) != 0) {
          diff = (int8_T)rtDWork.address_data;
          tmp_0 = (int16_T)(((int8_T)(diff & 64) != 0 ? (int8_T)(diff | -64) :
                             (int8_T)(diff & 63)) << 5);
          tmp_0 = (int16_T)(((int16_T)(tmp_0 & 4096) != 0 ? (int16_T)(tmp_0 |
            -4096) : (int16_T)(tmp_0 & 4095)) - 32);
          rtB.addr_inc = (int8_T)(int16_T)(((int16_T)(tmp_0 & 4096) != 0 ?
            (int16_T)(tmp_0 | -4096) : (int16_T)(tmp_0 & 4095)) >> 5);
          rtB.PC_func = 1U;
        }
        break;

       case 1U:
        if (((int32_T)((uint32_T)(int32_T)rtB.UnitDelay3 >> 2) & 1) != 0) {
          diff = (int8_T)rtDWork.address_data;
          rtB.addr_inc = (int8_T)(int16_T)(hdlcodercpu_eml_minus((int8_T)
            ((int8_T)(diff & 64) != 0 ? (int8_T)(diff | -64) : (int8_T)(diff &
            63))) >> 5);
          rtB.PC_func = 1U;
        }
        break;
      }

      rtDWork.CPU_state = 15U;
      break;

     case 7U:
      rtDWork.CPU_state = 1U;
      if ((((int32_T)((uint32_T)(int32_T)rtDWork.minor_opcode >> 3) & 1) != 0) ==
          0) {
        switch ((uint8_T)((int32_T)((uint32_T)(int32_T)rtDWork.minor_opcode >> 5)
                          & 1)) {
         case 0U:
          if (((int32_T)((uint32_T)(int32_T)rtB.UnitDelay3 >> 1) & 1) != 0) {
            diff = (int8_T)rtDWork.address_data;
            rtB.addr_inc = (int8_T)(int16_T)(hdlcodercpu_eml_minus((int8_T)
              ((int8_T)(diff & 64) != 0 ? (int8_T)(diff | -64) : (int8_T)(diff &
              63))) >> 5);
            rtB.PC_func = 1U;
          }
          break;

         case 1U:
          if ((rtB.UnitDelay3 & 1) != 0) {
            diff = (int8_T)rtDWork.address_data;
            rtB.addr_inc = (int8_T)(int16_T)(hdlcodercpu_eml_minus((int8_T)
              ((int8_T)(diff & 64) != 0 ? (int8_T)(diff | -64) : (int8_T)(diff &
              63))) >> 5);
            rtB.PC_func = 1U;
          }
          break;
        }
      }

      switch (rtDWork.minor_opcode) {
       case 8U:
        rtB.hlt = 1U;
        rtDWork.CPU_state = 22U;
        break;

       case 9U:
        rtB.AC_func = 0U;
        break;

       case 10U:
        rtB.ALU_func = 4U;
        rtB.shifter_sel = 3U;
        rtDWork.CPU_state = 6U;
        break;

       case 11U:
        rtB.ALU_func = 5U;
        rtB.shifter_sel = 3U;
        break;

       case 12U:
        rtB.shifter_sel = 1U;
        rtDWork.CPU_state = 6U;
        break;

       case 13U:
        rtB.shifter_sel = 2U;
        rtDWork.CPU_state = 6U;
        break;

       case 14U:
        rtB.DM_addr = MAX_uint8_T;
        rtDWork.CPU_state = 12U;
        break;

       case 15U:
        rtB.ALU_func = 7U;
        rtB.shifter_sel = 3U;
        break;
      }
      break;
    }
    break;

   case 6U:
    rtB.AC_func = 2U;
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    rtDWork.CPU_state = 1U;
    break;

   case 7U:
    rtB.DM_addr = rtDWork.indirect_address;
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    rtDWork.CPU_state = 13U;
    break;

   case 8U:
    rtB.DM_addr = rtDWork.indirect_address;
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    rtDWork.CPU_state = 15U;
    break;

   case 9U:
    rtB.DM_addr = rtDWork.indirect_address;
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    rtDWork.CPU_state = 17U;
    break;

   case 10U:
    rtB.DM_addr = rtDWork.indirect_address;
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    rtDWork.CPU_state = 19U;
    break;

   case 11U:
    diff = rtB.feedbackforindirectaddressing;
    if (rtB.feedbackforindirectaddressing <= 0) {
      diff = 0;
    }

    rtB.DM_addr = (uint8_T)diff;
    rtB.DM_r_w = 1U;
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    rtDWork.CPU_state = 1U;
    break;

   case 12U:
    rtB.print_data = TRUE;
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    rtDWork.CPU_state = 1U;
    break;

   case 13U:
    rtB.ALU_func = 6U;
    rtB.shifter_sel = 3U;
    if (rtDWork.previous_CPU_state == 4) {
      rtDWork.previous_CPU_state = rtDWork.CPU_state;
      rtDWork.CPU_state = 14U;
    } else {
      rtDWork.previous_CPU_state = rtDWork.CPU_state;
      rtDWork.CPU_state = 6U;
    }
    break;

   case 14U:
    rtB.AC_func = 2U;
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    if (((int32_T)((uint32_T)(int32_T)rtDWork.minor_opcode >> 5) & 1) != 0) {
      diff = rtB.feedbackforindirectaddressing;
      if (rtB.feedbackforindirectaddressing <= 0) {
        diff = 0;
      }

      rtDWork.indirect_address = (uint8_T)diff;
      rtDWork.CPU_state = 7U;
    } else {
      rtDWork.CPU_state = 25U;
    }
    break;

   case 15U:
    rtB.ALU_func = 1U;
    rtB.shifter_sel = 3U;
    if (rtDWork.previous_CPU_state == 4) {
      rtDWork.previous_CPU_state = rtDWork.CPU_state;
      rtDWork.CPU_state = 16U;
    } else {
      rtDWork.previous_CPU_state = rtDWork.CPU_state;
      rtDWork.CPU_state = 6U;
    }
    break;

   case 16U:
    rtB.AC_func = 2U;
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    if (((int32_T)((uint32_T)(int32_T)rtDWork.minor_opcode >> 5) & 1) != 0) {
      diff = rtB.feedbackforindirectaddressing;
      if (rtB.feedbackforindirectaddressing <= 0) {
        diff = 0;
      }

      rtDWork.indirect_address = (uint8_T)diff;
      rtDWork.CPU_state = 8U;
    } else {
      rtDWork.CPU_state = 25U;
    }
    break;

   case 17U:
    rtB.ALU_func = 2U;
    rtB.shifter_sel = 3U;
    if (rtDWork.previous_CPU_state == 4) {
      rtDWork.previous_CPU_state = rtDWork.CPU_state;
      rtDWork.CPU_state = 18U;
    } else {
      rtDWork.previous_CPU_state = rtDWork.CPU_state;
      rtDWork.CPU_state = 6U;
    }
    break;

   case 18U:
    rtB.AC_func = 2U;
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    if (((int32_T)((uint32_T)(int32_T)rtDWork.minor_opcode >> 5) & 1) != 0) {
      diff = rtB.feedbackforindirectaddressing;
      if (rtB.feedbackforindirectaddressing <= 0) {
        diff = 0;
      }

      rtDWork.indirect_address = (uint8_T)diff;
      rtDWork.CPU_state = 9U;
    } else {
      rtDWork.CPU_state = 25U;
    }
    break;

   case 19U:
    rtB.ALU_func = 3U;
    rtB.shifter_sel = 3U;
    if (rtDWork.previous_CPU_state == 4) {
      rtDWork.previous_CPU_state = rtDWork.CPU_state;
      rtDWork.CPU_state = 20U;
    } else {
      rtDWork.previous_CPU_state = rtDWork.CPU_state;
      rtDWork.CPU_state = 6U;
    }
    break;

   case 20U:
    rtB.AC_func = 2U;
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    if (((int32_T)((uint32_T)(int32_T)rtDWork.minor_opcode >> 5) & 1) != 0) {
      diff = rtB.feedbackforindirectaddressing;
      if (rtB.feedbackforindirectaddressing <= 0) {
        diff = 0;
      }

      rtDWork.indirect_address = (uint8_T)diff;
      rtDWork.CPU_state = 10U;
    } else {
      rtDWork.CPU_state = 25U;
    }
    break;

   case 21U:
    rtDWork.CPU_state = 11U;
    break;

   case 22U:
    rtB.hlt = 1U;
    rtDWork.CPU_state = 22U;
    break;

   default:
    rtDWork.previous_CPU_state = rtDWork.CPU_state;
    rtDWork.CPU_state = 1U;
    break;
  }

  if (rtB.hlt != 0) {
    ssSetStopRequested(rtS, 1);
  }

  rtB.UnitDelay2 = rtDWork.UnitDelay2_DSTATE;
  rtDWork.sfEvent_j = CALL_EVENT;
  rtDWork.AC_value_not_empty = TRUE;
  rtB.AC_out = rtDWork.AC_value;
  switch (rtB.AC_func) {
   case 0U:
    rtDWork.AC_value = 0;
    break;

   case 1U:
    rtDWork.AC_value = rtB.AC_data;
    break;

   case 2U:
    rtDWork.AC_value = rtB.UnitDelay2;
    break;

   case 3U:
    break;
  }

  if (rtDWork.we_d_DSTATE && rtrtC.Compare) {
    rtB.Switch1 = rtDWork.din_d_DSTATE;
  } else {
    rtB.Switch1 = rtDWork.ram_data_DSTATE;
  }

  rtDWork.sfEvent_n = CALL_EVENT;
  carry = (uint8_T)((int32_T)((uint32_T)(int32_T)rtB.out_flags_n >> 3) & 1);
  overflow = (uint8_T)((int32_T)((uint32_T)(int32_T)rtB.out_flags_n >> 1) & 1);
  diff = rtB.AC_out;
  switch (rtB.ALU_func) {
   case 0U:
    break;

   case 1U:
    diff = (int8_T)(rtB.Switch1 & rtB.AC_out);
    break;

   case 2U:
    hdlcodercpu_eml_sum_w_carry(rtB.AC_out, rtB.Switch1, carry, &diff, &c_out,
      &overflow);
    carry = c_out;
    break;

   case 3U:
    hdlcodercpu_eml_sum_w_carry(rtB.AC_out, (int8_T)~rtB.Switch1, (uint8_T)
      ((uint8_T)~carry & 1), &diff, &c_out, &overflow);
    carry = c_out;
    break;

   case 4U:
    diff = (int8_T)~rtB.AC_out;
    break;

   case 5U:
    carry = (uint8_T)((uint8_T)~carry & 1);
    break;

   case 6U:
    diff = rtB.Switch1;
    break;

   case 7U:
    carry = 0U;
    break;
  }

  rtB.out_flags_m = (uint8_T)(((((((carry & 3) << 1 & 3) | (int32_T)((uint32_T)
    (int32_T)(uint8_T)diff >> 7)) & 3) << 1 | (overflow & 7)) & 7) << 1 | !(diff
    != 0));
  rtB.alu_out = diff;
  rtb_convert = rtB.DM_addr;
  rtB.select = rtDWork.ram_DSTATE[rtb_convert];
  memcpy((void *)&rtb_wr_port[0], (void *)rtDWork.ram_DSTATE, sizeof(int8_T) <<
         8U);
  rtb_wr_port[rtb_convert] = rtB.AC_out;
  rtB.DataTypeConversion = ((rtB.DM_r_w != 0));
  for (i = 0; i < 256; i++) {
    if (rtB.DataTypeConversion) {
      rtB.switch_a[i] = rtb_wr_port[i];
    } else {
      rtB.switch_a[i] = rtDWork.ram_DSTATE[i];
    }
  }

  rtB.UnitDelay4 = rtDWork.UnitDelay4_DSTATE;
  rtDWork.sfEvent_e = CALL_EVENT;
  tmp_0 = rtB.addr_inc;
  tmp = rtB.UnitDelay4;
  tmp_0 = (int16_T)(((int16_T)(tmp_0 & 256) != 0 ? (int16_T)(tmp_0 | -256) :
                     (int16_T)(tmp_0 & 255)) + ((tmp & 256) != 0 ? (int16_T)(tmp
    | -256) : tmp));
  rtB.PC_next = (uint8_T)(int16_T)((int16_T)(tmp_0 & 256) != 0 ? (int16_T)(tmp_0
    | -256) : (int16_T)(tmp_0 & 255));
  rtDWork.sfEvent_kd = CALL_EVENT;
  rtDWork.PC_value_not_empty = TRUE;
  rtB.addr_out = rtDWork.PC_value;
  switch (rtB.PC_func) {
   case 0U:
    rtDWork.PC_value = 0U;
    break;

   case 1U:
    rtDWork.PC_value = rtB.PC_next;
    break;

   case 2U:
    rtDWork.PC_value = (uint8_T)(uint16_T)((int32_T)((uint32_T)(rtDWork.PC_value
      << 7) + 128U) >> 7);
    break;
  }

  rtDWork.sfEvent_p = CALL_EVENT;
  rtDWork.data_not_empty = TRUE;
  rtDWork.data[0] = 2314U;
  rtDWork.data[1] = 2560U;
  rtDWork.data[2] = 2316U;
  rtDWork.data[3] = 2561U;
  rtDWork.data[4] = 2322U;
  rtDWork.data[5] = 2572U;
  rtDWork.data[6] = 2310U;
  rtDWork.data[7] = 2573U;
  rtDWork.data[8] = 2323U;
  rtDWork.data[9] = 2574U;
  rtDWork.data[10] = 2555U;
  rtDWork.data[11] = 2575U;
  rtDWork.data[12] = 2319U;
  rtDWork.data[13] = 2576U;
  rtDWork.data[14] = 2558U;
  rtDWork.data[15] = 2577U;
  rtDWork.data[16] = 2306U;
  rtDWork.data[17] = 2578U;
  rtDWork.data[18] = 2315U;
  rtDWork.data[19] = 2579U;
  rtDWork.data[20] = 2324U;
  rtDWork.data[21] = 2580U;
  rtDWork.data[22] = 2314U;
  rtDWork.data[23] = 2581U;
  rtDWork.data[24] = 2305U;
  rtDWork.data[25] = 2562U;
  rtDWork.data[26] = 2305U;
  rtDWork.data[27] = 2563U;
  rtDWork.data[28] = 2305U;
  rtDWork.data[29] = 2564U;
  rtDWork.data[30] = 2U;
  rtDWork.data[31] = 3704U;
  rtDWork.data[32] = 1540U;
  rtDWork.data[33] = 3704U;
  rtDWork.data[34] = 1025U;
  rtDWork.data[35] = 2565U;
  rtDWork.data[36] = 261U;
  rtDWork.data[37] = 2566U;
  rtDWork.data[38] = 2U;
  rtDWork.data[39] = 3704U;
  rtDWork.data[40] = 1025U;
  rtDWork.data[41] = 2567U;
  rtDWork.data[42] = 263U;
  rtDWork.data[43] = 3704U;
  rtDWork.data[44] = 1542U;
  rtDWork.data[45] = 3330U;
  rtDWork.data[46] = 2055U;
  rtDWork.data[47] = 2304U;
  rtDWork.data[48] = 2563U;
  rtDWork.data[49] = 263U;
  rtDWork.data[50] = 2821U;
  rtDWork.data[51] = 6U;
  rtDWork.data[52] = 2823U;
  rtDWork.data[53] = 2305U;
  rtDWork.data[54] = 3704U;
  rtDWork.data[55] = 1026U;
  rtDWork.data[56] = 2562U;
  rtDWork.data[57] = 0U;
  rtDWork.data[58] = 3704U;
  rtDWork.data[59] = 1538U;
  rtDWork.data[60] = 3842U;
  rtDWork.data[61] = 2271U;
  rtDWork.data[62] = 2305U;
  rtDWork.data[63] = 2564U;
  rtDWork.data[64] = 3U;
  rtDWork.data[65] = 3704U;
  rtDWork.data[66] = 1540U;
  rtDWork.data[67] = 3842U;
  rtDWork.data[68] = 2260U;
  rtDWork.data[69] = 2304U;
  rtDWork.data[70] = 2562U;
  rtDWork.data[71] = 257U;
  rtDWork.data[72] = 2815U;
  rtDWork.data[73] = 3696U;
  rtDWork.data[74] = 2305U;
  rtDWork.data[75] = 3704U;
  rtDWork.data[76] = 1025U;
  rtDWork.data[77] = 2561U;
  rtDWork.data[78] = 2305U;
  rtDWork.data[79] = 3704U;
  rtDWork.data[80] = 1026U;
  rtDWork.data[81] = 2562U;
  rtDWork.data[82] = 0U;
  rtDWork.data[83] = 3704U;
  rtDWork.data[84] = 1538U;
  rtDWork.data[85] = 3842U;
  rtDWork.data[86] = 2289U;
  rtDWork.data[87] = 3648U;
  if (rtB.IM_read == 1) {
    i = (int32_T)((uint32_T)rtB.addr_out + 1U);
    if ((uint32_T)i > 255U) {
      i = 255;
    }

    rtB.instr_out = rtDWork.data[i - 1];
  } else {
    rtB.instr_out = 0U;
  }

  rtDWork.sfEvent_c = CALL_EVENT;
  rtDWork.IR_value_not_empty = TRUE;
  rtB.IR_out = 0U;
  switch (rtB.IR_func) {
   case 0U:
    rtDWork.IR_value = 0U;
    break;

   case 1U:
    rtDWork.IR_value = rtB.instr_out;
    break;

   case 2U:
    rtB.IR_out = rtDWork.IR_value;
    break;
  }

  rtDWork.sfEvent_k = CALL_EVENT;
  overflow = (uint8_T)((int32_T)((uint32_T)(int32_T)rtB.out_flags_m >> 1) & 1);
  c_out = (uint8_T)((int32_T)((uint32_T)(int32_T)rtB.out_flags_m >> 3) & 1);
  switch (rtB.shifter_sel) {
   case 1U:
    diff = (int8_T)(rtB.alu_out << 1);
    c_out = (uint8_T)(int32_T)((uint32_T)(int32_T)(uint8_T)rtB.alu_out >> 7);
    overflow = (uint8_T)(((int32_T)((uint32_T)(int32_T)(uint8_T)rtB.alu_out >> 6)
                          & 1) ^ (int32_T)((uint32_T)(int32_T)(uint8_T)
      rtB.alu_out >> 7));
    break;

   case 2U:
    diff = (int8_T)(rtB.alu_out >> 1);
    break;

   default:
    diff = rtB.alu_out;
    break;
  }

  rtB.out_flags = (uint8_T)(((c_out << 1 | (int32_T)((uint32_T)(int32_T)(uint8_T)
    diff >> 7)) << 1 | overflow) << 1 | !(diff != 0));
  rtB.shift_out = diff;
  rtDWork.sfEvent = CALL_EVENT;
  rtB.y = 0;
  if (rtB.print_data) {
    rtB.y = rtB.Switch1;
  }

  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  rtDWork.UnitDelay6_DSTATE = rtB.y;
  rtDWork.UnitDelay5_DSTATE = rtB.Switch1;
  rtDWork.UnitDelay3_DSTATE = rtB.out_flags;
  rtDWork.UnitDelay7_DSTATE = FALSE;
  rtDWork.UnitDelay1_DSTATE = rtB.IR_out;
  rtDWork.UnitDelay2_DSTATE = rtB.shift_out;
  rtDWork.din_d_DSTATE = rtB.AC_out;
  rtDWork.we_d_DSTATE = rtB.DataTypeConversion;
  rtDWork.ram_data_DSTATE = rtB.select;
  memcpy((void *)rtDWork.ram_DSTATE, (void *)(&rtB.switch_a[0]), sizeof(int8_T) <<
         8U);
  rtDWork.UnitDelay4_DSTATE = rtB.addr_out;
  UNUSED_PARAMETER(tid);
}

void MdlInitSystemMatrices(void)
{
}

void MdlTerminate(void)
{
}

void MdlInitializeSizes(void)
{
  ssSetNumContStates(rtS, 0);
  ssSetNumY(rtS, 0);
  ssSetNumU(rtS, 0);
  ssSetDirectFeedThrough(rtS, 0);
  ssSetNumSampleTimes(rtS, 1);
  ssSetNumBlocks(rtS, 44);
  ssSetNumBlockIO(rtS, 34);
}

void MdlInitializeSampleTimes(void)
{
  ssSetSampleTime(rtS, 0, 1.0);
  ssSetOffsetTime(rtS, 0, 0.0);
}

void raccel_set_checksum(SimStruct *rtS)
{
  ssSetChecksumVal(rtS, 0, 1098889608U);
  ssSetChecksumVal(rtS, 1, 305082574U);
  ssSetChecksumVal(rtS, 2, 2258326502U);
  ssSetChecksumVal(rtS, 3, 3694173767U);
}

SimStruct * raccel_register_model(void)
{
  static struct _ssMdlInfo mdlInfo;
  (void) memset((char *)rtS, 0,
                sizeof(SimStruct));
  (void) memset((char *)&mdlInfo, 0,
                sizeof(struct _ssMdlInfo));
  ssSetMdlInfoPtr(rtS, &mdlInfo);

  {
    static time_T mdlPeriod[NSAMPLE_TIMES];
    static time_T mdlOffset[NSAMPLE_TIMES];
    static time_T mdlTaskTimes[NSAMPLE_TIMES];
    static int_T mdlTsMap[NSAMPLE_TIMES];
    static int_T mdlSampleHits[NSAMPLE_TIMES];
    static boolean_T mdlTNextWasAdjustedPtr[NSAMPLE_TIMES];
    static int_T mdlPerTaskSampleHits[NSAMPLE_TIMES * NSAMPLE_TIMES];
    static time_T mdlTimeOfNextSampleHit[NSAMPLE_TIMES];

    {
      int_T i;
      for (i = 0; i < NSAMPLE_TIMES; i++) {
        mdlPeriod[i] = 0.0;
        mdlOffset[i] = 0.0;
        mdlTaskTimes[i] = 0.0;
        mdlTsMap[i] = i;
        mdlSampleHits[i] = 1;
      }
    }

    ssSetSampleTimePtr(rtS, &mdlPeriod[0]);
    ssSetOffsetTimePtr(rtS, &mdlOffset[0]);
    ssSetSampleTimeTaskIDPtr(rtS, &mdlTsMap[0]);
    ssSetTPtr(rtS, &mdlTaskTimes[0]);
    ssSetSampleHitPtr(rtS, &mdlSampleHits[0]);
    ssSetTNextWasAdjustedPtr(rtS, &mdlTNextWasAdjustedPtr[0]);
    ssSetPerTaskSampleHitsPtr(rtS, &mdlPerTaskSampleHits[0]);
    ssSetTimeOfNextSampleHitPtr(rtS, &mdlTimeOfNextSampleHit[0]);
  }

  ssSetSolverMode(rtS, SOLVER_MODE_SINGLETASKING);

  {
    ssSetBlockIO(rtS, ((void *) &rtB));
    (void) memset(((void *) &rtB), 0,
                  sizeof(BlockIO));
  }

  {
    void *dwork = (void *) &rtDWork;
    ssSetRootDWork(rtS, dwork);
    (void) memset(dwork, 0,
                  sizeof(D_Work));
  }

  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    ssSetModelMappingInfo(rtS, &dtInfo);
    dtInfo.numDataTypes = 19;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];
    dtInfo.B = &rtBTransTable;
  }

  ssSetRootSS(rtS, rtS);
  ssSetVersion(rtS, SIMSTRUCT_VERSION_LEVEL2);
  ssSetModelName(rtS, "hdlcodercpu_eml");
  ssSetPath(rtS, "hdlcodercpu_eml");
  ssSetTStart(rtS, 0.0);
  ssSetTFinal(rtS, 1.0E+7);
  ssSetStepSize(rtS, 1.0);
  ssSetFixedStepSize(rtS, 1.0);

  {
    static RTWLogInfo rt_DataLoggingInfo;
    ssSetRTWLogInfo(rtS, &rt_DataLoggingInfo);
  }

  {
    rtliSetLogXSignalInfo(ssGetRTWLogInfo(rtS), (NULL));
    rtliSetLogXSignalPtrs(ssGetRTWLogInfo(rtS), (NULL));
    rtliSetLogT(ssGetRTWLogInfo(rtS), "tout");
    rtliSetLogX(ssGetRTWLogInfo(rtS), "");
    rtliSetLogXFinal(ssGetRTWLogInfo(rtS), "");
    rtliSetSigLog(ssGetRTWLogInfo(rtS), "");
    rtliSetLogVarNameModifier(ssGetRTWLogInfo(rtS), "none");
    rtliSetLogFormat(ssGetRTWLogInfo(rtS), 0);
    rtliSetLogMaxRows(ssGetRTWLogInfo(rtS), 1000);
    rtliSetLogDecimation(ssGetRTWLogInfo(rtS), 1);
    rtliSetLogY(ssGetRTWLogInfo(rtS), "");
    rtliSetLogYSignalInfo(ssGetRTWLogInfo(rtS), (NULL));
    rtliSetLogYSignalPtrs(ssGetRTWLogInfo(rtS), (NULL));
  }

  {
    static ssSolverInfo slvrInfo;
    ssSetSolverInfo(rtS, &slvrInfo);
    ssSetSolverName(rtS, "FixedStepDiscrete");
    ssSetVariableStepSolver(rtS, 0);
    ssSetSolverConsistencyChecking(rtS, 0);
    ssSetSolverAdaptiveZcDetection(rtS, 0);
    ssSetSolverRobustResetMethod(rtS, 0);
    ssSetSolverStateProjection(rtS, 0);
    ssSetSolverMassMatrixType(rtS, (ssMatrixType)0);
    ssSetSolverMassMatrixNzMax(rtS, 0);
    ssSetModelOutputs(rtS, MdlOutputs);
    ssSetModelLogData(rtS, rt_UpdateTXYLogVars);
    ssSetModelUpdate(rtS, MdlUpdate);
    ssSetTNextTid(rtS, INT_MIN);
    ssSetTNext(rtS, rtMinusInf);
    ssSetSolverNeedsReset(rtS);
    ssSetNumNonsampledZCs(rtS, 0);
  }

  ssSetChecksumVal(rtS, 0, 1098889608U);
  ssSetChecksumVal(rtS, 1, 305082574U);
  ssSetChecksumVal(rtS, 2, 2258326502U);
  ssSetChecksumVal(rtS, 3, 3694173767U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[10];
    ssSetRTWExtModeInfo(rtS, &rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = &rtAlwaysEnabled;
    systemRan[7] = &rtAlwaysEnabled;
    systemRan[8] = &rtAlwaysEnabled;
    systemRan[9] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(ssGetRTWExtModeInfo(rtS), &ssGetModelMappingInfo
      (rtS));
    rteiSetChecksumsPtr(ssGetRTWExtModeInfo(rtS), ssGetChecksums(rtS));
    rteiSetTPtr(ssGetRTWExtModeInfo(rtS), ssGetTPtr(rtS));
  }

  return rtS;
}
