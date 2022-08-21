library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity TestBench_Uart_RX is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Baud_Rate       : integer := 115_200);
end TestBench_Uart_RX;

architecture Behavioral of TestBench_Uart_RX is

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

constant C_Clock_Period : time := 10ns;

signal Clk              : STD_LOGIC := '0';
signal In_RX            : STD_LOGIC := '1';  -- '1' IDLE durumdur. 
signal Out_Data         : STD_LOGIC_VECTOR (7 downto 0);
signal Out_RX_Done_Tick : STD_LOGIC;

constant C_Baud_Rate_115200	: time := 8.68 us;   -- 1/115200
constant C_HEX_Value_43		: STD_LOGIC_VECTOR (9 downto 0) := '1' & x"43" & '0';
constant C_HEX_Value_A5		: STD_LOGIC_VECTOR (9 downto 0) := '1' & x"A5" & '0';
        
begin

Uart_RX_DUT : Uart_RX
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Baud_Rate => C_Baud_Rate)
    Port Map (Clk => Clk, In_RX => In_RX, Out_Data => Out_Data, Out_RX_Done_Tick => Out_RX_Done_Tick);

P_Clock_Generation : process begin
    Clk <= '0';
    wait for C_Clock_Period/2;
    Clk <= '1';
    wait for C_Clock_Period/2;
end process;

P_STIMULI : process begin
    wait for C_Clock_Period*10;
    
    for i in 0 to 9 loop
        In_RX <= C_HEX_Value_43(i);
        wait for C_Baud_Rate_115200;
    end loop;
    
    wait for 10 us;
    
    for i in 0 to 9 loop
        In_RX <= C_HEX_Value_A5(i);
        wait for C_Baud_Rate_115200;
    end loop; 
    
    wait for 20 us;
    
    assert false
    report "SIM DONE"
    severity failure;

end process P_STIMULI;

end Behavioral;
