#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
#include<set>
#include<cmath>
using namespace std;

/*
K Sum average
*/
vector<double> KSumAverage(int K, const vector<int>& nums) {
  vector<double> result;
  int windowStart  = 0;
  int windowSum = 0;
  for(int windowEnd = 0; windowEnd < nums.size(); windowEnd++) {
     windowSum += nums[windowEnd];
     if(windowEnd - windowStart + 1 == K) {
       result.push_back((1.0*windowSum)/K);
       windowSum -= nums[windowStart];
       windowStart++;
     }
  }
  return result;
}

void KSumAverage() {
	vector<double> result =
    KSumAverage(5, vector<int>{1, 3, 2, 6, -1, 4, 1, 8, 2});
  	cout << "Averages of subarrays of size K: ";
	for (double d : result) {
		cout << d << " ";
	}
	cout << endl;
}

/*
*/

int KMaxSum(int K, const vector<int>& nums) {
  int windowStart = 0;
  int maxSum = INT32_MIN;
  int windowSum = 0;
  for(int windowEnd = 0; windowEnd < nums.size(); windowEnd++) {
    windowSum += nums[windowEnd];
    if(windowEnd - windowStart + 1 == K) {
      maxSum = max(maxSum, windowSum);
      windowSum -= nums[windowStart];
      windowStart++;
    }
  }
  return maxSum;
}


void KMaxSum() {
	cout << "Maximum sum of a subarray of size K: "
       << KMaxSum(3, vector<int>{2, 1, 5, 1, 3, 2}) << endl;
  	cout << "Maximum sum of a subarray of size K: "
       << KMaxSum(2, vector<int>{2, 3, 4, 1, 5}) << endl;
}

/*
Given an array of positive numbers and a positive number ‘S,’ find the length of the smallest contiguous subarray whose sum is greater than or equal to ‘S’. Return 0 if no such subarray exists.

Example 1:

str: [2, 1, 5, 2, 3, 2], S=7 
Output: 2
Explanation: The smallest subarray with a sum greater than or equal to '7' is [5, 2].
*/

int MinSizeSubArraySum(int S, const vector<int>& nums) {
  int windowStart = 0;
  int windowSum = 0;
  int minWindowLen = INT32_MAX;
  for(int windowEnd = 0; windowEnd < nums.size(); windowEnd++) {
    windowSum += nums[windowEnd];
    while(windowSum >= S) {
      minWindowLen = min(minWindowLen, windowEnd - windowStart + 1);
      windowSum -= nums[windowStart];
      windowStart++;
    }
  }
  return minWindowLen == INT32_MAX ? 0 : minWindowLen;
}

void MinSizeSubArraySum() {
	int result = MinSizeSubArraySum(7, vector<int>{2, 1, 5, 2, 3, 2});
	cout << "Smallest subarray length: " << result << endl;
	result = MinSizeSubArraySum(7, vector<int>{2, 1, 5, 2, 8});
	cout << "Smallest subarray length: " << result << endl;
	result = MinSizeSubArraySum(8, vector<int>{3, 4, 1, 1, 6});
	cout << "Smallest subarray length: " << result << endl;
}

/*

*/

int LongestSubstringWithKDistinctChars(const string& str, int K) {
  int windowStart = 0;
  unordered_map<char, int> frequencies;
  int maxLength = INT32_MIN;
  for(int windowEnd = 0; windowEnd <str.size(); windowEnd++) {
    frequencies[str[windowEnd]]++;
    while(frequencies.size() > K) {
      frequencies[str[windowStart]]--;
      if(frequencies[str[windowStart]] == 0) {
        frequencies.erase(str[windowStart]);
      }
      windowStart++;
    }
    maxLength = max(maxLength, windowEnd - windowStart + 1);
  }
  return maxLength == INT32_MIN ? 0 : maxLength; 
}


void LongestSubstringWithKDistinctChars() {
	cout << "Length of the longest substring: " << LongestSubstringWithKDistinctChars("araaci", 2)
       << endl;
  cout << "Length of the longest substring: " << LongestSubstringWithKDistinctChars("araaci", 1)
      << endl;
  cout << "Length of the longest substring: " << LongestSubstringWithKDistinctChars("cbbebi", 3)
      << endl;
}

