/* Categories of Unicode characters.
   Copyright (C) 2002, 2006-2007, 2009-2025 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 2002.

   This file is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   This file is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include <config.h>

/* Specification.  */
#include "unictype.h"

#include "bitmap.h"

bool
uc_is_general_category (ucs4_t uc, uc_general_category_t category)
{
  if (category.generic)
    return category.lookup.lookup_fn (uc, category.bitmask);
  else
    return bitmap_lookup (category.lookup.table, uc);
}
