library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

------------------------- Sequence Detector "1101" with Mealy Machine ------------------------- 
--------------------- S0 --1/0--> S1 --1/0--> S2 --0/0--> S3 --1/1--> S1 ---------------------- 

entity Sequence_Detector_Mealy_Machine is
    Port ( Clk      : in STD_LOGIC;
           Clear    : in STD_LOGIC;
           In_Data  : in STD_LOGIC;
           Out_Data : out STD_LOGIC);
end Sequence_Detector_Mealy_Machine;

architecture Behavioral of Sequence_Detector_Mealy_Machine is

type State_Type is (S0,S1,S2,S3);
signal Present_State, Next_State : State_Type;

begin

State_Register : process (Clk, Clear) begin
    if (Clear = '1') then
        Present_State <= S0;
    elsif (Clk'event and Clk = '1') then  -- rising_edge(Clk)
        Present_State <= Next_State;
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
                Next_State <= S1;
            else
                Next_State <= S0;
            end if;            
        when others => null;      
    end case;
end process;

C2 : process (Clk,Clear) begin
    if (Clear = '1') then
        Out_Data <= '0';
    elsif (Clk'event and Clk = '1') then
        if(Present_State = S3 and In_Data = '1') then
            Out_Data <= '1'; 
        else
            Out_Data <= '0';
        end if;
    end if;
end process;

end Behavioral;
