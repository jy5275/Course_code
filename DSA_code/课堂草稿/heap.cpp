#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
template<class T>
class MinHeap {
public:
	T * heapArray;   //����������
	int CurrentSize, MaxSize;
	void BuildHeapDown();
	void BuildHeapUp();
public:
	MinHeap(const int MaxSize_);
	virtual ~MinHeap() { delete[]heapArray; }
	bool isLeaf(int pos)const;
	int leftchild(int pos)const;
	int rightchild(int pos)const;
	int Parent(int pos) const;
	bool Remove(int pos, T &node);  //ɾ�������±�Ԫ��
	bool Insert(const T &newNode);  //������Ԫ��
	T &RemoveMin();                 //ɾ����Сֵ(�Ѷ�)
	void SiftUp(int position);      //���ϵ���
	void SiftDown(int left);        //ɸѡ��
};
template<class T>
MinHeap<T>::MinHeap(const int MaxSize_) {
	CurrentSize = 0;
	MaxSize = MaxSize_;
	heapArray = new T[MaxSize];
	for (int i = 0; i < MaxSize; i++) {
		heapArray[i] = rand();
	}
	CurrentSize = MaxSize;
	BuildHeapDown();     //���ֽ��ѷ���������
}
template<class T>
void MinHeap<T>::BuildHeapUp() {     //�ӵ����ϵ�������С��
	for (int i = CurrentSize / 2 - 1; i >= 0; i--)
		SiftDown(i);
}
template<class T>
void MinHeap<T>::BuildHeapDown() {     //�������µ�������С��
	for (int i = 0; i < CurrentSize; i++)
		SiftUp(i);
}
template<class T>
bool MinHeap<T>::isLeaf(int pos)const {   //�ж��Ƿ�ΪҶ�ӽ��
	return (pos >= CurrentSize / 2) && (pos < CurrentSize);
}
template<class T>
int MinHeap<T>::leftchild(int pos)const { return 2 * pos + 1; }
template<class T>
int MinHeap<T>::rightchild(int pos)const { return 2 * pos + 2; }
template<class T>
int MinHeap<T>::Parent(int pos)const { return (pos - 1) / 2; }

//--SiftDown---���µ����ɶѣ���*p���¡�����,ֱ�� max(*left, *right) > *p----
template<class T>
void MinHeap<T>::SiftDown(int position) {
	int i = position, down = 2 * i + 1;   //iָ��ǰ���,downָ��i->left
	T temp = heapArray[i];    //������Ԫ��
	while (down < CurrentSize) {
		if ((down < CurrentSize - 1) && (heapArray[down + 1] < heapArray[down]))
			down++;                 // down = left < right ? left : right;
		if (heapArray[down] < heapArray[i]) {  // if (*down < *i)
			heapArray[i] = heapArray[down];    // *i = *down
			i = down; down = 2 * i + 1;
		}
		else break;      //����downȫ������i,˵��temp���Ƶ��ʵ�λ��!
	}
	heapArray[i] = temp;
}
//-----SiftUp---���ϵ����ɶѣ���*p���ϡ�����,ֱ�� *parent < *p---------------
template<class T>
void MinHeap<T>::SiftUp(int position) {   //
	int i = position, parent = Parent(position);
	T temp = heapArray[i];        // ����*i
	while ((heapArray[parent] > temp) && (i > 0)) {   //���*Parent��Щ
		heapArray[i] = heapArray[parent];             // *i = *Parent
		i = Parent(i);            //��ʱû��Ҫ*parent = *i,���滹�ỻ
		parent = Parent(i);
	}
	heapArray[i] = temp;
}
//-----------Insert:����Ԫ��,�Ȳ�����ĩCurrentSize,��SiftUp-------------
template<class T>
bool MinHeap<T>::Insert(const T &newNode) {
	if (CurrentSize >= MaxSize) return false;
	heapArray[CurrentSize] = newNode;  //newNode�����������
	SiftUp(CurrentSize++);   //��CurrentSize��Ԫ�������͵��ô��ĵط�
	return true;
}
//-----------RemoveMin:�Ƴ���Сֵ,��ĩ������,��SiftDown--------------
template<class T>
T &MinHeap<T>::RemoveMin() {
	if (CurrentSize <= 0) exit(1);    //�ն�
	T temp = heapArray[0];
	heapArray[0] = heapArray[--CurrentSize];
	SiftDown(0);
	return temp;    //����ɾ�����Ǹ�Ԫ��?
}
//-----Remove:ɾ��posλ�õ�Ԫ��,���䷵�ص�node----------------------
template<class T>
bool MinHeap<T>::Remove(int pos, T &node) {
	if ((pos < 0) || (pos >= CurrentSize)) return false;
	T temp = heapArray[pos];
	heapArray[pos] = heapArray[--CurrentSize];  //ĩβ��Ԫ��������
	SiftUp(pos);
	SiftDown(pos);
	node = temp;
	return true;
}
MinHeap<int> h(100);

bool Test(int t) {
	bool leftOK, rightOK;
	if (2 * t + 1 < h.CurrentSize)
		leftOK = Test(h.leftchild(t));
	else leftOK = true;
	if (2 * t + 2 < h.CurrentSize)
		rightOK = Test(h.rightchild(t));
	else rightOK = true;
	return leftOK && rightOK;
}
int main() {
	cout << Test(0) << endl;
	delete[]h.heapArray;
	return 0;
}