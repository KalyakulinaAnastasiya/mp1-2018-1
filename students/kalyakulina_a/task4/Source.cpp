#include <iostream>
#include <string>
#include <fstream>
#include <atltime.h>
using namespace std;

class Watch {
private:
	CTime timeWatch;
	int tempWatch;
public:
	Watch (CTime timeW,  int tempW) {
		timeWatch = timeW;
		tempWatch = tempW;
	}

	string putWatch(){
		return to_string(timeWatch.GetDay())+"."+to_string(timeWatch.GetMonth())+"."+
			to_string(timeWatch.GetYear())+" "+ to_string(timeWatch.GetHour())+":"+
			to_string(timeWatch.GetMinute())+":"+to_string(timeWatch.GetSecond())+" "+
			to_string(tempWatch)+"\n";
	}

	CTime getTimeWatch() {
		return timeWatch;
	}

	int getTempWatch() {
		return tempWatch;
	}

	void setTimeWatch(CTime ctime){
		timeWatch = ctime;
	}

	void setTempWatch(int tempW){
		tempWatch = tempW;
	}

	bool operator==(const Watch & watch) {
		return this->timeWatch == watch.timeWatch;
	}
	bool operator<(const Watch & watch) {
		return this->timeWatch < watch.timeWatch;
	}
	bool operator>(const Watch & watch) {
		return this->timeWatch > watch.timeWatch;
	}
};

class Temperature{
private:
	Watch *masWatch [1000];                                                                          //про второй конструктор!!!!!!
	int line;				//количество строк(заполненых дат) в наблюдении 
	CTime startDate;		//Начальная дата и время измерений

public:
	Temperature(){
		line=0;
		startDate = NULL;
	}

	void AddWatch (CTime timeW, int tempW){
		Watch *w = new Watch ( timeW, tempW);
		masWatch[line] = w;
		line++;
	}

	void AddWatch (string dateStr, int tempW){
		bool pr = true;

		CTime timeW = getCTimeFromString(dateStr);

		for (int i=0;i<line;i++)
		{
			if (timeW  == masWatch[i]->getTimeWatch()) 
			{
				masWatch[i]->setTempWatch(tempW);
				pr = false;
			}
		}
		if (pr)
		{
			AddWatch (timeW, tempW);
		}

	}

	void AddWatchFromString (string watchStr){
		int year, month, day, hh, tempW;
		int mm;
		int ss;
		char *cstr = &watchStr[0u];

		sscanf(cstr, "%d.%d.%d %d:%d:%d %d", &day, &month, &year, &hh, &mm, &ss, &tempW);
		CTime timeW = CTime(year, month, day, hh, mm, ss);
		Watch *w = new Watch ( timeW, tempW);
		masWatch[line] = w;
		line++;
	}


	~Temperature(){
		for (int i=0; i<line; i++) {
			delete masWatch[i];
		}
	}

	void getTemperatureFromFile(string fileName){
		ifstream file(fileName);
		string str;
		while(getline(file, str)){
			cout<<str<<endl;

			AddWatchFromString(str);

		}
		file.close();

	}

