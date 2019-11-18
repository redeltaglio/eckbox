/*******************************************************
 *     Authors:                                        *
 *     Nick Rupert - NuclearDachshund@yahoo.com.au     *
 *     Luke Garfield - artofluke@cox.net               *
 *                                                     *
 *     Project Homepage: http://eckbox.sourceforge.net *
 *                                                     *
 *     License: Jabber Open Source License             *
 *******************************************************/

#include <vga.h>

#define extern static
#include <asm/io.h>
#undef extern

#include <sys/perm.h>
#include <fstream>

#include "eckbox.h"

using namespace std;

int main(int argc, char** argv)
{
  vga_init();
  vga_setmode(G800x600x256);

  int pix, href, vref, x, y;
  if(argv[1])
  {
    x=atoi(argv[1]);
    y=atoi(argv[2]);
  }
  else
  {
    x=800;
    y=600;
  }

  ifstream fin;
  fin.open("delays",ios::in);
  fin>>pix;
  fin>>href;
  fin>>vref;
  fin.close();

  ioperm(0x378,1,1);
  
  int p1, p2;
  unsigned long long int t1=0, t2=0;

  while(t2-t1<vref-50)   //this while just pauses execution until
  {                      // a vref has been done
    p1=inb(0x378);
    t1=rdtsc();
    p2=inb(0x378);
    while(p2<10)   //10 here is approx noise val for no pixel
    {
      inb(0x378);
      t2=rdtsc();
    }
  }

  while(true)
  {
    for(int i=0; i<y; i++)
    {
      for(int k=0; k<x; k++)
      {
	p1=inb(0x378);
	if(p1<128)
	{
	  vga_setcolor(0);
	  vga_drawpixel(k,i);
	}
	else
	{
	  vga_setcolor(15);
	  vga_drawpixel(k,i);
	}
	if(k<x-1)
	  pause(pix);
	else if(k==x-1 && i<y-1)
	  pause(href);
	else
	  pause(vref);
      }
    }
  }
  vga_setmode(TEXT);
  return (0);
}
