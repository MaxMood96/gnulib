/* Test of u8_[v]asnprintf() function.
   Copyright (C) 2007, 2009-2025 Free Software Foundation, Inc.

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

/* Written by Bruno Haible <bruno@clisp.org>, 2007.  */

static void
test_function (uint8_t * (*my_asnprintf) (uint8_t *, size_t *, const char *, ...))
{
  uint8_t buf[8];
  int size;

  /* Test return value convention.  */

  for (size = 0; size <= 8; size++)
    {
      size_t length = size;
      uint8_t *result = my_asnprintf (NULL, &length, "%d", 12345);
      static const uint8_t expected[] = "12345";
      ASSERT (result != NULL);
      ASSERT (u8_strcmp (result, expected) == 0);
      ASSERT (length == 5);
      free (result);
    }

  for (size = 0; size <= 8; size++)
    {
      static const uint8_t initializer[] = "DEADBEEF";
      static const uint8_t expected[] = "12345";
      size_t length;
      uint8_t *result;

      u8_cpy (buf, initializer, 8);
      length = size;
      result = my_asnprintf (buf, &length, "%d", 12345);
      ASSERT (result != NULL);
      ASSERT (u8_strcmp (result, expected) == 0);
      ASSERT (length == 5);
      if (size < 6)
        ASSERT (result != buf);
      ASSERT (u8_cmp (buf + size, initializer + size, 8 - size) == 0);
      if (result != buf)
        free (result);
    }

  /* Verify that u8_[v]asnprintf() rejects a width > 2 GiB, < 4 GiB.  */
  {
    size_t length;
    uint8_t *s = my_asnprintf (NULL, &length, "x%03000000000dy\n", -17);
    ASSERT (s == NULL);
    ASSERT (errno == EOVERFLOW);
  }
  {
    static const uint8_t arg[] = { '@', 0 };
    size_t length;
    uint8_t *s = my_asnprintf (NULL, &length, "x%03000000000Uy\n", arg);
    ASSERT (s == NULL);
    ASSERT (errno == EOVERFLOW);
  }

  /* Verify that u8_[v]asnprintf() rejects a width > 4 GiB.  */
  {
    size_t length;
    uint8_t *s =
      my_asnprintf (NULL, &length,
                    "x%04294967306dy\n", /* 2^32 + 10 */
                    -17);
    ASSERT (s == NULL);
    ASSERT (errno == EOVERFLOW);
  }
  {
    static const uint8_t arg[] = { '@', 0 };
    size_t length;
    uint8_t *s =
      my_asnprintf (NULL, &length,
                    "x%04294967306Uy\n", /* 2^32 + 10 */
                    arg);
    ASSERT (s == NULL);
    ASSERT (errno == EOVERFLOW);
  }
  {
    size_t length;
    uint8_t *s =
      my_asnprintf (NULL, &length,
                    "x%018446744073709551626dy\n", /* 2^64 + 10 */
                    -17);
    ASSERT (s == NULL);
    ASSERT (errno == EOVERFLOW);
  }
  {
    static const uint8_t arg[] = { '@', 0 };
    size_t length;
    uint8_t *s =
      my_asnprintf (NULL, &length,
                    "x%018446744073709551626Uy\n", /* 2^64 + 10 */
                    arg);
    ASSERT (s == NULL);
    ASSERT (errno == EOVERFLOW);
  }
}
