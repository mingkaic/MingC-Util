//
//  bstree.cpp
//  Tree
//
//  description: binary tree search
//
//  Created by Mingkai Chen on 2016-01-18.
//  Copyright © 2016 Mingkai Chen. All rights reserved.
//

#ifdef __BSTREE__H

// search for key in subtree i_root
// @param[in]   key   T typed data to search for
// return   NULL if root is NULL
//          pointer to root (if root contains key)
//          pointer to the parent to node containing key otherwise

template <class T>
dcontain::treenode<T>* bstree<T>::BinSearch (T key, dcontain::treenode<T>* i_root) const
    {
    dcontain::treenode<T>* parent;
    dcontain::treenode<T>* child;
    parent = child = i_root;

    while(NULL != child)
        {
        if (this->equals(child->getData(), key))
            {
            child = NULL;
            }
        else 
            {
            parent = child;
            if (0 > this->compare(child->getData(), key))
                {
                child = child->left;
                }
            else
                {
                child = child->right;
                }
            }
        }
    return parent;
    }

// get the successor of subtree rooted by i_root
// @param[in]   i_root  dcontain::treenode pointer root of subtree
// return   NULL if root right is NULL
//          pointer to successor's parent 
//          (which is root if right node has no left child)

template <class T>
dcontain::treenode<T>* bstree<T>::successorParent (dcontain::treenode<T>* i_root)
    {
    dcontain::treenode<T>* success = i_root;
    dcontain::treenode<T>* parent = NULL;
    
    if (NULL != i_root->right)
        {
        parent = success;
        success = i_root->right;
        while (NULL != success->left)
            {
            parent = success;
            success = success->left;
            }
        }

    return parent;
    }

// recurse through this tree in order
// @param[in]   root    pointer to root of subtree to recurse through
// @param[in]   func    function to perform on each node
// return  void

template <class T>
void bstree<T>::completeRecurse (dcontain::treenode<T>* root, 
    std::function<void(dcontain::treenode<T>*)> func) const
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

template <class T>
bstree<T>::bstree (void) : root(NULL)
    {
    }

// destroys self content, then copy src content to self
// @remark copy constructor

template <class T>
bstree<T>::bstree (const bstree<T>& src) : root(NULL), comparator<T>(src)
    {
    if (NULL != src.root)
        {
        root = src.root->cascadeCopy();
        }
    }

// destructor
// @remark destructor

template <class T>
bstree<T>::~bstree (void)
    {
    clear();
    }

// copy assignment operator
// @param[in]   src     reference to bstree object to copy from
// @return      reference to this after copy assignment

template <class T>
bstree<T>& bstree<T>::operator = (const bstree<T>& src)
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

template <class T>
dcontain::wrapper<T> bstree<T>::get (T key) const
    {
    dcontain::wrapper<T> pass;
    dcontain::treenode<T>* parent = BinSearch(key, root);
    if (NULL != parent)
        {
        dcontain::treenode<T>* keyComparer = parent;
        signed compIndex = this->compare(key, parent->getData());
        if (0 < compIndex)
            {
            keyComparer = parent->left;
            }
        else if (0 > compIndex)
            {
            keyComparer = parent->right;
            }
        if (NULL != keyComparer)
            {
            pass.good = true;
            pass.value = keyComparer->getData();
            }
        }
    return pass;
    }

// insert key into tree
// @param[in]   key     key
// @return wrapper object value associated with previous key, 
// castable to false if there was no associated value
// castable to true otherwise

template <class T>
dcontain::wrapper<T> bstree<T>::put (T key)
    {
    dcontain::wrapper<T> pass;
    dcontain::treenode<T>* parent = BinSearch(key, root);
    if (NULL == parent) // the root is NULL
        {
        root = new dcontain::treenode<T>(key);
        }
    else 
        {
        signed compIndex = this->compare(parent->getData(), key);
        if (0 > compIndex)
            {
            if (NULL != parent->left)
                {
                pass.good = true;
                pass.value = parent->left->getData();
                parent->left->injectData(key);
                }
            else
                {
                parent->left = new dcontain::treenode<T>(key);
                }
            }
        else if (0 < compIndex)
            {
            if (NULL != parent->right)
                {
                pass.good = true;
                pass.value = parent->right->getData();
                parent->right->injectData(key);
                }
            else
                {
                parent->right = new dcontain::treenode<T>(key);
                }
            }
        else // parent is root
            {
            pass.good = true;
            pass.value = root->getData();
            root->injectData(key);
            }
        }
    return pass;
    }

// remove value in tree
// @param[in]   key     key
// @return wrapper object value associated with previous key, 
// castable to false if there was no associated value
// castable to true otherwise

template <class T>
dcontain::wrapper<T> bstree<T>::remove (T key)
    {
    dcontain::wrapper<T> pass;
    dcontain::treenode<T>* parent = BinSearch(key, root);
    if (NULL != parent)
        {
        T p_data = parent->getData();
        bool isRoot = root == parent && this->equals(p_data, key);
        bool isLeft = 0 > this->compare(p_data, key);
        dcontain::treenode<T>* heir = NULL;
        dcontain::treenode<T>* keyComparer;
        
        if (isRoot)
            {
            keyComparer = parent;
            }
        else if (true == isLeft)
            {
            keyComparer = parent->left;
            }
        else
            {
            keyComparer = parent->right;
            }

        if (NULL != keyComparer && this->equals(key, keyComparer->getData()))
            {
            dcontain::treenode<T>* heirParent = successorParent(keyComparer);
            if (NULL == heirParent)
                {
                if (NULL != keyComparer->left)
                    {
                    heir = keyComparer->left;
                    }
                }
            else if (heirParent == keyComparer)
                {
                heir = keyComparer->right;
                heir->left = keyComparer->left;
                }
            else
                {
                heir = heirParent->left;
                heirParent->left = heir->right;
                heir->left = keyComparer->left;
                heir->right = keyComparer->right;
                }
            pass.good = true;
            pass.value = keyComparer->getData();
            delete keyComparer;
                
            if (isRoot)
                {
                root = heir;
                }
            else if (isLeft)
                {
                parent->left = heir;
                }
            else
                {
                parent->right = heir;
                }
            }
        }

    return pass;
    }

// get a searchlist copy of this tree in order
// @param[]  void
// @return a searchlist of this tree

template <class T>
std::vector<T> bstree<T>::getList (void) const
    {
    std::vector<T> sample;
    completeRecurse(root, [&sample](dcontain::treenode<T>* root) 
        {
        sample.push_back(root->getData());
        });
    return sample;
    }

// determine the number of nodes in this tree
// @param[]  void
// @return size_t number of nodes in this tree

template <class T>
size_t bstree<T>::size (void) const
    {
    size_t count = 0;
    completeRecurse(root, [&count](dcontain::treenode<T>* root) 
        {
        count++;
        });
    return count;
    }

// remove all nodes in this tree
// @param[]  void
// @return void

template <class T>
void bstree<T>::clear (void)
    {
    if (NULL != root)
        {
        root->cascadeDelete();
        }
    root = NULL;
    }

#endif /* __BSTREE__H */