#include"BSTree.h"
int main()
{
	BSTree<int> bt;
	int arr[]={6,2,4,9,1,3,8,7,0,5};
	for(auto& e:arr)
	{
		bt.Insert(e);
	}
	bt.PrintTree();
	bt.Find(5);
	bt.Find(10);
	bt.Erase(4);
	bt.PrintTree();
	BSTree<int>bt1=bt;
	bt1.PrintTree();
	bt1=bt;
	return 0;
}
