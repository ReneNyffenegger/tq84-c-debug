#include "tq84_debug.h"

void func_forty_two() {
  TQ84_DEBUG_INDENT();
  TQ84_DEBUG("I am in func_forty_two");
}

void func_ninety_nine(int from, int to) {
  TQ84_DEBUG_INDENT_T("func_ninety_nine");

  { TQ84_DEBUG_INDENT_T("loop from %d to %d", from, to);

    for (int i=from; i<to; i++) {
      TQ84_DEBUG("i=%d", i);
    }
    TQ84_DEBUG("Loop is over");
  }
}

void func_a(int i) {
  TQ84_DEBUG_INDENT_T("func_a i=%d", i);

  if (i == 42) {
    TQ84_DEBUG("Calling func_forty_two");
    func_forty_two();
  }
  else if (i == 99) {
    TQ84_DEBUG("Calling func_ninety_nine");
    func_ninety_nine(5, 10);
  }

}

int main() {
  tq84_debug_open("w");
  TQ84_DEBUG_INDENT_T("main");

  TQ84_DEBUG("Calling func_a with 42");
  func_a(42);
  TQ84_DEBUG("Calling func_a with 99");
  func_a(99);
  TQ84_DEBUG("Calling func_a with 57");
  func_a(57);

}
