library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.all;

entity Data_Memory is
    Port ( Clk                      : in STD_LOGIC;
           In_Memory_Access_Address : in STD_LOGIC_VECTOR(15 downto 0);
           In_Memory_Write_Data     : in STD_LOGIC_VECTOR(15 downto 0);
           In_Memory_Write_Enable   : in STD_LOGIC;
           In_Memory_Read           : in STD_LOGIC;
           Out_Memory_Read_Data     : out STD_LOGIC_VECTOR(15 downto 0));
end Data_Memory;

architecture Behavioral of Data_Memory is

signal RAM_Address : STD_LOGIC_VECTOR(7 downto 0);
type T_Data_Memory is array (0 to 255) of STD_LOGIC_VECTOR (15 downto 0);
signal RAM: T_Data_Memory := ((others => (others =>'0')));

begin

RAM_Address <= In_Memory_Access_Address(8 downto 1);

P_MAIN: process (Clk) begin
    if(rising_edge(Clk)) then
        if (In_Memory_Write_Enable='1') then
            RAM(to_integer(unsigned(RAM_Address))) <= In_Memory_Write_Data;
        end if;
    end if;
end process;

Out_Memory_Read_Data <= RAM(to_integer(unsigned(RAM_Address))) when (In_Memory_Read='1') else x"0000";

end Behavioral;

