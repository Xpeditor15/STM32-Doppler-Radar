LIBRARY ieee;
USE ieee.std_logic_1164.ALL;

ENTITY bcd_7segment_tb IS
END bcd_7segment_tb;

ARCHITECTURE behavior OF bcd_7segment_tb IS 

    -- Component Declaration
    COMPONENT bcd_7segment
    PORT(
			A : IN  std_logic;
         B : IN  std_logic;
         C : IN  std_logic;
         D : IN  std_logic;
         a_out : OUT std_logic;
         b_out : OUT std_logic;
         c_out : OUT std_logic;
         d_out : OUT std_logic;
         e_out : OUT std_logic;
         f_out : OUT std_logic;
         g_out : OUT std_logic
        );
    END COMPONENT;

   --Inputs
   signal A : std_logic := '0';
   signal B : std_logic := '0';
   signal C : std_logic := '0';
   signal D : std_logic := '0';

	--Outputs
   signal a_out : std_logic;
   signal b_out : std_logic;
   signal c_out : std_logic;
   signal d_out : std_logic;
   signal e_out : std_logic;
   signal f_out : std_logic;
   signal g_out : std_logic;
 
BEGIN

	-- Instantiate the Unit Under Test (UUT)
   uut: bcd_7segment PORT MAP (
          A => A, B => B, C => C, D => D,
          a_out => a_out, b_out => b_out, c_out => c_out,
          d_out => d_out, e_out => e_out, f_out => f_out, g_out => g_out
        );

   -- Stimulus process
   stim_proc: process
   begin		
      -- Initial wait time
      wait for 100 ns;	

      report "Starting Step-by-Step Simulation" severity note;
		
		wait for 10 ns;

      -- 1 (0001)
      A <= '0'; B <= '0'; C <= '0'; D <= '1';
      wait for 10 ns;

      -- 2 (0010)
      A <= '0'; B <= '0'; C <= '1'; D <= '0';
      wait for 10 ns;

      -- 3 (0011)
      A <= '0'; B <= '0'; C <= '1'; D <= '1';
      wait for 10 ns;
		
		-- 4 (0100)
      A <= '0'; B <= '1'; C <= '0'; D <= '0';
      wait for 10 ns;

      -- 5 (0101)
      A <= '0'; B <= '1'; C <= '0'; D <= '1';
      wait for 10 ns;

      -- 6 (0110)
      A <= '0'; B <= '1'; C <= '1'; D <= '0';
      wait for 10 ns;

      -- 7 (0111)
      A <= '0'; B <= '1'; C <= '1'; D <= '1';
      wait for 10 ns;

      -- 8 (1000)
      A <= '1'; B <= '0'; C <= '0'; D <= '0';
      wait for 10 ns;
		
		-- 9 (1001)
      A <= '1'; B <= '0'; C <= '0'; D <= '1';
      wait for 10 ns;

      report "Simulation Completed" severity note;
      wait; -- Stop simulation
   end process;

END;