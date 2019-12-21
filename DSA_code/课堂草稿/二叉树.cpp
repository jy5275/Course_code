#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
template<class T>
void Visit(const CNode<T> *n) {
	// visit...
}
template<class T>
class CNode {
	T val;
	CNode<T> *left, *right, *parent;
public:
	CNode();  //�޲ι��캯��
	CNode(const T &val_);
	CNode(const T &val_, CNode<T> *l, CNode<T> *r);
	T value()const { return val; }
	CNode<T> *leftchild()const;    //����������Root
	CNode<T> *rightchild()const;   //����������Root
	void setLeftChild(CNode<T>*);  //����������
	void setRightChild(CNode<T>*); //����������
	void setValue(const T &val);
	bool isLeaf()const;   //�ж��Ƿ�ΪҶ�ڵ�
	CNode<T> &operator=(CNode<T> &CNode);
};
template<class T>
class BinaryTree {
	CNode<T> *root;
public:
	BinaryTree() { root = NULL; }
	~BinaryTree() { DeleteBinaryTree(root); }
	bool isEmpty() const { return(root == NULL) ? true : false; }
	CNode<T> *Root() { return root; }
	CNode<T> *Parent(CNode<T> *rt, CNode<T> *current);
	CNode<T> *LeftSibling(CNode<T> *current);  //����
	CNode<T> *RightSibling(CNode<T> *current); //����
	void CreateTree(const T &val_, BinaryTree<T> &leftTree, BinaryTree<T> &rightTree);
	void PreOrder(CNode<T> *rt);    //��rt��ʼ,ǰ�����������
	void MidOrder(CNode<T> *rt);     //��rt��ʼ,�������������
	void PostOrder(CNode<T> *rt);   //��rt��ʼ,�������������
	void LevelOrder(CNode<T> *rt);  //�������
	void DeleteBinaryTree(CNode<T> *rt) {  //ɾ��rt��ʼ�Ķ�����
		if (rt != NULL) {  //Meaningless for !root
			DeleteBinaryTree(rt->left);
			DeleteBinaryTree(rt->right);
			delete rt;
		}
	}
};
template<class T>            //Search for the parent CNode. O(n),�ݹ�Ѱ�Ҹ��ڵ�
CNode<T> *BinaryTree<T>::Parent(CNode<T> *rt, CNode<T> *current) {
	if (!rt) return NULL;    //Parent return NULL when going to the wrong biforks
	if (rt->leftchild() == curent || rt->rightchild() == current) 
		return rt;
	CNode<T> *p = NULL;
	p = Parent(rt->leftchild(), current);   //Search parent in [rt->left, current]
	if (p) return p;               
	p = Parent(rt->rightchild(), current);  //Search parent in [rt->right, current]
	if (p) return p;
	return NULL;
}
template<class T>          //������ѹջ,��·�½�;��յ�ջ,���ҵ��ա�
void BinaryTree<T>::PreOrder(CNode<T> *root) {  //��root��ʼ����ǰ������
	stack<CNode<T>*> aStack;
	CNode<T> *pointer = root;
	aStack.push(NULL);
	while (pointer) {      //Go on if pointer do not meet stop sign in aStack (NULL)
		Visit(pointer);
		if (pointer->rightchild())           //If RightTree is not empty, push it!
			aStack.push(pointer->rightchild());
		if (pointer->leftchild())            //LeftTree is not empty
			pointer = pointer->leftchild();  //Go on next LeftTree's root!
		else {             //Switch to the last RightTree in stack!
			pointer = aStack.top();           
			aStack.pop();
		}
	}
}
template<class T>          //����ǰѹջ,��������;��ջ����,����������
void BinaryTree<T>::MidOrder(CNode<T> *rt) {  //������������
	stack<CNode<T>*> aStack;        //��Ҫ��ڵ��˼·,���ܾ����ڵ����ڵ���!
	CNode<T> *p= rt;
	while (!aStack.empty() || p) {   //pΪ������Ҫ��ջ��p��ֵ;�����ջҲΪ��,��break��
		if (p) {           //MODE = Default������ǰѹջ,��������
			aStack.push(p);
			p = p->leftchild();   //If leftTree is empty, p set NULL!
		}
		else {             //MODE=�ա�����ջ����,��������
			p = aStack.top();     //P necessarily follows current CNode!
			aStack.pop();  //aStack.top() always remember where to go when leftTree empty
			Visit(p);
			p = p->rightchild();  //If RightTree is empty, p set NULL!
		}
	}
}
enum Tags { Left, Right };    //���鷳�����Ѻ�������
template<class T>
class StackElement {
public:
	CNode<T> *p;
	Tags tag;
	StackElement(CNode<T> *p_, Tags t_) :p(p_), tag(t_) {}
};
template<class T>
void BinaryTree<T>::PostOrder(CNode<T> *rt) {
	stack<StackElement<T>> aStack;            //��Ҫ��ڵ��˼·,���ܾ����ڵ����ڵ���!
	CNode<T> *p = rt;
	while (!aStack.empty() || p) {
		if (p) {          //MODE = ������������p-Lѹջ,����������
			aStack.push(StackElement<T>(p, Left));
			p = p->leftchild();
		}
		else {            //MODE = ��������������ջѹR,����������
			p = aStack.top().p;        //1.Redirect p to the Visiting CNode
			if (aStack.top().tag == Left) {         //p�������������,���ű�������
				aStack.pop();                       //2.pop(p,left)
				aStack.push(StackElement<T>(p, Right));   //3.push(p,right)
				p = p->rightchild();
			}
			else if (aStack.top().tag == Right) {   //p�������������,���ʲ���pΪ����
				aStack.pop();                       //����ջ����,����ȴ���
				Visit(p);                           //3.Visit
				p = NULL;      //��pΪ����,������һѭ���ֻᱻ��ֵΪs.top()
			}
		}
	}
}
template<class T>
void BinaryTree<T>::LevelOrder(CNode<T> *rt) {   //�����������
	while (1) {
		queue<CNode<T>*> aQueue;
		CNode<T> *p = rt;
		if (p) aQueue.push(p);
		while (!aQueue.empty()) {
			p = aQueue.front();
			Visit(p);
			if (p->leftchild()) aQueue.push(p->leftchild());
			if (p->rightchild()) aQueue.push(p->rightchild());
			aQueue.pop();
		}
	}
}
int main() {

	return 0;
}
