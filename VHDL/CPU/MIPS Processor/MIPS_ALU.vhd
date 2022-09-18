library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.NUMERIC_STD.all;

entity MIPS_ALU is
    Port ( In_A          : in STD_LOGIC_VECTOR(31 downto 0);
           In_B          : in STD_LOGIC_VECTOR(31 downto 0);
           In_Selection  : in STD_LOGIC_VECTOR(3 downto 0);
           Out_C         : out STD_LOGIC_VECTOR(31 downto 0);
           Out_Zero      : out STD_LOGIC);
end MIPS_ALU;

architecture Behavioral of MIPS_ALU is

signal ALU_Result : STD_LOGIC_VECTOR(31 downto 0) := (others => '0');
    
begin

P_MIPS_ALU : process (In_A, In_B, In_Selection) begin
    case In_Selection is
        when "0000" => ALU_Result <= In_A and In_B; 
        when "0001" => ALU_Result <= In_A or In_B;
        when "0010" => ALU_Result <= STD_LOGIC_VECTOR(Unsigned(In_A) + Unsigned(In_B));  
        when "0110" => ALU_Result <= STD_LOGIC_VECTOR(Unsigned(In_A) - Unsigned(In_B));
        when "0111" => 
            if (In_A < In_B) then  
                ALU_Result <= x"00000001";
            else 
                ALU_Result <= x"00000000";
            end if;    
        when "1100" => ALU_Result <= In_A nor In_B;
        when others => null; ALU_Result <= x"00000000";   
    end case;    
end process;

Out_C <= ALU_Result;
Out_Zero <= '1' when ALU_Result = x"00000000" else '0';

end Behavioral;