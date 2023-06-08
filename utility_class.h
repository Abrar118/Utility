#include<bits/stdc++.h>
typedef long long in;
using namespace std;

////////////////////////////////////////////////////////////////////////////////////
//single linked list

template<class type>struct node
{
    type key;
    node* nxt;
};

template<class type>class SingleLinkedList
{
    node<type>* head=NULL;
    int length=0;

    public:
        void insert_last(int x)
        {
            node<type>* temp=new node<type>();

            if(head==NULL)
            {
                temp->key=x;
                temp->nxt=NULL;
                head=temp;
            }
            else
            {
                node<type>* data=head;
                while(data->nxt!=NULL) data=data->nxt;

                temp->key=x;
                temp->nxt=NULL;

                data->nxt=temp;
            }
            ++length;
        }

        void insert_first(int x)
        {
            node<type>* temp=new node<type>();

            temp->key=x;
            temp->nxt=head;
            head=temp;
            ++length;
        }

        void insert_at(int id,int x)
        {
            node<type>* temp=new node<type>();

            if(!id)
            {
                temp->key=x;
                temp->nxt=head->nxt;
                head=temp;
            }
            else
            {
                node<type>* current=head;
                node<type>* prev=NULL;
                int position=0;

                while(position!=id)
                {
                    if(position==id-1) prev=current;
                    current=current->nxt;
                    ++position;
                }

                temp->key=x;
                temp->nxt=current;
                prev->nxt=temp;
            }
            ++length;
        }

        void insert_after(node<type>* id,int x)
        {
            node<type>* temp=new node<type>();

            if(id==head)
            {
                temp->key=x;
                temp->nxt=head->nxt;
                head->nxt=temp;
            }
            else
            {
                node<type>* current=head;

                while(current!=id) current=current->nxt;

                temp->key=x;
                temp->nxt=current->nxt;
                current->nxt=temp;
            }
            ++length;
        }

        node<type>* find_first(int x)
        {
            node<type>* temp=head;
            if(head==NULL) return NULL;
            while(temp!=NULL)
            {
                if(temp->key==x) break;
                else temp=temp->nxt;
            }
            return temp;
        }

        void erase_first(int x)
        {
            node<type>* current=head;
            node<type>* prev=NULL;

            if(head->key==x)
            {
                head=head->nxt;
                free(current);
            }
            else
            {
                while(current!=NULL)
                {
                    prev=current;
                    current=current->nxt;
                    if(current!=NULL and current->key==x) break;
                }

                if(current!=NULL) prev->nxt=current->nxt, free(current);
            }
            --length;
        }

        void erase_at(node<type>* id)
        {
            node<type>* temp=head;

            if(id==head)
            {
                head=head->nxt;
                free(temp);
            }
            else
            {
                while(temp!=NULL)
                {
                    if(temp->nxt==id) break;
                    temp=temp->nxt;
                }

                temp->nxt=id->nxt;
                free(id);
            }
            --length;
        }

        void sort()
        {
            bool state;
            node<type>* current;
            node<type>* later;
            for(int i=0;i<length-1;++i)
            {
                state=false;
                current=head;
                later=current->nxt;
                for(int k=0;k<length-i-1;++k)
                {
                    if(current->key>later->key)
                    {
                        swap(current->key,later->key);
                        state=true;
                    }
                    current=later;
                    later=later->nxt;
                }
                if(!state) break;
            }
        }

        node<type>* get_head()
        {
            return this->head;
        }

        int size()
        {
            return this->length;
        }

        void print()
        {
            node<type>* temp=head;
            while(temp!=NULL)
            {
                cout<<temp->key<<" ";
                temp=temp->nxt;
            }
            cout<<endl;
        }

        void clear()
        {
            node<type>* temp=head;
            node<type>* current=NULL;
            
            while(temp!=NULL)
            {
                current=temp->nxt;
                free(temp);
                temp=current;
            }
        }
};


//double linked list
template<typename data> struct Double_Node
{
    data key;
    Double_Node* right;
    Double_Node* left;
};

