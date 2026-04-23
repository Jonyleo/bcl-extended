// SPDX-FileCopyrightText: 2021 Benjamin Brock
//
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include "alloc.hpp"
#include "comm.hpp"
#include "ops.hpp"
#include "request.hpp"

namespace BCL {

extern uint64_t shared_segment_size;
extern void *smem_base_ptr;

extern inline void init_malloc();

bool we_initialized;
bool bcl_finalized;

uint64_t my_rank;
uint64_t my_nprocs;

namespace backend {

uint64_t rank() {
  return BCL::my_rank;
}

uint64_t nprocs() {
  return BCL::my_nprocs;
}

} // end backend

void barrier() {
  // TODO what does this mean ? Must create this function
  MEUSI_Barrier();
}

void flush() {
  // TODO what does this mean ? Must create this function
  MEUSI_Flush();
}



struct shm_cond_t {
  uint64_t val;

  void wait(uint64_t val, pthread_spinlock_t &lock) {
    while(val != val) {
      pthread_spin_lock(lock);
    }
  }

  void signal(pthread_spinlock_t &lock) {
    pthread_spin_unlock(lock);
  }
};

struct CommData {
  struct barrier {
    pthread_spinlock_t lock;
    uint64_t val;

    void wait() {
      if(pthread_spin_trylock(&lock) == 0) {
        val += BCL::my_nprocs - 1;
        
        while(val != 0) { }

        for(int i = 0; i < BCL::my_nprocs-1; i++) {
          pthread_spin_unlock(&lock);
        }

      } else {
        val -= 1

        pthread_spin_lock(&lock);
      }
    }
  };

  struct broadcast {
    pthread_spinlock_t lock;
    
    uint64_t data;
    uint64_t size;

    uint8_t sender;

    uint8_t received_count;

    pthread_spinlock_t wait_locks[64];
    uint8_t wait_lock_status[64];


    void send(uint64_t _data, uint64_t _size) {
      pthread_spin_lock(&lock);

      data = _data;
      size = _size;

      sender = BCL::my_rank;

      received_count = 0;

      uint8_t received = 0;

      for(int i = 0; i < 64; i++) {
        if(wait_lock_status[i] != 0) {
          pthread_spin_unlock(&wait_locks[i]);
          received++;
        }
      }

      while(received != recived_count) {}
    } 
  }

  struct message {
    pthread_spinlock_t lock;
    shm_cond_t cond;

    uint8_t sender;
    uint8_t receiver;
    uint8_t received;
  }
}

// MPI communicator, shared_segment_size in MB,
// and whether to start the progress thread.
void init(uint64_t shared_segment_size = 256, bool thread_safe = false) {
  BCL::shared_segment_size = 1024*1024*shared_segment_size;

  int rank, nprocs;
  
  // TODO what does this mean ? Must create this function
  void shared_mem = MEUSI_Init(BCL::shared_segment_size);

  BCL::sm

  init_malloc();

  BCL::barrier();
}

void finalize() {
  BCL::barrier();

  // TODO what does this mean ? Must create this function
  MEUSI_Finalize();
}

} // end BCL
