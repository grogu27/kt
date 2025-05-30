/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <folly/Portability.h>

// Disable a couple of warnings due to GMock exporting classes
// that derive from stdlib classes which aren't explicitly exported.
FOLLY_PUSH_WARNING
FOLLY_MSVC_DISABLE_WARNING(4251)
FOLLY_MSVC_DISABLE_WARNING(4275)
// IWYU pragma: begin_exports
#include <gmock/gmock.h>
// IWYU pragma: end_exports
FOLLY_POP_WARNING
