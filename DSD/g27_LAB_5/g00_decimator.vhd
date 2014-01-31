-- g00_decimator
--
-- 500:1 sampling rate decimator
-- assumes an input SR of 50 MHz and an output SR of 48KHz
-- Hogenauer CIC filter with N=3 stages, M=2, and downsampling factor of 1024
-- max wordlength is ceil[24+3*log_2(2*1024)] = 57bits
-- VHDL implementation adapted from the book "Digital Signal Processing with
-- Field Programmable Gate Arrays", by Uwe Meyer-Baese, Springer, 2000
--
-- Version 1.0
-- Designer: James Clark
-- March 6 2008

LIBRARY ieee;
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

ENTITY g00_decimator IS
	PORT
	(
		SR50MHz       : IN signed(23 downto 0);
		SR48KHz       : OUT signed(23 downto 0);
		clk, rst      : IN std_logic -- clk assumed to be 24MHz
	);
END g00_decimator;

ARCHITECTURE a OF g00_decimator IS
SUBTYPE word24 IS signed(23 downto 0);
SUBTYPE word57 IS signed(56 downto 0);
signal Rcount : integer range 0 to 1023;
signal x : word24;
signal sxtx : word57;
signal i0, i1, i2 : word57;
signal i2d1, i2d2, c3, c2, c1, c0 : word57;
signal c1d1, c1d2, c2d1, c2d2 : word57;

begin

sgnextend : process( x )
	begin
		sxtx(23 downto 0) <= x;
		for k in 56 downto 24 loop
			sxtx(k) <= x(23);
		end loop;
	end process sgnextend;
			
process(clk,rst)
	begin
		if rst='1' then
			Rcount <= 0; -- keeps track of the downsampling
		elsif clk='1' and clk'EVENT then
			x <= SR50MHz; 
			i0 <= i0 + sxtx;	-- integrator stage 1
			i1 <= i1 + i0;	-- integrator stage 2
			i2 <= i2 + i1;  -- integrator stage 3
			if Rcount = 1023 then
				Rcount <= 0;
				c0 <= i2;
				i2d1 <= c0;
				i2d2 <= i2d1;
				c1 <= c0 - i2d2; -- comb stage 1
				c1d1 <= c1;
				c1d2 <= c1d1;
				c2 <= c1 - c1d2; -- comb stage 2
				c2d1 <= c2;
				c2d2 <= c2d1;
				c3 <= c2 - c2d2; -- comb stage 3
			else
				Rcount <= Rcount + 1;
			end if; -- Rcount
		end if; -- if rst
	end process;		
	SR48KHz <= c3(56 downto 33);				
end a;	