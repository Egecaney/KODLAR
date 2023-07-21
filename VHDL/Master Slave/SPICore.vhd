library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


entity SPICore is
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
end SPICore;

architecture Behavioral of SPICore is

component SPI2 is
    Generic(C_Num_SPI_DataBits  : integer := 16;
            C_Num_SPI_RegBits   : integer := 8;
            C_DVSR              : integer := 9);
       Port(Clk                 : in STD_LOGIC;
            RegisterIn          : in STD_LOGIC_VECTOR(C_Num_SPI_RegBits-1 downto 0);
            DataIn              : in STD_LOGIC_VECTOR(C_Num_SPI_DataBits-1 downto 0);
            DataOut             : out STD_LOGIC_VECTOR(C_Num_SPI_DataBits-1 downto 0);
            Start               : in STD_LOGIC;
            SPI_Done_Tick       : out STD_LOGIC;
            SCLK                : out STD_LOGIC;
            MISO                : in STD_LOGIC;
            MOSI                : out STD_LOGIC);
end component;

type ChipStates is (S_IDLE, S_Start, S_WriteRegisterCommand, S_ReadRegisterCommand, S_WriteData, S_ReadData);
signal ChipState : ChipStates := S_IDLE;

constant SPI_Cont_DVSR_Int  : integer := (C_ClockFrequency/(2*C_SPI_Clock)) -1;         -- DVSR = (Fsys/(2xFspi))-1

signal SPI_Cont_RegIn        : STD_LOGIC_VECTOR(C_Num_SPI_RegBits-1 downto 0)   := (others => '0');
signal SPI_Cont_DataIn       : STD_LOGIC_VECTOR(C_Num_SPI_DataBits-1 downto 0)  := (others => '0');
signal SPI_Cont_Start        : STD_LOGIC := '0';
signal SPI_Cont_SPI_DoneTick : STD_LOGIC := '0';
signal SPI_Cont_DataOut      : STD_LOGIC_VECTOR(C_Num_SPI_DataBits-1 downto 0)  := (others => '0');

signal Chip_DataIn           : STD_LOGIC_VECTOR(C_Num_SPI_DataBits-1 downto 0)  := (others => '0');
signal Chip_RegIn            : STD_LOGIC_VECTOR(C_Num_SPI_RegBits-1 downto 0)   := (others => '0');

begin

SPI2_Instantiation : SPI2
    Generic Map(C_Num_SPI_DataBits => C_Num_SPI_DataBits, C_Num_SPI_RegBits => C_Num_SPI_RegBits, C_DVSR => SPI_Cont_DVSR_Int)
       Port Map(Clk => Clk, RegisterIn => SPI_Cont_RegIn, DataIn => SPI_Cont_DataIn, DataOut => SPI_Cont_DataOut, Start => SPI_Cont_Start, 
                SPI_Done_Tick => SPI_Cont_SPI_DoneTick, SCLK => SCLK, MISO => MISO, MOSI => MOSI);
                
P_MAIN : process(Clk) begin
    if(Clk'event and Clk = '1') then
        case ChipState is
        
            when S_IDLE =>
                if(Start = '1') then
                    ChipState <= S_Start;
                else
                    ChipState <= S_IDLE;
                    Done_Tick <= '0';
                    CS        <= '1';
                end if;
            
            when S_Start =>
                SPI_Cont_RegIn  <= RegisterIn;
                CS              <= '0';
                if(Read_Write = '0') then
                    ChipState <= S_ReadRegisterCommand;
                    SPI_Cont_Start <= '1';
                elsif(Read_Write = '1') then
                    ChipState <= S_WriteRegisterCommand;
                    SPI_Cont_Start <= '1';
                end if;
            
            when S_WriteRegisterCommand =>
                if(SPI_Cont_SPI_DoneTick = '1') then
                    ChipState <= S_WriteData;
                    SPI_Cont_Start <= '1';
                    Done_Tick <= '1';
                else
                    ChipState <= S_WriteRegisterCommand;
                    SPI_Cont_Start <= '0';
                    SPI_Cont_DataIn <= DataIn;
                end if;
            
            when S_WriteData =>
                if(SPI_Cont_SPI_DoneTick = '1') then
                    ChipState <= S_IDLE;
                    Done_Tick <= '1';
                    CS <= '1';
                else
                    ChipState <= S_WriteData;
                    SPI_Cont_Start <= '0';
                    Done_Tick <= '0';
                end if;
            
            when S_ReadRegisterCommand =>
                if(SPI_Cont_SPI_DoneTick = '1') then
                    ChipState <= S_ReadData;
                    SPI_Cont_Start <= '1';
                    Done_Tick <= '1';
                else
                    ChipState <= S_ReadRegisterCommand;
                    SPI_Cont_Start <= '0';
                    SPI_Cont_DataIn <= (others => '0');
                end if;
            
            when S_ReadData =>
                if(SPI_Cont_SPI_DoneTick = '1') then
                    ChipState <= S_IDLE;
                    Done_Tick <= '1';
                    CS <= '1';
                    DataOut <= SPI_Cont_DataOut;
                else
                    ChipState <= S_ReadData;
                    SPI_Cont_Start <= '0';
                    Done_Tick <= '0';
                end if;
            
            when others => null;
            
        end case;        
    end if;
end process;                
    
end Behavioral;