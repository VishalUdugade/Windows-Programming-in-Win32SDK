//header
#include<windows.h>
#define MYTIMER 203
static int iPaintFlag = 0;

//global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
     HDC hdc;
     PAINTSTRUCT ps;
     RECT rc;
     static HBRUSH brush[6];
     
	//code
	switch (iMsg)
	{
	    case WM_CREATE:
              brush[0] = CreateSolidBrush(RGB(0,0,255));
              brush[1] = CreateSolidBrush(RGB(0,255,255));
              brush[2] = CreateSolidBrush(RGB(255,0,0));
              brush[3] = CreateSolidBrush(RGB(0,255,0));
              brush[4] = CreateSolidBrush(RGB(456,12,255));
              brush[5] = CreateSolidBrush(RGB(74,98,94));

             SetTimer(hwnd, MYTIMER, 1000, NULL);
	         break;
        case WM_TIMER:
             KillTimer(hwnd,MYTIMER);
             if(iPaintFlag < 5)
             {
             	iPaintFlag = iPaintFlag + 1;
             }
             else
             {
             	iPaintFlag = 0;
             }
             InvalidateRect(hwnd,NULL,TRUE);
             SetTimer(hwnd,MYTIMER, 1000, NULL);
             break;
        case WM_PAINT:
             GetClientRect(hwnd,&rc);
             hdc = BeginPaint(hwnd,&ps);
             FillRect(hdc, &rc, brush[iPaintFlag]);
             EndPaint(hwnd,&ps);
             break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
