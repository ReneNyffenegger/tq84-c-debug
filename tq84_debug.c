
#include "tq84_debug.h"

// #define TQ84_DEBUG_ENABLED

#ifdef TQ84_DEBUG_ENABLED

#if !defined(TQ84_DEBUG_TO_FILE) && !defined(TQ84_DEBUG_TO_MEMORY) && !defined(TQ84_DEBUG_KERNEL)
  #error "Specify TQ84_DEBUG_TO_FILE or TQ84_DEBUG_TO_MEMORY"
#endif


int   indent;

#if defined(TQ84_DEBUG_TO_FILE) || defined(TQ84_DEBUG_TO_MEMORY)

   #include <stdio.h>
   #include <stdarg.h>
// #include <time.h>

   #define TQ84_DEBUG_FUNC_WIDTH "50"

#elif defined(TQ84_DEBUG_KERNEL)

   #include <linux/kernel.h>

   #define TQ84_CLASS_NAME   "tq84"
   #define TQ84_DEVICE_NAME  "tq84_debug"

   #define TQ84_DEBUG_FUNC_WIDTH "35"

   static int     majNr;
   static struct  class*  tq84CharClass  = NULL;
   static struct  device* tq84CharDevice = NULL;
   
   static int     open_device      (struct inode*, struct file*);
   static int     release_device   (struct inode*, struct file*);
   static ssize_t read_from_device (struct file* , char*, size_t, loff_t*);
   static ssize_t write_to_device  (struct file* , const char*, size_t, loff_t*);

   static const struct file_operations fops = {
     .open    = open_device,
     .read    = read_from_device,
     .write   = write_to_device,
     .release = release_device,
   };

#endif

#ifdef TQ84_DEBUG_TO_FILE
   static FILE* f_debug = NULL;
#else
   #define  tq84_debug_memory_size 0x40000
   char  tq84_debug_memory[tq84_debug_memory_size]; 
   int   tq84_debug_memory_pos = 0;
   int   tq84_debug_memory_already_written = 0;
   #ifdef TQ84_DEBUG_TO_MEMORY
   const char* tq84_debug_memory_filename;
   #endif
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
  #if  defined(TQ84_DEBUG_TO_FILE)
    vfprintf(f_debug, fmt, ap);
  #else
    if (!tq84_debug_memory_already_written) {
       tq84_debug_memory_pos += vsprintf(&tq84_debug_memory[tq84_debug_memory_pos], fmt, ap);
    }
  #endif
#endif
}

TQ84_DEBUG_EXPORT void tq84_debug_out(const char* fmt, ...) {
#ifdef TQ84_DEBUG_ENABLED
  va_list ap; va_start(ap, fmt);
  tq84_debug_out_va_list(fmt, ap);
#endif
}

TQ84_DEBUG_EXPORT void tq84_debug_end_line(void) {
#ifdef TQ84_DEBUG_ENABLED
  tq84_debug_out("\n");
  #ifdef TQ84_DEBUG_TO_FILE
    fflush(f_debug);
  #else

    if (tq84_debug_memory_pos > tq84_debug_memory_size - 255) {
        tq84_debug_close();
    }

  #endif
#endif
}

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

static void tq84_debug_indent_(void) {
#ifdef TQ84_DEBUG_ENABLED
  int i;
  for (i=0; i<indent*2; i++) {
    tq84_debug_out(" ");
  }
#endif
}

static void tq84_debug_indent_null(void) {
#ifdef TQ84_DEBUG_ENABLED
  tq84_debug_out("%-" TQ84_DEBUG_FUNC_WIDTH "s %-20s %4s: ", "", "", "");
  tq84_debug_indent_();
#endif
}

static void tq84_debug_indent_position(const char* filename, const char* funcname, unsigned int line) {
#ifdef TQ84_DEBUG_ENABLED
  // tq84_debug_out("%-50s %-20s %4d: ", filename, funcname, line);
  tq84_debug_out("%-" TQ84_DEBUG_FUNC_WIDTH "s %-20s %4d: ", filename, funcname, line);
  tq84_debug_indent_();
#endif
}

