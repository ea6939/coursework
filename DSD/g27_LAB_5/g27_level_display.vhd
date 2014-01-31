library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity g27_level_display is
	port ( X : in integer range 0 to 255;
		   L9, L8, L7, L6, L5, L4, L3, L2, L1, L0 : out std_logic);
end g27_level_display;

architecture inside of g27_level_display is
begin

proc : process(X)
begin

L9 <= '0'; 
L8 <= '0'; 
L7 <= '0';
L6 <= '0';
L5 <= '0'; 
L4 <= '0'; 
L3 <= '0'; 
L2 <= '0'; 
L1 <= '0'; 
L0 <= '0';
     
	case X is
		when 26 to 50 =>
			L0 <= '1';
		when 51 to 75 =>
			L1 <= '1'; 
			L0 <= '1';
		when 76 to 100 =>
			L2 <= '1';
			L1 <= '1'; 
			L0 <= '1';
		when 101 to 125 =>
			L3 <= '1'; 
			L2 <= '1';
			L1 <= '1'; 
			L0 <= '1';
		when 126 to 150 =>
			L4 <= '1';
			L3 <= '1'; 
			L2 <= '1';
			L1 <= '1'; 
			L0 <= '1';
		when 151 to 175 =>
			L5 <= '1';
			L4 <= '1';
			L3 <= '1'; 
			L2 <= '1';
			L1 <= '1'; 
			L0 <= '1';
		when 176 to 200 =>
			L6 <= '1';
			L5 <= '1';
			L4 <= '1';
			L3 <= '1'; 
			L2 <= '1';
			L1 <= '1'; 
			L0 <= '1';
		when 201 to 225 =>
			L7 <= '1';
			L6 <= '1';
			L5 <= '1';
			L4 <= '1';
			L3 <= '1'; 
			L2 <= '1';
			L1 <= '1'; 
			L0 <= '1';
		when 226 to 250 =>
			L8 <= '1';
			L7 <= '1';
			L6 <= '1';
			L5 <= '1';
			L4 <= '1';
			L3 <= '1'; 
			L2 <= '1';
			L1 <= '1'; 
			L0 <= '1';
		when 251 to 255 =>
			L9 <= '1';
			L8 <= '1';
			L7 <= '1';
			L6 <= '1';
			L5 <= '1';
			L4 <= '1';
			L3 <= '1'; 
			L2 <= '1';
			L1 <= '1'; 
			L0 <= '1';
		when others =>
			L9 <= '0'; 
			L8 <= '0'; 
			L7 <= '0';
			L6 <= '0';
			L5 <= '0'; 
			L4 <= '0'; 
			L3 <= '0'; 
			L2 <= '0'; 
			L1 <= '0'; 
			L0 <= '0';
     
			
		end case;
	end process;
end inside;