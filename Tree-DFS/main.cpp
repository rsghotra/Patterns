#include<iostream>
#include<vector>
using namespace std;

/*
We will be using recursion (or we can also use a stack for the iterative approach) to keep track of all the previous (parent) nodes while traversing. This also means that the space complexity of the algorithm will be O(H), where ‘H’ is the maximum height of the tree.
Remember: Space Complexity will be O(H); Max no. of calls in the stack
*/

struct TreeNode {
  TreeNode* left;
  TreeNode* right;
  int data;
  TreeNode(int d) {
    this->data = d;
    this->left = 0;
    this->right = 0;
  }
};


/*
Given a binary tree and a number ‘S’, find if the tree has a path from root-to-leaf such that the sum of all the node values of that path equals ‘S’.
Generally tree questions are solved in post order form; L, R, Root

T(N): O(N) -> as we will touch every node;
S(N): O(H) -> recursion stack will be O(H)
Where H is height of Tree; 
Note: Height of the tree = O(N) when Tree is a LL; Else lies betweem logN-N
*/
bool HasPath(TreeNode* root, int S) {
  if(root == 0) {
    return false;
  }
  if(root->data == S && root->left == 0 && root->right == 0) {
    return true;
  } else {
    return HasPath(root->left, S - root->data) || HasPath(root->right, S - root->data);
  }
}

void HasPath() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  cout << "Tree has path: " << HasPath(root, 23) << endl;
  cout << "Tree has path: " << HasPath(root, 16) << endl;
}

/*
Given a binary tree and a number ‘S’, find all paths from root-to-leaf such that the sum of all the node values of each path equals ‘S’

T(N) O(N^2) : where ‘N’ is the total number of nodes in the tree. 
This is due to the fact that we traverse each node once (which will take O(N)), and for every leaf node, we might have to store its path (by making a copy of the current path) which will take O(N).

if the tree is balanced then the lenght of the path will be LogN
We can calculate a tighter time complexity of O(NlogN);
Space Complexity(Recursion stack): O(H); could be O(N)


*/
void AllPathSumR(TreeNode* root, int sum, vector<int>& currentPath, vector<vector<int>>& allPaths) {
  if(root == 0) {
    return;
  }
  currentPath.push_back(root->data);
  if(root->data == sum && root->left == 0 && root->right == 0) {
    allPaths.push_back(currentPath);
  } else { // do not forget to put it in else;
    AllPathSumR(root->left, sum - root->data, currentPath, allPaths);
    AllPathSumR(root->right, sum - root->data, currentPath, allPaths);
  }
  currentPath.pop_back();
}


vector<vector<int>> AllPathSum(TreeNode* root, int S) {
  vector<vector<int>> allPaths;
  vector<int> currentPath;
  AllPathSumR(root, S, currentPath, allPaths);
  return allPaths;
}

void AllPathSum() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(4);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  int sum = 23;
  vector<vector<int>> result = AllPathSum(root, sum);
  cout << "Tree paths with sum " << sum << ": " << endl;
  for (auto vec : result) {
    for (auto num : vec) {
      cout << num << " ";
    }
    cout << endl;
  }
}

/*
Given a binary tree, find the root-to-leaf path with the maximum sum.
T(N): O(NLogN) - O(N)
S(N): O(H) or O(LogN) to O(N)
*/

void MaxPathSum(TreeNode* root, int& pathSum, int& maxSum, vector<int>& currentPath, vector<int>& maxPath) {
  if(root == 0) {
    return;
  }
  pathSum += root->data;
  currentPath.push_back(root->data);
  if(root->left == 0 && root->right == 0) {
    if(maxSum < pathSum) {
      maxPath = currentPath;
      maxSum = pathSum;
    }
  } else {
    MaxPathSum(root->left, pathSum, maxSum, currentPath, maxPath);
    MaxPathSum(root->right, pathSum, maxSum, currentPath, maxPath);
  }
  pathSum -= root->data;
  currentPath.pop_back();
}

vector<int> MaxPathSum(TreeNode* root) {
  vector<int> maxPath;
  int maxSum = INT32_MIN;
  vector<int> currentPath;
  int pathSum = 0;
  MaxPathSum(root, pathSum, maxSum, currentPath, maxPath);
  cout << maxSum << endl;
  return maxPath;
}

void MaxPathSum() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(4);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  root->right->right->left = new TreeNode(15);
  cout << "Max Path and its Sum is: " << endl;
  vector<int> result = MaxPathSum(root);
  for (auto num : result) {
    cout << num << " ";
  }
}

/* Given a binary tree where each node can only have a digit (0-9) value, each root-to-leaf path will represent a number. Find the total sum of all the numbers represented by all paths.
*/

void SumOfPathNums(TreeNode* root, int pathSum, int& sum) {
  if(root == 0) {
    return;
  }
  //careful here: not pathSum +=
  pathSum = pathSum * 10 + root->data;
  if(root->left == 0 && root->right == 0) {
    sum += pathSum;
  } else {
    SumOfPathNums(root->left, pathSum, sum);
    SumOfPathNums(root->right, pathSum, sum);
  }
  pathSum -= root->data;
}

int SumOfPathNums(TreeNode* root) {
  int sum = 0;
  int pathSum = 0;
  SumOfPathNums(root, pathSum, sum);
  return sum;
}

