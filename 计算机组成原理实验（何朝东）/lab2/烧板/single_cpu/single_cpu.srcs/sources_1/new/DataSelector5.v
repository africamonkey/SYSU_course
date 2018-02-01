`timescale 1ns / 1ps

module DataSelector5(
    input src,
    input [4:0] dataIn0,
    input [4:0] dataIn1,
    output [4:0] dataOut
    );
    assign dataOut[4:0] = (src == 0) ? dataIn0[4:0] : dataIn1[4:0];
endmodule
