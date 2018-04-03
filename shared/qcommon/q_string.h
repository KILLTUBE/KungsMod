#pragma once

#include "q_platform.h"
#include "rd-rend2/include_ccall.h"

#if defined(__cplusplus)
extern "C" {
#endif

CCALL int Q_isprint( int c );
CCALL int Q_isprintext( int c );
CCALL int Q_isgraph( int c );
CCALL int Q_islower( int c );
CCALL int Q_isupper( int c );
CCALL int Q_isalpha( int c );
CCALL qboolean Q_isanumber( const char *s );
CCALL qboolean Q_isintegral( float f );

// portable case insensitive compare
CCALL int Q_stricmp(const char *s1, const char *s2);
CCALL int	Q_strncmp(const char *s1, const char *s2, int n);
CCALL int	Q_stricmpn(const char *s1, const char *s2, int n);
CCALL char *Q_strlwr( char *s1 );
CCALL char *Q_strupr( char *s1 );
CCALL char *Q_strrchr( const char* string, int c );

// buffer size safe library replacements
void Q_strncpyz( char *dest, const char *src, int destsize );
void Q_strcat( char *dest, int size, const char *src );

const char *Q_stristr( const char *s, const char *find);

// strlen that discounts Quake color sequences
int Q_PrintStrlen( const char *string );

// removes color sequences from string
char *Q_CleanStr( char *string );
void Q_StripColor(char *text);
const char *Q_strchrs( const char *string, const char *search );

void Q_strstrip( char *string, const char *strip, const char *repl );

#if defined (_MSC_VER)
	// vsnprintf is ISO/IEC 9899:1999
	// abstracting this to make it portable
	int Q_vsnprintf( char *str, size_t size, const char *format, va_list args );
#else // not using MSVC
	#define Q_vsnprintf vsnprintf
#endif

#if defined(__cplusplus)
} // extern "C"
#endif
