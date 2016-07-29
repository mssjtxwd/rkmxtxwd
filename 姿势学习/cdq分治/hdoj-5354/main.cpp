#include<bits/stdc++.h>
#pragma comment(linker, "/STACK:102400000,102400000")
#define pb push_back
#define mk make_pair
using namespace std;
const int MAXN = 200005;
int ans[MAXN];
vector<int> Map[MAXN];
int size[MAXN],color[MAXN];
typedef pair<int,int> PII;
typedef pair<PII,int> PI3;
stack<PI3> S;
int f[MAXN],n,m;
PII gf(int u)
{
	int c = 0;
	for (;f[u]!=u;u=f[u]) c ^= color[u];
	c ^= color[u];
	return mk(u,c);
}
void undo(int tot)
{
	//cout<<"undo:"<<tot<<endl;
	for (int i=0;i<tot;i++)
	{
		auto tmp = S.top();
		auto x = tmp.first;
		auto col = tmp.second;
		S.pop();
		size[x.first] -= size[x.second];
		color[x.second] = col;
		f[x.second] = x.second;
	}
}
bool merge(int u,int v)
{
	auto x = gf(u);
	auto y = gf(v);
	//cout<<"merge:"<<u<<' '<<v<<endl;
	if (x.first == y.first) {
		if (x.second == y.second) return true;
		return false;
	}
	if (size[x.first] < size[y.first]) {
	//	cout<<"swap:"<<x.first<<' '<<y.first;//<<endl;
		swap(x,y);
	//	cout<<"=>"<<x.first<<' '<<y.first<<endl;
	}
	size[x.first] += size[y.first];
	int tmp = color[y.first];
	if ((x.second == y.second)) color[y.first] ^= 1;
	f[y.first] = x.first;
	S.push(mk(mk(x.first,y.first),tmp));
	//for (int i=1;i<=n;i++) cout<<f[i]<<' ';cout<<endl;
	//for (int i=1;i<=n;i++) cout<<color[i]<<' ';cout<<endl;
	return false;
}

void solve(int l,int r){
	if (l == r) {
		ans[l] = 1;
		//cout<<"solve:"<<l<<' '<<r<<endl;
		return;
	}
	int mid = (l+r)/2;
	//[l,mid]
	int tot = 0;
	bool flag = false;
	for (int i=mid+1;i<=r;i++) {
		for (int v:Map[i])
			if (v<l || v>mid) {
				flag = merge(i,v);
				tot++;
				if (flag) {
					for (int j=l;j<=mid;j++) ans[j] = 0;
					goto end1;
				}
			}
	}
	solve(l,mid);
	end1:
	undo(tot);
	tot = 0; flag = false;
	for (int i=l;i<=mid;i++) {
		for (int v:Map[i])
			if (v<mid+1 || v>r) {
				flag = merge(i,v);
				tot++;
				if (flag) {
					for (int j=mid+1;j<=r;j++) ans[j] = 0;
					goto end2;
				}
			}
	}
	solve(mid+1,r);
	end2:
	undo(tot);
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	int T;
	scanf("%d",&T);
	while (T--)
	{
		//int n,m;
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) {
			Map[i].clear();
			f[i] = i;
			size[i] = 1;
		}
		for (int i=0;i<m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			Map[x].pb(y);
			Map[y].pb(x);
		}
		//memset(ans,0,sizeof ans);
		solve(1,n);
		for (int i=1;i<=n;i++) printf("%d",ans[i]); printf("\n");
	}
}