	void setTemperatureIntoFile(string fileName){
		ofstream fout(fileName);
		for (int i=0;i<line;i++)
		{
			fout<<masWatch[i]->putWatch();
		}
		fout.close();

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

	int getTempWatch (string dateStr){
		CTime timeW = getCTimeFromString(dateStr);
		int tempW = NULL;
		for (int i=0; i<line;i++)
		{
			if (masWatch[i]->getTimeWatch() == timeW)
			{
				tempW = masWatch[i]->getTempWatch();
			}
		}
		return tempW;
	}

	CTime getFirstWatchDate() {
		return startDate;
	}

	void setFirstWatchDate(string dateStr) {
		startDate = getCTimeFromString(dateStr);
	}

	string dateToString (CTime ctime) {

		return to_string(ctime.GetDay())+"."+to_string(ctime.GetMonth())+"."+to_string(ctime.GetYear())+" "
			+to_string(ctime.GetHour())+":"+to_string(ctime.GetMinute())+":"+to_string(ctime.GetSecond());
	}


	void setSerieWatch(string strSerie[], int size) {
		for (int i=0;i<size;i++)
		{
			AddWatchFromString(strSerie[i]);
		}
	}

	int getAvgTempByDate(string dateStr){
		CTime ctime = getCTimeFromString(dateStr);
		int sumTemp = 0;
		int countTemp = 0;
		int res = 0;
		for (int i=0;i<line;i++)
		{
			if (masWatch[i]->getTimeWatch().GetDay() == ctime.GetDay() &&
				masWatch[i]->getTimeWatch().GetMonth() == ctime.GetMonth() &&
				masWatch[i]->getTimeWatch().GetYear() == ctime.GetYear())
			{
				sumTemp += masWatch[i]->getTempWatch();
				countTemp++;
			}
		}
		if (countTemp != 0)
		{
			res = sumTemp/countTemp;
		}
		return res;
	}

	int getAvgTempByMonth(int monthNumber, int yearNumber){
		int sumTemp = 0;
		int countTemp = 0;
		int res = 0;
		for (int i=0;i<line;i++)
		{
			if (masWatch[i]->getTimeWatch().GetMonth() == monthNumber &&
				masWatch[i]->getTimeWatch().GetYear() == yearNumber)
			{
				sumTemp += masWatch[i]->getTempWatch();
				countTemp++;
			}
		}
		if (countTemp != 0)
		{
			res = sumTemp/countTemp;
		}
		return res;
	}

	int getAvgTempDayByMonth(int monthNumber, int yearNumber){
		int sumTemp = 0;
		int countTemp = 0;
		int res = 0;

		for (int i=0;i<line;i++)
		{
			if (masWatch[i]->getTimeWatch().GetMonth() == monthNumber &&
				masWatch[i]->getTimeWatch().GetYear() == yearNumber &&
				masWatch[i]->getTimeWatch().GetHour() >= 8 &&
				masWatch[i]->getTimeWatch().GetHour() <= 19)
			{
				sumTemp += masWatch[i]->getTempWatch();
				countTemp++;
			}
		}
		if (countTemp != 0)
		{
			res = sumTemp/countTemp;
		}
		return res;
	}

	int getAvgTempNightByMonth(int monthNumber, int yearNumber){
		int sumTemp = 0;
		int countTemp = 0;
		int res = 0;

		for (int i=0;i<line;i++)
		{
			if (masWatch[i]->getTimeWatch().GetMonth() == monthNumber &&
				masWatch[i]->getTimeWatch().GetYear() == yearNumber &&
				(masWatch[i]->getTimeWatch().GetHour() <= 7 ||
				masWatch[i]->getTimeWatch().GetHour() >= 20))
			{
				sumTemp += masWatch[i]->getTempWatch();
				countTemp++;
			}
		}
		if (countTemp != 0)
		{
			res = sumTemp/countTemp;
		}
		return res;
	}

	int getAvgTempByAll(){
		int sumTemp = 0;
		int countTemp = 0;
		int res = 0;
		for (int i=0;i<line;i++)
		{
			sumTemp += masWatch[i]->getTempWatch();
			countTemp++;
		}
		if (countTemp != 0)
		{
			res = sumTemp/countTemp;
		}
		return res;
	}

	void putAll(){
		for (int i=0;i<line;i++){
			cout<<masWatch[i]->putWatch()<<"\n";
		}

	}

};



int main(){

	string serieWatch[] = {"01.01.2018 08:00:00 15",
		"01.01.2018 09:00:00 16",
		"01.01.2018 10:00:00 18",
		"01.01.2018 11:00:00 14",
		"01.01.2018 12:00:00 13",
		"02.01.2018 13:00:00 12",
		"03.01.2018 01:00:00 10"};

	Temperature *s=new Temperature();

	setlocale(LC_ALL, "Russian");
	// Установить начальную дату наблюдений
	cout<<"Установить начальную дату и время наблюдений: \n";
	cout<<"--------------------------------------------- \n";
	s->setFirstWatchDate("31.12.2017 14:00:00");
	// Узнать начальную дату наблюдений
	string str = s->dateToString(s->getFirstWatchDate());
	cout<<"Начальная дата наблюдений - <<str"<<"\n";
	// Добавить наблюдение
	cout<<"Добавить наблюдение: \n";
	cout<<"-------------------- \n";
	s->AddWatch("01.01.2018 13:00:00", 14);
	s->putAll();
	// Узнать температуру в выбранном наблюдении
	cout<<"Узнать температуру в выбранном наблюдении: \n";
	cout<<"------------------------------------------ \n";
	int tempW = s->getTempWatch("01.01.2018 12:00:00");
	if (tempW != NULL)
	{
		cout<<" Температура = "<<tempW<<"\n";
	} else {
		cout<<"Нет такого измерения\n";
	}
	// Задать серию наблюдений
	cout<<"Задать серию наблюдений: \n";
	cout<<"------------------------ \n";
	s->setSerieWatch(serieWatch, 7);
	s->putAll();
	// Получить среднюю температуру за день
	cout<<"Получить среднюю температуру за день: \n";
	cout<<"------------------------------------- \n";
	tempW = s->getAvgTempByDate("01.01.2018");
	printf(" Средняя температура = %d\n", tempW);
	// Получить среднюю температуру за месяц
	cout<<"Получить среднюю температуру за месяц: \n";
	cout<<"-------------------------------------- \n";
	tempW = s->getAvgTempByMonth(1,2018);
	printf(" Средняя температура = %d\n", tempW);
	// Получить среднюю температуру за всю историю
	cout<<"Получить среднюю температуру за всю историю: \n";
	cout<<"-------------------------------------------- \n";
	tempW = s->getAvgTempByAll();
	printf(" Средняя температура = %d\n", tempW);
	// Получить среднюю дневную температуру за месяц
	cout<<"Получить среднюю дневную температуру за месяц: \n";
	cout<<"-------------------------------------- \n";
	tempW = s->getAvgTempDayByMonth(1,2018);
	printf(" Средняя температура = %d\n", tempW);
	// Получить среднюю ночную температуру за месяц
	cout<<"Получить среднюю ночную температуру за месяц: \n";
	cout<<"-------------------------------------- \n";
	tempW = s->getAvgTempNightByMonth(1,2018);
	printf(" Средняя температура = %d", tempW);

	// Сохранение наблюдений в файл
	cout<<"Сохранение наблюдений в файл: \n";
	cout<<"----------------------------- \n";
	s->setTemperatureIntoFile("TemperatureOut.txt");
	// Загрузка наблюдений из файла
	cout<<"Загрузка наблюдений из файла: \n";
	cout<<"----------------------------- \n";
	s->getTemperatureFromFile("Temperature.txt");
	s->putAll();

	int c;
	cin>>c;
}