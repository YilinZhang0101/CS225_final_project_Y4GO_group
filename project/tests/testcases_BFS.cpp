#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "graph_constructor.h"

using namespace std;

vector<Vertex> large_graph_path(Vertex start, Vertex end)
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
    graph_container graph(airports, edges);
    vector<Vertex> path = graph.solvebyBFS(start, end);
    return path;
}
TEST_CASE("BFS works on small graph with all out directing graph", "[weight=0][part=2]")
{
    vector<Vertex> airports{"a", "b", "c", "d", "e", "f", "g"};
    vector<pair<Vertex, Vertex>> edges{
        pair<Vertex, Vertex>("a", "b"),
        pair<Vertex, Vertex>("a", "c"),
        pair<Vertex, Vertex>("a", "d"),
        pair<Vertex, Vertex>("a", "e"),
        pair<Vertex, Vertex>("a", "f"),
        pair<Vertex, Vertex>("b", "g")};
    graph_container graph(airports, edges);
    vector<Vertex> path = graph.solvebyBFS("a", "g");
    REQUIRE(path.size() == 3);
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "g");
}

TEST_CASE("BFS works on small graph with undirected graph", "[weight=0][part=2]")
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
    graph_container graph(airports, edges);
    vector<Vertex> path = graph.solvebyBFS("a", "g");
    REQUIRE(path.size() == 3);
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "g");
}

TEST_CASE("BFS works on larger graph for unreachable vertex", "[weight=0][part=2]")
{
    vector<Vertex> path = large_graph_path("a", "h");
    REQUIRE(path[0] == "Destination not reachable!");
    vector<Vertex> path1 = large_graph_path("a", "q");
    REQUIRE(path1[0] == "Destination not reachable!");
}

TEST_CASE("BFS works on larger graph for reachable vertex", "[weight=0][part=2]")
{
    vector<Vertex> path = large_graph_path("a", "d");
    REQUIRE(path.size() == 5);
    REQUIRE(path[0] == "a");
    REQUIRE(path[1] == "b");
    REQUIRE(path[2] == "y");
    REQUIRE(path[3] == "o");
    REQUIRE(path[4] == "d");
    vector<Vertex> path1 = large_graph_path("a", "w");
    REQUIRE(path1.size() == 3);
    REQUIRE(path1[0] == "a");
    REQUIRE(path1[1] == "g");
    REQUIRE(path1[2] == "w");
}