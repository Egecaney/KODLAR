library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.ram_pkg.all;

entity TestBench_Block_RAM is
    generic (
        RAM_WIDTH 		: integer 	:= 16;				  -- Specify RAM data width
        RAM_DEPTH 		: integer 	:= 128;				  -- Specify RAM depth (number of entries)
        RAM_PERFORMANCE : string 	:= "LOW_LATENCY");    -- Select "HIGH_PERFORMANCE" or "LOW_LATENCY" 
        -- RAM_PERFORMANCE : string 	:= "HIGH_PERFORMANCE"    -- Select "HIGH_PERFORMANCE" or "LOW_LATENCY"
end TestBench_Block_RAM;

architecture Behavioral of TestBench_Block_RAM is

component Block_RAM is
    Generic (
        RAM_WIDTH 		: integer 	:= 16;				-- Specify RAM data width
        RAM_DEPTH 		: integer 	:= 128;				-- Specify RAM depth (number of entries)
        RAM_PERFORMANCE : string 	:= "LOW_LATENCY");    -- Select "HIGH_PERFORMANCE" or "LOW_LATENCY" 
    
    Port (
        Addra : in STD_LOGIC_VECTOR((clogb2(RAM_DEPTH)-1) downto 0);    -- Address bus, width determined from RAM_DEPTH
        Dina  : in STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0);		  		-- RAM input data
        Clka  : in STD_LOGIC;                       			  		-- Clock
        Wea   : in STD_LOGIC;                       			  		-- Write enable
        Douta : out STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0));   			-- RAM output data
end component;

signal Addra : STD_LOGIC_VECTOR((clogb2(RAM_DEPTH)-1) downto 0)	:= (others => '0');
signal Dina  : STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0) := (others => '0');
signal Clka  : STD_LOGIC := '0';            
signal Wea   : STD_LOGIC := '0';                      
signal Douta : STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0);

constant C_Clock_Period	: time := 10 ns;

begin

Block_RAM_DUT : block_ram
    Generic map(RAM_WIDTH => RAM_WIDTH, RAM_DEPTH => RAM_DEPTH, RAM_PERFORMANCE => RAM_PERFORMANCE)
    Port map(Addra => Addra, Dina => Dina, Clka => Clka, Wea => Wea, Douta => Douta);

P_Clock_Generation : process begin
    Clka <= '0';
    wait for C_Clock_Period/2;
    Clka <= '1';
    wait for C_Clock_Period/2;
end process;

P_STIMULI : process begin 
    wait for C_Clock_Period*10;
    
    Addra 	<= "0000010";
    Dina	<= x"ABCD";
    Wea		<= '1';
    wait for C_Clock_Period;
    
    Addra 	<= "0000011";
    Dina	<= x"1234";
    Wea		<= '1';
    wait for C_Clock_Period;
    
    Addra 	<= "0000100";
    Dina	<= x"9876";
    Wea		<= '1';
    wait for C_Clock_Period;
    
    Wea		<= '0';
    wait for C_Clock_Period;
    
    Addra 	<= "0000010";
    wait for C_Clock_Period*3;
    
    Addra 	<= "0000011";
    wait for C_Clock_Period*3;
    
    Addra 	<= "0000100";
    wait for C_Clock_Period*3;
    
    wait for C_Clock_Period*10;
    assert false 
    report "SIM DONE"
    severity failure;
end process P_STIMULI;

end Behavioral;
