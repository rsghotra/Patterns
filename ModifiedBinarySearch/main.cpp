#include<iostream>
#include<vector>
#include<limits>
using namespace std;

class ArrayReader {
 public:
  vector<int> arr;

  ArrayReader(const vector<int> &arr) { this->arr = arr; }

  virtual int get(int index) {
    if (index >= arr.size()) {
      return numeric_limits<int>::max();
    }
    return arr[index];
  }
};

int OrderAgnosticBS(const vector<int>& nums, int key) {
  int start = 0, end = nums.size() - 1;
  bool isAscending = nums[start] < nums[end];

  while(start <= end) {
    int mid = start + (end - start)/2;
    if(key == nums[mid]) {
      return mid;
    }
    if(isAscending) {
      if(key < nums[mid]) {
        end = mid - 1;
      } else {
        start = mid + 1;
      }
    } else {
      if(key < nums[mid]) {
        start = mid + 1;
      } else {
        end  = mid -1 ;
      }
    }
  }
  return -1;
}

int Ceiling(const vector<int>& nums, int key) {
  if(key > nums[nums.size() - 1]) { //ceiling will not exist if key is bigger
    return -1;
  }
  int start = 0;
  int end = nums.size() - 1;

  while(start <= end) {
    int mid = start + (end - start)/2;
    if(key == nums[mid]) {
      return mid;
    } else if(key < nums[mid]) {
      end = mid-1;
    } else {
      start = mid + 1;
    }
  }
  return start;
}

int Floor(const vector<int>& nums, int key) {
  if(key < nums[0]) {
    return -1;
  }

  int start = 0;
  int end = nums.size() - 1;
  while(start <= end) {
    int mid = start + (end - start)/2;
    if(key == nums[mid]) {
      return mid;
    } else if(key < nums[mid]) {
      end = mid-1;
    } else {
      start = mid + 1;
    }
  }
  return end;
}

void OrderAgnosticBS() {
  cout << OrderAgnosticBS(vector<int>{4, 6, 10}, 10) << endl;
  cout << OrderAgnosticBS(vector<int>{1, 2, 3, 4, 5, 6, 7}, 5) << endl;
  cout << OrderAgnosticBS(vector<int>{10, 6, 4}, 10) << endl;
  cout << OrderAgnosticBS(vector<int>{10, 6, 4}, 4) << endl;
}

void Ceiling() {
  cout << "Ceilings: " << endl;
  cout << Ceiling(vector<int>{4, 6, 6}, 6) << endl;
  cout << Ceiling(vector<int>{1, 3, 8, 10, 15}, 12) << endl;
  cout << Ceiling(vector<int>{4, 6, 10}, 17) << endl;
  cout << Ceiling(vector<int>{4, 6, 10}, -1) << endl;
}

void Floor() {
  cout << "Floors: " << endl;
  cout << Floor(vector<int>{4, 6, 6}, 6) << endl;
  cout << Floor(vector<int>{1, 3, 8, 10, 15}, 12) << endl;
  cout << Floor(vector<int>{4, 6, 10}, 17) << endl;
  cout << Floor(vector<int>{4, 6, 10}, -1) << endl;
}

char NextLetter(const vector<char>& letters, char key) {
  if(key < letters[0] || key > letters[letters.size() - 1]) {
    return letters[0];
  }
  int start = 0;
  int end = letters.size() - 1;
  while(start <= end) {
    int mid = start + (end - start)/2;
    if(key < letters[mid]) {
      end = mid-1;
    } else {
      start = mid + 1;
    }
  }
  return letters[start%letters.size()];
}

void NextLetter() {
  cout << "Next Letter " <<endl;
  cout << NextLetter(vector<char>{'a', 'c', 'f', 'h'}, 'f') << endl;
  cout << NextLetter(vector<char>{'a', 'c', 'f', 'h'}, 'b') << endl;
  cout << NextLetter(vector<char>{'a', 'c', 'f', 'h'}, 'm') << endl;
  cout << NextLetter(vector<char>{'a', 'c', 'f', 'h'}, 'h') << endl;
}

