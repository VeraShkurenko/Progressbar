#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <string>
#include <iostream>

using namespace std;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	srand(time(0));
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

HWND hOutput, hList, hStart, hSum, hMult, hAver;
TCHAR szOutput[50];
TCHAR buf[5];
int amount;

int GenerateRandom()
{
	int value = (rand() % 20) - 10;
	return value == 0 ? GenerateRandom() : value;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		hOutput = GetDlgItem(hWnd, IDC_STATIC);
		hList = GetDlgItem(hWnd, IDC_LIST1);
		hStart = GetDlgItem(hWnd, IDC_BUTTON1);
		hSum = GetDlgItem(hWnd, IDC_RADIO1);
		hMult = GetDlgItem(hWnd, IDC_RADIO2);
		hAver = GetDlgItem(hWnd, IDC_RADIO3);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON1)
		{
			SetWindowText(hOutput, NULL);
			SendMessage(hList, LB_RESETCONTENT, 0, 0);

			EnableWindow(hSum, TRUE);
			EnableWindow(hMult, TRUE);
			EnableWindow(hAver, TRUE);
			SendMessage(hSum, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(hMult, BM_SETCHECK, BST_UNCHECKED, 0);
			SendMessage(hAver, BM_SETCHECK, BST_UNCHECKED, 0);

			amount = rand() % 10 + 10;
			for (int i = 0; i < amount; i++)
			{
				wsprintf(buf, TEXT("%d"), GenerateRandom());
				SendMessage(hList, LB_ADDSTRING, 0, LPARAM(buf));
			}
		}
		else if (LOWORD(wParam) == IDC_RADIO1)
		{
			int sum = 0;

			for (int i = 0; i < amount; i++)
			{
				SendMessage(hList, LB_GETTEXT, i, LPARAM(buf));
				sum += stoi(buf);
			}

			wsprintf(szOutput, TEXT("%d"), sum);
			SetWindowText(hOutput, szOutput);
		}
		else if (LOWORD(wParam) == IDC_RADIO2)
		{
			int mult = 1;

			for (int i = 0; i < amount; i++)
			{
				SendMessage(hList, LB_GETTEXT, i, LPARAM(buf));
				mult *= stoi(buf);
			}

			wsprintf(szOutput, TEXT("%d"), mult);
			SetWindowText(hOutput, szOutput);
		}
		else if (LOWORD(wParam) == IDC_RADIO3)
		{
			double aver = 0;

			for (int i = 0; i < amount; i++)
			{
				SendMessage(hList, LB_GETTEXT, i, LPARAM(buf));
				aver += stoi(buf);
			}

			aver /= amount;
			swprintf(szOutput, 50, TEXT("%.2f"), aver);
			SetWindowText(hOutput, szOutput);
		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}