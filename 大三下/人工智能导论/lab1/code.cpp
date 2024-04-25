#include <bits/stdc++.h>
using namespace std;
typedef pair<int,string> PIS;
string start,target="1238x4765";
int score(string s)
{
	int tol=0;
	for(int i=0;i<9;++i)
	{
		if(s[i]!='x')
		{
			int t=s[i]-'1';
			tol+=abs(i/3-t/3)+abs(i%3-t%3);
		}
	}
	return tol;
}
string bfs(){
	unordered_map<string,int> d;
	priority_queue<PIS,vector<PIS>,greater<PIS>> heap;
	unordered_map<string,pair<string,char>> last;
	
	heap.push({score(start),start});
	char oper[]="udlr";
    int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};

    while(heap.size())
    {
        auto t=heap.top();
        heap.pop();
        string state=t.second;

        if(t.second==target) break;

        int x,y;
        for(int i=0;i<9;i++)
        {
	        if(state[i]=='x')
	        {
	            x=i/3,y=i%3;
	            break;
	        }
    	}

        string init=state;
        for(int i=0;i<4;i++)
        {
            int a=x+dx[i],b=y+dy[i];
            if(a<0||a>=3||b<0||b>=3) continue;
            swap(state[a*3+b],state[x*3+y]);
            if(!d.count(state)||d[state]>d[init]+1)
            {
                d[state]=d[init]+1;
                heap.push({score(state)+d[state],state});
                last[state]={init,oper[i]};
            }
            state=init;
        }
    }
	if(heap.size()==0) return "unsolvable";
    string ans;
    while(target!=start)
    {
        ans+=last[target].second;
        target=last[target].first;
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
int main()
{
	for(int i=0;i<9;++i)
	{
		string s;
		cin>>s;
		start+=s;
	}
	cout<<bfs();
	return 0;
}