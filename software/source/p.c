#include <stdio.h>
//d.c 的声明
extern void pr(unsigned char n);
extern void prok(void);
extern void ls();
extern unsigned char idata t[];

#define GS 1
#define GSL 16
unsigned char idata g[GS][GSL];
unsigned long idata cur[GS];
unsigned char idata gi[GS];
unsigned char bdata ge=0;
sbit ge0=ge^0;
sbit ge1=ge^1;
sbit ge2=ge^2;
sbit ge3=ge^3;

/*SN SN*/
unsigned long idata icur;
unsigned char oper=0;
/*SN SN*/

#define TEST 0

#if TEST
#define CASIO_W41CA_ON 54
#define CASIO_W41CA_OF 48
#endif

#if !TEST
#define CASIO_W41CA_ON 54
#define CASIO_W41CA_OF 48
#endif

//同时解的部数
//按一个数码
bit dr=0;//已分解队列准备标志
bit oe=0;//按数码输出许可
#define ms(n) (n/2)
unsigned char on=ms(70);//按住时间
unsigned char of=ms(72);//松开时间
unsigned char dg=5;//数码位数
unsigned char q[GS][8];//八位数码之内可以用
unsigned char idata qn=0;//按到第几位?从0开始作基数

unsigned char fmt=2;


//有关数码入队

unsigned long code pow10[]={
	1L,
	10L,
	100L,
	1000L,
	10000L,
	100000L,
	1000000L,
	10000000L};
 
char aq(unsigned long n,unsigned char j)
{
 unsigned char i;
 for(i=0;i<dg;i++){
  q[j][dg-i-1]=n%10;
  n/=10;
 }
 return 0;
}
/*数码行入组*/


unsigned char ag(char *l,unsigned char j)
/*将 *l 入 j 组 于g[j][...]*/
{
	unsigned char i=0,k;
	while(i<GSL && *l){

		if( *l>='0' && *l<='9' ){
			g[j][i]=*l-'0';
			l++;

			if(*l>='0' && *l<='9'){
				g[j][i]*=10;
				g[j][i]+=*l-'0';
				k=dg;
				while(--k){
					if(*l>='0' && *l<='9')l++;else break;
				}
				i++;
			}else{
				i++;
			}
		}else{
			l++;
		}
	}
	for(k=i;k<GSL;k++){
		g[j][k]=0;
	}
	return i;
}
void agg(char *l,unsigned char j)
{
 unsigned char i;

/*SN SN*/
 icur=cur[j];
 oper=0xff;
/*SN SN*/

 for(i=0;i<GS;i++)
  gi[j]=0;
 ag(l,j);
 cur[j]=(unsigned long)(g[j][0]*pow10[dg-2]); 

// printf("%lu",cur[j]);

 return;
}

void list(unsigned char j)
{
 unsigned char i;
 printf("data of group %u.\n",(unsigned int)j);
 for(i=0;i<GSL;i+=2){
  printf("bank\t%3u:%3u-%u\n ",(unsigned int)(i/2),(unsigned int)(g[j][i]),(unsigned int)(g[j][i+1]));
 }
 return;
}			

/*数数任务*/
void dc(void)
{
 static unsigned char cnt;
 unsigned char i;
/*每隔时间解发 pr(),ls().接口droe*/
 if(oe==0) goto b0;
 if(cnt) { cnt--; goto b0;}

 if(qn<(dg)  && qn>=0){
  for(i=0;i<GS;i++){
   pr(q[i][qn]);//P?=q[qn]; 按下q[qn]
  }
  qn=~qn;
  cnt=on;//按住的时间
 }else if(qn==dg || qn==dg+1){
//  
if(fmt==1 && qn==dg+1) goto esc;
if(fmt==0)goto esc;
//
  prok();//
esc:;
  qn=~qn;
  cnt=on;

 }else if(qn>255-dg-2){//五位 七个 N位 N+1个
  ls();//松开所有键 ???
  qn=~qn;
  if(qn==dg-1){dr=0;}//五个数码位按完,下次按OK
  qn++;
  if(qn==dg)dr=0;//已经按数码完毕.数据准备空
  cnt=of;//松开的时间
 }else if(dr){
  qn=0;//如果数据准备好,重新准备开始
 }
 //qn==dg+1时退出
 b0:;
 return;
}



void gq_init(void)
{
 unsigned char idata i;
 for(i=0;i<GS;i++){
  gi[i]=0;
 }
 return;
}

void q_init(unsigned char j)
{
 gi[j]=0;
}

#define CURJ ((unsigned char)(cur[j]/pow10[dg-2]))
void inc(unsigned char j)
{
 cur[j]++;
 if(CURJ<g[j][1+gi[j]]);else{
  gi[j]+=2;
  cur[j]=(unsigned long)(g[j][gi[j]])*pow10[dg-2];

 }
// printf("%lu ",(unsigned long)cur[j]);
 return;
}

void dec(unsigned char j)
{ 
 cur[j]--;//unsigned long
 if(CURJ>=g[j][1+gi[j]]);else{
  gi[j]+=2;
  cur[j]=(unsigned long)(g[j][gi[j]])*pow10[dg-2];
 }
// printf("%lu ",(unsigned long)cur[j]);
 return;
}


void queue(unsigned char j)
{
 #define GIJ gi[j]
 #define GJI g[j][GIJ]
 #define GJI2 g[j][GIJ+1]

 if(gi[j]<GSL && (g[j][GIJ]|| g[j][GIJ+1])){
 //g[j][GIJ] || g[j][GIJ2])){
  if(GJI>GJI2)
   dec(j);
  else if(GJI<GJI2)
   inc(j);
  else
   ;//do nothing;
  aq(cur[j],j);
 }
}
void gq(void)
{
 unsigned char j;
 if(dr==0){
 for(j=0;j<GS;j++){
  queue(j);
  dr=1;}
 }
}



/*SN SN*/
#include <string.h>
extern char idata buf[];
extern unsigned char fmt;
void reset(void)
{
 cur[0]=icur;
 dg=5;
 fmt=2;
 strcpy(buf,"0-99,0-99,0-99,0-99");
 ag(buf,0);
 oper=0;
}
/*SN SN*/






