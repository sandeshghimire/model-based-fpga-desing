-- -------------------------------------------------------------
-- 
-- File Name: hdlsrc\Shifter_8_bit.vhd
-- Created: 2014-03-05 16:19:14
-- 
-- Generated by MATLAB 7.12 and Simulink HDL Coder 2.1
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Shifter_8_bit
-- Source Path: hdlcodercpu_eml/CPU_Subsystem_8_bit/Shifter (8-bit)
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY Shifter_8_bit IS
  PORT( select_rsvd                       :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
        input                             :   IN    std_logic_vector(7 DOWNTO 0);  -- int8
        in_flags                          :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
        out_flags                         :   OUT   std_logic_vector(3 DOWNTO 0);  -- ufix4
        shift_out                         :   OUT   std_logic_vector(7 DOWNTO 0)  -- int8
        );
END Shifter_8_bit;


ARCHITECTURE rtl OF Shifter_8_bit IS

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
  SIGNAL select_unsigned                  : unsigned(1 DOWNTO 0);  -- ufix2
  SIGNAL input_signed                     : signed(7 DOWNTO 0);  -- int8
  SIGNAL in_flags_unsigned                : unsigned(3 DOWNTO 0);  -- ufix4
  SIGNAL out_flags_tmp                    : unsigned(3 DOWNTO 0);  -- ufix4
  SIGNAL shift_out_tmp                    : signed(7 DOWNTO 0);  -- int8

BEGIN
  select_unsigned <= unsigned(select_rsvd);

  input_signed <= signed(input);

  in_flags_unsigned <= unsigned(in_flags);

  Shifter_8_bit_1_output : PROCESS (select_unsigned, input_signed, in_flags_unsigned)
    VARIABLE c_out : std_logic;
    VARIABLE sign_bit : std_logic;
    VARIABLE is_zero : unsigned(7 DOWNTO 0);
    VARIABLE zero_ufix1 : std_logic;
    VARIABLE c_uint : std_logic;
    VARIABLE c : signed(7 DOWNTO 0);
    VARIABLE c_0 : std_logic;
  BEGIN
    --MATLAB Function 'CPU_Subsystem_8_bit/Shifter (8-bit)': '<S11>:1'
    -- An 8-bit shifter:
    -- select = 1 => shift left by 1 bit
    -- select = 2 => shift right by 1 bit
    -- otherwise, pass the input
    -- HDL specific fimath
    -- Overflow (V)
    --'<S11>:1:16'
    c_uint := in_flags_unsigned(1);
    -- Carry (C)
    --'<S11>:1:19'
    c_out := in_flags_unsigned(3);

    CASE select_unsigned IS
      WHEN "01" =>
        -- shift left
        -- affects C and V as well
        --'<S11>:1:25'
        c := input_signed sll 1;
        -- Carry (C)
        --'<S11>:1:27'
        c_out := input_signed(7);
        -- Overflow (V)
        --'<S11>:1:29'
        c_uint := input_signed(7) XOR input_signed(6);
      WHEN "10" =>
        -- shift right
        --'<S11>:1:32'
        c := SHIFT_RIGHT(input_signed , 1);
      WHEN OTHERS => 
        -- pass the input
        --'<S11>:1:35'
        c := input_signed;
    END CASE;

    -- Negativity  (N)
    --'<S11>:1:39'
    sign_bit := c(7);
    -- Is Zero? (Z)
    --'<S11>:1:42'
    c_0 := hdlcoder_to_stdlogic( NOT (c /= 0));
    is_zero := '0' & '0' & '0' & '0' & '0' & '0' & '0' & c_0;
    --'<S11>:1:43'
    zero_ufix1 := is_zero(0);
    -- Set [C, N, V, Z] in the flag register
    --'<S11>:1:46'
    out_flags_tmp <= unsigned'(c_out & sign_bit & c_uint & zero_ufix1);
    shift_out_tmp <= c;
  END PROCESS Shifter_8_bit_1_output;


  out_flags <= std_logic_vector(out_flags_tmp);

  shift_out <= std_logic_vector(shift_out_tmp);

END rtl;

