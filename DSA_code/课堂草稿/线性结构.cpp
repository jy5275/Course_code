#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<vector>
#include<list>
#include<bitset>
#include<string>
#include<cstring>
#include<cmath>
#include<memory>
#include<stdexcept>
#include<time.h>
#include<algorithm>
#include<iomanip>
#include<fstream>
using namespace std;
template<class T>
class List {   //线性结构抽象类
public:
	int size;
	void clear() = 0;
	bool isEmpty() = 0;
	bool append(const T value) = 0;
	bool insert(const int p, const T value) = 0; //位置p上增加一个元素
	bool MyDelete(const int p) = 0;
	bool getValue(const int p, T &value) = 0;    //按i取value
	bool setValue(const int p, const T v_) = 0;  //按i修改value
	bool getPos(int &i, const T value) = 0;      //按value找p
};
//---------------------------------顺序表---------------------------------------
template<class T>
class arrList :public List<T> {
	T *aList;
	int maxSize, position;
public:
	arrList(const int ms_) { aList = new T[size_]; maxSize = ms_; size = position = 0; }
	~arrList() { delete[]aList; }
	void clear() { size = 0; delete[]aList; position = 0; aList = new T[maxSize]; }
	int length() { return size; }
	bool append(const T value);
	void insert_sorted(const T value);
	bool insert(const int p, const T value);
	bool MyDelete(const int p);
	bool setValue(const int p, const T value);
	bool getValue(const int p, T &value);
	bool getPos(int &p, const T value);
	bool unique_sorted();
	void reverse();
};
//------------------------------------------------------------------------------
template<class T>
bool arrList<T>::MyDelete(const int p) {    //删去p位置的元素
	if (p < 0 || p >= size) {
		cerr << "Illegal delete!" << endl;
		return false;
	}
	for (int i = p; i <= size - 2; i++)   //p后挨个前移一格
		aList[i] = aList[i + 1];
	size--;
	return true;
}
template<class T>
void arrList<T>::unique_sorted() {
	int i = 1;
	while (i < size) {
		if (aList[i] == aList[i - 1])
			MyDelete(i);
		else i++
	}
}
template<class T>
void MySwap(T *t1, T *t2) {
	T tmp = *t1;
	*t1 = *t2;
	*t2 = tmp;
}
template<class T>
void arrList<T>::reverse() {
	int p = 0, q = size - 1;
	while (1) {
		if (p >= q)break;
		MySwap(aList + p, aList + q);
		p++; q--;
	}
}
template<class T>
bool arrList<T>::getPos(int &p, const T value) {    //顺序表::查找某元素位置
	for (int i = 0; i < size; i++) {
		if (aList[i] == value) {
			p = i;
			return true;
		}
	}
	return false;
}
template<class T>
void arrList<T>::insert_sorted(const T value) {  //sorted顺序表::插入value元素
	int p = 0;
	while (aList[p] > value) p++;
	for (int i = size; i > p; i--)
		aList[i] = aList[i - 1];
	aList[p] = value;
	size++;
	return true;
}
template<class T>
bool arrList<T>::insert(const int p, const T value) {  //顺序表::在p处插元素
	if (p<0 || p>size || size >= maxSize) {
		cerr << "Illegal insertion!" << endl;
		return false;
	}
	for (int i = size; i > p; i--)    //挨个后移一格
		aList[i] = aList[i - 1];
	aList[p] = value;
	size++;
	return true;
}
//blabla其它函数太简单懒得写啦~

