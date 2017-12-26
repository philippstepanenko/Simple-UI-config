// Simple UI+config for batch files
// Program for those who like to click on the buttons.
// ---------------------------------------------------

#include <windows.h>
#include <string>
#include <fstream>
#define N 10 // Maximum number of files (.bat)
#define M 2 // Maximum number of file parameters
#define W 300 // Width
#define H 200 // Height
#define DELIMITER "#"

using namespace std;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	string temp[M]; // temp
	string bat[N]; // name (batch files)
	string cap[N]; // caption (buttons)
	string mes[N]; // messages
	int pos=0;
	int i=0;
	int j=0;
	int m=0;
    string s;
    ifstream file("config.conf");
	i=0;
    while(getline(file, s) && i<N){
    	j=0;
        pos=s.find(DELIMITER);
        while (pos != std::string::npos&&j<M){
			temp[j]=s.substr(0,pos);
			j++;
			s=s.substr(pos+1,s.length()-pos-1);
			pos=s.find(DELIMITER);
		}
		temp[j]=s;
		m=j;
		for (j=0; j<=m; j++){
			if (j==0) bat[i]=temp[j];
			if(j==1) cap[i]=temp[j];
			if(j==2) mes[i]=temp[j];
		}
		i++;
    }

    file.close();
	//for (j=0;j<i;j++){
		//cout << bat[j] << " ";
		//cout << cap[j] << endl;
	//}	
	
HWND hwndButton[i];

	switch(Message) {
		case WM_CREATE:
	   		for(j=0; j<i;j++){
	   			int w = cap[j].length()*10;
	   			int cx = W/2 - w/2;
	   			hwndButton[j] = CreateWindow(TEXT("button"),TEXT(cap[j].c_str()), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON ,
				   cx, 25+j*25, w, 25, hwnd, (HMENU) j, NULL, NULL);
	   		}
		break;	
		
case WM_COMMAND:

				WinExec(("bat\\"+bat[LOWORD(wParam)]).c_str(), SW_HIDE); 
				MessageBox(0, mes[LOWORD(wParam)].c_str(), "message",MB_OK);
		
		
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
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Simple UI",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		W, /* width */
		H, /* height */
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
