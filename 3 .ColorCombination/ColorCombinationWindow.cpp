#include<windows.h>
#include"MyWindow.h"
#define MYTIMER 102

int iPaintFlag = 0;
 
//global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);
DWORD WINAPI ThreadProcThree(LPVOID);
DWORD WINAPI ThreadProcFour(LPVOID);
DWORD WINAPI ThreadProcPlaySound(LPVOID);


HDC hdc;
RECT rc;

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
	static HANDLE hThreadOne = NULL;
	static HANDLE hThreadTwo = NULL;
	static HANDLE hThreadThree = NULL;
	static HANDLE hThreadFour = NULL;

	static HANDLE hThreadPlaySound = NULL;

	PAINTSTRUCT ps;
	//code
	switch(iMsg)
	{
		case WM_CREATE:
			hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID)hwnd, 0, NULL);

			hThreadTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);

			hThreadThree = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcThree, (LPVOID)hwnd, 0, NULL);

			hThreadFour = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcFour, (LPVOID)hwnd, 0, NULL);

			hThreadPlaySound = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcPlaySound, (LPVOID)hwnd, 0, NULL);

			SetTimer(hwnd, MYTIMER, 1000, NULL);
			break;
		case WM_TIMER:
			KillTimer(hwnd, MYTIMER);
			if(iPaintFlag < 4)
			{
				iPaintFlag++;
			}
			else
			{
				iPaintFlag = 0;
			}
			InvalidateRect(hwnd, NULL, TRUE);
			SetTimer(hwnd, MYTIMER, 1000, NULL);
			break;
		case WM_PAINT:
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			break;
		case WM_DESTROY:
			if (hThreadOne == 0)
			{
				CloseHandle(hThreadOne);
				hThreadOne = NULL;
			}
			if(hThreadTwo == 0)
			{
				CloseHandle(hThreadTwo);
				hThreadTwo = NULL;
			}
			if (hThreadThree == 0)
			{
				CloseHandle(hThreadThree);
				hThreadThree = NULL;
			}
			if (hThreadFour == 0)
			{
				CloseHandle(hThreadFour);
				hThreadFour = NULL;
			}
			PostQuitMessage(0);
			break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

DWORD WINAPI ThreadProcOne(LPVOID lParam)
{
	static HBRUSH brush[5];
	HDC ohdc;
	RECT rco;

	brush[0] = CreateSolidBrush(RGB(255, 0, 0));
	brush[1] = CreateSolidBrush(RGB(0, 255, 0));
	brush[2] = CreateSolidBrush(RGB(0, 0, 255));
	brush[3] = CreateSolidBrush(RGB(255, 255, 0));
	brush[4] = CreateSolidBrush(RGB(0, 255, 255));
	
	while (iPaintFlag != -1)
	{ 
		//Sleep(1000);
		if (iPaintFlag == 0)
		{
			SelectObject(hdc, brush[0]);
		}
		else if (iPaintFlag == 1)
		{
			SelectObject(hdc, brush[1]);
		}
		else if (iPaintFlag == 2)
		{
			SelectObject(hdc, brush[2]);
		}
		else if (iPaintFlag == 3)
		{
			SelectObject(hdc, brush[3]);
		}
		else if (iPaintFlag == 4)
		{
			SelectObject(hdc, brush[4]);
		}

		ohdc = hdc;
		rco.bottom = rc.bottom/2;
		rco.left = rc.right / 2;
		rco.right = rc.right;
		rco.top = rc.top;
		FillRect(ohdc, &rco, brush[iPaintFlag]);
	}
	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID lParam)
{
	static HBRUSH brush[5];
	HDC thdc;
	RECT rct;

	brush[0] = CreateSolidBrush(RGB(192, 192, 192));
	brush[1] = CreateSolidBrush(RGB(128, 128, 128));
	brush[2] = CreateSolidBrush(RGB(128, 0, 0));
	brush[3] =  CreateSolidBrush(RGB(128, 128, 0));
	brush[4] =  CreateSolidBrush(RGB(0, 128, 0));


	while (iPaintFlag != -1)
	{
		//Sleep(1000);
		if (iPaintFlag == 0)
		{
			SelectObject(hdc, brush[0]);
		}
		else if (iPaintFlag == 1)
		{
			SelectObject(hdc, brush[1]);
		}
		else if (iPaintFlag == 2)
		{
			SelectObject(hdc, brush[2]);
		}
		else if (iPaintFlag == 3)
		{
			SelectObject(hdc, brush[3]);
		}
		else if (iPaintFlag == 4)
		{
			SelectObject(hdc, brush[4]);
		}

		rct.bottom = rc.bottom/2;
		rct.left = rc.left;
		rct.right = rc.right/2;
		rct.top = rc.top;
		thdc = hdc;
		FillRect(thdc, &rct, brush[iPaintFlag]);
	}
	return 0;
}

