library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Debounce is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Debounce_Time  : integer := 1000;
        C_Initial_Value  : STD_LOGIC := '0');
    Port(
        Clk : in STD_LOGIC ;
        In_Signal : in STD_LOGIC;
        Out_Signal : out STD_LOGIC);
end Debounce;

architecture Behavioral of Debounce is

constant C_Timer_Lim : integer := C_Clock_Frequency/C_Debounce_Time;

signal S_Timer        : integer range 0 to C_Timer_Lim;
signal S_Timer_Enable : STD_LOGIC := '0';
signal S_Timer_Tick   : STD_LOGIC := '0';

type T_State is (S_Initial, S_Zero, S_Zero2One, S_One, S_One2Zero);
signal State : T_State := S_Initial;

begin

P_MAIN: process (Clk) begin
    if (rising_edge(Clk)) then
        case State is
            
            when S_Initial =>
                if (C_Initial_Value = '0') then
                    State <= S_Zero;
                else
                    State <= S_One;
                end if;
                            
            when S_Zero =>
                Out_Signal <= '0';
                if (In_Signal = '1') then
                    State <= S_Zero2One;
                end if;
                
            when S_Zero2One =>
                Out_Signal <= '0';
                S_Timer_Enable <= '1';
                if (S_Timer_Tick = '1') then
                    State <= S_One;
                    S_Timer_Enable <= '0';
                end if;
                if (In_Signal = '0') then
                    State <= S_Zero;
                    S_Timer_Enable <= '0';
                end if;
            
            when S_One =>
                Out_Signal <= '1';
                if (In_Signal = '0') then
                    State <= S_One2Zero;
                end if;
            
            when S_One2Zero =>
                Out_Signal <= '1';
                S_Timer_Enable <= '1';
                if (S_Timer_Tick = '1') then
                    State <= S_Zero;
                    S_Timer_Enable <= '0';
                end if;
                if (In_Signal = '1') then
                    State <= S_One;
                    S_Timer_Enable <= '0';
                end if;           
        
        end case;
    end if;
end process;

P_TIMER : process(Clk) begin
    if (rising_edge(Clk)) then
        if(S_Timer_Enable = '1') then
            if (S_Timer = C_Timer_Lim - 1) then
                S_Timer <= 0;
                S_Timer_Tick <= '1';
            else
                S_Timer_Tick <= '0';
                S_Timer <= S_Timer +1;
            end if;
        else
            S_Timer_Tick <= '0';
            S_Timer <= 0;
        end if;
    end if;
end process;

end Behavioral;
