#include <iostream>
#include "info_constructor.h"
#include "graph_constructor.h"
using namespace std;
int main()
{
    // get data path and read data
    string airport_data, routes_data, airlines_data;
    cout << "Your airport data source path: (enter nothing if using default data)" << endl;
    getline(cin, airport_data);
    if (airport_data == "")
        airport_data = "../data/airports.txt";
    cout << "Your routes data source path: (enter nothing if using default data)" << endl;
    getline(cin, routes_data);
    if (routes_data == "")
        routes_data = "../data/routes.txt";
    cout << "Your airlines data source path: (enter nothing if using default data)" << endl;
    getline(cin, airlines_data);
    if (airlines_data == "")
        airlines_data = "../data/airlines.txt";
    info_container information(airport_data, routes_data, airlines_data);

    information.read();
    information.clean();
    // load data to graph calculator
    vector<Vertex> airports = information.generate_vertices();
    vector<pair<Vertex, Vertex>> routes = information.generate_edges();
    vector<double> dist = information.calculate_dist();
    graph_container calculator(airports, routes, dist);
    string start, end;
    // get departure and arrival airports
    bool find = false;
    while (find == false)
    {
        cout << "Your place of departure:" << endl;
        getline(cin, start);
        start = "\"" + start + "\"";
        for (auto it = airports.begin(); it != airports.end(); ++it)
        {
            if (*it == start)
                find = true;
        }
        if (find == false)
        {
            cout << "Invalid Input!" << endl;
        }
    }
    find = false;
    while (find == false)
    {
        cout << "Your destination:" << endl;
        getline(cin, end);
        end = "\"" + end + "\"";
        for (auto it = airports.begin(); it != airports.end(); ++it)
        {
            if (*it == start)
                find = true;
        }
        if (find == false)
        {
            cout << "Invalid Input!" << endl;
        }
    }
    // print out output calculated
    vector<Vertex> min_transfer = calculator.solvebyBFS(start, end);
    vector<Vertex> min_dist = calculator.solvebyDij(start, end);
    vector<Vertex> min_deltaStepping = calculator.solvebyDeltaStepping(start, end);
    vector<string> min_transfer_airlineinfo = information.airlineinfo(min_transfer);
    vector<string> min_dist_airlineinfo = information.airlineinfo(min_dist);
    vector<string> min_deltaStepping_airlineinfo = information.airlineinfo(min_deltaStepping);
    cout << "\n"
         << "minimum transfer route:" << endl;
    for (auto it = min_transfer.begin(); it != min_transfer.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "Airlines available for corresponding route section: " << endl;
    for (unsigned idx = 0; idx < min_transfer_airlineinfo.size(); idx++)
    {
        cout << "Section" << idx + 1 << ": " << min_transfer_airlineinfo[idx] << endl;
    }
    cout << "\n"
         << "minimum distance route:" << endl;
    for (auto it = min_dist.begin(); it != min_dist.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "Airlines available for corresponding route section: " << endl;
    for (unsigned idx = 0; idx < min_dist_airlineinfo.size(); idx++)
    {
        cout << "Section" << idx + 1 << ": " << min_dist_airlineinfo[idx] << endl;
    }
    cout << "\n"
         << "minimum deltaStepping route:" << endl;
    for (auto it = min_deltaStepping.begin(); it != min_deltaStepping.end(); ++it)
    {
        cout << *it << endl;
    }
    cout << "Airlines available for corresponding route section: " << endl;
    for (unsigned idx = 0; idx < min_deltaStepping_airlineinfo.size(); idx++)
    {
        cout << "Section" << idx + 1 << ": " << min_deltaStepping_airlineinfo[idx] << endl;
    }
    return 0;
}
