#include "nocrt.h" // IWYU pragma: keep
#include <windows.h> // IWYU pragma: keep

__attribute((force_align_arg_pointer, used, noreturn))
void entry_point() {

    ExitProcess(0);
}