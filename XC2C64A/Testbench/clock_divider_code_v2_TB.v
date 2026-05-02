`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   02:25:14 03/09/2026
// Design Name:   clock_divider_code_v1
// Module Name:   /home/ise/Downloads/Xilinx_Electronics_Project/test/clock_divider_code_v1_TB.v
// Project Name:  test
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: clock_divider_code_v1
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module clock_divider_code_v1_TB;

	// Inputs
	reg clk;
	reg reset;

	// Bidirs
	wire clk_d;
	wire clk_sampling;
	wire clk_display;

	// Instantiate the Unit Under Test (UUT)
	clock_divider_code_v1 uut (
		.clk(clk), 
		.reset(reset), 
		.clk_d(clk_d),
		.clk_sampling(clk_sampling),
		.clk_display(clk_display)
	);

	initial begin
		// Initialize Inputs
		clk = 1;
		forever #271.27 clk<=~clk;
	end
	
	initial begin
		reset = 1;
		#40;
		reset = 0;
		#100000;
	end;
      
endmodule

