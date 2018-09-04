#include<iostream>
#include<fstream>
#include<Windows.h>
#include <stdlib.h>
#include<conio.h>
#include<time.h>
#include"CMyConsole.h"
#include"mytimer.h"
#include<cmath>
using namespace std;
#define width 10
#define height 20
#define gpl 10//goals per line


enum Direction{UP,RIGHT,DOWN,LEFT};
enum Shape{BAR,SQUARE,RIGHTHAND,LEFTHAND,STRANGE,ZRIGHT,ZLEFT,DISCREAT};
struct point{ int r;int c; };//r�У�c��

/*---------����---------*/
class block
{
	Shape shape;// �������״ ��������
	point key;//�������
	point all[4];//�����ĸ����λ��
	Direction direction;
	bool state;//�Ƿ����½�������
	void complete();
public:
	block();
	block(Shape);
	void setkey( point);
	point* Getall();
	bool bfalling();
	void stopfalling();
	void changedirection();
	void changeback();
};

/*--------�����----------*/
class board
{
	bool a[height][width];//��Ϸ�����
	int goals;//�÷�
	int bg;//best goals
	int level;
	double SPEEDDOWN;
	ofstream fout;
	ifstream fin;
	block* pblock;
	block* pblock2;
	block next;
	point* all;
	HANDLE hOut;
	HANDLE hIn;
	INPUT_RECORD inputRecord;
	DWORD dw;
	bool gameover();
public:
	board();
	~board();
	void cleanline(int);//����һ��
	bool dropcheck();
	bool opcheck();//�Լ��̲����ļ���Ƿ��ܲ���
	void finalcheck();//�Ƿ������÷֣��Ƿ�gameover
	void print();//������غ�check����������ӡ�����͵÷�
	void printblock();
	void newblock();//����һ���µķ���
	void load();//�ѷ���load���������
	void deload();
	void drop();
	void keyboardoperate();
	void singleRun();
	CMyConsole myconsole;
};

/*---------tetris----------*/
class tetris
{
	board oboard;
public:
    bool Run();

};

/*------tetris ��----------------*/
bool tetris::Run()
{
	oboard.myconsole.SetTitle("Tetris by Snoleaf");
	oboard.myconsole.SetSize(2 * width+4 , height+12);
	oboard.myconsole.HideCursor();

    while (1)
	{
		oboard.singleRun();
	}

}

/*----------block ���ʵ��---------------*/
block::block()
{
	direction = DOWN;
	srand((unsigned int)time(0));
	shape = Shape(rand() % 7);//����ķ�������
	key.r = 0, key.c = 4;
	complete();
	state = true;
}
block::block(Shape s)
{
	direction = DOWN;
	shape = s;
	key.r = 0, key.c = 4;
	complete();
	state = true;
}

bool block::bfalling()
{
	return state;
}
void block::stopfalling()
{
	state = false;
}

