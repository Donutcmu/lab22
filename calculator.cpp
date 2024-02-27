#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
char firstinputsave[100];
char secondinputsave[100];
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	HWND textfield,plusbutton,minusbutton,multiplybutton,dividebutton;
	HWND firstinput,secondinput;
	switch(Message) {
		case WM_ERASEBKGND: {
		HDC hdc = (HDC)wParam;
		RECT rect;
		GetClientRect(hwnd, &rect);
		HBRUSH hBrush = CreateSolidBrush(RGB(210, 0, 0)); 
		FillRect(hdc, &rect, hBrush);
		DeleteObject(hBrush);
		return (LRESULT)TRUE; 
	}
		case WM_CREATE:
			textfield = CreateWindow("STATIC",
									"Please input two numbers",
									WS_VISIBLE | WS_CHILD | WS_BORDER,
									20,20,180,20,
									hwnd,NULL,NULL,NULL);
			plusbutton = CreateWindow("BUTTON",
										"+",
										WS_VISIBLE | WS_CHILD | WS_BORDER,
										40,120,20,20,
										hwnd,(HMENU) 1,NULL,NULL);
			minusbutton = CreateWindow("BUTTON",
										"-",
										WS_VISIBLE | WS_CHILD | WS_BORDER,
										70,120,20,20,
										hwnd,(HMENU) 2,NULL,NULL);
			multiplybutton = CreateWindow("BUTTON",
										"*",
										WS_VISIBLE | WS_CHILD | WS_BORDER,
										100,120,20,20,
										hwnd,(HMENU) 3,NULL,NULL);
			dividebutton = CreateWindow("BUTTON",
										"/",
										WS_VISIBLE | WS_CHILD | WS_BORDER,
										130,120,20,20,
										hwnd,(HMENU) 4,NULL,NULL);
			firstinput = CreateWindow("EDIT",
										"",
										WS_VISIBLE | WS_CHILD | WS_BORDER,
										20,50,150,20,
										hwnd,NULL,NULL,NULL);
			secondinput = CreateWindow("EDIT",
										"",
										WS_VISIBLE | WS_CHILD | WS_BORDER,
										20,80,150,20,
										hwnd,NULL,NULL,NULL);
			break;
		/* Upon destruction, tell the main thread to stop */
		case WM_COMMAND:
				
				GetWindowText(firstinput, &firstinputsave[100], 100);
            	GetWindowText(secondinput, &secondinputsave[100], 100);
				double a,b;
				 a = atof(firstinputsave);
				 b = atof(secondinputsave);
				char result[100];
				double plus,minus,time,divide;
			switch (LOWORD(wParam))
			{
				
			case 1:
				plus = a + b;
				sprintf(result,"%.6f",plus);
				::MessageBeep(MB_ICONERROR);
				::MessageBox(hwnd, result ,"Result",MB_OK);
				break;
			case 2:
				minus = a-b;
				sprintf(result,"%.6f",minus);
				::MessageBeep(MB_ICONERROR);
				::MessageBox(hwnd, result ,"Result",MB_OK);
				break;
			case 3:
				time = a*b;
				sprintf(result,"%.6f",time);
				::MessageBeep(MB_ICONERROR);
				::MessageBox(hwnd,result,"Result",MB_OK);
				break;
			case 4:
				divide = a/b;
				sprintf(result,"%.6f",divide);
				::MessageBeep(MB_ICONERROR);
				::MessageBox(hwnd,result,"Result",MB_OK);
				break;
			default:
				break;
			}
			break;

		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
