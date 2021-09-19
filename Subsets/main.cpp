#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
#include<cmath>
using namespace std;

struct TreeNode {
  TreeNode* left;
  TreeNode* right;
  int data;
  TreeNode(int d) {
    this->data = d;
    this->left = 0;
    this->right =0;
  }
};

vector<vector<int>> FindSubsets(const vector<int>& nums) {
  vector<vector<int>> subsets;
  subsets.push_back(vector<int>{});
  for(int i = 0; i < nums.size(); i++) {
    size_t n = subsets.size();
    for(size_t j = 0; j < n; j++) {
      vector<int> subset{subsets[j]};
      subset.push_back(nums[i]);
      subsets.push_back(subset);
    }
  }
  return subsets;
}

void FindSubsets() {
	vector<vector<int>> result = FindSubsets(vector<int>{1, 3});
	cout << "Here is the list of subsets: " << endl;
	for (auto vec : result) {
		for (auto num : vec) {
		cout << num << " ";
		}
		cout << endl;
	}

	result = FindSubsets(vector<int>{1, 5, 3});
	cout << "Here is the list of subsets: " << endl;
	for (auto vec : result) {
		for (auto num : vec) {
		cout << num << " ";
		}
		cout << endl;
	}
}

/*
Subsets with dups
*/
vector<vector<int>> SubsetsWithDuplicates(vector<int>& nums) {
  std::sort(nums.begin(), nums.end());
  vector<vector<int>> subsets;
  subsets.push_back(vector<int>{});
  int startIndex = 0;
  int endIndex = 0;

  for(size_t i = 0; i < nums.size(); i++) {
    startIndex = 0;
    if(i > 0 && nums[i-1] == nums[i]) {
      startIndex = endIndex + 1;
    }
    endIndex = subsets.size() - 1 ;
    for(size_t j = startIndex; j <= endIndex; j++) {
      vector<int> subset(subsets[j]);
      subset.push_back(nums[i]);
      subsets.push_back(subset);
    }
  }
  return subsets;
}

void SubsetsWithDuplicates() {
	vector<int> vec = {1, 3, 3};
	vector<vector<int>> result = SubsetsWithDuplicates(vec);
	cout << "Here is the list of subsets with dups: " << endl;
	for (auto vec : result) {
		for (auto num : vec) {
		cout << num << " ";
		}
		cout << endl;
	}

	vec = {1, 5, 3, 3};
	result = SubsetsWithDuplicates(vec);
	cout << "Here is the list of subsets with dups: " << endl;
	for (auto vec : result) {
		for (auto num : vec) {
		cout << num << " ";
		}
		cout << endl;
	}
}

/*
Permutations
O(NxN!)
*/
vector<vector<int>> FindPermutations(const vector<int>& nums) {
  vector<vector<int>> permutations;
  queue<vector<int>> interim;
  interim.push(vector<int>{});

  for(int i = 0; i < nums.size(); i++) {
    int size = interim.size();
    for(int j = 0; j < size; j++) {
      vector<int> oldPermutation = interim.front();
      interim.pop();
      for(int k = 0; k <= oldPermutation.size(); k++) {
        vector<int> newPermutation(oldPermutation);
        newPermutation.insert(newPermutation.begin() + k, nums[i]);
        if(newPermutation.size() == nums.size()) {
          permutations.push_back(newPermutation);
        } else {
          interim.push(newPermutation);
        }
      }
    }
  }
  return permutations;
}

void FindPermutations() {
	vector<vector<int>> result = FindPermutations(vector<int>{1, 3, 5});
  	cout << "Here are all the permutations: " << endl;
	for (auto vec : result) {
		for (auto num : vec) {
		cout << num << " ";
		}
		cout << endl;
	}
}

/*
Find Permutation by changing case.
*/

vector<string> PermutationsByChangingCase(const string& str) {
  if(str == "") return {};
  vector<string> permutations;
  permutations.push_back(str); //beginning with given string;
  //traverse over given string one by one
  for(int i = 0; i <str.size(); i++) {
    if(isalpha(str[i])) {
      int n = permutations.size();
      for(int j = 0; j < n; j++) {
        vector<char> oldPermutation(permutations[j].begin(), permutations[j].end());
        //watch out => i index not j
        if(islower(oldPermutation[i])) {
          oldPermutation[i] = toupper(oldPermutation[i]);
        } else {
          oldPermutation[i] = tolower(oldPermutation[i]);
        }
        permutations.push_back(string(oldPermutation.begin(), oldPermutation.end()));
      }
    }
  }
  return permutations;
}

void PermutationsByChangingCase() {
  vector<string> result = PermutationsByChangingCase("ad52");
	cout << "String permutations are: ";
	for (auto str : result) {
		cout << str << " ";
	}
	cout << endl;

	result = PermutationsByChangingCase("ab7c");
	cout << "String permutations are: ";
	for (auto str : result) {
		cout << str << " ";
	}
	cout << endl;
}

/*
Generate Balanced Paranthesis
*/

