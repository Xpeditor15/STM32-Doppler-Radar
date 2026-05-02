`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    07:25:25 03/15/2026 
// Design Name: 
// Module Name:    clock_divider_code_v2 
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
module clock_divider_code_v2(
    input clk,
    input reset,
    output clk_d,
	 output clk_sampling,
	 output clk_display
    );
	 
reg [13:0] div_cnt;

always@(posedge clk or posedge reset)
begin
if(reset)
div_cnt <=14'd0;
else
div_cnt<= div_cnt + 1;
end

assign clk_d = div_cnt[4];
assign clk_sampling = div_cnt[0];
assign clk_display = div_cnt[13];


endmodule