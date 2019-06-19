`timescale 1ns / 1ps

module main_sim(

    );
    reg clock;
    reg [1:0] SW_in;
    reg SW_reset;
    reg clk;
    
    main uut(
        .CLK(clock),
        .SW_in(SW_in),
        .SW_reset(SW_reset),
        .button(clk)
    );
    
    always #1 clock = ~clock;
    always #4000000 clk = ~clk;
    initial begin
        clock = 0;
        clk = 0;
        SW_in = 0;
        SW_reset = 0;
        #8000000;
        SW_reset = 1;
    end
endmodule
