#include<iostream>
#include<queue>
#include<vector>
using namespace std;

struct TreeNode {
  TreeNode* left;
  TreeNode* right;
  TreeNode* next;
  int data;
  TreeNode(int data) {
    this->data = data;
    this->left = left;
    this->right = right;
    this->next = 0;
  }
};

/*
Given a binary tree, populate an array to represent its level-by-level traversal. You should populate the values of all nodes of each level from left to right in separate sub-arrays.

T: O(N)
O(N) for space for output list
S: O(N/2) for queue as we have max N/2 nodes at any level of the tree and those nodes will be store in the queue
*/

vector<vector<int>> LevelOrder(TreeNode* root) {
  if(root == 0) {
    return {};
  }
  vector<vector<int>> result;
  queue<TreeNode*> incoming;
  incoming.push(root);

  while(!incoming.empty()) {
    int levelSize = incoming.size();
    vector<int> currentLevel;
    for(int i = 0; i < levelSize; i++) {
      TreeNode* node = incoming.front();
      incoming.pop();
      currentLevel.push_back(node->data);
      if(node->left) incoming.push(node->left);
      if(node->right) incoming.push(node->right);
    }
    result.push_back(currentLevel);
  }
  return result;
}

void LevelOrder() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  vector<vector<int>> result = LevelOrder(root);
  cout << "\nLevel order traversal: \n";
  for (auto vec : result) {
    for (auto num : vec) {
      cout << num << " ";
    }
    cout << endl;
  }
}

/*
Given a binary tree, populate an array to represent its level-by-level traversal in reverse order, i.e., the lowest level comes first. You should populate the values of all nodes in each level from left to right in separate sub-arrays.
T(N): O(N) as we touch each level
S(N): O(N/2){for queue} + O(N) for the output list

*/

vector<vector<int>> ReverseLevelOrder(TreeNode* root) {
  if(root == 0) {
    return {};
  }
  vector<vector<int>> output;
  deque<vector<int>> result;
  queue<TreeNode*> incoming;
  incoming.push(root);

  while(!incoming.empty()) {
    int levelSize = incoming.size();
    vector<int> currentLevel;
    for(int i = 0; i < levelSize; i++) {
      TreeNode* node = incoming.front();
      incoming.pop();
      currentLevel.push_back(node->data);
      if(node->left) incoming.push(node->left);
      if(node->right) incoming.push(node->right);
    }
    result.push_front(currentLevel);
  }
  std::move(result.begin(), result.end(), back_inserter(output));
  return output;
}

void ReverseLevelOrder() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  auto result = ReverseLevelOrder(root);

  cout << "\nReverse level order traversal: \n";
  for (auto que : result) {
    for (auto num : que) {
      cout << num << " ";
    }
    cout << endl;
  }
}

vector<vector<int>> ZigZagTraversal(TreeNode* root) {
  if(root == 0) {
    return vector<vector<int>>{};
  }
  vector<vector<int>> result;
  queue<TreeNode*> incoming;
  incoming.push(root);
  bool leftToRight = true;
  while(!incoming.empty()) {
    int levelSize = incoming.size();
    vector<int> currentLevel(levelSize);
    for(int i = 0; i < levelSize; i++) {
      TreeNode* node = incoming.front();
      incoming.pop();
      if(leftToRight) {
        currentLevel[i] = node->data;
      } else {
        currentLevel[levelSize - i - 1] = node->data;
      }
      if(node->left) incoming.push(node->left);
      if(node->right) incoming.push(node->right);
    }
    result.push_back(currentLevel);
    leftToRight = !leftToRight;
  }
  return result;
}


void ZigZagTraversal() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  root->right->left->left = new TreeNode(20);
  root->right->left->right = new TreeNode(17);
  vector<vector<int>> result = ZigZagTraversal(root);
  cout << "\nZigzag traversal: \n";
  for (auto vec : result) {
    for (auto num : vec) {
      cout << num << " ";
    }
    cout << endl;
  }
}

/*
Given a binary tree, populate an array to represent the averages of all of its levels.
T(N): O(N)
S(N): O(H)
*/
vector<double> LevelOrderAverage(TreeNode* root) {
  vector<double> result;
  queue<TreeNode*> incoming;
  incoming.push(root);
  while(!incoming.empty()) {
    int levelSize = incoming.size();
    int levelSum = 0;
    for(int i = 0; i < levelSize; i++) {
      TreeNode* node = incoming.front(); incoming.pop();
      levelSum += node->data;
      if(node->left) incoming.push(node->left);
      if(node->right) incoming.push(node->right);
    }
    result.push_back((1.0*levelSum)/levelSize);
  }
  return result;
}


void LevelOrderAverage() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->left->right = new TreeNode(2);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  vector<double> result = LevelOrderAverage(root);
  cout << "Level averages are: ";
  for (auto num : result) {
    cout << num << " ";
  }
}

int MinimumDepthOfATree(TreeNode* root) {
  queue<TreeNode*> incoming;
  incoming.push(root);

  int depth = 0;
  while(!incoming.empty()) {
    depth++;
    int levelSize = incoming.size();
    for(int i = 0; i < levelSize; i++) {
      TreeNode* node = incoming.front();
      incoming.pop();
      if(node->left == 0 && node->right == 0) {
        return depth;
      }
      if(node->left) incoming.push(node->left);
      if(node->right) incoming.push(node->right);
    }
  }
  return depth;
}

void  MinimumDepthOfATree() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  cout << "\nTree Minimum Depth: " << MinimumDepthOfATree(root) << endl;
  root->left->left = new TreeNode(9);
  root->right->left->left = new TreeNode(11);
  cout << "Tree Minimum Depth: " << MinimumDepthOfATree(root) << endl;
}

