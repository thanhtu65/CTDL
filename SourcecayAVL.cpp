#include<iostream>
#include<algorithm>
using namespace std;
// dinh nghia struct
struct Node {
	int data;
	int height;
	Node* left;
	Node* right;
};
// ham tao node moi
Node* createNode(int key) {
	Node* node = new Node();
	node->data = key;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}
// ham tinh chieu cao 
int getHeight(Node* node) {
	return node ? node->height : 0;
}
// ham tinh he so can bang
int getBalance(Node* node) {
	return node ? getHeight(node->left) - getHeight(node->right) : 0;
}
// ham xoay phai
Node* rotateRight(Node* y) {
	Node* x = y->left;
	Node* T3 = x->right;
	x->right = y;
	y->left = T3;
	y->height = 1 + max(getHeight(y->left), getHeight(y->right));
	x->height = 1 + max(getHeight(y->left), getHeight(y->right));
	return x;
}
// ham xoay trai
Node* rotateLeft(Node* x) {
	Node* y = x->right;
	Node* T2 = y->left;
	y->left = x;
	x->right = T2;

	x->height = 1 + max(getHeight(x->left), getHeight(x->right));
	y->height = 1 + max(getHeight(y->left), getHeight(y->right));

	return y;
}
// ham nhap node moi
Node* insertNode(Node* node, int key) {
	if (!node) return createNode(key);

	// Chèn vào nhánh trái nếu key nhỏ hơn node->data
	if (key < node->data)
		node->left = insertNode(node->left, key);
	// Chèn vào nhánh phải nếu key lớn hơn hoặc bằng node->data
	else
		node->right = insertNode(node->right, key);

	// Cập nhật chiều cao của node
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));

	// Tính toán hệ số cân bằng
	int balance = getBalance(node);

	// Kiểm tra các trường hợp mất cân bằng và thực hiện các phép xoay
	if (balance > 1 && key < node->left->data)
		return rotateRight(node);

	if (balance > 1 && key > node->left->data) {
		node->left = rotateLeft(node->left);
		return rotateRight(node);
	}

	if (balance < -1 && key < node->right->data) {
		node->right = rotateRight(node->right);
		return rotateLeft(node);
	}

	return node;
}

void preOrderTraversal(Node* root) {
	if (root) {
		cout << root->data << " ";
		preOrderTraversal(root->left);
		preOrderTraversal(root->right);
	}
}
void inOrderTraversal(Node* root) {
	if (root) {
		inOrderTraversal(root->left);
		cout << root->data << " ";
		inOrderTraversal(root->right);
	}
}
int main() {
	Node* root = nullptr;
	int n, key;

	cout << "Nhap so phan tu: ";
	cin >> n;
	cout << "Nhap cac phan tu: ";
	for (int i = 0; i < n; ++i) {
		cin >> key;
		root = insertNode(root, key);
	}

	cout << "Theo thu tu duyet truoc: ";
	preOrderTraversal(root);
	cout << endl;
	cout << "Theo thu tu duyet sau: ";
	inOrderTraversal(root);

	return 0;
}
