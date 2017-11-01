#include<iostream>
using namespace std;
#include<stack>
#include<sstream>
#include<vector>
#include<queue>
#include<set>



class NFA_Node;

class Trans
{
	public:
		char incept;
		NFA_Node* des;	
		Trans(char incept,NFA_Node* des)
		{
			this->incept=incept;
			this->des=des;
		}
};

class NFA_Node
{
	public:
		int stateID;
		vector<Trans*> t;
		bool visit;
		NFA_Node(int stateID)
		{
			visit=false;
			this->stateID=stateID;	
		}
		void AddTrans(Trans* tt)
		{
			t.push_back(tt);
		}
		
}; 

class NFA
{
	public:
		NFA_Node* start;
		NFA_Node* end;
		NFA(){}
		NFA(int SID,char c)
		{
			NFA_Node* s1=new NFA_Node(SID);
			NFA_Node* s2=new NFA_Node(SID+1);
			Trans* tt=new Trans(c,s2);
			s1->AddTrans(tt);
			start=s1;
			end=s2;	
		}
	
};

class Converter
{
 	public:
        int S_ID;
        Converter(string str)
        {
            pretreat(str);
            Houzhui(this->lamb);
            S_ID=1;
        }
        Converter(){S_ID=1;}
        
        void show()
        {
            cout<<this->lamb<<endl;    
        }
        
        NFA ToNFA()
        {
            //stNFA.Clear();
            //Operator_Stack.Clear();
            NFA tempb,tempb1,tempb2;
           
            char tempc1;
            for(int i=0;i<lamb.size();i++)
            {
                tempc1 = lamb[i];
                if (isOperator(tempc1))
                {
                    switch (tempc1)
                    {
                        case '|':
                            tempb1 = stNFA.top();
                            stNFA.pop();
                            tempb2 = stNFA.top();
                            stNFA.pop();
                            tempb1=Union(tempb2,tempb1);
                            stNFA.push(tempb1);
                            break;
                        case '&':
                            tempb1 = stNFA.top();
                            stNFA.pop();
                            tempb2 = stNFA.top();
                            stNFA.pop();
                            tempb2=Connect(tempb1,tempb2);
                            stNFA.push(tempb2);
                            break;
                        case '*':
                            tempb1 = stNFA.top();
                            stNFA.pop();
                            tempb1=Closure(tempb1);
                            stNFA.push(tempb1);
                            break;
                    }
                }
                else
                {
                    tempb = NFA(S_ID,tempc1);
                    S_ID+=2;
                    stNFA.push(tempb);
                }
            }
            tempb = stNFA.top();
            stNFA.pop();
            return tempb;
        }
      
        
 	private:
        stack<NFA> stNFA;
        stack<char> Operator_Stack;
        string lamb;
        
        bool isOperator(char c)
        {
            switch (c)
            { 
                case '|':
                case '&':
                case '(':
                case ')':
                case '!':
                case '*': return true;
                default: return false;
            }
        }
        
        int getOperatorNumber(char t1)
        {
            switch (t1)
            {
                case '$': return 0;
                case '!': return 1;
                case ')': return 2;
                case '|': return 3;
                case '&': return 4;
                case '*': return 5;
                case '(': return 6;
                default: return 7;
            }
        }
        
        bool Operator_Less_Than(char t1, char t2)
        {
            int temp1 = getOperatorNumber(t1);
            int temp2 = getOperatorNumber(t2);
            if (temp1 <= temp2)
                return true;
            return false;
        }
        

        void pretreat(string str)//穿进去原始正则表达式 使ab变成a&b  
        {
        	int i=0;
        	char c,pc;
        
        	pc=str[i];
        	c=str[++i];
        	while(str[i]!='\0')
        	{
        		if(((pc==')'&&c=='('))||(!isOperator(pc)&&!isOperator(c))||(!isOperator(pc)&&c=='(')||(pc==')'&&!isOperator(c))||(pc=='*'&&!isOperator(c))||(pc=='*'&&c=='('))//四种情况需要加&	
        		str.insert(i,"&");
        		pc=str[i++];
        		c=str[i];
        	}
        	str+="!"; 
            this->lamb=str;	
        }
        
        
        void Houzhui(string lamb)
        {
            string l="";
            Operator_Stack.push('$');
            char tempc,tempc2;
          
            for(int i=0;i<lamb.size();i++)
            {
                tempc = lamb[i];
                if (isOperator(tempc))
                {
                    switch (tempc)
                    {
                        case '(': Operator_Stack.push(tempc); break;
                        case ')':
                            while (Operator_Stack.top() != '(')
                            {
                                tempc2 = Operator_Stack.top();
                                Operator_Stack.pop();
                                l += tempc2;
                            }
                            Operator_Stack.pop();
                            break;
                        default :
                            tempc2 = Operator_Stack.top();
                            while (tempc2!='('&&Operator_Less_Than(tempc,tempc2))
                            {
                                tempc2 = Operator_Stack.top();
                                Operator_Stack.pop();
                                l += tempc2;
                                tempc2 = Operator_Stack.top();
                            }
                            Operator_Stack.push(tempc);
                            break;
                    }
                }
                else
                    l += tempc;
            }
            this->lamb=l;
        }
    
