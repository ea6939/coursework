-- updater circuit
--
-- entity name: g27_updater
--
-- Copyright (C) 2013 Lulan Shen, Loren Lugosch
-- Version 1.0
-- Author: Lulan Shen; lulan.shen@mail.mcgill.ca
--         Loren Lugosch; loren.lugosch@mail.mcgill.ca
-- Date: November 22, 2013

LIBRARY ieee;
USE ieee.std_logic_1164.all;

library lpm;
use lpm.lpm_components.all; 

entity g27_updater is 
	port ( clk, reset, enable : in std_logic;
		update_enable : out std_logic);
end g27_updater;

architecture inside of g27_updater is

signal I0, I1 : std_logic_vector(10 downto 0);
signal I2 : std_logic;
		
begin

I0(10) <= '1';
I0(9 downto 0) <= (others => '0'); -- gives 1000000000

with I1 select
I2 <= '1' when "00000000000",
	  '0' when others;
	
update_enable <= I2;

count : component lpm_counter
	GENERIC MAP (
		lpm_direction => "DOWN",
		lpm_port_updown => "PORT_UNUSED",
		lpm_type => "LPM_COUNTER",
		lpm_width => 11
	)
	PORT MAP (
		sload => I2,
		clock => clk,
		aclr => not reset,
		data => I0,
		q => I1
	);
	
end inside;