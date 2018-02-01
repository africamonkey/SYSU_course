`timescale 1ns / 1ps

module ControlUnit(
    input [5:0] Op,
    input zero,
    input sign,
    output reg ALUSrcA,
    output reg ALUSrcB,
    output reg [1:0] PCSrc,
    output reg ExtSel,
    output reg RegWre,
    output reg RegDst,
    output reg [2:0] ALUOp,
    output reg RD,
    output reg WR,
    output reg DBDataSrc
    );
    always @ (Op or zero or sign) begin
        if (Op == 6'b000000) begin
            ALUSrcA = 0;
            ALUSrcB = 0;
            PCSrc = 0;
            ExtSel = 0;
            RegWre = 1;
            RegDst = 1;
            ALUOp = 3'b000;
            RD = 1;
            WR = 1;
            DBDataSrc = 0;
        end
        else
        if (Op == 6'b000001) begin
            ALUSrcA = 0;
            ALUSrcB = 1;
            PCSrc = 0;
            ExtSel = 1;
            RegWre = 1;
            RegDst = 0;
            ALUOp = 3'b000;
            RD = 1;
            WR = 1;
            DBDataSrc = 0;
        end
        else
        if (Op == 6'b000010) begin
            ALUSrcA = 0;
            ALUSrcB = 0;
            PCSrc = 0;
            ExtSel = 0;
            RegWre = 1;
            RegDst = 1;
            ALUOp = 3'b001;
            RD = 1;
            WR = 1;
            DBDataSrc = 0;
        end
        else
        if (Op == 6'b010000) begin
            ALUSrcA = 0;
            ALUSrcB = 1;
            PCSrc = 0;
            ExtSel = 0;
            RegWre = 1;
            RegDst = 0;
            ALUOp = 3'b011;
            RD = 1;
            WR = 1;
            DBDataSrc = 0;
        end
        else
        if (Op == 6'b010001) begin
            ALUSrcA = 0;
            ALUSrcB = 0;
            PCSrc = 0;
            ExtSel = 0;
            RegWre = 1;
            RegDst = 1;
            ALUOp = 3'b010;
            RD = 1;
            WR = 1;
            DBDataSrc = 0;
        end
        else
        if (Op == 6'b010010) begin
            ALUSrcA = 0;
            ALUSrcB = 0;
            PCSrc = 0;
            ExtSel = 0;
            RegWre = 1;
            RegDst = 1;
            ALUOp = 3'b011;
            RD = 1;
            WR = 1;
            DBDataSrc = 0;
        end
        else
        if (Op == 6'b011000) begin
            ALUSrcA = 1;
            ALUSrcB = 0;
            PCSrc = 0;
            ExtSel = 0;
            RegWre = 1;
            RegDst = 1;
            ALUOp = 3'b110;
            RD = 1;
            WR = 1;
            DBDataSrc = 0;
        end
        else
        if (Op == 6'b011100) begin
            ALUSrcA = 0;
            ALUSrcB = 0;
            PCSrc = 0;
            ExtSel = 0;
            RegWre = 1;
            RegDst = 1;
            ALUOp = 3'b101;
            RD = 1;
            WR = 1;
            DBDataSrc = 0;
        end
        else
        if (Op == 6'b100110) begin
            ALUSrcA = 0;
            ALUSrcB = 1;
            PCSrc = 0;
            ExtSel = 1;
            RegWre = 0;
            RegDst = 0;
            ALUOp = 3'b000;
            RD = 1;
            WR = 0;
            DBDataSrc = 0;
        end
        else
        if (Op == 6'b100111) begin
            ALUSrcA = 0;
            ALUSrcB = 1;
            PCSrc = 0;
            ExtSel = 1;
            RegWre = 1;
            RegDst = 0;
            ALUOp = 3'b000;
            RD = 0;
            WR = 1;
            DBDataSrc = 1;
        end
        else
        if (Op == 6'b110000) begin
            ALUSrcA = 0;
            ALUSrcB = 0;
            PCSrc = zero ? 1 : 0;
            ExtSel = 1;
            RegWre = 0;
            RegDst = 0;
            ALUOp = 3'b001;
            RD = 1;
            WR = 1;
            DBDataSrc = 0;
        end
        else
        if (Op == 6'b110001) begin
            ALUSrcA = 0;
            ALUSrcB = 0;
            PCSrc = zero ? 0 : 1;
            ExtSel = 1;
            RegWre = 0;
            RegDst = 0;
            ALUOp = 3'b001;
            RD = 1;
            WR = 1;
            DBDataSrc = 0;
        end
        else
        if (Op == 6'b110010) begin
            ALUSrcA = 0;
            ALUSrcB = 0;
            PCSrc = (!sign && !zero) ? 1 : 0;
            ExtSel = 1;
            RegWre = 0;
            RegDst = 0;
            ALUOp = 3'b001;
            RD = 1;
            WR = 1;
            DBDataSrc = 0;
        end
        else
        if (Op == 6'b111000) begin
            PCSrc = 2;
        end
        else
        if (Op == 6'b111111) begin
            PCSrc = 3;
        end
    end
endmodule