        NFA& Connect(NFA G1, NFA G2) //把G1连在G2后面 
        {
			Trans* t=new Trans('@',G1.start);
			G2.end->AddTrans(t)	;		
  			G2.end = G1.end;
  			return G2;	
		}
        NFA& Union(NFA G1, NFA G2) //G1|G2
        {
			NFA_Node* n1=new NFA_Node(S_ID++);
			Trans* t1=new Trans('@',G1.start);
			Trans* t2=new Trans('@',G2.start);
			n1->AddTrans(t1);
			n1->AddTrans(t2);
			
			NFA_Node* n2=new NFA_Node(S_ID++);
			Trans* t3=new Trans('@',n2);
			Trans* t4=new Trans('@',n2);
			G1.end->AddTrans(t3);
			G2.end->AddTrans(t4);
			
			NFA* G=new NFA();
			G->start=n1;
			G->end=n2;
			
			return *G;
		}
        NFA& Closure(NFA G2) //G2*
        {
			Trans* t=new Trans('#',G2.start);//#表示是重复的空输入  
			G2.end->AddTrans(t);
			
			NFA_Node* n1=new NFA_Node(S_ID++);
			Trans* t1=new Trans('@',n1);
			G2.end->AddTrans(t1);
			
			NFA_Node* n2=new NFA_Node(S_ID++);
			Trans* t2=new Trans('@',G2.start);
			n2->AddTrans(t2);
			

			Trans* t3=new Trans('@',n1);
			n2->AddTrans(t3);
			
			NFA* G=new NFA();
			G->start=n2;
			G->end=n1;
			
			
  			return *G;			
		}
};

void Display(NFA &G,set<char> &S,vector<NFA_Node*> &V)
{
	cout<<"正则表达式转NFA"<<endl; 
	queue<NFA_Node*> MyQueue;
	MyQueue.push(G.start);
	cout<<"开始状态"<<G.start->stateID<<endl;
	char tt;
	while(!MyQueue.empty())
	{ 
		NFA_Node* tmp=MyQueue.front();
		MyQueue.pop();
		V.push_back(tmp);
		tmp->visit=true;
		if(tmp->t.size()>0)
		cout<<"从状态"<<tmp->stateID<<"出发"<<endl;
		if(tmp->t.size()>0)
		for(int i =0;i<tmp->t.size();i++)
		{
			tt=tmp->t[i]->incept;
			if(tt!='@'&&tt!='#')
			S.insert(tt);
			if(tt=='@') 
			{
				cout<<tmp->stateID<<"---"<<"epsilon"<<"--->"<<tmp->t[i]->des->stateID;
				if(tmp->t[i]->des->t.size()==0) cout<<"接收状态";
				cout<<endl;
				if(tmp->t[i]->des->visit==false)
				{MyQueue.push(tmp->t[i]->des);tmp->t[i]->des->visit=true;}
			}
			else if(tt=='#')
			{
				cout<<tmp->stateID<<"---"<<"epsilon回到"<<"--->"<<tmp->t[i]->des->stateID<<endl;	
			}
			else
			{
				cout<<tmp->stateID<<"---"<<tt<<"--->"<<tmp->t[i]->des->stateID;
				if(tmp->t[i]->des->t.size()==0) cout<<"接收状态";
				cout<<endl;
				if(tmp->t[i]->des->visit==false)
				{MyQueue.push(tmp->t[i]->des);tmp->t[i]->des->visit=true;}
			}
		}	
	}
	cout<<"接收状态"<<G.end->stateID<<endl;
}

class DFA_Edge;

class DFA_Node
{
	public:
		int stateID;
		vector<DFA_Edge*> t;
		vector<int> ori;
		bool flag;
		DFA_Node(int s)
		{
			flag=false;
			stateID=s;	
		}
};

class DFA_Edge
{
	public:
		char incept;
		DFA_Node* des;
		bool visit;
		DFA_Edge(char a,DFA_Node* &b)
		{
			incept=a;
			des=b;
			visit=false;
		}
};





const int MAX=100;
class NFA_To_DFA
{
	public:
		int MaxStatus;
		int T[MAX][MAX];
		int visit[MAX];
		vector<NFA_Node*> tmp;
		set<char> Alpha;
		vector<NFA_Node*> nfa;
		NFA_Node* start; 
		vector<DFA_Node*> dfa;
		int cando;//存NFA的接收状态 
		
		NFA_To_DFA(int max,NFA_Node* &S,int cando)
		{
			this->MaxStatus=max;
			this->start=S;	
			this->cando=cando;
			Init();
			for(int i=0;i<=MAX;i++)
			for(int j=0;j<=MAX;j++)
			T[i][j]=0;	
		}
		void Init()
		{
			for(int i=0;i<=this->MaxStatus;i++)
			{
				this->visit[i]=0;
			}
			this->tmp.clear();	
		}
		NFA_Node*& find(int st)
		{
			for(int i=0;i<nfa.size();i++)
			if(nfa[i]->stateID==st) return nfa[i];	
		}
		DFA_Node*& finddfa(int st)
		{
			for(int i=0;i<dfa.size();i++)
			if(dfa[i]->stateID==st) return dfa[i];	
		}
		
