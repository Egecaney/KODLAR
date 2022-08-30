library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- The vending machine sells bootles of water for 75 Cent customers can enter either a dollar bill of quarters.

entity FSM_Vending_Machine is
    Port ( Clk          : in STD_LOGIC; 
           Reset        : in STD_LOGIC;
           In_Dolar     : in STD_LOGIC; 
           In_Quarter   : in STD_LOGIC;
           Out_Dispense : out STD_LOGIC; 
           Out_Change   : out STD_LOGIC);
end FSM_Vending_Machine;

architecture Behavioral of FSM_Vending_Machine is

type State_Type is (S_Wait, S_25, S_50);
signal Present_State, Next_State : State_Type;

begin

State_Register : process (Clk, Reset) begin
    if (Reset = '0') then
        Present_State <= S_Wait;
    elsif (Clk'event and Clk = '1') then
        Present_State <= Next_State;
    end if;
end process;

Next_State_Logic : process (Present_State, In_Dolar, In_Quarter) begin
    case Present_State is    
        when S_Wait =>
            if (In_Quarter = '1') then
                Next_State <= S_25;
            else
                Next_State <= S_Wait;
            end if;       
        when S_25 =>
            if (In_Quarter = '1') then
                Next_State <= S_50;
            else
                Next_State <= S_25;
            end if;       
        when S_50 =>
            if (In_Quarter = '1') then
                Next_State <= S_Wait;
            else
                Next_State <= S_50;
            end if;                     
        when others => Next_State <= S_Wait;      
    end case;
end process;

Output_Logic : process (Present_State, In_Dolar, In_Quarter) begin
    case Present_State is    
        when S_Wait =>
            if (In_Dolar = '1') then
                Out_Dispense <= '1'; Out_Change <= '1';
            else
                Out_Dispense <= '0'; Out_Change <= '0';
            end if;       
        when S_25 => Out_Dispense <= '0'; Out_Change <= '0';      
        when S_50 =>
            if (In_Quarter = '1') then
                Out_Dispense <= '1'; Out_Change <= '0';  
            else
                Out_Dispense <= '0'; Out_Change <= '0';
            end if;                     
        when others => Out_Dispense <= '0'; Out_Change <= '0';      
    end case;
end process;

end Behavioral;
