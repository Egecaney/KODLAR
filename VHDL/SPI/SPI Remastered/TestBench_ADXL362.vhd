library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity TestBench_ADXL362 is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCLK_Frequency  : integer := 1_000_000;
              C_Read_Frequency  : integer := 1_000);
end TestBench_ADXL362;

architecture Behavioral of TestBench_ADXL362 is

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
	

signal Clk : std_logic := '0';
signal In_MISO : std_logic := '0';

signal Out_AX 	: STD_LOGIC_VECTOR (15 downto 0);
signal Out_AY 	: STD_LOGIC_VECTOR (15 downto 0);
signal Out_AZ 	: STD_LOGIC_VECTOR (15 downto 0);
signal Out_Ready	: STD_LOGIC;
signal Out_CS 	: std_logic;
signal Out_SCLK 	: std_logic;
signal Out_MOSI 	: std_logic;

-- Clock Period Definitions
constant C_Clock_Period : time := 10 ns;
constant C_SCLK_Period 	: time := 1 us;
 
signal Signal_SPI 	    : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
signal S_SPI_Write 	    : STD_LOGIC := '0';
signal S_SPI_Write_Done : STD_LOGIC := '0';  

begin

ADXL362_DUT : ADXL362
    Generic Map(C_Clock_Frequency => C_Clock_Frequency, C_SCLK_Frequency => C_SCLK_Frequency, C_Read_Frequency => C_Read_Frequency)
    Port map(Clk => Clk, In_MISO => In_MISO, Out_MOSI => Out_MOSI, Out_SCLK => Out_SCLK, Out_CS => Out_CS, Out_AX => Out_AX, Out_AY => Out_AY, Out_AZ => Out_AZ, Out_Ready => Out_Ready);

P_Clock_Generation : process begin
    Clk <= '0';
    wait for C_Clock_Period/2;
    Clk <= '1';
    wait for C_Clock_Period/2;
end process;

P_SPI_Write : process begin
	wait until rising_edge(S_SPI_Write);
        for i in 0 to 7 loop
            In_MISO  <= Signal_SPI(7-i);  wait until falling_edge(Out_SCLK);
        end loop;
	S_SPI_Write_Done    <= '1'; wait for 1 ps; S_SPI_Write_Done    <= '0';
end process;

P_STIMULI: process begin		
    wait for C_Clock_Period*10;
	wait for 1 ms;
    
    wait until falling_edge(Out_CS);      
	wait for 16 us; 
	wait until falling_edge(Out_SCLK);
	wait for C_Clock_Period;
	wait for 1 ps;
	
	Signal_SPI <= x"A1";
	S_SPI_Write <= '1';  wait for 1 ps;  S_SPI_Write <= '0';
	wait until rising_edge(S_SPI_Write_Done); wait for 1 ps; 
	
	Signal_SPI <= x"A2";
	S_SPI_Write <= '1';  wait for 1 ps;  S_SPI_Write <= '0';
	wait until rising_edge(S_SPI_Write_Done); wait for 1 ps;
	
	Signal_SPI <= x"A3";
	S_SPI_Write <= '1';  wait for 1 ps;  S_SPI_Write <= '0';
	wait until rising_edge(S_SPI_Write_Done); wait for 1 ps;
	
	Signal_SPI <= x"A4";
	S_SPI_Write <= '1';  wait for 1 ps;  S_SPI_Write <= '0';
	wait until rising_edge(S_SPI_Write_Done); wait for 1 ps;
	
	Signal_SPI <= x"A5";
	S_SPI_Write <= '1';  wait for 1 ps;  S_SPI_Write <= '0';
	wait until rising_edge(S_SPI_Write_Done); wait for 1 ps;
	
	Signal_SPI <= x"A6";
	S_SPI_Write <= '1';  wait for 1 ps;  S_SPI_Write <= '0';
	wait until rising_edge(S_SPI_Write_Done); wait for 1 ps;
	
	wait until rising_edge(Out_CS);
	wait for 20 us;
    wait for C_Clock_Period*40 ;
    
    assert false
    report "SIM DONE" 
    severity failure;
end process;


end Behavioral;
