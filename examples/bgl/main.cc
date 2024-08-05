#include "climb.h"
#include "grade_hueco.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/variant.hpp>

int main()
{
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, 
            boost::variant<Climb*, GradeHueco>, boost::no_property> Graph;

    Graph g;

    auto v1 = boost::add_vertex(g);
    auto v2 = boost::add_vertex(g);

    boost::add_edge(v1, v2, g);

    typedef boost::property_map<Graph, boost::vertex_index_t>::type VertexIndexMap;
    VertexIndexMap vertex_index_map = get(boost::vertex_index, g);

    std::shared_ptr<Climb> climb(Climb_new(), Climb_free);
    Climb_set_name(climb.get(), "The Cheat");

    GradeHueco grade { 7 };

    g[v1] = climb.get();
    g[v2] = grade;

    return 0;
}
