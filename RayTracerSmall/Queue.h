#pragma once
#include "SafeThreadQueue.h"


template<typename T>
//use shortcut to track work
//Remember to delete the Node pointers
class Queue
{

public:
	struct Node
	{
		T data;
		Node* pNext;
		Node(T nodeData) : data(std::move(nodeData)) {}
	};

	Node* head;
	Node* pTail;

	Queue() : pTail(nullptr) {}
	Queue(const Queue& other) = delete;
	Queue& operator=(const Queue& other) = delete;

	std::shared_ptr<T> tryPop()
	{
		if (!head)
		{
			return std::shared_ptr<T>();
		}

		std::shared_ptr<T> const res(
			std::make_shared<T>(std::move(head->data)));
		Node* const oldHead = std::move(head);
		head = std::move(oldHead->pNext);
		if (!head)
		{
			pTail = nullptr;
		}

		return res;
	}

	void push(T newValue)
	{
		//overload new functions so it malloc 
		std::unique_ptr<Node> pNode(std::move(newValue)));
		Node* const newTail = pNode.get();
		if()
	}

private:
};
//https://learning.oreilly.com/library/view/c-concurrency-in/9781617294693/kindle_split_016.html#ch06lev1sec2