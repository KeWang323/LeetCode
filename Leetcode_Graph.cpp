/*

133. Clone Graph (Medium)

Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.


OJ's undirected graph serialization:
Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
Second node is labeled as 1. Connect node 1 to node 2.
Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:

	   1
	  / \
	 /   \
	0 --- 2
		 / \
		 \_/

*/
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
		if (node == NULL) {
			return NULL;
		}
		unordered_map<int, UndirectedGraphNode*> mapping;
		UndirectedGraphNode* newhead = new UndirectedGraphNode(node->label);
		mapping[node->label] = newhead;
		queue<UndirectedGraphNode*> q;
		q.push(node);
		while (!q.empty()) {
			for (UndirectedGraphNode *nei : q.front()->neighbors) {
				if (mapping.find(nei->label) == mapping.end()) {
					mapping[nei->label] = new UndirectedGraphNode(nei->label);
					q.push(nei);
				}
				mapping[q.front()->label]->neighbors.push_back(mapping[nei->label]);
			}
			q.pop();
		}
		return newhead;
	}
};
/*

399. Evaluate Division (Medium)

Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0.
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ].
The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.

*/
class Solution {
public:
	vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
		unordered_map<string, unordered_map<string, double>> pairs;
		for (int i = 0; i < equations.size(); i++) {
			pairs[equations[i].first][equations[i].second] = values[i];
			pairs[equations[i].second][equations[i].first] = 1 / values[i];
		}
		vector<double> res(queries.size());
		for (int i = 0; i < queries.size(); i++) {
			if (pairs.count(queries[i].first) && pairs.count(queries[i].second)) {
				if (queries[i].first == queries[i].second) {
					res[i] = 1.0;
				}
				else {
					unordered_set<string> visited;
					res[i] = dfs(queries[i].first, queries[i].second, pairs, visited, 1.0);
				}
			}
			else {
				res[i] = -1.0;
			}
		}
		return res;
	}
private:
	double dfs(const string& start, const string& end, unordered_map<string, unordered_map<string, double>> pairs, unordered_set<string>& visited, double value) {
		if (pairs[start].find(end) != pairs[start].end()) {
			return value * pairs[start][end];
		}
		for (pair<string, double> p : pairs[start]) {
			string str = p.first;
			if (visited.find(str) == visited.end()) {
				visited.insert(str);
				double cur = dfs(str, end, pairs, visited, value * p.second);
				if (cur != -1.0) {
					return cur;
				}
			}
		}
		return -1.0;
	}
};