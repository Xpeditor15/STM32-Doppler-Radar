`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    06:54:47 03/15/2026 
// Design Name: 
// Module Name:    state_machine_v2
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
module state_machine_v2(
    input reset,
    input clk,
    input rx_serial, // receives the UART signal
    //output reg load, // goes high when it has read all 8 bits from UART
    //output reg busy, // goes high when it is receiving the data
	 //output wire [7:0] final_output,
	 output wire [6:0] display_output,
	 output wire anode_tens,
	 output wire anode_ones
    );

wire CLK_D;
wire CLK_SAMP;
wire CLK_DISPLAY;

wire reset = 1'b0;

reg CLK_EN;
wire [7:0] raw_parallel_data;

wire [7:0] final_output;

wire [7:0] raw_binary;
wire [3:0] msb_output;
wire [3:0] lsb_output;
wire [3:0] display_input;

reg load; // Create the register internally since you removed it from the outputs

reg SELECT; // if 1, show tens; if 0, show ones

wire [6:0] seg_data;
	 
clock_divider_code_v2 clock_div (
	.clk(clk),
   .reset(reset),
   .clk_d(CLK_D),
	.clk_sampling(CLK_SAMP),
	.clk_display(CLK_DISPLAY)
);


shift_register_1 shift_regis_reg (
	.Serial_Data_In(rx_serial),
	.CE(CLK_EN),
	.Clock(CLK_SAMP),
	.Clear(reset),
	.Q(raw_parallel_data)
);
	
	 
shift_register storage_latch (
	.D(raw_parallel_data),
	.CE(load),
	.Clock(CLK_SAMP),
	.Clear(reset),
	.Q(final_output)
);

bcd_converter_v1 bcd_converter (
	.binary(raw_binary),
	.tens(msb_output),
	.ones(lsb_output)
);

bcd_7segment display (
	.A(display_input[3]),
	.B(display_input[2]),
	.C(display_input[1]),
	.D(display_input[0]),
	.a_out(seg_data[6]),
	.b_out(seg_data[5]),
	.c_out(seg_data[4]),
	.d_out(seg_data[3]),
	.e_out(seg_data[2]),
	.f_out(seg_data[1]),
	.g_out(seg_data[0])
);

reg [1:0] currentState; // keeps track of the current state of the machine
reg [3:0] tickPos; // keeps track of which tick of 16x oversampling the device is at
reg [3:0] bitPos; // keeps track of which of the 10 bits the device is at (start bit, 8-bit data transmission, stop bit)

parameter IDLE = 2'b00;
parameter START = 2'b01;
parameter TRANS = 2'b11;
parameter STOP = 2'b10;

//always @(posedge reset or posedge CLK_DISPLAY) begin
	//if (reset) begin
		//SELECT <= 1'b0;
		//anode_tens <= 1'b0;
		//anode_ones <= 1'b1;
		
		//display_input <= 4'b0000;
		//display_output <= 7'b1111111;
	//end else begin
		//SELECT <= ~SELECT;
		//anode_tens <= ~SELECT;
		//anode_ones <= SELECT;
		
		//display_input <= (~SELECT) ? msb_output : lsb_output;
		//display_output <= ~seg_data;
	//end
//end
	
always @(posedge reset or posedge CLK_DISPLAY) begin
	if (reset) begin
		SELECT <= 1'b0;
	end else begin
		SELECT <= ~SELECT;
	end
end

	

always @(posedge reset or posedge CLK_SAMP) begin // only starts if it detects a reset or positive edge on the clock
	if (reset) begin
		currentState <= IDLE;
		CLK_EN <= 1'b0;
		tickPos <= 4'd0; // resets the tickPos and bitPos to initial value
		bitPos <= 4'd0;
		load <= 1'b0; // goes low as it has not received anything
		//busy <= 1'b0; // resets to low

		//raw_parallel_data = 
		//final_output = <= 8'd0;
	end else begin
		case (currentState) // switch case like in C++
			IDLE: begin
				CLK_EN <= 1'b0;
				load <= 1'b0;
				//busy <= 1'b0; // nothing is received from UART
				bitPos <= 4'd0;
				tickPos <= 4'd0; // new
				if (rx_serial == 1'b0) begin
					currentState <= START;
					tickPos <= 4'd0; // resets again and start counting from zero
				end
			end
			START: begin
				//busy <= 1'b1; // indicate that it is starting to receive bits 
				if (tickPos == 4'd7) begin // if there are already  ticks detected
					if (rx_serial == 1'b0) begin // checks if the 8th bit is still 0
						currentState <= TRANS;
						tickPos <= 4'd0;
						bitPos <= 4'd0;
					end else begin
						currentState <= IDLE; // no 8 consecutive 0 ticks detected
					end
				end else begin
					tickPos <= tickPos + 4'd1; // increment 
				end
			end
			TRANS: begin
				if (tickPos == 4'd15) begin // one whole data bit has completed
					tickPos <= 4'd0;
					CLK_EN <= 1'b1;
					if (bitPos == 4'd7) begin // all 8 data bits has completed
						currentState <= STOP;
					end else begin
						bitPos <= bitPos + 4'd1; // continue to next bit
					end
				end else begin
					CLK_EN <= 1'b0;
					tickPos <= tickPos + 4'd1; // continue to next tick
				end
			end
			STOP: begin
				CLK_EN <= 1'b0;
				if (tickPos == 4'd15) begin
					load <= 1'b1; // signal that the data is received successfully
					currentState <= IDLE;
				end else begin
					tickPos <= tickPos + 4'd1;
				end
			end
		endcase
	end
end

assign raw_binary = {final_output[0], final_output[1], final_output[2], final_output[3], final_output[4], final_output[5], final_output[6], final_output[7]};
assign anode_tens = ~SELECT;
assign anode_ones = SELECT;
assign display_input = (~SELECT) ? msb_output : lsb_output;
assign display_output = ~seg_data;

endmodule
