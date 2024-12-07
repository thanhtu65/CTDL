#include <iostream>
#include <sstream>
#include <stack>
#include <cctype>
using namespace std;

// Cấu trúc một nút trong cây biểu thức
struct Node {
    string data; // Dữ liệu của nút (toán tử hoặc toán hạng)
    Node* left;  // Con trỏ đến nút con trái
    Node* right; // Con trỏ đến nút con phải

    // Hàm tạo nút mới
    Node(string value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Hàm kiểm tra xem cây có rỗng không
bool isEmpty(Node* root) {
    return root == nullptr;
}

// Hàm kiểm tra xem một chuỗi có phải toán tử không
bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
}

// Hàm xác định độ ưu tiên của toán tử
int precedence(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

// Hàm tạo cây từ biểu thức trung tố (Infix)
Node* Tree(const string& infix) {
    stack<Node*> nodes;
    stack<string> operators;
    istringstream iss(infix);
    string token;

    while (iss >> token) {
        if (isalnum(token[0]) || token.size() > 1) { // Nếu là toán hạng (biến hoặc số)
            nodes.push(new Node(token));
        }
        else if (token == "(") {
            operators.push(token);
        }
        else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                string op = operators.top();
                operators.pop();

                Node* right = nodes.top(); nodes.pop();
                Node* left = nodes.top(); nodes.pop();

                Node* node = new Node(op);
                node->left = left;
                node->right = right;

                nodes.push(node);
            }
            operators.pop(); // Bỏ dấu '('
        }
        else if (isOperator(token)) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                string op = operators.top();
                operators.pop();

                Node* right = nodes.top(); nodes.pop();
                Node* left = nodes.top(); nodes.pop();

                Node* node = new Node(op);
                node->left = left;
                node->right = right;

                nodes.push(node);
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        string op = operators.top();
        operators.pop();

        Node* right = nodes.top(); nodes.pop();
        Node* left = nodes.top(); nodes.pop();

        Node* node = new Node(op);
        node->left = left;
        node->right = right;

        nodes.push(node);
    }

    return nodes.top();
}

// Hàm duyệt cây theo thứ tự Trung tố (Infix) không đệ quy
void inorder(Node* root) {
    if (root == nullptr) return;

    stack<Node*> s;
    Node* current = root;

    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        cout << current->data << " ";
        current = current->right;
    }
}

// Hàm duyệt cây theo thứ tự Tiền tố (Prefix) không đệ quy
void preorder(Node* root) {
    if (root == nullptr) return;

    stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        Node* current = s.top();
        s.pop();
        cout << current->data << " ";

        if (current->right != nullptr) s.push(current->right);
        if (current->left != nullptr) s.push(current->left);
    }
}

// Hàm duyệt cây theo thứ tự Hậu tố (Postfix) không đệ quy
void postorder(Node* root) {
    if (root == nullptr) return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* current = s1.top();
        s1.pop();
        s2.push(current);

        if (current->left != nullptr) s1.push(current->left);
        if (current->right != nullptr) s1.push(current->right);
    }

    while (!s2.empty()) {
        Node* current = s2.top();
        s2.pop();
        cout << current->data << " ";
    }
}

int main() {
    string infix;

    cout << "Nhập biểu thức trung tố (có dấu ngoặc nếu cần, các phần tử cách nhau bởi khoảng trắng): ";
    getline(cin, infix);

    Node* root = Tree(infix);

    if (isEmpty(root)) {
        cout << "Cây biểu thức rỗng!\n";
        return 0;
    }

    cout << "Biểu thức Trung tố (Infix): ";
    inorder(root);
    cout << endl;

    cout << "Biểu thức Tiền tố (Prefix): ";
    preorder(root);
    cout << endl;

    cout << "Biểu thức Hậu tố (Postfix): ";
    postorder(root);
    cout << endl;

    return 0;
}

















