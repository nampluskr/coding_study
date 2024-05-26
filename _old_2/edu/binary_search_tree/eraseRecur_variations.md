## Recursive Erase Methods in Binary Search Tree

### No child / One child / Two Children

```cpp
    Node* eraseRecur(Node* cur, const T& data) {
        if (cur == nullptr) return nullptr;
        if (cur->data == data) {
            // Case 1: No child
            if (cur->left == nullptr && cur->right == nullptr) {
                delete cur;
                return nullptr;
            }
            // Case 2: One child
            else if (cur->left == nullptr || cur->right == nullptr) {
                Node* child = (cur->left != nullptr)? cur->left: cur->right;
                delete cur;
                return child;
            // Case 3: Two children
            } else {
                Node* min_node = findMin(cur->right);
                cur->data = min_node->data;
                cur->right = eraseRecur(cur->right, cur->data);
            }
        }
        if (data < cur->data) cur->left = eraseRecur(cur->left, data);
        else cur->right = eraseRecur(cur->right, data);
        return cur;
    }
```

### SWEA set

```cpp
    Node* eraseRecur(Node* cur, const T& data) {
        if (cur == nullptr) return nullptr;
        if (cur->data == data) {
            if (cur->left == nullptr) {
                Node *child = cur->right;
                delete cur;
                return child;
            }
            else if (cur->right == nullptr) {
                Node *child = cur->left;
                delete cur;
                return child;
            }
            Node* min_node = findMin(cur->right);
            cur->data = min_node->data;
            cur->right = eraseRecur(cur->right, cur->data);
        }
        if (data < cur->data) cur->left = eraseRecur(cur->left, data);
        else cur->right = eraseRecur(cur->right, data);
        return cur;
    }
```

### geeksforgeeks

- https://www.geeksforgeeks.org/deletion-in-binary-search-tree/

```cpp
    Node* eraseRecur(Node* cur, const T& data) {
        if (cur == nullptr) return nullptr;
        if (cur->data == data) {
            if (cur->left == nullptr) {
                Node *child = cur->right;
                delete cur;
                return child;
            }
            else if (cur->right == nullptr) {
                Node *child = cur->left;
                delete cur;
                return child;
            }
            Node* temp_prev = cur;
            Node* temp_cur = cur->right;
            while (temp_cur->left != nullptr) {
                temp_prev = temp_cur;
                temp_cur = temp_cur->left;
            }
            cur->data = temp_cur->data;
            if  (temp_prev->left == temp_cur) temp_prev->left = temp_cur->right;
            else temp_prev->right = temp_cur->right;
            delete temp_cur;
            return cur;
        }
        if (data < cur->data) cur->left = eraseRecur(cur->left, data);
        else cur->right = eraseRecur(cur->right, data);
        return cur;
    }
```

### Successor / Predecessor

- https://www.interviewbit.com/blog/delete-node-from-binary-search-tree/

```cpp
    Node* findMax(Node* cur) {
        if (cur->right == nullptr) return cur;
        return findMax(cur->right);
    }

    Node* eraseRecur(Node* cur, const T& data) {
        if (cur == nullptr) return nullptr;
        if (cur->data == data) {
           if (cur->left == nullptr && cur->right == nullptr){
               delete cur;
               return nullptr;
           }
           else if (cur->right != nullptr) {
               Node* min_node = findMin(cur->right);   // successor
               cur->data = min_node->data;
               cur->right = eraseRecur(cur->right, min_node->data);
           }
           else {  // (cur->left != nullptr)
               Node* max_node = findMax(cur->left);    // predecessor
               cur->data = max_node->data;
               cur->left = eraseRecur(cur->left, max_node->data);
           }
           return cur;
        }
        if (data < cur->data) cur->left = eraseRecur(cur->left, data);
        else cur->right = eraseRecur(cur->right, data);
        return cur;
    }
```