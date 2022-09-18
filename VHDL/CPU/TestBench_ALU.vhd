library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
-- use IEEE.NUMERIC_STD.all;

entity TestBench_ALU is
end TestBench_ALU;

architecture Behavioral of TestBench_ALU is

component ALU is
    Port ( In_A             : in STD_LOGIC_VECTOR(7 downto 0);
           In_B             : in STD_LOGIC_VECTOR(7 downto 0);
           In_Selection     : in STD_LOGIC_VECTOR(3 downto 0);
           Out_C            : out STD_LOGIC_VECTOR(8 downto 0));
end component;

signal In_A             : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
signal In_B             : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
signal In_Selection     : STD_LOGIC_VECTOR(3 downto 0) := (others => '0');
signal Out_C            : STD_LOGIC_VECTOR(8 downto 0);

begin

ALU_DUT : ALU
    Port Map(In_A => In_A, In_B => In_B, In_Selection => In_Selection, Out_C => Out_C);

P_STIMULI: process begin

    In_A <= x"8A";
    In_B <= x"02";
    In_Selection <= x"0";
    wait for 100 ns;
    
    for i in 0 to 14 loop 
        In_Selection <= In_Selection + x"1";
        wait for 100 ns;
    end loop;
    
    In_A <= x"F6";
    In_B <= x"0A";
    In_Selection <= x"0";
    wait for 100 ns;
    
    In_B <= x"F6";
    In_A <= x"0A";
    In_Selection <= x"1";
    wait for 100 ns;
    
    assert false
    report "SIM DONE"
    severity failure;
end process;
end Behavioral;
