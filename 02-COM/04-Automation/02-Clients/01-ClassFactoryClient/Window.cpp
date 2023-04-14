//header files
#include<windows.h>
#include"AutomationServerWithRegFile.h"
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
	IMyMath* pIMyMath = NULL;
	HRESULT hr;
	int num1, num2, sum,sub;
	TCHAR str[255];
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoInitialize(NULL);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("COInitialize failed"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		hr = CoCreateInstance(CLSID_MyMath, NULL, CLSCTX_INPROC_SERVER, IID_IMyMath, (void**)&pIMyMath);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("CoCreateInstance failed to get IMyMath Inteface"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		num1 = 175;
		num2 = 125;
		pIMyMath->SumOfTwoIntergers(num1, num2, &sum);
		wsprintf(str, TEXT("Sum of %d and %d is :%d"), num1, num2, sum);
		MessageBox(hwnd, str, TEXT("Sum"), MB_OK);
		pIMyMath->SubtractionOfTwoIntergers(num1, num2, &sub);
		wsprintf(str, TEXT("Subtraction of %d and %d is :%d"), num1, num2, sub);
		MessageBox(hwnd, str, TEXT("Sub"), MB_OK);
		pIMyMath->Release();
		pIMyMath = NULL;
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		CoUninitialize();
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}











