library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity TestBench_ADT7420 is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCL_Frequency   : integer := 400_000;
              C_Device_Address  : STD_LOGIC_VECTOR(6 downto 0) := "1001011");
end TestBench_ADT7420;

architecture Behavioral of TestBench_ADT7420 is

component ADT7420 is
    Generic ( C_Clock_Frequency : integer := 100_000_000;
              C_SCL_Frequency   : integer := 400_000;
              C_Device_Address  : STD_LOGIC_VECTOR(6 downto 0) := "1001011");  
       Port ( Clk               : in STD_LOGIC;                         
              Reset             : in STD_LOGIC;
              SDA               : inout STD_LOGIC;
              SCL               : inout STD_LOGIC;
              Out_Interrupt     : out STD_LOGIC;
              Out_Temperature   : out STD_LOGIC_VECTOR(12 downto 0));
end component;

signal Clk               : STD_LOGIC := '0';                         
signal Reset             : STD_LOGIC := '1';
signal SDA               : STD_LOGIC := 'H';
signal SCL               : STD_LOGIC := 'H';
signal Out_Interrupt     : STD_LOGIC;
signal Out_Temperature   : STD_LOGIC_VECTOR(12 downto 0);

constant C_Clock_Period : time := 10 ns;
signal Message : String(1 to 10) := "Initial---";
begin

ADT7420_DUT : ADT7420
    Generic Map (C_Clock_Frequency => C_Clock_Frequency, C_SCL_Frequency => C_SCL_Frequency, C_Device_Address => C_Device_Address)
    Port Map (Clk => Clk, Reset => Reset, SDA => SDA, SCL => SCL, Out_Interrupt => Out_Interrupt, Out_Temperature => Out_Temperature);

P_Clock_Generation : process begin
    Clk <= '0';
    wait for C_Clock_Period/2;
    Clk <= '1';
    wait for C_Clock_Period/2;
end process;

process begin
    SCL	<= 'H';
    wait until (SCL = 'H') and (SDA'event and SDA='0');	-- start condition
    Message <= "startCond-";
    wait until SCL = '0';
    for i in 1 to 8 loop
        wait until (SCL'event and SCL='0');
        wait for 1 ps;
    end loop;
    
    -- give slave ack
    SDA <= '0';
    Message <= "slaveAck--";
    wait until (SCL'event and SCL = '0');
    SDA <= 'H';
    wait for 1 ps;
    
    wait until (SCL = 'H') and (SDA'event and SDA='H');	-- stop condition
    Message <= "stopCond--";
    wait for 1 ps;
    
    
    -- read part    
    wait until (SCL = 'H') and (SDA'event and SDA='0');	-- start condition
    Message <= "startCond-";
    wait until SCL = '0';
    for i in 1 to 8 loop
        wait until (SCL'event and SCL='0');
        wait for 1 ps;
    end loop;
    
    
    -- give slave ack
    SDA <= '0';
    Message <= "slaveAck--";
    wait until (SCL'event and SCL = '0');
    Message <= "tempMSB---";
    
    -- sent slave data
    SDA <= '0';
    wait until (SCL'event and SCL = '0');
    SDA <= '0';
    wait until (SCL'event and SCL = '0');
    SDA <= 'H';
    wait until (SCL'event and SCL = '0');
    SDA <= 'H';
    wait until (SCL'event and SCL = '0');
    SDA <= '0';
    wait until (SCL'event and SCL = '0');
    SDA <= 'H';
    wait until (SCL'event and SCL = '0');
    SDA <= '0';
    wait until (SCL'event and SCL = '0');
    SDA <= '0';
    wait until (SCL'event and SCL = '0');
    Message <= "masterAck-";
    SDA <= 'H';
    wait until (SCL'event and SCL = '0');
    Message <= "tempLSB---";
    -- sent slave data
    SDA <= '0';
    wait until (SCL'event and SCL = '0');
    SDA <= '0';
    wait until (SCL'event and SCL = '0');
    SDA <= '0';
    wait until (SCL'event and SCL = '0');
    SDA <= 'H';
    wait until (SCL'event and SCL = '0');
    SDA <= 'H';
    wait until (SCL'event and SCL = '0');
    SDA <= 'H';
    wait until (SCL'event and SCL = '0');
    SDA <= 'H';
    wait until (SCL'event and SCL = '0');
    SDA <= '0';
    wait until (SCL'event and SCL = '0');
    Message <= "masterAck-";
    SDA <= 'H';
    
    wait until (SCL = 'H') and (SDA'event and SDA='H');	-- stop condition
    Message <= "stopCond--";
    
    
    wait for 1.5 ms;
    
    assert false
    report "sim done"
    severity failure;

end process;

end Behavioral;
