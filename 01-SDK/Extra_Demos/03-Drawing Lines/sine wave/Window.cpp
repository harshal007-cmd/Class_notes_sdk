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
	HPEN hPen;
	PAINTSTRUCT ps;
	int x, y, i;
	static INT flag = 0;
	static int cxClient, cyClient;
	RECT rect;
	POINT apt[NUM];
	LOGPEN logpen;
	//code
	switch (iMsg)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_LBUTTONDOWN:
		flag++;
		if (flag > 3)
			flag = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//hPen = (HPEN)GetStockObject(WHITE_PEN);
		
		
		/*
		Rectangle(hdc, cxClient / 8, cyClient / 8,
			7 * cxClient / 8, 7 * cyClient / 8);

		MoveToEx(hdc, 0, 0, NULL);
		LineTo(hdc, cxClient, cyClient);

		MoveToEx(hdc, 0, cyClient, NULL);
		LineTo(hdc, cxClient, 0);

		Ellipse(hdc, cxClient / 8, cyClient / 8,
			7 * cxClient / 8, 7 * cyClient / 8);
		RoundRect(hdc, cxClient / 4, cyClient / 4,
			3 * cxClient / 4, 3 * cyClient / 4,
			cxClient / 4, cyClient / 4);
		*/
			
		if (flag == 0) {
			hPen = CreatePen(PS_DASH, 1, RGB(255, 0, 2));
			SelectObject(hdc, hPen);
			

		}
		else if(flag==1) {
			hPen = CreatePen(PS_DASH, 2, RGB(255, 255, 0));
			SelectObject(hdc, hPen);
			
		}
		else {
			hPen = CreatePen(PS_DASH, 2, RGB(255, 125, 0));
			SelectObject(hdc, hPen);

		}
		MoveToEx(hdc, 0, cyClient / 2, NULL);
		LineTo(hdc, cxClient, cyClient / 2);

		for (i = 0;i < NUM;++i) {
			apt[i].x = i * cxClient / NUM;
			apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / NUM)));
		}

		Polyline(hdc, apt, NUM);

		//EndPaint(hwnd, &ps);

		break;
	

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}

