library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity MIPS_MUX is
    Generic ( C_Bit     : integer := 32);
       Port ( In_Data_1    : in STD_LOGIC_VECTOR(C_Bit-1 downto 0);
              In_Data_2    : in STD_LOGIC_VECTOR(C_Bit-1 downto 0);
              In_Selection : in STD_LOGIC;
              Out_Data     : out STD_LOGIC_VECTOR(C_Bit-1 downto 0));
end MIPS_MUX;

architecture Behavioral of MIPS_MUX is

begin

Out_Data <= In_Data_1 when In_Selection = '0' else In_Data_2;

end Behavioral;
