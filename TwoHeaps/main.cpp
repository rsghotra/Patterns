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

int main() {
  StreamMedian();
  MaximizeCapital();
  return 0;
}