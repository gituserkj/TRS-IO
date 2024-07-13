//Copyright (C)2014-2023 Gowin Semiconductor Corporation.
//All rights reserved.
//File Title: IP file
//GOWIN Version: V1.9.9 Beta-4 Education
//Part Number: GW2A-LV18PG256C8/I7
//Device: GW2A-18
//Device Version: C
//Created Time: Tue Jun 18 07:40:24 2024

module blk_mem_gen_3 (dout, clk, oce, ce, reset, wre, ad, din);

output [5:0] dout;
input clk;
input oce;
input ce;
input reset;
input wre;
input [10:0] ad;
input [5:0] din;

wire [25:0] sp_inst_0_dout_w;
wire gw_gnd;

assign gw_gnd = 1'b0;

SP sp_inst_0 (
    .DO({sp_inst_0_dout_w[25:0],dout[5:0]}),
    .CLK(clk),
    .OCE(oce),
    .CE(ce),
    .RESET(reset),
    .WRE(wre),
    .BLKSEL({gw_gnd,gw_gnd,gw_gnd}),
    .AD({ad[10:0],gw_gnd,gw_gnd,gw_gnd}),
    .DI({gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,din[5:0]})
);

defparam sp_inst_0.READ_MODE = 1'b1;
defparam sp_inst_0.WRITE_MODE = 2'b00;
defparam sp_inst_0.BIT_WIDTH = 8;
defparam sp_inst_0.BLK_SEL = 3'b000;
defparam sp_inst_0.RESET_MODE = "SYNC";
defparam sp_inst_0.INIT_RAM_00 = 256'h000E11101010110E001E09090E09091E0011111F11110A04000F10171517110E;
defparam sp_inst_0.INIT_RAM_01 = 256'h000F11111310100F001010101C10101F001F10101C10101F001E09090909091E;
defparam sp_inst_0.INIT_RAM_02 = 256'h0011121418141211000E110101010101000E04040404040E001111111F111111;
defparam sp_inst_0.INIT_RAM_03 = 256'h000E11111111110E00111113151911110011111115151B11001F101010101010;
defparam sp_inst_0.INIT_RAM_04 = 256'h000E11010E10110E001112141E11111E000D12151111110E001010101E11111E;
defparam sp_inst_0.INIT_RAM_05 = 256'h00111B15111111110004040A0A111111000E111111111111000404040404041F;
defparam sp_inst_0.INIT_RAM_06 = 256'h0004040404150E04001F10080402011F00040404040A11110011110A040A1111;
defparam sp_inst_0.INIT_RAM_07 = 256'h001F1F1F1F000000000004021F020400000004081F08040000040E1504040404;
defparam sp_inst_0.INIT_RAM_08 = 256'h000A0A1F0A1F0A0A00000000000A0A0A00040004040404040000000000000000;
defparam sp_inst_0.INIT_RAM_09 = 256'h0000000010080C0C000D121508141408000313080402191800041E050E140F04;
defparam sp_inst_0.INIT_RAM_0A = 256'h000004041F0404000004150E1F0E150400080402020204080002040808080402;
defparam sp_inst_0.INIT_RAM_0B = 256'h0000100804020100000C0C0000000000000000001F000000080C0C0000000000;
defparam sp_inst_0.INIT_RAM_0C = 256'h000E11010601110E001F10100E01110E000E040404040C04000E11191513110E;
defparam sp_inst_0.INIT_RAM_0D = 256'h001010080402011F000E11111E100806000E1101011E101F0002021F120A0602;
defparam sp_inst_0.INIT_RAM_0E = 256'h080C0C000C0C0000000C0C000C0C0000000C02010F11110E000E11110E11110E;
defparam sp_inst_0.INIT_RAM_0F = 256'h000400040201110E00080402010204080000001F001F00000002040810080402;
defparam sp_inst_0.INIT_RAM_10 = 256'h000E11101010110E001E09090E09091E0011111F11110A04000F10171517110E;
defparam sp_inst_0.INIT_RAM_11 = 256'h000F11111310100F001010101C10101F001F10101C10101F001E09090909091E;
defparam sp_inst_0.INIT_RAM_12 = 256'h0011121418141211000E110101010101000E04040404040E001111111F111111;
defparam sp_inst_0.INIT_RAM_13 = 256'h000E11111111110E00111113151911110011111115151B11001F101010101010;
defparam sp_inst_0.INIT_RAM_14 = 256'h000E11010E10110E001112141E11111E000D12151111110E001010101E11111E;
defparam sp_inst_0.INIT_RAM_15 = 256'h00111B15111111110004040A0A111111000E111111111111000404040404041F;
defparam sp_inst_0.INIT_RAM_16 = 256'h0004040404150E04001F10080402011F00040404040A11110011110A040A1111;
defparam sp_inst_0.INIT_RAM_17 = 256'h001F1F1F1F000000000004021F020400000004081F08040000040E1504040404;
defparam sp_inst_0.INIT_RAM_18 = 256'h000E1110110E00000016191119161010000F110F010E00002A152A152A152A15;
defparam sp_inst_0.INIT_RAM_19 = 256'h010F1111110E0000000404040E040502000E101F110E0000000D1311130D0101;
defparam sp_inst_0.INIT_RAM_1A = 256'h00121418141210100101010101030001000E0404040C00040011111119161010;
defparam sp_inst_0.INIT_RAM_1B = 256'h000E1111110E0000001111111916000000111115151A0000000E04040404040C;
defparam sp_inst_0.INIT_RAM_1C = 256'h001E010E100F00000010101019160000010D1313130D00001016191919160000;
defparam sp_inst_0.INIT_RAM_1D = 256'h000A15151111000000040A1111110000000D13111111000000020504041F0404;
defparam sp_inst_0.INIT_RAM_1E = 256'h0002040408040402001F0804021F0000010F11111111000000110A040A110000;
defparam sp_inst_0.INIT_RAM_1F = 256'h1F15040A19151311120C0C122121120C0008040402040408001B0A0A1F11110E;
defparam sp_inst_0.INIT_RAM_20 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_21 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_22 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_23 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_24 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_25 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_26 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_27 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_28 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_29 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_2A = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_2B = 256'h0000000000000000000000000000000000000000000000000000000000000010;
defparam sp_inst_0.INIT_RAM_2C = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_2D = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_2E = 256'h0000000000000010000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_2F = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_30 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_31 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_32 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_33 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_34 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_35 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_36 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_37 = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_38 = 256'h0000000000000000000000000000000000000000000000002A152A152A152A15;
defparam sp_inst_0.INIT_RAM_39 = 256'h0000000000000E01000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_3A = 256'h0000000000000000000000000000060900000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_3B = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_3C = 256'h0000000000000000000000000000000000000000000001010000000000001010;
defparam sp_inst_0.INIT_RAM_3D = 256'h0000000000000000000000000000000000000000000000000000000000000000;
defparam sp_inst_0.INIT_RAM_3E = 256'h000000000000000000000000000000000000000000000E010000000000000000;
defparam sp_inst_0.INIT_RAM_3F = 256'h0000000000000000000000000C12212100000000000000000000000000000000;

endmodule //blk_mem_gen_3
