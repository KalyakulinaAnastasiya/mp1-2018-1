#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <atltime.h>
using namespace std;

class ClientInformation{
private:
	int ClientNumber;			// Номер счета
	string Name;		// ФИО
	string Password;	// Пароль
	int Amount;			// Сумма на счету
public:
	ClientInformation () {}
	ClientInformation (int Number, string Name, string Password) {
		this->ClientNumber = Number;
		this->Name = Name;
		this->Password = Password;
		this->Amount = 0;
	}

	int getAmout () {
		return Amount;
	}

	void addAmount (int amount) {
		this->Amount+=amount;
	}

	void subAmount (int amount) {
		if (amount > this->Amount)
		{
			cout<<"Недостаточно средств на счете\n";
		}
		else
		{
			this->Amount-=amount;
		}
	}

	bool operator==(const ClientInformation & inf) {
		return this->ClientNumber == inf.ClientNumber&&this->Password == inf.Password;
	}

	string getName(){
		return this->Name;
	}

	string getPassword(){
		return this->Password;
	}

	int getClientNumber() {
		return this->ClientNumber;
	}
};

class DepositInformation{
private:
	int depositNumber;			// Номер депозита
	string depositName;			// Имя депозита		
	double depositRate;			// Процентная ставка
	int depositAge;				// Срок депозита в месяцах
	int startSumma;				// Начальная сумма
	int endSumma;				// Конечноя сумма
public:
	DepositInformation () {}
	DepositInformation (int depositNumber, string depositName, double depositRate,
		int depositAge, int startSumma, int endSumma) {
			this->depositNumber = depositNumber;
			this->depositName = depositName;
			this->depositRate = depositRate;
			this->depositAge = depositAge;
			this->startSumma = startSumma;
			this->endSumma = endSumma;
	}

	int getDepositNumber ()
	{
		return depositNumber;
	}

	string getDepositName ()
	{
		return depositName;
	}

	double getDepositRate ()
	{
		return depositRate;
	}

	int getDepositAge ()
	{
		return depositAge;
	}

	int getDepositstartSumma ()
	{
		return startSumma;
	}

	int getDepositendSumma ()
	{
		return depositNumber;
	}

};

class Deposit {
	int ClentNumber;
	int DepositNumber;
	int Amount;
	bool IsOpen;
	CTime DateOpen;
	CTime DateClose;
	int ProcReturning;
public:

	Deposit(int clientNumber, int depositNumber, int amount, string dateOpen){
		this->ClentNumber = clientNumber;
		this->DepositNumber = depositNumber;
		this->Amount = amount;
		this->IsOpen = true;
		this->DateOpen = getCTimeFromString(dateOpen);
		this->ProcReturning = 0;
	}

	CTime getDateOpen (){
		return DateOpen;
	}

	CTime getDateClose (){
		return DateClose;
	}

	int getClientNumber(){
		return this->ClentNumber;
	}

	int getDepositNumber() {
		return this->DepositNumber;
	}

	int getAmount(){
		return this->Amount;
	}

	bool getIsOpen() {
		return this->IsOpen;
	}

	int getProcReturning(){
		return this->ProcReturning;
	}

	CTime getCTimeFromString(string dateStr) {
		int year, month, day;
		int hh = 0;
		int mm = 0;
		int ss = 0;
		char *cstr = &dateStr[0u];

		sscanf(cstr, "%d.%d.%d %d:%d:%d", &day, &month, &year, &hh, &mm, &ss);
		return CTime(year, month, day, hh, mm, ss);

	}

	int getProcent(string currentDate, double depositRate, int amount){
		CTime ct = getCTimeFromString(currentDate);
		int proc = amount * getDays(DateOpen, ct) * depositRate / 365.0;
		return proc;
	}

	int getDays(CTime c1, CTime c2) {
		int year1 = c1.GetYear();
		int month1 = c1.GetMonth();
		int day1 = c1.GetDay();

		int year2 = c2.GetYear();
		int month2 = c2.GetMonth();
		int day2 = c2.GetDay();

		int days = 0;

		days = (year2 - year1) * 365;
		days+= (month2 - month1) * 30;
		days+= day2 - day1;
		return days;
	}

