/*
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	@(#)stdio.h	5.3 (Berkeley) 3/15/86
 */

/*
 * NB: to fit things in six character monocase externals, the
 * stdio code uses the prefix `__s' for stdio objects, typically
 * followed by a three-character attempt at a mnemonic.
 */

#ifndef _STDIO_H_
#define	_STDIO_H_

#include "_ansi.h"

#define	_FSTDIO			/* ``function stdio'' */

#define __need_size_t
#define __need_NULL
#include <sys/cdefs.h>
#include <stddef.h>

/* typedef only __gnuc_va_list, used throughout the header */
#define __need___va_list
#include <stdarg.h>

/* typedef va_list only when required */
#if __POSIX_VISIBLE >= 200809 || __XSI_VISIBLE
#ifdef __GNUC__
#ifndef _VA_LIST_DEFINED
typedef __gnuc_va_list va_list;
#define _VA_LIST_DEFINED
#endif
#else /* !__GNUC__ */
#include <stdarg.h>
#endif
#endif /* __POSIX_VISIBLE >= 200809 || __XSI_VISIBLE */

/*
 * <sys/reent.h> defines __FILE, _fpos_t.
 * They must be defined there because struct _reent needs them (and we don't
 * want reent.h to include this file.
 */

#include <sys/reent.h>
#include <sys/types.h>

_BEGIN_STD_C

#if !defined(__FILE_defined)
typedef __FILE FILE;
# define __FILE_defined
#endif

#ifdef __CYGWIN__
typedef _fpos64_t fpos_t;
#else
typedef _fpos_t fpos_t;
#ifdef __LARGE64_FILES
typedef _fpos64_t fpos64_t;
#endif
#endif /* !__CYGWIN__ */

#include <sys/stdio.h>

#define	__SLBF	0x0001		/* line buffered */
#define	__SNBF	0x0002		/* unbuffered */
#define	__SRD	0x0004		/* OK to read */
#define	__SWR	0x0008		/* OK to write */
	/* RD and WR are never simultaneously asserted */
#define	__SRW	0x0010		/* open for reading & writing */
#define	__SEOF	0x0020		/* found EOF */
#define	__SERR	0x0040		/* found error */
#define	__SMBF	0x0080		/* _buf is from malloc */
#define	__SAPP	0x0100		/* fdopen()ed in append mode - so must  write to end */
#define	__SSTR	0x0200		/* this is an sprintf/snprintf string */
#define	__SOPT	0x0400		/* do fseek() optimisation */
#define	__SNPT	0x0800		/* do not do fseek() optimisation */
#define	__SOFF	0x1000		/* set iff _offset is in fact correct */
#define	__SORD	0x2000		/* true => stream orientation (byte/wide) decided */
#if defined(__CYGWIN__)
#  define __SCLE  0x4000        /* convert line endings CR/LF <-> NL */
#endif
#define	__SL64	0x8000		/* is 64-bit offset large file */

/* _flags2 flags */
#define	__SNLK  0x0001		/* stdio functions do not lock streams themselves */
#define	__SWID	0x2000		/* true => stream orientation wide, false => byte, only valid if __SORD in _flags is true */

/*
 * The following three definitions are for ANSI C, which took them
 * from System V, which stupidly took internal interface macros and
 * made them official arguments to setvbuf(), without renaming them.
 * Hence, these ugly _IOxxx names are *supposed* to appear in user code.
 *
 * Although these happen to match their counterparts above, the
 * implementation does not rely on that (so these could be renumbered).
 */
#define	_IOFBF	0		/* setvbuf should set fully buffered */
#define	_IOLBF	1		/* setvbuf should set line buffered */
#define	_IONBF	2		/* setvbuf should set unbuffered */

#define	EOF	(-1)

#ifdef __BUFSIZ__
#define	BUFSIZ		__BUFSIZ__
#else
#define	BUFSIZ		1024
#endif

#ifdef __FOPEN_MAX__
#define FOPEN_MAX	__FOPEN_MAX__
#else
#define	FOPEN_MAX	20
#endif

#ifdef __FILENAME_MAX__
#define FILENAME_MAX    __FILENAME_MAX__
#else
#define	FILENAME_MAX	1024
#endif

#ifdef __L_tmpnam__
#define L_tmpnam	__L_tmpnam__
#else
#define	L_tmpnam	FILENAME_MAX
#endif

#if __BSD_VISIBLE || __XSI_VISIBLE
#define P_tmpdir        "/tmp"
#endif

#ifndef SEEK_SET
#define	SEEK_SET	0	/* set file offset to offset */
#endif
#ifndef SEEK_CUR
#define	SEEK_CUR	1	/* set file offset to current plus offset */
#endif
#ifndef SEEK_END
#define	SEEK_END	2	/* set file offset to EOF plus offset */
#endif

#define	TMP_MAX		26

#define	stdin	(_REENT->_stdin)
#define	stdout	(_REENT->_stdout)
#define	stderr	(_REENT->_stderr)

#define _stdin_r(x)	((x)->_stdin)
#define _stdout_r(x)	((x)->_stdout)
#define _stderr_r(x)	((x)->_stderr)

/*
 * Functions defined in ANSI C standard.
 */

#ifndef __VALIST
#ifdef __GNUC__
#define __VALIST __gnuc_va_list
#else
#define __VALIST char*
#endif
#endif

