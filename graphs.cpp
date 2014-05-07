#include<iostream>
#include<queue>
#include<stack>
#include"minheap.h"
#include<stdlib.h>
#include"UF.h"
#include<vector>


class edge
{
public:
int u,v;
int w;
void add(int x,int y,int z)
{
	u = x;
	v = y;
	w = z;
}

bool operator<(const edge &rhs) const	//for sorting the vector, it uses the overloaded < operator.
{ return w < rhs.w; }

};



class graph
{
	node *head[10];
	bool visited[10];
	heap pq;
	int parent[10];
	int distTo[10];
	int size;
	stack<node*> sorted;
public:
	



	graph(const int &x):size(x)
	{
		for(int i=0;i<x;i++)
		{
			head[i] = new node(i);
			visited[i] = false;
			parent[i] = -1;
		}
	}

	int weight(const int &x,const int &y)
	{
		node *p = head[x];
		while(p->ele!=y)
			p = p->next;
		return p->w;
	}

	void insert(const int &x,const int &y,const int &w)
	{
		node *p = head[x];
		while(p->next)
		{
			p = p->next;
		}
		p->next = new node(y);
		p->next->w = w;
	}
	void insert_nw(int x,int y)
	{
		node *p = head[x];
		while(p->next)
		{
			p = p->next;
		}
		p->next = new node(y);
		
	}

	void BFS()
	{
		node *x = head[0];
		queue<node*> a;
		a.push(x);
		
		while(!a.empty())
		{
			x = a.front();
			x = head[x->ele];
			a.pop();
			if(!visited[x->ele])
			cout<<x->ele<<"\n";
			visited[x->ele] = true;
			while(x)
			{
				if(!visited[x->ele])
					a.push(x);
				x = x->next;
			}

		}
	}

	void DFS(node *x)
	{
		visited[x->ele] = true;
		cout<<x->ele<<"\n";
		while(x)
		{
			if(!visited[x->ele])
				DFS(head[x->ele]);
			x = x->next;
		}
	}

	void DFS()
	{
		for(int i=0;i<=size;i++)
			if(!visited[i])
				DFS(head[i]);
	}

	int w(int x, int y)
	{
		node *p = head[x];
		while(p->ele!=y)
			p = p->next;
		return p->w;
	}


	void display()
	{
		node *x = head[0];
		for(int i =0;i<size;i++)
		{
			x = head[i];
			while(x)
			{
				cout<<x->ele<<"->";
				x = x->next;
			}
			cout<<"\n";
		}
	}
	

	vector<edge> add_edges()
	{
		node *x = head[0];
		edge e;
		vector<edge> g_edges;
		for(int i=0;i<size;i++)
		{
			x = head[i]->next;
			while(x)
			{
				e.add(i,x->ele,x->w);
				g_edges.push_back(e);
				
				x = x->next;
			}
		}
		sort(g_edges.begin(),g_edges.end());
		return g_edges;
	}


	queue<edge> kruskals()
	{
		vector<edge> edges;
		queue<edge> mst;
		edges = add_edges();
		UF uf(size);
		for(int i=0;i<edges.size();i++)
		{
			edge e = edges[i];
			if(!uf.connected(e.u,e.v))
			{
				uf.Union(e.u,e.v);
				mst.push(e);
			}
		}
		return mst;
	}


	//use this for kruskals..it'll display all the edges in the MST
	void display_kruskals()
	{
		queue<edge> mst = kruskals();
		edge e;
		while(!mst.empty())
		{
			e = mst.front();
			mst.pop();
			cout<<e.u<<" "<<e.v<<"\n";
			
		}
	}
			
		


	void prims(int a)
	{
		
		for(int i=0;i<size;i++)
		{
			if(i==a)
			{
					head[a]->key = 0;
					pq.insert(head[a]);
			}
			else
			{
					head[i]->key = 999;
					pq.insert(head[i]);
			}
		}
		node *x = NULL,*p = NULL;
		while(!pq.empty())
		{
			x = pq.extract_min();
			p = x;
			while(x)
			{
				if(pq.isPresent(x)&&(x->w < head[x->ele]->key))
				{
					head[x->ele]->key = x->w;
					parent[x->ele] = p->ele;
					pq.build_min_heap();
					
				}
				x = x->next;
			//cout<<x->key<<" ";
			}
		}
	}
	
	
	void dijkstras(int s)
	{
		node *x = NULL;
		int p;
		for(int i=0;i<size;i++)
		{
			head[i]->key = 999;
		}
		head[s]->key = 0;
		for(int i=0;i<size;i++)
			pq.insert(head[i]);
		while(!pq.empty())
		{
			x = pq.extract_min();
			p = x->ele;
			x = x->next;
			while(x)
			{
				
				relax(p,x->ele,w(p,x->ele));
				x = x->next;
			}
		}
		
	}

	void relax(int u, int v, int w)
	{
		node *x = head[u];
		node *p = head[v];
		if(head[v]->key > head[u]->key + w)
		{
				head[v]->key = head[u]->key + w;
				pq.build_min_heap();
		}
	}




	

	//to display the MST for prim's algo, first call prims(), then this, y = parent[x] means edge in MST is (y,x)
	void foo()
	{
		int min = 0;
		for(int i=1;i<size;i++)
		{
			cout<<i<<":- "<<parent[i]<<"\n";
			min+=w(parent[i],i);
		}
		cout<<"\n\n"<<min;
	}


	//execute dijkstras(), then this.. it'll show the minimum weights from source vertex to i th vertex.
	void foo1()
	{
		
		for(int i=0;i<size;i++)
		{
			cout<<head[i]->ele<<"->"<<head[i]->key<<"\n"; // key stores the minimum weight from source to that (ith) vertex.
		}
	}

	void topological_visit(node *x)
	{
		visited[x->ele] = true;
		int i = x->ele;
		while(x)
		{
			if(!visited[x->ele])
				topological_visit(head[x->ele]);
			x = x->next;
		}
		sorted.push(head[i]);
	}


	void topological_sort()
	{
		for(int i=0;i<size;i++)
		{
			if(!visited[i])
				topological_visit(head[i]);
		}

		
	}

	void display_topo_sort()
	{
		node *x;
		topological_sort();
		while(!sorted.empty())
		{
			x = sorted.top();
			cout<<x->ele<<"\n";
			sorted.pop();
		}
	}



			

	


};




int main()
{
	graph a(9);
	vector<edge> b;
	edge aa;

	int x,y,w;
	while(cin>>x>>y>>w)
	{
		a.insert(x,y,w);
	}
	//a.BFS();
	a.prims(0);
	a.foo();
	



	//a.prims(0);

	//a.foo();

}

