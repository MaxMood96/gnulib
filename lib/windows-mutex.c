/* Plain mutexes (native Windows implementation).
   Copyright (C) 2005-2025 Free Software Foundation, Inc.

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

/* Written by Bruno Haible <bruno@clisp.org>, 2005.
   Based on GCC's gthr-win32.h.  */

#include <config.h>

/* Specification.  */
#include "windows-mutex.h"

#include <errno.h>
#include <stdlib.h>

void
glwthread_mutex_init (glwthread_mutex_t *mutex)
{
  mutex->owner = 0;
  InitializeCriticalSection (&mutex->lock);
  mutex->guard.done = 1;
}

int
glwthread_mutex_lock (glwthread_mutex_t *mutex)
{
  if (!mutex->guard.done)
    {
      if (InterlockedIncrement (&mutex->guard.started) == 0)
        /* This thread is the first one to need this mutex.  Initialize it.  */
        glwthread_mutex_init (mutex);
      else
        {
          /* Don't let mutex->guard.started grow and wrap around.  */
          InterlockedDecrement (&mutex->guard.started);
          /* Yield the CPU while waiting for another thread to finish
             initializing this mutex.  */
          while (!mutex->guard.done)
            Sleep (0);
        }
    }
  /* If this thread already owns the mutex, POSIX pthread_mutex_lock() is
     required to deadlock here.  But let's not do that on purpose.  */
  EnterCriticalSection (&mutex->lock);
  {
    DWORD self = GetCurrentThreadId ();
    mutex->owner = self;
  }
  return 0;
}

int
glwthread_mutex_trylock (glwthread_mutex_t *mutex)
{
  if (!mutex->guard.done)
    {
      if (InterlockedIncrement (&mutex->guard.started) == 0)
        /* This thread is the first one to need this mutex.  Initialize it.  */
        glwthread_mutex_init (mutex);
      else
        {
          /* Don't let mutex->guard.started grow and wrap around.  */
          InterlockedDecrement (&mutex->guard.started);
          /* Let another thread finish initializing this mutex, and let it also
             lock this mutex.  */
          return EBUSY;
        }
    }
  if (!TryEnterCriticalSection (&mutex->lock))
    return EBUSY;
  {
    DWORD self = GetCurrentThreadId ();
    /* TryEnterCriticalSection succeeded.  This means that the mutex was either
       previously unlocked (and thus mutex->owner == 0) or previously locked by
       this thread (and thus mutex->owner == self).  Since the mutex is meant to
       be plain, we need to fail in the latter case.  */
    if (mutex->owner == self)
      {
        LeaveCriticalSection (&mutex->lock);
        return EBUSY;
      }
    if (mutex->owner != 0)
      abort ();
    mutex->owner = self;
  }
  return 0;
}

int
glwthread_mutex_unlock (glwthread_mutex_t *mutex)
{
  if (!mutex->guard.done)
    return EINVAL;
  mutex->owner = 0;
  LeaveCriticalSection (&mutex->lock);
  return 0;
}

int
glwthread_mutex_destroy (glwthread_mutex_t *mutex)
{
  if (!mutex->guard.done)
    return EINVAL;
  DeleteCriticalSection (&mutex->lock);
  mutex->guard.done = 0;
  return 0;
}
