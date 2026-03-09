#include "nocrt.h" // IWYU pragma: keep
#include <windows.h> // IWYU pragma: keep

// Halal c includes
#include <stdint.h> // IWYU pragma: keep
#include <stddef.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stdbool.h> // IWYU pragma: keep
#include <intrin.h> // IWYU pragma: keep

__attribute((force_align_arg_pointer, used, noreturn))
void entry_point() {

    ExitProcess(0);
}