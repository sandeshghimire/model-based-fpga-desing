-- -------------------------------------------------------------
-- 
-- File Name: hdlsrc\Instruction_Register.vhd
-- Created: 2014-03-05 16:19:14
-- 
-- Generated by MATLAB 7.12 and Simulink HDL Coder 2.1
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Instruction_Register
-- Source Path: hdlcodercpu_eml/CPU_Subsystem_8_bit/Instruction Register
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY Instruction_Register IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        func                              :   IN    std_logic_vector(1 DOWNTO 0);  -- ufix2
        IR_in                             :   IN    std_logic_vector(11 DOWNTO 0);  -- ufix12
        IR_out                            :   OUT   std_logic_vector(11 DOWNTO 0)  -- ufix12
        );
END Instruction_Register;


ARCHITECTURE rtl OF Instruction_Register IS

  -- Signals
  SIGNAL func_unsigned                    : unsigned(1 DOWNTO 0);  -- ufix2
  SIGNAL IR_in_unsigned                   : unsigned(11 DOWNTO 0);  -- ufix12
  SIGNAL IR_out_tmp                       : unsigned(11 DOWNTO 0);  -- ufix12
  SIGNAL IR_value                         : unsigned(11 DOWNTO 0);  -- ufix12
  SIGNAL IR_value_next                    : unsigned(11 DOWNTO 0);  -- ufix12

BEGIN
  func_unsigned <= unsigned(func);

  IR_in_unsigned <= unsigned(IR_in);

  Instruction_Register_1_process : PROCESS (clk, reset)
  BEGIN
    IF reset = '1' THEN
      IR_value <= to_unsigned(0, 12);
    ELSIF clk'EVENT AND clk = '1' THEN
      IF enb = '1' THEN
        IR_value <= IR_value_next;
      END IF;
    END IF;
  END PROCESS Instruction_Register_1_process;

  Instruction_Register_1_output : PROCESS (func_unsigned, IR_in_unsigned, IR_value)
  BEGIN
    IR_value_next <= IR_value;
    --MATLAB Function 'CPU_Subsystem_8_bit/Instruction Register': '<S8>:1'
    -- A 12-bit Instruction Register with the following func:
    -- func == 0 => reset
    -- func == 1 => store into IR
    -- func == 2 => read from IR;
    -- otherwise, preserve old value and return 0
    -- HDL specific fimath
    --'<S8>:1:22'
    IR_out_tmp <= to_unsigned(0, 12);

    CASE func_unsigned IS
      WHEN "00" =>
        -- reset
        --'<S8>:1:27'
        IR_value_next <= to_unsigned(0, 12);
      WHEN "01" =>
        -- store into IR
        --'<S8>:1:30'
        IR_value_next <= IR_in_unsigned;
      WHEN "10" =>
        -- read IR
        --'<S8>:1:33'
        IR_out_tmp <= IR_value;
      WHEN OTHERS => 
        NULL;
    END CASE;

  END PROCESS Instruction_Register_1_output;


  IR_out <= std_logic_vector(IR_out_tmp);

END rtl;
