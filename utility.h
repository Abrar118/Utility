#include<bits/stdc++.h>
const in modv=1e9+7;
typedef long long in;
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//returns first occurence, -1 if not found
in bin_search(vector<in>a,in k)
{
    in m,op=0,en=a.size()-1,ans=-1;
    while(op<=en)
    {
        m=(op+en)>>1;
        if(a[m]<k) op=m+1;
        else if(a[m]>k) en=m-1;
        else
        {
            ans=m; en=m-1;
        }

    }
    return ans;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//lower bound
in low(vector<in>a,in k)
{
    in m,op=0,en=a.size()-1;
    while(op<en)
    {
        m=(op+en)>>1;
        if(a[m]>=k) en=m;
        else op=m+1;
    }
    if(op==a.size()-1 && a[a.size()-1]<k) op++;
    return op;
}

//upper bound
in up(vector<in>a,in k)
{
    in m,op=0,en=a.size()-1;
    while(op<en)
    {
        m=(op+en)>>1;
        if(a[m]<=k) op=m+1;
        else en=m;
    }
    if(op==a.size()-1 && a[a.size()-1]<=k) op++;
    return op;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//makes the longtest suffix that is also a prefix table
void suffix_prefix(string s,vector<in>&a)
{
    in pt1=0,pt2=1,n=s.size();
    a[0]=0;
    while(pt2<n)
    {
        if(s[pt1]!=s[pt2])
        {
            if(pt1) pt1=a[pt1-1];
            else
            {
               a[pt2]=0; ++pt2;
            }
        }
        else
        {
            a[pt2]=pt1+1;
            ++pt1; ++pt2;
        }
    }
}

//searches for pattern in a given string
in search(string t,string p)
{
    in n=t.size(),np=p.size(),id_t=0,id_p=0;
    vector<in>a(np);
    suffix_prefix(p,a);
    while(id_t<n)
    {
        if(t[id_t]==p[id_p])
        {
            ++id_t; ++id_p;
        }
        if(id_p==np) return id_t-np;
        else if(id_t<n and t[id_t]!=p[id_p])
        {
            if(id_p) id_p=a[id_p-1];
            else ++id_t;
        }
    }
    return -1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//returns a^n mod m
in mod(in a,in n,in m)
{
    if(n==0) return 1;
    else if(n&1)
    {
        in x=a%m;
        in y=mod(a,n-1,m)%m;
        return (x*y)%m;
    }
    else
    {
        in k=mod(a,n/2,m)%m;
        return (k*k)%m;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//returns a^n mod m
in big_power(in a,in n,in m)
{
    in ans=1;
    a%=m;
    if(!a) return 0;
    while(n)
    {
        if(n&1) ans=(ans*a)%m;
        a=(a*a)%m;
        n>>=1;
    }
    return ans;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//returns n! mod m
in big_fact(in n,in m)
{
    in f=1;
    while(n)
    {
        f=(f*n)%m; --n;
    }
    return f;
}

////////////////////////////////////////////////////////////////////////////////////
///modulo multiplication
in modulo_multiplication(in a, in b, in mod)
{
    in res=0;
    a%=mod;
 
    while (b)
    {
        if (b & 1) res=(res+a)%mod;
        a=(2*a)%mod;
        b>>=1;
    }
 
    return res;
}

//ncr
in ncr(in n,in r,in m)
{
    if (n<r) return 0;
    if (!r) return 1;

    in fac[n+1];
    fac[0]=1;
    for (in i=1;i<=n;++i) fac[i]=(fac[i-1]*i)%m;
 
    return ((fac[n]*big_power(fac[r],m-2,m)%m*big_power(fac[n-r],m-2,m)%m))%m;
}

in ncr(in n, in r)
{
    in C[r+1];
    memset(C,0,sizeof(C));
 
    C[0]=1;
 
    for (in i=1;i<=n;++i)
    {
        for (in k=min(i,r);k>0;--k) C[k]=C[k]+C[k-1];
    }
    return C[r];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//returns a^n in logn time
in power(in a,in n)
{
    in ans=1;
    while(n)
    {
        if(n&1) ans*=a;
        a*=a;
        n>>=1;
    }
    return ans;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//return if power of 2
bool is_power_of_2(in x)
{
    return x and !(x&(x-1));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//increment decrement in given range
void scanline(vector<in>&a,vector<pair<in,in>>q,vector<in>increment)
{
    in n=a.size(),nq=q.size(),l,r;
    in d[n]; d[0]=a[0];
    for(in i=1;i<n;++i) d[i]=a[i]-a[i-1];
    for(in i=0;i<nq;++i)
    {
        l=q[i].first; r=q[i].second;
        d[l]+=increment[i]; d[r+1]-=increment[i];
    }
    a[0]=d[0];
    for(in i=1;i<n;++i)
    {
        a[i]=(d[i]+a[i-1]);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//prime numbers <=n
in sieve_of_erato(in n,vector<in>&p)
{
    vector<bool>a(n+1,true);
    a[0]=a[1]=false;
    for(in i=2;i*i<=n;i++)
    {
        if(a[i]==true)
        {
            for(in k=i*i;k<=n;k+=i) a[k]=false;
        }
    }
    for(in i=2;i<=n;i++)
    {
        if(a[i]==true)
        {
            p.push_back(i);
        }
    }
    return p.size();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///prime factors
vector<in>spf(100005);
void sieve()
{
    spf[1] = 1;
    for (int i=2; i<100005; i++)
 
        // marking smallest prime factor for every
        // number to be itself.
        spf[i] = i;
 
    // separately marking spf for every even
    // number as 2
    for (int i=4; i<100005; i+=2)
        spf[i] = 2;
 
    for (int i=3; i*i<100005; i++)
    {
        // checking if i is prime
        if (spf[i] == i)
        {
            // marking SPF for all numbers divisible by i
            for (int j=i*i; j<100005; j+=i)
 
                // marking spf[j] if it is not
                // previously marked
                if (spf[j]==j)
                    spf[j] = i;
        }
    }
}

vector<int> getFactorization(int x)
{
    vector<int> ret;
    while (x != 1)
    {
        ret.push_back(spf[x]);
        x = x / spf[x];
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//check whether or not a number is prime in logn time
bool prime_check(in n)
{
    vector<in>a{2,3,5,7,11,13,17,19,23,29,31,37};
    if(n<38)
    {
        if(find(a.begin(),a.end(),n)==a.end()) return false;
    }
    else
    {
        for(in x:a)
        {
            if(big_power(x,n-1,n)!=1) return false;
        }
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void subset(string s)
{
    int mask;
    for(int i=0;i<power(2,s.size());++i)
    {
        mask=1; cout<<i+1<<" ";
        for(int k=0;k<s.size();++k)
        {
            if(mask&i) cout<<s[k]<<" ";
            mask<<=1;
        }
        cout<<endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//dfs
vector<int>a[100];
bool state[100];
int p;

void dfs(int node)
{
    state[node]=true;
    for(int i=0;i<a[node].size();++i)
    {
        p=a[node][i];
        if(!state[p]) dfs(p);
    }
}

//without self loop
//for any loop remove the p!=prent condition
bool dfs_cycle(int node,int parent)
{
    //cout<<"visiting node "<<node<<endl;
    state[node]=true;
    for(int i=0;i<a[node].size();++i)
    {
        p=a[node][i];
        if(!state[p]) dfs_cycle(p,node);
        else if(state[p] and p!=parent) return true;
    }
    return false;
}

//topological sort
vector<int>result; //reverse after traversal
bool cycle;
int color[100];
void top_sort(int node)
{
    color[node]=1;
    sort(a[node].begin(),a[node].end(), greater<in>());
    
    for(int i=0;i<a[node].size();++i)
    {
        p=a[node][i];
        if(!color[p]) top_sort(p);
        else if(color[p]==1)
        {
            cycle=true; return;
        }
    }
    color[node]=2;
    result.push_back(node);
}

///bfs
int path[100],prog;
queue<int>tier;

void bfs(int node)
{
    state[node]=true;
    path[node]=0;
    tier.push(node);
    while(!tier.empty())
    {
        prog=tier.front();
        tier.pop();
        for(int i=0;i<a[prog].size();++i)
        {
            p=a[prog][i];
            if(!state[p]) state[p]=true, path[p]=path[prog]+1, tier.push(p);
        }
    }
}

bool bipartite_check(int node)
{
    state[node]=true;
    color[node]=0;
    tier.push(node);
    while(!tier.empty())
    {
        prog=tier.front();
        tier.pop();
        for(int i=0;i<a[prog].size();++i)
        {
            p=a[prog][i];
            if(!state[p] and color[p]!=color[prog]) state[p]=true, color[p]=(color[prog]+1)%2, tier.push(p);
            else if(color[p]==color[prog])
            {
                while(!tier.empty()) tier.pop();
                return false;
            }
        }
    }
    return true;
}

void make_graph()
{
    int n,e,x,y; cin>>n>>e;
    set<int>nodes;
    for(int i=0;i<e;++i)
    {
        cin>>x>>y;
        a[x].push_back(y);
        nodes.insert(x), nodes.insert(y);
    }
    //for(int i=0;i<nodes.size();++i) cout<<nodes[i]<<" ";
    //cout<<endl;
    for(set<int>::iterator it=nodes.begin();it!=nodes.end();++it)
    {
        if(!state[*it]) dfs(*it);
    }
    for(set<int>::iterator it=nodes.begin();it!=nodes.end();++it)
    {
        if(state[*it]) cout<<"VISITED node "<<*it<<endl;
        else cout<<"Has not visited "<<*it<<endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//fibonacci
map<in,in>fibb;
const in m=1000000007;

in fib(in n,in i)
{
    if(fibb.count(n)) return fibb[n];
    else if(i==n)
    {
        fibb[n]=(fibb[n-1]+fibb[n-2])%m;
        return fibb[n];
    }
    else
    {
        fibb[i]=(fibb[i-1]+fibb[i-2])%m;
        return fib(n,i+1);
    }
}

//or
map<in,in>terms;

in fib(in n)
{
    if(terms.count(n)) return terms[n];
    else
    {
        terms[n]=(fib(n-1)+fib(n-2))%m;
        return terms[n];
    }
}

map<in,in>logfib;

in fibonacci(in n)
{
    if(logfib.count(n)) return logfib[n];
    else
    {
        in k;
        k=(n&1)? (n+1)/2:n/2;
        if(n&1)
        {
            return logfib[n]=(fibonacci(k)*fibonacci(k)+fibonacci(k-1)*fibonacci(k-1));
        }
        else return logfib[n]=((2*fibonacci(k-1)+fibonacci(k))*fibonacci(k));
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////permutation of an array
in n;
vector<char>arrange, remaining;

void perm(in taken)
{
    if(n==taken)
    {
        for(in i=0;i<n;++i) cout<<remaining[i]<<" ";
        cout<<endl; return;
    }
    for(in i=taken;i<n;++i)
    {
        swap(remaining[i],remaining[taken]);
        arrange.push_back(remaining[taken]);
        perm(taken+1);
        arrange.pop_back();
        swap(remaining[i],remaining[taken]);
    }
}

//Lexicographical
void permute(vector<char>initial,vector<char>current)
{
    if(!initial.size())
    {
        for(char i:current) cout<<i;
        cout<<endl;
        return;
    }
    for(in i=0;i<initial.size();++i)
    {
        char ch = initial[i];
        current.push_back(ch);
        vector<char>next;
        
        for(int k=0;k<initial.size();++k)
        {
            if(k==i) continue;
            next.push_back(initial[k]);
        }

        permute(next,current);
        current.pop_back();
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
///string product and addition

string string_add(string s,string ss)
{
    string sss;
    int n=s.size(), ns=ss.size();
    int p1=n-1, p2=ns-1, carry=0,x,y;
    while(p1>=0 or p2>=0)
    {
        x=(p1<0)? 0:s[p1]-48;
        y=(p2<0)? 0:ss[p2]-48;
        sss.push_back(48+(x+y+carry)%10);
        carry=((x+y+carry)>9)? 1:0;
        --p1, --p2;
    }
    if(carry>0) sss.push_back(48+carry);
    reverse(sss.begin(),sss.end());
    return sss;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//merge sort
void merge(vector<int>&a, int l, int m, int r)
{
    int temp[r-l+1],id=0;

    int i,k;
    for(i=l, k=m+1; i<=m and k<=r;)
    {
        if(a[i]<a[k]) temp[id++]=a[i++];
        else temp[id++]=a[k++];
    }

    while(i<=m) temp[id++]=a[i++];
    while(k<=r) temp[id++]=a[k++];

    for(int i=l;i<=r;++i) a[i]=temp[i-l];
}

void merge_sort(vector<int>&a, int l, int r)
{
    if(l<r)
    {
        int m=l+(r-l)/2;
        merge_sort(a,l,m);
        merge_sort(a,m+1,r);
        merge(a,l,m,r);
    }
    else return;
}

/////////////////////////////////////////////////////////////////////////////
///disjoint set
class Disjoint_set
{
    int *parent, *rank;

    public:
        Disjoint_set(int capacity)
        {
            this->parent=new int[capacity];
            this->rank=new int[capacity];

            make_set(capacity);
        }

        void make_set(int capacity)
        {
            for(int i=0;i<capacity;++i) parent[i]=i, rank[i]=0;
        }

        int find(int id)
        {
            if(parent[id]!=id) parent[id]=find(parent[id]);
            return parent[id];
        }

        void unite(int i, int k)
        {
            int i_set=find(i), k_set=find(k);

            if(i_set==k_set) return;
            
            if(rank[i_set]<rank[k_set]) parent[i_set]=k_set;
            else if(rank[i_set]>rank[k_set]) parent[k_set]=i_set;
            else parent[i_set]=k_set, ++rank[k_set];
        }

        int operator[](int id)
        {
            return parent[id];
        }

        int get_rank(int id)
        {
            return rank[id];
        }

        ~Disjoint_set()
        {
            delete[] rank;
            delete[] parent;
        }
};

/////////////////////////////////////////////////////////////////////////////////////////////
//kruskal's algorithm
int kruskal(vector<pair<int,pair<int,int>>>&edge)
{
    sort(edge.begin(),edge.end());

    int ans=0, n=edge.size();
    Disjoint_set color(n);

    for(int i=0;i<n;++i)
    {
        int x=edge[i].second.first, y=edge[i].second.second;
        if(color.find(x)!=color.find(y))
        {
            color.unite(x,y), ans+=edge[i].first;
        }
    }
    
    return ans;
}

///////////////////////////////////////////////////////////////////////////////////////////
//kadane's algorithm
in kadane_sum(vector<in>&a)
{
    in local_sum=0, global_sum=LLONG_MIN;

    for(in i:a)
    {
        local_sum+=i;
        local_sum=max(i,local_sum);
        
        global_sum=max(local_sum,global_sum);
    }

    return global_sum;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///sesgment tree
in actual[100], segment[200], lazy[200];

void make_tree(in op,in en,in root)
{
    if(op>en) return;
    
    if(op==en) //if leaf node
    {
        segment[root]=actual[op]; return;
    }

    in m=op+(en-op)/2;
    make_tree(op,m,2*root+1);
    make_tree(m+1,en,2*root+2);

    segment[root]=min(segment[2*root+1],segment[2*root+2]);
}

in query(in qop,in qen,in op,in en,in root)
{
    if(op>en) return LLONG_MAX;

    if(qop<=op and qen>=en) return segment[root]; //full overlap

    if(qop>en or qen<op) return LLONG_MAX;  //no overlap

    in m=op+(en-op)/2;
    return min(query(qop,qen,op,m,2*root+1), query(qop,qen,m+1,en,2*root+2));
}

void update(in op, in en, in pos, in root, in x)
{
    if(op>en or pos>en or pos<op) return;

    segment[root]+=x;

    if(op==en) return;

    in m=op+(en-op)/2;
    update(op,m,pos,2*root+1,x);
    update(m+1,en,pos,2*root+2,x);
}

void lazy_update(in qop,in qen,in x,in op,in en,in root)
{
    if(op>en) return;

    if(lazy[root]) //corrsponding position is not zero then it hasn't been updated
    {
        segment[root]+=lazy[root];
        if(op!=en) lazy[2*root+1]+=lazy[root], lazy[2*root+2]+=lazy[root]; //propagate the change to childen
        lazy[root]=0;
    }

    if(qop>en or qen<op) return;

    if(qop<=op and qen>=en) 
    {
        segment[root]+=x;
        if(op!=en) lazy[2*root+1]+=lazy[root], lazy[2*root+2]+=lazy[root];
        return;
    }

    int m=op+(en-op)/2;
    lazy_update(qop,qen,x,op,m,2*root+1);
    lazy_update(qop,qen,x,m+1,en,2*root+2);
    segment[root]=min(segment[2*root+1],segment[2*root+2]);
}

in lazy_query(in qop,in qen,in op,in en,in root)
{
    if(op>en) return LLONG_MAX;

    if(lazy[root])
    {
        segment[root]+=lazy[root];
        if(op!=en) lazy[2*root+1]+=lazy[root], lazy[2*root+2]+=lazy[root];
        lazy[root]=0;
    }

    if(qop<=op and qen>=en) return segment[root];

    if(qop>en or qen<op) return LLONG_MAX;

    in m=op+(en-op)/2;
    return min(lazy_query(qop,qen,op,m,2*root+1), lazy_query(qop,qen,m+1,en,2*root+2));
}


////////////////////////////////////////////////////////////////////////////////////////
////fenwick tree
class fenwick_tree
{
    in* fentree;
    in len;

    public:
        fenwick_tree(in n,vector<in>&a)
        {
            fentree=new in[n+1];
            for(int i=0;i<n+1;++i) fentree[i]=0;
            this->len=n;
            for(int i=0;i<n;++i) update(i,a[i]);
        }

        void update(in id,in val)
        {
            ++id;
            while(id<len+1)
            {
                fentree[id]+=val;
                id+=(id&(-id));
            }
        }

        in get_sum(in id)
        {
            in ans=0;
            ++id;
            while(id>0)
            {
                ans+=fentree[id];
                id-=(id&(-id));
            }

            return ans;
        }

        ~fenwick_tree()
        {
            delete[] fentree;
        }
};

//////////////////////////////////////////////////////////////////////////////////////////////////
//Dijkstra's shortest path
vector<pair<in,in>>aa[100];
bool visited[100];
in dis[100], value, cost;
pair<in,in>pp;

class Comp
{
    public:
        bool operator()(pair<in,in>&a, pair<in,in>&b)
        {
            return a.second>b.second;
        }
};

void dijkstra(in node)
{
    priority_queue<pair<in,in>, vector<pair<in,in>>, Comp>q;
    q.push({node,0});

    while(!q.empty())
    {
        pp=q.top(), q.pop();
        value=pp.first, cost=pp.second;

        if(!visited[value])
        {
            dis[value]=cost, visited[value]=true;

            for(in i=0;i<aa[value].size();++i)
            {
                if(!visited[aa[value][i].first]) q.push({aa[value][i].first, cost+aa[value][i].second});
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/////check if a sequence with sum k exists or not
bool Check(vector<int>&a,int n,int k)
{
    for(int i=n-1;i>=0;--i)
    {
        if(k>=a[i])
            k-=a[i];
    }
    if(k!=0) return false;
    else return true;
}

/////////////////////////////////////////////////////////////////////////////
//last two digit of factorial
int dig[]= {1,1,2,6,24,12,72,4,32,88};

in last_two_of_power(in a,in n)
{
    in ans=a;
    while(--n) ans=(ans*a)%100;
    return ans;
}

in last_two(in n)
{
    if(n<10) return dig[n];
    in a=n/5, b=n%5;
    in ans1=last_two_of_power(12,a), ans2=last_two(a), temp=1;
    for(in i=1;i<b+1;++i) temp=(temp*(5*a+i))%100;
    //cout<<ans1<<" "<<ans2<<" "<<temp<<endl;
    return (ans1*ans2*temp)%100;
}

/////////////////////////////////////////////////////////////////////////////////////
//no of incrreasing subseq of len k
in no_of_inc_seq(vector<in>&a,in n,in k)
{
    in dp[k][n], sum=0;
    memset(dp,0,sizeof(dp));
 
    for(int i=0;i<n;++i) dp[0][i]=1;
 
    for(int l=1;l<k;++l)
    {
        for (int i=l;i<n;++i)
        {
            dp[l][i]=0;
            for(int j=l-1;j<i;++j)
            {
                if (a[j]<a[i]) dp[l][i]=(dp[l][i]+dp[l-1][j])%modv;
            }
        }
    }
 
    for (int i=k-1;i<n;++i) sum=(sum+dp[k-1][i])%modv;

    return sum%modv;
}

/////////////////////////////////////////////////////////////////////////////////////
//trie data structure
class Trie_node
{
    public:
        Trie_node* child[26];
        int end_of_word, prefix_count;

        Trie_node(int end_of_word=0)
        {
            this->end_of_word=end_of_word;
            this->prefix_count=1;
            for(int i=0;i<26;++i) child[i]=NULL;
        }
};

class Trie
{
    public:
        Trie_node* root;

        Trie()
        {
            root=new Trie_node();
        }

        void insert(string key)
        {
            if(root==NULL) root=new Trie_node();
            Trie_node* temp=root;

            for(int i=0;i<key.size();++i)
            {
                int index=key[i]-'a';
                if(temp->child[index]==NULL) temp->child[index]=new Trie_node();
                else ++temp->child[index]->prefix_count;
                temp=temp->child[index];
            }

            ++temp->end_of_word;
        }

        int search(string key)
        {
            Trie_node* temp=root;

            for(int i=0;i<key.size();++i)
            {
                int index=key[i]-'a';
                if(temp->child[index]==NULL) return false;
                temp=temp->child[index];
            }

            return temp->end_of_word;
        }

        int count_prefix(string key)
        {
            Trie_node* temp=root;

            for(int i=0;i<key.size();++i)
            {
                int index=key[i]-'a';
                if(temp->child[index]==NULL) return false;
                temp=temp->child[index];
            }

            return temp->prefix_count;
        }

        bool remove(string key)
        {
            return remove(key,root,0);
        }

        bool remove(string key, Trie_node* node, int len)
        {
            if(node==NULL) return false;

            if(len==key.size())
            {
                if(!node->end_of_word) return false;

                --node->end_of_word;
                if(empty(node) and !node->end_of_word)
                {
                    delete node;
                    return true;
                }

                return false;
            }

            int index=key[len]-'a';
            bool permission=remove(key, node->child[index], len+1);

            if(permission)
            {
                node->child[index]=NULL;
                if(!node->end_of_word and empty(node))
                {
                    delete node;
                    return true;
                }
            }

            return false;
        }

        bool empty(Trie_node* node)
        {
            for(int i=0;i<26;++i)
            {
                if(node->child[i]!=NULL) return false;
            }

            return true;
        }

        void display()
        {
            display(root,"");
        }

        void display(Trie_node* node,string s)
        {
            if(node->end_of_word) cout<<s<<endl;
            for(int i=0;i<26;++i)
            {
                if(node->child[i]!=NULL)
                {
                    s.push_back('a'+i);
                    display(node->child[i],s);
                    s.pop_back();
                }
            }
        }

        void clear(Trie_node* node)
        {
            if(node==NULL) return;

            for(int i=0;i<26;++i)
            {
                if(node->child[i]!=NULL) clear(node->child[i]);
            }
            
            delete node;
        }

        ~Trie()
        {
            clear(root);
        }
};

///////////////////////////////////////////////////////////////////////////////////////////////
//knacpsack
int dp[100][100];
int knapsack(int capacity, int item,vector<int>&prices,vector<int>&weight)
{
    if(capacity<1 or item<0) return 0;

    int not_taken=knapsack(capacity,item-1, prices,weight);
    int taken=0;
    if(capacity-weight[item]>=0) taken=knapsack(capacity-weight[item], item-1, prices, weight)+prices[item];

    return max(not_taken,taken);
}

void knapsack_bottom_up(int capacity,vector<int>&prices,vector<int>&weight)
{
    for(int i=0;i<prices.size();++i) dp[0][i]=0;
    for(int i=0;i<capacity+1;++i) dp[i][0]=0;

    for(int i=1;i<capacity+1;++i)
    {
        for(int k=1;k<prices.size();++k)
        {
            int not_taken=dp[i][k-1];
            int taken=0;
            if(i-weight[k]>=0) taken=dp[i-weight[k]][k-1]+prices[k];
            dp[i][k]=max(not_taken,taken);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////lcs
int dp[100][100];

int lcs_dp(string s,string ss,int i,int k)
{
    if(!i or !k) return 0;
    
    if(s[i-1]==ss[k-1])
    {
        if(dp[i-1][k-1]!=-1) return 1+dp[i-1][k-1];
        return dp[i-1][k-1]=1+lcs_dp(s,ss,i-1,k-1);
    }

    int temp1,temp2;
    
    if(dp[i][k-1]!=-1) temp1=dp[i][k-1];
    else dp[i][k-1]=temp1=lcs_dp(s,ss,i,k-1);

    if(dp[i-1][k]!=-1) temp2=dp[i-1][k];
    else dp[i-1][k]=temp2=lcs_dp(s,ss,i-1,k);

    return max(temp1,temp2);
}

void lcs_bottom_up(string& s, string& ss)
{
    for(int i=1;i<s.size()+1;++i)
    {
        for(int k=1;k<ss.size()+1;++k)
        {
            if(s[i-1]==ss[k-1]) dp[i][k]=1+dp[i-1][k-1];
            else dp[i][k]=max(dp[i][k-1],dp[i-1][k]);
        }
    }
}

void print_lcs(string& s, string& ss, int i, int k)
{
    if(!i or !k) return;

    if(s[i-1]==ss[k-1]) print_lcs(s,ss,i-1,k-1), cout<<s[i-1];
    else
    {
        if(dp[i-1][k]>dp[i][k-1]) print_lcs(s,ss,i-1,k);
        else print_lcs(s,ss,i,k-1);
    }
}

string dp_[100][100];

void lcs_bottom_up_lex(string& s, string& ss)
{
    for(int i=0;i<s.size()+1;++i) dp_[i][0]="";
    for(int i=0;i<ss.size()+1;++i) dp_[0][i]="";

    for(int i=1;i<s.size()+1;++i)
    {
        for(int k=1;k<ss.size()+1;++k)
        {
            if(s[i-1]==ss[k-1]) dp_[i][k]=dp_[i-1][k-1]+s[i-1];
            else if(dp_[i-1][k].size()>dp_[i][k-1].size()) dp_[i][k]=dp_[i-1][k];
            else if(dp_[i-1][k].size()<dp_[i][k-1].size()) dp_[i][k]=dp_[i][k-1];
            else
            {
                if(lexicographical_compare(dp_[i][k-1].begin(),dp_[i][k-1].end(), dp_[i-1][k].begin(),dp_[i-1][k].end())) dp_[i][k]=dp_[i][k-1];
                else dp_[i][k]=dp_[i-1][k];
            }
        }
    }
}

string s;
int longest_palindrome(int i, int k)
{
    if(i==k) return 1;
    if(i>k) return 0;

    if(dp[i][k]!=-1) return dp[i][k];

    if(s[i]==s[k]) return dp[i][k]=longest_palindrome(i+1,k-1)+2;

    return dp[i][k]=max(longest_palindrome(i+1,k), longest_palindrome(i,k-1));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////MCM
int dp[15][15], split[15][15];
vector<int>dimentions;

int matrix_mult(int i, int k)
{
    if(i==k) return 0;
    if(dp[i][k]!=-1) return dp[i][k];

    int ans=INT_MAX, split_pos=-1, temp;

    for(int j=i;j<k;++j)
    {
        temp=matrix_mult(i,j)+matrix_mult(j+1,k)+(dimentions[i-1]*dimentions[j]*dimentions[k]);
        if(ans>temp) ans=temp, split_pos=j;
    }

    split[i][k]=split_pos;
    return dp[i][k]=ans;
}

void print_bracket(int i, int k)
{
    if(i==k)
    {
        cout<<'A'<<i; return;
    }
    cout<<"(";
    print_bracket(i,split[i][k]);
    cout<<" x ";
    print_bracket(split[i][k]+1,k);
    cout<<")";
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//longest increasing consecutive subsequence
int longestSubsequence(int a[], int n)
{
    unordered_map<int, int> mp;
    int dp[n];
    memset(dp, 0, sizeof(dp));
 
    int maximum = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        if (mp.find(a[i] - 1) != mp.end())
        {
            int lastIndex = mp[a[i] - 1] - 1;
            dp[i] = 1 + dp[lastIndex];
        }
        else dp[i] = 1;
        mp[a[i]] = i + 1;
        maximum = max(maximum, dp[i]);
    }
 
    return maximum;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
///longest increasing subsequence
int longest_increasing_subsequence(vector<int>& arr)
{
    vector<int> ans;
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        auto it= lower_bound(ans.begin(), ans.end(), arr[i]);
        if (it == ans.end()) ans.push_back(arr[i]);
        else *it = arr[i];
    }
    return ans.size();
}

/////////////////////////////////////////////////////////////////////////////////
//number of substrings with n set bits
in calc(string& s, in n)
{
    in ans=0, cnt=0;
    vector<in>a(s.size()+1,0);

    a[0]=1;
    for(int i=0;i<s.size();++i)
    {
        cnt+=s[i]-48;
        if(cnt>=n) ans+=a[cnt-n];
        ++a[cnt];
    }

    return ans;
}