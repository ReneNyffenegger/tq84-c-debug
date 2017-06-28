#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "tq84_debug.h"

static FILE* f_debug = NULL;

int   indent;

// #define TQ84_DEBUG 1

void tq84_debug_out(const char* fmt, va_list ap) {
#ifdef TQ84_DEBUG

  if (! f_debug) tq84_debug_open();

//va_list ap; va_start(ap, fmt);
  vfprintf(f_debug, fmt, ap);

//fprintf(f_debug, "\n");
#endif
}

void tq84_debug_indent_() {
#ifdef TQ84_DEBUG

  if (! f_debug) tq84_debug_open();

  int i;
  for (i=0; i<indent*2; i++) {
    fprintf(f_debug, " ");
  }
#endif
}

void tq84_debug_open() {
#ifdef TQ84_DEBUG
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
//    "tq84_debug_%4d-%02d_%02d_%02d.%02d.%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
      "tq84_debug");

  f_debug = fopen(file_name, "a");
#endif
}

void tq84_debug_indent(const char* fmt, ...) {
#ifdef TQ84_DEBUG

  va_list ap; va_start(ap, fmt);
 
  tq84_debug_indent_();
  tq84_debug_out(fmt, ap);

//tq84_debug_out("{\n", NULL);
  fprintf(f_debug, " {\n");
  fflush(f_debug);

  indent++;
#endif
}

void tq84_debug_dedent(/*const char* fmt, ...*/) {
#ifdef TQ84_DEBUG

  indent--;
  tq84_debug_indent_();

//tq84_debug_out("}\n", NULL);
  fprintf(f_debug, "}\n");
  fflush(f_debug);

#endif
}
void tq84_debug(const char* fmt, ...) {
#ifdef TQ84_DEBUG
  va_list ap; va_start(ap, fmt);

  tq84_debug_indent_();
  tq84_debug_out(fmt, ap);

//tq84_debug_out("\n", NULL);
  fprintf(f_debug, "\n");

  fflush(f_debug);
#endif
}
