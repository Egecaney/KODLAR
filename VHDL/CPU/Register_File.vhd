library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.all;

entity Register_File is
    Port ( Clk                           : in STD_LOGIC;
           Reset                         : in STD_LOGIC;
           In_Register_Write_Enable      : in STD_LOGIC;
           In_Register_Write_Dest        : in STD_LOGIC_VECTOR(2 downto 0);
           In_Register_Write_Data        : in STD_LOGIC_VECTOR(7 downto 0);
           In_Register_Read_Address_1    : in STD_LOGIC_VECTOR(2 downto 0);
           In_Register_Read_Address_2    : in STD_LOGIC_VECTOR(2 downto 0);
           Out_Register_Read_Data_1      : out STD_LOGIC_VECTOR(7 downto 0);
           Out_Register_Read_Data_2      : out STD_LOGIC_VECTOR(7 downto 0)
    );
end Register_File;

architecture Behavioral of Register_File is

type T_Register_File is array (0 to 7) of STD_LOGIC_VECTOR(7 downto 0);
signal Register_Array : T_Register_File;

begin
 
P_MAIN: process(Clk, Reset) begin
    if (Reset = '1') then
        Register_Array(0) <= x"01";
        Register_Array(1) <= x"02";
        Register_Array(2) <= x"03";
        Register_Array(3) <= x"04";
        Register_Array(4) <= x"05";
        Register_Array(5) <= x"06";
        Register_Array(6) <= x"07";
        Register_Array(7) <= x"08";
    elsif (rising_edge(Clk)) then
        if (In_Register_Write_Enable = '1') then
            Register_Array(to_integer(unsigned(In_Register_Write_Dest))) <= In_Register_Write_Data;
        end if;
    end if;
end process;

Out_Register_Read_Data_1 <= x"00" when In_Register_Read_Address_1 = "000" else Register_Array(to_integer(unsigned(In_Register_Read_Address_1)));
Out_Register_Read_Data_2 <= x"00" when In_Register_Read_Address_2 = "000" else Register_Array(to_integer(unsigned(In_Register_Read_Address_2)));

end Behavioral;