#if __POSIX_VISIBLE
char *	_EXFUN(ctermid, (char *));
#endif
#if __XSI_VISIBLE && __XSI_VISIBLE < 600
char *	_EXFUN(cuserid, (char *));
#endif
FILE *	_EXFUN(tmpfile, (void));
char *	_EXFUN(tmpnam, (char *));
#if __BSD_VISIBLE || __XSI_VISIBLE || __POSIX_VISIBLE >= 200112
char *	_EXFUN(tempnam, (const char *, const char *));
#endif
int	_EXFUN(fclose, (FILE *));
int	_EXFUN(fflush, (FILE *));
FILE *	_EXFUN(freopen, (const char *__restrict, const char *__restrict, FILE *__restrict));
void	_EXFUN(setbuf, (FILE *__restrict, char *__restrict));
int	_EXFUN(setvbuf, (FILE *__restrict, char *__restrict, int, size_t));
int	_EXFUN(fprintf, (FILE *__restrict, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 2, 3))));
int	_EXFUN(fscanf, (FILE *__restrict, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__scanf__, 2, 3))));
int	_EXFUN(printf, (const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 1, 2))));
int	_EXFUN(scanf, (const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__scanf__, 1, 2))));
int	_EXFUN(sscanf, (const char *__restrict, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__scanf__, 2, 3))));
int	_EXFUN(vfprintf, (FILE *__restrict, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 2, 0))));
int	_EXFUN(vprintf, (const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 1, 0))));
int	_EXFUN(vsprintf, (char *__restrict, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 2, 0))));
int	_EXFUN(fgetc, (FILE *));
char *  _EXFUN(fgets, (char *__restrict, int, FILE *__restrict));
int	_EXFUN(fputc, (int, FILE *));
int	_EXFUN(fputs, (const char *__restrict, FILE *__restrict));
int	_EXFUN(getc, (FILE *));
int	_EXFUN(getchar, (void));
char *  _EXFUN(gets, (char *));
int	_EXFUN(putc, (int, FILE *));
int	_EXFUN(putchar, (int));
int	_EXFUN(puts, (const char *));
int	_EXFUN(ungetc, (int, FILE *));
size_t	_EXFUN(fread, (_PTR __restrict, size_t _size, size_t _n, FILE *__restrict));
size_t	_EXFUN(fwrite, (const _PTR __restrict , size_t _size, size_t _n, FILE *));
#ifdef _COMPILING_NEWLIB
int	_EXFUN(fgetpos, (FILE *, _fpos_t *));
#else
int	_EXFUN(fgetpos, (FILE *__restrict, fpos_t *__restrict));
#endif
int	_EXFUN(fseek, (FILE *, long, int));
#ifdef _COMPILING_NEWLIB
int	_EXFUN(fsetpos, (FILE *, const _fpos_t *));
#else
int	_EXFUN(fsetpos, (FILE *, const fpos_t *));
#endif
long	_EXFUN(ftell, ( FILE *));
void	_EXFUN(rewind, (FILE *));
void	_EXFUN(clearerr, (FILE *));
int	_EXFUN(feof, (FILE *));
int	_EXFUN(ferror, (FILE *));
void    _EXFUN(perror, (const char *));
#ifndef _REENT_ONLY
FILE *	_EXFUN(fopen, (const char *__restrict _name, const char *__restrict _type));
int	_EXFUN(sprintf, (char *__restrict, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 2, 3))));
int	_EXFUN(remove, (const char *));
int	_EXFUN(rename, (const char *, const char *));
#ifdef _COMPILING_NEWLIB
int	_EXFUN(_rename, (const char *, const char *));
#endif
#endif
#if __LARGEFILE_VISIBLE || __POSIX_VISIBLE >= 200112
#ifdef _COMPILING_NEWLIB
int	_EXFUN(fseeko, (FILE *, _off_t, int));
_off_t	_EXFUN(ftello, ( FILE *));
#else
int	_EXFUN(fseeko, (FILE *, off_t, int));
off_t	_EXFUN(ftello, ( FILE *));
#endif
#endif
#if __GNU_VISIBLE
int	_EXFUN(fcloseall, (_VOID));
#endif
#ifndef _REENT_ONLY
#if __ISO_C_VISIBLE >= 1999
int	_EXFUN(snprintf, (char *__restrict, size_t, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 3, 4))));
int	_EXFUN(vsnprintf, (char *__restrict, size_t, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 3, 0))));
int	_EXFUN(vfscanf, (FILE *__restrict, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__scanf__, 2, 0))));
int	_EXFUN(vscanf, (const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__scanf__, 1, 0))));
int	_EXFUN(vsscanf, (const char *__restrict, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__scanf__, 2, 0))));
#endif
#if __GNU_VISIBLE
int	_EXFUN(asprintf, (char **__restrict, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 2, 3))));
int	_EXFUN(vasprintf, (char **, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 2, 0))));
#endif
#if __MISC_VISIBLE /* Newlib-specific */
int	_EXFUN(asiprintf, (char **, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 2, 3))));
char *	_EXFUN(asniprintf, (char *, size_t *, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 3, 4))));
char *	_EXFUN(asnprintf, (char *__restrict, size_t *__restrict, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 3, 4))));
#ifndef diprintf
int	_EXFUN(diprintf, (int, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 2, 3))));
#endif
int	_EXFUN(fiprintf, (FILE *, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 2, 3))));
int	_EXFUN(fiscanf, (FILE *, const char *, ...)
               _ATTRIBUTE ((__format__ (__scanf__, 2, 3))));
