library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity I2C_Master is
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
end I2C_Master;

architecture Behavioral of I2C_Master is

constant C_Divider : integer := (C_Clock_Frequency/C_SCL_Frequency)/4;  -- Number of clocks in 1/4 cycle of SCL

type Type_Machine is (S_Ready, S_Start, S_Command, S_Slave_ACK1, S_Write, S_Read, S_Slave_ACK2, S_Master_ACK, S_Stop); -- Needed States
signal I2C_State : Type_Machine;  -- State Machine

signal S_Data_Clk      : STD_LOGIC;             -- Data clock for SDA
signal S_Data_Clk_Prev : STD_LOGIC;             -- Data clock during previous system clock
SIGNAL S_SCL_Clk       : STD_LOGIC;             -- Constantly running internal SCL
SIGNAL S_SCL_Enable    : STD_LOGIC := '0';      -- Enables internal SCL to output

signal S_SDA_Enable_N  : STD_LOGIC;             -- Enables internal SDA to output
signal S_SDA_Internal  : STD_LOGIC := '1';      -- Internal SDA

signal S_Address_RW    : STD_LOGIC_VECTOR(7 downto 0);   -- Latched in address and read/write
signal S_Data_TX       : STD_LOGIC_VECTOR(7 downto 0);   -- Latched in data to write to slave
signal S_Data_Rx       : STD_LOGIC_VECTOR(7 downto 0);   -- Data received from slave
  
SIGNAL S_Bit_Contour   : integer range 0 TO 7 := 7;      -- Tracks bit number in transaction
signal S_Stretch       : STD_LOGIC := '0';               -- Identifies if slave is stretching SCL

begin

-- Generate the timing for the bus clock (S_SCL_Clk) and the data clock (S_Data_Clk)
process (Clk, Reset) 
    variable Counter  :  integer range 0 to C_Divider*4;  -- Timing for clock generation 
