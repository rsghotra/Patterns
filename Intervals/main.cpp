#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>
#include<cmath>
using namespace std;



/*
Merge Intervals
*/

vector<vector<int>> MergeIntervals(vector<vector<int>>& intervals) {
  if(intervals.size() < 2) return intervals;
  std::sort(intervals.begin(), intervals.end(),[](const vector<int>& x, const vector<int>& y) {
    return x[0] < y[0];
  });
  vector<vector<int>> result;
  vector<vector<int>>::const_iterator intervalItr = intervals.begin();
  vector<int> interval = *intervalItr;
  intervalItr++;
  int start = interval[0];
  int end = interval[1];
  while(intervalItr != intervals.end()) {
    interval = *intervalItr++;
    if(interval[0] <= end) {
      end = max(end, interval[1]);
    } else {
      result.push_back({start, end});
      start = interval[0];
      end = interval[1];
    }
  }
  result.push_back({start, end});
  return result;
}

void MergeIntervals() {
	vector<vector<int>> input = {{1, 3}, {2, 5}, {7, 9}};
	cout << "Merged intervals: ";
	for (auto interval : MergeIntervals(input)) {
		cout << "[" << interval[0] << "," << interval[1] << "] ";
	}
	cout << endl;

	input = {{6, 7}, {2, 4}, {5, 9}};
	cout << "Merged intervals: ";
	for (auto interval : MergeIntervals(input)) {
		cout << "[" << interval[0] << "," << interval[1] << "] ";
	}
	cout << endl;

	input = {{1, 4}, {2, 6}, {3, 5}};
	cout << "Merged intervals: ";
	for (auto interval : MergeIntervals(input)) {
		cout << "[" << interval[0] << "," << interval[1] << "] ";
	}
	cout << endl;
}

/*
Insert Interval
*/

vector<vector<int>> InsertInterval(vector<vector<int>>& intervals, vector<int>& newInterval) {
  if(intervals.empty()) {
    return {newInterval};
  }
  //find the correct place;
  vector<vector<int>> result;
  size_t i = 0;
  while(i < intervals.size() && intervals[i][1] < newInterval[0]) {
    result.push_back(intervals[i]);
    i++;
  }
  //keep going & merging; Let’s call the new interval ‘a’ and the first interval with the above condition ‘b’; b.start <= a.end
  while(i < intervals.size() && intervals[i][0] <= newInterval[1]) {
    newInterval[0] = min(newInterval[0], intervals[i][0]);
    newInterval[1] = max(newInterval[1], intervals[1][1]);
    i++;
  }

  result.push_back(newInterval);
  while(i < intervals.size()) {
    result.push_back(intervals[i]);
    i++;
  }
  return result;

}

void InsertIntervals() {
	vector<vector<int>> input = {{1, 3}, {5, 7}, {8, 12}};
	cout << "Intervals after inserting the new interval: ";
	vector<int> newInterval = {4,6};
	for (auto interval : InsertInterval(input, newInterval)) {
		cout << "[" << interval[0] << "," << interval[1]<< "] ";
	}
	cout << endl;

	newInterval = {4, 10};
	cout << "Intervals after inserting the new interval: ";
	for (auto interval : InsertInterval(input, newInterval)) {
		cout << "[" << interval[0] << "," << interval[1]<< "] ";
	}
	cout << endl;

	input = {{2, 3}, {5, 7}};
	newInterval = {1,4};
	cout << "Intervals after inserting the new interval: ";
	for (auto interval : InsertInterval(input, newInterval)) {
		cout << "[" << interval[0] << "," << interval[1] << "] ";
	}
	cout << endl;
}

/*
Intersection of intervals
*/

vector<vector<int>> IntervalsIntersection(vector<vector<int>>& intervals1, vector<vector<int>>& intervals2) {
  vector<vector<int>> result;
  int i = 0, j = 0;
  while(i < intervals1.size() && j < intervals2.size()) {
    //check for intersection
    if((intervals1[i][0] >= intervals2[j][0] && intervals1[i][0] <= intervals2[j][1]) ||
       (intervals2[j][0] >= intervals1[i][0] && intervals2[j][0] <= intervals1[i][1])) {
      result.push_back({max(intervals1[i][0], intervals2[j][0]), min(intervals1[i][1], intervals2[j][1])});
    }
    if(intervals1[i][1] < intervals2[j][1]) {
      i++;
    } else {
      j++;
    }
  }
  return result;
}

void IntervalsIntersection() {
	vector<vector<int>> input1 = {{1, 3}, {5, 6}, {7, 9}};
	vector<vector<int>> input2 = {{2, 3}, {5, 7}};
	vector<vector<int>> result = IntervalsIntersection(input1, input2);
	cout << "Intervals Intersection: ";
	for (auto interval : result) {
		cout << "[" << interval[0] << "," << interval[1] << "] ";
	}
	cout << endl;

	input1 = {{1, 3}, {5, 7}, {9, 12}};
	input2 = {{5, 10}};
	result = IntervalsIntersection(input1, input2);
	cout << "Intervals Intersection: ";
	for (auto interval : result) {
		cout << "[" << interval[0] << "," << interval[1] << "] ";
	}
  cout << endl;
}

