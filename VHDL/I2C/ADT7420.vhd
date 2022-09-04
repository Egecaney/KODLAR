library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity ADT7420 is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCL_Frequency   : integer := 400_000;
              C_Device_Address  : STD_LOGIC_VECTOR(6 downto 0) := "1001011");  
       Port ( Clk               : in STD_LOGIC;                         
              Reset             : in STD_LOGIC;
              SDA               : inout STD_LOGIC;
              SCL               : inout STD_LOGIC;
              Out_Interrupt     : out STD_LOGIC;
              Out_Temperature   : out STD_LOGIC_VECTOR(12 downto 0));
end ADT7420;

architecture Behavioral of ADT7420 is

component I2C_Master is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCL_Frequency   : integer := 400_000);                  -- Speed the I2C Bus (SCL) 
       Port ( Clk               : in STD_LOGIC;                         
              Reset             : in STD_LOGIC;                         -- Active LOW Reset
              In_Enable         : in STD_LOGIC;                         -- Latch in Command
              In_Device_Addres  : in STD_LOGIC_VECTOR(6 downto 0);      -- Address of Target Slave
              In_Read_Write     : in STD_LOGIC;                         -- '0' is Write, '1' is Read
              In_Data_Write     : in STD_LOGIC_VECTOR (7 downto 0);     -- Data Write to Slave
              Out_Busy          : out STD_LOGIC;                        -- Indicates transaction in progress
              Out_Data_Read     : out STD_LOGIC_VECTOR (7 downto 0);    -- Data Read from Slave
              ACK_Error         : buffer STD_LOGIC;                     -- Flag if improper acknowledge from slave
              SDA               : inout STD_LOGIC;                      -- Serial data output of I2C bus
              SCL               : inout STD_LOGIC);                     -- Serial clock output of I2C bus
end component;

signal S_I2C_Enable         : STD_LOGIC := '0';
signal S_Read_Write         : STD_LOGIC := '0';
signal S_Data_Write         : STD_LOGIC_VECTOR (7 downto 0) := (others => '0'); 
signal S_Data_Read          : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');  
signal S_ACK_Error          : STD_LOGIC := '0';

signal S_Busy               : STD_LOGIC := '0';
signal S_Busy_Prev          : STD_LOGIC := '0';
signal S_Busy_Contour       : integer range 0 to 255 := 0;

signal S_Enable	            : STD_LOGIC := '0';
signal S_Wait_Enable	    : STD_LOGIC := '0';
signal S_Contour	        : integer range 0 to 255 := 0;

type Type_States is (S_IDLE, S_MEASURE);
signal ADT7420_State : Type_States := S_IDLE;

constant C_Countour_250ms_Lim   : integer    := C_Clock_Frequency/1000;             -- For Test Bench
--constant C_Countour_250ms_Lim   : integer    := C_Clock_Frequency/4;              -- 250ms'de bir okumak için.
signal  S_Countour_250ms : integer range 0 to C_Countour_250ms_Lim - 1 := 0;
signal  S_Countour_250ms_Enable  : STD_LOGIC := '0';
signal  S_Countour_250ms_Tick    : STD_LOGIC := '0';

begin

I2C_Master_Instantiation : I2C_Master
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_SCL_Frequency => C_SCL_Frequency)
    Port Map (Clk => Clk, Reset => Reset, In_Enable => S_I2C_Enable, In_Device_Addres => C_Device_Address, In_Read_Write => S_Read_Write,
              In_Data_Write => S_Data_Write, Out_Busy => S_Busy, Out_Data_Read => S_Data_Read, ACK_Error => S_ACK_Error, SDA => SDA, SCL => SCL);

S_Countour_250ms_Enable <= '1';

P_MAIN : process (Clk) begin
    if (rising_edge(Clk)) then
        case ADT7420_State is
            
            when S_IDLE =>
                -- IDLE durumunda Slave'e Register Adres icin WRITE command gonderiliyor.
		        -- Ýlk güç açýlýp reset kalktýðýnda 250 ms bekleniliyor. Bir daha bu 250 ms reset olmadýkça beklenmiyor.
                S_Busy_Prev <= S_Busy;
                if (S_Busy_Prev = '0' and S_Busy = '1') then
                    S_Busy_Contour <= S_Busy_Contour + 1;
                end if;
                Out_Interrupt <= '0';
                if (Reset = '1') then
                    if(S_Countour_250ms_Tick = '1') then
                        S_Enable <= '1';
                    end if;
                else
                    S_Enable <= '0';
                end if;
                if (S_Enable = '1') then
                    if (S_Busy_Contour = 0) then    -- First byte write
                        S_I2C_Enable <= '1';
                        S_Read_Write <= '0';        -- Write
                        S_Data_Write <= x"00";      -- Temperature MSB Register Address
                    elsif (S_Busy_Contour = 1) then
                        S_I2C_Enable <= '0';
                        if (S_Busy = '0') then
                            S_Wait_Enable <= '1';
                            S_Busy_Contour <= 0;
                            S_Enable <= '0';    
                        end if;
                    end if;
                end if;
                -- Bu aslinda kritik, datasheette STOP sonrasi START condition icin min bekleme zamani olarak 1.3 us denilmiþ.
                -- Burada beklenecek sure parametrik olsa daha iyi olur, CLKFREQ parametresi ile ifade edilmelidir.
                if (S_Wait_Enable = '1') then
                    if (S_Contour = 255) then
                        ADT7420_State <= S_MEASURE;
                        S_Contour <= 0;
                        S_Wait_Enable <= '0';
                    else
                        S_Contour <= S_Contour + 1;
                    end if;
                end if;
            
            when S_MEASURE =>
                S_Busy_Prev	<= S_Busy;
                if (S_Busy_Prev = '0' and S_Busy = '1') then
                    S_Busy_Contour <= S_Busy_Contour + 1;
                end if;		
                if (S_Busy_Contour = 0) then		
                    S_I2C_Enable <= '1';
                    S_Read_Write <= '1';		    -- READ
                    S_Data_Write <= x"00";	
                elsif (S_Busy_Contour = 1) then	    -- READ Starts
                    if (S_Busy = '0') then
                        Out_Temperature(12 downto 5) <= S_Data_Read;
                    end if;					
                    S_Read_Write <= '1';
                elsif (S_Busy_Contour = 2) then	    -- Data READ
                    S_I2C_Enable <= '0';            -- NO OTHER BYTE WILL BE READ.
                    if (S_Busy = '0') then
                        Out_Temperature(4 downto 0)	<= S_Data_Read(7 downto 3);
                        ADT7420_State <= S_IDLE;
                        S_Busy_Contour <= 0;
                        Out_Interrupt <= '1';
                    end if;						
                end if;	
            
        end case;
    end if;
end process;

P_Contour_250ms : process (Clk)begin
    if (rising_edge(CLK)) then
        if (S_Countour_250ms_Enable = '1') then
            if (S_Countour_250ms = C_Countour_250ms_Lim - 1) then
                S_Countour_250ms_Tick <= '1';
                S_Countour_250ms <= 0;
            else
                S_Countour_250ms_Tick <= '0';
                S_Countour_250ms <= S_Countour_250ms + 1;
            end if;
        else
            S_Countour_250ms_Tick <= '0';
            S_Countour_250ms <= 0;
        end if;
end if;
end process;

end Behavioral;
