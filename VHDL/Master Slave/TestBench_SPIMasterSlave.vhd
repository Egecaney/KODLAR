library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


entity TestBench_SPIMasterSlave is
    Generic(C_ClockFrequency        : integer := 100_000_000;
            C_SPI_Clock             : integer := 50_000_000;
            C_Num_SPI_DataBits      : integer := 16;
            C_Num_SPI_RegBits       : integer := 8);
end TestBench_SPIMasterSlave;

architecture Behavioral of TestBench_SPIMasterSlave is

component SPI_MasterSlave is
    Generic(C_ClockFrequency        : integer := 100_000_000;
            C_SPI_Clock             : integer := 50_000_000;
            C_Num_SPI_DataBits      : integer := 16;
            C_Num_SPI_RegBits       : integer := 8);
      Port (MasterClk               : in  STD_LOGIC;
            SlaveReset              : in  STD_LOGIC;
            MasterDataIn            : in  STD_LOGIC_VECTOR(C_Num_SPI_DataBits + C_Num_SPI_RegBits - 1 downto 0);
            MasterDataOut           : out STD_LOGIC_VECTOR(C_Num_SPI_DataBits + C_Num_SPI_RegBits - 1 downto 0);
            MasterDataComing        : in  STD_LOGIC;
            MasterDataReady         : out STD_LOGIC;
            SlaveFirstChannel_Spare : out STD_LOGIC_VECTOR(3 downto 0);
            SlaveFirstChannel_RxTx  : out STD_LOGIC;
            SlaveFirstChannel_Phase : out STD_LOGIC_VECTOR(5 downto 0);
            SlaveFirstChannel_Gain  : out STD_LOGIC_VECTOR(4 downto 0);      
            SlaveSecondChannel_Spare: out STD_LOGIC_VECTOR(3 downto 0);
            SlaveSecondChannel_RxTx : out STD_LOGIC;
            SlaveSecondChannel_Phase: out STD_LOGIC_VECTOR(5 downto 0);
            SlaveSecondChannel_Gain : out STD_LOGIC_VECTOR(4 downto 0); 
            SlaveThirdChannel_Spare : out STD_LOGIC_VECTOR(3 downto 0);
            SlaveThirdChannel_RxTx  : out STD_LOGIC;
            SlaveThirdChannel_Phase : out STD_LOGIC_VECTOR(5 downto 0);
            SlaveThirdChannel_Gain  : out STD_LOGIC_VECTOR(4 downto 0);   
            SlaveForthChannel_Spare : out STD_LOGIC_VECTOR(3 downto 0);
            SlaveForthChannel_RxTx  : out STD_LOGIC;
            SlaveForthChannel_Phase : out STD_LOGIC_VECTOR(5 downto 0);
            SlaveForthChannel_Gain  : out STD_LOGIC_VECTOR(4 downto 0);
            SlaveFifthChannel       : out STD_LOGIC_VECTOR(15 downto 0));
            -- DebugOut             : out STD_LOGIC_VECTOR(21 downto 0)   
end component;

-- Inputs
signal MasterClk                : STD_LOGIC := '0';
signal SlaveReset               : STD_LOGIC := '0';
signal MasterDataIn             : STD_LOGIC_VECTOR(C_Num_SPI_DataBits + C_Num_SPI_RegBits - 1 downto 0) := (others => '0');
signal MasterDataComing         : STD_LOGIC := '0';

-- Outputs        
signal MasterDataOut            : STD_LOGIC_VECTOR(C_Num_SPI_DataBits + C_Num_SPI_RegBits - 1 downto 0);
signal MasterDataReady          : STD_LOGIC;

-- Slave Outputs
signal SlaveFirstChannel_Spare  : STD_LOGIC_VECTOR(3 downto 0);
signal SlaveFirstChannel_RxTx   : STD_LOGIC;
signal SlaveFirstChannel_Phase  : STD_LOGIC_VECTOR(5 downto 0);
signal SlaveFirstChannel_Gain   : STD_LOGIC_VECTOR(4 downto 0);  
signal SlaveSecondChannel_Spare : STD_LOGIC_VECTOR(3 downto 0);
signal SlaveSecondChannel_RxTx  : STD_LOGIC;
signal SlaveSecondChannel_Phase : STD_LOGIC_VECTOR(5 downto 0);
signal SlaveSecondChannel_Gain  : STD_LOGIC_VECTOR(4 downto 0); 
signal SlaveThirdChannel_Spare  : STD_LOGIC_VECTOR(3 downto 0);
signal SlaveThirdChannel_RxTx   : STD_LOGIC;
signal SlaveThirdChannel_Phase  : STD_LOGIC_VECTOR(5 downto 0);
signal SlaveThirdChannel_Gain   : STD_LOGIC_VECTOR(4 downto 0); 
signal SlaveForthChannel_Spare  : STD_LOGIC_VECTOR(3 downto 0);
signal SlaveForthChannel_RxTx   : STD_LOGIC;
signal SlaveForthChannel_Phase  : STD_LOGIC_VECTOR(5 downto 0);
signal SlaveForthChannel_Gain   : STD_LOGIC_VECTOR(4 downto 0);
signal SlaveFifthChannel        : STD_LOGIC_VECTOR(15 downto 0);

