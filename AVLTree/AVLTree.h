#pragma once
#include<iostream>
#include<cassert>
#include<vector>
using namespace std;

template<class k,class v>
struct AVLTreeNode
{
	pair<k, v> _kv;
	AVLTreeNode<k,v>* _left;
	AVLTreeNode<k, v>* _right;
	AVLTreeNode<k, v>* _parent;
	int _bf;
	AVLTreeNode(const pair<k,v>& kv)
		:_kv(kv),_left(nullptr),_right(nullptr),_parent(nullptr),_bf(0)
	{ }
};

template<class k, class v>
class AVLTree
{
public:
	using Node = AVLTreeNode<k,v>;
	AVLTree()
		:_root(nullptr)
	{ }

	~AVLTree()
	{
		_Destroy(_root);
		_root = nullptr;
	}
	AVLTree(const AVLTree& t)
		:_root(_Copy(t._root))
	{
	}
	AVLTree& operator=(AVLTree t)
	{
		
		swap(_root, t._root);
		return *this;
	}

	bool IsBalance()
	{
		return _IsBalance(_root);
	}
	int Size()
	{
		return _Size(_root);
	}
	int Height()
	{
		
		return _Height(_root);
	}
	void Print()
	{
		_InOder(_root);
		cout << endl;
	}
	Node* find(const k& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_kv.first)
			{
				cur = cur->_left;
			}
			else if (key > cur->_kv.first)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}
	bool insert(const pair<k, v>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
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
		cur = new Node(kv);
		if (kv.first < parent->_kv.first)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;

		while (parent)
		{
			if (parent->_left == cur)
			{
				parent->_bf--;
			}
			else 
			{
				parent->_bf++;
			}

			if (parent->_bf == 0)
				break;
			if (parent->_bf == -1 || parent->_bf == 1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2)
			{
				//Ðý×ª
				if (parent->_bf == 2 && parent->_right->_bf == 1)
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && parent->_left->_bf == -1)
				{
					RotateR(parent);
				}
				else if (parent->_bf == 2 && parent->_right->_bf == -1)
				{
					RotateRL(parent);
				}
				else if (parent->_bf == -2 && parent->_left->_bf == 1)
				{
					RotateLR(parent);
				}
				break;

			}
			else
			{
				assert(false);
			}


		}
		return true;
	}
private:
	int _Size(Node*root)
	{
		if (root == nullptr)
			return 0;
		return _Size(root->_left) + _Size(root->_right) + 1;
	}
	int _Height(Node* root)
	{
		if (root == nullptr) return 0;
		return max(_Height(root->_left), _Height(root->_right)) + 1;
	}
	bool _IsBalance(Node* root)
	{
		if (root == nullptr) return true;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		if (rightHeight - leftHeight != root->_bf)
			return false;
		return abs(root->_bf) < 2 && _IsBalance(root->_left) && _IsBalance(root->_right);
	}
	Node* _Copy(const Node* t)
	{
		if (t == nullptr)
		{
			return nullptr;
		}
		Node* newnode = new Node(t->_kv);
		newnode->_bf = t->_bf;
		newnode->_left = _Copy(t->_left);
		newnode->_right = _Copy(t->_right);

		if (newnode->_left)
			newnode->_left->_parent = newnode;
		if (newnode->_right)
			newnode->_right->_parent = newnode;
		return newnode;
	}
	void _InOder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOder(root->_left);
		cout << "("<<root->_kv.first<<","<<root->_kv.second<<")" << " ";
		_InOder(root->_right);
	}
	void _Destroy(Node* root)
	{
		if (root == nullptr)
			return;
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
			if (pParent->_left == parent)
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
		parent->_bf = subL->_bf = 0;
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
		subR->_bf = parent->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;
		RotateL(parent->_left);
		RotateR(parent);
		if (bf == 0)
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			subL->_bf = 0;
			parent->_bf = 1;
			subLR->_bf = 0;
		}
		else if (bf == 1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
			subLR->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(subR);
		RotateL(parent);
		if (bf == 0)
		{
			subR->_bf = subRL->_bf = parent->_bf = 0;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
			subRL->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}
private:
	Node* _root=nullptr;
};