/*
Can attend all appointments;
*/
bool CanAttendAllAppointments(vector<vector<int>>& intervals) {
  if(intervals.size() < 2) return true;
  sort(intervals.begin(), intervals.end(), [](const vector<int>& x, const vector<int>& y) {
    return x[0] < y[0];
  });
  vector<vector<int>>::const_iterator intervalItr = intervals.begin();
  vector<int> interval = *intervalItr++;
  int start = interval[0];
  int end = interval[1];
  while(intervalItr != intervals.end()) {
    interval = *intervalItr++;
    if(interval[0] <= end) {
      return false;
    } else {
      start = interval[0];
      end = interval[1];
    }
  }
  return true;
}

void CanAttendAllAppointments() {
	vector<vector<int>> intervals = {{1, 4}, {2, 5}, {7, 9}};
	bool result = CanAttendAllAppointments(intervals);
	cout << "\nCan attend all appointments: " << result << endl;

	intervals = {{6, 7}, {2, 4}, {8, 12}};
	result = CanAttendAllAppointments(intervals);
	cout << "Can attend all appointments: " << result << endl;

	intervals = {{4, 5}, {2, 3}, {3, 6}};
	result = CanAttendAllAppointments(intervals);
	cout << "Can attend all appointments: " << result << endl;
}

/*
Minimum Meeting Room
*/

struct EndCompare {
  bool operator()(vector<int>& x, vector<int>& y) {
    return x[1] > y[1];
  }
};

int MinimumMeetingRooms(vector<vector<int>>& meetings) {
  //sort by min start time;
  //heap by minEnd time
  sort(meetings.begin(), meetings.end(), [](const vector<int>& x, const vector<int>& y) {
    return x[0] < y[0];
  });
  priority_queue<vector<int>, vector<vector<int>>, EndCompare> minHeap;
  int minRooms = 0;
  for(auto meeting: meetings) {
    while(!minHeap.empty() && minHeap.top()[1] <= meeting[0]) {
      minHeap.pop();
    }
    minHeap.push(meeting);
    minRooms = max(minRooms, int(minHeap.size()));
  }
  return minRooms;
}

void MinimumMeetingRooms() {
	vector<vector<int>> input = {{4, 5}, {2, 3}, {2, 4}, {3, 5}};
	int result = MinimumMeetingRooms(input);
	cout << "Minimum meeting rooms required: " << result << endl;

	input = {{1, 4}, {2, 5}, {7, 9}};
	result = MinimumMeetingRooms(input);
	cout << "Minimum meeting rooms required: " << result << endl;

	input = {{6, 7}, {2, 4}, {8, 12}};
	result = MinimumMeetingRooms(input);
	cout << "Minimum meeting rooms required: " << result << endl;

	input = {{1, 4}, {2, 3}, {3, 6}};
	result = MinimumMeetingRooms(input);
	cout << "Minimum meeting rooms required: " << result << endl;

	input = {{4, 5}, {2, 3}, {2, 4}, {3, 5}};
	result = MinimumMeetingRooms(input);
	cout << "Minimum meeting rooms required: " << result << endl;
}

/*
Maximum CPU Load
*/

int MaximumCPULoad(vector<vector<int>>& jobs) {
  sort(jobs.begin(), jobs.end(), [](const vector<int>& x, const vector<int>& y) {
    return x[0] < y[0];
  });

  priority_queue<vector<int>, vector<vector<int>>, EndCompare> minHeap;
  int currentCPULoad = 0;
  int maxCPULoad = 0;
  for(auto job: jobs) {
    while(!minHeap.empty() && job[0] > minHeap.top()[1]) {
      currentCPULoad -= minHeap.top()[2];
      minHeap.pop();
    }
    minHeap.push(job);
    currentCPULoad += job[2];
    maxCPULoad = max(maxCPULoad, currentCPULoad);
  }
  return maxCPULoad;
}

void MaximumCPULoad() {
	vector<vector<int>> input = {{1, 4, 3}, {7, 9, 6}, {2, 5, 4}};
	cout << "Maximum CPU load at any time: " << MaximumCPULoad(input) << endl;

	input = {{6, 7, 10}, {8, 12, 15}, {2, 4, 11}};
	cout << "Maximum CPU load at any time: " << MaximumCPULoad(input) << endl;

	input = {{1, 4, 2}, {3, 6, 5}, {2, 4, 1}};
	cout << "Maximum CPU load at any time: " << MaximumCPULoad(input) << endl;
}

int main() {
  MergeIntervals();
  InsertIntervals();
  IntervalsIntersection();
  CanAttendAllAppointments();
  MinimumMeetingRooms();
  MaximumCPULoad();
  return 0;
}