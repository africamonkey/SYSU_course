`timescale 1ns / 1ps

module main(
    input CLK,
    input [1:0] SW_in,
    input SW_reset,
    input button,
    output [6:0] a_to_g,
    output [3:0] an,
    output dp
    );
    reg [15:0] x;
    
    sevenseg light(
        .CLK(CLK),
        .x(x),
        .a_to_g(a_to_g),
        .an(an),
        .dp(dp)
    );
    
    wire clk;
    buttonRevise buttonRevise(
        .CLK(CLK),
        .buttonIn(button),
        .buttonOut(clk)
    );
    
    wire [5:0] Op;
    wire zero, sign;
    wire ALUSrcA, ALUSrcB;
    wire [1:0] PCSrc;
    wire ExtSel, RegWre, RegDst;
    wire [2:0] ALUOp;
    wire RD, WR, DBDataSrc;
    wire [31:0] rega, regb;
    wire [31:0] result;
    wire [31:0] PCIn;
    wire [31:0] PCOut;
    wire [25:0] long_jump;
    wire [31:0] Dataout;
    wire [31:0] RAMDataout;
    wire [4:0] ReadReg1;
    wire [4:0] ReadReg2;
    wire [4:0] WriteReg;
    wire [31:0] WriteData;
    wire [31:0] ReadData1;
    wire [31:0] ReadData2;
    wire [4:0] rd;
    wire [31:0] sa;
    wire [15:0] ImIn;
    wire [31:0] ImOut;
    assign Op = Dataout[31:26];
    assign ReadReg1 = Dataout[25:21];
    assign ReadReg2 = Dataout[20:16];
    assign rd = Dataout[15:11];
    assign sa[31:5] = 0;
    assign sa[4:0] = Dataout[10:6];
    assign ImIn[15:0] = Dataout[15:0];
    assign long_jump[25:0] = Dataout[25:0];
    
    always @ (SW_in) begin
        if (SW_in == 0) begin
            x[15:8] = PCOut[7:0];
            x[7:0] = PCIn[7:0];
        end
        else
        if (SW_in == 1) begin
            x[15:13] = 0;
            x[12:8] = ReadReg1[4:0];
            x[7:0] = ReadData1[7:0];
        end
        else
        if (SW_in == 2) begin
            x[15:13] = 0;
            x[12:8] = ReadReg2[4:0];
            x[7:0] = ReadData2[7:0];
        end
        else
        if (SW_in == 3) begin
            x[15:8] = result[7:0];
            x[7:0] = WriteData[7:0];
        end
    end
        
    DataSelector5 WriteRegisterSelector(
        .src(RegDst),
        .dataIn0(ReadReg2),
        .dataIn1(rd),
        .dataOut(WriteReg)
    );
    
    DataSelector32 ALUSelectorA(
        .src(ALUSrcA),
        .dataIn0(ReadData1),
        .dataIn1(sa),
        .dataOut(rega)
    );
    
    DataSelector32 ALUSelectorB(
        .src(ALUSrcB),
        .dataIn0(ReadData2),
        .dataIn1(ImOut),
        .dataOut(regb)
    );
    
    BitExtend BitExtend(
        .ExtSel(ExtSel),
        .dataIn(ImIn),
        .dataOut(ImOut)
    );
    
    PC PC(
        .clk(clk),
        .reset(SW_reset),
        .PCIn(PCIn),
        .PCOut(PCOut)
    );
    
    PCSelector PCSelector(
        .PCIn(PCOut),
        .short_jump(ImOut),
        .long_jump(long_jump),
        .PCSrc(PCSrc),
        .PCOut(PCIn)
    );
    
    wire reset_rd;
    assign reset_rd = ~SW_reset;
    ROM ROM(
        .rd(reset_rd),
        .addr(PCOut),
        .dataOut(Dataout)
    );
    
    RegFile RegFile(
        .CLK(clk),
        .RST(SW_reset),
        .RegWre(RegWre),
        .ReadReg1(ReadReg1),
        .ReadReg2(ReadReg2),
        .WriteReg(WriteReg),
        .WriteData(WriteData),
        .ReadData1(ReadData1),
        .ReadData2(ReadData2)
    );
    
    RAM RAM(
        .clk(clk),
        .address(result),
        .writeData(ReadData2),
        .nRD(RD),
        .nWR(WR),
        .Dataout(RAMDataout)
    );
    
    ALU32 ALU(
        .ALUopcode(ALUOp),
        .rega(rega),
        .regb(regb),
        .result(result),
        .zero(zero),
        .sign(sign)
    );
    
    ControlUnit ControlUnit(
        .Op(Op),
        .zero(zero),
        .sign(sign),
        .ALUSrcA(ALUSrcA),
        .ALUSrcB(ALUSrcB),
        .PCSrc(PCSrc),
        .ExtSel(ExtSel),
        .RegWre(RegWre),
        .RegDst(RegDst),
        .ALUOp(ALUOp),
        .RD(RD),
        .WR(WR),
        .DBDataSrc(DBDataSrc)
    );
    
    DataSelector32 DBDataSelector(
        .src(DBDataSrc),
        .dataIn0(result),
        .dataIn1(RAMDataout),
        .dataOut(WriteData)
    );
endmodule
