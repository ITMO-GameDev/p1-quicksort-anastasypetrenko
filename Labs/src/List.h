#pragma once

#include <cstdlib>
#include <cassert>

template<typename T>
class List {
public:
    List();
    ~List();

    List& operator=(const List& other) = delete;

    void insert_head(const T& value);
    void insert_tail(const T& value);

    struct Node {
        Node* prev;
        Node* next;
        T val;

        Node(Node* prev, Node* next, T val);
    };

    Node* insert(Node* node, const T& value);
    void remove(Node* node);

    void remove_head();
    void remove_tail();

    const T& head() const;
    const T& tail() const;

    int size() const;
    bool empty() const;

    void clear();

    class Iterator {
    public:
        friend class List;
        const T& get() const;
        void set(const T& value);
        void insert(const T& value);
        void remove();
        void next();
        void prev();
        bool hasNext() const;
        bool hasPrev() const;

    private:
        explicit Iterator(List<T>* owner, Node* node);
        Node* mNode;
        List<T>* mOwner;
    };

    class ConstIterator {
    public:
        friend class List;

        const T& get() const;
        void next();
        void prev();
        bool hasNext() const;
        bool hasPrev() const;

    private:
        explicit ConstIterator(const List<T>* owner, const Node* node);
        const Node* mNode;
        const List<T>* mOwner;
    };

    Iterator iterator();
    const ConstIterator iterator() const;

private:
    Node* mHead;
    Node* mTail;
    size_t mSize;
};

template<typename T>
const T &List<T>::ConstIterator::get() const {
    return mNode->val;
}

template<typename T>
void List<T>::ConstIterator::next() {
    mNode = mNode->next;
}

template<typename T>
void List<T>::ConstIterator::prev() {
    mNode = mNode->prev;
}

template<typename T>
bool List<T>::ConstIterator::hasNext() const {
    return mNode;
}

template<typename T>
bool List<T>::ConstIterator::hasPrev() const {
    return mNode;
}

template<typename T>
List<T>::ConstIterator::ConstIterator(const List<T> *owner, const List::Node *node) : mOwner(owner), mNode(node) {

}

template<typename T>
const T &List<T>::Iterator::get() const {
    return mNode->val;
}

template<typename T>
void List<T>::Iterator::set(const T &value) {
    mNode->val = value;
}

template<typename T>
void List<T>::Iterator::insert(const T &value) {
    mNode = mOwner->insert(mNode, value);
}

template<typename T>
void List<T>::Iterator::remove() {
    Node* nextNode = mNode->next;
    mOwner->remove(mNode);
    mNode = nextNode;
}

template<typename T>
void List<T>::Iterator::next() {
    mNode = mNode->next;
}

template<typename T>
void List<T>::Iterator::prev() {
    mNode = mNode->prev;
}

template<typename T>
bool List<T>::Iterator::hasNext() const {
    return mNode;
}

template<typename T>
bool List<T>::Iterator::hasPrev() const {
    return mNode;
}

template<typename T>
List<T>::Iterator::Iterator(List<T> *owner, List::Node *node) : mOwner(owner), mNode(node) {

}

template<typename T>
List<T>::Node::Node(List::Node *prev, List::Node *next, T val) : prev(prev), next(next), val(val) {

}

template<typename T>
List<T>::List() : mHead(nullptr), mTail(nullptr), mSize(0) {

}

template<typename T>
List<T>::~List() {
    clear();
}

template<typename T>
void List<T>::insert_head(const T &value) {
    Node* node = new Node(nullptr, mHead, value);

    if (mHead) {
        mHead->prev = node;
        mHead = node;
    } else {
        assert(!mTail);
        assert(empty());
        mHead = node;
        mTail = node;
    }

    assert(!mHead->prev);

    ++mSize;
}

template<typename T>
void List<T>::insert_tail(const T &value) {
    Node* node = new Node(mTail, nullptr, value);

    if (mTail) {
        mTail->next = node;
        mTail = node;
    } else {
        assert(!mHead);
        assert(empty());
        mHead = node;
        mTail = node;
    }

    assert(!mTail->next);

    ++mSize;
}


template<typename T>
typename List<T>::Node* List<T>::insert(Node *node, const T& value) {
    bool isHead = node == mHead;
    if (isHead) {
        insert_head(value);
        return mHead;
    } else {
        Node* prevNode = node->prev;
        Node* insertedNode = new Node(prevNode, node, value);
        prevNode->next = insertedNode;
        node->prev = insertedNode;

        ++mSize;
        return insertedNode;
    }
}

template<typename T>
void List<T>::remove(Node *node) {
    bool isHead = node == mHead;
    bool isTail = node == mTail;
    if (isHead && isTail) {
        remove_head();
    } else if (isHead) {
        remove_head();
    } else if (isTail) {
        remove_tail();
    } else {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        assert(prevNode);
        assert(nextNode);
        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete node;
        --mSize;
    }
}

template<typename T>
void List<T>::remove_head() {
    Node* nextHead = mHead->next;
    delete mHead;
    mHead = nextHead;
    if (mHead) {
        mHead->prev = nullptr;
    } else {
        assert(mSize == 1);
        mTail = nullptr;
    }

    --mSize;
}

template<typename T>
void List<T>::remove_tail() {
    Node* nextTail = mTail->prev;
    delete mTail;
    mTail = nextTail;
    if (mTail) {
        mTail->next = nullptr;
    } else {
        assert(mSize == 1);
        mHead = nullptr;
    }

    --mSize;
}

template<typename T>
const T &List<T>::head() const {
    return mHead->val;
}

template<typename T>
const T &List<T>::tail() const {
    return mTail->val;
}

template<typename T>
int List<T>::size() const {
    return mSize;
}

template<typename T>
bool List<T>::empty() const {
    return mSize == 0;
}

template<typename T>
void List<T>::clear() {
    for (Node* deleteIter = mHead; deleteIter;) {
        Node* next = deleteIter->next;
        delete deleteIter;
        deleteIter = next;
    }
}

template<typename T>
typename List<T>::Iterator List<T>::iterator() {
    return List::Iterator(this, mHead);
}

template<typename T>
const typename List<T>::ConstIterator List<T>::iterator() const {
    return List::ConstIterator(this, mHead);
}
