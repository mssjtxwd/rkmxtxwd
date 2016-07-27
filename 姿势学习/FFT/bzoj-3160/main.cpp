#include<bits/stdc++.h>
using namespace std; 
typedef long long LL;
const int MOD = 1000000007;
template <typename T> int arrange(vector<T>& a){
    int n=a.size();
    for(int i=1,x=0,y=0;i<=n;i++){
        if(x>y) swap(a[x],a[y]);
        x^=i&-i;
        y^=n/(i&-i)>>1;
    }
    return n;
}
class FFT { // 快速傅里叶变换
public:
    typedef complex<double> complex_num;
    void fourier(vector<complex_num>& a, int o){ // 数组长度n必须是2的幂
        int n=arrange(a); // o是变换方向，+1为时域->频域，-1为频域->时域
        const double PI=acos(-1);
        for(int m=1;m<n;m+=m){
            complex_num w=1,e(cos(PI/m),sin(PI/m)*o);
            for(int x=0;x<n;w=1,x+=m+m)
            for(int y=0;y<m;y++,w*=e){
                complex_num t=w*a[x+y+m];
                a[x+y+m]=a[x+y]-t;
                a[x+y]+=t;
            }
        }
        if(o<0) for(int i=0;i<n;i++) a[i]/=n;
    }
    vector<int> convolution(const vector<int>& a, const vector<int>& b){
        int n=a.size(),m=b.size();
        int s=1<<(32-__builtin_clz(n+m-2)); // n+m必须大于等于2
        vector<complex_num> u(s),v(s);
        for(int i=0;i<n;i++) u[i]=a[i];
        for(int i=0;i<m;i++) v[i]=b[i];
        fourier(u,+1);
        fourier(v,+1);
        for(int i=0;i<s;i++) u[i]*=v[i];
        fourier(u,-1);
        vector<int> w(n+m-1);
        for(int i=0;i<n+m-1;i++) w[i]=int(u[i].real()+0.5);
        return w;
    }
} F;
vector<int> a,b,c;
LL manacher(const char* s, int n){
    vector<int> u(n+n-1,1); // u[i]表示以i/2为圆心的最长回文子串的直径
    for(int i=1,x=0;i<n+n-1;i++){ // 比如字符串babbaa，看作b.a.b.b.a.a
        u[i]=max(x+u[x]-i,1-i%2); // 相应位置的直径长度就是10301410121
        if(x+x>=i) u[i]=min(u[i],u[x+x-i]);
        int a=(i-1-u[i])>>1,b=(i+1+u[i])>>1;
        while(a>=0 && b<n && s[a]==s[b]) a--,b++,u[i]+=2;
        if(i+u[i]>x+u[x]) x=i;
    }
    LL ret = 0;
    for (int i=0;i<u.size();i++) {
    	int x = u[i];
    	ret+=(x + 1) / 2;
    	if (ret >= MOD) ret-=MOD;
    }
    return ret;
}
char s[200005];
int two[200005];
int u[200005]; 
int main()
{
	two[0] = 1;
	for (int i=1;i<=200000;i++) {
		two[i] = two[i-1] + two[i-1];
		if (two[i] >= MOD) two[i] -= MOD;
	}
	freopen("1.in","r",stdin);
	scanf("%s",s);
	int n = strlen(s);
	LL ans = 0;
	memset(u,0,sizeof u);
	for (char ch='a';ch<='b';ch++) {
		a.clear();
		b.clear();
		for (int i=0;i<n;i++) {
			a.push_back(s[i]==ch ? 1:0);
			b.push_back(a[i]);
		}
		//cout<<"a: "; for (int x:a) cout<<x<<' ';cout<<endl;
	//	cout<<"b: "; for (int x:b) cout<<x<<' ';cout<<endl;
		c = F.convolution(a,b);
	//	cout<<"after FFT:"<<endl;
		for (int i=0;i<c.size();i++) {
			int x = c[i];
			if (i % 2 == 0 && a[i/2]==1 && b[i/2]==1) {
				x/=2;
				x++;
			}
			else x/=2;
			u[i]+=x;
		}
	}
//	for (int i=0;i<c.size();i++) cout<<u[i]<<' ';cout<<endl;
	for (int i=0;i<c.size();i++) {
		ans = ans + two[u[i]] - 1;
		if (ans >= MOD) ans -= MOD;
		if (ans < 0) ans += MOD;	
	}
	//cout<<ans<<endl;
	LL d = manacher(s,n) % MOD;
//	cout<<d<<endl;
	ans -= d; ans %= MOD;
	if (ans < 0) ans += MOD;
	printf("%lld\n",ans);
}
