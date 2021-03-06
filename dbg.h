#ifndef _dbg_h_
#define _dbg_h_

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%s:%d: " M "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%s:%d: errno %s) " M "\n",  __FILE__, __func__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%s:%d: errno %s) " M "\n", __FILE__, __func__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%s:%d) " M "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

// MUST CREATE "error:" label in code where this is called from!
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

// modified with %c", '.' to avoid " warning: ISO C99 requires rest arguments to be used [enabled by default]"
#define check_mem(A) check((A), "Out of memory%c", '.') 


#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif


