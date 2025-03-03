/*
 * Copyright (C) 2008-2025 Free Software Foundation, Inc.
 * Written by Eric Blake and Bruno Haible
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include <config.h>

#include <string.h>

#include "signature.h"
SIGNATURE_CHECK (memchr, void *, (void const *, int, size_t));

#include <stdlib.h>

#include "zerosize-ptr.h"
#include "macros.h"

/* Test the library, not the compiler+library.  */
static void *
lib_memchr (void const *s, int c, size_t n)
{
  return memchr (s, c, n);
}
static void *(*volatile volatile_memchr) (void const *, int, size_t)
  = lib_memchr;
#undef memchr
#define memchr volatile_memchr

int
main (void)
{
  size_t n = 0x100000;
  char *input = malloc (n);
  ASSERT (input);

  input[0] = 'a';
  input[1] = 'b';
  memset (input + 2, 'c', 1024);
  memset (input + 1026, 'd', n - 1028);
  input[n - 2] = 'e';
  input[n - 1] = 'a';

  /* Basic behavior tests.  */
  ASSERT (memchr (input, 'a', n) == input);

  ASSERT (memchr (input, 'a', 0) == NULL);

  {
    void *page_boundary = zerosize_ptr ();
    if (page_boundary)
      ASSERT (memchr (page_boundary, 'a', 0) == NULL);
  }

  ASSERT (memchr (input, 'b', n) == input + 1);
  ASSERT (memchr (input, 'c', n) == input + 2);
  ASSERT (memchr (input, 'd', n) == input + 1026);

  ASSERT (memchr (input + 1, 'a', n - 1) == input + n - 1);
  ASSERT (memchr (input + 1, 'e', n - 1) == input + n - 2);
  ASSERT (memchr (input + 1, 0x789abc00 | 'e', n - 1) == input + n - 2);

  ASSERT (memchr (input, 'f', n) == NULL);
  ASSERT (memchr (input, '\0', n) == NULL);

  /* Check that a very long haystack is handled quickly if the byte is
     found near the beginning.  */
  {
    size_t repeat = 10000;
    for (; repeat > 0; repeat--)
      {
        ASSERT (memchr (input, 'c', n) == input + 2);
      }
  }

  /* Alignment tests.  */
  {
    int i, j;
    for (i = 0; i < 32; i++)
      {
        for (j = 0; j < 256; j++)
          input[i + j] = j;
        for (j = 0; j < 256; j++)
          {
            ASSERT (memchr (input + i, j, 256) == input + i + j);
          }
      }
  }

  /* Check that memchr() does not read past the first occurrence of the
     byte being searched.  See the Austin Group's clarification
     <https://www.opengroup.org/austin/docs/austin_454.txt>.
     Test both '\0' and something else, since some implementations
     special-case searching for NUL.
  */
  {
    char *page_boundary = (char *) zerosize_ptr ();
    /* Too small, and we miss cache line boundary tests; too large,
       and the test takes cubically longer to complete.  */
    int limit = 257;

    if (page_boundary != NULL)
      {
        for (n = 1; n <= limit; n++)
          {
            char *mem = page_boundary - n;
            memset (mem, 'X', n);
            ASSERT (memchr (mem, 'U', n) == NULL);
            ASSERT (memchr (mem, 0, n) == NULL);

            {
              size_t i;
              size_t k;

              for (i = 0; i < n; i++)
                {
                  mem[i] = 'U';
                  for (k = i + 1; k < n + limit; k++)
                    ASSERT (memchr (mem, 'U', k) == mem + i);
                  mem[i] = 0;
                  for (k = i + 1; k < n + limit; k++)
                    ASSERT (memchr (mem, 0, k) == mem + i);
                  mem[i] = 'X';
                }
            }
          }
      }
  }

  free (input);

  /* Test zero-length operations on NULL pointers, allowed by
     <https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3322.pdf>.  */
  ASSERT (memchr (NULL, '?', 0) == NULL);

  return test_exit_status;
}
