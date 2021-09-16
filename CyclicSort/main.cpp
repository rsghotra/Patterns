#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;


/*
Write a function to sort the objects in-place on their creation sequence number in O(n) and without any extra space.
Each object, when created, was assigned a unique number from 1 to ‘n’ based on their creation sequence
*/

void Swap(vector<int>& nums, int i, int j) {
  int temp = nums[i];
  nums[i] = nums[j];
  nums[j] = temp; 
}

//1 to n; you know; -1 on both important terms
void CycleSort(vector<int>& nums) {
  //nums[i] == i + 1; => nums[i] - 1 = i;
  int i = 0;
  while(i < nums.size()) {
    if(nums[i] > 0 && nums[i] != i+1 && nums[i] - 1 < nums.size() && nums[i] != nums[nums[i] - 1]) {
      Swap(nums, i, nums[i] - 1);
    } else {
      i++;
    }
  }
}

void CycleSort() {
    vector<int> arr = {3, 1, 5, 4, 2};
    CycleSort(arr);
    for (auto num : arr) {
      cout << num << " ";
    }
    cout << endl;

    arr = vector<int>{2, 6, 4, 3, 1, 5};
    CycleSort(arr);
    for (auto num : arr) {
      cout << num << " ";
    }
    cout << endl;

    arr = vector<int>{1, 5, 6, 4, 3, 2};
    CycleSort(arr);
    for (auto num : arr) {
      cout << num << " ";
    }
    cout << endl;
}

/*
We are given an array containing ‘n’ distinct numbers taken from the range 0 to ‘n’. Since the array has only ‘n’ numbers out of the total ‘n+1’ numbers, find the missing number.
0 to n; n+1 numbs but have onlt n
nums[i] = i;
*/
int MissingNumber(vector<int>& nums) {
  //nums[i] = i
  int i = 0;
  while(i < nums.size()) {
    //for 0 to n; nums[i] >= 0; when 1 to n ; nums[i] > 0 are entertained
    if(nums[i] >= 0 && nums[i] < nums.size() && nums[i] != i && nums[i] != nums[nums[i]]) {
      Swap(nums, i, nums[i]);
    } else{
      i++;
    }
  }

  for(int j = 0; j < nums.size(); j++) {
    if(nums[j] != j) {
      return j;
    }
  }
  return -1;
}

void MissingNumber() {
  vector<int> v1 = {4, 0, 3, 1};
  cout << "Missing Number: ";
  cout << MissingNumber(v1) << endl;
  v1 = {8, 3, 5, 2, 4, 6, 0, 1};
  cout << MissingNumber(v1) << endl;
}

/*
We are given an unsorted array containing numbers taken from the range 1 to ‘n’. The array can have duplicates, which means some numbers will be missing. Find all those missing numbers.
1 to n
*/

vector<int> MissingNumbers(vector<int>& nums) {
  vector<int> result;
  int i = 0;
  while(i < nums.size()) {
    if(nums[i] > 0 && nums[i] - 1 < nums.size() && nums[i] != i+1 && nums[i] != nums[nums[i] - 1]) {
      Swap(nums, i, nums[i] - 1);
    } else {
      i++;
    }
  }
  for(int j = 0; j < nums.size(); j++) {
    if(nums[j] != j+1) {
      result.push_back(j+1);
    }
  }
  return result;
}

void MissingNumbers() {
  vector<int> v1 = {2, 3, 1, 8, 2, 3, 5, 1};
  vector<int> missing = MissingNumbers(v1);
  cout << "Missing numbers: ";
  for (auto num : missing) {
    cout << num << " ";
  }
  cout << endl;

  v1 = {2, 4, 1, 2};
  missing = MissingNumbers(v1);
  cout << "Missing numbers: ";
  for (auto num : missing) {
    cout << num << " ";
  }
  cout << endl;

  v1 = {2, 3, 2, 1};
  missing = MissingNumbers(v1);
  cout << "Missing numbers: ";
  for (auto num : missing) {
    cout << num << " ";
  }
  cout << endl;
}

/*
We are given an unsorted array containing ‘n+1’ numbers taken from the range 1 to ‘n’. The array has only one duplicate but it can be repeated multiple times. Find that duplicate number without using any extra space. You are, however, allowed to modify the input array.
*/

