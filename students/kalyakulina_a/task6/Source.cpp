#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

class FirstField{
private:
	HANDLE ConsoleOutput;                                     //���� �� ���������� windows ��� ������ � ������� �������
	CONSOLE_CURSOR_INFO oldCursorInfo, curCursorInfo;
	WORD oldTextAttr;

public: FirstField() {
			ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

			GetConsoleCursorInfo(ConsoleOutput, &oldCursorInfo);
			curCursorInfo.dwSize = oldCursorInfo.dwSize;
			curCursorInfo.bVisible = oldCursorInfo.bVisible;

			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(ConsoleOutput, &csbi);
			oldTextAttr = csbi.wAttributes;
		}

		~FirstField() {
			SetConsoleCursorInfo(ConsoleOutput, &oldCursorInfo);
			SetConsoleTextAttribute(ConsoleOutput, oldTextAttr);
		}

		void cursor_show(bool visible) {                                      //��������� �������
			curCursorInfo.bVisible = visible;
			SetConsoleCursorInfo(ConsoleOutput, &curCursorInfo);
		}

		void text_attr(WORD attr) {                                             //���� ������/����
			SetConsoleTextAttribute(ConsoleOutput, attr);
		}

		void pos(int x, int y, char ch) {                                    //������� ������� � ����� �������
			COORD point;
			point.X = static_cast<SHORT>(x);
			point.Y = static_cast<SHORT>(y);
			SetConsoleCursorPosition(ConsoleOutput, point);
			if (ch > 0)
				_putch(ch);
		}

		void pos_str(int x, int y, const char *str) {                   //������� ������� � ����� ������
			pos(x, y, 0);
			_cprintf("%s", str);
		}

		void cls() {                                                        //������� ������
			system("cls");
		}
};

struct Coords {
public:
	int x, y;

	Coords(){
		this->x;
		this->y;
	}

	Coords(int _x, int _y){
		this->x = _x;
		this->y = _y;
	}

	Coords& operator +=(const Coords& op) {
		x += op.x;
		y += op.y;
		return *this;
	}

	friend const Coords operator +(const Coords op1, const Coords op2) {
		return Coords(op1.x + op2.x, op1.y + op2.y);
	}

	friend const bool operator ==(const Coords& op1, const Coords& op2) {
		return op1.x == op2.x && op1.y == op2.y;
	}

};

class Snake{
private:
	vector <Coords> worm;       // ������ ��������� ��������� ���� ����
	char head_mark;         // ������ ������ ����
	int drawn;
	char tail;
public:
	Snake(){
		head_mark = '@';
		tail = 'O';
	}
	void reset(Coords start_pos) {
		worm.clear();
		worm.reserve(1000);								// �������������� ������
		worm.push_back(start_pos);						// �������� ���������� ������
		start_pos.x--;
		worm.push_back(start_pos);						// �������� ���������� ������
		start_pos.x--;
		worm.push_back(start_pos);
		start_pos.x--;
		worm.push_back(start_pos);
		start_pos.x--;
		worm.push_back(start_pos);
		worm[0].x++;									// ���������� x ������ - �� 1 ������
	}

	void draw(FirstField& scr) {
		int wsize = worm.size() - 1;
		for (int i = 0; i < wsize; i++)
			scr.pos(worm[i].x, worm[i].y, tail);
		scr.pos(worm[wsize].x, worm[wsize].y, head_mark);
		drawn = worm.size();
	}

	void move(const Coords& delta, FirstField& scr) {
		if (drawn == worm.size())
			scr.pos(worm[0].x, worm[0].y, ' ');
		else
			drawn++;
		for (unsigned int i = 1; i < worm.size(); i++)
			worm[i - 1] = worm[i];
		worm[worm.size()-1] += delta;    

		scr.pos(worm[worm.size() - 1].x, worm[worm.size() - 1].y, head_mark);
		scr.pos(worm[worm.size() - 2].x, worm[worm.size() - 2].y, tail);
	}

	void grow(const Coords& pos, int growbits) {
		for (int i = 0; i < growbits; ++i)
			worm.insert(worm.begin(), pos);
	}

	bool into(const Coords& pos) {
		for (unsigned int i = 0; i < worm.size(); i++)
			if (worm[i].x == pos.x && worm[i].y == pos.y)
				return true;
		return false;
	}

	Coords head() {
		return worm[worm.size() - 1];
	}

	int size() {
		return worm.size();
	}
};

