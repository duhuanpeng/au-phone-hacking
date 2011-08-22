#include <stdio.h>
#include <string.h>

extern bit oe;
extern void ls(void);


 extern char *systime(void);
 extern unsigned char on;


#define SIZE 32
extern char idata buf[SIZE];

#define T_UNIT 2


//char code *cmd[]={
///*0		0*/"time","t",//查看/设置系统时间 t
//*2		1*/"seton","o",//设置按住时间 o
//*4		2*/"setoff","x",//设置松开时间 x
//*6		3*/"setdig","n",//设置密码位数 n
//*8		4*/"range","r",//测试范围 r
//*10	5*/"stop","s",//停止计数 s
//*12	6*/"list","l", //列出队列 l
//*14	7*/"format","f",//格式
//*16	8*/""};
bit hold=0;
/*lock up the operator.*/
code char code *cmd[]={
"time","seton","setoff","setdig","range","stop","list","format",
"t","o","x","n","r","s","l","f",""};

code  char code *HLP[]={
"help of time",//0
"help of seton",//1
"help of setoff",//2
"help of setdig",//3
"help of range",//4
"help of stop",//5
"help of list",//6
"help of format",//7
"help of system"};


code char code *p_cmd[]={
"*time",
"*seton",
"*setoff",
"*setdig",
"*range",
"*stop",
"*list",
"*format",
"*system"};
/*
增加认证功能
*/
extern char bdata ath;
extern char bdata atl;
/***************/

unsigned char s2n(char idata *s)
{
 unsigned char i;
 i=0;
 while(*cmd[i]){
  if(strncmp(cmd[i],s,strlen(cmd[i])))i++;else break;
 }
 return i;
}

 
unsigned char a2n(char idata *s)
{
 unsigned char n=0;
 
 while((*s<='0' || *s>'9') && *s)
  s++;

 if(*s=='\0') return 0;
 n=*s-'0';
 s++;
 if(*s<'0' || *s>'9') return n;
 n*=10;
 n+=*s-'0';
 s++;
 if( *s<'0' || *s>'9' || n>25 ) return n;
 
 n*=10;
 if(n==250 && *s>'5')n=255;
 else n+=*s-'0';
 return n;
}
 

/*
 while(n<=~0){
  n*=10;
  n+=*s-'0';
  s++;
  if(*s<'0' || *s>'9')break;
 }
 return n;
}*/


void cmd_time(void)
{
 printf("system uptime:%s\n",systime());
}


static unsigned char xa=2,xb=255;//for on off adjustment
static unsigned char oa=2,ob=255;


void cmd_seton(void)
{
 /*commands:
 seton N
 o N
 o
 in further
 o+
 o-
 seton+
 seton-
 */
 unsigned char n;



 n=a2n(buf);

 if(n){
  on=n;
  printf("the \"on\" duration is updated to %d ticks(%d ms).\n",(int)on,(int)(on*T_UNIT));
  return;
 }

 n=0;
 while(buf[n]){
  if(buf[n]=='+'){
    oa=on;
	on>>=1;
	on+=ob/2;
/*	printf("--debug--\n"
	       "oa:%d\n"
		   "ob:%d\n"
		   "on:%d\n",(int)oa,(int)ob,(int)on);*/
	printf("the \"on\" duration is increase to %d ticks(%d ms).\n",(int)on,(int)(on*2));
	return;
  }
  else if(buf[n]=='-') {
    ob=on;
	on>>=1;
	on+=oa/2;

/*
     printf("--debug--\n"
	       "oa:%d\n"
		   "ob:%d\n"
		   "on:%d\n",(int)oa,(int)ob,(int)on);*/

   	printf("the \"on\" duration is decrease to %d ticks(%d ms).\n",(int)on,(int)(on*2));
	return;
  }
  else if(buf[n]=='?'){
   printf(
   "**online help:\n"
   "**command:seton\n"
   "**function:adjust the \"on\" state duration.\n"
   "**useage:\n"
   "  seton N\n"
   "  o N\n"
   "**note: N is a number between 1 to 255(2ms-510ms).\n"
   );
   return;
  }
  n++;
 }
 printf("current \"on\" state duration is %d ticks(%d ms).\n",(int)on,(int)(on*2));
 return;
}
extern unsigned char of;

