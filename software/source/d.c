/*与接键板硬件相关的驱动
#include <at89x52.h>
#include <stdio.h>
void pr(unsigned char n);
void prok(void);
void ls();




//按键的设定
#define B(n) ~(1<<n)
unsigned char idata t[]={
    B(4),	//0
 B(0),		//1
 B(1),		//2
 B(2),		//3
 B(4),		//4
 B(5),		//5
 B(6),		//6
    B(0),	//7		
	B(1),	//8
	B(2),	//9

	B(5)	//10
 };



void pr(unsigned char n)
{
 //putchar('0'+n);

 if(n>0 && n<7){
  P0=t[n];
 }else{
  P2=t[n];
 }
 return;
}
void prok(void)
{
 //putchar('K');
 P2=t[10];
}
void ls()
{
 //putchar('L');
 P0=P2=0xff;
 return;
}
*/
