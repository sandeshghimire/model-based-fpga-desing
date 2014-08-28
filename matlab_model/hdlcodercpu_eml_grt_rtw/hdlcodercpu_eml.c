/*
 * hdlcodercpu_eml.c
 *
 * Code generation for model "hdlcodercpu_eml".
 *
 * Model version              : 1.558
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Sun Aug 24 14:18:00 2014
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ASIC/FPGA->ASIC/FPGA
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "hdlcodercpu_eml.h"
#include "hdlcodercpu_eml_private.h"

/* Block signals (auto storage) */
B_hdlcodercpu_eml_T hdlcodercpu_eml_B;

/* Block states (auto storage) */
DW_hdlcodercpu_eml_T hdlcodercpu_eml_DW;

/* Real-time model */
RT_MODEL_hdlcodercpu_eml_T hdlcodercpu_eml_M_;
RT_MODEL_hdlcodercpu_eml_T *const hdlcodercpu_eml_M = &hdlcodercpu_eml_M_;

/* Forward declaration for local functions */
static int8_T hdlcodercpu_eml_minus(int8_T a0);
static void hdlcodercpu_eml_sum_w_carry(int8_T u1, int8_T u2, uint8_T c_in,
  int8_T *sum, uint8_T *carry, uint8_T *overflow);

/* Function for MATLAB Function: '<S1>/Control Unit' */
static int8_T hdlcodercpu_eml_minus(int8_T a0)
{
  return (int8_T)(a0 - 1);
}

/*
 * Function for MATLAB Function: '<S1>/Arithmetic Logical Unit (8-bit)'
 * function [sum, carry, overflow] = sum_w_carry(u1, u2, c_in)
 */
static void hdlcodercpu_eml_sum_w_carry(int8_T u1, int8_T u2, uint8_T c_in,
  int8_T *sum, uint8_T *carry, uint8_T *overflow)
{
  int16_T temp_sum;
  int16_T tmp;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* % Full Adder with flag register appropriately set */
  /*  sum = u1 + u2 + c_in */
  /*  appropriately set the carry and the overflow */
  /* '<S4>:1:79' hdl_fm = fimath(... */
  /* '<S4>:1:80' 'RoundMode', 'floor',... */
  /* '<S4>:1:81' 'OverflowMode', 'wrap',... */
  /* '<S4>:1:82' 'ProductMode', 'FullPrecision', 'ProductWordLength', 32,... */
  /* '<S4>:1:83' 'SumMode', 'FullPrecision', 'SumWordLength', 32,... */
  /* '<S4>:1:84' 'CastBeforeSum', true); */
  /*  zero-extend u1 by 1 bit for carry detection */
  /* '<S4>:1:87' temp_u1 = fi(bitconcat(fi(0, 0, 1, 0, hdl_fm), u1), 1, 9, 0, hdl_fm); */
  /*  zero-extend u2 by 1 bit for carry detection */
  /* '<S4>:1:90' temp_u2 = fi(bitconcat(fi(0, 0, 1, 0, hdl_fm), u2), 1, 9, 0, hdl_fm); */
  /*  Sum is stored in 9 bits with the msb indicating carry */
  /* '<S4>:1:93' temp_sum = fi(temp_u1 + temp_u2 + c_in, 1, 9, 0, hdl_fm); */
  tmp = (uint8_T)u1;
  temp_sum = (uint8_T)u2;
  tmp = (int16_T)(((tmp & 512) != 0 ? (int32_T)(int16_T)(tmp | -512) : (int32_T)
                   tmp) + ((temp_sum & 512) != 0 ? (int32_T)(int16_T)(temp_sum |
    -512) : (int32_T)temp_sum));
  tmp = (int16_T)((int16_T)(tmp & 512) != 0 ? (int32_T)(int16_T)(tmp | -512) :
                  (int32_T)(int16_T)(tmp & 511));
  tmp = (int16_T)(((int16_T)(tmp & 1024) != 0 ? (int32_T)(int16_T)(tmp | -1024) :
                   (int32_T)(int16_T)(tmp & 1023)) + ((c_in & 1024) != 0 ?
    (int32_T)(int16_T)(c_in | -1024) : (int32_T)c_in));
  tmp = (int16_T)((int16_T)(tmp & 1024) != 0 ? (int32_T)(int16_T)(tmp | -1024) :
                  (int32_T)(int16_T)(tmp & 1023));
  temp_sum = (int16_T)((int16_T)(tmp & 256) != 0 ? (int32_T)(int16_T)(tmp | -256)
                       : (int32_T)(int16_T)(tmp & 255));

  /*  Carry  (C) */
  /* '<S4>:1:96' carry = getmsb(temp_sum); */
  tmp = (int16_T)((uint32_T)((uint16_T)temp_sum & 511) >> 8);
  tmp = (int16_T)((int16_T)((tmp & 256) != 0 ? (int32_T)(int16_T)(tmp | -256) :
                   (int32_T)tmp) & 1);
  *carry = (uint8_T)((uint8_T)((int16_T)(tmp & 256) != 0 ? (int32_T)(int16_T)
    (tmp | -256) : (int32_T)(int16_T)(tmp & 255)) & 1);

  /*  Stored back in the designated register */
  /* '<S4>:1:99' sum = fi(temp_sum, 1, 8, 0, hdl_fm); */
  *sum = (int8_T)temp_sum;

  /*  Sign bit */
  /* '<S4>:1:102' sign_bit = getmsb(sum); */
  /*  if the inputs have the same sign and the output generated has a different sign,  */
  /*  overflow is generated! */
  /* '<S4>:1:106' overflow_int = uint8((getmsb(u1) == getmsb(u2)) ... */
  /* '<S4>:1:107'                      && (sign_bit ~= bitget(u1,8))); */
  /*  Overflow (V) */
  /* '<S4>:1:110' overflow = fi(overflow_int, 0, 1, 0, hdl_fm); */
  *overflow = (uint8_T)(((int32_T)((uint32_T)(uint8_T)u1 >> 7) == (int32_T)
    ((uint32_T)(uint8_T)u2 >> 7)) && ((int32_T)((uint32_T)(uint8_T)*sum >> 7) !=
                         (int32_T)((uint32_T)(uint8_T)u1 >> 7)));

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
}