int	_EXFUN(iprintf, (const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 1, 2))));
int	_EXFUN(iscanf, (const char *, ...)
               _ATTRIBUTE ((__format__ (__scanf__, 1, 2))));
int	_EXFUN(siprintf, (char *, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 2, 3))));
int	_EXFUN(siscanf, (const char *, const char *, ...)
               _ATTRIBUTE ((__format__ (__scanf__, 2, 3))));
int	_EXFUN(sniprintf, (char *, size_t, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 3, 4))));
int	_EXFUN(vasiprintf, (char **, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 2, 0))));
char *	_EXFUN(vasniprintf, (char *, size_t *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 3, 0))));
char *	_EXFUN(vasnprintf, (char *, size_t *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 3, 0))));
int	_EXFUN(vdiprintf, (int, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 2, 0))));
int	_EXFUN(vfiprintf, (FILE *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 2, 0))));
int	_EXFUN(vfiscanf, (FILE *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__scanf__, 2, 0))));
int	_EXFUN(viprintf, (const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 1, 0))));
int	_EXFUN(viscanf, (const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__scanf__, 1, 0))));
int	_EXFUN(vsiprintf, (char *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 2, 0))));
int	_EXFUN(vsiscanf, (const char *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__scanf__, 2, 0))));
int	_EXFUN(vsniprintf, (char *, size_t, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 3, 0))));
#endif /* __MISC_VISIBLE */
#endif /* !_REENT_ONLY */

/*
 * Routines in POSIX 1003.1:2001.
 */

#if __POSIX_VISIBLE
#ifndef _REENT_ONLY
FILE *	_EXFUN(fdopen, (int, const char *));
#endif
int	_EXFUN(fileno, (FILE *));
#endif
#if __MISC_VISIBLE || __POSIX_VISIBLE >= 199209
int	_EXFUN(pclose, (FILE *));
FILE *  _EXFUN(popen, (const char *, const char *));
#endif

#if __BSD_VISIBLE
void    _EXFUN(setbuffer, (FILE *, char *, int));
int	_EXFUN(setlinebuf, (FILE *));
#endif

#if __MISC_VISIBLE || (__XSI_VISIBLE && __POSIX_VISIBLE < 200112)
int	_EXFUN(getw, (FILE *));
int	_EXFUN(putw, (int, FILE *));
#endif
#if __MISC_VISIBLE || __POSIX_VISIBLE
int	_EXFUN(getc_unlocked, (FILE *));
int	_EXFUN(getchar_unlocked, (void));
void	_EXFUN(flockfile, (FILE *));
int	_EXFUN(ftrylockfile, (FILE *));
void	_EXFUN(funlockfile, (FILE *));
int	_EXFUN(putc_unlocked, (int, FILE *));
int	_EXFUN(putchar_unlocked, (int));
#endif

/*
 * Routines in POSIX 1003.1:200x.
 */

#if __POSIX_VISIBLE >= 200809
# ifndef _REENT_ONLY
#  ifndef dprintf
int	_EXFUN(dprintf, (int, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 2, 3))));
#  endif
FILE *	_EXFUN(fmemopen, (void *__restrict, size_t, const char *__restrict));
/* getdelim - see __getdelim for now */
/* getline - see __getline for now */
FILE *	_EXFUN(open_memstream, (char **, size_t *));
int	_EXFUN(vdprintf, (int, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 2, 0))));
# endif
#endif
#if __ATFILE_VISIBLE
int	_EXFUN(renameat, (int, const char *, int, const char *));
#endif

/*
 * Recursive versions of the above.
 */

int	_EXFUN(_asiprintf_r, (struct _reent *, char **, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 3, 4))));
char *	_EXFUN(_asniprintf_r, (struct _reent *, char *, size_t *, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 4, 5))));
char *	_EXFUN(_asnprintf_r, (struct _reent *, char *__restrict, size_t *__restrict, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 4, 5))));
int	_EXFUN(_asprintf_r, (struct _reent *, char **__restrict, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 3, 4))));
int	_EXFUN(_diprintf_r, (struct _reent *, int, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 3, 4))));
int	_EXFUN(_dprintf_r, (struct _reent *, int, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 3, 4))));
int	_EXFUN(_fclose_r, (struct _reent *, FILE *));
int	_EXFUN(_fcloseall_r, (struct _reent *));
FILE *	_EXFUN(_fdopen_r, (struct _reent *, int, const char *));
int	_EXFUN(_fflush_r, (struct _reent *, FILE *));
int	_EXFUN(_fgetc_r, (struct _reent *, FILE *));
int	_EXFUN(_fgetc_unlocked_r, (struct _reent *, FILE *));
char *  _EXFUN(_fgets_r, (struct _reent *, char *__restrict, int, FILE *__restrict));
char *  _EXFUN(_fgets_unlocked_r, (struct _reent *, char *__restrict, int, FILE *__restrict));
#ifdef _COMPILING_NEWLIB
int	_EXFUN(_fgetpos_r, (struct _reent *, FILE *__restrict, _fpos_t *__restrict));
int	_EXFUN(_fsetpos_r, (struct _reent *, FILE *, const _fpos_t *));
#else
int	_EXFUN(_fgetpos_r, (struct _reent *, FILE *, fpos_t *));
int	_EXFUN(_fsetpos_r, (struct _reent *, FILE *, const fpos_t *));
#endif
int	_EXFUN(_fiprintf_r, (struct _reent *, FILE *, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 3, 4))));
int	_EXFUN(_fiscanf_r, (struct _reent *, FILE *, const char *, ...)
               _ATTRIBUTE ((__format__ (__scanf__, 3, 4))));
