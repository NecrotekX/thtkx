AC_PREREQ(2.62) dnl 2.62 for AC_OPENMP.
AC_INIT([Touhou Toolkit Extra], [6],
        [mpp.translation@gmail.com / xarnonymous@gmail.com],
        [thtkx],
        [https://github.com/NecrotekX/thtkx])
AM_INIT_AUTOMAKE([1.9 foreign])
AC_CONFIG_SRCDIR([thdat.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

dnl PACKAGE_URL was introduced in autoconf 2.64.
m4_ifndef([AC_PACKAGE_URL],
          [AC_DEFINE([PACKAGE_URL], ["https://github.com/NecrotekX/thtkx"],
                     [Define to the home page for this package.])])

AH_TEMPLATE([HAVE_LIBPNG],
            [Define to 1 if libpng is available.])
AH_TEMPLATE([HAVE_ZLIB],
            [Define to 1 if zlib is available.])
AH_TEMPLATE([feof_unlocked],
            [These definitions are used to provide replacements
             if the unlocked stdio functions are missing.])
AH_TEMPLATE([fileno_unlocked], [...])
AH_TEMPLATE([fread_unlocked], [...])
AH_TEMPLATE([fwrite_unlocked], [...])
AH_TEMPLATE([getc_unlocked], [...])
AH_TEMPLATE([putc_unlocked], [...])
AH_TEMPLATE([__USE_MINGW_ANSI_STDIO],
            [Define to 1 to use MinGW's internal stdio library instead of Windows'.])
AH_TEMPLATE([API_SYMBOL], [Attribute for public functions.])

dnl check for programs

AC_PROG_CC_C99
AC_PROG_LEX
AM_PROG_LEX
AC_PROG_YACC
LT_INIT

dnl check for libraries

AC_ARG_WITH([libpng],
            [AS_HELP_STRING([--without-libpng],
                            [compile the package without image support])])
AS_IF([test "x$with_libpng" != xno],
      [PKG_CHECK_MODULES([libpng], [libpng zlib],
                         [AC_DEFINE([HAVE_LIBPNG], [1])]
                         [AC_DEFINE([HAVE_ZLIB], [1])]
                         )])

dnl check for header files

AC_CHECK_HEADERS([dnl
    libgen.h dnl basename
    sys/mman.h dnl
])

dnl check for types

AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

dnl check for structures

dnl check for compiler characteristics

AC_C_BIGENDIAN([AC_MSG_ERROR([big-endian systems are not supported])])

AC_OPENMP
AS_IF([test "x$enable_openmp" = xno || test "x$ac_cv_prog_c_openmp" = xunsupported],
      [THTK_TRY_CFLAGS([-Wno-unknown-pragmas])
       OPENMP_CFLAGS="$thtk_accepted_cflags"])

THTK_CHECK_PACKING

AC_CHECK_DECL([WIN32],
              [AC_DEFINE([__USE_MINGW_ANSI_STDIO], [1])])

dnl TODO: Make this work for Windows builds.
AC_CHECK_DECL([WIN32],
              [AC_DEFINE([API_SYMBOL], [__declspec(dllexport)])],
              [AC_DEFINE([API_SYMBOL], [__attribute__ ((visibility("default")))])])
THTK_TRY_CFLAGS([-fvisibility=hidden])
AC_SUBST([LIBCFLAGS], ["$thtk_accepted_cflags"])

dnl check for library functions

AC_CHECK_FUNCS([dnl
    _splitpath dnl
    mempcpy dnl
    mmap dnl
    munmap dnl
])

AC_CHECK_FUNC([feof_unlocked],   [], [AC_DEFINE([feof_unlocked],   [feof])])
AC_CHECK_FUNC([fileno_unlocked], [], [AC_DEFINE([fileno_unlocked], [fileno])])
AC_CHECK_FUNC([fread_unlocked],  [], [AC_DEFINE([fread_unlocked],  [fread])])
AC_CHECK_FUNC([fwrite_unlocked], [], [AC_DEFINE([fwrite_unlocked], [fwrite])])
AC_CHECK_FUNC([getc_unlocked],   [], [AC_DEFINE([getc_unlocked],   [getc])])
AC_CHECK_FUNC([putc_unlocked],   [], [AC_DEFINE([putc_unlocked],   [putc])])

AC_CONFIG_FILES([Makefile thtk/Makefile thtk/thtk.pc])
AC_OUTPUT