/* Model output function */
static void hdlcodercpu_eml_output(void)
{
  /* local block i/o variables */
  int8_T rtb_UnitDelay6;
  uint8_T rtb_hlt;
  uint8_T carry;
  int8_T diff;
  uint8_T rtb_DM_addr;
  int8_T rtb_wr_port[256];
  boolean_T rtb_print_data;
  uint8_T rtb_DM_r_w;
  uint8_T rtb_shifter_sel;
  uint8_T rtb_ALU_func;
  uint8_T rtb_out_flags;
  uint8_T rtb_AC_func;
  int8_T rtb_AC_data;
  uint8_T rtb_IR_func;
  uint8_T rtb_PC_func;
  uint8_T rtb_IM_read;
  int8_T rtb_addr_inc;
  uint16_T rtb_instr_out;
  int32_T i;
  int16_T tmp;

  /* UnitDelay: '<S1>/Unit Delay 6' */
  rtb_UnitDelay6 = hdlcodercpu_eml_DW.UnitDelay6_DSTATE;

  /* MATLAB Function: '<S1>/Control Unit' incorporates:
   *  UnitDelay: '<S1>/Unit Delay 1'
   *  UnitDelay: '<S1>/Unit Delay 3'
   *  UnitDelay: '<S1>/Unit Delay 5'
   *  UnitDelay: '<S1>/Unit Delay 7'
   */
  /* MATLAB Function 'CPU_Subsystem_8_bit/Control Unit': '<S5>:1' */
  /*  CPU Controller */
  /*  */
  /*  The CPU Instruction Set: */
  /*  ------------------------ */
  /*   */
  /*  LDA <loc>: AC = content(<loc>) */
  /*  LDAI <loc>: AC = content(content(<loc>)) */
  /*  AND <loc>: AC = AC & content(<loc>) */
  /*  ANDI <loc>: AC = AC & content(content(<loc>)) */
  /*  ADD <loc>: AC = AC + content(<loc>) + C(flag)  */
  /*  ADDI <loc>: AC = AC + content(content(<loc>)) + C(flag) */
  /*  SUB <loc>: AC = AC - content(<loc>) - C(flag)  */
  /*  SUBI <loc>: AC = AC - content(content(<loc>)) - C(flag) */
  /*  JMP <loc>: Jump to <PC + <loc>> */
  /*  LI <const>: AC = <const> */
  /*  STA <loc>: content(<loc>) = AC */
  /*  STAI <loc>: content(content(<loc>)) = AC */
  /*  BRA_C <loc>: Jump to <PC + <loc>> if (C(flag) == 1) */
  /*  BRA_N <loc>: Jump to <PC + <loc>> if (N(flag) == 1) */
  /*  BRA_V <loc>: Jump to <PC + <loc>> if (V(flag) == 1) */
  /*  BRA_Z <loc>: Jump to <PC + <loc>> if (Z(flag) == 1) */
  /*  NOP: Do nothing */
  /*  CLA: AC = 0 */
  /*  CMA: Complement AC */
  /*  CMC: Complement C(flag) */
  /*  ASL: AC = AC << 1 */
  /*  ASR: AC = AC >> 1 */
  /*  PRINT: Display value from the memory-mapped location 255 */
  /*  CLC: C(flag) = 0 */
  /*  */
  /*  12-bit Instruction Encoding: */
  /*  --------------------------- */
  /*  */
  /*  	LDA:   000 0 <8-bit loc> */
  /*  	LDAI:  000 1 <8-bit loc> */
  /*  	AND:   001 0 <8-bit loc> */
  /*  	ANDI:  001 1 <8-bit loc> */
  /*  	ADD:   010 0 <8-bit loc> */
  /*  	ADDI:  010 1 <8-bit loc> */
  /*  	SUB:   011 0 <8-bit loc> */
  /*  	SUBI:  011 1 <8-bit loc> */
  /*  	JMP:   1000 <8-bit loc> */
  /*  	LI:    1001 <8-bit const> */
  /*  	STA:   101 0 <8-bit loc> */
  /*  	STAI:  101 1 <8-bit loc> */
  /*  	BRA_C: 1100 <8-bit loc> */
  /*  	BRA_N: 1101 <8-bit loc> */
  /*  	BRA_C: 1110 <8-bit loc> */
  /*  	BRA_C: 1111 <8-bit loc> */
  /*  	HLT:   111 0 0100 0 000  */
  /*  	CLA:   111 0 0100 1 000 */
  /*  	CMA:   111 0 0101 0 000 */
  /*  	CMC:   111 0 0101 1 000 */
  /*  	ASL:   111 0 0110 0 000 */
  /*  	ASR:   111 0 0110 1 000 */
  /*  	PRINT: 111 0 0111 0 000 */
  /*  	CLC:   111 0 0111 1 000   */
  /*  HDL specific fimath */
  /* '<S5>:1:63' hdl_fm = fimath(... */
  /* '<S5>:1:64' 'RoundMode', 'floor',... */
  /* '<S5>:1:65' 'OverflowMode', 'wrap',... */
  /* '<S5>:1:66' 'ProductMode', 'FullPrecision', 'ProductWordLength', 32,... */
  /* '<S5>:1:67' 'SumMode', 'FullPrecision', 'SumWordLength', 32,... */
  /* '<S5>:1:68' 'CastBeforeSum', true); */
  /* '<S5>:1:72' if(isempty(CPU_state)) */
  /* '<S5>:1:77' if(isempty(previous_CPU_state)) */
  /* '<S5>:1:81' if(master_rst) */
  if (hdlcodercpu_eml_DW.UnitDelay7_DSTATE) {
    /* '<S5>:1:82' CPU_state = uint8(0); */
    hdlcodercpu_eml_DW.CPU_state = 0U;
  }

  /* '<S5>:1:85' shifter_sel = fi(0, 0, 2, 0, hdl_fm); */
  rtb_shifter_sel = 0U;

  /* '<S5>:1:86' ALU_func = fi(0, 0, 3, 0, hdl_fm); */
  rtb_ALU_func = 0U;

  /* '<S5>:1:87' out_flags = in_flags; */
  rtb_out_flags = hdlcodercpu_eml_DW.UnitDelay3_DSTATE;

  /* '<S5>:1:88' AC_func = fi(4, 0, 3, 0, hdl_fm); */
  rtb_AC_func = 4U;

  /*  NOP */
  /* '<S5>:1:89' AC_data = fi(0, 1, 8, 0, hdl_fm); */
  rtb_AC_data = 0;

  /* '<S5>:1:90' IR_func = fi(3, 0, 2, 0, hdl_fm); */
  rtb_IR_func = 3U;

  /*  NOP */
  /* '<S5>:1:91' PC_func = fi(3, 0, 2, 0, hdl_fm); */
  rtb_PC_func = 3U;

  /*  NOP */
  /* '<S5>:1:92' IM_read = fi(0, 0, 1, 0, hdl_fm); */
  rtb_IM_read = 0U;

  /* '<S5>:1:93' DM_addr = uint8(0); */
  rtb_DM_addr = 0U;

  /* '<S5>:1:94' DM_r_w = fi(0, 0, 1, 0, hdl_fm); */
  rtb_DM_r_w = 0U;

  /* '<S5>:1:95' addr_inc = fi(0, 1, 8, 0, hdl_fm); */
  rtb_addr_inc = 0;

  /* '<S5>:1:96' print_data = false; */
  rtb_print_data = false;

  /* '<S5>:1:97' hlt = uint8(0); */
  rtb_hlt = 0U;

  /*  Instruction: <12..1> */
  /*  major_opcode: <12..10> */
  /*  indirect_addressing: <9> */
  /*  minor_opcode: <9..4> */
  /*  address bits: <8..1> */
  /* '<S5>:1:110' if(isempty(major_opcode)) */
  /* '<S5>:1:117' switch(CPU_state) */
  switch (hdlcodercpu_eml_DW.CPU_state) {
   case 0U:
    /* '<S5>:1:121' case 0, */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*   RESETTING OUTPUTS */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* '<S5>:1:122' PC_func = fi(0, 0, 2, 0, hdl_fm); */
    rtb_PC_func = 0U;

    /* '<S5>:1:123' AC_func = fi(0, 0, 3, 0, hdl_fm); */
    rtb_AC_func = 0U;

    /* '<S5>:1:124' IR_func = fi(0, 0, 2, 0, hdl_fm); */
    rtb_IR_func = 0U;

    /* '<S5>:1:125' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /* '<S5>:1:126' CPU_state = uint8(1); */
    hdlcodercpu_eml_DW.CPU_state = 1U;

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*   FETCH */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    break;

   case 1U:
    /* '<S5>:1:131' case 1, */
    /*  Read from IM */
    /* '<S5>:1:133' IM_read = fi(1, 0, 1, 0, hdl_fm); */
    rtb_IM_read = 1U;

    /*  Increment PC */
    /* '<S5>:1:135' PC_func = fi(2, 0, 2, 0, hdl_fm); */
    rtb_PC_func = 2U;

    /*  store into IR */
    /* '<S5>:1:137' IR_func = fi(1, 0, 2, 0, hdl_fm); */
    rtb_IR_func = 1U;

    /* '<S5>:1:139' CPU_state = uint8(2); */
    hdlcodercpu_eml_DW.CPU_state = 2U;
    break;

   case 2U:
    /* '<S5>:1:141' case 2, */
    /*  Read from IR */
    /* '<S5>:1:143' IR_func = fi(2, 0, 2, 0, hdl_fm); */
    rtb_IR_func = 2U;

    /*  Accommodating for the 'unit delay' from IR_out to IR_in */
    /* '<S5>:1:146' CPU_state = uint8(3); */
    hdlcodercpu_eml_DW.CPU_state = 3U;
    break;

   case 3U:
    /* '<S5>:1:148' case 3, */
    /*  IR_in <12..10> */
    /* '<S5>:1:150' major_opcode = fi(bitsrl(IR_in, 9), 0, 8, 0, hdl_fm); */
    hdlcodercpu_eml_DW.major_opcode = (uint8_T)((uint32_T)
      hdlcodercpu_eml_DW.UnitDelay1_DSTATE >> 9);

    /* '<S5>:1:151' mask = fi(63, 0, 12, 0, hdl_fm); */
    /*  IR_in <9..4> */
    /* '<S5>:1:153' minor_opcode = fi(bitand(bitsrl(IR_in, 3), mask), 0, 8, 0, hdl_fm); */
    hdlcodercpu_eml_DW.minor_opcode = (uint8_T)((int32_T)((uint32_T)
      hdlcodercpu_eml_DW.UnitDelay1_DSTATE >> 3) & 63);

    /* '<S5>:1:154' mask = fi(255, 0, 12, 0, hdl_fm); */
    /*  IR_in <8..1> */
    /* '<S5>:1:156' address_data = fi(bitand(IR_in, mask), 0, 8, 0, hdl_fm); */
    hdlcodercpu_eml_DW.address_data = (uint8_T)
      (hdlcodercpu_eml_DW.UnitDelay1_DSTATE & 255);

    /*  Go to the decode stage */
    /* '<S5>:1:159' CPU_state = uint8(4); */
    hdlcodercpu_eml_DW.CPU_state = 4U;

    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /*   DECODE AND EXECUTE */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    break;

   case 4U:
    /* '<S5>:1:164' case 4, */
    /* '<S5>:1:165' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /* '<S5>:1:166' switch(uint8(major_opcode)) */
    switch (hdlcodercpu_eml_DW.major_opcode) {
     case 0U:
      /* '<S5>:1:167' case 0, */
      /*  LDA */
      /*  minor_opcode contains the address (assuming direct addressing) */
      /* '<S5>:1:170' DM_addr = uint8(address_data); */
      rtb_DM_addr = hdlcodercpu_eml_DW.address_data;

      /*  Read the data memory */
      /* '<S5>:1:172' DM_r_w = fi(0, 0, 1, 0, hdl_fm); */
      /*  Simply pass the value read from memory */
      /* '<S5>:1:174' CPU_state = uint8(13); */
      hdlcodercpu_eml_DW.CPU_state = 13U;
      break;

     case 1U:
      /* '<S5>:1:176' case 1, */
      /*  AND            */
      /* '<S5>:1:178' DM_addr = uint8(address_data); */
      rtb_DM_addr = hdlcodercpu_eml_DW.address_data;

      /*  Reading the data memory for address or data */
      /* '<S5>:1:180' DM_r_w = fi(0, 0, 1, 0, hdl_fm); */
      /* '<S5>:1:182' CPU_state = uint8(15); */
      hdlcodercpu_eml_DW.CPU_state = 15U;
      break;

     case 2U:
      /* '<S5>:1:184' case 2, */
      /*  ADD */
      /* '<S5>:1:186' DM_addr = uint8(address_data); */
      rtb_DM_addr = hdlcodercpu_eml_DW.address_data;

      /*  Reading the data memory for address or data */
      /* '<S5>:1:188' DM_r_w = fi(0, 0, 1, 0, hdl_fm); */
      /* '<S5>:1:190' CPU_state = uint8(17); */
      hdlcodercpu_eml_DW.CPU_state = 17U;
      break;

     case 3U:
      /* '<S5>:1:192' case 3, */
      /*  SUB */
      /* '<S5>:1:194' DM_addr = uint8(address_data); */
      rtb_DM_addr = hdlcodercpu_eml_DW.address_data;

      /*  Reading the data memory for address or data */
      /* '<S5>:1:196' DM_r_w = fi(0, 0, 1, 0, hdl_fm); */
      /* '<S5>:1:198' CPU_state = uint8(19); */
      hdlcodercpu_eml_DW.CPU_state = 19U;
      break;

     case 4U:
      /* '<S5>:1:200' case 4, */
      /* '<S5>:1:201' minor_opcode_bit6 = bitget(minor_opcode, 6); */
      /* '<S5>:1:202' switch(uint8(minor_opcode_bit6)) */
      switch ((uint8_T)((int32_T)((uint32_T)hdlcodercpu_eml_DW.minor_opcode >> 5)
                        & 1)) {
       case 0U:
        /* '<S5>:1:203' case 0, */
        /*  JMP */
        /* '<S5>:1:205' temp_address_data = fi(address_data, 1, 7, 0, hdl_fm); */
        /* '<S5>:1:206' addr_inc = fi(temp_address_data-1, 1, 8, 0, hdl_fm); */
        diff = (int8_T)hdlcodercpu_eml_DW.address_data;
        rtb_addr_inc = (int8_T)(((int8_T)(diff & 64) != 0 ? (int32_T)(int8_T)
          (diff | -64) : (int32_T)(int8_T)(diff & 63)) - 1);

        /* '<S5>:1:207' PC_func = fi(1, 0, 2, 0, hdl_fm); */
        rtb_PC_func = 1U;
        break;

       case 1U:
        /* '<S5>:1:209' case 1, */
        /*  LI */
        /* '<S5>:1:211' AC_data = fi(address_data, 1, 8, 0, hdl_fm); */
        rtb_AC_data = (int8_T)hdlcodercpu_eml_DW.address_data;

        /* '<S5>:1:212' AC_func = fi(1, 0, 3, 0, hdl_fm); */
        rtb_AC_func = 1U;
        break;
      }

      /*  Go back to the fetch stage again */
      /* '<S5>:1:215' CPU_state = uint8(1); */
      hdlcodercpu_eml_DW.CPU_state = 1U;
      break;

     case 5U:
      /* '<S5>:1:217' case 5, */
      /*  STA */
      /*  minor_opcode contains the address (assuming direct addressing) */
      /* '<S5>:1:220' DM_addr = uint8(address_data); */
      rtb_DM_addr = hdlcodercpu_eml_DW.address_data;

      /* '<S5>:1:221' indirect_bit = bitget(minor_opcode, 6); */
      /* '<S5>:1:222' if(logical(indirect_bit)) */
      if (((int32_T)((uint32_T)hdlcodercpu_eml_DW.minor_opcode >> 5) & 1) != 0)
      {
        /*  indirect addressing */
        /*  Read the address from the data memory */
        /* '<S5>:1:225' DM_r_w = fi(0, 0, 1, 0, hdl_fm); */
        /* '<S5>:1:226' CPU_state = uint8(21); */
        hdlcodercpu_eml_DW.CPU_state = 21U;
      } else {
        /* '<S5>:1:227' else */
        /*  Write into the data memory */
        /* '<S5>:1:229' DM_r_w = fi(1, 0, 1, 0, hdl_fm); */
        rtb_DM_r_w = 1U;

        /*  Go back to the fetch stage again */
        /* '<S5>:1:231' CPU_state = uint8(25); */
        hdlcodercpu_eml_DW.CPU_state = 25U;

        /*  going to 'otherwise' */
      }
      break;

     case 6U:
      /* '<S5>:1:234' case 6, */
      /* '<S5>:1:235' minor_opcode_bit6 = bitget(minor_opcode, 6); */
      /* '<S5>:1:236' switch(uint8(minor_opcode_bit6)) */
      switch ((uint8_T)((int32_T)((uint32_T)hdlcodercpu_eml_DW.minor_opcode >> 5)
                        & 1)) {
       case 0U:
        /* '<S5>:1:238' case 0, */
        /*  special branches: */
        /*  BRA_C */
        /* '<S5>:1:240' c = bitget(in_flags, 4); */
        /* '<S5>:1:241' if(logical(c)) */
        if (((int32_T)((uint32_T)hdlcodercpu_eml_DW.UnitDelay3_DSTATE >> 3) & 1)
            != 0) {
          /* '<S5>:1:242' temp_address_data = fi(address_data, 1, 7, 0, hdl_fm); */
          /* '<S5>:1:243' addr_inc = fi(temp_address_data-1, 1, 8, 0, hdl_fm); */
          diff = (int8_T)hdlcodercpu_eml_DW.address_data;
          rtb_addr_inc = (int8_T)(((int8_T)(diff & 64) != 0 ? (int32_T)(int8_T)
            (diff | -64) : (int32_T)(int8_T)(diff & 63)) - 1);

          /* '<S5>:1:244' PC_func = fi(1, 0, 2, 0, hdl_fm); */
          rtb_PC_func = 1U;
        }
        break;

       case 1U:
        /* '<S5>:1:247' case 1, */
        /*  BRA_N */
        /* '<S5>:1:249' n = bitget(in_flags, 3); */
        /* '<S5>:1:250' if(logical(n)) */
        if (((int32_T)((uint32_T)hdlcodercpu_eml_DW.UnitDelay3_DSTATE >> 2) & 1)
            != 0) {
          /* '<S5>:1:251' temp_address_data = fi(address_data, 1, 7, 0, hdl_fm); */
          /* '<S5>:1:252' addr_inc = fi(temp_address_data-1, 1, 8, 0, hdl_fm); */
          diff = (int8_T)hdlcodercpu_eml_DW.address_data;
          rtb_addr_inc = hdlcodercpu_eml_minus((int8_T)((int8_T)(diff & 64) != 0
            ? (int32_T)(int8_T)(diff | -64) : (int32_T)(int8_T)(diff & 63)));

          /* '<S5>:1:253' PC_func = fi(1, 0, 2, 0, hdl_fm); */
          rtb_PC_func = 1U;
        }
        break;
      }

      /*  Go back to the fetch stage again */
      /* '<S5>:1:257' CPU_state = uint8(15); */
      hdlcodercpu_eml_DW.CPU_state = 15U;
      break;

     case 7U:
      /* '<S5>:1:259' case 7, */
      /*  by default, go back to the fetch stage again */
      /* '<S5>:1:261' CPU_state = uint8(1); */
      hdlcodercpu_eml_DW.CPU_state = 1U;

      /* '<S5>:1:262' minor_opcode_bit4 = bitget(minor_opcode, 4); */
      /* '<S5>:1:263' if(logical(minor_opcode_bit4) == 0) */
      if ((((int32_T)((uint32_T)hdlcodercpu_eml_DW.minor_opcode >> 3) & 1) != 0)
          == 0) {
        /*  Further cases of special branches: */
        /* '<S5>:1:265' minor_opcode_bit6 = bitget(minor_opcode, 6); */
        /* '<S5>:1:266' switch(uint8(minor_opcode_bit6)) */
        switch ((uint8_T)((int32_T)((uint32_T)hdlcodercpu_eml_DW.minor_opcode >>
                  5) & 1)) {
         case 0U:
          /* '<S5>:1:267' case 0, */
          /*  BRA_V */
          /* '<S5>:1:269' v = bitget(in_flags, 2); */
          /* '<S5>:1:270' if(logical(v)) */
          if (((int32_T)((uint32_T)hdlcodercpu_eml_DW.UnitDelay3_DSTATE >> 1) &
               1) != 0) {
            /* '<S5>:1:271' temp_address_data = fi(address_data, 1, 7, 0, hdl_fm); */
            /* '<S5>:1:272' addr_inc = fi(temp_address_data-1, 1, 8, 0, hdl_fm); */
            diff = (int8_T)hdlcodercpu_eml_DW.address_data;
            rtb_addr_inc = hdlcodercpu_eml_minus((int8_T)((int8_T)(diff & 64) !=
              0 ? (int32_T)(int8_T)(diff | -64) : (int32_T)(int8_T)(diff & 63)));

            /* '<S5>:1:273' PC_func = fi(1, 0, 2, 0, hdl_fm); */
            rtb_PC_func = 1U;
          }
          break;

         case 1U:
          /* '<S5>:1:276' case 1, */
          /*  BRA_Z */
          /* '<S5>:1:278' z = bitget(in_flags, 1); */
          /* '<S5>:1:279' if(logical(z)) */
          if ((hdlcodercpu_eml_DW.UnitDelay3_DSTATE & 1) != 0) {
            /* '<S5>:1:280' temp_address_data = fi(address_data, 1, 7, 0, hdl_fm); */
            /* '<S5>:1:281' addr_inc = fi(temp_address_data-1, 1, 8, 0, hdl_fm); */
            diff = (int8_T)hdlcodercpu_eml_DW.address_data;
            rtb_addr_inc = hdlcodercpu_eml_minus((int8_T)((int8_T)(diff & 64) !=
              0 ? (int32_T)(int8_T)(diff | -64) : (int32_T)(int8_T)(diff & 63)));

            /* '<S5>:1:282' PC_func = fi(1, 0, 2, 0, hdl_fm); */
            rtb_PC_func = 1U;
          }
          break;
        }
      }

      /*  Instructions having no operands */
      /* '<S5>:1:287' switch(uint8(minor_opcode)) */
      switch (hdlcodercpu_eml_DW.minor_opcode) {
       case 8U:
        /* '<S5>:1:288' case 8, */
        /*  HLT */
        /*  Stop the simulation */
        /* '<S5>:1:291' hlt = uint8(1); */
        rtb_hlt = 1U;

        /* '<S5>:1:292' CPU_state = uint8(22); */
        hdlcodercpu_eml_DW.CPU_state = 22U;
        break;

       case 9U:
        /* '<S5>:1:293' case 9, */
        /*  CLA */
        /* '<S5>:1:295' AC_func = fi(0, 0, 3, 0, hdl_fm); */
        rtb_AC_func = 0U;
        break;

       case 10U:
        /* '<S5>:1:297' case 10, */
        /*  CMA */
        /* '<S5>:1:299' ALU_func = fi(4, 0, 3, 0, hdl_fm); */
        rtb_ALU_func = 4U;

        /* '<S5>:1:300' shifter_sel = fi(3, 0, 2, 0, hdl_fm); */
        rtb_shifter_sel = 3U;

        /* '<S5>:1:301' CPU_state = uint8(6); */
        hdlcodercpu_eml_DW.CPU_state = 6U;
        break;

       case 11U:
        /* '<S5>:1:303' case 11, */
        /*  CMC */
        /* '<S5>:1:305' ALU_func = fi(5, 0, 3, 0, hdl_fm); */
        rtb_ALU_func = 5U;

        /* '<S5>:1:306' shifter_sel = fi(3, 0, 2, 0, hdl_fm); */
        rtb_shifter_sel = 3U;
        break;

       case 12U:
        /* '<S5>:1:308' case 12, */
        /*  ASL */
        /* '<S5>:1:310' shifter_sel = fi(1, 0, 2, 0, hdl_fm); */
        rtb_shifter_sel = 1U;

        /* '<S5>:1:311' CPU_state = uint8(6); */
        hdlcodercpu_eml_DW.CPU_state = 6U;
        break;

       case 13U:
        /* '<S5>:1:313' case 13, */
        /*  ASR */
        /* '<S5>:1:315' shifter_sel = fi(2, 0, 2, 0, hdl_fm); */
        rtb_shifter_sel = 2U;

        /* '<S5>:1:316' CPU_state = uint8(6); */
        hdlcodercpu_eml_DW.CPU_state = 6U;
        break;

       case 14U:
        /* '<S5>:1:318' case 14, */
        /*  PRINT    */
        /* '<S5>:1:320' DM_addr = uint8(255); */
        rtb_DM_addr = MAX_uint8_T;

        /*  Read the data memory */
        /* '<S5>:1:322' DM_r_w = fi(0, 0, 1, 0, hdl_fm); */
        /* '<S5>:1:324' CPU_state = uint8(12); */
        hdlcodercpu_eml_DW.CPU_state = 12U;
        break;

       case 15U:
        /* '<S5>:1:326' case 15, */
        /*  CLC */
        /* '<S5>:1:328' ALU_func = fi(7, 0, 3, 0, hdl_fm); */
        rtb_ALU_func = 7U;

        /* '<S5>:1:329' shifter_sel = fi(3, 0, 2, 0, hdl_fm); */
        rtb_shifter_sel = 3U;
        break;

       default:
        /* '<S5>:1:331' otherwise */
        /*  by default, go back to the fetch stage again */
        /* '<S5>:1:333' CPU_state = uint8(1); */
        hdlcodercpu_eml_DW.CPU_state = 1U;

        /*  Minor Opcode cases end here         */
        break;
      }

      /*  Major Opcode cases end here */
      break;
    }

    /*  introducing delay */
    break;

   case 6U:
    /* '<S5>:1:341' case 6, */
    /*  accounting for the delay from shift_out to AC_in2 */
    /* '<S5>:1:343' AC_func = fi(2, 0, 3, 0, hdl_fm); */
    rtb_AC_func = 2U;

    /* '<S5>:1:344' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /*  Go back to the fetch stage again */
    /* '<S5>:1:346' CPU_state = uint8(1); */
    hdlcodercpu_eml_DW.CPU_state = 1U;

    /*  Operations with indirect addressing */
    break;

   case 7U:
    /* '<S5>:1:349' case 7, */
    /*  LDA Indirect */
    /*  data_in is the address read from the data memory */
    /* '<S5>:1:352' DM_addr = indirect_address; */
    rtb_DM_addr = hdlcodercpu_eml_DW.indirect_address;

    /*  Read the data memory */
    /* '<S5>:1:354' DM_r_w = fi(0, 0, 1, 0, hdl_fm); */
    /* '<S5>:1:356' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /* '<S5>:1:357' CPU_state = uint8(13); */
    hdlcodercpu_eml_DW.CPU_state = 13U;
    break;

   case 8U:
    /* '<S5>:1:359' case 8, */
    /*  AND Indirect */
    /*  data_in is the address read from the data memory */
    /* '<S5>:1:362' DM_addr = indirect_address; */
    rtb_DM_addr = hdlcodercpu_eml_DW.indirect_address;

    /*  Read the data memory */
    /* '<S5>:1:364' DM_r_w = fi(0, 0, 1, 0, hdl_fm); */
    /* '<S5>:1:366' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /* '<S5>:1:367' CPU_state = uint8(15); */
    hdlcodercpu_eml_DW.CPU_state = 15U;
    break;

   case 9U:
    /* '<S5>:1:369' case 9, */
    /*  ADD Indirect */
    /*  data_in is the address read from the data memory */
    /* '<S5>:1:372' DM_addr = indirect_address; */
    rtb_DM_addr = hdlcodercpu_eml_DW.indirect_address;

    /*  Read the data memory */
    /* '<S5>:1:374' DM_r_w = fi(0, 0, 1, 0, hdl_fm); */
    /* '<S5>:1:376' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /* '<S5>:1:377' CPU_state = uint8(17); */
    hdlcodercpu_eml_DW.CPU_state = 17U;
    break;

   case 10U:
    /* '<S5>:1:379' case 10, */
    /*  SUB Indirect */
    /*  data_in is the address read from the data memory */
    /* '<S5>:1:382' DM_addr = indirect_address; */
    rtb_DM_addr = hdlcodercpu_eml_DW.indirect_address;

    /*  Read the data memory */
    /* '<S5>:1:384' DM_r_w = fi(0, 0, 1, 0, hdl_fm); */
    /* '<S5>:1:386' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /* '<S5>:1:387' CPU_state = uint8(19); */
    hdlcodercpu_eml_DW.CPU_state = 19U;
    break;

   case 11U:
    /* '<S5>:1:389' case 11, */
    /*  STA Indirect */
    /*  data_in is the address read from the data memory */
    /* '<S5>:1:392' DM_addr = uint8(data_in); */
    diff = hdlcodercpu_eml_DW.UnitDelay5_DSTATE;
    if (hdlcodercpu_eml_DW.UnitDelay5_DSTATE < 0) {
      diff = 0;
    }

    rtb_DM_addr = (uint8_T)diff;

    /*  Write the data memory */
    /* '<S5>:1:394' DM_r_w = fi(1, 0, 1, 0, hdl_fm); */
    rtb_DM_r_w = 1U;

    /* '<S5>:1:395' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /* '<S5>:1:396' CPU_state = uint8(1); */
    hdlcodercpu_eml_DW.CPU_state = 1U;
    break;

   case 12U:
    /* '<S5>:1:398' case 12, */
    /*  PRINT */
    /* '<S5>:1:400' print_data = true; */
    rtb_print_data = true;

    /* '<S5>:1:401' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /* '<S5>:1:402' CPU_state = uint8(1); */
    hdlcodercpu_eml_DW.CPU_state = 1U;
    break;

   case 13U:
    /* '<S5>:1:404' case 13, */
    /*  LDA (contd.) */
    /*  Simply pass the value read from memory */
    /* '<S5>:1:407' ALU_func = fi(6, 0, 3, 0, hdl_fm); */
    rtb_ALU_func = 6U;

    /* '<S5>:1:408' shifter_sel = fi(3, 0, 2, 0, hdl_fm); */
    rtb_shifter_sel = 3U;

    /* '<S5>:1:410' if(previous_CPU_state == uint8(4)) */
    if (hdlcodercpu_eml_DW.previous_CPU_state == 4) {
      /* '<S5>:1:411' previous_CPU_state = CPU_state; */
      hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

      /* '<S5>:1:412' CPU_state = uint8(14); */
      hdlcodercpu_eml_DW.CPU_state = 14U;
    } else {
      /* '<S5>:1:413' else */
      /* '<S5>:1:414' previous_CPU_state = CPU_state; */
      hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

      /* '<S5>:1:415' CPU_state = uint8(6); */
      hdlcodercpu_eml_DW.CPU_state = 6U;
    }
    break;

   case 14U:
    /* '<S5>:1:418' case 14, */
    /* '<S5>:1:419' indirect_bit = bitget(minor_opcode, 6); */
    /*  accounting for the delay from shift_out to AC_in2 */
    /* '<S5>:1:421' AC_func = fi(2, 0, 3, 0, hdl_fm); */
    rtb_AC_func = 2U;

    /* '<S5>:1:423' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /* '<S5>:1:424' if(logical(indirect_bit)) */
    if (((int32_T)((uint32_T)hdlcodercpu_eml_DW.minor_opcode >> 5) & 1) != 0) {
      /*  indirect addressing */
      /* '<S5>:1:426' indirect_address = uint8(data_in); */
      diff = hdlcodercpu_eml_DW.UnitDelay5_DSTATE;
      if (hdlcodercpu_eml_DW.UnitDelay5_DSTATE < 0) {
        diff = 0;
      }

      hdlcodercpu_eml_DW.indirect_address = (uint8_T)diff;

      /* '<S5>:1:427' CPU_state = uint8(7); */
      hdlcodercpu_eml_DW.CPU_state = 7U;
    } else {
      /* '<S5>:1:428' else */
      /* '<S5>:1:429' CPU_state = uint8(25); */
      hdlcodercpu_eml_DW.CPU_state = 25U;
    }
    break;

   case 15U:
    /* '<S5>:1:432' case 15, */
    /*  AND (contd.) */
    /* '<S5>:1:435' ALU_func = fi(1, 0, 3, 0, hdl_fm); */
    rtb_ALU_func = 1U;

    /* '<S5>:1:436' shifter_sel = fi(3, 0, 2, 0, hdl_fm); */
    rtb_shifter_sel = 3U;

    /* '<S5>:1:438' if(previous_CPU_state == uint8(4)) */
    if (hdlcodercpu_eml_DW.previous_CPU_state == 4) {
      /* '<S5>:1:439' previous_CPU_state = CPU_state; */
      hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

      /* '<S5>:1:440' CPU_state = uint8(16); */
      hdlcodercpu_eml_DW.CPU_state = 16U;
    } else {
      /* '<S5>:1:441' else */
      /* '<S5>:1:442' previous_CPU_state = CPU_state; */
      hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

      /* '<S5>:1:443' CPU_state = uint8(6); */
      hdlcodercpu_eml_DW.CPU_state = 6U;
    }
    break;

   case 16U:
    /* '<S5>:1:446' case 16, */
    /* '<S5>:1:447' indirect_bit = bitget(minor_opcode, 6); */
    /*  accounting for the delay from shift_out to AC_in2 */
    /* '<S5>:1:449' AC_func = fi(2, 0, 3, 0, hdl_fm); */
    rtb_AC_func = 2U;

    /* '<S5>:1:451' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /* '<S5>:1:452' if(logical(indirect_bit)) */
    if (((int32_T)((uint32_T)hdlcodercpu_eml_DW.minor_opcode >> 5) & 1) != 0) {
      /*  indirect addressing */
      /* '<S5>:1:454' indirect_address = uint8(data_in); */
      diff = hdlcodercpu_eml_DW.UnitDelay5_DSTATE;
      if (hdlcodercpu_eml_DW.UnitDelay5_DSTATE < 0) {
        diff = 0;
      }

      hdlcodercpu_eml_DW.indirect_address = (uint8_T)diff;

      /* '<S5>:1:455' CPU_state = uint8(8); */
      hdlcodercpu_eml_DW.CPU_state = 8U;
    } else {
      /* '<S5>:1:456' else */
      /* '<S5>:1:457' CPU_state = uint8(25); */
      hdlcodercpu_eml_DW.CPU_state = 25U;
    }
    break;

   case 17U:
    /* '<S5>:1:460' case 17, */
    /*  ADD (contd.) */
    /* '<S5>:1:462' ALU_func = fi(2, 0, 3, 0, hdl_fm); */
    rtb_ALU_func = 2U;

    /* '<S5>:1:463' shifter_sel = fi(3, 0, 2, 0, hdl_fm); */
    rtb_shifter_sel = 3U;

    /* '<S5>:1:465' if(previous_CPU_state == uint8(4)) */
    if (hdlcodercpu_eml_DW.previous_CPU_state == 4) {
      /* '<S5>:1:466' previous_CPU_state = CPU_state; */
      hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

      /* '<S5>:1:467' CPU_state = uint8(18); */
      hdlcodercpu_eml_DW.CPU_state = 18U;
    } else {
      /* '<S5>:1:468' else */
      /* '<S5>:1:469' previous_CPU_state = CPU_state; */
      hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

      /* '<S5>:1:470' CPU_state = uint8(6); */
      hdlcodercpu_eml_DW.CPU_state = 6U;
    }
    break;

   case 18U:
    /* '<S5>:1:473' case 18, */
    /* '<S5>:1:474' indirect_bit = bitget(minor_opcode, 6); */
    /*  accounting for the delay from shift_out to AC_in2 */
    /* '<S5>:1:476' AC_func = fi(2, 0, 3, 0, hdl_fm); */
    rtb_AC_func = 2U;

    /* '<S5>:1:478' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /* '<S5>:1:479' if(logical(indirect_bit)) */
    if (((int32_T)((uint32_T)hdlcodercpu_eml_DW.minor_opcode >> 5) & 1) != 0) {
      /*  indirect addressing */
      /* '<S5>:1:481' indirect_address = uint8(data_in); */
      diff = hdlcodercpu_eml_DW.UnitDelay5_DSTATE;
      if (hdlcodercpu_eml_DW.UnitDelay5_DSTATE < 0) {
        diff = 0;
      }

      hdlcodercpu_eml_DW.indirect_address = (uint8_T)diff;

      /* '<S5>:1:482' CPU_state = uint8(9); */
      hdlcodercpu_eml_DW.CPU_state = 9U;
    } else {
      /* '<S5>:1:483' else */
      /* '<S5>:1:484' CPU_state = uint8(25); */
      hdlcodercpu_eml_DW.CPU_state = 25U;
    }
    break;

   case 19U:
    /* '<S5>:1:487' case 19, */
    /*  SUB (contd.) */
    /* '<S5>:1:489' ALU_func = fi(3, 0, 3, 0, hdl_fm); */
    rtb_ALU_func = 3U;

    /* '<S5>:1:490' shifter_sel = fi(3, 0, 2, 0, hdl_fm); */
    rtb_shifter_sel = 3U;

    /* '<S5>:1:492' if(previous_CPU_state == uint8(4)) */
    if (hdlcodercpu_eml_DW.previous_CPU_state == 4) {
      /* '<S5>:1:493' previous_CPU_state = CPU_state; */
      hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

      /* '<S5>:1:494' CPU_state = uint8(20); */
      hdlcodercpu_eml_DW.CPU_state = 20U;
    } else {
      /* '<S5>:1:495' else */
      /* '<S5>:1:496' previous_CPU_state = CPU_state; */
      hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

      /* '<S5>:1:497' CPU_state = uint8(6); */
      hdlcodercpu_eml_DW.CPU_state = 6U;
    }
    break;

   case 20U:
    /* '<S5>:1:500' case 20, */
    /* '<S5>:1:501' indirect_bit = bitget(minor_opcode, 6); */
    /*  accounting for the delay from shift_out to AC_in2 */
    /* '<S5>:1:503' AC_func = fi(2, 0, 3, 0, hdl_fm); */
    rtb_AC_func = 2U;

    /* '<S5>:1:505' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /* '<S5>:1:506' if(logical(indirect_bit)) */
    if (((int32_T)((uint32_T)hdlcodercpu_eml_DW.minor_opcode >> 5) & 1) != 0) {
      /*  indirect addressing */
      /* '<S5>:1:508' indirect_address = uint8(data_in); */
      diff = hdlcodercpu_eml_DW.UnitDelay5_DSTATE;
      if (hdlcodercpu_eml_DW.UnitDelay5_DSTATE < 0) {
        diff = 0;
      }

      hdlcodercpu_eml_DW.indirect_address = (uint8_T)diff;

      /* '<S5>:1:509' CPU_state = uint8(10); */
      hdlcodercpu_eml_DW.CPU_state = 10U;
    } else {
      /* '<S5>:1:510' else */
      /* '<S5>:1:512' CPU_state = uint8(25); */
      hdlcodercpu_eml_DW.CPU_state = 25U;
    }
    break;

   case 21U:
    /* '<S5>:1:515' case 21, */
    /*  STA indirect */
    /* '<S5>:1:517' CPU_state = uint8(11); */
    hdlcodercpu_eml_DW.CPU_state = 11U;
    break;

   case 22U:
    /* '<S5>:1:519' case 22, */
    /*  lock state */
    /* '<S5>:1:521' hlt = uint8(1); */
    rtb_hlt = 1U;

    /* '<S5>:1:522' CPU_state = uint8(22); */
    hdlcodercpu_eml_DW.CPU_state = 22U;
    break;

   default:
    /* '<S5>:1:524' otherwise */
    /* '<S5>:1:525' previous_CPU_state = CPU_state; */
    hdlcodercpu_eml_DW.previous_CPU_state = hdlcodercpu_eml_DW.CPU_state;

    /*  by default, go back to the fetch stage again */
    /* '<S5>:1:527' CPU_state = uint8(1); */
    hdlcodercpu_eml_DW.CPU_state = 1U;

    /*  switch(CPU_state) end here */
    break;
  }

  /* End of MATLAB Function: '<S1>/Control Unit' */

  /* Stop: '<Root>/Stop Simulation' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   */
  if (rtb_hlt != 0) {
    rtmSetStopRequested(hdlcodercpu_eml_M, 1);
  }

  /* End of Stop: '<Root>/Stop Simulation' */

  /* MATLAB Function: '<S1>/Accumulator' incorporates:
   *  UnitDelay: '<S1>/Unit Delay2'
   */
  /* MATLAB Function 'CPU_Subsystem_8_bit/Accumulator': '<S3>:1' */
  /* % Accumulator with the following func: */
  /*  func == 0 => reset */
  /*  func == 1 => store into AC from port 1 */
  /*  func == 2 => store into AC from port 2 */
  /*  func == 3 => read from AC; */
  /*  otherwise, preserve old value and return 0 */
  /*  HDL specific fimath */
  /* '<S3>:1:11' hdl_fm = fimath(... */
  /* '<S3>:1:12' 'RoundMode', 'floor',... */
  /* '<S3>:1:13' 'OverflowMode', 'wrap',... */
  /* '<S3>:1:14' 'ProductMode', 'FullPrecision', 'ProductWordLength', 32,... */
  /* '<S3>:1:15' 'SumMode', 'FullPrecision', 'SumWordLength', 32,... */
  /* '<S3>:1:16' 'CastBeforeSum', true); */
  /* '<S3>:1:20' if(isempty(AC_value)) */
  /* '<S3>:1:24' AC_out = fi(AC_value, 1, 8, 0, hdl_fm); */
  hdlcodercpu_eml_B.AC_out = hdlcodercpu_eml_DW.AC_value;

  /* '<S3>:1:26' switch(uint8(func)) */
  switch (rtb_AC_func) {
   case 0U:
    /* '<S3>:1:27' case 0, */
    /*  reset */
    /* '<S3>:1:29' AC_value = fi(0, 1, 8, 0, hdl_fm); */
    hdlcodercpu_eml_DW.AC_value = 0;
    break;

   case 1U:
    /* '<S3>:1:30' case 1, */
    /*  store into AC */
    /* '<S3>:1:32' AC_value = AC_in1; */
    hdlcodercpu_eml_DW.AC_value = rtb_AC_data;
    break;

   case 2U:
    /* '<S3>:1:33' case 2, */
    /*  store into AC */
    /* '<S3>:1:35' AC_value = AC_in2; */
    hdlcodercpu_eml_DW.AC_value = hdlcodercpu_eml_DW.UnitDelay2_DSTATE;
    break;

   case 3U:
    /* '<S3>:1:36' case 3, */
    /*  read the AC value */
    /* '<S3>:1:38' AC_out = AC_value; */
    break;
  }

  /* End of MATLAB Function: '<S1>/Accumulator' */

  /* Switch: '<S6>/Switch1' incorporates:
   *  Logic: '<S6>/And'
   *  UnitDelay: '<S6>/din_d'
   *  UnitDelay: '<S6>/ram_data'
   *  UnitDelay: '<S6>/we_d'
   */
  if (hdlcodercpu_eml_DW.we_d_DSTATE && hdlcodercpu_eml_ConstB.Compare) {
    hdlcodercpu_eml_B.Switch1 = hdlcodercpu_eml_DW.din_d_DSTATE;
  } else {
    hdlcodercpu_eml_B.Switch1 = hdlcodercpu_eml_DW.ram_data_DSTATE;
  }

  /* End of Switch: '<S6>/Switch1' */

  /* MATLAB Function: '<S1>/Arithmetic Logical Unit (8-bit)' */
  /* MATLAB Function 'CPU_Subsystem_8_bit/Arithmetic Logical Unit (8-bit)': '<S4>:1' */
  /*  This 8-bit ALU supports the following operations: */
  /*  AND (Logical AND), ADD, SUB, CMA (Complement AC), CMC (Complement Carry) and CLC (Clear Carry) */
  /*  and appropriately sets a 4-bit flag register, which has the following format: */
  /*  [C N V Z] */
  /*  HDL specific fimath */
  /* '<S4>:1:8' hdl_fm = fimath(... */
  /* '<S4>:1:9' 'RoundMode', 'floor',... */
  /* '<S4>:1:10' 'OverflowMode', 'wrap',... */
  /* '<S4>:1:11' 'ProductMode', 'FullPrecision', 'ProductWordLength', 32,... */
  /* '<S4>:1:12' 'SumMode', 'FullPrecision', 'SumWordLength', 32,... */
  /* '<S4>:1:13' 'CastBeforeSum', true); */
  /*  Get the carry in */
  /* '<S4>:1:16' carry = bitget(in_flags, 4); */
  carry = (uint8_T)((int32_T)((uint32_T)rtb_out_flags >> 3) & 1);

  /*  Get the overflow in */
  /* '<S4>:1:19' overflow = bitget(in_flags, 2); */
  rtb_out_flags = (uint8_T)((int32_T)((uint32_T)rtb_out_flags >> 1) & 1);

  /*  Simply pass the AC, when there is no designated func */
  /* '<S4>:1:22' alu_out = fi(AC, 1, 8, 0, hdl_fm); */
  diff = hdlcodercpu_eml_B.AC_out;

  /*  3-bit encoding of ALU ops, which can potentially support upto 8 operations */
  /*  Most of the encodings are unused to comply to Parwan supported ops */
  /* '<S4>:1:26' switch(uint8(func)) */
  switch (rtb_ALU_func) {
   case 0U:
    /* '<S4>:1:27' case 0, */
    /*  NOP */
    /*  simply pass the AC */
    break;

   case 1U:
    /* '<S4>:1:29' case 1, */
    /*  AND */
    /*  Bitwise AND */
    /* '<S4>:1:31' alu_out = bitand(alu_in, AC); */
    diff = (int8_T)(hdlcodercpu_eml_B.Switch1 & hdlcodercpu_eml_B.AC_out);
    break;

   case 2U:
    /* '<S4>:1:32' case 2, */
    /*  ADD */
    /*  Add with carry and overflow appropriately set */
    /* '<S4>:1:34' [alu_out, carry, overflow] = sum_w_carry(AC, alu_in, carry); */
    hdlcodercpu_eml_sum_w_carry(hdlcodercpu_eml_B.AC_out,
      hdlcodercpu_eml_B.Switch1, carry, &diff, &rtb_AC_func, &rtb_out_flags);
    carry = rtb_AC_func;
    break;

   case 3U:
    /* '<S4>:1:35' case 3, */
    /*  SUB */
    /*  Subtract with borrow (set to carry) and overflow appropriately set */
    /* '<S4>:1:37' [alu_out, carry, overflow] = sub_w_borrow(AC, alu_in, carry); */
    /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
    /* % Full Subtracter with flag register appropriately set  */
    /*  diff = u1 - u2 - b_in = u1 + bitcmp(u2) + bitcmp(b_in) */
    /*  appropriately set the borrow and the overflow */
    /* '<S4>:1:70' [diff, carry, overflow] = sum_w_carry(u1, bitcmp(u2), bitcmp(b_in)); */
    hdlcodercpu_eml_sum_w_carry(hdlcodercpu_eml_B.AC_out, (int8_T)
      ~hdlcodercpu_eml_B.Switch1, (uint8_T)((uint8_T)~carry & 1), &diff,
      &rtb_AC_func, &rtb_out_flags);
    carry = rtb_AC_func;
    break;

   case 4U:
    /* '<S4>:1:38' case 4, */
    /*  CMA */
    /*  Complement AC */
    /* '<S4>:1:40' alu_out = fi(bitcmp(AC), 1, 8, 0, hdl_fm); */
    diff = (int8_T)~hdlcodercpu_eml_B.AC_out;
    break;

   case 5U:
    /* '<S4>:1:41' case 5, */
    /*  CMC */
    /*  Complement Carry */
    /* '<S4>:1:43' carry = bitcmp(carry); */
    carry = (uint8_T)((uint8_T)~carry & 1);
    break;

   case 6U:
    /* '<S4>:1:44' case 6, */
    /*  Get alu_in out */
    /*  Pass the input */
    /* '<S4>:1:46' alu_out = fi(alu_in, 1, 8, 0, hdl_fm); */
    diff = hdlcodercpu_eml_B.Switch1;
    break;

   case 7U:
    /* '<S4>:1:47' case 7, */
    /*  CLC */
    /*  Clear Carry */
    /* '<S4>:1:49' carry = fi(0, 0, 1, 0, hdl_fm); */
    carry = 0U;
    break;
  }

  /*  Negativity  (N) */
  /* '<S4>:1:53' sign_bit = getmsb(alu_out); */
  /*  Is Zero? (Z) */
  /* '<S4>:1:56' is_zero = uint8(~all(alu_out)); */
  /* '<S4>:1:57' zero_ufix1 = fi(is_zero, 0, 1, 0, hdl_fm); */
  /*  Set the output flag register [C N V Z] */
  /* '<S4>:1:60' out_flags = bitconcat(bitconcat(bitconcat(carry, sign_bit), overflow), zero_ufix1); */
  rtb_ALU_func = (uint8_T)(((((((carry & 3) << 1 & 3) | (int32_T)((uint32_T)
    (uint8_T)diff >> 7)) & 3) << 1 | (rtb_out_flags & 7)) & 7) << 1 | !(diff !=
    0));

  /* Selector: '<S6>/select' incorporates:
   *  DataTypeConversion: '<S6>/convert'
   *  UnitDelay: '<S6>/ram'
   */
  hdlcodercpu_eml_B.select = hdlcodercpu_eml_DW.ram_DSTATE[rtb_DM_addr];

  /* Assignment: '<S6>/wr_port' incorporates:
   *  DataTypeConversion: '<S6>/convert'
   *  UnitDelay: '<S6>/ram'
   */
  memcpy(&rtb_wr_port[0], &hdlcodercpu_eml_DW.ram_DSTATE[0], sizeof(int8_T) <<
         8U);
  rtb_wr_port[rtb_DM_addr] = hdlcodercpu_eml_B.AC_out;

  /* DataTypeConversion: '<S1>/Data Type Conversion' */
  hdlcodercpu_eml_B.DataTypeConversion = (rtb_DM_r_w != 0);

  /* Switch: '<S6>/switch' incorporates:
   *  UnitDelay: '<S6>/ram'
   */
  for (i = 0; i < 256; i++) {
    if (hdlcodercpu_eml_B.DataTypeConversion) {
      hdlcodercpu_eml_B.switch_i[i] = rtb_wr_port[i];
    } else {
      hdlcodercpu_eml_B.switch_i[i] = hdlcodercpu_eml_DW.ram_DSTATE[i];
    }
  }

  /* End of Switch: '<S6>/switch' */

  /* MATLAB Function: '<S1>/Program Counter' incorporates:
   *  MATLAB Function: '<S1>/PC Incrementer'
   */
  /* MATLAB Function 'CPU_Subsystem_8_bit/PC Incrementer': '<S9>:1' */
  /*  PC incrementer increments the PC with jmp_offset */
  /*  HDL specific fimath */
  /* '<S9>:1:5' hdl_fm = fimath(... */
  /* '<S9>:1:6' 'RoundMode', 'floor',... */
  /* '<S9>:1:7' 'OverflowMode', 'wrap',... */
  /* '<S9>:1:8' 'ProductMode', 'FullPrecision', 'ProductWordLength', 32,... */
  /* '<S9>:1:9' 'SumMode', 'FullPrecision', 'SumWordLength', 32,... */
  /* '<S9>:1:10' 'CastBeforeSum', true); */
  /* '<S9>:1:12' PC_next = fi(jmp_offset + PC_current, 0, 8, 0, hdl_fm); */
  /* MATLAB Function 'CPU_Subsystem_8_bit/Program Counter': '<S10>:1' */
  /*  Program Counter */
  /*  func = 0 => reset PC */
  /*  func = 1 => load PC */
  /*  func = 2 => increment PC */
  /*  HDL specific fimath */
  /* '<S10>:1:8' hdl_fm = fimath(... */
  /* '<S10>:1:9' 'RoundMode', 'floor',... */
  /* '<S10>:1:10' 'OverflowMode', 'wrap',... */
  /* '<S10>:1:11' 'ProductMode', 'FullPrecision', 'ProductWordLength', 32,... */
  /* '<S10>:1:12' 'SumMode', 'FullPrecision', 'SumWordLength', 32,... */
  /* '<S10>:1:13' 'CastBeforeSum', true); */
  /* '<S10>:1:16' if(isempty(PC_value)) */
  /* '<S10>:1:20' addr_out = fi(PC_value, 0, 8, 0, hdl_fm); */
  hdlcodercpu_eml_B.addr_out = hdlcodercpu_eml_DW.PC_value;

  /* '<S10>:1:22' switch(uint8(func)) */
  switch (rtb_PC_func) {
   case 0U:
    /* '<S10>:1:23' case 0, */
    /*  reset */
    /* '<S10>:1:25' PC_value = fi(0, 0, 8, 0, hdl_fm); */
    hdlcodercpu_eml_DW.PC_value = 0U;
    break;

   case 1U:
    /* MATLAB Function: '<S1>/PC Incrementer' incorporates:
     *  UnitDelay: '<S1>/Unit Delay 4'
     */
    /* '<S10>:1:26' case 1, */
    /*  store into PC */
    /* '<S10>:1:28' PC_value = addr_in; */
    tmp = (int16_T)(((int16_T)(rtb_addr_inc & 256) != 0 ? (int32_T)(int16_T)
                     (rtb_addr_inc | -256) : (int32_T)(int16_T)(rtb_addr_inc &
      255)) + ((hdlcodercpu_eml_DW.UnitDelay4_DSTATE & 256) != 0 ? (int32_T)
               (int16_T)(hdlcodercpu_eml_DW.UnitDelay4_DSTATE | -256) : (int32_T)
               hdlcodercpu_eml_DW.UnitDelay4_DSTATE));
    hdlcodercpu_eml_DW.PC_value = (uint8_T)((int16_T)(tmp & 256) != 0 ? (int32_T)
      (int16_T)(tmp | -256) : (int32_T)(int16_T)(tmp & 255));
    break;

   case 2U:
    /* '<S10>:1:29' case 2, */
    /*  increment PC */
    /* '<S10>:1:31' PC_value = fi(PC_value + 1, 0, 8, 0, hdl_fm); */
    hdlcodercpu_eml_DW.PC_value++;
    break;
  }

  /* End of MATLAB Function: '<S1>/Program Counter' */

  /* MATLAB Function: '<S1>/Instruction ROM' */
  /* MATLAB Function 'CPU_Subsystem_8_bit/Instruction ROM': '<S7>:1' */
  /* % Instruction Memory */
  /*  read == 1 => read from IM */
  /*  HDL specific fimath */
  /* '<S7>:1:7' hdl_fm = fimath(... */
  /* '<S7>:1:8' 'RoundMode', 'floor',... */
  /* '<S7>:1:9' 'OverflowMode', 'wrap',... */
  /* '<S7>:1:10' 'ProductMode', 'FullPrecision', 'ProductWordLength', 32,... */
  /* '<S7>:1:11' 'SumMode', 'FullPrecision', 'SumWordLength', 32,... */
  /* '<S7>:1:12' 'CastBeforeSum', true); */
  /* '<S7>:1:16' if(isempty(data)) */
  /*  ASSEMBLED CODE from sort1.in */
  /* '<S7>:1:21' data(1) = fi(2314, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[0] = 2314U;

  /*  LI 10 */
  /* '<S7>:1:22' data(2) = fi(2560, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[1] = 2560U;

  /*  STA 0 */
  /* '<S7>:1:23' data(3) = fi(2316, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[2] = 2316U;

  /*  LI 12 */
  /* '<S7>:1:24' data(4) = fi(2561, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[3] = 2561U;

  /*  STA 1 */
  /* '<S7>:1:25' data(5) = fi(2322, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[4] = 2322U;

  /*  LI 18 */
  /* '<S7>:1:26' data(6) = fi(2572, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[5] = 2572U;

  /*  STA 12 */
  /* '<S7>:1:27' data(7) = fi(2310, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[6] = 2310U;

  /*  LI 6 */
  /* '<S7>:1:28' data(8) = fi(2573, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[7] = 2573U;

  /*  STA 13 */
  /* '<S7>:1:29' data(9) = fi(2323, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[8] = 2323U;

  /*  LI 19 */
  /* '<S7>:1:30' data(10) = fi(2574, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[9] = 2574U;

  /*  STA 14 */
  /* '<S7>:1:31' data(11) = fi(2555, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[10] = 2555U;

  /*  LI 251 */
  /* '<S7>:1:32' data(12) = fi(2575, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[11] = 2575U;

  /*  STA 15 */
  /* '<S7>:1:33' data(13) = fi(2319, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[12] = 2319U;

  /*  LI 15 */
  /* '<S7>:1:34' data(14) = fi(2576, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[13] = 2576U;

  /*  STA 16 */
  /* '<S7>:1:35' data(15) = fi(2558, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[14] = 2558U;

  /*  LI 254 */
  /* '<S7>:1:36' data(16) = fi(2577, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[15] = 2577U;

  /*  STA 17 */
  /* '<S7>:1:37' data(17) = fi(2306, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[16] = 2306U;

  /*  LI 2 */
  /* '<S7>:1:38' data(18) = fi(2578, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[17] = 2578U;

  /*  STA 18 */
  /* '<S7>:1:39' data(19) = fi(2315, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[18] = 2315U;

  /*  LI 11 */
  /* '<S7>:1:40' data(20) = fi(2579, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[19] = 2579U;

  /*  STA 19 */
  /* '<S7>:1:41' data(21) = fi(2324, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[20] = 2324U;

  /*  LI 20 */
  /* '<S7>:1:42' data(22) = fi(2580, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[21] = 2580U;

  /*  STA 20 */
  /* '<S7>:1:43' data(23) = fi(2314, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[22] = 2314U;

  /*  LI 10 */
  /* '<S7>:1:44' data(24) = fi(2581, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[23] = 2581U;

  /*  STA 21 */
  /* '<S7>:1:45' data(25) = fi(2305, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[24] = 2305U;

  /*  LI 1 */
  /* '<S7>:1:46' data(26) = fi(2562, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[25] = 2562U;

  /*  STA 2 */
  /* '<S7>:1:47' data(27) = fi(2305, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[26] = 2305U;

  /*  LI 1 */
  /* '<S7>:1:48' data(28) = fi(2563, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[27] = 2563U;

  /*  STA 3 */
  /* '<S7>:1:49' data(29) = fi(2305, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[28] = 2305U;

  /*  LI 1 */
  /* '<S7>:1:50' data(30) = fi(2564, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[29] = 2564U;

  /*  STA 4 */
  /* '<S7>:1:51' data(31) = fi(2, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[30] = 2U;

  /*  LDA 2 */
  /* '<S7>:1:52' data(32) = fi(3704, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[31] = 3704U;

  /*  CLC */
  /* '<S7>:1:53' data(33) = fi(1540, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[32] = 1540U;

  /*  SUB 4 */
  /* '<S7>:1:54' data(34) = fi(3704, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[33] = 3704U;

  /*  CLC */
  /* '<S7>:1:55' data(35) = fi(1025, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[34] = 1025U;

  /*  ADD 1 */
  /* '<S7>:1:56' data(36) = fi(2565, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[35] = 2565U;

  /*  STA 5 */
  /* '<S7>:1:57' data(37) = fi(261, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[36] = 261U;

  /*  LDAI 5 */
  /* '<S7>:1:58' data(38) = fi(2566, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[37] = 2566U;

  /*  STA 6 */
  /* '<S7>:1:59' data(39) = fi(2, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[38] = 2U;

  /*  LDA 2 */
  /* '<S7>:1:60' data(40) = fi(3704, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[39] = 3704U;

  /*  CLC */
  /* '<S7>:1:61' data(41) = fi(1025, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[40] = 1025U;

  /*  ADD 1 */
  /* '<S7>:1:62' data(42) = fi(2567, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[41] = 2567U;

  /*  STA 7 */
  /* '<S7>:1:63' data(43) = fi(263, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[42] = 263U;

  /*  LDAI 7 */
  /* '<S7>:1:64' data(44) = fi(3704, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[43] = 3704U;

  /*  CLC */
  /* '<S7>:1:65' data(45) = fi(1542, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[44] = 1542U;

  /*  SUB 6 */
  /* '<S7>:1:66' data(46) = fi(3330, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[45] = 3330U;

  /*  BRA_N 2 */
  /* '<S7>:1:67' data(47) = fi(2055, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[46] = 2055U;

  /*  JMP 7 */
  /* '<S7>:1:68' data(48) = fi(2304, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[47] = 2304U;

  /*  LI 0 */
  /* '<S7>:1:69' data(49) = fi(2563, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[48] = 2563U;

  /*  STA 3 */
  /* '<S7>:1:70' data(50) = fi(263, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[49] = 263U;

  /*  LDAI 7 */
  /* '<S7>:1:71' data(51) = fi(2821, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[50] = 2821U;

  /*  STAI 5 */
  /* '<S7>:1:72' data(52) = fi(6, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[51] = 6U;

  /*  LDA 6 */
  /* '<S7>:1:73' data(53) = fi(2823, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[52] = 2823U;

  /*  STAI 7 */
  /* '<S7>:1:74' data(54) = fi(2305, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[53] = 2305U;

  /*  LI 1 */
  /* '<S7>:1:75' data(55) = fi(3704, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[54] = 3704U;

  /*  CLC */
  /* '<S7>:1:76' data(56) = fi(1026, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[55] = 1026U;

  /*  ADD 2 */
  /* '<S7>:1:77' data(57) = fi(2562, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[56] = 2562U;

  /*  STA 2 */
  /* '<S7>:1:78' data(58) = fi(0, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[57] = 0U;

  /*  LDA 0 */
  /* '<S7>:1:79' data(59) = fi(3704, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[58] = 3704U;

  /*  CLC */
  /* '<S7>:1:80' data(60) = fi(1538, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[59] = 1538U;

  /*  SUB 2 */
  /* '<S7>:1:81' data(61) = fi(3842, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[60] = 3842U;

  /*  BRA_Z 2 */
  /* '<S7>:1:82' data(62) = fi(2271, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[61] = 2271U;

  /*  JMP -33 */
  /* '<S7>:1:83' data(63) = fi(2305, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[62] = 2305U;

  /*  LI 1 */
  /* '<S7>:1:84' data(64) = fi(2564, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[63] = 2564U;

  /*  STA 4 */
  /* '<S7>:1:85' data(65) = fi(3, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[64] = 3U;

  /*  LDA 3 */
  /* '<S7>:1:86' data(66) = fi(3704, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[65] = 3704U;

  /*  CLC */
  /* '<S7>:1:87' data(67) = fi(1540, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[66] = 1540U;

  /*  SUB 4 */
  /* '<S7>:1:88' data(68) = fi(3842, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[67] = 3842U;

  /*  BRA_Z 2 */
  /* '<S7>:1:89' data(69) = fi(2260, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[68] = 2260U;

  /*  JMP -44 */
  /* '<S7>:1:90' data(70) = fi(2304, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[69] = 2304U;

  /*  LI 0 */
  /* '<S7>:1:91' data(71) = fi(2562, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[70] = 2562U;

  /*  STA 2 */
  /* '<S7>:1:92' data(72) = fi(257, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[71] = 257U;

  /*  LDAI 1 */
  /* '<S7>:1:93' data(73) = fi(2815, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[72] = 2815U;

  /*  STA 255 */
  /* '<S7>:1:94' data(74) = fi(3696, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[73] = 3696U;

  /*  PRINT */
  /* '<S7>:1:95' data(75) = fi(2305, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[74] = 2305U;

  /*  LI 1 */
  /* '<S7>:1:96' data(76) = fi(3704, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[75] = 3704U;

  /*  CLC */
  /* '<S7>:1:97' data(77) = fi(1025, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[76] = 1025U;

  /*  ADD 1 */
  /* '<S7>:1:98' data(78) = fi(2561, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[77] = 2561U;

  /*  STA 1 */
  /* '<S7>:1:99' data(79) = fi(2305, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[78] = 2305U;

  /*  LI 1 */
  /* '<S7>:1:100' data(80) = fi(3704, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[79] = 3704U;

  /*  CLC */
  /* '<S7>:1:101' data(81) = fi(1026, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[80] = 1026U;

  /*  ADD 2 */
  /* '<S7>:1:102' data(82) = fi(2562, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[81] = 2562U;

  /*  STA 2 */
  /* '<S7>:1:103' data(83) = fi(0, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[82] = 0U;

  /*  LDA 0 */
  /* '<S7>:1:104' data(84) = fi(3704, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[83] = 3704U;

  /*  CLC */
  /* '<S7>:1:105' data(85) = fi(1538, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[84] = 1538U;

  /*  SUB 2 */
  /* '<S7>:1:106' data(86) = fi(3842, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[85] = 3842U;

  /*  BRA_Z 2 */
  /* '<S7>:1:107' data(87) = fi(2289, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[86] = 2289U;

  /*  JMP -15 */
  /* '<S7>:1:108' data(88) = fi(3648, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_DW.data[87] = 3648U;

  /*  HLT */
  /*  Loading from memory */
  /* '<S7>:1:112' if(read == 1) */
  if (rtb_IM_read == 1) {
    /* '<S7>:1:113' instr_out = data(addr+1); */
    i = (int32_T)(hdlcodercpu_eml_B.addr_out + 1U);
    if ((uint32_T)i > 255U) {
      i = 255;
    }

    rtb_instr_out = hdlcodercpu_eml_DW.data[i - 1];
  } else {
    /* '<S7>:1:114' else */
    /* '<S7>:1:115' instr_out = fi(0, 0, 12, 0, hdl_fm); */
    rtb_instr_out = 0U;
  }

  /* End of MATLAB Function: '<S1>/Instruction ROM' */

  /* MATLAB Function: '<S1>/Instruction Register' */
  /* MATLAB Function 'CPU_Subsystem_8_bit/Instruction Register': '<S8>:1' */
  /*  A 12-bit Instruction Register with the following func: */
  /*  func == 0 => reset */
  /*  func == 1 => store into IR */
  /*  func == 2 => read from IR; */
  /*  otherwise, preserve old value and return 0 */
  /*  HDL specific fimath */
  /* '<S8>:1:9' hdl_fm = fimath(... */
  /* '<S8>:1:10' 'RoundMode', 'floor',... */
  /* '<S8>:1:11' 'OverflowMode', 'wrap',... */
  /* '<S8>:1:12' 'ProductMode', 'FullPrecision', 'ProductWordLength', 32,... */
  /* '<S8>:1:13' 'SumMode', 'FullPrecision', 'SumWordLength', 32,... */
  /* '<S8>:1:14' 'CastBeforeSum', true); */
  /* '<S8>:1:18' if(isempty(IR_value)) */
  /* '<S8>:1:22' IR_out = fi(0, 0, 12, 0, hdl_fm); */
  hdlcodercpu_eml_B.IR_out = 0U;

  /* '<S8>:1:24' switch(uint8(func)) */
  switch (rtb_IR_func) {
   case 0U:
    /* '<S8>:1:25' case 0, */
    /*  reset */
    /* '<S8>:1:27' IR_value = fi(0, 0, 12, 0, hdl_fm); */
    hdlcodercpu_eml_DW.IR_value = 0U;
    break;

   case 1U:
    /* '<S8>:1:28' case 1, */
    /*  store into IR */
    /* '<S8>:1:30' IR_value = IR_in; */
    hdlcodercpu_eml_DW.IR_value = rtb_instr_out;
    break;

   case 2U:
    /* '<S8>:1:31' case 2, */
    /*  read IR */
    /* '<S8>:1:33' IR_out = IR_value; */
    hdlcodercpu_eml_B.IR_out = hdlcodercpu_eml_DW.IR_value;
    break;
  }

  /* End of MATLAB Function: '<S1>/Instruction Register' */

  /* MATLAB Function: '<S1>/Shifter (8-bit)' incorporates:
   *  MATLAB Function: '<S1>/Arithmetic Logical Unit (8-bit)'
   */
  /* MATLAB Function 'CPU_Subsystem_8_bit/Shifter (8-bit)': '<S11>:1' */
  /*  An 8-bit shifter: */
  /*  select = 1 => shift left by 1 bit */
  /*  select = 2 => shift right by 1 bit */
  /*  otherwise, pass the input */
  /*  HDL specific fimath */
  /* '<S11>:1:8' hdl_fm = fimath(... */
  /* '<S11>:1:9' 'RoundMode', 'floor',... */
  /* '<S11>:1:10' 'OverflowMode', 'wrap',... */
  /* '<S11>:1:11' 'ProductMode', 'FullPrecision', 'ProductWordLength', 32,... */
  /* '<S11>:1:12' 'SumMode', 'FullPrecision', 'SumWordLength', 32,... */
  /* '<S11>:1:13' 'CastBeforeSum', true); */
  /*  Overflow (V) */
  /* '<S11>:1:16' overflow = bitget(in_flags, 2); */
  rtb_out_flags = (uint8_T)((int32_T)((uint32_T)rtb_ALU_func >> 1) & 1);

  /*  Carry (C) */
  /* '<S11>:1:19' c_out = bitget(in_flags, 4); */
  rtb_AC_func = (uint8_T)((uint32_T)rtb_ALU_func >> 3);

  /* '<S11>:1:21' switch(uint8(select)) */
  switch (rtb_shifter_sel) {
   case 1U:
    /* '<S11>:1:22' case 1, */
    /*  shift left */
    /*  affects C and V as well */
    /* '<S11>:1:25' shift_out = bitsll(input, 1); */
    rtb_AC_data = (int8_T)(diff << 1);

    /*  Carry (C) */
    /* '<S11>:1:27' c_out = bitget(input, 8); */
    rtb_AC_func = (uint8_T)((uint32_T)(uint8_T)diff >> 7);

    /*  Overflow (V) */
    /* '<S11>:1:29' overflow = bitxor(bitget(input, 8), bitget(input, 7)); */
    rtb_out_flags = (uint8_T)(((int32_T)((uint32_T)(uint8_T)diff >> 6) & 1) ^
      (int32_T)((uint32_T)(uint8_T)diff >> 7));
    break;

   case 2U:
    /* '<S11>:1:30' case 2, */
    /*  shift right */
    /* '<S11>:1:32' shift_out = bitsra(input, 1); */
    rtb_AC_data = (int8_T)(diff >> 1);
    break;

   default:
    /* '<S11>:1:33' otherwise */
    /*  pass the input */
    /* '<S11>:1:35' shift_out = fi(input, 1, 8, 0, hdl_fm); */
    rtb_AC_data = diff;
    break;
  }

  /*  Negativity  (N) */
  /* '<S11>:1:39' sign_bit = getmsb(shift_out); */
  /*  Is Zero? (Z) */
  /* '<S11>:1:42' is_zero = uint8(~all(shift_out)); */
  /* '<S11>:1:43' zero_ufix1 = fi(is_zero, 0, 1, 0, hdl_fm); */
  /*  Set [C, N, V, Z] in the flag register */
  /* '<S11>:1:46' out_flags = bitconcat(bitconcat(bitconcat(c_out, sign_bit), overflow), zero_ufix1); */
  hdlcodercpu_eml_B.out_flags = (uint8_T)(((rtb_AC_func << 1 | (int32_T)
    ((uint32_T)(uint8_T)rtb_AC_data >> 7)) << 1 | rtb_out_flags) << 1 |
    !(rtb_AC_data != 0));
  hdlcodercpu_eml_B.shift_out = rtb_AC_data;

  /* End of MATLAB Function: '<S1>/Shifter (8-bit)' */

  /* MATLAB Function: '<S1>/output_enable' */
  /* MATLAB Function 'CPU_Subsystem_8_bit/output_enable': '<S12>:1' */
  /*  to the pin-out */
  /*  HDL specific fimath */
  /* '<S12>:1:5' hdl_fm = fimath(... */
  /* '<S12>:1:6' 'RoundMode', 'floor',... */
  /* '<S12>:1:7' 'OverflowMode', 'wrap',... */
  /* '<S12>:1:8' 'ProductMode', 'FullPrecision', 'ProductWordLength', 32,... */
  /* '<S12>:1:9' 'SumMode', 'FullPrecision', 'SumWordLength', 32,... */
  /* '<S12>:1:10' 'CastBeforeSum', true); */
  /* '<S12>:1:12' y = fi(0, 1, 8, 0, hdl_fm); */
  hdlcodercpu_eml_B.y = 0;

  /* '<S12>:1:14' if(enable) */
  if (rtb_print_data) {
    /* '<S12>:1:15' y = fi(u, 1, 8, 0, hdl_fm); */
    hdlcodercpu_eml_B.y = hdlcodercpu_eml_B.Switch1;
  }

  /* End of MATLAB Function: '<S1>/output_enable' */
}

