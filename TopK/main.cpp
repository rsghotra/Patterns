#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
using namespace std;

struct ValCompare {
  bool operator() (const int& x, const int& y) {
    return x > y;
  }
};

struct DistCompare {
  bool operator() (const vector<int>& point1, const vector<int>& point2) {
      int dist1 = point1[0]*point1[0] + point1[1]*point1[1];
      int dist2 = point2[0]*point2[0] + point2[1]*point2[1];
      return dist1 < dist2;
  }
};

struct FrequencyCompare {
  bool operator()(const pair<int, int>& x, const pair<int, int>& y) {
    return x.second > y.second;
  }
};

struct CharFrequencyCompare {
  bool operator()(const pair<char, int>& x, const pair<char, int>& y) {
    return x.second < y.second;
  }
};

vector<int> KLargestNumbers(const vector<int>& nums, int K) {
  if(K > nums.size()) {
    return {};
  }
  //insert K element into minHeap;
  vector<int> minHeap(nums.begin(), nums.begin() + K);//means i = k-1 at the end;
  make_heap(minHeap.begin(), minHeap.end(), ValCompare());
  for(int i = K; i < nums.size(); i++) {
    if(nums[i] > minHeap.front()) {
      pop_heap(minHeap.begin(), minHeap.end(), ValCompare());
      minHeap.pop_back();
      minHeap.push_back(nums[i]);
      push_heap(minHeap.begin(), minHeap.end(), ValCompare());
    }
  }
  return minHeap;
}

void KLargestNumbers() {
  vector<int> result = KLargestNumbers(vector<int>{3, 1, 5, 12, 2, 11}, 3);
  cout << "Here are the top K numbers: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  result = KLargestNumbers(vector<int>{5, 12, 11, -1, 12}, 3);
  cout << "Here are the top K numbers: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;
}

/*
K smallest numbers
*/
int KthSmallestNumber(const vector<int>& nums, int K) {
  if(K > nums.size()) {
    return 0;
  }
  priority_queue<int, vector<int>> maxHeap;
  for(int i = 0; i < K; i++) {
    maxHeap.push(nums[i]);
  }

  for(int i = K; i < nums.size(); i++) {
    if(nums[i] < maxHeap.top()) {
      maxHeap.pop();
      maxHeap.push(nums[i]);
    }
  }
  return maxHeap.top();
}

void KthSmallestNumber() {
  int result = KthSmallestNumber(vector<int>{1, 5, 12, 2, 11, 5}, 3);
  cout << "Kth smallest number is: " << result << endl;

  // since there are two 5s in the input array, our 3rd and 4th smallest numbers should be a '5'
  result = KthSmallestNumber(vector<int>{1, 5, 12, 2, 11, 5}, 4);
  cout << "Kth smallest number is: " << result << endl;

  result = KthSmallestNumber(vector<int>{5, 12, 11, -1, 12}, 3);
  cout << "Kth smallest number is: " << result << endl;
}

/*
K Closest Points To Origin;
maxHeap;
*/

vector<vector<int>> KClosestPointsToOrigin(const vector<vector<int>>& points, int K) {
  vector<vector<int>> maxHeap(points.begin(), points.begin() + K);
  make_heap(maxHeap.begin(), maxHeap.end(), DistCompare());
  for(int i = K; i < points.size(); i++) {
    if((points[i][0]*points[i][0] + points[i][1]*points[i][1]) < (maxHeap.front()[0]*maxHeap.front()[0] + maxHeap.front()[1]*maxHeap.front()[1])) {
      pop_heap(maxHeap.begin(), maxHeap.end(), DistCompare());
      maxHeap.pop_back();
      maxHeap.push_back(points[i]);
      push_heap(maxHeap.begin(), maxHeap.end(), DistCompare());
    }
  }
  return maxHeap;
}

void KClosestPointsToOrigin() {
  vector<vector<int>> points = KClosestPointsToOrigin({{1, 3}, {3, 4}, {2, -1}}, 2);
  cout << "Here are the k points closest the origin: ";
  for (auto p : points) {
    cout << "[" << p[0] << " , " << p[1] << "] ";
  }
  cout << endl;
}

