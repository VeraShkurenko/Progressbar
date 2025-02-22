#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

HWND hLogin, hPassword;

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        hLogin = GetDlgItem(hWnd, IDC_EDIT1);
        hPassword = GetDlgItem(hWnd, IDC_EDIT2);

        return TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDC_BUTTON1)
        {

            int length = SendMessage(hLogin, WM_GETTEXTLENGTH, 0, 0);
            TCHAR* buffer = new TCHAR[length + 1];
            GetWindowText(hLogin, buffer, length + 1);
            int lengthP = SendMessage(hPassword, WM_GETTEXTLENGTH, 0, 0);
            TCHAR* bufferP = new TCHAR[lengthP + 1];
            GetWindowText(hPassword, bufferP, lengthP + 1);

            bool isAdmin = _tcscmp(buffer, _TEXT("admin")) == 0 && _tcscmp(bufferP, _TEXT("admin")) == 0;

            MessageBox(hWnd, isAdmin ? TEXT("Користувач адмін") : TEXT("Користувач не адмін"), TEXT("Результат"), MB_OK);
            delete[] buffer;
        }
        return TRUE;
    case WM_SHOWWINDOW:
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}