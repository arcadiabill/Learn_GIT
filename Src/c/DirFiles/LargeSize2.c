#if /* linux */
#define _FILE_OFFSET_BITS 64
#endif

#include <stdio.h>

#if /* windows */
#define fseeko _fseeki64
#define ftello _ftelli64
typedef __int64 off_t;
#endif

#if /* other */
#define fseeko fseek
#define ftello ftell
typedef long off_t;
#endif
