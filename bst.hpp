/**
 * Binary Search Tree - Template
 *
 * Store values in a BST
 * Can use Inorder, Preorder and Postorder to traverse tree
 * Can use Add/Remove to modify tree
 * Rebalance creates a balanced tree
 *
 * @author Lexun Chi
 * @date 4/14/2019
 */

#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <string>

using namespace std;

template<class T>
class BST {
  // display a sideways ascii representation of tree
  friend ostream &operator<<(ostream &os, const BST &bst) {
    bst.sideways(bst.rootPtr, 0, os);
    return os;
  }

 private:
  // Node for BST
  typedef struct node {
    T data;
    struct node *leftPtr;
    struct node *rightPtr;
  } Node;

  // root of the tree
  Node *rootPtr{
      nullptr
  };

  // Make a new BST Node
  Node *makeNode(const T &value) const {
    // TODO(me)
    //nullptr = new Node(value);
    //return nullptr;
    Node *rootPtr = new Node(value);

    rootPtr ->leftPtr = new Node(value);
    rootPtr ->rightPtr = new Node(value);

    return rootPtr;
  }

  // helper function for displaying tree sideways, works recursively
  void sideways(Node *current, int level, ostream &os) const {
    static const string indents{"   "};
    if (current) {
      level++;
      sideways(current->rightPtr, level, os);

      // indent for readability, 4 spaces per depth level
      for (int i = level; i >= 0; i--)
        os << indents;

      // display information of object
      os << current->data << endl;
      sideways(current->leftPtr, level, os);
    }
  }

  // Additional private functions
  // TODO(me)
  /*Helper functions that I created*/

 public:
  // constructor, empty tree
  BST() {
    // TODO(me)
    rootPtr = NULL;
  }

  // constructor, tree with root
  explicit BST(const T &rootItem) {
    // TODO(me)
    Node *n = new Node();
    n->data = rootItem;
    rootPtr  = n;
  }

  // given an array of length n
  // create a tree to have all items in that array
  // with the minimum height (i.e. rebalance)
  BST(const T arr[], int n) {
    // TODO(me)
    constructBST(arr, 0, n-1, rootPtr);
  }

  // copy constructor
  BST(const BST<T> &bst) {
    // TODO(me)
    rootPtr = copyTree(bst.rootPtr);
  }

  // destructor
  virtual ~BST() {
    // TODO(me)
    Clear();
  }

  //?????
  Node* copyTree(Node* root) {
      Node *n = NULL;
      if(root != NULL) {
          n = new Node();
          n->data = root->data;
          n->leftPtr = copyTree(root->leftPtr);
          n->rightPtr = copyTree(root->rightPtr);
      }
      return n;
  }

  // true if no nodes in BST
  bool IsEmpty() const {
    // TODO(me)
    return (rootPtr == NULL);
  }

  //Helper method for getHeight method
  int getHeightHelper(Node* rootPtr) const {
      if(rootPtr == NULL)
          return 0;
      else{
          //compute the depth pf each subtree
          int lDepth = getHeightHelper(rootPtr->leftPtr);
          int rDepth = getHeightHelper(rootPtr->rightPtr);

          //find the larger one
          if(lDepth > rDepth)
              return (lDepth+1);
          else
              return (rDepth+1);
      }
  }
  // 0 if empty, 1 if only root, otherwise
  // height of root is max height of subtrees + 1
  int getHeight() const {
    // TODO(me)
    return getHeightHelper(rootPtr);
  }
  //Helper method for NumberOfNodes
  int NodeNumHelper(Node* rootPtr) const {
      if(rootPtr == NULL)
          return 0;
      return 1 + NodeNumHelper(rootPtr->leftPtr) + NodeNumHelper(rootPtr->rightPtr);
  }

  // number of nodes in BST
  int NumberOfNodes() const {
    // TODO(me)
    return NodeNumHelper(rootPtr);
  }


    Node* AddHelper(const T &item, Node* rootPtr) {
        Node *newNode = new Node();
        newNode->data = item;

      if(rootPtr == NULL) {
          //rootPtr = newNode;
          return newNode;
      }
      if(item.compare(rootPtr->data) < 0) {
          rootPtr -> leftPtr = AddHelper(item, rootPtr->leftPtr);
          return rootPtr;
      } else {
          rootPtr -> rightPtr = AddHelper(item, rootPtr->rightPtr);
          return rootPtr;
      }

      return NULL;
  }
  // add a new item, return true if successful
  bool Add(const T &item) {
    // TODO(me)
    rootPtr = AddHelper(item, rootPtr);
    return true;
  }

  //
  Node* findMin(Node* rootPtr) const{
      if(rootPtr == NULL)
          return NULL;
      if(rootPtr->leftPtr != NULL)
          return findMin(rootPtr->leftPtr);
      return rootPtr;
  }