FILE *	_EXFUN(_fmemopen_r, (struct _reent *, void *__restrict, size_t, const char *__restrict));
FILE *	_EXFUN(_fopen_r, (struct _reent *, const char *__restrict, const char *__restrict));
FILE *	_EXFUN(_freopen_r, (struct _reent *, const char *__restrict, const char *__restrict, FILE *__restrict));
int	_EXFUN(_fprintf_r, (struct _reent *, FILE *__restrict, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 3, 4))));
int	_EXFUN(_fpurge_r, (struct _reent *, FILE *));
int	_EXFUN(_fputc_r, (struct _reent *, int, FILE *));
int	_EXFUN(_fputc_unlocked_r, (struct _reent *, int, FILE *));
int	_EXFUN(_fputs_r, (struct _reent *, const char *__restrict, FILE *__restrict));
int	_EXFUN(_fputs_unlocked_r, (struct _reent *, const char *__restrict, FILE *__restrict));
size_t	_EXFUN(_fread_r, (struct _reent *, _PTR __restrict, size_t _size, size_t _n, FILE *__restrict));
size_t	_EXFUN(_fread_unlocked_r, (struct _reent *, _PTR __restrict, size_t _size, size_t _n, FILE *__restrict));
int	_EXFUN(_fscanf_r, (struct _reent *, FILE *__restrict, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__scanf__, 3, 4))));
int	_EXFUN(_fseek_r, (struct _reent *, FILE *, long, int));
int	_EXFUN(_fseeko_r,(struct _reent *, FILE *, _off_t, int));
long	_EXFUN(_ftell_r, (struct _reent *, FILE *));
_off_t	_EXFUN(_ftello_r,(struct _reent *, FILE *));
void	_EXFUN(_rewind_r, (struct _reent *, FILE *));
size_t	_EXFUN(_fwrite_r, (struct _reent *, const _PTR __restrict, size_t _size, size_t _n, FILE *__restrict));
size_t	_EXFUN(_fwrite_unlocked_r, (struct _reent *, const _PTR __restrict, size_t _size, size_t _n, FILE *__restrict));
int	_EXFUN(_getc_r, (struct _reent *, FILE *));
int	_EXFUN(_getc_unlocked_r, (struct _reent *, FILE *));
int	_EXFUN(_getchar_r, (struct _reent *));
int	_EXFUN(_getchar_unlocked_r, (struct _reent *));
char *	_EXFUN(_gets_r, (struct _reent *, char *));
int	_EXFUN(_iprintf_r, (struct _reent *, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 2, 3))));
int	_EXFUN(_iscanf_r, (struct _reent *, const char *, ...)
               _ATTRIBUTE ((__format__ (__scanf__, 2, 3))));
FILE *	_EXFUN(_open_memstream_r, (struct _reent *, char **, size_t *));
void	_EXFUN(_perror_r, (struct _reent *, const char *));
int	_EXFUN(_printf_r, (struct _reent *, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 2, 3))));
int	_EXFUN(_putc_r, (struct _reent *, int, FILE *));
int	_EXFUN(_putc_unlocked_r, (struct _reent *, int, FILE *));
int	_EXFUN(_putchar_unlocked_r, (struct _reent *, int));
int	_EXFUN(_putchar_r, (struct _reent *, int));
int	_EXFUN(_puts_r, (struct _reent *, const char *));
int	_EXFUN(_remove_r, (struct _reent *, const char *));
int	_EXFUN(_rename_r, (struct _reent *,
			   const char *_old, const char *_new));
int	_EXFUN(_scanf_r, (struct _reent *, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__scanf__, 2, 3))));
int	_EXFUN(_siprintf_r, (struct _reent *, char *, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 3, 4))));
int	_EXFUN(_siscanf_r, (struct _reent *, const char *, const char *, ...)
               _ATTRIBUTE ((__format__ (__scanf__, 3, 4))));
int	_EXFUN(_sniprintf_r, (struct _reent *, char *, size_t, const char *, ...)
               _ATTRIBUTE ((__format__ (__printf__, 4, 5))));
int	_EXFUN(_snprintf_r, (struct _reent *, char *__restrict, size_t, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 4, 5))));
int	_EXFUN(_sprintf_r, (struct _reent *, char *__restrict, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__printf__, 3, 4))));
int	_EXFUN(_sscanf_r, (struct _reent *, const char *__restrict, const char *__restrict, ...)
               _ATTRIBUTE ((__format__ (__scanf__, 3, 4))));
