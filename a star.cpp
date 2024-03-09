#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

map<string, vector<pair<string, ll>>> graph; // node1 - node2 - cost
map<string,ll > heuristic;

map<string, bool> vis;
map<string, ll> dist;

map<string, string> parentNode;
vector<string> path;

void printPath(string node)
{
    path.push_back(node);
    if (parentNode[node] == node)
        return;
    printPath(parentNode[node]);
}

void A_StarSearch(string source, string destination)
{
    multiset<pair<ll, string>> st; // dist - nodeName

    st.insert(make_pair(heuristic[source], source));
    dist[source] = heuristic[source];
    parentNode[source] = source;

    while (!st.empty())
    {
        auto node = *st.begin();
        string parent = node.second;
        ll cost = node.first;

        st.erase(st.begin());

        if (vis[parent])
            continue;
        vis[parent] = true;
        if (parent == destination)
            break;

        for(auto child : graph[parent])
        {
            string childName = child.first;
            ll pathCost = child.second;
            ll tempCost = cost - heuristic[parent] + pathCost + heuristic[childName];

            if (tempCost < dist[childName])
            {
                parentNode[childName] = parent;
                dist[childName] = tempCost;
            }
            st.insert(make_pair(dist[childName], childName));
        }
    }
}

int main()
{
    int nodes, edges;
    cin >> nodes >> edges;
    while (edges--)
    {
        string node1, node2;
        ll cost;
        cin >> node1 >> node2 >> cost;
        graph[node1].push_back(make_pair(node2, cost));
        graph[node2].push_back(make_pair(node1, cost));
    }

    while (nodes--)
    {
         // huristic array
        string s;
        int hr;
        cin >> s >> hr;
        heuristic[s] = hr;
        vis[s] = false;
        dist[s] = INT_MAX;
    }

    string source, destination;
    cin >> source >> destination;

    A_StarSearch(source, destination);
    cout << "The path cost is :: " << dist[destination] << endl;
    printPath(destination);
    cout << "And the path is :: ";
    for (ll i = path.size() - 1; i >= 0; i--)
    {
        cout << path[i];
        if (i != 0)
            cout << " -> ";
    }
    cout << endl;
    return 0;
}



/*
input:

10 11
Arab Sibiu 140
Arab Timisoara 118
Arab Zerind 75
Sibiu Oradea 151
Sibiu Fagaras 99
Sibiu RimnicuVilcea 80
Fagaras Bucharest 211
RimnicuVilcea Craiova 146
RimnicuVilcea Pitesti 97
Pitesti Craiova 138
Pitesti Bucharest 101

Arab 366
Sibiu 253
Timisoara 329
Zerind 374
Oradea 380
Fagaras 176
RimnicuVilcea 193
Bucharest 0
Craiova 160
Pitesti 100

Arab Bucharest
*/
