#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
	ListNode *next;
	int data;
	ListNode(int data) {
		this->data = data;
		next = nullptr;
	}
};

/*
Given the head of a Singly LinkedList, write a function to determine if the
LinkedList has a cycle in it or not

T: O(N) where N is number of nodes
S: O(1)
*/

bool HasCycle(ListNode *head) {
	if (head == 0)
		return false;
	ListNode *slowPtr = head;
	ListNode *fastPtr = head;

	do {
		slowPtr = slowPtr->next;
		fastPtr = fastPtr->next;
		if (fastPtr) {
			fastPtr = fastPtr->next;
		}
		if (slowPtr == fastPtr && slowPtr != 0) {
			return true;
		}
	} while (fastPtr != 0);
	return false;
}

void HasCycle() {
	ListNode *head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = new ListNode(5);
	head->next->next->next->next->next = new ListNode(6);
	cout << "LinkedList has cycle: " << HasCycle(head) << endl;

	head->next->next->next->next->next->next = head->next->next;
	cout << "LinkedList has cycle: " << HasCycle(head) << endl;

	head->next->next->next->next->next->next = head->next->next->next;
	cout << "LinkedList has cycle: " << HasCycle(head) << endl;
}

/*
Given the head of a LinkedList with a cycle, find the length of the cycle.
T(N) = O(N) where N is number of nodes
S(N) = O(1)
*/

int CalculateLength(ListNode *slowPtr) {
	ListNode *ptr = slowPtr;
	int count = 0;
	do {
		count++;
		ptr = ptr->next;
	} while (slowPtr != ptr);
	return count;
}

int CycleLength(ListNode *head) {
	if (head == 0)
		return 0;
	ListNode *slowPtr = head;
	ListNode *fastPtr = head;

	do {
		slowPtr = slowPtr->next;
		fastPtr = fastPtr->next;
		if (fastPtr) {
			fastPtr = fastPtr->next;
		}
		if (slowPtr == fastPtr && slowPtr != 0) {
			return CalculateLength(slowPtr);
		}
	} while (fastPtr != 0);
	return 0;
}

void CycleLength() {
	ListNode *head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = new ListNode(5);
	head->next->next->next->next->next = new ListNode(6);
	head->next->next->next->next->next->next = head->next->next;
	cout << "LinkedList cycle length: " << CycleLength(head) << endl;

	head->next->next->next->next->next->next = head->next->next->next;
	cout << "LinkedList cycle length: " << CycleLength(head) << endl;
}

/*
Given the head of a Singly LinkedList that contains a cycle, write a function to
find the starting node of the cycle. T(N) = O(N) where N is number of nodes in
the LL S(N) = O(1)
*/

ListNode *StartPointOfCycle(ListNode *head) {
	int cycleLen = CycleLength(head);
	if (cycleLen == 0)
		return nullptr;
	ListNode *pointer1 = head;
	ListNode *pointer2 = head;
	while (cycleLen > 0) {
		pointer1 = pointer1->next;
		cycleLen--;
	}
	while (pointer1 != pointer2) {
		pointer1 = pointer1->next;
		pointer2 = pointer2->next;
	}
	return pointer1;
}

void StartPointOfCycle() {
	ListNode *head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = new ListNode(5);
	head->next->next->next->next->next = new ListNode(6);

	head->next->next->next->next->next->next = head->next->next;
	cout << "LinkedList cycle start: " << StartPointOfCycle(head)->data << endl;

	head->next->next->next->next->next->next = head->next->next->next;
	cout << "LinkedList cycle start: " << StartPointOfCycle(head)->data << endl;

	head->next->next->next->next->next->next = head;
	cout << "LinkedList cycle start: " << StartPointOfCycle(head)->data << endl;
}

/*
Any number will be called a happy number if, after repeatedly replacing  with a
number equal to the sum of the square of all of its digits, leads us to number
‘1’. All other (not-happy) numbers will never reach ‘1’. Instead, they will be
stuck in a cycle of numbers which does not include ‘1’. T(N) = O(logN);
difficult to determine though S(N) = O(1)
*/

int CalculateSquareSum(int num) {
	int sum = 0;
	while (num > 0) {
		//% returns the right most digit while / returns the left most digit;
		sum += (num % 10) * (num % 10);
		num = num / 10;
	}
	return sum;
}

int HappyNumber(int num) {
	int slow = num;
	int fast = num;

	do {
		slow = CalculateSquareSum(slow);
		fast = CalculateSquareSum(fast);
		fast = CalculateSquareSum(fast);
	} while (slow != fast);
	if (slow == 1) {
		return true;
	}
	return false;
}

void HappyNumber() {
	cout << HappyNumber(522) << endl;
	cout << HappyNumber(20) << endl;
	cout << HappyNumber(26) << endl;
	cout << HappyNumber(23) << endl;
}

/*
Given the head of a Singly LinkedList, write a method to return the middle node
of the LinkedList. T(N) = O(N); S(N) = O(1)
*/

