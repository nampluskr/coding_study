#pragma once

template<typename T>
struct Node {
    T data;
    Node* left, * right;
};

template<typename T>
struct BinarySearchTree_recur {
    Node<T>* root;

    Node<T>* find(const T& data) { return find_recur(root, data); }
    void insert(const T& data) { root = insert_recur(root, data); }
    void remove(const T& data) { root = remove_recur(root, data); }

    Node<T>* find_recur(Node<T>* ptr, const T& data) {
        if (ptr == nullptr) return nullptr;
        if (data == ptr->data)
            return ptr;
        if (data < ptr->data)
            return find_recur(ptr->left, data);
        else
            return find_recur(ptr->right, data);
    }
    Node<T>* insert_recur(Node<T>* ptr, const T& data) {
        if (ptr == nullptr) return new Node<T>{ data, nullptr, nullptr };
        
        if (data == ptr->data)
            return ptr;
        else if (data < ptr->data)
            ptr->left = insert_recur(ptr->left, data);
        else
            ptr->right = insert_recur(ptr->right, data);
        return ptr;
    }
    Node<T>* findMin(Node<T>* ptr) {
        if (ptr->left == nullptr) return ptr;
        return findMin(ptr->left);
    }
    Node<T>* remove_recur(Node<T>* ptr, const T& data) {
        if (ptr == nullptr) return nullptr;

        if (data == ptr->data){
            Node<T>* temp = ptr;

            // case 1: no child
            if (ptr->left == nullptr && ptr->right == nullptr)
                ptr = nullptr;

            // case 2: one child
            else if (ptr->left != nullptr && ptr->right == nullptr)
                ptr = ptr->left;
            else if (ptr->left == nullptr && ptr->right != nullptr)
                ptr = ptr->right;

            // case 3: two children
            else {
                Node<T>* min_node = findMin(ptr->right);
                ptr->right = ptr->right->right;
                min_node->left = ptr->left;
                min_node->right = ptr->right;
                ptr = min_node;
            }
            delete temp;
            return ptr;
        }
        if (data < ptr->data)
            ptr->left = remove_recur(ptr->left, data);
        else
            ptr->right = remove_recur(ptr->right, data);
        return ptr;
    }
    //Node<T>* remove_recur(Node<T>* ptr, const T& data) {
    //    if (ptr == nullptr) return nullptr;

    //    if (data < ptr->data)
    //        ptr->left = remove_recur(ptr->left, data);
    //    else if (ptr->data < data)
    //        ptr->right = remove_recur(ptr->right, data);
    //    else {
    //        if (ptr->left == nullptr) {
    //            auto temp = root->right; delete ptr;
    //            return temp;
    //        }
    //        else if (ptr->right == nullptr) {
    //            auto temp = root->left; delete ptr;
    //            return temp;
    //        }
    //        auto temp = findMin(ptr->right);
    //        ptr->data = temp->data;
    //        ptr->right = remove_recur(ptr->right, temp->data);
    //    }
    //    return ptr;
    //}
};

template<typename T>
struct BinarySearchTree_iter{
    Node<T>* root;

    Node<T>* find(const T& data) {
        Node<T>* ptr = root;
        while (ptr != nullptr) {
            if (data == ptr->data) return ptr;
            if (data < ptr->data)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        return nullptr;
    }
    void insert(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* ptr = root;
        while (ptr != nullptr) {
            if (data == ptr->data) return;
            prev = ptr;
            if (data < ptr->data)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        Node<T>* node = new Node<T>{ data, nullptr, nullptr };
        if (prev == nullptr)    // tree is empty!
            root = node;
        else if (data < prev->data)
            prev->left = node;
        else
            prev->right = node;
    }
    void remove(const T& data) {
        Node<T>* prev = nullptr;
        Node<T>* ptr = root;
        while (ptr != nullptr) {
            if (data == ptr->data) break;
            prev = ptr;
            if (data < ptr->data)
                ptr = ptr->left;
            else
                ptr = ptr->right;
        }
        if (ptr == nullptr) return; // data is not found

        // case 1: no child
        if (ptr->left == nullptr && ptr->right == nullptr) {        
            if (prev == nullptr) { root = nullptr; }
            else {
                if (prev->left == ptr) { prev->left = nullptr; }
                else { prev->right = nullptr; }
            }
        }
        // case 2: one child
        else if (ptr->left == nullptr || ptr->right == nullptr) {
            Node<T>* child = (ptr->left) ? ptr->left : ptr->right;
            if (prev == nullptr) { root = child; }
            else {
                if (prev->left == ptr) { prev->left = child; }
                else { prev->right = child; }
            }
        }
        // case 3: two children
        else {
            Node<T>* succ_prev = ptr;
            Node<T>* succ_ptr = ptr->right;
            while (succ_ptr->left != nullptr) {
                succ_prev = succ_ptr;
                succ_ptr = succ_ptr->left;
            }
            ptr->data = succ_ptr->data;
            if (succ_prev->left == succ_ptr) { succ_prev->left = succ_ptr->right; }
            else { succ_prev->right = succ_ptr->right; }
            ptr = succ_ptr;
        }
        delete ptr;
    }
};