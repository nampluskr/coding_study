### compolet binary tree 에 원소 삽입 (Q 이용)

```cpp
// https://www.geeksforgeeks.org/linked-complete-binary-tree-its-creation/
#include <cstdio>
#include <queue>
using namespace std;

struct Node {
	int data;
	Node* right;
	Node* left;
};

void insert(Node** root, int data, queue<Node*>* queue) {
	Node* node = new Node{ data, nullptr, nullptr };

	if (*root == nullptr) { *root = node; }
	else {
		Node* cur = queue->front();

		if (cur->left == nullptr) { cur->left = node; }
		else if (cur->right == nullptr) { cur->right = node; }

		if (cur != nullptr && cur->left != nullptr && cur->right != nullptr)
			queue->pop();
	}
	queue->push(node);
}

void levelOrder(Node* root) {
	queue<Node*> Q;
	Q.push(root);

	while (!Q.empty()) {
		Node* node = Q.front(); Q.pop();
		printf("%d ", node->data);

		if (node->left)
			Q.push(node->left);
		if (node->right)
			Q.push(node->right);
	}
}

int main()
{
	Node* root = nullptr;
	queue<Node*> Q;

	for (int i = 1; i <= 12; i++)
		insert(&root, i, &Q);

	levelOrder(root);

	return 0;
}
```
