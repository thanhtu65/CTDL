#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

// Cấu trúc Node dùng cho danh sách liên kết trong danh sách lân cận
struct Node {
    int vertex;
    Node* next;
};

// Hàm thêm cạnh vào danh sách lân cận
void addEdge(Node* adjList[], int src, int dest) {
    Node* newNode = new Node{ dest, adjList[src] };
    adjList[src] = newNode;
}

// Duyệt BFS (Duyệt theo chiều rộng) với ma trận lân cận
void BFS_Matrix(int graph[][100], int n, int start) {
    bool visited[100] = { false };
    queue<int> q;
    visited[start] = true;
    q.push(start);

    cout << "BFS (Matrix): ";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << char(u + 'a') << " ";

        for (int v = 0; v < n; v++) {
            if (graph[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << endl;
}

// Duyệt DFS (Duyệt theo chiều sâu) với ma trận lân cận
void DFS_Matrix(int graph[][100], int n, int start) {
    bool visited[100] = { false };
    stack<int> s;
    s.push(start);

    cout << "DFS (Matrix): ";
    while (!s.empty()) {
        int u = s.top();
        s.pop();

        if (!visited[u]) {
            visited[u] = true;
            cout << char(u + 'a') << " ";
        }

        // Duyệt các đỉnh kề theo thứ tự tăng dần (thêm vào stack theo thứ tự ngược lại)
        for (int v = n - 1; v >= 0; v--) {
            if (graph[u][v] == 1 && !visited[v]) {
                s.push(v);
            }
        }
    }
    cout << endl;
}

// Duyệt BFS (Duyệt theo chiều rộng) với danh sách lân cận
void BFS_List(Node* adjList[], int n, int start) {
    bool visited[100] = { false };
    queue<int> q;
    visited[start] = true;
    q.push(start);

    cout << "BFS (List): ";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << char(u + 'a') << " ";

        Node* temp = adjList[u];
        while (temp) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = true;
                q.push(temp->vertex);
            }
            temp = temp->next;
        }
    }
    cout << endl;
}

// Duyệt DFS (Duyệt theo chiều sâu) với danh sách lân cận
void DFS_List(Node* adjList[], int n, int start) {
    bool visited[100] = { false };
    stack<int> s;
    s.push(start);

    cout << "DFS (List): ";
    while (!s.empty()) {
        int u = s.top();
        s.pop();

        if (!visited[u]) {
            visited[u] = true;
            cout << char(u + 'a') << " ";
        }

        Node* temp = adjList[u];
        // Duyệt theo thứ tự tăng dần (thêm vào stack theo thứ tự ngược lại)
        stack<int> tempStack;
        while (temp) {
            if (!visited[temp->vertex]) {
                tempStack.push(temp->vertex);
            }
            temp = temp->next;
        }

        // Thêm các đỉnh vào stack để duyệt theo thứ tự tăng dần
        while (!tempStack.empty()) {
            s.push(tempStack.top());
            tempStack.pop();
        }
    }
    cout << endl;
}

// Nhập đồ thị theo ma trận lân cận
void inputGraphMatrix(int graph[][100], int& n) {
    cout << "Nhap so dinh cua do thi: ";
    cin >> n;

    cout << "Nhap ma tran lan can (0 hoac 1):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }
}

// Nhập đồ thị theo danh sách lân cận
void inputGraphList(Node* adjList[], int& n) {
    cout << "Nhap so dinh cua do thi: ";
    cin >> n;

    // Khởi tạo danh sách lân cận rỗng
    for (int i = 0; i < n; i++) {
        adjList[i] = nullptr;
    }

    int edges;
    cout << "Nhap so canh: ";
    cin >> edges;

    for (int i = 0; i < edges; i++) {
        int src, dest;
        cout << "Nhap canh " << i + 1 << " (dinh nguon, dinh dich): ";
        cin >> src >> dest;
        addEdge(adjList, src, dest);
    }
}

int main() {
    int graph[100][100];  // Ma trận lân cận
    Node* adjList[100];   // Danh sách lân cận
    int n, start;

    // Nhập đồ thị theo ma trận lân cận
    inputGraphMatrix(graph, n);
    cout << "Nhap dinh bat dau (0 -> " << n - 1 << "): ";
    cin >> start;

    BFS_Matrix(graph, n, start);
    DFS_Matrix(graph, n, start);

    // Nhập đồ thị theo danh sách lân cận
    inputGraphList(adjList, n);
    cout << "Nhap dinh bat dau (0 -> " << n - 1 << "): ";
    cin >> start;

    BFS_List(adjList, n, start);
    DFS_List(adjList, n, start);

    return 0;
}

