`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/03 16:21:03
// Design Name: 
// Module Name: clkdiv
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


module clkdiv(
    input wire mclk,
    input wire clr,
    output wire clk190,
    output wire clk3
    );
    reg [26:0] q;
    always @ (posedge ~mclk or posedge clr) begin
        if (clr == 1)
            q <= 0;
        else
            q <= q + 1;
    end
    assign clk190 = q[18];
    assign clk3 = q[25]; 
endmodule
