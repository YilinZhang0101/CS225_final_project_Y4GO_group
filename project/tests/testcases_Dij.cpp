#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "graph_constructor.h"

using namespace std;

vector<Vertex> large_graph_path_unweighted(Vertex start, Vertex end)
{
    vector<Vertex> airports{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    vector<pair<Vertex, Vertex>> edges{
        pair<Vertex, Vertex>("a", "b"),
        pair<Vertex, Vertex>("a", "c"),
        pair<Vertex, Vertex>("a", "j"),
        pair<Vertex, Vertex>("a", "g"),
        pair<Vertex, Vertex>("b", "y"),
        pair<Vertex, Vertex>("b", "f"),
        pair<Vertex, Vertex>("b", "p"),
        pair<Vertex, Vertex>("c", "x"),
        pair<Vertex, Vertex>("c", "n"),
        pair<Vertex, Vertex>("c", "l"),
        pair<Vertex, Vertex>("d", "a"),
        pair<Vertex, Vertex>("g", "i"),
        pair<Vertex, Vertex>("g", "w"),
        pair<Vertex, Vertex>("g", "j"),
        pair<Vertex, Vertex>("h", "r"),
        pair<Vertex, Vertex>("i", "m"),
        pair<Vertex, Vertex>("i", "s"),
        pair<Vertex, Vertex>("j", "e"),
        pair<Vertex, Vertex>("j", "u"),
        pair<Vertex, Vertex>("j", "v"),
        pair<Vertex, Vertex>("k", "w"),
        pair<Vertex, Vertex>("l", "t"),
        pair<Vertex, Vertex>("o", "d"),
        pair<Vertex, Vertex>("p", "y"),
        pair<Vertex, Vertex>("q", "p"),
        pair<Vertex, Vertex>("q", "f"),
        pair<Vertex, Vertex>("r", "z"),
        pair<Vertex, Vertex>("u", "e"),
        pair<Vertex, Vertex>("v", "k"),
        pair<Vertex, Vertex>("y", "o"),
        pair<Vertex, Vertex>("z", "h"),
    };
    vector<double> distances = vector<double>(edges.size(), 1);
    graph_container graph(airports, edges, distances);
    vector<Vertex> path = graph.solvebyDij(start, end);
    return path;
}
//**need modification on weight
vector<Vertex> large_graph_path_weighted(Vertex start, Vertex end)
{
    vector<Vertex> airports{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    vector<pair<Vertex, Vertex>> edges{
        pair<Vertex, Vertex>("a", "b"),//1
        pair<Vertex, Vertex>("a", "c"),//2
        pair<Vertex, Vertex>("a", "j"),//3
        pair<Vertex, Vertex>("a", "g"),//1
        pair<Vertex, Vertex>("b", "y"),//1
        pair<Vertex, Vertex>("b", "f"),//2
        pair<Vertex, Vertex>("b", "p"),//1
        pair<Vertex, Vertex>("c", "x"),//2
        pair<Vertex, Vertex>("c", "n"),//2
        pair<Vertex, Vertex>("c", "l"),//1
        pair<Vertex, Vertex>("d", "a"),//2
        pair<Vertex, Vertex>("g", "i"),//2
        pair<Vertex, Vertex>("g", "w"),//15
        pair<Vertex, Vertex>("g", "j"),//1
        pair<Vertex, Vertex>("h", "r"),//1
        pair<Vertex, Vertex>("i", "m"),//1
        pair<Vertex, Vertex>("i", "s"),//1
        pair<Vertex, Vertex>("j", "e"),//7
        pair<Vertex, Vertex>("j", "u"),//1
        pair<Vertex, Vertex>("j", "v"),//6
        pair<Vertex, Vertex>("k", "w"),//2
        pair<Vertex, Vertex>("l", "t"),//2
        pair<Vertex, Vertex>("o", "d"),//3
        pair<Vertex, Vertex>("p", "y"),//1
        pair<Vertex, Vertex>("q", "p"),//2
        pair<Vertex, Vertex>("q", "f"),//1
        pair<Vertex, Vertex>("r", "z"),//1
        pair<Vertex, Vertex>("u", "e"),//1
        pair<Vertex, Vertex>("v", "k"),//1
        pair<Vertex, Vertex>("y", "o"),//1
        pair<Vertex, Vertex>("z", "h"),//1
    };
    vector<double> distances = {1, 2, 3, 1, 1, 2, 1, 2, 2, 1,  2, 2, 15, 1, 1, 1, 1, 7, 1,6, 2, 2, 3, 1, 2, 1, 1, 1, 1, 1, 1};
    graph_container graph(airports, edges, distances);
    vector<Vertex> path = graph.solvebyDij(start, end);
    return path;
}

TEST_CASE("Dij works on small graph with all out directing unweighted graph", "[weight=0][part=3]")
{

    vector<Vertex> airports{"a", "b", "c", "d", "e", "f", "g"};
    vector<pair<Vertex, Vertex>> edges{
        pair<Vertex, Vertex>("a", "b"),
        pair<Vertex, Vertex>("a", "c"),
        pair<Vertex, Vertex>("a", "d"),
        pair<Vertex, Vertex>("a", "e"),
        pair<Vertex, Vertex>("a", "f"),
        pair<Vertex, Vertex>("b", "g")};
    vector<double> distances = vector<double>(edges.size(), 1);
    graph_container graph(airports, edges, distances);
    vector<Vertex> path = graph.solvebyDij("a", "g");
    REQUIRE(path.size() == 3);
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "g");
}

TEST_CASE("Dij works on small graph with undirected unweighted graph", "[weight=0][part=3]")
{
    /*
       same graph structure of above graph, but undirected edges
    */
    vector<Vertex> airports{"a", "b", "c", "d", "e", "f", "g"};
    vector<pair<Vertex, Vertex>> edges{
        pair<Vertex, Vertex>("a", "b"),
        pair<Vertex, Vertex>("a", "b"),
        pair<Vertex, Vertex>("a", "c"),
        pair<Vertex, Vertex>("c", "a"),
        pair<Vertex, Vertex>("a", "d"),
        pair<Vertex, Vertex>("d", "a"),
        pair<Vertex, Vertex>("a", "e"),
        pair<Vertex, Vertex>("e", "a"),
        pair<Vertex, Vertex>("a", "f"),
        pair<Vertex, Vertex>("f", "a"),
        pair<Vertex, Vertex>("b", "g"),
        pair<Vertex, Vertex>("g", "b")};
    vector<double> distances = vector<double>(edges.size(), 1);
    graph_container graph(airports, edges, distances);
    vector<Vertex> path = graph.solvebyDij("a", "g");
    REQUIRE(path.size() == 3);
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "g");
}

