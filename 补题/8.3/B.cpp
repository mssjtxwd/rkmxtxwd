#include<bits/stdc++.h>
using namespace std;
const int MAXN = 500005,LOG = 19,MOD = 1000000007;
int n,f[MAXN][LOG],dep[MAXN];
vector<int> Map[MAXN];
int st[MAXN],ed[MAXN],tot;
typedef long long LL;
void init()
{
	for (int i=1;i<=LOG;i++) {
		for (int j=0;j<n;j++) {
			f[j][i] = f[f[j][i-1]][i-1];
		}
	}
}
int lcm(int x,int y) {
	int i;
	if (dep[x] < dep[y]) swap(x,y);
	for (i=0;(1<<i)<=dep[x];i++);
	i--;
	for (int j=i;j>=0;j--)
		if (dep[x] - (1<<j) >= dep[y]) x = f[x][j];
	if (x == y) return x;
	for (int j=i;j>=0;j--) {
		if (f[x][j] != -1 && f[x][j]!=f[y][j]) {
			x = f[x][j];
			y = f[y][j];
		}
	}
	return f[x][0];
}
void dfs(int u,int p) {
	f[u][0] = p;
	st[u] = tot++;
	for (int v:Map[u]) {
		if (v == p) continue;
		dep[v] = dep[u] + 1;
		dfs(v,u);
	}
	ed[u] = tot++;
}
class BList {
public:
	int bsz,bct;
	int v[1000005];
	int l[1005],r[1005],mk[1005];
	void set(int n) {
		bsz = (int)sqrt(n) + 1;
		bct = n % bsz == 0 ? n / bsz : n / bsz + 1;
		for (int i=0;i<bct;i++) {
			l[i] = bsz * i;
			r[i] = min(l[i] + bsz - 1,n - 1);
			mk[i] = 0;
		}
	}
	void modify(int x,int y) {
		int idx = x / bsz;
		v[x] += y;
		if (v[x] >= MOD) v[x] -= MOD;
		mk[idx] += y;
		if (mk[idx] >= MOD) mk[idx] -= MOD;
	}
	LL getval(int x) {
		int idx = x / bsz;
		int tmp = 0;
		for (int i=0;i<idx;i++) {
			tmp += mk[i];
			if (tmp >= MOD) tmp -= MOD;
		}
		for (int i=l[idx];i<=x;i++) {
			tmp += v[i];
			if (tmp >= MOD) tmp -= MOD;
		}
		//cout<<"getval:"<<x<<' '<<tmp<<endl;
		return (LL)tmp;
	}
} B;
int main()
{
	//freopen("001.in","r",stdin);
	//int n;
	scanf("%d",&n);
	B.set(n);
	for (int i=1;i<n;i++) {
		#define pb push_back
		int x,y;
		scanf("%d%d",&x,&y);
		Map[x].pb(y);
		Map[y].pb(x);
	}
	dfs(0,0);
	init();
	for (int i=0;i<n;i++) {
		int x;
		scanf("%d",&x);
		B.modify(st[i],x);
		B.modify(ed[i],-x);	
	}
	int q;
	scanf("%d",&q);
	while (q--)
	{
		int k,x,y,a,b,c,d,u,v;
		scanf("%d%d%d%d%d%d%d%d%d",&k,&x,&y,&a,&b,&c,&d,&u,&v);
		for (int i=1;i<=k;i++) {
			B.modify(st[x],y);
			B.modify(ed[x],-y);
			x = (a * x + b);
			if (x>=n) x %= n;
			y = (c * y + d);
			if (y>=MOD) y%=MOD;
			//for (int j=0;j<2*n;j++) cout<<B.v[j]<<' ';cout<<endl;
		}
		int l = lcm(u,v);
		LL ans = B.getval(st[u]) - B.getval(st[l]) + B.getval(st[v]) - B.getval(st[l]) + B.v[l];
		if (ans < 0) ans += MOD;
		printf("%lld\n",ans);
	}
	
} 