//#include <iostream>
//#include <sstream>
//#include <stack>
//#include <cctype>
//using namespace std;
//
//// Cấu trúc một nút trong cây biểu thức
//struct Node {
//    string data; // Dữ liệu của nút (toán tử hoặc toán hạng)
//    Node* left;  // Con trỏ đến nút con trái
//    Node* right; // Con trỏ đến nút con phải
//
//    // Hàm tạo nút mới
//    Node(string value) {
//        data = value;
//        left = nullptr;
//        right = nullptr;
//    }
//};
//
//// Hàm kiểm tra xem cây có rỗng không
//bool isEmpty(Node* root) {
//    return root == nullptr;
//}
//
//// Hàm kiểm tra xem một chuỗi có phải toán tử không
//bool isOperator(const string& s) {
//    return s == "+" || s == "-" || s == "*" || s == "/" || s == "^";
//}
//
//// Hàm xác định độ ưu tiên của toán tử
//int precedence(const string& op) {
//    if (op == "+" || op == "-") return 1;
//    if (op == "*" || op == "/") return 2;
//    if (op == "^") return 3;
//    return 0;
//}
//
//// Hàm tạo cây từ biểu thức trung tố (Infix)
//Node* buildExpressionTreeFromInfix(const string& infix) {
//    stack<Node*> nodes;
//    stack<string> operators;
//    istringstream iss(infix);
//    string token;
//
//    while (iss >> token) {
//        if (isalnum(token[0]) || token.size() > 1) { // Nếu là toán hạng (biến hoặc số)
//            nodes.push(new Node(token));
//        }
//        else if (token == "(") {
//            operators.push(token);
//        }
//        else if (token == ")") {
//            while (!operators.empty() && operators.top() != "(") {
//                string op = operators.top();
//                operators.pop();
//
//                Node* right = nodes.top(); nodes.pop();
//                Node* left = nodes.top(); nodes.pop();
//
//                Node* node = new Node(op);
//                node->left = left;
//                node->right = right;
//
//                nodes.push(node);
//            }
//            operators.pop(); // Bỏ dấu '('
//        }
//        else if (isOperator(token)) {
//            while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
//                string op = operators.top();
//                operators.pop();
//
//                Node* right = nodes.top(); nodes.pop();
//                Node* left = nodes.top(); nodes.pop();
//
//                Node* node = new Node(op);
//                node->left = left;
//                node->right = right;
//
//                nodes.push(node);
//            }
//            operators.push(token);
//        }
//    }
//
//    while (!operators.empty()) {
//        string op = operators.top();
//        operators.pop();
//
//        Node* right = nodes.top(); nodes.pop();
//        Node* left = nodes.top(); nodes.pop();
//
//        Node* node = new Node(op);
//        node->left = left;
//        node->right = right;
//
//        nodes.push(node);
//    }
//
//    return nodes.top();
//}
//
//// Hàm duyệt cây theo thứ tự Trung tố (Infix)
//void inorderTraversal(Node* root) {
//    if (root == nullptr) return;
//
//    if (root->left) cout << "(";
//    inorderTraversal(root->left);
//    cout << root->data;
//    inorderTraversal(root->right);
//    if (root->right) cout << ")";
//}
//
//// Hàm duyệt cây theo thứ tự Tiền tố (Prefix)
//void preorderTraversal(Node* root) {
//    if (root == nullptr) return;
//
//    cout << root->data << " ";
//    preorderTraversal(root->left);
//    preorderTraversal(root->right);
//}
//
//// Hàm duyệt cây theo thứ tự Hậu tố (Postfix)
//void postorderTraversal(Node* root) {
//    if (root == nullptr) return;
//
//    postorderTraversal(root->left);
//    postorderTraversal(root->right);
//    cout << root->data << " ";
//}
//
//int main() {
//    string infix;
//
//    cout << "Nhập biểu thức trung tố (có dấu ngoặc nếu cần, các phần tử cách nhau bởi khoảng trắng): ";
//    getline(cin, infix);
//
//    Node* root = buildExpressionTreeFromInfix(infix);
//
//    if (isEmpty(root)) {
//        cout << "Cây biểu thức rỗng!\n";
//        return 0;
//    }
//
//    cout << "Biểu thức Trung tố (Infix): ";
//    inorderTraversal(root);
//    cout << endl;
//
//    cout << "Biểu thức Tiền tố (Prefix): ";
//    preorderTraversal(root);
//    cout << endl;
//
//    cout << "Biểu thức Hậu tố (Postfix): ";
//    postorderTraversal(root);
//    cout << endl;
//
//    return 0;
//}
