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

entity Block_RAM is
    Generic (
        RAM_WIDTH 		: integer 	:= 16;				  -- Specify RAM data width
        RAM_DEPTH 		: integer 	:= 128;				  -- Specify RAM depth (number of entries)
        RAM_PERFORMANCE : string 	:= "LOW_LATENCY";   -- Select "HIGH_PERFORMANCE" or "LOW_LATENCY" 
        C_RAM_TYPE 		: string 	:= "BLOCK");
    Port (
        Addra : in STD_LOGIC_VECTOR((clogb2(RAM_DEPTH)-1) downto 0);    -- Address bus, width determined from RAM_DEPTH
        Dina  : in STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0);		  		-- RAM Input Data
        Clka  : in STD_LOGIC;                       			  		-- Clock
        Wea   : in STD_LOGIC;                       			  		-- Write Enable
        Douta : out STD_LOGIC_VECTOR(RAM_WIDTH-1 downto 0)   			-- RAM Output Data
    );
end Block_RAM;

architecture Behavioral of Block_RAM is

constant C_RAM_WIDTH 		: integer := RAM_WIDTH;
constant C_RAM_DEPTH 		: integer := RAM_DEPTH;
constant C_RAM_PERFORMANCE 	: string  := RAM_PERFORMANCE;

signal Douta_REG : std_logic_vector(C_RAM_WIDTH-1 downto 0) := (others => '0');
type Ram_Type is array (C_RAM_DEPTH-1 downto 0) of std_logic_vector (C_RAM_WIDTH-1 downto 0);          -- 2D Array Declaration for RAM signal
signal Ram_Data : std_logic_vector(C_RAM_WIDTH-1 downto 0) ;

-- Following code defines RAM
signal Ram_Name : Ram_Type := (others => (others => '0'));

-- Ram_Style attribute
attribute Ram_Style : string;
attribute Ram_Style of Ram_Name : signal is C_RAM_TYPE;

begin

-- write process
process(Clka)begin
    if(rising_edge(Clka)) then
        if(Wea = '1') then
            Ram_Name(to_integer(unsigned(Addra))) <= Dina;
        end if;
        Ram_Data <= Ram_Name(to_integer(unsigned(Addra)));     
    end if;
end process;

--  Following code generates LOW_LATENCY (no output register)
--  Following is a 1 clock cycle read latency at the cost of a longer clock-to-out timing

No_Output_Register : if C_RAM_PERFORMANCE = "LOW_LATENCY" generate
    Douta <= Ram_Data;
end generate;

--  Following code generates HIGH_PERFORMANCE (use output register)
--  Following is a 2 clock cycle read latency with improved clock-to-out timing
Output_Register : if C_RAM_PERFORMANCE = "HIGH_PERFORMANCE"  generate
    process(Clka)
    begin
        if(rising_edge(Clka)) then
            Douta_REG <= Ram_Data;
        end if;
    end process;
    Douta <= Douta_REG;
end generate;

end Behavioral;