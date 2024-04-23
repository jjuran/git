/*
	relix.h
	-------
	
	MacRelix support, by Josh Juran
*/

// Include <ctype.h> early so git's macros don't interfere with it later
#include <ctype.h>

#define GIT_VERSION "1.8.3.2"

// MacRelix has small thread stacks, and 68K has a hard 32K local data limit.
#define LARGE_PACKET_MAX (16384 - 16)

// Enable #pragma cplusplus over dynamic aggregate initializers.
#define USE_CPLUSPLUS_FOR_INIT 1

#define NO_CURL  1
#define NO_EXPAT 1
#define NO_GETTEXT 1
#define NO_ICONV 1
#define NO_IPV6  1
// MacRelix has mmap(), but we want the small window size
#define NO_MMAP  1
#define NO_NSEC  1
#define NO_OPENSSL 1
#define NO_PTHREADS 1
#define NO_LIBGEN_H 1

#define HAVE_STRING_H 1

#define SHA1_HEADER "block-sha1/sha1.h"

#define ETC_GITCONFIG "/etc/gitconfig"

#define ETC_GITATTRIBUTES "/etc/gitattributes"

#define GIT_EXEC_PATH "/usr/lib/git-core"

#define GIT_MAN_PATH  "man"
#define GIT_INFO_PATH "info"
#define GIT_HTML_PATH "html"

#define GIT_USER_AGENT "git/" GIT_VERSION

#define PREFIX "/usr"

#define gitmemmem     memmem
#define gitstrcasestr strcasestr

extern int reexec( void* f, ... );
