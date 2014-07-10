-- -------------------------------------------------------------
-- 
-- File Name: hdlsrc\output_enable.vhd
-- Created: 2014-03-05 16:19:14
-- 
-- Generated by MATLAB 7.12 and Simulink HDL Coder 2.1
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: output_enable
-- Source Path: hdlcodercpu_eml/CPU_Subsystem_8_bit/output_enable
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY output_enable IS
  PORT( u                                 :   IN    std_logic_vector(7 DOWNTO 0);  -- int8
        enable                            :   IN    std_logic;
        y                                 :   OUT   std_logic_vector(7 DOWNTO 0)  -- int8
        );
END output_enable;


ARCHITECTURE rtl OF output_enable IS

  -- Signals
  SIGNAL u_signed                         : signed(7 DOWNTO 0);  -- int8
  SIGNAL y_tmp                            : signed(7 DOWNTO 0);  -- int8

BEGIN
  u_signed <= signed(u);

  output_enable_1_output : PROCESS (u_signed, enable)
  BEGIN
    --MATLAB Function 'CPU_Subsystem_8_bit/output_enable': '<S12>:1'
    -- to the pin-out
    -- HDL specific fimath
    --'<S12>:1:12'
    y_tmp <= to_signed(0, 8);
    IF enable = '1' THEN 
      --'<S12>:1:14'
      --'<S12>:1:15'
      y_tmp <= u_signed;
    END IF;
  END PROCESS output_enable_1_output;


  y <= std_logic_vector(y_tmp);

END rtl;