/*
Everything like above except that K = 2;
OR
Longest Substring with at most 2 distinct characters
*/

int FruitBasket(const vector<char>& fruits) {
  int windowStart = 0;
  int maxLen = INT32_MIN;
  unordered_map<char, int> frequencies;
  for(int windowEnd = 0; windowEnd < fruits.size(); windowEnd++) {
    frequencies[fruits[windowEnd]]++;
    while(frequencies.size() > 2) {
      frequencies[fruits[windowStart]]--;
      if(frequencies[fruits[windowStart]] == 0) {
        frequencies.erase(fruits[windowStart]);
      }
      windowStart++;
    }
    maxLen = max(maxLen, windowEnd - windowStart+1);
  }
  return maxLen == INT32_MIN ? 0 : maxLen;
}

void FruitBasket() {
 	cout << "Maximum number of fruits: "
       	<< FruitBasket(vector<char>{'A', 'B', 'C', 'A', 'C'}) << endl;
  cout << "Maximum number of fruits: "
       	<< FruitBasket(vector<char>{'A', 'B', 'C', 'B', 'B', 'C'}) << endl;
}

/*
Longest Substring with no repeating chars;
set use hoga; while loop use hogi
*/

int NoRepeatSubstringMaxLength(const string& str) {
  int windowStart = 0;
  int windowEnd = 0;
  int maxLen = INT32_MIN;
  set<char> entries;
  while(windowEnd < str.size()) {
    if(entries.find(str[windowEnd]) == entries.end()) {
      entries.insert(str[windowEnd]);
      maxLen = max(windowEnd - windowStart + 1, maxLen);
      windowEnd++;
    } else {
      //found; shrink the window and don't move ahead;
      entries.erase(str[windowStart]);
      windowStart++;
    }
  }
  return maxLen;
}


void NoRepeatSubstringMaxLength() {
	cout << "Length of the longest substring: " << NoRepeatSubstringMaxLength("aabccbb") << endl;
  cout << "Length of the longest substring: " << NoRepeatSubstringMaxLength("abbbb") << endl;
  cout << "Length of the longest substring: " << NoRepeatSubstringMaxLength("abccde") << endl;
}

/*
Dynamic Window + maxFrequencyCount + character replacement
*/
int KCharacterReplacements(const string& str, int K) {
  int windowStart = 0;
  int maxLen = 0;
  int maxCharCount  = 0;
  unordered_map<char, int> frequencies;
  for(int windowEnd = 0; windowEnd < str.size(); windowEnd++) {
    frequencies[str[windowEnd]]++;
    maxCharCount = max(maxCharCount, frequencies[str[windowEnd]]);

    if(windowEnd - windowStart + 1 - maxCharCount > K) {
      frequencies[str[windowStart]]--;
      windowStart++;
    }
    maxLen = max(windowEnd - windowStart + 1, maxLen);
  }
  return maxLen;
}


void KCharacterReplacements() {
	cout << KCharacterReplacements("aabccbb", 2) << endl;
  cout << KCharacterReplacements("abbcb", 1) << endl;
  cout << KCharacterReplacements("abccde", 1) << endl;
}

/*
Longest Substring With Ones after Replacement
*/

int LongestSubArrayReplaceOnes(const vector<int>& nums, int K) {
  int windowStart = 0;
  int maxLen = 0;
  int maxOnesCount = 0;

  for(int windowEnd = 0; windowEnd < nums.size(); windowEnd++) {
    if(nums[windowEnd] == 1) {
      maxOnesCount++;
    }

    if(windowEnd - windowStart + 1 - maxOnesCount > K) {
      if(nums[windowStart] == 1) {
        maxOnesCount--;
      }
      windowStart++;
    }
    maxLen = max(maxLen, windowEnd - windowStart + 1);
  }
  return maxLen;
}

void LongestSubArrayReplaceOnes() {
  cout << "LongestSubArrayReplaceOnes: " << endl;
	cout << LongestSubArrayReplaceOnes(vector<int>{0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1}, 2) << endl;
  cout <<LongestSubArrayReplaceOnes(vector<int>{0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1}, 3) << endl;
}

/*
*/

