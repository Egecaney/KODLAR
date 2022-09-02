library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity ADXL362 is
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
end ADXL362;

architecture Behavioral of ADXL362 is

component SPI_Master_Remastered is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCLK_Frequency  : integer := 1_000_000);
       Port ( Clk 			    : in  STD_LOGIC;
              In_Enable	        : in  STD_LOGIC;
              In_MOSI_Data      : in  STD_LOGIC_VECTOR (7 downto 0);
              Out_MISO_Data	    : out STD_LOGIC_VECTOR (7 downto 0);
              Out_Data_Ready    : out STD_LOGIC;
              Out_CS		    : out STD_LOGIC;
              Out_SCLK 	        : out STD_LOGIC;
              Out_MOSI		    : out STD_LOGIC;
              In_MISO 	        : in  STD_LOGIC);
end component;

constant C_Timer_Read_Lim    : integer := C_Clock_Frequency/C_Read_Frequency;
signal   S_Timer_Read        : integer range 0 to C_Timer_Read_Lim := 0;
signal   S_Timer_Read_Tick   : STD_LOGIC := '0';

signal   S_MOSI_Data		 : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
signal   S_MISO_Data		 : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
signal   S_Enable			 : STD_LOGIC := '0';
signal   S_Data_Ready		 : STD_LOGIC := '0';

signal   S_Begin_Read		 : STD_LOGIC := '0';
signal   S_Contour			 : integer range 0 to 7 := 0;

type Type_State is (S_CONFIGURE, S_MEASURE);
signal States : Type_State := S_CONFIGURE;

begin

SPI_Master_Remastered_Instantiation : SPI_Master_Remastered
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_SCLK_Frequency => C_SCLK_Frequency)
    Port Map (Clk => Clk, In_Enable => S_Enable, In_MOSI_Data => S_MOSI_Data, Out_MISO_Data => S_MISO_Data, Out_Data_Ready => S_Data_Ready, Out_CS => Out_CS, Out_SCLK => Out_SCLK, Out_MOSI => Out_MOSI, In_MISO => In_MISO);

P_Timer_Read : process (Clk) begin
    if (rising_edge(Clk)) then
        if (S_Timer_Read = C_Timer_Read_Lim-1) then
            S_Timer_Read <= 0;
            S_Timer_Read_Tick <= '1';
        else
            S_Timer_Read <= S_Timer_Read + 1;
            S_Timer_Read_Tick <= '0';
        end if;
    end if;
end process ;

P_MAIN : process (Clk) begin
    if (rising_edge(Clk)) then
        Out_Ready	<= '0'; 
        case States is
        
            when S_CONFIGURE =>
                if (S_Timer_Read_Tick = '1') then
                    S_Begin_Read <= '1';
                end if;
                if (S_Begin_Read = '1') then
                    if (S_Contour = 0) then
                        S_Enable <= '1';
                        S_MOSI_Data	<= x"0A";	          -- Write Command to ADXL362
                        if (S_Data_Ready = '1') then
                            S_MOSI_Data	<= x"2D";	      -- POWER_CTL Register Address
                            S_Contour <= S_Contour + 1;
                        end if;
                    elsif (S_Contour = 1) then
                        if (S_Data_Ready = '1') then
                            S_MOSI_Data	<= x"02";	      -- Enable Measurmenet Mode
                            S_Contour <= S_Contour + 1;
                        end if;					
                    elsif (S_Contour = 2) then
                        if (S_Data_Ready = '1') then
                            S_Contour <= 0;
                            S_Enable <= '0';
                            States <= S_MEASURE;
                            S_Begin_Read <= '0';
                        end if;
                    end if;
                end if;

            when S_MEASURE =>         
                if (S_Timer_Read_Tick = '1') then
                    S_Begin_Read <= '1';
                end if;           
                if (S_Begin_Read = '1') then
                    if (S_Contour = 0) then
                        S_Enable <= '1';
                        S_MOSI_Data	<= x"0B";	          -- Read Command to ADXL362
                        if (S_Data_Ready = '1') then
                            S_MOSI_Data	<= x"0E";	      -- XDATA_L Register Address
                            S_Contour <= S_Contour + 1;
                        end if;		
                    elsif (S_Contour = 1) then
                        if (S_Data_Ready = '1') then
                            S_MOSI_Data	<= x"00";	-- In continious read mode, only first address is enough
                            S_Contour <= S_Contour + 1;
                        end if;	
                    elsif (S_Contour = 2) then
                        if (S_Data_Ready = '1') then
                            -- In_MOSI_Data	<= x"00";
                            S_Contour <= S_Contour + 1;
                            Out_AX(7 downto 0) <= S_MISO_Data;
                        end if;
                    elsif (S_Contour = 3) then
                        if (S_Data_Ready = '1') then
                            -- In_MOSI_Data	<= x"00";
                            S_Contour <= S_Contour + 1;
                            Out_AX(15 downto 8)	<= S_MISO_Data;
                        end if;		
                    elsif (S_Contour = 4) then
                        if (S_Data_Ready = '1') then
                            -- In_MOSI_Data	<= x"00";
                            S_Contour <= S_Contour + 1;
                            Out_AY(7 downto 0) <= S_MISO_Data;
                        end if;			
                    elsif (S_Contour = 5) then
                        if (S_Data_Ready = '1') then
                            -- In_MOSI_Data	<= x"00";
                            S_Contour <= S_Contour + 1;
                            Out_AY(15 downto 8)	<= S_MISO_Data;
                        end if;		
                    elsif (S_Contour = 6) then
                        if (S_Data_Ready = '1') then
                            -- In_MOSI_Data	<= x"00";
                            S_Contour <= S_Contour + 1;
                            Out_AZ(7 downto 0) <= S_MISO_Data;
                        end if;							
                    elsif (S_Contour = 7) then
                        if (S_Data_Ready = '1') then
                            -- In_MOSI_Data	<= x"00";
                            S_Contour <= 0;
                            Out_AZ(15 downto 8)	<= S_MISO_Data;
                            Out_Ready <= '1';
                            S_Enable <= '0';
                            S_Begin_Read <= '0';
                        end if;						
                    end if;
                end if;
        
        end case;      
    end if;
end process;

end Behavioral;
