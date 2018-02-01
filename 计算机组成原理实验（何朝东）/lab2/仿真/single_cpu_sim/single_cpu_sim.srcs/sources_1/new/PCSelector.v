`timescale 1ns / 1ps

module PCSelector(
    input [31:0] PCIn,
    input [31:0] short_jump,
    input [25:0] long_jump,
    input [1:0] PCSrc,
    output reg [31:0] PCOut
    );
    always @ (PCIn or short_jump or long_jump or PCSrc) begin
        if (PCSrc == 0) begin
            PCOut = PCIn + 4;
        end else
        if (PCSrc == 1) begin
            PCOut = PCIn + 4 + (short_jump << 2);
        end else
        if (PCSrc == 2) begin
            PCOut[31:28] = PCIn[31:28];
            PCOut[27:2] = long_jump[25:0];
            PCOut[1:0] = 2'b00;
        end else begin
            PCOut = PCIn;
        end
    end
endmodule
