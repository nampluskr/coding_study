### [bst] recursive

```cpp
class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None


class BinarySearchTree_recur:
    def __init__(self, root=None):
        self.root = root

    def find(self, data):
        return self.find_recur(self.root, data)

    def insert(self, data):
        self.root = self.insert_recur(self.root, data)

    def remove(self, data):
        self.root = self.remove_recur(self.root, data)

    def find_recur(self, node, data):
        if node is None:
            return None
        if data == node.data:
            return node
        if data < node.data:
            return self.find_recur(node.left, data)
        else:
            return self.find_recur(node.right, data)

    def insert_recur(self, node, data):
        if node is None:
            return Node(data)
        if data == node.data:
            return node
        if data < node.data:
            node.left = self.insert_recur(node.left, data)
        elif data > node.data:
            node.right = self.insert_recur(node.right, data)
        return node

    def find_min(self, node):
        if (node.left is None):
            return node
        return self.find_min(node.left)

    def remove_recur(self, node, data):
        if node is None:
            return None
        if data == node.data:
            if node.left is None and node.right is None:
                del node
                return None
            elif node.right is None:
                temp = node.left
                del node
                return temp
            elif node.left is None:
                temp = node.right
                del node
                return temp
            else:
                succ = self.find_min(node.right)
                node.data = succ.data
                node.right = self.remove_recur(node.right, succ.data)

        if data < node.data:
            node.left = self.remove_recur(node.left, data)
        elif data > node.data:
            node.right = self.remove_recur(node.right, data)
        return node


def inorder(node):
    if node is None:
        return
    inorder(node.left)
    print(f"{node.data}", end=' ')
    inorder(node.right)


if __name__ == '__main__':

    bst = BinarySearchTree_recur()
    bst.insert(50)
    bst.insert(30)
    bst.insert(20)
    bst.insert(40)
    bst.insert(70)
    bst.insert(60)
    inorder(bst.root)

    print("\nDelete a Leaf Node: 20")
    bst.remove(20)
    print("Modified BST tree after deleting Leaf Node:")
    inorder(bst.root)

    print("\nDelete Node with single child: 70")
    bst.remove(70)
    print("Modified BST tree after deleting single child Node:")
    inorder(bst.root)

    print("\nDelete Node with both child: 50")
    bst.remove(50)
    print("Modified BST tree after deleting both child Node:")
    inorder(bst.root)

```

### [bst] iterative

```cpp
class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None


class BinarySearchTree_iter:
    def __init__(self):
        self.root = None

    def find(self, data):
        node = self.root
        while node is not None:
            if data == node.data:
                return node
            if data < node.data:
                node = node.left
            else:
                node = node.right
        return None

    def insert(self, data):
        prev, node = None, self.root
        while node is not None:
            if data == node.data:
                return node
            prev = node
            if data < node.data:
                node = node.left
            else:
                node = node.right

        new_node = Node(data)
        if prev is None:
            self.root = new_node
        elif data < prev.data:
            prev.left = new_node
        else:
            prev.right = new_node

    def remove(self, data):
        prev, node = None, self.root
        while node is not None:
            if data == node.data:
                break

            prev = node
            if data < node.data:
                node = node.left
            else:
                node = node.right

        if node is None:
            return

        if node.left is None and node.right is None:
            if prev is None:
                self.root = None
            elif prev.left is node:
                prev.left = None
            else: prev.right = None
        elif node.right is None:
            if prev is None:
                self.root = node.left
            elif prev.left is node:
                prev.left = node.left
            else:
                prev.right = node.left
        elif node.left is None:
            if prev is None:
                self.root = node.right
            elif prev.left is node:
                prev.left = node.right
            else:
                prev.right = node.right
        else:
            succ_prev, succ = node, node.right
            while succ.left is not None:
                succ_prev, succ = node, succ.left

            node.data = succ.data
            if succ_prev.left is succ:
                succ_prev.left = succ.right
            else:
                succ_prev.right = succ.right
            node = succ
        del node


def inorder(node):
    if node is None:
        return
    inorder(node.left)
    print(f"{node.data}", end=' ')
    inorder(node.right)

if __name__ == "__main__":

    bst = BinarySearchTree_iter()
    bst.insert(50)
    bst.insert(30)
    bst.insert(20)
    bst.insert(40)
    bst.insert(70)
    bst.insert(60)
    inorder(bst.root)

    print("\nDelete a Leaf Node: 20")
    bst.remove(20)
    print("Modified BST tree after deleting Leaf Node:")
    inorder(bst.root)

    print("\nDelete Node with single child: 70")
    bst.remove(70)
    print("Modified BST tree after deleting single child Node:")
    inorder(bst.root)

    print("\nDelete Node with both child: 50")
    bst.remove(50)
    print("Modified BST tree after deleting both child Node:")
    inorder(bst.root)
```

### [ordered linked lit] recursive

```cpp
class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

class OrderedLinkedList_recur:
    def __init__(self):
        self.head = None

    def find(self, data):
        return self.find_recur(self.head, data)

    def insert(self, data):
        self.head = self.insert_recur(self.head, data)

    def remove(self, data):
        self.head = self.remove_recur(self.head, data)

    def find_recur(self, node, data):
        if node is None:
            return None
        if data == node.data:
            return node
        if data < node.data:
            return self.find_recur(node.next, data)
        else:
            return None

    def insert_recur(self, node, data):
        if node is None:
            return Node(data)
        if data == node.data:
            return node
        if data < node.data:
            node.next = self.insert_recur(node.next, data)
        else:
            node = Node(data, next=node)
        return node

    def remove_recur(self, node, data):
        if node is None:
            return None
        if data == node.data:
            temp = node
            if node.next is None:
                node = None
            else:
                node = node.next
            del temp
            return node

        if data < node.data:
            node.next = self.remove_recur(node.next, data)
        else:
            pass
        return node

def inorder(node):
    if node is None:
        return
    print(f"{node.data}", end=' ')
    inorder(node.next)


if __name__ == "__main__":

    sll = OrderedLinkedList_recur()
    sll.insert(30)
    sll.insert(20)
    sll.insert(50)
    sll.insert(10)
    sll.insert(40)
    inorder(sll.head)

    print("\n>>Delete 40:")
    sll.remove(40)
    inorder(sll.head)

    print("\n>>Delete 30:")
    sll.remove(30)
    inorder(sll.head)

    print("\n>>Delete 50:")
    sll.remove(50)
    inorder(sll.head)
```