ListNode *MiddleLinkedList(ListNode *head) {
	ListNode *slow = head;
	ListNode *fast = head;

	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

void MiddleLinkedList() {
	ListNode *head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = new ListNode(3);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = new ListNode(5);
	cout << "Middle Node: " << MiddleLinkedList(head)->data << endl;

	head->next->next->next->next->next = new ListNode(6);
	cout << "Middle Node: " << MiddleLinkedList(head)->data << endl;
}

ListNode *Reverse(ListNode *head) {
	ListNode *previous = 0;
	ListNode *current = head;
	ListNode *next = 0;
	while (current != 0) {
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}
	return previous;
}
/*
Given the head of a Singly LinkedList, write a method to check if the LinkedList
is a palindrome or not. T(N) = O(N)
https://discuss.educative.io/t/losing-original-linked-list/20724/4
*/

bool isPalindrome(ListNode *head) {
	if (head == 0 || head->next == 0) {
		return true;
	}

	ListNode *middle = MiddleLinkedList(head);
	ListNode *reversedHead = Reverse(middle);
	ListNode *copyReverseHead = reversedHead;

	while (head != 0 && copyReverseHead != 0) {
		if (head->data != copyReverseHead->data) {
			Reverse(reversedHead);
			return false;
		}
		head = head->next;
		copyReverseHead = copyReverseHead->next;
	}
	Reverse(reversedHead);
	if (head == 0 || copyReverseHead == 0) {
		// 1->2->2-1
		return true;
	}
	return false;
}

void isPalindrome() {
	ListNode *head = new ListNode(2);
	head->next = new ListNode(4);
	head->next->next = new ListNode(6);
	head->next->next->next = new ListNode(4);
	head->next->next->next->next = new ListNode(2);
	cout << "Is palindrome: " << isPalindrome(head) << endl;

	head->next->next->next->next->next = new ListNode(2);
	cout << "Is palindrome: " << isPalindrome(head) << endl;
}

/*
Given the head of a Singly LinkedList, write a method to modify the LinkedList
such that the nodes from the second half of the LinkedList are inserted
alternately to the nodes from the first half in reverse order. So if the
LinkedList has nodes 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> null, your method should
return 1 -> 6 -> 2 -> 5 -> 3 -> 4 -> null.

T(N): O(N)
S(N): O(1)
*/

void RearrangeLinkedList(ListNode *head) {
	if (head == 0 || head->next == 0)
		return;
	ListNode *middle = MiddleLinkedList(head);
	ListNode *reversedHead = Reverse(middle);

	ListNode *leftPtr = head;
	ListNode *rightPtr = reversedHead;
	ListNode *temp = 0;
	while (leftPtr != 0 && rightPtr != 0) {
		temp = leftPtr->next;
		leftPtr->next = rightPtr;
		leftPtr = temp;

		temp = rightPtr->next;
		rightPtr->next = leftPtr;
		rightPtr = temp;
	}
	// when list will have even elements; then last node's next will be pointing
	// to itself;
	// 2->4->6->8->10->12 ==> 2->4->6->8<-10<-12
	//                                 |
	//                                null
	// Hence, this check is mandatory
	if (leftPtr != 0) {
		leftPtr->next = 0; // this will not needed happen when list has odd
						   // elements then leftPtr will be null
	}
}

void RearrangeLinkedList() {
	ListNode *head = new ListNode(2);
	head->next = new ListNode(4);
	head->next->next = new ListNode(6);
	head->next->next->next = new ListNode(8);
	head->next->next->next->next = new ListNode(10);
	head->next->next->next->next->next = new ListNode(12);
	// head->next->next->next->next->next->next = new ListNode(14);
	RearrangeLinkedList(head);
	while (head != nullptr) {
		cout << head->data << " ";
		head = head->next;
	}
	cout << endl;
}

/*
Write a method to determine if the array has a cycle. The cycle should have more
than one element and should follow one direction which means the cycle should
not contain both forward and backward movements. T(N) = O(N2); Note: did not
prepare O(1) solution S(N) = O(1)
*/
int FindNextIndex(const vector<int> &arr, bool isForward, int currentIndex) {
	bool direction = arr[currentIndex] >= 0;
	if (isForward != direction) {
		return -1; // change in direction, return -1
	}

	int nextIndex = (currentIndex + arr[currentIndex]) % (int)arr.size();
	if (nextIndex < 0)
		nextIndex += arr.size(); // wrap around for negative numbers

	// one element cycle, return -1
	if (nextIndex == currentIndex) {
		nextIndex = -1;
	}

	return nextIndex;
}

bool CycleInCircularArray(const vector<int> nums) {
	for (int i = 0; i < nums.size(); i++) {
		bool isForward = nums[i] >= 0;

		int slow = i;
		int fast = i;

		do {
			slow = FindNextIndex(nums, isForward, slow);
			fast = FindNextIndex(nums, isForward, fast);
			if (fast != -1) {
				fast = FindNextIndex(nums, isForward, fast);
			}
		} while (slow != -1 && fast != -1 && slow != fast);

		if (slow == fast && slow != -1) {
			return true;
		}
	}
	return false;
}

void CycleInCircularArray() {
	cout << "Cycle in circular array: " << endl;
	cout << CycleInCircularArray(vector<int>{1, 2, -1, 2, 2}) << endl;
	cout << CycleInCircularArray(vector<int>{2, 2, -1, 2}) << endl;
	cout << CycleInCircularArray(vector<int>{2, 1, -1, -2}) << endl;
}

int main() {
	// cycle related
	HasCycle();
	CycleLength();
	StartPointOfCycle();
	HappyNumber();
  CycleInCircularArray();

	// mid point related
	MiddleLinkedList();
	isPalindrome();
	RearrangeLinkedList();

	return 0;
}
