`timescale 1ns / 1ps

module clockdiv(
    input wire CLK,
    output reg CLK2
    );
    parameter T = 20000;
    reg [19:0] count = 0;
    always @ (posedge CLK) begin
        count = count + 1;
        if (count >= T) begin
            count = 0;
            CLK2 = ~CLK2;
        end
    end
endmodule
