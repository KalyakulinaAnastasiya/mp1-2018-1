#include <iostream>
using namespace std;

class Menu{
private:
	char** str;
	int count_rows;         //количество строк
	int last_sel;			// Последний выбранный пункт
	int hide_item;			// Временно скрытый пункт меню

public:
	Menu(){
		count_rows=0;
		last_sel = -1;
		hide_item = -1;
		str = NULL;
	}

	Menu(int menuCount){
		count_rows=menuCount;
		last_sel=-1;
		str = new char* [count_rows];

		for (int i=0; i<count_rows;i++)
		{
			str[i] = new char[1];
		}

	}

	~Menu(){
		for (int i=0; i<count_rows; i++)
		{
			delete[] str[i];
		}
		delete[] str;
	}

	void putMenu(){
		for(int i=0; i<count_rows; i++){
			if (i != hide_item)
			{
				printf("%d  -  %s\n", i+1, str[i]);
			}
		}
	}

	void putMenu(int left, int down){
		for(int j=0; j<down; j++){
			printf("\n");
		}

		for(int i=0; i<count_rows; i++) {
			if (i != hide_item)
			{
				for(int j=0; j<left; j++){
					printf(" ");
				}
				printf("%d  -  %s\n", i+1, str[i]);
			}
		}
	}


	int getNumberItemsMenu(){
		return count_rows;
	}

	void setNameItemsMenu(char mn[], int number){

		delete[] str[number];

		str[number]= new char[strlen(mn) + 1];
		strcpy(str[number], mn);
	}

	char* getNumberItemsMenu(int itm) {
		return str[itm-1];
	}

	void setCountItemsMenu(int itm) {
		for (int i=itm; i<count_rows;i++)
		{
			delete[] str[i];
		}

		char** str_tmp = new char* [itm];
		for (int i=0; i<itm; i++)
		{
			str_tmp[i] = str[i];
		}

		delete[] str;
		str = str_tmp;
		count_rows = itm;

	}

	int getlastNumberItemsMenu(){
		return last_sel;
	}

	int ShowAndSelMenu(){
		int itm = hide_item;
		putMenu();
		printf("Выбирите пункт меню: ");
		cin>>itm;
		if ((itm-1) == hide_item)
		{
			printf("Пункт меню скрыт!\n");
		}
		last_sel = itm-1;
		return itm;
	}

	void hideMenuItem (int itm) {
		hide_item = itm;
	}

	void showHidedMenuItem()
	{
		hide_item = -1;
	}
};

void main()
{
	char *str_a[] = {"Первый пункт"};
	int itm;

	setlocale(LC_ALL, "Russian");

	Menu *a = new Menu(6);
	a->setNameItemsMenu("Первый пункт",0);
	a->setNameItemsMenu("Второй пункт",1);
	a->setNameItemsMenu("Третий пункт",2);
	a->setNameItemsMenu("Четвертый пункт",3);
	a->setNameItemsMenu("Пятый пункт",4);
	a->setNameItemsMenu("Шестой пункт",5);
	a->putMenu();
	//Вывести меню на экран в выбранной позиции окна консоли
	a->putMenu(5,5);

	// Задать число команд меню
	a->setCountItemsMenu(4);
	a->putMenu();

	// Узнать число команд меню	
	printf("В меню  %d команд\n", a->getNumberItemsMenu());
	if (a->getlastNumberItemsMenu() < 0) {
		cout<<"Пункты меню не выбирались \n";
	} else {
		printf("Последний выбранный пункт меню: %d -  %s\n", a->getlastNumberItemsMenu(), a->getNumberItemsMenu (a->getlastNumberItemsMenu()));
	}


	//обеспечить выбор пользователем пункта меню с выдачей выбранного номера
	cout<<"выбор пункта меню: \n";
	cout<<"------------------------------------------------ \n";
	itm = a->ShowAndSelMenu();
	printf("Выбран пункт %d -  %s\n",itm, a->getNumberItemsMenu (itm)); 

	cout<<"Выдача номера последнего выбранного пункта меню: \n";
	cout<<"------------------------------------------------ \n";
	if (a->getlastNumberItemsMenu() < 0) {
		cout<<"Пункты меню не выбирались \n";
	} else {
		printf("Последний выбранный пункт меню: %d -  %s\n", a->getlastNumberItemsMenu(), a->getNumberItemsMenu (a->getlastNumberItemsMenu()));
	}

	// Скрываем пункт меню
	a->hideMenuItem(2);
	itm = a->ShowAndSelMenu();
	printf("Выбран пункт %d -  %s\n",itm, a->getNumberItemsMenu (itm));
	// Показываем скрытый пункт меню
	a->showHidedMenuItem();
	itm = a->ShowAndSelMenu();
	printf("Выбран пункт %d -  %s\n",itm, a->getNumberItemsMenu (itm));
	int c = 0;
	cin>>c;

}