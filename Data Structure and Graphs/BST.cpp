//https://vjudge.net/problem/SPOJ-BST1

#include<bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};

Node* insert(Node* root, int x) {
    if (root == NULL) {
        root = new Node(x);
    } else if (x < root->val) {
        root->left = insert(root->left, x);
    } else {
        root->right = insert(root->right, x);
    }
    return root;
}

void preorder(Node* root) {
    if(root == NULL) return;

    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if(root == NULL) return;

    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

void postorder(Node* root) {
    if(root == NULL) return;

    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int val) {
    if (root == NULL) {
        return root;
    }
    if (val < root->val) {
        root->left = deleteNode(root->left, val);
    } else if (val > root->val) {
        root->right = deleteNode(root->right, val);
    } else {
        // Node found
        if (root->left == NULL) {
            // Node with only right child or no child
            Node* temp = root->right;
            delete root; // delete current node
            return temp; // replace current node by right child
        } else if (root->right == NULL) {
            // Node with only left child or no child
            Node* temp = root->left;
            delete root; // delete current node
            return temp; // replace current node by left child
        } else {
            // Node with two children
            Node* temp = findMin(root->right);  // Find the inorder successor
            root->val = temp->val;  // Copy the inorder successor's value to the node
            root->right = deleteNode(root->right, temp->val);  // Delete the inorder successor
        }
    }
    return root;
}

bool find(Node* root, int val) {
    if (root == NULL) {
        return 0; // Value not found
    }
    if (root->val == val) {
        return 1; // Value found
    } else if (val < root->val) {
        return find(root->left, val);
    } else {
        return find(root->right, val);
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    Node* root = NULL;
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        root = insert(root, x);
    }
    string s; cin >> s;
    if(s == "pre") {
        preorder(root);
        cout << "\n";
    } else if(s == "post") {
        postorder(root);
        cout << "\n";
    } else if(s == "in") {
        inorder(root);
        cout << "\n";
    }
    return 0;
}
