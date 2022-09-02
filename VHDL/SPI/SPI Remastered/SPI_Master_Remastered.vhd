-- AUTHOR        : EGEMEN CAN AYDUÐAN
-- CREATED       : 30.08.2022
-- REVISION DATE : 30.08.2022

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity SPI_Master_Remastered is
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
end SPI_Master_Remastered;

architecture Behavioral of SPI_Master_Remastered is

-- CONSTANTS
constant C_Edge_Contour_Lim_Div2	: integer := C_Clock_Frequency/(C_SCLK_Frequency*2);
 
-- INTERNAL SIGNALS
signal S_Write_Register : STD_LOGIC_VECTOR (7 downto 0) 	:= (others => '0');	
signal S_Read_Register  : STD_LOGIC_VECTOR (7 downto 0) 	:= (others => '0');	
 
signal S_SCLK_Enable	: STD_LOGIC := '0';
signal S_SCLK			: STD_LOGIC := '0';
signal S_SCLK_Prev	    : STD_LOGIC := '0';
signal S_SCLK_Rise	    : STD_LOGIC := '0';
signal S_SCLK_Fall	    : STD_LOGIC := '0';

signal S_MOSI_Enable	: STD_LOGIC := '0';
signal S_MISO_Enable	: STD_LOGIC := '0';
signal S_Once           : STD_LOGIC := '0';
 
signal S_Edge_Contour   : integer range 0 to C_Edge_Contour_Lim_Div2 := 0;
signal S_Contour 		: integer range 0 to 15 := 0;
 
-- STATE DEFINITIONS
type Type_States is (S_Idle, S_Transfer);
signal SPI_State : Type_States := S_Idle;

begin


-- P_SAMPLE_Enable process assigns S_MOSI_Enable and S_MISO_Enable internal signals to S_SCLK_Fall or S_SCLK_Rise in a combinational logic. 
P_SAMPLE_Enable : process (S_SCLK_Fall, S_SCLK_Rise) begin   
    S_MOSI_Enable <= S_SCLK_Fall;
    S_MISO_Enable <= S_SCLK_Rise;             
end process;

-- P_Rise_Fall_Detect process assigns S_SCLK_Fall and S_SCLK_Rise signals in a combinational logic.
P_Rise_Fall_Detect : process (S_SCLK, S_SCLK_Prev) begin
    if(S_SCLK = '1' and S_SCLK_Prev = '0') then
        S_SCLK_Rise <= '1';
    else
        S_SCLK_Rise <= '0';
    end if;
    if(S_SCLK = '0' and S_SCLK_Prev = '1') then
        S_SCLK_Fall <= '1';
    else
        S_SCLK_Fall <= '0';
    end if;
end process;

-- In the P_SCLK_Generation process, internal SCLK signal is generated if S_SCLK_Enable signal is '1'. 
P_SCLK_Generation : process (Clk) begin
    if (rising_edge(Clk)) then
        if (S_SCLK_Enable = '1') then
            if (S_Edge_Contour = C_Edge_Contour_Lim_Div2 - 1) then
                S_SCLK <= not S_SCLK;
                S_Edge_Contour <= 0;
            else
                S_Edge_Contour <= S_Edge_Contour + 1;
            end if;
        else
            S_Edge_Contour <= 0;
            S_SCLK <= '0';
        end if;
    end if;
end process;

-- In the MAIN process S_Idle and S_Transfer states are implemented. 
-- State changes from S_Idle to S_Transfer when In_Enable input signal has the logic high value. At that cycle, S_Write_Register signal is assigned to In_MOSI_Data input signal.
-- According to C_CPHA generic parameter, the transaction operation changes slightly.
P_MAIN : process (Clk) begin
    if(rising_edge(Clk)) then
        Out_Data_Ready <= '0';
        S_SCLK_Prev <= S_SCLK;
        
        case SPI_State is 
            when S_Idle =>
                Out_CS         <= '1';
                Out_MOSI       <= '0';
                Out_Data_Ready <= '0';
                S_SCLK_Enable  <= '0';
                S_Contour      <= 0;
                Out_SCLK   <= '0';
                if (In_Enable = '1') then
                    SPI_State        <= S_Transfer;
                    S_SCLK_Enable    <= '1';
                    S_Write_Register <= In_MOSI_Data;
                    Out_MOSI         <= In_MOSI_Data(7);
                    S_Read_Register  <= x"00";
                end if;
                
            when S_Transfer =>
                Out_CS   <= '0';
                Out_MOSI <= S_Write_Register(7);
                
                if (S_Contour = 0) then
                    Out_SCLK <= S_SCLK;
                    if (S_MISO_Enable = '1') then
                        S_Read_Register(0) <= In_MISO;
                        S_Read_Register(7 downto 1) <= S_Read_Register(6 downto 0);
                        S_Contour <= S_Contour + 1;
                        S_Once <= '1';
                    end if;
                elsif(S_Contour = 8) then
                    if (S_Once = '1') then
                        Out_Data_Ready <= '1';
                        S_Once <= '0';
                    end if;
                    Out_MISO_Data <= S_Read_Register;
                    Out_SCLK <= S_SCLK;
                    if (S_MOSI_Enable = '1') then
                        if (In_Enable = '1') then
                            S_Write_Register <= In_MOSI_Data;
                            Out_MOSI <= In_MOSI_Data(7);
                            S_Contour <= 0;
                        else
                            S_Contour <= S_Contour + 1;
                        end if;
                        if (S_MISO_Enable = '1') then
                            SPI_State <= S_Idle;
                            Out_CS <= '1';
                        end if;
                    end if;
                elsif(S_Contour = 9) then
                    if (S_MISO_Enable = '1') then
                        SPI_State <= S_Idle;
                        Out_CS <= '1';
                    end if;
                else
                    Out_SCLK <= S_SCLK;
                    if (S_MISO_Enable = '1') then
                        S_Read_Register(0) <= In_MISO;
                        S_Read_Register(7 downto 1) <= S_Read_Register(6 downto 0);
                        S_Contour <= S_Contour + 1;    
                    end if;
                    if (S_MOSI_Enable = '1') then
                        S_Write_Register(7 downto 1) <= S_Write_Register(6 downto 0);   
                    end if;            
                end if;              
        end case;
    end if;
end process;

end Behavioral;
