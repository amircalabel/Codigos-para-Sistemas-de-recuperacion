#include <bits/stdc++.h>
using namespace std;

class node {
public:
    char value;
    node* left;
    node* right;
    node* next = NULL;
    node(char c)
    {
        this->value = c;
        left = NULL;
        right = NULL;
    }
    node()
    {
        left = NULL;
        right = NULL;
    }
    friend class Stack;
    friend class expression_tree;
};

class Stack {
    node* head = NULL;
 
public:
    void push(node*);
    node* pop();
    friend class expression_tree;
};

class expression_tree {
public:
    void inorder(node* x)
    {
        if (x == NULL)
            return;
        else {
            inorder(x->left);
            cout << x->value << "  ";
            inorder(x->right);
        }
    }
    
    node* buildTreeFromInorder(const string& inorder) {
        stack<node*> operators;
        stack<node*> operands;

        for (char c : inorder) {
            if (isOperator(c)) {
                while (!operators.empty() && precedence(operators.top()->value) >= precedence(c)) {
                    node* op = operators.top();
                    operators.pop();
                    node* right = operands.top();
                    operands.pop();
                    node* left = operands.top();
                    operands.pop();
                    op->left = left;
                    op->right = right;
                    operands.push(op);
                }
                operators.push(new node(c));
            } else {
                operands.push(new node(c));
            }
        }

        while (!operators.empty()) {
            node* op = operators.top();
            operators.pop();
            node* right = operands.top();
            operands.pop();
            node* left = operands.top();
            operands.pop();
            op->left = left;
            op->right = right;
            operands.push(op);
        }

        return operands.top();
    }

private:
    bool isOperator(char c) {
        return (c == '&' || c == '|');
    }

    int precedence(char op) {
        if (op == '|')
            return 1;
        if (op == '&')
            return 2;
        return 0;
    }
};
 
void Stack::push(node* x)
{
    if (head == NULL) {
        head = x;
    } else {
        x->next = head;
        head = x;
    }
}

node* Stack::pop()
{
    node* p = head;
    head = head->next;
    return p;
}

int main()
{
    string s = "A&B|C";
    // If you wish to take input from user:
    // cout << "Insert Inorder Expression: " << endl;
    // cin >> s;
    
    expression_tree et;
    node* root = et.buildTreeFromInorder(s);
    
    cout << "The Inorder Traversal of Expression Tree: ";
    et.inorder(root);
    return 0;
}
