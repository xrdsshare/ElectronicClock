#include<reg52.h>
#include <intrins.h>
#define uchar unsigned char 
#define uint unsigned int
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
uchar code teble1[]={1,2,3,4,5,6,7,8,9,10,11,12};
sbit dula = P2^0;
sbit wela1 = P2^1;
sbit wela2 = P2^2;
sbit wela3 = P2^3;
sbit wela4 = P2^4; 
sbit wela5 = P2^5;
sbit dsq = P2^6;
sbit cs = P1^3;
sbit as = P1^0;
sbit rw = P1^1;
sbit ds = P1^2;
sbit irq = P1^4;
sbit k1 = P1^5;
sbit k2 = P1^6;
sbit k3 = P1^7;

char nian, yue, ri, nyue, nri, shi, fen, miao, xq, wen, led;
uint temp,num;
float f_temp;
uchar c_sun,year_sun,month_sun,day_sun;

void delay(uint z)			   //延时
{
	uint x,y;
	
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void write_ds(uchar add,uchar date)			//向DS12c887写
{
	cs=0;
	as=1;
	ds=1;
	rw=1;
	P0=add;
	as=0;
	rw=0;
	P0=date;
	rw=1;
	as=1;
	cs=1;				
}

uint read_ds(uchar add)					  //读DS12C887
{
	uchar date;
	as=1;
	ds=1;
	rw=1;
	cs=0;
	P0=add;
	as=0;
	ds=0;
	P0=0xff;
	date = P0;
	as=1;
	ds=1;
	cs=1;
	return date;
}

void set_time(uchar n, uchar y, uchar r, uchar x, char s, uchar f, uchar m)			//设置DS12C887
{
	write_ds(0,m);
	write_ds(2,f);
	write_ds(4,s);
	write_ds(6,x);
	write_ds(7,r);
	write_ds(8,y);
	write_ds(9,n);
}				 

void display_n(uint n)				//显示年
{
	uint a, b, c, d;
	a = 2;
	b = 0;
	c = n/10;
	d = n%10;
    dula = 1;
	P0 = table[a];
	dula = 0;
	P0 = 0xff;
	wela1 = 1;
	P0 = 0xfe;
	wela1 = 0;

	dula = 1;
	P0 = table[b];
	dula = 0;
	P0 = 0xff;
	wela1 = 1;
	P0 = 0xfd;
	wela1 = 0;

	dula = 1;
	P0 = table[c];
	dula = 0;
	P0 = 0xff;
	wela1 = 1;
	P0 = 0xfb;
	wela1 = 0;

	dula = 1;
	P0 = table[d];
	dula = 0;
	P0 = 0xff;
	wela1 = 1;
	P0 = 0xf7;
	wela1 = 0;

	wela1 = 1;
	P0 = 0xff;
	wela1 = 0;
}

void display_yy(uchar y)					 //显示阳历月
{
    dula = 1;
	P0 = table[y/10];
	dula = 0;
	P0 = 0xff;
	wela2 = 1;
	P0 = 0xfe;
	wela2 = 0;

	dula = 1;
	P0 = table[y%10];
	dula = 0;
	P0 = 0xff;
	wela2 = 1;
	P0 = 0xfd;
	wela2 = 0;

	wela2 = 1;
	P0 = 0xff;
	wela2 = 0;
}

void display_yr(uchar r)					  //显示阳历日
{
	dula = 1;
	P0 = table[r/10];
	dula = 0;
	P0 = 0xff;
	wela2 = 1;
	P0 = 0xef;
	wela2 = 0;

	dula = 1;
	P0 = table[r%10];
	dula = 0;
	P0 = 0xff;
	wela2 = 1;
	P0 = 0xdf;
	wela2 = 0;

	wela2 = 1;
	P0 = 0xff;
	wela2 = 0;
}

void display_nyr(uchar y, uchar r)				//显示阴历月日
{
	uint a, b, c, d;
	a = y/10;
	b = y%10;
	c = r/10;
	d = r%10;
    dula = 1;
	P0 = table[a];
	dula = 0;
	P0 = 0xff;
	wela2 = 1;
	P0 = 0xfb;
	wela2 = 0;

	dula = 1;
	P0 = table[b];
	dula = 0;
	P0 = 0xff;
	wela2 = 1;
	P0 = 0xf7;
	wela2 = 0;

	dula = 1;
	P0 = table[c];
	dula = 0;
	P0 = 0xff;
	wela2 = 1;
	P0 = 0xbf;
	wela2 = 0;

	dula = 1;
	P0 = table[d];
	dula = 0;
	P0 = 0xff;
	wela2 = 1;
	P0 = 0x7f;
	wela2 = 0;

	wela2 = 1;
	P0 = 0xff;
	wela2 = 0;
}

void display_s(uchar s)						   //显示时
{	
    dula = 1;
	P0 = table[s/10];
	dula = 0;
	P0 = 0xff;
	wela3 = 1;
	P0 = 0xfe;
	wela3 = 0;

	dula = 1;
	P0 = table[s%10];
	dula = 0;
	P0 = 0xff;
	wela3 = 1;
	P0 = 0xfd;
	wela3 = 0;

	wela3 = 1;
	P0 = 0xff;
	wela3 = 0;
}

void display_f(uchar f)							 //显示分
{
	dula = 1;
	P0 = table[f/10];
	dula = 0;
	P0 = 0xff;
	wela3 = 1;
	P0 = 0xfb;
	wela3 = 0;

	dula = 1;
	P0 = table[f%10];
	dula = 0;
	P0 = 0xff;
	wela3 = 1;
	P0 = 0xf7;
	wela3 = 0;

	wela3 = 1;
	P0 = 0xff;
	wela3 = 0;
}

void display_m(uchar m)							 //显示秒
{
    dula = 1;
	P0 = table[m/10];
	dula = 0;
	P0 = 0xff;
	wela3 = 1;
	P0 = 0xef;
	wela3 = 0;

	dula = 1;
	P0 = table[m%10];
	dula = 0;
	P0 = 0xff;
	wela3 = 1;
	P0 = 0xdf;
	wela3 = 0;

	wela3 = 1;
	P0 = 0xff;
	wela3 = 0;		 
}
 /*
void display_led(uchar l)						   //显示生肖灯
{
	uchar code table1[]={ 0x00,
	0xef,0xdf,0xbf,0x7f,
	0xfe,0xfd,0xfb,0xf7,
	0xef,0xdf,0xbf,0x7f,
	};
	if(l < 5)
	{
		P0 = 0xff;
		wela1 = 1;
		P0 = table1[l];
		wela1 = 0;
	}
	else
	{
		P0 = 0xff;
		wela4 = 1;
		P0 = table1[l];
		wela4 = 0;

		wela4 = 1;
		P0 = 0xff;
		wela4 = 0;
	}					
}		   */
void display_wen(uchar w)						 //显示温度
{
	dula = 1;
	P0 = table[w/10];
	dula = 0;
	P0 = 0xff;
	wela3 = 1;
	P0 = 0xbf;
	wela3 = 0;

	dula = 1;
	P0 = table[w%10];
	dula = 0;
	P0 = 0xff;
	wela3 = 1;
	P0 = 0x7f;
	wela3 = 0;

	wela3 = 1;
	P0 = 0xff;
	wela3 = 0;
}
void display_xq(week)							 //显示星期
{
    dula = 1;
	P0 = table[week];
	dula = 0;
	P0 = 0xff;
	wela5 = 1;
	P0 = 0xfe;
	wela5 = 0;

	wela5 = 1;
	P0 = 0xff;
	wela5 = 0;	
}

/*********************************************/
//温度芯片处理
void dsreset(void)
{
	uint i;
	dsq = 0;
	i = 103;
	while(i>0)i--;
	dsq = 1;
	i = 4; 
	while(i>0) i--;
}

bit tempreadbit(void)
{
	uint i;
	bit dat;
	dsq = 0;i++;
	dsq = 1;i++;i++;
	dat = dsq;
	i = 8;while(i>0)i--;
	return (dat);
}

uchar tempread()
{
	uchar i, j, dat;
	dat = 0;
	for(i=1;i<=8;i++)
	{
		j = tempreadbit();
		dat = (j<<7)|(dat>>1);
	}
	return(dat);
}

void tempwritebyte(uchar dat)
{
	uint i;
	uchar j;
	bit testb;
	for(j=1;j<=8;j++)
	{
		testb = dat&0x01;
		dat = dat>>1;
		if(testb)
		{
			dsq = 0;
			i++;i++;
			dsq = 1;
			i = 8;while(i>0)i--;
		}
		else
		{
			dsq = 0;
			i = 8;while(i>0) i--;
			dsq = 1;
			i++;i++;
		}
	}
}

void tempchange(void)
{
	dsreset();
	delay(1);
	tempwritebyte(0xcc);
	tempwritebyte(0x44);
}

uint get_temp()
{
	uchar a, b;
	dsreset();
	delay(1);
	tempwritebyte(0xcc);
	tempwritebyte(0xbe);
	a = tempread();
	b = tempread();
	temp = b;
	temp<<=8;
	temp = temp|a;
	f_temp = temp*0.0625;
	temp = f_temp*10 + 0.5;
	temp =temp/10/1;
	return temp;
} 


void csh()					 //初始化
{
	write_ds(0x0a,0x20);
	write_ds(0x0b,0x26);		
	P0 = 0xff;	
	wela1 = wela2 = wela3 = wela4 = wela5 = 0;
}

/****************************************************/
//阳历转农历
code uchar year_code[] = {									 //1901至2099农历数据 ，这个在网上抄的，该很多次都失败，只能保留1901到1999的数据
                          0x04,0xAe,0x53,    //1901 0
                          0x0A,0x57,0x48,    //1902 3
                          0x55,0x26,0xBd,    //1903 6
                          0x0d,0x26,0x50,    //1904 9
                          0x0d,0x95,0x44,    //1905 12
                          0x46,0xAA,0xB9,    //1906 15
                          0x05,0x6A,0x4d,    //1907 18
                          0x09,0xAd,0x42,    //1908 21
                          0x24,0xAe,0xB6,    //1909
                          0x04,0xAe,0x4A,    //1910
                          0x6A,0x4d,0xBe,    //1911
                          0x0A,0x4d,0x52,    //1912
                          0x0d,0x25,0x46,    //1913
                          0x5d,0x52,0xBA,    //1914
                          0x0B,0x54,0x4e,    //1915
                          0x0d,0x6A,0x43,    //1916
                          0x29,0x6d,0x37,    //1917
                          0x09,0x5B,0x4B,    //1918
                          0x74,0x9B,0xC1,    //1919
                          0x04,0x97,0x54,    //1920
                          0x0A,0x4B,0x48,    //1921
                          0x5B,0x25,0xBC,    //1922
                          0x06,0xA5,0x50,    //1923
                          0x06,0xd4,0x45,    //1924
                          0x4A,0xdA,0xB8,    //1925
                          0x02,0xB6,0x4d,    //1926
                          0x09,0x57,0x42,    //1927
                          0x24,0x97,0xB7,    //1928
                          0x04,0x97,0x4A,    //1929
                          0x66,0x4B,0x3e,    //1930
                          0x0d,0x4A,0x51,    //1931
                          0x0e,0xA5,0x46,    //1932
                          0x56,0xd4,0xBA,    //1933
                          0x05,0xAd,0x4e,    //1934
                          0x02,0xB6,0x44,    //1935
                          0x39,0x37,0x38,    //1936
                          0x09,0x2e,0x4B,    //1937
                          0x7C,0x96,0xBf,    //1938
                          0x0C,0x95,0x53,    //1939
                          0x0d,0x4A,0x48,    //1940
                          0x6d,0xA5,0x3B,    //1941
                          0x0B,0x55,0x4f,    //1942
                          0x05,0x6A,0x45,    //1943
                          0x4A,0xAd,0xB9,    //1944
                          0x02,0x5d,0x4d,    //1945
                          0x09,0x2d,0x42,    //1946
                          0x2C,0x95,0xB6,    //1947
                          0x0A,0x95,0x4A,    //1948
                          0x7B,0x4A,0xBd,    //1949
                          0x06,0xCA,0x51,    //1950
                          0x0B,0x55,0x46,    //1951
                          0x55,0x5A,0xBB,    //1952
                          0x04,0xdA,0x4e,    //1953
                          0x0A,0x5B,0x43,    //1954
                          0x35,0x2B,0xB8,    //1955
                          0x05,0x2B,0x4C,    //1956
                          0x8A,0x95,0x3f,    //1957
                          0x0e,0x95,0x52,    //1958
                          0x06,0xAA,0x48,    //1959
                          0x7A,0xd5,0x3C,    //1960
                          0x0A,0xB5,0x4f,    //1961
                          0x04,0xB6,0x45,    //1962
                          0x4A,0x57,0x39,    //1963
                          0x0A,0x57,0x4d,    //1964
                          0x05,0x26,0x42,    //1965
                          0x3e,0x93,0x35,    //1966
                          0x0d,0x95,0x49,    //1967
                          0x75,0xAA,0xBe,    //1968
                          0x05,0x6A,0x51,    //1969
                          0x09,0x6d,0x46,    //1970
                          0x54,0xAe,0xBB,    //1971
                          0x04,0xAd,0x4f,    //1972
                          0x0A,0x4d,0x43,    //1973
                          0x4d,0x26,0xB7,    //1974
                          0x0d,0x25,0x4B,    //1975
                          0x8d,0x52,0xBf,    //1976
                          0x0B,0x54,0x52,    //1977
                          0x0B,0x6A,0x47,    //1978
                          0x69,0x6d,0x3C,    //1979
                          0x09,0x5B,0x50,    //1980
                          0x04,0x9B,0x45,    //1981
                          0x4A,0x4B,0xB9,    //1982
                          0x0A,0x4B,0x4d,    //1983
                          0xAB,0x25,0xC2,    //1984
                          0x06,0xA5,0x54,    //1985
                          0x06,0xd4,0x49,    //1986
                          0x6A,0xdA,0x3d,    //1987
                          0x0A,0xB6,0x51,    //1988
                          0x09,0x37,0x46,    //1989
                          0x54,0x97,0xBB,    //1990
                          0x04,0x97,0x4f,    //1991
                          0x06,0x4B,0x44,    //1992
                          0x36,0xA5,0x37,    //1993
                          0x0e,0xA5,0x4A,    //1994
                          0x86,0xB2,0xBf,    //1995
                          0x05,0xAC,0x53,    //1996
                          0x0A,0xB6,0x47,    //1997
                          0x59,0x36,0xBC,    //1998
                          0x09,0x2e,0x50,    //1999 294
                          0x0C,0x96,0x45,    //2000 297
                          0x4d,0x4A,0xB8,    //2001
                          0x0d,0x4A,0x4C,    //2002
                          0x0d,0xA5,0x41,    //2003
                          0x25,0xAA,0xB6,    //2004
                          0x05,0x6A,0x49,    //2005
                          0x7A,0xAd,0xBd,    //2006
                          0x02,0x5d,0x52,    //2007
                          0x09,0x2d,0x47,    //2008
                          0x5C,0x95,0xBA,    //2009
                          0x0A,0x95,0x4e,    //2010
                          0x0B,0x4A,0x43,    //2011
                          0x4B,0x55,0x37,    //2012
                          0x0A,0xd5,0x4A,    //2013
                          0x95,0x5A,0xBf,    //2014
                          0x04,0xBA,0x53,    //2015
                          0x0A,0x5B,0x48,    //2016
                          0x65,0x2B,0xBC,    //2017
                          0x05,0x2B,0x50,    //2018
                          0x0A,0x93,0x45,    //2019
                          0x47,0x4A,0xB9,    //2020
                          0x06,0xAA,0x4C,    //2021
                          0x0A,0xd5,0x41,    //2022
                          0x24,0xdA,0xB6,    //2023
                          0x04,0xB6,0x4A,    //2024
                          0x69,0x57,0x3d,    //2025
                          0x0A,0x4e,0x51,    //2026
                          0x0d,0x26,0x46,    //2027
                          0x5e,0x93,0x3A,    //2028
                          0x0d,0x53,0x4d,    //2029
                          0x05,0xAA,0x43,    //2030
                          0x36,0xB5,0x37,    //2031
                          0x09,0x6d,0x4B,    //2032
                          0xB4,0xAe,0xBf,    //2033
                          0x04,0xAd,0x53,    //2034
                          0x0A,0x4d,0x48,    //2035
                          0x6d,0x25,0xBC,    //2036
                          0x0d,0x25,0x4f,    //2037
                          0x0d,0x52,0x44,    //2038
                          0x5d,0xAA,0x38,    //2039
                          0x0B,0x5A,0x4C,    //2040
                          0x05,0x6d,0x41,    //2041
                          0x24,0xAd,0xB6,    //2042
                          0x04,0x9B,0x4A,    //2043
                          0x7A,0x4B,0xBe,    //2044
                          0x0A,0x4B,0x51,    //2045
                          0x0A,0xA5,0x46,    //2046
                          0x5B,0x52,0xBA,    //2047
                          0x06,0xd2,0x4e,    //2048
                          0x0A,0xdA,0x42,    //2049
                          0x35,0x5B,0x37,    //2050
                          0x09,0x37,0x4B,    //2051
                          0x84,0x97,0xC1,    //2052
                          0x04,0x97,0x53,    //2053
                          0x06,0x4B,0x48,    //2054
                          0x66,0xA5,0x3C,    //2055
                          0x0e,0xA5,0x4f,    //2056
                          0x06,0xB2,0x44,    //2057
                          0x4A,0xB6,0x38,    //2058
                          0x0A,0xAe,0x4C,    //2059
                          0x09,0x2e,0x42,    //2060
                          0x3C,0x97,0x35,    //2061
                          0x0C,0x96,0x49,    //2062
                          0x7d,0x4A,0xBd,    //2063
                          0x0d,0x4A,0x51,    //2064
                          0x0d,0xA5,0x45,    //2065
                          0x55,0xAA,0xBA,    //2066
                          0x05,0x6A,0x4e,    //2067
                          0x0A,0x6d,0x43,    //2068
                          0x45,0x2e,0xB7,    //2069
                          0x05,0x2d,0x4B,    //2070
                          0x8A,0x95,0xBf,    //2071
                          0x0A,0x95,0x53,    //2072
                          0x0B,0x4A,0x47,    //2073
                          0x6B,0x55,0x3B,    //2074
                          0x0A,0xd5,0x4f,    //2075
                          0x05,0x5A,0x45,    //2076
                          0x4A,0x5d,0x38,    //2077
                          0x0A,0x5B,0x4C,    //2078
                          0x05,0x2B,0x42,    //2079
                          0x3A,0x93,0xB6,    //2080
                          0x06,0x93,0x49,    //2081
                          0x77,0x29,0xBd,    //2082
                          0x06,0xAA,0x51,    //2083
                          0x0A,0xd5,0x46,    //2084
                          0x54,0xdA,0xBA,    //2085
                          0x04,0xB6,0x4e,    //2086
                          0x0A,0x57,0x43,    //2087
                          0x45,0x27,0x38,    //2088
                          0x0d,0x26,0x4A,    //2089
                          0x8e,0x93,0x3e,    //2090
                          0x0d,0x52,0x52,    //2091
                          0x0d,0xAA,0x47,    //2092
                          0x66,0xB5,0x3B,    //2093
                          0x05,0x6d,0x4f,    //2094
                          0x04,0xAe,0x45,    //2095
                          0x4A,0x4e,0xB9,    //2096
                          0x0A,0x4d,0x4C,    //2097
                          0x0d,0x15,0x41,    //2098
                          0x2d,0x92,0xB5,    //2099
};

code uchar day_code1[9]={0x0,0x1f,0x3b,0x5a,0x78,0x97,0xb5,0xd4,0xf3};
code uint day_code2[3]={0x111,0x130,0x14e};

bit c_moon;
data uchar year_moon,month_moon,day_moon;

bit get_moon_day(uchar month_p,uint table_addr)
{
	uchar temp;
	switch (month_p)
	{
        case 1:{temp=year_code[table_addr]&0x08;
               if (temp==0)return(0);else return(1);}
        case 2:{temp=year_code[table_addr]&0x04;
               if (temp==0)return(0);else return(1);}
        case 3:{temp=year_code[table_addr]&0x02;
               if (temp==0)return(0);else return(1);}
        case 4:{temp=year_code[table_addr]&0x01;
               if (temp==0)return(0);else return(1);}
        case 5:{temp=year_code[table_addr+1]&0x80;
               if (temp==0) return(0);else return(1);}
        case 6:{temp=year_code[table_addr+1]&0x40;
               if (temp==0)return(0);else return(1);}
        case 7:{temp=year_code[table_addr+1]&0x20;
               if (temp==0)return(0);else return(1);}
        case 8:{temp=year_code[table_addr+1]&0x10;
               if (temp==0)return(0);else return(1);}
        case 9:{temp=year_code[table_addr+1]&0x08;
               if (temp==0)return(0);else return(1);}
        case 10:{temp=year_code[table_addr+1]&0x04;
               if (temp==0)return(0);else return(1);}
        case 11:{temp=year_code[table_addr+1]&0x02;
               if (temp==0)return(0);else return(1);}
        case 12:{temp=year_code[table_addr+1]&0x01;
               if (temp==0)return(0);else return(1);}
        case 13:{temp=year_code[table_addr+2]&0x80;
               if (temp==0)return(0);else return(1);}
      }
}

void Conversion(bit c,uchar year,uchar month,uchar day)
{                         //c=0 为21世纪,c=1 为19世纪
    uchar temp1,temp2,temp3,month_p;
    uint temp4,table_addr;
    bit flag2,flag_y;
	temp1=year/16;  
    temp2=year%16;
    temp1=month/16;
    temp2=month%16;
    temp1=day/16;
    temp2=day%16;

    if(c==0)
	{                   
		table_addr=(year+0x64-1)*0x3;
    }
    else
	{
        table_addr=(year-1)*0x3;
    }
    temp1=year_code[table_addr+2]&0x60; 
    temp1=_cror_(temp1,5);
    temp2=year_code[table_addr+2]&0x1f; 
    if(temp1==0x1)
	{  
        temp3=temp2-1;  
    }  
    else
	{
        temp3=temp2+0x1f-1;        
    }
    if (month<10)
	{ 
        temp4=day_code1[month-1]+day-1;
    }
    else
	{
        temp4=day_code2[month-10]+day-1;
    }
    if ((month>0x2)&&(year%0x4==0))	
	{  
        temp4+=1;
    }
    if (temp4>=temp3)
	{ 
        temp4-=temp3;
        month=0x1;
        month_p=0x1; 
        flag2=get_moon_day(month_p,table_addr); 
        flag_y=0;
        if(flag2==0)temp1=0x1d; 
        else temp1=0x1e; 
        temp2=year_code[table_addr]&0xf0;
        temp2=_cror_(temp2,4);  
        while(temp4>=temp1)
		{
	        temp4-=temp1;
	        month_p+=1;
	        if(month==temp2)
			{
			    flag_y=~flag_y;
			    if(flag_y==0)
			    month+=1;
            }
            else 
				month+=1;
            flag2=get_moon_day(month_p,table_addr);
            if(flag2==0)
				temp1=0x1d;
            else 
				temp1=0x1e;
        }
        day=temp4+1;
    }
    else
	{ 
        temp3-=temp4;
        if (year==0x0)
		{
			year=0x63;c=1;
  		}
        else 
			year-=1;
        table_addr-=0x3;
        month=0xc;
        temp2=year_code[table_addr]&0xf0;
        temp2=_cror_(temp2,4);
        if (temp2==0)
			month_p=0xc; 
        else 
			month_p=0xd;
        flag_y=0;
        flag2=get_moon_day(month_p,table_addr);
        if(flag2==0)
			temp1=0x1d;
        else 
			temp1=0x1e;
        while(temp3>temp1)
		{
            temp3-=temp1;
            month_p-=1;
            if(flag_y==0)
				month-=1;
            if(month==temp2)
				flag_y=~flag_y;
            flag2=get_moon_day(month_p,table_addr);
            if(flag2==0)
				temp1=0x1d;
            else temp1=0x1e;
         }
         day=temp1-temp3+1;
    }
    c_moon=c;                 //运算结束后,把数据转换为十进制数据
    temp1=year/10;
    temp1=_crol_(temp1,4);
    temp2=year%10;
    year_moon=temp1|temp2;
	month_moon=month;
	day_moon= day;
}
 /*
//阳历年转化为生肖数字，模仿农历转换的
uchar code table2[]={7,1,6,11,4,10,3,8,1,7,12,5,10,4,9,2,7,1,6,11,4,10,3,8,1,7,12,5,10,4,9,2,7,1,6,11,4,10,3,8,1,7,12,5,10,4,9,2,7,1,6,11,4,10,3,8,1,7,12,5,10,4,9,2,7,1,6,11,4,10,3,8,1,7,12,5,10,4,9,2,7,1,6,11,4,10,3,8,1,7,12,5,10,4,9,2,7,1,6,11}  ;           //2000-2099 
uint code table3[]={0,31,59,90,120,151,181,212,243,273,304,334 };
uchar shengxiao(uchar year,uchar month,uchar day )
{
	uchar a;
	uint b, d ;
	a =  table2[year];
	b = table3[month-1];
	d = b + day - 1;
	if ((month>2)&&(year%4==0))
		d++;
	d = d + a;
	d = d %12;
	if(d==0)
		d = 12;	
	return d;
} */
 
void key()				//按键扫描
{
	uchar bb = 0;
	if(k1==0)
	{
		delay(500);
		if(k1==0)
		{
			bb = 1;
		}
		while(!k1);
		delay(5);
		while(!k1);
	}
	while(bb)
	{
		if(k1==0)
		{
		delay(5);
		if(k1==0)
		{
			bb++;
		}
		while(!k1);
		delay(5);
		while(!k1);
		}

		if(bb==1)
		{
			display_n(nian);
			if(k2==0)
			{
				delay(5);
				if(k2==0)
				{
					nian++;
					if(nian>99)
						nian = 0;
				}
				while(!k2);
				delay(5);
				while(!k2);
			}

			if(k3==0)
			{
				delay(5);
				if(k3==0)
				{
					nian--;
					if(nian<0)
						nian = 99;
				}
				while(!k3);
				delay(5);
				while(!k3);
			}
		}

		if(bb==2)
		{
			display_yy(yue);
			if(k2==0)
			{
				delay(5);
				if(k2==0)
				{
					yue++;
					if(yue>12)
						yue = 1;
				}
				while(!k2);
				delay(5);
				while(!k2);
			}

			if(k3==0)
			{
				delay(5);
				if(k3==0)
				{
					yue--;
					if(yue<1)
						yue = 12;
				}
				while(!k3);
				delay(5);
				while(!k3);
			}
		}

		if(bb==3)
		{
			display_yr(ri);
			if(k2==0)
			{
				delay(5);
				if(k2==0)
				{
					ri++;
					if(ri>31)
						ri = 1;
				}
				while(!k2);
				delay(5);
				while(!k2);
			}

			if(k3==0)
			{
				delay(5);
				if(k3==0)
				{
					ri--;
					if(ri<1)
						ri = 31;
				}
				while(!k3);
				delay(5);
				while(!k3);
			}
		}

		if(bb==4)
		{
			display_xq(xq);
			if(k2==0)
			{
				delay(5);
				if(k2==0)
				{
					xq++;
					if(xq>7)
						xq = 1;
				}
				while(!k2);
				delay(5);
				while(!k2);
			}

			if(k3==0)
			{
				delay(5);
				if(k3==0)
				{
					xq--;
					if(xq<1)
						xq = 7;
				}
				while(!k3);
				delay(5);
				while(!k3);
			}
		}
		if(bb==5)
		{
			display_s(shi);
			if(k2==0)
			{
				delay(5);
				if(k2==0)
				{
					shi++;
					if(shi>23)
						shi = 0;
				}
				while(!k2);
				delay(5);
				while(!k2);
			}

			if(k3==0)
			{
				delay(5);
				if(k3==0)
				{
					shi--;
					if(shi<0)
						shi = 23;
				}
				while(!k3);
				delay(5);
				while(!k3);
			}
		}

		if(bb==6)
		{
			display_f(fen);
			if(k2==0)
			{
				delay(5);
				if(k2==0)
				{
					fen++;
					if(fen>59)
						fen = 0;
				}
				while(!k2);
				delay(5);
				while(!k2);
			}

			if(k3==0)
			{
				delay(5);
				if(k3==0)
				{
					fen--;
					if(fen<0)
						fen = 59;
				}
				while(!k3);
				delay(5);
				while(!k3);
			}
		}

		if(bb==7)
		{
			display_m(miao);
			if(k2==0)
			{
				delay(5);
				if(k2==0)
				{
					miao++;
					if(miao>59)
						miao = 0;
				}
				while(!k2);
				delay(5);
				while(!k2);
			}

			if(k3==0)
			{
				delay(5);
				if(k3==0)
				{
					miao--;
					if(miao<0)
						miao = 59;
				}
				while(!k3);
				delay(5);
				while(!k3);
			}
		}

		if(bb==8)
		{
			set_time(nian, yue, ri, xq, shi, fen, miao) ;
			display_n(nian);			    
			display_yy(yue);
			display_yr(ri);
			display_xq(xq);	
			display_s(shi);
			display_f(fen);
			display_m(miao);
		}
	}

}			   


void main()
{
	csh();
	while(1)
	{
		tempchange();
		display_wen(get_temp());
		nian = read_ds(9);
		yue = read_ds(8);
		ri = read_ds(7);
		xq = read_ds(6);
		shi = read_ds(4);
		fen = read_ds(2);
		miao = read_ds(0);
		c_sun=0;
	    year_sun=nian;
	    month_sun=yue;
	    day_sun=ri;
	    Conversion(c_sun,year_sun,month_sun,day_sun);
//		led = shengxiao(year_sun,month_sun,day_sun);
		display_n(nian);			    
		display_yy(yue);
		display_yr(ri);
		display_xq(xq);	
		display_nyr(month_moon,day_moon);
		display_s(shi);
		display_f(fen);
		display_m(miao);   
//		display_led(led); 
		key();
	}
}