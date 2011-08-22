#include <at89x52.h>
#include <string.h>
#include <intrins.h>
//p.c声明
#define GS 1


extern unsigned long idata cur[GS];
extern void agg(char *l,unsigned char j);



//同时解的部数
//按一个数码
extern bit dr;//队列准备
extern bit oe;//按数码输出许可
#define ms(n) (n/6)
extern unsigned char on;//按住时间
extern unsigned char of;//松开时间
extern unsigned char dg;//数码位数
extern unsigned char q[GS][8];//八位数码之内可以用
extern unsigned char idata qn;//按到第几位?从0开始作基数
extern char aq(unsigned long n,unsigned char j);
extern void queue(unsigned char j);//某列数
extern void gq(void);//所有都开数
extern unsigned char ag(char *l,unsigned char j);//将*l 添入数组队中
extern void list(unsigned char j);
extern void gq_init(void);
extern void q_init(unsigned char j);
extern void dc(void);//在T0定时中断中


//d.c 的声明
extern void pr(unsigned char n);
extern void prok(void);
extern void ls();
extern unsigned char idata t[];

//s.c
extern void s_init(void);
extern char get(void);
extern char put(char c);
//g.c 的声明
extern void getline (char idata *line, unsigned char n);

//c.c 的声明
extern char gl(char idata *buf,unsigned char n);
extern char idata *skip(char idata *s,char code *a);

#define SIZE 32
char idata buf[SIZE];
//t.c 的声明k
extern void clock(void);
extern char *systime(void);
char settime(char idata *time);
extern bit chg;
//extern unsigned char hour;
//extern unsigned char min;
//a.c的声明
extern char bdata ath;
extern char pass(char *buf,char c,unsigned char n);

//有关数码入队
#include <stdio.h>
//extern char putchar (char);
//extern int printf   (const char *, ...);

//cmd 的声明
extern unsigned char s2n(char idata *s);

extern code void   (code *f[])(void);

extern unsigned char a2n(char idata *s);
extern code char code *HLP[];

//s.c的第二部分声明，有关晶振部分
extern unsigned char crystal;
extern code char code s1200[];
extern code char code *s12[];
extern unsigned char code th0_ov[];
extern unsigned char code tl0_ov[];
//有关按键部分

extern void keys(void);
extern bit k1c,k1f,k1;
extern bit k2c,k2f,k2;


/*SN SN*/
 extern unsigned char oper;
 extern unsigned char sudo(void);

/*SN SN*/
extern bit hold;


void main(void)
{
//debug


 void t0_init(void);
 //unsigned long a=19500;
 unsigned char n;
 unsigned char i;
 t0_init(); 
 s_init();
 //crystal_set;

 printf("hello, i am alive!\n");

 EA=1;
 oe=0;
 gq_init();


/*
auto start in 10 seconds.
*/




#define AUTOSTART 10
 do{
  static unsigned char a_start=AUTOSTART;
  if(a_start){
    if(chg)chg=0,a_start--,
	printf("will start in %d second.\n",(int)a_start);
	if(a_start==0){
       strncpy(buf,"r 0-99,0-99,0-99,0-99,0-99,0-99",32);
	   puts(buf);
	   agg(buf,0);
/*SN SN*/
	   oper=0;
/*SN SN*/
	   oe=1;
	}
  }
  
  if(gl(buf,sizeof(buf))>=0){
    a_start=0;

   	if(hold){
	  if(strcmp(buf,"unhold")==0) hold=0,puts("active");else puts("hold");
	  goto holded;
	}else if(strcmp(buf,"hold")==0){
      hold=1;
	  puts("console holded.");
	  goto holded;
	}

	n=s2n(skip(buf," "));
	if(n>7 && n<=15) n-=8;
	 else if(n>15) n=8;
	for(i=0;buf[i];i++){
	 if(buf[i]=='?'){printf("%s\n",HLP[i]);
	                 break;}
    }
 	(*f[n])();
	

   	if(ath==1) printf("kevin");
	  else if(ath)	printf("root>");
	  else printf("easy");
	printf("@tty>");

  	if(ath!=0xff && buf[0]=='s' && buf[1]=='u') sudo();
	if(ath==0 && strcmp(buf,"i am kevin#")==0)ath=1,printf("nice to hear you! :)");
	if(ath==1 && strcmp(buf,"good bye#")==0)ath=0,printf("see you. :)");
    if(ath==1 && strncmp(buf,"st",2)==0) settime(buf+3);
    if(buf[0]=='p') t[buf[4-2]-'0']=~1<<buf[6-2]-'0' & ~1<<buf[7-2]-'0';

  }

  if(k1c==0 && k1){
   if(hold)
    puts("HOLD");
   else{
    k1=0;
	if(crystal<5)crystal++;else crystal=0;
    TH1=s1200[crystal];
	printf("serial port: %s\n",s12[crystal]);
   }
  }
holded:;

   #define LIMIT_PIN P1_1
   #define LIMIT_CNT 21600L
   LIMIT_PIN=1;
   _nop_();
   _nop_();
   if(ath!=1)
    if(LIMIT_PIN && cur[0]>LIMIT_CNT) cur[0]=LIMIT_CNT;
  gq();

/*SN SN*/
{ 

/*extern vars.*/
  extern unsigned char idata min;
  extern unsigned char idata sec;
  extern unsigned char fmt;
  extern unsigned char oper;
  extern void reset(void);


  const unsigned char lmt=12;
  static unsigned char lt=0;
  static unsigned char fm;
  if(fm!=min && oper){
    lt++;
	fm=min;
  }
  if(ath==0 && lt>=lmt && oper  ){
   lt=0;
   reset();
   printf("trial timeout.");
  }
}
/*SN SN*/
 }while(1);
}

void t0_init(void)
{
 TH0=th0_ov[crystal%6];
 TL0=tl0_ov[crystal%6];
 TMOD&=0xf0;
 TMOD|=0x01;
 TR0=1;
 ET0=1;
 return;
}

void t0(void) interrupt TF0_VECTOR
{
 TH0=th0_ov[crystal];
 TL0=tl0_ov[crystal];
 dc();                                                                                                                                                                                                                                                                                                                      
 clock();
 keys();
 return;
}
