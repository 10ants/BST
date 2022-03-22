#include <list>
#include <iostream> // For debugging.  Only main should have cout for real
template <typename T>
class Tree
{
	struct TreeNode
	{
		T mData;
		TreeNode* mLeft = nullptr;
		TreeNode* mRight = nullptr;
		TreeNode* mParent = nullptr;
		TreeNode()
		{
		}
		TreeNode(T tData) : TreeNode()
		{
			mData = tData;
		}
	};
	TreeNode* mHead;
	void CopyTree(TreeNode* tNode)
	{
		if (tNode != nullptr)
		{
			Add(tNode->mData); // Add data from the sent Node
			CopyTree(tNode->mLeft); // recurse to the left child node
			CopyTree(tNode->mRight);// recurse to the right child node
		}
	}

	void DumpTree(std::list<T>* tLeftToRight, TreeNode* tNode)
	{
		if (tNode != nullptr) 
		{ 	
			DumpTree(tLeftToRight, tNode->mLeft);
			tLeftToRight->push_back(tNode->mData);
			DumpTree(tLeftToRight, tNode->mRight);
		}
	}
		void DeleteTree(TreeNode * tNode) // Delete that node and everything under it.
		{
			if (tNode != nullptr)
			{
				DeleteTree(tNode->mLeft); // recurse left child
				DeleteTree(tNode->mRight); // recurse right child
				delete tNode; // Delete node
			}
		}

		TreeNode* PrivateFind(const T & tWhat) // Finding node that is being requested
		{
			if (mHead == nullptr) //If the tree is empty then don't do anything
				return nullptr;

			TreeNode* tWalker = mHead;
			while (true) {
				if (tWalker->mData == tWhat) //If current node is the node being looked for return it
					return tWalker;

				else if (tWalker->mData > tWhat) //If the data for the node being searched for is smaller than current node
				{
					if (tWalker->mLeft == nullptr)
						return tWalker;
					else
						tWalker = tWalker->mLeft; //Find the smaller node
				}
				else //If the data for the searched node is bigger than current 
				{
					if (tWalker->mRight == nullptr)
						return tWalker;
					else
						tWalker = tWalker->mRight; // Find the bigger node
				}
			}
		}

	public:
		Tree()
		{
			mHead = nullptr;
		}

		Tree(const Tree & other) : Tree()
		{
			CopyTree(other.mHead);
		}

		Tree& operator= (const Tree & other)
		{
			if (this == &other)
				return *this;
			DeleteTree(mHead);
			mHead = nullptr;
			CopyTree(other.mHead);

			return *this;
		}

		~Tree()
		{
			DeleteTree(mHead);
		}

		void Add(T tWhat)
		{
			if (mHead == nullptr) //If tree is empty, start tree with tWhat as head
			{
				mHead = new TreeNode(tWhat);
				return;
			}

			TreeNode* tWalker = PrivateFind(tWhat); //Checking if tWhat is already in the tree 

			if (tWalker->mData == tWhat) // if it is dont do anything
				return;
			if (tWalker->mData > tWhat) //If tWalker is bigger than tWhat then add tWhat to its left 
			{
				tWalker->mLeft = new TreeNode(tWhat);
				tWalker->mLeft->mParent = tWalker;
			}
			else //If tWalker is smaller than tWhat then add tWhat to its right
			{
				tWalker->mRight = new TreeNode(tWhat);
				tWalker->mRight->mParent = tWalker;
			}
		}

		void Remove(T tWhat) // Where you delete all nodes.
		{
	

			TreeNode* tWalker = PrivateFind(tWhat);
			if (tWalker->mRight == nullptr && tWalker->mLeft == nullptr) //If tWalker has no children
			{
				if (tWalker->mParent->mLeft == tWalker)
				{
					tWalker->mParent->mLeft = nullptr;
				}

				if (tWalker->mParent->mRight == tWalker)
				{
					tWalker->mParent->mRight = nullptr;
				}
				delete tWalker;
			}

			else if (tWalker->mRight != nullptr 
				&& tWalker->mLeft == nullptr) //If tWalker has one child on the right 
			{
				if (tWalker->mParent->mLeft == tWalker)
				{
					tWalker->mParent->mLeft = tWalker->mRight;
					tWalker->mRight->mParent = tWalker->mParent;
					delete tWalker;
				}

				else if (tWalker->mParent->mRight == tWalker)
				{
					tWalker->mParent->mRight = tWalker->mRight;
					tWalker->mRight->mParent = tWalker->mParent;
					delete tWalker;
				}
			}

			else if (tWalker->mRight == nullptr
				&& tWalker->mLeft != nullptr)//If tWalker has one child on the left
			{
				if (tWalker->mParent->mLeft == tWalker)
				{
					tWalker->mParent->mLeft = tWalker->mLeft;
					tWalker->mLeft->mParent = tWalker->mParent;
					delete tWalker;
				}

				else if (tWalker->mParent->mRight == tWalker)
				{
					tWalker->mParent->mRight = tWalker->mLeft;
					tWalker->mLeft->mParent = tWalker->mParent;
					delete tWalker;
				}
			}
			

			else //If tWalker has two children
			{	
				TreeNode* tSuccesor = tWalker->mRight; //Take on step right
				while (tSuccesor->mLeft) // Keep pushing the succesor left
				{
					tSuccesor = tSuccesor->mLeft;
				}

				T temp = tSuccesor->mData; //Moving the succesors data up the tree
				Remove(tSuccesor->mData);

				tWalker->mData = temp;
			}
		}

		bool Contains(T tWhat)
		{
			if (mHead == nullptr)
				return false;

			TreeNode* tWalker = PrivateFind(tWhat); //If you found tWhat then return true if not then dont.
			if (tWalker->mData == tWhat)
				return true;
			else
				return false;
		}

		void Dump(std::list<T>*tLeftToRight)
		{
			DumpTree(tLeftToRight, mHead);
		}
	
};
/*----------------------------------------
			 50
		 30      80
	   10      60  90
		 15   55     100
						 110
							 120
 -----------------------------------------*/
