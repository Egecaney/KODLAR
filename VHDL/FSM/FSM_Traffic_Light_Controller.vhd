library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_unsigned.ALL;

entity FSM_Traffic_Light_Controller is
    Port ( Clk : in STD_LOGIC;
           Clear : in STD_LOGIC;
           Out_Lights : out STD_LOGIC_VECTOR(5 downto 0));
end FSM_Traffic_Light_Controller;

architecture Behavioral of FSM_Traffic_Light_Controller is

type Type_State is (S0,S1,S2,S3,S4,S5);
signal State : Type_State;

signal   Counter    : STD_LOGIC_VECTOR(3 downto 0);
constant C_15second : STD_LOGIC_VECTOR(3 downto 0) := "1111";
constant C_3second  : STD_LOGIC_VECTOR(3 downto 0) := "0011";

begin

P_MAIN : process (Clk, Clear) begin
    if (Clear = '0') then
        State <= S0; 
        Counter <= x"0";
    elsif (Clk'event and Clk = '1') then
        case State is
            when S0 =>
                if (Counter < C_15second) then
                    State <= S0; Counter <= Counter + 1;
                else
                    State <= S1; Counter <= x"0";
                end if;
            when S1 =>
                if (Counter < C_3second) then
                    State <= S1; Counter <= Counter + 1;
                else
                    State <= S2; Counter <= x"0";
                end if;
            when S2 =>
                if (Counter < C_3second) then
                    State <= S2; Counter <= Counter + 1;
                else
                    State <= S3; Counter <= x"0";
                end if;
            when S3 =>
                if (Counter < C_15second) then
                    State <= S3; Counter <= Counter + 1;
                else
                    State <= S4; Counter <= x"0";
                end if;
            when S4 =>
                if (Counter < C_3second) then
                    State <= S4; Counter <= Counter + 1;
                else
                    State <= S5; Counter <= x"0";
                end if;
            when S5 =>
                if (Counter < C_3second) then
                    State <= S5; Counter <= Counter + 1;
                else
                    State <= S0; Counter <= x"0";
                end if;
            when others => State <= S0; 
        end case;
    end if;
end process;

P_OUTPUT : process (State) begin
    case State is
            when S0 => Out_Lights <= "100001";
            when S1 => Out_Lights <= "100010";
            when S2 => Out_Lights <= "100100";
            when S3 => Out_Lights <= "001100";
            when S4 => Out_Lights <= "010100";
            when S5 => Out_Lights <= "100100";
            when others => Out_Lights <= "100001"; 
        end case; 
end process;

end Behavioral;
