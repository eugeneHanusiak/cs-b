#ifndef MYMAP
#define MYMAP

#include <iostream>

template<typename KeyType, typename ValueType>
//asociative array that stores elemets as key and its value, its structure is represented as a binary search tree
class myMap{

public:

    //Constructor
    myMap();

    //Destructor
    ~myMap();

    //Adds a new pair (key and value) to map, if such key is present in the map method changes it's value to new
    void makePair(KeyType, ValueType);

    //Returns value of key
    ValueType getKey(KeyType key);

    //Returns true if map is empty
    bool isEmpty();

    //Removes all elements
    void clear();

    //Return number of elements in the map
    int size();

    //Remove element of map that contains key
    void remove(KeyType);

    //Return true if this key present in the map
    bool hasKey(KeyType key);

private:

    // Structure for storing key-value pairs as Binary Search Tree
    struct nodeTree  {
        KeyType Key;
        ValueType Value;
        int nodeHeight;
        nodeTree* left;
        nodeTree* right;
    };

    //Balance the binary tree
    nodeTree* balanceTree(nodeTree* node);

    // Returns the height of current sub-tree
    int getNodeHeight(nodeTree* node);

    //Return the difference of height of right and left sub-trees
    int getBalanceFactor(nodeTree* node);

    //Correcting the height of current nod
    //add 1 to sub tree that higher
    void fixHeight(nodeTree* node);

    //Right turn around current node
    nodeTree* rotateRight(nodeTree* node);

    //Left turn around a current node
    nodeTree* rotateLeft(nodeTree* node);

    //Inserts new node with pair key and value to the tree and balance it
    nodeTree* insertNode(nodeTree* node, KeyType key, ValueType value);

    //Deleting node with current key and balance tree
    nodeTree* removeNode(nodeTree* node, KeyType key);

    //Returns pointer to the last left node
    nodeTree* findMinNode(nodeTree* node);

    //Deleting minimal element of current sub-tree
    nodeTree* removeMinNode(nodeTree* node);

    //Returns pointer to node that contains current key
    nodeTree* findNode(nodeTree* node, KeyType key);

    //deleting all nodes in tree
    void clearTree(nodeTree* node);

    nodeTree* root;
    int count;
};

template<typename KeyType, typename ValueType>
int myMap<KeyType, ValueType>::getNodeHeight(nodeTree *node){
    if (node != 0){
        return node->nodeHeight;
    }
    return 0;
}

template<typename KeyType, typename ValueType>
int myMap<KeyType, ValueType>::getBalanceFactor(nodeTree *node){
    return getNodeHeight(node->right) - getNodeHeight(node->left);
}

template<typename KeyType, typename ValueType>
void myMap<KeyType, ValueType>::fixHeight(nodeTree *node){
    //make +1 ot hight of more higher sub tree
    if (getNodeHeight(node->left) > getNodeHeight(node->right)){
        node->nodeHeight = getNodeHeight(node->left) + 1;
    } else {
        node->nodeHeight = getNodeHeight(node->right) + 1;
    }
}

template<typename KeyType, typename ValueType>
typename myMap<KeyType, ValueType>::nodeTree* myMap<KeyType, ValueType>::rotateLeft(nodeTree *node){
    nodeTree* RightSubTree = node->right;
    node->right = RightSubTree->left;
    RightSubTree->left = node;
    fixHeight(node);
    fixHeight(RightSubTree);
    return RightSubTree;
}


template<typename KeyType, typename ValueType>
typename myMap<KeyType, ValueType>::nodeTree* myMap<KeyType, ValueType>::rotateRight(nodeTree *node){
    nodeTree* leftSubTree = node->left;
    node->left = leftSubTree->right;
    leftSubTree->right = node;
    fixHeight(node);
    fixHeight(leftSubTree);
    return leftSubTree;
}

template<typename KeyType, typename ValueType>
typename myMap<KeyType, ValueType>::nodeTree* myMap<KeyType, ValueType>::balanceTree(nodeTree *node){
    fixHeight(node);

    //if right subtree higher then left on two
    if (getBalanceFactor(node) == 2){
        //if left subtree higher then right do big left turn
        if (getBalanceFactor(node->right) < 0){
            node->right = rotateRight(node->right);
        }
        //else - do left turn
        return rotateLeft(node);
    }
    //if left subtree higher then right on two
    if (getBalanceFactor(node) == -2){
        //if right subtree higher then left do big right turn
        if (getBalanceFactor(node->left) > 0){
            node->left = rotateLeft(node->left);
        }
        //else - do simple right turn
        return rotateRight(node);
    }
    return node;
}


