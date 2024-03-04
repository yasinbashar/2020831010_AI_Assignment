#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<vector<char>>graph;
map<pair<char,char>,int>cost;

vector<int>uniform_cost_search(vector<char>goal,char start)
{

	vector<int>ans;

	priority_queue<pair<int,char>>queuee;

	// set the answer vector to max value
	for (int i=0;i<goal.size();i++)
		ans.push_back(INT_MAX);

	queuee.push(make_pair(0, start));
	map<char,int>visited;

	// count
	int count = 0;

	while (queuee.size() > 0) {

		pair<int, char> p = queuee.top();

		queuee.pop();

		p.first *= -1;

		if (find(goal.begin(), goal.end(), p.second) != goal.end()) {

			int index = find(goal.begin(), goal.end(),
							p.second) - goal.begin();

			if (ans[index] == INT_MAX)
				count++;


			if (ans[index] > p.first)
				ans[index] = p.first;

			queuee.pop();

			if (count == goal.size())
				return ans;
		}

		if (visited[p.second] == 0)
			for (int i=0;i<graph[p.second].size();i++) {
				queuee.push(make_pair((p.first +
				cost[make_pair(p.second, graph[p.second][i])]) * -1,
				graph[p.second][i]));
			}
		visited[p.second] = 1;
	}

	return ans;
}

int main()
{
	graph.resize(5);

	graph['S'].push_back('A');
	graph['S'].push_back('G');
	graph['A'].push_back('C');
	graph['B'].push_back('D');
	graph['D'].push_back('G');
	graph['C'].push_back('D');
	graph['C'].push_back('G');
	graph['D'].push_back('G');
	graph['A'].push_back('B');


	cost[make_pair('S', 'A')] = 1;
	cost[make_pair('S', 'G')] = 12;
	cost[make_pair('A', 'B')] = 3;
	//cost[make_pair(2, 3)] = 3;
	cost[make_pair('B', 'D')] = 3;
	cost[make_pair('D', 'G')] = 3;
	cost[make_pair('A', 'C')] = 1;
	cost[make_pair('C', 'D')] = 1;
	cost[make_pair('D', 'G')] = 3;
	cost[make_pair('C', 'G')] = 2;

	vector<char>goal;

	goal.push_back('G');

	vector<int> ans = uniform_cost_search(goal, 'S');

	cout << "Minimum cost from S to G is = " << ans[0] << endl;

	return 0;
}
