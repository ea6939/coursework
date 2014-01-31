-- this circuit computes the sine(x)
--
-- entity name: g27_sine
--
-- Copyright (C) 2013 Lulan Shen, Loren Lugosch
-- Version 1.0
-- Author: Lulan Shen; lulan.shen@mail.mcgill.ca
--         Loren Lugosch; loren.lugosch@mail.mcgill.ca
-- Date: September 30, 2013

library ieee; -- allows use of the std_logic_vector type
use ieee.std_logic_1164.all;
library lpm; -- allows use of the Altera library modules
use lpm.lpm_components.all;

entity g27_sine is 
 port ( clock        : in std_logic;
		input_value  : in std_logic_vector(6 downto 0) ;
		-- input is a 7-bit binary value representing numbers between 0 and 128.(input x between 0 and 90 degrees)
		sine : out std_logic_vector(15 downto 0));
		-- output should have 16 bits
end g27_sine;
	
architecture sine of g27_sine is

begin
	crc_table : lpm_rom -- use the altera rom library macrocell
	GENERIC MAP(
		lpm_widthad => 7, -- sets the width of the ROM address bus
		lpm_numwords => 128, -- sets the words stored in the ROM
		lpm_outdata => "UNREGISTERED", -- no register on the output
		lpm_address_control => "REGISTERED", -- register on the input
		lpm_file => "g27_sine.mif", -- the ascii file containing the ROM data
		lpm_width => 16) -- the width of the word stored in each ROM location
		PORT MAP(inclock => clock, address => input_value, q => sine);

end sine;
		
		
 