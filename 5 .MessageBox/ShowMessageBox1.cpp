#include<windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HWND hwnd,HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

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

LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam, LPARAM lParam)
{
	//code
	/*hwnd        = which window the messagebox shown.

	/*2nd parameter = which message show.
	      TEXT("____")*/

    /*3rd parameter = Caption.
           TEXT("_____") */

    /*4th parameter = Which Button is shown.
           MB_OK.*/

   switch(iMsg)
   {
       case WM_CREATE:
           MessageBox(hwnd,TEXT("WM_Create is Received"),TEXT("Message"),MB_OK);
       break;

       case WM_KEYDOWN:
            MessageBox(hwnd,TEXT("WM_KEYDOWN is Received"),TEXT("Message"),MB_OK);
       break;

       case WM_LBUTTONDOWN:
            MessageBox(hwnd,TEXT("WM_LBUTTONDOWN is Received"),TEXT("Message"),MB_OK);
       break;

       case WM_RBUTTONDOWN:
            MessageBox(hwnd,TEXT("WM_RBUTTONDOWN is Received"),TEXT("Message"),MB_OK);
       break;

       case WM_DESTORY:
            PostQuitMessage(0);
       break;
   }

   return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}

