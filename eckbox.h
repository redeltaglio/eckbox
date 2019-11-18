// file: eckbox.h
// contains classes and functions used in eckbox prog

extern inline unsigned long long int rdtsc() // rdtsc: returns # of cpu cycles elapsed since startup
{
  unsigned long long int x;
  asm volatile(".byte 0x0f, 0x31" : "=A" (x));
  return x;
}

int pause(int cycles) //pause: pauses cycles number of CPU cycles.  returns exact cpu cycles delayed
{
  unsigned long long int x=rdtsc();
  for(int i=0; i<cycles/10; i++)
    asm("nop");
  unsigned long long int y=rdtsc();
  return y-x;
}
