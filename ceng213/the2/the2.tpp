#pragma once

#include "LTree.tpp"
#include <iostream>
// *** You can add additional headers/functions/variables as necessary. ***

// *** Implement the functions below. ***
template<typename T>
void LTree<T>::popBack()
{
    if(mRoot == nullptr) return;
    LTree<T>::Node *nodeToPopBack = mTail;
    if(nodeToPopBack->mPrev != nullptr) nodeToPopBack->mPrev->mNext = nullptr;
    if(nodeToPopBack->mParent != nullptr){
        if(nodeToPopBack->mParent->mRight == nodeToPopBack){
            nodeToPopBack->mParent->mRight = nullptr;
        } else {
            nodeToPopBack->mParent->mLeft = nullptr;
        }
    }
    mTail = nodeToPopBack->mPrev;
    if(mRoot == nodeToPopBack) mRoot = nullptr;
    delete nodeToPopBack;
}







template<typename T>
typename LTree<T>::Node* LTree<T>::pushBack(const T& value) {
    LTree<T>::Node* newNode = new Node(value);
    if (mRoot == nullptr) {
        mRoot = mTail = newNode;
    } else { // non-empty tree
        Node* current = mTail;
        while (current->mParent != nullptr && current->mParent->mRight == current) {
            current = current->mParent;
        }
        if (current->mParent != nullptr) {
            if (current->mParent->mRight != nullptr) {
                current = current->mParent->mRight;
                while (current != nullptr && current->mLeft != nullptr) {
                    current = current->mLeft;
                }
            } else {
                current = current->mParent;
            }
        } else {
            while (current->mLeft != nullptr) {
                current = current->mLeft;
            }
            if (current->mRight != nullptr) {
                while (current->mRight != nullptr) {
                    current = current->mRight;
                }
            }
        }
        newNode->mParent = current;
        if (current->mLeft == nullptr) {
            current->mLeft = newNode;
        } else {
            current->mRight = newNode;
        }
        newNode->mPrev = mTail;
        mTail->mNext = newNode;
        mTail = newNode;
    }
    return newNode;
}

template<typename T>
void LTree<T>::exchange(LTree<T>::Node* a, LTree<T>::Node* b) {
    if (a == b)
        return;

    if (a->mParent == b) {
        a->mParent = a;
    } else if (b->mParent == a) {
        b->mParent = b;
    }

    std::swap(a->mLeft, b->mLeft);
    std::swap(a->mParent, b->mParent);
    std::swap(a->mRight, b->mRight);

    if (a->mLeft)
        a->mLeft->mParent = a;
    if (a->mRight)
        a->mRight->mParent = a;
    if (b->mLeft)
        b->mLeft->mParent = b;
    if (b->mRight)
        b->mRight->mParent = b;

    if (a->mParent) {
        if (a->mParent->mLeft == b)
            a->mParent->mLeft = a;
        else if (a->mParent->mRight == b)
            a->mParent->mRight = a;
    }
    if (b->mParent) {
        if (b->mParent->mLeft == a)
            b->mParent->mLeft = b;
        else if (b->mParent->mRight == a)
            b->mParent->mRight = b;
    }

    if (mRoot == a)
        mRoot = b;
    else if (mRoot == b)
        mRoot = a;

    if (mTail == a)
        mTail = b;
    else if (mTail == b)
        mTail = a;

    if (a->mPrev == b) {
        a->mPrev = a;
    } else if (b->mPrev == a) {
        b->mPrev = b;
    }

    if (a->mNext == b) {
        a->mNext = a;
    } else if (b->mNext == a) {
        b->mNext = b;
    }

    std::swap(a->mNext, b->mNext);
    std::swap(a->mPrev, b->mPrev);

    if (a->mPrev)
        a->mPrev->mNext = a;
    if (a->mNext)
        a->mNext->mPrev = a;
    if (b->mPrev)
        b->mPrev->mNext = b;
    if (b->mNext)
        b->mNext->mPrev = b;
}

template <typename T>
void LTree<T>::split(LTree<T>** outLeft, LTree<T>** outRight) {
    if (mRoot == nullptr) {
        *outLeft = nullptr;
        *outRight = nullptr;
        return;
    }

    *outLeft = new LTree<T>();
    *outRight = new LTree<T>();

    (*outLeft)->mRoot = mRoot->mLeft;
    (*outRight)->mRoot = mRoot->mRight;


    mRoot->mLeft = nullptr;
    mRoot->mRight = nullptr;
    mTail = mRoot;

    if ((*outLeft)->mRoot != nullptr) {
        (*outLeft)->mRoot->mParent = nullptr;
        (*outLeft)->mRoot->mPrev = nullptr;
        LTree<T>::Node* currentNode = (*outLeft)->mRoot;

        currentNode->mPrev = nullptr;
        while (currentNode->mNext != nullptr) {
            currentNode->mNext->mPrev = currentNode;
            currentNode = currentNode->mNext;
        }
        (*outLeft)->mTail = (currentNode == mRoot) ? currentNode->mPrev : currentNode;
    }

    if ((*outRight)->mRoot != nullptr) {
        (*outRight)->mRoot->mParent = nullptr;
        (*outRight)->mRoot->mPrev = nullptr;

        LTree<T>::Node* currentNode = (*outRight)->mRoot;
        currentNode->mPrev = nullptr;

        while (currentNode->mNext != nullptr) {
            currentNode->mNext->mPrev = currentNode;
            currentNode = currentNode->mNext;
        }
        (*outRight)->mTail = (currentNode == mRoot) ? currentNode->mPrev : currentNode;
    }


    mRoot->mPrev = nullptr;
    mRoot->mNext = nullptr;
}