constant C_ClockPeriod          : time := 10ns;
constant C_SCLK_Period          : time := 20ns;
          
begin

SPI_MasterSlave_DUT : SPI_MasterSlave
    Generic Map(C_ClockFrequency => C_ClockFrequency, C_SPI_Clock => C_SPI_Clock, C_Num_SPI_DataBits => C_Num_SPI_DataBits, C_Num_SPI_RegBits => C_Num_SPI_RegBits)
       Port Map(MasterClk => MasterClk, SlaveReset => SlaveReset, MasterDataIn => MasterDataIn, MasterDataOut => MasterDataOut, MasterDataComing => MasterDataComing, MasterDataReady => MasterDataReady,
                SlaveFirstChannel_Spare => SlaveFirstChannel_Spare, SlaveFirstChannel_RxTx => SlaveFirstChannel_RxTx, SlaveFirstChannel_Phase => SlaveFirstChannel_Phase, SlaveFirstChannel_Gain => SlaveFirstChannel_Gain,
                SlaveSecondChannel_Spare => SlaveSecondChannel_Spare, SlaveSecondChannel_RxTx => SlaveSecondChannel_RxTx, SlaveSecondChannel_Phase => SlaveSecondChannel_Phase, SlaveSecondChannel_Gain => SlaveSecondChannel_Gain,
                SlaveThirdChannel_Spare => SlaveThirdChannel_Spare, SlaveThirdChannel_RxTx => SlaveThirdChannel_RxTx, SlaveThirdChannel_Phase => SlaveThirdChannel_Phase, SlaveThirdChannel_Gain => SlaveThirdChannel_Gain,
                SlaveForthChannel_Spare => SlaveForthChannel_Spare, SlaveForthChannel_RxTx => SlaveForthChannel_RxTx, SlaveForthChannel_Phase => SlaveForthChannel_Phase, SlaveForthChannel_Gain => SlaveForthChannel_Gain,
                SlaveFifthChannel => SlaveFifthChannel);

P_Clock_Generation : process begin
    MasterClk <= '0';
    wait for C_ClockPeriod/2;
    MasterClk <= '1';
    wait for C_ClockPeriod/2;
end process;

P_STIMULI : process begin
    
    SlaveReset <= '0';
    wait for C_ClockPeriod*10;
    
    SlaveReset <= '1';
    wait for C_ClockPeriod*10;
    
    MasterDataComing <= '1';
    MasterDataIn <= '1' & "0000000" & "1111000011110000";
    wait for C_ClockPeriod;
    MasterDataComing <= '0';
    wait until rising_edge(MasterDataReady);
    
    wait for 100us;
    
    MasterDataComing <= '1';
    MasterDataIn <= '1' & "0000001" & "0000111100001111";
    wait for C_ClockPeriod;
    MasterDataComing <= '0';
    wait until rising_edge(MasterDataReady);
    
    wait for 100us;
    
    MasterDataComing <= '1';
    MasterDataIn <= '1' & "0000010" & "1100110011001100";
    wait for C_ClockPeriod;
    MasterDataComing <= '0';
    wait until rising_edge(MasterDataReady);
    
    wait for 100us;
    
    MasterDataComing <= '1';
    MasterDataIn <= '1' & "0000011" & "1010101010101010";
    wait for C_ClockPeriod;
    MasterDataComing <= '0';
    wait until rising_edge(MasterDataReady);
    
    wait for 100us;
    
    MasterDataComing <= '1';
    MasterDataIn <= '1' & "0000100" & "0101010101010101";
    wait for C_ClockPeriod;
    MasterDataComing <= '0';
    wait until rising_edge(MasterDataReady);
    
    wait for 100us;
    
    MasterDataComing <= '1';
    MasterDataIn <= '0' & "0000000" & "0000000000000000";
    wait for C_ClockPeriod;
    MasterDataComing <= '0';
    wait until rising_edge(MasterDataReady);
    
    wait for 100us;
    
    MasterDataComing <= '1';
    MasterDataIn <= '0' & "0000001" & "0000000000000000";
    wait for C_ClockPeriod;
    MasterDataComing <= '0';
    wait until rising_edge(MasterDataReady);
    
    wait for 100us;
    
    MasterDataComing <= '1';
    MasterDataIn <= '0' & "0000010" & "0000000000000000";
    wait for C_ClockPeriod;
    MasterDataComing <= '0';
    wait until rising_edge(MasterDataReady);
    
    wait for 100us;
    
    MasterDataComing <= '1';
    MasterDataIn <= '0' & "0000011" & "0000000000000000";
    wait for C_ClockPeriod;
    MasterDataComing <= '0';
    wait until rising_edge(MasterDataReady);
    
    wait for 100us;
    
    MasterDataComing <= '1';
    MasterDataIn <= '0' & "0000100" & "0000000000000000";
    wait for C_ClockPeriod;
    MasterDataComing <= '0';
    wait until rising_edge(MasterDataReady);
    
    wait for 100us;
    
    assert false
    report "SIM DONE"
    severity failure;
   
end process;





end Behavioral;
