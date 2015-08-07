AC_PREREQ([2.69])
AC_INIT(server-client, 1.0)
AC_CONFIG_SRCDIR([src/server.c])
AM_INIT_AUTOMAKE
AC_PROG_CC
AC_HEADER_STDC
AC_CHECK_HEADERS([netdb.h netinet/in.h stdlib.h string.h sys/socket.h unistd.h])
AC_FUNC_ERROR_AT_LINE
AC_CHECK_FUNCS([bzero gethostbyname socket])
AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
