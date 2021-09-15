#include<iostream>
using namespace std;

struct ListNode {
  ListNode* next;
  int data;
  ListNode(int data) {
    this->data = data;
    this->next = 0;
  }
};

/*
Given the head of a Singly LinkedList, reverse the LinkedList. Write a function to return the new head of the reversed LinkedList.
T(N) = O(N) where N are the number of nodes;
S(N) = O(1)
*/
ListNode* Reverse(ListNode* head) {
  ListNode* current = head;
  ListNode* previous = 0;
  ListNode* next = 0;
  while(current != 0) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }
  return previous;
}

void Reverse() {
  ListNode *head = new ListNode(2);
  head->next = new ListNode(4);
  head->next->next = new ListNode(6);
  head->next->next->next = new ListNode(8);
  head->next->next->next->next = new ListNode(10);

  ListNode *result = Reverse(head);
  cout << "Nodes of the reversed LinkedList are: ";
  while (result != nullptr) {
    cout << result->data << " ";
    result = result->next;
  }
  cout << endl;
}

/*
Given the head of a LinkedList and two positions ‘p’ and ‘q’, reverse the LinkedList from position ‘p’ to ‘q’.
OR
Reverse the first ‘k’ elements of a given LinkedList. P = 1, Q = k
T(N): O(N)
S(N): O(1)
*/

ListNode* ReverseSublist(ListNode* head, int p, int q) {
  //reverse between p and q; but first reached the appropriate positions
  ListNode* current = head;
  ListNode* previous = 0;
  int i = 0;
  for(i = 0; i < p - 1 && current != 0; i++) {
    previous = current;
    current = current->next;
  }
  if(current == 0) {
    return head;
  }
  ListNode* lastNodePrevious = previous;
  ListNode* lastNodeCurrent = current;
  ListNode* next = 0;
  for(int i = 0; i < q-p+1 && current != 0; i++) {
    next = current->next;
    current->next = previous;
    previous = current;
    current = next;
  }

  if(lastNodePrevious) {
    lastNodePrevious->next = previous;
  } else {
    head = previous;
  }
  lastNodeCurrent->next = current;
  return head;
}

void ReverseSublist() {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);

  ListNode *result = ReverseSublist(head, 2, 4);
  cout << "Nodes of the reversed LinkedList are: ";
  while (result != nullptr) {
    cout << result->data << " ";
    result = result->next;
  }
  cout << endl;
}

/*
Given a LinkedList with ‘n’ nodes, reverse it based on its size in the following way:

If ‘n’ is even, reverse the list in a group of n/2 nodes.
If n is odd, keep the middle node as it is, reverse the first ‘n/2’ nodes and reverse the last ‘n/2’ nodes.
*/

int Length(ListNode* head) {
  int len = 0;
  while(head) {
    len++;
    head = head->next;
  }
  return len;
}

void ReverseOddEvenSublists() {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);

  int n = Length(head);
  ListNode* result = 0;
  if(n%2 == 0) {
    //even
    cout << "Reversing Even List" << endl;
    result = ReverseSublist(head, 0, n/2);
    result = ReverseSublist(result, n/2+1, n);
  } else {
    cout << "Reversing Odd List" << endl;
    result = ReverseSublist(head, 0, n/2);
    result = ReverseSublist(result, n/2+2, n);
  }
  
  cout << "Nodes of the reversed LinkedList are: ";
  while (result != nullptr) {
    cout << result->data << " ";
    result = result->next;
  }
  cout << endl;
}


/*
Given the head of a LinkedList and a number ‘k’, reverse every ‘k’ sized sub-list starting from the head.
T(N) = O(N)
S(N) = O(1)
*/

ListNode* ReverseKSizedSublists(ListNode* head, int K) {
  if(head == 0 || K <= 0) return head;

  ListNode* current = head;
  ListNode* previous = 0;
  
  //no need move to the position as we are in the right position anyways.
  while(current != 0) {
    ListNode* lastPrevious = previous;
    ListNode* lastCurrent = current;
    ListNode* next = 0;
    for(int i = 0; current != 0 && i < K; i++) {
      next = current->next;
      current->next = previous;
      previous = current;
      current = next;
    }
    
    if(lastPrevious) {
      lastPrevious->next = previous;
    } else {
      head = previous;
    }
    lastCurrent->next = current;
    //if you put this line before 176; LL will be malformed
    if(current == 0) break;
    previous = lastCurrent; //previous right now poiint on first node of the reverse LL, whereas it should now be reset to last node of the newly reverse list because we have to move on to reverse next part; Current is already well place.
  }
  return head;
}

