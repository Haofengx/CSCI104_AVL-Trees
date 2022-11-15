#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n);
		bool zigzig(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p, AVLNode<Key, Value>* g);
		void rotateLeft(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p);
		void rotateRight(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p);
		void removeFix(AVLNode<Key, Value>* n, int8_t diff);
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
		// BST implementation
		// Special case if the tree if NULL
	  if(static_cast<AVLNode<Key, Value>*>(this->root_) == NULL){
			this->root_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
			static_cast<AVLNode<Key, Value>*>(this->root_)->setBalance(0);
      return;
		}
    // copy a root node to iterate all tree
		AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(this->root_);
    bool flag = true;
    // use loop to iterate
    while(flag){
        if(temp->getKey() < new_item.first){
            if(temp->getRight() != NULL){
                temp = temp->getRight();
            }
            else{
                temp->setRight(new AVLNode<Key, Value>(new_item.first, new_item.second, temp));
								temp = temp->getRight();
                flag = false;
            }
        }
        else if(temp->getKey() > new_item.first){
            if(temp->getLeft() != NULL){
                temp = temp->getLeft();
            }
            else{
                temp->setLeft(new AVLNode<Key, Value>(new_item.first, new_item.second, temp));
								temp = temp->getLeft();
                flag = false;
            }
        }
				else{
						temp->setValue(new_item.second);
						flag = false;
				}
    }
		// End implementation of BST insertion
		// start of update balance and 
		// first set temp balance to 0
		temp->setBalance(0);
		// second checking balance of parent and grandparent
		if(temp->getParent() != NULL){
			int8_t balanceOfTempParent = temp->getParent()->getBalance();
			if(balanceOfTempParent == -1) temp->getParent()->setBalance(0);
			else if(balanceOfTempParent == 1) temp->getParent()->setBalance(0);
			else if(balanceOfTempParent == 0){
				if(temp->getParent()->getLeft() == temp) temp->getParent()->setBalance(-1);
				else temp->getParent()->setBalance(1);
				insertFix(temp->getParent(), temp);
			}
		}
}

// insertFix which could change balance of AVLnode
// and rotate nodes to fix tree when situation is not balanced
template<class Key, class Value>
void AVLTree<Key, Value>:: insertFix(AVLNode<Key,Value>* p, AVLNode<Key,Value>* n){
	if(p == NULL || p->getParent() == NULL) return;
	AVLNode<Key, Value>* g = p->getParent();
	// if p is left child of g
	if(p == g->getLeft()){
		g->updateBalance(-1);
		// case 1: b(g) == 0
		if(g->getBalance() == 0) return;
		// case 2: b(g) == -1
		else if(g->getBalance() == -1) insertFix(g, p);
		// case 3: b(g) == -2
		else if(g->getBalance() == -2){
			// if n,p,g is zig-zig
			if(n == p->getLeft()){
				rotateRight(p, g);
				p->setBalance(0);
				g->setBalance(0);
			}
			// else if n,p,g is zig-zag
			else{
				rotateLeft(n, p);
				rotateRight(n, g);
				// subcase: b(n) == -1
				if(n->getBalance() == -1){
					p->setBalance(0);
					g->setBalance(1);
					n->setBalance(0);
				}
				// subcase: b(n) == 0
				else if(n->getBalance() == 0){
					p->setBalance(0);
					g->setBalance(0);
					n->setBalance(0);
				}
				// subcase: b(n) == 1
				else if(n->getBalance() == 1){
					p->setBalance(-1);
					g->setBalance(0);
					n->setBalance(0);
				}
			}
		}
	}
	// else if p is right child of g
	else{
		g->updateBalance(1);
		// case 1: b(g) == 0
		if(g->getBalance() == 0) return;
		// case 2: b(g) == 1
		else if(g->getBalance() == 1) insertFix(g, p);
		// case 3: b(g) == 2
		else if(g->getBalance() == 2){
			// if n,p,g is zig-zig
			if(n == p->getRight()){
				rotateLeft(p, g);
				p->setBalance(0);
				g->setBalance(0);
			}
			// else if n,p,g is zig-zag
			else{
				rotateRight(n, p);
				rotateLeft(n, g);
				// subcase: b(n) == 1
				if(n->getBalance() == 1){
					p->setBalance(0);
					g->setBalance(-1);
					n->setBalance(0);
				}
				// subcase: b(n) == 0
				else if(n->getBalance() == 0){
					p->setBalance(0);
					g->setBalance(0);
					n->setBalance(0);
				}
				// subcase: b(n) == -1
				else if(n->getBalance() == -1){
					p->setBalance(1);
					g->setBalance(0);
					n->setBalance(0);
				}
			}
		}
	}
}

// helper function to determine whether the situation is zigzig or zigzag
// return true if is zig-zig and return false if zig-zag
template<class Key, class Value>
bool AVLTree<Key, Value>:: zigzig(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p, AVLNode<Key, Value>* g){
	int8_t nbalance = n->getBalance();
	int8_t pbalance = p->getBalance();
	int8_t gbalance = g->getBalance();
	if(nbalance >= pbalance && pbalance >= gbalance) return true;
	else if(nbalance <= pbalance && pbalance <= gbalance) return true;
	else return false;
}

// helper function to rotate nodes n,p,g and child nodes
template<class Key, class Value>
void AVLTree<Key, Value>:: rotateRight(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p){
	if(p->getParent()){
		AVLNode<Key, Value>* g = p->getParent();
		if(p == g->getLeft()) g->setLeft(n);
		else g->setRight(n);
		n->setParent(g);
	}
	else{
		n->setParent(NULL);
		this->root_ = n;
	}
	if(n->getRight()){
		p->setLeft(n->getRight());
		n->getRight()->setParent(p);
	}
	else{
		p->setLeft(NULL);
	}
	n->setRight(p);
	p->setParent(n);
}

