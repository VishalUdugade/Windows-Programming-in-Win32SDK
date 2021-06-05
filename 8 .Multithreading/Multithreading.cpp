//header
#include<windows.h>

//global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

//int MyStrLen(TCHAR*);

//Winmain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR
	lpszCmdLine, int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//code
	//initialization of WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register above class
	RegisterClassEx(&wndclass);
	
	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("My Application"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam , LPARAM lParam)
{
	static HANDLE hThreadOne = NULL;
	static HANDLE hThreadTwo = NULL;

	switch(iMsg)
	{
	     case WM_CREATE:
	            hThreadOne = CreateThread(NULL,0,((LPTHREAD_START_ROUTINE)ThreadProcOne), (LPVOID)hwnd, 0, NULL);

                hThreadTwo = CreateThread(NULL,0,((LPTHREAD_START_ROUTINE)ThreadProcTwo), (LPVOID)hwnd, 0, NULL);
	     break;

	     case WM_LBUTTONDOWN:
	           MessageBox(hwnd,TEXT("This is a Multithread Application"),TEXT("Message"),MB_OK);
	     break;

	     case WM_DESTROY:

	          if(hThreadOne)
	          {
                   CloseHandle(hThreadOne);
                   hThreadOne = NULL;
	          }
	          if(hThreadTwo)
	          {
                   CloseHandle(hThreadTwo);
                   hThreadTwo = NULL;
	          }

	          PostQuitMessage(0);
	     break;
	}

	return (DefWindowProc(hwnd,iMsg,wParam,lParam));
}


DWORD WINAPI ThreadProcOne(LPVOID Param)
{
	//local Variables
	HDC hdc;
	int i;
	TCHAR str[255];

	
	//code
	hdc = GetDC((HWND)Param);
	SetTextColor(hdc, RGB(0, 255, 255));

	for (i = 0; i < 32768; i++)
	{
		wsprintf(str, TEXT("Therad1 : Increasing order : %d"), i);
		TextOut(hdc, 5, 5, str, ARRAYSIZE(str));
		Sleep(100);
	}
	ReleaseDC((HWND)Param, hdc);
	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID Param)
{
	HDC hdc;
	int i;
	TCHAR str[255];

	hdc = GetDC((HWND)Param);
	SetTextColor(hdc,RGB(0,255,255));

	for(i = 32768; i >= 0; i--)
	{
		wsprintf(str, TEXT("Therad2 : Decreasing order : %ul"), i);
		TextOut(hdc, 5, 25, str, ARRAYSIZE(str));
		Sleep(100);
	}

	ReleaseDC((HWND)Param, hdc);
	return 0;
}

