/*与接键板硬件相关的驱动*/
#include <at89x52.h>
#include <stdio.h>
void pr(unsigned char n);
void prok(void);
void ls();




//按键的设定
#define C(n) ~(1<<(n+3))
#define L(n) ~(1<<(n-1))
#define B(n) (~(1<<n))
#define CL(x,y) (B(x)) & (B(y))

unsigned char idata t[]={

CL(1,6),		//0

CL(2,5),		//1
CL(2,6),		//2
CL(2,7),		//3

CL(3,5),		//4
CL(3,6),		//5
CL(3,7),		//6

CL(4,5),		//7		
CL(4,6),		//8
CL(4,7),		//9

B(0)		//OK
};



void pr(unsigned char n)
{
 P0=t[n];
 return;
}
void prok(void)
{
 //putchar('K');
 P0=t[10];
}
void ls()
{
 //putchar('L');
 P0=P2=0xff;
 return;
}