char *	_EXFUN(_tempnam_r, (struct _reent *, const char *, const char *));
FILE *	_EXFUN(_tmpfile_r, (struct _reent *));
char *	_EXFUN(_tmpnam_r, (struct _reent *, char *));
int	_EXFUN(_ungetc_r, (struct _reent *, int, FILE *));
int	_EXFUN(_vasiprintf_r, (struct _reent *, char **, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 3, 0))));
char *	_EXFUN(_vasniprintf_r, (struct _reent*, char *, size_t *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 4, 0))));
char *	_EXFUN(_vasnprintf_r, (struct _reent*, char *, size_t *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 4, 0))));
int	_EXFUN(_vasprintf_r, (struct _reent *, char **, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 3, 0))));
int	_EXFUN(_vdiprintf_r, (struct _reent *, int, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 3, 0))));
int	_EXFUN(_vdprintf_r, (struct _reent *, int, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 3, 0))));
int	_EXFUN(_vfiprintf_r, (struct _reent *, FILE *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 3, 0))));
int	_EXFUN(_vfiscanf_r, (struct _reent *, FILE *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__scanf__, 3, 0))));
int	_EXFUN(_vfprintf_r, (struct _reent *, FILE *__restrict, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 3, 0))));
int	_EXFUN(_vfscanf_r, (struct _reent *, FILE *__restrict, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__scanf__, 3, 0))));
int	_EXFUN(_viprintf_r, (struct _reent *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 2, 0))));
int	_EXFUN(_viscanf_r, (struct _reent *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__scanf__, 2, 0))));
int	_EXFUN(_vprintf_r, (struct _reent *, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 2, 0))));
int	_EXFUN(_vscanf_r, (struct _reent *, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__scanf__, 2, 0))));
int	_EXFUN(_vsiprintf_r, (struct _reent *, char *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 3, 0))));
int	_EXFUN(_vsiscanf_r, (struct _reent *, const char *, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__scanf__, 3, 0))));
int	_EXFUN(_vsniprintf_r, (struct _reent *, char *, size_t, const char *, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 4, 0))));
int	_EXFUN(_vsnprintf_r, (struct _reent *, char *__restrict, size_t, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 4, 0))));
int	_EXFUN(_vsprintf_r, (struct _reent *, char *__restrict, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__printf__, 3, 0))));
int	_EXFUN(_vsscanf_r, (struct _reent *, const char *__restrict, const char *__restrict, __VALIST)
               _ATTRIBUTE ((__format__ (__scanf__, 3, 0))));

/* Other extensions.  */

int	_EXFUN(fpurge, (FILE *));
ssize_t _EXFUN(__getdelim, (char **, size_t *, int, FILE *));
ssize_t _EXFUN(__getline, (char **, size_t *, FILE *));

#if __MISC_VISIBLE
void	_EXFUN(clearerr_unlocked, (FILE *));
int	_EXFUN(feof_unlocked, (FILE *));
int	_EXFUN(ferror_unlocked, (FILE *));
int	_EXFUN(fileno_unlocked, (FILE *));
int	_EXFUN(fflush_unlocked, (FILE *));
int	_EXFUN(fgetc_unlocked, (FILE *));
int	_EXFUN(fputc_unlocked, (int, FILE *));
size_t	_EXFUN(fread_unlocked, (_PTR __restrict, size_t _size, size_t _n, FILE *__restrict));
size_t	_EXFUN(fwrite_unlocked, (const _PTR __restrict , size_t _size, size_t _n, FILE *));
#endif

#if __GNU_VISIBLE
char *  _EXFUN(fgets_unlocked, (char *__restrict, int, FILE *__restrict));
int	_EXFUN(fputs_unlocked, (const char *__restrict, FILE *__restrict));
#endif

#ifdef __LARGE64_FILES
#if !defined(__CYGWIN__) || defined(_COMPILING_NEWLIB)
FILE *	_EXFUN(fdopen64, (int, const char *));
FILE *  _EXFUN(fopen64, (const char *, const char *));
FILE *  _EXFUN(freopen64, (_CONST char *, _CONST char *, FILE *));
_off64_t _EXFUN(ftello64, (FILE *));
_off64_t _EXFUN(fseeko64, (FILE *, _off64_t, int));
int     _EXFUN(fgetpos64, (FILE *, _fpos64_t *));
int     _EXFUN(fsetpos64, (FILE *, const _fpos64_t *));
FILE *  _EXFUN(tmpfile64, (void));

FILE *	_EXFUN(_fdopen64_r, (struct _reent *, int, const char *));
FILE *  _EXFUN(_fopen64_r, (struct _reent *,const char *, const char *));
FILE *  _EXFUN(_freopen64_r, (struct _reent *, _CONST char *, _CONST char *, FILE *));
_off64_t _EXFUN(_ftello64_r, (struct _reent *, FILE *));
_off64_t _EXFUN(_fseeko64_r, (struct _reent *, FILE *, _off64_t, int));
int     _EXFUN(_fgetpos64_r, (struct _reent *, FILE *, _fpos64_t *));
int     _EXFUN(_fsetpos64_r, (struct _reent *, FILE *, const _fpos64_t *));
FILE *  _EXFUN(_tmpfile64_r, (struct _reent *));
#endif /* !__CYGWIN__ */
#endif /* __LARGE64_FILES */

/*
 * Routines internal to the implementation.
 */

int	_EXFUN(__srget_r, (struct _reent *, FILE *));
int	_EXFUN(__swbuf_r, (struct _reent *, int, FILE *));

/*
 * Stdio function-access interface.
 */