void ReverseKSizedSublists() {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);
  head->next->next->next->next->next = new ListNode(6);
  head->next->next->next->next->next->next = new ListNode(7);
  head->next->next->next->next->next->next->next = new ListNode(8);

  ListNode *result = ReverseKSizedSublists(head, 3);
  cout << "Nodes of the reversed LinkedList are: ";
  while (result != nullptr) {
    cout << result->data << " ";
    result = result->next;
  }
}

/*
Given the head of a Singly LinkedList and a number ‘k’, rotate the LinkedList to the right by ‘k’ nodes.
T(N): O(N)
Algo:
1. Find Len and Last Node of the LL
2. Connect Last Node's next to current head;
3. Skip k-1 steps to come at right position
4. newHead = lastNode->next 
4. lastNode->next = 0;
*/

ListNode* Rotate(ListNode* head, int rotations) {
  if(head == 0 || head->next == 0 || rotations <= 0) {
    return head;
  }

  //1
  int listLen = 1;
  ListNode* lastNode = head;
  while(lastNode->next) {
    listLen++;
    lastNode = lastNode->next;
  }

  //2
  lastNode->next = head;

  //3;
  rotations = rotations%listLen;
  int skipLen = listLen - rotations;
  ListNode* lastNodeOfLL = head;
  for(int i = 0; i < skipLen-1; i++) {
    lastNodeOfLL = lastNodeOfLL->next;
  }

  //4
  head = lastNodeOfLL->next;
  lastNodeOfLL->next = 0;
  
  return head;
}

void Rotate() {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);
  head->next->next->next->next->next = new ListNode(6);

  ListNode *result = Rotate(head, 3);
  cout << "\nNodes of the rotated LinkedList are: ";
  while (result != nullptr) {
    cout << result->data << " ";
    result = result->next;
  }
}

/*
Given the head of a LinkedList and a number ‘k’, reverse every alternating ‘k’ sized sub-list starting from the head.
If, in the end, you are left with a sub-list with less than ‘k’ elements, reverse it too.
T(N): O(N)
*/

ListNode* ReverseAlternatingKSublists(ListNode* head, int K) {
  if(head == 0 || head->next == 0 || K <= 0) {
    return head;
  }

  ListNode* previous = 0;
  ListNode* current = head;
  ListNode* next = 0;

  while(current != 0) {

    ListNode* lastNodePrevious = previous;
    ListNode* lastNodeCurrent = current;

    //remember when doing for K times then i < K;
    //however to come to the correct positoin in order to start processing i < K-1
    for(int i = 0; i < K && current != 0; i++) {
      next = current->next;
      current->next = previous;
      previous = current;
      current = next;
    }

    if(lastNodePrevious) {
      lastNodePrevious->next = previous;
    } else {
      head = previous;
    }

    lastNodeCurrent->next = current;
    if(current == 0) {
      break;
    }
    previous = lastNodeCurrent;
    for(int i = 0; i < K && current != 0; i++) {
      previous = current;
      current = current->next;
    }
  }
  return head;
}

void ReverseAlternatingKSublists() {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);
  head->next->next->next->next->next = new ListNode(6);
  head->next->next->next->next->next->next = new ListNode(7);
  head->next->next->next->next->next->next->next = new ListNode(8);

  ListNode *result = ReverseAlternatingKSublists(head, 2);
  cout << "\nNodes of the alternating K reversed LinkedList are: ";
  while (result != nullptr) {
    cout << result->data << " ";
    result = result->next;
  }
}


int main() {
  Reverse();
  ReverseSublist();
  ReverseOddEvenSublists();
  ReverseKSizedSublists();
  Rotate();
  ReverseAlternatingKSublists();
  return 0;
}