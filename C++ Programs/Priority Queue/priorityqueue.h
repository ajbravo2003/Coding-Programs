/**------------------------------------------
//  Project 5 - Priority Quene
    Course: CS 251, Spring 2023.
    System: Visual Studio Code 2023
    Author: Alejandro Bravo
 ---------------------------------------------**/
 /// @file priorityqueue.h
#pragma once
#include <iostream>
#include <sstream>
#include <set>
using namespace std;
template<typename T>
class priorityqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;  // stored data for the p-queue
        bool dup;  // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;  // links to linked list of NODES with duplicate priorities
        NODE* left;  // links to left child
        NODE* right;  // links to right child
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of elements in the pqueue
    NODE* curr;  // pointer to next item in pqueue (see begin and next)
    void toStringRecursionFunction(NODE* node, ostream& output) {//helper function for to string
        if (node != nullptr) {//traverses the tree at root
            toStringRecursionFunction(node->left, output);//stores left nodes
            output << node->priority << " value: " << node->value << endl;//prints out prioritys and values
            toStringRecursionFunction(node->link, output);//stores duplicate nodes in outstream
            toStringRecursionFunction(node->right, output);//stores the right nodes in outstream
        }
    }

void clearRecursionFunction(NODE* currentNode) {//helper function for clear to traverse through the tree
    if (currentNode == nullptr) {//checks if root is already empty
        return;
    }
    clearRecursionFunction(currentNode->left);//traverses through the left nodes
    clearRecursionFunction(currentNode->right);//traverses through the right nodes
    clearRecursionFunction(currentNode->link);//traverses through the right nodes
    delete currentNode;
}

void recursionFunctionOperator(NODE* currentNode) {
      if (currentNode != nullptr) {//checks if the node is empty
        this->enqueue(currentNode->value, currentNode->priority);//enqueue the value and priority of the current node
        if (currentNode->dup) {//if the current node is a duplicate node
            NODE* tempNode = currentNode->link;//get the first node in the linked list of duplicates
            while (tempNode != nullptr) {//enqueue all nodes in the linked list of duplicates
                this->enqueue(tempNode->value, tempNode->priority);
                tempNode = tempNode->link;//move to the next node in the linked list
            }
        }
        recursionFunctionOperator(currentNode->left);//recursively traverse the left subtree
        recursionFunctionOperator(currentNode->right);//recursively traverse the right subtree
    }

}

bool recursingBoolOperator(NODE* thisNode, NODE* otherNode) const {
    if (thisNode == nullptr && otherNode == nullptr) {//checks to make sure if one is null both bsts have to be
        return true;
    }
    if (thisNode == nullptr || otherNode == nullptr) {//checks if one tree is empty and one isnt
        return false;
    }
    if (thisNode->priority != otherNode->priority) {//checks to make sure prioirtys of both are same
        return false;
    }
    
    recursingBoolOperator(thisNode->left, otherNode->left);
    while(thisNode->link != nullptr && otherNode->link != nullptr){//traverses through the linked list
        if(thisNode->link!= otherNode->link){//checks to make sure both nodes are the same
            return false;
        }
        if(thisNode->priority!= otherNode->priority){
            return false;
        }
        if(thisNode->value!= otherNode->value){
            return false;
        }
        thisNode = thisNode->link;//continues to next node
        otherNode = otherNode->link;//continues to next node
    }
     recursingBoolOperator(thisNode->right, otherNode->right);//recursing through all nodes to make sure theyre the same
}

