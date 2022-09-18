library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.NUMERIC_STD.all;

entity ALU is
    Port ( In_A             : in STD_LOGIC_VECTOR(7 downto 0);
           In_B             : in STD_LOGIC_VECTOR(7 downto 0);
           In_Selection     : in STD_LOGIC_VECTOR(3 downto 0);
           Out_C            : out STD_LOGIC_VECTOR(8 downto 0));
end ALU;

architecture Behavioral of ALU is

signal ALU_Result    : STD_LOGIC_VECTOR(8 downto 0) := (others => '0');
    
begin

P_ALU : process (In_A, In_B, In_Selection)
    begin
        case In_Selection is
            when "0000" => 
                Out_C <= ('0' & In_A) + ('0' & In_B);
            when "0001" =>
                if ((In_A > In_B) or (In_A = In_B)) then 
                    Out_C <= ('0' & In_A) - ('0' & In_B);
                    Out_C(8) <= '0';
                else 
                    Out_C <= ('0' & In_B) - ('0' & In_A);
                    Out_C(8) <= '1';
                end if;
            when "0010" => 
                Out_C <= STD_LOGIC_VECTOR(To_Unsigned((To_Integer(Unsigned(('0' & In_A)))*To_Integer(Unsigned(('0' & In_B)))),9));   
            when "0011" => 
                Out_C <= STD_LOGIC_VECTOR(To_Unsigned((To_Integer(Unsigned(('0' & In_A)))/To_Integer(Unsigned(('0' & In_B)))),9));
            when "0100" => 
                Out_C <= '0' & STD_LOGIC_VECTOR(Unsigned((In_A)) SLL 1);
            when "0101" => 
                Out_C <= '0' & STD_LOGIC_VECTOR(Unsigned((In_A)) SRL 1);
            when "0110" => 
                Out_C <= '0' & STD_LOGIC_VECTOR(Unsigned((In_A)) ROL 1);           
            when "0111" => 
                Out_C <= '0' & STD_LOGIC_VECTOR(Unsigned((In_A)) ROR 1);           
            when "1000" => 
                Out_C <= (('0' & In_A) and ('0' & In_B));   
            when "1001" => 
                Out_C <= (('0' & In_A) or ('0' & In_B));
            when "1010" => 
                Out_C <= (('0' & In_A) xor ('0' & In_B));   
            when "1011" => 
                Out_C <= (('0' & In_A) nor ('0' & In_B)); 
            when "1100" => 
                Out_C <= (('0' & In_A) nand ('0' & In_B));
            when "1101" => 
                Out_C <= (('0' & In_A) xnor ('0' & In_B));    
            when "1110" =>
                if (In_A > In_B) then 
                    Out_C <= "000000001";
                else 
                    Out_C <= "000000000";
                end if;
            when "1111" =>
                if (In_A = In_B) then 
                    Out_C <= "000000001";
                else 
                    Out_C <= "000000000";
                end if; 
            when others => null;    
        end case;    
end process;

end Behavioral;