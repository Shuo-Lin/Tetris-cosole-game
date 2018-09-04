#include<iostream>
using namespace std;
#include<Windows.h>
#pragma comment( lib, "winmm.lib" )

class CMyConsole
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO cursor;
public:
	CMyConsole();
	~CMyConsole();
	void SetTitle(const char *);//���ô����� 
	void SetSize(short, short);//���ô��ڴ�С
	void SetCursor(short, short);//���ù��λ��
	void HideCursor();//���ع��
	void ShowCursor(DWORD dwSize);//��ʾ��꣨����Ȱٷֱȣ�
	void DrawBox(SMALL_RECT rc, bool bDouble);
	HANDLE GetHandle();
};

/*--------���캯��--------*/
CMyConsole::CMyConsole()
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
}
CMyConsole::~CMyConsole()
{
	CloseHandle(hOut);
}

/*-------��������--------*/
void CMyConsole::SetTitle(const char* t)
{
	SetConsoleTitleA(t);
}
void CMyConsole::SetSize(short x, short y)//���ô��ںͻ�������С��������>=���ڣ�ͬ����û�й�����
{
	COORD pos = { x, y };
	SMALL_RECT rc = { 0, 0, x - 1, y - 1 };

	SetConsoleWindowInfo(hOut, true, &rc);

	SetConsoleScreenBufferSize(hOut, pos);
}


/*-------�������-------*/
void CMyConsole::SetCursor(short x, short y)//���ù��λ��
{
	//	COORD pos = { x, y };

	SetConsoleCursorPosition(hOut, COORD{ x, y });
}
void  CMyConsole::HideCursor()//���ع��
{
	cursor.dwSize = 1;
	cursor.bVisible = false;
	SetConsoleCursorInfo(hOut, &cursor);
}
void CMyConsole::ShowCursor(DWORD dwSize = 20)//��ʾ���
{
	cursor.dwSize = dwSize;
	cursor.bVisible = true;
	SetConsoleCursorInfo(hOut, &cursor);
}

HANDLE CMyConsole::GetHandle()
{
	return hOut;
}

/*--������Ƶ--*/
void audioplay(const char * file)
{
	PlaySoundA(file, 0, 0);
}