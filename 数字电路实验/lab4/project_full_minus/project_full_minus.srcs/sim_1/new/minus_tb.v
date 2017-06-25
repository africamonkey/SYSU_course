`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/04/10 18:40:45
// Design Name: 
// Module Name: minus_tb
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

module minus_tb(

    );
    reg a;
    reg b;
    reg cin;
    
    wire sum1, sum2, sum3;
    wire cout1, cout2, cout3;
    
    minus_1 uut1(.a(a), .b(b), .cin(cin), .sum(sum1), .cout(cout1));
    minus_2 uut2(.a(a), .b(b), .cin(cin), .sum(sum2), .cout(cout2));
    minus_3 uut3(.a(a), .b(b), .cin(cin), .sum(sum3), .cout(cout3));
    initial begin
        a = 0;
        b = 0;
        cin = 0;
        #2;
    end
    
    integer i, j;
    always begin
        for (i = 0; i < 8; i = i + 1) begin
            j = i;
            cin = j & 1;
            j = j >> 1;
            b = j & 1;
            j = j >> 1;
            a = j & 1;
            #2;
        end
    end

endmodule