		void findclosure(NFA_Node* p)
		{
			visit[p->stateID]=1;
			visit[0]++;	
			if(p->t.size()==0) return;
			for(int i=0;i<p->t.size();i++)
			{
				if(!visit[p->t[i]->des->stateID]&&(p->t[i]->incept=='#'||p->t[i]->incept=='@'))
				findclosure(p->t[i]->des);	
			}
		}
		void closure()
		{
			for(int i=0;i<tmp.size();i++)
			{
				findclosure(tmp[i]);	
			}	
		}
		
		
		int AddStatus()//T[0][0]当前状态集合数 初始为0 
		{
		    if(visit[0]==0)//表示没有状态
			return -2; 
			for(int i=1;i<=T[0][0];i++)  
		    {  
				if(visit[0]!=T[i][0])//此集合状态数不一样 则跳过 
				continue;
		    	int j=1;
				for(;j<=MaxStatus;j++)  
		        if(visit[j]!=T[i][j])//有一个状态不一样 则跳过  
		                    break;  
		        if(j==(MaxStatus+1))  //说明矩阵T中已有此集合,并返回位置  
		                return i;        
		    }  
		    T[0][0]++;  
		    for(int i=0;i<=MaxStatus;i++)  
		        T[T[0][0]][i]=visit[i];
				
		//	cout<<T[T[0][0]][0];
		    return -1;               	
		}//返回-1表示插入了新状态集合
		 
		void moveto(int st,char c)
		{
		//	if(st==2) cout<<T[st][0]<<endl;
			for(int i=1;i<=MaxStatus;i++)
			{
				if(T[st][i])
				{
					NFA_Node* p=find(i); 
					if(p->t.size()>0)
					for(int j=0;j<p->t.size();j++)	
					if(p->t[j]->incept==c)
					{tmp.push_back(p->t[j]->des);}//cout<<c<<" "; cout<<p->t[j]->des->stateID<<endl;}
				}
			}
		}
		 
		void Convert()
		{
			int i,j;
			
			findclosure(start);	
			AddStatus();
			DFA_Node* s1=new DFA_Node(1);
			if(visit[cando]) s1->flag=true;
			for(i=1;i<=MaxStatus;i++)
			if(visit[i]) s1->ori.push_back(i);
			
			dfa.push_back(s1);
			Init();
			//cout<<Alpha.size();
			for(i=1;i<=T[0][0];i++)//i目前的状态集合号 
			{
				for(set<char>::iterator t1=Alpha.begin();t1!=Alpha.end();t1++)	
				{
					moveto(i,*t1);
					closure();
					if((j=AddStatus())>=0)//没有新状态产生 
					{
						DFA_Edge* e1=new DFA_Edge(*t1,finddfa(j));
						finddfa(i)->t.push_back(e1);	
							
					}
					else if(j==-1)//产生了新状态 
					{
						DFA_Node* d1=new DFA_Node(T[0][0]);
						if(visit[cando]) d1->flag=true;//是否是接收状态 
						for(int tt=1;tt<=MaxStatus;tt++)
						if(visit[tt]) d1->ori.push_back(tt);//把原状态加进去 
						dfa.push_back(d1);
						DFA_Edge* e1=new DFA_Edge(*t1,finddfa(T[0][0]));
						finddfa(i)->t.push_back(e1);
				//		cout<<T[0][0]<<endl;
					}

					Init();	
				}
			}						
		}
		
		void show(DFA_Node* p)
		{
			if(p->ori.size()==0) return;
			cout<<"(原状态";
			for(int i=0;i<p->ori.size();i++)
			cout<<p->ori[i];
			cout<<")";
		}
		
		void Display()
		{
			cout<<"NFA转DFA"<<endl; 
			for(int i=0;i<dfa.size();i++)
			dfs(dfa[i]);	
		}
				
		void dfs(DFA_Node* &p)
		{
			if(p->t.size()>0)
			for(int i=0;i<p->t.size();i++)
			if(p->t[i]->visit==false)
			{
				cout<<p->stateID;
				if(p->flag) cout<<"(接收状态)";
				show(p);
				cout<<"---"<<p->t[i]->incept<<"--->"<<p->t[i]->des->stateID;
				show(p->t[i]->des);
				if(p->t[i]->des->flag) cout<<"(接收状态)";
				cout<<endl;
				p->t[i]->visit=true;
				dfs(p->t[i]->des);
			}
		}
};

int main()
{
	string str;
	char s[100];
	while(gets(s))
	{
		str=s;
		Converter cnt(str);
       // cnt.show();
		NFA result=cnt.ToNFA();
		
		NFA_To_DFA ntd(cnt.S_ID-1,result.start,result.end->stateID);
		
	//	cout<<result.start->stateID;
	//	cout<<result.start->t.size();
		
		Display(result,ntd.Alpha,ntd.nfa);
		
		ntd.Convert();
		
		ntd.Display();
	}
	while(1);
}