	int getProcFromDeposit (string currentDate, double depositRate, int amount) {
		int proc = getProcent(currentDate, depositRate, amount) - ProcReturning;
		this->ProcReturning+=proc;
		return proc;
	}

	int closeDiposit (string currentDate, double depositRate, int amount, int age) {
		int proc = 0;
		CTime ct = getCTimeFromString(currentDate);
		int days = getDays(DateOpen, ct);
		if (days < age*30) {
			return -1;
		}
		else {
			proc = getProcFromDeposit (currentDate, depositRate, amount);
			IsOpen = false;
			DateClose = ct;
			return proc;
		}
	}
};

class ProcessingCenter{
private:
	vector <DepositInformation> depositInform;
	vector <ClientInformation> clientInform;
	vector <Deposit> deposit;
	int clientNumber;
	vector <DepositInformation>::iterator iteratorDepositInform;
	vector <ClientInformation>::iterator iteratorClientInform;
	vector <Deposit>::iterator iteratorDeposit;
public:

	ProcessingCenter() {
		this->clientNumber = 1;
		DepositInformation *d = new DepositInformation(1,"Депозит №1 на 3 месяца 6% годовых от 1 до 100 000 руб.",0.06,3,1,100000);
		this->depositInform.push_back(*d);
		d = new DepositInformation(2,"Депозит №2 на 3 месяца 6% годовых от 100 001 до 500 000 руб.",0.066,3,100001,500000);
		this->depositInform.push_back(*d);
	}

	~ProcessingCenter() {
		ClientInformation *c = NULL;
		iteratorClientInform = clientInform.begin();
		while (iteratorClientInform != clientInform.end()) {
			*c = *iteratorClientInform++;
			delete c;
		}

		DepositInformation *d = NULL;
		iteratorDepositInform = depositInform.begin();
		while (iteratorDepositInform != depositInform.end()) {
			*d = *iteratorDepositInform++;
			delete d;
		}

		Deposit *p = NULL;
		iteratorDeposit = deposit.begin();
		while (iteratorDeposit != deposit.end()) {
			*p = *iteratorDeposit++;
			delete p;
		}
	}

	void addClient(string name, string password) {
		ClientInformation * c = new ClientInformation(this->clientNumber, name,password);
		this->clientNumber++;
		this->clientInform.push_back(*c);
	}

	int getAutorization(string name, string password) {
		iteratorClientInform = clientInform.begin();
		while (iteratorClientInform != clientInform.end()) {
			if (iteratorClientInform->getName() == name && 
				iteratorClientInform->getPassword() == password)
			{
				return iteratorClientInform->getClientNumber();
			}
			iteratorClientInform++;
		}
		return -1;
	}

	string getDipositForClient(int clientNumber) {
		string str = "";
		int clientAmount = 0;
		iteratorClientInform = clientInform.begin();
		while (iteratorClientInform != clientInform.end()) {
			if (iteratorClientInform->getClientNumber() == clientNumber)
			{
				clientAmount = iteratorClientInform->getAmout();
			}
			iteratorClientInform++;
		}

		iteratorDepositInform = depositInform.begin();
		while (iteratorDepositInform != depositInform.end()) {
			if (clientAmount >= iteratorDepositInform->getDepositstartSumma())
			{
				str = str + iteratorDepositInform->getDepositName()  +	"\n";
			}
			iteratorDepositInform++;
		}
		return str;
	}

	int getAmountClient(int clientNumber) {
		int clientAmount = 0;
		iteratorClientInform = clientInform.begin();
		while (iteratorClientInform != clientInform.end()) {
			if (iteratorClientInform->getClientNumber() == clientNumber)
			{
				clientAmount = iteratorClientInform->getAmout();
			}
			iteratorClientInform++;
		}
		return clientAmount;
	}

	void addAmount(int clientNumber, int amound){
		iteratorClientInform = clientInform.begin();
		while (iteratorClientInform != clientInform.end()) {
			if (iteratorClientInform->getClientNumber() == clientNumber)
			{
				iteratorClientInform->addAmount(amound);
			}
			iteratorClientInform++;
		}
	}

