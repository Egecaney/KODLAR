library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

Package Ram_PKG is
    function clogb2 (depth: in natural) return integer;
End Ram_PKG;

Package Body Ram_PKG is
    Function clogb2( depth : natural) return integer is
        variable Temp    : integer := depth;
        variable Ret_Val : integer := 0;
        begin
            while Temp > 1 loop
                Ret_Val := Ret_Val + 1;
                Temp    := Temp / 2;
            end loop;
            return Ret_Val;
    end Function;
end Package Body Ram_PKG;

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use work.Ram_PKG.all;               -- This package performs Logarithmic operation for automate.
USE std.textio.all;

entity Top_BlockRAM_and_UART is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Baud_Rate       : integer := 115_200;
        C_Stop_Bits       : integer := 2;
        RAM_WIDTH 		  : integer := 16;
        RAM_DEPTH 		  : integer := 128;
        RAM_PERFORMANCE   : string 	:= "LOW_LATENCY";
        C_RAM_TYPE 		  : string 	:= "BLOCK");      
    Port ( 
        Clk    : in STD_LOGIC;
        In_RX  : in STD_LOGIC;
        Out_TX : out STD_LOGIC);
end Top_BlockRAM_and_UART;

architecture Behavioral of Top_BlockRAM_and_UART is

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

component Uart_RX is
    Generic(
        C_Clock_Frequency : integer := 100_000_000;
        C_Baud_Rate       : integer := 115_200);
    Port(
        Clk               : in STD_LOGIC;
        In_RX             : in STD_LOGIC;
        Out_Data          : out STD_LOGIC_VECTOR (7 downto 0);
        Out_RX_Done_Tick  : out STD_LOGIC );
end component;

component Block_RAM is
    Generic (
        RAM_WIDTH 		: integer 	:= 16;				  -- Specify RAM data width
        RAM_DEPTH 		: integer 	:= 128;				  -- Specify RAM depth (number of entries)
        RAM_PERFORMANCE : string 	:= "LOW_LATENCY";     -- Select "HIGH_PERFORMANCE" or "LOW_LATENCY" 
        C_RAM_TYPE 		: string 	:= "BLOCK");
    Port (
        Addra : in STD_LOGIC_VECTOR((clogb2(RAM_DEPTH)-1) downto 0);    -- Address bus, width determined from RAM_DEPTH
        Dina  : in STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0);		  		-- RAM Input Data
        Clka  : in STD_LOGIC;                       			  		-- Clock
        Wea   : in STD_LOGIC;                       			  		-- Write Enable
        Douta : out STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0)   			-- RAM Output Data
    );
end component;

signal S_Out_Data 		  : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
signal S_In_Data		  : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
signal S_Out_RX_Done_Tick : STD_LOGIC := '0';
signal S_Out_TX_Done_Tick : STD_LOGIC := '0';
signal S_In_TX_Start 	  : STD_LOGIC := '0';

signal S_Addra 			  : STD_LOGIC_VECTOR((clogb2(RAM_DEPTH)-1) downto 0);    
signal S_Dina  			  : STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0);
signal S_Wea   			  : STD_LOGIC;  
signal S_Douta 			  : STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0) ;              

type T_States is (S_IDLE, S_OKU, S_YAZ, S_TRANSMIT);
signal State : T_States := S_IDLE;

signal S_Data_Buffer : STD_LOGIC_VECTOR (4*8-1 downto 0) := (others => '0');
signal S_Counter	 : integer range 0 to 255 := 0;

begin

Uart_RX_Instantiation : Uart_RX 
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Baud_Rate => C_Baud_Rate)
    Port Map (Clk => Clk, In_RX => In_RX, Out_Data => S_Out_Data, Out_RX_Done_Tick => S_Out_RX_Done_Tick);

Uart_TX_Instantiation : Uart_TX 
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_Baud_Rate => C_Baud_Rate, C_Stop_Bits => C_Stop_Bits)
    Port Map (Clk => Clk, In_Data => S_In_Data, In_TX_Start => S_In_TX_Start, Out_TX => Out_TX, Out_TX_Done_Tick => S_Out_TX_Done_Tick);
    
Block_RAM_128x16_Instantiation: Block_RAM
    Generic Map(RAM_WIDTH => RAM_WIDTH, RAM_DEPTH => RAM_DEPTH, RAM_PERFORMANCE => RAM_PERFORMANCE, C_RAM_TYPE=> C_RAM_TYPE)
    Port Map (Addra => S_Addra, Dina => S_Dina, Clka => Clk, Wea => S_Wea, Douta => S_Douta);
    
P_MAIN : process (Clk) begin
    if (rising_edge(Clk)) then
        case State is
        
            when S_IDLE =>
          
                S_Wea <= '0';
                S_Counter <= 0;
                if (S_Out_RX_Done_Tick = '1') then
                    S_Data_Buffer(7 downto 0) <= S_Out_Data;
                    S_Data_Buffer(4*8-1 downto 1*8) <= S_Data_Buffer(3*8-1 downto 0*8);
                end if;
                
                if (S_Data_Buffer(4*8-1 downto 3*8) = x"0A") then
                    State	<= S_YAZ;
                end if;
                if (S_Data_Buffer(4*8-1 downto 3*8) = x"0B") then
                    State	<= S_OKU;
                end if;
            
            when S_YAZ =>
                S_Addra	<= S_Data_Buffer(3*8-2 downto 2*8);
                S_Dina <= S_Data_Buffer(2*8-1 downto 0*8);
                S_Wea <= '1';
                State <= S_IDLE;
                S_Data_Buffer <= (others => '0');
            
            when S_OKU =>
            
                S_Addra <= S_Data_Buffer(3*8-2 downto 2*8);
                S_Counter <= S_Counter + 1;
                if (S_Counter = 1) then
                    S_Data_Buffer(2*8-1 downto 0*8)	<= S_Douta;
                    State <= S_TRANSMIT;	
                    S_Counter <= 3;
                    S_In_Data <= S_Data_Buffer(4*8-1 downto 3*8);
                    S_In_TX_Start <= '1';
                end if;
            
            when S_TRANSMIT => 
                
                if (S_Counter = 0) then
                    S_In_TX_Start <= '0';
                    if (S_Out_TX_Done_Tick = '1') then
                        State <= S_IDLE;
                        S_Data_Buffer <= (others => '0');
                    end if;
                else
                    S_In_Data <= S_Data_Buffer(S_Counter*8-1 downto (S_Counter-1)*8);
                    if (S_Out_TX_Done_Tick = '1') then
                        S_Counter <= S_Counter - 1;
                    end if;				
                end if;
            
        end case;
    end if;
end process;

end Behavioral;
