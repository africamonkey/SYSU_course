`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/04/10 19:27:11
// Design Name: 
// Module Name: minus_2
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


module minus_2(
    input a,
    input b,
    input cin,
    output sum,
    output cout
    );
    wire s1, t1, t2, t3, na;
    assign s1 = a ^ b;
    assign sum = s1 ^ cin;
    assign na = ~a;
    assign t1 = na & b;
    assign t2 = na & cin;
    assign t3 = b & cin;
    assign cout = t1 | t2 | t3;
endmodule
