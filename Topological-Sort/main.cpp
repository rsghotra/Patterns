#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
#include<cmath>
using namespace std;

/*
Given a directed graph, find the topological ordering of its vertices.
OR
Find if a given Directed Graph has a cycle in it or not.
*/

vector<int> TopologicalSort(int vertices, const vector<vector<int>>& edges) {
  //initialization
  unordered_map<int, vector<int>> graph;
  unordered_map<int, int> inDegree;
  vector<int> result;
  for(int i = 0; i < vertices; i++) {
    graph[i] = vector<int>{};
    inDegree[i] = 0;
  }

  //build graph
  for(int i = 0; i < edges.size(); i++) {
    int parent = edges[i][0];
    int child = edges[i][1];
    graph[parent].push_back(child);
    inDegree[child]++;
  }

  queue<int> sources;
  for(auto entry: inDegree) {
    if(entry.second == 0) {
      sources.push(entry.first);
    }
  }
  //process graph
  while(!sources.empty()) {
    int vtx = sources.front();
    sources.pop();
    result.push_back(vtx);
    vector<int> children = graph[vtx];
    for(auto child: children) {
      inDegree[child]--;
      if(inDegree[child] == 0) {
        sources.push(child);
      }
    }
  }
  if(result.size() != vertices) {
    return vector<int>{};
  }
  return result;
}

void TopologicalSort() {
  vector<int> result =
      TopologicalSort(4, vector<vector<int>>{vector<int>{3, 2}, vector<int>{3, 0},
                                                   vector<int>{2, 0}, vector<int>{2, 1}});
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  result = TopologicalSort(
      5, vector<vector<int>>{vector<int>{4, 2}, vector<int>{4, 3}, vector<int>{2, 0},
                             vector<int>{2, 1}, vector<int>{3, 1}});
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  result = TopologicalSort(
      7, vector<vector<int>>{vector<int>{6, 4}, vector<int>{6, 2}, vector<int>{5, 3},
                             vector<int>{5, 4}, vector<int>{3, 0}, vector<int>{3, 1},
                             vector<int>{3, 2}, vector<int>{4, 1}});
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;
}



/*
There is a dictionary containing words from an alien language for which we don’t know the ordering of the alphabets. Write a method to find thguage. It is given that the input is a valid dictionary and there exists an ordering among its alphabets.
*/

string AlienDictionary(const vector<string>& words) {
  //initial
  unordered_map<char, int> inDegree;
  unordered_map<char, vector<char>> graph;
  string orderedString;
  for(auto word: words) {
    for(char ch: word) {
      inDegree[ch] = 0;
      graph[ch] = vector<char>();
    }
  }

  for(int i = 0; i < words.size() - 1; i++) {
    string word1 = words[i];
    string word2 = words[i+1];
    for(int j = 0; j < min(word1.size(), word1.size()); j++) {
      char parent = word1[j];
      char child = word2[j];
      if(parent != child) {
        graph[parent].push_back(child);
        inDegree[child]++;
        break;
      }
    }
  }

  queue<char> sources;
  for(auto entry: inDegree) {
    if(entry.second == 0) {
      sources.push(entry.first);
    }
  }

  while(!sources.empty()) {
    char vtx =sources.front();
    sources.pop();
    orderedString += vtx;
    vector<char> children = graph[vtx];
    for(auto child: children) {
      inDegree[child]--;
      if(inDegree[child] == 0) {
        sources.push(child);
      }
    }
  }

  if(orderedString.size()  != inDegree.size()) {
    return "";
  }
  return orderedString;
}

void AlienDictionary() {
  string result = AlienDictionary(vector<string>{"ba", "bc", "ac", "cab"});
  cout << "Character order: " << result << endl;

  result = AlienDictionary(vector<string>{"cab", "aaa", "aab"});
  cout << "Character order: " << result << endl;

  result = AlienDictionary(vector<string>{"ywx", "wz", "xww", "xz", "zyy", "zwz"});
  cout << "Character order: " << result << endl;
}

/*
Given a sequence originalSeq and an array of sequences, write a method to find if originalSeq can be uniquely reconstructed from the array of sequences.

Unique reconstruction means that we need to find if originalSeq is the only sequence such that all sequences in the array are subsequences of it.
*/

bool RecounstructSequence(vector<int>& originalSequence, vector<vector<int>>& sequences) {
  vector<int> result;
  unordered_map<int, vector<int>> graph;
  unordered_map<int, int> inDegree;
  for(auto sequence: sequences) {
    for(int i = 0; i < sequence.size(); i++) {
      graph[sequence[i]] = vector<int>{};
      inDegree[sequence[i]] = 0;
    }
  }

  for(auto sequence: sequences) {
    for(int i = 0; i <sequence.size() - 1; i++) {
      int parent = sequence[i];
      int child = sequence[i+1];
      graph[parent].push_back(child);
      inDegree[child]++;
    }
  }

  if(inDegree.size() != originalSequence.size()) return false;
  queue<int> sources;
  for(auto entry: inDegree) {
    if(entry.second == 0) {
      sources.push(entry.first);
    }
  }

  while(!sources.empty()) {
    if(sources.size() > 2) {
      return false;
    }
    if(originalSequence[result.size()]  != sources.front()) {
      return false;
    }
    int vtx = sources.front();
    sources.pop();
    result.push_back(vtx);
    vector<int> children = graph[vtx];
    for(auto child: children) {
      inDegree[child]--;
      if(inDegree[child] == 0) {
        sources.push(child);
      }
    }
  }
  return result.size() == originalSequence.size();
}

/*
Minimum Height Trees
*/
vector<int> MinimumHeightTrees(int nodes, vector<vector<int>>& edges) {
  vector<int> minHeightTreeNodes;
  if(nodes == 1) {
    minHeightTreeNodes.push_back(0);
    return minHeightTreeNodes;
  }
  unordered_map<int, int> inDegree;
  unordered_map<int, vector<int>> graph;
  for(int i = 0; i < nodes; i++) {
    inDegree[i] = 0;
    graph[i] = vector<int>();
  }

  for(int i = 0; i < edges.size(); i++) {
    int parent = edges[i][0];
    int child = edges[i][1];

    graph[parent].push_back(child);
    graph[child].push_back(parent);
    inDegree[parent]++;
    inDegree[child]++;
  }

  queue<int> leaves;
  for(auto entry: inDegree) {
    if(entry.second == 1) {
      leaves.push(entry.first);
    }
  }

  int currentNodes = nodes;
  while(currentNodes > 2) {
    int leavesSize = leaves.size();
    currentNodes -= leavesSize;
    for(int i = 0; i < leavesSize; i++) {
      int vtx = leaves.front(); leaves.pop();
      vector<int> children = graph[vtx];
      for(auto child: children) {
        inDegree[child]--;
        if(inDegree[child] == 1) {
          leaves.push(child);
        }
      }
    }
  }
  while(!leaves.empty()) {
    minHeightTreeNodes.push_back(leaves.front());
    leaves.pop();
  }
  return minHeightTreeNodes;
}

int main() {
  TopologicalSort();
  AlienDictionary();
}