### [ordered linked lit] iterative

```cpp
class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

class OrderedLinkedList_iter:
    def __init__(self):
        self.head = None

    def find(self, data):
        node = self.head
        while node is not None:
            if data == node.data:
                return node
            if data < node.data:
                node = node.next
            else:
                break
        return None

    def insert(self, data):
        prev, node = None, self.head
        while node is not None:
            if data == node.data:
                return
            if data < node.data:
                prev, node = node, node.next
            else:
                break

        new_node = Node(data, next=node)
        # prev    node
        # None [-] 30   <-- 40
        if prev is None:
            self.head = new_node
        # prev node
        # 50 [-] 30 <-- 40
        else:
            prev.next = new_node

    def remove(self, data):
        prev, node = None, self.head
        while node is not None:
            if data == node.data:
                break
            if data < node.data:
                prev, node = node, node.next
            else:
                pass

        if node is None:                # Not found!
            return
        if node.next is None:
            if prev is None:
                self.head = None
            else:
                prev.next = None
        else:
            if prev is None:
                self.head = node.next
            else:
                prev.next = node.next
        del node
        # prev  node
        # None  [30] - 20  <-- remove

        # prev node
        # 50 [30] - 20 <-- remove


def inorder(node):
    if node is None:
        return
    print(f"{node.data}", end=' ')
    inorder(node.next)


if __name__ == "__main__":

    sll = OrderedLinkedList_iter()
    sll.insert(30)
    sll.insert(20)
    sll.insert(50)
    sll.insert(10)
    sll.insert(40)
    inorder(sll.head)

    print("\n>>Delete 40:")
    sll.remove(40)
    inorder(sll.head)

    print("\n>>Delete 30:")
    sll.remove(30)
    inorder(sll.head)

    print("\n>>Delete 50:")
    sll.remove(50)
    inorder(sll.head)
```

### [unordered linked lit] recursive

```cpp
class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

class LinkedList_recur:
    def __init__(self):
        self.head = None

    def find(self, data):
        return self.find_recur(self.head, data)

    def insert(self, data):
        self.head = self.insert_recur(self.head, data)

    def remove(self, data):
        self.head = self.remove_recur(self.head, data)

    def find_recur(self, node, data):
        if node is None:
            return None
        if data == node.data:
            return node
        return self.find_recur(node.next, data)

    def insert_recur(self, node, data):
        if node is None:
            return Node(data)
        if data == node.data:
            return node

        node.next = self.insert_recur(node.next, data)
        return node

    def remove_recur(self, node, data):
        if node is None:
            return None
        if data == node.data:
            temp = node
            if node.next is None:
                node = None
            else:
                node = node.next
            del temp
            return node

        node.next = self.remove_recur(node.next, data)
        return node

def inorder(node):
    if node is None:
        return
    print(f"{node.data}", end=' ')
    inorder(node.next)


if __name__ == "__main__":

    sll = LinkedList_recur()
    sll.insert(30)
    sll.insert(20)
    sll.insert(50)
    sll.insert(10)
    sll.insert(40)
    inorder(sll.head)

    print("\n>>Delete 40:")
    sll.remove(40)
    inorder(sll.head)

    print("\n>>Delete 30:")
    sll.remove(30)
    inorder(sll.head)

    print("\n>>Delete 50:")
    sll.remove(50)
    inorder(sll.head)
```

### [unordered linked lit] iterative

```cpp
class Node:
    def __init__(self, data, next=None):
        self.data = data
        self.next = next

class LinkedList_iter:
    def __init__(self):
        self.head = None

    def find(self, data):
        node = self.head
        while node is not None:
            if data == node.data:
                return node
            node = node.next
        return None

    def insert(self, data):
        prev, node = None, self.head
        while node is not None:
            if data == node.data:
                return
            prev, node = node, node.next

        new_node = Node(data)
        if prev is None:
            self.head = new_node
        else:
            prev.next = new_node

    def remove(self, data):
        prev, node = None, self.head
        while node is not None:
            if data == node.data:
                break
            prev, node = node, node.next

        if node is None:                # Not found!
            return
        if node.next is None:
            if prev is None:
                self.head = None
            else:
                prev.next = None
        else:
            if prev is None:
                self.head = node.next
            else:
                prev.next = node.next
        del node


def inorder(node):
    if node is None:
        return
    print(f"{node.data}", end=' ')
    inorder(node.next)


if __name__ == "__main__":

    sll = LinkedList_iter()
    sll.insert(30)
    sll.insert(20)
    sll.insert(50)
    sll.insert(10)
    sll.insert(40)
    inorder(sll.head)

    print("\n>>Delete 40:")
    sll.remove(40)
    inorder(sll.head)

    print("\n>>Delete 30:")
    sll.remove(30)
    inorder(sll.head)

    print("\n>>Delete 50:")
    sll.remove(50)
    inorder(sll.head)
```
