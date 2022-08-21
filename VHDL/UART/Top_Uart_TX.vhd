library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Top_Uart_TX is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Baud_Rate       : integer := 115_200;
        C_Stop_Bits       : integer := 2);
    Port(
        Clk               : in STD_LOGIC;
        In_Switch         : in STD_LOGIC_VECTOR (7 downto 0);
        In_Button         : in STD_LOGIC;
        Out_TX            : out STD_LOGIC);
end Top_Uart_TX;

architecture Behavioral of Top_Uart_TX is

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

component Debounce is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Debounce_Time  : integer := 1000;
        C_Initial_Value  : STD_LOGIC := '0');
    Port(
        Clk : in STD_LOGIC ;
        In_Signal : in STD_LOGIC;
        Out_Signal : out STD_LOGIC);
end component;

signal S_Button_Debounce      : STD_LOGIC := '0';
signal S_Button_Debounce_Prev : STD_LOGIC := '0';
signal S_TX_Start             : STD_LOGIC := '0';
signal S_TX_Done_Tick         : STD_LOGIC := '0';

begin

Uart_TX_Instantiation : Uart_TX
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Baud_Rate => C_Baud_Rate, C_Stop_Bits => C_Stop_Bits)
    Port Map (Clk => Clk, In_Data => In_Switch, In_TX_Start => S_TX_Start, Out_TX => Out_TX, Out_TX_Done_Tick => S_TX_Done_Tick);

Debounce_Instantiation : Debounce
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Debounce_Time => 1000, C_Initial_Value => '0')
    Port Map(Clk => Clk, In_Signal => In_Button, Out_Signal => S_Button_Debounce);

process (Clk) begin
    if (rising_edge(Clk)) then
        S_Button_Debounce_Prev	<= S_Button_Debounce;
        S_TX_Start		<= '0';
        if (S_Button_Debounce = '1' and S_Button_Debounce_Prev = '0') then
            S_TX_Start	<= '1';
        end if;
    end if;
end process;  
    
end Behavioral;
