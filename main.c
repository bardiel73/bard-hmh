#include "nocrt.h" // IWYU pragma: keep
#include <windows.h> // IWYU pragma: keep

// Halal c includes
#include <stdint.h> // IWYU pragma: keep
#include <stddef.h> // IWYU pragma: keep
#include <stdarg.h> // IWYU pragma: keep
#include <stdbool.h> // IWYU pragma: keep
#include <intrin.h> // IWYU pragma: keep

static struct {
    HINSTANCE instance_handle;
    HWND window_handle;

    HANDLE stdout_handle;
    DWORD stdout_bytes_written;
} state_win32 = {0};

static LRESULT CALLBACK WindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
        case WM_CLOSE: { // user attempted to close the window
            // DestroyWindow(hwnd);
            PostQuitMessage(0);
        } break;

        case WM_DESTROY: { // the closed window's resources are getting released
            // thread is quiting (sends WM_QUIT, not handled by windproc, used to exit the inf loop in main)
            PostQuitMessage(0);
        } break;
	}
	return DefWindowProcW(wnd, msg, wparam, lparam);
}

static void init_layer_win32() {
    state_win32.stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    state_win32.instance_handle = GetModuleHandleA(NULL);

    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = state_win32.instance_handle;
    wc.lpszClassName = "bard_hmh_wc";
    wc.hCursor       = LoadCursorA(NULL, IDC_ARROW);
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0,
        "bard_hmh_wc",
        "TITLE",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, state_win32.instance_handle, NULL
    );
    state_win32.window_handle = hwnd;
}

void puts_win32(char* restrict msg) {
    WriteFile(state_win32.stdout_handle, msg, (DWORD)strlen(msg), &state_win32.stdout_bytes_written, NULL);
}

__attribute((force_align_arg_pointer, used, noreturn))
void entry_point() {
    init_layer_win32();

    MessageBox(0, "basically a game now", "ship it", MB_OK);


    ExitProcess(0);
}