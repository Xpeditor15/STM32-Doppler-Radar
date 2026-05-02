-- Vhdl test bench created from schematic /home/ise/kx_group/shift_register.sch - Mon Mar  9 02:14:26 2026
--
-- Notes: 
-- 1) This testbench template has been automatically generated using types
-- std_logic and std_logic_vector for the ports of the unit under test.
-- Xilinx recommends that these types always be used for the top-level
-- I/O of a design in order to guarantee that the testbench will bind
-- correctly to the timing (post-route) simulation model.
-- 2) To use this template as your testbench, change the filename to any
-- name of your choice with the extension .vhd, and use the "Source->Add"
-- menu in Project Navigator to import the testbench. Then
-- edit the user defined section below, adding code to generate the 
-- stimulus for your design.
--
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY shift_register_sch_tb IS
END shift_register_sch_tb;
ARCHITECTURE behavioral OF shift_register_sch_tb IS 

COMPONENT shift_register
   PORT(	
			D             :In std_logic_vector(7 downto 0);
			Clock         :In std_logic;
			Clear         :In std_logic;
			CE            :In std_logic;
			Q             :Out std_logic_vector(7 downto 0)
			);
   END COMPONENT;

	SIGNAL D             :std_logic_vector(7 downto 0) := (others => '0');
	SIGNAL Clock         :std_logic :='0';
	SIGNAL Clear         :std_logic :='0';
	SIGNAL CE            :std_logic :='1';
	SIGNAL Q             :std_logic_vector(7 downto 0);


BEGIN

   UUT: shift_register
	PORT MAP(
		D              => D,
		Clock          => Clock,
		Clear          => Clear,
		CE             => CE,
		Q              => Q
   );

-- *** Test Bench - User Defined Section ***
   clk_process : PROCESS
   BEGIN
		WHILE TRUE LOOP
			Clock <= '0';
			WAIT FOR 5 ns;
			Clock <= '1';
			WAIT FOR 5 ns;
		END LOOP;
	END PROCESS;
	
	tb : PROCESS
	BEGIN
	--clear register
	Clear <= '1';
	D     <= (others => '0');
	WAIT FOR 12 ns;
	
	Clear <= '0';
	
	--input sequence 
	WAIT FOR 3 ns;
	D      <= "00000001";
	WAIT FOR 100 ns;
	
	D       <="00000000";
	WAIT FOR 100 ns;
	
	D       <= "00000001";
	WAIT FOR 100 ns;
	
	D       <= "00000011";
	WAIT FOR 100 ns;
	
	--extra time to observe
	D       <= (others =>'0');
	WAIT FOR 40 ns;
	
      WAIT; -- will wait forever
   END PROCESS;
-- *** End Test Bench - User Defined Section ***

END behavioral;
