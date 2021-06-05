//header
#include<windows.h>

//global function declaration
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM)

//Winmain()
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine,int iCmdShow)
{
     //Variable Declaration
     WNDCLASSEX wndclass;
     HWND hwnd;
     MSG msg; //this msg structure is for Hardware Posted Messages , Software messages is directly send by O.S 
              // to WndProc.
     TCHAR szAppName[] = TEXT("MyApp");

     //code
     //initialization of WNDCLASSEX
     wndclass.cbSize         = sizeof(WNDCLASSEX);
     wndclass.style          = CS_HREDRAW | CS_VREDRAW;
     wndclass.cbClsExtra     = 0;
     wndclass.cbWndProc      = 0;
     wndclass.lpfnWndProc    = WndProc;
     wndclass.hInstance      = hInstance;
     wndclass.hIcon          = LoadIcon(NULL,IDI_APPLICATION);
     wndclass.hCursor        = LoadCursor(NULL,IDC_ARROW);
     wndclass.lpszClassName  = szAppName;
     wndclass.lpszMenuName   = NULL;
     wndclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);

     //register above class
     RegisterClassEx(&wndclass);

     //create window
     hwnd = CreateWindow(szAppName,/*Which Class of Window*/
             TEXT("BlankWindow"),/*Unicode complient string, Window Name*/
             WS_OVERLAPPEDWINDOW,/*Which stylel of window*/
             CW_USEDEFAULT,/*X-Coordinate, IN Left Side where the window show.*/
             CW_USEDEFAULT,/*y-Coordinate, In top side where the window show. */
             CW_USEDEFAULT,/*Window Height */
             NULL,/* this parameter is a handle of paraent window of this window.
                     but when we give to NULL it means the desktop is a parent of this window*/
             NULL,/* Menu to Handle */
             hInstance,/* Handle of window */
             NULL); /* for extra information */

             ShowWindow(hwnd, iCmdShow); //hwnd = which window (handle of window)
                                         //iCmdShow = OS returned parameter x and y coordinate of window
                                         //how to show this window.

             UpdateWindow(hwnd);//Used to paint the window on screen using Brush


             //Message Loop Heart of Window
             while(GetMessage(&msg, NULL, 0, 0))
             {
                  TranslateMessage(&msg);//classification of messages H.w and s.w. , Hardware message is posted to WndProc and software message passed to O.S. and then O.S send it directly to WndProc. 
                  DispatchMessage(&msg);//it calls wndProc
             }

             return((int)msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
     //code
     switch(iMsg)
     {
         case WM_DESTROY:
              PostQuitMessage(0);//parameter of postquitmessage is a wparam of quit message.
                                 //postquit message create internally structure of wm_quit message.
         break;
     }
     return(DefWindowProc(hwnd,iMsg,wParam,lParam));//DefWindowProc calls goes in WndProc of O.S. Main Window.
}


