#include <stdio.h>
#include "stats.h"
#include "../data-structure/skip-list_test.h"
#include "../data-structure/storage_test.h"

void print_hdr(char *title) {
  puts(DIV);
  puts(title);
  puts(DIV);
}

int main() {
  print_hdr("test skipList");
  test_skipList();
  puts(DIV);
  puts("");

  print_hdr("test storage");
  test_storage();
  puts(DIV);

  return 0;
}