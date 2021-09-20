#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
#include<cmath>
using namespace std;

void Swap(vector<int>& input, int i, int j) {
  int temp = input[i];
  input[i] = input[j];
  input[j] = temp;
}

pair<int, int> TargetSumHashMap(const vector<int>& input, int targetSum) {
  //number and index
  unordered_map<int, int> mappings;
  for(int i = 0; i < input.size(); i++) {
    if(mappings.find(targetSum - input[i]) != mappings.end()) {
      return make_pair(i, mappings[targetSum - input[i]]);
    } else {
      mappings[input[i]] = i;
    }
  }
  return make_pair(-1, -1);
}

//note the array is sorted that is why two pointer sol is possibe
pair<int, int> TargetSum(const vector<int>& input, int targetSum) {
  int leftPtr = 0;
  int rightPtr = input.size() -1 ;
  while(leftPtr  < rightPtr) {
    if(input[leftPtr] + input[rightPtr] == targetSum) {
      return make_pair(leftPtr, rightPtr);
    } else if(input[leftPtr] + input[rightPtr] < targetSum) {
      leftPtr++;
    } else {
      rightPtr--;
    }
  }
  return make_pair(-1, -1);
}

/*

Given a sorted array, create a new array containing squares of all the numbers of the input array in the sorted order.

Example 1:

Input: [-2, -1, 0, 2, 3]
Output: [0, 1, 4, 4, 9]

*/

vector<int> SquareSorted(const vector<int>& nums) {
  int leftPtr = 0;
  vector<int>result(nums.size());
  int highIndex = nums.size() -1 ;
  int rightPtr = nums.size() - 1;
  while(leftPtr < rightPtr) {
    int leftSquare = nums[leftPtr]*nums[leftPtr];
    int rightSquare = nums[rightPtr]*nums[rightPtr];
    if(leftSquare > rightSquare) {
      result[highIndex] = leftSquare;
      highIndex--;
      leftPtr++;
    } else {
      result[highIndex] = rightSquare;
      highIndex--;
      rightPtr--;
    }
  }
  return result;
}

/*
Given an array of unsorted numbers, find all unique triplets in it that add up to zero.

Example 1:

Input: [-3, 0, 1, 2, -1, 1, -2]
Output: [-3, 1, 2], [-2, 0, 2], [-2, 1, 1], [-1, 0, 1]


as input is unsorted; we must sort them

*/

void SearchPairs(vector<int>& nums, int targetSum, int left, vector<vector<int>>& triplets) {
  int first = nums[left-1];
  int right = nums.size() - 1;
  while(left < right) {
    if(nums[left] + nums[right] == targetSum) {
      triplets.push_back({first, nums[left], nums[right]});
      left++;
      right--;
      while(left < right && nums[left-1] == nums[left]) {
        left++;
      }
      while(left < right && nums[right] == nums[right+1]) {
        right--;
      }
    } else if(nums[left] + nums[right] < targetSum) {
      left++;
    } else {
      right--;
    }
  }
}

vector<vector<int>> TripletsSumToZero(vector<int>& nums) {
  vector<vector<int>> triplets;
  sort(nums.begin(), nums.end());
  for(int i = 0; i < nums.size() - 2; i++) {
    if(i > 0 && nums[i-1] == nums[i]) {
      continue;
    }
    //X+Y+Z=0 ==> Y+Z=-X
    SearchPairs(nums, -nums[i], i+1, triplets);
  }
  return triplets;
}


void SearchClosest(vector<int>& nums, int targetSum, int first, int left, int right, int& smallestDiff) {
  while(left < right) {
    int targetDiff = targetSum - nums[first] - nums[left] - nums[right];
    if(targetDiff == 0) {
      smallestDiff = 0;
      return;
    }
    smallestDiff = min(smallestDiff, abs(targetDiff));
    if(targetDiff > 0) {
      left++;
    }
    if(targetDiff < 0) {
      right--;
    }
  }
}

int TripletsSumCloseToTarget(vector<int>& nums, int targetSum) {
  int smallestDiff = INT32_MAX;
  for(int i = 0; i < nums.size() - 2; i++) {
    int first = i;
    int left = i+1;
    int right = nums.size() - 1;
    SearchClosest(nums, targetSum, first, left, right, smallestDiff);
    if(smallestDiff == 0) {
      break;
    }
  }
  return targetSum - smallestDiff;
}

int CountLess(vector<int>& nums, int targetSum, int left, int& count) {
  int right = nums.size() - 1;
  while(left < right) {
    if(nums[left] + nums[right] < targetSum) {
      count += right - left;
      left++;
    } else {
      right--;
    }
  }
}

int CountTripletsLessThanTarget(vector<int>& nums, int targetSum) {
  sort(nums.begin(), nums.end());
  int count = 0;
  //X+Y+Z=targetSum => Y+Z= targetSum - X => targetSum' = targetSum - X
  for(int i = 0; i < nums.size() - 2; i++) {
    CountLess(nums, targetSum - nums[i], i+1, count);
  }
  return count;
}

