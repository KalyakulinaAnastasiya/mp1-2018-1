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

	Menu(char mas[]){
		count_rows=1;
		last_sel=-1;
		str=(char**)realloc(str, sizeof(char*));
		str[0]=(char*)malloc(strlen(mas) + 1);
		strcpy(str[0], mas); 
	}

	~Menu(){
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
		if (number == count_rows) {
			str=(char**)realloc(str, (count_rows+1)*sizeof(char*));
			count_rows++;
		} else {
			free (str[number]);
		}
		str[number]=(char*)malloc(strlen(mn) + 1);
		strcpy(str[number], mn);
	}

	char* getNumberItemsMenu(int itm) {
		last_sel = itm;
		return str[itm-1];
	}

	void setCountItemsMenu(int itm) {
		count_rows = itm;
	}

	int getlastNumberItemsMenu(){
		return last_sel;
	}
};

void main()
{
	char *str_a[] = {"Первый пункт"};
	int itm;

	setlocale(LC_ALL, "Russian");

	Menu *a = new Menu("Первый пункт");
	a->putMenu();
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
	int c = 0;
	cin>>c;

}