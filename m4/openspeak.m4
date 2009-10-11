# Choose what you want to build

AC_DEFUN([OS_BUILD_WHAT],
[
    OS_WITH_CLIENT=no
    OS_WITH_SERVER=no
    
# Build the client?
    AC_ARG_ENABLE(client,
                AC_HELP_STRING([--disable-client],
                	[ Decide wether you want to have the client or not.]),
                [OS_WITH_CLIENT=$enableval], OS_WITH_CLIENT=yes)
    AM_CONDITIONAL([COND_CLIENT], [test "$OS_WITH_CLIENT" = yes]) 

# Build the server?
    AC_ARG_ENABLE(server,
                AC_HELP_STRING([--enable-server],
                	[ Decide wether you want to have the server or not.]),
                OS_WITH_SERVER=$enableval,)
    AM_CONDITIONAL([COND_SERVER], [test "$OS_WITH_SERVER" = yes])
])				
