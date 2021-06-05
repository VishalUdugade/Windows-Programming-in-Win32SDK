#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyApp");

	//code
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style  = CS_HREDRAW | CS_VREDRAW;
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
	RegisterClassEx(&wndclass)

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
	       	while(GetMessage(&msg, NULL, 0, 0))
	       	{
	       	    TranslateMessage(&msg);
	       	    DispatchMessage(&msg);
	       	}

	       	return((int)msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; /*Handle to device context. (for working of graphics card the device driver of graphics card gives a structure to  programmer for controlling the graphics card . ) the handle of that graphics card is HDC.*/

    PAINTSTRUCT ps; //it is a structure it contains information for an application. This information can be used to paint the client area of a window owend by that application.

    RECT rc; //It is structure contains co-ordinates of its upper - left and lower-right corners. int x, int y, int width, int height.

    //code
    switch(iMsg)
    {
       case WM_PAINT:
             GetClientRect(hwnd,&rc); //it gives the co-ordinates of client area of window using 1st parameter which is the handle of window. and fill that co-ordinates in rc object of PAINTSTRUCT .	

             hdc = BeginPaint(hwnd,&ps); //it is specialized to draw an Client area of window.

             SetBkColor(hdc, RGB(0 , 0, 0)); //set Background color of client rectangle . by default windows background color is whit.
        break;

        case WM_DESTROY:
             PostQuitMessage(0);
            break;
    }
    return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}