/*
Connect Ropes; Need to make a Rope With MinCost;
Greedy Approach - put entire data into minHeap;
then take one rope at a time; join them, push them back;
Keep doing until heap has only 1 big rope.
*/

int ConnectRopes(const vector<int>& ropes) {
  priority_queue<int, vector<int>, greater<>> minHeap;
  for(auto rope: ropes) {
    minHeap.push(rope);
  }
  int cost = 0;
  int temp = 0;
  while(minHeap.size() > 1) {
    temp = minHeap.top();
    minHeap.pop();
    temp += minHeap.top();
    minHeap.pop();
    cost += temp;
    minHeap.push(temp);
  }
  return cost;
}

void ConnectRopes() {
  int result = ConnectRopes(vector<int>{1, 3, 11, 5});
  cout << "Minimum cost to connect ropes: " << result << endl;
  result = ConnectRopes(vector<int>{3, 4, 5, 6});
  cout << "Minimum cost to connect ropes: " << result << endl;
  result = ConnectRopes(vector<int>{1, 3, 11, 5, 2});
  cout << "Minimum cost to connect ropes: " << result << endl;
}

/*
Given an unsorted array of numbers, find the top ‘K’ frequently occurring numbers in it.
top K
Frequently: some sort of frequency Map;

Simplest Algo: Prepare a freqency Map; Insert each entry of the map in minHeap; When HeapSize > K; Pop One.

*/

vector<int> TopKFrequent(const vector<int>& nums, int K) {
  unordered_map<int, int> frequencies;
  for(int num: nums) {
    frequencies[num]++;
  }
  priority_queue<pair<int, int>, vector<pair<int,int>>, FrequencyCompare> minHeap;
  //watch out: iterating over the frequencies not INPUT
  for(auto entry: frequencies) {
    minHeap.push(entry);
    if(minHeap.size() > K) {
      minHeap.pop();
    }
  }

  vector<int> result;
  while(!minHeap.empty()) {
    result.push_back(minHeap.top().first);
    minHeap.pop();
  }
  return result;
}

void TopKFrequent() {
  vector<int> result =
      TopKFrequent(vector<int>{1, 3, 5, 12, 11, 12, 11}, 2);
  cout << "Here are the K frequent numbers: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  result = TopKFrequent(vector<int>{5, 12, 11, 3, 11}, 2);
  cout << "Here are the K frequent numbers: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;
}

/*
Frequency Sort: Given a string, sort it based on the decreasing frequency of its characters.
*/

string FrequencySort(const string& input) {
  unordered_map<char, int> frequencies;
  for(auto ch: input) {
    frequencies[ch]++;
  }
  priority_queue<pair<char, int>, vector<pair<char, int>> , CharFrequencyCompare> maxHeap;
  for(auto entry: frequencies) {
    maxHeap.push(entry);
  }
  string result = "";
  while(!maxHeap.empty()) {
    auto entry = maxHeap.top();maxHeap.pop();
    while(entry.second > 0) {
      result += entry.first;
      entry.second--;
    }
  }
  return result;
}

void FrequencySort() {
  string result = FrequencySort("Programming");
  cout << "Here is the given string after sorting characters by frequency: " << result << endl;

  result = FrequencySort("abcbab");
  cout << "Here is the given string after sorting characters by frequency: " << result << endl;
}

/*
Design a class to efficiently find the Kth largest element in a stream of numbers.

The class should have the following two things:

The constructor of the class should accept an integer array containing initial numbers from the stream and an integer ‘K’.
The class should expose a function add(int num) which will store the given number and return the Kth largest number.
*/
//make a MinHeap; incoming is larger than Top then push and POP: Only K are allowed

class KthLargestNumberInStream {
  private:
    priority_queue<int, vector<int>, ValCompare> minHeap;
    int K;
  public:
    KthLargestNumberInStream(const vector<int>& stream, int K) {
      this->K = K; //K must be set before for loop;
      for(int i = 0; i < stream.size(); i++) {
        add(stream[i]);
      }
      
    }
    int add(int num) {
      minHeap.push(num);
      if(minHeap.size() > this->K) {
        minHeap.pop();
      }
      return minHeap.top();
    }
};

