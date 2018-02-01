`timescale 1ns / 1ps

module PC(
    input clk,
    input reset,
    input [31:0] PCIn,
    output reg [31:0] PCOut
    );
    always @ (posedge clk) begin
        PCOut[31:0] = reset == 0 ? 8'h00000000 : PCIn[31:0];
    end
endmodule
