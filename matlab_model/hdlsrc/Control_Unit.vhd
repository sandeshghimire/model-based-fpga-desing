-- -------------------------------------------------------------
-- 
-- File Name: hdlsrc\Control_Unit.vhd
-- Created: 2014-02-20 11:03:15
-- 
-- Generated by MATLAB 7.12 and Simulink HDL Coder 2.1
-- 
-- -------------------------------------------------------------


-- -------------------------------------------------------------
-- 
-- Module: Control_Unit
-- Source Path: hdlcodercpu_eml/CPU_Subsystem_8_bit/Control Unit
-- Hierarchy Level: 1
-- 
-- -------------------------------------------------------------
LIBRARY IEEE;
USE IEEE.std_logic_1164.ALL;
USE IEEE.numeric_std.ALL;

ENTITY Control_Unit IS
  PORT( clk                               :   IN    std_logic;
        reset                             :   IN    std_logic;
        enb                               :   IN    std_logic;
        data_in                           :   IN    std_logic_vector(7 DOWNTO 0);  -- int8
        in_flags                          :   IN    std_logic_vector(3 DOWNTO 0);  -- ufix4
        master_rst                        :   IN    std_logic;
        IR_in                             :   IN    std_logic_vector(11 DOWNTO 0);  -- ufix12
        shifter_sel                       :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
        out_flags                         :   OUT   std_logic_vector(3 DOWNTO 0);  -- ufix4
        ALU_func                          :   OUT   std_logic_vector(2 DOWNTO 0);  -- ufix3
        print_data                        :   OUT   std_logic;
        DM_addr                           :   OUT   std_logic_vector(7 DOWNTO 0);  -- uint8
        DM_r_w                            :   OUT   std_logic;  -- ufix1
        AC_func                           :   OUT   std_logic_vector(2 DOWNTO 0);  -- ufix3
        AC_data                           :   OUT   std_logic_vector(7 DOWNTO 0);  -- int8
        IR_func                           :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
        PC_func                           :   OUT   std_logic_vector(1 DOWNTO 0);  -- ufix2
        addr_inc                          :   OUT   std_logic_vector(7 DOWNTO 0);  -- int8
        IM_read                           :   OUT   std_logic;  -- ufix1
        hlt                               :   OUT   std_logic_vector(7 DOWNTO 0)  -- uint8
        );
END Control_Unit;


ARCHITECTURE rtl OF Control_Unit IS

  -- Signals
  SIGNAL data_in_signed                   : signed(7 DOWNTO 0);  -- int8
  SIGNAL in_flags_unsigned                : unsigned(3 DOWNTO 0);  -- ufix4
  SIGNAL IR_in_unsigned                   : unsigned(11 DOWNTO 0);  -- ufix12
  SIGNAL shifter_sel_tmp                  : unsigned(1 DOWNTO 0);  -- ufix2
  SIGNAL out_flags_tmp                    : unsigned(3 DOWNTO 0);  -- ufix4
  SIGNAL ALU_func_tmp                     : unsigned(2 DOWNTO 0);  -- ufix3
  SIGNAL DM_addr_tmp                      : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL AC_func_tmp                      : unsigned(2 DOWNTO 0);  -- ufix3
  SIGNAL AC_data_tmp                      : signed(7 DOWNTO 0);  -- int8
  SIGNAL IR_func_tmp                      : unsigned(1 DOWNTO 0);  -- ufix2
  SIGNAL PC_func_tmp                      : unsigned(1 DOWNTO 0);  -- ufix2
  SIGNAL addr_inc_tmp                     : signed(7 DOWNTO 0);  -- int8
  SIGNAL hlt_tmp                          : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL CPU_state                        : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL previous_CPU_state               : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL major_opcode                     : unsigned(7 DOWNTO 0);  -- ufix8
  SIGNAL minor_opcode                     : unsigned(7 DOWNTO 0);  -- ufix8
  SIGNAL address_data                     : unsigned(7 DOWNTO 0);  -- ufix8
  SIGNAL indirect_address                 : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL CPU_state_next                   : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL previous_CPU_state_next          : unsigned(7 DOWNTO 0);  -- uint8
  SIGNAL major_opcode_next                : unsigned(7 DOWNTO 0);  -- ufix8
  SIGNAL minor_opcode_next                : unsigned(7 DOWNTO 0);  -- ufix8
  SIGNAL address_data_next                : unsigned(7 DOWNTO 0);  -- ufix8
  SIGNAL indirect_address_next            : unsigned(7 DOWNTO 0);  -- uint8

