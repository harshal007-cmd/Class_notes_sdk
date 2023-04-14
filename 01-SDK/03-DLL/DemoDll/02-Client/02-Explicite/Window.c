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
	HMODULE hDll=NULL;
	typedef int (*MakeCubeFunctionPointer)(int);
	typedef int (*MakeSquareFunctionPointer)(int);

	MakeCubeFunctionPointer pfnMakeCube = NULL;  //pfn=pointer to function
	MakeSquareFunctionPointer pfnMakeSquare = NULL;  //pfn=pointer to function

	INT iNum = 15;
	INT iCube,iSquare;
	TCHAR str[255];
	//code
	switch (iMsg)
	{
	case WM_CREATE:
		// Source1 dll code
		hDll = LoadLibrary(TEXT("MyMathOne.dll"));
		if (hDll == NULL) {
			MessageBox(hwnd, TEXT("LoadLibrary() function is failed.."), TEXT("Error.!!"), MB_OK);
			DestroyWindow(hwnd);
		}
		pfnMakeSquare = (MakeSquareFunctionPointer)GetProcAddress(hDll, "MakeSquare");
		if (pfnMakeSquare == NULL) {
			MessageBox(hwnd, TEXT("GetProcAddress() function is failed.."), TEXT("Error.!!"), MB_OK);
			FreeLibrary(hDll);
			DestroyWindow(hwnd);
		}
		iSquare = pfnMakeSquare(iNum);
		wsprintf(str, TEXT("Square of %d is %d"), iNum, iSquare);
		MessageBox(hwnd, str, TEXT("Square.."), MB_OK);
		FreeLibrary(hDll);
		hDll = NULL;
		//DestroyWindow(hwnd);

		hDll = LoadLibrary(TEXT("MyMathTwo.dll"));
		if (hDll == NULL) {
			MessageBox(hwnd, TEXT("LoadLibrary() function is failed.."), TEXT("Error.!!"), MB_OK);
			DestroyWindow(hwnd);
		}
		pfnMakeCube = (MakeSquareFunctionPointer)GetProcAddress(hDll, "MakeCube");
		if (pfnMakeCube == NULL) {
			MessageBox(hwnd, TEXT("GetProcAddress() function is failed.."), TEXT("Error.!!"), MB_OK);
			FreeLibrary(hDll);
			DestroyWindow(hwnd);
		}
		iSquare = pfnMakeCube(iNum);
		wsprintf(str, TEXT("Cube of %d is %d"), iNum, iSquare);
		MessageBox(hwnd, str, TEXT("Cube.."), MB_OK);
		FreeLibrary(hDll);
		hDll = NULL;
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}
