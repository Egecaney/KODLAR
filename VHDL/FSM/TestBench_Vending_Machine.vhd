library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity TestBench_Vending_Machine is
end TestBench_Vending_Machine;

architecture Behavioral of TestBench_Vending_Machine is

component FSM_Vending_Machine is
    Port ( Clk          : in STD_LOGIC; 
           Reset        : in STD_LOGIC;
           In_Dolar     : in STD_LOGIC; 
           In_Quarter   : in STD_LOGIC;
           Out_Dispense : out STD_LOGIC; 
           Out_Change   : out STD_LOGIC);
end component;

constant C_Clock_Period : time := 20ns;

signal Clk          : STD_LOGIC := '0';
signal Reset        : STD_LOGIC := '0';
signal In_Dolar     : STD_LOGIC := '0';
signal In_Quarter   : STD_LOGIC := '0';
signal Out_Dispense : STD_LOGIC;
signal Out_Change   : STD_LOGIC;

begin

DUT_Vending_Machine : FSM_Vending_Machine
    Port Map (Clk => Clk, Reset => Reset, In_Dolar => In_Dolar, In_Quarter => In_Quarter, Out_Dispense => Out_Dispense, Out_Change => Out_Change);
    
P_Clock_Generation : process begin
    Clk <= '0'; wait for C_Clock_Period/2;
    Clk <= '1'; wait for C_Clock_Period/2;
end process;

Reset_STIM : process begin
    Reset <= '0'; wait for 2 ns;
    Reset <= '1'; wait;
end process;

--Dolar_STIM : process begin
--    In_Dolar <= '0'; wait for 5 ns;
--    In_Dolar <= '1'; wait for 5 ns;
--    In_Dolar <= '0'; wait;
--end process;

Quarter_STIM : process begin
    In_Quarter <= '0'; wait for 25 ns;
    
    In_Quarter <= '1'; wait for 5 ns;
    In_Quarter <= '0'; wait for 15 ns;
       
    In_Quarter <= '1'; wait for 5 ns;
    In_Quarter <= '0'; wait for 15 ns;
    
    In_Quarter <= '1'; wait for 5 ns;
    In_Quarter <= '0'; wait for 15 ns;
    
    In_Dolar <= '1'; wait for 5 ns;
    In_Dolar <= '0'; wait for 5 ns;
    
    In_Quarter <= '1'; wait for 10 ns;
    In_Quarter <= '0'; wait for 15 ns;
       
    In_Quarter <= '1'; wait for 10 ns;
    In_Quarter <= '0'; wait for 15 ns;
    
    In_Quarter <= '1'; wait for 10 ns;
    In_Quarter <= '0'; wait for 15 ns;
    
    assert false
    report "SIM DONE"
    severity failure;
    
end process;

end Behavioral;
