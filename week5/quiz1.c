#include <stdio.h>
#include <stdlib.h>
#include "libfdr/jval.h"
#include "libfdr/dllist.h"

int main()
{
  Jval a,b;
  a.i = 1;
  b.i = 2;

  Dllist d = new_dllist();

  return 0;
}