class Game{
private:
	int width, height;      // ������ � ������ �������� ����
	int latency;            // �������� ����� ���������� ������� � �������������
	FirstField scr;         // ������������
	int lengthSnake;		// ������������ ����� ������
	Snake snake;			// ������
	char fruit;				// ���
	enum Command { NOCOMMAND = 0, LEFT, RIGHT, UP, DOWN, EXIT};
	Command com;
	char border;			// ������ ��� ��������� ����� �������� ����
public:
	Game(FirstField scr, int width, int height, int latency, int lengthSnake) {
		this->width = width;
		this->height = height;
		this->latency = latency;
		this->scr = scr;;
		this->snake;
		this->com;
		this->border = '#';
		this->fruit = '$';
		this->lengthSnake = lengthSnake;
	}

	Command get_command() {

		int ch;

		ch = _getch();
		if (ch == 0 || ch == 0xe0) {
			ch = _getch();
		} else if (ch = 27) return EXIT;

		com = NOCOMMAND;
		switch(ch){
		case 75: com = LEFT; break;
		case 72: com = UP; break;
		case 77: com = RIGHT; break;
		case 80: com = DOWN; break;
		}

		return com;
	}

	// ���������� ��� ����������� ��������� �������.
	// �����������: ���������� �� ������ �������� � ���� ����.
	Coords make_food() {
		Coords food;
		do {
			food.x = rand() % (width - 2) + 1;
			food.y = rand() % (height - 2) + 1;
		} while (snake.into(food));

		return food;
	}

	void draw_field() {
		scr.cls();

		for (int y = 0; y < height; y++) {
			if (y == 0 || y == height - 1) {
				for (int x = 0; x < width; x++)
					scr.pos(x, y, border);
			}
			else {
				scr.pos(0, y, border);
				scr.pos(width - 1, y, border);
			}
		}
		scr.pos(0, height, 0);
	}


	void game_loop() {
		bool gameOver = false;
		draw_field();           // ���������� ������� ����

		snake.reset(Coords(width / 2, height / 2));     // ���������� ����: ����� 2,
		// ��������� - � �������� �������� ����,
		// ����������� - �����
		Command cmd = NOCOMMAND;
		// delta  �������� ���������� ��������� (dx, dy) ��� ������� ����������� ���� �� ����
		Coords delta(-1, 0);                // ��������� �������� - �����
		Coords food = make_food();          // ��������� ���������� ���
		scr.pos(food.x, food.y, fruit);      // ������� ��� �� �����

		snake.draw(scr);                    // ��������� ��������� ����

		// ������� ��������� ���������� ����

		do {

			if (_kbhit())                   // ���� � ������ ���������� ���� ����������,
				cmd = get_command();        // �� ������� �������

			// ��������� ������
			switch (cmd) {
			case LEFT:
				delta = Coords(-1, 0);
				break;
			case RIGHT:
				delta = Coords(1, 0);
				break;
			case UP:
				delta = Coords(0, -1);
				break;
			case DOWN:
				delta = Coords(0, 1);
				break;
			case EXIT: 
				gameOver = true;
				break;
			default:
				break;
			}

			clearkeys();

			Coords hd = snake.head();       // ���������� ������ ����
			hd += delta;                    // ���������� ������ ���� ����� ���������� (��������� �������)
			// ���� ������ ���� ����������� � �������� ���� ��� �� ����� ����, �� ���� �������
			if (hd.x == 0 || hd.x == width-1 || hd.y == 0 || hd.y == height-1 || snake.into(hd))
				gameOver = true;

			else {          // ���� ���� ��� ����, ��
				snake.move(delta, scr);     // �������� ���� �� delta

				if (snake.head() == food) { // ���� ���������� ������ ���� ��������� � ����������� ���, ��
					snake.grow(food, 1);    // ��������� ����� ����
					food = make_food();     // ��������� ���������� ����� ���
					scr.pos(food.x, food.y, fruit); // ������� ��� �� �����
					if (snake.size() >= lengthSnake) gameOver = true;
				}

				Sleep(latency);             // �������� ����� ��������� ���������� �������

			}
		} while (!gameOver);          // ������, ���� ���� ����

		scr.pos_str(width / 2 - 8, 10, " G a m e    o v e r ");
		clearkeys();
		_getch();
		clearkeys();
	}

	void clearkeys() {
		while (_kbhit())
			_getch();
	}


};




void main() {
	setlocale(LC_ALL, "Russian");
	FirstField screen;
	screen.cursor_show(false);
	screen.text_attr((WORD)0x0a);
	screen.cls();
	Game game(screen, 80, 24, 200, 8);

	game.game_loop();

}
