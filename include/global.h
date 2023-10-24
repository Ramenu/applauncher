#ifndef APPLAUNCHER_GLOBAL_H
#define APPLAUNCHER_GLOBAL_H

#include <cstdint>
#include <cstddef>

#ifndef NDEBUG
    static constexpr bool DEBUG = true;
#else
    static constexpr bool DEBUG = false;
#endif
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using usize = size_t;

#endif // APPLAUNCHER_GLOBAL_H