library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity TestBench_Debounce is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Debounce_Time  : integer := 1000;
        C_Initial_Value  : STD_LOGIC := '0');
end TestBench_Debounce;

architecture Behavioral of TestBench_Debounce is

component Debounce is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Debounce_Time  : integer := 1000;
        C_Initial_Value  : STD_LOGIC := '0');
    Port(
        Clk        : in STD_LOGIC ;
        In_Signal  : in STD_LOGIC;
        Out_Signal : out STD_LOGIC);
end component;

signal Clk        : STD_LOGIC := '0';
signal In_Signal  : STD_LOGIC := '0';
signal Out_Signal : STD_LOGIC := '0';

constant C_Clock_Period : time := 10ns;

begin

Debounce_DUT : Debounce
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Debounce_Time => C_Debounce_Time, C_Initial_Value => C_Initial_Value)
    Port Map(Clk => Clk, In_Signal => In_Signal, Out_Signal => Out_Signal);

P_Clock_Generation : process begin
    Clk <= '0';
    wait for C_Clock_Period/2;
    Clk <= '1';
    wait for C_Clock_Period/2;
end process;

P_STIMULI : process begin
    In_Signal	<= '0';
    wait for 2 ms;
    
    In_Signal	<= '1';
    wait for 100 us;
    In_Signal	<= '0';
    wait for 200 us;
    In_Signal	<= '1';
    wait for 100 us;
    In_Signal	<= '0';
    wait for 100 us;
    In_Signal	<= '1';
    wait for 800 us;
    In_Signal	<= '0';
    wait for 50 us;
    In_Signal	<= '1';
    wait for 3 ms;
    
    In_Signal 	<= '0';
    wait for 100 us;
    In_Signal 	<= '1';
    wait for 200 us;
    In_Signal 	<= '0';
    wait for 950 us;
    In_Signal 	<= '1';
    wait for 150 us;
    In_Signal 	<= '0';
    wait for 2 ms;
    
    assert false
    report "SIM DONE"
    severity failure;
end process;

end Behavioral;
