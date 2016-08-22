#include <iostream>
using namespace std;

/*
void bfs(vertex st)
{
    vector <vertex> vertQue;
    vertQue.push(st);
    st.setVisited(true);

    while (!vertQue.empty())
    {
        vertex temp = vertQue.front();
        vertQue.pop();

        for(auto itr = temp.begin(); itr != temp.end(); itr.getNext())
        {
            if (!itr.getVisited())
            {
                vertQue.push(itr);
                temp.setVisted(true);
            }
        }

    }
}

void dfs(vertex st)
{
    st.setVisited(true);

    for (auto itr = st.begin(); itr != st.end(); itr.getNext())
    {
        if (!itr.getVisited())
        {
            dfs(itr);
        }
    }
}
*/

struct Node
{
    int data;
    vector<Node*> links;
};

class Graph
{
    vector<Node*> nodes;
};

int main()
{
    cout << endl;
    return 0;
}
