#define extern static
#include <asm/io.h>
#undef extern

#include <sys/perm.h>

#include <fstream>

#include "eckbox.h"

#define thresh 42             // threshold of val of black/white
using namespace std;
int main(int argc, char** argv)
{
  ioperm(0x378,1,1);          // gives permission to use port 0x378
  
  long long int t1, t2;
  int p1,p2,href,vref,pix;
  
  p1=inb(0x378);
  t1=rdtsc();
  p2=inb(0x378);
  while(p2-p1<thresh)
    p2=inb(0x378);
  t2=rdtsc();
  
  pix=t2-t1;                 //sets delay time between pixels

  p1=p2;
  t1=t2;
  while(t2-t1<pix+42)
  {
    p2=inb(0x378);
    while(p2-p1<thresh)
      p2=inb(0x378);
    t2=rdtsc();
  }
  href=t2;                   //sets href delay time
  
  p1=p2;
  t1=t2;
  while(t2-t1<href+42)
  {
    p2=inb(0x378);
    while(p2-p1<thresh)
      p2=inb(0x378);
    t2=rdtsc();
  }
  vref=t2;                 //sets vref delay time

  ofstream fout;
  fout.open("/etc/eckbox.conf",ios::out);
  fout<<pix<<endl<<href<<endl<<vref;
  fout.close();
 
  return (0);
}
  
  
