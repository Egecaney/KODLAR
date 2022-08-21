library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity TestBench_Uart_TX is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Baud_Rate       : integer := 10_000_000;
        C_Stop_Bits       : integer := 2);
end TestBench_Uart_TX;

architecture Behavioral of TestBench_Uart_TX is

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

constant C_Clock_Period : time := 10ns;

signal Clk              : STD_LOGIC;
signal In_Data          : STD_LOGIC_VECTOR (7 downto 0);
signal In_TX_Start      : STD_LOGIC;
signal Out_TX           : STD_LOGIC;
signal Out_TX_Done_Tick : STD_LOGIC ;

begin

Uart_TX_DUT : Uart_TX
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Baud_Rate => C_Baud_Rate, C_Stop_Bits => C_Stop_Bits)
    Port Map (Clk => Clk, In_Data => In_Data, In_TX_Start => In_TX_Start, Out_TX => Out_TX, Out_TX_Done_Tick => Out_TX_Done_Tick);

P_Clock_Generation : process begin
    Clk <= '0';
    wait for C_Clock_Period/2;
    Clk <= '1';
    wait for C_Clock_Period/2;
end process;

P_STIMULI : process begin
    In_Data			<= x"00";
    In_TX_Start		<= '0';
    wait for C_Clock_Period*10;
    
    In_Data		<= x"51";
    In_TX_Start	<= '1';
    wait for C_Clock_Period;
    
    In_TX_Start	<= '0';
    wait for 1.2 us;
    
    In_Data		<= x"A3";
    In_TX_Start	<= '1';
    wait for C_Clock_Period;
    
    In_TX_Start	<= '0'; 
    wait until (rising_edge(Out_TX_Done_Tick));
    
    wait for 1 us;
    assert false
    report "SIM DONE"
    severity failure;
end process ;

end Behavioral;
