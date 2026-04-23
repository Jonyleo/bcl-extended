// SPDX-FileCopyrightText: 2021 Benjamin Brock
//
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

namespace BCL {
  inline uint8_t compare_and_swap(GlobalPtr<uint8_t> ptr, uint8_t old_val, uint8_t new_val) {
    return atomic_cas_8(ptr.local(),old_val,new_val);
  }

  inline uint16_t compare_and_swap(GlobalPtr<uint16_t> ptr, uint16_t old_val, uint16_t new_val) {
    return atomic_cas_16(ptr.local(),old_val,new_val);
  }

  inline uint32_t compare_and_swap(GlobalPtr<uint32_t> ptr, uint32_t old_val, uint32_t new_val) {
    return atomic_cas_32(ptr.local(),old_val,new_val);
  }

  inline uint64_t compare_and_swap(GlobalPtr<uint64_t> ptr, uint64_t old_val, uint64_t new_val) {
    return atomic_cas_64(ptr.local(),old_val,new_val);
  }
}
