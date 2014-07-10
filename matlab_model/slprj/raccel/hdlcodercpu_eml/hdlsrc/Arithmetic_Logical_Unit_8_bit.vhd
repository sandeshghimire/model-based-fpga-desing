-- -------------------------------------------------------------
-- 
-- File Name: hdlsrc\Arithmetic_Logical_Unit_8_bit.vhd
-- Created: 2014-02-20 13:53:07
-- 
-- Generated by MATLAB 7.12 and Simulink HDL Coder 2.1
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Arithmetic_Logical_Unit_8_bit
-- Source Path: hdlcodercpu_eml/CPU_Subsystem_8_bit/Arithmetic Logical Unit (8-bit)
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY Arithmetic_Logical_Unit_8_bit IS
  PORT( in_flags                          :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
        func                              :   IN    std_logic_vector(2 DOWNTO 0);  -- ufix3
        alu_in                            :   IN    std_logic_vector(7 DOWNTO 0);  -- int8
        AC                                :   IN    std_logic_vector(7 DOWNTO 0);  -- int8
        alu_out                           :   OUT   std_logic_vector(7 DOWNTO 0);  -- int8
        out_flags                         :   OUT   std_logic_vector(3 DOWNTO 0)  -- ufix4
        );
END Arithmetic_Logical_Unit_8_bit;


ARCHITECTURE rtl OF Arithmetic_Logical_Unit_8_bit IS

  -- Functions
  -- HDLCODER_TO_STDLOGIC 
  FUNCTION hdlcoder_to_stdlogic(arg: boolean) RETURN std_logic IS
  BEGIN
    IF arg THEN
      RETURN '1';
    ELSE
      RETURN '0';
    END IF;
  END FUNCTION;


  -- Signals
  SIGNAL in_flags_unsigned                : unsigned(3 DOWNTO 0);  -- ufix4
  SIGNAL func_unsigned                    : unsigned(2 DOWNTO 0);  -- ufix3
  SIGNAL alu_in_signed                    : signed(7 DOWNTO 0);  -- int8
  SIGNAL AC_signed                        : signed(7 DOWNTO 0);  -- int8
  SIGNAL alu_out_tmp                      : signed(7 DOWNTO 0);  -- int8
  SIGNAL out_flags_tmp                    : unsigned(3 DOWNTO 0);  -- ufix4

