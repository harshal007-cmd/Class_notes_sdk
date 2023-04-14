//header files
#include<windows.h>
#include<math.h>

#define NUM 1000
#define TWOPI (2*3.14159) 

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(NULL));
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

void DrawBezier(HDC hdc, POINT apt[])
{
	PolyBezier(hdc, apt, 4);
	MoveToEx(hdc, apt[0].x, apt[0].y, NULL);
	LineTo(hdc, apt[1].x, apt[1].y);
	MoveToEx(hdc, apt[2].x, apt[2].y, NULL);
	LineTo(hdc, apt[3].x, apt[3].y);
}

LRESULT CALLBACK WndProg(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//local variable declarations
	HDC hdc;
	PAINTSTRUCT ps;
	int x, y, i;
	static int cxClient, cyClient;
	RECT rect;
	POINT apt[NUM];

	//code
	switch (iMsg)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		apt[0].x = cxClient / 4;
		apt[0].y = cyClient / 2;
		apt[1].x = cxClient / 2;
		apt[1].y = cyClient / 4;
		apt[2].x = cxClient / 2;
		apt[2].y = 3 * cyClient / 4;
		apt[3].x = 3 * cxClient / 4;
		apt[3].y = cyClient / 2;
		return 0;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)
		{
			hdc = GetDC(hwnd);
			SelectObject(hdc, GetStockObject(WHITE_PEN));
			DrawBezier(hdc, apt);
			if (wParam & MK_LBUTTON)
			{
				apt[1].x = LOWORD(lParam);
				apt[1].y = HIWORD(lParam);
			}
			if (wParam & MK_RBUTTON)
			{
				apt[2].x = LOWORD(lParam);
				apt[2].y = HIWORD(lParam);
			}
			SelectObject(hdc, GetStockObject(BLACK_PEN));
			DrawBezier(hdc, apt);
			ReleaseDC(hwnd, hdc);
		}
		return 0;

	case WM_PAINT:
		InvalidateRect(hwnd, NULL, TRUE);
		hdc = BeginPaint(hwnd, &ps);
		DrawBezier(hdc, apt);
		EndPaint(hwnd, &ps);
		return 0;

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

