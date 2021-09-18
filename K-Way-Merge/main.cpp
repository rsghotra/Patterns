#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
#include<cmath>
using namespace std;

struct ListNode {
  ListNode* next;
  int data;
  ListNode(int d) {
    this->data = d;
    this->next = 0;
  }
};

/*
Given an array of ‘K’ sorted LinkedLists, merge them into one sorted list.
*/
struct ListCompare {
  bool operator()(const ListNode* x, const ListNode* y) {
    return x->data > y->data;
  }
};

ListNode* MergeKSortedLists(const vector<ListNode*> & lists) {
  priority_queue<ListNode*, vector<ListNode*>, ListCompare> minHeap;
  for(auto head: lists) {
    if(head != 0) {
      minHeap.push(head);
    }
  }
  ListNode* newHead = 0, *tail = 0;

  while(!minHeap.empty()) {
    ListNode* node = minHeap.top();
    minHeap.pop();
    if(newHead == 0) {
      newHead = tail = node;
    } else {
      tail->next = node;
      tail = tail->next;
    }
    if(node->next) {
      minHeap.push(node->next);
    }
  }
  return newHead;
}

void MergeKSortedLists() {
  ListNode *l1 = new ListNode(2);
  l1->next = new ListNode(6);
  l1->next->next = new ListNode(8);

  ListNode *l2 = new ListNode(3);
  l2->next = new ListNode(6);
  l2->next->next = new ListNode(7);

  ListNode *l3 = new ListNode(1);
  l3->next = new ListNode(3);
  l3->next->next = new ListNode(4);

  ListNode *result = MergeKSortedLists(vector<ListNode *>{l1, l2, l3});
  cout << "Here are the elements form the merged list: ";
  while (result != nullptr) {
    cout << result->data << " ";
    result = result->next;
  }
  cout << endl;
}

/*
Merge K Sorted Arrays
*/

struct KValCompare {
  bool operator()(const pair<int, pair<int, int>>& x, const pair<int, pair<int, int>>& y) {
    return x.first > y.first;
  }
};


vector<int> MergeKSortedArrays(const vector<vector<int>>& lists) {
  //minHeap
  priority_queue<pair<int,pair<int,int>>, vector<pair<int, pair<int, int>>>, KValCompare> minHeap;
  //insert first element
  for(int i = 0; i < lists.size(); i++) {
    if(lists[i].empty() == false) {
      minHeap.push(make_pair(lists[i][0], make_pair(i, 0)));
    }
  }
  vector<int> result;
  while(!minHeap.empty()) {
    auto entry = minHeap.top();
    minHeap.pop();
    result.push_back(entry.first);
    entry.second.second++;
    if(lists[entry.second.first].size() > entry.second.second) {
      entry.first = lists[entry.second.first][entry.second.second];
      minHeap.push(entry);
    }
  }
  return result;
}

void MergeKSortedArrays() {
  vector<vector<int>> nums = {{2,6,8}, {3,6,7}, {1,3,4}};

  vector<int> result = MergeKSortedArrays(nums);
  cout << "K Merged arrays: " << endl;
  for(int num: result) {
    cout << num << " ";
  }
  cout << endl;
}

/*
Given ‘M’ sorted arrays, find the  Kth smallest number among all the arrays.
Given ‘M’ sorted arrays, find the median number among all arrays. You are given total numbers in all arrays to be N; so median will basically will be N/2 element; Hence, K = N/2
Given a list of ‘K’ sorted arrays, merge them into one sorted list.
*/

int KthSmallestInMSortedArrays(const vector<vector<int>>& lists, int K) {
  //min heap;
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, KValCompare> minHeap;
  for(int i = 0; i < lists.size(); i++) {
    if(lists[i].empty() == false) {
      minHeap.push(make_pair(lists[i][0], make_pair(i, 0)));
    }
  }

  int count = 0;
  int result = 0;
  while(!minHeap.empty()) {
    auto entry = minHeap.top();
    minHeap.pop();
    count++;
    result = entry.first;
    if(count == K) {
      break;
    }
    entry.second.second++;
    if(lists[entry.second.first].size() > entry.second.second) {
      entry.first = lists[entry.second.first][entry.second.second];
      minHeap.push(entry);
    }
  }
  return result;
}


void KthSmallestInMSortedArrays() {
  vector<vector<int>> lists = {{2, 6, 8}, {3, 6, 7}, {1, 3, 4}};
  int result = KthSmallestInMSortedArrays(lists, 5);
  cout << "Kth smallest number is: " << result;
}

