library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Uart_RX is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Baud_Rate       : integer := 115_200);
    Port(
        Clk               : in STD_LOGIC;
        In_RX             : in STD_LOGIC;
        Out_Data          : out STD_LOGIC_VECTOR (7 downto 0);
        Out_RX_Done_Tick  : out STD_LOGIC );
end Uart_RX;

architecture Behavioral of Uart_RX is

constant C_Bit_Timer_Lim : integer := C_Clock_Frequency/C_Baud_Rate;

type T_State is (S_Idle, S_Start, S_Data, S_Stop);
signal State : T_State := S_Idle;

signal S_Bit_Timer   : integer range 0 to C_Bit_Timer_Lim := 0;
signal S_Bit_Counter : integer range 0 to 7 := 0;
signal S_Shift_Reg   : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');

begin
P_MAIN : process(Clk) begin
    if(rising_edge(Clk)) then
        case State is
            
            when S_Idle =>
                Out_RX_Done_Tick <= '0';
                S_Bit_Timer <= 0;
                if (In_RX = '0') then
                    State <= S_Start;
                end if;
            
            when S_Start =>
                if (S_Bit_Timer <= C_Bit_Timer_Lim/2 - 1) then
                    State <= S_Data;
                    S_Bit_Timer <= 0;
                else
                    S_Bit_Timer <= S_Bit_Timer + 1; 
                end if;
            
            when S_Data =>
                if (S_Bit_Timer = C_Bit_Timer_Lim - 1) then
                    if (S_Bit_Counter = 7) then
                        State <= S_Stop;
                        S_Bit_Counter <= 0;
                    else
                        S_Bit_Counter <= S_Bit_Counter + 1;
                    end if;
                    S_Shift_Reg <= In_RX & (S_Shift_Reg(7 downto 1));
                    S_Bit_Timer <= 0;
                else
                    S_Bit_Timer <= S_Bit_Timer + 1; 
                end if;
            
            when S_Stop =>
                if (S_Bit_Timer = C_Bit_Timer_Lim - 1) then
                    State <= S_Idle;
                    S_Bit_Timer <= 0;
                    Out_RX_Done_Tick <= '1';
                else
                    S_Bit_Timer <= S_Bit_Timer + 1; 
                end if;

        end case;
    end if;
end process;

Out_Data <= S_Shift_Reg;

end Behavioral;