DWORD WINAPI ThreadProcThree(LPVOID lParam)
{
	static HBRUSH brush[5];
	HDC trhdc;
	RECT rctr;

	brush[0] = CreateSolidBrush(RGB(255, 0, 0));
	brush[1] = CreateSolidBrush(RGB(255, 255, 0));
	brush[2] =  CreateSolidBrush(RGB(0, 255, 0));
	brush[3] = CreateSolidBrush(RGB(128, 128, 128));
	brush[4] =  CreateSolidBrush(RGB(0, 255, 255));


	while (iPaintFlag != -1)
	{
		//Sleep(1000);
		if (iPaintFlag == 0)
		{
			SelectObject(hdc, brush[0]);
		}
		else if (iPaintFlag == 1)
		{
			SelectObject(hdc, brush[1]);
		}
		else if (iPaintFlag == 2)
		{
			SelectObject(hdc, brush[2]);
		}
		else if (iPaintFlag == 3)
		{
			SelectObject(hdc, brush[3]);
		}
		else if (iPaintFlag == 4)
		{
			SelectObject(hdc, brush[4]);
		}

		rctr.bottom = rc.bottom;
		rctr.left = rc.right / 2;
		rctr.right = rc.right;
		rctr.top = rc.bottom/2;
		trhdc = hdc;
		FillRect(trhdc, &rctr, brush[iPaintFlag]);
	}
	return 0;
}

DWORD WINAPI ThreadProcFour(LPVOID lParam)
{
	static HBRUSH brush[5];
	HDC fhdc;
	RECT rcf;

	brush[0] = CreateSolidBrush(RGB(255, 0, 255));
	brush[1] =  CreateSolidBrush(RGB(0, 255, 255));
	brush[2] = CreateSolidBrush(RGB(0, 0, 128));
	brush[3] = CreateSolidBrush(RGB(0, 0, 255));
	brush[4] =   CreateSolidBrush(RGB(0, 255, 0));


	while (iPaintFlag != -1)
	{
		//Sleep(1000);
		if (iPaintFlag == 0)
		{
			SelectObject(hdc, brush[0]);
		}
		else if (iPaintFlag == 1)
		{
			SelectObject(hdc, brush[1]);
		}
		else if (iPaintFlag == 2)
		{
			SelectObject(hdc, brush[2]);
		}
		else if (iPaintFlag == 3)
		{
			SelectObject(hdc, brush[3]);
		}
		else if (iPaintFlag == 4)
		{
			SelectObject(hdc, brush[4]);
		}

		rcf.bottom = rc.bottom;
		rcf.left = rc.left;
		rcf.right = rc.right / 2;
		rcf.top = rc.bottom /2;
		fhdc = hdc;
		FillRect(fhdc, &rcf, brush[iPaintFlag]);
	}
	return 0;
}

DWORD WINAPI ThreadProcPlaySound(LPVOID lParam)
{
	BOOL Check;
	Check = PlaySound(MAKEINTRESOURCE(SOUNDNAME), NULL, SND_RESOURCE | SND_ASYNC | SND_NODEFAULT);
	if (Check == FALSE)
	{
		MessageBox((HWND)lParam, TEXT("PlaySound Fails.."), TEXT("Message"), MB_OK);
	}

	//PlayResource("SOUNDNAME",(HWND)lParam);
	return 0;
}


