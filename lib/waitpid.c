/* Wait for process state change.
   Copyright (C) 2001-2003, 2005-2025 Free Software Foundation, Inc.

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
#include <sys/wait.h>

/* Implementation for native Windows systems.  */

#include <process.h> /* for _cwait, WAIT_CHILD */

pid_t
waitpid (pid_t pid, int *statusp, int options)
{
  return _cwait (statusp, pid, WAIT_CHILD);
}
