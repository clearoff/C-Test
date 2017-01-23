//面试题：反转链表

#include <iostream>
using namespace std;


struct ListNode 
{
	int val;
	struct ListNode *next;
	ListNode(int x)
		:val(x), next(NULL)
	{};
};


class Solution 
{
public:
	//非递归
	static ListNode*  ReverseList(ListNode* pHead) 
	{
		if (pHead == NULL || pHead->next == NULL)
			return pHead;

		ListNode* pre = NULL;
		ListNode* next = NULL;

		while (pHead)
		{
			next = pHead->next;
			pHead->next = pre;
			pre = pHead;
			pHead = next;
		}
		return pre;
	}

	//递归版本
	static ListNode* ReverListR(ListNode* pHead)
	{
		if (pHead == NULL || pHead->next == NULL)
			return pHead;

		//找到链表中的最后一个不为NULL的节点
		ListNode* newHead = ReverListR(pHead->next);

		pHead->next->next = pHead;        //让当前节点的下一个节点的next指针指向当前节点
		pHead->next = NULL;               //让当前节点的next指针指向NULL

		return newHead;
	}

	static void PrintList(ListNode* pHead)
	{
		if (pHead == NULL)
			return;

		while (pHead)
		{
			cout << pHead->val << "->";
			pHead = pHead->next;
		}
		cout << "NULL"<<endl;
	}
};


void testNR()
{
	ListNode l1(1);
	ListNode l2(2);
	ListNode l3(3);
	ListNode l4(4);
	ListNode l5(5);
	ListNode l6(6);
	l1.next = &l2;
	l2.next = &l3;
	l3.next = &l4;
	l4.next = &l5;
	l5.next = &l6;
	Solution::PrintList(&l1);
	ListNode* newHead=Solution::ReverseList(&l1);
	Solution::PrintList(newHead);
}

void testR()
{
	ListNode l1(1);
	ListNode l2(2);
	ListNode l3(3);
	ListNode l4(4);
	ListNode l5(5);
	ListNode l6(6);
	l1.next = &l2;
	l2.next = &l3;
	l3.next = &l4;
	l4.next = &l5;
	l5.next = &l6;
	Solution::PrintList(&l1);
	ListNode* newHead = Solution::ReverListR(&l1);
	Solution::PrintList(newHead);
}

int main()
{
	//testNR();
	testR();
	return 0;
}