TQ84_DEBUG_EXPORT void tq84_debug_open(
      const char* filename
   #ifdef TQ84_DEBUG_TO_FILE
    , const char* mode_a_or_w
   #endif
) { /* mode_a_or_w: a = append to log file, w = create it */
#ifdef TQ84_DEBUG_ENABLED
  #ifdef TQ84_DEBUG_TO_FILE
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
  #ifdef TQ84_DEBUG_TO_MEMORY
    tq84_debug_memory_filename = filename;
  #endif
#endif
}


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

TQ84_DEBUG_EXPORT void tq84_debug_dedent(void /*TQ84_DEBUG_ENV_TYPE env*/  /*const char* fmt, ...*/) {
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


TQ84_DEBUG_EXPORT void tq84_debug_close() {
#ifdef TQ84_DEBUG_ENABLED

  #if defined TQ84_DEBUG_TO_MEMORY || defined TQ84_DEBUG_KERNEL
//  printk(KERN_ALERT TQ84_DEVICE_NAME ": tq84_debug_close was called\n");
    if (! tq84_debug_memory_already_written) {

      #if defined TQ84_DEBUG_TO_MEMORY

         FILE* f = fopen("/tmp/tq84_debug_out_to_memory", "w");
         fprintf(f, tq84_debug_memory);
         fclose(f);

      #else
      #endif 
      tq84_debug_memory_already_written = 1;
   }

  #endif

#endif
}

#ifdef TQ84_DEBUG_KERNEL
static int open_device(struct inode* inodep, struct file* filep) {
//  printk(KERN_INFO TQ84_DEVICE_NAME ": opened\n"); 
    return 0;
}

static ssize_t read_from_device(struct file* filep, char* buffer, size_t len, loff_t* offset) {
    int error_count = 0;
    error_count = copy_to_user(buffer, tq84_debug_memory, tq84_debug_memory_pos);
  
    if (error_count == 0) {
      return 0;
    }
  
    printk(KERN_ALERT TQ84_DEVICE_NAME ": Failed to send %d characters\n", error_count);
    return -EFAULT;
}

static ssize_t write_to_device(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
 //
 // Is there something interesting that could be done?
 //
    return len;
}

static int release_device(struct inode *inodep, struct file* filep) {
    return 0;
}


static int __init tq84_debug_dev_init(void) {         
 //
 // Compare with linux/drivers/char/mem.c
 //


    majNr = register_chrdev(0, TQ84_DEVICE_NAME, &fops);
    if (majNr < 0) {
      printk(KERN_ALERT TQ84_DEVICE_NAME ": could not register a new major number\n");
      return majNr;
    }
    
    tq84CharClass = class_create(THIS_MODULE, TQ84_CLASS_NAME);
    
    if (IS_ERR(tq84CharClass)) {
      unregister_chrdev(majNr, TQ84_DEVICE_NAME);
      printk(KERN_ALERT TQ84_DEVICE_NAME ": Failed to register device class\n");
      return PTR_ERR(tq84CharClass);
    }
    
    tq84CharDevice = device_create(tq84CharClass, NULL, MKDEV(majNr, 0), NULL, TQ84_DEVICE_NAME);
    
    if (IS_ERR(tq84CharDevice)) {
      class_destroy(tq84CharClass);
      unregister_chrdev(majNr, TQ84_DEVICE_NAME);
      printk(KERN_ALERT TQ84_DEVICE_NAME ": Could not create the device\n");
      return PTR_ERR(tq84CharDevice);
    }
    
 // printk(KERN_INFO TQ84_DEVICE_NAME ": allocated major number: %d\n", majNr);

     return 0;
}


fs_initcall(tq84_debug_dev_init);

#endif



#endif