template<typename data> class DoublyLinkedList
{
    Double_Node<data>* head=NULL;
    Double_Node<data>* tail=NULL;
    int asize=0;

    public:
        void insert_last(data x)
        {
            Double_Node<data>* temp=new Double_Node<data>();
            temp->key=x;

            if(head==NULL and tail==NULL)
            {
                temp->right=NULL;
                temp->left=NULL;
                head=tail=temp;
            }
            else
            {
                temp->right=NULL;
                temp->left=tail;
                tail->right=temp;
                tail=temp;
            }
            ++asize;
        }

        void insert_first(data x)
        {
            Double_Node<data>* temp=new Double_Node<data>();
            temp->key=x;

            if(head==NULL and tail==NULL)
            {
                temp->right=NULL;
                temp->left=NULL;
                head=tail=temp;
            }
            else
            {
                temp->right=head;
                temp->left=NULL;
                head->left=temp;
                head=temp;
            }
            ++asize;
        }

        void insert_after(Double_Node<data>* id, data x)
        {
            Double_Node<data>* temp=new Double_Node<data>();
            temp->key=x;

            if(head==NULL and tail==NULL)
            {
                temp->right=NULL;
                temp->left=NULL;
                head=tail=temp;
            }
            else
            {
                temp->right=id->right;
                temp->left=id;
                id->right=temp;
            }
            ++asize;
        }

        Double_Node<data>* find_first(data x)
        {
            Double_Node<data>* temp=head;

            while(temp!=NULL)
            {
                if(temp->key==x) break;
                temp=temp->right;
            }

            return temp;
        }

        Double_Node<data>* find_last(data x)
        {
            Double_Node<data>* temp=tail;

            while(temp!=NULL)
            {
                if(temp->key==x) break;
                temp=temp->left;
            }
            return temp;
        }

        void erase_first(data x)
        {
            Double_Node<data>* temp=head;

            if(head==NULL and tail==NULL) return;
            else if(asize==1)
            {
                if(head->key!=x) return;
                else
                {
                    head=tail=NULL;
                    free(temp);
                    --asize;
                }
            }
            else
            {
                if(head->key==x)
                {
                    head=head->right;
                    head->left=NULL;
                    free(temp);
                    --asize;
                }
                else if(tail->key==x)
                {
                    temp=tail;
                    tail=tail->left;
                    tail->right=NULL;
                    free(temp);
                    --asize;
                }
                else
                {
                    while(temp!=NULL)
                    {
                        if(temp->key==x) break;
                        else temp=temp->right;
                    }

                    temp->left->right=temp->right;
                    temp->right->left=temp->left;
                    free(temp);
                    --asize;
                }
            }
        }

        Double_Node<data>* get_head()
        {
            return head;
        }

        Double_Node<data>* get_tail()
        {
            return tail;
        }

        void print()
        {
            Double_Node<data>* temp=head;
            while(temp!=NULL)
            {
                cout<<temp->key<<" ";
                temp=temp->right;
            }
            cout<<endl;
        }

        void clear()
        {
            Double_Node<data>* temp=head;
            Double_Node<data>* current=NULL;
            while(temp!=NULL)
            {
                current=temp->right;
                free(temp);
                temp=current;
            }
        }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
///dynamic array
template<class type>class dynamic_array
{
    int asize;
    type* a;

    public:
        dynamic_array()
        {
            this->asize=0;
            a=(type*)malloc(0);
        }

        void push_front(type x)
        {
            a=(type*)realloc(a,(asize+1)*sizeof(type));
            for(int i=asize;i>-1;--i) a[i]=a[i-1];
            a[0]=x, ++asize;
        }

        void push_back(type x)
        {
            a=(type*)realloc(a,(asize+1)*sizeof(type));
            a[asize]=x, ++asize;
        }

        void insert(int id,type x)
        {
            if(id>asize) cout<<"Index "<<id<<" is not accessible"<<endl;
            else
            {
                a=(type*)realloc(a,(asize+1)*sizeof(type));
                for(int i=asize;i>id;--i) a[i]=a[i-1];
                a[id]=x, ++asize;
            }
        }

        int pop_front()
        {
            if(!asize) cout<<"Array is empty!"<<endl;
            else
            {
                int x=a[0];
                for(int i=0;i<asize;++i) a[i]=a[i+1];
                --asize;
                return x;
            }
            return 0;
        }

        int pop_back()
        {
            if(!asize) cout<<"Array is empty!"<<endl;
            else return a[--asize];
            return 0;
        }

        int erase(int id)
        {
            int x=a[id];
            if(!asize) cout<<"Array is empty!"<<endl;
            else if(id>asize) cout<<"Index "<<id<<" is not accessible"<<endl;
            else
            {
                for(int i=id;i<asize;++i) a[i]=a[i+1];
                --asize;
                return x;
            }
            return 0;
        }

        int find(type x)
        {
            int id=-1;
            for(int i=0;i<asize;++i)
            {
                if(a[i]==x)
                {
                    id=i; break;
                }
            }
            return id;
        }

        void rotate_left()
        {
            int x=a[0];
            for(int i=0;i<asize-1;++i) a[i]=a[i+1];
            a[asize-1]=x;
        }

        void rotate_right()
        {
            int x=a[asize-1];
            for(int i=asize-1;i>-1;--i) a[i]=a[i-1];
            a[0]=x;
        }

        void sort()
        {
            bool state;
            for(int i=0;i<asize-1;++i)
            {
                state=false;
                for(int k=0;k<asize-i-1;++k)
                {
                    if(a[k]>a[k+1])
                    {
                        swap(a[k],a[k+1]), state = true;
                    }
                }
                if(!state) break;
            }
        }

        int size()
        {
            return asize;
        }

        void clear()
        {
            free(a);
            asize=0;
        }

        int operator[](int x)
        {
            return a[x];
        }

        void print()
        {
            if(!asize) cout<<"The array is empty"<<endl;
            else for(int i=0;i<asize;++i) cout<<a[i]<<" ";
            cout<<endl;
        }

        ~dynamic_array()
        {
            free(a);
            asize=0;
        }
};

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

string multi(string s,string ss)
{
    string sss;
    vector<string>a;
    int x,y,carry;
    for(int i=ss.size()-1;i>-1;--i)
    {
        x=ss[i]-48; carry=0;
        for(int k=s.size()-1;k>-1;--k)
        {
            y=s[k]-48;
            sss.push_back(48+(x*y+carry)%10);
            carry=(x*y+carry)/10;
        }
        if(carry>0) sss.push_back(48+carry);
        reverse(sss.begin(),sss.end());
        for(int x=0;x<ss.size()-i-1;++x) sss.push_back('0');
        a.push_back(sss);
        sss.clear();
    }
    sss=a[0];
    for(int i=1;i<a.size();++i) sss=string_add(sss,a[i]);
    return sss;
}

char plot[20][20];

void scatter_plot()
{
    system("cls");
    int size=rand()%20;
    set<pair<int,int>>points;
    for(int i=0;i<100;++i) points.insert({rand()%20,rand()%20});
    for(set<pair<int,int>>::iterator it=points.begin();it!=points.end();++it) plot[(*it).first][(*it).second]='.';

    for(int i=0;i<20;++i)
    {
        for(int k=0;k<20;++k) cout<<plot[i][k]<<" ";
        cout<<endl;
    }

}


///////////////////////////////////////////////////////////////////////////////////////////////////////
//stack with two queue
//pop_costly
class Stack_pop_costly
{
    queue<int>q1,q2;
    int len;

    public:
        Stack_pop_costly()
        {
            this->len=0;
        }

        void push(int x)
        {
            q1.push(x); ++len;
        }

        void pop()
        {
            if(!q1.empty())
            {
                for(int i=0;i<len-1;++i)
                {
                    if(!q1.empty())
                    {
                        q2.push(q1.front());
                        q1.pop();
                    }
                }
                
                swap(q1,q2);
                --len;
            }
        }

        int top()
        {
            return q1.back();
        }

        bool empty()
        {
            return q1.empty();
        }

        int size()
        {
            return len;
        }

        void print()
        {
            while(!q1.empty()) cout<<q1.front()<<" ", q1.pop();
            cout<<"<--TOP"<<endl;
        }
};

//push_costly
class Stack_push_costly
{
    queue<int>q1,q2;
    int len;

    public:
        Stack_push_costly()
        {
            this->len=0;
        }

        void push(int x)
        {
            q2.push(x);
            while(!q1.empty()) q2.push(q1.front()), q1.pop();
            swap(q1,q2);
            ++len;
        }

        void pop()
        {
           if(!q1.empty()) q1.pop();
        }

        int top()
        {
            return q1.front();
        }

        bool empty()
        {
            return q1.empty();
        }

        int size()
        {
            return len;
        }

        void print()
        {
            cout<<"TOP--> ";
            while(!q1.empty()) cout<<q1.front()<<" ", q1.pop();
        }
};


////////////////////////////////////////////////////////////////////////////////////////
//Queue using two stacks
//push_costly
class Queue_push_costly
{
    stack<int>s1,s2;
    int len;

    public:
        Queue_push_costly()
        {
            this->len=0;
        }

        void push(int x)
        {
            while(!s1.empty()) s2.push(s1.top()), s1.pop();
            s1.push(x);
            while(!s2.empty()) s1.push(s2.top()), s2.pop();
            ++len;
        }

        void pop()
        {
            if(!s1.empty()) s1.pop(), --len;
        }

        bool empty()
        {
            return s1.empty();
        }

        int front()
        {
            return s1.top();
        }

        int back()
        {
            while(!s1.empty()) s2.push(s1.top()), s1.pop();
            int x=s2.top();
            while(!s2.empty()) s1.push(s2.top()), s2.pop();
            return x;
        }

        int size()
        {
            return len;
        }

        void print()
        {
            cout<<"Front-> ";
            while(!s1.empty()) cout<<s1.top()<<" ", s1.pop();
            cout<<"<-Back"<<endl;
        }
};

//pop_costly
class Queue_pop_costly
{
    stack<int>s1,s2;
    int len;

    public:
        Queue_pop_costly()
        {
            this->len=0;
        }

        void push(int x)
        {
            s1.push(x), ++len;
        }

        void pop()
        {
            while(!s1.empty()) s2.push(s1.top()), s1.pop();
            if(!s2.empty()) s2.pop(), --len;
            while(!s2.empty()) s1.push(s2.top()), s2.pop();
        }

        bool empty()
        {
            return s1.empty();
        }

        int front()
        {
            while(!s1.empty()) s2.push(s1.top()), s1.pop();
            int x=s2.top();
            while(!s2.empty()) s1.push(s2.top()), s2.pop();
            return x;
        }

        int back()
        {
            return s1.top();
        }

        int size()
        {
            return len;
        }

        void print()
        {
            while(!s1.empty()) s2.push(s1.top()), s1.pop();
            cout<<"Front-> ";
            while(!s2.empty()) cout<<s2.top()<<" ", s2.pop();
            cout<<"<-Back"<<endl;
        }
};

////////////////////////////////////////////////////////////////////////////////////////
//circular queue
class Circular_queue
{
    int* a;
    int len, front, back, capacity;

    public:
        Circular_queue(int len=100)
        {
            this->len=this->front=this->back=0;
            this->capacity=len;
            a=new int[len];
        }

        bool empty()
        {
            if(len) return false;
            return true;
        }

        void push(int x)
        {
            if(len<capacity)
            {
                a[back]=x;
                back=(back+1)%capacity;
                ++len;
            }
            else cout<<"Overflow"<<endl;
        }

        void pop()
        {
            if(!empty())
            {
                front=(front+1)%capacity;
                --len;
            }
            else cout<<"Underflow"<<endl;
        }

        void print()
        {
            if(len)
            {
                cout<<"Front-> "<<a[front]<<" ";
                for(int i=(front+1)%capacity; i!=back; i=(i+1)%capacity) cout<<a[i]<<" ";
                cout<<"<-Back"<<endl;
            }
        }

        int size()
        {
            return len;
        }

        void clear()
        {
            delete[] a;
        }
};

//////////////////////////////////////////////////////////////////////////////////////////////
//binary search tree (The Untold Story)

struct bs_node
{
    int key;
    bs_node *right, *left, *parent;

    public:
        bs_node(int key=-1,bs_node* parent=NULL)
        {
            this->key=key;
            this->left=this->right=NULL;
            this->parent=parent;
        }
};

class BST
{
    bs_node* root;
    bs_node* data;
    int len;
    map<bs_node*,int>level;
    //int* height;

    public:
        BST()
        {
            this->root=NULL, this->len=0;
            this->data=this->root;
            level[this->root]=0;
        }

        void insert(int x)
        {
            if(this->root==NULL)
            {
                this->root=new bs_node(x);

                this->data=this->root;
                return;
            }
            else
            {
                if(data->key>x)
                {
                    if(data->left==NULL)
                    {
                        bs_node* temp=new bs_node(x,data);

                        data->left=temp;
                        this->data=this->root;
                        return;
                    }
                    else data=data->left, insert(x);
                }
                else
                {
                    if(data->right==NULL)
                    {
                        bs_node* temp=new bs_node(x,data);

                        data->right=temp;
                        this->data=this->root;
                        return;
                    }
                    else data=data->right, insert(x);
                }
            }
            ++this->len;
        }

        void erase(bs_node* temp)
        {
            if(temp==NULL) return;

            if(temp->left==NULL and temp->right==NULL)
            {
                if(temp==this->root)
                {
                    delete temp, this->root=NULL;
                    return;
                }

                if(temp->parent->key>temp->key) temp->parent->left=NULL;
                else temp->parent->right=NULL;

                delete temp;
                return;
            }
            else if(temp->left==NULL or temp->right==NULL)
            {
                bs_node* child;
                if(temp->left==NULL) child=temp->right;
                else child=temp->left;

                if(temp==root)
                {
                    delete temp;
                    this->root=child;
                    child->parent=NULL;
                    return;
                }

                child->parent=temp->parent;

                if(temp->parent->key>temp->key) temp->parent->left=child;
                else temp->parent->right=child;

                delete temp;
                return;
            }

            ////for bs_node with double children
            bs_node* data=in_order_successor(temp);
            int x=data->key;
            erase(data);
            temp->key=x;
        }

        void erase(int x)
        {
            bs_node* temp=find(x);
            erase(temp);
        }

        bs_node* find(int x)
        {
            bs_node* temp=this->root;

            while(temp!=NULL)
            {
                if(x==temp->key) break;
                else if(x<temp->key) temp=temp->left;
                else temp=temp->right;
            }

            return temp;
        }

        bs_node* in_order_successor(bs_node* node)
        {
            if(node->right!=NULL) return min_of_tree(node->right);
            if(node==root or node==NULL) return NULL;

            while(node->parent->left!=node) node=node->parent;
            return node->parent;
        }

        bs_node* min_of_tree(bs_node* root)
        {
            while(root and root->left!=NULL) root=root->left;
            return root;
        }

        bs_node* max_of_tree(bs_node* root)
        {
            while(root and root->right!=NULL) root=root->left;
            return root;
        }

        int height_of_node(bs_node* temp)
        {
            int x=0;
            while(temp!=this->root) ++x, temp=temp->parent;
            return x;
        }

        int height(bs_node* temp)
        {
            if(temp==NULL) return -1;
            if(temp->left==NULL and temp->right==NULL) return 0;
            return 1+ max(height(temp->left),height(temp->right));
        }

        bs_node* get_root()
        {
            return this->root;
        }

        int size()
        {
            return this->len;
        }

        void in_order_print(bs_node* root)
        {
            if(this->root!=NULL)
            {
                if(root->left!=NULL) in_order_print(root->left);
                if(root!=NULL) cout<<root->key<<" ";
                if(root->right!=NULL) in_order_print(root->right);
            }
        }

        void level_order_print()
        {
            queue<bs_node*>q;
            q.push(root);

            int current_level=-1;

            while(!q.empty())
            {
                bs_node* temp=q.front();
                q.pop();

                if(level[temp]>current_level) cout<<endl, ++current_level;
                cout<<temp->key<<" ";

                if(temp->left!=NULL) level[temp->left]=level[temp]+1, q.push(temp->left);
                if(temp->right!=NULL) level[temp->right]=level[temp]+1, q.push(temp->right);
            }
        }

        void clear(bs_node* temp)
        {
            if(this->root!=NULL)
            {
                if(temp->left!=NULL) clear(temp->left);
                if(temp->right!=NULL) clear(temp->right);
                cout<<"Cleared "<<temp->key<<endl;
                delete temp;
            }
        }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//disjoint set
class Disjoint_set
{
    int *parent, *rank, capacity;

    public:
        Disjoint_set(int capacity)
        {
            this->parent=new int[capacity];
            this->rank=new int[capacity];
            this->capacity=capacity;

            for(int i=0;i<capacity;++i) parent[i]=i, rank[i]=0;
        }

        int find(int id)
        {
            if(parent[id]!=id) parent[id]=find(parent[id]);
            return parent[id];
        }

        void unite(int i, int k)
        {
            int set_of_i=find(i), set_of_k=find(k);

            if(set_of_i==set_of_k) return;
            
            if(rank[set_of_i]<rank[set_of_k]) parent[set_of_i]=set_of_k;
            else if(rank[set_of_i]>rank[set_of_k]) parent[set_of_k]=set_of_i;
            else parent[set_of_i]=set_of_k, ++rank[set_of_k];
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

/////Binary Search using recursion
int first_occurence(vector<int>&a,int left,int right,int k)
{
    if(left>right) return -1;

    int m=left+(right-left)/2;

    if(a[m]==k)
    {
        if(m>0 and a[m-1]==k) return first_occurence(a,left,right-1,k);
        else return m;
    }
    else if(a[m]<k) return first_occurence(a,m+1,right,k);

    return first_occurence(a,left,m-1,k);
}

int last_occurence(vector<int>&a,int left, int right, int k)
{
    if(left>right) return -1;

    int m=left+(right-left)/2;

    if(a[m]==k)
    {
        if(m<a.size()-1 and a[m+1]==k) return last_occurence(a,left+1,right,k);
        else return m;
    }
    else if(a[m]<k) return last_occurence(a,m+1,right,k);

    return last_occurence(a,left,m-1,k);
}


//returns the first number that is greater than K
int Upper_bound(vector<int>&a,int left,int right,int k)
{
    if(left>right)
    {
        if(left==a.size()-1 and a[a.size()-1]<=k) ++left;
        return left;
    }

    int m=left+(right-left)/2;

    if(a[m]>k) return Upper_bound(a,left,m-1,k);
    return Upper_bound(a,m+1,right,k);
}


//retruns the first number that is equal or greater than K
int Lower_bound(vector<int>&a,int left, int right, int k)
{
    if(left>right)
    {
        if(left==a.size()-1 and a[a.size()-1]<k) ++left;
        return left;
    }

    int m=left+(right-left)/2;

    if(a[m]<k) return Lower_bound(a,m+1, right, k);
    return Lower_bound(a,left, m-1, k);
}


//returns the number of occurences
int count_occurence(vector<int>&a,int left, int right, int k)
{
    int left_index =  first_occurence(a,left, right, k);

    int right_index = last_occurence(a,left, right, k);

    if(left_index!=-1 and right_index!=-1) return right_index-left_index+1;
    return -1;
}

double square_root(double left, double right, double x)
{
    //cout<<left<<" "<<right<<" ";
    if(left>right) return left;

    double m=(double)left+((double)right-(double)left)/2.0; //cout<<m<<endl;

    if(abs(m*m-x)<0.0000001) return m;
    else if(m*m<x) return square_root(m,right,x);
    return square_root(left,m,x);
}

///////////////////////////////////////////////////////////////
///stacks in one array
class Stack_with_array
{
    int* a;
    int top1, top2, len1, len2;

    public:
        Stack_with_array(int n)
        {
            a=new int[n];
            len1=len2=0, top1=0, top2=n-1;
        }

        void push(int val_1=0, int stack_number_1=0, int val_2=0, int stack_number_2=0)
        {
            if(stack_number_1==1)
            {
                if(top1!=top2)
                {
                    a[top1]=val_1;
                    ++top1;
                    ++len1;
                }
            }

            if(stack_number_2==1)
            {
                if(top1!=top2)
                {
                    a[top2]=val_2;
                    --top2;
                    ++len2;
                }
            }
        }

        void pop(int stack_1=0, int stack_2=0)
        {
            if(stack_1==1)
            {
                if(len1>0)
                {
                    --top1;
                    --len1;
                }
            }

            if(stack_2==1)
            {
                if(len2>0)
                {
                    ++top2;
                    --len2;
                }
            }
        }

        int top_1()
        {
            if(len1>0) return a[top1-1];
            return INT_MIN;
        }

        int top_2()
        {
            if(len2>0) return a[top2+1];
            return INT_MIN;
        }
};

//////////////////////////////////////////////////////////////////////////////////
///Heap
class Heap
{
    int size, len;
    bool min_heap;
    int* a;

    protected:
        void heapify_up(int id)
        {
            while(id/2)
            {
                if(min_heap)
                {
                    if(a[id]<a[id/2]) swap(a[id],a[id/2]), id/=2;
                    else break;
                }
                else
                {
                    if(a[id]>a[id/2]) swap(a[id],a[id/2]), id/=2;
                    else break;
                }
            }
        }

        void heapify_down(int id)
        {
            while(2*id<size+1)
            {
                if(min_heap)
                {
                    if(2*id+1>size)
                    {
                        if(a[id]>a[2*id]) swap(a[2*id],a[id]), id=2*id;
                        else break;
                    }
                    else
                    {
                        if(a[id]>a[2*id] and a[id]>a[2*id+1])
                        {
                            int temp;
                            if(a[2*id]>a[2*id+1]) temp=2*id+1;
                            else temp=2*id;

                            swap(a[id],a[temp]), id=temp;
                        }
                        else if(a[id]>a[2*id]) swap(a[id],a[2*id]), id=2*id;
                        else if(a[id]>a[2*id+1]) swap(a[id],a[2*id+1]), id=2*id+1;
                        else break;
                    }
                }
                else
                {
                    if(2*id+1>size)
                    {
                        if(a[id]<a[2*id]) swap(a[2*id],a[id]), id=2*id;
                        else break;
                    }
                    else
                    {
                        if(a[id]<a[2*id] and a[id]<a[2*id+1])
                        {
                            int temp;
                            if(a[2*id]<a[2*id+1]) temp=2*id+1;
                            else temp=2*id;

                            swap(a[id],a[temp]), id=temp;
                        }
                        else if(a[id]<a[2*id]) swap(a[id],a[2*id]), id=2*id;
                        else if(a[id]<a[2*id+1]) swap(a[id],a[2*id+1]), id=2*id+1;
                        else break;
                    }
                }
            }
        }

    public:
        Heap(int len=10, string max_min="min")
        {
            this->len=len, size=0;
            this->min_heap= (max_min=="min"? true:false);
            a=new int[len+1];
        }

        void push(int x)
        {
            a[++size]=x;
            heapify_up(size);
        }

        void pop()
        {
            swap(a[1],a[size]);
            --size;
            heapify_down(1);
        }

        void heap_sort()
        {
            int temp=size;
            for(int i=0;i<temp-1;++i) pop();
            size=temp;
        }

        void build_heap()
        {
            for(int i=size/2;i>0;--i) heapify_down(i);
        }

        void convert()
        {
            min_heap=(min_heap)? false:true;
            build_heap();
        }

        int operator[](int id)
        {
            return a[id];
        }

        int heap_size()
        {
            return size;
        }

        ~Heap()
        {
            delete[] a;
        }
};


/////////////////////////////////////////////////////////////////////////////////////////////////
//quick sort
int partition(vector<int>&a, int start, int end)
{
    int n=end, i=start;
    for(int k=start;k<end;++k)
    {
        if(a[k]<=a[n-1]) swap(a[i++],a[k]);
    }
 
    return i-1;
}

void quick_sort(vector<int>&a, int start, int end)
{
    if(start<end)
    {
        int id= partition(a,start,end);
        //cout<<id<<endl;
        quick_sort(a,start,id);
        quick_sort(a,id+1,end);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////knapsack
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
    for(int i=0;i<prices.size()+1;++i) dp[0][i]=0;
    for(int i=0;i<capacity+1;++i) dp[i][0]=0;

    for(int i=1;i<capacity+1;++i)
    {
        for(int k=1;k<prices.size()+1;++k)
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