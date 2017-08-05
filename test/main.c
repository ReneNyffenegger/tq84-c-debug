#include "tq84_debug.h"

void func_b() {
  tq84_debug_indent(1, "func_a");

  tq84_debug_dedent(1);
}

void func_a() {
  tq84_debug_indent(1, "func_a");

  tq84_debug(1, "Calling func_b");
  func_b();

  tq84_debug_dedent(1);
}

int main() {
  tq84_debug_indent(1, "main");

  tq84_debug(1, "Calling func_a");
  func_a();

  tq84_debug_dedent(1);
}
