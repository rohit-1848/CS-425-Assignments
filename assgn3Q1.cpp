/*
Compile the code using the command: g++ -std=c++14 assgn3Q1.cpp -o assgn3Q1
Run the code using the command: ./assgn3Q1
and then the user will be prompted to enter the source and destination vertices.
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 10000000;

void dijkstras(vector<vector<pair<int, int>>> &adjList, vector<int> &dist, vector<int> &par, int src)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({dist[src], src});
    while (!pq.empty())
    {
        pair<int, int> pqTop = pq.top();
        pq.pop();
        int currSrc = pqTop.second;
        int currDist = pqTop.first;
        for (auto &currChild : adjList[currSrc])
        {
            if (currDist + currChild.second < dist[currChild.first])
            {
                pq.push({(currDist + currChild.second), currChild.first});
                dist[currChild.first] = currDist + currChild.second;
                par[currChild.first] = currSrc;
            }
        }
    }
}

void bellmanFord(vector<vector<pair<int, int>>> &adjList, vector<int> &dist, vector<int> &par, int src)
{
    int totNodes = adjList.size();
    vector<vector<int>> edges;
    for (int currPar = 0; currPar < totNodes; currPar++)
    {
        for (auto &currChild : adjList[currPar])
        {
            edges.push_back({currPar, currChild.first, currChild.second});
        }
    }
    int totEdges = edges.size();
    for (int i = 0; i < totNodes - 1; i++)
    {
        for (int j = 0; j < totEdges; j++)
        {
            int currPar = edges[j][0], currChild = edges[j][1], currWeight = edges[j][2];
            if (dist[currPar] + currWeight < dist[currChild])
            {
                dist[currChild] = dist[currPar] + currWeight;
                par[currChild] = currPar;
            }
        }
    }
}

void printPath(vector<vector<int>> &costs, vector<int> &par, int dest)
{
    if (par[dest] == dest)
    {
        return;
    }
    printPath(costs, par, par[dest]);
    int parent = par[dest], child = dest;
    char parentName = parent < 8 ? 'A' + parent : 'A' + parent + 1;
    char childName = child < 8 ? 'A' + child : 'A' + child + 1;
    cout << parentName << " -- " << costs[parent][child] << " --> " << childName << ",  ";
}

int main()
{

    /*
    a 0
    b 1
    c 2
    d 3
    e 4
    f 5
    g 6
    h 7
    j 8
    k 9
    */

    char srcName, destName;
    bool srcCheck = true, destCheck = true;
    while (srcCheck || destCheck)
    {
        cout << "Please enter the source vertex" << '\n';
        cin >> srcName;
        if (!(srcName >= 'A' && srcName <= 'K' && srcName != 'I'))
        {
            cout << "Please enter a valid source between A-K which is not I" << "\n\n\n";
            srcCheck = true;
            continue;
        }
        else
            srcCheck = false;
        cout << "Please enter the destination vertex" << '\n';
        cin >> destName;
        if (!(destName >= 'A' && destName <= 'K' && destName != 'I'))
        {
            cout << "Please enter a valid destination between A-K which is not I" << "\n\n\n";
            destCheck = true;
            continue;
        }
        else
            destCheck = false;
    }
    int src = srcName < 'J' ? srcName - 'A' : srcName - 'A' - 1;
    int dest = destName < 'J' ? destName - 'A' : destName - 'A' - 1;
    vector<vector<pair<int, int>>> adjList = {
        {{1, 1}, {4, 1}},
        {{0, 1}, {2, 1}},
        {{1, 1}, {6, 1}, {5, 3}, {8, 4}},
        {{4, 5}, {7, 1}, {8, 2}, {9, 1}},
        {{0, 1}, {3, 5}, {6, 1}},
        {{2, 3}, {9, 1}},
        {{2, 1}, {4, 1}, {7, 1}},
        {{3, 1}, {6, 1}},
        {{2, 4}, {3, 2}},
        {{3, 1}, {5, 1}}};
    vector<int> dist(10, INF);
    dist[src] = 0;
    vector<int> par(10);
    for (int i = 0; i < 10; i++)
    {
        par[i] = i;
    }
    vector<vector<int>> costs(10, vector<int>(10, INF));
    for (int currPar = 0; currPar < 10; currPar++)
    {
        for (auto &currChild : adjList[currPar])
        {
            costs[currPar][currChild.first] = currChild.second;
        }
    }
    cout << "\n\n";
    cout << "Dijkstras Algo Path" << '\n';
    dijkstras(adjList, dist, par, src);
    printPath(costs, par, dest);
    cout << '\n';
    cout << "Total cost is " << dist[dest] << "\n\n\n";
    cout << "Bellman Ford Algo Path" << '\n';
    bellmanFord(adjList, dist, par, src);
    printPath(costs, par, dest);
    cout << '\n';
    cout << "Total cost is " << dist[dest] << '\n';
    return 0;
}