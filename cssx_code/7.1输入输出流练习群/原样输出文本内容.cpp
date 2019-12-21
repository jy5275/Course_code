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
	while ((c = cin.get()) != EOF)	//方法一:重定向stdin后用cin.get()逐字读取 
			cout.put(c);
	
	cout<<"---------------------"<<endl; 
	
	ifstream src1("copy.txt",ios::in); 
	while ((c = src1.get()) != EOF)	//方法二:创建新ifstream类对象,逐字读取 
		cout.put(c);
	
	cout<<"---------------------"<<endl; 
	
	ifstream src2("copy.txt",ios::in);
	while (src2.getline(buffer, LEN))	//方法三:创建新ifstream类对象,逐行读取 
	    cout<<buffer<<endl;
	    
	src2.close();
	src1.close();
	return 0;
}
