`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2017/05/02 23:13:55
// Design Name: 
// Module Name: sevenseg
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// // Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sevenseg(
    input wire CLK,
    output reg[6:0] a_to_g,
    output reg [3:0] an,
    output wire dp
    );
    
    reg [15:0] x = 'hFFFF;
    reg [39:0] number = 'h16337222FF;
    reg [1:0] s;
    reg[3:0] digit;
    assign dp = 1;
    reg [19:0] count = 0;
    reg [32:0] cnt = 0;
    parameter T1MS = 50000;
    parameter T2MS = 100000000;
    
    always @ (posedge CLK) begin
        case (s)
            0: begin digit = x[3:0]; an = 'b1110; end
            1: begin digit = x[7:4]; an = 'b1101; end
            2: begin digit = x[11:8]; an = 'b1011; end
            3: begin digit = x[15:12]; an = 'b0111; end
            default: digit = x[3:0];
        endcase
        case (digit)
            0: a_to_g = 7'b0000001;
            1: a_to_g = 7'b1001111;
            2: a_to_g = 7'b0010010;
            3: a_to_g = 7'b0000110;
            4: a_to_g = 7'b1001100;
            5: a_to_g = 7'b0100100;
            6: a_to_g = 7'b0100000;
            7: a_to_g = 7'b0001111;
            8: a_to_g = 7'b0000000;
            9: a_to_g = 7'b0000100;
            default: a_to_g = 7'b1111111;
        endcase
    end
    
    always @ (posedge CLK) begin
        count = count + 1;
        if (count == T1MS) begin
            count = 0;
            s = s + 1;
        end
    end
    
    always @ (posedge CLK) begin
        cnt = cnt + 1;
        if (cnt == T2MS) begin
            cnt = 0;
            number[39:4] <= number[35:0];
            number[3:0] <= number[39:36];
            x[15:0] = number[15:0];
        end
    end
endmodule