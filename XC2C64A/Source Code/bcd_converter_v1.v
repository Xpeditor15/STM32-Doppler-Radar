`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    02:14:44 03/11/2026 
// Design Name: 
// Module Name:    bcd_converter_v1 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module bcd_converter_v1(
    input [7:0] binary,
    output reg [3:0] tens,
    output reg [3:0] ones
    );

	integer i;
	always @(*) begin // always trigger
		tens = 4'd0; // define both tens and ones as 0000
		ones = 4'd0;
		
		for (i = 7; i >= 0; i = i - 1) begin // starts iterating on the LSB of the binary value
			if (tens >= 5) tens = tens + 3;
			if (ones >= 5) ones = ones + 3;
			
			tens = {tens[2:0], ones[3]};
			ones = {ones[2:0], binary[i]};
		end
	end


endmodule
