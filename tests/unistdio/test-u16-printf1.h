/* Test of u16_v[a]s[n]printf() function.
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
test_xfunction (uint16_t * (*my_xasprintf) (const char *, ...))
{
  /* Test support of size specifiers as in C99.  */

  {
    uint16_t *result =
      my_xasprintf ("%ju %d", (uintmax_t) 12345671, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '3', '4', '5', '6', '7', '1', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  {
    uint16_t *result =
      my_xasprintf ("%zu %d", (size_t) 12345672, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '3', '4', '5', '6', '7', '2', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  {
    uint16_t *result =
      my_xasprintf ("%tu %d", (ptrdiff_t) 12345673, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '3', '4', '5', '6', '7', '3', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  {
    uint16_t *result =
      my_xasprintf ("%Lg %d", (long double) 1.5, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '.', '5', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  /* Test the support of the 'U' conversion specifier for Unicode strings.  */

  {
    static const uint8_t unicode_string[] = "Hello";
    {
      uint16_t *result =
        my_xasprintf ("%U %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'H', 'e', 'l', 'l', 'o', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Width.  */
      uint16_t *result =
        my_xasprintf ("%10U %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', ' ', 'H', 'e', 'l', 'l', 'o', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Width given as argument.  */
      uint16_t *result =
        my_xasprintf ("%*U %d", 10, unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', ' ', 'H', 'e', 'l', 'l', 'o', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Negative width given as argument (cf. FLAG_LEFT below).  */
      uint16_t *result =
        my_xasprintf ("%*U %d", -10, unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'H', 'e', 'l', 'l', 'o', ' ', ' ', ' ', ' ', ' ', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* FLAG_LEFT.  */
      uint16_t *result =
        my_xasprintf ("%-10U %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'H', 'e', 'l', 'l', 'o', ' ', ' ', ' ', ' ', ' ', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* FLAG_ZERO: no effect.  */
      uint16_t *result =
        my_xasprintf ("%010U %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', ' ', 'H', 'e', 'l', 'l', 'o', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
  }
  { /* Width with a non-ASCII argument.  */
    static const uint8_t unicode_string[] = /* hétérogénéité */
      "h\303\251t\303\251rog\303\251n\303\251it\303\251";
    uint16_t *result =
      my_xasprintf ("%20U %d", unicode_string, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'h', 0x00e9, 't',
        0x00e9, 'r', 'o', 'g', 0x00e9, 'n', 0x00e9, 'i', 't', 0x00e9,
        ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }
  { /* Width with a non-BMP argument.  */
    static const uint8_t unicode_string[] = "\360\237\220\203"; /* 🐃 */
    uint16_t *result =
      my_xasprintf ("%10U %d", unicode_string, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 0xd83d,
        0xdc03, ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  {
    static const uint16_t unicode_string[] = { 'H', 'e', 'l', 'l', 'o', 0 };
    {
      uint16_t *result =
        my_xasprintf ("%lU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'H', 'e', 'l', 'l', 'o', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Width.  */
      uint16_t *result =
        my_xasprintf ("%10lU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', ' ', 'H', 'e', 'l', 'l', 'o', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Width given as argument.  */
      uint16_t *result =
        my_xasprintf ("%*lU %d", 10, unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', ' ', 'H', 'e', 'l', 'l', 'o', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Negative width given as argument (cf. FLAG_LEFT below).  */
      uint16_t *result =
        my_xasprintf ("%*lU %d", -10, unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'H', 'e', 'l', 'l', 'o', ' ', ' ', ' ', ' ', ' ', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* FLAG_LEFT.  */
      uint16_t *result =
        my_xasprintf ("%-10lU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'H', 'e', 'l', 'l', 'o', ' ', ' ', ' ', ' ', ' ', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* FLAG_ZERO: no effect.  */
      uint16_t *result =
        my_xasprintf ("%010lU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', ' ', 'H', 'e', 'l', 'l', 'o', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
  }
  { /* Width with a non-ASCII argument.  */
    static const uint16_t unicode_string[] = /* hétérogénéité */
      { 'h', 0x00e9, 't', 0x00e9, 'r', 'o', 'g', 0x00e9, 'n', 0x00e9,
        'i', 't', 0x00e9, 0
      };
    uint16_t *result =
      my_xasprintf ("%20lU %d", unicode_string, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'h', 0x00e9, 't',
        0x00e9, 'r', 'o', 'g', 0x00e9, 'n', 0x00e9, 'i', 't', 0x00e9,
        ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }
  { /* Width with a non-BMP argument.  */
    static const uint16_t unicode_string[] = { 0xd83d, 0xdc03, 0 }; /* 🐃 */
    uint16_t *result =
      my_xasprintf ("%10lU %d", unicode_string, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 0xd83d,
        0xdc03, ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  {
    static const uint32_t unicode_string[] = { 'H', 'e', 'l', 'l', 'o', 0 };
    {
      uint16_t *result =
        my_xasprintf ("%llU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'H', 'e', 'l', 'l', 'o', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Width.  */
      uint16_t *result =
        my_xasprintf ("%10llU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', ' ', 'H', 'e', 'l', 'l', 'o', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Width given as argument.  */
      uint16_t *result =
        my_xasprintf ("%*llU %d", 10, unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', ' ', 'H', 'e', 'l', 'l', 'o', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Negative width given as argument (cf. FLAG_LEFT below).  */
      uint16_t *result =
        my_xasprintf ("%*llU %d", -10, unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'H', 'e', 'l', 'l', 'o', ' ', ' ', ' ', ' ', ' ', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* FLAG_LEFT.  */
      uint16_t *result =
        my_xasprintf ("%-10llU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'H', 'e', 'l', 'l', 'o', ' ', ' ', ' ', ' ', ' ', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* FLAG_ZERO: no effect.  */
      uint16_t *result =
        my_xasprintf ("%010llU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', ' ', 'H', 'e', 'l', 'l', 'o', ' ', '3', '3', 0 };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
  }
  { /* Width with a non-ASCII argument.  */
    static const uint32_t unicode_string[] = /* hétérogénéité */
      { 'h', 0x00e9, 't', 0x00e9, 'r', 'o', 'g', 0x00e9, 'n', 0x00e9,
        'i', 't', 0x00e9, 0
      };
    uint16_t *result =
      my_xasprintf ("%20llU %d", unicode_string, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'h', 0x00e9, 't',
        0x00e9, 'r', 'o', 'g', 0x00e9, 'n', 0x00e9, 'i', 't', 0x00e9,
        ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }
  { /* Width with a non-BMP argument.  */
    static const uint32_t unicode_string[] = { 0x1f403, 0 }; /* 🐃 */
    uint16_t *result =
      my_xasprintf ("%10llU %d", unicode_string, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 0xd83d,
        0xdc03, ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  /* Test the support of the 's' conversion specifier for strings.  */

  {
    uint16_t *result =
      my_xasprintf ("Mr. %s %d", "Ronald Reagan", 33, 44, 55);
    static const uint16_t expected[] =
      { 'M', 'r', '.', ' ', 'R', 'o', 'n', 'a', 'l', 'd',
        ' ', 'R', 'e', 'a', 'g', 'a', 'n', ' ', '3', '3',
        0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Width.  */
    uint16_t *result =
      my_xasprintf ("Mr. %20s %d", "Ronald Reagan", 33, 44, 55);
    static const uint16_t expected[] =
      { 'M', 'r', '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', 'R', 'o', 'n', 'a', 'l', 'd', ' ', 'R', 'e',
        'a', 'g', 'a', 'n', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Width given as argument.  */
    uint16_t *result =
      my_xasprintf ("Mr. %*s %d", 20, "Ronald Reagan", 33, 44, 55);
    static const uint16_t expected[] =
      { 'M', 'r', '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', 'R', 'o', 'n', 'a', 'l', 'd', ' ', 'R', 'e',
        'a', 'g', 'a', 'n', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Negative width given as argument (cf. FLAG_LEFT below).  */
    uint16_t *result =
      my_xasprintf ("Mr. %*s %d", -20, "Ronald Reagan", 33, 44, 55);
    static const uint16_t expected[] =
      { 'M', 'r', '.', ' ', 'R', 'o', 'n', 'a', 'l', 'd',
        ' ', 'R', 'e', 'a', 'g', 'a', 'n', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* FLAG_LEFT.  */
    uint16_t *result =
      my_xasprintf ("Mr. %-20s %d", "Ronald Reagan", 33, 44, 55);
    static const uint16_t expected[] =
      { 'M', 'r', '.', ' ', 'R', 'o', 'n', 'a', 'l', 'd',
        ' ', 'R', 'e', 'a', 'g', 'a', 'n', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* FLAG_ZERO: no effect.  */
    uint16_t *result =
      my_xasprintf ("Mr. %020s %d", "Ronald Reagan", 33, 44, 55);
    static const uint16_t expected[] =
      { 'M', 'r', '.', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', 'R', 'o', 'n', 'a', 'l', 'd', ' ', 'R', 'e',
        'a', 'g', 'a', 'n', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  /* Test the support of the 'a' and 'A' conversion specifier for hexadecimal
     output of floating-point numbers.  */

  { /* A positive number.  */
    uint16_t *result =
      my_xasprintf ("%a %d", 3.1416015625, 33, 44, 55);
    static const uint16_t expected1[] =
      { '0', 'x', '1', '.', '9', '2', '2', 'p', '+', '1', ' ', '3', '3', 0 };
    static const uint16_t expected2[] =
      { '0', 'x', '3', '.', '2', '4', '4', 'p', '+', '0', ' ', '3', '3', 0 };
    static const uint16_t expected3[] =
      { '0', 'x', '6', '.', '4', '8', '8', 'p', '-', '1', ' ', '3', '3', 0 };
    static const uint16_t expected4[] =
      { '0', 'x', 'c', '.', '9', '1', 'p', '-', '2', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0
            || u16_strcmp (result, expected3) == 0
            || u16_strcmp (result, expected4) == 0);
    free (result);
  }

  { /* Width.  */
    uint16_t *result =
      my_xasprintf ("%10a %d", 1.75, 33, 44, 55);
    static const uint16_t expected1[] =
      { ' ', ' ', '0', 'x', '1', '.', 'c', 'p', '+', '0', ' ', '3', '3', 0 };
    static const uint16_t expected2[] =
      { ' ', ' ', '0', 'x', '3', '.', '8', 'p', '-', '1', ' ', '3', '3', 0 };
    static const uint16_t expected3[] =
      { ' ', ' ', ' ', ' ', '0', 'x', '7', 'p', '-', '2', ' ', '3', '3', 0 };
    static const uint16_t expected4[] =
      { ' ', ' ', ' ', ' ', '0', 'x', 'e', 'p', '-', '3', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0
            || u16_strcmp (result, expected3) == 0
            || u16_strcmp (result, expected4) == 0);
    free (result);
  }

  { /* Width given as argument.  */
    uint16_t *result =
      my_xasprintf ("%*a %d", 10, 1.75, 33, 44, 55);
    static const uint16_t expected1[] =
      { ' ', ' ', '0', 'x', '1', '.', 'c', 'p', '+', '0', ' ', '3', '3', 0 };
    static const uint16_t expected2[] =
      { ' ', ' ', '0', 'x', '3', '.', '8', 'p', '-', '1', ' ', '3', '3', 0 };
    static const uint16_t expected3[] =
      { ' ', ' ', ' ', ' ', '0', 'x', '7', 'p', '-', '2', ' ', '3', '3', 0 };
    static const uint16_t expected4[] =
      { ' ', ' ', ' ', ' ', '0', 'x', 'e', 'p', '-', '3', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0
            || u16_strcmp (result, expected3) == 0
            || u16_strcmp (result, expected4) == 0);
    free (result);
  }

  { /* Negative width given as argument (cf. FLAG_LEFT below).  */
    uint16_t *result =
      my_xasprintf ("%*a %d", -10, 1.75, 33, 44, 55);
    static const uint16_t expected1[] =
      { '0', 'x', '1', '.', 'c', 'p', '+', '0', ' ', ' ', ' ', '3', '3', 0 };
    static const uint16_t expected2[] =
      { '0', 'x', '3', '.', '8', 'p', '-', '1', ' ', ' ', ' ', '3', '3', 0 };
    static const uint16_t expected3[] =
      { '0', 'x', '7', 'p', '-', '2', ' ', ' ', ' ', ' ', ' ', '3', '3', 0 };
    static const uint16_t expected4[] =
      { '0', 'x', 'e', 'p', '-', '3', ' ', ' ', ' ', ' ', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0
            || u16_strcmp (result, expected3) == 0
            || u16_strcmp (result, expected4) == 0);
    free (result);
  }

  { /* Small precision.  */
    uint16_t *result =
      my_xasprintf ("%.10a %d", 1.75, 33, 44, 55);
    static const uint16_t expected1[] =
      { '0', 'x', '1', '.', 'c', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '+', '0', ' ', '3', '3',
        0
      };
    static const uint16_t expected2[] =
      { '0', 'x', '3', '.', '8', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '-', '1', ' ', '3', '3',
        0
      };
    static const uint16_t expected3[] =
      { '0', 'x', '7', '.', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '-', '2', ' ', '3', '3',
        0
      };
    static const uint16_t expected4[] =
      { '0', 'x', 'e', '.', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '-', '3', ' ', '3', '3',
        0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0
            || u16_strcmp (result, expected3) == 0
            || u16_strcmp (result, expected4) == 0);
    free (result);
  }

  { /* Large precision.  */
    uint16_t *result =
      my_xasprintf ("%.50a %d", 1.75, 33, 44, 55);
    static const uint16_t expected1[] =
      { '0', 'x', '1', '.', 'c', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '+', '0', ' ', '3', '3',
        0
      };
    static const uint16_t expected2[] =
      { '0', 'x', '3', '.', '8', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '-', '1', ' ', '3', '3',
        0
      };
    static const uint16_t expected3[] =
      { '0', 'x', '7', '.', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '-', '2', ' ', '3', '3',
        0
      };
    static const uint16_t expected4[] =
      { '0', 'x', 'e', '.', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '-', '3', ' ', '3', '3',
        0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0
            || u16_strcmp (result, expected3) == 0
            || u16_strcmp (result, expected4) == 0);
    free (result);
  }

  { /* A positive number.  */
    uint16_t *result =
      my_xasprintf ("%La %d", 3.1416015625L, 33, 44, 55);
    static const uint16_t expected1[] =
      { '0', 'x', '1', '.', '9', '2', '2', 'p', '+', '1',
        ' ', '3', '3', 0
      };
    static const uint16_t expected2[] =
      { '0', 'x', '3', '.', '2', '4', '4', 'p', '+', '0',
        ' ', '3', '3', 0
      };
    static const uint16_t expected3[] =
      { '0', 'x', '6', '.', '4', '8', '8', 'p', '-', '1',
        ' ', '3', '3', 0
      };
    static const uint16_t expected4[] =
      { '0', 'x', 'c', '.', '9', '1', 'p', '-', '2', ' ',
        '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0
            || u16_strcmp (result, expected3) == 0
            || u16_strcmp (result, expected4) == 0);
    free (result);
  }

  { /* Width.  */
    uint16_t *result =
      my_xasprintf ("%10La %d", 1.75L, 33, 44, 55);
    static const uint16_t expected1[] =
      { ' ', ' ', '0', 'x', '1', '.', 'c', 'p', '+', '0', ' ', '3', '3', 0 };
    static const uint16_t expected2[] =
      { ' ', ' ', '0', 'x', '3', '.', '8', 'p', '-', '1', ' ', '3', '3', 0 };
    static const uint16_t expected3[] =
      { ' ', ' ', ' ', ' ', '0', 'x', '7', 'p', '-', '2', ' ', '3', '3', 0 };
    static const uint16_t expected4[] =
      { ' ', ' ', ' ', ' ', '0', 'x', 'e', 'p', '-', '3', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0
            || u16_strcmp (result, expected3) == 0
            || u16_strcmp (result, expected4) == 0);
    free (result);
  }

  { /* Width given as argument.  */
    uint16_t *result =
      my_xasprintf ("%*La %d", 10, 1.75L, 33, 44, 55);
    static const uint16_t expected1[] =
      { ' ', ' ', '0', 'x', '1', '.', 'c', 'p', '+', '0', ' ', '3', '3', 0 };
    static const uint16_t expected2[] =
      { ' ', ' ', '0', 'x', '3', '.', '8', 'p', '-', '1', ' ', '3', '3', 0 };
    static const uint16_t expected3[] =
      { ' ', ' ', ' ', ' ', '0', 'x', '7', 'p', '-', '2', ' ', '3', '3', 0 };
    static const uint16_t expected4[] =
      { ' ', ' ', ' ', ' ', '0', 'x', 'e', 'p', '-', '3', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0
            || u16_strcmp (result, expected3) == 0
            || u16_strcmp (result, expected4) == 0);
    free (result);
  }

  { /* Negative width given as argument (cf. FLAG_LEFT below).  */
    uint16_t *result =
      my_xasprintf ("%*La %d", -10, 1.75L, 33, 44, 55);
    static const uint16_t expected1[] =
      { '0', 'x', '1', '.', 'c', 'p', '+', '0', ' ', ' ', ' ', '3', '3', 0 };
    static const uint16_t expected2[] =
      { '0', 'x', '3', '.', '8', 'p', '-', '1', ' ', ' ', ' ', '3', '3', 0 };
    static const uint16_t expected3[] =
      { '0', 'x', '7', 'p', '-', '2', ' ', ' ', ' ', ' ', ' ', '3', '3', 0 };
    static const uint16_t expected4[] =
      { '0', 'x', 'e', 'p', '-', '3', ' ', ' ', ' ', ' ', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0
            || u16_strcmp (result, expected3) == 0
            || u16_strcmp (result, expected4) == 0);
    free (result);
  }

  { /* Small precision.  */
    uint16_t *result =
      my_xasprintf ("%.10La %d", 1.75L, 33, 44, 55);
    static const uint16_t expected1[] =
      { '0', 'x', '1', '.', 'c', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '+', '0', ' ', '3', '3',
        0
      };
    static const uint16_t expected2[] =
      { '0', 'x', '3', '.', '8', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '-', '1', ' ', '3', '3',
        0
      };
    static const uint16_t expected3[] =
      { '0', 'x', '7', '.', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '-', '2', ' ', '3', '3',
        0
      };
    static const uint16_t expected4[] =
      { '0', 'x', 'e', '.', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '-', '3', ' ', '3', '3',
        0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0
            || u16_strcmp (result, expected3) == 0
            || u16_strcmp (result, expected4) == 0);
    free (result);
  }

  { /* Large precision.  */
    uint16_t *result =
      my_xasprintf ("%.50La %d", 1.75L, 33, 44, 55);
    static const uint16_t expected1[] =
      { '0', 'x', '1', '.', 'c', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '+', '0', ' ', '3', '3',
        0
      };
    static const uint16_t expected2[] =
      { '0', 'x', '3', '.', '8', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '-', '1', ' ', '3', '3',
        0
      };
    static const uint16_t expected3[] =
      { '0', 'x', '7', '.', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '-', '2', ' ', '3', '3',
        0
      };
    static const uint16_t expected4[] =
      { '0', 'x', 'e', '.', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '0', '0', '0', 'p', '-', '3', ' ', '3', '3',
        0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0
            || u16_strcmp (result, expected3) == 0
            || u16_strcmp (result, expected4) == 0);
    free (result);
  }

  /* Test the support of the %f format directive.  */

  { /* A positive number.  */
    uint16_t *result =
      my_xasprintf ("%f %d", 12.75, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '.', '7', '5', '0', '0', '0', '0', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Width.  */
    uint16_t *result =
      my_xasprintf ("%10f %d", 1.75, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', '1', '.', '7', '5', '0', '0', '0', '0', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Width given as argument.  */
    uint16_t *result =
      my_xasprintf ("%*f %d", 10, 1.75, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', '1', '.', '7', '5', '0', '0', '0', '0', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Negative width given as argument (cf. FLAG_LEFT below).  */
    uint16_t *result =
      my_xasprintf ("%*f %d", -10, 1.75, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '.', '7', '5', '0', '0', '0', '0', ' ', ' ', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Precision.  */
    uint16_t *result =
      my_xasprintf ("%.f %d", 1234.0, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '3', '4', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* A positive number.  */
    uint16_t *result =
      my_xasprintf ("%Lf %d", 12.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '.', '7', '5', '0', '0', '0', '0', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Width.  */
    uint16_t *result =
      my_xasprintf ("%10Lf %d", 1.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', '1', '.', '7', '5', '0', '0', '0', '0', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Width given as argument.  */
    uint16_t *result =
      my_xasprintf ("%*Lf %d", 10, 1.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', '1', '.', '7', '5', '0', '0', '0', '0', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Negative width given as argument (cf. FLAG_LEFT below).  */
    uint16_t *result =
      my_xasprintf ("%*Lf %d", -10, 1.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '.', '7', '5', '0', '0', '0', '0', ' ', ' ', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Precision.  */
    uint16_t *result =
      my_xasprintf ("%.Lf %d", 1234.0L, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '3', '4', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  /* Test the support of the %F format directive.  */

  { /* A positive number.  */
    uint16_t *result =
      my_xasprintf ("%F %d", 12.75, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '.', '7', '5', '0', '0', '0', '0', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Precision.  */
    uint16_t *result =
      my_xasprintf ("%.F %d", 1234.0, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '3', '4', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* A positive number.  */
    uint16_t *result =
      my_xasprintf ("%LF %d", 12.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '.', '7', '5', '0', '0', '0', '0', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Precision.  */
    uint16_t *result =
      my_xasprintf ("%.LF %d", 1234.0L, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '3', '4', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  /* Test the support of the %e format directive.  */

  { /* A positive number.  */
    uint16_t *result =
      my_xasprintf ("%e %d", 12.75, 33, 44, 55);
    static const uint16_t expected1[] =
      { '1', '.', '2', '7', '5', '0', '0', '0', 'e', '+',
        '0', '1', ' ', '3', '3', 0
      };
    static const uint16_t expected2[] =
      { '1', '.', '2', '7', '5', '0', '0', '0', 'e', '+',
        '0', '0', '1', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0);
    free (result);
  }

  { /* Width.  */
    uint16_t *result =
      my_xasprintf ("%15e %d", 1.75, 33, 44, 55);
    static const uint16_t expected1[] =
      { ' ', ' ', ' ', '1', '.', '7', '5', '0', '0', '0',
        '0', 'e', '+', '0', '0', ' ', '3', '3', 0
      };
    static const uint16_t expected2[] =
      { ' ', ' ', '1', '.', '7', '5', '0', '0', '0', '0',
        'e', '+', '0', '0', '0', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0);
    free (result);
  }

  { /* Width given as argument.  */
    uint16_t *result =
      my_xasprintf ("%*e %d", 15, 1.75, 33, 44, 55);
    static const uint16_t expected1[] =
      { ' ', ' ', ' ', '1', '.', '7', '5', '0', '0', '0',
        '0', 'e', '+', '0', '0', ' ', '3', '3', 0
      };
    static const uint16_t expected2[] =
      { ' ', ' ', '1', '.', '7', '5', '0', '0', '0', '0',
        'e', '+', '0', '0', '0', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0);
    free (result);
  }

  { /* Negative width given as argument (cf. FLAG_LEFT below).  */
    uint16_t *result =
      my_xasprintf ("%*e %d", -15, 1.75, 33, 44, 55);
    static const uint16_t expected1[] =
      { '1', '.', '7', '5', '0', '0', '0', '0', 'e', '+',
        '0', '0', ' ', ' ', ' ', ' ', '3', '3', 0
      };
    static const uint16_t expected2[] =
      { '1', '.', '7', '5', '0', '0', '0', '0', 'e', '+',
        '0', '0', '0', ' ', ' ', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0);
    free (result);
  }

  { /* Precision.  */
    uint16_t *result =
      my_xasprintf ("%.e %d", 1234.0, 33, 44, 55);
    static const uint16_t expected1[] =
      { '1', 'e', '+', '0', '3', ' ', '3', '3', 0 };
    static const uint16_t expected2[] =
      { '1', 'e', '+', '0', '0', '3', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0);
    free (result);
  }

  { /* A positive number.  */
    uint16_t *result =
      my_xasprintf ("%Le %d", 12.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '.', '2', '7', '5', '0', '0', '0', 'e', '+',
        '0', '1', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Width.  */
    uint16_t *result =
      my_xasprintf ("%15Le %d", 1.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', ' ', '1', '.', '7', '5', '0', '0', '0',
        '0', 'e', '+', '0', '0', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Width given as argument.  */
    uint16_t *result =
      my_xasprintf ("%*Le %d", 15, 1.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', ' ', '1', '.', '7', '5', '0', '0', '0',
        '0', 'e', '+', '0', '0', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Negative width given as argument (cf. FLAG_LEFT below).  */
    uint16_t *result =
      my_xasprintf ("%*Le %d", -15, 1.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '.', '7', '5', '0', '0', '0', '0', 'e', '+',
        '0', '0', ' ', ' ', ' ', ' ', '3', '3', 0
      };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Precision.  */
    uint16_t *result =
      my_xasprintf ("%.Le %d", 1234.0L, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', 'e', '+', '0', '3', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  /* Test the support of the %g format directive.  */

  { /* A positive number.  */
    uint16_t *result =
      my_xasprintf ("%g %d", 12.75, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '.', '7', '5', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Width.  */
    uint16_t *result =
      my_xasprintf ("%10g %d", 1.75, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', ' ', ' ', ' ', ' ', '1', '.', '7', '5', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Width given as argument.  */
    uint16_t *result =
      my_xasprintf ("%*g %d", 10, 1.75, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', ' ', ' ', ' ', ' ', '1', '.', '7', '5', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Negative width given as argument (cf. FLAG_LEFT below).  */
    uint16_t *result =
      my_xasprintf ("%*g %d", -10, 1.75, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '.', '7', '5', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Precision.  */
    uint16_t *result =
      my_xasprintf ("%.g %d", 1234.0, 33, 44, 55);
    static const uint16_t expected1[] =
      { '1', 'e', '+', '0', '3', ' ', '3', '3', 0 };
    static const uint16_t expected2[] =
      { '1', 'e', '+', '0', '0', '3', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected1) == 0
            || u16_strcmp (result, expected2) == 0);
    free (result);
  }

  { /* A positive number.  */
    uint16_t *result =
      my_xasprintf ("%Lg %d", 12.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '2', '.', '7', '5', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Width.  */
    uint16_t *result =
      my_xasprintf ("%10Lg %d", 1.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', ' ', ' ', ' ', ' ', '1', '.', '7', '5', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Width given as argument.  */
    uint16_t *result =
      my_xasprintf ("%*Lg %d", 10, 1.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { ' ', ' ', ' ', ' ', ' ', ' ', '1', '.', '7', '5', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Negative width given as argument (cf. FLAG_LEFT below).  */
    uint16_t *result =
      my_xasprintf ("%*Lg %d", -10, 1.75L, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', '.', '7', '5', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  { /* Precision.  */
    uint16_t *result =
      my_xasprintf ("%.Lg %d", 1234.0L, 33, 44, 55);
    static const uint16_t expected[] =
      { '1', 'e', '+', '0', '3', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  /* Test the support of the %n format directive.  */

  {
    int count = -1;
    uint16_t *result =
      my_xasprintf ("%d %n", 123, &count, 33, 44, 55);
#if NEED_PRINTF_WITH_N_DIRECTIVE
    static const uint16_t expected[] =
      { '1', '2', '3', ' ', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    ASSERT (count == 4);
    free (result);
#else
    ASSERT (result == NULL);
#endif
  }

  /* Test the support of the POSIX/XSI format strings with positions.  */

  {
    uint16_t *result =
      my_xasprintf ("%2$d %1$d", 33, 55);
    static const uint16_t expected[] =
      { '5', '5', ' ', '3', '3', 0 };
    ASSERT (result != NULL);
    ASSERT (u16_strcmp (result, expected) == 0);
    free (result);
  }

  /* Test the support of the grouping flag.  */

  {
    uint16_t *result =
      my_xasprintf ("%'d %d", 1234567, 99);
    ASSERT (result != NULL);
    ASSERT (result[u16_strlen (result) - 1] == '9');
    free (result);
  }

  /* Test the support of the 'U' conversion specifier for Unicode strings.  */

  {
    static const uint8_t unicode_string[] = "Rafa\305\202 Maszkowski"; /* Rafał Maszkowski */
    {
      uint16_t *result =
        my_xasprintf ("%U %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'R', 'a', 'f', 'a', 0x0142, ' ', 'M', 'a', 's', 'z',
          'k', 'o', 'w', 's', 'k', 'i', ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Width.  */
      uint16_t *result =
        my_xasprintf ("%20U %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', 'R', 'a', 'f', 'a', 0x0142, ' ',
          'M', 'a', 's', 'z', 'k', 'o', 'w', 's', 'k', 'i',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Width given as argument.  */
      uint16_t *result =
        my_xasprintf ("%*U %d", 20, unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', 'R', 'a', 'f', 'a', 0x0142, ' ',
          'M', 'a', 's', 'z', 'k', 'o', 'w', 's', 'k', 'i',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Negative width given as argument (cf. FLAG_LEFT below).  */
      uint16_t *result =
        my_xasprintf ("%*U %d", -20, unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'R', 'a', 'f', 'a', 0x0142, ' ', 'M', 'a', 's', 'z',
          'k', 'o', 'w', 's', 'k', 'i', ' ', ' ', ' ', ' ',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* FLAG_LEFT.  */
      uint16_t *result =
        my_xasprintf ("%-20U %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'R', 'a', 'f', 'a', 0x0142, ' ', 'M', 'a', 's', 'z',
          'k', 'o', 'w', 's', 'k', 'i', ' ', ' ', ' ', ' ',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* FLAG_ZERO: no effect.  */
      uint16_t *result =
        my_xasprintf ("%020U %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', 'R', 'a', 'f', 'a', 0x0142, ' ',
          'M', 'a', 's', 'z', 'k', 'o', 'w', 's', 'k', 'i',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
  }

  {
    static const uint16_t unicode_string[] = /* Rafał Maszkowski */
      {
        'R', 'a', 'f', 'a', 0x0142, ' ', 'M', 'a', 's', 'z', 'k', 'o', 'w',
        's', 'k', 'i', 0
      };
    {
      uint16_t *result =
        my_xasprintf ("%lU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'R', 'a', 'f', 'a', 0x0142, ' ', 'M', 'a', 's', 'z',
          'k', 'o', 'w', 's', 'k', 'i', ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Width.  */
      uint16_t *result =
        my_xasprintf ("%20lU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', 'R', 'a', 'f', 'a', 0x0142, ' ',
          'M', 'a', 's', 'z', 'k', 'o', 'w', 's', 'k', 'i',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Width given as argument.  */
      uint16_t *result =
        my_xasprintf ("%*lU %d", 20, unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', 'R', 'a', 'f', 'a', 0x0142, ' ',
          'M', 'a', 's', 'z', 'k', 'o', 'w', 's', 'k', 'i',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Negative width given as argument (cf. FLAG_LEFT below).  */
      uint16_t *result =
        my_xasprintf ("%*lU %d", -20, unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'R', 'a', 'f', 'a', 0x0142, ' ', 'M', 'a', 's', 'z',
          'k', 'o', 'w', 's', 'k', 'i', ' ', ' ', ' ', ' ',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* FLAG_LEFT.  */
      uint16_t *result =
        my_xasprintf ("%-20lU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'R', 'a', 'f', 'a', 0x0142, ' ', 'M', 'a', 's', 'z',
          'k', 'o', 'w', 's', 'k', 'i', ' ', ' ', ' ', ' ',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* FLAG_ZERO: no effect.  */
      uint16_t *result =
        my_xasprintf ("%020lU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', 'R', 'a', 'f', 'a', 0x0142, ' ',
          'M', 'a', 's', 'z', 'k', 'o', 'w', 's', 'k', 'i',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
  }

  {
    static const uint32_t unicode_string[] = /* Rafał Maszkowski */
      {
        'R', 'a', 'f', 'a', 0x0142, ' ', 'M', 'a', 's', 'z', 'k', 'o', 'w',
        's', 'k', 'i', 0
      };
    {
      uint16_t *result =
        my_xasprintf ("%llU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'R', 'a', 'f', 'a', 0x0142, ' ', 'M', 'a', 's', 'z',
          'k', 'o', 'w', 's', 'k', 'i', ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Width.  */
      uint16_t *result =
        my_xasprintf ("%20llU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', 'R', 'a', 'f', 'a', 0x0142, ' ',
          'M', 'a', 's', 'z', 'k', 'o', 'w', 's', 'k', 'i',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Width given as argument.  */
      uint16_t *result =
        my_xasprintf ("%*llU %d", 20, unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', 'R', 'a', 'f', 'a', 0x0142, ' ',
          'M', 'a', 's', 'z', 'k', 'o', 'w', 's', 'k', 'i',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* Negative width given as argument (cf. FLAG_LEFT below).  */
      uint16_t *result =
        my_xasprintf ("%*llU %d", -20, unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'R', 'a', 'f', 'a', 0x0142, ' ', 'M', 'a', 's', 'z',
          'k', 'o', 'w', 's', 'k', 'i', ' ', ' ', ' ', ' ',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* FLAG_LEFT.  */
      uint16_t *result =
        my_xasprintf ("%-20llU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { 'R', 'a', 'f', 'a', 0x0142, ' ', 'M', 'a', 's', 'z',
          'k', 'o', 'w', 's', 'k', 'i', ' ', ' ', ' ', ' ',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
    { /* FLAG_ZERO: no effect.  */
      uint16_t *result =
        my_xasprintf ("%020llU %d", unicode_string, 33, 44, 55);
      static const uint16_t expected[] =
        { ' ', ' ', ' ', ' ', 'R', 'a', 'f', 'a', 0x0142, ' ',
          'M', 'a', 's', 'z', 'k', 'o', 'w', 's', 'k', 'i',
          ' ', '3', '3', 0
        };
      ASSERT (result != NULL);
      ASSERT (u16_strcmp (result, expected) == 0);
      free (result);
    }
  }

  /* Test non-ASCII characters in the format string.  */

  {
    uint16_t *result =
      my_xasprintf ("\304rger", 33, 44, 55);
    ASSERT (result == NULL && errno == EINVAL);
  }
}
