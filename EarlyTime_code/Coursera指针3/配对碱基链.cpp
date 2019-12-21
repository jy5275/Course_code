#include<iostream>
#include<string.h>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
int main() {
	int n, i, j;
	cin >> n; cin.get();
	char bp[256];
	for (i = 0; i < n; i++) {
		cin.getline(bp, 256);
		for (j = 0; bp[j] != '\0'; j++) {
			switch (bp[j])
			{
			case 'A':cout << 'T'; break;
			case 'T':cout << 'A'; break;
			case 'C':cout << 'G'; break;
			case 'G':cout << 'C'; break;
			default:
				break;
			}
		}
		cout << endl;
	}

	return 0;
}