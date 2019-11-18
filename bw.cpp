#include <vga.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
  if(argv[1])
    cout<<"Starting...Will exit after "<<argv[1]<<" seconds.\n";
  else
  {
    cout<<"Usage:\n";
    cout<<"\tbw [seconds]\n";
    cout<<"Also, recommended autoadjust of monitor before this program's execution.\n";
    exit(0);
  }
  sleep(4);
  vga_init();
  vga_setmode(G800x600x256);
  for(int i=0; i<600; i++)
  {
    for(int k=0; k<800; k+=2)
    {
      vga_setcolor(0);
      vga_drawpixel(k,i);
      vga_setcolor(15);
      vga_drawpixel(k+1,i);
    }
  }
  if(argc==0)
    sleep(15);
  else
    sleep(atoi(argv[1]));
  vga_setmode(TEXT);
  return(0);
}
      