point* block::Getall()
{
	return all;
}
void block::setkey(point nk)
{
	key = nk;
	complete();
}
void block::complete()
{
	all[0] = key;
	switch (shape)
	{
	case BAR:
		switch (direction)
		{
		case UP:
		case DOWN:
			all[1] = { key.r, key.c - 1 };
			all[2] = { key.r, key.c + 1 };
			all[3] = { key.r, key.c + 2 };
			break;
		case RIGHT:
		case LEFT:
			all[1] = { key.r - 1, key.c };
			all[2] = { key.r + 1, key.c };
			all[3] = { key.r + 2, key.c };
			break;
		}
		break;
	case SQUARE:
		all[1] = { key.r, key.c + 1 };
		all[2] = { key.r + 1, key.c };
		all[3] = { key.r + 1, key.c + 1 };
		break;
	case RIGHTHAND:
		switch (direction)
		{
		case UP:
			all[1] = { key.r - 1, key.c };
			all[2] = { key.r, key.c - 1 };
			all[3] = { key.r, key.c - 2 };
			break;
		case RIGHT:
			all[1] = { key.r, key.c + 1 };
			all[2] = { key.r - 1, key.c };
			all[3] = { key.r - 2, key.c };
			break;
		case DOWN:
			all[1] = { key.r + 1, key.c };
			all[2] = { key.r, key.c + 1 };
			all[3] = { key.r, key.c + 2 };
			break;
		case LEFT:
			all[1] = { key.r, key.c - 1 };
			all[2] = { key.r + 1, key.c };
			all[3] = { key.r + 2, key.c };
			break;
		}

		break;
	case LEFTHAND:
		switch (direction)
		{
		case UP:
			all[1] = { key.r - 1, key.c };
			all[2] = { key.r, key.c + 1 };
			all[3] = { key.r, key.c + 2 };
			break;
		case RIGHT:
			all[1] = { key.r, key.c + 1 };
			all[2] = { key.r + 1, key.c };
			all[3] = { key.r + 2, key.c };
			break;
		case DOWN:
			all[1] = { key.r + 1, key.c };
			all[2] = { key.r, key.c - 1 };
			all[3] = { key.r, key.c - 2 };
			break;
		case LEFT:
			all[1] = { key.r, key.c - 1 };
			all[2] = { key.r - 1, key.c };
			all[3] = { key.r - 2, key.c };
			break;
		}

		break;
	case STRANGE:
		switch (direction)
		{
		case UP:
			all[1] = { key.r - 1, key.c };
			all[2] = { key.r, key.c + 1 };
			all[3] = { key.r, key.c - 1 };
			break;
		case RIGHT:
			all[1] = { key.r, key.c + 1 };
			all[2] = { key.r + 1, key.c };
			all[3] = { key.r - 1, key.c };
			break;
		case DOWN:
			all[1] = { key.r, key.c - 1 };
			all[2] = { key.r, key.c + 1 };
			all[3] = { key.r + 1, key.c };
			break;
		case LEFT:
			all[1] = { key.r, key.c - 1 };
			all[2] = { key.r + 1, key.c };
			all[3] = { key.r - 1, key.c };
			break;
		}

		break;
	case ZRIGHT:
		switch (direction)
		{
		case UP:
		case DOWN:
			all[1] = { key.r + 1, key.c };
			all[2] = { key.r + 1, key.c + 1 };
			all[3] = { key.r + 2, key.c + 1 };
			break;
		case RIGHT:
		case LEFT:
			all[1] = { key.r, key.c - 1 };
			all[2] = { key.r + 1, key.c - 1 };
			all[3] = { key.r + 1, key.c - 2 };
			break;
		}

		break;
	case ZLEFT:
		switch (direction)
		{
		case UP:
		case DOWN:
			all[1] = { key.r + 1, key.c };
			all[2] = { key.r + 1, key.c - 1 };
			all[3] = { key.r + 2, key.c - 1 };
			break;
		case RIGHT:
		case LEFT:
			all[1] = { key.r, key.c + 1 };
			all[2] = { key.r + 1, key.c + 1 };
			all[3] = { key.r + 1, key.c + 2 };
			break;
		}

		break;
	case DISCREAT:
		all[1] = { key.r, key.c +2 };
		all[2] = { key.r + 1, key.c+1  };
		all[3] = { key.r + 2, key.c + 1 };

	}
}
void block::changedirection()
{
	direction = Direction((direction+1)%4);
	complete();
}
void block::changeback()
{
	direction = Direction((direction + 4) % 5);
	complete();
}
/*----------board ���ʵ��---------------*/
board::board()
{
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < height; i++)
   	for (int j = 0; j < width; j++)
	   	a[i][j] = false;
	goals = 0;
	level = 1;
	SPEEDDOWN = 1;
	pblock2 = new block;
	fin.open("GoalsRecord.txt");
	fout.open("GoalsRecord.txt",ios::app);
	if (fin.eof())
		bg = 0;
	else
		fin >> bg;
}
board::~board()
{
	fin.close();
	fout.close();
	delete pblock;
	delete pblock2;
}

void board::cleanline(int row)
{
	for (int i = row; i > 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			a[i][j] = a[i - 1][j];
		}
	}
}
bool board::opcheck()//�ж϶Է���������next�Ƿ�Ϸ�
{
	point *nextall = &next.Getall()[0];
    for (int i = 0; i < 4; i++)
	{
		if (nextall[i].r >= height || nextall[i].c >= width || nextall[i].c < 0)//�߽���
			return false;
		if (a[nextall[i].r][nextall[i].c])//��ײ���
			return false;
	}
	return true;
}
void board::finalcheck()
{
	int counter_fullline = 0;
	for (int i = 0; i < height; i++)//����Ƿ������÷�
	{
		int counter=0;
		for (int j = 0; j < width; j++)
		{
			if (a[i][j])
				counter++;
		}
		if (counter == width)
		{
			counter_fullline++;
			printf("\a");
			cleanline(i);//��������
			goals += (gpl*counter_fullline)*level;//һ���������� ��1��10�֣���2��20��... *�ȼ�
			level = goals / 100 + 1;
			SPEEDDOWN = pow(level, -0.3)/2;
		}
	}
	for (int j = 0; j < width; j++)//����Ƿ�over
	{
		if (a[0][j])
			gameover();
			
	}
}
void board::print()
{
	system("cls");
	SetConsoleTextAttribute(hOut, 15 );
	for (int i = 0; i < 4; i++)
	{
		myconsole.SetCursor(pblock2->Getall()[i].c*2+2, pblock2->Getall()[i].r+1);
		printf("��");
	}
	myconsole.SetCursor(0, 4);

	printf("  �x�x�x�x�x�x�x�x�x�x\n");
	for (int i = 0; i < height; i++)
	{
		printf("��");
		for (int j = 0; j < width; j++)
		{
			if (a[i][j])
				printf("��");
			else
				printf("  ");
		}
		printf("��\n");
	}
	printf("  ��������������������");
	printf("\n\n");
	printf("  Level: %d \n", level);
	printf("  Goals: %d\n",goals);
	printf("  Best Goals:%d\n", bg);
}
void board::printblock()
{
	all = pblock->Getall();
	for (int i = 0; i < 4; i++)
	{
		myconsole.SetCursor(all[i].c*2+2, all[i].r+5);
		printf("  ");
	}
	SetConsoleTextAttribute(hOut, 0);
	point* nextall = next.Getall();

	for (int i = 0; i < 4; i++)
	{
		SetConsoleTextAttribute(hOut, rand() % 6 + 9);
		myconsole.SetCursor(nextall[i].c * 2 + 2, nextall[i].r + 5);
		printf("��");
	}
}
void  board::newblock()
{
	pblock = new block(*pblock2);
	pblock2 = new block;
	all = pblock->Getall();
	for (int i = 0; i < 4; i++)
	{
		if (a[all[i].r][all[i].c] == true)
			gameover();
	}
}
void board::load()
{
	all = pblock->Getall();
	for (int i = 0; i < 4; i++)
	{	
		a[all[i].r][all[i].c] = true;
	}
}
void board::deload()
{
	all = pblock->Getall();
	for (int i = 0; i < 4; i++)
	{
		a[all[i].r][all[i].c] = false;
	}
}

