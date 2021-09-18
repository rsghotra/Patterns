#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
#include<cmath>
using namespace std;

/*
Given an array of n-1n−1 integers in the range from 11 to nn, find the one number that is missing from the array.
*/

int FindMissingNumber(const vector<int>& nums) {
  int x1 = 1;
  int n = nums.size() + 1; //since nums has n-1 numbers;
  for(int i = 2; i <= n; i++) {
    x1 = x1 ^ i;
  }
  int x2 = nums[0];
  for(int j = 1; j < nums.size(); j++) {
    x2 = x2 ^ nums[j];
  }
  return x1 ^ x2;
}

void FindMissingNumber() {
  vector<int> v1 = {1, 5, 2, 6, 4};
  cout << "Missing number is: " << FindMissingNumber(v1);
}

/*
In a non empty array of integers , every number appears twice except for one, find that single number.
*/

int SingleNumber(const vector<int>& nums) {
  int x1 = nums[0];
  for(int i = 1; i < nums.size(); i++) {
    x1 = x1 ^ nums[i];
  }
  return x1;
}

void SingleNumber() {
  cout << "\nSingle number in array of dups: " << endl;
  cout << SingleNumber(vector<int>{1, 4, 2, 1, 3, 2, 3}) << endl;
}

vector<int> TwoSingleNumbers(const vector<int>& nums) {
  int x1 = nums[0];
  for(int i = 1; i < nums.size(); i++) {
    x1 = x1 ^ nums[i];
  }

  //x1 is mix of two nums;
  int rightMostBit = 1;
  while((rightMostBit & x1) == 0) {
    rightMostBit = rightMostBit << 1;
  }
  int num1 = 0;
  int num2 = 0;
  for(int num: nums) {
    if((num & rightMostBit) == 0) {
      num1 = num ^ num1;
    } else {
      num2 = num ^ num2;
    }
  }
  return vector<int>{num1, num2};
}

void TwoSingleNumbers() {
  vector<int> v1 = {1, 4, 2, 1, 3, 5, 6, 2, 3, 5};
  vector<int> result = TwoSingleNumbers(v1);
  cout << "Single numbers are: " << result[0] << ", " << result[1] << endl;

  v1 = {2, 1, 3, 2};
  result = TwoSingleNumbers(v1);
  cout << "Single numbers are: " << result[0] << ", " << result[1] << endl;
}

/*
Every non-negative integer N has a binary representation, for example, 8 can be represented as “1000” in binary and 7 as “0111” in binary.

The complement of a binary representation is the number in binary that we get when we change every 1 to a 0 and every 0 to a 1. For example, the binary complement of “1010” is “0101”.

For a given positive number N in base-10, return the complement of its binary representation as a base-10

number ^ compliment = all_bit_set
number ^ number ^ compliment = number ^ all_bit_set
0 ^ compliment = number ^ all_bit_set

=>compliment = number ^ all_bit_set

Question comes down to discovering how many bits there are in the numbers;
First find out how how many bits are needed to represent number:
take the current number and do a rightShift
*/

int Base10Complement(int num) {
  int n = num;
  int bitCount = 0;
  while(n > 0) {
    bitCount++;
    n = n >> 1;
  }

  int all_bits_set = pow(2, bitCount) - 1;
  return num ^ all_bits_set;
}


void Base10Complement() {
  cout << "Bitwise complement is: " << Base10Complement(8) << endl;
  cout << "Bitwise complement is: " << Base10Complement(10) << endl;
}

/*
Flip Binary Image
*/
vector<vector<int>> FlipBinaryImageHorizonatally(vector<vector<int>> image) {
  for(int row = 0; row < image.size(); row++) {
    for(int col = 0; col < (image[0].size() + 1)/2; col++) {
      int temp = image[row][col] ^ 1;
      image[row][col] = image[row][image[row].size() - col - 1] ^ 1;
      image[row][image[row].size() - col - 1] = temp;
    }
  }
  return image;
}

void print(const vector<vector<int>> arr) {
  for(int i=0; i < arr.size(); i++) {
    for (int j=0; j < arr[i].size(); j++) {
      cout << arr[i][j] << " ";
    }
    cout << "\n";
  }
}

void FlipBinaryImageHorizonatally() {
  vector<vector<int>> arr = vector<vector<int>>{{1, 0, 1}, {1, 1, 1}, {0, 1, 1}};
  print(FlipBinaryImageHorizonatally(arr));
  cout << "\n";

  vector<vector<int>> arr2 = vector<vector<int>>{{1,1,0,0},{1,0,0,1},{0,1,1,1},{1,0,1,0}};
  print(FlipBinaryImageHorizonatally(arr2));
}


int main() {
  FindMissingNumber();
  SingleNumber();
  TwoSingleNumbers();
  Base10Complement();
  FlipBinaryImageHorizonatally();
  return 0;
}