#if __BSD_VISIBLE
# ifdef __LARGE64_FILES
FILE	*_EXFUN(funopen,(const _PTR __cookie,
		int (*__readfn)(_PTR __c, char *__buf,
				_READ_WRITE_BUFSIZE_TYPE __n),
		int (*__writefn)(_PTR __c, const char *__buf,
				 _READ_WRITE_BUFSIZE_TYPE __n),
		_fpos64_t (*__seekfn)(_PTR __c, _fpos64_t __off, int __whence),
		int (*__closefn)(_PTR __c)));
FILE	*_EXFUN(_funopen_r,(struct _reent *, const _PTR __cookie,
		int (*__readfn)(_PTR __c, char *__buf,
				_READ_WRITE_BUFSIZE_TYPE __n),
		int (*__writefn)(_PTR __c, const char *__buf,
				 _READ_WRITE_BUFSIZE_TYPE __n),
		_fpos64_t (*__seekfn)(_PTR __c, _fpos64_t __off, int __whence),
		int (*__closefn)(_PTR __c)));
# else
FILE	*_EXFUN(funopen,(const _PTR __cookie,
		int (*__readfn)(_PTR __cookie, char *__buf,
				_READ_WRITE_BUFSIZE_TYPE __n),
		int (*__writefn)(_PTR __cookie, const char *__buf,
				 _READ_WRITE_BUFSIZE_TYPE __n),
		fpos_t (*__seekfn)(_PTR __cookie, fpos_t __off, int __whence),
		int (*__closefn)(_PTR __cookie)));
FILE	*_EXFUN(_funopen_r,(struct _reent *, const _PTR __cookie,
		int (*__readfn)(_PTR __cookie, char *__buf,
				_READ_WRITE_BUFSIZE_TYPE __n),
		int (*__writefn)(_PTR __cookie, const char *__buf,
				 _READ_WRITE_BUFSIZE_TYPE __n),
		fpos_t (*__seekfn)(_PTR __cookie, fpos_t __off, int __whence),
		int (*__closefn)(_PTR __cookie)));
# endif /* !__LARGE64_FILES */

# define	fropen(__cookie, __fn) funopen(__cookie, __fn, (int (*)())0, \
					       (fpos_t (*)())0, (int (*)())0)
# define	fwopen(__cookie, __fn) funopen(__cookie, (int (*)())0, __fn, \
					       (fpos_t (*)())0, (int (*)())0)
#endif /* __BSD_VISIBLE */

#if __GNU_VISIBLE
typedef ssize_t cookie_read_function_t(void *__cookie, char *__buf, size_t __n);
typedef ssize_t cookie_write_function_t(void *__cookie, const char *__buf,
					size_t __n);
# ifdef __LARGE64_FILES
typedef int cookie_seek_function_t(void *__cookie, _off64_t *__off,
				   int __whence);
# else
typedef int cookie_seek_function_t(void *__cookie, off_t *__off, int __whence);
# endif /* !__LARGE64_FILES */
typedef int cookie_close_function_t(void *__cookie);
typedef struct
{
  /* These four struct member names are dictated by Linux; hopefully,
     they don't conflict with any macros.  */
  cookie_read_function_t  *read;
  cookie_write_function_t *write;
  cookie_seek_function_t  *seek;
  cookie_close_function_t *close;
} cookie_io_functions_t;
FILE *_EXFUN(fopencookie,(void *__cookie,
		const char *__mode, cookie_io_functions_t __functions));
FILE *_EXFUN(_fopencookie_r,(struct _reent *, void *__cookie,
		const char *__mode, cookie_io_functions_t __functions));
#endif /* __GNU_VISIBLE */

#ifndef __CUSTOM_FILE_IO__
/*
 * The __sfoo macros are here so that we can 
 * define function versions in the C library.
 */
#define       __sgetc_raw_r(__ptr, __f) (--(__f)->_r < 0 ? __srget_r(__ptr, __f) : (int)(*(__f)->_p++))

#ifdef __SCLE
/*  For a platform with CR/LF, additional logic is required by
  __sgetc_r which would otherwise simply be a macro; therefore we
  use an inlined function.  The function is only meant to be inlined
  in place as used and the function body should never be emitted.  

  There are two possible means to this end when compiling with GCC,
  one when compiling with a standard C99 compiler, and for other
  compilers we're just stuck.  At the moment, this issue only
  affects the Cygwin target, so we'll most likely be using GCC. */

_ELIDABLE_INLINE int __sgetc_r(struct _reent *__ptr, FILE *__p);

_ELIDABLE_INLINE int __sgetc_r(struct _reent *__ptr, FILE *__p)
  {
    int __c = __sgetc_raw_r(__ptr, __p);
    if ((__p->_flags & __SCLE) && (__c == '\r'))
      {
      int __c2 = __sgetc_raw_r(__ptr, __p);
      if (__c2 == '\n')
        __c = __c2;
      else
        ungetc(__c2, __p);
      }
    return __c;
  }
#else
#define __sgetc_r(__ptr, __p) __sgetc_raw_r(__ptr, __p)
#endif

#ifdef __GNUC__
_ELIDABLE_INLINE int __sputc_r(struct _reent *_ptr, int _c, FILE *_p) {
#ifdef __SCLE
	if ((_p->_flags & __SCLE) && _c == '\n')
	  __sputc_r (_ptr, '\r', _p);
#endif
	if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
		return (*_p->_p++ = _c);
	else
		return (__swbuf_r(_ptr, _c, _p));
}
#else
/*
 * This has been tuned to generate reasonable code on the vax using pcc
 */