void SumOfPathNums() {
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(0);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(1);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(5);
  cout << "\nTotal Sum of Path Numbers: " << SumOfPathNums(root) << endl;
}

/*
Given a binary tree and a number sequence, find if the sequence is present as a root-to-leaf path in the given tree.
T(N): O(N) - Since we will be touching each node only once.
S(N): O(H): LogN - N
*/

bool SequencePathPresent(TreeNode* currentNode, const vector<int>& sequence, int& sqIndex){
  if(currentNode == 0 || sqIndex == sequence.size() || sequence[sqIndex] != currentNode->data) {
    return false;
  }
  if(currentNode->left == 0 && currentNode->right == 0 && sequence[sqIndex] == currentNode->data) {
    return true;
  }
  sqIndex++;
  return SequencePathPresent(currentNode->left, sequence, sqIndex) || SequencePathPresent(currentNode->right, sequence, sqIndex);
}


bool SequencePathPresent(TreeNode* root, const vector<int>& sequence) {
  if(root == 0) {
    return sequence.empty();
  }
  int sqIndex = 0;
  return SequencePathPresent(root, sequence, sqIndex);
}

void SequencePathPresent() {
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(0);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(1);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(5);

  cout << "Tree has path sequence: " << SequencePathPresent(root, vector<int>{1, 0, 7})
       << endl;
  cout << "Tree has path sequence: " << SequencePathPresent(root, vector<int>{1, 1, 6})
       << endl;
}

/*
Given a binary tree and a number ‘S’, find all paths in the tree such that the sum of all the node values of each path equals ‘S’. Please note that the paths can start or end at any node but all paths must follow direction from parent to child (top to bottom).
T(N):O(N2) to O(NLogN)
S(N): O(H)
The time complexity of the above algorithm is O(N^2) in the worst case, where ‘N’ is the total number of nodes in the tree. This is due to the fact that we traverse each node once, but for every node, we iterate the current path. The current path, in the worst case, can be O(N)(in the case of a skewed tree). But, if the tree is balanced, then the current path will be equal to the height of the tree, i.e., O(logN). So the best case of our algorithm will be O(NlogN).
*/
int CountPathsForASum(TreeNode* currentNode, int sum, vector<int>& currentPath) {
  if(currentNode == nullptr) {
    return 0;
  }
  currentPath.push_back(currentNode->data);
  int pathSum = 0;
  int pathCount = 0;
  for(vector<int>::reverse_iterator itr = currentPath.rbegin(); itr != currentPath.rend(); itr++) {
    pathSum += *itr;
    if(pathSum == sum) {
      pathCount++;
    }
  }
  pathCount += CountPathsForASum(currentNode->left, sum, currentPath);
  pathCount += CountPathsForASum(currentNode->right, sum, currentPath);
  currentPath.pop_back();
  return pathCount;
}

int CountPathsForASum(TreeNode* root, int sum) {
  //if something must be refilled in every call then must be pass by value;
  vector<int> currentPath;
  return CountPathsForASum(root, sum, currentPath);
}

void CountPathsForASum() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(4);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  cout << "Tree has path: " << CountPathsForASum(root, 11) << endl;
}


/*
Given a binary tree, find the length of its diameter. The diameter of a tree is the number of nodes on the longest path between any two leaf nodes. The diameter of a tree may or may not pass through the root.
Note: You can always assume that t tree.
T(N) = O(N)
S(N) = O(H)
*/

int Diameter(TreeNode* currentNode, int& treeDiameter) {
  if(currentNode == 0) {
    return 0;
  }
  int leftTreeHeight = Diameter(currentNode->left, treeDiameter);
  int rightTreeHeight = Diameter(currentNode->right, treeDiameter);
  
  //watch out; we do not want leaves now
  if(leftTreeHeight != 0 && rightTreeHeight != 0) {
    int diameter = leftTreeHeight + rightTreeHeight + 1;
    treeDiameter = max(treeDiameter, diameter);
  }
  //root dia
  return max(leftTreeHeight, rightTreeHeight) + 1;
}

int TreeDiameter(TreeNode* root) {
  int treeDiameter = 0;
  Diameter(root, treeDiameter);
  return treeDiameter;
}

void TreeDiameter() {
  TreeNode *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);
  root->left->left = new TreeNode(4);
  root->right->left = new TreeNode(5);
  root->right->right = new TreeNode(6);
  cout << "Tree Diameter: " << TreeDiameter(root) << endl;
  root->left->left = nullptr;
  root->right->left->left = new TreeNode(7);
  root->right->left->right = new TreeNode(8);
  root->right->right->left = new TreeNode(9);
  root->right->left->right->left = new TreeNode(10);
  root->right->right->left->left = new TreeNode(11);
  cout << "Tree Diameter: " << TreeDiameter(root) << endl;
}

/*
Find the path with the maximum sum in a given binary tree. Write a function that returns the maximum sum.

A path can be defined as a sequence of nodes between any two nodes and doesn’t necessarily pass through the root. The path must contain at least one node.

*/


void MaxPathSumAny() {
  
}

int main() {
  HasPath();
  AllPathSum();
  MaxPathSum();
  MaxPathSumAny();
  SumOfPathNums();
  SequencePathPresent();
  CountPathsForASum();
  TreeDiameter();
  return 0;
}