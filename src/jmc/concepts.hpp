#pragma once

#include <concepts>
#include <type_traits>

namespace jmc {
template <typename T, typename U>
concept IsComparable = requires(T a, U b) { {a == b} -> std::same_as<bool>; };

template <typename T>
concept NonPtrNonRef = requires { !std::is_pointer_v<T> && !std::is_reference_v<T>; };
} // namespace jmc