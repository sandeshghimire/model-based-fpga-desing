-- -------------------------------------------------------------
-- 
-- File Name: hdlsrc\Instruction_ROM.vhd
-- Created: 2014-03-05 16:19:14
-- 
-- Generated by MATLAB 7.12 and Simulink HDL Coder 2.1
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Instruction_ROM
-- Source Path: hdlcodercpu_eml/CPU_Subsystem_8_bit/Instruction ROM
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;
USE work.CPU_Subsystem_8_bit_pkg.ALL;

ENTITY Instruction_ROM IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        addr                              :   IN    std_logic_vector(7 DOWNTO 0);  -- uint8
        read                              :   IN    std_logic;  -- ufix1
        instr_out                         :   OUT   std_logic_vector(11 DOWNTO 0)  -- ufix12
        );
END Instruction_ROM;


ARCHITECTURE rtl OF Instruction_ROM IS

  -- Signals
  SIGNAL addr_unsigned                    : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL instr_out_tmp                    : unsigned(11 DOWNTO 0);  -- ufix12
  SIGNAL data                             : vector_of_unsigned12(0 TO 255);  -- ufix12 [256]
  SIGNAL data_next                        : vector_of_unsigned12(0 TO 255);  -- ufix12 [256]

BEGIN
  addr_unsigned <= unsigned(addr);

  Instruction_ROM_1_process : PROCESS (clk, reset)
  BEGIN
    IF reset = '1' THEN
      data <= (OTHERS => to_unsigned(0, 12));
    ELSIF clk'EVENT AND clk = '1' THEN
      IF enb = '1' THEN
        data <= data_next;
      END IF;
    END IF;
  END PROCESS Instruction_ROM_1_process;

  Instruction_ROM_1_output : PROCESS (addr_unsigned, read, data)
    VARIABLE data_temp : vector_of_unsigned12(0 TO 255);
    VARIABLE add_temp : unsigned(8 DOWNTO 0);
    VARIABLE sub_cast : unsigned(7 DOWNTO 0);
    VARIABLE sub_cast_0 : signed(31 DOWNTO 0);
  BEGIN
    data_temp := data;
    --MATLAB Function 'CPU_Subsystem_8_bit/Instruction ROM': '<S7>:1'
    --% Instruction Memory
    -- read == 1 => read from IM
    -- HDL specific fimath
    -- ASSEMBLED CODE from sort1.in
    --'<S7>:1:21'
    data_temp(0) := to_unsigned(2314, 12);
    -- LI 10
    --'<S7>:1:22'
    data_temp(1) := to_unsigned(2560, 12);
    -- STA 0
    --'<S7>:1:23'
    data_temp(2) := to_unsigned(2316, 12);
    -- LI 12
    --'<S7>:1:24'
    data_temp(3) := to_unsigned(2561, 12);
    -- STA 1
    --'<S7>:1:25'
    data_temp(4) := to_unsigned(2322, 12);
    -- LI 18
    --'<S7>:1:26'
    data_temp(5) := to_unsigned(2572, 12);
    -- STA 12
    --'<S7>:1:27'
    data_temp(6) := to_unsigned(2310, 12);
    -- LI 6
    --'<S7>:1:28'
    data_temp(7) := to_unsigned(2573, 12);
    -- STA 13
    --'<S7>:1:29'
    data_temp(8) := to_unsigned(2323, 12);
    -- LI 19
    --'<S7>:1:30'
    data_temp(9) := to_unsigned(2574, 12);
    -- STA 14
    --'<S7>:1:31'
    data_temp(10) := to_unsigned(2555, 12);
    -- LI 251
    --'<S7>:1:32'
    data_temp(11) := to_unsigned(2575, 12);
    -- STA 15
    --'<S7>:1:33'
    data_temp(12) := to_unsigned(2319, 12);
    -- LI 15
    --'<S7>:1:34'
    data_temp(13) := to_unsigned(2576, 12);
    -- STA 16
    --'<S7>:1:35'
    data_temp(14) := to_unsigned(2558, 12);
    -- LI 254
    --'<S7>:1:36'
    data_temp(15) := to_unsigned(2577, 12);
    -- STA 17
    --'<S7>:1:37'
    data_temp(16) := to_unsigned(2306, 12);
    -- LI 2
    --'<S7>:1:38'
    data_temp(17) := to_unsigned(2578, 12);
    -- STA 18
    --'<S7>:1:39'
    data_temp(18) := to_unsigned(2315, 12);
    -- LI 11
    --'<S7>:1:40'
    data_temp(19) := to_unsigned(2579, 12);
    -- STA 19
    --'<S7>:1:41'
    data_temp(20) := to_unsigned(2324, 12);
    -- LI 20
    --'<S7>:1:42'
    data_temp(21) := to_unsigned(2580, 12);
    -- STA 20
    --'<S7>:1:43'
    data_temp(22) := to_unsigned(2314, 12);
    -- LI 10
    --'<S7>:1:44'
    data_temp(23) := to_unsigned(2581, 12);
    -- STA 21
    --'<S7>:1:45'
    data_temp(24) := to_unsigned(2305, 12);
    -- LI 1
    --'<S7>:1:46'
    data_temp(25) := to_unsigned(2562, 12);
    -- STA 2
    --'<S7>:1:47'
    data_temp(26) := to_unsigned(2305, 12);
    -- LI 1
    --'<S7>:1:48'
    data_temp(27) := to_unsigned(2563, 12);
    -- STA 3
    --'<S7>:1:49'
    data_temp(28) := to_unsigned(2305, 12);
    -- LI 1
    --'<S7>:1:50'
    data_temp(29) := to_unsigned(2564, 12);
    -- STA 4
    --'<S7>:1:51'
    data_temp(30) := to_unsigned(2, 12);
    -- LDA 2
    --'<S7>:1:52'
    data_temp(31) := to_unsigned(3704, 12);
    -- CLC
    --'<S7>:1:53'
    data_temp(32) := to_unsigned(1540, 12);
    -- SUB 4
    --'<S7>:1:54'
    data_temp(33) := to_unsigned(3704, 12);
    -- CLC
    --'<S7>:1:55'
    data_temp(34) := to_unsigned(1025, 12);
    -- ADD 1
    --'<S7>:1:56'
    data_temp(35) := to_unsigned(2565, 12);
    -- STA 5
    --'<S7>:1:57'
    data_temp(36) := to_unsigned(261, 12);
    -- LDAI 5
    --'<S7>:1:58'
    data_temp(37) := to_unsigned(2566, 12);
    -- STA 6
    --'<S7>:1:59'
    data_temp(38) := to_unsigned(2, 12);
    -- LDA 2
    --'<S7>:1:60'
    data_temp(39) := to_unsigned(3704, 12);
    -- CLC
    --'<S7>:1:61'
    data_temp(40) := to_unsigned(1025, 12);
    -- ADD 1
    --'<S7>:1:62'
    data_temp(41) := to_unsigned(2567, 12);
    -- STA 7
    --'<S7>:1:63'
    data_temp(42) := to_unsigned(263, 12);
    -- LDAI 7
    --'<S7>:1:64'
    data_temp(43) := to_unsigned(3704, 12);
    -- CLC
    --'<S7>:1:65'
    data_temp(44) := to_unsigned(1542, 12);
    -- SUB 6
    --'<S7>:1:66'
    data_temp(45) := to_unsigned(3330, 12);
    -- BRA_N 2
    --'<S7>:1:67'
    data_temp(46) := to_unsigned(2055, 12);
    -- JMP 7
    --'<S7>:1:68'
    data_temp(47) := to_unsigned(2304, 12);
    -- LI 0
    --'<S7>:1:69'
    data_temp(48) := to_unsigned(2563, 12);
    -- STA 3
    --'<S7>:1:70'
    data_temp(49) := to_unsigned(263, 12);
    -- LDAI 7
    --'<S7>:1:71'
    data_temp(50) := to_unsigned(2821, 12);
    -- STAI 5
    --'<S7>:1:72'
    data_temp(51) := to_unsigned(6, 12);
    -- LDA 6
    --'<S7>:1:73'
    data_temp(52) := to_unsigned(2823, 12);
    -- STAI 7
    --'<S7>:1:74'
    data_temp(53) := to_unsigned(2305, 12);
    -- LI 1
    --'<S7>:1:75'
    data_temp(54) := to_unsigned(3704, 12);
    -- CLC
    --'<S7>:1:76'
    data_temp(55) := to_unsigned(1026, 12);
    -- ADD 2
    --'<S7>:1:77'
    data_temp(56) := to_unsigned(2562, 12);
    -- STA 2
    --'<S7>:1:78'
    data_temp(57) := to_unsigned(0, 12);
    -- LDA 0
    --'<S7>:1:79'
    data_temp(58) := to_unsigned(3704, 12);
    -- CLC
    --'<S7>:1:80'
    data_temp(59) := to_unsigned(1538, 12);
    -- SUB 2
    --'<S7>:1:81'
    data_temp(60) := to_unsigned(3842, 12);
    -- BRA_Z 2
    --'<S7>:1:82'
    data_temp(61) := to_unsigned(2271, 12);
    -- JMP -33
    --'<S7>:1:83'
    data_temp(62) := to_unsigned(2305, 12);
    -- LI 1
    --'<S7>:1:84'
    data_temp(63) := to_unsigned(2564, 12);
    -- STA 4
    --'<S7>:1:85'
    data_temp(64) := to_unsigned(3, 12);
    -- LDA 3
    --'<S7>:1:86'
    data_temp(65) := to_unsigned(3704, 12);
    -- CLC
    --'<S7>:1:87'
    data_temp(66) := to_unsigned(1540, 12);
    -- SUB 4
    --'<S7>:1:88'
    data_temp(67) := to_unsigned(3842, 12);
    -- BRA_Z 2
    --'<S7>:1:89'
    data_temp(68) := to_unsigned(2260, 12);
    -- JMP -44
    --'<S7>:1:90'
    data_temp(69) := to_unsigned(2304, 12);
    -- LI 0
    --'<S7>:1:91'
    data_temp(70) := to_unsigned(2562, 12);
    -- STA 2
    --'<S7>:1:92'
    data_temp(71) := to_unsigned(257, 12);
    -- LDAI 1
    --'<S7>:1:93'
    data_temp(72) := to_unsigned(2815, 12);
    -- STA 255
    --'<S7>:1:94'
    data_temp(73) := to_unsigned(3696, 12);
    -- PRINT
    --'<S7>:1:95'
    data_temp(74) := to_unsigned(2305, 12);
    -- LI 1
    --'<S7>:1:96'
    data_temp(75) := to_unsigned(3704, 12);
    -- CLC
    --'<S7>:1:97'
    data_temp(76) := to_unsigned(1025, 12);
    -- ADD 1
    --'<S7>:1:98'
    data_temp(77) := to_unsigned(2561, 12);
    -- STA 1
    --'<S7>:1:99'
    data_temp(78) := to_unsigned(2305, 12);
    -- LI 1
    --'<S7>:1:100'
    data_temp(79) := to_unsigned(3704, 12);
    -- CLC
    --'<S7>:1:101'
    data_temp(80) := to_unsigned(1026, 12);
    -- ADD 2
    --'<S7>:1:102'
    data_temp(81) := to_unsigned(2562, 12);
    -- STA 2
    --'<S7>:1:103'
    data_temp(82) := to_unsigned(0, 12);
    -- LDA 0
    --'<S7>:1:104'
    data_temp(83) := to_unsigned(3704, 12);
    -- CLC
    --'<S7>:1:105'
    data_temp(84) := to_unsigned(1538, 12);
    -- SUB 2
    --'<S7>:1:106'
    data_temp(85) := to_unsigned(3842, 12);
    -- BRA_Z 2
    --'<S7>:1:107'
    data_temp(86) := to_unsigned(2289, 12);
    -- JMP -15
    --'<S7>:1:108'
    data_temp(87) := to_unsigned(3648, 12);
    -- HLT
    -- Loading from memory
    IF read = '1' THEN 
      --'<S7>:1:113'
      add_temp := resize(addr_unsigned, 9) + 1;
      IF add_temp(8) /= '0' THEN 
        sub_cast := "11111111";
      ELSE 
        sub_cast := add_temp(7 DOWNTO 0);
      END IF;
      sub_cast_0 := signed(resize(sub_cast, 32));
      instr_out_tmp <= data_temp(to_integer(sub_cast_0 - 1));
    ELSE 
      --'<S7>:1:115'
      instr_out_tmp <= to_unsigned(0, 12);
    END IF;
    data_next <= data_temp;
  END PROCESS Instruction_ROM_1_output;


  instr_out <= std_logic_vector(instr_out_tmp);

END rtl;

