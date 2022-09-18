library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.NUMERIC_STD.all;

entity MIPS_ALU_Controller is
    Port ( In_Function      : in STD_LOGIC_VECTOR(5 downto 0);
           In_ALU_Operation : in STD_LOGIC_VECTOR(1 downto 0);
           Out_Operation    : out STD_LOGIC_VECTOR(3 downto 0));
end MIPS_ALU_Controller;

architecture Behavioral of MIPS_ALU_Controller is

begin

-- ALU CONTROLLER on the Web
Out_Operation(0) <= (In_Function(3) or In_Function(0)) and In_ALU_Operation(1);
Out_Operation(1) <= (not In_Function(2)) or (not In_ALU_Operation(1));
Out_Operation(2) <= (In_ALU_Operation(1) and In_Function(1)) or In_ALU_Operation(0);
Out_Operation(3) <= '0';

end Behavioral;
