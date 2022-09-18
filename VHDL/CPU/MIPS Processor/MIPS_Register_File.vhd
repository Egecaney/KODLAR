library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.NUMERIC_STD.all;

entity MIPS_Register_File is
    Generic ( C_Bit     : integer := 32;
              C_Address : integer := 5);
       Port ( In_Read_Register_Address_1  : in STD_LOGIC_VECTOR(C_Address-1 downto 0);
              In_Read_Register_Address_2  : in STD_LOGIC_VECTOR(C_Address-1 downto 0);
              In_Write_Register           : in STD_LOGIC_VECTOR(C_Address-1 downto 0);
              In_Write_Register_Data      : in STD_LOGIC_VECTOR(C_Bit-1 downto 0);
              In_Write_Register_Enable    : in STD_LOGIC;
              Out_Read_Register_Data_1    : out STD_LOGIC_VECTOR(C_Bit-1 downto 0);
              Out_Read_Register_Data_2    : out STD_LOGIC_VECTOR(C_Bit-1 downto 0));
end MIPS_Register_File;

architecture Behavioral of MIPS_Register_File is

type T_Register_File is array(0 to (2**C_Address)-1) of STD_LOGIC_VECTOR(C_Bit-1 downto 0);        -- ** Exponential (2**C_Address = 32)

-- 32 Register with 32 Bit
signal Register_Array : T_Register_File := (x"00000000", x"11111111", x"22222222", x"33333333",
                                            x"44444444", x"55555555", x"66666666", x"77777777",
                                            x"88888888", x"99999999", x"AAAAAAAA", x"BBBBBBBB",
                                            x"CCCCCCCC", x"DDDDDDDD", x"EEEEEEEE", x"FFFFFFFF",
                                            x"00000000", x"11111111", x"22222222", x"33333333",
                                            x"44444444", x"55555555", x"66666666", x"77777777",
                                            x"88888888", x"99999999", x"AAAAAAAA", x"BBBBBBBB",
                                            x"10008000", x"7FFFF1EC", x"EEEEEEEE", x"FFFFFFFF");   -- Global Pointer , Stack Pointer , Frame Pointer, Return  
                                              
begin

P_MAIN : process (In_Write_Register_Enable) begin
    if (In_Write_Register_Enable = '1') then
        Register_Array(To_integer(Unsigned(In_Write_Register))) <= In_Write_Register_Data;
    end if;
end process;

Out_Read_Register_Data_1 <= Register_Array(to_integer(unsigned(In_Read_Register_Address_1)));
Out_Read_Register_Data_2 <= Register_Array(to_integer(unsigned(In_Read_Register_Address_2)));

end Behavioral;