void KthLargestNumberStream() {
    KthLargestNumberInStream kthLargestNumber({3, 1, 5, 12, 2, 11}, 4);
    cout << "4th largest number is: " << kthLargestNumber.add(6) << endl;
    cout << "4th largest number is: " << kthLargestNumber.add(13) << endl;
    cout << "4th largest number is: " << kthLargestNumber.add(4) << endl;
}

/*
K closest numbers
Given a sorted number array and two integers ‘K’ and ‘X’, find ‘K’ closest numbers to ‘X’ in the array. Return the numbers in the sorted order. ‘X’ is not necessarily present in the array.

Algo:
 - Implement a simple Binary Search; which will return mid - if not found
 - From index X; start moving left and right
*/
int BinarySearch(const vector<int>& nums, int key) {
  int start = 0;
  int end = nums.size() - 1;
  while(start <= end) {
    int mid = start + (end - start)/2;
    if(nums[mid] == key) {
      return mid;
    } else if(key < nums[mid]) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }
  if(start == nums.size()) {
    start = start - 1;
  }
  return start;
}


vector<int> KClosestNumbers(const vector<int>& nums, int K, int X) {
  deque<int> result;
  int index = BinarySearch(nums, X);
  int leftPointer = index;
  int rightPointer = index + 1;
  for(int i = 0; i < K; i++) {
    if(leftPointer >= 0 && rightPointer < nums.size()) {
      if(abs(nums[leftPointer] - X) < abs(nums[rightPointer] - X)) {
        result.push_front(nums[leftPointer]);
        leftPointer--; // <-|->
      } else {
        result.push_back(nums[rightPointer]);
        rightPointer++; // <-|->
      }
    } else if(leftPointer >= 0) {
      result.push_front(nums[leftPointer]);
      leftPointer--;
    } else if(rightPointer < nums.size()) {
      result.push_back(nums[rightPointer]);
      rightPointer++;
    }
  }
  vector<int> movedResult;
  std::move(result.begin(), result.end(), back_inserter(movedResult));
  return movedResult;
}

void KClosestNumbers() {
  vector<int> result = KClosestNumbers(vector<int>{5, 6, 7, 8, 9}, 3, 7);
  cout << "'K' closest numbers to 'X' are: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  result = KClosestNumbers(vector<int>{2, 4, 5, 6, 9}, 3, 6);
  cout << "'K' closest numbers to 'X' are: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  result = KClosestNumbers(vector<int>{2, 4, 5, 6, 9}, 3, 10);
  cout << "'K' closest numbers to 'X' are: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;
}

/*
Given an array of numbers and a number ‘K’, we need to remove ‘K’ numbers from the array such that we are left with maximum distinct numbers.
Algo:
  - Greedy Approach: we will try to remove the less frequent element to get    more distinct elements
  - Prepare a MAP of frequencies;
  - declare numOfDistintChar = 0
  - traverse the map and if the incoming has:
    - frequncy == 1 => numOfDistintChar++
    - frequency > 1 => push on the MinHeap
*/

int MaximumDistinctElements(const vector<int>& nums, int K) {
  unordered_map<int, int> frequencies;
  priority_queue<pair<int, int>, vector<pair<int,int>>, FrequencyCompare> minHeap;
  int num_of_distinct = 0;
  for(int num: nums) {
    frequencies[num]++;
  }
  for(auto entry: frequencies) {
    if(entry.second == 1) {
      num_of_distinct++;
    } else {
      minHeap.push(entry);
    }
  }

  while(minHeap.empty() == false && K > 0) {
    auto entry = minHeap.top();
    minHeap.pop();
    while(K > 0 && entry.second > 1) {
      K--;
      entry.second--;
    }
    if(entry.second == 1) {
      num_of_distinct++;
    }
  }

  while(K > 0 && num_of_distinct > 0) {
    K--;
    num_of_distinct--;
  }
  return num_of_distinct;
}

void MaximumDistinctElements() {
  int result =
      MaximumDistinctElements(vector<int>{7, 3, 5, 8, 5, 3, 3}, 2);
  cout << "Maximum distinct numbers after removing K numbers: " << result << endl;

  result = MaximumDistinctElements(vector<int>{3, 5, 12, 11, 12}, 3);
  cout << "Maximum distinct numbers after removing K numbers: " << result << endl;

  result = MaximumDistinctElements(
      vector<int>{1, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5}, 2);
  cout << "Maximum distinct numbers after removing K numbers: " << result << endl;
}

