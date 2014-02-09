---------------------------------
-- Copyright 2013
-- Loren Lugosch 260404057, loren.lugosch@mail.mcgill.ca
-- Lulan Shen 260449509
--
-- This circuit selects one of two sound qualities for the circuit using the rise and fall rate of the envelope
-- 
-- Revision 1.0
---------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity g27_envelope_controller is
		port (	envelope_switch : in std_logic;
				RISE_RATE          : out std_logic_vector(7 downto 0);
				FALL_RATE          : out std_logic_vector(7 downto 0));	
end g27_envelope_controller;

architecture inside of g27_envelope_controller is
begin

with envelope_switch select
FALL_RATE <= "00000001" when '0',
			 "11111111" when others;
			with envelope_switch select
RISE_RATE <= "00000001" when '0',
			 "11111111" when others;
			 		
end inside;