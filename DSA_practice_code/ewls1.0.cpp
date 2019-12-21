//修改了那个i=i之后，确定性算法+EWLS 153分
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstdio>
#include<cstdlib>
#include <set>
#include <vector>
#include<cstring>
#include <algorithm>
#include <cmath>
#include<bitset>
using namespace std;
#define MAXN 760
#define MAXE 250001
#define INF 100000000

using namespace std;
int N, M;
const int MAX = 760;
int GG[MAX][MAX], tmax = 0;
bitset<MAX> inClique;
vector<int> curClique, tans;
bool pushOK(int x, vector<int> &v) {
	int size = v.size();
	for (int i = 0; i < size; i++)
		if (!GG[v[i]][x])return false;
	return true;
}
void Dfs(int l, int temp) {
	if (l == N + 1) {		//到达最深层！回溯！
		if (temp > tmax) {		//尝试更新tmax与tans
			tmax = temp;
			tans = curClique;
		}
		return;
	}
	if (temp + (N - l) + 1 < tmax)return;
	if (pushOK(l, curClique)) {		//l可以入团！
		curClique.push_back(l);		//入团试试
		Dfs(l + 1, temp + 1);		//继续搜
		curClique.pop_back();		//l结点出团,试试不含l的团有多大
	}
	Dfs(l + 1, temp);
}
void init() {
	tans.clear();
	curClique.clear();
	tmax = 0;
	memset(GG, 0, sizeof(GG));
}


struct Edge
{
	int s, e, w, a;//a是age，最后一次加入到L的step数，初始时为0,a只对L中的边有意义，每次有一条边加入L时，会更新a
	Edge(int s_, int e_) : s(s_), e(e_), w(1), a(0) {}
	Edge() {}
};

struct mycmp
{
	bool operator()(const Edge* _Left, const Edge* _Right) const
	{	// apply operator> to operands
		if (_Left->a == _Right->a)
		{
			if (_Left->s == _Right->s)
			{
				return _Left->e<_Right->e;
			}
			return _Left->s<_Right->s;
		}
		return (_Left->a < _Right->a);
	}
};

int rG[MAXN][MAXN];
vector<int> G[MAXN];
int dscore[MAXN];
Edge E[MAXN][MAXN];//存放边的数组，维护w和a
set<int> C, CC;
int mysize;

set<Edge*, mycmp> L, UL;//L和UL是存指向E中元素的指针的set
bool ninC[MAXN];//n是否在C里的bool数组
bool ninCC[MAXN];
int ub;
int out[MAXN];

void Init(int delta)
{
	int maxdscore = 0, choosepoint;
	//先初始化一遍dscore
	for (int i = 1; i <= N; i++)
	{
		dscore[i] = G[i].size();
		if (maxdscore < dscore[i])
		{
			maxdscore = dscore[i];
			choosepoint = i;
		}
	}
	//贪心找点覆盖
	while (!L.empty())
	{
		C.insert(choosepoint);
		ninC[choosepoint] = true;
		ninCC[choosepoint] = true;
		mysize = G[choosepoint].size();
		for (int i = 0; i < mysize; i++)
		{
			if (!ninC[G[choosepoint][i]] && E[choosepoint][G[choosepoint][i]].s>0)//
			{
				Edge* deledge;
				if (choosepoint < G[choosepoint][i])
					deledge = E[choosepoint] + G[choosepoint][i];
				else
					deledge = E[G[choosepoint][i]] + choosepoint;
				L.erase(deledge);
			}
		}
		//维护dscore
		maxdscore = -INF;
		for (int i = 1; i <= N; i++)
		{
			if (!ninC[i])
			{
				dscore[i] = 0;
				mysize = G[i].size();
				for (int j = 0; j < mysize; j++)
				{
					if (!ninC[G[i][j]] && E[i][G[i][j]].s>0)
						dscore[i]++;
				}
				if (maxdscore < dscore[i])
				{
					maxdscore = dscore[i];
					choosepoint = i;
				}
			}
		}
	}
	ub = C.size();
	CC = C;
	maxdscore = -INF;
	//开始删C中的点，删delta个
	if (delta >= C.size() / 5)
		delta = C.size() / 5;//?
	for (int o = 0; o < delta; o++)
	{
		maxdscore = -INF;
		set<int>::iterator i = C.begin();
		while (i != C.end())
		{
			dscore[*i] = 0;
			mysize = G[*i].size();
			for (int j = 0; j < mysize; j++)
			{
				if (!ninC[G[*i][j]] && E[*i][G[*i][j]].s>0)
					dscore[*i]--;
			}
			if (maxdscore < dscore[*i])
			{
				maxdscore = dscore[*i];
				choosepoint = *i;
			}
			++i;
		}
		ninC[choosepoint] = false;
		C.erase(choosepoint);
		//处理删掉的点的关联边，维护L和UL
		mysize = G[choosepoint].size();
		for (int i = 0; i < mysize; i++)
		{
			if (!ninC[G[choosepoint][i]] && E[choosepoint][G[choosepoint][i]].s>0)
			{
				Edge *addedge;
				if (choosepoint < G[choosepoint][i])
					addedge = E[choosepoint] + G[choosepoint][i];
				else
					addedge = E[G[choosepoint][i]] + choosepoint;
				L.insert(addedge);
				UL.insert(addedge);
			}
		}
	}
	//结束之后再计算一遍dscore
	for (int i = 1; i <= N; i++)
	{
		dscore[i] = 0;
		if (ninC[i])
		{
			mysize = G[i].size();
			for (int j = 0; j < mysize; j++)
			{
				if (!ninC[G[i][j]] && E[i][G[i][j]].s>0)
					dscore[i]--;
			}
		}
		else
		{
			mysize = G[i].size();
			for (int j = 0; j < mysize; j++)
			{
				if (!ninC[G[i][j]] && E[i][G[i][j]].s>0)
					dscore[i]++;
			}
		}
	}
}

