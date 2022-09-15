library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

Package Ram_PKG is
    function clogb2 (depth: in natural) return integer;
End Ram_PKG;

Package Body Ram_PKG is
    Function clogb2( depth : natural) return integer is
        variable Temp    : integer := depth;
        variable Ret_Val : integer := 0;
        begin
            while Temp > 1 loop
                Ret_Val := Ret_Val + 1;
                Temp    := Temp / 2;
            end loop;
            return Ret_Val;
    end Function;
end Package Body Ram_PKG;

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use work.Ram_PKG.all;               -- This package performs Logarithmic operation for automate.
USE std.textio.all;

-- DATA PROCOL:
-- COMMAND SENT BY PC TO TOP MODULE:
-- [START_BYTE1] | [START_BYTE2] | [CMND] | [ADDR] | [DATA] | [CHECKSUM]

-- RESPONSE SENT BY TOP MODULE TO PC:
-- [START_BYTE1] | [START_BYTE2] | [CMND] | [ADDR] | [DATA] | [CHECKSUM]

entity Uart_TX_RX_CheckSUM is
    Generic ( C_Clock_Frequency     : integer := 100_000_000;
              C_Baud_Rate           : integer := 115_200;
              C_Stop_Bits           : integer := 2;
              C_Start_Byte_1        : integer := 171;       -- 0xAB 
              C_Start_Byte_2        : integer := 205;       -- 0xCD
              C_Command_Write       : integer := 17;        -- 0x11
              C_Command_Read        : integer := 34;        -- 0x22
              C_Response_Write_Done : integer := 51;        -- 0x33
              C_Response_Read_Done  : integer := 68;        -- 0x44
              C_Response_CheckSum   : integer := 238;       -- 0xEE
              C_Address_Length      : integer := 1;
              C_Data_Length         : integer := 1;
              C_RAM_Width 		    : integer := 8;
              C_RAM_Depth		    : integer := 256;
              C_RAM_Performance     : string  := "LOW_LATENCY";
              C_RAM_Type 		    : string  := "BLOCK");
       Port ( Clk                   : in  STD_LOGIC;
              RX                    : in  STD_LOGIC;
              TX                    : out STD_LOGIC);
end Uart_TX_RX_CheckSUM;

architecture Behavioral of Uart_TX_RX_CheckSUM is

type STD_Lv8_Array is array (natural range <>) of STD_LOGIC_VECTOR(7 downto 0);
type T_States is (S_IDLE, S_START_1, S_RD_CMND, S_RD_CMND_ADDR, S_RD_CMND_DATA, S_RD_CMND_CS, S_CHECK_CMND_CS, S_WR_BRAM, S_RD_BRAM, S_SND_RESP);
signal State : T_States    := S_IDLE;   

-- Sabit Tanimlar
constant C_Buffer_Length  : integer := (1 + C_Address_Length + C_Data_Length + 1);
constant C_Bit_Timer_Lim  : integer := C_Clock_Frequency/C_Baud_Rate; 
constant C_Timeout_Lim    : integer := C_Bit_Timer_Lim*12;
constant C_Buffer         : STD_Lv8_Array(0 to (C_Buffer_Length - 1)) := (others => (others => '0'));

--  UART Bufferlari
signal Command_Buffer     : STD_Lv8_Array(0 to (C_Buffer_Length - 1)) := C_Buffer;
signal Response_Buffer    : STD_Lv8_Array(0 to (C_Buffer_Length - 1)) := C_Buffer;

-- UART RX
signal RX_Data_Out        : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
signal RX_Done_Tick       : STD_LOGIC := '0'; 
    
-- UART TX
signal TX_Data_In         : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
signal TX_Done_Tick       : STD_LOGIC := '0';
signal TX_Start 	      : STD_LOGIC := '0';

-- BRAM 
signal Bram_Wea           : STD_LOGIC := '0';
signal Bram_Wea_Prev      : STD_LOGIC := '0';
signal Bram_Address       : STD_LOGIC_VECTOR((clogb2(C_RAM_Depth)-1) downto 0) := (others => '0');
signal Bram_Dina          : STD_LOGIC_VECTOR(C_RAM_Width-1 downto 0)           := (others => '0');
signal Bram_Douta         : STD_LOGIC_VECTOR(C_RAM_Width-1 downto 0)           := (others => '0');
signal Bram_Douta_Arr     : STD_Lv8_Array(0 to (C_Data_Length - 1))            := (others => (others => '0')); 

