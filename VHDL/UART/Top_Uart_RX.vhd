library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity Top_Uart_RX is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Baud_Rate       : integer := 115_200);
    Port(
        Clk      : in STD_LOGIC;
        In_RX    : in STD_LOGIC;
        Out_Leds : out STD_LOGIC_VECTOR (15 downto 0));
end Top_Uart_RX;

architecture Behavioral of Top_Uart_RX is

component Uart_RX is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Baud_Rate       : integer := 115_200);
    Port(
        Clk               : in STD_LOGIC;
        In_RX             : in STD_LOGIC;
        Out_Data          : out STD_LOGIC_VECTOR (7 downto 0);
        Out_RX_Done_Tick  : out STD_LOGIC );
end component;

signal S_Leds         : STD_LOGIC_VECTOR (15 downto 0) := (others => '0');
signal S_Data_Out     : STD_LOGIC_VECTOR (7 downto 0)  := (others => '0');
signal S_RX_Done_Tick : STD_LOGIC := '0';
begin

Uart_RX_Instantiation : Uart_RX
    Generic Map(C_Clock_Frequency => C_Clock_Frequency,C_Baud_Rate => C_Baud_Rate)
    Port Map(Clk => Clk, In_RX => In_RX, Out_Data => S_Data_Out, Out_RX_Done_Tick => S_RX_Done_Tick);

process (Clk) begin
    if (rising_edge(Clk)) then
        if(S_RX_Done_Tick = '1') then                      -- 2 baytlýk veri geldiðinde, veriye göre LED'leri yakar.
            S_Leds (15 downto 8) <= S_Leds (7 downto 0);
            S_Leds (7 downto 0)  <= S_Data_Out;
        end if;
    end if;
end process; 

Out_Leds <= S_Leds;
-- x"6655" gönderildiðinde, Out_Leds(15 downto 8) 0110 0110, Out_Leds(15 downto 8) 0101 0101 olur.

end Behavioral;