begin                  
    if (Reset = '0') then                    -- Reset Asserted
        S_Stretch <= '0';
        Counter := 0;
    elsif (Clk'event and Clk = '1') then
        S_Data_Clk_Prev <= S_Data_Clk;       -- Store Previous value of data clock
        if (Counter = C_Divider*4-1) then    -- End of timing cycle
            Counter := 0;                    -- Reset timer
        elsif (S_Stretch <= '0') then        -- Clock stretching from slave not detected
            Counter := Counter + 1;          -- Continue clock generation timing    
        end if;  
        case Counter is
            when 0 to (C_Divider - 1) =>              -- First 1/4 cycle of clocking
                S_SCL_Clk  <= '0';
                S_Data_Clk <= '0';
            when C_Divider to (C_Divider*2 - 1) =>    -- Second 1/4 cycle of clocking
                S_SCL_Clk  <= '0';
                S_Data_Clk <= '1';
            when C_Divider*2 to (C_Divider*3 - 1) =>  -- Third 1/4 cycle of clocking
                S_SCL_Clk  <= '1';
                if (SCL = '0') then
                    S_Stretch <= '1';
                else
                    S_Stretch <= '0';
                end if;
                S_Data_Clk <= '1';
            when others =>                            -- Last 1/4 cycle of clocking
                S_SCL_Clk  <= '1';
                S_Data_Clk <= '0';
        end case;
    end if;
end process;

process (Clk, Reset) begin
    if (Reset = '0') then                                                           -- Reset Asserted
        I2C_State <= S_Ready;                                                       -- Return to Initial State
        Out_Busy <= '0';                                                            -- Indicate not available
        S_SCL_Enable <= '0';                                                        -- Sets SCL High Impedance
        S_SDA_Internal <= '1';                                                      -- Sets SDA High Impedance
        ACK_Error <= '0';                                                           -- Clear acknowledge error flag
        S_Bit_Contour <= 7;                                                         -- Restarts data bit counter
        Out_Data_Read <= "00000000";                                                -- Clear data read port
    elsif (Clk'event and Clk = '1') then                                        
        if (S_Data_Clk = '1' and S_Data_Clk_Prev = '0') then                        -- Data clock rising edge
            case I2C_State is
                when S_Ready =>                                                     -- IDLE State
                    if (In_Enable = '1') then
                        Out_Busy <= '1';
                        S_Address_RW <= In_Device_Addres & In_Read_Write;           -- Collect requested slave address and command
                        S_Data_TX <= In_Data_Write;                                 -- Collect requested data to write
                        I2C_State <= S_Start;                                       -- Go to Start bit
                    else
                        Out_Busy <= '0';
                        I2C_State <= S_Ready;                                       -- Remain IDLE
                    end if;
                when S_Start =>                                                     -- Start bit of transaction
                    Out_Busy <= '1';                                                -- Resume BUSY if continuous mode
                    S_SDA_Internal <= S_Address_RW(S_Bit_Contour);                  -- Set first address bit to bus
                    I2C_State <= S_Command;                                         -- Go to Command
                when S_Command =>                                                   -- Address and command byte of transaction
                    if (S_Bit_Contour = 0) then
                        S_SDA_Internal <= '1';                                      -- Release sda for slave acknowledge
                        S_Bit_Contour <= 7;                                         -- Reset bit counter for "byte" states
                        I2C_State <= S_Slave_ACK1;                                  -- Go to slave acknowledge (command)
                    else
                        S_Bit_Contour <= S_Bit_Contour - 1;                         -- Keep track of transaction bits
                        S_SDA_Internal <= S_Address_RW(S_Bit_Contour - 1);          -- Write address/command bit to bus
                        I2C_State <= S_Command;                                     -- Continue with command
                    end if;
                when S_Slave_ACK1 =>                                                -- Slave acknowledge bit (command)
                    if (S_Address_RW(0)= '0') then                                  -- Write command
                        S_SDA_Internal <= S_Data_TX(S_Bit_Contour);                 -- Write first bit of data
                        I2C_State <= S_Write;                                       -- Go to Write byte
                    else                                                            -- Read command
                        S_SDA_Internal <= '1';                                      -- Release SDA from incoming data
                        I2C_State <= S_Read;                                        -- Go to read byte
                    end if; 
                when S_Write =>                                                     -- Write byte of transaction
                    Out_Busy <= '1';                                                -- Resume BUSY if continuous mode
                    if (S_Bit_Contour = 0) then
                        S_SDA_Internal <= '1';                                      -- Reset SDA for Slave ACK
                        S_Bit_Contour <= 7;                                         -- Reset bit counter for "byte" states
                        I2C_State <= S_Slave_ACK2;                                  -- Go to slave acknowledge (write)
                    else
                        S_Bit_Contour <= S_Bit_Contour - 1;                         -- Keep track of transaction bits
                        S_SDA_Internal <= S_Data_TX(S_Bit_Contour - 1);             -- Write address/command bit to bus
                        I2C_State <= S_Write;                                       -- Continue with command
                    end if;
                when S_Read =>
                    Out_Busy <= '1';                                                -- Resume BUSY if continuous mode
                    if (S_Bit_Contour = 0) then
                        if (In_Enable = '1' and S_Address_RW = In_Device_Addres & In_Read_Write) then    -- Continuing with another read at same address
                            S_SDA_Internal <= '0';                                  -- Acknowledge the byte has been received
                        else                                                        -- Stopping or continuing with a write
                            S_SDA_Internal <= '1';                                  -- Send a no-acknowledge (before stop or repeated start)
                        end if;
                        S_Bit_Contour <= 7;                                         -- Reset bit counter for "byte" states
                        Out_Data_Read <= S_Data_Rx;                                 -- Output Received Data
                        I2C_State <= S_Master_ACK;                                  -- Go to Master ACK
                    else
                        S_Bit_Contour <= S_Bit_Contour - 1;                         -- Keep track of transaction bits
                        I2C_State <= S_Read;                                        -- Continue with command
                    end if;
                when S_Slave_ACK2 =>                                                -- Slave ACK bit (write)
                    if (In_Enable = '1') then                                       -- Continue transaction
                        Out_Busy <= '1';                                            -- Continue is accepted
                        S_Address_RW <= In_Device_Addres & In_Read_Write;           -- Collect requested slave address and command
                        S_Data_TX <= In_Data_Write;                                 -- Collect requested data to write
                        if (S_Address_RW = In_Device_Addres & In_Read_Write) then   -- Continue transaction with another write
                            S_SDA_Internal <= In_Data_Write(S_Bit_Contour);         -- Write first bit of data
                            I2C_State <= S_Write;                                   -- Go to write byte
                        else                                                        -- Continue transaction with a read or new slave
                            I2C_State <= S_Start;                                   -- Go to Repeated Start
                        end if;
                    else
                        I2C_State <= S_Stop;                                        -- Go to Stop bit
                    end if;
                when S_Master_ACK =>
                    if (In_Enable = '1') then                                       -- Continue transaction
                        Out_Busy <= '0';                                            -- Continue is accepted and data received is available on bus
                        S_Address_RW <= In_Device_Addres & In_Read_Write;           -- Collect requested slave address and command
                        S_Data_TX <= In_Data_Write;                                 -- Collect requested data to write
                        if (S_Address_RW = In_Device_Addres & In_Read_Write) then   -- Continue transaction with another write
                            S_SDA_Internal <= '1';                                  -- Write first bit of data
                            I2C_State <= S_Read;                                    -- Go to write byte
                        else                                                        -- Continue transaction with a read or new slave
                            I2C_State <= S_Start;                                   -- Repeated Start
                        end if;
                    else
                        I2C_State <= S_Stop;                                        -- Go to Stop bit
                    end if;
                when S_Stop =>
                        Out_Busy <= '0';                                            -- Unflag BUSY
                        I2C_State <= S_Ready;                                       -- Go to IDLE state
            end case;
        elsif (S_Data_Clk = '0' and S_Data_Clk_Prev = '1') then                     -- Data clock falling edge  
            case I2C_State is
                when S_Start =>                                                     
                    if (S_SCL_Enable = '0') then                                    -- Starting new transaction
                        S_SCL_Enable <= '1';                                        -- Enable scl output
                        ACK_Error <= '0';                                           -- Reset ACK error output
                    end if;
                when S_Slave_ACK1 =>                                                -- Receiving slave acknowledge (command)
                    if(SDA /= '0' or ACK_Error = '1') then                          -- NACK or previous NACK 
                        ACK_Error <= '1';                                           -- Set error output if NACK
                    end if;
                when S_Read =>                                                      -- Receiving slave data
                    S_Data_RX(S_Bit_Contour) <= SDA;                                -- Receive current slave data bit
                when S_Slave_ACK2 =>
                    if(SDA /= '0' or ACK_Error = '1') then                          -- NACK or previous NACK 
                        ACK_Error <= '1';                                           -- Set error output if NACK
                    end if;
                when S_Stop => S_SCL_Enable <= '0';                                  -- Disable SCL
                when others => null;
            end case;
       end if;
    end if;
end process;


-- Set SDA Output
With I2C_State Select
    S_SDA_Enable_N <= S_Data_Clk_Prev when S_Start,                             -- Generate START condition
                NOT S_Data_Clk_Prev when S_Stop,                                -- Generate STOP condition
                S_SDA_Internal when others;                                     -- Set to internal SDA signal  
                        
-- Set SCL and SDA outputs
SCL <= '0' when (S_SCL_Enable = '1' and S_SCL_Clk = '0') else 'Z';
SDA <= '0' when S_SDA_Enable_N = '0' else 'Z';

end Behavioral;