library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity TestBench_Program_Counter is
end TestBench_Program_Counter;

architecture Behavioral of TestBench_Program_Counter is

component Program_Counter is
    Port ( Clk       : in STD_LOGIC;
           Reset     : in STD_LOGIC;
           In_Enable : in STD_LOGIC;
           In_Load   : in STD_LOGIC;
           Input     : in STD_LOGIC_VECTOR(3 downto 0);
           Output    : out STD_LOGIC_VECTOR(3 downto 0));
end component;

constant C_Clock_Period : time := 10ns;

signal Clk       : STD_LOGIC := '0';
signal Reset     : STD_LOGIC := '0';
signal In_Enable : STD_LOGIC := '0';
signal In_Load   : STD_LOGIC := '0';
signal Input     : STD_LOGIC_VECTOR(3 downto 0) := (others => '0');
signal Output    : STD_LOGIC_VECTOR(3 downto 0);

begin

PC_DUT : Program_Counter
    Port Map (Clk => Clk, Reset => Reset, In_Enable => In_Enable, In_Load => In_Load, Input => Input, Output => Output);
    
P_Clock_Generation : process begin
    Clk <= '0';
    wait for C_Clock_Period/2;
    Clk <= '1';
    wait for C_Clock_Period/2;
end process;

P_STIMULI : process begin
    wait for C_Clock_Period*2;
    
    In_Enable <= '1';
    wait for C_Clock_Period*2;
    
    In_Enable <= '0';
    Reset     <= '1';
    wait for C_Clock_Period*2;
    
    In_Enable <= '1';
    Reset     <= '0';
    wait for C_Clock_Period*2;
    
    In_Enable <= '1';
    In_Load   <= '1';
    Input     <= "1010";
    wait for C_Clock_Period*2;
    
    In_Enable <= '1';
    In_Load   <= '0';
    wait for C_Clock_Period*2;
    
    In_Enable <= '1';
    In_Load   <= '0';
    wait for C_Clock_Period*2;
    
    In_Enable <= '0';
    wait for C_Clock_Period*2;
    
    Reset     <= '1';
    wait for C_Clock_Period*2;
    
    assert false
    report "SIM DONE"
    severity failure;
end process; 

end Behavioral;
