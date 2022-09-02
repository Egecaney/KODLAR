library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity Top_ADXL362 is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCLK_Frequency  : integer := 1_000_000;
              C_Read_Frequency  : integer := 2;
              C_Baud_Rate       : integer := 115_200;
              C_Stop_Bits       : integer := 2);
       Port ( Clk 			    : in  STD_LOGIC;
              In_MISO 	        : in  STD_LOGIC;
              Out_CS		    : out STD_LOGIC;
              Out_SCLK 	        : out STD_LOGIC;
              Out_MOSI		    : out STD_LOGIC;
              Out_TX            : out STD_LOGIC);
end Top_ADXL362;

architecture Behavioral of Top_ADXL362 is

component ADXL362 is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCLK_Frequency  : integer := 1_000_000;
              C_Read_Frequency  : integer := 100);
       Port ( Clk 			    : in  STD_LOGIC;
              In_MISO 	        : in  STD_LOGIC;
              Out_CS		    : out STD_LOGIC;
              Out_SCLK 	        : out STD_LOGIC;
              Out_MOSI		    : out STD_LOGIC;
              Out_AX            : out STD_LOGIC_VECTOR (15 downto 0);
              Out_AY	        : out STD_LOGIC_VECTOR (15 downto 0);
              Out_AZ	        : out STD_LOGIC_VECTOR (15 downto 0);
              Out_Ready         : out STD_LOGIC);
end component;

component Uart_TX is
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
end component;

signal S_AX			 : STD_LOGIC_VECTOR (15 downto 0)	:= (others => '0');
signal S_AY			 : STD_LOGIC_VECTOR (15 downto 0)	:= (others => '0');
signal S_AZ			 : STD_LOGIC_VECTOR (15 downto 0)	:= (others => '0');
signal S_Data		 : STD_LOGIC_VECTOR (7 downto 0)		:= (others => '0');
signal S_TX_Buffer	 : STD_LOGIC_VECTOR (6*8-1 downto 0)	:= (others => '0');

signal S_Ready		  : STD_LOGIC	:= '0';
signal S_TX_Start	  : STD_LOGIC	:= '0';
signal S_TX_Done_Tick : STD_LOGIC	:= '0';
signal S_Sent_Trig	  : STD_LOGIC	:= '0';

signal S_Contour	  : integer range 0 to 7 := 0;

begin

ADXL362_Instantiation : ADXL362
    Generic Map(C_Clock_Frequency => C_Clock_Frequency, C_SCLK_Frequency => C_SCLK_Frequency, C_Read_Frequency => C_Read_Frequency)
    Port map(Clk => Clk, In_MISO => In_MISO, Out_MOSI => Out_MOSI, Out_SCLK => Out_SCLK, Out_CS => Out_CS, Out_AX => S_AX, Out_AY => S_AY, Out_AZ => S_AZ, Out_Ready => S_Ready);

Uart_TX_Instantiation : Uart_TX
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Baud_Rate => C_Baud_Rate, C_Stop_Bits => C_Stop_Bits)
    Port Map (Clk => Clk, In_Data => S_Data, In_TX_Start => S_TX_Start, Out_TX => Out_TX, Out_TX_Done_Tick => S_TX_Done_Tick); 
    
P_MAIN : process (Clk) begin
    if (rising_edge(Clk)) then
        if (S_Ready = '1') then
            S_TX_Buffer	<= S_AX & S_AY & S_AZ;
            S_Contour <= 6;
            S_Sent_Trig	<= '1';
        end if;
        S_Data <= S_TX_Buffer(6*8-1 downto 5*8);
        if (S_Sent_Trig = '1') then
            if (S_Contour = 6) then
                S_TX_Start <= '1';
                S_TX_Buffer(6*8-1 downto 8)	<= S_TX_Buffer(5*8-1 downto 0);
                S_Contour <= S_Contour - 1;	
            elsif (S_Contour = 0) then
                S_TX_Start <= '0';
                if (S_TX_Done_Tick = '1') then
                    S_Sent_Trig	<= '0';
                end if;
            else
                if (S_TX_Done_Tick = '1') then
                    S_Contour <= S_Contour - 1;
                    S_TX_Buffer(6*8-1 downto 8)	<= S_TX_Buffer(5*8-1 downto 0);
                end if;
            end if;
        end if;
    end if;
end process ;

end Behavioral;
