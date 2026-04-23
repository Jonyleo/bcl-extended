// SPDX-FileCopyrightText: 2021 Benjamin Brock
//
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <stdexcept>
#include "backend.hpp"

namespace BCL {

class request {
public:
  request() = default;
  request(const request&) = default;

  void wait() {
    // Nothing
  }

  bool check() const {
    return true;
  }
};

}

#include <bcl/core/future.hpp>
