#include <stdio.h>

unsigned char idata hour=0;
unsigned char idata min=0;
unsigned char idata sec=0;
#define TICK_OV (60/0.002)/60




unsigned int idata tick=TICK_OV;
bit chg=1;

void clock(void)
{
 if(--tick);else{
  tick=TICK_OV;
  chg=1;
  if(++sec==60){
    sec=0;
	if(++min==60){
	  min=0;
	  hour++;
	}
  }
 }
 
 


 return;
}


/*

void clock2(void)
{
 if(--tick);else{
   tick=TICK_OV;
   chg=1;
   if(++min==60){hour++;min=0;}//printf("hour=%d\n",hour);} /*未处理小时溢出*/
//   return;//不返回值
/*-/ }

 return;
}*/

char *systime(void)
{
 static char s[7];
/*
 s[7]=0;
 s[5]=min%10+'0';
 s[4]=min/10+'0';
 s[3]=':';
 s[2]=hour%10+'0';
 s[1]=hour/10%10+'0';//if(s[1]=='0')s[1]=' ';
 s[0]=hour/100+'0';if(s[0]=='0'){return s+1;}
*/
 sprintf(s,"%bd:%bd",hour,min);

 return s;
}

char settime(char idata *time)
{
 //"12:12"
 //"01234"
 unsigned char i;
// puts(time);
 for(i=0;i<5;i++){
  if(i==2)continue;
  if(time[i]<'0' || time[i]>'9'){
   return 1;
  }
 }
 if(time[3]>'5')
  return 1;
 hour=(time[0]-'0')*10+time[1]-'0';
 min=(time[3]-'0')*10+time[4]-'0';
 tick=TICK_OV;
 return 0;
}

  


