#include <iostream>
#include <vector>
using namespace std;

// This is a Bi-Directional Graph
// http://stackoverflow.com/questions/39095527/how-to-achieve-forward-declaration-of-template-class

template <typename E>
class Graph
{
    private:
        template<typename T>
        class Vertex; // Forward Declaration

        vector<Vertex <E> > vertices;

        class Edge
        {
            public:
                Vertex<E>& _orig;

                Vertex<E>& _dest;
                uint32_t _weight;

                Edge(Vertex<E>& orig, Vertex<E>& dest, uint32_t weight) : _orig(orig),
                                                                          _dest(dest),
                                                                          _weight(weight) { }

                Vertex<E>& getOrig() { return _orig; }
                Vertex<E>& getDest() { return _dest; }
                uint32_t getWeight() { return _weight; }
        };

        template<typename T>
        class Vertex
        {
            public:
                T _data;
                vector<Edge> _edges;

                Vertex(T data) : _data(data) { }

                void addEdgeToVertex(Edge& edge)
                {
                    _edges.push_back(edge);
                }

                void printEdgesOfVertex()
                {
                    cout << _data << ":" << endl;
                    for(Edge e : _edges)
                    {
                        cout << endl;
                    }
                }
        };

    public:
        void addEdge(Vertex<E>& orig, Vertex<E>& dest, uint32_t weight)
        {
            Edge edge(orig, dest, weight);
            orig.addEdgeToVertex(edge);
            dest.addEdgeToVertex(edge);
        }

        void printEdges(Vertex<E>& vert)
        {
            vert.printEdgesOfVertex();
        }
};

int main()
{
    cout << endl;
    return 0;
}

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