BEGIN
  in_flags_unsigned <= unsigned(in_flags);

  func_unsigned <= unsigned(func);

  alu_in_signed <= signed(alu_in);

  AC_signed <= signed(AC);

  Arithmetic_Logical_Unit_8_bit_1_output : PROCESS (in_flags_unsigned, func_unsigned, alu_in_signed, AC_signed)
    VARIABLE overflow : std_logic;
    VARIABLE sign_bit : std_logic;
    VARIABLE is_zero : unsigned(7 DOWNTO 0);
    VARIABLE zero_ufix1 : std_logic;
    VARIABLE temp_u1 : signed(8 DOWNTO 0);
    VARIABLE temp_u2 : signed(8 DOWNTO 0);
    VARIABLE temp_sum : signed(8 DOWNTO 0);
    VARIABLE sign_bit_0 : std_logic;
    VARIABLE overflow_int : unsigned(7 DOWNTO 0);
    VARIABLE t_0 : std_logic;
    VARIABLE c_r : signed(7 DOWNTO 0);
    VARIABLE c_r_0 : std_logic;
    VARIABLE temp_u1_0 : signed(8 DOWNTO 0);
    VARIABLE temp_u2_0 : signed(8 DOWNTO 0);
    VARIABLE temp_sum_0 : signed(8 DOWNTO 0);
    VARIABLE sign_bit_1 : std_logic;
    VARIABLE overflow_int_0 : unsigned(7 DOWNTO 0);
    VARIABLE t_1 : std_logic;
    VARIABLE c_r_1 : signed(7 DOWNTO 0);
    VARIABLE c_r_2 : std_logic;
    VARIABLE c_r_3 : std_logic;
    VARIABLE add_cast : signed(10 DOWNTO 0);
    VARIABLE add_temp : signed(10 DOWNTO 0);
    VARIABLE add_cast_0 : signed(10 DOWNTO 0);
    VARIABLE add_temp_0 : signed(10 DOWNTO 0);
  BEGIN
    --MATLAB Function 'CPU_Subsystem_8_bit/Arithmetic Logical Unit (8-bit)': '<S4>:1'
    -- This 8-bit ALU supports the following operations:
    -- AND (Logical AND), ADD, SUB, CMA (Complement AC), CMC (Complement Carry) and CLC (Clear Carry)
    -- and appropriately sets a 4-bit flag register, which has the following format:
    -- [C N V Z]
    -- HDL specific fimath
    -- Get the carry in
    --'<S4>:1:16'
    c_r_2 := in_flags_unsigned(3);
    -- Get the overflow in
    --'<S4>:1:19'
    overflow := in_flags_unsigned(1);
    -- Simply pass the AC, when there is no designated func
    --'<S4>:1:22'
    c_r_1 := AC_signed;
    -- 3-bit encoding of ALU ops, which can potentially support upto 8 operations
    -- Most of the encodings are unused to comply to Parwan supported ops

    CASE func_unsigned IS
      WHEN "000" =>
        -- NOP
        -- simply pass the AC
        NULL;
      WHEN "001" =>
        -- AND
        -- Bitwise AND
        --'<S4>:1:31'
        c_r_1 := alu_in_signed AND AC_signed;
      WHEN "010" =>
        -- ADD
        -- Add with carry and overflow appropriately set
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        --% Full Adder with flag register appropriately set
        -- sum = u1 + u2 + c_in
        -- appropriately set the carry and the overflow
        -- zero-extend u1 by 1 bit for carry detection
        --'<S4>:1:87'
        temp_u1 := signed("0" & unsigned(AC_signed));
        -- zero-extend u2 by 1 bit for carry detection
        --'<S4>:1:90'
        temp_u2 := signed("0" & unsigned(alu_in_signed));
        -- Sum is stored in 9 bits with the msb indicating carry
        --'<S4>:1:93'
        add_cast := '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & c_r_2;
        add_temp := resize(resize(temp_u1, 10) + resize(temp_u2, 10), 11) + add_cast;
        temp_sum := add_temp(8 DOWNTO 0);
        -- Carry  (C)
        --'<S4>:1:96'
        -- Stored back in the designated register
        --'<S4>:1:99'
        c_r_1 := temp_sum(7 DOWNTO 0);
        -- Sign bit
        --'<S4>:1:102'
        sign_bit_0 := c_r_1(7);
        -- if the inputs have the same sign and the output generated has a different sign, 
        -- overflow is generated!
        IF (AC_signed(7) = alu_in_signed(7)) AND (sign_bit_0 /= AC_signed(7)) THEN 
          --'<S4>:1:106'
          t_0 := '1';
        ELSE 
          --'<S4>:1:106'
          t_0 := '0';
        END IF;
        --'<S4>:1:106'
        overflow_int := '0' & '0' & '0' & '0' & '0' & '0' & '0' & t_0;
        -- Overflow (V)
        --'<S4>:1:110'
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        --'<S4>:1:34'
        c_r_2 := temp_sum(8);
        --'<S4>:1:34'
        overflow := overflow_int(0);
      WHEN "011" =>
        -- SUB
        -- Subtract with borrow (set to carry) and overflow appropriately set
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        --% Full Subtracter with flag register appropriately set 
        -- diff = u1 - u2 - b_in = u1 + bitcmp(u2) + bitcmp(b_in)
        -- appropriately set the borrow and the overflow
        c_r :=  NOT alu_in_signed;
        c_r_0 :=  NOT c_r_2;
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        --% Full Adder with flag register appropriately set
        -- sum = u1 + u2 + c_in
        -- appropriately set the carry and the overflow
        -- zero-extend u1 by 1 bit for carry detection
        --'<S4>:1:87'
        temp_u1_0 := signed("0" & unsigned(AC_signed));
        -- zero-extend u2 by 1 bit for carry detection
        --'<S4>:1:90'
        temp_u2_0 := signed("0" & unsigned(c_r));
        -- Sum is stored in 9 bits with the msb indicating carry
        --'<S4>:1:93'
        add_cast_0 := '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & '0' & c_r_0;
        add_temp_0 := resize(resize(temp_u1_0, 10) + resize(temp_u2_0, 10), 11) + add_cast_0;
        temp_sum_0 := add_temp_0(8 DOWNTO 0);
        -- Carry  (C)
        --'<S4>:1:96'
        -- Stored back in the designated register
        --'<S4>:1:99'
        c_r_1 := temp_sum_0(7 DOWNTO 0);
        -- Sign bit
        --'<S4>:1:102'
        sign_bit_1 := c_r_1(7);
        -- if the inputs have the same sign and the output generated has a different sign, 
        -- overflow is generated!
        IF (AC_signed(7) = c_r(7)) AND (sign_bit_1 /= AC_signed(7)) THEN 
          --'<S4>:1:106'
          t_1 := '1';
        ELSE 
          --'<S4>:1:106'
          t_1 := '0';
        END IF;
        --'<S4>:1:106'
        overflow_int_0 := '0' & '0' & '0' & '0' & '0' & '0' & '0' & t_1;
        -- Overflow (V)
        --'<S4>:1:110'
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        --'<S4>:1:70'
        --'<S4>:1:37'
        c_r_2 := temp_sum_0(8);
        --'<S4>:1:37'
        overflow := overflow_int_0(0);
      WHEN "100" =>
        -- CMA
        -- Complement AC
        --'<S4>:1:40'
        c_r_1 :=  NOT AC_signed;
      WHEN "101" =>
        -- CMC
        -- Complement Carry
        --'<S4>:1:43'
        c_r_2 :=  NOT c_r_2;
      WHEN "110" =>
        -- Get alu_in out
        -- Pass the input
        --'<S4>:1:46'
        c_r_1 := alu_in_signed;
      WHEN "111" =>
        -- CLC
        -- Clear Carry
        --'<S4>:1:49'
        c_r_2 := '0';
      WHEN OTHERS => 
        NULL;
    END CASE;

    -- Negativity  (N)
    --'<S4>:1:53'
    sign_bit := c_r_1(7);
    -- Is Zero? (Z)
    --'<S4>:1:56'
    c_r_3 := hdlcoder_to_stdlogic( NOT (c_r_1 /= 0));
    is_zero := '0' & '0' & '0' & '0' & '0' & '0' & '0' & c_r_3;
    --'<S4>:1:57'
    zero_ufix1 := is_zero(0);
    -- Set the output flag register [C N V Z]
    --'<S4>:1:60'
    out_flags_tmp <= unsigned'(c_r_2 & sign_bit & overflow & zero_ufix1);
    alu_out_tmp <= c_r_1;
  END PROCESS Arithmetic_Logical_Unit_8_bit_1_output;


  alu_out <= std_logic_vector(alu_out_tmp);

  out_flags <= std_logic_vector(out_flags_tmp);

END rtl;

