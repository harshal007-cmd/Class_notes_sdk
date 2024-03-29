	//header files
#include<windows.h>
#include"Window.h"


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
	TCHAR szAppName[]=TEXT("WINDEV");

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
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,NULL,
		hInstance,
		NULL);

	//show window
	ShowWindow(hwnd,iCmdShow);

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
	HDC hdc;
	TEXTMETRIC tm;
	SIZE sz;
	static int cyChar, cxChar, cxCaps;
	int i, X, Y;
	PAINTSTRUCT ps;
	RECT rc;
	char* str[] = { "HHHHH","AAAAA","RRRRR","SSSSS","HHHHH","AAAAA","LLLLL" };
	char* heading[] = { "HARSHAL","HARSHAL","HARSHAL","HARSHAL","HARSHAL","HARSHAL","HARSHAL" };

	//code
	switch (iMsg)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetTextExtentPoint32(hdc, heading[0], strlen(heading[0]), &sz);
		X = Y = 10;

		for (i = 0;i <= 10;++i) {
			TextOut(hdc, X, Y, heading[i], strlen(heading[i]));
			X = X + sz.cx;
		}
		X = 7;
		Y = Y + sz.cy;
		for (i = 0;i <= 6;++i) {
			TextOut(hdc, X, Y, str[i], strlen(str[i]));
			Y = Y + sz.cy;
		}
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}