/*
Given an array, find the sum of all numbers between the K1’th and K2’th smallest elements of that array.

*/

int SumOfElementsK1ToK2(const vector<int>& nums, int K1, int K2) {
  priority_queue<int, vector<int>, greater<>> minHeap;
  for(int num: nums) {
    minHeap.push(num);
  }

  int sum = 0;
  for(int i = 1; i <= K1; i++) {
    minHeap.pop();
  }
  for(int i = K1 + 1; i < K2; i++) {
    sum += minHeap.top();
    minHeap.pop();
  }
  return sum;
}

void SumOfElementsK1ToK2() {
  int result = SumOfElementsK1ToK2(vector<int>{1, 3, 12, 5, 15, 11}, 3, 6);
  cout << "Sum of all numbers between k1 and k2 smallest numbers: " << result << endl;

  result = SumOfElementsK1ToK2(vector<int>{3, 5, 8, 7}, 1, 4);
  cout << "Sum of all numbers between k1 and k2 smallest numbers: " << result << endl;
}

/*
Given a string, find if its letters can be rearranged in such a way that no two same characters come next to each other.
Example 1:
Input: "aappp"
Output: "papap"
Explanation: In "papap", none of the repeating characters come next to each other.

Algo:
  - Prepare a frequency Map of the string
  - Greedy Approach: MaxHeap based on Frequency;
  - pick One Char and append to the output;
  - if frequency is still > 1 then set this element as previous;


*/

string ReArrangeString(const string& str) {
  unordered_map<char, int> frequencies;
  for(char ch: str) {
    frequencies[ch]++;
  }
  priority_queue<pair<char, int>, vector<pair<char, int>>, CharFrequencyCompare> maxHeap;
  for(auto entry: frequencies) {
    maxHeap.push(entry);
  }
  string result = "";

  pair<char, int> previous(-1, -1);
  while(maxHeap.empty() == false) {
    auto entry = maxHeap.top();
    maxHeap.pop();
    result += entry.first;
    entry.second--;
    if(previous.second > 0) {
      maxHeap.push(previous);
    }
    previous = entry;
  }
  return result.size() == str.size() ? result : "";
}

void ReArrangeString() {
  cout << "Rearranged string: " << ReArrangeString("aappp") << endl;
  cout << "Rearranged string: " << ReArrangeString("Programming") << endl;
  cout << "Rearranged string: " << ReArrangeString("aapa") << endl;
}

/*
Given a string and a number ‘K’, find if the string can be rearranged such that the same characters are at least ‘K’ distance apart from each other.
Algo: 
  - prepare a frequency map
  - prepare a maxHeap on frequency
  - insert complete string into frequency map
  - keep a queue of previous
  - when queue size() == K; take out one char from front;

*/
string ReArrangeStringKDistanceApart(const string& str, int K) {
  unordered_map<char, int> frequencies;
  for(char ch: str) {
    frequencies[ch]++;
  }

  priority_queue<pair<char, int>, vector<pair<char, int>>, CharFrequencyCompare> maxHeap;
  for(auto entry: frequencies) {
    maxHeap.push(entry);
  }

  queue<pair<char, int>> queue;
  string result = "";
  while(!maxHeap.empty()) {
    auto entry = maxHeap.top();
    maxHeap.pop();
    result += entry.first;
    entry.second--;
    queue.push(entry);
    if(queue.size() == K) {
      auto entry = queue.front();
      queue.pop();
      if(entry.second > 0) {
        maxHeap.push(entry);
      }
    }
  }
  return result.size() == str.size() ? result : "";
}


void ReArrangeStringKDistanceApart() {
  cout << "Reorganized string: "
       << ReArrangeStringKDistanceApart("Programming", 3) << endl;
  cout << "Reorganized string: "
       << ReArrangeStringKDistanceApart("mmpp", 2) << endl;
  cout << "Reorganized string: "
       << ReArrangeStringKDistanceApart("aab", 2) << endl;
  cout << "Reorganized string: " << ReArrangeStringKDistanceApart("aappa", 3)
       << endl;
}