/* Model update function */
static void hdlcodercpu_eml_update(void)
{
  /* Update for UnitDelay: '<S1>/Unit Delay 6' */
  hdlcodercpu_eml_DW.UnitDelay6_DSTATE = hdlcodercpu_eml_B.y;

  /* Update for UnitDelay: '<S1>/Unit Delay 5' */
  hdlcodercpu_eml_DW.UnitDelay5_DSTATE = hdlcodercpu_eml_B.Switch1;

  /* Update for UnitDelay: '<S1>/Unit Delay 3' */
  hdlcodercpu_eml_DW.UnitDelay3_DSTATE = hdlcodercpu_eml_B.out_flags;

  /* Update for UnitDelay: '<S1>/Unit Delay 7' incorporates:
   *  Constant: '<Root>/Master Reset'
   */
  hdlcodercpu_eml_DW.UnitDelay7_DSTATE = false;

  /* Update for UnitDelay: '<S1>/Unit Delay 1' */
  hdlcodercpu_eml_DW.UnitDelay1_DSTATE = hdlcodercpu_eml_B.IR_out;

  /* Update for UnitDelay: '<S1>/Unit Delay2' */
  hdlcodercpu_eml_DW.UnitDelay2_DSTATE = hdlcodercpu_eml_B.shift_out;

  /* Update for UnitDelay: '<S6>/din_d' */
  hdlcodercpu_eml_DW.din_d_DSTATE = hdlcodercpu_eml_B.AC_out;

  /* Update for UnitDelay: '<S6>/we_d' */
  hdlcodercpu_eml_DW.we_d_DSTATE = hdlcodercpu_eml_B.DataTypeConversion;

  /* Update for UnitDelay: '<S6>/ram_data' */
  hdlcodercpu_eml_DW.ram_data_DSTATE = hdlcodercpu_eml_B.select;

  /* Update for UnitDelay: '<S6>/ram' */
  memcpy(&hdlcodercpu_eml_DW.ram_DSTATE[0], &hdlcodercpu_eml_B.switch_i[0],
         sizeof(int8_T) << 8U);

  /* Update for UnitDelay: '<S1>/Unit Delay 4' */
  hdlcodercpu_eml_DW.UnitDelay4_DSTATE = hdlcodercpu_eml_B.addr_out;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++hdlcodercpu_eml_M->Timing.clockTick0)) {
    ++hdlcodercpu_eml_M->Timing.clockTickH0;
  }

  hdlcodercpu_eml_M->Timing.t[0] = hdlcodercpu_eml_M->Timing.clockTick0 *
    hdlcodercpu_eml_M->Timing.stepSize0 + hdlcodercpu_eml_M->Timing.clockTickH0 *
    hdlcodercpu_eml_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void hdlcodercpu_eml_initialize(void)
{
  {
    int32_T i;

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay 6' */
    hdlcodercpu_eml_DW.UnitDelay6_DSTATE = 0;

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay 5' */
    hdlcodercpu_eml_DW.UnitDelay5_DSTATE = 0;

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay 3' */
    hdlcodercpu_eml_DW.UnitDelay3_DSTATE = ((uint8_T)0U);

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay 7' */
    hdlcodercpu_eml_DW.UnitDelay7_DSTATE = false;

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay 1' */
    hdlcodercpu_eml_DW.UnitDelay1_DSTATE = ((uint16_T)0U);

    /* InitializeConditions for MATLAB Function: '<S1>/Control Unit' */
    hdlcodercpu_eml_DW.CPU_state = 0U;
    hdlcodercpu_eml_DW.previous_CPU_state = 0U;
    hdlcodercpu_eml_DW.major_opcode = 0U;
    hdlcodercpu_eml_DW.minor_opcode = 0U;
    hdlcodercpu_eml_DW.address_data = 0U;
    hdlcodercpu_eml_DW.indirect_address = 0U;

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay2' */
    hdlcodercpu_eml_DW.UnitDelay2_DSTATE = 0;

    /* InitializeConditions for MATLAB Function: '<S1>/Accumulator' */
    hdlcodercpu_eml_DW.AC_value = 0;

    /* InitializeConditions for UnitDelay: '<S6>/din_d' */
    hdlcodercpu_eml_DW.din_d_DSTATE = 0;

    /* InitializeConditions for UnitDelay: '<S6>/we_d' */
    hdlcodercpu_eml_DW.we_d_DSTATE = false;

    /* InitializeConditions for UnitDelay: '<S6>/ram_data' */
    hdlcodercpu_eml_DW.ram_data_DSTATE = 0;

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay 4' */
    hdlcodercpu_eml_DW.UnitDelay4_DSTATE = ((uint8_T)0U);

    /* InitializeConditions for MATLAB Function: '<S1>/Program Counter' */
    hdlcodercpu_eml_DW.PC_value = 0U;
    for (i = 0; i < 256; i++) {
      /* InitializeConditions for UnitDelay: '<S6>/ram' */
      hdlcodercpu_eml_DW.ram_DSTATE[i] = 0;

      /* InitializeConditions for MATLAB Function: '<S1>/Instruction ROM' */
      hdlcodercpu_eml_DW.data[i] = 0U;
    }

    /* InitializeConditions for MATLAB Function: '<S1>/Instruction Register' */
    hdlcodercpu_eml_DW.IR_value = 0U;
  }
}

