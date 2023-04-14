//header files
#include<windows.h>
#include"Window.h"
#define ID_NUMBER 501



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
	PAINTSTRUCT ps;
	RECT rc;
	static INT iPaintFlag = 0;
	HBRUSH hbrush;
	//TCHAR str[] = TEXT("Hello_World!!!!");
	
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd,ID_NUMBER,1000,NULL);
		break;
	case WM_TIMER:
		KillTimer(hwnd,ID_NUMBER);
		iPaintFlag++;
		if (iPaintFlag > 8)
		{
			iPaintFlag = 0;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd, ID_NUMBER, 1000, NULL);
 		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rc );
		hdc = BeginPaint(hwnd,&ps);
		if(iPaintFlag==1)
		{
			hbrush=CreateSolidBrush(RGB(255, 0, 0));
		}
		else if(iPaintFlag==2)
		{
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
		}
		else if(iPaintFlag==3)
		{
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
		}
		else if(iPaintFlag==4)
		{
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
		}
		else if (iPaintFlag == 5)
		{
			hbrush = CreateSolidBrush(RGB(255, 0, 255));
		}
		else if (iPaintFlag == 6)
		{
			hbrush = CreateSolidBrush(RGB(255, 255, 0));
		}
		else if (iPaintFlag == 7)
		{
			hbrush = CreateSolidBrush(RGB(0, 0, 0));
		}
		else if (iPaintFlag == 8)
		{
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
		}
		else
		{
			hbrush = CreateSolidBrush(RGB(128, 128, 128)); //medium grey
		}
		FillRect(hdc, &rc, hbrush);
		DeleteObject(hbrush);
		EndPaint(hwnd,&ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

