#include "Tridy.h"
#include <iostream>

// -----
// NODE
// -----

Node::Node() : 
	data(0),
	left(nullptr),
	right(nullptr)
{
}

Node::Node(int _data) : 
	data(_data),
	left(nullptr),
	right(nullptr)
{
}

int Node::GetData() const { return data; }

void Node::SetData(int _data) {
	data = _data;
}

// -----
// BINARY TREE
// -----

BinaryTree::BinaryTree() :
	root(nullptr)
{
}

void BinaryTree::Insert(int _data) {
	if (!root)
		root = new Node(_data);
	else
		Insert(root, _data);

}

void BinaryTree::Insert(Node* _node, int _data) {
	if (_node) {
		if (_data < _node->data) {
			if (!_node->left)
				_node->left = new Node(_data);
			else
				Insert(_node->left, _data);
		} else if (_data > _node->data) {
			if (!_node->right)
				_node->right = new Node(_data);
			else
				Insert(_node->right, _data);
		} else {
			std::cout << "This number is already included: " << _data << std::endl;
		}
	} else {
		std::cout << "This should not be reached! This is a private method accessed via the public one, which takes care about this." << std::endl;
		exit(1);
	}
}

bool BinaryTree::Search(int _data) { return Search(root, _data); }

bool BinaryTree::Search(Node* node, int _data) {
	if (!node) return false;
	if (_data < node->data)
		return Search(node->left, _data);
	else if (_data > node->data)
		return Search(node->right, _data);
	else
		return true;
}

bool BinaryTree::Contains(int _data) {
	Node* node = root;
	while (node != nullptr && node->data != _data) {
		if (_data < node->data)
			node = node->left;
		else
			node = node->right;
	}
	return node;
}

void BinaryTree::Delete(int _data) {
	Delete(root, _data);
}

void BinaryTree::Delete(Node* &node, int _data) {
	if (!node)
		return;
	else if (_data < node->data)
		Delete(node->left, _data);
	else if (_data > node->data)
		Delete(node->right, _data);
	else { // We found it
	       if (!node->left)
		       node = node->right;
	       else if (!node->right)
		       node = node->left;
	       else {
		       Node* t = FindMin(node->left);
		       t->left = node->left;
		       t->right = node->right;
		       node = t;
	       }
	}
}

Node* BinaryTree::FindMin(Node* &node) {
	if (node->right)
		return FindMin(node->right);
	else {
		Node* result = node;
		node = node->left;
		return result;
	}
}

void BinaryTree::Print() {
	std::cout << "==========" << std::endl;
	Print(root, 0);
	std::cout << "==========" << std::endl;
}

void BinaryTree::Print(Node* node, int lvl) {
	if (node) {
		lvl++;
		//Print(node->left, lvl);
		Print(node->right, lvl);
		for (int i = 0; i < lvl; i++)
			std::cout << "---";
		std::cout << node->data << std::endl;
		//Print(node->right, lvl);
		Print(node->left, lvl);
	}
}