TEST_CASE("Dij works on larger unweighted graph for unreachable vertex", "[weight=0][part=3]")
{
    vector<Vertex> path = large_graph_path_weighted("a", "h");
    REQUIRE(path[0] == "Destination not reachable!");
    vector<Vertex> path1 = large_graph_path_weighted("a", "q");
    REQUIRE(path1[0] == "Destination not reachable!");
}

TEST_CASE("Dij works on larger unweighted graph for reachable vertex", "[weight=0][part=3]")
{

    vector<Vertex> path = large_graph_path_unweighted("a", "d");
    REQUIRE(path.size() == 5);
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "y");
    REQUIRE(path[3] == "o");
    REQUIRE(path[4] == "d");
    vector<Vertex> path1 = large_graph_path_unweighted("a", "w");
    REQUIRE(path1.size() == 3);
    REQUIRE(path1[0] == "a");
    REQUIRE(path1[1] == "g");
    REQUIRE(path1[2] == "w");
}

// test on weighted graph **need modification
TEST_CASE("Dij works on small graph with all out directing weighted graph", "[weight=0][part=3]")
{

    vector<Vertex> airports{"a", "b", "c", "d", "e", "f", "g"};
    vector<pair<Vertex, Vertex>> edges{
        pair<Vertex, Vertex>("a", "b"),
        pair<Vertex, Vertex>("a", "c"),
        pair<Vertex, Vertex>("a", "d"),
        pair<Vertex, Vertex>("a", "e"),
        pair<Vertex, Vertex>("a", "f"),
        pair<Vertex, Vertex>("b", "g")};
    vector<double> distances = {2, 2, 3, 3, 3, 4};
    graph_container graph(airports, edges, distances);
    vector<Vertex> path = graph.solvebyDij("a", "g");
    REQUIRE(path.size() == 3);
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "g");
}

