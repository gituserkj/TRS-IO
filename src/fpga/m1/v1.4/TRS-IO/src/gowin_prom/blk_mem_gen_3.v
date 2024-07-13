//Copyright (C)2014-2023 Gowin Semiconductor Corporation.
//All rights reserved.
//File Title: IP file
//GOWIN Version: V1.9.9 Beta-4 Education
//Part Number: GW1NR-LV9QN88PC6/I5
//Device: GW1NR-9
//Device Version: C
//Created Time: Wed Mar 20 07:12:00 2024

module blk_mem_gen_3 (dout, clk, oce, ce, reset, ad);

output [5:0] dout;
input clk;
input oce;
input ce;
input reset;
input [9:0] ad;

wire [25:0] prom_inst_0_dout_w;
wire gw_gnd;

assign gw_gnd = 1'b0;

pROM prom_inst_0 (
    .DO({prom_inst_0_dout_w[25:0],dout[5:0]}),
    .CLK(clk),
    .OCE(oce),
    .CE(ce),
    .RESET(reset),
    .AD({gw_gnd,ad[9:0],gw_gnd,gw_gnd,gw_gnd})
);

defparam prom_inst_0.READ_MODE = 1'b1;
defparam prom_inst_0.BIT_WIDTH = 8;
defparam prom_inst_0.RESET_MODE = "SYNC";
defparam prom_inst_0.INIT_RAM_00 = 256'h000E11101010110E001E09090E09091E0011111F11110A04000E15150D01110E;
defparam prom_inst_0.INIT_RAM_01 = 256'h000F11111310100F001010101C10101F001F10101C10101F001E09090909091E;
defparam prom_inst_0.INIT_RAM_02 = 256'h0011121418141211000E110101010101000E04040404040E001111111F111111;
defparam prom_inst_0.INIT_RAM_03 = 256'h000E11111111110E00111111131519110011111115151B11001F101010101010;
defparam prom_inst_0.INIT_RAM_04 = 256'h000E11010E10110E001112141E11111E000D12151111110E001010101E11111E;
defparam prom_inst_0.INIT_RAM_05 = 256'h00111B15111111110004040A0A111111000E111111111111000404040404041F;
defparam prom_inst_0.INIT_RAM_06 = 256'h0004040404150E04001F10080402011F00040404040A11110011110A040A1111;
defparam prom_inst_0.INIT_RAM_07 = 256'h001F000000000000000004021F020400000004081F08040000040E1504040404;
defparam prom_inst_0.INIT_RAM_08 = 256'h000A0A1F0A1F0A0A00000000000A0A0A00040004040404040000000000000000;
defparam prom_inst_0.INIT_RAM_09 = 256'h0000000010080C0C000D121508141408000313080402191800041E050E140F04;
defparam prom_inst_0.INIT_RAM_0A = 256'h000004041F0404000004150E1F0E150400080402020204080002040808080402;
defparam prom_inst_0.INIT_RAM_0B = 256'h0000100804020100000C0C0000000000000000001F00000010080C0C00000000;
defparam prom_inst_0.INIT_RAM_0C = 256'h000E11010601110E001F10100E01110E000E040404040C04000E11191513110E;
defparam prom_inst_0.INIT_RAM_0D = 256'h001010080402011F000E11111E100806000E1101011E101F0002021F120A0602;
defparam prom_inst_0.INIT_RAM_0E = 256'h10080C0C000C0C0000000C0C000C0C00000C02010F11110E000E11110E11110E;
defparam prom_inst_0.INIT_RAM_0F = 256'h000400040201110E00080402010204080000001F001F00000002040810080402;
defparam prom_inst_0.INIT_RAM_10 = 256'h000E11101010110E001E09090E09091E0011111F11110A04000E15150D01110E;
defparam prom_inst_0.INIT_RAM_11 = 256'h000F11111310100F001010101C10101F001F10101C10101F001E09090909091E;
defparam prom_inst_0.INIT_RAM_12 = 256'h0011121418141211000E110101010101000E04040404040E001111111F111111;
defparam prom_inst_0.INIT_RAM_13 = 256'h000E11111111110E00111111131519110011111115151B11001F101010101010;
defparam prom_inst_0.INIT_RAM_14 = 256'h000E11010E10110E001112141E11111E000D12151111110E001010101E11111E;
defparam prom_inst_0.INIT_RAM_15 = 256'h00111B15111111110004040A0A111111000E111111111111000404040404041F;
defparam prom_inst_0.INIT_RAM_16 = 256'h0004040404150E04001F10080402011F00040404040A11110011110A040A1111;
defparam prom_inst_0.INIT_RAM_17 = 256'h001F000000000000000004021F020400000004081F08040000040E1504040404;
defparam prom_inst_0.INIT_RAM_18 = 256'h000E1110110E00000016191119161010000F110F010E00000000000002040606;
defparam prom_inst_0.INIT_RAM_19 = 256'h0E010D13130D0000000404040E040502000E101F110E0000000D1311130D0101;
defparam prom_inst_0.INIT_RAM_1A = 256'h00121418141210100E11010101010001000E0404040C00040011111119161010;
defparam prom_inst_0.INIT_RAM_1B = 256'h000E1111110E0000001111111916000000151515151A0000000E04040404040C;
defparam prom_inst_0.INIT_RAM_1C = 256'h001E010E100F0000001010101916000001010D13130D00001010161919160000;
defparam prom_inst_0.INIT_RAM_1D = 256'h000A15151111000000040A1111110000000D13111111000000020504041F0404;
defparam prom_inst_0.INIT_RAM_1E = 256'h0002040408040402001F0804021F00000E010F111111000000110A040A110000;
defparam prom_inst_0.INIT_RAM_1F = 256'h000A150A150A150A000000000002150800080404020404080004040400040404;

endmodule //blk_mem_gen_3
