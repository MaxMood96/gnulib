/* Test of conversion of 32-bit wide string to string.
   Copyright (C) 2008-2025 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Written by Bruno Haible <bruno@clisp.org>, 2008.  */

#include <config.h>

#include <uchar.h>

#include "signature.h"
SIGNATURE_CHECK (c32srtombs, size_t,
                 (char *, const char32_t **, size_t, mbstate_t *));

#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"

int
main (int argc, char *argv[])
{
  /* configure should already have checked that the locale is supported.  */
  if (setlocale (LC_ALL, "") == NULL)
    return 1;

  if (argc > 1)
    {
      char32_t input[10];
      size_t n;
      const char32_t *src;
      #define BUFSIZE 20
      char buf[BUFSIZE];
      size_t ret;

      {
        size_t i;
        for (i = 0; i < BUFSIZE; i++)
          buf[i] = '_';
      }

      switch (argv[1][0])
        {
        case '2':
          /* Locale encoding is ISO-8859-1 or ISO-8859-15.  */
          {
            const char original[] = "B\374\337er"; /* "Büßer" */

            ret = mbstoc32s (input, original, 10);
            ASSERT (ret == 5);

            for (n = 0; n < 10; n++)
              {
                src = input;
                ret = c32srtombs (NULL, &src, n, NULL);
                ASSERT (ret == 5);
                ASSERT (src == input);

                src = input;
                ret = c32srtombs (buf, &src, n, NULL);
                ASSERT (ret == (n <= 5 ? n : 5));
                ASSERT (src == (n <= 5 ? input + n : NULL));
                ASSERT (memcmp (buf, original, ret) == 0);
                if (src == NULL)
                  ASSERT (buf[ret] == '\0');
                ASSERT (buf[ret + (src == NULL) + 0] == '_');
                ASSERT (buf[ret + (src == NULL) + 1] == '_');
                ASSERT (buf[ret + (src == NULL) + 2] == '_');
              }
          }
          break;

        case '3':
          /* Locale encoding is UTF-8.  */
          {
            const char original[] = "s\303\274\303\237\360\237\230\213!"; /* "süß😋!" */

            ret = mbstoc32s (input, original, 10);
            ASSERT (ret == 5);

            for (n = 0; n < 15; n++)
              {
                src = input;
                ret = c32srtombs (NULL, &src, n, NULL);
                ASSERT (ret == 10);
                ASSERT (src == input);

                src = input;
                ret = c32srtombs (buf, &src, n, NULL);
                ASSERT (ret == (n < 1 ? n :
                                n < 3 ? 1 :
                                n < 5 ? 3 :
                                n < 9 ? 5 :
                                n <= 10 ? n : 10));
                ASSERT (src == (n < 1 ? input + n :
                                n < 3 ? input + 1 :
                                n < 5 ? input + 2 :
                                n < 9 ? input + 3 :
                                n <= 10 ? input + (n - 5) : NULL));
                ASSERT (memcmp (buf, original, ret) == 0);
                if (src == NULL)
                  ASSERT (buf[ret] == '\0');
                ASSERT (buf[ret + (src == NULL) + 0] == '_');
                ASSERT (buf[ret + (src == NULL) + 1] == '_');
                ASSERT (buf[ret + (src == NULL) + 2] == '_');
              }
          }
          break;

        case '4':
          /* Locale encoding is EUC-JP.  */
          {
            const char original[] = "<\306\374\313\334\270\354>"; /* "<日本語>" */

            ret = mbstoc32s (input, original, 10);
            ASSERT (ret == 5);

            for (n = 0; n < 10; n++)
              {
                src = input;
                ret = c32srtombs (NULL, &src, n, NULL);
                ASSERT (ret == 8);
                ASSERT (src == input);

                src = input;
                ret = c32srtombs (buf, &src, n, NULL);
                ASSERT (ret == (n < 1 ? n :
                                n < 3 ? 1 :
                                n < 5 ? 3 :
                                n < 7 ? 5 :
                                n <= 8 ? n : 8));
                ASSERT (src == (n < 1 ? input + n :
                                n < 3 ? input + 1 :
                                n < 5 ? input + 2 :
                                n < 7 ? input + 3 :
                                n <= 8 ? input + (n - 3) : NULL));
                ASSERT (memcmp (buf, original, ret) == 0);
                if (src == NULL)
                  ASSERT (buf[ret] == '\0');
                ASSERT (buf[ret + (src == NULL) + 0] == '_');
                ASSERT (buf[ret + (src == NULL) + 1] == '_');
                ASSERT (buf[ret + (src == NULL) + 2] == '_');
              }
          }
          break;


        case '5':
          /* Locale encoding is GB18030.  */
          #if (defined __GLIBC__ && __GLIBC__ == 2 && __GLIBC_MINOR__ >= 13 && __GLIBC_MINOR__ <= 15) || (GL_CHAR32_T_IS_UNICODE && (defined __FreeBSD__ || defined __NetBSD__ || defined __sun))
          if (test_exit_status != EXIT_SUCCESS)
            return test_exit_status;
          fputs ("Skipping test: The GB18030 converter in this system's iconv is broken.\n", stderr);
          return 77;
          #endif
          {
            const char original[] = "s\250\271\201\060\211\070\224\071\375\067!"; /* "süß😋!" */

            ret = mbstoc32s (input, original, 10);
            ASSERT (ret == 5);

            for (n = 0; n < 15; n++)
              {
                src = input;
                ret = c32srtombs (NULL, &src, n, NULL);
                ASSERT (ret == 12);
                ASSERT (src == input);

                src = input;
                ret = c32srtombs (buf, &src, n, NULL);
                ASSERT (ret == (n < 1 ? n :
                                n < 3 ? 1 :
                                n < 7 ? 3 :
                                n < 11 ? 7 :
                                n <= 12 ? n : 12));
                ASSERT (src == (n < 1 ? input + n :
                                n < 3 ? input + 1 :
                                n < 7 ? input + 2 :
                                n < 11 ? input + 3 :
                                n <= 12 ? input + (n - 7) : NULL));
                ASSERT (memcmp (buf, original, ret) == 0);
                if (src == NULL)
                  ASSERT (buf[ret] == '\0');
                ASSERT (buf[ret + (src == NULL) + 0] == '_');
                ASSERT (buf[ret + (src == NULL) + 1] == '_');
                ASSERT (buf[ret + (src == NULL) + 2] == '_');
              }
          }
          break;

        default:
          return 1;
        }

      return test_exit_status;
    }

  return 1;
}
