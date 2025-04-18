# locale-ja.m4
# serial 19
dnl Copyright (C) 2003, 2005-2025 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.
dnl This file is offered as-is, without any warranty.

dnl From Bruno Haible.

dnl Determine the name of a japanese locale with EUC-JP encoding.
AC_DEFUN_ONCE([gt_LOCALE_JA],
[
  AC_REQUIRE([AC_CANONICAL_HOST])
  AC_REQUIRE([AM_LANGINFO_CODESET])
  AC_CACHE_CHECK([for a traditional japanese locale], [gt_cv_locale_ja], [
    AC_LANG_CONFTEST([AC_LANG_SOURCE([[
#include <locale.h>
#include <time.h>
#if HAVE_LANGINFO_CODESET
# include <langinfo.h>
#endif
#include <stdlib.h>
#include <string.h>
struct tm t;
char buf[16];
int main ()
{
  /* On BeOS and Haiku, locales are not implemented in libc.  Rather, libintl
     imitates locale dependent behaviour by looking at the environment
     variables, and all locales use the UTF-8 encoding.  */
#if defined __BEOS__ || defined __HAIKU__
  return 1;
#else
  /* Check whether the given locale name is recognized by the system.  */
# if defined _WIN32 && !defined __CYGWIN__
  /* On native Windows, setlocale(category, "") looks at the system settings,
     not at the environment variables.  Also, when an encoding suffix such
     as ".65001" or ".54936" is specified, it succeeds but sets the LC_CTYPE
     category of the locale to "C".  */
  if (setlocale (LC_ALL, getenv ("LC_ALL")) == NULL
      || strcmp (setlocale (LC_CTYPE, NULL), "C") == 0)
    return 1;
# else
  if (setlocale (LC_ALL, "") == NULL) return 1;
# endif
  /* Check whether nl_langinfo(CODESET) is nonempty and not "ASCII" or "646".
     On Mac OS X 10.3.5 (Darwin 7.5) in the fr_FR locale, nl_langinfo(CODESET)
     is empty, and the behaviour of Tcl 8.4 in this locale is not useful.
     On OpenBSD 4.0, when an unsupported locale is specified, setlocale()
     succeeds but then nl_langinfo(CODESET) is "646". In this situation,
     some unit tests fail.
     On MirBSD 10, when an unsupported locale is specified, setlocale()
     succeeds but then nl_langinfo(CODESET) is "UTF-8".  */
# if HAVE_LANGINFO_CODESET
  {
    const char *cs = nl_langinfo (CODESET);
    if (cs[0] == '\0' || strcmp (cs, "ASCII") == 0 || strcmp (cs, "646") == 0
        || strcmp (cs, "UTF-8") == 0)
      return 1;
  }
# endif
# ifdef __CYGWIN__
  /* On Cygwin, avoid locale names without encoding suffix, because the
     locale_charset() function relies on the encoding suffix.  Note that
     LC_ALL is set on the command line.  */
  if (strchr (getenv ("LC_ALL"), '.') == NULL) return 1;
# endif
  /* Check whether MB_CUR_MAX is > 1.  This excludes the dysfunctional locales
     on Cygwin 1.5.x.  */
  if (MB_CUR_MAX == 1)
    return 1;
  /* Check whether in a month name, no byte in the range 0x80..0x9F occurs.
     This excludes the UTF-8 encoding (except on MirBSD).  */
  {
    const char *p;
    t.tm_year = 1975 - 1900; t.tm_mon = 2 - 1; t.tm_mday = 4;
    if (strftime (buf, sizeof (buf), "%B", &t) < 2) return 1;
    for (p = buf; *p != '\0'; p++)
      if ((unsigned char) *p >= 0x80 && (unsigned char) *p < 0xa0)
        return 1;
  }
  return 0;
#endif
}
      ]])])
    if AC_TRY_EVAL([ac_link]) && test -s conftest$ac_exeext; then
      case "$host_os" in
        # Handle native Windows specially, because there setlocale() interprets
        # "ar" or "ara" as "Arabic" or "Arabic_Saudi Arabia.1256",
        # "en" or "eng" as "English" or "English_United States.1252",
        # "fr" or "fra" as "French" or "French_France.1252",
        # "ge"(!) or "deu"(!) as "German" or "German_Germany.1252",
        # "ja" or "jpn" as "Japanese" or "Japanese_Japan.932",
        # and similar.
        mingw* | windows*)
          # Note that on native Windows, the Japanese locale is
          # Japanese_Japan.932, and CP932 is very different from EUC-JP, so we
          # cannot use it here.
          gt_cv_locale_ja=none
          ;;
        *)
          # Setting LC_ALL is not enough. Need to set LC_TIME to empty, because
          # otherwise on Mac OS X 10.3.5 the LC_TIME=C from the beginning of the
          # configure script would override the LC_ALL setting. Likewise for
          # LC_CTYPE, which is also set at the beginning of the configure script.
          # Test for the AIX locale name.
          if (LC_ALL=ja_JP LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
            gt_cv_locale_ja=ja_JP
          else
            # Test for the locale name with explicit encoding suffix.
            if (LC_ALL=ja_JP.EUC-JP LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
              gt_cv_locale_ja=ja_JP.EUC-JP
            else
              # Test for the HP-UX, OSF/1, NetBSD locale name.
              if (LC_ALL=ja_JP.eucJP LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
                gt_cv_locale_ja=ja_JP.eucJP
              else
                # Test for the IRIX, FreeBSD locale name.
                if (LC_ALL=ja_JP.EUC LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
                  gt_cv_locale_ja=ja_JP.EUC
                else
                  # Test for the Solaris 10 locale name.
                  if (LC_ALL=ja LC_TIME= LC_CTYPE= ./conftest; exit) 2>/dev/null; then
                    gt_cv_locale_ja=ja
                  else
                    # Special test for NetBSD 1.6.
                    if test -f /usr/share/locale/ja_JP.eucJP/LC_CTYPE; then
                      gt_cv_locale_ja=ja_JP.eucJP
                    else
                      # None found.
                      gt_cv_locale_ja=none
                    fi
                  fi
                fi
              fi
            fi
          fi
          ;;
      esac
    fi
    rm -fr conftest*
  ])
  LOCALE_JA=$gt_cv_locale_ja
  case $LOCALE_JA in #(
    '' | *[[[:space:]\"\$\'*@<:@]]*)
      dnl This locale name might cause trouble with sh or make.
      AC_MSG_WARN([invalid locale "$LOCALE_JA"; assuming "none"])
      LOCALE_JA=none;;
  esac
  AC_SUBST([LOCALE_JA])
])
