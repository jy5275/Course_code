#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stack>
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
int goalStatus;           //目标状态
bitset<362880> Flags;      //判重比特位
const int MAXS = 400000;  
char result[MAXS];
class CNode {
public:
	int father, status;  //status状态,即this排列的编号
	char move;           //father到本节点的移动方式 u/d/r/l
	CNode(int s_, int f_, char m_) :status(s_), father(f_), move(m_) {
		Flags.set(status);
	}
	CNode() {}
}myQueue[MAXS]; //为什么不能用queue?
int qHead, qTail;
char sz4Moves[] = "udrl";
int factorial[10];  //存放0~9的阶乘,不用每次都算一遍,需要时直取即可,gw用的unsigned int？
int getPermutationNumForInt(int perInt[], int len) {  
	//算perInt里放着的这个关于整数0~len-1的排列是第几个排列
	int num = 0;
	bool used[21];
	memset(used, 0, sizeof(bool)*len);
	for (int i = 0; i < len; ++i) {
		int n = 0;
		for (int j = 0; j < perInt[i]; j++) {
			if (!used[j]) n++;
		}
		num = num + n * factorial[len - i - 1];
		used[perInt[i]] = true;
	}
	return num;
}
template<class T>
int getPermutationNum(T s1, T s2, int len) {
	//给定排列求序号,[s2,s2+len)是要求序号的排列
	int *perInt = new int[len];   //转换成[0,len-1]的整数排列
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (*(s2 + i) == *(s1 + j)) {
				perInt[i] = j; break;
			}
		}
	}
	int num = getPermutationNumForInt(perInt, len); delete[]perInt;
	return num;
}
template<class T>
void genPermutationByNum(T s1, T s2, int len, int No) {
	//[s1,s1+len)放着0号排列,排列中的各元素都不一样
	//函数里可放各种东西,int/char/自定义对象等,只要给出0号排列与No,就能求出No号排列
	int perInt[21];  //要转换成[0,len-1]的整数的排列,作为结果
	bool used[21];
	memset(used, 0, sizeof(bool)*len);
	for (int i = 0; i < len; i++) {
		int tmp; int n = 0; int j;
		for (j = 0; j < len; j++) {
			if (!used[j]) {
				if (factorial[len - i - 1] >= No + 1)break;
				else No -= factorial[len - i - 1];
			}
		}
		perInt[i] = j;
		used[j] = true;
	}
	for (int i = 0; i < len; i++)
		*(s2 + i) = *(s1 + perInt[i]);
}
int strStatusToIntStatus(const char *strStatus) {  
	//把char[]形式的状态转换为int形式的状态(排列序号)
	return getPermutationNum("012345678", strStatus, 9);
}
void IntStatusToStrStatus(int n, char *strStatus) {
	//把int形式的状态转为char[]形式的状态,即求n号排列
	genPermutationByNum((char*)"012345678", strStatus, 9, n);
}
int NewStatus(int nStatus, char cMove) {
	//求nStatus经过cMove移动后得到的新状态(int形式).若移动不了则返回-1
	char szTmp[20];
	int nZeroPos;  //记录空格的位置
	IntStatusToStrStatus(nStatus, szTmp); //已转为char[]状态,存放在szTmp中了
	for (int i = 0; i < 9; i++) {
		if (szTmp[i] == '0') {
			nZeroPos = i; break;
		}
	}
	switch(cMove) {
	case 'u':if (nZeroPos - 3 < 0) return -1;    //已经在第一行！不能上移！
			 else {
				 szTmp[nZeroPos] = szTmp[nZeroPos - 3];  //把上一行数字下移
				 szTmp[nZeroPos - 3] = '0';              //原位置清空
			 }break;
	case 'd':if (nZeroPos + 3 > 8) return -1;    //已经在第三行！不能下移！
			 else {                              //可以下移！
				 szTmp[nZeroPos] = szTmp[nZeroPos + 3];  //把下边行数字上移
				 szTmp[nZeroPos + 3] = '0';              //原位置清空
			 }break;
	case 'l':if (nZeroPos % 3 == 0) return -1;   //已经在最左列！不能左移！
			 else {
				 szTmp[nZeroPos] = szTmp[nZeroPos - 1];  //把左列数字右移
				 szTmp[nZeroPos - 1] = '0';              //原位置清空
			 }break;
	case 'r':if (nZeroPos % 3 == 2) return -1;   //已经在最右列！不能右移！
			 else {
				 szTmp[nZeroPos] = szTmp[nZeroPos + 1];  //把右列数字左移
				 szTmp[nZeroPos + 1] = '0';              //原位置清空
			 }break;
	}
	return strStatusToIntStatus(szTmp);
}
bool Bfs(int nStatus) {   //核心函数！寻找从nStatus状态到目标的路径
	int nNewStatus;
	Flags.reset();
	qHead = 0; qTail = 1; //队尾指针指向最后一个元素后边
	myQueue[qHead] = CNode(nStatus, -1, 0);  
	while (qHead != qTail) {  //只要队非空,就能继续
		nStatus = myQueue[qHead].status;         //1.取出front
		if (nStatus == goalStatus) return true;  //2.判定目标状态
		for (int i = 0; i < 4; i++) {            //3.扩展新节点(遍历所有方向)
			nNewStatus = NewStatus(nStatus, sz4Moves[i]);//3.1确定临时新节点参数
			if (nNewStatus == -1) continue;      //3.2判断扩展条件
			if (Flags[nNewStatus]) continue;     //3.3判重
			Flags.set(nNewStatus);               //3.4更新判重bitset(改进后省去)
			myQueue[qTail++] = CNode(nNewStatus, qHead, sz4Moves[i]); //3.5压入！
		}
		qHead++;  //4.弹出首元素,移动首指针,相当于弹出首元素了
	}
	return false; //5.设置失败输出
}
int main() {
	factorial[0] = factorial[1] = 1;
	for (int i = 2; i <= 9; i++)
		factorial[i] = i * factorial[i - 1];   //动规获取阶乘库
	goalStatus = strStatusToIntStatus("123456780");  //这是咱们的goal,转为int
	char szLine[50], szLine2[20];
	while (cin.getline(szLine, 48)) {
		//先要将输入字符串转变成数字字符串
		int i, j;
		for (i = 0, j = 0; szLine[i]; i++) {
			if (szLine[i] != ' ') {
				if (szLine[i] == 'x') szLine2[j++] = '0';
				else szLine2[j++] = szLine[i];
			}
		}
		if (Bfs(strStatusToIntStatus(szLine2))) {
			int nMoves = 0, nPos = qHead;
			while (nPos) {   //nPos=0时已经退回初始状态了
				result[nMoves++] = myQueue[nPos].move; //result里边倒序存放步骤
				nPos = myQueue[nPos].father;   //通过father直接寻访上个节点,有趣！
				//"1.判断临时目标状态"已通过直接下表寻访father来完成
				//nPos的移动自动完成"2.弹出首元素"
			}
			for (int i = nMoves - 1; i >= 0; i--) cout << result[i]; //倒序输出移动步骤
		}
		else cout << "unsolvable" << endl;
	}
	clock_t startTime = clock();

	clock_t endTime = clock();
	cout<< "程序段运行时间:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}