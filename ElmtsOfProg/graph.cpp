// Copy of dfs_graph. My code
#include <iostream>
#include <list>
#include <cstring>
#include <queue>
using namespace std;

class Graph
{
	int num_vertices;
	list<int> *adj_list;
	void DFS_Util(int, bool[]);
	public:
		Graph(int);
		void add_edge(int, int);	
		void DFS(int);	
		void BFS(int);
};

Graph::Graph(int n)
{
	num_vertices = n;
	adj_list = new list<int>[n];
}

void Graph::add_edge(int s, int v)
{
	adj_list[s].push_back(v);
}

void Graph::DFS_Util(int vertex, bool visited[])
{
	visited[vertex] = true;
	cout<<vertex<<"..";
	
	list<int>::iterator it = adj_list[vertex].begin();
	for(it; it != adj_list[vertex].end(); it++)
	{
		if(!visited[*it])
		{
			DFS_Util(*it,visited);
		}
	}
}

void Graph::DFS(int vertex)
{
	bool *visited = new bool[num_vertices];
	memset(visited, 0, sizeof(visited));	
	
	DFS_Util(vertex, visited);
}

void Graph::BFS(int vertex)
{
	bool *visited = new bool[num_vertices];
	memset(visited, 0, sizeof(visited));	

	queue<int> *bfs_q = new queue<int>[num_vertices];
	bfs_q->push(vertex);
	do
	{
		int temp_v = bfs_q->front();
		bfs_q->pop();
		cout<<temp_v<<"..";
		if(!visited[temp_v])
		{
			visited[temp_v] = true;
			list<int>::iterator it = adj_list[temp_v].begin();
			for(; it != adj_list[temp_v].end(); it++)
			{
				if(!visited[*it])
					bfs_q->push(*it);
			}
			
		}
	}while(!(bfs_q->empty()));
}

int main()
{
	Graph g(4);
	g.add_edge(0,1);
	g.add_edge(0,2);
	g.add_edge(1,2);
	g.add_edge(2,0);
	g.add_edge(2,3);
	g.add_edge(3,3);
	g.DFS(2);
	cout<<endl;
	g.BFS(2);
	cout<<endl;	
	/*Graph *g2 = new Graph(4);
	g2->add_edge(0,1);
	*/
	cout<<endl;
	return 0;
}
