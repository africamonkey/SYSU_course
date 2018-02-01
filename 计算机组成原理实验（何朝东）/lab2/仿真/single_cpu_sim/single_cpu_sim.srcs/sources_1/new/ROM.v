`timescale 1ns / 1ps

module ROM(
    input rd,
    input [31:0] addr,
    output reg [31:0] dataOut
    );
    
    reg [7:0] rom[99:0];
    initial begin
        $readmemb("C:/Users/marse/Documents/digit/single_cpu/rom_data.txt", rom);
    end
    always @ (rd or addr) begin
        if (rd == 0) begin
            dataOut[31:24] = rom[addr];
            dataOut[23:16] = rom[addr + 1];
            dataOut[15:8] = rom[addr + 2];
            dataOut[7:0] = rom[addr + 3];
        end
    end
endmodule
