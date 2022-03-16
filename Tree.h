#pragma once
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
        bool mIsDead = false;

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
    TreeNode* PrivateFind(const T& tWhat)
    {
        if (mHead == nullptr)
            return nullptr;

        TreeNode* tWalker = mHead;
        while (tWalker != nullptr) 
        {
            if (tWalker->mData == tWhat) 
            {
                return tWalker;
            }
            else if (tWalker->mData > tWhat) 
            {
                if (tWalker->mLeft == nullptr) 
                {
                    return tWalker;
                }
                else 
                {
                    tWalker = tWalker->mLeft;
                }
            }
            else 
            {
                if (tWalker->mRight == nullptr) 
                {
                    return tWalker;
                }
                else 
                {
                    tWalker = tWalker->mRight;
                }
            }
        }
        return tWalker;
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

        TreeNode* tWalker = PrivateFind(tWhat);
        if (tWalker->mData == tWhat)
        {
            tWalker->mIsDead = false;  // Might already be false.Don't care.
        }
        else if (tWalker->mData > tWhat) 
        {
            tWalker->mLeft = new TreeNode(tWhat);
        }
        else 
        {
            tWalker->mRight = new TreeNode(tWhat);
        }
    }
    

    void Remove(T tWhat)
    {
        if (mHead == nullptr) 
            return;

        TreeNode* tWalker = PrivateFind(tWhat);
        if (tWalker->mData == tWhat)
        {
            tWalker->mIsDead = true;
        }
    }
    

    bool Contains(T tWhat)
    {
        if (mHead == nullptr) 
            return false;

        TreeNode* tWalker = PrivateFind(tWhat);
        if (tWalker->mData == tWhat)
            return true;
        else
            return false;
    }


    void Dump(std::list<T>* tLeftToRight)
    {
        DumpTree(tLeftToRight, mHead);
    }
};
