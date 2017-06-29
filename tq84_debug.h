#ifdef __cplusplus
extern "C" {
#endif

#define TQ84_DEBUG_ENV_TYPE unsigned int

void tq84_debug_open();
void tq84_debug_dedent(TQ84_DEBUG_ENV_TYPE env/*const char* fmt, ...*/);
void tq84_debug_indent(TQ84_DEBUG_ENV_TYPE env, const char* fmt, ...);
void tq84_debug       (TQ84_DEBUG_ENV_TYPE env, const char* fmt, ...);
//void tq84_debug_out(const char* fmt, ...);

#ifdef __cplusplus
}
#endif
