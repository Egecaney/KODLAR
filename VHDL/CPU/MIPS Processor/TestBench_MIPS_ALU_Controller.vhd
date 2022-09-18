library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity TestBench_MIPS_ALU_Controller is
end TestBench_MIPS_ALU_Controller;

architecture Behavioral of TestBench_MIPS_ALU_Controller is

component MIPS_ALU_Controller is
    Port ( In_Function      : in STD_LOGIC_VECTOR(5 downto 0);
           In_ALU_Operation : in STD_LOGIC_VECTOR(1 downto 0);
           Out_Operation    : out STD_LOGIC_VECTOR(3 downto 0));
end component;

signal In_Function      : STD_LOGIC_VECTOR(5 downto 0) := (others => '0');
signal In_ALU_Operation : STD_LOGIC_VECTOR(1 downto 0) := (others => '0');
signal Out_Operation    : STD_LOGIC_VECTOR(3 downto 0);
           

begin

MIPS_ALU_Controller_DUT : MIPS_ALU_Controller
    Port Map(In_Function => In_Function, In_ALU_Operation => In_ALU_Operation, Out_Operation => Out_Operation);

P_STIMULI : process begin
    
    In_Function <= "100100";    -- AND
    In_ALU_Operation <= "10";
    wait for 25 ns;
    
    In_Function <= "100101";    -- OR
    In_ALU_Operation <= "10";
    wait for 25 ns;
    
    In_Function <= "100000";    -- ADD
    In_ALU_Operation <= "10";
    wait for 25 ns;
    
    In_Function <= "100010";    -- SUB
    In_ALU_Operation <= "10";
    wait for 25 ns;
    
    In_Function <= "101010";    -- SLT (Set on Less Than)
    In_ALU_Operation <= "10";
    wait for 25 ns;
       
    assert false
    report "SIM DONE"
    severity failure;
end process; 

end Behavioral;
