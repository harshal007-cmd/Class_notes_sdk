//header files
#include<windows.h>
#include"Window.h"



//global function declaration
LRESULT CALLBACK WndProg(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

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
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	
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
	HANDLE hThread1, hThread2;
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hThread1 = CreateThread(NULL,
			0,
			(LPTHREAD_START_ROUTINE)ThreadProcOne,
			(LPVOID)hwnd,
			0,
			NULL);
		hThread2 = CreateThread(NULL,
			0,
			(LPTHREAD_START_ROUTINE)ThreadProcTwo,
			(LPVOID)hwnd,
			0,
			NULL);						
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("This is my message box"), TEXT("Message"),MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

DWORD WINAPI ThreadProcOne(LPVOID param)
{
	//vaiable declarations 
	HDC hdc;
	TCHAR str[255];
	LONG i;

	//code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc,RGB(0,0,0));
	SetTextColor(hdc, RGB(255,255,0));
	for (i = 0;i < LONG_MAX ;i++)
	{
		wsprintf(str,TEXT("Numbers in incrementing order: %d"),i);
		TextOut(hdc,5,5,str,wcslen(str));
	}
	ReleaseDC((HWND)param,hdc);
	return 0;

}

DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	//vaiable declarations 
	HDC hdc;
	TCHAR str[255];
	LONG i;

	//code
	hdc = GetDC((HWND)param);
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 255));
	for (i = LONG_MAX;i >= 0;i--)
	{
		wsprintf(str, TEXT("Numbers in decrementing order: %d"), i);
		TextOut(hdc, 5, 20, str, wcslen(str));
	}
	ReleaseDC((HWND)param, hdc);
	return 0;
}




