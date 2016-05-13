//
//  rbtree.cpp
//  Tree
//
//  description: red black marked binary tree search to ensure log n search/insertion/removal
//
//  Created by Ming Kai Chen on 2014-06-26.
//  Copyright (c) 2014 Ming Kai Chen. All rights reserved.
//

#ifdef __RB_TREE__H

// constructs node with data
// @remark constructor

template <typename T>
rbnode<T>::rbnode (T data) :
left(NULL), right(NULL), parent(NULL), isBlack(true)
    {
    this->dataInit(data);
    }

// constructs node with data and color
// @remark constructor

template <typename T>
rbnode<T>::rbnode (T data, bool black) :
left(NULL), right(NULL), parent(NULL), isBlack(black)
    {
    this->dataInit(data);
    }

// deletes self and children

template <typename T>
void rbnode<T>::cascadeDelete (void)
    {
    if (NULL != left)
        {
        left->cascadeDelete();
        }
    if (NULL != right)
        {
        right->cascadeDelete();
        }
    delete this;
    }

// copies self and children

template <typename T>
rbnode<T>* rbnode<T>::cascadeCopy (void) const
    {
    rbnode<T>* cpy = new rbnode<T>(this->data, isBlack);

    if (NULL != left)
        {
        cpy->left = left->cascadeCopy();
        cpy->left->parent = cpy;
        }
    if (NULL != right)
        {
        cpy->right = right->cascadeCopy();
        cpy->right->parent = cpy;
        }
    
    return cpy;
    }

// fixes redblack order after removal
// @param[out]  parent          pointer to the parent node to fix around
// @param[in]   childIsLeft     true if troubled child is left of parent
// @return void

template <typename T>
void rbtree<T>::deleteFixUp (rbnode<T>* parent, bool childIsLeft)
    {
    rbnode<T>* child;
    rbnode<T>* sibling;
    
    child = childIsLeft ? parent->left : parent->right;
    while (child != this->root && (NULL == child || child->isBlack))
        {
        sibling = childIsLeft ? parent->right : parent->left;
        // sibling cannot be NULL, parent cannot be NULL
        if (false == sibling->isBlack)
            {
            sibling->isBlack = true;
            parent->isBlack = false;
            // rotate in the child's direction
            rotate(parent, childIsLeft);
            sibling = childIsLeft ? parent->right : parent->left;
            }
        // sibling can be childless which are treated as black
        if ((NULL == sibling->left || true == sibling->left->isBlack) &&
            (NULL == sibling->right || true == sibling->right->isBlack))
            {
            sibling->isBlack = false;
            // moving up in the tree
            child = parent;
            parent = child->parent;
            if (parent && parent->left == child)
                childIsLeft = true;
            else
                childIsLeft = false;
            }
        else
            {
            if (true == childIsLeft &&
                (NULL == sibling->right || true == sibling->right->isBlack))
                {
                if (NULL != sibling->left)
                    {
                    sibling->left->isBlack = true;
                    }
                
                sibling->isBlack = false;
                rotate(sibling, false); // right rotate
                sibling = parent->right;
                }
            if (false == childIsLeft &&
                (NULL == sibling->left || sibling->left->isBlack))
                {
                if (NULL != sibling->right)
                    {
                    sibling->right->isBlack = true;
                    }
                
                sibling->isBlack = false;
                rotate(sibling, true); // left rotate
                sibling = parent->left;
                }
            if (true == childIsLeft && NULL != sibling->right)
                {
                sibling->right->isBlack = true;
                }
            if (false == childIsLeft && NULL != sibling->left)
                {
                sibling->left->isBlack = true;
                }
            sibling->isBlack = parent->isBlack;
            parent->isBlack = true;
            rotate(parent, childIsLeft); // rotate in child's direction
            child = this->root;
            }
        }
    child->isBlack = true;
    }

// rotate node section
// @param[out]  parent      pointer to the pivot node
// @param[in]   rotateLeft  true if right child should become new parent
// @return void

template <typename T>
void rbtree<T>::rotate (rbnode<T>* parent, bool rotateLeft)
    {
    rbnode<T>* child;
    if (true == rotateLeft)
        {
        child = parent->right;
        // parent's right adopts child's left
        parent->right = child->left;
        if (child->left)
            child->left->parent = parent;
        // child's left adopts parent
        child->left = parent;
        }
    else
        {
        child = parent->left;
        // parent's left adopts child's right
        parent->left = child->right;
        if (child->right)
            child->right->parent = parent;
        // child's right adopts parent
        child->right = parent;
        }
    // child's new parent is his previous grandparent
    child->parent = parent->parent;
    // parent's new parent was its previous child
    // if root, no parent
    if (parent->parent)
        {
        if (parent->parent->left == parent)
            {
            parent->parent->left = child;
            }
        else
            {
            parent->parent->right = child;
            }
        }
    parent->parent = child;
    // rotation fixup
    if (this->root == parent)
        {
        this->root = child;
        }
    }

// search for key in subtree i_root
// @param[in]   key   T typed data to search for
// return   NULL if root is NULL
//          pointer to node containing key

template <typename T>
rbnode<T>* rbtree<T>::BinSearch (T key, rbnode<T>* i_root) const
    {
    rbnode<T>* match;
    rbnode<T>* child = match = i_root;

    while(NULL != child && false == this->equals(match->getData(), key))
        {
        match = child;
        if (0 > this->compare(child->getData(), key))
            {
            child = child->left;
            }
        else
            {
            child = child->right;
            }
        }
    return match;
    }

// get the successor of subtree rooted by i_root
// @param[in]   i_root  rbnode pointer root of subtree
// return   root if root right is NULL
//          pointer to successor

template <typename T>
rbnode<T>* rbtree<T>::successor (rbnode<T>* i_root)
    {
    rbnode<T>* success = i_root;
    
    if (NULL != i_root->right)
        {
        success = i_root->right;
        }
    while (NULL != success->left)
        {
        success = success->left;
        }
    
    return success;
    }

// recurse through this tree in order
// @param[in]   root    pointer to root of subtree to recurse through
// @param[in]   func    function to perform on each node
// return  void

template <typename T>
void rbtree<T>::completeRecurse (rbnode<T>* root, 
                    std::function<void(rbnode<T>*)> func) const
    {
    if (NULL != root)
        {
        if (NULL != root->left)
            {
            completeRecurse(root->left, func);
            }
        func(root);
        if (NULL != root->right)
            {
            completeRecurse(root->right, func);
            }
        }
    }

// constructs NULL root
// @remark default constructor

template <typename T>
rbtree<T>::rbtree (void) : root(NULL)
    {
    }

// destroys self content, then copy src content to self
// @remark copy constructor

template <typename T>
rbtree<T>::rbtree (const rbtree& src) : root(NULL), comparator<T>(src)
    {
    if (NULL != src.root)
        {
        root = src.root->cascadeCopy();
        }
    }

// destructor
// @remark destructor

template <typename T>
rbtree<T>::~rbtree (void)
    {
    clear();
    }

// copy assignment operator
// @param[in]   src     reference to rbtree object to copy from
// @return      reference to this after copy assignment

template <typename T>
rbtree<T>& rbtree<T>::operator = (const rbtree<T>& src)
    {
    comparator<T>::operator = (src);
    if (this != &src)
        {
        clear();
        if (NULL != src.root)
            {
            root = src.root->cascadeCopy();
            }
        }
    return *this;
    }

// determine if key is in tree
// @param[in]   key     key
// @return wrapper object value associated with key,
// castable to false if there was no associated value
// castable to true otherwise

template <typename T>
dcontain::wrapper<T> rbtree<T>::get (T key) const
    {
    dcontain::wrapper<T> pass;
    rbnode<T>* match = BinSearch(key, root);
    if (NULL != match && this->equals(match->getData(), key))
        {
        pass.good = true;
        pass.value = match->getData();
        }
    return pass;
    }

// insert key into tree
// @param[in]   key     key
// @return wrapper object value associated with previous key, 
// castable to false if there was no associated value
// castable to true otherwise

