`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    15:39:50 12/26/2020 
// Design Name: 
// Module Name:    Count_display 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module Count_display(
		clk, mode, an, seg, speed
    );
	 
	 input clk;
	 input wire[1:0] mode;
	 input wire[3:0] speed;
	 output wire[3:0] an;
	 output wire[6:0] seg;
	 
	 wire [15:0] num;
	 wire [1:0] mode1;
	 
	
	 
	 Counter  #(50000000)	//1Hz计数频率
		A0( 
			.clk 		(clk),
			.rst 		(mode[1]),
			.cnt 		(),
			.cout 	(clk_count),
			.speed 	(speed)
		);
		

	 //四位十进制计数器，异步
	 Dec_cnt X0(
		.clk	(clk_count),
		.mode	(mode1),
		.cnt	(num[3:0]),
		.cout	(C0)
	 );
	 
	 Dec_cnt X1(
		.clk	(C0),
		.mode	(mode1),
		.cnt	(num[7:4]),
		.cout	(C1)
	 );
	 
	 Dec_cnt X2(
		.clk	(C1),
		.mode	(mode1),
		.cnt	(num[11:8]),
		.cout	(C2)
	 );
	 
	 Dec_cnt X3(
		.clk	(C2),
		.mode	(mode1),
		.cnt	(num[15:12]),
		.cout	(C3)
	 );
	 
	 
	  assign mode1[0] = mode[0];
	  assign mode1[1] = (num[4]&num[8]&num[10])|mode[1];
	 
	 
	 
	 Counter  #(100000)	//扫描分频
		A1( 
			.clk 		(clk),
			.rst 		(0),
			.cnt 		(),
			.cout 	(next),
			.speed	(0)
		);
	 
	 display sh(
		.num 		(num),
		.clk 		(next),
		.an 		(an),
		.show 	(seg)
	);
	
	


endmodule

module Dec_cnt(
		clk, mode, cnt, cout
    );
	 input clk;
	 input wire[1:0] mode;
	 output reg[3:0] cnt;
	 output reg cout;

	always @(posedge clk or posedge mode[1])
	if(mode[1] == 1)
		begin
			cnt <= 0;
			cout <= 0;
		end
	else if(mode == 2'b00) //计数
				if(cnt == 9)
					 begin
						cnt <= 0;
						cout <= 1;
					 end
				else
					begin
					  cnt <= cnt + 1;
					  cout <= 0;
					end
			else 
				cnt <= cnt;
endmodule

//计数分频器
module Counter #(
		parameter cnt_num = 100000)(
		clk, rst, speed, cnt, cout
    );
	 input clk;
	 input rst;
	 input wire[2:0] speed;
	 output reg[31:0] cnt;
	 output reg cout;
	 
	 wire [31:0] MAX;
	 assign MAX = cnt_num >> speed;
	
	//always@(speed)
	//	MAX = cnt_num >> speed;
	
	always @(posedge clk or posedge rst)
	begin
		 if(rst == 1)
			  cnt <= 0;
		 else if(cnt > MAX - 2)	//用==时，由于max会减小，导致错过相等，导致一直不清零
				 begin
					cnt <= 0;
					cout <= 1;
				 end  
		 else
			begin
			  cnt <= cnt + 1;
			  cout <= 0;
			end
	end
endmodule


//显示数码管
module display(
		clk, num, an, show
	);
	
	input clk;
	input wire[15:0] num;
	output reg[6:0] show;
	output reg[3:0] an;
	
	reg[3:0] digit;
	reg[1:0] ch;
	
	always @(posedge clk)
		if(ch == 3)
			ch <= 0;
		else 
			ch <= ch + 1;
	
	always @(num)
		case(ch)
			0:digit = num[3:0];
			1:digit = num[7:4];
			2:digit = num[11:8];
			3:digit = num[15:12];
			default:digit = 'hF;
		endcase
		
	always@(digit)
		case(digit)
			0:show=7'b1000000;
			1:show=7'b1111001;
			2:show=7'b0100100;
			3:show=7'b0110000;
			4:show=7'b0011001;
			5:show=7'b0010010;
			6:show=7'b0000010;
			7:show=7'b1111000;
			8:show=7'b0000000;
			9:show=7'b0010000;
			default:show=7'b0111111;
		endcase
		
	always@(ch)
		begin
			an = 4'b1111;
			an[ch] = 0;
		end
	
endmodule