template<typename KeyType, typename ValueType>
typename myMap<KeyType, ValueType>::nodeTree* myMap<KeyType, ValueType>::insertNode(nodeTree* node, KeyType key, ValueType value){
    //making new node if its not present in tree
    if (node == NULL) {
        count++;
        node = new nodeTree;
        node->Key = key;
        node->Value = value;
        node->nodeHeight = 1;
        node->right = node->left = 0;
        return node;
    } else if (key > node->Key){
        node->right = insertNode(node->right, key, value); //going to right sub tree and insert new node using recursion
    } else if (key < node->Key){
        node->left = insertNode(node->left, key, value); //going to left sub tree and insert new node using recursion
    } else {
        //if node present in tree change it value
        node->Value = value;
    }

    return balanceTree(node);

}


template<typename KeyType, typename ValueType>
typename myMap<KeyType, ValueType>::nodeTree* myMap<KeyType, ValueType>::findNode(nodeTree* node, KeyType key){
    if (key > node->Key) {
        //if current key not found in this subtree
        if(node->right == 0) {
            return 0;
        }
        //going to right sub tree and search key there using recursion
        return findNode(node->right, key);

    } else if (key < node->Key) {
        //if current key not found in this subtree
        if (node->left == 0) {
            return 0;
        }
        //going to left sub tree and search key there using recursion
        return findNode(node->left, key);
    }
    //retur node with current key
    return node;
}

template<typename KeyType, typename ValueType>
typename myMap<KeyType, ValueType>::nodeTree* myMap<KeyType, ValueType>::removeNode(nodeTree* node, KeyType key){
    //if key not found
    if (node == 0) {
        return 0;
    }
    if (key < node->Key) {
        //find key in the left subtree using recursion
        node->left = removeNode(node->left, key);
    } else if (key >node->Key) {
        //search key in the right subtree using recursion
        node->right = removeNode(node->right, key);
    } else if (key == node->Key) {
        //save left and right sub tree of current node
        nodeTree* leftNode = node->left;
        nodeTree* rightNode = node->right;

        delete node;
        count--;

        if (rightNode == 0){
            return leftNode;
        }
        //finds minimal node in the right subtree and puts it to the place of deleted node
        nodeTree* minNode = findMinNode(rightNode);
        //add right subtree without min node
        minNode->right = removeMinNode(rightNode);
        //add left subtree
        minNode->left = leftNode;
        return balanceTree(minNode);
    }
    return balanceTree(node);
}

template<typename KeyType, typename ValueType>
typename myMap<KeyType, ValueType>::nodeTree* myMap<KeyType, ValueType>::findMinNode(nodeTree *node){
    //find min (last left) node using recursion
    return (node->left == NULL) ? node : findMinimum(node->left);
}

template<typename KeyType, typename ValueType>
typename myMap<KeyType, ValueType>::nodeTree* myMap<KeyType, ValueType>::removeMinNode(nodeTree *node){
    if(node->left == 0) {
        //replace min node to its right sub tree
        return node->right;
    }
    node->left = removeMinNode(node->left);
    return balanceTree(node);
}

template<typename KeyType, typename ValueType>
void myMap<KeyType, ValueType>::clearTree(nodeTree *node){
    //deleting all nodes using recursion
    if (node->left != 0){
        clearTree(node->left);
    }
    if (node->right != 0){
        clearTree(node->right);
    }

    delete node;
}


//Constructor
template<typename KeyType, typename ValueType>
myMap<KeyType, ValueType>::myMap(){
    root = 0;
    count = 0;
}
//Destructor
template<typename KeyType, typename ValueType>
myMap<KeyType, ValueType>::~myMap(){
    clearTree(root);
}

template<typename KeyType, typename ValueType>
void myMap<KeyType, ValueType>::makePair(KeyType key, ValueType value){
    root = insertNode(root, key, value);
}

template<typename KeyType, typename ValueType>
ValueType myMap<KeyType, ValueType>::getKey(KeyType key){
    nodeTree* result = findNode(root, key);
    if (result == 0){
        std::cout << "Key not found!!!" << std::endl;
        exit(1);
    }
    return result->Value;

}

template<typename KeyType, typename ValueType>
int myMap<KeyType, ValueType>::size(){
    return count;
}

template<typename KeyType, typename ValueType>
void myMap<KeyType, ValueType>::remove(KeyType key){
    nodeTree* result = removeNode(root, key);
    if (result == 0) {
        std::cout << "Key not found!!!" << std::endl;
        exit(1);
    }
    root = result;
}

template<typename KeyType, typename ValueType>
bool myMap<KeyType, ValueType>::isEmpty(){
    return count == 0;
}

template<typename KeyType, typename ValueType>
void myMap<KeyType, ValueType>::clear(){
    clearTree(root);
    count = 0;
    root = 0;
}

template<typename KeyType, typename ValueType>
bool myMap<KeyType, ValueType>::hasKey(KeyType key){
    return findNode(root, key) != 0;
}

#endif // MYMAP
