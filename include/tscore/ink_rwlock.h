/** @file

  A thin wrapper for pthread rwlocks.

  @section license License

  Licensed to the Apache Software Foundation (ASF) under one
  or more contributor license agreements.  See the NOTICE file
  distributed with this work for additional information
  regarding copyright ownership.  The ASF licenses this file
  to you under the Apache License, Version 2.0 (the
  "License"); you may not use this file except in compliance
  with the License.  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
 */

//-------------------------------------------------------------------------
// Read-Write Lock -- Code from Stevens' Unix Network Programming -
// Interprocess Communications.  This is the simple implementation and
// will not work if used in conjunction with ink_thread_cancel().
//-------------------------------------------------------------------------

#pragma once

#include "tscore/ink_error.h"
#include <pthread.h>

typedef pthread_rwlock_t ink_rwlock;

void ink_rwlock_init(ink_rwlock *rw);
void ink_rwlock_destroy(ink_rwlock *rw);

// Instead of calling ink_rwlock_init(), an ink_rwlock instance can be initialized with one of thsee values.
//
ink_rwlock const INK_RWLOCK_INIT = PTHREAD_RWLOCK_INITIALIZER;
#if defined(__linux__)
ink_rwlock const INK_RWLOCK_INIT_NO_WRITER_STARVATION = PTHREAD_RWLOCK_WRITER_NONRECURSIVE_INITIALIZER_NP;
#else
// Testing indicates that for MacOS/Darwin and FreeBSD, pthread rwlocks always prevent writer starvation.
//
ink_rwlock const INK_RWLOCK_INIT_NO_WRITER_STARVATION = INK_RWLOCK_INIT;

#if !(defined(darwin) || defined(freebsd))
#warning "Use of ink_rwlock may result in writer starvation"
#endif
#endif

inline void
ink_rwlock_rdlock(ink_rwlock *rw)
{
  int error = pthread_rwlock_rdlock(rw);
  if (unlikely(error != 0)) {
    ink_abort("pthread_rwlock_rdlock(%p) failed: %s (%d)", rw, strerror(error), error);
  }
}

inline bool
ink_rwlock_tryrdlock(ink_rwlock *rw)
{
  int error = pthread_rwlock_tryrdlock(rw);
  if (EBUSY == error) {
    return false;
  }
  if (unlikely(error != 0)) {
    ink_abort("pthread_rwlock_tryrdlock(%p) failed: %s (%d)", rw, strerror(error), error);
  }
  return true;
}

inline void
ink_rwlock_wrlock(ink_rwlock *rw)
{
  int error = pthread_rwlock_wrlock(rw);
  if (unlikely(error != 0)) {
    ink_abort("pthread_rwlock_wrlock(%p) failed: %s (%d)", rw, strerror(error), error);
  }
}

inline bool
ink_rwlock_trywrlock(ink_rwlock *rw)
{
  int error = pthread_rwlock_trywrlock(rw);
  if (EBUSY == error) {
    return false;
  }
  if (unlikely(error != 0)) {
    ink_abort("pthread_rwlock_trywrlock(%p) failed: %s (%d)", rw, strerror(error), error);
  }
  return true;
}

inline void
ink_rwlock_unlock(ink_rwlock *rw)
{
  int error = pthread_rwlock_unlock(rw);
  if (unlikely(error != 0)) {
    ink_abort("pthread_rwlock_unlock(%p) failed: %s (%d)", rw, strerror(error), error);
  }
}
