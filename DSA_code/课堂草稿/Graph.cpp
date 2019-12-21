#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<list>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;
class Edge {
public:
	int from, to, weight;
	Edge() { from = -1; to = -1; weight = 0; }
	Edge(int f_, int t_, int w_) :from(f_), to(t_), weight(w_) { }
	bool operator<(Edge o) { return weight < o.weight; }
};
class Graph {
public:
	int numVertex, numEdge, *Mark, *indegree;
	Graph(int numVert_) :numVertex(numVert_), numEdge(0) {
		indegree = new int[numVertex];   //记录结点i的degree在indegree[i]里边
		Mark = new int[numVertex];
		for (int i = 0; i < numVertex; i++) {
			Mark[i] = 0; indegree[i] = 0;
		}
	}
	~Graph() { delete[] Mark; delete[] indegree; }
	int VerticesNum() { return numVertex; }
	int EdgesNum() { return numEdge; }
	virtual Edge FirstEdge(int oneVertex) = 0; //返回与顶点oneVertex相关联的1st边
	virtual Edge NextEdge(Edge preEdge) = 0; //返回与边preEdge有相同关联顶点oneVertex的next边
	virtual void setEdge(int f_, int t_, int w_) = 0;   //添加一条边
	virtual void delEdge(int f_, int t_) = 0;           //删一条边
	
	bool IsEdge(Edge oneEdge) {
		return oneEdge.weight > 0 && oneEdge.weight < INFINITY && oneEdge.to >= 0;
	}
	int FromVertex(Edge oneEdge) { return oneEdge.from; }
	int ToVertex(Edge oneEdge) { return oneEdge.to; }
	int Weight(Edge oneEdge) { return oneEdge.weight; }
};

//===========================邻接矩阵Graph=======Begin==================================
class Graphm :public Graph {    // 邻接矩阵中Edge对象并不实体存在,只在传参时生成,
	int **matrix;               // ..真正保存Graph信息的是matrix(int**)
public:
	Graphm(int numVert_) :Graph(numVert_) {  
		matrix = new int*[numVertex];    //matrix中numVertex个元素都是int*型的
		for (int i = 0; i < numVertex; i++) matrix[i] = new int[numVertex];
		for (int i = 0; i < numVertex; i++) {
			for (int j = 0; j < numVertex; j++) matrix[i][j] = 0;
		}
	}
	Edge FirstEdge(int oneVertex) {     //返回与顶点oneVertex相关联的第一条边
		Edge myEdge;
		myEdge.from = oneVertex; myEdge.to = -1;
		for (int i = 0; i < numVertex; i++) {
			if (matrix[oneVertex][i] != 0) {
				myEdge.to = i; myEdge.weight = matrix[oneVertex][i]; 
				break;
			}
		}
		return myEdge;
	}
	Edge NextEdge(Edge preEdge) {    //返回与边preEdge有相同关联顶点oneVertex的next边
		Edge myEdge;
		myEdge.from = preEdge.from; myEdge.to = -1;
		for (int i = preEdge.to + 1; i < numVertex; i++) {
			if (matrix[preEdge.from][i] != 0) {    // <from, i> exist in the Graph
				myEdge.to = i;
				myEdge.weight = matrix[myEdge.from][i];
				break;
			}
		}
		return myEdge;
	}
	void setEdge(int from, int to, int weight) {   //添加一条边
		if (matrix[from][to] <= 0) {
			numEdge++; indegree[to]++;
		}
		matrix[from][to] = weight;
	}
	void delEdge(int from, int to) {    //删一条边
		if (matrix[from][to] > 0) {
			numEdge--; indegree[to]--;
		}
		matrix[from][to] = 0;
	}
};
//===========================邻接表Graph=======Begin=================================
class listUnit {
public:
	int vertex, weight;
};
template<class Elem>
class CLink {
public:
	Elem element;     //这儿的Elem就是listUnit
	CLink *pNext = NULL;
	CLink(const Elem &e_, CLink *p_ = NULL) :element(e_), pNext(p_) {}
	CLink(CLink *p_ = NULL) :pNext(p_) {}
};
template<class Elem>
class CList {         //一条CList就是一个Vertex,每个CLink就是一条边
public:
	CLink<Elem> *head = NULL;
	CList() { head = new CLink<Elem>(); }
	void removeall() {
		CLink<Elem> *fence = NULL;
		while (head != NULL) {
			fence = head; head = head->pNext; delete fence;
		}
	}
	~CList() { removeall(); }
};
class Graphl :public Graph {
	CList<listUnit> *graList;    //一个图就是一个数组,基类型是CList<listUnit>*
public:
	Graphl(int numVert_) :Graph(numVert_) {
		graList = new CList<listUnit>[numVertex];
	}
	~Graphl() { delete[]graList; }
	Edge FirstEdge(int oneVertex) {
		Edge myEdge;
		myEdge.from = oneVertex; myEdge.to = -1;
		CLink<listUnit> *temp = graList[oneVertex].head;  //oneV号结点对应oneV号链表
		if (temp != NULL) {
			myEdge.to = temp->element.vertex;
			myEdge.weight = temp->element.weight;
		}
		return myEdge;
	}
	Edge NextEdge(Edge preEdge) {
		Edge myEdge;
		myEdge.from = preEdge.from; myEdge.to = -1;
		CLink<listUnit> *temp = graList[preEdge.from].head;
		while (temp && temp->element.vertex <= preEdge.to) temp = temp->pNext;
		if (temp) {
			myEdge.to = temp->element.vertex;
			myEdge.weight = temp->element.weight;
		}
		return myEdge;
	}
	void setEdge(int from, int to, int weight) {

	}
	void delEdge(int from, int to) {

	}
};
int main() {
	return 0;
}