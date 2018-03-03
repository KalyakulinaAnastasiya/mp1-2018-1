#include <iostream>
#include <locale.h>

using namespace std;

class TWeighingScales
{
private:
	double kg; // weight in kg
public:
	TWeighingScales(double _kg = 0)// constructor
	{
		kg = _kg;
	}
	TWeighingScales & operator=(const TWeighingScales & kg1) 
	{
		kg = kg1.kg;
		return *this;
	}
	void display() // output on display
	{
		cout << "Weight in kg: " << kg << endl;
	}
	double killograms() 
	{
		return kg;
	}
	double pharmacyPound() //conversion to the phatmscy pound 
	{
		return kg * 2.2679;
	}

	double troyOunce() // conversion to the troy ounce
	{
		return kg * 35.2739;
	}
	double pood() // conversion to the pood
	{
		return kg * 0.061;
	}
	void displayPharmacyPound()
	{
		cout << "Weight in pharmacy pound:" << pharmacyPound() << endl;
	}
	void displayTroyOunce()
	{
		cout << "Weight in troy ounce:" << troyOunce() << endl;
	}
	void displayPood()
	{
		cout << "Weight in pood:" << pood() << endl;
	}
};


int main()
{
	setlocale(LC_ALL, "Russian");
	double flag;
	int a, b;
metka2:cout << "Enter the weight in kilograms:";
	cin >> flag;
	TWeighingScales weight1, weight2(flag);
	weight1.operator=(weight2);
metka3:cout << "\n Select an actoin:\n" << endl;
	cout << "1. Learn the current weight in kilograms\n" << endl;
	cout << "2. Learn the weight of the selected unit\n" << endl;
	cout << "3. Change the weight in kilograms\n" << endl;
	cin >> a;
	switch (a)
	{
	case 1: weight2.display(); break;
	case 2:
	{
	metka1:cout << "In which unit of measurement do you prefer to know the weight?\n" << endl;
		cout << "1. Pharmacy fund" << endl;
		cout << "2. Troy ounce" << endl;
		cout << "3. Pood" << endl;
		cin >> b;
		switch (b)
		{
		case 1: weight2.displayPharmacyPound(); break;
		case 2: weight2.displayTroyOunce(); break;
		case 3: weight2.displayPood(); break;
		default: cout << "Incorrect entry. Please try again.\n"; goto metka1;
		}
		break;
	}
	case 3: goto metka2;
	default: cout << "Incorrect entry. Please try again.\n"; goto metka3;
	}
}