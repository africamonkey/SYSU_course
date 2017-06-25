`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/04/23 23:53:14
// Design Name: 
// Module Name: alu
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module alu(
    input s2,
    input s1,
    input s0,
    input a,
    input b,
    input cin,
    output reg out1,
    output reg out2
    );
    always @ (s2 or s1 or s0 or a or b or cin) begin
        if (s2 == 0 && s1 == 0 && s0 == 0) 
        begin
            out1 = a & b;
            out2 = 0;
        end
        if (s2 == 0 && s1 == 0 && s0 == 1)
        begin
            out1 = a | b;
            out2 = 0;
        end
        if (s2 == 0 && s1 == 1 && s0 == 0)
        begin
            out1 = ~a;
            out2 = 0;
        end
        if (s2 == 0 && s1 == 1 && s0 == 1)
        begin
            out1 = ~b;
            out2 = 0;
        end
        if (s2 == 1 && s1 == 0 && s0 == 0)
        begin
            out1 = a ^ b;
            out2 = 0;
        end
        if (s2 == 1 && s1 == 0 && s0 == 1)
        begin
            out1 = a ^ b ^ cin;
            out2 = (cin & b) | (cin & a) | (b & a);
        end
        if (s2 == 1 && s1 == 1 && s0 == 0)
        begin
            out1 = a ^ b ^ cin;
            out2 = (cin & b) | (cin & (~a)) | (b & (~a)); 
        end
        if (s2 == 1 && s1 == 1 && s0 == 1)
        begin
            out1 = 0;
            out2 = 0;
        end
    end
endmodule

