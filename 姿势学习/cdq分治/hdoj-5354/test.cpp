#include<bits/stdc++.h>
#pragma comment(linker, "/STACK:102400000,102400000")
#define pb push_back
#define mk make_pair
using namespace std;
const int MAXN = 200005;
vector<int> Map[MAXN];
int size[MAXN],color[MAXN];
typedef pair<int,int> PII;
stack<PII> S;
int f[MAXN],n,m;
PII gf(int u)
{
	int c = 0;
	for (;f[u]!=u;u=f[u]) c ^= color[u];
	c ^= color[u];
	return mk(u,c);
}
bool merge(int u,int v)
{
	auto x = gf(u);
	auto y = gf(v);
	//cout<<"merge:"<<u<<' '<<v<<endl;
	if (x.first == y.first) {
		if (x.second == y.second) return true;
	}
	if (size[x.first] < size[y.first]) {
	//	cout<<"swap:"<<x.first<<' '<<y.first;//<<endl;
		swap(x,y);
	//	cout<<"=>"<<x.first<<' '<<y.first<<endl;
	}
	size[x.first] += size[y.first];
	if ((x.second + y.second + 1) % 2 == 1)color[y.first] ^= 1;
	f[y.first] = x.first;
	S.push(mk(x.first,y.first));
	//for (int i=1;i<=n;i++) cout<<f[i]<<' ';cout<<endl;
	//for (int i=1;i<=n;i++) cout<<color[i]<<' ';cout<<endl;
	return false;
}
vector<PII> E;
int main()
{
	freopen("1.in","r",stdin);
	freopen("1_.out","w",stdout);
	int T;
	scanf("%d",&T);
	while (T--)
	{
		//int n,m;
		scanf("%d%d",&n,&m);
		E.clear();
		for (int i=0;i<m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			E.pb(mk(x,y));
		}
		for (int i=1;i<=n;i++)
		{
			for (int j=1;j<=n;j++) {
				f[j] = j;
				size[j] = 1; 
				color[j] = 0;
			}
			while (!S.empty()) S.pop();
			bool flag = false;
			for (auto e:E) {
				if (e.first == i || e.second == i) continue;
				flag = merge(e.first,e.second);
				if (flag) break;
			}
			printf("%d",flag?0:1);
		}
		printf("\n");
	}
} 
