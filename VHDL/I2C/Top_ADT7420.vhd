library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity Top_ADT7420 IS
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCL_Frequency   : integer := 400_000;
              C_Device_Address  : STD_LOGIC_VECTOR(6 downto 0) := "1001011";
              C_Baud_Rate       : integer := 115_200;
              C_Stop_Bits       : integer := 1);
       Port ( Clk               : in STD_LOGIC;                         
              Reset             : in STD_LOGIC;
              SDA               : inout STD_LOGIC;
              SCL               : inout STD_LOGIC;
              Out_TX            : out STD_LOGIC);
end Top_ADT7420;

architecture Behavioral of Top_ADT7420 is

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

component Uart_TX is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_Baud_Rate       : integer := 115_200;
              C_Stop_Bits       : integer := 2);
       Port ( Clk               : in STD_LOGIC;
              In_Data           : in STD_LOGIC_VECTOR (7 downto 0);
              In_TX_Start       : in STD_LOGIC;
              Out_TX            : out STD_LOGIC;
              Out_TX_Done_Tick  : out STD_LOGIC);
end component;

-- UART_TX Signals
signal S_TX_Start 	     : STD_LOGIC := '0';
signal S_TX_Done_Tick    : STD_LOGIC := '0';
signal S_Data			 : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');

-- ADT7420 Signals
signal S_Interrupt 	     : STD_LOGIC := '0';
signal S_Temperature	 : STD_LOGIC_VECTOR (12 downto 0) := (others => '0');
signal S_Sign		 	 : STD_LOGIC_VECTOR (2 downto 0)  := (others => '0');

begin

ADT7420_Instantiation : ADT7420
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_SCL_Frequency => C_SCL_Frequency, C_Device_Address => C_Device_Address)
    Port Map (Clk => Clk, Reset => Reset, SDA => SDA, SCL => SCL, Out_Interrupt => S_Interrupt, Out_Temperature => S_Temperature);

Uart_TX_Instantiation : Uart_TX
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Baud_Rate => C_Baud_Rate, C_Stop_Bits => C_Stop_Bits)
    Port Map (Clk => Clk, In_Data => S_Data, In_TX_Start => S_TX_Start, Out_TX => Out_TX, Out_TX_Done_Tick => S_TX_Done_Tick);         
              
S_Sign <= S_Temperature(12) & S_Temperature(12) & S_Temperature(12);

process (Clk) begin
    if (rising_edge(Clk)) then
        S_Data <= S_Temperature(7 downto 0);
        if (S_Interrupt = '1') then
            S_Data <= S_Sign & S_Temperature(12 downto 8);
            S_TX_Start	<= '1';
        end if;		
        if (S_TX_Done_Tick = '1') then
            S_TX_Start	<= '0';
        end if;  
    end if;
end process;

end Behavioral;
