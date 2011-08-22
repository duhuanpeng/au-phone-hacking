//хож╓
#include <stdio.h>
#include <string.h>
#define CR         0x0D
#define BACKSPACE  0x08
#define ESC        27


code char code pw[]="su fjlo-dgh-wdad";
char bdata ath=0;
char bdata atl=0;
unsigned char block=10000;
extern char idata buf[];
unsigned char sudo(void)
{
 unsigned char i;
 #define AT ath
 AT=0xff;
 for(i=0;i<strlen(pw);i++){
   if(pw[i]=='-')continue;
   if(buf[i]!=pw[i]) AT=0;
 }
/*
 debug
 puts("******\n");
 puts(buf);
 putchar('0'+strlen(pw));
 puts(pw);*/
 if(AT) printf("work in smart mode!\n");
   else printf("switch to smart mode failed.\nstill in easy mode.\nplease type r <ENTER>\n");
 return AT;
}

