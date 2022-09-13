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
use work.Ram_PKG.all;
USE std.textio.all;

entity UART_I2C_SPI is
    Generic ( C_Clock_Frequency : integer   := 100_000_000;
              C_Baud_Rate       : integer   := 115_200;
              C_Stop_Bits       : integer   := 2;
              C_SCL_Frequency   : integer   := 400_000;
              C_Device_Address  : STD_LOGIC_VECTOR(6 downto 0) := "1001011";
              C_SCLK_Frequency  : integer   := 1_000_000;
              C_Read_Frequency  : integer   := 2;
              C_Block_RAM_Width : integer 	:= 8;
              C_Block_RAM_Depth : integer 	:= 128;
              C_RAM_Performance : string 	:= "LOW_LATENCY";
              C_RAM_Type 		: string 	:= "Block");
       Port ( Clk               : in STD_LOGIC;
              SDA               : inout STD_LOGIC;
              SCL               : inout STD_LOGIC;
              MISO 	            : in  STD_LOGIC;
              CS		        : out STD_LOGIC;
              SCLK 	            : out STD_LOGIC;
              MOSI		        : out STD_LOGIC;
              In_RX             : in STD_LOGIC;
              Out_TX            : out STD_LOGIC;
              Out_Leds          : out STD_LOGIC_VECTOR(3 downto 0));
end UART_I2C_SPI;

architecture Behavioral of UART_I2C_SPI is

component Uart_RX is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Baud_Rate       : integer := 115_200);
    Port(
        Clk               : in STD_LOGIC;
        In_RX             : in STD_LOGIC;
        Out_Data          : out STD_LOGIC_VECTOR (7 downto 0);
        Out_RX_Done_Tick  : out STD_LOGIC );
end component;

component Uart_TX is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Baud_Rate       : integer := 115_200;
        C_Stop_Bits       : integer := 2);
    Port(
        Clk               : in STD_LOGIC;
        In_Data           : in STD_LOGIC_VECTOR (7 downto 0);
        In_TX_Start       : in STD_LOGIC;
        Out_TX            : out STD_LOGIC;
        Out_TX_Done_Tick  : out STD_LOGIC );
end component;

component Block_RAM is
    Generic ( RAM_WIDTH 	  : integer 	:= 16;
              RAM_DEPTH 	  : integer 	:= 128;
              RAM_PERFORMANCE : string 	:= "LOW_LATENCY";
              C_RAM_TYPE 	  : string 	:= "BLOCK");
       Port ( Addra           : in STD_LOGIC_VECTOR((clogb2(RAM_DEPTH)-1) downto 0);
              Dina            : in STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0);
              Clka            : in STD_LOGIC;
              Wea             : in STD_LOGIC;
              Douta           : out STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0));
end component;

component ADXL362 is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCLK_Frequency  : integer := 1_000_000;
              C_Read_Frequency  : integer := 100);
       Port ( Clk 			    : in  STD_LOGIC;
              In_MISO 	        : in  STD_LOGIC;
              Out_CS		    : out STD_LOGIC;
              Out_SCLK 	        : out STD_LOGIC;
              Out_MOSI		    : out STD_LOGIC;
              Out_AX            : out STD_LOGIC_VECTOR (15 downto 0);
              Out_AY	        : out STD_LOGIC_VECTOR (15 downto 0);
              Out_AZ	        : out STD_LOGIC_VECTOR (15 downto 0);
              Out_Ready         : out STD_LOGIC);
end component;

component ADT7420 is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCL_Frequency   : integer := 400_000;
              C_Device_Address  : STD_LOGIC_VECTOR(6 downto 0) := "1001011");  
       Port ( Clk               : in STD_LOGIC;                         
              Reset             : in STD_LOGIC;
              SDA               : inout STD_LOGIC;
              SCL               : inout STD_LOGIC;
              Out_Interrupt     : out STD_LOGIC;
              Out_Temperature   : out STD_LOGIC_VECTOR(12 downto 0));
end component;

