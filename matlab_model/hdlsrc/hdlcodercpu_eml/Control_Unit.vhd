-- -------------------------------------------------------------
-- 
-- File Name: hdlsrc\hdlcodercpu_eml\Control_Unit.vhd
-- Created: 2014-08-26 11:41:14
-- 
-- Generated by MATLAB 8.3 and HDL Coder 3.4
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

  Control_Unit_1_process : PROCESS (clk)
  BEGIN
    IF clk'EVENT AND clk = '1' THEN
      IF reset = '1' THEN
        CPU_state <= to_unsigned(2#00000000#, 8);
        previous_CPU_state <= to_unsigned(2#00000000#, 8);
        major_opcode <= to_unsigned(2#00000000#, 8);
        minor_opcode <= to_unsigned(2#00000000#, 8);
        address_data <= to_unsigned(2#00000000#, 8);
        indirect_address <= to_unsigned(2#00000000#, 8);
      ELSIF enb = '1' THEN
        CPU_state <= CPU_state_next;
        previous_CPU_state <= previous_CPU_state_next;
        major_opcode <= major_opcode_next;
        minor_opcode <= minor_opcode_next;
        address_data <= address_data_next;
        indirect_address <= indirect_address_next;
      END IF;
    END IF;
  END PROCESS Control_Unit_1_process;

  Control_Unit_1_output : PROCESS (data_in_signed, in_flags_unsigned, master_rst, IR_in_unsigned, CPU_state,
       previous_CPU_state, major_opcode, minor_opcode, address_data,
       indirect_address)
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
  BEGIN
    CPU_state_temp := CPU_state;
    previous_CPU_state_next <= previous_CPU_state;
    major_opcode_next <= major_opcode;
    minor_opcode_next <= minor_opcode;
    address_data_next <= address_data;
    indirect_address_next <= indirect_address;
    --MATLAB Function 'CPU_Subsystem_8_bit/Control Unit': '<S5>:1'
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
      --'<S5>:1:81'
      --'<S5>:1:82'
      CPU_state_temp := to_unsigned(2#00000000#, 8);
    END IF;
    --'<S5>:1:85'
    shifter_sel_tmp <= to_unsigned(2#00#, 2);
    --'<S5>:1:86'
    ALU_func_tmp <= to_unsigned(2#000#, 3);
    --'<S5>:1:87'
    out_flags_tmp <= in_flags_unsigned;
    --'<S5>:1:88'
    AC_func_tmp <= to_unsigned(2#100#, 3);
    -- NOP
    --'<S5>:1:89'
    AC_data_tmp <= to_signed(2#00000000#, 8);
    --'<S5>:1:90'
    IR_func_tmp <= to_unsigned(2#11#, 2);
    -- NOP
    --'<S5>:1:91'
    PC_func_tmp <= to_unsigned(2#11#, 2);
    -- NOP
    --'<S5>:1:92'
    IM_read <= '0';
    --'<S5>:1:93'
    DM_addr_tmp <= to_unsigned(2#00000000#, 8);
    --'<S5>:1:94'
    DM_r_w <= '0';
    --'<S5>:1:95'
    addr_inc_tmp <= to_signed(2#00000000#, 8);
    --'<S5>:1:96'
    print_data <= '0';
    --'<S5>:1:97'
    hlt_tmp <= to_unsigned(2#00000000#, 8);
    -- Instruction: <12..1>
    -- major_opcode: <12..10>
    -- indirect_addressing: <9>
    -- minor_opcode: <9..4>
    -- address bits: <8..1>
    --'<S5>:1:117'

    CASE CPU_state_temp IS
      WHEN "00000000" =>
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        --  RESETTING OUTPUTS
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        --'<S5>:1:122'
        PC_func_tmp <= to_unsigned(2#00#, 2);
        --'<S5>:1:123'
        AC_func_tmp <= to_unsigned(2#000#, 3);
        --'<S5>:1:124'
        IR_func_tmp <= to_unsigned(2#00#, 2);
        --'<S5>:1:125'
        previous_CPU_state_next <= CPU_state_temp;
        --'<S5>:1:126'
        CPU_state_temp := to_unsigned(2#00000001#, 8);
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        --  FETCH
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      WHEN "00000001" =>
        -- Read from IM
        --'<S5>:1:133'
        IM_read <= '1';
        -- Increment PC
        --'<S5>:1:135'
        PC_func_tmp <= to_unsigned(2#10#, 2);
        -- store into IR
        --'<S5>:1:137'
        IR_func_tmp <= to_unsigned(2#01#, 2);
        --'<S5>:1:139'
        CPU_state_temp := to_unsigned(2#00000010#, 8);
      WHEN "00000010" =>
        -- Read from IR
        --'<S5>:1:143'
        IR_func_tmp <= to_unsigned(2#10#, 2);
        -- Accommodating for the 'unit delay' from IR_out to IR_in
        --'<S5>:1:146'
        CPU_state_temp := to_unsigned(2#00000011#, 8);
      WHEN "00000011" =>
        -- IR_in <12..10>
        --'<S5>:1:150'
        c_0 := IR_in_unsigned srl 9;
        major_opcode_next <= c_0(7 DOWNTO 0);
        -- IR_in <9..4>
        --'<S5>:1:153'
        c_1 := IR_in_unsigned srl 3;
        c_uint := c_1 AND to_unsigned(2#000000111111#, 12);
        minor_opcode_next <= c_uint(7 DOWNTO 0);
        -- IR_in <8..1>
        --'<S5>:1:156'
        c_uint_0 := IR_in_unsigned AND to_unsigned(2#000011111111#, 12);
        address_data_next <= c_uint_0(7 DOWNTO 0);
        -- Go to the decode stage
        --'<S5>:1:159'
        CPU_state_temp := to_unsigned(2#00000100#, 8);
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        --  DECODE AND EXECUTE
        --%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
      WHEN "00000100" =>
        --'<S5>:1:165'
        previous_CPU_state_next <= CPU_state_temp;

        CASE major_opcode IS
          WHEN "00000000" =>
            -- LDA
            -- minor_opcode contains the address (assuming direct addressing)
            --'<S5>:1:170'
            DM_addr_tmp <= address_data;
            -- Read the data memory
            --'<S5>:1:172'
            DM_r_w <= '0';
            -- Simply pass the value read from memory
            --'<S5>:1:174'
            CPU_state_temp := to_unsigned(2#00001101#, 8);
          WHEN "00000001" =>
            -- AND           
            --'<S5>:1:178'
            DM_addr_tmp <= address_data;
            -- Reading the data memory for address or data
            --'<S5>:1:180'
            DM_r_w <= '0';
            --'<S5>:1:182'
            CPU_state_temp := to_unsigned(2#00001111#, 8);
          WHEN "00000010" =>
            -- ADD
            --'<S5>:1:186'
            DM_addr_tmp <= address_data;
            -- Reading the data memory for address or data
            --'<S5>:1:188'
            DM_r_w <= '0';
            --'<S5>:1:190'
            CPU_state_temp := to_unsigned(2#00010001#, 8);
          WHEN "00000011" =>
            -- SUB
            --'<S5>:1:194'
            DM_addr_tmp <= address_data;
            -- Reading the data memory for address or data
            --'<S5>:1:196'
            DM_r_w <= '0';
            --'<S5>:1:198'
            CPU_state_temp := to_unsigned(2#00010011#, 8);
          WHEN "00000100" =>
            --'<S5>:1:201'
            minor_opcode_bit6 := minor_opcode(5);

            CASE minor_opcode_bit6 IS
              WHEN '0' =>
                -- JMP
                --'<S5>:1:205'
                temp_address_data := signed(address_data(6 DOWNTO 0));
                --'<S5>:1:206'
                addr_inc_tmp <= resize(temp_address_data, 8) - 1;
                --'<S5>:1:207'
                PC_func_tmp <= to_unsigned(2#01#, 2);
              WHEN '1' =>
                -- LI
                --'<S5>:1:211'
                AC_data_tmp <= signed(address_data);
                --'<S5>:1:212'
                AC_func_tmp <= to_unsigned(2#001#, 3);
              WHEN OTHERS => 
                NULL;
            END CASE;

            -- Go back to the fetch stage again
            --'<S5>:1:215'
            CPU_state_temp := to_unsigned(2#00000001#, 8);
          WHEN "00000101" =>
            -- STA
            -- minor_opcode contains the address (assuming direct addressing)
            --'<S5>:1:220'
            DM_addr_tmp <= address_data;
            --'<S5>:1:221'
            indirect_bit := minor_opcode(5);
            IF indirect_bit /= '0' THEN 
              -- indirect addressing
              -- Read the address from the data memory
              --'<S5>:1:225'
              DM_r_w <= '0';
              --'<S5>:1:226'
              CPU_state_temp := to_unsigned(2#00010101#, 8);
            ELSE 
              -- Write into the data memory
              --'<S5>:1:229'
              DM_r_w <= '1';
              -- Go back to the fetch stage again
              --'<S5>:1:231'
              CPU_state_temp := to_unsigned(2#00011001#, 8);
              -- going to 'otherwise'
            END IF;
          WHEN "00000110" =>
            --'<S5>:1:235'
            minor_opcode_bit6_0 := minor_opcode(5);

            CASE minor_opcode_bit6_0 IS
              WHEN '0' =>
                -- special branches:
                -- BRA_C
                --'<S5>:1:240'
                c := in_flags_unsigned(3);
                IF c /= '0' THEN 
                  --'<S5>:1:242'
                  temp_address_data_0 := signed(address_data(6 DOWNTO 0));
                  --'<S5>:1:243'
                  addr_inc_tmp <= resize(temp_address_data_0, 8) - 1;
                  --'<S5>:1:244'
                  PC_func_tmp <= to_unsigned(2#01#, 2);
                END IF;
              WHEN '1' =>
                -- BRA_N
                --'<S5>:1:249'
                n := in_flags_unsigned(2);
                IF n /= '0' THEN 
                  --'<S5>:1:251'
                  temp_address_data_1 := signed(address_data(6 DOWNTO 0));
                  --'<S5>:1:252'
                  addr_inc_tmp <= resize(temp_address_data_1, 8) - 1;
                  --'<S5>:1:253'
                  PC_func_tmp <= to_unsigned(2#01#, 2);
                END IF;
              WHEN OTHERS => 
                NULL;
            END CASE;

            -- Go back to the fetch stage again
            --'<S5>:1:257'
            CPU_state_temp := to_unsigned(2#00001111#, 8);
          WHEN "00000111" =>
            -- by default, go back to the fetch stage again
            --'<S5>:1:261'
            CPU_state_temp := to_unsigned(2#00000001#, 8);
            --'<S5>:1:262'
            minor_opcode_bit4 := minor_opcode(3);
            IF (minor_opcode_bit4 /= '0') = FALSE THEN 
              --'<S5>:1:263'
              -- Further cases of special branches:
              --'<S5>:1:265'
              minor_opcode_bit6_1 := minor_opcode(5);

              CASE minor_opcode_bit6_1 IS
                WHEN '0' =>
                  -- BRA_V
                  --'<S5>:1:269'
                  v := in_flags_unsigned(1);
                  IF v /= '0' THEN 
                    --'<S5>:1:271'
                    temp_address_data_2 := signed(address_data(6 DOWNTO 0));
                    --'<S5>:1:272'
                    addr_inc_tmp <= resize(temp_address_data_2, 8) - 1;
                    --'<S5>:1:273'
                    PC_func_tmp <= to_unsigned(2#01#, 2);
                  END IF;
                WHEN '1' =>
                  -- BRA_Z
                  --'<S5>:1:278'
                  z := in_flags_unsigned(0);
                  IF z /= '0' THEN 
                    --'<S5>:1:280'
                    temp_address_data_3 := signed(address_data(6 DOWNTO 0));
                    --'<S5>:1:281'
                    addr_inc_tmp <= resize(temp_address_data_3, 8) - 1;
                    --'<S5>:1:282'
                    PC_func_tmp <= to_unsigned(2#01#, 2);
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
                --'<S5>:1:291'
                hlt_tmp <= to_unsigned(2#00000001#, 8);
                --'<S5>:1:292'
                CPU_state_temp := to_unsigned(2#00010110#, 8);
              WHEN "00001001" =>
                -- CLA
                --'<S5>:1:295'
                AC_func_tmp <= to_unsigned(2#000#, 3);
              WHEN "00001010" =>
                -- CMA
                --'<S5>:1:299'
                ALU_func_tmp <= to_unsigned(2#100#, 3);
                --'<S5>:1:300'
                shifter_sel_tmp <= to_unsigned(2#11#, 2);
                --'<S5>:1:301'
                CPU_state_temp := to_unsigned(2#00000110#, 8);
              WHEN "00001011" =>
                -- CMC
                --'<S5>:1:305'
                ALU_func_tmp <= to_unsigned(2#101#, 3);
                --'<S5>:1:306'
                shifter_sel_tmp <= to_unsigned(2#11#, 2);
              WHEN "00001100" =>
                -- ASL
                --'<S5>:1:310'
                shifter_sel_tmp <= to_unsigned(2#01#, 2);
                --'<S5>:1:311'
                CPU_state_temp := to_unsigned(2#00000110#, 8);
              WHEN "00001101" =>
                -- ASR
                --'<S5>:1:315'
                shifter_sel_tmp <= to_unsigned(2#10#, 2);
                --'<S5>:1:316'
                CPU_state_temp := to_unsigned(2#00000110#, 8);
              WHEN "00001110" =>
                -- PRINT   
                --'<S5>:1:320'
                DM_addr_tmp <= to_unsigned(2#11111111#, 8);
                -- Read the data memory
                --'<S5>:1:322'
                DM_r_w <= '0';
                --'<S5>:1:324'
                CPU_state_temp := to_unsigned(2#00001100#, 8);
              WHEN "00001111" =>
                -- CLC
                --'<S5>:1:328'
                ALU_func_tmp <= to_unsigned(2#111#, 3);
                --'<S5>:1:329'
                shifter_sel_tmp <= to_unsigned(2#11#, 2);
              WHEN OTHERS => 
                -- by default, go back to the fetch stage again
                --'<S5>:1:333'
                CPU_state_temp := to_unsigned(2#00000001#, 8);
                -- Minor Opcode cases end here        
            END CASE;

            -- Major Opcode cases end here
          WHEN OTHERS => 
            NULL;
        END CASE;

        -- introducing delay
      WHEN "00000110" =>
        -- accounting for the delay from shift_out to AC_in2
        --'<S5>:1:343'
        AC_func_tmp <= to_unsigned(2#010#, 3);
        --'<S5>:1:344'
        previous_CPU_state_next <= CPU_state_temp;
        -- Go back to the fetch stage again
        --'<S5>:1:346'
        CPU_state_temp := to_unsigned(2#00000001#, 8);
        -- Operations with indirect addressing
      WHEN "00000111" =>
        -- LDA Indirect
        -- data_in is the address read from the data memory
        --'<S5>:1:352'
        DM_addr_tmp <= indirect_address;
        -- Read the data memory
        --'<S5>:1:354'
        DM_r_w <= '0';
        --'<S5>:1:356'
        previous_CPU_state_next <= CPU_state_temp;
        --'<S5>:1:357'
        CPU_state_temp := to_unsigned(2#00001101#, 8);
      WHEN "00001000" =>
        -- AND Indirect
        -- data_in is the address read from the data memory
        --'<S5>:1:362'
        DM_addr_tmp <= indirect_address;
        -- Read the data memory
        --'<S5>:1:364'
        DM_r_w <= '0';
        --'<S5>:1:366'
        previous_CPU_state_next <= CPU_state_temp;
        --'<S5>:1:367'
        CPU_state_temp := to_unsigned(2#00001111#, 8);
      WHEN "00001001" =>
        -- ADD Indirect
        -- data_in is the address read from the data memory
        --'<S5>:1:372'
        DM_addr_tmp <= indirect_address;
        -- Read the data memory
        --'<S5>:1:374'
        DM_r_w <= '0';
        --'<S5>:1:376'
        previous_CPU_state_next <= CPU_state_temp;
        --'<S5>:1:377'
        CPU_state_temp := to_unsigned(2#00010001#, 8);
      WHEN "00001010" =>
        -- SUB Indirect
        -- data_in is the address read from the data memory
        --'<S5>:1:382'
        DM_addr_tmp <= indirect_address;
        -- Read the data memory
        --'<S5>:1:384'
        DM_r_w <= '0';
        --'<S5>:1:386'
        previous_CPU_state_next <= CPU_state_temp;
        --'<S5>:1:387'
        CPU_state_temp := to_unsigned(2#00010011#, 8);
      WHEN "00001011" =>
        -- STA Indirect
        -- data_in is the address read from the data memory
        --'<S5>:1:392'
        IF data_in_signed(7) = '1' THEN 
          DM_addr_tmp <= "00000000";
        ELSE 
          DM_addr_tmp <= unsigned(data_in_signed);
        END IF;
        -- Write the data memory
        --'<S5>:1:394'
        DM_r_w <= '1';
        --'<S5>:1:395'
        previous_CPU_state_next <= CPU_state_temp;
        --'<S5>:1:396'
        CPU_state_temp := to_unsigned(2#00000001#, 8);
      WHEN "00001100" =>
        -- PRINT
        --'<S5>:1:400'
        print_data <= '1';
        --'<S5>:1:401'
        previous_CPU_state_next <= CPU_state_temp;
        --'<S5>:1:402'
        CPU_state_temp := to_unsigned(2#00000001#, 8);
      WHEN "00001101" =>
        -- LDA (contd.)
        -- Simply pass the value read from memory
        --'<S5>:1:407'
        ALU_func_tmp <= to_unsigned(2#110#, 3);
        --'<S5>:1:408'
        shifter_sel_tmp <= to_unsigned(2#11#, 2);
        IF previous_CPU_state = 4 THEN 
          --'<S5>:1:410'
          --'<S5>:1:411'
          previous_CPU_state_next <= CPU_state_temp;
          --'<S5>:1:412'
          CPU_state_temp := to_unsigned(2#00001110#, 8);
        ELSE 
          --'<S5>:1:414'
          previous_CPU_state_next <= CPU_state_temp;
          --'<S5>:1:415'
          CPU_state_temp := to_unsigned(2#00000110#, 8);
        END IF;
      WHEN "00001110" =>
        --'<S5>:1:419'
        indirect_bit_0 := minor_opcode(5);
        -- accounting for the delay from shift_out to AC_in2
        --'<S5>:1:421'
        AC_func_tmp <= to_unsigned(2#010#, 3);
        --'<S5>:1:423'
        previous_CPU_state_next <= CPU_state_temp;
        IF indirect_bit_0 /= '0' THEN 
          -- indirect addressing
          --'<S5>:1:426'
          IF data_in_signed(7) = '1' THEN 
            indirect_address_next <= "00000000";
          ELSE 
            indirect_address_next <= unsigned(data_in_signed);
          END IF;
          --'<S5>:1:427'
          CPU_state_temp := to_unsigned(2#00000111#, 8);
        ELSE 
          --'<S5>:1:429'
          CPU_state_temp := to_unsigned(2#00011001#, 8);
        END IF;
      WHEN "00001111" =>
        -- AND (contd.)
        --'<S5>:1:435'
        ALU_func_tmp <= to_unsigned(2#001#, 3);
        --'<S5>:1:436'
        shifter_sel_tmp <= to_unsigned(2#11#, 2);
        IF previous_CPU_state = 4 THEN 
          --'<S5>:1:438'
          --'<S5>:1:439'
          previous_CPU_state_next <= CPU_state_temp;
          --'<S5>:1:440'
          CPU_state_temp := to_unsigned(2#00010000#, 8);
        ELSE 
          --'<S5>:1:442'
          previous_CPU_state_next <= CPU_state_temp;
          --'<S5>:1:443'
          CPU_state_temp := to_unsigned(2#00000110#, 8);
        END IF;
      WHEN "00010000" =>
        --'<S5>:1:447'
        indirect_bit_1 := minor_opcode(5);
        -- accounting for the delay from shift_out to AC_in2
        --'<S5>:1:449'
        AC_func_tmp <= to_unsigned(2#010#, 3);
        --'<S5>:1:451'
        previous_CPU_state_next <= CPU_state_temp;
        IF indirect_bit_1 /= '0' THEN 
          -- indirect addressing
          --'<S5>:1:454'
          IF data_in_signed(7) = '1' THEN 
            indirect_address_next <= "00000000";
          ELSE 
            indirect_address_next <= unsigned(data_in_signed);
          END IF;
          --'<S5>:1:455'
          CPU_state_temp := to_unsigned(2#00001000#, 8);
        ELSE 
          --'<S5>:1:457'
          CPU_state_temp := to_unsigned(2#00011001#, 8);
        END IF;
      WHEN "00010001" =>
        -- ADD (contd.)
        --'<S5>:1:462'
        ALU_func_tmp <= to_unsigned(2#010#, 3);
        --'<S5>:1:463'
        shifter_sel_tmp <= to_unsigned(2#11#, 2);
        IF previous_CPU_state = 4 THEN 
          --'<S5>:1:465'
          --'<S5>:1:466'
          previous_CPU_state_next <= CPU_state_temp;
          --'<S5>:1:467'
          CPU_state_temp := to_unsigned(2#00010010#, 8);
        ELSE 
          --'<S5>:1:469'
          previous_CPU_state_next <= CPU_state_temp;
          --'<S5>:1:470'
          CPU_state_temp := to_unsigned(2#00000110#, 8);
        END IF;
      WHEN "00010010" =>
        --'<S5>:1:474'
        indirect_bit_2 := minor_opcode(5);
        -- accounting for the delay from shift_out to AC_in2
        --'<S5>:1:476'
        AC_func_tmp <= to_unsigned(2#010#, 3);
        --'<S5>:1:478'
        previous_CPU_state_next <= CPU_state_temp;
        IF indirect_bit_2 /= '0' THEN 
          -- indirect addressing
          --'<S5>:1:481'
          IF data_in_signed(7) = '1' THEN 
            indirect_address_next <= "00000000";
          ELSE 
            indirect_address_next <= unsigned(data_in_signed);
          END IF;
          --'<S5>:1:482'
          CPU_state_temp := to_unsigned(2#00001001#, 8);
        ELSE 
          --'<S5>:1:484'
          CPU_state_temp := to_unsigned(2#00011001#, 8);
        END IF;
      WHEN "00010011" =>
        -- SUB (contd.)
        --'<S5>:1:489'
        ALU_func_tmp <= to_unsigned(2#011#, 3);
        --'<S5>:1:490'
        shifter_sel_tmp <= to_unsigned(2#11#, 2);
        IF previous_CPU_state = 4 THEN 
          --'<S5>:1:492'
          --'<S5>:1:493'
          previous_CPU_state_next <= CPU_state_temp;
          --'<S5>:1:494'
          CPU_state_temp := to_unsigned(2#00010100#, 8);
        ELSE 
          --'<S5>:1:496'
          previous_CPU_state_next <= CPU_state_temp;
          --'<S5>:1:497'
          CPU_state_temp := to_unsigned(2#00000110#, 8);
        END IF;
      WHEN "00010100" =>
        --'<S5>:1:501'
        indirect_bit_3 := minor_opcode(5);
        -- accounting for the delay from shift_out to AC_in2
        --'<S5>:1:503'
        AC_func_tmp <= to_unsigned(2#010#, 3);
        --'<S5>:1:505'
        previous_CPU_state_next <= CPU_state_temp;
        IF indirect_bit_3 /= '0' THEN 
          -- indirect addressing
          --'<S5>:1:508'
          IF data_in_signed(7) = '1' THEN 
            indirect_address_next <= "00000000";
          ELSE 
            indirect_address_next <= unsigned(data_in_signed);
          END IF;
          --'<S5>:1:509'
          CPU_state_temp := to_unsigned(2#00001010#, 8);
        ELSE 
          --'<S5>:1:512'
          CPU_state_temp := to_unsigned(2#00011001#, 8);
        END IF;
      WHEN "00010101" =>
        -- STA indirect
        --'<S5>:1:517'
        CPU_state_temp := to_unsigned(2#00001011#, 8);
      WHEN "00010110" =>
        -- lock state
        --'<S5>:1:521'
        hlt_tmp <= to_unsigned(2#00000001#, 8);
        --'<S5>:1:522'
        CPU_state_temp := to_unsigned(2#00010110#, 8);
      WHEN OTHERS => 
        --'<S5>:1:525'
        previous_CPU_state_next <= CPU_state_temp;
        -- by default, go back to the fetch stage again
        --'<S5>:1:527'
        CPU_state_temp := to_unsigned(2#00000001#, 8);
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

