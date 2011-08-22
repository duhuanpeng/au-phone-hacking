#include <at89x52.h>
#include <stdio.h>
#include <ctype.h>
//控制台
#define CNTLQ      ('Q'-'A'+1)
#define CNTLS      ('S'-'A'+1)
#define DEL        0x7F
#define BACKSPACE  0x08
#define CR         0x0D
#define LF         0x0A
char gl(char idata *buf,unsigned char n)
{
 static char pos=0;
 char c;

 if(RI==0) return ~pos;

 c=SBUF;
 RI=0;

 if(c==CR){
  c=LF;
  putchar(c);
  buf[pos==n-2?n-1:pos]=0;
  c=pos;
  pos=0;
  return c;
 } //充许输出空串

 if(c==BACKSPACE || c==DEL){
  if(pos!=0){
     pos--;
	 putchar('\b');
	 putchar(' ');
	 putchar(0x08);
   }
  return ~pos;
 }
 if(c!=CNTLQ && c!=CNTLS && pos==n-2){
  buf[pos]=c;
  putchar(c);
  putchar(0x08);
  return ~pos;
 }
 if(c!=CNTLQ && c!=CNTLS){
  //putchar(buf[pos++]=c);
  buf[pos]=c;
#define PIN 0xff

#if PIN
  putchar( buf[0]=='s' && buf[1]=='u' && pos>2 ? '*' :buf[pos]);
#else
  putchar(buf[pos]);
#endif

  pos++;
  if(pos>=n){
   c=pos;
   pos=0;
   buf[c-1]=0;
   putchar(LF);
   return c;
  }else{
   return ~pos;
  }
 }
 return ~pos;
} 


char idata *skip(char idata *s,char code *a)
{
	char *p;
	while(*s){
		p=a;
		while(*p){
			if(*p==*s)break;
			p++;
		}
		if(*p)
			s++;
		else
			break;
		}
	return(s);

}

char idata *skipnum(char idata *s)
{
	while(*s){
		if(*s<'0' || *s>'9') break;
		s++;
	}
	return(s);
}








 