pair<int, int> ChooseExchangePair()
{
	int u = 0, v = 0;
	set<Edge*>::iterator edge = L.begin();
	if (edge == L.end())
		return pair<int, int>(0, 0);
	int v1 = (*edge)->s;
	int v2 = (*edge)->e;
	set<int>::iterator i = C.begin();
	while (i != C.end())//此处不是随机可以吗，会倾向于选择C中小的点？
	{
		int p = *i;
		int score = dscore[p] + dscore[v1];
		if (E[p][v1].s>0)//p和score之间存在边
		{
			score += E[p][v1].w;
		}
		if (score>0)
			return pair<int, int>(p, v1);
		score = dscore[p] + dscore[v2];
		if (E[p][v2].s>0)//p和score之间存在边
		{
			score += E[p][v2].w;
		}
		if (score>0)
			return pair<int, int>(p, v2);
		++i;
	}
	//遍历UL
	set<Edge*>::iterator uledge = UL.begin();
	while (uledge != UL.end())
	{
		v1 = (*uledge)->s;
		v2 = (*uledge)->e;
		set<int>::iterator i = C.begin();
		while (i != C.end())//此处不是随机可以吗，会倾向于选择C中小的点？
		{
			int p = *i;
			int score = dscore[p] + dscore[v1];
			if (E[p][v1].s>0)//p和score之间存在边
			{
				score += E[p][v1].w;
			}
			if (score>0)
				return pair<int, int>(p, v1);
			score = dscore[p] + dscore[v2];
			if (E[p][v2].s>0)//p和score之间存在边
			{
				score += E[p][v2].w;
			}
			if (score>0)
				return pair<int, int>(p, v2);
			++i;
		}
		++uledge;
	}
	return pair<int, int>(0, 0);
}