BEGIN
  data_in_signed <= signed(data_in);

  in_flags_unsigned <= unsigned(in_flags);

  IR_in_unsigned <= unsigned(IR_in);

  Control_Unit_1_process : PROCESS (clk, reset)
  BEGIN
    IF reset = '1' THEN
      CPU_state <= to_unsigned(0, 8);
      previous_CPU_state <= to_unsigned(0, 8);
      major_opcode <= to_unsigned(0, 8);
      minor_opcode <= to_unsigned(0, 8);
      address_data <= to_unsigned(0, 8);
      indirect_address <= to_unsigned(0, 8);
    ELSIF clk'EVENT AND clk = '1' THEN
      IF enb = '1' THEN
        CPU_state <= CPU_state_next;
        previous_CPU_state <= previous_CPU_state_next;
        major_opcode <= major_opcode_next;
        minor_opcode <= minor_opcode_next;
        address_data <= address_data_next;
        indirect_address <= indirect_address_next;
      END IF;
    END IF;
  END PROCESS Control_Unit_1_process;

  Control_Unit_1_output : PROCESS (data_in_signed, in_flags_unsigned, master_rst, IR_in_unsigned, CPU_state, previous_CPU_state, 
      major_opcode, minor_opcode, address_data, indirect_address)
    VARIABLE minor_opcode_bit6 : std_logic;
    VARIABLE temp_address_data : signed(6 DOWNTO 0);
    VARIABLE indirect_bit : std_logic;
    VARIABLE c : std_logic;
    VARIABLE n : std_logic;
    VARIABLE minor_opcode_bit4 : std_logic;
    VARIABLE v : std_logic;
    VARIABLE z : std_logic;
    VARIABLE c_0 : unsigned(11 DOWNTO 0);
    VARIABLE c_1 : unsigned(11 DOWNTO 0);
    VARIABLE c_uint : unsigned(11 DOWNTO 0);
    VARIABLE c_uint_0 : unsigned(11 DOWNTO 0);
    VARIABLE CPU_state_temp : unsigned(7 DOWNTO 0);
    VARIABLE minor_opcode_bit6_0 : std_logic;
    VARIABLE temp_address_data_0 : signed(6 DOWNTO 0);
    VARIABLE temp_address_data_1 : signed(6 DOWNTO 0);
    VARIABLE minor_opcode_bit6_1 : std_logic;
    VARIABLE temp_address_data_2 : signed(6 DOWNTO 0);
    VARIABLE temp_address_data_3 : signed(6 DOWNTO 0);
    VARIABLE indirect_bit_0 : std_logic;
    VARIABLE indirect_bit_1 : std_logic;
    VARIABLE indirect_bit_2 : std_logic;
    VARIABLE indirect_bit_3 : std_logic;
    VARIABLE sub_cast : signed(12 DOWNTO 0);
    VARIABLE sub_temp : signed(12 DOWNTO 0);
    VARIABLE sub_cast_0 : signed(12 DOWNTO 0);
    VARIABLE sub_temp_0 : signed(12 DOWNTO 0);
    VARIABLE sub_cast_1 : signed(12 DOWNTO 0);
    VARIABLE sub_temp_1 : signed(12 DOWNTO 0);
    VARIABLE sub_cast_2 : signed(12 DOWNTO 0);
    VARIABLE sub_temp_2 : signed(12 DOWNTO 0);
    VARIABLE sub_cast_3 : signed(12 DOWNTO 0);
    VARIABLE sub_temp_3 : signed(12 DOWNTO 0);
  BEGIN
    CPU_state_temp := CPU_state;
    previous_CPU_state_next <= previous_CPU_state;
    major_opcode_next <= major_opcode;
    minor_opcode_next <= minor_opcode;
    address_data_next <= address_data;
    indirect_address_next <= indirect_address;
    -- CPU Controller
    --
    -- The CPU Instruction Set:
    -- ------------------------
    -- 
    -- LDA <loc>: AC = content(<loc>)
    -- LDAI <loc>: AC = content(content(<loc>))
    -- AND <loc>: AC = AC & content(<loc>)
    -- ANDI <loc>: AC = AC & content(content(<loc>))
    -- ADD <loc>: AC = AC + content(<loc>) + C(flag) 
    -- ADDI <loc>: AC = AC + content(content(<loc>)) + C(flag)
    -- SUB <loc>: AC = AC - content(<loc>) - C(flag) 
    -- SUBI <loc>: AC = AC - content(content(<loc>)) - C(flag)
    -- JMP <loc>: Jump to <PC + <loc>>
    -- LI <const>: AC = <const>
    -- STA <loc>: content(<loc>) = AC
    -- STAI <loc>: content(content(<loc>)) = AC
    -- BRA_C <loc>: Jump to <PC + <loc>> if (C(flag) == 1)
    -- BRA_N <loc>: Jump to <PC + <loc>> if (N(flag) == 1)
    -- BRA_V <loc>: Jump to <PC + <loc>> if (V(flag) == 1)
    -- BRA_Z <loc>: Jump to <PC + <loc>> if (Z(flag) == 1)
    -- NOP: Do nothing
    -- CLA: AC = 0
    -- CMA: Complement AC
    -- CMC: Complement C(flag)
    -- ASL: AC = AC << 1
    -- ASR: AC = AC >> 1
    -- PRINT: Display value from the memory-mapped location 255
    -- CLC: C(flag) = 0
    --
    -- 12-bit Instruction Encoding:
    -- ---------------------------
    --
    -- 	LDA:   000 0 <8-bit loc>
    -- 	LDAI:  000 1 <8-bit loc>
    -- 	AND:   001 0 <8-bit loc>
    -- 	ANDI:  001 1 <8-bit loc>
    -- 	ADD:   010 0 <8-bit loc>
    -- 	ADDI:  010 1 <8-bit loc>
    -- 	SUB:   011 0 <8-bit loc>
    -- 	SUBI:  011 1 <8-bit loc>
    -- 	JMP:   1000 <8-bit loc>
    -- 	LI:    1001 <8-bit const>
    -- 	STA:   101 0 <8-bit loc>
    -- 	STAI:  101 1 <8-bit loc>
    -- 	BRA_C: 1100 <8-bit loc>
    -- 	BRA_N: 1101 <8-bit loc>
    -- 	BRA_C: 1110 <8-bit loc>
    -- 	BRA_C: 1111 <8-bit loc>
    -- 	HLT:   111 0 0100 0 000 
    -- 	CLA:   111 0 0100 1 000
    -- 	CMA:   111 0 0101 0 000
    -- 	CMC:   111 0 0101 1 000
    -- 	ASL:   111 0 0110 0 000
    -- 	ASR:   111 0 0110 1 000
    -- 	PRINT: 111 0 0111 0 000
    -- 	CLC:   111 0 0111 1 000  
    -- HDL specific fimath
    IF master_rst = '1' THEN 
      CPU_state_temp := to_unsigned(0, 8);
    END IF;
    shifter_sel_tmp <= to_unsigned(0, 2);
    ALU_func_tmp <= to_unsigned(0, 3);
    out_flags_tmp <= in_flags_unsigned;
    AC_func_tmp <= to_unsigned(4, 3);
    -- NOP
    AC_data_tmp <= to_signed(0, 8);
    IR_func_tmp <= to_unsigned(3, 2);
    -- NOP
    PC_func_tmp <= to_unsigned(3, 2);
    -- NOP
    IM_read <= '0';
    DM_addr_tmp <= to_unsigned(0, 8);
    DM_r_w <= '0';
    addr_inc_tmp <= to_signed(0, 8);
    print_data <= '0';
    hlt_tmp <= to_unsigned(0, 8);
    -- Instruction: <12..1>
    -- major_opcode: <12..10>
    -- indirect_addressing: <9>
    -- minor_opcode: <9..4>
    -- address bits: <8..1>

    CASE CPU_state_temp IS
      WHEN "00000000" =>
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        --  RESETTING OUTPUTS
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        PC_func_tmp <= to_unsigned(0, 2);
        AC_func_tmp <= to_unsigned(0, 3);
        IR_func_tmp <= to_unsigned(0, 2);
        previous_CPU_state_next <= CPU_state_temp;
        CPU_state_temp := to_unsigned(1, 8);
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        --  FETCH
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      WHEN "00000001" =>
        -- Read from IM
        IM_read <= '1';
        -- Increment PC
        PC_func_tmp <= to_unsigned(2, 2);
        -- store into IR
        IR_func_tmp <= to_unsigned(1, 2);
        CPU_state_temp := to_unsigned(2, 8);
      WHEN "00000010" =>
        -- Read from IR
        IR_func_tmp <= to_unsigned(2, 2);
        -- Accommodating for the 'unit delay' from IR_out to IR_in
        CPU_state_temp := to_unsigned(3, 8);
      WHEN "00000011" =>
        -- IR_in <12..10>
        c_0 := IR_in_unsigned srl 9;
        major_opcode_next <= c_0(7 DOWNTO 0);
        -- IR_in <9..4>
        c_1 := IR_in_unsigned srl 3;
        c_uint := c_1 AND to_unsigned(63, 12);
        minor_opcode_next <= c_uint(7 DOWNTO 0);
        -- IR_in <8..1>
        c_uint_0 := IR_in_unsigned AND to_unsigned(255, 12);
        address_data_next <= c_uint_0(7 DOWNTO 0);
        -- Go to the decode stage
        CPU_state_temp := to_unsigned(4, 8);
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        --  DECODE AND EXECUTE
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      WHEN "00000100" =>
        previous_CPU_state_next <= CPU_state_temp;

        CASE major_opcode IS
          WHEN "00000000" =>
            -- LDA
            -- minor_opcode contains the address (assuming direct addressing)
            DM_addr_tmp <= address_data;
            -- Read the data memory
            DM_r_w <= '0';
            -- Simply pass the value read from memory
            CPU_state_temp := to_unsigned(13, 8);
          WHEN "00000001" =>
            -- AND           
            DM_addr_tmp <= address_data;
            -- Reading the data memory for address or data
            DM_r_w <= '0';
            CPU_state_temp := to_unsigned(15, 8);
          WHEN "00000010" =>
            -- ADD
            DM_addr_tmp <= address_data;
            -- Reading the data memory for address or data
            DM_r_w <= '0';
            CPU_state_temp := to_unsigned(17, 8);
          WHEN "00000011" =>
            -- SUB
            DM_addr_tmp <= address_data;
            -- Reading the data memory for address or data
            DM_r_w <= '0';
            CPU_state_temp := to_unsigned(19, 8);
          WHEN "00000100" =>
            minor_opcode_bit6 := minor_opcode(5);

            CASE minor_opcode_bit6 IS
              WHEN '0' =>
                -- JMP
                temp_address_data := signed(address_data(6 DOWNTO 0));
                sub_cast := resize(temp_address_data & '0' & '0' & '0' & '0' & '0', 13);
                sub_temp := sub_cast - 32;
                addr_inc_tmp <= sub_temp(12 DOWNTO 5);
                PC_func_tmp <= to_unsigned(1, 2);
              WHEN '1' =>
                -- LI
                AC_data_tmp <= signed(address_data);
                AC_func_tmp <= to_unsigned(1, 3);
              WHEN OTHERS => 
                NULL;
            END CASE;

            -- Go back to the fetch stage again
            CPU_state_temp := to_unsigned(1, 8);
          WHEN "00000101" =>
            -- STA
            -- minor_opcode contains the address (assuming direct addressing)
            DM_addr_tmp <= address_data;
            indirect_bit := minor_opcode(5);
            IF indirect_bit /= '0' THEN 
              -- indirect addressing
              -- Read the address from the data memory
              DM_r_w <= '0';
              CPU_state_temp := to_unsigned(21, 8);
            ELSE 
              -- Write into the data memory
              DM_r_w <= '1';
              -- Go back to the fetch stage again
              CPU_state_temp := to_unsigned(25, 8);
              -- going to 'otherwise'
            END IF;
          WHEN "00000110" =>
            minor_opcode_bit6_0 := minor_opcode(5);

            CASE minor_opcode_bit6_0 IS
              WHEN '0' =>
                -- special branches:
                -- BRA_C
                c := in_flags_unsigned(3);
                IF c /= '0' THEN 
                  temp_address_data_0 := signed(address_data(6 DOWNTO 0));
                  sub_cast_1 := resize(temp_address_data_0 & '0' & '0' & '0' & '0' & '0', 13);
                  sub_temp_1 := sub_cast_1 - 32;
                  addr_inc_tmp <= sub_temp_1(12 DOWNTO 5);
                  PC_func_tmp <= to_unsigned(1, 2);
                END IF;
              WHEN '1' =>
                -- BRA_N
                n := in_flags_unsigned(2);
                IF n /= '0' THEN 
                  temp_address_data_1 := signed(address_data(6 DOWNTO 0));
                  sub_cast_0 := resize(temp_address_data_1 & '0' & '0' & '0' & '0' & '0', 13);
                  sub_temp_0 := sub_cast_0 - 32;
                  addr_inc_tmp <= sub_temp_0(12 DOWNTO 5);
                  PC_func_tmp <= to_unsigned(1, 2);
                END IF;
              WHEN OTHERS => 
                NULL;
            END CASE;

            -- Go back to the fetch stage again
            CPU_state_temp := to_unsigned(15, 8);
          WHEN "00000111" =>
            -- by default, go back to the fetch stage again
            CPU_state_temp := to_unsigned(1, 8);
            minor_opcode_bit4 := minor_opcode(3);
            IF (minor_opcode_bit4 /= '0') = FALSE THEN 
              -- Further cases of special branches:
              minor_opcode_bit6_1 := minor_opcode(5);

              CASE minor_opcode_bit6_1 IS
                WHEN '0' =>
                  -- BRA_V
                  v := in_flags_unsigned(1);
                  IF v /= '0' THEN 
                    temp_address_data_2 := signed(address_data(6 DOWNTO 0));
                    sub_cast_2 := resize(temp_address_data_2 & '0' & '0' & '0' & '0' & '0', 13);
                    sub_temp_2 := sub_cast_2 - 32;
                    addr_inc_tmp <= sub_temp_2(12 DOWNTO 5);
                    PC_func_tmp <= to_unsigned(1, 2);
                  END IF;
                WHEN '1' =>
                  -- BRA_Z
                  z := in_flags_unsigned(0);
                  IF z /= '0' THEN 
                    temp_address_data_3 := signed(address_data(6 DOWNTO 0));
                    sub_cast_3 := resize(temp_address_data_3 & '0' & '0' & '0' & '0' & '0', 13);
                    sub_temp_3 := sub_cast_3 - 32;
                    addr_inc_tmp <= sub_temp_3(12 DOWNTO 5);
                    PC_func_tmp <= to_unsigned(1, 2);
                  END IF;
                WHEN OTHERS => 
                  NULL;
              END CASE;

            END IF;
            -- Instructions having no operands

            CASE minor_opcode IS
              WHEN "00001000" =>
                -- HLT
                -- Stop the simulation
                hlt_tmp <= to_unsigned(1, 8);
                CPU_state_temp := to_unsigned(22, 8);
              WHEN "00001001" =>
                -- CLA
                AC_func_tmp <= to_unsigned(0, 3);
              WHEN "00001010" =>
                -- CMA
                ALU_func_tmp <= to_unsigned(4, 3);
                shifter_sel_tmp <= to_unsigned(3, 2);
                CPU_state_temp := to_unsigned(6, 8);
              WHEN "00001011" =>
                -- CMC
                ALU_func_tmp <= to_unsigned(5, 3);
                shifter_sel_tmp <= to_unsigned(3, 2);
              WHEN "00001100" =>
                -- ASL
                shifter_sel_tmp <= to_unsigned(1, 2);
                CPU_state_temp := to_unsigned(6, 8);
              WHEN "00001101" =>
                -- ASR
                shifter_sel_tmp <= to_unsigned(2, 2);
                CPU_state_temp := to_unsigned(6, 8);
              WHEN "00001110" =>
                -- PRINT   
                DM_addr_tmp <= to_unsigned(255, 8);
                -- Read the data memory
                DM_r_w <= '0';
                CPU_state_temp := to_unsigned(12, 8);
              WHEN "00001111" =>
                -- CLC
                ALU_func_tmp <= to_unsigned(7, 3);
                shifter_sel_tmp <= to_unsigned(3, 2);
              WHEN OTHERS => 
                -- by default, go back to the fetch stage again
                CPU_state_temp := to_unsigned(1, 8);
                -- Minor Opcode cases end here        
            END CASE;

            -- Major Opcode cases end here
          WHEN OTHERS => 
            NULL;
        END CASE;

        -- introducing delay
      WHEN "00000110" =>
        -- accounting for the delay from shift_out to AC_in2
        AC_func_tmp <= to_unsigned(2, 3);
        previous_CPU_state_next <= CPU_state_temp;
        -- Go back to the fetch stage again
        CPU_state_temp := to_unsigned(1, 8);
        -- Operations with indirect addressing
      WHEN "00000111" =>
        -- LDA Indirect
        -- data_in is the address read from the data memory
        DM_addr_tmp <= indirect_address;
        -- Read the data memory
        DM_r_w <= '0';
        previous_CPU_state_next <= CPU_state_temp;
        CPU_state_temp := to_unsigned(13, 8);
      WHEN "00001000" =>
        -- AND Indirect
        -- data_in is the address read from the data memory
        DM_addr_tmp <= indirect_address;
        -- Read the data memory
        DM_r_w <= '0';
        previous_CPU_state_next <= CPU_state_temp;
        CPU_state_temp := to_unsigned(15, 8);
      WHEN "00001001" =>
        -- ADD Indirect
        -- data_in is the address read from the data memory
        DM_addr_tmp <= indirect_address;
        -- Read the data memory
        DM_r_w <= '0';
        previous_CPU_state_next <= CPU_state_temp;
        CPU_state_temp := to_unsigned(17, 8);
      WHEN "00001010" =>
        -- SUB Indirect
        -- data_in is the address read from the data memory
        DM_addr_tmp <= indirect_address;
        -- Read the data memory
        DM_r_w <= '0';
        previous_CPU_state_next <= CPU_state_temp;
        CPU_state_temp := to_unsigned(19, 8);
      WHEN "00001011" =>
        -- STA Indirect
        -- data_in is the address read from the data memory
        IF data_in_signed(7) = '1' THEN 
          DM_addr_tmp <= "00000000";
        ELSE 
          DM_addr_tmp <= unsigned(data_in_signed);
        END IF;
        -- Write the data memory
        DM_r_w <= '1';
        previous_CPU_state_next <= CPU_state_temp;
        CPU_state_temp := to_unsigned(1, 8);
      WHEN "00001100" =>
        -- PRINT
        print_data <= '1';
        previous_CPU_state_next <= CPU_state_temp;
        CPU_state_temp := to_unsigned(1, 8);
      WHEN "00001101" =>
        -- LDA (contd.)
        -- Simply pass the value read from memory
        ALU_func_tmp <= to_unsigned(6, 3);
        shifter_sel_tmp <= to_unsigned(3, 2);
        IF previous_CPU_state = 4 THEN 
          previous_CPU_state_next <= CPU_state_temp;
          CPU_state_temp := to_unsigned(14, 8);
        ELSE 
          previous_CPU_state_next <= CPU_state_temp;
          CPU_state_temp := to_unsigned(6, 8);
        END IF;
      WHEN "00001110" =>
        indirect_bit_0 := minor_opcode(5);
        -- accounting for the delay from shift_out to AC_in2
        AC_func_tmp <= to_unsigned(2, 3);
        previous_CPU_state_next <= CPU_state_temp;
        IF indirect_bit_0 /= '0' THEN 
          -- indirect addressing
          IF data_in_signed(7) = '1' THEN 
            indirect_address_next <= "00000000";
          ELSE 
            indirect_address_next <= unsigned(data_in_signed);
          END IF;
          CPU_state_temp := to_unsigned(7, 8);
        ELSE 
          CPU_state_temp := to_unsigned(25, 8);
        END IF;
      WHEN "00001111" =>
        -- AND (contd.)
        ALU_func_tmp <= to_unsigned(1, 3);
        shifter_sel_tmp <= to_unsigned(3, 2);
        IF previous_CPU_state = 4 THEN 
          previous_CPU_state_next <= CPU_state_temp;
          CPU_state_temp := to_unsigned(16, 8);
        ELSE 
          previous_CPU_state_next <= CPU_state_temp;
          CPU_state_temp := to_unsigned(6, 8);
        END IF;
      WHEN "00010000" =>
        indirect_bit_1 := minor_opcode(5);
        -- accounting for the delay from shift_out to AC_in2
        AC_func_tmp <= to_unsigned(2, 3);
        previous_CPU_state_next <= CPU_state_temp;
        IF indirect_bit_1 /= '0' THEN 
          -- indirect addressing
          IF data_in_signed(7) = '1' THEN 
            indirect_address_next <= "00000000";
          ELSE 
            indirect_address_next <= unsigned(data_in_signed);
          END IF;
          CPU_state_temp := to_unsigned(8, 8);
        ELSE 
          CPU_state_temp := to_unsigned(25, 8);
        END IF;
      WHEN "00010001" =>
        -- ADD (contd.)
        ALU_func_tmp <= to_unsigned(2, 3);
        shifter_sel_tmp <= to_unsigned(3, 2);
        IF previous_CPU_state = 4 THEN 
          previous_CPU_state_next <= CPU_state_temp;
          CPU_state_temp := to_unsigned(18, 8);
        ELSE 
          previous_CPU_state_next <= CPU_state_temp;
          CPU_state_temp := to_unsigned(6, 8);
        END IF;
      WHEN "00010010" =>
        indirect_bit_2 := minor_opcode(5);
        -- accounting for the delay from shift_out to AC_in2
        AC_func_tmp <= to_unsigned(2, 3);
        previous_CPU_state_next <= CPU_state_temp;
        IF indirect_bit_2 /= '0' THEN 
          -- indirect addressing
          IF data_in_signed(7) = '1' THEN 
            indirect_address_next <= "00000000";
          ELSE 
            indirect_address_next <= unsigned(data_in_signed);
          END IF;
          CPU_state_temp := to_unsigned(9, 8);
        ELSE 
          CPU_state_temp := to_unsigned(25, 8);
        END IF;
      WHEN "00010011" =>
        -- SUB (contd.)
        ALU_func_tmp <= to_unsigned(3, 3);
        shifter_sel_tmp <= to_unsigned(3, 2);
        IF previous_CPU_state = 4 THEN 
          previous_CPU_state_next <= CPU_state_temp;
          CPU_state_temp := to_unsigned(20, 8);
        ELSE 
          previous_CPU_state_next <= CPU_state_temp;
          CPU_state_temp := to_unsigned(6, 8);
        END IF;
      WHEN "00010100" =>
        indirect_bit_3 := minor_opcode(5);
        -- accounting for the delay from shift_out to AC_in2
        AC_func_tmp <= to_unsigned(2, 3);
        previous_CPU_state_next <= CPU_state_temp;
        IF indirect_bit_3 /= '0' THEN 
          -- indirect addressing
          IF data_in_signed(7) = '1' THEN 
            indirect_address_next <= "00000000";
          ELSE 
            indirect_address_next <= unsigned(data_in_signed);
          END IF;
          CPU_state_temp := to_unsigned(10, 8);
        ELSE 
          CPU_state_temp := to_unsigned(25, 8);
        END IF;
      WHEN "00010101" =>
        -- STA indirect
        CPU_state_temp := to_unsigned(11, 8);
      WHEN "00010110" =>
        -- lock state
        hlt_tmp <= to_unsigned(1, 8);
        CPU_state_temp := to_unsigned(22, 8);
      WHEN OTHERS => 
        previous_CPU_state_next <= CPU_state_temp;
        -- by default, go back to the fetch stage again
        CPU_state_temp := to_unsigned(1, 8);
        -- switch(CPU_state) end here
    END CASE;

    CPU_state_next <= CPU_state_temp;
  END PROCESS Control_Unit_1_output;


  shifter_sel <= std_logic_vector(shifter_sel_tmp);

  out_flags <= std_logic_vector(out_flags_tmp);

  ALU_func <= std_logic_vector(ALU_func_tmp);

  DM_addr <= std_logic_vector(DM_addr_tmp);

  AC_func <= std_logic_vector(AC_func_tmp);

  AC_data <= std_logic_vector(AC_data_tmp);

  IR_func <= std_logic_vector(IR_func_tmp);

  PC_func <= std_logic_vector(PC_func_tmp);

  addr_inc <= std_logic_vector(addr_inc_tmp);

  hlt <= std_logic_vector(hlt_tmp);

END rtl;