int DuplicateNumber(vector<int>& nums) {
  int i = 0;
  while(i < nums.size()) {
    if(nums[i] > 0 && nums[i] != i+1 && nums[i] - 1 < nums.size() && nums[i] != nums[nums[i] - 1]) {
      Swap(nums, i, nums[i] - 1);
    } else {
      i++;
    }
  }
  for(int j = 0; j < nums.size(); j++) {
    if(nums[j] != j+1) {
      return nums[j];
    }
  }
} 

void DuplicateNumber() {
  cout << "Duplicate Number: " << endl;
  vector<int> v1 = {1, 4, 4, 3, 2};
  cout << DuplicateNumber(v1) << endl;

  v1 = {2, 1, 3, 3, 5, 4};
  cout << DuplicateNumber(v1) << endl;

  v1 = {2, 4, 1, 4, 4};
  cout << DuplicateNumber(v1) << endl;
}

/*
Problem 1: Can we solve the above problem in O(1)O(1) space and without modifying the input array?

Solution: While doing the cyclic sort, we realized that the array will have a cycle due to the duplicate number and that the start of the cycle will always point to the duplicate number. This means that we can use the fast & the slow pointer method to find the duplicate number or the start of the cycle similar to Start of LinkedList Cycle.
*/

int FindDuplicate(vector<int>& nums, int cycleLength) {
  int pointer1 = 0;
  int pointer2 = 0;
  while(cycleLength > 0) {
    pointer1 = nums[pointer1];
    cycleLength--;
  }

  while(pointer1 != pointer2) {
    pointer1 = nums[pointer1];
    pointer2 = nums[pointer2];
  }
  return pointer1;
}

int DuplicateNumberFastSlow(vector<int>& nums) {
  int slow = 0;
  int fast = 0;
  do {
    slow = nums[slow];
    fast = nums[nums[fast]];
  }while(slow != fast);
  
  int cycleLength = 0;
  int current = nums[slow];
  do {
    cycleLength++;
    current = nums[current];
  } while(current != nums[slow]);

  return FindDuplicate(nums, cycleLength);
}

void DuplicateNumberFastSlow() {
  cout << "Duplicate Numbers Fast Slow: " << endl;
  vector<int> v1 = {1, 4, 4, 3, 2};
  cout << DuplicateNumberFastSlow(v1) << endl;

  v1 = {2, 1, 3, 3, 5, 4};
  cout << DuplicateNumberFastSlow(v1) << endl;

  v1 = {2, 4, 1, 4, 4};
  cout << DuplicateNumberFastSlow(v1) << endl;
}

/*
We are given an unsorted array containing ‘n’ numbers taken from the range 1 to ‘n’. The array has some numbers appearing twice, find all these duplicate numbers without using any extra space.
1 to n
*/

vector<int> DuplicateNumbers(vector<int>& nums) {
  vector<int> duplicates;
  int i = 0;
  while(i < nums.size()) {
    if(nums[i] > 0 && nums[i] != i+1 && nums[i] != nums[nums[i] - 1] && nums[i] - 1 < nums.size()) {
      Swap(nums, i, nums[i] - 1);
    } else {
      i++;
    }
  }
  for(int j = 0; j < nums.size(); j++) {
    if(nums[j] != j+1) {
      duplicates.push_back(nums[j]);
    }
  }
  return duplicates;
}

void DuplicateNumbers() {
  vector<int> v1 = {3, 4, 4, 5, 5};
  vector<int> duplicates = DuplicateNumbers(v1);
  cout << "Duplicates are: ";
  for (auto num : duplicates) {
    cout << num << " ";
  }
  cout << endl;

  v1 = {5, 4, 7, 2, 3, 5, 3};
  duplicates = DuplicateNumbers(v1);
  cout << "Duplicates are: ";
  for (auto num : duplicates) {
    cout << num << " ";
  }
  cout << endl;
}

/*
We are given an unsorted array containing ‘n’ numbers taken from the range 1 to ‘n’. The array originally contained all the numbers from 1 to ‘n’, but due to a data error, one of the numbers got duplicated which also resulted in one number going missing. Find both these numbers.
*/

