#include <iostream>
using namespace std;

class Menu{
private:
	char** str;
	int count_rows;         //���������� �����
	int last_sel;			// ��������� ��������� �����
	int hide_item;			// �������� ������� ����� ����

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
		printf("�������� ����� ����: ");
		cin>>itm;
		if ((itm-1) == hide_item)
		{
			printf("����� ���� �����!\n");
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
	char *str_a[] = {"������ �����"};
	int itm;

	setlocale(LC_ALL, "Russian");

	Menu *a = new Menu(6);
	a->setNameItemsMenu("������ �����",0);
	a->setNameItemsMenu("������ �����",1);
	a->setNameItemsMenu("������ �����",2);
	a->setNameItemsMenu("��������� �����",3);
	a->setNameItemsMenu("����� �����",4);
	a->setNameItemsMenu("������ �����",5);
	a->putMenu();
	//������� ���� �� ����� � ��������� ������� ���� �������
	a->putMenu(5,5);

	// ������ ����� ������ ����
	a->setCountItemsMenu(4);
	a->putMenu();

	// ������ ����� ������ ����	
	printf("� ����  %d ������\n", a->getNumberItemsMenu());
	if (a->getlastNumberItemsMenu() < 0) {
		cout<<"������ ���� �� ���������� \n";
	} else {
		printf("��������� ��������� ����� ����: %d -  %s\n", a->getlastNumberItemsMenu(), a->getNumberItemsMenu (a->getlastNumberItemsMenu()));
	}


	//���������� ����� ������������� ������ ���� � ������� ���������� ������
	cout<<"����� ������ ����: \n";
	cout<<"------------------------------------------------ \n";
	itm = a->ShowAndSelMenu();
	printf("������ ����� %d -  %s\n",itm, a->getNumberItemsMenu (itm)); 

	cout<<"������ ������ ���������� ���������� ������ ����: \n";
	cout<<"------------------------------------------------ \n";
	if (a->getlastNumberItemsMenu() < 0) {
		cout<<"������ ���� �� ���������� \n";
	} else {
		printf("��������� ��������� ����� ����: %d -  %s\n", a->getlastNumberItemsMenu(), a->getNumberItemsMenu (a->getlastNumberItemsMenu()));
	}

	// �������� ����� ����
	a->hideMenuItem(2);
	itm = a->ShowAndSelMenu();
	printf("������ ����� %d -  %s\n",itm, a->getNumberItemsMenu (itm));
	// ���������� ������� ����� ����
	a->showHidedMenuItem();
	itm = a->ShowAndSelMenu();
	printf("������ ����� %d -  %s\n",itm, a->getNumberItemsMenu (itm));
	int c = 0;
	cin>>c;

}