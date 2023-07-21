library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity UartHandler is
    Generic(C_Clock_Frequency   : integer := 100_000_000;
            C_Baud_Rate         : integer := 115_200;
            C_Num_Uart_DataBits : integer := 8;
            C_Stop_Bits         : integer := 1);
       Port(Clk                 : in  STD_LOGIC;
            TX                  : out STD_LOGIC;
            TX_Start            : in  STD_LOGIC;
            TX_Data             : in  STD_LOGIC_VECTOR (C_Num_Uart_DataBits-1 downto 0);
            TX_DoneTick         : out STD_LOGIC;
            RX                  : in  STD_LOGIC;
            RX_Data             : out STD_LOGIC_VECTOR (C_Num_Uart_DataBits-1 downto 0);
            RX_DoneTick         : out STD_LOGIC);
end UartHandler;

architecture Behavioral of UartHandler is

constant C_Bit_Timer_Lim : integer := C_Clock_Frequency/C_Baud_Rate;
constant C_Stop_Bit_Lim  : integer := (C_Clock_Frequency/C_Baud_Rate)*C_Stop_Bits;

signal S_RX_Bit_Timer    : integer range 0 to C_Bit_Timer_Lim        := 0;
signal S_RX_Bit_Counter  : integer range 0 to C_Num_Uart_DataBits-1  := 0;
signal S_RX_Shift_Reg    : STD_LOGIC_VECTOR (C_Num_Uart_DataBits-1 downto 0) := (others => '0');

signal S_TX_Bit_Timer    : integer range 0 to C_Bit_Timer_Lim        := 0;
signal S_TX_Bit_Counter  : integer range 0 to C_Num_Uart_DataBits-1  := 0;
signal S_TX_Shift_Reg    : STD_LOGIC_VECTOR (C_Num_Uart_DataBits-1 downto 0) := (others => '0');

type UartRXStates is (RXIdle, RXStart, RXData, RXStop);
signal RXState : UartRXStates := RXIdle;

type UartTXStates is (TXIdle, TXStart, TXData, TXStop);
signal TXState : UartTXStates := TXIdle;

begin

P_TX : process (Clk) begin
    if (rising_edge(Clk)) then
        case TXState is
            
            when TXIdle =>
                TX <= '1';
                TX_DoneTick <= '0';
                S_TX_Bit_Counter <= 0;
                if(TX_Start = '1') then 
                    TXState <= TXStart;
                    TX <= '0';
                    S_TX_Shift_Reg <= TX_Data;
                end if;
                
            when TXStart =>
                if(S_TX_Bit_Timer = C_Bit_Timer_Lim - 1) then
                    TXState <= TXData;
                    TX <= S_TX_Shift_Reg(0);
                    S_TX_Shift_Reg(7) <= S_TX_Shift_Reg(0);
                    S_TX_Shift_Reg(6 downto 0) <= S_TX_Shift_Reg(7 downto 1);
                    S_TX_Bit_Timer <= 0;
                else
                    S_TX_Bit_Timer <= S_TX_Bit_Timer + 1;
                end if;
            
            when TXData =>
                if(S_TX_Bit_Counter = 7) then
                    if(S_TX_Bit_Timer = C_Bit_Timer_Lim - 1) then
                        S_TX_Bit_Counter <= 0;
                        TXState <= TXStop;
                        TX <= '1';
                        S_TX_Bit_Timer <= 0;
                    else
                        S_TX_Bit_Timer <= S_TX_Bit_Timer + 1;
                    end if;
                else
                    if(S_TX_Bit_Timer = C_Bit_Timer_Lim - 1) then
                        S_TX_Shift_Reg(7) <= S_TX_Shift_Reg(0);
                        S_TX_Shift_Reg(6 downto 0) <= S_TX_Shift_Reg(7 downto 1);
                        TX <= S_TX_Shift_Reg(0);
                        S_TX_Bit_Counter <= S_TX_Bit_Counter + 1;
                        S_TX_Bit_Timer <= 0;
                    else
                        S_TX_Bit_Timer <= S_TX_Bit_Timer + 1;
                    end if;               
                end if;
                
            when TXStop =>
                if(S_TX_Bit_Timer = C_Bit_Timer_Lim - 1) then
                    TXState <= TXIdle;
                    TX_DoneTick <= '1';
                    S_TX_Bit_Timer <= 0;
                else
                    S_TX_Bit_Timer <= S_TX_Bit_Timer + 1;
                end if;
                
        end case;
    end if;
end process;

P_RX : process(Clk) begin
    if(rising_edge(Clk)) then
        case RXState is
            
            when RXIdle =>
                RX_DoneTick <= '0';
                S_RX_Bit_Timer <= 0;
                if (RX = '0') then
                    RXState <= RXStart;
                end if;
            
            when RXStart =>
                if (S_RX_Bit_Timer <= C_Bit_Timer_Lim/2 - 1) then
                    RXState <= RXData;
                    S_RX_Bit_Timer <= 0;
                else
                    S_RX_Bit_Timer <= S_RX_Bit_Timer + 1; 
                end if;
            
            when RXData =>
                if (S_RX_Bit_Timer = C_Bit_Timer_Lim - 1) then
                    if (S_RX_Bit_Counter = 7) then
                        RXState <= RXStop;
                        S_RX_Bit_Counter <= 0;
                    else
                        S_RX_Bit_Counter <= S_RX_Bit_Counter + 1;
                    end if;
                    S_RX_Shift_Reg <= RX & (S_RX_Shift_Reg(7 downto 1));
                    S_RX_Bit_Timer <= 0;
                else
                    S_RX_Bit_Timer <= S_RX_Bit_Timer + 1; 
                end if;
            
            when RXStop =>
                if (S_RX_Bit_Timer = C_Bit_Timer_Lim - 1) then
                    RXState <= RXIdle;
                    S_RX_Bit_Timer <= 0;
                    RX_DoneTick <= '1';
                else
                    S_RX_Bit_Timer <= S_RX_Bit_Timer + 1; 
                end if;

        end case;
    end if;
end process;

RX_Data <= S_RX_Shift_Reg;

end Behavioral;