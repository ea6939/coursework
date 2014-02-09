---------------------------------
-- Copyright 2013
-- Loren Lugosch 260404057, loren.lugosch@mail.mcgill.ca
-- Lulan Shen
--
-- This circuit produces a (bpm) beats per minute metronome
-- and a beat every 60/(24*bpm) corresponding to the beginning of the period of a note.
-- 
-- Revision 1.0
---------------------------------

library ieee;
use ieee.std_logic_1164.all;

library lpm;
use lpm.lpm_components.all; 

entity g27_tempo is
	port ( bpm 		    : in std_logic_vector(7 downto 0);
		   clk, reset   : in std_logic;
		   beat_gate    : out std_logic;
		   tempo_enable : out std_logic);
end g27_tempo;

architecture inside of g27_tempo is
---------------------------------
----- component declaration
---------------------------------

	component g27_lpm_ff2 is 
		port (clock, aclr, enable : in std_logic;
								q : out std_logic);
	end component;

	
---------------------------------
----- /component declaration
---------------------------------

---------------------------------
----- signal declaration
---------------------------------	
	signal I0,I1: std_logic_vector(23 downto 0);
	signal I4: std_logic_vector(3 downto 0);
	signal I2,I3,I5,I6: std_logic;
	
---------------------------------
----- /signal declaration
---------------------------------	
	
begin

	I6 <= not I5;
	tempo_enable <= I3;
	with I1 select --using a giant OR gate makes delays
		I2 <= '0' when "000000000000000000000000",
		'1' when others;
		
	I3 <= not I2;
	--I5 <= I4(3) or I4(2) or I4(1) or I4(0);
	with I4 select
		I5 <= '0' when "0000",
		'1' when others;
	
	-- This ROM stores the values of the factor by which the 50 MHz clock gets divided to get 
	-- the bpm
	inst0: lpm_rom
			generic map (lpm_widthad=>8, 
				lpm_numwords=>256, 
			    lpm_outdata=>"UNREGISTERED",
			    lpm_address_control=>"REGISTERED",
				lpm_file => "g27_bpm.mif",
				lpm_width => 24)
			port map (inclock=>clk, address=>bpm, q=>I0);
			
	inst1: component lpm_counter -- copied from wizard file
			GENERIC MAP (
				lpm_direction => "DOWN",
				lpm_port_updown => "PORT_UNUSED",
				lpm_type => "LPM_COUNTER",
				lpm_width => 24
			)
			PORT MAP (
				sload => I3,
				aclr => not reset,
				clock => clk,
				data => I0,--data => "000000000000000001100100",
				cnt_en => '1',
				q => I1
			);
	
	-- This counter multiplies the period of the main signal by 12.							   	 
	inst2: component lpm_counter  -- copied from wizard file
			GENERIC MAP (
				lpm_direction => "DOWN",
				lpm_port_updown => "PORT_UNUSED",
				lpm_type => "LPM_COUNTER",
				lpm_width => 4
			)
			PORT MAP (
				sload => I6,
				aclr => not reset,
				clock => clk,
				data => "1100", --data => "1011",
				cnt_en => I3,
				q => I4
			);
	
	-- This flip flop makes the square wave beat.
	inst3: component g27_lpm_ff2 port map (clock=>clk, aclr=>not reset, enable=>I6, q=>beat_gate);

end inside;