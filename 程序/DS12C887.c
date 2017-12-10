#include<reg52.h>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
sbit lcdrs=P2^4;
sbit lcden=P2^6;
sbit s1=P3^0;  //功能键
sbit s2=P3^1;  //增大键
sbit s3=P3^2;  //减小键
sbit s4=P3^6;  //闹铃查看键
sbit beep=P2^3;//蜂鸣器
sbit dscs=P1^4;
sbit dsas=P1^5;
sbit dsrw=P1^6;
sbit dsds=P1^7;
sbit dsirq=P3^3; //中断
bit flag1,flag_ri;//定义标志位	  flag1设置闹铃
uchar count,s1num,flag,t0_num;
char miao,shi,fen,year,month,day,week,amiao,afen,ashi;
char code table[]=" 20  -  -  ";  //   20  -  -     
uchar code table1[]="      :  :  ";   //       :  :  

void write_ds(uchar,uchar); 
uchar read_ds(uchar);
void set_time();
void read_alarm();
void set_alarm(uchar,uchar,uchar); 

void delayms(uint z)		//延时毫秒的程序
{
	uint x,y;
	for(x=z;x>0;x--)
	for(y=112;y>0;y--);
}
void di()
{
	beep=0;
	delayms(100);
	beep=1;
}
void write_cmd(uchar cmd)
{
	lcden=0;
	lcdrs=0;
	P0=c   md;
	_nop_();
	lcden=1;
	delayms(1);
	lcden=0;
    _nop_();
}
void write_dat(uchar dat)
{
	lcden=0;
	lcdrs=1;
	P0=dat;
    _nop_();
	lcden=1;
	delayms(1);
	lcden=0;
	_nop_();
}
void lcdint()
{
	lcden=0;
	write_cmd(0x38);   // 显示模式设置	
	write_cmd(0x0c);   //开显示，不显示光标，不闪烁
	write_cmd(0x06);   //写一个字符后地址加1，屏幕不移
	write_cmd(0x01);	//清屏
	delayms(1);
}
void init()
{
	uchar num;
	EA=1;//开总中断
	EX1=1;//开外部中断1
	IT1=1;//外部中断下降沿触发
	flag1=0; t0_num=0;s1num=0;week=1;
	write_ds(0x0A,0x20);//打开振荡器
	write_ds(0x0B,0x26);//设置24小时模式，数据二进制格式，开启闹铃中断
	set_time();//设置上电默认时间,调试的时候用
	lcdint();
	write_cmd(0x80);
	for(num=0;num<15;num++)
		{
		 	write_dat(table[num]);
		}
	write_cmd(0xc0);
	for(num=0;num<11;num++)
		{
			write_dat(table1[num]);
		}
}
void write_sfm(uchar add,char date)		 //写时间,2位一起写
{
	char shi,ge;
	shi=date/10;ge=date%10;
	write_cmd(0xc0+add);
	write_dat(0x30+shi);
	write_dat(0x30+ge);		
}	
void write_nyr(uchar add,char date)//年月日
{
	char shi,ge;
	shi=date/10;ge=date%10;
	write_cmd(0x80+add);
	write_dat(0x30+shi);
	write_dat(0x30+ge);
}
void write_week(char we)//星期
{
	write_cmd(0x80+12);
	switch(we)
	{
		case 1: write_dat('M');write_dat('O');write_dat('N');break;
		case 2: write_dat('T');write_dat('U');write_dat('E');break;
		case 3: write_dat('W');write_dat('E');write_dat('D');break;
		case 4: write_dat('T');write_dat('H');write_dat('U');break;
		case 5: write_dat('F');write_dat('R');write_dat('I');break;
		case 6: write_dat('S');write_dat('A');write_dat('T');break;
		case 7: write_dat('S');write_dat('U');write_dat('N');break;
	}
}
void keyscan()
{
	if(flag_ri==1)
	{
		if((s1==0)||(s2==0)||(s3==0)||(s4==0))//按任意键取消闹钟报警
		{
			delayms(5);
			if((s1==0)||(s2==0)||(s3==0)||(s4==0))
			{
				while(!(s1&&s2&&s3&&s4));di();
				flag_ri=0;
			}
		}
	}	
	if(s1==0)			  //如果功能按键1按下
	{
		delayms(5);		   //去抖动
		if(s1==0)
		{		 	
			while(!s1);		  //等待松手
			s1num++;			//记下次数
			di();			  //蜂鸣器响
			if(flag1==1)	  //设置闹铃为1时才对s1num调整，只调秒，分，时
			{
				if(s1num>3)	
				{
					s1num=1;
				}
			}
			flag=1;		//在调整时间时标志位flag为1，不进行正常操作
			switch(s1num)
			{
				case 1:write_cmd(0xc0+10); write_cmd(0x0f);	break;  //按一下秒钟 指针显示闪烁
				case 2:write_cmd(0xc0+7); break;
				case 3:write_cmd(0xc0+4); break;
				case 4:write_cmd(0x80+12); break;
				case 5:write_cmd(0x80+9); break;
				case 6:write_cmd(0x80+6); break;
				case 7:write_cmd(0x80+3); break;
				default: 			 //用default可以解决s1num跑飞
					s1num=0;
					write_cmd(0x0c);  //按了8次关闪烁，flag=0,退出调整，显示时间
					flag=0;
					write_ds(0,miao);  //将调整后的时间写入ds12c887
					write_ds(2,fen);
					write_ds(4,shi);
					write_ds(6,week);
					write_ds(7,day);
					write_ds(8,month);
					write_ds(9,year);
					break;

			}
		}
	}
	if(s1num!=0)	//S1有按下过，检测S2，S3
	{
		if(s2==0)		//如果按键2按下执行加
		{
			delayms(5);
			if(s2==0)
			{
				while(!s2);di();
				switch(s1num)
				{
					case 1:
						miao++;
					 	if(miao>59)
						{
							miao=0;
						}
						write_sfm(10,miao);
						write_cmd(0x80+0x40+10);
					 	break;  
					case 2:
						fen++;
					 	if(fen>59)
						{
							fen=0;
						}
						write_sfm(7,fen);
						write_cmd(0x80+0x40+7);
					 	break; 
					case 3:
						shi++;
					 	if(shi>23)
						{
							shi=0;
						}
						write_sfm(4,shi);
						write_cmd(0x80+0x40+4);
					 	break; 
					case 4:
						week++;
					 	if(week>7)
						{
							week=1;
						}
						write_week(week);
						write_cmd(0x80+12);
					 	break; 
					case 5:
						day++;
					 	if(day>31)
						{
							day=1;
						}
						write_nyr(9,day);
						write_cmd(0x80+9);
					 	break; 
					case 6:
						month++;
					 	if(month>12)
						{
							month=1;
						}
						write_nyr(6,month);
						write_cmd(0x80+6);
					 	break; 
					case 7:
						year++;
					 	if(year>99)
						{
							year=0;
						}
						write_nyr(3,year);
						write_cmd(0x80+3);
					 	break; 
					}
				}
			}
		if(s3==0)
		{
			delayms(5);
			if(s3==0)
			{
				while(!s3);di();
				switch(s1num)
				{
					case 1:
						miao--;
					 	if(miao<0)
						{
							miao=59;
						}
						write_sfm(10,miao);
						write_cmd(0x80+0x40+10);
					 	break;  
					case 2:
						fen--;
					 	if(fen<0)
						{
							fen=59;
						}
						write_sfm(7,fen);
						write_cmd(0x80+0x40+7);
					 	break; 
					case 3:
						shi--;
					 	if(shi<0)
						{
							shi=23;
						}
						write_sfm(4,shi);
						write_cmd(0x80+0x40+4);
					 	break; 
					case 4:
						week--;
					 	if(week<1)
						{
							week=7;
						}
						write_week(week);
						write_cmd(0x80+12);
					 	break; 
					case 5:
						day--;
					 	if(day<1)
						{
							day=31;
						}
						write_nyr(9,day);
						write_cmd(0x80+9);
					 	break; 
					case 6:
						month--;
					 	if(month<1)
						{
							month=12;
						}
						write_nyr(6,month);
						write_cmd(0x80+6);
					 	break; 
					case 7:
						year--;
					 	if(year<0)
						{
							year=99;
						}
						write_nyr(3,year);
						write_cmd(0x80+3);
					 	break; 
					}				
			   }
         	}
		}
		if(s4==0)
		{
			delayms(5);
			if(s4==0)
			{
				while(!s4);di(); flag1=~flag1;	//闹铃调好后再按一次键返回
				if(flag1==0)   //退出闹钟设置保存数值
				{
					flag=0;	   //启动时间显示
					write_cmd(0x80+0x40);
					write_dat(' ');
					write_dat(' ');
					write_cmd(0x0c);  //清屏下，否则光标乱跳   （闹铃调时间时）
					write_ds(1,miao);
					write_ds(3,fen);
					write_ds(5,shi);
				}
				else  //设置闹钟
				{
					read_alarm();  //读原始数据
					miao=amiao;
					fen=afen;
					shi=ashi;
					write_cmd(0xc0);
					write_dat('R');write_dat('i');
					write_cmd(0x80+0x40);
					write_sfm(4,ashi);
					write_sfm(7,afen);	
					write_sfm(10,amiao);		
				}			
			}
		}
}
void write_ds(uchar add,uchar date)//写12c887函数
{
	dscs=0;
	dsas=1;
	dsds=1;
	dsrw=1;
	P0=add;	 //写地址
	dsas=0;
	dsrw=0;
	P0=date;  //写数据
	dsrw=1;
	dsas=1;
	dscs=1;	
}
uchar read_ds(uchar add) //读12c887
{
	uchar ds_date;
	dsas=1;
	dsds=1;
	dsrw=1;
	dscs=0;
	P0=add;
	dsas=0;
	dsds=0;
	P0=0xff;
	ds_date=P0;
	dsds=1;
	dsas=1;
	dscs=1;
	return ds_date;	
}
void set_time()	 //初始化
{
	write_ds(0,0);	//秒
	write_ds(1,10);	//秒闹铃
	write_ds(2,34);	//分钟	
	write_ds(3,34);	//分钟闹铃
	write_ds(4,15);	//小时
	write_ds(5,15);	//小时闹铃
	write_ds(6,5);	//星期
	write_ds(7,20);	//日
	write_ds(8,5);	//月
	write_ds(9,11);	//年
} 
void read_alarm()
{
	amiao=read_ds(1);
	afen=read_ds(3);
	ashi=read_ds(5);
}
void main()
{
	init();
	while(1)
	{
		keyscan();	   //键盘不断扫描	
		if(flag_ri==1)	  //如果闹铃时间到
		{
			di();
			delayms(100);
			di();
			delayms(500);
		}
		if(flag==0&&flag1==0)
		{
			keyscan();
			year=read_ds(9);
			month=read_ds(8);
			day=read_ds(7);
			week=read_ds(6);
			shi=read_ds(4);
			fen=read_ds(2);
			miao=read_ds(0);
			write_sfm(10,miao);
			write_sfm(7,fen);
			write_sfm(4,shi);
			write_week(week);
			write_nyr(3,year);
			write_nyr(6,month);
			write_nyr(9,day);
		} 	
	} 
}
void exter()interrupt 2	   //闹铃外部中断1
{
	uchar c;	 //闹铃时间到
	flag_ri=1;
	c=read_ds(0x0c);   //读C寄存器表示响应中断
}