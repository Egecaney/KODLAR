library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity SPI_MasterSlave is
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
end SPI_MasterSlave;

architecture Behavioral of SPI_MasterSlave is

signal  SPI_Start       : STD_LOGIC := '0';
signal  SPI_ReadWrite   : STD_LOGIC := '0';
signal  SPI_RegisterIn  : STD_LOGIC_VECTOR(C_Num_SPI_RegBits - 1 downto 0)  := (others => '0');
signal  SPI_DataIn      : STD_LOGIC_VECTOR(C_Num_SPI_DataBits - 1 downto 0) := (others => '0');
signal  SPI_DataOut     : STD_LOGIC_VECTOR(C_Num_SPI_DataBits - 1 downto 0) := (others => '0');
signal  SPI_MOSI        : STD_LOGIC := '0';
signal  SPI_CLK         : STD_LOGIC := '0';
signal  SPI_CS          : STD_LOGIC := '1';
signal  SPI_DoneTick    : STD_LOGIC := '0';
signal  SPI_MISO        : STD_LOGIC;

signal  Read_Write       : STD_LOGIC := '0';
signal  Register_Address : STD_LOGIC_VECTOR(C_Num_SPI_RegBits - 2 downto 0)  := (others => '0');
signal  Data_Value       : STD_LOGIC_VECTOR(C_Num_SPI_DataBits - 1 downto 0) := (others => '0');

signal  Counter          : integer range 0 to 7 := 0;
type    Type_State is (S_IDLE, S_READ, S_WRITE, S_WAIT);
signal  States : Type_State := S_IDLE; 

begin

Master_SPI : entity work.SPICore
    Generic Map(C_ClockFrequency => C_ClockFrequency, C_SPI_Clock => C_SPI_Clock, C_Num_SPI_DataBits => C_Num_SPI_DataBits, C_Num_SPI_RegBits => C_Num_SPI_RegBits)
       Port Map(Clk => MasterClk, Start => SPI_Start, Read_Write => SPI_ReadWrite, RegisterIn => SPI_RegisterIn, DataIn => SPI_DataIn, DataOut => SPI_DataOut,
                MISO => SPI_MISO, MOSI => SPI_MOSI, SCLK => SPI_CLK, CS => SPI_CS, Done_Tick => SPI_DoneTick);
                
Slave_SPI  : entity work.VerilogSlave
       Port Map(SlaveClock => SPI_CLK, SlaveChipSelect => SPI_CS, SlaveDataIn => SPI_MOSI, SlaveDataOut => SPI_MISO, ResetButton => SlaveReset, 
                FirstChannel_Spare  => SlaveFirstChannel_Spare,  FirstChannel_RxTx  => SlaveFirstChannel_RxTx,  FirstChannel_Phase  => SlaveFirstChannel_Phase,  FirstChannel_Gain  => SlaveFirstChannel_Gain,     
                SecondChannel_Spare => SlaveSecondChannel_Spare, SecondChannel_RxTx => SlaveSecondChannel_RxTx, SecondChannel_Phase => SlaveSecondChannel_Phase, SecondChannel_Gain => SlaveSecondChannel_Gain,
                ThirdChannel_Spare  => SlaveThirdChannel_Spare,  ThirdChannel_RxTx  => SlaveThirdChannel_RxTx,  ThirdChannel_Phase  => SlaveThirdChannel_Phase,  ThirdChannel_Gain  => SlaveThirdChannel_Gain, 
                ForthChannel_Spare  => SlaveForthChannel_Spare,  ForthChannel_RxTx  => SlaveForthChannel_RxTx,  ForthChannel_Phase  => SlaveForthChannel_Phase,  ForthChannel_Gain  => SlaveForthChannel_Gain,
                FifthChannel => SlaveFifthChannel);
                
P_MAIN : process (MasterClk) begin
    if(rising_edge(MasterClk)) then
        MasterDataReady <= '0';
        case States is
        
            when S_IDLE =>
                if(MasterDataComing = '1' and Counter = 0) then
                    Read_Write <= MasterDataIn(23);
                    Register_Address <= MasterDataIn(22 downto 16);
                    Data_Value <= MasterDataIn(15 downto 0);
                    Counter <= Counter + 1;
                end if;
                if(Counter = 1)then
                    if(Read_Write = '1') then
                        States <= S_WRITE;
                    elsif(Read_Write = '0') then
                        States <= S_READ;
                    end if;
                    Counter <= 0;
                end if;
                    
            when S_WRITE =>
                if(Counter = 0) then
                    SPI_Start <= '1';
                    SPI_ReadWrite <= '1';
                    SPI_RegisterIn <= Read_Write & Register_Address;
                    SPI_DataIn <= Data_Value;
                    if(SPI_DoneTick = '1') then
                        Counter <= Counter + 1;
                    end if;
                elsif(Counter = 1) then
                    SPI_Start <= '0';
                    if(SPI_DoneTick = '1') then
                        Counter <= 0;
                        States <= S_WAIT;
                        MasterDataReady <= '1';
                        SPI_ReadWrite <= '0';
                        SPI_RegisterIn <= (others => '0');
                        SPI_DataIn <= (others => '0');     
                        MasterDataOut <= Read_Write & Register_Address & Data_Value;
                    end if;
                end if;
            
            when S_READ =>
                if(Counter = 0) then
                    SPI_Start <= '1';
                    SPI_ReadWrite <= '0';
                    SPI_RegisterIn <= Read_Write & Register_Address;
                    if(SPI_DoneTick = '1') then
                        Counter <= Counter + 1;
                    end if;
                elsif(Counter = 1) then
                    SPI_Start <= '0';
                    if(SPI_DoneTick = '1') then
                        Counter <= 0;
                        States <= S_WAIT;
                        MasterDataReady <= '1';
                        SPI_ReadWrite <= '0';
                        SPI_RegisterIn <= (others => '0');
                        Data_Value <= SPI_DataOut;   
                        MasterDataOut <= Read_Write & Register_Address & SPI_DataOut;
                    end if;
                end if;
            
            when S_WAIT =>
                States <= S_IDLE;
        
            when others => null;
            
        end case;
    end if;
end process;

-- DebugOut(15 downto 0) <= SPI_DataOut;
-- DebugOut(16) <= SPI_DoneTick;
-- DebugOut(17) <= SPI_Start;
-- DebugOut(18) <= SPI_CS;
-- DebugOut(19) <= SPI_CLK;
-- DebugOut(20) <= SPI_MOSI;
-- DebugOut(21) <= SPI_MISO;

end Behavioral;