  //This is the helper method for Remove()
  Node* removeHelper(Node* rootPtr, const T &item) const {
      if(rootPtr == NULL)
          return NULL;
      if(item.compare(rootPtr->data) < 0)
          rootPtr->leftPtr = removeHelper(rootPtr->leftPtr, item);
      else if(item.compare(rootPtr->data) > 0)
          rootPtr->rightPtr = removeHelper(rootPtr->rightPtr, item);
      else {
          //case 1: no children
          if(rootPtr->leftPtr ==  NULL && rootPtr->rightPtr == NULL) {
              delete rootPtr;
              rootPtr = NULL;
          }
          //case 2: one chile(right)
          else if(rootPtr->leftPtr == NULL) {
              Node *temp = rootPtr;
              rootPtr = rootPtr->rightPtr;
              delete temp;
          }
          //case 3: one chile(left)
          else if(rootPtr->rightPtr == NULL) {
              Node* temp = rootPtr;
              rootPtr = rootPtr->leftPtr;
              delete temp;
          }
          //case 4: two cildren
          else{
              Node* temp = findMin(rootPtr->rightPtr);
              rootPtr->data = temp->data;
              rootPtr->rightPtr = removeHelper(rootPtr->rightPtr, temp->data);
          }
      }
      return rootPtr;
  }
  // remove item, return true if successful
  bool Remove(const T &item) {
    // TODO(me)
    if(removeHelper(rootPtr, item)!= NULL)
        return true;
    return false;
  }

  //This is the helper method for contains method
  bool ContainsHelper(const T &item, Node* rootPtr) const {
      if(rootPtr == NULL)
          return false;
      if(item == rootPtr->data)
          return true;
      else if(item < rootPtr -> data)
          return ContainsHelper(item, rootPtr -> leftPtr);
      else
          return ContainsHelper(item, rootPtr -> rightPtr);

  }
  // true if item is in BST
  bool Contains(const T &item) const {
    // TODO(me)
    return(ContainsHelper(item, rootPtr));
  }

  //Helper class of inorderTraverse
  void InorderHelper(Node *root, void visit(const T &item)) const {
      if (root == NULL) return;

      InorderHelper(root->leftPtr, visit);
      visit(root->data);
      InorderHelper(root->rightPtr, visit);
  }
  // inorder traversal: left-root-right
  // takes a function that takes a single parameter of type T
  void InorderTraverse(void visit(const T &item)) const {
    // TODO(me)
    InorderHelper(rootPtr, visit);
  }

  //Helper class of preorderTraverse
  void PreorderHelper(Node* root, void visit(const T &item)) const {
      if(root == NULL)
          return;
      visit(root->data);
      PreorderHelper(root->leftPtr, visit);

      PreorderHelper(root->rightPtr, visit);
  }
  // preorder traversal: root-left-right
  void PreorderTraverse(void visit(const T &item)) const {
    // TODO(me)
    PreorderHelper(rootPtr, visit);
  }

  //Helper function of postorderTraverse
  void PostorderHelper(Node* root, void visit(const T &item)) const {
     if(root == NULL)
        return;
     PostorderHelper(root->leftPtr, visit);

     PostorderHelper(root->rightPtr, visit);
      visit(root->data);
  }
  // postorder traversal: left-right-root
  void PostorderTraverse(void visit(const T &item)) const {
    // TODO(me)
    PostorderHelper(rootPtr, visit);
  }

  //This helper method attempts to convert an array into a bst
  void constructBST(T* array[], int start, int end, Node* rootPtr){
      if(start > end)
          return;
      int mid = (start+end)/2;

      if(rootPtr == NULL)
          rootPtr = new Node(array[mid]);

      rootPtr->leftPtr = constructBST(array, start, mid-1, rootPtr->leftPtr);
      rootPtr->rightPtr = constructBST(array, mid+1, end, rootPtr->rightPtr);
  }

  //traverse the tree inorder and record the data into the array
  void bstToArray(Node* rootPtr, T* array[], int *index) {
     while(rootPtr != NULL) {
        bstToArray(rootPtr->leftPtr, array, index);
        array[index] = rootPtr->data;
        index++;
        bstToArray(rootPtr->rootPtr, array, index);
     }
  }
  // create dynamic array, copy all the items to the array
  // and then read the array to re-create this tree from scratch
  // so that resulting tree should be balanced
  void Rebalance() {
    // TODO(me)
    T* array = new T[NumberOfNodes()];
    bstToArray(rootPtr, array, 0);
    constructBST(array, 0, NumberOfNodes() - 1, rootPtr);
  }

  //Helper method for clear()
  //I am not sure about this method.
  void clearHelper(Node* rootPtr) {
      if(rootPtr != NULL) {
          clearHelper(rootPtr->leftPtr);
          clearHelper(rootPtr->rightPtr);

          //delete rootPtr->data;
          delete rootPtr;

          //rootPtr->data = NULL;
      }
  }
  // delete all nodes in tree
  void Clear() {
    // TODO(me)
    clearHelper(rootPtr);
  }

  bool equalHelper(Node* rootPtr, Node* otherrootPtr) const {
      if(rootPtr == NULL && otherrootPtr == NULL)
          return true;
      else if(rootPtr == NULL || otherrootPtr ==  NULL)
          return false;
      else if(rootPtr->data != otherrootPtr->data)
          return false;
      return equalHelper(rootPtr -> leftPtr, otherrootPtr -> leftPtr) &&
              equalHelper(rootPtr -> rightPtr, otherrootPtr -> rightPtr);
  }
  // trees are equal if they have the same structure
  // AND the same item values at all the nodes
  bool operator==(const BST<T> &other) const {
    // TODO(me)y
    if(equalHelper(rootPtr, other.rootPtr))
        return true;
    return false;
  }

  // not == to each other
  bool operator!=(const BST<T> &other) const {
    // TODO(me)
    return !(*this == other);
  }
};

#endif  // BST_HPP
