`timescale 1ns / 1ps

module BitExtend(
    input ExtSel,
    input [15:0] dataIn,
    output [31:0] dataOut
    );
    assign dataOut[15:0] = dataIn[15:0];
    assign dataOut[31:16] = (ExtSel && dataIn[15]) ? 16'b1111111111111111 : 16'b0000000000000000; 
endmodule
