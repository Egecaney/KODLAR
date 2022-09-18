library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity TestBench_Data_Memory is
end TestBench_Data_Memory;

architecture Behavioral of TestBench_Data_Memory is

component Data_Memory is
    Port ( Clk                      : in STD_LOGIC;
           In_Memory_Access_Address : in STD_LOGIC_VECTOR(15 downto 0);
           In_Memory_Write_Data     : in STD_LOGIC_VECTOR(15 downto 0);
           In_Memory_Write_Enable   : in STD_LOGIC;
           In_Memory_Read           : in STD_LOGIC;
           Out_Memory_Read_Data     : out STD_LOGIC_VECTOR(15 downto 0));
end component;

signal Clk                      : STD_LOGIC := '0';
signal In_Memory_Access_Address : STD_LOGIC_VECTOR(15 downto 0) := (others => '0');
signal In_Memory_Write_Data     : STD_LOGIC_VECTOR(15 downto 0) := (others => '0');
signal In_Memory_Write_Enable   : STD_LOGIC := '0';
signal In_Memory_Read           : STD_LOGIC := '0';
signal Out_Memory_Read_Data     : STD_LOGIC_VECTOR(15 downto 0);

constant C_Clock_Period : time := 10ns;

begin

Data_Memory_DUT : Data_Memory
    Port Map (Clk => Clk, In_Memory_Access_Address => In_Memory_Access_Address, In_Memory_Write_Data => In_Memory_Write_Data, In_Memory_Write_Enable => In_Memory_Write_Enable, In_Memory_Read => In_Memory_Read, Out_Memory_Read_Data => Out_Memory_Read_Data);
        
P_Clock_Generation : process begin
    Clk <= '0';
    wait for C_Clock_Period/2;
    Clk <= '1';
    wait for C_Clock_Period/2;
end process;

P_STIMULI : process begin
    wait for C_Clock_Period*2;
    
    In_Memory_Access_Address <= x"01A0";
    In_Memory_Write_Data     <= x"1111";
    In_Memory_Write_Enable   <= '0';
    In_Memory_Read           <= '0';
    
    wait for C_Clock_Period*2;
    
    In_Memory_Access_Address <= x"01A0";
    In_Memory_Write_Data     <= x"1111";
    In_Memory_Write_Enable   <= '1';
    In_Memory_Read           <= '0';
    
    wait for C_Clock_Period*2;
    
    In_Memory_Access_Address <= x"0100";
    In_Memory_Write_Data     <= x"1001";
    In_Memory_Write_Enable   <= '1';
    In_Memory_Read           <= '0';
    
    wait for C_Clock_Period*2;
    
    In_Memory_Access_Address <= x"01A0";
    In_Memory_Write_Enable   <= '0';
    In_Memory_Read           <= '1';
    
    wait for C_Clock_Period*2;
    
    In_Memory_Access_Address <= x"0100";
    In_Memory_Write_Enable   <= '0';
    In_Memory_Read           <= '0';
    
    wait for C_Clock_Period*2;
    
    In_Memory_Access_Address <= x"0100";
    In_Memory_Write_Enable   <= '0';
    In_Memory_Read           <= '1';
    
    wait for C_Clock_Period*2;
    
    assert false
    report "SIM DONE"
    severity failure;
end process;

end Behavioral;
