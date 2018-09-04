using namespace std;
#include <Windows.h>
#include"tetris.h"


int main(int argc, char** argv)
{


	PlaySoundA("Two Year Montage - Theodore Shapiro.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	tetris otetris;
	otetris.Run();

	/*
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	INPUT_RECORD inputRecored;
	DWORD reads;
	CONSOLE_SCREEN_BUFFER_INFO screenBuffer;


	
	double start = clock();
	while (timer(start,5))
	{
		ReadConsoleInput(hIn, &inputRecored, 1, &reads);

		if (inputRecored.EventType == KEY_EVENT)
		{
			if (inputRecored.Event.KeyEvent.bKeyDown)
			switch (inputRecored.Event.KeyEvent.wVirtualKeyCode)
			{
			case VK_LEFT:cout << "LEFT key pressed" << endl; break;
			case VK_UP:cout << "UP key pressed" << endl; break;
			case VK_RIGHT:cout << "RIGHT key pressed" << endl; break;
			case VK_DOWN:cout << "DOWN key pressed" << endl; break;
			case VK_ESCAPE: goto here;
			default:cout << "other keys\n";
			}
		}

		if (inputRecored.EventType == MOUSE_EVENT)
		{
			switch (inputRecored.Event.MouseEvent.dwButtonState)
			{
			case FROM_LEFT_1ST_BUTTON_PRESSED:
				if (inputRecored.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
					cout << "双击了鼠标左键\n";
				else
					cout << "单击了鼠标左键\n";
				break;
			case RIGHTMOST_BUTTON_PRESSED:
				if (inputRecored.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
					cout << "双击了鼠标右键\n";
				else
					cout << "单击了鼠标右键\n";
				break;
			case FROM_LEFT_2ND_BUTTON_PRESSED:
				cout << "点击了左起第二键\n";
				break;
			case FROM_LEFT_3RD_BUTTON_PRESSED:
				cout << "点击了左起第三键\n";
				break;
			case FROM_LEFT_4TH_BUTTON_PRESSED:
				cout << "点击了左起第四键\n";
				break;
			default:
				cout << "鼠标上还有其他键？？\n";
				break;
			}
			cout << "点击的坐标为:(" << inputRecored.Event.MouseEvent.dwMousePosition.X << "," << inputRecored.Event.MouseEvent.dwMousePosition.Y << ").\n";
		}
	}
	here:cout << "Loop escaped\n\n";*/

	return 0;
}