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
struct point{ int r;int c; };//r行，c列

/*---------方块---------*/
class block
{
	Shape shape;// 方块的形状 ，有五种
	point key;//方块基点
	point all[4];//方块四个点的位置
	Direction direction;
	bool state;//是否在下降过程中
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

/*--------主面板----------*/
class board
{
	bool a[height][width];//游戏主面板
	int goals;//得分
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
	void cleanline(int);//消除一行
	bool dropcheck();
	bool opcheck();//对键盘操作的检查是否能操作
	void finalcheck();//是否消除得分，是否gameover
	void print();//方块落地后，check，清屏并打印主面板和得分
	void printblock();
	void newblock();//产生一个新的方块
	void load();//把方块load到主面板上
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

/*------tetris 类----------------*/
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

/*----------block 类的实现---------------*/
block::block()
{
	direction = DOWN;
	srand((unsigned int)time(0));
	shape = Shape(rand() % 7);//随机的方块类型
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
/*----------board 类的实现---------------*/
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
bool board::opcheck()//判断对方块操作后的next是否合法
{
	point *nextall = &next.Getall()[0];
    for (int i = 0; i < 4; i++)
	{
		if (nextall[i].r >= height || nextall[i].c >= width || nextall[i].c < 0)//边界检查
			return false;
		if (a[nextall[i].r][nextall[i].c])//碰撞检查
			return false;
	}
	return true;
}
void board::finalcheck()
{
	int counter_fullline = 0;
	for (int i = 0; i < height; i++)//检查是否消除得分
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
			cleanline(i);//消除此行
			goals += (gpl*counter_fullline)*level;//一次性消多行 第1行10分，第2行20分... *等级
			level = goals / 100 + 1;
			SPEEDDOWN = pow(level, -0.3)/2;
		}
	}
	for (int j = 0; j < width; j++)//检查是否over
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
		printf("□");
	}
	myconsole.SetCursor(0, 4);

	printf("  ▁▁▁▁▁▁▁▁▁▁\n");
	for (int i = 0; i < height; i++)
	{
		printf("▕");
		for (int j = 0; j < width; j++)
		{
			if (a[i][j])
				printf("█");
			else
				printf("  ");
		}
		printf("▏\n");
	}
	printf("  ▔▔▔▔▔▔▔▔▔▔");
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
		printf("█");
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
			printf("    创造了新纪录！\n");
			fout.close();
			fout.open("GoalsRecord.txt");
			fout << goals;
		}
		else
		{
			printf(" 继续努力！    \n 差 %d 分破纪录 ！\n", bg-goals);
		}
	
	printf(" 按r键重新开始 \n 关闭程序请任意其他键 \n");
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
	else if (first == 54 || first == 103 || first == 71)//6键,G键 开挂用
	{
		for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			a[i][j] = false;
		print();
		printblock();
		load();
	}
	else if (first == 27)//ESC键
	{
		myconsole.SetCursor(0, height+5);
			printf("Pause");
			system("pause");
	}
}