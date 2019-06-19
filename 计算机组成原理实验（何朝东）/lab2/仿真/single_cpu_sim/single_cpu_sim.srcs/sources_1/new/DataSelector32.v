`timescale 1ns / 1ps

module DataSelector32(
    input src,
    input [31:0] dataIn0,
    input [31:0] dataIn1,
    output [31:0] dataOut
    );
    assign dataOut[31:0] = (src == 0) ? dataIn0[31:0] : dataIn1[31:0];
endmodule
