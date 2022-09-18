library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.NUMERIC_STD.all;

entity TestBench_MIPS_Register_File is
    Generic ( C_Bit     : integer := 32;
              C_Address : integer := 5);
end TestBench_MIPS_Register_File;

architecture Behavioral of TestBench_MIPS_Register_File is

component MIPS_Register_File is
    Generic ( C_Bit     : integer := 32;
              C_Address : integer := 5);
       Port ( In_Read_Register_Address_1  : in STD_LOGIC_VECTOR(C_Address-1 downto 0);
              In_Read_Register_Address_2  : in STD_LOGIC_VECTOR(C_Address-1 downto 0);
              In_Write_Register           : in STD_LOGIC_VECTOR(C_Address-1 downto 0);
              In_Write_Register_Data      : in STD_LOGIC_VECTOR(C_Bit-1 downto 0);
              In_Write_Register_Enable    : in STD_LOGIC;
              Out_Read_Register_Data_1    : out STD_LOGIC_VECTOR(C_Bit-1 downto 0);
              Out_Read_Register_Data_2    : out STD_LOGIC_VECTOR(C_Bit-1 downto 0));
end component;

signal In_Read_Register_Address_1  : STD_LOGIC_VECTOR(C_Address-1 downto 0) := (others => '0');
signal In_Read_Register_Address_2  : STD_LOGIC_VECTOR(C_Address-1 downto 0) := (others => '0');
signal In_Write_Register           : STD_LOGIC_VECTOR(C_Address-1 downto 0) := (others => '0');
signal In_Write_Register_Data      : STD_LOGIC_VECTOR(C_Bit-1 downto 0) := (others => '0');
signal In_Write_Register_Enable    : STD_LOGIC := '0';
signal Out_Read_Register_Data_1    : STD_LOGIC_VECTOR(C_Bit-1 downto 0);
signal Out_Read_Register_Data_2    : STD_LOGIC_VECTOR(C_Bit-1 downto 0);
 
begin

MIPS_Register_File_DUT : MIPS_Register_File
    Generic Map (C_Bit => C_Bit, C_Address => C_Address)
    Port Map (In_Read_Register_Address_1 => In_Read_Register_Address_1, In_Read_Register_Address_2 => In_Read_Register_Address_2, In_Write_Register => In_Write_Register,
              In_Write_Register_Data => In_Write_Register_Data, In_Write_Register_Enable => In_Write_Register_Enable, Out_Read_Register_Data_1 => Out_Read_Register_Data_1, Out_Read_Register_Data_2 => Out_Read_Register_Data_2);
              
P_STIMULI : process begin
--    for i in 0 to 30 loop
--        In_Read_Register_Address_1 <= STD_LOGIC_VECTOR(To_Unsigned(i,5));
--        In_Read_Register_Address_2 <= STD_LOGIC_VECTOR(To_Unsigned(i+1,5));
--        wait for 25 ns;
--    end loop;
    
    In_Write_Register <= "01000";
    In_Write_Register_Data <= x"A5A5A5A5";
    wait for 25 ns;
    
    In_Write_Register_Enable <= '1';
    wait for 25 ns;
    
    In_Write_Register_Enable <= '0';
    wait for 25 ns;
    
    assert false
    report "SIM DONE"
    severity failure;
end process; 
            
end Behavioral;
