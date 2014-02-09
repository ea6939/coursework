---------------------------------
-- Copyright 2013
-- Loren Lugosch 260404057, loren.lugosch@mail.mcgill.ca
-- Lulan Shen 260449509
--
-- This circuit interprets note numbers between 12 and 15 as rests and makes volume = 0 accordingly.
-- 
-- Revision 1.0
---------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity g27_rest_calculator is
	port ( volume : in std_logic_vector(22 downto 0);
			note_number : in std_logic_vector(3 downto 0);
			volume2 : out std_logic_vector(22 downto 0));
end g27_rest_calculator;

architecture inside of g27_rest_calculator is
begin

with note_number select
	volume2 <= "00000000000000000000000" when "1100",
			   "00000000000000000000000" when "1101",
	           "00000000000000000000000" when "1110",
	           "00000000000000000000000" when "1111",
	           volume when others;
	           
end inside;	           