/*
Scheduling Tasks: You are given a list of tasks that need to be run, in any order, on a server. Each task will take one CPU interval to execute but once a task has finished, it has a cooling period during which it can’t be run again. If the cooling period for all tasks is ‘K’ intervals, find the minimum number of CPU intervals that the server needs to finish all tasks.

If at any time the server can’t execute any task then it must stay idle.

Example 1:

Input: [a, a, a, b, c, c], K=2
Output: 7
Explanation: a -> c -> b -> a -> c -> idle -> a

Algo: 
  - frequency map of occurences
  - begin with a max frequency task
  - keep a queue managed
  - keep a interval count
WRONG IMPLEMENTATION BELOW;
*/

int ScheduleTasks(vector<char>& tasks, int K) {
  unordered_map<char, int> frequencies;
  for(char ch: tasks) {
    frequencies[ch]++;
  }
  
  priority_queue<pair<char, int>, vector<pair<char, int>>, CharFrequencyCompare> maxHeap;
  for(auto entry: frequencies) {
    maxHeap.push(entry);
  }

  queue<pair<char, int>> interim;
  int intervals = 0;

  while(!maxHeap.empty()) {
    auto entry = maxHeap.top();
    maxHeap.pop();
    intervals++;
    entry.second--;
    interim.push(entry);
    if(interim.size() == K) {
      auto entry = interim.front(); interim.pop();
      if(entry.second > 0) {
        maxHeap.push(entry);
      }
      intervals++;
    }
  }

  return intervals;
}

void ScheduleTasks() {
  vector<char> tasks = {'a', 'a', 'a', 'b', 'c', 'c'};
  cout << "Minimum intervals needed to execute all tasks: "
       << ScheduleTasks(tasks, 2) << endl;

  tasks = vector<char>{'a', 'b', 'a'};
  cout << "Minimum intervals needed to execute all tasks: "
       << ScheduleTasks(tasks, 3) << endl;
}

/*
Frequency Stack: Design a class that simulates a Stack data structure, implementing the following two operations:

push(int num): Pushes the number ‘num’ on the stack.
pop(): Returns the most frequent number in the stack. If there is a tie, return the number which was pushed later.

More of less it is a matter of Can you fucking write a Comparator?
*/
class Element {
  private:
  public:
    int data;
    int frequency;
    int sequenceNumber;
    Element(int d, int f, int s) {
      this->data = d;
      this->frequency = f;
      this->sequenceNumber = s;
    }
};

struct EleCompare {
  bool operator()(const Element& e1, const Element& e2) {
    if(e1.frequency == e2.frequency) {
      return e1.sequenceNumber < e2.sequenceNumber;
    }
    return e1.frequency < e2.frequency;
  }
};

class FrequencyStack {
  private:
    int sequenceNumber = 0;
    priority_queue<Element, vector<Element>, EleCompare> maxHeap;
    unordered_map<int, int> frequencies;
  public:
    virtual void push(int num) {
      sequenceNumber++;
      frequencies[num]++;
      maxHeap.push({num, frequencies[num], sequenceNumber});
    }
    virtual int pop() {
      int num = maxHeap.top().data;
      maxHeap.pop();
      frequencies[num]--;
      if(frequencies[num] == 0) {
        frequencies.erase(num);
      }
      return num;
    }
};

void FrequencyStk() {
  FrequencyStack frequencyStack;
  frequencyStack.push(1);
  frequencyStack.push(2);
  frequencyStack.push(3);
  frequencyStack.push(2);
  frequencyStack.push(1);
  frequencyStack.push(2);
  frequencyStack.push(5);
  cout << frequencyStack.pop() << endl;
  cout << frequencyStack.pop() << endl;
  cout << frequencyStack.pop() << endl;
}

int main() {
  KLargestNumbers();
  KthSmallestNumber();
  KClosestPointsToOrigin();
  ConnectRopes();
  //map + heap
  TopKFrequent();
  FrequencySort();
  //infinite stream
  KthLargestNumberStream();
  //Binary Search + Heap
  KClosestNumbers();
  //map + heap
  MaximumDistinctElements();
  SumOfElementsK1ToK2();
  //re-arrangement - game of previous & queue; Scheduling; CPU Scheduling
  ReArrangeString();
  ReArrangeStringKDistanceApart();
  ScheduleTasks();
  FrequencyStk();
  return 0;
}