int BSNumberRangeSearch(const vector<int>& nums, int key, bool highIndex){
  int keyIndex = -1;
  int start = 0;
  int end = nums.size() - 1;
  while(start <= end) {
    int mid = start + (end - start)/2;
    if(key == nums[mid]){ //key == nums[mid]
      keyIndex = mid;
      if(highIndex) {
        start = mid+1;
      } else {
        end  = mid - 1;
      }
    } else if(key < nums[mid]) {
      end = mid - 1;
    } else if(key > nums[mid]) {
      start = mid + 1;
    }
  }
  return keyIndex;
}

pair<int, int> NumberRange(const vector<int>& nums, int key) {
  pair<int, int> result(-1, -1);
  result.first = BSNumberRangeSearch(nums, key, false);
  if(result.first != -1) {
    result.second = BSNumberRangeSearch(nums, key, true);
  }
  return result;
}

void NumberRange() {
  pair<int, int> result = NumberRange(vector<int>{4, 6, 6, 6, 9}, 6);
  cout << "Range: [" << result.first << ", " << result.second << "]" << endl;
  result = NumberRange(vector<int>{1, 3, 8, 10, 15}, 10);
  cout << "Range: [" << result.first << ", " << result.second << "]" << endl;
  result = NumberRange(vector<int>{1, 3, 8, 10, 15}, 12);
  cout << "Range: [" << result.first << ", " << result.second << "]" << endl;
}

/*
Search in a Sorted Infinited Array
*/

int BinarySearch(ArrayReader* reader, int key, int start, int end) {
  while(start <= end) {
    int mid = start + (end - start)/2;
    if(key == reader->get(mid)) {
      return mid;
    } else if(key < reader->get(mid)) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }
  return -1;
}

int SearchSortedInfinite(ArrayReader* reader, int key) {
  //find the fucking bounds;
  int start = 0;
  int end = 1;
  while(reader->get(end) < key) {
    int newStart = end + 1;
    end = (end - start + 1)* 2;
    start = newStart;
  }
  return BinarySearch(reader, key, start, end);
}



void SearchSortedInfinite() {
  cout << "Search Sorted Infinite" << endl;
  ArrayReader *reader =
      new ArrayReader(vector<int>{4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30});
  cout << SearchSortedInfinite(reader, 16) << endl;
  cout << SearchSortedInfinite(reader, 11) << endl;
  reader = new ArrayReader(vector<int>{1, 3, 8, 10, 15});
  cout << SearchSortedInfinite(reader, 15) << endl;
  cout << SearchSortedInfinite(reader, 200) << endl;
  delete reader;
}

/*
Given an array of numbers sorted in ascending order, find the element in the array that has the minimum difference with the given ‘key’.

if key is present return key;
else return minimum of start and end;
*/

int MinimumDifference(const vector<int>& nums, int key) {
  if(key < nums[0]) {
    return nums[0];
  }
  if(key > nums[nums.size() - 1]) {
    return nums[nums.size() - 1];
  }
  int start = 0;
  int end = nums.size() - 1;
  while(start <= end) {
    int mid = start + (end - start)/2;
    if(key == nums[mid]) {
      return key;
    }
    if(key < nums[mid]) {
      end = mid -1;
    } else {
      start = mid + 1;
    }
  }
  if(abs(key - nums[start]) < abs(key - nums[end])) {
    return nums[start];
  }
  return nums[end];
}

void MinimumDifference() {
  cout << "Minimum Difference " << endl;
  cout << MinimumDifference(vector<int>{4, 6, 10}, 7) << endl;
  cout << MinimumDifference(vector<int>{4, 6, 10}, 4) << endl;
  cout << MinimumDifference(vector<int>{1, 3, 8, 10, 15}, 12) << endl;
  cout << MinimumDifference(vector<int>{4, 6, 10}, 17) << endl;
}

