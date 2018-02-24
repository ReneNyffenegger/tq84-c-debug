#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "tq84_debug.h"

#define TQ84_DEBUG_ENABLED

#ifdef TQ84_DEBUG_ENABLED

#if !defined(TQ84_DEBUG_TO_FILE) && !defined(TQ84_DEBUG_TO_MEMORY)
  #error "Specify TQ84_DEBUG_TO_FILE or TQ84_DEBUG_TO_MEMORY"
#endif

#ifndef TQ84_DEBUG_TO_FILE
//#define TQ84_DEBUG_TO_FILE
#endif

int   indent;

#ifdef TQ84_DEBUG_TO_FILE
static FILE* f_debug = NULL;
#else
// char tq84_debug_line[2048]; 
// int  tq84_debug_line_pos = 0;
   #define  tq84_debug_memory_size 0x40000
   char tq84_debug_memory[tq84_debug_memory_size]; 
   int  tq84_debug_memory_pos = 0;
   int  tq84_debug_memory_already_written = 0;
#endif

/* -------------------------------------------------------------------
  
   Allow the user to define TQ84_DEBUG_EXPORT in order to
   export(?) the tq84_debug* functions.
   If no such definition was made, the TQ84_DEBUG_EXPORT is
   set to nothing.
*/
#ifndef TQ84_DEBUG_EXPORT
#define TQ84_DEBUG_EXPORT
#endif
/* ------------------------------------------------------------------- */

TQ84_DEBUG_EXPORT void tq84_debug_var_goes_out_of_scope(int* v __attribute__((unused)) ) {
  tq84_debug_dedent();
}


TQ84_DEBUG_EXPORT void tq84_debug_out_va_list(const char* fmt, va_list ap) {
#ifdef TQ84_DEBUG_ENABLED
  #ifdef TQ84_DEBUG_TO_FILE
    vfprintf(f_debug, fmt, ap);
  #else
    tq84_debug_memory_pos += vsprintf(&tq84_debug_line[tq84_debug_memory_pos], fmt, ap);
  #endif
#endif
}

TQ84_DEBUG_EXPORT void tq84_debug_out(const char* fmt, ...) {
#ifdef TQ84_DEBUG_ENABLED
  va_list ap; va_start(ap, fmt);
  tq84_debug_out_va_list(fmt, ap);
#endif
}

TQ84_DEBUG_EXPORT void tq84_debug_end_line() {
#ifdef TQ84_DEBUG_ENABLED
  #ifdef TQ84_DEBUG_TO_FILE
    fprintf(f_debug, "\n");
    fflush(f_debug);
  #else
    static int already_written = 0;
    const char* filename = "/tmp/tq84-debug";

    tq84_debug_memory[tq84_debug_memory_pos++] = "\n";

    if (tq84_debug_memory_pos > tq84_debug_memory_size - 255) {

       if (! tq84_debug_memory_already_written) {
         int f = fopen(filename, "w");
         fprintf(f, tq84_debug_memory);
         fclose(f);
         tq84_debug_memory_already_written = 1;
      }

    }

    
    #if 0
    openlog("inittq84", 0, LOG_DAEMON);
    syslog(LOG_INFO, "%s", tq84_debug_line);
    closelog();
    tq84_debug_line_pos=0;
    #endif
  #endif
#endif
}

#endif
/*
static int tq84_debug_dont_env(TQ84_DEBUG_ENV_TYPE env) {
  if (env ==    1) return 0;
  if (env ==    2) return 0; // net_processing.cpp
  if (env ==    3) return 0; // wallet/wallet.cpp
  if (env ==    4) return 0; // txdb.cpp
  if (env ==    5) return 0; // validation.cpp
  if (env ==    6) return 0; // init.cpp
  if (env ==    7) return 0; // net.cpp
  if (env ==    8) return 0; // wallet/walletdb.cpp
  if (env ==    9) return 0; // wallet/rpcdump.cpp
  if (env ==   10) return 0; // wallet/crypter.cpp
  if (env ==   11) return 1; // wallet/wallet.cpp      CWallet::GetDebit, CWallet::IsFromMe, CWallet::AddToWalletIfInvolvingMe, CWallet::SyncTransaction
  if (env ==   12) return 0; // qt/bitcoin.cpp
  if (env ==   13) return 0; // qt/winshutdownmonitor.cpp
  if (env ==   14) return 0; // wallet/db.cpp
  if (env ==   15) return 0; // key.cpp

  return 1;
}
*/

static void tq84_debug_indent_() {
#ifdef TQ84_DEBUG_ENABLED
  int i;
  for (i=0; i<indent*2; i++) {
    tq84_debug_out(" ");
  }
#endif
}

static void tq84_debug_indent_null() {
#ifdef TQ84_DEBUG_ENABLED
  tq84_debug_out("%-50s %-20s %4s: ", "", "", "");
  tq84_debug_indent_();
#endif
}

static void tq84_debug_indent_position(const char* filename, const char* funcname, unsigned int line) {
#ifdef TQ84_DEBUG_ENABLED
  tq84_debug_out("%-50s %-20s %4d: ", filename, funcname, line);
  tq84_debug_indent_();
#endif
}

#ifdef TQ84_DEBUG_TO_FILE
TQ84_DEBUG_EXPORT void tq84_debug_open(
    const char* filename, const char* mode_a_or_w
) { /* mode_a_or_w: a = append to log file, w = create it */
#ifdef TQ84_DEBUG_ENABLED
  /*
  time_t t;
  struct tm tm;
  */
  char file_name[200];

  if (f_debug) {
    /* Don't reopen */
    return;
  }

  /*
  t=time(NULL);
  tm = *localtime(&t);
  */

  sprintf(file_name,
/*
#ifdef __unix__
      "/tmp/"
#else
      "c:\\temp\\"
#endif
*/
/*    "tq84_debug_%4d-%02d_%02d_%02d.%02d.%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); */
      filename);

    f_debug = fopen(file_name, mode_a_or_w);
#endif
}
#endif


TQ84_DEBUG_EXPORT int tq84_debug_indent(/*TQ84_DEBUG_ENV_TYPE env,*/ const char* filename, const char* funcname, unsigned int line, const char* fmt, ...) {
#ifdef TQ84_DEBUG_ENABLED

  va_list ap; va_start(ap, fmt);

/* if (tq84_debug_dont_env(env)) return 0; */
 
  tq84_debug_indent_position(filename, funcname, line);
  tq84_debug_out_va_list(fmt, ap);

  tq84_debug_out(" {");
  tq84_debug_end_line();

  indent++;
#endif
  return 42;
}

TQ84_DEBUG_EXPORT void tq84_debug_dedent(/*TQ84_DEBUG_ENV_TYPE env*/  /*const char* fmt, ...*/) {
#ifdef TQ84_DEBUG_ENABLED

/*if (tq84_debug_dont_env(env)) return; */

  indent--;
  tq84_debug_indent_null();
  tq84_debug_out("}");
  tq84_debug_end_line();

#endif
}
TQ84_DEBUG_EXPORT void tq84_debug(/*TQ84_DEBUG_ENV_TYPE env,*/ const char* filename, const char* funcname, unsigned int line, const char* fmt, ...) {
#ifdef TQ84_DEBUG_ENABLED
  va_list ap; va_start(ap, fmt);

/*if (tq84_debug_dont_env(env)) return; */

  tq84_debug_indent_position(filename, funcname, line);
  tq84_debug_out_va_list(fmt, ap);
  tq84_debug_out("");
  tq84_debug_end_line();

#endif
}