public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue() {//sets all data memebers to default values
        curr = nullptr;
        root = nullptr;
        size = 0;
    }

    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue& operator=(const priorityqueue& other) {
       this->clear();//clears function
        recursionFunctionOperator(other.root);//gets all nodes from other quene
        this->root = other.root;
        return *this;
    }

    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear(){      
    if(root==nullptr){//checks if the root is null
        return;//doesnt delete anything
    }
    clearRecursionFunction(root);//passes root node to traverse through the list
    root = nullptr;//sets all data memeber back to default values
    curr = nullptr;
    size = 0;
    }

    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue() {

    }

    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    void enqueue(T value, int priority) {
        NODE* insertedNode = new NODE;//creates a new node 
        insertedNode->priority = priority;//sets the priority to the node priority
        insertedNode->value = value;//sets the value given to the node value
        insertedNode->dup = false;//sets false to duplicate
        insertedNode->left = nullptr;//sets all pointers in the new node to nullptr or else we crash
        insertedNode->right = nullptr;
        insertedNode->link = nullptr;
        if (root == nullptr) {//checks if theres a root node
            root = insertedNode;//sets created node to rode
            insertedNode->parent = nullptr;//sets null to parent since it's the root node
            size++;
        }
        else {//activates when there is a root node
            size++;
            NODE* parentNode = nullptr;//creates a parent node to set a parent
            NODE* tempNode = root;//creates a node to traverse the list
            while (tempNode != nullptr) {//traverses through list
                parentNode = tempNode;//sets parentnode to temp
                if (priority < tempNode->priority) {//checks if priority is smaller than node priority
                    tempNode = tempNode->left;//moves to the left
                }

                else if (priority > tempNode->priority) {//checks if priority is greater than the current nodes priority
                    tempNode = tempNode->right;//moves to the right
                }

                else {//else that means node is a duplicate
                    while(tempNode->link!=nullptr){//travereses through the link listed of duplicates to add new duplicate node at the end
                        tempNode = tempNode->link;
                    }
                    insertedNode->link = tempNode->link;//sets node to link to node
                    tempNode->link = insertedNode;//adds node into the linked list of duplicates
                    insertedNode->dup = true;//sets true to duplicate
                    return;//breaks out of loop because no more traversing isnt needed and no parent is needed
                }
            }
            insertedNode->parent = parentNode;//sets root as the parent
            if (priority < parentNode->priority) {//checks if parent priority is less than priority
                parentNode->left = insertedNode;//sets node to the left
            }

            else {
                parentNode->right = insertedNode;//sets node to the right side of the parent
            }
        } 
        //delete insertedNode
    }
    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
  T dequeue() {
    if(size == 0){//returns nothing is quene is empty
        return T();
    }
    NODE* currNode = root;
    while (currNode->left != nullptr) {//gets the lowest priority node
        currNode = currNode->left;
    }
    while (currNode->right != nullptr && currNode->right->priority == currNode->priority) {
        currNode = currNode->right;
    }
    if(currNode->dup==true){//checks if its a duplicate
        currNode->link = currNode->link->link;

    }
    if (currNode == root) {//checks if the lowest priority node is the root
        if (root->left == nullptr && root->right == nullptr) {
            root = nullptr;
        } else if (root->left != nullptr && root->right == nullptr) {
            root = root->left;
            root->parent = nullptr;
        } else if (root->left == nullptr && root->right != nullptr) {
            root = root->right;
            root->parent = nullptr;
        } else {
            NODE* rightNode = root->right;
            root = root->left;
            root->parent = nullptr;
            NODE* tempNode = root;
            while (tempNode->right != nullptr) {
                tempNode = tempNode->right;
            }
            tempNode->right = rightNode;
            rightNode->parent = tempNode;
        }
    } 
    
    else {//else reassigns the nodes based on the node that will be deleted
        NODE* parentNode = currNode->parent;
        if (currNode->left == nullptr && currNode->right == nullptr) {
            if (parentNode->left == currNode) {
                parentNode->left = nullptr;
            } else {
                parentNode->right = nullptr;
            }
        } 
        
        else if (currNode->left != nullptr && currNode->right == nullptr) {
            if (parentNode->left == currNode) {
                parentNode->left = currNode->left;
            } else {
                parentNode->right = currNode->left;
            }
            currNode->left->parent = parentNode;
        } 
        
        else if (currNode->left == nullptr && currNode->right != nullptr) {
            if (parentNode->left == currNode) {
                parentNode->left = currNode->right;
            } else {
                parentNode->right = currNode->right;
            }
            currNode->right->parent = parentNode;
        } 
        
        else {
            NODE* rightNode = currNode->right;
            if (parentNode->left == currNode) {
                parentNode->left = currNode->left;
            } else {
                parentNode->right = currNode->left;
            }
            currNode->left->parent = parentNode;
            NODE* largestLeftNode = currNode->left;
            while (largestLeftNode->right != nullptr) {
                largestLeftNode = largestLeftNode->right;
            }
            largestLeftNode->right = rightNode;
            rightNode->parent = largestLeftNode;
        }
    }
    size--;
    T valueOut = currNode->value;
    delete currNode;//deletes node
    return valueOut;//returns value of lowest priority 
}



    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size() {
        return size;
    }

    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin() {
         curr = root;//sets the current to the root
         if (curr != nullptr) {//keeps going while there are nodes
             while (curr->left != nullptr) {//traverses through the left nodes to start inorder traversal
            curr = curr->left;//starts from bottom to top
        }
    }
}

    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T& value, int& priority) {
    if (curr == nullptr) {//checks if there are no more nodes to traverse
        return false;//no more nodes so it breaks out of function
    }
    value = curr->value;//sets values of node
    priority = curr->priority;//sets prioirty to node
    if (curr->link != nullptr) {//checks if theres a link
        curr = curr->link;//traverses to next node in duplicate list
    } 
    
    else if (curr->right != nullptr) {//checks right side of the tree
        curr = curr->right;
        while (curr->left != nullptr) {//traverses to the left node of the tree
            curr = curr->left;//keeps going to most left node
        }
    } 
    else {
        NODE* parent = curr->parent;//traverses through parent nodes
        while (parent != nullptr && curr == parent->right) {//checks the right node of parent
            curr = parent;
            parent = parent->parent;//keeps going to next parent
        }
        curr = parent;//assigns current to parent
    }
     return true;//returns true since there is still nodes
    }

    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //
    string toString() {
        stringstream string;
        toStringRecursionFunction(root, string);
        return string.str();
    }

    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number 
    // of duplicate priorities
    //
    T peek() {
    NODE* tempNode = root;
    while (tempNode->left != nullptr) {
        tempNode = tempNode->left;
    }
    return tempNode->value;
    }

    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue& other) const {
         if (this->size != other.size) {//checks if the size between both bst are the same
        return false;
    }
    return recursingBoolOperator(root, other.root);//calls recursion function to check all nodes of both bsts 
    }

    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};