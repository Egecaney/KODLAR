library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


entity TestBench_SPICore is
    Generic(C_ClockFrequency    : integer := 100_000_000;
            C_SPI_Clock         : integer := 50_000_000;
            C_Num_SPI_DataBits  : integer := 16;
            C_Num_SPI_RegBits   : integer := 8);
end TestBench_SPICore;

architecture Behavioral of TestBench_SPICore is

component SPICore is
    Generic(C_ClockFrequency    : integer := 100_000_000;
            C_SPI_Clock         : integer := 50_000_000;
            C_Num_SPI_DataBits  : integer := 16;
            C_Num_SPI_RegBits   : integer := 8);
       Port(Clk                 : in STD_LOGIC;
            Start               : in STD_LOGIC;
            Read_Write          : in STD_LOGIC;
            RegisterIn          : in STD_LOGIC_VECTOR(C_Num_SPI_RegBits-1 downto 0);
            DataIn              : in STD_LOGIC_VECTOR(C_Num_SPI_DataBits-1 downto 0);
            DataOut             : out STD_LOGIC_VECTOR(C_Num_SPI_DataBits-1 downto 0);
            MISO                : in STD_LOGIC;
            MOSI                : out STD_LOGIC;
            SCLK                : out STD_LOGIC;
            CS                  : out STD_LOGIC;
            Done_Tick           : out STD_LOGIC);
end component;

-- Inputs 
signal Clk          : STD_LOGIC := '0';
signal Start        : STD_LOGIC;
signal Read_Write   : STD_LOGIC := '0';
signal RegisterIn   : STD_LOGIC_VECTOR(C_Num_SPI_RegBits-1 downto 0)  := (others => '0');
signal DataIn       : STD_LOGIC_VECTOR(C_Num_SPI_DataBits-1 downto 0) := (others => '0');

-- Outputs
signal DataOut      : STD_LOGIC_VECTOR(C_Num_SPI_DataBits-1 downto 0) := (others => '0');
signal Done_Tick    : STD_LOGIC := '0';

-- SPI Pins
signal MISO         : STD_LOGIC := '0';
signal MOSI         : STD_LOGIC;
signal SCLK         : STD_LOGIC;
signal CS           : STD_LOGIC := '1';

-- SPI Singals to Read Data
signal Signal_SPI   : STD_LOGIC_VECTOR(C_Num_SPI_DataBits-1 downto 0) := (others => '0');

-- Clock Period Definations
constant C_Clock_Period : time := 10ns;

begin

SPI_Core_DUT : SPICore
    Generic Map(C_ClockFrequency => C_ClockFrequency, C_SPI_Clock => C_SPI_Clock, C_Num_SPI_DataBits => C_Num_SPI_DataBits, C_Num_SPI_RegBits => C_Num_SPI_RegBits)
       Port Map(Clk => Clk, Start => Start, Read_Write => Read_Write, RegisterIn => RegisterIn, DataIn => DataIn, DataOut => DataOut, 
                MISO => MISO, MOSI => MOSI, SCLK => SCLK, CS => CS, Done_Tick => Done_Tick);
                

P_Clock_Generation : process begin
    Clk <= '0';
    wait for C_Clock_Period/2;
    Clk <= '1';
    wait for C_Clock_Period/2;
end process;

P_STIMULI: process begin

    Start <= '0';
    wait for C_Clock_Period*50;
    
    Start       <= '1';
    Read_Write  <= '1';
    RegisterIn  <= x"84";
    DataIn      <= x"F0F0";
    -- wait for C_Clock_Period;
    wait until rising_edge(Done_Tick);
    Start       <= '0';
    wait until rising_edge(Done_Tick);
    
    wait for C_Clock_Period*100;
    
    Start       <= '1';
    Read_Write  <= '1';
    RegisterIn  <= x"81";
    DataIn      <= x"AA55";
    -- wait for C_Clock_Period;
    wait until rising_edge(Done_Tick);
    Start       <= '0';
    wait until rising_edge(Done_Tick);
    
    wait for C_Clock_Period*100;
    
    Start       <= '1';
    Read_Write  <= '0';
    Signal_SPI  <= x"AA55";
    -- wait for C_Clock_Period;
    wait until rising_edge(Done_Tick);
    Start       <= '0';
    for i in 0 to (C_Num_SPI_DataBits-1) loop
        MISO <= Signal_SPI((C_Num_SPI_DataBits-1) - i);
        wait until falling_edge(SCLK);
    end loop;
    wait until rising_edge(Done_Tick);
    
    wait for C_Clock_Period*100;
    
    Start       <= '1';
    Read_Write  <= '1';
    RegisterIn  <= x"84";
    DataIn      <= x"FF55";
    -- wait for C_Clock_Period;
    wait until rising_edge(Done_Tick);
    Start       <= '0';
    wait until rising_edge(Done_Tick);
    
    wait for C_Clock_Period*100;
    
    Start       <= '1';
    Read_Write  <= '0';
    Signal_SPI  <= x"71E1";
    -- wait for C_Clock_Period;
    wait until rising_edge(Done_Tick);
    Start       <= '0';
    for i in 0 to (C_Num_SPI_DataBits-1) loop
        MISO <= Signal_SPI((C_Num_SPI_DataBits-1) - i);
        wait until falling_edge(SCLK);
    end loop;
    wait until rising_edge(Done_Tick);
    
    wait for C_Clock_Period*100;
    
    assert false
    report "SIM DONE"
    severity failure;

end process;              
    
end Behavioral;
