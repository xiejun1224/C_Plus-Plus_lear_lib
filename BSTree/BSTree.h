#include<iostream>
using namespace std;
template<class k>
struct BSNode
{
	BSNode(const k& key)
		:_key(key),_left(nullptr),_right(nullptr)
	{}

		k _key;
		BSNode*_left;
		BSNode*_right;
};

template<class k>
class BSTree
{
public:
	using Node=BSNode<k>;
	BSTree& operator=(BSTree bt)
	{
		swap(_root,bt._root);
		return *this;
	}
	~BSTree()
	{
		Destroy(_root);
	}
	BSTree()
		:_root(nullptr)
	{
	}
	BSTree(const BSTree& bt)
	{
		_root=Copy(bt._root);
	}
	bool Insert(const k& key)
	{
		if(_root==nullptr)
		{
			_root=new Node(key);
			return true;
		}
		Node*cur=_root;
		Node*parent=cur;
		while(cur)
		{
			if(cur->_key>key)
			{
				parent=cur;
				cur=cur->_left;
			}
			else if(cur->_key<key)
			{
				parent=cur;
				cur=cur->_right;
			}
			else
				return false;
		}
	if(parent->_key>key)
	{
		parent->_left=new Node(key);
		return true;
	}
	else
	{
		parent->_right=new Node(key);
		return true;
	}

	}

	void PrintTree()
	{
		_InOrder(_root);
		cout<<endl;
	}


	bool Find(const k& key)
	{
		Node*cur=_root;
		while(cur)
		{
			if(cur->_key>key)
			{
				cur=cur->_left;
			}
			else if(cur->_key<key)
			{
				cur=cur->_right;
			}
			else
			{
				cout<<"找到了"<<endl;
				return true;
			}
		}
		cout<<"没找到"<<endl;
		return false;
	}

	bool Erase(const k& key)
	{
		Node*cur=_root;
		Node*parent=nullptr;
		while(cur)
		{
			if(cur->_key>key)
			{
				parent=cur;
				cur=cur->_left;
			}
			else if(cur->_key<key)
			{
				parent=cur;
				cur=cur->_right;
			}
			else
			{
				if(cur->_left==nullptr)
				{
					if(parent==nullptr)
					{
						_root=cur->_right;
					}
					else if(parent->_left==cur)
					{
						parent->_left=cur->_right;
					}
					else
					{
						parent->_right=cur->_right;
					}
					delete cur;
					cout<<"true"<<endl;
					return true;
				}
				else if(cur->_right==nullptr)
				{
					if(parent==nullptr)
					{
						_root=cur->_left;
					}
					else if(parent->_left==cur)
					{
						parent->_left=cur->_left;
					}
					else
					{
						parent->_right=cur->_left;
					}
					delete cur;
					cout<<"true"<<endl;
					return true;
				}
				else
				{
					Node*lm=cur->_left;
					Node*lm_parent=cur;
					while(lm->_right)
					{
						lm_parent=lm;
						lm=lm->_right;
					}
					cur->_key=lm->_key;
					
					
			
						
			
					
					
					
						if(lm_parent==cur)
						{
							cur->_left=lm->_left;
						}
						else
						{
							lm_parent->_right=lm->_left;
						}
							delete lm;
							cout<<"true"<<endl;
							return true;
					

				}


			}

		}
		cout<<"false"<<endl;
		return false;
	}
	private:
	Node* Copy(const Node* root)
	{
		if(root==nullptr)
			return nullptr;
		Node*newnode=new Node(root->_key);
		newnode->_left=Copy(root->_left);
		newnode->_right=Copy(root->_right);
		return newnode;
	}
	void Destroy(Node*root)
	{
		if(root==nullptr)
			return;
		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}
		void _InOrder(Node*cur)
		{
			if(cur==nullptr)
				return;
			_InOrder(cur->_left);
			cout<<cur->_key<< " ";
			_InOrder(cur->_right);

		}
		Node*_root;
};



















