#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLACK 0
#define BLUE1 1
#define GREEN1 2
#define CYAN1 3
#define RED1 4
#define MAGENTA1 5
#define YELLOW1 6
#define GRAY1 7
#define GRAY2 8
#define BLUE2 9
#define GREEN2 10
#define CYAN2 11
#define RED2 12
#define MAGENTA2 13
#define YELLOW2 14
#define WHITE 15

#define SPECIAL1 0XE0
#define SPECIAL2 0x00
#define SPACE 0x20
#define UP 0x48
#define DOWN 0x50
#define LEFT 75
#define RIGHT 76

#define WIDTH 108
#define HEIGHT 48

#define UX 30  //시작 유저의 x좌표
#define UY 45  //시작 유저의 y좌표

int called = 0;

int oldx = UX, oldy = UY; // 플레이어의 old 좌표
int newx = UX, newy = UY; //플레이어의 new 좌표
int keep_moving = 1;  //1:계속이동

int Delay = 10;
int frame_count = 0; // game 진행 frame count 로 속도 조절용으로 사용된다.
int p1_frame_sync = 4; //플레이어의 이동속도

// □ , ■
void help();
void gameStart();
void playermove();
void playerdraw();
void playererase();

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void removeCursor(void)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void start() {
	textcolor(YELLOW1, BLACK);
	int a;
	printf("□□□□□□□■■■■□■□□■□■■■■□■■■■□■■■■■□■■■■■□■■■□■□□□■□■■■■□□□□□□□\n");
	printf("□□□□□□□■□□□□■□□■□■□□■□■□□■□□□■□□□□□■□□□□■□□■■□□■□■□□□□□□□□□□\n");
	printf("□□□□□□□■■■■□■■■■□■□□■□■□□■□□□■□□□□□■□□□□■□□■□■□■□■□■■□□□□□□□\n");
	printf("□□□□□□□□□□■□■□□■□■□□■□■□□■□□□■□□□□□■□□□□■□□■□□■■□■□□■□□□□□□□\n");
	printf("□□□□□□□■■■■□■□□■□■■■■□■■■■□□□■□□□□□■□□□■■■□■□□□■□■■■■□□□□□□□\n");
	gotoxy(54, 10);
	printf("1. 게임시작");
	gotoxy(54, 15);
	printf("2. 게임방법");
	gotoxy(54, 20);
	printf("3. 종료");
	gotoxy(54, 25);
	printf("번호를 입력해주세요");
	gotoxy(54, 27);
	while (1) {
		scanf("%d", &a);
		if (a == 1) {
			gameStart();
		}
		else if (a == 2) {
			help();
		}
		else if (a == 3) {
		}
	}
}

void init_game() {
	//변수값초기화
	system("cls");
	removeCursor();
}

void gameStart() {
	unsigned char ch;
	init_game();
		while (1) {
			if (kbhit() == 1) {
				ch = getch();
				if(ch == SPECIAL1 || ch==SPECIAL2){
					ch = getch();
					switch (ch) {
					case UP:case DOWN: case LEFT:
						playermove(ch);
						if (frame_count % p1_frame_sync == 0)
							playermove(0);
						break;
					case 77:
						playermove(ch);
						if (frame_count % p1_frame_sync == 0)
							playermove(0);

					default:
						if (frame_count % p1_frame_sync == 0)
							playermove(0);
					}

				}
			}
			else {
				//속도조절
			}
			Sleep(Delay);
			frame_count++;
		}
}
void playermove(unsigned char ch) {
	int move_flag = 0;
	static unsigned char last_ch = 0;

	if (called = 0) {
		removeCursor();
		playerdraw(oldx, oldy);
		called = 1;
	}
	if (keep_moving && ch == 0) {
		ch = last_ch;
	}
	last_ch = ch;
	switch (ch) {
	case UP:
		if (oldy > 25)
			newy = oldy - 1;
		move_flag = 1;
		break;
	case DOWN:
		if (oldy < HEIGHT - 3)
			newy = oldy + 1;
		move_flag = 1;
		break;
	case LEFT:
		if (oldx > 2)
			newx = oldx - 1;
		move_flag = 1;
		break;
	case 77:
		if (oldx < WIDTH-2)
			newx = oldx + 1;
		move_flag = 1;
		break;
	}
	if (move_flag) {
		playererase(oldx, oldy);
		playerdraw(newx, newy);
		oldx = newx;
		oldy = newy;
	}
}

void playerdraw(int x, int y) {
	textcolor(GREEN1, BLACK);
	gotoxy(x, y);
	printf("<=★=>");
}
void playererase(int x, int y) {
	gotoxy(x, y);
	printf("      ");
}

void help() {
	system("cls");
	gotoxy(56, 8);
	printf("도움말");

}

int main() {
	start();
}
