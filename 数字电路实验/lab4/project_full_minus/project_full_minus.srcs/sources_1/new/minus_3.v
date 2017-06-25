`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/04/10 19:35:50
// Design Name: 
// Module Name: minus_3
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


module minus_3(
    input a,
    input b,
    input cin,
    output sum,
    output cout
    );
    reg sum;
    reg cout;
    always @ (a or b or cin) begin
        sum = a ^ b ^ cin;
        cout = (~a & b) | (~a & cin) | (b & cin);
    end
endmodule