TEST_CASE("Dij works  on small graph with undirected weighted graph", "[weight=0][part=3]")
{
    /*
       same graph structure of above graph, but undirected edges
    */
    vector<Vertex> airports{"a", "b", "c", "d", "e", "f", "g"};
    vector<pair<Vertex, Vertex>> edges{
        pair<Vertex, Vertex>("a", "b"),
        pair<Vertex, Vertex>("a", "b"),
        pair<Vertex, Vertex>("a", "c"),
        pair<Vertex, Vertex>("c", "a"),
        pair<Vertex, Vertex>("a", "d"),
        pair<Vertex, Vertex>("d", "a"),
        pair<Vertex, Vertex>("a", "e"),
        pair<Vertex, Vertex>("e", "a"),
        pair<Vertex, Vertex>("a", "f"),
        pair<Vertex, Vertex>("f", "a"),
        pair<Vertex, Vertex>("b", "g"),
        pair<Vertex, Vertex>("g", "b")};
    vector<double> distances = {2, 2, 1, 1, 5, 5, 4, 4, 3, 3, 8, 8};
    graph_container graph(airports, edges, distances);
    vector<Vertex> path = graph.solvebyDij("a", "g");
    REQUIRE(path.size() == 3);
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "g");
}

TEST_CASE("Dij works on larger weighted graph for unreachable vertex", "[weight=0][part=3]")
{

    vector<Vertex> path = large_graph_path_weighted("a", "h");
    REQUIRE(path[0] == "Destination not reachable!");
    vector<Vertex> path1 = large_graph_path_weighted("a", "q");
    REQUIRE(path1[0] == "Destination not reachable!");
}

TEST_CASE("Dij works on larger weighted graph for reachable vertex", "[weight=0][part=3]")
{
    vector<Vertex> path = large_graph_path_weighted("a", "d");
    REQUIRE(path.size() == 5);
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "y");
    REQUIRE(path[3] == "o");
    REQUIRE(path[4] == "d");
    vector<Vertex> path1 = large_graph_path_weighted("a", "w");
    REQUIRE(path1.size() == 6);
    REQUIRE(path1[0] == "a");
    REQUIRE(path1[1] == "g");
    REQUIRE(path1[2] == "j");
    REQUIRE(path1[3] == "v");
    REQUIRE(path1[4] == "k");
    REQUIRE(path1[5] == "w");
}

TEST_CASE("More Dij works on larger weighted graph for reachable vertex", "[weight=0][part=3]")
{
    vector<Vertex> path = large_graph_path_weighted("a", "y");
    REQUIRE(path.size() == 3);
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "y");
    vector<Vertex> path1 = large_graph_path_weighted("a", "l");
    REQUIRE(path1.size() == 3);
    REQUIRE(path1[0] == "a");
    REQUIRE(path1[1] == "c");
    REQUIRE(path1[2] == "l");
}

TEST_CASE("Further Dij works on larger weighted graph for reachable vertex", "[weight=0][part=3]")
{
    vector<Vertex> path = large_graph_path_weighted("d", "e");
    REQUIRE(path.size() == 6);
    REQUIRE(path[0] == "d");
    REQUIRE(path[1] == "a");
    REQUIRE(path[2] == "g");
    REQUIRE(path[3] == "j");
    REQUIRE(path[4] == "u");
    REQUIRE(path[5] == "e");
    vector<Vertex> path1 = large_graph_path_weighted("d", "f");
    REQUIRE(path1.size() == 4);
    REQUIRE(path1[0] == "d");
    REQUIRE(path1[1] == "a");
    REQUIRE(path1[2] == "b");
    REQUIRE(path1[3] == "f");
    vector<Vertex> path2 = large_graph_path_weighted("j", "e");
    REQUIRE(path2.size() == 3);
    REQUIRE(path2[0] == "j");
    REQUIRE(path2[1] == "u");
    REQUIRE(path2[2] == "e");
}