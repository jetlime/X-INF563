#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(fmt, args...)  fprintf(stderr, fmt, ## args)
#else
#define DEBUG_PRINT(fmt, args...)    /* do nothing */
#endif