#define       __sputc_raw_r(__ptr, __c, __p) \
	(--(__p)->_w < 0 ? \
		(__p)->_w >= (__p)->_lbfsize ? \
			(*(__p)->_p = (__c)), *(__p)->_p != '\n' ? \
				(int)*(__p)->_p++ : \
				__swbuf_r(__ptr, '\n', __p) : \
			__swbuf_r(__ptr, (int)(__c), __p) : \
		(*(__p)->_p = (__c), (int)*(__p)->_p++))
#ifdef __SCLE
#define __sputc_r(__ptr, __c, __p) \
        ((((__p)->_flags & __SCLE) && ((__c) == '\n')) \
          ? __sputc_raw_r(__ptr, '\r', (__p)) : 0 , \
        __sputc_raw_r((__ptr), (__c), (__p)))
#else
#define __sputc_r(__ptr, __c, __p) __sputc_raw_r(__ptr, __c, __p)
#endif
#endif

#define	__sfeof(p)	((int)(((p)->_flags & __SEOF) != 0))
#define	__sferror(p)	((int)(((p)->_flags & __SERR) != 0))
#define	__sclearerr(p)	((void)((p)->_flags &= ~(__SERR|__SEOF)))
#define	__sfileno(p)	((p)->_file)

#ifndef _REENT_SMALL
#define	feof(p)		__sfeof(p)
#define	ferror(p)	__sferror(p)
#define	clearerr(p)	__sclearerr(p)

#if __MISC_VISIBLE
#define	feof_unlocked(p)	__sfeof(p)
#define	ferror_unlocked(p)	__sferror(p)
#define	clearerr_unlocked(p)	__sclearerr(p)
#endif /* __MISC_VISIBLE */
#endif /* _REENT_SMALL */

#if 0 /* __POSIX_VISIBLE - FIXME: must initialize stdio first, use fn */
#define	fileno(p)	__sfileno(p)
#endif

#ifndef __CYGWIN__
#ifndef lint
#define	getc(fp)	__sgetc_r(_REENT, fp)
#define putc(x, fp)	__sputc_r(_REENT, x, fp)
#endif /* lint */
#endif /* __CYGWIN__ */

#if __MISC_VISIBLE
/* fast always-buffered version, true iff error */
#define	fast_putc(x,p) (--(p)->_w < 0 ? \
	__swbuf_r(_REENT, (int)(x), p) == EOF : (*(p)->_p = (x), (p)->_p++, 0))
#endif

#if __GNU_VISIBLE || (__XSI_VISIBLE && __XSI_VISIBLE < 600)
#define	L_cuserid	9		/* posix says it goes in stdio.h :( */
#endif
#if __POSIX_VISIBLE
#define L_ctermid       16
#endif

#endif /* !__CUSTOM_FILE_IO__ */

#define	getchar()	getc(stdin)
#define	putchar(x)	putc(x, stdout)

#if __MISC_VISIBLE || __POSIX_VISIBLE
#define	getchar_unlocked()	getc_unlocked(stdin)
#define	putchar_unlocked(x)	putc_unlocked(x, stdout)
#endif

#if ( defined (__mips_clib_small) || defined (__mips_clib_tiny) )

#undef	stdin
#undef	stdout
#undef	stderr
extern FILE *__stdin;
extern FILE *__stdout;
extern FILE *__stderr;
#define	stdin	__stdin
#define	stdout	__stdout
#define	stderr	__stderr

#if defined (__mips_fio_float__)
char * asnprintf_float (char *str, size_t *size, const char *fmt, ...);
int asprintf_float (char **str, const char *fmt, ...);
int dprintf_float (int fd, const char *fmt, ...);
int fprintf_float (FILE *fp, const char *fmt, ...);
int printf_float (const char *fmt, ...);
int snprintf_float (char *str, size_t size, const char *fmt, ...);
int sprintf_float (char *str, const char *fmt, ...);
char * vasnprintf_float (char *str, size_t *size, const char *fmt, __VALIST ap);
int vasprintf_float (char **str, const char *fmt, __VALIST ap);
int vdprintf_float (int fd, const char *fmt, __VALIST ap);
int vfprintf_float (FILE *fp, const char *fmt, __VALIST ap);
int vprintf_float (const char *fmt, __VALIST ap);
int vsnprintf_float (char *str, size_t size, const char *fmt, __VALIST ap);
int vsprintf_float (char *str, const char *fmt, __VALIST ap);

int fscanf_float (FILE *fp, const char *fmt, ...);
int scanf_float (const char *fmt, ...);
int sscanf_float ( const char *str, const char * fmt, ...);
int vfscanf_float (FILE *fp, const char *fmt, __VALIST ap);
int vscanf_float (const char *fmt, __VALIST ap);
int vsscanf_float (const char *str, const char *fmt, __VALIST ap);

#define asnprintf     asnprintf_float
#define asprintf      asprintf_float
#define dprintf       dprintf_float
#define fprintf       fprintf_float
#define printf        printf_float
#define snprintf      snprintf_float
#define sprintf       sprintf_float
#define vasnprintf    vasnprintf_float
#define vasprintf     vasprintf_float
#define vdprintf      vdprintf_float
#define vfprintf      vfprintf_float
#define vprintf       vprintf_float
#define vsnprintf     vsnprintf_float
#define vsprintf      vsprintf_float
#define fscanf        fscanf_float
#define scanf         scanf_float
#define sscanf        sscanf_float
#define vfscanf       vfscanf_float
#define vscanf        vscanf_float
#define vsscanf       vsscanf_float

