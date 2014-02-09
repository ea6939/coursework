---------------------------------
-- Copyright 2013
-- Loren Lugosch 260404057, loren.lugosch@mail.mcgill.ca
-- Lulan Shen 260449509
--
-- This circuit indicates system status
-- 
-- Revision 1.0
---------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity g27_status_display_controller is
		port (	loop_mode : in std_logic;
				pause : in std_logic;
				SS0 : out std_logic_vector(6 downto 0); -- seven segment LEDs
				SS1 : out std_logic_vector(6 downto 0);
				SS2 : out std_logic_vector(6 downto 0);
				SS3 : out std_logic_vector(6 downto 0));	
end g27_status_display_controller;

architecture inside of g27_status_display_controller is
begin

SS3 <= "1111111"; -- keep these two segments blank, can be used for other things later
SS2 <= "1111111";

with loop_mode select
SS1 <= "1111111" when '0', -- spells L
		"1000111" when others;

with pause select
SS0 <= "1111111" when '1', -- spells P
		"0001100" when others;

end inside;