//header files
#include<windows.h>

	 

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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szAppName;  //MUST do it
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	
	
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
	TCHAR str[255];
	int num1,num2,num3;
	
	HDC hdc ;
	PAINTSTRUCT ps ;
	RECT rect ;

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		//PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		num1=25;
		num2=25;
		num3=num1+num2;
		wsprintf(str,TEXT("Sum of %d and %d is = %d"),num1,num2,num3);
		MessageBox(hwnd,str,TEXT("Message"),MB_OK | MB_YESNO);
		break;
/*	case WM_PAINT:
		hdc = BeginPaint (hwnd, &ps) ;
 
		GetClientRect (hwnd, &rect) ;
 
		DrawText (hdc, TEXT ("Hello, Windows 10!"), -1, &rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
		EndPaint (hwnd, &ps) ;
		break; */
	case WM_KEYDOWN:
		wsprintf(str, TEXT("WM_KEYDOWN message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;
	case WM_LBUTTONDOWN:
		wsprintf(str, TEXT("WM_LBUTTONDOWN message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;
	case WM_RBUTTONDOWN:
		wsprintf(str, TEXT("WM_RBUTTONDOWN message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		break;
	case WM_DESTROY:
		wsprintf(str, TEXT("WM_DESTROY message is received"));
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));

}


