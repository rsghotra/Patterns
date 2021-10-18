#include<iostream>
#include<queue>
using namespace std;

class MedianOfAStream {
  private:
    priority_queue<int> maxHeap; //connecting first half of a number;
    priority_queue<int, vector<int>, greater<>> minHeap; //connecting second half of a number
  public:
    void InsertNum(int num) {
      if(maxHeap.empty() || maxHeap.top() >= num) {
        maxHeap.push(num);
      } else {
        minHeap.push(num);
      }

      if(maxHeap.size() > minHeap.size() + 1){
        minHeap.push(maxHeap.top());
        maxHeap.pop();
      } else if(maxHeap.size() < minHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
      }
    }

    double CalculateMedian() {
      if(maxHeap.size() == minHeap.size()) {
        return (minHeap.top() + maxHeap.top())/2.0;
      }
      return maxHeap.top();
    }
};

void StreamMedian() {
  MedianOfAStream medianOfAStream;
  medianOfAStream.InsertNum(3);
  medianOfAStream.InsertNum(1);
  cout << "The median is: " << medianOfAStream.CalculateMedian() << endl;
  medianOfAStream.InsertNum(5);
  cout << "The median is: " << medianOfAStream.CalculateMedian() << endl;
  medianOfAStream.InsertNum(4);
  cout << "The median is: " << medianOfAStream.CalculateMedian() << endl;
}

/*
Given a set of investment projects with their respective profits, we need to find the most profitable projects. We are given an initial capital and are allowed to invest only in a fixed number of projects. Our goal is to choose projects that give us the maximum profit. Write a function that returns the maximum total capital after selecting the most profitable projects.

We can start an investment project only when we have the required capital. Once a project is selected, we can assume that its profit has become our capital.
*/

  struct CapitalCompare {
    bool operator()(const pair<int, int>& x, const pair<int, int>& y) {
      return x.first > y.first;
    }
  };
  struct ProfitCompare {
    bool operator()(const pair<int, int>& x, const pair<int, int>& y) {
      return x.first < y.first;
    }
  };
  priority_queue<pair<int, int>, vector<pair<int, int>>, CapitalCompare> minCapitalHeap;
  priority_queue<pair<int, int>, vector<pair<int, int>>, ProfitCompare> maxProfitHeap;
   
  int FindMaximumCapital(const vector<int>& capital, const vector<int>& profits, int numProjects, int initialCapital) {
      //step 1. prepare minCapitalHeap;
      for(int i = 0; i < capital.size(); i++) {
        minCapitalHeap.push(make_pair(capital[i], i));
      }

      int availableCapital = initialCapital;
      for(int i = 0; i < numProjects; i++) {
        while(!minCapitalHeap.empty() && minCapitalHeap.top().first <= availableCapital) {
          auto capitalIndex = minCapitalHeap.top().second;
          minCapitalHeap.pop();
          maxProfitHeap.push(make_pair(profits[capitalIndex], capitalIndex));
        }

        if(maxProfitHeap.empty()) {
          break;
        }
        availableCapital += maxProfitHeap.top().first;
        maxProfitHeap.pop();
      }
      return availableCapital;
  }

void MaximizeCapital() {
  int result =
        FindMaximumCapital(vector<int>{0, 1, 2}, vector<int>{1, 2, 3}, 2, 1);
    cout << "Maximum capital: " << result << endl;
    result =
        FindMaximumCapital(vector<int>{0, 1, 2, 3}, vector<int>{1, 2, 3, 5}, 3, 0);
    cout << "Maximum capital: " << result << endl;
}

template<typename T, class Container = vector<T>, class Compare = less<typename Container::value_type>>
class priority_queue_with_remove: public priority_queue<T, Container, Compare> {
public:
    bool remove(const T & valToRemove) {
        auto itr = std::find(this->c.begin(), this->c.end(), valToRemove);
        if(itr == this->c.end()) {
            return false;
        }
        this->c.erase(itr);
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
        return true;
    }
};

class SlidingWindowMedian {
 public:
  virtual void rebalanceHeaps(priority_queue_with_remove<int>& maxHeap,priority_queue_with_remove<int, vector<int>, greater<>>& minHeap) {
    if(maxHeap.size() > minHeap.size() + 1) {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
    } else if(maxHeap.size() < minHeap.size()) {
        maxHeap.push(minHeap.top());
        minHeap.pop();
    }
  }
    
  virtual double calculateMedian(priority_queue_with_remove<int>& maxHeap,priority_queue_with_remove<int, vector<int>, greater<>>& minHeap) {
    double median = 0;
    if(maxHeap.size() == minHeap.size()) {
        median = maxHeap.top()/2.0  + minHeap.top()/2.0;
    } else {
        median = maxHeap.top();
    }
    return median;
  }

  virtual vector<double> findSlidingWindowMedian(const vector<int> &nums, int k) {
    vector<double> result;
    priority_queue_with_remove<int> maxHeap;
    priority_queue_with_remove<int, vector<int>, greater<>> minHeap;
    
    int windowStart = 0;
    for(int windowEnd = 0; windowEnd < nums.size(); windowEnd++) {
        //usually we have maps or some other logic. But in this case we will have heap logic
        if(maxHeap.empty() || maxHeap.top() >= nums[windowEnd]) {
            maxHeap.push(nums[windowEnd]);
        } else {
            minHeap.push(nums[windowEnd]);
        }
        rebalanceHeaps(maxHeap, minHeap);
        
        if(windowEnd - windowStart + 1 >= k) {
            result.push_back(calculateMedian(maxHeap, minHeap));
            int elementToBeRemoved = nums[windowStart];
            if(elementToBeRemoved <= maxHeap.top()) {
                maxHeap.remove(elementToBeRemoved);
            } else {
                minHeap.remove(elementToBeRemoved);
            }
            rebalanceHeaps(maxHeap, minHeap);
            windowStart++;
        }
    }
    return result;
  }
};

int SlidingWindowMedian() {
  SlidingWindowMedian slidingWindowMedian;
  vector<double> result =
      slidingWindowMedian.findSlidingWindowMedian(vector<int>{1, 2, -1, 3, 5}, 2);
  cout << "Sliding window medians are: ";
  for (auto num : result) {
    cout << num << " ";
  }
  cout << endl;

  slidingWindowMedian = SlidingWindowMedian();
  result = slidingWindowMedian.findSlidingWindowMedian(vector<int>{1, 2, -1, 3, 5}, 3);
  cout << "Sliding window medians are: ";
  for (auto num : result) {
    cout << num << " ";
  }
}


int main() {
  StreamMedian();
  MaximizeCapital();
  SlidingWindowMedian();
  return 0;
}