void cmd_setoff(void)
{
 /*commands:
 setoff N
 x N
 x
 in further
 x+
 x-
 setoff+
 setoff-
 */
 unsigned char n;
 n=a2n(buf);

 if(n){
  of=n;
  printf("the \"off\" duration is updated to %d ticks(%d ms).\n",(int)of,(int)(of*2));
  return;
 }

 n=0;
 while(buf[n]){
  if(buf[n]=='+'){
    oa=of;
	of>>=1;
	of+=xb/2;
/*	printf("--debug--\n"
	       "oa:%d\n"
		   "ob:%d\n"
		   "on:%d\n",(int)oa,(int)ob,(int)on);*/
	printf("the \"off\" duration is increase to %d ticks(%d ms).\n",(int)of,(int)(of*2));
	return;
  }
  else if(buf[n]=='-') {
    xb=of;
	of>>=1;
	of+=xa/2;

/*
     printf("--debug--\n"
	       "oa:%d\n"
		   "ob:%d\n"
		   "on:%d\n",(int)oa,(int)ob,(int)on);*/

   	printf("the \"off\" duration is decrease to %d ticks(%d ms).\n",(int)of,(int)(of*T_UNIT));
	return;
  }
  else if(buf[n]=='?'){
   printf(
   "**online help:\n"
   "**command:setoff\n"
   "**function:adjust the \"off\" state duration.\n"
   "**useage:\n"
   "  setoff N\n"
   "  x N\n"
   "**note: N is a number between 1 to 255(2ms-510ms).\n"
   );
   return;
  }
  n++;
 }
 printf("current \"off\" state duration is %d ticks(%d ms).\n",(int)of,(int)(of*T_UNIT));
 return;
}
extern unsigned char dg;

void cmd_setdig(void)
{
 /*supported command:
 setdig N
 n N
 n
 */
 unsigned char n;
 n=a2n(buf);
 if(n>=3 && n<=8) dg=n,printf("set to %d digitals.\n",(int)dg);
  else if(n==0) printf("system now is for %d digitals.\n",(int)dg);
  else printf("bad argument,only suport 3 to 8 digitals.\n");
 return;
}
void cmd_range(void)
{
 extern unsigned char ag(char *l,unsigned char j);
 extern void agg(char *l,unsigned char j);
 extern void list(unsigned char j);
 void cmd_list(void);
 unsigned char i=0;
 while(buf[i]){
  if(buf[i]>='0' && buf[i]<='9')break;
  i++;
 }
 if(buf[i]) agg(buf,0);
 oe=1;
 list(0);


}
void cmd_stop(void)
{
 extern unsigned long idata cur[];
 oe=0;
 ls();
 list(0);
 printf("count to %lu stopped!\n",cur[0]);
}



void cmd_list(void)
{
 extern void list(unsigned char j);
 extern unsigned long idata cur[];
 list(0);
 printf("current number is %lu\n",cur[0]);
}
extern unsigned char fmt;


void fmtprt(void)
{
 unsigned char i;
 for(i=0;i<dg;i++)
  putchar('*');
 for(i=0;i<fmt;i++)
  putchar('#');
 return;
}

 

void cmd_format(void)
{
 unsigned char i=0,j,k;
 while(buf[i]!='*' && buf[i]!='#' && buf[i])i++;
 for(j=i;buf[j]!='#' && buf[j];j++);
 for(k=j;buf[k]=='#' && buf[k];k++);
 /*debug
 printf("%d %d %d\n",(int)i,(int)j,(int)k);
 printf("%d %d\n",(int)(j-i),(int)(k-j));
 */
 
 i=j-i;
 j=k-j;
 k=0;
 if(i==0 && j==0){
  printf("current output format is:");
  fmtprt();
  putchar('\n');



  return;
 }
 if(i>=3 && i<=8) dg=i,k++;
 if(j>=0 && j<=2) fmt=j,k++;
 if(k){
  printf("format is updated to:");
  fmtprt();
  putchar('\n');
 }else{
  printf("bad argument.");
 }

 return;
}
void cmd_error(void)
{
 if(*buf) puts("bad command.");
}
code void   (code *f[])(void)={
cmd_time,cmd_seton,cmd_setoff,cmd_setdig,
cmd_range,cmd_stop,cmd_list,cmd_format,
cmd_error};
