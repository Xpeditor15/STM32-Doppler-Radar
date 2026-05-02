`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   04:01:37 03/10/2026
// Design Name:   state_machine_v1
// Module Name:   /home/ise/Downloads/Xilinx_Electronics_Project/test/state_machine_v1_tb.v
// Project Name:  test
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: state_machine_v1
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module state_machine_v2_tb;

	// Inputs
	reg reset;
	reg clk;
	reg rx_serial;

	// Outputs
	// wire load;
	// wire busy;
	//wire [7:0] final_output;
	wire [6:0] display_output;
	wire anode_tens;
	wire anode_ones;

	// Instantiate the Unit Under Test (UUT)
	state_machine_v2 uut (
		.reset(reset), 
		.clk(clk), 
		.rx_serial(rx_serial), 
		//.load(load), 
		//.busy(busy),
		//.final_output(final_output),
		.display_output(display_output),
		.anode_tens(anode_tens),
		.anode_ones(anode_ones)
	);
	
	initial begin
    clk = 0;          // 1. Give it a starting value!
    forever #271 clk <= ~clk; // 2. Keep it looping forever
	end

	initial begin
		// Initialize Inputs
		reset = 1;
		rx_serial = 1; // IDLE is high

		// Wait 100 ns for global reset to finish
		#1000000;
		reset = 0;
		
		#8000000;
		
		rx_serial = 0; #17360; // start bit
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;S
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360; // stop bit
		
		#8000000;
		rx_serial = 0; #17360; // start bit
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360;
		
		#8000000;
		rx_serial = 0; #17360; // start bit
		rx_serial = 0; #17360;
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360;
		
		#8000000;
		rx_serial = 0; #17360; // start bit
		rx_serial = 1; #17360;
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360;
		
		#8000000;
		rx_serial = 0; #17360; // start bit
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360;
		
		#8000000;
		rx_serial = 0; #17360; // start bit
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360;
		
		#8000000;
		rx_serial = 0; #17360; // start bit
		rx_serial = 0; #17360;
		rx_serial = 1; #17360;
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360;
		
		#8000000;
		rx_serial = 0; #17360; // start bit
		rx_serial = 1; #17360;
		rx_serial = 1; #17360;
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360;
		
		#8000000;
		rx_serial = 0; #17360; // start bit
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360;
		
		#8000000;
		rx_serial = 0; #17360; // start bit
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360;
		
		#8000000;
		rx_serial = 0; #17360; // start bit
		rx_serial = 0; #17360; // UART 10
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360;
		
		#8000000;
		rx_serial = 0; #17360; // start bit
		rx_serial = 1; #17360; // UART 21
		rx_serial = 0; #17360;
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360;
		
		#8000000;
		rx_serial = 0; #17360; // start bit
		rx_serial = 1; #17360; // UART 67
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 0; #17360;
		rx_serial = 1; #17360;
		rx_serial = 0; #17360;
		
		rx_serial = 1; #17360;
		
		#500000;
		
        
		// Add stimulus here

	end
      
		
endmodule