#elif defined (__mips_fio_int__)

char * asnprintf_int (char *str, size_t *size, const char *fmt, ...);
int asprintf_int (char **str, const char *fmt, ...);
int dprintf_int (int fd, const char *fmt, ...);
int fprintf_int (FILE *fp, const char *fmt, ...);
int printf_int (const char *fmt, ...);
int snprintf_int (char *str, size_t size, const char *fmt, ...);
int sprintf_int (char *str, const char *fmt, ...);
char * vasnprintf_int (char *str, size_t *size, const char *fmt, __VALIST ap);
int vasprintf_int (char **str, const char *fmt, __VALIST ap);
int vdprintf_int (int fd, const char *fmt, __VALIST ap);
int vfprintf_int (FILE *fp, const char *fmt, __VALIST ap);
int vprintf_int (const char *fmt, __VALIST ap);
int vsnprintf_int (char *str, size_t size, const char *fmt, __VALIST ap);
int vsprintf_int (char *str, const char *fmt, __VALIST ap);

int fscanf_int (FILE *fp, const char *fmt, ...);
int scanf_int (const char *fmt, ...);
int sscanf_int ( const char *str, const char * fmt, ...);
int vfscanf_int (FILE *fp, const char *fmt, __VALIST ap);
int vscanf_int (const char *fmt, __VALIST ap);
int vsscanf_int (const char *str, const char *fmt, __VALIST ap);

#define asnprintf    asnprintf_int
#define asprintf     asprintf_int
#define dprintf      dprintf_int
#define fprintf      fprintf_int
#define printf       printf_int
#define snprintf     snprintf_int
#define sprintf      sprintf_int
#define vasnprintf   vasnprintf_int
#define vasprintf    vasprintf_int
#define vdprintf     vdprintf_int
#define vfprintf     vfprintf_int
#define vprintf      vprintf_int
#define vsnprintf    vsnprintf_int
#define vsprintf     vsprintf_int
#define fscanf       fscanf_int
#define scanf        scanf_int
#define sscanf       sscanf_int
#define vfscanf      vfscanf_int
#define vscanf       vscanf_int
#define vsscanf      vsscanf_int
#endif

#if defined (__mips_clib_tiny) && defined (__mips_no_file_io__)
void clearerr_nofio (FILE * afp);
int fclose_nofio (FILE *afp);
int feof_nofio (FILE * afp);
int ferror_nofio (FILE * afp);
int fflush_nofio (FILE *afp);
int fgetc_nofio (FILE * afp);
int fgetpos_nofio (FILE *fp, _fpos_t *pos);
char *fgets_nofio (char *buf, int n, FILE *afp);
FILE * fopen_nofio (const char *fname, const char *mode);
int fputc_nofio (int c, FILE * afp);
int fputs_nofio (char const *s, FILE *fp);
size_t fread_nofio (void * buf, size_t size, size_t count, FILE * afp);
FILE *freopen_nofio (const char *file, const char *mode, FILE *afp);
int fseek_nofio (register FILE *fp, long offset, int whence);
int fsetpos_nofio (FILE *fp, const _fpos_t *pos);
long ftell_nofio (FILE *fp);
size_t fwrite_nofio (const void * abuf, size_t size, size_t count, FILE * afp);
int getc_nofio (FILE *fp);
int getchar_nofio (void);
char * gets_nofio (char *buf);
int putc_nofio (int c, FILE *fp);
int putchar_nofio (int c);
int puts_nofio (const char *s);
int remove_nofio (const char *filename);
void rewind_nofio (FILE * fp);
void setbuf_nofio (FILE *fp, char *buf);
int setvbuf_nofio (FILE *afp, char *buf, int mode, size_t size);
FILE * tmpfile_nofio (void);
char *tmpnam_nofio (char *s);
int ungetc_nofio (int c, FILE *afp);
void perror_nofio (const char *s);

#define clearerr	clearerr_nofio
#define fclose		fclose_nofio
#define feof		feof_nofio
#define ferror		ferror_nofio
#define fflush		fflush_nofio
#define fgetc		fgetc_nofio
#define fgetpos		fgetpos_nofio
#define fgets		fgets_nofio
#define fopen		fopen_nofio
#define fputc		fputc_nofio
#define fputs		fputs_nofio
#define fread		fread_nofio
#define freopen		freopen_nofio
#define fseek		fseek_nofio
#define fsetpos		fsetpos_nofio
#define ftell		ftell_nofio
#define fwrite		fwrite_nofio
#define getc		getc_nofio
#define getchar		getchar_nofio
#define gets		gets_nofio
#define putc		putc_nofio
#define putchar		putchar_nofio
#define puts		puts_nofio
#define remove		remove_nofio
#define rewind		rewind_nofio
#define setbuf		setbuf_nofio
#define setvbuf		setvbuf_nofio
#define tmpfile		tmpfile_nofio
#define tmpnam		tmpnam_nofio
#define ungetc  ungetc_nofio
#define perror  perror_nofio
#endif

#undef	getc
#undef	putc
#undef	getchar
#undef	putchar
#undef	feof
#undef	ferror
#undef	clearerr

#endif

_END_STD_C

#endif /* _STDIO_H_ */