void EWLS(int delta, int maxstep)
{
	int step = 0;
	Init(delta);
	while (step++ < maxstep)
	{
		pair<int, int> changepair = ChooseExchangePair();
		int u = changepair.first;
		int v = changepair.second;
		if (u>0 && v>0)
		{
			//先从L和UL中删除边(C中加入v点)
			ninC[v] = true;
			C.insert(v);
			mysize = G[v].size();
			for (int i = 0; i < mysize; i++)
			{
				if (!ninC[G[v][i]] && E[v][G[v][i]].s>0)
				{
					Edge* deledge;
					if (v < G[v][i])
						deledge = E[v] + G[v][i];
					else
						deledge = E[G[v][i]] + v;
					L.erase(deledge);
					UL.erase(deledge);
				}
			}
			ninC[u] = false;//C中删除u点
			C.erase(u);
			//再在L中加入边，并且要维护边的age，注意新变成没覆盖的边是不会被加入UL的
			mysize = G[u].size();
			for (int i = 0; i <mysize; i++)
			{
				if (!ninC[G[u][i]] && E[u][G[u][i]].s>0)
				{
					Edge* addedge;
					E[u][G[u][i]].a = step;
					E[G[u][i]][u].a = step;
					if (u < G[u][i])
						addedge = E[u] + G[u][i];
					else
						addedge = E[G[u][i]] + u;
					L.insert(addedge);
				}
			}
			//更新dscore
			for (int i = 1; i <= N; i++)
			{
				dscore[i] = 0;
				if (ninC[i])
				{
					mysize = G[i].size();
					for (int j = 0; j<mysize; j++)
					{
						if (!ninC[G[i][j]] && E[i][G[i][j]].s>0)
						{
							dscore[i] -= E[i][G[i][j]].w;
						}
					}
				}
				else
				{
					mysize = G[i].size();
					for (int j = 0; j<mysize; j++)
					{
						if (!ninC[G[i][j]] && E[i][G[i][j]].s>0)
						{
							dscore[i] += E[i][G[i][j]].w;
						}
					}
				}
			}
		}
		else//到达局部最优
		{
			set<Edge*> ::iterator p = L.begin();
			while (p != L.end())
			{
				(*p)->w++;//更新w
				E[(*p)->e][(*p)->s].w++;
				++p;
			}
			int randout = rand() % C.size();
			int randin = rand() % (N - C.size());
			bool myflag1 = true, myflag2 = true;
			for (int i = 1; i <= N && (myflag1 || myflag2); i++)
			{
				if (ninC[i])
					randout--;
				else
					randin--;
				if (randout<0 && myflag1)
				{
					u = i;
					myflag1 = false;
				}
				if (randin<0 && myflag2)
				{
					v = i;
					myflag2 = false;
				}
			}
			ninC[v] = true;
			C.insert(v);
			mysize = G[v].size();
			for (int i = 0; i < mysize; i++)
			{
				if (!ninC[G[v][i]] && E[v][G[v][i]].s>0)
				{
					Edge* deledge;
					if (v < G[v][i])
						deledge = E[v] + G[v][i];
					else
						deledge = E[G[v][i]] + v;
					L.erase(deledge);
				}
			}
			ninC[u] = false;//C中删除u点
			C.erase(u);
			mysize = G[u].size();
			for (int i = 0; i < mysize; i++)
			{
				if (!ninC[G[u][i]] && E[u][G[u][i]].s>0)
				{
					Edge* addedge;
					E[u][G[u][i]].a = step;
					E[G[u][i]][u].a = step;
					if (u < G[u][i])
						addedge = E[u] + G[u][i];
					else
						addedge = E[G[u][i]] + u;
					L.insert(addedge);
				}
			}
			UL = L;//重构UL
				   //更新dscore
			for (int i = 1; i <= N; i++)
			{
				dscore[i] = 0;
				if (ninC[i])
				{
					mysize = G[i].size();
					for (int j = 0; j<mysize; j++)
					{
						if (!ninC[G[i][j]] && E[i][G[i][j]].s>0)
						{
							dscore[i] -= E[i][G[i][j]].w;
						}
					}
				}
				else
				{
					mysize = G[i].size();
					for (int j = 0; j<mysize; j++)
					{
						if (!ninC[G[i][j]] && E[i][G[i][j]].s>0)
						{
							dscore[i] += E[i][G[i][j]].w;
						}
					}
				}
			}
		}
		if (int(C.size() + L.size())<ub)
		{
			ub = C.size() + L.size();
			if (L.empty())
			{
				CC = C;
			}
			else
			{
				CC = C;
				for (int i = 1; i <= N; i++)
					if (ninC[i])
						ninCC[i] = true;
					else
						ninCC[i] = false;
				int choosepoint;
				int maxdscore;
				//贪心找点覆盖
				set<Edge*, mycmp> L_ = L;
				while (!L_.empty())
				{
					maxdscore = -INF;
					for (int i = 1; i <= N; i++)
					{
						if (!ninCC[i])
						{
							dscore[i] = 0;
							mysize = G[i].size();
							for (int j = 0; j < mysize; j++)
							{
								if (!ninCC[G[i][j]] && E[i][G[i][j]].s>0)
									dscore[i] += E[i][G[i][j]].w;
							}
							if (maxdscore < dscore[i])
							{
								maxdscore = dscore[i];
								choosepoint = i;
							}
						}
					}
					CC.insert(choosepoint);
					ninCC[choosepoint] = true;
					mysize = G[choosepoint].size();
					for (int i = 0; i < mysize; i++)
					{
						if (!ninCC[G[choosepoint][i]] && E[choosepoint][G[choosepoint][i]].s>0)//
						{
							Edge* deledge;
							if (choosepoint < G[choosepoint][i])
								deledge = E[choosepoint] + G[choosepoint][i];
							else
								deledge = E[G[choosepoint][i]] + choosepoint;
							L_.erase(deledge);
						}
					}
				}
				maxdscore = -INF;
				//开始删C中的点，删delta个
				if (delta>C.size() / 5)
					delta = C.size() / 5;
				for (int o = 0; o < delta; o++)
				{
					maxdscore = -INF;
					set<int>::iterator i = C.begin();
					while (i != C.end())
					{
						dscore[*i] = 0;
						mysize = G[*i].size();
						for (int j = 0; j < mysize; j++)
						{
							if (!ninC[G[*i][j]] && E[*i][G[*i][j]].s>0)
								dscore[*i] -= E[*i][G[*i][j]].w;
						}
						if (maxdscore < dscore[*i])
						{
							maxdscore = dscore[*i];
							choosepoint = *i;
						}
						++i;
					}
					ninC[choosepoint] = false;
					C.erase(choosepoint);
					//处理删掉的点的关联边，维护L
					mysize = G[choosepoint].size();
					for (int i = 0; i < mysize; i++)
					{
						if (!ninC[G[choosepoint][i]] && E[choosepoint][G[choosepoint][i]].s>0)
						{
							E[choosepoint][G[choosepoint][i]].a = step;
							E[G[choosepoint][i]][choosepoint].a = step;
							Edge *addedge;
							if (choosepoint < G[choosepoint][i])
								addedge = E[choosepoint] + G[choosepoint][i];
							else
								addedge = E[G[choosepoint][i]] + choosepoint;
							L.insert(addedge);
						}
					}
				}
			}
		}
	}
}

