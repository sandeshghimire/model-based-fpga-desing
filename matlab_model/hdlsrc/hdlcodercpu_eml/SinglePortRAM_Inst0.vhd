-- -------------------------------------------------------------
-- 
-- File Name: hdlsrc\hdlcodercpu_eml\SinglePortRAM_Inst0.vhd
-- Created: 2014-08-26 11:41:14
-- 
-- Generated by MATLAB 8.3 and HDL Coder 3.4
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: SinglePortRAM_Inst0
-- Source Path: hdlcodercpu_eml/CPU_Subsystem_8_bit/SinglePortRAM_Inst0
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY SinglePortRAM_Inst0 IS
  PORT( clk                               :   IN    std_logic;
        enb                               :   IN    std_logic;
        din                               :   IN    std_logic_vector(7 DOWNTO 0);  -- int8
        addr                              :   IN    std_logic_vector(7 DOWNTO 0);  -- uint8
        we                                :   IN    std_logic;  -- ufix1
        dout                              :   OUT   std_logic_vector(7 DOWNTO 0)  -- int8
        );
END SinglePortRAM_Inst0;


ARCHITECTURE rtl OF SinglePortRAM_Inst0 IS

  -- Component Declarations
  COMPONENT SinglePortRAM_256x8b
    PORT( clk                             :   IN    std_logic;
          enb                             :   IN    std_logic;
          din                             :   IN    std_logic_vector(7 DOWNTO 0);  -- int8
          addr                            :   IN    std_logic_vector(7 DOWNTO 0);  -- uint8
          we                              :   IN    std_logic;  -- ufix1
          dout                            :   OUT   std_logic_vector(7 DOWNTO 0)  -- int8
          );
  END COMPONENT;

  -- Component Configuration Statements
  FOR ALL : SinglePortRAM_256x8b
    USE ENTITY work.SinglePortRAM_256x8b(rtl);

  -- Signals
  SIGNAL dout_tmp                         : std_logic_vector(7 DOWNTO 0);  -- ufix8

BEGIN
  u_SinglePortRAM_256x8b : SinglePortRAM_256x8b
    PORT MAP( clk => clk,
              enb => enb,
              din => din,  -- int8
              addr => addr,  -- uint8
              we => we,  -- ufix1
              dout => dout_tmp  -- int8
              );

  dout <= dout_tmp;

END rtl;

