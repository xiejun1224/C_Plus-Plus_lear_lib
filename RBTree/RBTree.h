#pragma once
#include<iostream>
using namespace std;

enum Color
{
	RED,
	BLACK
};
template<class k,class v>
struct RBTreeNode
{
	pair<k, v> _kv;
	RBTreeNode<k, v>* _left;
	RBTreeNode<k, v>* _right;
	RBTreeNode<k, v>* _parent;
	Color _col;

	RBTreeNode(const pair<k, v>& kv)
		:_kv(kv), _left(nullptr), _right(nullptr), _parent(nullptr), _col(RED)
	{ }
};

template<class k,class v>
class RBTree
{
public:
	using Node = RBTreeNode<k,v>;
	RBTree& operator=(RBTree t)
	{
		swap(_root, t._root);
		return *this;
	}
	RBTree(const RBTree& t)
	{
		_root = _Copy(t._root);
	}
	~RBTree()
	{
		_Destroy(_root);
		_root = nullptr;
	}
	RBTree()
		:_root(nullptr)
	{
	}
	Node* GetRoot() { return _root; }
	bool insert(const pair<k, v>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		//注意这里要先查找cur为空的节点在new新的节点否则万一有相同的k直接返回false但空间已经new了造成了内存泄漏
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}
		Node* newnode = new Node(kv);
		if (newnode->_kv.first < parent->_kv.first)
		{
			parent->_left = newnode;
		}
		else
		{
			parent->_right = newnode;
		}
		newnode->_parent = parent;
		
		Node* uncle = nullptr;
		cur = newnode;

		while (parent&&parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				uncle = grandfather->_right;
			}
			else
			{
				uncle = grandfather->_left;
			}
			if (uncle && uncle->_col == RED)
			{
				parent->_col = uncle->_col = BLACK;
				grandfather->_col = RED;
				cur = grandfather;
				parent = cur->_parent;
			}
			else
			{
				if (grandfather->_left == parent)
				{
					if (cur == parent->_left)
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						RotateLR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
				}
				else
				{
					if (cur == parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						RotateRL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}

				}
				break;
			}
		}
		_root->_col = BLACK;
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
	}
private:
	void _InOrder(const Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	Node* _Copy(const Node* root)
	{
		if (root == nullptr)
			return nullptr;
		Node* newroot = new Node(root->_kv);
		newroot->_col = root->_col;
		newroot->_left = _Copy(root->_left);
		newroot->_right = _Copy(root->_right);
		if (newroot->_left)
			newroot->_left->_parent = newroot;
		if (newroot->_right)
			newroot->_right->_parent = newroot;
		
		return newroot;		
	}

	void _Destroy(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		subL->_right = parent;
		if (subLR)
			subLR->_parent = parent;
		Node* pParent = parent->_parent;
		if (pParent == nullptr)
		{
			_root = subL;
			subL->_parent = nullptr;
			parent->_parent = subL;
		}
		else
		{
			if (parent == pParent->_left)
			{
				pParent->_left = subL;
			}
			else
			{
				pParent->_right = subL;
			}
			subL->_parent = pParent;
			parent->_parent = subL;
		}
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		subR->_left = parent;
		if (subRL)
			subRL->_parent = parent;
		Node* pParent = parent->_parent;
		if (pParent == nullptr)
		{
			_root = subR;
			subR->_parent = nullptr;
			parent->_parent = subR;
		}
		else
		{
			if (pParent->_left == parent)
			{
				pParent->_left = subR;
			}
			else
			{
				pParent->_right = subR;
			}
			subR->_parent = pParent;
			parent->_parent = subR;
		}
	}

	void RotateLR(Node* parent)
	{
		RotateL(parent->_left);
		RotateR(parent);
	}

	void RotateRL(Node* parent)
	{
		RotateR(parent->_right);
		RotateL(parent);
	}
private:
	Node* _root;
};
