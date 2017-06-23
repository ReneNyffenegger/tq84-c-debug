#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "tq84_debug.h"

FILE* f_debug = NULL;

int   indent;


void tq84_debug_out(const char* fmt, va_list ap) {
//va_list ap; va_start(ap, fmt);
  vfprintf(f_debug, fmt, ap);

  fprintf(f_debug, "\n");
}

void tq84_debug_indent_() {
  int i;
  for (i=0; i<indent*2; i++) {
    fprintf(f_debug, " ");
  }
}

void tq84_debug_open() {
  time_t t;
  struct tm tm;
  char file_name[200];

  t=time(NULL);
  tm = *localtime(&t);

  sprintf(file_name,
#ifdef unix
      "/tmp/"
#else
      "c:\\temp\\"
#endif
      "tq84_vim_debug_%4d-%02d_%02d_%02d.%02d.%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  f_debug = fopen(file_name, "a");
}


void tq84_debug_indent(const char* fmt, ...) {

  va_list ap; va_start(ap, fmt);
 
  tq84_debug_indent_();
  tq84_debug_out(fmt, ap);

  tq84_debug_out("{\n", NULL);

  indent++;
}
void tq84_debug_dedent(/*const char* fmt, ...*/) {

  tq84_debug_indent_();
//va_list ap; va_start(ap, fmt);
//tq84_debug_out(fmt, ap);

  tq84_debug_out("}\n", NULL);

  indent--;
}
void tq84_debug(const char* fmt, ...) {
  va_list ap; va_start(ap, fmt);
  tq84_debug_out(fmt, ap);

  tq84_debug_indent_();

  tq84_debug_out("\n", NULL);
}
