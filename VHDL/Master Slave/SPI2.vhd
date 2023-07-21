library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity SPI2 is
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
end SPI2;

architecture Behavioral of SPI2 is

constant Mode0          : STD_LOGIC_VECTOR(1 downto 0) := "00";
signal   SPI_Mode       : STD_LOGIC_VECTOR(1 downto 0) := Mode0;

signal   Count_DVSR     : integer := 0;
signal   Num_DataBits   : integer range 0 to C_Num_SPI_DataBits-1 := 0;
signal   Num_RegBits    : integer range 0 to C_Num_SPI_RegBits-1  := 0;

signal   SDataOut       : STD_LOGIC_VECTOR(C_Num_SPI_DataBits-1 downto 0) := (others => '0');
signal   SDataIn        : STD_LOGIC_VECTOR(C_Num_SPI_DataBits-1 downto 0) := (others => '0');
signal   SRegisterOut   : STD_LOGIC_VECTOR(C_Num_SPI_RegBits-1 downto 0)  := (others => '0');

type SPI_Controller is (S_IDLE, P01, P02, P1, P2);
signal SPI_Controller_State : SPI_Controller := S_IDLE;

begin

P_MAIN : process(Clk) begin
    if (Clk'event and Clk = '1') then
        case SPI_Controller_State is
            
            when S_IDLE =>
                SPI_Done_Tick <= '0';
                MOSI          <= '0';
                if (Start = '1') then
                    Count_DVSR   <= 0;
                    Num_RegBits  <= 0;
                    SRegisterOut <= RegisterIn(C_Num_SPI_RegBits-2 downto 0) & '0';
                    MOSI <= RegisterIn(C_Num_SPI_RegBits-1);
                    SPI_Controller_State <= P01;
                else
                    SDataOut <= (others => '0');
                    SDataIn  <= (others => '0');
                end if;
            
            when P01 =>
                if(Count_DVSR = C_DVSR) then
                    Count_DVSR <= 0;
                    SDataIn    <= SDataIn(C_Num_SPI_DataBits-2 downto 0) & MISO;
                    SPI_Controller_State <= P1;
                else
                    Count_DVSR <= Count_DVSR + 1;
                end if;
            
            when P02 =>
                if(Count_DVSR = C_DVSR) then
                    Count_DVSR <= 0;
                    SDataIn    <= SDataIn(C_Num_SPI_DataBits-2 downto 0) & MISO;
                    SPI_Controller_State <= P2;
                    SPI_Done_Tick <= '0';
                else
                    Count_DVSR <= Count_DVSR + 1;
                end if;
            
            when P1 =>
                if(Count_DVSR = C_DVSR) then
                    if(Num_RegBits = C_Num_SPI_RegBits -1) then
                        SPI_Done_Tick <= '1';
                        DataOut <= SDataIn;
                        SPI_Controller_State <= P02;
                        Count_DVSR <= 0;
                        Num_DataBits <= 0;
                        SDataOut    <= DataIn(C_Num_SPI_DataBits-2 downto 0) & '0';
                        MOSI <= DataIn(C_Num_SPI_DataBits-1);
                    else
                        Count_DVSR <= 0;
                        SRegisterOut <= SRegisterOut(C_Num_SPI_RegBits-2 downto 0) & '0';
                        Num_RegBits <= Num_RegBits + 1;
                        SPI_Controller_State <= P01;
                        MOSI <= SRegisterOut(C_Num_SPI_RegBits-1);
                    end if;
                else
                    Count_DVSR <= Count_DVSR + 1;
                    SPI_Controller_State <= P1;
                end if;
            
            when P2 =>
                if(Count_DVSR = C_DVSR) then
                    if(Num_DataBits = C_Num_SPI_DataBits -1) then
                        SPI_Done_Tick <= '1';
                        DataOut <= SDataIn;
                        SPI_Controller_State <= S_IDLE;
                    else
                        Count_DVSR <= 0;
                        SDataOut <= SDataOut(C_Num_SPI_DataBits-2 downto 0) & '0';
                        Num_DataBits <= Num_DataBits + 1;
                        SPI_Controller_State <= P02;
                        MOSI <= SDataOut(C_Num_SPI_DataBits-1);
                    end if;
                else
                    Count_DVSR <= Count_DVSR + 1;
                    SPI_Controller_State <= P2;
                end if;
        end case;
    end if;
end process;

P_SCLK: process(SPI_Controller_State, SPI_Mode) begin
    if(SPI_Mode = Mode0) then
        if(SPI_Controller_State = P1 or SPI_Controller_State = P2) then
            SCLK <= '1';
        else
            SCLK <= '0';
        end if;
    end if;
end process;

end Behavioral;
