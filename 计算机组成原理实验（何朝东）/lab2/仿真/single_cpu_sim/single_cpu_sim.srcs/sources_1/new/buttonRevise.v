`timescale 1ns / 1ps

module buttonRevise(
    input wire CLK,
    input wire buttonIn,
    output reg buttonOut
    );
    
    /*
    wire CLK2;
    clockdiv _clockdiv(
        .CLK(CLK),
        .CLK2(CLK2)
    );
    */
    
    reg [19:0] dat = 0;
    always @ (posedge CLK) begin
        dat[19:1] = dat[18:0];
        dat[0:0] = buttonIn;
        if (dat == 20'b11111_11111_11111_11111) begin
            buttonOut = 1;
        end else begin
            buttonOut = 0;
        end
    end
endmodule
