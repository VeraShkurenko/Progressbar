#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

TCHAR szResult[100];
int points;

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        if (SendDlgItemMessage(hWnd, IDC_RADIO2, BM_GETCHECK, 0, 0) == BST_CHECKED) points += 20;
        if (SendDlgItemMessage(hWnd, IDC_RADIO4, BM_GETCHECK, 0, 0) == BST_CHECKED) points += 20;
        if (SendDlgItemMessage(hWnd, IDC_RADIO8, BM_GETCHECK, 0, 0) == BST_CHECKED) points += 20;

        if (SendDlgItemMessage(hWnd, IDC_CHECK3, BM_GETCHECK, 0, 0) != BST_CHECKED) 
        {
            if (SendDlgItemMessage(hWnd, IDC_CHECK1, BM_GETCHECK, 0, 0) == BST_CHECKED) points += 10;
            if (SendDlgItemMessage(hWnd, IDC_CHECK2, BM_GETCHECK, 0, 0) == BST_CHECKED) points += 10;
        }
        if (SendDlgItemMessage(hWnd, IDC_CHECK4, BM_GETCHECK, 0, 0) != BST_CHECKED)
        {
            if (SendDlgItemMessage(hWnd, IDC_CHECK5, BM_GETCHECK, 0, 0) == BST_CHECKED) points += 10;
            if (SendDlgItemMessage(hWnd, IDC_CHECK6, BM_GETCHECK, 0, 0) == BST_CHECKED) points += 10;
        }

        if (LOWORD(wParam) == IDC_BUTTON1)
        {
            wsprintf(szResult, TEXT("ʳ������ ����: %d/100"), points);
            MessageBox(hWnd, szResult, TEXT("���������"), MB_OK);
        }
        points = 0;
        return TRUE;
    case WM_SHOWWINDOW:
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}