signal S_Data_Buffer      : STD_LOGIC_VECTOR(23 downto 0) := (others => '0');
signal S_Counter          : integer range 0 to 255 := 0;

signal S_Data_Out 		  : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
signal S_Data_In		  : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
signal S_RX_Done_Tick     : STD_LOGIC := '0';
signal S_TX_Start 	      : STD_LOGIC := '0';
signal S_TX_Done_Tick     : STD_LOGIC := '0';
signal S_UART_Once        : STD_LOGIC := '0';

signal S_Addra 			  : STD_LOGIC_VECTOR((clogb2(C_Block_RAM_Depth)-1) downto 0) := (others => '0');    
signal S_Dina  			  : STD_LOGIC_VECTOR(C_Block_RAM_Width-1 downto 0) := (others => '0');
signal S_Wea   			  : STD_LOGIC := '0'; 
signal S_Douta 			  : STD_LOGIC_VECTOR(C_Block_RAM_Width-1 downto 0) := (others => '0'); 

signal S_Interrupt 	      : STD_LOGIC := '0';
signal S_Temperature	  : STD_LOGIC_VECTOR (12 downto 0) := (others => '0');
signal S_Sign	          : STD_LOGIC_VECTOR (2 downto 0)  := (others => '0');

signal S_AX			      : STD_LOGIC_VECTOR (15 downto 0)	:= (others => '0');
signal S_AY			      : STD_LOGIC_VECTOR (15 downto 0)	:= (others => '0');
signal S_AZ			      : STD_LOGIC_VECTOR (15 downto 0)	:= (others => '0');
signal S_Ready		      : STD_LOGIC	:= '0';
signal S_Sent_Trig	      : STD_LOGIC	:= '0';
signal S_TX_Buffer	      : STD_LOGIC_VECTOR (6*8-1 downto 0)	:= (others => '0');

type T_Device_Selection is (S_Selection, S_UART, S_I2C, S_SPI);
signal Device_Selection : T_Device_Selection := S_Selection;

type T_UART is (S_Idle, S_Read, S_Write, S_Transmit);
signal UART : T_UART := S_Idle;

begin

Uart_RX_Instantiation : Uart_RX 
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Baud_Rate => C_Baud_Rate)
    Port Map (Clk => Clk, In_RX => In_RX, Out_Data => S_Data_Out, Out_RX_Done_Tick => S_RX_Done_Tick);

Uart_TX_Instantiation : Uart_TX 
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Baud_Rate => C_Baud_Rate, C_Stop_Bits => C_Stop_Bits)
    Port Map (Clk => Clk, In_Data => S_Data_In, In_TX_Start => S_TX_Start, Out_TX => Out_TX, Out_TX_Done_Tick => S_TX_Done_Tick);
    
Block_RAM_128x16_Instantiation: Block_RAM
    Generic Map(RAM_WIDTH => C_Block_RAM_Width, RAM_DEPTH => C_Block_RAM_Depth, RAM_PERFORMANCE => C_RAM_Performance, C_RAM_TYPE=> C_RAM_Type)
    Port Map (Addra => S_Addra, Dina => S_Dina, Clka => Clk, Wea => S_Wea, Douta => S_Douta);

ADT7420_Instantiation : ADT7420
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_SCL_Frequency => C_SCL_Frequency, C_Device_Address => C_Device_Address)
    Port Map (Clk => Clk, Reset => '1', SDA => SDA, SCL => SCL, Out_Interrupt => S_Interrupt, Out_Temperature => S_Temperature);

ADXL362_Instantiation : ADXL362
    Generic Map(C_Clock_Frequency => C_Clock_Frequency, C_SCLK_Frequency => C_SCLK_Frequency, C_Read_Frequency => C_Read_Frequency)
    Port map(Clk => Clk, In_MISO => MISO, Out_MOSI => MOSI, Out_SCLK => SCLK, Out_CS => CS, Out_AX => S_AX, Out_AY => S_AY, Out_AZ => S_AZ, Out_Ready => S_Ready);
    
