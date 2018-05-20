#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

class FirstField{
private:
	HANDLE ConsoleOutput;                                     //типы из библиотеки windows для работы с экраном консоли
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

		void cursor_show(bool visible) {                                      //видимость курсора
			curCursorInfo.bVisible = visible;
			SetConsoleCursorInfo(ConsoleOutput, &curCursorInfo);
		}

		void text_attr(WORD attr) {                                             //цвет текста/фона
			SetConsoleTextAttribute(ConsoleOutput, attr);
		}

		void pos(int x, int y, char ch) {                                    //позиция курсора и вывод символа
			COORD point;
			point.X = static_cast<SHORT>(x);
			point.Y = static_cast<SHORT>(y);
			SetConsoleCursorPosition(ConsoleOutput, point);
			if (ch > 0)
				_putch(ch);
		}

		void pos_str(int x, int y, const char *str) {                   //позиция курсора и вывод строки
			pos(x, y, 0);
			_cprintf("%s", str);
		}

		void cls() {                                                        //очистка экрана
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
	vector <Coords> worm;       // вектор координат сегментов тела змеи
	char head_mark;         // символ головы змеи
	int drawn;
	char tail;
public:
	Snake(){
		head_mark = '@';
		tail = 'O';
	}
	void reset(Coords start_pos) {
		worm.clear();
		worm.reserve(1000);								// зарезервировть память
		worm.push_back(start_pos);						// добавить координаты головы
		start_pos.x--;
		worm.push_back(start_pos);						// добавить координаты хвоста
		start_pos.x--;
		worm.push_back(start_pos);
		start_pos.x--;
		worm.push_back(start_pos);
		start_pos.x--;
		worm.push_back(start_pos);
		worm[0].x++;									// координата x хвоста - на 1 правее
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
	int width, height;      // ширина и высота игрового поля
	int latency;            // задержка между изменением позиции в миллисекундах
	FirstField scr;         // визуализация
	int lengthSnake;		// максимальная длина змейки
	Snake snake;			// змейка
	char fruit;				// еда
	enum Command { NOCOMMAND = 0, LEFT, RIGHT, UP, DOWN, EXIT};
	Command com;
	char border;			// символ для рисования рамки игрового поля
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

	// Координата еды вычисляется случайным образом.
	// Ограничение: координата не должна попадать в тело змеи.
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
		draw_field();           // нарисовать игровое поле

		snake.reset(Coords(width / 2, height / 2));     // установить змею: длина 2,
		// положение - в середине игрового поля,
		// направление - влево
		Command cmd = NOCOMMAND;
		// delta  содержит приращение координат (dx, dy) для каждого перемещения змеи по полю
		Coords delta(-1, 0);                // начальное движение - влево
		Coords food = make_food();          // вычислить координаты еды
		scr.pos(food.x, food.y, fruit);      // вывести еду на экран

		snake.draw(scr);                    // первичное рисование змеи

		// вывести начальную статистику игры

		do {

			if (_kbhit())                   // если в буфере клавиатуры есть информация,
				cmd = get_command();        // то принять команду

			// обработка команд
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

			Coords hd = snake.head();       // координата головы змеи
			hd += delta;                    // координата головы змеи после приращения (следующая позиция)
			// если голова змеи столкнулась с границей поля или со телом змеи, то змея умирает
			if (hd.x == 0 || hd.x == width-1 || hd.y == 0 || hd.y == height-1 || snake.into(hd))
				gameOver = true;

			else {          // если змея ещё жива, то
				snake.move(delta, scr);     // сдвинуть змею на delta

				if (snake.head() == food) { // если координата головы змеи совпадает с координатой еды, то
					snake.grow(food, 1);    // увеличить длину змеи
					food = make_food();     // вычислить координаты новой еды
					scr.pos(food.x, food.y, fruit); // вывести еду на экран
					if (snake.size() >= lengthSnake) gameOver = true;
				}

				Sleep(latency);             // задержка перед следующим изменением позиции

			}
		} while (!gameOver);          // играем, пока змея жива

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
