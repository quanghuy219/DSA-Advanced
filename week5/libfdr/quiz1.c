#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include "jval.h"
#include "dllist.h"
#include "jrb.h"

int main()
{
  Jval a,b;
  a.i = 1;
  b.i = 2;

  Dllist d = new_dllist();
  dll_append(d,a);
  dll_append(d,b);

  Dllist c;
  dll_traverse(c,d) {
  	printf("%d\n",jval_i(c->val) );
  };
  
  return 0;
}