	void subAmount(int clientNumber, int amount){
		iteratorClientInform = clientInform.begin();
		while (iteratorClientInform != clientInform.end()) {
			if (iteratorClientInform->getClientNumber() == clientNumber)
			{
				iteratorClientInform->subAmount(amount);
			}
			iteratorClientInform++;
		}
	}

	void addDeposit (int clientNumber, int depositNumber, int amount, string dateOpen) {
		Deposit *d = new Deposit(clientNumber, depositNumber, amount, dateOpen);
		this->deposit.push_back(*d);
		iteratorClientInform = clientInform.begin();
		while (iteratorClientInform != clientInform.end()) {
			if (iteratorClientInform->getClientNumber() == clientNumber)
			{
				iteratorClientInform->subAmount(amount);
			}
			iteratorClientInform++;
		}
	}

	string dateToString (CTime ctime) {
		return to_string(ctime.GetDay())+"."+to_string(ctime.GetMonth())+"."+to_string(ctime.GetYear());
	}

	string getDepositByClient(int clientNumber) {
		string str = "";
		int depositNumber = 0;
		int depositAmount = 0;
		iteratorDeposit = deposit.begin();
		while (iteratorDeposit != deposit.end()) {
			if (iteratorDeposit->getClientNumber() == clientNumber)
			{
				depositNumber = iteratorDeposit->getDepositNumber();
				depositAmount = iteratorDeposit->getAmount();
			}
			iteratorDeposit++;
		}

		iteratorDepositInform = depositInform.begin();
		while (iteratorDepositInform != depositInform.end()){
			str = iteratorDepositInform->getDepositName() + " на сумму " + to_string(depositAmount);
			iteratorDepositInform++;
		}

		return str;
	}

	int getOpenDiposit(int clientNumber) {
		iteratorDeposit = deposit.begin();
		while (iteratorDeposit != deposit.end()) {
			if (iteratorDeposit->getClientNumber() == clientNumber &&
				iteratorDeposit->getIsOpen())
			{
				return iteratorDeposit->getDepositNumber();
			}
			iteratorDeposit++;
		}
		return -1;
	}

	string getDepositState(int depositNumber, string currentDate) {
		string str = "";
		double proc = 0;
		int amount = 0;
		iteratorDepositInform = depositInform.begin();
		while (iteratorDepositInform != depositInform.end()) {
			if (depositNumber == iteratorDepositInform->getDepositNumber())
			{
				proc = iteratorDepositInform->getDepositRate();
			}
			iteratorDepositInform++;
		}

		iteratorDeposit = deposit.begin();
		while (iteratorDeposit != deposit.end()) {
			if (iteratorDeposit->getDepositNumber() == depositNumber)
			{
				str = "Состояние депозита №"+iteratorDeposit->getDepositNumber();
				if ( iteratorDeposit->getIsOpen()) 
				{
					str+="Открыт "+dateToString(iteratorDeposit->getDateOpen())+"\n";
				}
				else
				{
					str+="Закрыт "+dateToString(iteratorDeposit->getDateClose())+"\n";
				}
				str+="Сумма депозита = "+to_string(iteratorDeposit->getAmount())+" руб.\n";
				amount = iteratorDeposit->getAmount();
				str+="Начисленный процент = "+to_string(iteratorDeposit->getProcent(currentDate, proc, amount))+" руб.\n";
				str+="из них переведено на счет "+to_string(iteratorDeposit->getProcReturning())+" руб.\n";
			}
			iteratorDeposit++;
		}
		return str;
	};

	void returnDepositProc(int depositNumber, string currentDate){
		double proc = 0;
		int amount = 0;
		int procent = 0;
		int clientNumber = 0;

		iteratorDepositInform = depositInform.begin();
		while (iteratorDepositInform != depositInform.end()) {
			if (depositNumber == iteratorDepositInform->getDepositNumber())
			{
				proc = iteratorDepositInform->getDepositRate();
			}
			iteratorDepositInform++;
		}

		iteratorDeposit = deposit.begin();
		while (iteratorDeposit != deposit.end()) {
			if (iteratorDeposit->getDepositNumber() == depositNumber)
			{

				amount = iteratorDeposit->getAmount();
				procent = iteratorDeposit->getProcFromDeposit(currentDate, proc, amount);
				clientNumber = iteratorDeposit->getClientNumber();
			}
			iteratorDeposit++;
		}

		iteratorClientInform = clientInform.begin();
		while (iteratorClientInform != clientInform.end()) {
			if (iteratorClientInform->getClientNumber() == clientNumber)
			{
				iteratorClientInform->addAmount(procent);
			}
			iteratorClientInform++;
		}

	}

