#include <iostream>
using namespace std;

class Menu{
private:
	char** str;
	int count_rows;         //количество строк
	int last_sel;			// Последний выбранный пункт

public:
	Menu(){
		count_rows=0;
		last_sel = -1;
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
			printf("%d  -  %s\n", i+1, str[i]);
		}
	}

	void putMenu(int left, int down){
		for(int j=0; j<down; j++){
			printf("\n");
		}

		for(int i=0; i<count_rows; i++) {
			for(int j=0; j<left; j++){
				printf(" ");
			}
			printf("%d  -  %s\n", i+1, str[i]);
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
		last_sel = itm;
		return str[itm-1];
	}

	void setCountItemsMenu(int itm) {
		for (int i=itm; i<count_rows;i++)
		{
			delete[] str[i];
		}
		count_rows = itm;

	}

	int getlastNumberItemsMenu(){
		return last_sel;
	}

	int ShowAndSelMenu(){
		int itm;
		putMenu();
		printf("Выбирите пункт меню: ");
		cin>>itm;
		return itm;
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
	cout<<"Выбор пункта меню с выдачей выбранного номера: \n";
	cout<<"---------------------------------------------- \n";
	a->putMenu();
	cout<<"Выберите пункт меню: ";
	cin>>itm;
	printf("Выбран пункт %d -  %s\n",itm, a->getNumberItemsMenu (itm));

	cout<<"Выдача номера последнего выбранного пункта меню: \n";
	cout<<"------------------------------------------------ \n";
	if (a->getlastNumberItemsMenu() < 0) {
		cout<<"Пункты меню не выбирались \n";
	} else {
		printf("Последний выбранный пункт меню: %d -  %s\n", a->getlastNumberItemsMenu(), a->getNumberItemsMenu (a->getlastNumberItemsMenu()));
	}

	cout<<"выбор пункта меню: \n";
	cout<<"------------------------------------------------ \n";
	itm = a->ShowAndSelMenu();
	printf("Выбран пункт %d -  %s\n",itm, a->getNumberItemsMenu (itm)); 

	int c = 0;
	cin>>c;

}