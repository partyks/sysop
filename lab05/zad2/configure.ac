#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([cw05zad2], [1.0], [mizmuda@student.agh.edu.pl])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([zad2.c])
AC_CONFIG_HEADERS([config.h])
AM_PROG_CC_C_O

AC_ARG_WITH(
	handler, 
	AC_HELP_STRING([--with-handler], [With sigaction is to be used]),
	[ if test "x$with_handler" = "xsigaction" ; then
		 AC_DEFINE([ACTION], [], [Set if sigaction is to be used])
         AC_MSG_RESULT([Yes])
      else
         AC_MSG_RESULT([No])
      fi ],
	AC_MSG_RESULT([No])
)



# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
