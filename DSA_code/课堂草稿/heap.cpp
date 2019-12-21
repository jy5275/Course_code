#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
template<class T>
class MinHeap {
public:
	T * heapArray;   //存放这个数组
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
	bool Remove(int pos, T &node);  //删除给定下标元素
	bool Insert(const T &newNode);  //插入新元素
	T &RemoveMin();                 //删除最小值(堆顶)
	void SiftUp(int position);      //向上调整
	void SiftDown(int left);        //筛选法
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
	BuildHeapDown();     //两种建堆方法都可以
}
template<class T>
void MinHeap<T>::BuildHeapUp() {     //从底往上调整成最小堆
	for (int i = CurrentSize / 2 - 1; i >= 0; i--)
		SiftDown(i);
}
template<class T>
void MinHeap<T>::BuildHeapDown() {     //从上向下调整成最小堆
	for (int i = 0; i < CurrentSize; i++)
		SiftUp(i);
}
template<class T>
bool MinHeap<T>::isLeaf(int pos)const {   //判断是否为叶子结点
	return (pos >= CurrentSize / 2) && (pos < CurrentSize);
}
template<class T>
int MinHeap<T>::leftchild(int pos)const { return 2 * pos + 1; }
template<class T>
int MinHeap<T>::rightchild(int pos)const { return 2 * pos + 2; }
template<class T>
int MinHeap<T>::Parent(int pos)const { return (pos - 1) / 2; }

//--SiftDown---向下调整成堆：把*p向【下】调整,直到 max(*left, *right) > *p----
template<class T>
void MinHeap<T>::SiftDown(int position) {
	int i = position, down = 2 * i + 1;   //i指向当前结点,down指向i->left
	T temp = heapArray[i];    //待下移元素
	while (down < CurrentSize) {
		if ((down < CurrentSize - 1) && (heapArray[down + 1] < heapArray[down]))
			down++;                 // down = left < right ? left : right;
		if (heapArray[down] < heapArray[i]) {  // if (*down < *i)
			heapArray[i] = heapArray[down];    // *i = *down
			i = down; down = 2 * i + 1;
		}
		else break;      //左右down全都大于i,说明temp已移到适当位置!
	}
	heapArray[i] = temp;
}
//-----SiftUp---向上调整成堆：把*p向【上】调整,直到 *parent < *p---------------
template<class T>
void MinHeap<T>::SiftUp(int position) {   //
	int i = position, parent = Parent(position);
	T temp = heapArray[i];        // 缓存*i
	while ((heapArray[parent] > temp) && (i > 0)) {   //如果*Parent大些
		heapArray[i] = heapArray[parent];             // *i = *Parent
		i = Parent(i);            //暂时没必要*parent = *i,后面还会换
		parent = Parent(i);
	}
	heapArray[i] = temp;
}
//-----------Insert:插入元素,先插在最末CurrentSize,再SiftUp-------------
template<class T>
bool MinHeap<T>::Insert(const T &newNode) {
	if (CurrentSize >= MaxSize) return false;
	heapArray[CurrentSize] = newNode;  //newNode加在数组最后
	SiftUp(CurrentSize++);   //把CurrentSize号元素往上送到该呆的地方
	return true;
}
//-----------RemoveMin:移除最小值,最末移上来,再SiftDown--------------
template<class T>
T &MinHeap<T>::RemoveMin() {
	if (CurrentSize <= 0) exit(1);    //空堆
	T temp = heapArray[0];
	heapArray[0] = heapArray[--CurrentSize];
	SiftDown(0);
	return temp;    //返回删除的那个元素?
}
//-----Remove:删除pos位置的元素,将其返回到node----------------------
template<class T>
bool MinHeap<T>::Remove(int pos, T &node) {
	if ((pos < 0) || (pos >= CurrentSize)) return false;
	T temp = heapArray[pos];
	heapArray[pos] = heapArray[--CurrentSize];  //末尾的元素移上来
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