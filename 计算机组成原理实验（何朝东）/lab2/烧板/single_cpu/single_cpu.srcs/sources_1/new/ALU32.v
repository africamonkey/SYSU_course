`timescale 1ns / 1ps

module ALU32(
    input [2:0] ALUopcode,
    input [31:0] rega,
    input [31:0] regb,
    output reg [31:0] result,
    output zero,
    output sign
);
    reg [4:0] tmp;
    assign zero = (result==0)?1:0;
    assign sign = result[31:31];
    always @( ALUopcode or rega or regb ) begin
        case (ALUopcode)
            3'b000 : result = rega + regb;
            3'b001 : result = rega - regb;
            3'b010 : result = rega & regb;
            3'b011 : result = rega | regb;
            3'b100 : result = (rega < regb)?1:0; // 不带符号比较
            3'b101 : begin // 带符号比较
                if (rega<regb &&(( rega[31] == 0 && regb[31]==0) ||
                    (rega[31] == 1 && regb[31]==1))) result = 1;
                else if (rega[31] == 0 && regb[31]==1) result = 0;
                else if ( rega[31] == 1 && regb[31]==0) result = 1;
                else result = 0;
            end
            3'b110 : begin
                tmp = rega[4:0];
                result = regb << tmp;
            end
            default : begin
                result = 8'h00000000;
                $display (" no match");
            end
        endcase
    end
endmodule