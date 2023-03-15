#define DEBUG

#ifdef DEBUG
#define printf(fmt, args...)  fprintf(stderr, fmt, ## args)
#else
#define printf(fmt, args...)    /* do nothing */
#endif