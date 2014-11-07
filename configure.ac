#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([tableformat], [0.0.2], [okamura@informationsea.info])
AC_CONFIG_SRCDIR([tableformat.c])
AC_CONFIG_HEADERS([config.h])


AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([readme-alpha -Wall -Werror foreign color-tests])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

# Checks for programs.
AC_PROG_CC
AC_CONFIG_MACRO_DIR([m4])
ACLOCAL_AMFLAGS="-I m4"

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