//-------------------------链表-------------------------------------------------
template<class T>
class Link {    //链节类！
public:
	T data;
	Link<T> *next, *prev;
	Link(const T data_, const Link<T> *next_ = NULL, const Link<T> *prev_ = NULL) :
		data(data_), next(next_), prev(prev_) {}
	Link(const Link<T> *next_ = NULL, const Link<T> *prev_ = NULL) :
		next(next_), prev(prev_) {}
};
template<class T>
class lnkList :public List<T> {   //链表类！
	Link<T> *head, *tail;
public:
	Link<T> *setPos(const int i); //寻找第i个结点
	lnkList();
	~lnkList();
	void clear();
	bool isEmpty();
	bool append(const T value);
	bool insert(const int i, const T value); //位置p上增加一个元素
	bool MyDelete(const int i);
	bool getValue(const int i, T &value);    //按i取value
	bool setValue(const int i, const T v_);  //按i修改value
	bool getPos(int &i, const T value);      //按value找p
};
//------------------------------------------------------------------------------
template<class T>
void lnkList<T>::clear() {
	while (size > 0)
		MyDelete(0);
	if (size > 0)cerr << "Not cleared!" << endl;
}
template<class T>
bool lnkList<T>::isEmpty() {
	return !size;
}
template<class T>
bool lnkList<T>::append(const T value) {    //把某元素挂上去
	Link<T> *q = new Link<T>(value, tail->prev, tail);
	tail->prev->next = q;
	tail->prev = q;
	size++;
	return true;
}
template<class T>
bool lnkList<T>::getValue(const int i, T &value) {   //获取某节点值
	Link<T> *p = setPos(i);
	if (p == tail || p == head || p == NULL) {
		cerr << "Illegal query!" << endl;
		return false;
	}
	value = p->data;
	return true;
}
template<class T>
bool lnkList<T>::setValue(const int i, const T v_) {  //修改某节点值
	Link<T> *p = setPos(i);
	if (p == tail || p == head || p == NULL) {
		cerr << "Illegal edit!" << endl;
		return false;
	}
	p->data = v_;
	return true;
}
template<class T>
Link<T> *lnkList<T>::setPos(const int i) {  //返回第i个结点的指针
	int cnt = 0;                            //i>=n返回tail
	if (i < 0)return head;                  //负数返回head
	Link<T> *p = head->next;
	while (p != tail && cnt < i) {
		p = p->next;
		cnt++;
	}
	return p;
}
template<class T>
lnkList<T>::lnkList() {   //创建新链表,不需任何参数
	head = new Link<T>();
	tail = new Link<T>(NULL, head);
	head->next = tail;    //next/head与各自绑定的Link<T>同生死共命运
	size = 0;
}
template<class T>
lnkList<T>::~lnkList() {  //析构该链表
	Link<T> *tmp;
	while (head != NULL) {  //从头往后删
		tmp = head;
		head = head->next;
		delete tmp;
	}
}
template<class T>
bool lnkList<T>::getPos(int &i, const T value) {  //查找某元素位置
	Link<T> *p = head->next;
	int No = 0;
	while (p != tail) {
		if (p->data == T) {  //找到了！
			i = No;
			return true;
		}
		No++;
		p++;
	}
	return false;  //找不到！
}
//------------------------------------------------------------------------
template<class T>
bool lnkList<T>::insert(const int i, const T value) {  //双向链表中插入元素
	if (i > size || i < 0) {     //插入位置最小为0(接头),最大为size(续尾)
		cerr << "Illegal insert!" << endl;
		return false;
	}
	Link<T> *p = setPos(i - 1);  //负数返回head,i>=size返回tail
	size++;
	Link<T> *q = new Link<T>(value, p, p->next);
	p->next->prev = q;
	p->next = q;
	return true;
}
template<class T>
bool lnkList<T>::MyDelete(const int i) {  //双向链表中删除元素
	if (i > size || i < 0) {     //delete位置最小为0(砍头),最大为size-1(去尾)
		cerr << "Illegal insert!" << endl;
		return false;
	}
	Link<T> *p = setPos(i);
	size--;
	p->next->prev = p->prev;
	p->prev->next = p->next;
	delete p;
	return true;
}
//----------------------栈-------stack------------------------------------------------
template<class T>
class Stack {
public:
	void clear();
	bool push(const T item);
	bool pop(T &item);
	T &top() = 0;
	bool isEmpty() = 0;
	bool isFull() = 0;
};
//---------------------顺序栈:用向量实现-----------------------------------------------
template<class T>
class arrStack :public Stack<T> {
	int mSize, top;    //栈中最多有mSize个元素,top是栈顶位置
	T *st;             //存放栈元素的ptr
public:
	arrStack(int s_) :mSize(s_) {
		st = new T[mSize];
		top = -1;
	}
	arrStack() { top = -1; }  //创建空栈
	~arrStack() { delete[]st; }
	bool isFull() { return top == mSize - 1; }
	void clear() { top = -1; }
	bool push(const T item) {
		if (top == mSize - 1) {
			cerr << "Stack Overflow!" << endl;
			return false;
		}
		st[++top] = item;
		return true;
	}
	bool pop() {
		if (top == -1) { cerr << "Empty Stack!" << endl; return false; }
		top--;
		return ture;
	}
	T &top() {
		if (top == -1) { cerr << "Empty Stack!" << endl; return 0; }
		return st[top];
	}
};
//------------------链式栈---------------------------------------------------------
template<class T>
class lnkStack :public Stack<T> {
	Link<T> *top;
	int size;
public:
	lnkStack() { top = NULL; size = 0; }
	~lnkStack() { clear(); }
	void push(const T item) {
		Link<T> *tmp = new Link<T>(item, top);
		top = tmp;
		size++;
	}
	void pop() {
		if (size == 0) { cerr << "Empty Stack!" << endl; return; }
		Link<T> *tmp = top;
		top = top->next;
		size--;
		delete tmp;
	}
	T &top() {
		if (size == 0) { cerr << "Empty Stack!" << endl; return 0; }
		return top->data;
	}
	void clear() {
		while (top != NULL)
			pop();
	}
};
//=============================顺序队列====================
template<class T>
class Queue {
public:
	void clear();
	bool push(const T item);
	bool pop(T &item);
	T &back();
	bool isEmpty();
	bool isFull;
};
template<class T>
class arrQueue :public Queue<T> {
	int maxSize, front, rear;
	T *qu;    //存放元素
public:
	arrQueue(int size_) :maxSize(size_ + 1) {
		qu = new T[maxSize];   
		front = rear = 0;
	}
	~arrQueue() { delete[]qu; }
	void clear() { front = rear = 0; }  //省去"= 0"???
	bool push(const T item) {
		if (((rear + 1) % maxSize) == front) {   //再加一个就追上front了！ 
			cerr << "Queue Overflow!" << endl;
			return false;
		}
		qu[rear] = item;
		rear = (rear + 1) % maxSize;
		return true;
	}
	bool pop() {
		if (rear == front) {   //前胸贴后背,无法pop出来
			cerr << "Queue Empty!" << endl;
			return false;
		}
		front = (front + 1) % maxSize;
		return ture;
	}
	T &front() {
		if (rear == front) {   //前胸贴后背,无法front出来
			cerr << "Queue Empty!" << endl;
			return 0;
		}
		return qu[front];
	}
};
template<class T>
class lnkQueue :public Queue<T> {
	int size;
	Link<T> *front, *rear;
public:
	lnkQueue() :size(0), front(NULL), rear(NULL) {}
	~lnkQueue() { clear; }
	void clear() {
		while (front != NULL) {
			rear = front;
			front = front->next;
			delete rear;
		}
	}
};
//-------------------------------------------------------------------------------------
class String {
	int size;   //size是真实字符个数,不算'\0'
	char *str;
public:
	String() {}
	String(char *s) {
		size = strlen(s);
		str = new char[size + 1];
		strcpy(str, s);
	}
	String substr(int pos, int n) {
		int left = size - pos, i = 0; //最多只能提取left个字符,不算'\0'
		if (pos >= size) return NULL;
		if (n > left) n = left;   //最多只能拷贝n个字符
		String tmp;
		delete[]tmp.str;
		tmp.str = new char[n + 1];
		char *p = tmp.str, *q = &str[pos];
		while (i++ < n) *p++ = *q++;
		*p = '\0';
		tmp.size = n;
		return tmp;
	}
};
int main() {
	
	return 0;
}
