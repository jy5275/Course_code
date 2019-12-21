#include<iostream>  
using namespace std;
bool rn(int y) {
	if (y == 2000 || y == 2400 || y == 2800) return 1;
	if (y % 4 != 0 || y % 400 == 0) return 0;
	return 1;
}
int main(){
	int day, cal[9999][13] = { 0 };
	int year, month;
	for (year = 2018; year <= 9999; year++) {
		for (month = 1; month <= 12; month++) {
			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) cal[year][month] = 31;
			else if (month == 2) cal[year][month] = 28;
			else cal[year][month] = 30;
		}
		if (rn(year)) cal[year][2] = 29;
	}
	while (cin >> day) {
		day = day + 1;
		int flag = 0;
		for (year = 2018; year <= 9999; year++) {
			for (month = 1; month <= 12; month++) {
				if (day <= cal[year][month]) {
					cout << year << "-" << month << "-" << day << endl;
					flag = 1; break;
				}
				day = day - cal[year][month];
			}
			if (flag == 1)break;
		}
	}

	return 0;
}
