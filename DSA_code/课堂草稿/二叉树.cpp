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
	CNode();  //无参构造函数
	CNode(const T &val_);
	CNode(const T &val_, CNode<T> *l, CNode<T> *r);
	T value()const { return val; }
	CNode<T> *leftchild()const;    //返回左子树Root
	CNode<T> *rightchild()const;   //返回右子树Root
	void setLeftChild(CNode<T>*);  //设置左子树
	void setRightChild(CNode<T>*); //设置左子树
	void setValue(const T &val);
	bool isLeaf()const;   //判断是否为叶节点
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
	CNode<T> *LeftSibling(CNode<T> *current);  //左兄
	CNode<T> *RightSibling(CNode<T> *current); //右兄
	void CreateTree(const T &val_, BinaryTree<T> &leftTree, BinaryTree<T> &rightTree);
	void PreOrder(CNode<T> *rt);    //从rt开始,前序遍历二叉树
	void MidOrder(CNode<T> *rt);     //从rt开始,中序遍历二叉树
	void PostOrder(CNode<T> *rt);   //从rt开始,后序遍历二叉树
	void LevelOrder(CNode<T> *rt);  //层次周游
	void DeleteBinaryTree(CNode<T> *rt) {  //删除rt开始的二叉树
		if (rt != NULL) {  //Meaningless for !root
			DeleteBinaryTree(rt->left);
			DeleteBinaryTree(rt->right);
			delete rt;
		}
	}
};
template<class T>            //Search for the parent CNode. O(n),递归寻找父节点
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
template<class T>          //【右子压栈,左路下降;左空弹栈,访右到空】
void BinaryTree<T>::PreOrder(CNode<T> *root) {  //从root开始深搜前序周游
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
template<class T>          //【当前压栈,遍历左树;弹栈访问,遍历右树】
void BinaryTree<T>::MidOrder(CNode<T> *rt) {  //深搜中序周游
	stack<CNode<T>*> aStack;        //需要跨节点的思路,不能局限在单个节点上!
	CNode<T> *p= rt;
	while (!aStack.empty() || p) {   //p为空则需要弹栈给p赋值;但如果栈也为空,就break了
		if (p) {           //MODE = Default——当前压栈,遍历左树
			aStack.push(p);
			p = p->leftchild();   //If leftTree is empty, p set NULL!
		}
		else {             //MODE=空——弹栈访问,遍历右树
			p = aStack.top();     //P necessarily follows current CNode!
			aStack.pop();  //aStack.top() always remember where to go when leftTree empty
			Visit(p);
			p = p->rightchild();  //If RightTree is empty, p set NULL!
		}
	}
}
enum Tags { Left, Right };    //很麻烦的深搜后序周游
template<class T>
class StackElement {
public:
	CNode<T> *p;
	Tags tag;
	StackElement(CNode<T> *p_, Tags t_) :p(p_), tag(t_) {}
};
template<class T>
void BinaryTree<T>::PostOrder(CNode<T> *rt) {
	stack<StackElement<T>> aStack;            //需要跨节点的思路,不能局限在单个节点上!
	CNode<T> *p = rt;
	while (!aStack.empty() || p) {
		if (p) {          //MODE = 有左树——【p-L压栈,遍历左树】
			aStack.push(StackElement<T>(p, Left));
			p = p->leftchild();
		}
		else {            //MODE = 无左树——【弹栈压R,遍历右树】
			p = aStack.top().p;        //1.Redirect p to the Visiting CNode
			if (aStack.top().tag == Left) {         //p的左树遍历完毕,接着遍历右树
				aStack.pop();                       //2.pop(p,left)
				aStack.push(StackElement<T>(p, Right));   //3.push(p,right)
				p = p->rightchild();
			}
			else if (aStack.top().tag == Right) {   //p的右树遍历完毕,访问并置p为咸鱼
				aStack.pop();                       //【弹栈访问,咸鱼等待】
				Visit(p);                           //3.Visit
				p = NULL;      //置p为咸鱼,反正下一循环又会被赋值为s.top()
			}
		}
	}
}
template<class T>
void BinaryTree<T>::LevelOrder(CNode<T> *rt) {   //广搜逐层周游
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