/*


*/

int MaxInBitonicArray(const vector<int>& nums) {
  //in bitonic array start == end is where the peak element will be
  int start = 0;
  int end = nums.size() - 1;
  while(start < end) { // we will stop when start == end
      int mid  = start + (end - start)/2;
      if(nums[mid] > nums[mid+1]) {
        end = mid;
      } else {
        start = mid + 1;
      }
  }
  return nums[start]; //or nums[end] as start == end;
}

void MaxInBitonicArray() {
  cout << "Max in Bitonic Array " << endl;
  cout << MaxInBitonicArray(vector<int>{1, 3, 8, 12, 4, 2}) << endl;
  cout << MaxInBitonicArray(vector<int>{3, 8, 3, 1}) << endl;
  cout << MaxInBitonicArray(vector<int>{1, 3, 8, 12}) << endl;
  cout << MaxInBitonicArray(vector<int>{10, 9, 8}) << endl;
}

/*
Given a Bitonic array, find if a given ‘key’ is present in it. An array is considered bitonic if it is monotonically increasing and then monotonically decreasing. Monotonically increasing or decreasing means that for any index i in the array arr[i] != arr[i+1].
*/

int FindMaxElementIndexBitonic(const vector<int>& nums) {
  int start = 0;
  int end = nums.size() - 1;
  while(start < end) {
    int mid = start + (end - start)/2;
    if(nums[mid] > nums[mid+1]) {
      end = mid;
    } else {
      start = mid + 1;
    }
  }
  return start; // or end as start == end at this time; 
}

int StandardBinarySearch(const vector<int>& nums, int start, int end, int key){
  while(start <= end) {
    int mid = start + (end - start)/2;
    if(key == nums[mid]) {
      return mid;
    }
    if(nums[start] < nums[end] ) { //ascending
      if(key < nums[mid]) {
        end = mid - 1;
      } else if(key > nums[mid]) {
        start = mid + 1;
      }
    } else {
      if(key < nums[mid]) {
        start = mid + 1;
      } else if(key > nums[mid]) {
        end = mid - 1;
      }
    }
  }
  return -1;
}

int SearchBitonicArray(const vector<int>& nums, int key) {
  //findMaxElement index from bitonic;
  int maxIndex = FindMaxElementIndexBitonic(nums);
  int foundAt = StandardBinarySearch(nums, 0, maxIndex, key);
  if(foundAt == -1) {
    foundAt = StandardBinarySearch(nums, maxIndex+1, nums.size() - 1, key);
  }
  return foundAt;
}

void SearchBitonicArray() {
  cout << "Searching Bitonic " << endl;
  cout << SearchBitonicArray(vector<int>{1, 3, 8, 4, 3}, 4) << endl;
  cout << SearchBitonicArray(vector<int>{3, 8, 3, 1}, 8) << endl;
  cout << SearchBitonicArray(vector<int>{1, 3, 8, 12}, 12) << endl;
  cout << SearchBitonicArray(vector<int>{10, 9, 8}, 10) << endl;
}

/*
Search rotated array no dups;
*/

//10, 15, 1, 3, 8
int SearchRotatedArrayNoDups(const vector<int>& nums, int key) {
  //no smart check as array is up and down
  int start = 0;
  int end = nums.size() - 1;
  while(start <= end) {
    int mid = start + (end - start)/2;
    if(key == nums[mid]) return mid;
    if(nums[start] <= nums[mid]) {
      //left part is sorted
      if(key >= nums[start] && key < nums[mid]) {
        end = mid - 1;
      } else {
        start = mid + 1;
      }
    } else {
      if(key > nums[mid] && key <= nums[end]) {
        start = mid + 1;
      } else {
        end = mid - 1;
      }
    }
  }
  return -1;
}