bool board::gameover()
{
	SetConsoleTextAttribute(myconsole.GetHandle(),240);
	myconsole.SetCursor(0, 10);
	printf("    Game Over!      \n     Goals:[%d]     \n",goals);
	int r=0;
	

		if (goals > bg)
		{
			printf("    �������¼�¼��\n");
			fout.close();
			fout.open("GoalsRecord.txt");
			fout << goals;
		}
		else
		{
			printf(" ����Ŭ����    \n �� %d ���Ƽ�¼ ��\n", bg-goals);
		}
	
	printf(" ��r�����¿�ʼ \n �رճ��������������� \n");
	board::~board();
	int endx = _getch();
	if (endx == 82 || endx == 114)
	{
		return 1;
	}
	else
	{
		exit(0);
	}

}

void  board::singleRun()
{
	newblock();
	load();
	print();
	while (1)
	{
		ctimer t(SPEEDDOWN);
	//	const double start = clock();
		while (t.blast())
		{
			if (_kbhit())
			{
				keyboardoperate();
			}
				
		}
		
		next = *pblock;
		next.setkey(point{ next.Getall()[0].r + 1, next.Getall()[0].c });
		deload();
		if (opcheck())
		{
			printblock();
			*pblock = next;
			load();
		}
		else
		{
			load();
			print();
			finalcheck();		
			break;
		}
	
	}
}
void board::keyboardoperate()
{
	const int first = _getch();
	if (first == 224)
	{
		switch (_getch())
		{
		case 72://VK_UP
		uphere : next = *pblock;
			next.changedirection();
			deload();
			if (opcheck())
			{
				printblock();
				*pblock = next;
			}
			else if (next.Getall()[0].c >= width - 2)
			{
				next = *pblock;
				next.setkey(point{ next.Getall()[0].r, next.Getall()[0].c - 1 });
				deload();
				if (opcheck())
				{
					printblock();
					*pblock = next;
				}
				else
					goto downhere;
				load();
				goto uphere;
			}
			else if (next.Getall()[0].c <= 1)
			{
				next = *pblock;
				next.setkey(point{ next.Getall()[0].r, next.Getall()[0].c + 1 });
				deload();
				if (opcheck())
				{
					printblock();
					*pblock = next;
				}
				else
					goto downhere;
				load();
				goto uphere;
			}
			else if (next.Getall()[0].r <= 1)
			{
				next = *pblock;
				next.setkey(point{ next.Getall()[0].r + 1, next.Getall()[0].c });
				deload();
				if (opcheck())
				{
					printblock();
					*pblock = next;
				}
				else
					goto downhere;
				load();
				goto uphere;
			}
		downhere:	load();
			break;
		case 80://VK_DOWN
			next = *pblock;
			next.setkey(point{ next.Getall()[0].r + 1, next.Getall()[0].c });
			deload();
			if (opcheck())
			{
				printblock();
				*pblock = next;
			}
			load();
			break;
		case 75://VK_LEFT
			next = *pblock;
			next.setkey(point{ next.Getall()[0].r, next.Getall()[0].c - 1 });
			deload();
			if (opcheck())
			{
				printblock();
				*pblock = next;
			}
			load();
			break;
		case 77://VK_RGIHT
			next = *pblock;
			next.setkey(point{ next.Getall()[0].r, next.Getall()[0].c + 1 });
			deload();
			if (opcheck())
			{
				printblock();
				*pblock = next;
			}
			load();
			break;
		}
	}
	else if (first == 54 || first == 103 || first == 71)//6��,G�� ������
	{
		for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			a[i][j] = false;
		print();
		printblock();
		load();
	}
	else if (first == 27)//ESC��
	{
		myconsole.SetCursor(0, height+5);
			printf("Pause");
			system("pause");
	}
}