class ParanthesisString {
  public:
    int openBkt = 0;
    int closeBkt = 0;
    string str;
    ParanthesisString(string str, int open, int close) {
      this->openBkt = open;
      this->closeBkt = close;
      this->str = str;
    }
};

vector<string> GenerateParanthesis(int num) {
  vector<string> result;
  queue<ParanthesisString> queue;
  queue.push({"", 0, 0});
  while(!queue.empty()) {
    ParanthesisString ps = queue.front();
    queue.pop();
    if(ps.openBkt == num && ps.closeBkt == num) {
      result.push_back(ps.str);
    } else {
      if(ps.openBkt < num) {
        queue.push({ps.str + "(", ps.openBkt + 1, ps.closeBkt});
      }
      if(ps.openBkt > ps.closeBkt) {
        queue.push({ps.str + ")", ps.openBkt, ps.closeBkt + 1});
      }
    }
  }
  return result;
}

void GenerateParanthesis() {
	vector<string> result = GenerateParanthesis(2);
	cout << "All combinations of balanced parentheses are: ";
	for (auto str : result) {
		cout << str << " ";
	}
	cout << endl;

	result = GenerateParanthesis(3);
	cout << "All combinations of balanced parentheses are: ";
	for (auto str : result) {
		cout << str << " ";
	}
	cout << endl;
}

/*
Evaluate Expression
*/
unordered_map<string, vector<int>> mappings = unordered_map<string, vector<int>>();
vector<int> EvaluateExpression(const string& str) {
  //memo
  if(mappings.find(str) != mappings.end()) {
    return mappings[str];
  }
  vector<int> result;
  if(str.find("+") == string::npos && str.find("-") == string::npos && str.find("*") == string::npos) {
    //str is a number;
    result.push_back(stoi(str));
  } else {
    for(size_t i = 0; i < str.size(); i++) {
      if(!isdigit(str[i])) {
        vector<int> leftPart = EvaluateExpression(str.substr(0, i));
        vector<int> rightPart = EvaluateExpression(str.substr(i+1));
        for(auto part1: leftPart) {
          for(auto part2: rightPart) {
            if(str[i] == '+') {
              result.push_back(part1 + part2);
            } else if(str[i] == '-') {
              result.push_back(part1 - part2);
            } else if(str[i] == '*') {
              result.push_back(part1 * part2);
            }
          }
        }
      }
    }
  }
  mappings[str] = result;
  return result;
}

void EvaluateExpression() {
	vector<int> result = EvaluateExpression("1+2*3");
	cout << "Expression evaluations: ";
	for (auto num : result) {
		cout << num << " ";
	}
	cout << endl;

	result = EvaluateExpression("2*3-4-5");
	cout << "Expression evaluations: ";
	for (auto num : result) {
		cout << num << " ";
	}
	cout << endl;
}

/*
Unique Trees: Catalan Numbers; But we need tree root of each unique;
we traverse number 1 to n; counting each node as root;
*/
vector<TreeNode*> FindUniqueTrees(int start, int end) {
  vector<TreeNode*> result;
  if(start > end) { 
    result.push_back(nullptr);
    return result;
  }
  for(int i = start; i <= end; i++) {
    vector<TreeNode*> leftSubtrees = FindUniqueTrees(start, i - 1);
    vector<TreeNode*> rightSubtrees = FindUniqueTrees(i+1, end);
    for(auto leftSubtree: leftSubtrees) {
      for(auto rightSubtree: rightSubtrees) {
        TreeNode* root = new TreeNode(i);
        root->left = leftSubtree;
        root->right = rightSubtree;
        result.push_back(root);
      }
    }
  }
  return result;
}

void FindUniqueTrees() {
	  vector<TreeNode *> result = FindUniqueTrees(1,2);
  	cout << "Total trees: " << result.size() << endl;

  	result = FindUniqueTrees(1,3);
  	cout << "Total trees: " << result.size() << endl;  
}

/*
Count Unique Trees
*/
unordered_map<int, int> utrees = unordered_map<int, int>();

int CountUniqueTrees(int n) {
  if(utrees.find(n) != utrees.end()) {
    return utrees[n];
  }
  if(n <= 1) {
    return 1; //basecase
  }
  int count = 0;
  for(int i = 1; i <= n; i++) {
    int leftSubtreesCount = CountUniqueTrees(i-1);
    int rightSubtreesCount = CountUniqueTrees(n-i);
    count += (leftSubtreesCount * rightSubtreesCount);
  }
  utrees[n] = count;
  return count;
}

void CountUniqueTrees() {
  	int count = CountUniqueTrees(3);
  	cout << "Total Count trees: " << count;
}

int main() {
  FindSubsets();//standard subset que
  SubsetsWithDuplicates();
  
  FindPermutations(); //queue needed;
  PermutationsByChangingCase();//no queue needed
  GenerateParanthesis(); //queue needed

  EvaluateExpression(); //recursion + memo
  FindUniqueTrees(); //recursion
  CountUniqueTrees(); //recursion + memo
  return 0;
}