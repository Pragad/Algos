#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>   // Contains function for hash
using namespace std;

// Used to print out additionals log messages
#define DEBUG

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

// This is a Bi-Directional Graph
// http://stackoverflow.com/questions/39095527/how-to-achieve-forward-declaration-of-template-class
//      If you use Graph like Graph<std::string> g;, then the template parameter E will be std::string, the member vertices will be vector<Vertex<std::string>>.
//      Then in Vertex, _data will be std::string, _edges will be vector<Edge<std::string>>

template <typename E>
class Graph
{
    private:
        template<typename T>
        class Vertex; // Forward Declaration

        // Have a vector to store all Vertices of the Graph
        // MAP:
        //      The map is used to quickly tell if a Vertices is present or not based on the the
        //      data. 
        //      Key: hash(data) given to Vertex
        //      Val: Place where Vertex is stored on the Vector
        //
        //      So with a Vertex's data, we can hash it to get the Key.
        //      Using the key, find if Vertex is present; Also where the Vertex is present
        //
        // The map also gives where the Vertex is stored in the vector
// http://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
// Check the above link for properly doing it
        vector<Vertex <E> > _vertices;
        unordered_map<uint32_t, uint32_t> _verticesMap;

        // Inner Class corresponding to an Edge of a graph.
        // Each edge has
        //      1) Origin
        //      2) Destination
        //      3) Weight
        // Using the Edge, you can get its origin, destination or its weight
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

        // Inner Class for Vertex of a Graph
        // Each Vertex has,
        //      1) _id
        //      2) Data
        //      3) List of edges
        // Using a Vertex you can,
        //      - add Edge to the Vertex
        //      - print all Edges of the Vertex
        template<typename T>
        class Vertex
        {
            public:
                uint32_t _id;   // A unique identifier for each node
                T _data;
                vector<Edge> _edges;

                Vertex(T data)
                {
                    uint32_t hashVal = std::hash<E>()(data);

                    _id = hashVal;
                    _data = data;
                }

                Vertex(uint32_t id, T data) : _id(id),
                                              _data(data) { }

                void addEdgeToVertex(Edge& edge)
                {
                    _edges.push_back(edge);
                }

                void printEdgesOfVertex()
                {
                    cout << _data << ":" << endl;
                    for(Edge e : _edges)
                    {
                        cout << e.getDest()._data << " : " << e.getWeight() << endl;
                    }
                }
        };

        // From a Graph class you can,
        //      - add Edge between two vertices
        //      - add a Vertex to the graph
        //      - print all Edges of a Vertex
        //      - print the Graph
    public:
        void addEdge(Vertex<E>& orig, Vertex<E>& dest, uint32_t weight)
        {
            Edge edge(orig, dest, weight);
            orig.addEdgeToVertex(edge);
            dest.addEdgeToVertex(edge);
        }

        void addEdge(E& orig, E& dest, uint32_t weight)
        {
            Vertex<E> v1;
            Vertex<E> v2;

            // Get Vertex from 'orig'
            uint32_t hashVal1 = std::hash<E>()(orig);
            auto itr1 = _verticesMap.find(hashVal1);
            if (itr1 != _verticesMap.end())
            {
                v1 = _vertices[itr1->second];
            }
            else
            {
                // We don't have this Vertex. So add this Vertex first
                DEBUG_MSG("Adding Vertex 1 to Graph" << endl);
                addVertex(orig);

                // The new Vertex will be the last element in the Vector
                addEdge(orig, dest, weight);
                v1 = _vertices[_vertices.size() - 1];
            }

            // Get Vertex from 'dest'
            uint32_t hashVal2 = std::hash<E>()(dest);
            auto itr2 = _verticesMap.find(hashVal2);
            if (itr2 != _verticesMap.end())
            {
                v2 = _vertices[itr2->second];
            }
            else
            {
                // We don't have this Vertex. So add this Vertex first
                DEBUG_MSG("Adding Vertex 2 to Graph" << endl);
                addVertex(dest);

                // The new Vertex will be the last element in the Vector
                addEdge(orig, dest, weight);
                v2 = _vertices[_vertices.size() - 1];
            }

            // If we are here, we will have both v1 and v2
            addEdge(v1, v2, weight);
        }

        // IMP: Add template arguement
        void addVertex(E data)
        {
            uint32_t hashVal = std::hash<E>()(data);
            auto itr = _verticesMap.find(hashVal);

            if (itr != _verticesMap.end())
            {
                DEBUG_MSG("Node Already Present at: " << itr->second << endl);
                return;
            }

            Vertex<E> vert(hashVal, data);
            _vertices.push_back(vert);

            DEBUG_MSG("Hash Val for: " << data << " : " << hashVal << endl);
            _verticesMap[hashVal] =  _vertices.size() - 1;
        }

        void printEdges(Vertex<E>& vert)
        {
            vert.printEdgesOfVertex();
        }

        void printGraph()
        {
            for (auto vert : _vertices)
            {
                vert.printEdgesOfVertex();
            }
        }
};

int main()
{
    Graph<string> g;
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");

    string a1 = "A";
    string b1 = "B";
    g.addEdge(a1, b1, 1);


    g.printGraph();
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

