// SPDX-FileCopyrightText: 2021 Benjamin Brock
//
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <stdexcept>
#include <cstring>
#include <vector>

#include <type_traits>

#include "backend.hpp"
#include "ops.hpp"
#include "request.hpp"
#include "async_allocator.hpp"
#include "atomics.hpp"

namespace BCL {

// Read size T's from src -> dst
// Blocks until dst is ready.
template <typename T>
inline void read(GlobalPtr<std::add_const_t<T>> src, T *dst, std::size_t size) {
  static_assert(sizeof(T) <= 64);

  *dst = *(src.local());
}

// Read size T's from src -> dst
// Just a regular read. If the type is 64 bytes or less (1 cache line), then the read is atomic
// If the type is not 64 bytes or less, then the application itself needs to do something about it
template <typename T>
inline void atomic_read(GlobalPtr<std::add_const_t<T>> src, T *dst, std::size_t size) {
  static_assert(sizeof(T) <= 64);

  *dst = *(src.local());
}

// Write size T's from src -> dst
template <typename T>
inline void write(const T *src, GlobalPtr<T> dst, size_t size) {
  static_assert(sizeof(T) <= 64);

  *(dst.local()) = *src;
}

template <typename T>
inline BCL::request async_read(GlobalPtr<std::add_const_t<T>> src, T* dst, size_t size) {
  MPI_Request request;

  BCL::read(src, dst, size);

  return BCL::request();
}

template <typename T>
inline BCL::request async_write(const T* src, GlobalPtr<T> dst, size_t size) {
  MPI_Request request;

  BCL::write(src, dst, size);

  return BCL::request();
}

template <typename T>
inline T broadcast(T &val, uint64_t root) {
  throw debug_error("BCL broadcast(): Has not been implemented on CXLSHM backend.");
}

template <typename T>
inline void broadcast(T* val, uint64_t root, size_t size, const BCL::Team& team) {
  throw debug_error("BCL broadcast() (with teams): Has not been implemented on CXLSHM backend.");
}

template <typename T>
inline auto arbroadcast(T* val, uint64_t root, size_t size, const BCL::Team& team) {
  throw debug_error("BCL arbroadcast(): Has not been implemented on CXLSHM backend.");
  return BCL::request();
}

template <typename T, typename Allocator>
inline void broadcast(std::vector<T, Allocator>& val, uint64_t root, const BCL::Team& team) {
  throw debug_error("BCL broadcast() (with teams): Has not been implemented on CXLSHM backend.");
}

template <typename T>
inline T broadcast(T& val, uint64_t root, const BCL::Team& team) {
  throw debug_error("BCL broadcast() (with teams): Has not been implemented on CXLSHM backend.");
}

template <typename T, typename Op>
inline T allreduce(const T& val, Op fn) {
  throw debug_error("BCL allreduce(): Has not been implemented on CXLSHM backend.");
}

template <typename T>
inline T allreduce(const T &val, const abstract_op <T> &op) {
  throw debug_error("BCL allreduce(): Has not been implemented on CXLSHM backend.");
}

template <typename T>
inline T fetch_and_op(const GlobalPtr <T> ptr, const T &val, const atomic_op <T> &op) {
  throw debug_error("BCL fetch_and_op(): Has not been implemented on CXLSHM backend.");
}

template <typename T>
inline BCL::future<T> arfetch_and_op(const GlobalPtr<T> ptr, const T& val, const atomic_op<T>& op) {
  throw debug_error("BCL arfetch_and_op(): Has not been implemented on CXLSHM backend.");
}

inline int int_compare_and_swap(const GlobalPtr <int> ptr, const int old_val, const int new_val) {
  return BCL::compare_and_swap(ptr, old_val, new_val);
}

inline uint16_t uint16_compare_and_swap(const GlobalPtr <uint16_t> ptr, const uint16_t old_val, const uint16_t new_val) {
  return BCL::compare_and_swap(ptr, old_val, new_val);
}

inline uint64_t uint64_compare_and_swap(const GlobalPtr <uint64_t> ptr, const uint64_t old_val, const uint64_t new_val) {
  return BCL::compare_and_swap(ptr, old_val, new_val);
}

} // end BCL
