#include <iostream>
using namespace std;
#include <cmath>

class Vector {
private:
	int *vec;
	int size;

public:
	Vector() {
		size = 1;
		vec = new int[1];
		vec[0]= 0;
	}

	Vector(int mas[], int n) {                   
		size = n; 
		vec = new int [n]; // это не точно +1
		for (int i=0; i<n; i++)
			vec[i] = mas[i];
	}

	~Vector() {
		delete[] vec; 
	}

	void putVector() {
		cout<<"--------------------------\n";
		for(int i=0; i<size; i++){
			cout<<vec[i]<<" ";
		}
		cout<<"\n--------------------------\n";
	}

	void setSizeVector(){
		cout<<"Задайте размер вектора: ";
		cin>>size;
		cout<<"\n";
		if((size<0)||(size>20)){
			cout<<"Размер выходит за границы допустимого. Попробуйте еще раз: ";
			cin>>size;
			cout<<"\n";
		}
	}

	int getSizeVector(){
		return size;
	}

	void setComponentVector(int number, int comp) {
		if (number < size) {
			vec[number]=comp;
		}
	}

	int getComponentVector(int number) {
		if (number >= size) return NULL;
		else return vec[number];
	}

	int getLengthVector(){
		int lengh=0;
		for(int i=0; i<size; i++){
			lengh+=vec[i]*vec[i];
		}
		return sqrt(lengh);

	}

	int getScalarVector(Vector& r){
		int scalar=0;
		int t_size;

		if(size>r.size) { t_size = r.size;}
		else {t_size = size;}

		for(int i=0; i<t_size; i++){
			scalar+=vec[i]*r.vec[i];
		}
		return scalar;
	}

	Vector& operator=(const Vector& r){
		if(this == &r){
			return *this;
		}
		size = r.size;
		for (int i=0; i<size; i++) {
			vec[i]=r.vec[i];
		}
		return *this;
	}

	/// Перегрузка оператора +
	friend const Vector operator +(Vector& a1,Vector &b1)
	{
		int *t_m = new int[a1.size];
		for (int i=0; i<a1.size; i++) {
			t_m[i]=a1.vec[i]+b1.vec[i];
		}

		return (Vector (t_m, a1.size));
	}
};


void main()
{
	int m_a[] = {1,2,3,4,5,6};
	int m_b[] = {6,5,4,3,2,1,9,8,7};
	int m_с[] = {3,2,1,9,8,7};
	int number;
	int comp;


	setlocale(LC_ALL, "Russian");

	Vector *a = new Vector(m_a, 6);
	a->putVector();
	cout<<"Ввод компоненты по номеру:\n";
	cout<<"--------------------------\n";
	cout<<"Введите номер компоненты: ";
	cin>>number;
	if (number >= a->getSizeVector()) {
		cout<<"Номер компоненты больше длины вектора\n";
	} else {
		cout<<"Введите значение компоненты: ";
		cin>>comp;
		a->setComponentVector(number, comp);
	}
	a->putVector();
	cout<<"Чтение компоненты по номеру:\n";
	cout<<"----------------------------\n";
	cout<<"Введите номер компоненты: ";
	cin>>number;
	if (number >= a->getSizeVector()) {
		cout<<"Номер компоненты больше длины вектора\n";
	} else {

		cout<<"\n Компонента с номером "<<number<<" равна "<<a->getComponentVector(number)<<"\n";
	}
	cout<<"Вычисление длины вектора:\n";
	cout<<"----------------------------\n";
	cout<<"\nДлина вектора а равна "<<a->getLengthVector()<<"\n";

	cout<<"Вычисление скалярного произведения векторов:\n";
	cout<<"--------------------------------------------\n";
	Vector *b = new Vector(m_b, 9);
	cout<<"\nCкалярное произведение векторов а и b равна "<<a->getScalarVector(*b)<<"\n";

	cout<<"Вычисление суммы векторов:\n";
	cout<<"--------------------------\n";
	Vector *v = new Vector();
	Vector *с = new Vector(m_с, 6);
	*v = *a + *с;
	v->putVector();
	int c = 0;
	cin>>c;
}