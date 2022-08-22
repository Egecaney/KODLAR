library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Uart_TX is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Baud_Rate       : integer := 115_200;
        C_Stop_Bits       : integer := 2);
    Port(
        Clk               : in STD_LOGIC;
        In_Data           : in STD_LOGIC_VECTOR (7 downto 0);
        In_TX_Start       : in STD_LOGIC;
        Out_TX            : out STD_LOGIC;
        Out_TX_Done_Tick  : out STD_LOGIC );
end Uart_TX;

architecture Behavioral of Uart_TX is

constant C_Bit_Timer_Lim : integer := C_Clock_Frequency/C_Baud_Rate;
constant C_Stop_Bit_Lim  : integer := (C_Clock_Frequency/C_Baud_Rate)*C_Stop_Bits;

type T_State is (S_Idle, S_Start, S_Data, S_Stop);
signal State : T_State := S_Idle;

signal S_Bit_Timer   : integer range 0 to C_Stop_Bit_Lim := 0;
signal S_Bit_Counter : integer range 0 to 7 := 0;
signal S_Shift_Reg   : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');

begin

P_MAIN : process (Clk) begin
    if (rising_edge(Clk)) then
        case State is
            
            when S_Idle =>
                Out_TX <= '1';
                Out_TX_Done_Tick <= '0';
                S_Bit_Counter <= 0;
                if(In_TX_Start = '1') then 
                    State <= S_Start;
                    Out_TX <= '0';
                    S_Shift_Reg <= In_Data;
                end if;
                
            when S_Start =>
                if(S_Bit_Timer = C_Bit_Timer_Lim - 1) then
                    State <= S_Data;
                    Out_TX <= S_Shift_Reg(0);
                    S_Shift_Reg(7) <= S_Shift_Reg(0);
                    S_Shift_Reg(6 downto 0) <= S_Shift_Reg(7 downto 1);
                    S_Bit_Timer <= 0;
                else
                    S_Bit_Timer <= S_Bit_Timer + 1;
                end if;
            
            when S_Data =>
                if(S_Bit_Counter = 7) then
                    if(S_Bit_Timer = C_Bit_Timer_Lim - 1) then
                        S_Bit_Counter <= 0;
                        State <= S_Stop;
                        Out_TX <= '1';
                        S_Bit_Timer <= 0;
                    else
                        S_Bit_Timer <= S_Bit_Timer + 1;
                    end if;
                else
                    if(S_Bit_Timer = C_Bit_Timer_Lim - 1) then
                        S_Shift_Reg(7) <= S_Shift_Reg(0);
                        S_Shift_Reg(6 downto 0) <= S_Shift_Reg(7 downto 1);
                        Out_TX <= S_Shift_Reg(0);
                        S_Bit_Counter <= S_Bit_Counter + 1;
                        S_Bit_Timer <= 0;
                    else
                        S_Bit_Timer <= S_Bit_Timer + 1;
                    end if;               
                end if;
                
            when S_Stop =>
                if(S_Bit_Timer = C_Bit_Timer_Lim - 1) then
                    State <= S_Idle;
                    Out_TX_Done_Tick <= '1';
                    S_Bit_Timer <= 0;
                else
                    S_Bit_Timer <= S_Bit_Timer + 1;
                end if;
                
        end case;
    end if;
end process;

end Behavioral;
