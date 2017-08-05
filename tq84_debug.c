#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "tq84_debug.h"

static FILE* f_debug = NULL;

int   indent;

#define TQ84_DEBUG_ENABLED 1

#ifdef TQ84_DEBUG_ENABLED

void tq84_debug_var_goes_out_of_scope(int* v __attribute__((unused)) ) {
  tq84_debug_dedent(1);
}

#endif

void tq84_debug_out(const char* fmt, va_list ap) {
#ifdef TQ84_DEBUG_ENABLED

  if (! f_debug) tq84_debug_open();

//va_list ap; va_start(ap, fmt);
  vfprintf(f_debug, fmt, ap);

//fprintf(f_debug, "\n");
#endif
}

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

static void tq84_debug_indent_() {
#ifdef TQ84_DEBUG_ENABLED

  if (! f_debug) tq84_debug_open();

  int i;
  for (i=0; i<indent*2; i++) {
    fprintf(f_debug, " ");
  }
#endif
}

void tq84_debug_open() {
#ifdef TQ84_DEBUG_ENABLED
  /*
  time_t t;
  struct tm tm;
  */
  char file_name[200];

  if (f_debug) {
    // Don't reopen
    return;
  }

  /*
  t=time(NULL);
  tm = *localtime(&t);
  */

  sprintf(file_name,
#ifdef unix
      "/tmp/"
#else
      "c:\\temp\\"
#endif
//    "tq84_debug_%4d-%02d_%02d_%02d.%02d.%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
      "tq84_debug");

//f_debug = fopen(file_name, "a");
  f_debug = fopen(file_name, "w");
#endif
}

int tq84_debug_indent(TQ84_DEBUG_ENV_TYPE env, const char* fmt, ...) {
#ifdef TQ84_DEBUG_ENABLED

  va_list ap; va_start(ap, fmt);

  if (tq84_debug_dont_env(env)) return 0;
 
  tq84_debug_indent_();
  tq84_debug_out(fmt, ap);

//tq84_debug_out("{\n", NULL);
  fprintf(f_debug, " {\n");
  fflush(f_debug);

  indent++;
#endif
  return 42;
}

void tq84_debug_dedent(TQ84_DEBUG_ENV_TYPE env /*const char* fmt, ...*/) {
#ifdef TQ84_DEBUG_ENABLED

  if (tq84_debug_dont_env(env)) return;

  indent--;
  tq84_debug_indent_();

//tq84_debug_out("}\n", NULL);
  fprintf(f_debug, "}\n");
  fflush(f_debug);

#endif
}
void tq84_debug(TQ84_DEBUG_ENV_TYPE env, const char* fmt, ...) {
#ifdef TQ84_DEBUG_ENABLED
  va_list ap; va_start(ap, fmt);

  if (tq84_debug_dont_env(env)) return;

  tq84_debug_indent_();
  tq84_debug_out(fmt, ap);

//tq84_debug_out("\n", NULL);
  fprintf(f_debug, "\n");

  fflush(f_debug);
#endif
}