bool PermutationExists(const string& str, const string& pattern) {
  unordered_map<char, int> frequencies;
  for(char ch: pattern) {
    frequencies[ch]++;
  }
  int windowStart = 0;
  int matchCount = 0;
  for(int windowEnd = 0; windowEnd < str.size(); windowEnd++){
    if(frequencies.find(str[windowEnd]) != frequencies.end()) {
      frequencies[str[windowEnd]]--;
      if(frequencies[str[windowEnd]] == 0) {
        matchCount++;
      }
    }
    if(matchCount == frequencies.size()) {
      return true;
    }
    if(windowEnd - windowStart + 1 == pattern.length()) {
      if(frequencies.find(str[windowStart]) != frequencies.end()) {
        if(frequencies[str[windowStart]] == 0) {
          matchCount--;
        }
        frequencies[str[windowStart]]++;
      }
      windowStart++;
    }
  }
  return false;
}

void PermutationExists() {
	cout << "Permutation exist: " << PermutationExists("oidbcaf", "abc") << endl;
 	cout << "Permutation exist: " << PermutationExists("odicf", "dc") << endl;
  cout << "Permutation exist: " << PermutationExists("bcdxabcdy", "bcdyabcdx") << endl;
  cout << "Permutation exist: " << PermutationExists("aaacb", "abc") << endl;
}

/*
*/

vector<int> StringAnagrams(const string& str, const string& pattern) {
  int windowStart = 0;
  unordered_map<char, int> frequencies;
  for(char ch: pattern) {
    frequencies[ch]++;
  }
  int matchCount = 0;
  vector<int> result;
  for(int windowEnd = 0; windowEnd < str.size(); windowEnd++) {
    if(frequencies.find(str[windowEnd]) != frequencies.end()) {
      frequencies[str[windowEnd]]--;
      if(frequencies[str[windowEnd]] == 0) {
        matchCount++;
      }
    }
    if(matchCount == frequencies.size()) {
      result.push_back(windowStart);
    }

    if(windowEnd - windowStart + 1 == pattern.length()) {
      if(frequencies.find(str[windowStart]) != frequencies.end()) {
        if(frequencies[str[windowStart]] == 0) {
          matchCount--;
        }
        frequencies[str[windowStart]]++;
      }
      windowStart++;
    }
  }
  return result;
}

void StringAnagrams() {
	vector<int> result = StringAnagrams("ppqp", "pq");
	for (auto num : result) {
		cout << num << " ";
	}
	cout << endl;

	result = StringAnagrams("abbcabc", "abc");
	for (auto num : result) {
		cout << num << " ";
	}
	cout << endl;
}

/*
*/

string FindSubstring(const string& str, const string& pattern) {
  int windowStart = 0;
  int subStrStart = 0;
  int minLength = INT32_MAX;
  int matchCount = 0;
  unordered_map<char, int> frequencies;
  for(char ch: pattern) {
    frequencies[ch]++;
  }
  for(int windowEnd = 0; windowEnd < str.size(); windowEnd++) {
    if(frequencies.find(str[windowEnd]) != frequencies.end()) {
      frequencies[str[windowEnd]]--;
      if(frequencies[str[windowEnd]] >= 0) {
        matchCount++;
      }
    }
    while(matchCount == pattern.size()) {
      minLength = min(minLength, windowEnd - windowStart + 1);
      subStrStart = windowStart;
      if(frequencies.find(str[windowStart]) != frequencies.end()) {
        if(frequencies[str[windowStart]] == 0) {
          matchCount--;
        }
        frequencies[str[windowStart]]++;
      }
      windowStart++;
    }
  }
  return minLength > int(str.size()) ? "" : str.substr(subStrStart, minLength);
}

void FindSubstring() {
	  cout << FindSubstring("aabdec", "abc") << endl;
  	cout << FindSubstring("abdbca", "abc") << endl;
  	cout << FindSubstring("adcad", "abc") << endl;
}

int main() {
  KSumAverage();
  KMaxSum();
  MinSizeSubArraySum();
  LongestSubstringWithKDistinctChars();
  FruitBasket();
  NoRepeatSubstringMaxLength();
  KCharacterReplacements();
  LongestSubArrayReplaceOnes();
  PermutationExists();
  StringAnagrams();
  FindSubstring();
}