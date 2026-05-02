`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   02:19:16 03/11/2026
// Design Name:   bcd_converter_v1
// Module Name:   /home/ise/Downloads/Xilinx_Electronics_Project/test/bcd_converter_v1_tb.v
// Project Name:  test
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: bcd_converter_v1
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

`timescale 1ns / 1ps

module bcd_converter_v1_tb;

	reg [7:0] tb_binary;
	
	wire [3:0] tb_tens;
	wire [3:0] tb_ones;
	
	bcd_converter_v1 uut (
		.binary(tb_binary),
		.tens(tb_tens),
		.ones(tb_ones)
	);
	
	initial begin
		tb_binary = 8'd0;
		
		#100;
		
		tb_binary = 8'd57;
		#50;
		$display("Test 1: Input=%d, Tens=%d, Ones=%d", tb_binary, tb_tens, tb_ones);
		
		tb_binary = 8'd99;
		#50;
		$display("Test 1: Input=%d, Tens=%d, Ones=%d", tb_binary, tb_tens, tb_ones);
		
		#20;;
	end
endmodule
	
	