void SearchRotatedArrayNoDups() {
  cout << "Searching Rotated Array No Dups " << endl;
  cout << SearchRotatedArrayNoDups(vector<int>{10, 15, 1, 3, 8}, 15) << endl;
  cout << SearchRotatedArrayNoDups(vector<int>{4, 5, 7, 9, 10, -1, 2}, 10) << endl;
}

/*
Search Rotated Array with Dups
*/
int SearchRotatedArrayDups(const vector<int>& nums, int key) {
  int start = 0;
  int end = nums.size() - 1;
  while(start <= end) {
    int mid = start + (end - start)/2;
    if(nums[mid] == key) {
      return mid;
    }
    if((nums[mid] == nums[start]) && (nums[mid] == nums[end])) {
      start++;
      end--;
    } else if(nums[start] <= nums[mid]) {
      if(key >= nums[start] && key < nums[mid]) {
        end = mid - 1;
      } else {
        start = mid + 1;
      }
    } else {
      if(key > nums[mid] && key <= nums[end]) {
        start = mid + 1;
      } else {
        end = mid - 1;
      }
    }
  }
  return -1;
}

void SearchRotatedArrayDups() {
  cout << "Searching in Roatated array with Dups: " << endl;
  cout << SearchRotatedArrayDups(vector<int>{3, 7, 3, 3, 3}, 7) << endl;
}


/*
Rotation Count No Dups

*/
int RotationCountNoDups(const vector<int>& nums) {
  int start = 0;
  int end = nums.size() - 1;

  while(start <= end) {
    int mid = start + (end - start)/2;
    //check if mid is the min
    if(start < mid && nums[mid-1] > nums[mid]) {
      return mid;
    }
    if(mid < end && nums[mid] > nums[mid+1]) {
      return mid+1;
    }
    if(nums[start] <= nums[mid]) {
      //means the pivot will be present on the right
      start = mid + 1;
    } else {
      end = mid - 1;
    }
  }
  return 0;
}

void RotationCountNoDups() {
  cout << "Rotation Count No Dups: " << endl;
  cout << RotationCountNoDups(vector<int>{10, 15, 1, 3, 8}) << endl;
  cout << RotationCountNoDups(vector<int>{4, 5, 7, 9, 10, -1, 2}) << endl;
  cout << RotationCountNoDups(vector<int>{1, 3, 8, 10}) << endl;
}

/*
Rotation Count: Dups
*/

int RotationCountDups(const vector<int>& nums) {
  int start = 0;
  int end = nums.size() -1 ;
  while(start <= end) {
    int mid = start + (end - start)/2;
    //check if mid suits this criteria
    //for start <--
    if(start < mid && nums[mid-1] > nums[mid]) {
      return mid;
    }
    if(mid < end && nums[mid] > nums[mid+1]) {
      return mid+1;
    }

    if((nums[start] == nums[mid]) && (nums[mid] == nums[end])) {
      //can't blindly move start and end; these coudl be valid;
      //for start -->
      if(nums[start] > nums[start+1]) {
        return start + 1;
      }
      start++;
      if(nums[end-1] > nums[end]) {
        return end;
      }
      end--;
    } else if(nums[start] <= nums[mid]) {
      start = mid + 1;
    } else {
      end = mid -1 ;
    }
  }
  return 0;
}

void RotationCountDups() {
  cout << "Rotation Count Dups " << endl;
  cout << RotationCountDups(vector<int>{3, 3, 7, 3}) << endl;
  cout << RotationCountDups(vector<int>{4, 5, 7, 9, 10, -1, 2}) << endl;
}
 
int main() {
//start <= end
  OrderAgnosticBS();
  Ceiling();
  Floor();
  NextLetter();
  NumberRange();
  SearchSortedInfinite();
  MinimumDifference();
  //start < end
  //bitonic
  MaxInBitonicArray();
  SearchBitonicArray();
  //rotated
  SearchRotatedArrayNoDups();
  SearchRotatedArrayDups();
  RotationCountNoDups();
  RotationCountDups();
  return 0;
}