	bool closeDeposit(int depositNumber, string currentDate) {
		double rate;
		int age;
		int amount = 0;
		int procent = 0;
		int clientNumber = 0;
		iteratorDepositInform = depositInform.begin();
		while (iteratorDepositInform != depositInform.end()) {
			if (depositNumber == iteratorDepositInform->getDepositNumber())
			{
				rate = iteratorDepositInform->getDepositRate();
				age = iteratorDepositInform->getDepositAge();
			}
			iteratorDepositInform++;
		}

		iteratorDeposit = deposit.begin();
		while (iteratorDeposit != deposit.end()) {
			if (iteratorDeposit->getDepositNumber() == depositNumber)
			{

				amount = iteratorDeposit->getAmount();
				procent = iteratorDeposit->closeDiposit(currentDate, rate, amount, age);
				clientNumber = iteratorDeposit->getClientNumber();
			}
			iteratorDeposit++;
		}

		if (procent < 0)
		{
			return false;
		} else {
			iteratorClientInform = clientInform.begin();
			while (iteratorClientInform != clientInform.end()) {
				if (iteratorClientInform->getClientNumber() == clientNumber)
				{
					iteratorClientInform->addAmount(procent+amount);
				}
				iteratorClientInform++;
			}
			return true;
		}
	}


};



int main() {
	setlocale(LC_ALL, "Russian");
	ProcessingCenter *p = new ProcessingCenter();
	p->addClient("Иванов Иван Иванович","pass1");
	int clientNumber1 = p->getAutorization("Иванов Иван Иванович","pass1");
	if (clientNumber1 > 0) {
		cout<<"Успешная авторизация!\n";
	} else {
		cout<<"Клиент не найден!\n";
	}
	string str = p->getDipositForClient(clientNumber1);
	cout<<str<<"\n";

	p->addAmount(clientNumber1, 10000);

	cout<<p->getAmountClient(clientNumber1)<<"\n";
	str = p->getDipositForClient(clientNumber1);
	cout<<str<<"\n";

	p->addClient("Петров Петр Петрович","pass2");
	int clientNumber2 = p->getAutorization("Петров Петр Петрович","pass2");
	if (clientNumber2 > 0) {
		cout<<"Успешная авторизация!\n";
	} else {
		cout<<"Клиент не найден!\n";
	}

	p->addAmount(clientNumber2, 400000);
	cout<<"На счете "<<p->getAmountClient(clientNumber2)<<" руб.\n";
	str = p->getDipositForClient(clientNumber2);
	cout<<str<<"\n";

	p->addDeposit(clientNumber1,1,3000,"01.01.2017");
	cout<<p->getDepositByClient(clientNumber1)<<"\n";
	cout<<p->getAmountClient(clientNumber1)<<"\n";

	int depositNumber = p->getOpenDiposit(clientNumber1);

	cout<<"Открыт депозит №"<<depositNumber<<"\n";

	cout<<p->getDepositState(depositNumber,"31.03.2017")<<"\n";

	cout<<"На счете "<<p->getAmountClient(clientNumber1)<<" руб.\n";
	p->returnDepositProc(depositNumber,"31.03.2017");
	cout<<p->getDepositState(depositNumber,"31.03.2017")<<"\n";
	cout<<"На счете "<<p->getAmountClient(clientNumber1)<<" руб.\n";

	if (p->closeDeposit(depositNumber,"30.04.2017"))
	{
		cout<<"Депозит закрыт!\n";
	}
	else
	{
		cout<<"Депозит не закрыт!\n";
	}
	cout<<"На счете "<<p->getAmountClient(clientNumber1)<<" руб.\n";
	int c;
	cin>>c;
}