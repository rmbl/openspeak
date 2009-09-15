# ===========================================================================
#        http://www.nongnu.org/autoconf-archive/ax_boost_signals.html
# ===========================================================================
#
# SYNOPSIS
#
#   AX_BOOST_SIGNALS2
#
# DESCRIPTION
#
#   Test for Signals library from the Boost C++ libraries. The macro
#   requires a preceding call to AX_BOOST_BASE. Further documentation is
#   available at <http://randspringer.de/boost/index.html>.
#
#   This macro sets:
#
#     HAVE_BOOST_SIGNALS2
#
# LICENSE
#
#   Copyright (c) 2008 Thomas Porschberg <thomas@randspringer.de>
#   Copyright (c) 2008 Michael Tindal
#
#   Copying and distribution of this file, with or without modification, are
#   permitted in any medium without royalty provided the copyright notice
#   and this notice are preserved.
#
#   Changes for Boost::Signals2 made by Philipp Gildein <rmbl@openspeak-project.org>

AC_DEFUN([AX_BOOST_SIGNALS2],
[

        AC_REQUIRE([AC_PROG_CC])
		CPPFLAGS_SAVED="$CPPFLAGS"
		CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS"
		export CPPFLAGS

		LDFLAGS_SAVED="$LDFLAGS"
		LDFLAGS="$LDFLAGS $BOOST_LDFLAGS"
		export LDFLAGS

        AC_CACHE_CHECK(whether the Boost::Signals2 library is available,
					   ax_cv_boost_signals,
        [AC_LANG_PUSH([C++])
		 AC_COMPILE_IFELSE(AC_LANG_PROGRAM([[@%:@include <boost/signals2.hpp>
											]],
                                  [[boost::signals2::signal<void ()> sig;
                                    return 0;
                                  ]]),
                           ax_cv_boost_signals=yes, ax_cv_boost_signals=no)
         AC_LANG_POP([C++])
		])
	    AC_DEFINE(HAVE_BOOST_SIGNALS2,,[define if the Boost::Signals2 library is available])

		CPPFLAGS="$CPPFLAGS_SAVED"
    	LDFLAGS="$LDFLAGS_SAVED"
])
