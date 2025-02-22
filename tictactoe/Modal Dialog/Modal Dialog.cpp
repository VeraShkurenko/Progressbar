#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <vector>
#include <iostream>

using namespace std;

HINSTANCE hInst;
HBITMAP hX, hO;
HWND hBtn[9], hFirst;

int values[9];
vector<int> emptyCells;

bool userTurn;
bool gameRunning;
int winner = -1;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	srand(time(0));
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

void EndGame()
{
	gameRunning = false;
	winner = -1;
	for (int i = 0; i < 9; i++)
	{
		EnableWindow(hBtn[i], FALSE);
	}
}

bool WinCondition()
{
	for (int i = 0; i <= 1; i++)
	{
		if (values[0] == values[1] && values[1] == values[2] && values[1] == i ||
			values[3] == values[4] && values[4] == values[5] && values[4] == i ||
			values[6] == values[7] && values[7] == values[8] && values[7] == i ||
			values[0] == values[3] && values[3] == values[6] && values[3] == i ||
			values[1] == values[4] && values[4] == values[7] && values[4] == i ||
			values[2] == values[5] && values[5] == values[8] && values[5] == i ||
			values[0] == values[4] && values[4] == values[8] && values[4] == i ||
			values[2] == values[4] && values[4] == values[6] && values[4] == i)
		{
			winner = i;
			return true;
		}
	}
	return false;
}

void CheckTurn(HWND& hWnd)
{
	if (WinCondition())
	{
		MessageBox(hWnd, winner == 1 ? TEXT("Ви перемогли") : TEXT("Комп'ютер переміг"), TEXT("Кінец гри"), MB_OK | MB_ICONINFORMATION);
		EndGame();
	} 
	else if (emptyCells.empty())
	{
		MessageBox(hWnd, TEXT("Ніхто не виграв 🙁"), TEXT("Кінец гри"), MB_OK | MB_ICONINFORMATION);
	}
}

void SelectCell(HWND& hWnd, int index)
{
	emptyCells.erase(std::remove(emptyCells.begin(), emptyCells.end(), index), emptyCells.end());

	EnableWindow(hBtn[index], FALSE);
	SendMessage(hBtn[index], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(userTurn ? hX : hO));
	values[index] = userTurn ? 1 : 0;

	userTurn = !userTurn;

	CheckTurn(hWnd);
}

int RandomCell()
{
	return emptyCells[rand() % emptyCells.size()];
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		hO = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		hX = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		hFirst = GetDlgItem(hWnd, IDC_CHECK1);

		for (int i = 0; i < 9; i++)
		{
			hBtn[i] = GetDlgItem(hWnd, IDC_BUTTON1 + i);
			emptyCells.push_back(i);
		}
		
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BUTTON10)
		{
			gameRunning = true;
			emptyCells.clear();
			for (int i = 0; i < 9; i++)
			{
				values[i] = -1;
				EnableWindow(hBtn[i], TRUE);
				SendMessage(hBtn[i], BM_SETIMAGE, WPARAM(IMAGE_BITMAP), LPARAM(NULL));
				emptyCells.push_back(i);
			}
			LRESULT userFirst = SendMessage(hFirst, BM_GETCHECK, 0, 0) == BST_CHECKED;
			userTurn = userFirst;
			if (!userFirst)
			{
				SelectCell(hWnd, RandomCell());
			}
		}
		else
		{
			for (int i = 0; i < 9; i++)
			{
				if (LOWORD(wParam) == IDC_BUTTON1 + i)
				{
					SelectCell(hWnd, i);
					if (!emptyCells.empty() && gameRunning)
						SelectCell(hWnd, RandomCell());
				}
			}
		}
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	}
	return FALSE;
}