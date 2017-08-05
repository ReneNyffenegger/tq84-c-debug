#include "tq84_debug.h"

void func_b() {
TQ84_DEBUG_INDENT(1, "func_a");

//tq84_debug_dedent(1);
}

void func_a() {
  TQ84_DEBUG_INDENT(1, "func_a");

  tq84_debug(1, "Calling func_b");
  func_b();

//tq84_debug_dedent(1);
}

int main() {
  tq84_debug_open();
  TQ84_DEBUG_INDENT(1, "main");

  tq84_debug(1, "Calling func_a");
  func_a();

//tq84_debug_dedent(1);
}
