#ifdef __cplusplus
extern "C" {
#endif

#ifdef TQ84_DEBUG_ENABLED

#define TQ84_CONCAT(a, b) a ## b
#define TQ84_CONCAT_INDIRECT(a, b) TQ84_CONCAT(a, b)

/*
#define TQ84_DEBUG_ENV_TYPE unsigned int
*/

void tq84_debug_open(const char* filename
   #ifdef TQ84_DEBUG_TO_FILE
    , const char* mode_a_or_w
   #endif
);
void tq84_debug_dedent(void /* TQ84_DEBUG_ENV_TYPE env  *//*const char* fmt, ...*/);
int  tq84_debug_indent(/* TQ84_DEBUG_ENV_TYPE env, */  const char* filename, const char* funcname, unsigned int line, const char* fmt, ...);
void tq84_debug       (/* TQ84_DEBUG_ENV_TYPE env, */  const char* filename, const char* funcname, unsigned int line, const char* fmt, ...);
void tq84_debug_close(void);

void tq84_debug_var_goes_out_of_scope(int*);
#define TQ84_DEBUG_INDENT_T(...)   int TQ84_CONCAT_INDIRECT(tq84_debug_, __COUNTER__)  __attribute__((cleanup (tq84_debug_var_goes_out_of_scope) )) = tq84_debug_indent(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define TQ84_DEBUG_INDENT()        int TQ84_CONCAT_INDIRECT(tq84_debug_, __COUNTER__)  __attribute__((cleanup (tq84_debug_var_goes_out_of_scope) )) = tq84_debug_indent(__FILE__, __FUNCTION__, __LINE__, __FUNCTION__)
#define TQ84_DEBUG(...)                                                                                                                               tq84_debug       (__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define TQ84_DEBUG_RETURN(x) \
    switch ( _Generic( (x), \
              char*       : 's',                 \
              const char* : 's',                 \
              int         : 'd',                 \
              double      : 'f',                 \
              void*       : 'x',                 \
              default     : '?') ) {             \
        case 's': TQ84_DEBUG("return %s", x); break; \
        case 'd': TQ84_DEBUG("return %d", x); break; \
        case 'f': TQ84_DEBUG("return %f", x); break; \
        case 'x': TQ84_DEBUG("return %x", x); break; \
        default : TQ84_DEBUG("return ?");            \
    }; \
    return x

#else

#define tq84_debug_open(...)
#define tq84_debug_close(...)
#define TQ84_DEBUG_INDENT_T(...)
#define TQ84_DEBUG_INDENT()
#define TQ84_DEBUG(...)

#endif

#ifdef __cplusplus
}
#endif
