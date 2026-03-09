#ifndef NOCRT_H_
#define NOCRT_H_

#if defined(_MSC_VER)

#include <windows.h> // IWYU pragma: keep

#include <stddef.h> // IWYU pragma: keep
#include <stdint.h> // IWYU pragma: keep
#include <intrin.h> // IWYU pragma: keep

#define NOCRT_INLINE __forceinline

#undef RtlFillMemory
#undef RtlMoveMemory
#undef RtlCopyMemory
#undef RtlCompareMemory
DECLSPEC_IMPORT void WINAPI RtlFillMemory(void* Destination, size_t Length, char Fill);
DECLSPEC_IMPORT void WINAPI RtlMoveMemory(void* Destination, const void* Source, size_t Length);
DECLSPEC_IMPORT void WINAPI RtlCopyMemory(void* Destination, const void* Source, size_t Length);
DECLSPEC_IMPORT size_t WINAPI RtlCompareMemory(const void* Destination, const void* Source, size_t Length);

#pragma function (memset)
NOCRT_INLINE void* memset(void* dst, int value, size_t count) {
    RtlFillMemory(dst, count, value);
    return dst;
}

#pragma function (memmove)
NOCRT_INLINE void* memmove(void* dst, const void* src, size_t count) {
    RtlMoveMemory(dst, src, count);
    return dst;
}

#pragma function (memcpy)
NOCRT_INLINE void* memcpy(void* dst, const void* src, size_t count) {
    RtlCopyMemory(dst, src, count);
    return dst;
}

#pragma function (memcmp)
NOCRT_INLINE inline int memcmp(const void* p1, const void* p2, size_t n) {
    size_t same = RtlCompareMemory(p1, p2, n);
    if (same == n) return 0;
    const uint8_t *a = (const uint8_t*)p1 + same;
    const uint8_t *b = (const uint8_t*)p2 + same;
    return (*a > *b) - (*a < *b);
}

#elif defined(__GNUC__) || defined(__clang__)

#include <stddef.h> // IWYU pragma: keep
#include <stdint.h> // IWYU pragma: keep
#include <intrin.h> // IWYU pragma: keep

#define NOCRT_INLINE inline __attribute__((always_inline))

NOCRT_INLINE void* memcpy(void* dst, const void* src, size_t count) {
    return __builtin_memcpy(dst, src, count);
}

NOCRT_INLINE void* memmove(void* dst, const void* src, size_t count) {
    return __builtin_memmove(dst, src, count);
}

NOCRT_INLINE void* memset(void* ptr, int value, size_t count) {
    return __builtin_memset(ptr, value, count);
}

NOCRT_INLINE int memcmp(const void* p1, const void* p2, size_t count) {
    return __builtin_memcmp(p1, p2, count);
}

#else 
#error "unsupported toolchain, define your own mem* family of functions or link with CRT"
#endif // gcc/clang/msvc

#endif // NOCRT_H_