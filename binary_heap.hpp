#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

#include <cassert>
#include <climits>
#include <cstdlib>
#include <functional>
#include <stack>

#define EMPTY nullptr

namespace {

/* Used to represent path in binary tree. */
typedef enum { L, R } Direction;

template <typename T> class Node {
   private:
    T data;

    Node *left, *right;

   public:
    /* Instantiate a leaf. */
    Node(T data);

    /* Instantiate an internal node. */
    Node(T data, Node *left, Node *right);

    /* Return the children corresponding to the given direction. */
    Node *get_child(Direction d);

    /* Insert a children. */
    void insert(Direction direction, Node<T> *node);

    T get_data();

    void set_data(T data);

    ~Node();
};
}  // namespace

template <typename T> class BinaryHeap {
   public:
    /* Create a new empty (default: min) heap. */
    BinaryHeap();

    /* Create a new empty heap that uses compare(a, b) to prioritise elements.
     * @param compare Should return true if priority(a) < priority(b).*/
    BinaryHeap(bool (*compare)(T, T));

    /* Get the number of elements in the binary-heap. */
    uint get_size();

    void insert(T element);

    T pop_top();

    T get_top();

    ~BinaryHeap();

   private:
    Node<T> *tree;

    uint size;

    std::function<bool(T, T)> compare;

    /* Return the path to the last leaf in a quasi-perfect binary tree
       of size n. */
    std::stack<Direction> get_dirlist(uint n, std::stack<Direction> = {});

    /* Insert a node as leaf after following a list of directions. */
    void insert_leaf(Node<T> *tree, Node<T> *to_insert,
                     std::stack<Direction> dirlist);

    /* Bubble-up a leaf to restablish the heap property. */
    void bubble_up(std::stack<Direction> &dirlist);
    void _bubble_up(Node<T> *node, std::stack<Direction> &dirlist);

    void swap_nodes(Node<T> *a, Node<T> *b);

    T pop_leaf(Node<T> *node, std::stack<Direction> dirlist);

    /* Bubble-down the root to restablish the heap property. */
    void bubble_down(Node<T> *node);
};

/* Node implementation ********************************************************/

template <typename T> Node<T>::Node(T data) {
    this->data = data;
    left = right = EMPTY;
}

template <typename T> Node<T>::Node(T data, Node *left, Node *right) {
    this->data  = data;
    this->left  = left;
    this->right = right;
}

template <typename T> Node<T> *Node<T>::get_child(Direction direction) {
    return direction == L ? left : right;
}

template <typename T> void Node<T>::insert(Direction direction, Node<T> *node) {
    direction == L ? left = node : right = node;
}

template <typename T> T Node<T>::get_data() { return data; }

template <typename T> void Node<T>::set_data(T data) { this->data = data; }

template <typename T> Node<T>::~Node() {
    if (left != EMPTY) delete (left);
    if (right != EMPTY) delete (right);
}

/* Binary-Heap implementation *************************************************/

template <typename T> BinaryHeap<T>::BinaryHeap() {
    compare = [](T a, T b) { return a > b; };
    size    = 0;
    tree    = EMPTY;
}

template <typename T> BinaryHeap<T>::BinaryHeap(bool compare(T, T)) {
    this->compare = compare;
    size          = 0;
    tree          = EMPTY;
}

template <typename T> void BinaryHeap<T>::insert(T element) {
    Node<T> *node = new Node<T>(element);

    if (++size == 1) {
        tree = node;
        return;
    }

    std::stack<Direction> dirlist = get_dirlist(size);
    insert_leaf(tree, node, dirlist);
    bubble_up(dirlist);
}

template <typename T>
std::stack<Direction> BinaryHeap<T>::get_dirlist(
    uint n, std::stack<Direction> directions) {
    if (n < 2) return directions;
    n % 2 == 0 ? directions.push(L) : directions.push(R);
    return get_dirlist(n / 2, directions);
}

