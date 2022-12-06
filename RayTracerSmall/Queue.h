#pragma once
#include "SafeThreadQueue.h"


template<typename T>

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
			std::make_shared<T>(std::move()));
		std::unique_ptr<Node> const oldHead = std::move(head);
		head = std::move( )
	}

private:
};
