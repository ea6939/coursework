---------------------------------
-- Copyright 2013
-- Loren Lugosch 260404057, loren.lugosch@mail.mcgill.ca
-- Lulan Shen 260449509
--
-- This circuit produces an envelope waveform.
-- 
-- Revision 1.0
---------------------------------

library ieee;
use ieee.std_logic_1164.all;

library lpm;
use lpm.lpm_components.all;

entity g27_Envelope is
	port ( RISE_RATE, FALL_RATE : in std_logic_vector(7 downto 0);
		  clk, reset : in std_logic; -- clk isn't 50 MHz, it's update_enable
		  GATE : in std_logic;
		  ENVELOPE : out std_logic_vector(7 downto 0));
end g27_Envelope;

architecture inside of g27_Envelope is

-- component declaration --
component I0_mux is
	port 
	(
		data0x		: IN STD_LOGIC_VECTOR (8 DOWNTO 0);
		data1x		: IN STD_LOGIC_VECTOR (8 DOWNTO 0);
		sel		: IN STD_LOGIC ;
		result		: OUT STD_LOGIC_VECTOR (8 DOWNTO 0)
	);
end component;
-- /component declaration --

signal ENVELOPE24, I3, I4 : std_logic_vector(23 downto 0);
signal I0, I1, I2, I5 : std_logic_vector(8 downto 0);

begin

mux1 : component I0_mux -- selects either 255 or 0
	PORT MAP (
		sel => not gate,
		data0x => "000000000",
		data1x => "011111111",
		result => I0
	);
	
mux2 : component I0_mux -- selects either rise or fall
	PORT MAP (
		sel => not gate,
		data0x => '0' & FALL_RATE,
		data1x => '0' & RISE_RATE,
		result => I2
	);

sub : lpm_add_sub -- copied from wizard
	GENERIC MAP (
		lpm_direction => "SUB",
		lpm_hint => "ONE_INPUT_IS_CONSTANT=NO,CIN_USED=NO",
		lpm_representation => "SIGNED",
		lpm_type => "LPM_ADD_SUB",
		lpm_width => 9
	)
	PORT MAP (
		dataa => I0,
		datab => I5, -- ENVELOPE
		result => I1
	);
	
mult : lpm_mult -- multiplier
	GENERIC MAP (
		lpm_hint => "MAXIMIZE_SPEED=5",
		lpm_representation => "SIGNED",
		lpm_type => "LPM_MULT",
		lpm_widtha => 9,
		lpm_widthb => 9,
		lpm_widthp => 24
	)
	PORT MAP (
		dataa => I1,
		datab => I2,
		result => I3
	);
	
add : lpm_add_sub
	GENERIC MAP (
		lpm_direction => "ADD",
		lpm_hint => "ONE_INPUT_IS_CONSTANT=NO,CIN_USED=NO",
		lpm_representation => "UNSIGNED",
		lpm_type => "LPM_ADD_SUB",
		lpm_width => 24
	)
	PORT MAP (
		dataa => I3,
		datab => ENVELOPE24,
		result => I4
	);
	
reg : lpm_ff -- stores ENVELOPE24 (copied from wizard), stores updated # if update HIGH
	GENERIC MAP (
		lpm_fftype => "DFF",
		lpm_type => "LPM_FF",
		lpm_width => 24
	)
	PORT MAP (
		aclr => not reset,-- change??
		clock => clk,
		data => I4,
		q => ENVELOPE24
	);
	
I5 <= '0' & ENVELOPE24(23 downto 16);
ENVELOPE <= I5(7 downto 0);

end inside;