#ifndef SORBET_CORE_ERRORS_INTERNAL_H
#define SORBET_CORE_ERRORS_INTERNAL_H
#include "core/Errors.h"

namespace sorbet::core::errors::Internal {
constexpr ErrorClass InternalError = {1001, StrictLevel::Stripe};
constexpr ErrorClass WrongSigil = {1002, StrictLevel::Stripe};
constexpr ErrorClass CyclicReferenceError = {1003, StrictLevel::Stripe};
} // namespace sorbet::core::errors::Internal

#endif
