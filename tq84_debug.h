#ifdef __cplusplus
extern "C" {
#endif

#define TQ84_CONCAT(a, b) a ## b
#define TQ84_CONCAT_INDIRECT(a, b) TQ84_CONCAT(a, b)

// #define TQ84_DEBUG_ENV_TYPE unsigned int

void tq84_debug_open(const char* mode_a_or_w);
void tq84_debug_dedent(/* TQ84_DEBUG_ENV_TYPE env  *//*const char* fmt, ...*/);
int  tq84_debug_indent(/* TQ84_DEBUG_ENV_TYPE env, */  const char* fmt, ...);
void tq84_debug       (/* TQ84_DEBUG_ENV_TYPE env, */  const char* fmt, ...);
//void tq84_debug_out(const char* fmt, ...);

void tq84_debug_var_goes_out_of_scope(int*);
#define TQ84_DEBUG_INDENT int TQ84_CONCAT_INDIRECT(tq84_debug_, __COUNTER__)  __attribute__((cleanup (tq84_debug_var_goes_out_of_scope) )) = tq84_debug_indent
#define TQ84_DEBUG tq84_debug

#ifdef __cplusplus
}
#endif