vector<int> CorruptPairs(vector<int>& nums) {
  int duplicateNumber = 0;
  int missingNumber = 0;
  int i = 0;
  while(i < nums.size()) {
    if(nums[i] > 0 && nums[i] != i+1 && nums[i] - 1 < nums.size() && nums[i] != nums[nums[i] - 1]) {
      Swap(nums, i, nums[i] - 1);
    } else {
      i++;
    }
  }
  for(int j = 0; j < nums.size(); j++) {
    if(nums[j] != j + 1) {
      duplicateNumber = nums[j];
      missingNumber = j+1;
      break;
    }
  }
  return vector<int>{duplicateNumber, missingNumber};
}

void CorruptPairs() {
  vector<int> v1 = {3, 1, 2, 5, 2};
  vector<int> nums = CorruptPairs(v1);
  cout << nums[0] << ", " << nums[1] << endl;

  v1 = {3, 1, 2, 3, 6, 4};
  nums = CorruptPairs(v1);
  cout << nums[0] << ", " << nums[1] << endl;
}


/*
Given an unsorted array containing numbers, find the smallest missing positive number in it.
*/

int FirstSmallestPositiveNumbers(vector<int>& nums) {
  int i = 0;
  while(i < nums.size()) {
    if(nums[i] > 0 && nums[i] - 1 < nums.size() && nums[i] != i + 1 && nums[i] != nums[nums[i] - 1]) {
      Swap(nums, i, nums[i] - 1);
    } else {
      i++;
    }
  }
  for(int j = 0; j < nums.size(); j++) {
    if(nums[j] != j+1) {
      return j+1;
    }
  }
  return nums.size();
}


void FirstSmallestPositiveNumbers() {
  cout << "First smallest missing positive number: " << endl;
  vector<int> v1 = {-3, 1, 5, 4, 2};
  cout << FirstSmallestPositiveNumbers(v1) << endl;

  v1 = {3, -2, 0, 1, 2};
  cout << FirstSmallestPositiveNumbers(v1) << endl;

  v1 = {3, 2, 5, 1};
  cout << FirstSmallestPositiveNumbers(v1) << endl;
}

/*
Given an unsorted array containing numbers and a number ‘k’, find the first ‘k’ missing positive numbers in the array.
*/

vector<int> FirstKMissingPositiveNumbers(vector<int>& nums, int K) {
  int i = 0;
  while(i < nums.size()) {
    if(nums[i] > 0 && nums[i] - 1 < nums.size() && nums[i] != i+1 && nums[i] != nums[nums[i] - 1]) {
      Swap(nums, i, nums[i] - 1);
    } else {
      i++;
    }
  }
  vector<int> missingNumbers;
  unordered_set<int> extraNumbers;

  for(int j = 0; j < nums.size() && missingNumbers.size() < K; j++) {
    if(nums[j] != j+1) {
      missingNumbers.push_back(j+1);
      extraNumbers.insert(nums[j]);
    }
  }

  int seed = 1;
  while(missingNumbers.size() < K) {
    int candidate = seed + nums.size();
    if(extraNumbers.find(candidate) == extraNumbers.end()) {
      missingNumbers.push_back(candidate);
    }
    seed++;
  }
  return missingNumbers;
}

void FirstKMissingPositiveNumbers() {
  vector<int> v1 = {3, -1, 4, 5, 5};
  vector<int> missingNumbers = FirstKMissingPositiveNumbers(v1, 3);
  cout << "Missing numbers: ";
  for (auto num : missingNumbers) {
    cout << num << " ";
  }
  cout << endl;

  v1 = {2, 3, 4};
  missingNumbers = FirstKMissingPositiveNumbers(v1, 3);
  cout << "Missing numbers: ";
  for (auto num : missingNumbers) {
    cout << num << " ";
  }
  cout << endl;

  v1 = {-2, -3, 4};
  missingNumbers = FirstKMissingPositiveNumbers(v1, 2);
  cout << "Missing numbers: ";
  for (auto num : missingNumbers) {
    cout << num << " ";
  }
  cout << endl;
}


int main() {
  CycleSort();
  MissingNumber();
  MissingNumbers();
  DuplicateNumber();
  DuplicateNumberFastSlow();
  DuplicateNumbers();
  CorruptPairs();
  FirstSmallestPositiveNumbers();
  FirstKMissingPositiveNumbers();
  return 0;
}