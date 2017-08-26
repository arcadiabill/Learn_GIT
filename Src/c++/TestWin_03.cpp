#include <windows.h>

LRESULT WndProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
               LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX WndClsEx;

	WndClsEx.cbSize      = sizeof(WNDCLASSEX);
	WndClsEx.style       = CS_HREDRAW | CS_VREDRAW;
	WndClsEx.lpfnWndProc = WndProcedure;
	WndClsEx.cbClsExtra  = 0;
	WndClsEx.cbWndExtra  = 0;
	WndClsEx.hInstance   = hInstance;

	return 0;
}

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
    case WM_DESTROY:
        PostQuitMessage(WM_QUIT);
        break;
    default:
        return DefWindowProc(hWnd, Msg, wParam, lParam);
    }
    return 0;
}
