#include <stdio.h>
//d.c ������
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

//ͬʱ��Ĳ���
//��һ������
bit dr=0;//�ѷֽ����׼����־
bit oe=0;//������������
#define ms(n) (n/2)
unsigned char on=ms(70);//��סʱ��
unsigned char of=ms(72);//�ɿ�ʱ��
unsigned char dg=5;//����λ��
unsigned char q[GS][8];//��λ����֮�ڿ�����
unsigned char idata qn=0;//�����ڼ�λ?��0��ʼ������

unsigned char fmt=2;


//�й��������

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
/*����������*/


unsigned char ag(char *l,unsigned char j)
/*�� *l �� j �� ��g[j][...]*/
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

/*��������*/
void dc(void)
{
 static unsigned char cnt;
 unsigned char i;
/*ÿ��ʱ��ⷢ pr(),ls().�ӿ�droe*/
 if(oe==0) goto b0;
 if(cnt) { cnt--; goto b0;}

 if(qn<(dg)  && qn>=0){
  for(i=0;i<GS;i++){
   pr(q[i][qn]);//P?=q[qn]; ����q[qn]
  }
  qn=~qn;
  cnt=on;//��ס��ʱ��
 }else if(qn==dg || qn==dg+1){
//  
if(fmt==1 && qn==dg+1) goto esc;
if(fmt==0)goto esc;
//
  prok();//
esc:;
  qn=~qn;
  cnt=on;

 }else if(qn>255-dg-2){//��λ �߸� Nλ N+1��
  ls();//�ɿ����м� ???
  qn=~qn;
  if(qn==dg-1){dr=0;}//�������λ����,�´ΰ�OK
  qn++;
  if(qn==dg)dr=0;//�Ѿ����������.����׼����
  cnt=of;//�ɿ���ʱ��
 }else if(dr){
  qn=0;//�������׼����,����׼����ʼ
 }
 //qn==dg+1ʱ�˳�
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