int MaximumDepthOfATree(TreeNode* root) {
  int maximumDepth = 0;
  queue<TreeNode*> incoming;
  incoming.push(root);

  while(!incoming.empty()) {
    maximumDepth++;
    int levelSize = incoming.size();
    for(int i = 0; i < levelSize; i++) {
      TreeNode* node = incoming.front();
      incoming.pop();
      if(node->left) incoming.push(node->left);
      if(node->right) incoming.push(node->right);
    }
  }
  return maximumDepth;
}

void MaximumDepthOfATree() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  cout << "\nTree Maximum Depth: " << MaximumDepthOfATree(root) << endl;
  root->left->left = new TreeNode(9);
  root->right->left->left = new TreeNode(11);
  cout << "Tree Maximum Depth: " << MaximumDepthOfATree(root) << endl;
}

/*
Given a binary tree and a node, find the level order successor of the given node in the tree. The level order successor is the node that appears right after the given node in the level order traversal.
*/


TreeNode* LevelOrderSuccessor(TreeNode* root, int val) {
  if(root == 0) return nullptr;
  queue<TreeNode*> incoming;
  incoming.push(root);
  while(!incoming.empty()) {
    int levelSize = incoming.size();
    for(int i = 0; i < levelSize; i++) {
      TreeNode* node = incoming.front();
      incoming.pop();
      if(node->left) incoming.push(node->left);
      if(node->right) incoming.push(node->right);
      if(node->data == val) {
        return incoming.front();
      }
    }
  }
  return nullptr;
}

void LevelOrderSuccessor() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  TreeNode *result = LevelOrderSuccessor(root, 12);
  cout << "Level Order Successor: " << endl;
  if (result != nullptr) {
    cout << result->data << " " << endl;
  }
  result = LevelOrderSuccessor(root, 9);
  if (result != nullptr) {
    cout << result->data << " " << endl;
  }
}

/*
Given a binary tree, connect each node with its level order successor. The last node of each level should point to a null node.
*/

void ConnectLevelOrderSiblings(TreeNode* root) {
  if(root == 0) return;
  queue<TreeNode*> incoming;
  incoming.push(root);
  while(!incoming.empty()) {
    int levelSize = incoming.size();
    TreeNode* previous = 0;
    for(int i = 0; i < levelSize; i++) {
      TreeNode* node = incoming.front();
      incoming.pop();
      if(previous == 0) {
        previous = node;
      } else {
        previous->next = node;
        previous = node;
      }
      if(node->left) incoming.push(node->left);
      if(node->right) incoming.push(node->right);
    }
  }
}

void PrintLevelOrder(TreeNode *nextLevelRoot) {
    //TreeNode *nextLevelRoot = this;
  while (nextLevelRoot != nullptr) {
    TreeNode *current = nextLevelRoot;
    nextLevelRoot = nullptr;
    while (current != nullptr) {
      cout << current->data << " ";
      if (nextLevelRoot == nullptr) {
        if (current->left != nullptr) {
          nextLevelRoot = current->left;
        } else if (current->right != nullptr) {
          nextLevelRoot = current->right;
        }
      }
      current = current->next;
    }
    cout << endl;
  }
}

void ConnectLevelOrderSiblings() {
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  ConnectLevelOrderSiblings(root);
  cout << "Level order traversal using 'next' pointer: " << endl;
  PrintLevelOrder(root);
}

/*
Given a binary tree, connect each node with its level order successor. The last node of each level should point to the first node of the next level.

*/

void ConnectAllLevelOrderSiblings(TreeNode* root) {
  if(root == 0) return;
  queue<TreeNode*> incoming;
  incoming.push(root);
  TreeNode* previous = 0;
  while(!incoming.empty()) {
    int levelSize = incoming.size();
    for(int i = 0; i < levelSize; i++) {
      TreeNode* node = incoming.front();
      incoming.pop();
      if(previous == 0) {
        previous = node;
      } else {
        previous->next = node;
        previous=node;
      }
      if(node->left) incoming.push(node->left);
      if(node->right) incoming.push(node->right);
    }
  }
}

void PrintTree(TreeNode *current) {
    cout << "Traversal using 'next' pointer: ";
    while (current != nullptr) {
      cout << current->data << " ";
      current = current->next;
    }
  }

void ConnectAllLevelOrderSiblings() {
  cout << "Connecting All Level Order" << endl;
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  ConnectAllLevelOrderSiblings(root);
  PrintTree(root);
}

/*
Given a binary tree, return an array containing nodes in its right view. The right view of a binary tree is the set of nodes visible when the tree is seen from the right side.
*/

vector<TreeNode*> RightViewOfBT(TreeNode* root) {
  vector<TreeNode*> result;
  queue<TreeNode*> incoming;
  incoming.push(root);
  while(!incoming.empty()) {
    int levelSize = incoming.size();
    for(int i = 0; i < levelSize; i++) {
      TreeNode* node = incoming.front();
      incoming.pop();
      if(i == levelSize - 1) {
        result.push_back(node);
      }
      if(node->left) incoming.push(node->left);
      if(node->right) incoming.push(node->right);
    }
  }
  return result;
}

void RightViewOfBT() {
  cout << "\nRight view of BT: " << endl;
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  root->left->left->left = new TreeNode(3);
  vector<TreeNode *> result = RightViewOfBT(root);
  for (auto node : result) {
    cout << node->data << " ";
  }
  cout << endl;
}

int main() {
  LevelOrder();
  ReverseLevelOrder();
  ZigZagTraversal();
  LevelOrderAverage();
  MinimumDepthOfATree();
  MaximumDepthOfATree();
  LevelOrderSuccessor();
  ConnectLevelOrderSiblings();
  ConnectAllLevelOrderSiblings();
  RightViewOfBT();
  return 0;
}