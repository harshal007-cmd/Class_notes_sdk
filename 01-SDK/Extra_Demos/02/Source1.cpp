//header files
#include<windows.h>
#include"Window.h"
#include"Header1.h"


//global function declaration
LRESULT CALLBACK WndProg(HWND, UINT, WPARAM, LPARAM);

//global variable declaration

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("WINDEV");

	//code
	//WNDCLASSEX initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProg;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	//wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));


	//registration of WNDCLASSEX
	RegisterClassEx(&wndclass);

	//creating window
	hwnd = CreateWindow(szAppName,
		TEXT("HVS:Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL,
		hInstance,
		NULL);

	//show window
	ShowWindow(hwnd, iCmdShow);

	//update the window
	UpdateWindow(hwnd);

	//Message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);

}

LRESULT CALLBACK WndProg(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local variable declarations
	static int cxChar, cxCaps, cyChar, cyClient, iVscrollPos;
	HDC hdc;
	int i, y;
	PAINTSTRUCT ps;
	TCHAR szBuffer[10];
	TEXTMETRIC tm;

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		cxChar = tm.tmAveCharWidth;
		cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		ReleaseDC(hwnd, hdc);
		SetScrollRange(hwnd, SB_VERT, 0, NUMLINES - 1, FALSE);
		SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);
		return 0;
	case WM_SIZE:
		cyClient = HIWORD(lParam);
		return 0;
	case WM_VSCROLL:
		switch (LOWORD(wParam))
		{
		case SB_LINEUP:
			iVscrollPos -= 1;
			break;

		case SB_LINEDOWN:
			iVscrollPos += 1;
			break;

		case SB_PAGEUP:
			iVscrollPos -= cyClient / cyChar;
			break;

		case SB_PAGEDOWN:
			iVscrollPos += cyClient / cyChar;
			break;

		case SB_THUMBPOSITION:
			iVscrollPos = HIWORD(wParam);
			break;

		default:
			break;
		}
		iVscrollPos = max(0, min(iVscrollPos, NUMLINES - 1));
		if (iVscrollPos != GetScrollPos(hwnd, SB_VERT))
		{
			SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		return 0;
	
	
		 case WM_PAINT:
			 hdc = BeginPaint(hwnd, &ps);

			 for (i = 0; i < NUMLINES; i++)
			 {
				 y = cyChar * (i - iVscrollPos);

				 TextOut(hdc, 0, y,
					 sysmetrics[i].szLabel,
					 lstrlen(sysmetrics[i].szLabel));

				 TextOut(hdc, 22 * cxCaps, y,
					 sysmetrics[i].szDesc,
					 lstrlen(sysmetrics[i].szDesc));

				 SetTextAlign(hdc, TA_RIGHT | TA_TOP);
				 TextOut(hdc, 22 * cxCaps + 40 * cxChar, y, szBuffer,
					 wsprintf(szBuffer, TEXT("%5d"),
						 GetSystemMetrics(sysmetrics[i].iIndex)));

				 SetTextAlign(hdc, TA_LEFT | TA_TOP);
			 }
			 EndPaint(hwnd, &ps);
			 return 0;
		 case WM_DESTROY:
			 PostQuitMessage(0);
			 return 0;
		}
return DefWindowProc(hwnd, iMsg, wParam, lParam);
}