library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity TestBench_SeqDet_Moore_Mealy is
end TestBench_SeqDet_Moore_Mealy;

architecture Behavioral of TestBench_SeqDet_Moore_Mealy is

component SequenceDetector_MooreMachine is
    Port ( Clk      : in STD_LOGIC;
           Clear    : in STD_LOGIC;
           In_Data  : in STD_LOGIC;
           Out_Data : out STD_LOGIC);
end component;

component Sequence_Detector_Mealy_Machine is
    Port ( Clk      : in STD_LOGIC;
           Clear    : in STD_LOGIC;
           In_Data  : in STD_LOGIC;
           Out_Data : out STD_LOGIC);
end component;

constant C_Clock_Period : time := 20ns;

signal Clk      : STD_LOGIC := '0';
signal Clear    : STD_LOGIC := '0';
signal In_Data  : STD_LOGIC := '0';
signal Out_Data_Moore : STD_LOGIC;
signal Out_Data_Mealy : STD_LOGIC;
begin

DUT_SeqDet_Moore : SequenceDetector_MooreMachine
    Port Map (Clk => Clk, Clear => Clear, In_Data => In_Data, Out_Data => Out_Data_Moore);

DUT_SeqDet_Mealy : Sequence_Detector_Mealy_Machine
    Port Map (Clk => Clk, Clear => Clear, In_Data => In_Data, Out_Data => Out_Data_Mealy);
    
P_Clock_Generation : process begin
    Clk <= '0';
    wait for C_Clock_Period/2;
    Clk <= '1';
    wait for C_Clock_Period/2;
end process;

P_STIMULI : process begin
    Clear <= '1';   
    wait for 100 ns;
     
    Clear <= '0'; 
    In_Data <= '0';  
    wait for 20 ns;
     
    In_Data <= '1';
    wait for 20 ns;
     
    In_Data <= '0';  
    wait for 20 ns; 
    
    In_Data <= '1';  
    wait for 20 ns;
     
    In_Data <= '1';  
    wait for 20 ns; 
    
    In_Data <= '0';   
    wait for 20 ns; 
    
    In_Data <= '1';  
    wait for 20 ns;
     
    In_Data <= '1';
    wait for 20 ns;
    
    In_Data <= '0';  
    wait for 20 ns; 
    
    In_Data <= '1';  
    wait for 20 ns;
    
    assert false
    report "SIM DONE"
    severity failure;
end process;

end Behavioral;
