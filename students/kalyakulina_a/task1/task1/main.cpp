
#include <iostream>
using namespace std;


class Long_number {
private:
	unsigned int a_right;		// Младшая часть
	unsigned int a_left;		// Старшая часть
	unsigned int a_sign;		// 0 - "+", 1 - "-"


public:
	Long_number() {a_right=a_left=0;a_sign=0;}

	Long_number(int i) {
		if (i<0) {
			a_sign=1;
			a_right=-i;
			a_left=0;
		}
		else {
			a_right=i; 
			a_left=0;
			a_sign=0;
		}
	}

	Long_number(unsigned int right, unsigned int left, unsigned int sign) {a_right=right; a_left=left; a_sign=sign;}

	// Вывод на консоль
	void putLong_number()
	{
		char *c = "";
		if (a_sign != 0) {
			c = "-";
		}

		cout<<c<<a_left<<a_right<<"\n";
	}

	// Перегрузка оператора +
	friend const Long_number operator +(Long_number& a1,Long_number &b1)
	{
		unsigned int t_l, t_r, t_s;		// 32 бит
		long t_res, t_a1, t_b1;			// 64 бит
		// Приводим данные к типу long (64 бит)
		t_a1 = a1.a_right + (a1.a_left ) * pow(2,32);
		t_b1 = b1.a_right + (b1.a_left ) * pow(2,32);
		// Учитываем знак
		if (a1.a_sign != 0) {t_a1 = -t_a1;}
		if (b1.a_sign != 0) {t_b1 = -t_b1;}
		// Операция
		t_res=t_a1+t_b1;
		// Формируем знак результата
		t_s = 0;
		if (t_res < 0) {
			t_s = 1;
			t_res=-t_res;
		}
		// Приводим результат к типу unsigned int (32 бит)
		t_r = t_res;				// Мл. часть
		t_l = (t_res) / pow(2,32);	// Ст. часть

		return (Long_number(t_r, t_l, t_s));
	}


	friend const Long_number operator -(Long_number& a1,Long_number &b1)
	{
		unsigned int t_l, t_r, t_s;		// 32 бит
		long t_res, t_a1, t_b1;			// 64 бит

		t_a1 = a1.a_right + (a1.a_left ) * pow(2,32);
		t_b1 = b1.a_right + (b1.a_left ) * pow(2,32);
		if (a1.a_sign != 0) {t_a1 = -t_a1;}
		if (b1.a_sign != 0) {t_b1 = -t_b1;}

		t_res=t_a1-t_b1;

		t_s = 0;
		if (t_res < 0) {
			t_s = 1;
			t_res=-t_res;
		}

		t_r = t_res;
		t_l = t_res  / pow(2,32);

		return (Long_number(t_r, t_l, t_s));
	}
	friend const Long_number operator /(Long_number& a1,Long_number &b1)
	{
		unsigned int t_l, t_r, t_s;		// 32 бит
		long t_res, t_a1, t_b1;			// 64 бит

		t_a1 = a1.a_right + (a1.a_left ) * pow(2,32);
		t_b1 = b1.a_right + (b1.a_left ) * pow(2,32);
		if (a1.a_sign != 0) {t_a1 = -t_a1;}
		if (b1.a_sign != 0) {t_b1 = -t_b1;}

		if (t_b1 != 0) {
			t_res=t_a1/t_b1;
		}

		else {
			t_res = 0;
			cout<<"Деление на нуль";
		}


		t_s = 0;
		if (t_res < 0) {
			t_s = 1;
			t_res=-t_res;
		}

		t_r = t_res;
		t_l = t_res / pow(2,32);

		return (Long_number(t_r, t_l, t_s));
	}

	friend const Long_number operator *(Long_number& a1,Long_number &b1)
	{
		unsigned int t_l, t_r, t_s;		// 32 бит
		long t_res, t_a1, t_b1;			// 64 бит

		t_a1 = a1.a_right + (a1.a_left ) * pow(2,32);
		t_b1 = b1.a_right + (b1.a_left ) * pow(2,32);
		if (a1.a_sign != 0) {t_a1 = -t_a1;}
		if (b1.a_sign != 0) {t_b1 = -t_b1;}

		t_res=t_a1*t_b1;

		t_s = 0;
		if (t_res < 0) {
			t_s = 1;
			t_res=-t_res;
		}

		t_r = t_res;
		t_l = t_res / pow(2,32);

		return (Long_number(t_r, t_l, t_s));
	}

	friend const Long_number operator %(Long_number& a1,Long_number &b1)
	{
		unsigned int t_l, t_r, t_s;		// 32 бит
		long t_res, t_a1, t_b1;			// 64 бит

		t_a1 = a1.a_right + (a1.a_left ) * pow(2,32);
		t_b1 = b1.a_right + (b1.a_left ) * pow(2,32);
		if (a1.a_sign != 0) {t_a1 = -t_a1;}
		if (b1.a_sign != 0) {t_b1 = -t_b1;}

		t_res=t_a1%t_b1;

		t_s = 0;
		if (t_res < 0) {
			t_s = 1;
			t_res=-t_res;
		}

		t_r = t_res;
		t_l = t_res / pow(2,32);

		return (Long_number(t_r, t_l, t_s));
	}

	Long_number& operator=(const Long_number& r) {
		//проверка на самоприсваивание
		if (this == &r) {
			return *this;
		}
		a_right = r.a_right;
		a_left = r.a_left;
		a_sign = r.a_sign;
		return *this;
	}

};



int main()
{
	//setlocale(LC_ALL, "Russian");
	Long_number* _a = new Long_number(10000);
	Long_number* _b = new Long_number(20000);
	Long_number* _c = new Long_number();
	*_c = *_a + *_b;
	_c->putLong_number();
	*_c = *_a * *_b;
	_c->putLong_number();
	*_c = *_a - *_b;
	_c->putLong_number();
	*_c = *_b / *_a;
	_c->putLong_number();
	*_c = *_a % *_b;
	_c->putLong_number();


	int c = 0;
	cin>>c;
	return 0;



}