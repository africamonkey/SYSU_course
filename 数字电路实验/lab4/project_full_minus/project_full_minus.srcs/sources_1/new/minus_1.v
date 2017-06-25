`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/04/10 18:35:23
// Design Name: 
// Module Name: minus_1
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


module minus_1(
    input a,
    input b,
    input cin,
    output sum,
    output cout
    );
    wire s1, t1, t2, t3, na;
    xor x1(s1, a, b);
    xor x2(sum, s1, cin);
    not n1(na, a);
    and a1(t1, na, b);
    and a2(t2, na, cin);
    and a3(t3, b, cin);
    or o1(cout, t1, t2, t3);
endmodule
