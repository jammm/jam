
#ifndef UF_H
#define UF_H
class UF
{
	int id[200];
	int sz[200];
	int count;

public:

	UF(int x)
	{
		count = x;
		for(int i=0;i<x;i++)
		{
			id[i] = i;
			sz[i] = 1;
		}
		
	}
	bool connected(int u, int v)
	{
		return find(u) == find(v);
	}

	int find(int i)
	{
		while(id[i]!=i)
			i = id[i];
		return i;
	}

	void Union(int u,int v)
	{
		int i = find(u);
		int j = find(v);
		if(sz[i]<sz[j])
		{
			id[i] = j;
			sz[j] += sz[i];
		}
		else
		{
			id[j] = i;
			sz[i] += sz[j];
		}
		count--;
	}

};

		



#endif