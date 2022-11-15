#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2);

    // Add helper functions here
    void deleteHelper(Node<Key, Value>* node);
    int calculateHeightIfBalanced(Node<Key,Value>* root) const;
    static Node<Key, Value>* successor(Node<Key, Value>* node);

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return current_ != rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    // get the successor and then return reference
    current_ = successor(current_);
    return *this;
}

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* node)
{
    // First condition: the right element doesn't exist
    // The successor is the first node who is a left child of his parent
    // that parent is the successor
    if(!node->getRight()){
        Node<Key, Value>* parent = node->getParent();
        while(parent != NULL && node == parent->getRight()){
            node = parent;
            parent = node->getParent();
        }
        node = parent;
    }
    // Second condition: the right element exist
    // The successor is the left most node of the right subtree
    else{
        node = node->getRight();
        while(node->getLeft()){
            node = node->getLeft();
        }
    }
    return node;
}

/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
		// Special case if the tree if NULL
	  if(root_ == NULL){
			root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);;
      return;
		}
    // copy a root node to iterate all tree
		Node<Key, Value>* temp = root_;
    bool flag = true;
    // use loop to iterate
    while(flag){
        if(temp->getKey() < keyValuePair.first){
            if(temp->getRight() != NULL){
                temp = temp->getRight();
            }
            else{
                temp->setRight(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp));
                flag = false;
            }
        }
        else if(temp->getKey() > keyValuePair.first){
            if(temp->getLeft() != NULL){
                temp = temp->getLeft();
            }
            else{
                temp->setLeft(new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp));
                flag = false;
            }
        }
				else{
						temp->setValue(keyValuePair.second);
						flag = false;
				}
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    // check for special case the node is not in the tree
    if(internalFind(key) == NULL){
        return;
    }
    // then the node is in the tree and ready to remove
    // there are three options for node: 0,1 or 2 child 
    Node<Key, Value>* temp = internalFind(key);
		// Check whether the node is root node
		bool rootflag = false;
		if(temp->getParent() == NULL) rootflag = true;
    Node<Key, Value>* parent = temp->getParent();
    // first condition is 0 child
    if(temp->getLeft() == NULL && temp->getRight() == NULL){
				if(rootflag){
					clear();
					return;
				}
        // if temp is at left of parent node
        if(parent->getLeft() == temp) parent->setLeft(NULL);
        // else temp is at right of parent node
        else parent->setRight(NULL);
        delete temp;
    }
    // second condition is 1 child (at right)
    else if(temp->getLeft() == NULL){
				if(rootflag){
					root_ = temp->getRight();
					root_->setParent(NULL);
					delete temp;
					return;
				}
        // if temp is at left of parent node
        if(parent->getLeft() == temp){
            parent->setLeft(temp->getRight());
        }
        // else temp is at right of parent node
        else{
            parent->setRight(temp->getRight());
        }
        temp->getRight()->setParent(parent);
        delete temp;
    }
    // second condition is 1 child (at left)
    else if(temp->getRight() == NULL){
				if(rootflag){
					root_ = temp->getLeft();
					root_->setParent(NULL);
					delete temp;
					return;
				}
        // if temp is at left of parent node
        if(parent->getLeft() == temp){
            parent->setLeft(temp->getLeft());
        }
        // else temp is at right of parent node
        else{
            parent->setRight(temp->getLeft());
        }
        temp->getLeft()->setParent(parent);
        delete temp;
    }
    // third condition is 2 children
    else{
        Node<Key, Value>* pred = predecessor(temp);
        nodeSwap(pred, temp);
        parent = temp->getParent();
				// Then we go back to 0 or 1 child conditions
				// check whether change the address of root_
				if(rootflag) root_ = pred;
				// first condition is 0 child
        if(temp->getLeft() == NULL && temp->getRight() == NULL){
					// if temp is at left of parent node
					if(parent->getLeft() == temp) parent->setLeft(NULL);
					// else temp is at right of parent node
					else parent->setRight(NULL);
				}
				// second condition is 1 child which is at left
				else{
					// if temp is at left of parent node
					if(parent->getLeft() == temp) parent->setLeft(temp->getLeft());
					// else temp is at right of parent node
					else parent->setRight(temp->getLeft());
					temp->getLeft()->setParent(parent);
				}
        delete temp;
    }
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    // First condition: the left element doesn't exist
    // The predecessor is the first node who is a right child of his parent 
    // and parent is the predecessor
    if(!current->getLeft()){
        while(current->getParent() != NULL){
            Node<Key, Value>* parent = current->getParent();
            if(current == parent->getRight()){
                current = current->getParent();
                break;
            }
            current = current->getParent();
        }
    }
    // Second condition: the left element exist
    // The predecessor is the right most node of the left subtree
    else{
        current = current->getLeft();
        while(current->getRight()){
            current = current->getRight();
        }
    }
    return current;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    // special case: empty tree
    if(empty()) return;
    // delete nodes;
    deleteHelper(root_);
		root_ = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::deleteHelper(Node<Key,Value>* node)
{
    if(node == NULL) return;
    deleteHelper(node->getLeft());
    deleteHelper(node->getRight());
    delete node;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    // special case: root is NULL
    if(!root_) return NULL;
    Node<Key, Value>* temp = root_;
    while(temp->getLeft()){
        temp = temp->getLeft();
    }
    return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    // special case: root is NULL
    if(!root_) return NULL;
    // loop the whole tree to find the node
    // Runtime is O(h)
    Node<Key, Value>* temp = root_;
    while(temp){
        if(temp->getKey() < key){
            temp = temp->getRight();
        }
        else if(temp->getKey() > key){
            temp = temp->getLeft();
        }
        else if(temp->getKey() == key){
            return temp;
        }
    }
    return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    // Base case: an empty tree is always balanced
    if (!root_) return true;
	return calculateHeightIfBalanced(root_) != -1;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::calculateHeightIfBalanced(Node<Key,Value>* root) const{
	// Think about cases to handle:
	// - What if at least one subtree is NOT balanced?
	// - What if BOTH are balanced?
    
	// Base case: return the leaf node and nullptr
	if (!root) return 0;
	if(root->getLeft() == NULL && root->getRight() == NULL) return 1;
    // Binary calculate height
	int leftheight = calculateHeightIfBalanced(root->getLeft());
	int rightheight = calculateHeightIfBalanced(root->getRight());
	if(leftheight - rightheight > 1 || leftheight - rightheight < -1 || leftheight == -1 || rightheight == -1){
		return -1;
	}
	else if(leftheight > rightheight){
		return 1 + leftheight;
	}
	else{
		return 1 + rightheight;
	}
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer
   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif