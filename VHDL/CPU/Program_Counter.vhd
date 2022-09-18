library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.NUMERIC_STD.all;

entity Program_Counter is
    Port ( Clk       : in STD_LOGIC;
           Reset     : in STD_LOGIC;
           In_Enable : in STD_LOGIC;
           In_Load   : in STD_LOGIC;
           Input     : in STD_LOGIC_VECTOR(3 downto 0);
           Output    : out STD_LOGIC_VECTOR(3 downto 0));
end Program_Counter;

architecture Behavioral of Program_Counter is

signal Counter : STD_LOGIC_VECTOR(3 downto 0) := (others => '0');

begin

P_MAIN : process (Clk, Reset) begin
    if (Reset = '1') then
        Counter <= "0000";
    elsif (rising_edge(Clk)) then
        if (In_Load = '1') then
            Counter <= Input;
        elsif (In_Enable = '1') then
            Counter <= Counter + 1;
        end if;
    end if; 
end process;

Output <= Counter;

end Behavioral;
