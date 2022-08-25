#include <stdio.h>
#include "stats.h"
#include "../data-structure/test_skip-list.h"
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

  print_hdr("test storage");
  test_storage();
  puts(DIV);

  return 0;
}