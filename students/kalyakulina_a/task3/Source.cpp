#include <iostream>
using namespace std;

class Menu{
private:
	char** str;
	int count_rows;         //���������� �����
	int last_sel;			// ��������� ��������� �����

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
	char *str_a[] = {"������ �����"};
	int itm;

	setlocale(LC_ALL, "Russian");

	Menu *a = new Menu("������ �����");
	a->putMenu();
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
	cout<<"����� ������ ���� � ������� ���������� ������: \n";
	cout<<"---------------------------------------------- \n";
	a->putMenu();
	cout<<"�������� ����� ����: ";
	cin>>itm;
	printf("������ ����� %d -  %s\n",itm, a->getNumberItemsMenu (itm));

	cout<<"������ ������ ���������� ���������� ������ ����: \n";
	cout<<"------------------------------------------------ \n";
	if (a->getlastNumberItemsMenu() < 0) {
		cout<<"������ ���� �� ���������� \n";
	} else {
		printf("��������� ��������� ����� ����: %d -  %s\n", a->getlastNumberItemsMenu(), a->getNumberItemsMenu (a->getlastNumberItemsMenu()));
	}
	int c = 0;
	cin>>c;

}