-- Modul ici Sinyaller
signal Timeout_Timer     : integer range 0 to C_Timeout_Lim := 0;
signal Address_IDX       : integer := 0;
signal Data_IDX          : integer := 0;
signal Response_IDX      : integer := 0;
signal TX_Inprogress     : STD_LOGIC := '0';

signal Sum_TXBuffer_Lv   : STD_LOGIC_VECTOR((7+2 + C_Buffer_Length) downto 0) := (others => '0');
signal Sum_RXBuffer_Lv   : STD_LOGIC_VECTOR((7+2 + C_Buffer_Length) downto 0) := (others => '0');
    
signal CheckSum_RXBuffer : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
signal CheckSum_TXBuffer : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');

component Uart_TX is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_Baud_Rate       : integer := 115_200;
              C_Stop_Bits       : integer := 2);
       Port ( Clk               : in STD_LOGIC;
              In_Data           : in STD_LOGIC_VECTOR (7 downto 0);
              In_TX_Start       : in STD_LOGIC;
              Out_TX            : out STD_LOGIC;
              Out_TX_Done_Tick  : out STD_LOGIC );
end component;

component Uart_RX is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_Baud_Rate       : integer := 115_200);
       Port ( Clk               : in STD_LOGIC;
              In_RX             : in STD_LOGIC;
              Out_Data          : out STD_LOGIC_VECTOR (7 downto 0);
              Out_RX_Done_Tick  : out STD_LOGIC );
end component;

component Block_RAM is
    Generic ( RAM_WIDTH 		: integer 	:= 16;
              RAM_DEPTH 		: integer 	:= 128;
              RAM_PERFORMANCE   : string 	:= "LOW_LATENCY";
              C_RAM_TYPE 		: string 	:= "BLOCK");
       Port ( Addra : in STD_LOGIC_VECTOR((clogb2(RAM_DEPTH)-1) downto 0);
              Dina  : in STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0);
              Clka  : in STD_LOGIC;
              Wea   : in STD_LOGIC;
              Douta : out STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0));
end component;

begin

Uart_RX_Instantiation : Uart_RX 
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Baud_Rate => C_Baud_Rate)
    Port Map (Clk => Clk, In_RX => RX, Out_Data => RX_Data_Out, Out_RX_Done_Tick => RX_Done_Tick);

Uart_TX_Instantiation : Uart_TX 
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Baud_Rate => C_Baud_Rate, C_Stop_Bits => C_Stop_Bits)
    Port Map (Clk => Clk, In_Data => TX_Data_In, In_TX_Start => TX_Start, Out_TX => TX, Out_TX_Done_Tick => TX_Done_Tick);
    
Block_RAM_128x16_Instantiation: Block_RAM
    Generic Map(RAM_WIDTH => C_RAM_Width, RAM_DEPTH => C_RAM_Depth, RAM_PERFORMANCE => C_RAM_Performance, C_RAM_TYPE=> C_RAM_Type)
    Port Map (Addra => Bram_Address, Dina => Bram_Dina, Clka => Clk, Wea => Bram_Wea, Douta => Bram_Douta);
    
-- Combinational Part
CheckSum_RXBuffer <= Sum_RXBuffer_Lv(7 downto 0);
CheckSum_TXBuffer <= Sum_TXBuffer_Lv(7 downto 0);

BRAM_Data_Concater : for ByteIDX in 0 to (C_Data_Length - 1) generate
    Bram_Dina(((8*(1 + ByteIDX)) - 1) downto (8*ByteIDX))  <= Command_Buffer(ByteIDX + C_Address_Length + 1);
end generate BRAM_Data_Concater;

BRAM_Address_Concater : for ByteIDX in 0 to (C_Address_Length - 1) generate
    Bram_Address(((8*(1 + ByteIDX)) - 1) downto (8 * ByteIDX))  <= Command_Buffer(ByteIDX + 1);
end generate BRAM_Address_Concater;

BRAM_Data_Splitter : for ByteIDX in 0 to (C_Data_Length - 1) generate
    Bram_Douta_Arr(ByteIDX)  <= Bram_Douta((( 8*(1 + ByteIDX)) - 1) downto (8*ByteIDX)) ;
end generate BRAM_Data_Splitter;

-- MAIN Process
P_MAIN : process (Clk)
    variable Sum_TXBuffer : unsigned(7+2 + C_Buffer_Length downto 0) := (others => ('0'));
    variable Sum_RXBuffer : unsigned(7+2 + C_Buffer_Length downto 0) := (others => ('0'));