P_Device_Selection : process (Clk) begin
    if (rising_edge(Clk)) then
        case Device_Selection is
            
            when S_Selection =>
                if (S_RX_Done_Tick = '1') then
                    S_Data_Buffer(7 downto 0) <= S_Data_Out;
                    S_Data_Buffer(23 downto 8) <= S_Data_Buffer(15 downto 0);
                end if;
                if (S_Data_Buffer(23 downto 22) = "01") then
                    Device_Selection <= S_UART;
                    S_UART_Once <= '1';
                end if;
                if (S_Data_Buffer(23 downto 22) = "10") then
                    Device_Selection <= S_I2C;
                    Out_Leds <= "0100";
                end if;
                if (S_Data_Buffer(23 downto 22) = "11") then
                    Device_Selection <= S_SPI;
                    Out_Leds <= "1000";
                end if;
            
            when S_UART =>
                case UART is
                    when S_Idle =>
                        S_Wea <= '0';
                        S_Counter <= 0;
                        if (S_UART_Once = '1') then
                            S_UART_Once <= '0';
                            if (S_Data_Buffer(21) = '1') then
                                UART <= S_Write;
                            end if;
                            if (S_Data_Buffer(21) = '0') then
                                UART <= S_Read;
                            end if;
                        end if;

                    when S_Write =>
                        S_Addra	<= S_Data_Buffer(20 downto 14);
                        S_Dina <= S_Data_Buffer(13 downto 6);
                        S_Wea <= '1';
                        UART <= S_Idle;
                        S_Data_Buffer <= (others => '0');
                        Out_Leds <= "0010";
                        Device_Selection <= S_Selection;
                    
                    when S_Read=>
                        S_Addra <= S_Data_Buffer(20 downto 14);
                        S_Counter <= S_Counter + 1;
                        Out_Leds <= "0001";
                        if (S_Counter = 1) then
                            S_Data_In <= S_Douta;
                            UART <= S_Transmit;	
                            S_Counter <= S_Counter - 1;
                            S_TX_Start <= '1';
                        end if;
                    
                    when S_Transmit =>  
                        if (S_Counter = 0) then
                            S_TX_Start <= '0';
                            if (S_TX_Done_Tick = '1') then
                                UART <= S_Idle;
                                Device_Selection <= S_Selection;
                                S_Data_Buffer <= (others => '0');
                            end if;				
                        end if;
                end case;
            
            when S_I2C =>
                S_Sign <= S_Temperature(12) & S_Temperature(12) & S_Temperature(12);
                S_Data_In <= S_Temperature(7 downto 0);
                if (S_Interrupt = '1') then
                    S_Data_In <= S_Sign & S_Temperature(12 downto 8);
                    S_TX_Start	<= '1';
                end if;		
                if (S_TX_Done_Tick = '1') then
                    S_TX_Start	<= '0';
                    Device_Selection <= S_Selection;
                    S_Data_Buffer <= (others => '0');
                end if;
                
            when S_SPI =>
                if (S_Ready = '1') then
                    S_TX_Buffer	<= S_AX & S_AY & S_AZ;
                    S_Counter <= 6;
                    S_Sent_Trig	<= '1';
                end if;
                S_Data_In <= S_TX_Buffer(6*8-1 downto 5*8);
                if (S_Sent_Trig = '1') then
                    if (S_Counter = 6) then
                        S_TX_Start <= '1';
                        S_TX_Buffer(6*8-1 downto 8)	<= S_TX_Buffer(5*8-1 downto 0);
                        S_Counter <= S_Counter - 1;	
                    elsif (S_Counter = 0) then
                        S_TX_Start <= '0';
                        if (S_TX_Done_Tick = '1') then
                            S_Sent_Trig	<= '0';
                            Device_Selection <= S_Selection;
                            S_Data_Buffer <= (others => '0');
                        end if;
                    else
                        if (S_TX_Done_Tick = '1') then
                            S_Counter <= S_Counter - 1;
                            S_TX_Buffer(6*8-1 downto 8)	<= S_TX_Buffer(5*8-1 downto 0);
                        end if;
                    end if;
                end if;
        end case;  
    end if;
end process;
    

end Behavioral;
