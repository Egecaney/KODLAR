library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity TestBench_SPI_Master_4Bit is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCLK_Frequency  : integer := 1_000_000;
              Data_Length       : integer := 4);
end TestBench_SPI_Master_4Bit;

architecture Behavioral of TestBench_SPI_Master_4Bit is

component SPI_Master_4Bit is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCLK_Frequency  : integer := 1_000_000;
              Data_Length       : integer := 4);
       Port ( Clk 			    : in  STD_LOGIC;
              In_Enable	        : in  STD_LOGIC;
              In_MOSI_Data      : in  STD_LOGIC_VECTOR (3 downto 0);
              Out_MISO_Data	    : out STD_LOGIC_VECTOR (3 downto 0);
              Out_Data_Ready    : out STD_LOGIC;
              Out_CS		    : out STD_LOGIC;
              Out_SCLK 	        : out STD_LOGIC;
              Out_MOSI		    : out STD_LOGIC;
              In_MISO 	        : in  STD_LOGIC);
end component;

-- INPUTS
signal Clk          : STD_LOGIC;
signal In_Enable    : STD_LOGIC;
signal In_MOSI_Data : STD_LOGIC_VECTOR (Data_Length-1 downto 0);
signal In_MISO 	    : STD_LOGIC;

-- OUTPUTS
signal Out_MISO_Data  : STD_LOGIC_VECTOR (Data_Length-1 downto 0);
signal Out_Data_Ready : STD_LOGIC;
signal Out_CS		  : STD_LOGIC;
signal Out_SCLK 	  : STD_LOGIC;
signal Out_MOSI		  : STD_LOGIC;

-- Clock Period Definitions
constant C_Clock_Period : time := 10 ns;
constant C_SCLK_Period 	: time := 1000 ns;
 
signal Signal_SPI 	    : STD_LOGIC_VECTOR(Data_Length-1 downto 0) := (others => '0');
signal S_SPI_Write 	    : STD_LOGIC := '0';
signal S_SPI_Write_Done : STD_LOGIC := '0';  

begin

SPI_Master_DUT : SPI_Master_4Bit 
    Generic Map(C_Clock_Frequency => C_Clock_Frequency, C_SCLK_Frequency => C_SCLK_Frequency)
    Port MAP (Clk => Clk, In_Enable => In_Enable, In_MOSI_Data => In_MOSI_Data, Out_MISO_Data => Out_MISO_Data, Out_Data_Ready => Out_Data_Ready, 
              Out_CS => Out_CS, Out_SCLK => Out_SCLK, Out_MOSI => Out_MOSI, In_MISO => In_MISO);
              
P_Clock_Generation : process begin
    Clk <= '0';
    wait for C_Clock_Period/2;
    Clk <= '1';
    wait for C_Clock_Period/2;
end process;

-- Stimulus process
P_STIMULI: process begin		
  
    wait for 100 ns;                   -- Hold reset state for 100 ns.	
    wait for C_Clock_Period*10;
 
	In_Enable <= '1';
	
	In_MOSI_Data <= x"A";             -- Write 0xA,
	wait until falling_edge(Out_CS);
	Signal_SPI   <= x"B";             -- Read 0xB
	S_SPI_Write  <= '1'; wait until rising_edge(S_SPI_Write_Done); S_SPI_Write <= '0';
 
	wait until rising_edge(Out_Data_Ready);
	
	In_MOSI_Data <= x"B";	          -- Write 0xB,
	wait until falling_edge(Out_SCLK);
	Signal_SPI   <= x"C";             -- Read 0xC
	S_SPI_Write  <= '1'; wait until rising_edge(S_SPI_Write_Done); S_SPI_Write <= '0';
	
	In_Enable <= '0';
	  
	wait for C_SCLK_Period*4;
 
	assert false
	report "SIM DONE"
	severity failure;
	
end process;

P_SPI_Write : process begin
	wait until rising_edge(S_SPI_Write);
 
	In_MISO <= Signal_SPI(3);
	wait until falling_edge(Out_SCLK);
	In_MISO <= Signal_SPI(2);
	wait until falling_edge(Out_SCLK);
	In_MISO <= Signal_SPI(1);
	wait until falling_edge(Out_SCLK);
	In_MISO <= Signal_SPI(0);

	S_SPI_Write_Done <= '1'; wait for 1 ps; S_SPI_Write_Done <= '0';
end process;

end Behavioral;
