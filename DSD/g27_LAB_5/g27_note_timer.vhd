---------------------------------
-- Copyright 2013
-- Loren Lugosch 260404057, loren.lugosch@mail.mcgill.ca
-- Lulan Shen 260449509
--
-- This circuit switches notes for the appropriate amount of time.
-- 
-- Revision 1.0
---------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity g27_note_timer is
	port ( clk, reset: in std_logic;
		   note_duration: in std_logic_vector (2 downto 0);
		   triplet: in std_logic;
		   tempo_enable: in std_logic;
		   GATE: out std_logic);
end g27_note_timer;

architecture inside of g27_note_timer is
	signal I1: std_logic_vector (3 downto 0);
	signal number_of_pulses: std_logic_vector(8 downto 0);
	signal count: integer range 0 to 384;
	
	begin
		I1 <= note_duration & triplet;
		with I1 select
			-- triplet = 0
			number_of_pulses <= "000000011" when "0000",--note_duration = 0 
								"000000110" when "0010",--1
								"000001100" when "0100",--2
								"000011000" when "0110",
								"000110000" when "1000",
								"001100000" when "1010",
								"011000000" when "1100",
								"110000000" when "1110",
			--triplet =1
								"000000010" when "0001",
								"000000100" when "0011",
								"000001000" when "0101",
								"000010000" when "0111",
								"000100000" when "1001",
								"001000000" when "1011",
								"010000000" when "1101",
								"100000000" when others;
								
	process (clk, reset)
		begin
			--if reset = '1' then
			if reset = '0' then --active low
				count <= 0;
				--GATE <= '1';
			
			elsif clk = '1' and clk'event then
				if count = 0 then
					count <= to_integer(unsigned(number_of_pulses));
					GATE <= '1';
				else
				
					if number_of_pulses = "000000011" then
						if tempo_enable = '1' and count > 2 then	
								count <= count - 1;
								GATE <= '1';
						elsif tempo_enable = '1' then
								count <= count - 1;
								GATE <= '0';
						end if;
						
					elsif number_of_pulses = "000000010" then
						if tempo_enable = '1' and count = 1 then	
								count <= count - 1;
								GATE <= '1';
						elsif tempo_enable = '1' then
								count <= count - 1;
								GATE <= '0';
						end if;
							
					else -- number of pulses not 3
						if tempo_enable = '1' and count > (to_integer(unsigned(number_of_pulses))/ 2) then	
								count <= count - 1;
								GATE <= '1';
						elsif tempo_enable = '1' then
								count <= count - 1;
								GATE <= '0';
						end if;
					end if;
				end if;
			end if;
		end process;
	end inside;
					
			
			
		
