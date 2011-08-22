#include <at89x52.h>
unsigned char crystal=2;
char code s1200[]={
0xf3,//6.00000MHz@1200bps*2
0xe8,//11.0592MHz@1200bps*2
0xe6,//12.0000MHz@1200bps*2
0xdd,//16.0000MHz@1200bps*2
0xd0,//22.1184MHz@1200bps*2
0xcc //24.0000MHz@1200bps*2
};
code char code  *s12[]={
"6.00000MHz@2400bps",//0
"11.0592MHz@2400bps",//1
"12.0000MHz@2400bps",//2
"16.0000MHz@2400bps",//3
"22.1184MHz@2400bps",//4
"24.0000MHz@2400bps"};//5

#define H(n) ((65536-(n))>>8)
#define L(n) ((65536-(n))%256)
unsigned char code th0_ov[]={
H(1000), //2ms@6MHz
H(9216/5),//2ms@11.0592MHz
H(2000), //2ms@12.0000MHz
H(8000/3),//2ms@16MHz
H(18432/5),//2ms@22.1184MHz
H(4000) //2ms@24MHz
};
unsigned char code tl0_ov[]={
L(1000),	//2ms@6MHz
L(9216/5),	//2ms@11.0592MHz
L(2000),	//2ms@12.0000MHz
L(8000/3),	//2ms@16MHz
L(18432/5),	//2ms@22.1184MHz
L(4000)		//2ms@24MHz
};






unsigned char code s9600[]={
0xfd,//11.0592MHz@9600bps
0xfa,//22.1184MHz@9600bps
};



bit k1c,k1f,k1;
bit k2c,k2f,k2;


void s_init(void)
{
    SCON  = 0x50;		        /* SCON: mode 1, 8-bit UART, enable rcvr      */
    TMOD |= 0x20;               /* TMOD: timer 1, mode 2, 8-bit reload        */
	PCON |= SMOD_;
    //TH1   = 221;                /* TH1:  reload value for 1200 baud @ 16MHz   */
	TH1=0xe8; //9600@22.1184MHz
    TR1   = 1;                  /* TR1:  timer 1 run                          */
    TI    = 1;                  /* TI:   set TI to send first char of UART    */
}

void keys(void)
{
 static unsigned char i;
 if(i)i--;else{
  i=10;
  k1f=k1c;
  k1c=P1_7;
  k1=k1f^k1c;

  k2f=k2c;
  k2c=P3_3;
  k2=k2f^k2c;
 }
}
/*
void set_crystal(void)
{
   if(k1c==0 && k1){
    k1=0;
	if(crystal<5)crystal++;else crystal=0;
    TH1=s1200[crystal];
	printf("serial port set to %s\n",s12[crystal]);
}*/