void SearchLess(vector<int>& nums, int targetSum, int left, vector<vector<int>>& triplets) {
  int first = left-1;
  int right = nums.size() - 1;
  while(left < right) {
    if(nums[left] + nums[right] < targetSum) {
      triplets.push_back({nums[first], nums[left], nums[right]});
      left++;
    } else {
      right--;
    }
  }
}


vector<vector<int>> SearchTripletsLessThanTarget(vector<int>& nums, int targetSum) {
  sort(nums.begin(), nums.end());
  vector<vector<int>> triplets;
  for(int i = 0; i < nums.size() - 2; i++) {
    SearchLess(nums, targetSum - nums[i], i+1, triplets);
  }
  return triplets;
}


//wrong solution;
vector<vector<int>> SubarraysProductLessThanTarget(vector<int>& input, int target) {
  int product = 1;
  int windowStart = 0;
  vector<vector<int>> result;
  for(int windowEnd = 0; windowEnd < input.size(); windowEnd++) {
    product = product * input[windowEnd];
    while(product >= target && windowStart < (int)input.size()) {
        product = product/input[windowStart];
        windowStart++;
    }
    vector<int> subarray;
    for(int i = windowEnd; i >= windowStart; i--) {
      subarray.push_back(input[i]);
    }
    result.push_back(subarray);
  }
  return result;
}

void DutchFlag(vector<int>& input) {
 int left = 0;
 int right = input.size() - 1;
 int i = 0;
 while(i <= right) {
   if(input[i] == 0) {
     Swap(input, i, left);
     left++;
     i++;
   } else if(input[i] == 1) {
     i++;
   } else {
     Swap(input, i, right);
     right--;
   }
 }
}
void SearchQuadruplets(vector<int>& input, int targetSum, int first, int second, vector<vector<int>>& quadruplets) {
  int left = second + 1;
  int right = input.size() - 1;
  while(left < right) {
    if(input[left] + input[right] + input[first] + input[second] == targetSum) {
      quadruplets.push_back({input[left] , input[right] , input[first] , input[second]});
      left++;
      right--;
      while(left < right && input[left-1] == input[left]) {
        left++;
      }
      while(left < right && input[right] == input[right+1]) {
        right--;
      }
    } else if(input[left] + input[right] < targetSum) {
      left++;
    } else {
      right--;
    }
  }
}

vector<vector<int>> Quadruplets(vector<int>& input, int targetSum) {
  sort(input.begin(), input.end());
  vector<vector<int>> result;
  for(int i = 0; i < input.size() - 3; i++) {
    if(i > 0 && input[i-1] == input[i]) {
      continue;
    }
    for(int j = i+1; j < input.size() - 2; j++) {
      if(j > i+1 && input[j-1] == input[j]) {
        continue;
      }
      SearchQuadruplets(input, targetSum - input[i] - input[j], i, j, result);
    }
  }
  return result;
}



int NextValidIndex(string & str, int index) {
  int backspace = 0;
  while(index >= 0) {
    if(str[index] == '#') {
      backspace++;
    } else if(backspace > 0) {
      backspace--;
    } else {
      break;
    }
    index--;
  }
  return index;
}

bool BackspaceCompare(string& str1, string& str2) {
  int ptr1 = str1.length() - 1;
  int ptr2 = str2.length() - 1;
  while(ptr1 >= 0 || ptr2 >= 0) {
    int I1 = NextValidIndex(str1, ptr1);
    int I2 = NextValidIndex(str2, ptr2);

    if(I1 < 0 && I2 < 0) {
      return true;
    }
    if(I1 < 0 || I2 < 0) {
      return false;
    }
    if(str1[I1] != str2[I2]) {
      return false;
    }
    ptr1 = --I1;
    ptr2 = --I2;
  }
  return true;
}

int ShortestWindowSort(const vector<int>& input) {
  int low = 0;
  int high = input.size() - 1;
  while(low < input.size() - 1 && input[low] <= input[low+1]) {
    low++;
  }
  if(low == input.size() - 1) {
    return 0; //array is sorted;
  }

  while(high > 0 && input[high-1] <= input[high]) {
    high--;
  }

  int subArrayMin = INT32_MAX;
  int subArrayMax = INT32_MIN;
  for(int i = low; i <= high; i++) {
    subArrayMin = min(subArrayMin, input[i]);
    subArrayMax = max(subArrayMin, input[i]);
  }

  while(low > 0 && input[low-1] > subArrayMin) {
    low--;
  }
  while(high < input.size() - 1 && input[high+1] < subArrayMax) {
    high++;
  }
  return high - low + 1;
}


int main() {
  // TargetSumHashMap();
  // TargetSum();
  // SquareSorted();
  // TripletsSumToZero();
  // TripletsSumCloseToZero();
  // CountTripletsLessThanTarget();
  // TripltesLessThanTarget();
  // SubarraysProductLessThanTarget();
  // DutchFlag();
  // Quadruplets();
  // BackspaceCompare();
  // ShortestWindowSort();
  return 0;
}