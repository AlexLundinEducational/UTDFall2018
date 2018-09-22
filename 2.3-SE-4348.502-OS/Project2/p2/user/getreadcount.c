#include "types.h"
#include "user.h"
#include "syscall.h"

int
main(int argc, char *argv[])
{
  int returnedCount =  getreadcount();
  printf(1, "\nKernel has called read this many times since boot:\n\t", returnedCount);
  exit();
}
