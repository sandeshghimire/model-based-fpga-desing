-- -------------------------------------------------------------
-- 
-- File Name: hdlsrc\Accumulator.vhd
-- Created: 2014-02-20 13:53:07
-- 
-- Generated by MATLAB 7.12 and Simulink HDL Coder 2.1
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Accumulator
-- Source Path: hdlcodercpu_eml/CPU_Subsystem_8_bit/Accumulator
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY Accumulator IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        func                              :   IN    std_logic_vector(2 DOWNTO 0);  -- ufix3
        AC_in1                            :   IN    std_logic_vector(7 DOWNTO 0);  -- int8
        AC_in2                            :   IN    std_logic_vector(7 DOWNTO 0);  -- int8
        AC_out                            :   OUT   std_logic_vector(7 DOWNTO 0)  -- int8
        );
END Accumulator;


ARCHITECTURE rtl OF Accumulator IS

  -- Signals
  SIGNAL func_unsigned                    : unsigned(2 DOWNTO 0);  -- ufix3
  SIGNAL AC_in1_signed                    : signed(7 DOWNTO 0);  -- int8
  SIGNAL AC_in2_signed                    : signed(7 DOWNTO 0);  -- int8
  SIGNAL AC_out_tmp                       : signed(7 DOWNTO 0);  -- int8
  SIGNAL AC_value                         : signed(7 DOWNTO 0);  -- sfix8
  SIGNAL AC_value_next                    : signed(7 DOWNTO 0);  -- sfix8

BEGIN
  func_unsigned <= unsigned(func);

  AC_in1_signed <= signed(AC_in1);

  AC_in2_signed <= signed(AC_in2);

  Accumulator_1_process : PROCESS (clk, reset)
  BEGIN
    IF reset = '1' THEN
      AC_value <= to_signed(0, 8);
    ELSIF clk'EVENT AND clk = '1' THEN
      IF enb = '1' THEN
        AC_value <= AC_value_next;
      END IF;
    END IF;
  END PROCESS Accumulator_1_process;

  Accumulator_1_output : PROCESS (func_unsigned, AC_in1_signed, AC_in2_signed, AC_value)
  BEGIN
    AC_value_next <= AC_value;
    --MATLAB Function 'CPU_Subsystem_8_bit/Accumulator': '<S3>:1'
    --% Accumulator with the following func:
    -- func == 0 => reset
    -- func == 1 => store into AC from port 1
    -- func == 2 => store into AC from port 2
    -- func == 3 => read from AC;
    -- otherwise, preserve old value and return 0
    -- HDL specific fimath
    --'<S3>:1:24'
    AC_out_tmp <= AC_value;

    CASE func_unsigned IS
      WHEN "000" =>
        -- reset
        --'<S3>:1:29'
        AC_value_next <= to_signed(0, 8);
      WHEN "001" =>
        -- store into AC
        --'<S3>:1:32'
        AC_value_next <= AC_in1_signed;
      WHEN "010" =>
        -- store into AC
        --'<S3>:1:35'
        AC_value_next <= AC_in2_signed;
      WHEN "011" =>
        -- read the AC value
        --'<S3>:1:38'
        NULL;
      WHEN OTHERS => 
        NULL;
    END CASE;

  END PROCESS Accumulator_1_output;


  AC_out <= std_logic_vector(AC_out_tmp);

END rtl;

