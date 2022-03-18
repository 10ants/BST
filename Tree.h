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

    // This tree wants a copy of that node and all beneath it

    void CopyTree(TreeNode* tNode)
    {
        if (tNode != nullptr)
        {
            Add(tNode->mData); // Add data from the sent Node
            CopyTree(tNode->mLeft); // recurse to the left child node
            CopyTree(tNode->mRight);// recurse to the right child node
        }
    }
    // Pack this list with the data from that node down, small to large

    void DumpTree(std::list<T>* tLeftToRight, TreeNode* tNode)
    {
        if (tNode != nullptr)
        {
            DumpTree(tLeftToRight, tNode->mLeft); // recurse left walker
            tLeftToRight->push_back(tNode->mData); // push back the data retrevied
            DumpTree(tLeftToRight, tNode->mRight); // recuse right walker
        }
    }
    // Delete that node and everything under it.

    void DeleteTree(TreeNode* tNode)
    {
        if (tNode != nullptr)
        {
            DeleteTree(tNode->mLeft); // recurse left child
            DeleteTree(tNode->mRight); // recurse right child
            delete tNode; // Delete node
        }
    }

    // Look at what Add/Contain/Remove all do as step one.  THey each have
    // different unique things to do as step two, but first they all want
    // the same node pointer to play with.
    // This is a single path, so it is a loop.

    TreeNode* PrivateFind(const T& tWhat) // Finding node that is being requested
    {

        if (mHead == nullptr) 
            return nullptr;

        TreeNode* tWalker = mHead;
        while (true) {
            if (tWalker->mData == tWhat) // if head is tWhat
                return tWalker;
            else if (tWalker->mData > tWhat) 
            {
                if (tWalker->mLeft == nullptr) //If tWalker is bigger than tWhat and nothing is smaller
                    return tWalker;
                else
                    tWalker = tWalker->mLeft; 
            }
            else
            {
                if (tWalker->mRight == nullptr) // If tWalker is smaler than tWhat and there is nothing bigger
                    return tWalker;
                else
                    tWalker = tWalker->mRight;
            }
        }
    }

   public:
    Tree()
    {
        mHead = nullptr;
    }

    Tree(const Tree& other) : Tree()
    {
        CopyTree(other.mHead);
    }

    Tree& operator= (const Tree& other)
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
        if (mHead == nullptr)
        {
            mHead = new TreeNode(tWhat);
            return;
        }

        TreeNode* tWalker = PrivateFind(tWhat); //Checking if tWhat is alreadyt in the tree 

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
        if (mHead == nullptr) //If the tree is empty 
        {
            return;
        }

        TreeNode* tWalker = PrivateFind(tWhat);

        if (tWalker->mData == tWhat
            && tWalker->mRight == nullptr
            && tWalker->mLeft == nullptr) //If tWalker has no children
            delete tWalker;

        if (tWalker->mData == tWhat
            && tWalker->mRight != nullptr
            && tWalker->mLeft == nullptr) //If tWalker has one child on the right 
        {
            if (tWalker == mHead)
            {
                mHead = tWalker->mRight;
                mHead->mLeft = nullptr;
                mHead->mRight = nullptr;
            }
            else if (tWalker > tWalker->mParent)
            {
                tWalker->mParent->mRight = tWalker->mRight;
                delete tWalker;
            }
            else
            {
                tWalker->mParent->mLeft = tWalker->mRight;
                delete tWalker;
            }
        }

        else if (tWalker->mData == tWhat
            && tWalker->mRight == nullptr
            && tWalker->mLeft != nullptr)//If tWalker has one child on the left
        {
            if (tWalker == mHead)
            {
                mHead = tWalker->mLeft;
                mHead->mLeft = nullptr;
                mHead->mRight = nullptr;
            }
            else if (tWalker > tWalker->mParent)
            {
                tWalker->mParent->mRight = tWalker->mLeft;
                delete tWalker;
            }
            else
            {
                tWalker->mParent->mLeft = tWalker->mLeft;
                delete tWalker;
            }
        }

        else //If tWalker has two children
        {
            while (tWalker->mRight->mLeft)
            {
                tWalker = tWalker->mRight->mLeft;
                delete tWalker->mRight->mLeft;
            }

            //Don't delete
            //Find the next highest, 1 right then as far left
            //Swap data
            //Delete their old node
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
