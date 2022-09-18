library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity MIPS_Sign_Extender is
    Port ( In_SE  : in STD_LOGIC_VECTOR(15 downto 0);
           Out_SE : out STD_LOGIC_VECTOR(31 downto 0));
end MIPS_Sign_Extender;

architecture Behavioral of MIPS_Sign_Extender is

begin

Out_SE <= (x"0000" & In_SE) when In_SE(15) = '0' else (x"FFFF" & In_SE);

end Behavioral;
