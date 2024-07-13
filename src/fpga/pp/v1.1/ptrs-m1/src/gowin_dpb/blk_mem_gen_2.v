//Copyright (C)2014-2023 Gowin Semiconductor Corporation.
//All rights reserved.
//File Title: IP file
//GOWIN Version: V1.9.9 Beta-4 Education
//Part Number: GW2A-LV18PG256C8/I7
//Device: GW2A-18
//Device Version: C
//Created Time: Sat Jun 08 10:03:06 2024

module blk_mem_gen_2 (douta, doutb, clka, ocea, cea, reseta, wrea, clkb, oceb, ceb, resetb, wreb, ada, dina, adb, dinb);

output [7:0] douta;
output [7:0] doutb;
input clka;
input ocea;
input cea;
input reseta;
input wrea;
input clkb;
input oceb;
input ceb;
input resetb;
input wreb;
input [9:0] ada;
input [7:0] dina;
input [9:0] adb;
input [7:0] dinb;

wire [7:0] dpb_inst_0_douta_w;
wire [7:0] dpb_inst_0_doutb_w;
wire gw_gnd;

assign gw_gnd = 1'b0;

DPB dpb_inst_0 (
    .DOA({dpb_inst_0_douta_w[7:0],douta[7:0]}),
    .DOB({dpb_inst_0_doutb_w[7:0],doutb[7:0]}),
    .CLKA(clka),
    .OCEA(ocea),
    .CEA(cea),
    .RESETA(reseta),
    .WREA(wrea),
    .CLKB(clkb),
    .OCEB(oceb),
    .CEB(ceb),
    .RESETB(resetb),
    .WREB(wreb),
    .BLKSELA({gw_gnd,gw_gnd,gw_gnd}),
    .BLKSELB({gw_gnd,gw_gnd,gw_gnd}),
    .ADA({gw_gnd,ada[9:0],gw_gnd,gw_gnd,gw_gnd}),
    .DIA({gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,dina[7:0]}),
    .ADB({gw_gnd,adb[9:0],gw_gnd,gw_gnd,gw_gnd}),
    .DIB({gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,gw_gnd,dinb[7:0]})
);

defparam dpb_inst_0.READ_MODE0 = 1'b0;
defparam dpb_inst_0.READ_MODE1 = 1'b1;
defparam dpb_inst_0.WRITE_MODE0 = 2'b00;
defparam dpb_inst_0.WRITE_MODE1 = 2'b00;
defparam dpb_inst_0.BIT_WIDTH_0 = 8;
defparam dpb_inst_0.BIT_WIDTH_1 = 8;
defparam dpb_inst_0.BLK_SEL_0 = 3'b000;
defparam dpb_inst_0.BLK_SEL_1 = 3'b000;
defparam dpb_inst_0.RESET_MODE = "SYNC";
defparam dpb_inst_0.INIT_RAM_00 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_01 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_02 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_03 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_04 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_05 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_06 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_07 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_08 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_09 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_0A = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_0B = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_0C = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_0D = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_0E = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_0F = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_10 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_11 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_12 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_13 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_14 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_15 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_16 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_17 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_18 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_19 = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_1A = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_1B = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_1C = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_1D = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_1E = 256'h2020202020202020202020202020202020202020202020202020202020202020;
defparam dpb_inst_0.INIT_RAM_1F = 256'h2020202020202020202020202020202020202020202020202020202020202020;

endmodule //blk_mem_gen_2