begin
    if (rising_edge(Clk)) then
        Bram_Wea_Prev  <=  Bram_Wea;
        case State is
            when S_IDLE =>
                Timeout_Timer   <= 0;
                TX_Start        <= '0';
                TX_Data_In      <= (others => '0');
                Command_Buffer  <= C_Buffer;
                Response_Buffer <= C_Buffer;
                Address_IDX     <= 0;
                Data_IDX        <= 0;
                Response_IDX    <= 0;
                Bram_Wea        <= '0';
                TX_Inprogress   <= '0';
                if (RX_Done_Tick = '1' and RX_Data_Out =  STD_LOGIC_VECTOR(to_unsigned(C_Start_Byte_1 ,8))) then
                    State   <= S_START_1;
                end if;
                
            when S_START_1 =>
                if (RX_Done_Tick = '1' and RX_Data_Out = STD_LOGIC_VECTOR(to_unsigned( C_Start_Byte_2 ,8))) then
                    State <= S_RD_CMND;
                    Timeout_Timer <= 0;
                else
                    if (Timeout_Timer = C_Timeout_Lim - 1) then
                        State   <= S_IDLE;
                        Timeout_Timer  <= 0;
                    else
                        Timeout_Timer <= Timeout_Timer + 1 ;
                    end if;
                end if;
                
            when S_RD_CMND =>
                if (RX_Done_Tick = '1') then
                    State <= S_RD_CMND_ADDR;
                    Address_IDX <= 0;
                    Timeout_Timer <= 0;
                    Command_Buffer(0) <= RX_Data_Out;
                else
                    if (Timeout_Timer = C_Timeout_Lim - 1) then
                        State   <= S_IDLE;
                        Timeout_Timer  <= 0;
                    else
                        Timeout_Timer <= Timeout_Timer + 1 ;
                    end if;
                end if;
                
            when S_RD_CMND_ADDR =>
                if (RX_Done_Tick = '1') then
                    Timeout_Timer <= 0;
                    Command_Buffer(Address_IDX + 1) <= RX_Data_Out;
                    if (Address_IDX = (C_Address_Length - 1)) then
                        State <= S_RD_CMND_DATA;
                        Address_IDX <= 0;
                        Data_IDX <= 0;
                    else
                        Address_IDX <= Address_IDX + 1;
                    end if;
                else
                    if (Timeout_Timer = C_Timeout_Lim - 1) then
                        State <= S_IDLE;
                        Timeout_Timer <= 0;
                    else
                        Timeout_Timer <= Timeout_Timer + 1 ;
                    end if;
                end if;
            
            when S_RD_CMND_DATA =>
                if (RX_Done_Tick = '1') then
                    Timeout_Timer <= 0;
                    Command_Buffer(Data_IDX + C_Address_Length + 1) <= RX_Data_Out;
                    if (Data_IDX = (C_Address_Length - 1)) then
                        State <= S_RD_CMND_CS;
                        Data_IDX  <= 0;
                    else
                        Data_IDX <= Data_IDX + 1;
                    end if;
                else
                    if (Timeout_Timer = C_Timeout_Lim - 1) then
                        State <= S_IDLE;
                        Timeout_Timer <= 0;
                    else
                        Timeout_Timer <= Timeout_Timer + 1 ;
                    end if;
                end if;
                
            when S_RD_CMND_CS =>
                if (RX_Done_Tick = '1') then
                    State <= S_CHECK_CMND_CS;
                    Timeout_Timer <= 0;
                    Command_Buffer(1 + C_Address_Length + C_Data_Length) <= RX_Data_Out;
                else
                    if (Timeout_Timer = C_Timeout_Lim - 1) then
                        State <= S_IDLE;
                        Timeout_Timer <= 0;
                    else
                        Timeout_Timer <= Timeout_Timer + 1;
                    end if;
                end if;
                
            when S_CHECK_CMND_CS =>
                if (Command_Buffer(1 + C_Address_Length + C_Data_Length) = CheckSum_RXBuffer) then
                    if (Command_Buffer(0) =  STD_LOGIC_VECTOR(to_unsigned(C_Command_Write, 8))) then
                        State <= S_WR_BRAM;
                        Bram_Wea <= '0';
                    else
                        State <= S_RD_BRAM;
                    end if;
                else
                    Response_Buffer(0) <= STD_LOGIC_VECTOR(to_unsigned( C_Response_CheckSum, 8));  -- Checksum Error
                    Loop1 : for AddressLoop in 0 to (C_Address_Length - 1) loop
                        Response_Buffer(1 + AddressLoop) <= x"00" ;
                    end loop Loop1;
                    Loop2 : for DataLoop in 0 to (C_Data_Length - 1 ) loop
                        Response_Buffer(1 + C_Address_Length + DataLoop) <= x"00" ;
                    end loop Loop2;
                    State <= S_SND_RESP;
                    TX_Inprogress <= '0';
                    Response_IDX <= 0;
                end if;
              
            when S_WR_BRAM => 
                if (Bram_Wea = '0' and Bram_Wea_Prev = '0') then
                    Bram_Wea <= '1';
                elsif (Bram_Wea = '1' and Bram_Wea_Prev ='0') then -- State ilk giris
                elsif (Bram_Wea = '1' and Bram_Wea_Prev ='1') then -- State ikinci giris
                    Bram_Wea <= '0';
                    Response_Buffer(0)  <= STD_LOGIC_VECTOR(to_unsigned(C_Response_Write_Done, 8));
                    ResponseWriter : for ByteIDX in 0 to (C_Address_Length + C_Data_Length - 1) loop
                        Response_Buffer(1 + ByteIDX) <= Command_Buffer(1 + ByteIDX);
                    end loop ResponseWriter;
                    State <= S_SND_RESP;
                end if;
                
            when S_RD_BRAM =>
                Response_Buffer(0) <= STD_LOGIC_VECTOR(to_unsigned(C_Response_Read_Done, 8));
                Response_AddressWriter : for ByteIDX in 0 to (C_Address_Length - 1) loop
                    Response_Buffer(1 + ByteIDX) <= Command_Buffer(1 + ByteIDX);
                end loop Response_AddressWriter;
                Response_DataWriter : for ByteIDX in 0 to (C_Data_Length - 1) loop
                    Response_Buffer(1 + C_Address_Length + ByteIDX) <= Bram_Douta_Arr(ByteIDX);
                end loop Response_DataWriter;
                State  <= S_SND_RESP;
                           
            when S_SND_RESP =>
                if (TX_Done_Tick ='1') then
                    TX_Inprogress  <= '0';
                end if;
                if (TX_Inprogress = '0') then
                    if (Response_IDX < (C_Buffer_Length +2)) then
                        TX_Inprogress <= '1';
                        TX_Start <= '1';
                        Response_IDX <= Response_IDX + 1;
                        if (Response_IDX = 0) then
                            TX_Data_In <= STD_LOGIC_VECTOR(to_unsigned(C_Start_Byte_1, 8));
                        elsif (Response_IDX = 1) then
                            TX_Data_In <= STD_LOGIC_VECTOR(to_unsigned(C_Start_Byte_2, 8));
                        elsif (Response_IDX = (C_Buffer_Length +1)) then
                            TX_Data_In <= CheckSum_TXBuffer;
                        else
                            TX_Data_In <= Response_Buffer(Response_IDX - 2);
                        end if;
                    else
                        State <= S_IDLE;
                    end if;
                else
                    TX_Start <= '0';
                end if;
        end case;

        -- Checksum Calculation FOR RX Buffer
        RXBuffer_CheckSum_Calculation : for RX_BufferIDX in 0 to ( C_Buffer_Length - 2 ) loop
            if (RX_BufferIDX = 0) then
                Sum_RXBuffer := to_unsigned(C_Start_Byte_1, Sum_RXBuffer'length) + to_unsigned(C_Start_Byte_2, Sum_RXBuffer'length) + resize(unsigned(Command_Buffer(0)), Sum_RXBuffer'length);
            else
                Sum_RXBuffer := Sum_RXBuffer + resize(unsigned(Command_Buffer(RX_BufferIDX)), Sum_RXBuffer'length);
            end if;
        end loop RXBuffer_CheckSum_Calculation;
        Sum_RXBuffer_Lv <= STD_LOGIC_VECTOR(Sum_RXBuffer);
        
        -- Checksum Calculation FOR TX Buffer
        TXBuffer_CheckSum_Calculation : for TX_BufferIDX in 0 to ( C_Buffer_Length - 1 ) loop
            if (TX_BufferIDX = 0) then
                Sum_TXBuffer := to_unsigned(C_Start_Byte_1, Sum_TXBuffer'length) + to_unsigned(C_Start_Byte_2, Sum_TXBuffer'length) + resize(unsigned(Response_Buffer(0)), Sum_TXBuffer'length );
            else
                Sum_TXBuffer := Sum_TXBuffer + resize(unsigned(Response_Buffer(TX_BufferIDX)), Sum_TXBuffer'length);
            end if;
        end loop TXBuffer_CheckSum_Calculation;
        Sum_TXBuffer_Lv <= STD_LOGIC_VECTOR(Sum_TXBuffer);
        
    end if;
end process;

end Behavioral;