// helper function to rotate nodes n,p,g and child nodes
template<class Key, class Value>
void AVLTree<Key, Value>:: rotateLeft(AVLNode<Key, Value>* n, AVLNode<Key, Value>* p){
	if(p->getParent()){
		AVLNode<Key, Value>* g = p->getParent();
		if(p == g->getLeft()) g->setLeft(n);
		else g->setRight(n);
		n->setParent(g);
	}
	else{
		n->setParent(NULL);
		this->root_ = n;
	}
	if(n->getLeft()){
		p->setRight(n->getLeft());
		n->getLeft()->setParent(p);
	}
	else{
		p->setRight(NULL);
	}
	n->setLeft(p);
	p->setParent(n);
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
	// TODO
	// BST implementation
	// check for special case the node is not in the tree
	if(static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::internalFind(key)) == NULL){
			return;
	}
	// then the node is in the tree and ready to remove
	// there are three options for node: 0,1 or 2 child 
	AVLNode<Key, Value>* temp = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::internalFind(key));
	// if node have two children swap the node with predecessor
	if(temp->getLeft() != NULL && temp->getRight() != NULL){
		AVLNode<Key, Value>* pred = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(temp));
		nodeSwap(pred, temp);
	}
	// diff will be the amount added to updateed the balance of p
	int8_t diff;
	AVLNode<Key, Value>* parent = temp->getParent();
	if(parent != NULL){
		if(parent->getLeft() == temp) diff = 1;
		else diff = -1;
	}
	// if node only have one node get the address of it
	AVLNode<Key, Value>* child = NULL;
	if(temp->getLeft() == NULL) child = temp->getRight();
	else child = temp->getLeft();
	if(parent != NULL){
		if(parent->getLeft() == temp) parent->setLeft(child);
		else parent->setRight(child);
	}
	else this->root_ = child;
	if(child != NULL) child->setParent(parent);
	// End implementation of BST remove
	delete temp;
	temp = NULL;
	removeFix(parent, diff);
}

// removeFix which could change balance of AVLnode
// and rotate nodes to fix tree when situation is not balanced
template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int8_t diff){
	if(n == NULL) return;
	// compute the next recursive call's argument before altering the tree
	AVLNode<Key, Value>* p = n->getParent();
	int8_t ndiff;
	if(p != NULL){
		if(p->getLeft() == n) ndiff = 1;
		else ndiff = -1;
	}
	// if diff == -1
	if(diff == -1){
		// case 1: b(n) + diff == -2
		if(n->getBalance() + diff == -2){
			AVLNode<Key, Value>* c = n->getLeft();
			// subcase 1a: b(c) == -1, zigzig
			if(c->getBalance() == -1){
				rotateRight(n->getLeft(), n);
				n->setBalance(0);
				c->setBalance(0);
				removeFix(p, ndiff);
			}
			// subcase 1b: b(c) == 0, zigzig
			else if(c->getBalance() == 0){
				rotateRight(n->getLeft(), n);
				n->setBalance(-1);
				c->setBalance(1);
				return;
			}
			// subcase 1c: b(c) == 1, zigzag
			else if(c->getBalance() == 1){
				AVLNode<Key, Value>* g = c->getRight();
				rotateLeft(g, c);
				rotateRight(g, n);
				if(g->getBalance() == 1){
					n->setBalance(0);
					c->setBalance(-1);
					g->setBalance(0);
				}
				else if(g->getBalance() == 0){
					n->setBalance(0);
					c->setBalance(0);
					g->setBalance(0);
				}
				else if(g->getBalance() == -1){
					n->setBalance(1);
					c->setBalance(0);
					g->setBalance(0);
				}
				removeFix(p, ndiff);
			}
		}
		// case 2: b(n) + diff == -1
		else if(n->getBalance() + diff == -1) n->setBalance(-1);
		// case 3: b(n) + diff == 0
		else if(n->getBalance() + diff == 0){
			n->setBalance(0);
			removeFix(p, ndiff);
		}
	}
	// if diff == 1
	else{
		// case 1: b(n) + diff == 2
		if(n->getBalance() + diff == 2){
			AVLNode<Key, Value>* c = n->getRight();
			// subcase 1a: b(c) == 1, zigzig
			if(c->getBalance() == 1){
				rotateLeft(n->getRight(), n);
				n->setBalance(0);
				c->setBalance(0);
				removeFix(p, ndiff);
			}
			// subcase 1b: b(c) == 0, zigzig
			else if(c->getBalance() == 0){
				rotateLeft(n->getRight(), n);
				n->setBalance(1);
				c->setBalance(-1);
				return;
			}
			// subcase 1c: b(c) == -1, zigzag
			else if(c->getBalance() == -1){
				AVLNode<Key, Value>* g = c->getLeft();
				rotateRight(g, c);
				rotateLeft(g, n);
				if(g->getBalance() == -1){
					n->setBalance(0);
					c->setBalance(1);
					g->setBalance(0);
				}
				else if(g->getBalance() == 0){
					n->setBalance(0);
					c->setBalance(0);
					g->setBalance(0);
				}
				else if(g->getBalance() == 1){
					n->setBalance(-1);
					c->setBalance(0);
					g->setBalance(0);
				}
				removeFix(p, ndiff);
			}
		}
		// case 2: b(n) + diff == 1
		else if(n->getBalance() + diff == 1) n->setBalance(1);
		// case 3: b(n) + diff == 0
		else if(n->getBalance() + diff == 0){
			n->setBalance(0);
			removeFix(p, ndiff);
		}
	}
}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif