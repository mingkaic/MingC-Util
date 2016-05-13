//
//  treap.cpp
//  Tree
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#ifdef __TREAP__H

// overload compare operations for prinode
template <typename T>
bool operator < (const prinode<T>*& left, const prinode<T>*& right)
    {
    long signed lp = -1;
    long signed rp = -1;
    if (NULL != left)
        {
        lp = left->getPriority();
        }
    if (NULL != right)
        {
        rp = right->getPriority();
        }
    return lp < rp;
    }

template <typename T>
bool operator > (const prinode<T>*& left, const prinode<T>*& right)
    {
    long signed lp = -1;
    long signed rp = -1;
    if (NULL != left)
        {
        lp = left->getPriority();
        }
    if (NULL != right)
        {
        rp = right->getPriority();
        }
    return lp > rp;
    }

// constructs node with data
// @remark constructor

template <typename T>
prinode<T>::prinode (T data) : left(NULL), right(NULL), parent(NULL)
    {
    priority = rand();
    this->dataInit(data);
    }

// constructs node with data and determined priority
// @remark constructor

template <typename T>
prinode<T>::prinode (T data, size_t priority) : left(NULL), right(NULL), parent(NULL), priority(priority)
    {
    this->dataInit(data);
    }

// deletes self and children

template <typename T>
void prinode<T>::cascadeDelete (void)
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
prinode<T>* prinode<T>::cascadeCopy (void) const
    {
    prinode<T>* cpy = new prinode<T>(this->data, this->getPriority());

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

template <typename T>
treap<T>* treap<T>::split()
    {
    }

template <typename T>
void treap<T>::merge(treap<T>* other)
    {
    }

// rotate node section
// @param[out]  parent      pointer to the pivot node
// @param[in]   rotateLeft  true if right child should become new parent
// @return void

template <typename T>
void treap<T>::rotate(prinode<T>* parent, bool rotLeft)
    {
    prinode<T>* child;
    if (true == rotLeft)
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
prinode<T>* treap<T>::BinSearch (T key, prinode<T>* i_root) const
    {
    prinode<T>* match;
    prinode<T>* child = match = i_root;

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
prinode<T>* treap<T>::successor (prinode<T>* i_root)
    {
    prinode<T>* success = i_root;
    
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
void treap<T>::completeRecurse (prinode<T>* root, 
                    std::function<void(prinode<T>*)> func) const
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

// destroys self content, then copy src content to self
// @remark copy constructor

template <typename T>
treap<T>::treap (const treap<T>& src) : root(NULL), comparator<T>(src)
    {
    if (NULL != src.root)
        {
        root = src.root->cascadeCopy();
        }
    }

// destructor
// @remark destructor

template <typename T>
treap<T>::~treap (void)
    {
    clear();
    }

// copy assignment operator
// @param[in]   src     reference to treap object to copy from
// @return      reference to this after copy assignment

template <typename T>
treap<T>& treap<T>::operator = (const treap<T>& src)
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
dcontain::wrapper<T> treap<T>::get (T key) const
    {
    dcontain::wrapper<T> pass;
    prinode<T>* match = BinSearch(key, root);
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
dcontain::wrapper<T> treap<T>::put (T key)
    {
    dcontain::wrapper<T> pass;
    prinode<T>* match = BinSearch(key, this->root);

    if (NULL == match)
        {
        this->root = new prinode<T>(key);
        }
    else if (this->equals(match->getData(), key))
        {
        pass.good = true;
        pass.value = match->getData();
        match->injectData(key);
        }
    else
        {
        prinode<T>* child = new prinode<T>(key);
        child->parent = match;

        // key < match
        bool isLeft = 0 < this->compare(key, match->getData());
        if (isLeft)
            {
            match->left = child;
            }
        else
            {
            match->right = child;
            }

        // bubble up
        while (child < match)
            {
            rotate(match, false == isLeft);
            match = child->parent;
            if (NULL != match)
                {
                isLeft = match->left == child;
                }
            }
        }
    return pass;
    }

// remove value in tree
// @param[in]   key     key
// @return wrapper object value associated with previous key, 
// castable to false if there was no associated value
// castable to true otherwise

template <typename T>
dcontain::wrapper<T> treap<T>::remove(T key)
    {
    dcontain::wrapper<T> pass;
    prinode<T>* foundNode = BinSearch(key, this->root);

    // if the tree is empty or the data is not found
    // remove by successor
    if (NULL != foundNode && this->equals(foundNode->getData(), key))
        {
        pass.good = true;
        pass.value = foundNode->getData();
        prinode<T>* parent = foundNode->parent;
        bool isLeft;
        if (NULL != parent)
            {
            isLeft = parent->left == foundNode;
            }

        if (NULL == foundNode->left && NULL == foundNode->right)
            {
            if (NULL == parent)
                {
                root = NULL;
                }
            else if (isLeft)
                {
                parent->left = NULL;
                }
            else
                {
                parent->right = NULL;
                }
            delete foundNode;
            }
        else if (NULL == foundNode->left)
            {
            foundNode->right->parent = parent;

            if (NULL == parent)
                {
                root = foundNode->right;
                }
            else if (isLeft)
                {
                parent->left = foundNode->right;
                }
            else
                {
                parent->right = foundNode->right;
                }
            delete foundNode;
            }
        else if (NULL == foundNode->right)
            {
            foundNode->left->parent = parent;
            
            if (NULL == parent)
                {
                root = foundNode->left;
                }
            else if (isLeft)
                {
                parent->left = foundNode->left;
                }
            else
                {
                parent->right = foundNode->left;
                }
            delete foundNode;
            }
        else
            {
            prinode<T>* heir = successor(foundNode);
            prinode<T>* child = NULL == heir->right ? heir->left : heir->right;
            parent = heir->parent;
            foundNode->copy(heir);
            
            if (NULL != child)
                {
                child->parent = parent;
                }

            if (heir == parent->left)
                {
                parent->left = child;
                }
            else
                {
                parent->right = child;
                }

            // bubble down
            isLeft = foundNode->left > foundNode->right;
            child = isLeft ? foundNode->left : foundNode->right;
            
            while (foundNode < child && NULL != foundNode)
                {
                rotate(foundNode, false == isLeft);
                foundNode = child->parent;
                if (NULL != foundNode)
                    {
                    isLeft = foundNode->left > foundNode->right;
                    child = isLeft ? foundNode->left : foundNode->right;
                    }
                }

            delete heir;
            }
        }
    
    return pass;
    }

template <typename T>
dcontain::wrapper<T>  treap<T>::peekTop (void)
    {
    dcontain::wrapper<T> pass;
    if (NULL != root)
        {
        pass.good = true;
        pass.value = this->root->getData();
        }
    return pass;
    }

template <typename T>
void treap<T>::tr_union()
    {
    }

template <typename T>
void treap<T>::tr_intersection()
    {
    }

template <typename T>
void treap<T>::tr_difference()
    {
    }

// creates a searchlist copy of this tree in order
// @param[]  void
// @return a searchlist of this tree

template <typename T>
std::vector<T> treap<T>::getList (void) const
    {
    std::vector<T> sample;
    completeRecurse(root, [&sample](prinode<T>* root) 
        {
        sample.push_back(root->getData());
        });
    return sample;
    }

// determine the number of nodes in this tree
// @param[]  void
// @return size_t number of nodes in this tree

template <typename T>
size_t treap<T>::size (void) const
    {
    size_t count = 0;
    completeRecurse(root, [&count](prinode<T>* root) 
        {
        count++;
        });
    return count;
    }

// remove all nodes in this tree
// @param[]  void
// @return void

template <typename T>
void treap<T>::clear (void)
    {
    if (NULL != root)
        {
        root->cascadeDelete();
        }
    root = NULL;
    }
        
#endif /* __TREAP__H */