library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

------------------------- Sequence Detector "1101" with Moore Machine ------------------------- 
----------------- S0/0 --1--> S1/0 --1--> S11/0 --0--> S110/0 --1--> S1101/1 ------------------ 

entity SequenceDetector_MooreMachine is
    Port ( Clk      : in STD_LOGIC;
           Clear    : in STD_LOGIC;
           In_Data  : in STD_LOGIC;
           Out_Data : out STD_LOGIC);
end SequenceDetector_MooreMachine;

architecture Behavioral of SequenceDetector_MooreMachine is

type State_Type is (S0,S1,S2,S3,S4);
signal Present_State, Next_State : State_Type;

begin

State_Register: process (Clk) begin
    if (Rising_edge(Clk)) then
        if (Clear = '1') then
            Present_State <= S0;
        else
            Present_State <= Next_State;
        end if;
    end if;
end process;

C1 : process (Present_State, In_Data) begin
    case Present_State is    
        when S0 =>
            if (In_Data = '1') then
                Next_State <= S1;
            else
                Next_State <= S0;
            end if;       
        when S1 =>
            if (In_Data = '1') then
                Next_State <= S2;
            else
                Next_State <= S0;
            end if;       
        when S2 =>
            if (In_Data = '0') then
                Next_State <= S3;
            else
                Next_State <= S2;
            end if;            
        when S3 =>
            if (In_Data = '1') then
                Next_State <= S4;
            else
                Next_State <= S0;
            end if;        
        when S4 =>
            if (In_Data = '0') then
                Next_State <= S0;
            else
                Next_State <= S2;
            end if;     
        when others => null;      
    end case;
end process;

C2 : process (Present_State) begin
    if (Present_State = S4) then
        Out_Data <= '1';
    else
        Out_Data <= '0';
    end if;
end process;

end Behavioral;