int main() {
	int numcount = 0;
	while (scanf("%d %d", &N, &M) != EOF) {
		if (N <= 500) {
			init();
			while (M--) {
				int u, v;
				scanf("%d%d", &u, &v);
				GG[u][v]++;
				GG[v][u]++;
			}
			if (N <= 600)
				Dfs(1, 0);
			printf("%d\n", tmax);
			for (int i = 0; i < tans.size(); i++)
				printf("%d ", tans[i]);
			printf("\n");
		}
		else {
			int u, v;
			for (int i = 0; i <= N; i++)
				for (int j = i + 1; j <= N; j++)
					E[i][j] = Edge(-1, -1);
			C.clear(); CC.clear();
			L.clear(); UL.clear();
			for (int i = 1; i <= N; i++) {
				G[i].clear();
				ninC[i] = false;
				ninCC[i] = false;
			}
			memset(rG, 0, sizeof(rG));
			memset(out, 0, sizeof(out));
			for (int i = 0; i < M; i++) {
				scanf("%d%d", &u, &v);
				rG[u][v] = 1;
				rG[v][u] = 1;
			}
			for (u = 1; u <= N; u++)
				for (v = u + 1; v <= N; v++)
					if (!rG[u][v]) {
						G[u].push_back(v);
						G[v].push_back(u);
						E[u][v] = Edge(u, v);
						E[v][u] = Edge(v, u);
						L.insert(E[u] + v);
					}
			M = (N*(N - 1)) / 2 - M;
			int delta = N / 100;
			double rat = N / 750;
			int maxstep = 700000 * rat;
			EWLS(delta, maxstep);
			set<int> ::iterator p = CC.begin();
			while (p != CC.end()) {
				out[*p] = 1;
				++p;
			}
			printf("%d\n", N - CC.size());
			for (int i = 1; i <= N; i++)
				if (out[i] == 0)
					printf("%d ", i);
			printf("\n");
		}
	}
	return 0;
}