/*
Given an N * NN∗N matrix where each row and column is sorted in ascending order, find the Kth smallest element in the matrix.
*/

int KthSmallestInSortedMatrix(const vector<vector<int>>& matrix, int K) {
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, KValCompare> minHeap;
  for(int i = 0; i < matrix.size() && i < K; i++) {
    if(matrix[i].empty() == false) {
      minHeap.push(make_pair(matrix[i][0], make_pair(i, 0)));
    }
  }

  int count = 0;
  int result = 0;
  while(!minHeap.empty()) {
    auto entry = minHeap.top();
    minHeap.pop();
    count++;
    result = entry.first;
    if(count == K) {
      break;
    }
    entry.second.second++;
    if(matrix[entry.second.first].size() > entry.second.second) {
      entry.first = matrix[entry.second.first][entry.second.second];
      minHeap.push(entry);
    }
  }
  return result;
}


void KthSmallestInSortedMatrix() {
  vector<vector<int>> matrix2 = {vector<int>{2, 6, 8}, vector<int>{3, 7, 10},
                                 vector<int>{5, 8, 11}};
  int result = KthSmallestInSortedMatrix(matrix2, 5);
  cout << "\nKth smallest number in sorted matrix: " << result << endl;
}

/*
Given ‘M’ sorted arrays, find the smallest range that includes at least one number from each of the ‘M’ lists.
*/

pair<int, int> SmallestRange(vector<vector<int>>& lists) {
  priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, KValCompare> minHeap;
  int rangeStart = 0;
  int rangeEnd = INT32_MAX; //carefully chosen to max as we arelooking for min range
  int currentMax = INT32_MIN;
  for(int i = 0; i < lists.size(); i++) {
    if(lists[i].empty() == false) {
      minHeap.push(make_pair(lists[i][0], make_pair(i, 0)));
      currentMax = max(currentMax, lists[i][0]);
    }
  }
  //watch out the condintion; we exist when any of the list is exhausted
  while(minHeap.size() == lists.size()) {
    auto entry = minHeap.top();
    minHeap.pop();
    if((rangeEnd - rangeStart) > (currentMax - entry.first)) {
      rangeEnd = currentMax;
      rangeStart = entry.first;
    }
    entry.second.second++;
    if(lists[entry.second.first].size() > entry.second.second) {
      entry.first = lists[entry.second.first][entry.second.second];
      currentMax = max(currentMax, entry.first);
      minHeap.push(entry);
    }
  }
  return make_pair(rangeStart, rangeEnd);
}


void SmallestRange() {
  vector<vector<int>> lists = {{1, 5, 8}, {4, 12}, {7, 8, 10}};
  auto result = SmallestRange(lists);
  cout << "Smallest range is: [" << result.first << ", " << result.second << "]";
}

/*
K Pairs with Largest Sums: Given two sorted arrays in descending order, find ‘K’ pairs with the largest sum where each pair consists of numbers from both the arrays.
*/

struct PairCompare {
  bool operator()(const pair<int, int>& x, const pair<int, int>&y) {
    return x.first + x.second > y.first + y.second;
  }
};

vector<pair<int, int>> KLargestPairs(const vector<int>& nums1, const vector<int>& nums2, int K) {
  vector<pair<int, int>> minHeap; //for sortedOrder
  for(int i = 0; i < nums1.size(); i++) {
    for(int j = 0; j < nums2.size(); j++) {
      if(minHeap.size() < K) {
        minHeap.push_back(make_pair(nums1[i], nums2[j]));
        push_heap(minHeap.begin(), minHeap.end(), PairCompare());
      } else {
        if(nums1[i] + nums2[j] < minHeap.front().first + minHeap.front().second) {
          break; //no point in moving ahead as array is descending
        } else {
          pop_heap(minHeap.begin(), minHeap.end(), PairCompare());
          minHeap.pop_back();
          minHeap.push_back(make_pair(nums1[i], nums2[j]));
          push_heap(minHeap.begin(), minHeap.end(), PairCompare());
        }
      }
    }
  }
  return minHeap;
}

void KLargestPairs() {
  auto result = KLargestPairs({9, 8, 2}, {6, 3, 1}, 3);
  cout << "\nPairs with largest sum are: ";
  for (pair<int,int> pr : result) {
    cout << "[" << pr.first << ", " << pr.second << "] ";
  }
}


int main() {
  MergeKSortedLists();
  MergeKSortedArrays();
  KthSmallestInMSortedArrays();
  KthSmallestInSortedMatrix();
  SmallestRange();
  KLargestPairs();
  return 0;
}
