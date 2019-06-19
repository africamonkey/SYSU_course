`timescale 1ns / 1ps

module sevenseg(
    input wire CLK,
    input wire[15:0] x,
    output reg[6:0] a_to_g,
    output reg[3:0] an,
    output wire dp
    );

    reg [3:0] digit;
    reg [1:0] s;
    assign dp = 1;
    wire CLK2;
    
    clockdiv _clockdiv(
        .CLK(CLK),
        .CLK2(CLK2)
    );
    always @ (posedge CLK2) begin
        s = s + 1;
    end

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
            10: a_to_g = 7'b0001000;
            11: a_to_g = 7'b1100000;
            12: a_to_g = 7'b0110001;
            13: a_to_g = 7'b1000010;
            14: a_to_g = 7'b0110000;
            15: a_to_g = 7'b0111000;
        endcase
    end
 
endmodule
