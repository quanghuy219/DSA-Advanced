#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "jval.h"
#include "dllist.h"
#include "jrb.h"

int main()
{
  IS is;
  JRB list, node;
  Dllist tmp, lines;

  is = new_inputstruct(NULL);
  list = make_jrb();

  while (get_line(is) >= 0) {
    for (int i = 0; i < is->NF; i++)
    {
      list = jrb_find_str(list, is->fields[i]);
      if (list == NULL)
      {
        list = jrb_insert_str(list, strdup(is->fields[i]), new_jval_v(new_dllist()));
      }
      lines = (Dllist) node->val.v;
      dll_append(lines, new_jval_i(is->line));
    }
  }

  jrb_traverse(node, list) {
    printf("%-20s: ", list->key.s);
    lines = (Dllist) list->val.v;
    dll_traverse(tmp, lines) {
      if (tmp != dll_first(lines)) printf(" , ");
      printf(" %d\n", tmp->val.i);
    }
  }
  
  return 0;
}