template <typename T>
dcontain::wrapper<T> rbtree<T>::put (T key)
    {
    dcontain::wrapper<T> pass;
    
    // find primary insertion place:
    //      NULL -> empty tree,
    //      data = key -> duplicate,
    //      data > key -> left is NULL -> child is left,
    //      data < key -> right is NULL -> child is right,
    rbnode<T>* topNode = BinSearch(key, this->root);
    
    // Insert to empty tree
    if (NULL == topNode)
        {
        this->root = new rbnode<T>(key, true);
        }
    else if (this->equals(topNode->getData(), key))
        {
        pass.good = true;
        pass.value = topNode->getData();
        topNode->injectData(key);
        }
    else
        {
        // this Node is red and has parent set to insertAfter
        rbnode<T>* child = new rbnode<T>(key, false);
        bool parentIsLeft = false;
        child->parent = topNode;
        
        bool childIsLeft = 0 > this->compare(topNode->getData(), key);
        if (true == childIsLeft)
            {
            topNode->left = child;
            }
        else
            {
            topNode->right = child;
            }
        
        // maintain RedBlack properties
        // note: grandparent is black in loop, since parent is red
        while (NULL != child->parent && false == child->parent->isBlack)
            {
            // due to iteration, topNode is not yet
            // guaranteed to be child's parent
            parentIsLeft = child->parent == child->parent->parent->left;
            // make topNode the uncle of the child
            topNode = parentIsLeft ? child->parent->parent->right : child->parent->parent->left;
            
            // case 1: uncle is red
            if (NULL != topNode && false == topNode->isBlack)
                {
                child->parent->isBlack = topNode->isBlack = true;
                topNode->parent->isBlack = false;
                // Move up to the grandparent
                child = topNode->parent;
                childIsLeft = (this->root != child && child->parent->left == child);
                }
            else // uncle is a black Node or nil
                {
                // case 2: parent and child orientation are not aligned
                // rotate parent, stay at the same level (the parent becometh the child)
                if (childIsLeft != parentIsLeft)
                    {
                    child = child->parent;
                    rotate(child, parentIsLeft);
                    }
                // case 3: orientations are aligned
                // parent must be black (in order to take over grandparent's position)
                // grandparent change to red
                child->parent->isBlack = true;
                child->parent->parent->isBlack = false;
                rotate(child->parent->parent, !parentIsLeft); // parent moves up
                }
            }
        // property 1: root is black
        this->root->isBlack = true;
        }
    
    return pass;
    }

// remove value in tree
// @param[in]   key     key
// @return wrapper object value associated with previous key, 
// castable to false if there was no associated value
// castable to true otherwise

template <typename T>
dcontain::wrapper<T> rbtree<T>::remove (T key)
    {
    dcontain::wrapper<T> pass;
    rbnode<T>* foundNode = BinSearch(key, this->root);

	// if the tree is empty or the data is not found
    // remove by successor
    if (NULL != foundNode && this->equals(foundNode->getData(), key))
        {
        pass.good = true;
        pass.value = foundNode->getData();

        rbnode<T>* heir = successor(foundNode);
        rbnode<T>* child = NULL == heir->right ? heir->left : heir->right;
        rbnode<T>* parent = heir->parent;
        bool childIsLeft = true;
        
        foundNode->injectData(heir->getData());
        
        // detach child from heir (if child exists)
        if (NULL != child) // at least 1 child
            {
            child->parent = parent;
            }
        if (NULL == parent) // if heir is the root
            {
            this->root = child;
            if (NULL != this->root)
                {
                this->root->isBlack = true;
                }
            }
        else
            {
            childIsLeft = heir == parent->left;
            if (true == childIsLeft)
                {
                parent->left = child;
                }
            else
                {
                parent->right = child;
                }
            if (true == heir->isBlack)
                {
                // child could be null, so parent is passed in
                deleteFixUp(parent, childIsLeft);
                }
            }
            
        delete heir;
        }
        
    return pass;
    }

// creates a searchlist copy of this tree in order
// @param[]  void
// @return a searchlist of this tree

template <typename T>
std::vector<T> rbtree<T>::getList (void) const
    {
    std::vector<T> sample;
    completeRecurse(root, [&sample](rbnode<T>* root) 
        {
        sample.push_back(root->getData());
        });
    return sample;
    }

// determine the number of nodes in this tree
// @param[]  void
// @return size_t number of nodes in this tree

template <typename T>
size_t rbtree<T>::size (void) const
    {
    size_t count = 0;
    completeRecurse(root, [&count](rbnode<T>* root) 
        {
        count++;
        });
    return count;
    }

// remove all nodes in this tree
// @param[]  void
// @return void

template <typename T>
void rbtree<T>::clear (void)
    {
    if (NULL != root)
        {
        root->cascadeDelete();
        }
    root = NULL;
    }

#endif /* __RB_TREE__H */