/* Model terminate function */
void hdlcodercpu_eml_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  hdlcodercpu_eml_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  hdlcodercpu_eml_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  hdlcodercpu_eml_initialize();
}

void MdlTerminate(void)
{
  hdlcodercpu_eml_terminate();
}

/* Registration function */
RT_MODEL_hdlcodercpu_eml_T *hdlcodercpu_eml(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)hdlcodercpu_eml_M, 0,
                sizeof(RT_MODEL_hdlcodercpu_eml_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = hdlcodercpu_eml_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    hdlcodercpu_eml_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    hdlcodercpu_eml_M->Timing.sampleTimes =
      (&hdlcodercpu_eml_M->Timing.sampleTimesArray[0]);
    hdlcodercpu_eml_M->Timing.offsetTimes =
      (&hdlcodercpu_eml_M->Timing.offsetTimesArray[0]);

    /* task periods */
    hdlcodercpu_eml_M->Timing.sampleTimes[0] = (1.0);

    /* task offsets */
    hdlcodercpu_eml_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(hdlcodercpu_eml_M, &hdlcodercpu_eml_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = hdlcodercpu_eml_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    hdlcodercpu_eml_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(hdlcodercpu_eml_M, 1.0E+7);
  hdlcodercpu_eml_M->Timing.stepSize0 = 1.0;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    hdlcodercpu_eml_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(hdlcodercpu_eml_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(hdlcodercpu_eml_M->rtwLogInfo, (NULL));
    rtliSetLogT(hdlcodercpu_eml_M->rtwLogInfo, "");
    rtliSetLogX(hdlcodercpu_eml_M->rtwLogInfo, "");
    rtliSetLogXFinal(hdlcodercpu_eml_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(hdlcodercpu_eml_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(hdlcodercpu_eml_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(hdlcodercpu_eml_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(hdlcodercpu_eml_M->rtwLogInfo, 1);
    rtliSetLogY(hdlcodercpu_eml_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(hdlcodercpu_eml_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(hdlcodercpu_eml_M->rtwLogInfo, (NULL));
  }

  hdlcodercpu_eml_M->solverInfoPtr = (&hdlcodercpu_eml_M->solverInfo);
  hdlcodercpu_eml_M->Timing.stepSize = (1.0);
  rtsiSetFixedStepSize(&hdlcodercpu_eml_M->solverInfo, 1.0);
  rtsiSetSolverMode(&hdlcodercpu_eml_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  hdlcodercpu_eml_M->ModelData.blockIO = ((void *) &hdlcodercpu_eml_B);
  (void) memset(((void *) &hdlcodercpu_eml_B), 0,
                sizeof(B_hdlcodercpu_eml_T));

  /* states (dwork) */
  hdlcodercpu_eml_M->ModelData.dwork = ((void *) &hdlcodercpu_eml_DW);
  (void) memset((void *)&hdlcodercpu_eml_DW, 0,
                sizeof(DW_hdlcodercpu_eml_T));

  /* Initialize Sizes */
  hdlcodercpu_eml_M->Sizes.numContStates = (0);/* Number of continuous states */
  hdlcodercpu_eml_M->Sizes.numY = (0); /* Number of model outputs */
  hdlcodercpu_eml_M->Sizes.numU = (0); /* Number of model inputs */
  hdlcodercpu_eml_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  hdlcodercpu_eml_M->Sizes.numSampTimes = (1);/* Number of sample times */
  hdlcodercpu_eml_M->Sizes.numBlocks = (44);/* Number of blocks */
  hdlcodercpu_eml_M->Sizes.numBlockIO = (10);/* Number of block outputs */
  return hdlcodercpu_eml_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
