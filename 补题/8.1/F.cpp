#include<bits/stdc++.h>
using namespace std;
int a[1005],b[1005];
int f[1005][1005];
int dp(int i,int j)
{
	//cout<<i<<' '<<j<<endl;
	if (f[i][j] > 0) return f[i][j];
	if (f[i][j] == -1) return 0;
	f[i][j] = -1;
	if (dp(a[i],a[j]) == 1) return f[i][j] = 1;
	if (dp(b[i],b[j]) == 1) return f[i][j] = 1;
	return f[i][j] = 2;
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	int T;
	scanf("%d",&T);
	while (T--)
	{
		int k,n;
		scanf("%d%d",&k,&n);
		for (int i=1;i<=n;i++) scanf("%d",a+i);
		for (int i=1;i<=n;i++) scanf("%d",b+i);	
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++) f[i][j] = i==j ? 1:0;
		
		bool ans = true;
		for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				if (f[i][j] == 0) {
					f[i][j] = dp(i,j);
					if (f[i][j] == 2) {
						ans = false;
						goto end;
					}
				}
		end:
		if (ans) printf("Yes\n");
		else printf("No\n");
	}
} 