Direction stack_pop(std::stack<Direction> &stack) {
    auto ret = stack.top();
    stack.pop();
    return ret;
}

template <typename T>
void BinaryHeap<T>::insert_leaf(Node<T> *tree, Node<T> *to_insert,
                                std::stack<Direction> dirlist) {
    assert(!dirlist.empty() && "ERROR: empty dirlist");

    Direction direction = stack_pop(dirlist);

    if (dirlist.empty()) {
        tree->insert(direction, to_insert);
        return;
    }

    Node<T> *child = tree->get_child(direction);
    insert_leaf(child, to_insert, dirlist);
}

template <typename T>
void BinaryHeap<T>::bubble_up(std::stack<Direction> &dirlist) {
    _bubble_up(tree, dirlist);
}

template <typename T>
void BinaryHeap<T>::_bubble_up(Node<T> *node, std::stack<Direction> &dirlist) {
    assert(!dirlist.empty() && "ERROR: empty dirlist");

    Direction direction  = stack_pop(dirlist);
    Node<T> * child      = node->get_child(direction);
    T         child_data = child->get_data(), node_data = node->get_data();

    if (dirlist.empty()) {
        if (compare(node_data, child_data)) swap_nodes(node, child);
        return;
    }

    _bubble_up(child, dirlist);

    child      = node->get_child(direction);
    child_data = child->get_data(), node_data = node->get_data();

    if (compare(node_data, child_data)) swap_nodes(node, child);
}

template <typename T> void BinaryHeap<T>::swap_nodes(Node<T> *a, Node<T> *b) {
    assert(a && b && "ERROR: empty node");

    T temp = a->get_data();
    a->set_data(b->get_data());
    b->set_data(temp);
}

template <typename T> T BinaryHeap<T>::pop_top() {
    assert(size > 0 && "ERROR: heap is empty");

    T data = tree->get_data();

    if (size == 1) {
        delete (tree);
        size--;
        tree = EMPTY;
        return data;
    }

    auto dirlist   = get_dirlist(size);
    auto leaf_data = pop_leaf(tree, dirlist);
    size--;
    tree->set_data(leaf_data);
    bubble_down(tree);

    return data;
}

template <typename T>
T BinaryHeap<T>::pop_leaf(Node<T> *node, std::stack<Direction> dirlist) {
    assert(!dirlist.empty() && "ERROR: empty dirlist");

    Direction direction = stack_pop(dirlist);
    Node<T> * child     = node->get_child(direction);

    if (dirlist.empty()) {
        T data = child->get_data();
        delete (child);
        node->insert(direction, EMPTY);
        return data;
    }

    return pop_leaf(child, dirlist);
}

template <typename T> void BinaryHeap<T>::bubble_down(Node<T> *node) {
    Node<T> * child;
    Direction dir;
    T         node_data = node->get_data();

    if (node->get_child(L) == EMPTY) return;

    if (node->get_child(R) == EMPTY && node->get_child(L) != EMPTY) {
        T left_data = node->get_child(L)->get_data();
        child       = node->get_child(L);
        if (compare(node_data, left_data)) swap_nodes(node, child);
        return;
    }

    T left_data  = node->get_child(L)->get_data(),
      right_data = node->get_child(R)->get_data();

    auto comp = compare(left_data, right_data) ? right_data : left_data;

    if (compare(node_data, comp)) {
        dir   = compare(left_data, right_data) ? R : L;
        child = node->get_child(dir);
        swap_nodes(node, child);
        bubble_down(child);
    }
}

template <typename T> uint BinaryHeap<T>::get_size() { return size; }

template <typename T> T BinaryHeap<T>::get_top() {
    assert(!(tree == EMPTY) && "ERROR: Attempting to insert in empty heap.");
    return this->tree->data;
}

template <typename T> BinaryHeap<T>::~BinaryHeap() { delete (tree); }

#endif
