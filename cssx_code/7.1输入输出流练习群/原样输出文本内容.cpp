#include<iostream>
#include<ostream>
#include<string.h>
#include<string>
#include<cstring>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
const int LEN=1000;
int main() {
	char c, buffer[LEN];
	freopen("copy.txt","r",stdin);
	while ((c = cin.get()) != EOF)	//����һ:�ض���stdin����cin.get()���ֶ�ȡ 
			cout.put(c);
	
	cout<<"---------------------"<<endl; 
	
	ifstream src1("copy.txt",ios::in); 
	while ((c = src1.get()) != EOF)	//������:������ifstream�����,���ֶ�ȡ 
		cout.put(c);
	
	cout<<"---------------------"<<endl; 
	
	ifstream src2("copy.txt",ios::in);
	while (src2.getline(buffer, LEN))	//������:������ifstream�����,���ж�ȡ 
	    cout<<buffer<<endl;
	    
	src2.close();
	src1.close();
	return 0;
}
