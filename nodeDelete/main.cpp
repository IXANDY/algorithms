#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <set>
#include <stack>

struct Node {

    Node* right;
    Node* left;
    Node* previous;

    int value;
};

void addNode(Node* head, Node* vertToPlace) {

    Node* tempHead = head;

    while (tempHead) {

        if (tempHead->value > vertToPlace->value) {

            if (tempHead->left == nullptr) {

                vertToPlace->previous = tempHead;
                tempHead->left = vertToPlace;

                break;
            }
            else {

                vertToPlace->previous = tempHead;
                tempHead = tempHead->left;
            }
            continue;
        }
        if (tempHead->value < vertToPlace->value) {

            if (tempHead->right == nullptr) {

                vertToPlace->previous = tempHead;
                tempHead->right = vertToPlace;

                break;
            }
            else {

                vertToPlace->previous = tempHead;
                tempHead = tempHead->right;
            }
            continue;
        }
        else {

            break;
        }

    }
}

void coutTree(Node* head, std::ofstream& cout) {

    if (head) {

        cout << head->value << std::endl;
        coutTree(head->left, cout);
        coutTree(head->right, cout);
    }
}

Node* findNode(Node* head, int num) {

    Node* tempHead = head;

    while (tempHead) {

        if (num > tempHead->value) {

            tempHead = tempHead->right;
            continue;
        }
        if (num < tempHead->value) {

            tempHead = tempHead->left;
        }
        else return tempHead;
    }

    return nullptr;
}

Node* deleteNode(Node* nodeDel, Node* head) {

    if (!nodeDel->right && !nodeDel->left) {

        if (nodeDel->previous->left == nodeDel)
            nodeDel->previous->left = nullptr;
        else
            nodeDel->previous->right = nullptr;

        delete nodeDel;
        return head;
    }

    if (!nodeDel->left || !nodeDel->right) {

        if (nodeDel == head) {

            if (nodeDel->right)
                head = nodeDel->right;
            else
                head = nodeDel->left;
        }
        else {

            if (nodeDel->previous->right == nodeDel) {

                if (nodeDel->left)
                    nodeDel->previous->right = nodeDel->left;
                else
                    nodeDel->previous->right = nodeDel->right;
            }
            else {

                if (nodeDel->left)
                    nodeDel->previous->left = nodeDel->left;
                else
                    nodeDel->previous->left = nodeDel->right;
            }
        }

        delete nodeDel;
        return head;
    }

    Node* tempHead = nodeDel->right;
    while (tempHead) {

        if (tempHead->left)
            tempHead = tempHead->left;
        else
            break;
    }

    if (nodeDel == head) {

        if (tempHead == nodeDel->right) {

            tempHead->left = nodeDel->left;
            head = tempHead;
        }
        else {

            tempHead->previous->left = tempHead->right;
            tempHead->right = nodeDel->right;
            tempHead->left  = nodeDel->left;
            head = tempHead;
        }
    }
    else {

        if (nodeDel->previous->right == nodeDel)
            nodeDel->previous->right = tempHead;
        else
            nodeDel->previous->left = tempHead;

        if (tempHead == nodeDel->right) {

            tempHead->left = nodeDel->left;
        }
        else {

            tempHead->previous->left = tempHead->right;
            tempHead->right = nodeDel->right;
            tempHead->left  = nodeDel->left;
        }
    }

    delete nodeDel;
    return head;
}

int main() {

    std::ifstream cin("input.txt");
    std::ofstream cout("output.txt");

    Node* head = new Node;

    int numToDel;
    cin >> numToDel;

    head->previous = nullptr;
    head->left = nullptr;
    head->right = nullptr;
    cin >> head->value;

    while (!cin.eof()) {

        int num;
        cin >> num;

        Node* temp = new Node;

        temp->left = nullptr;
        temp->right = nullptr;
        temp->value = num;

        addNode(head, temp);
    }

    Node* nodeToDel = findNode(head, numToDel);
    if (nodeToDel)
        head = deleteNode(nodeToDel, head);

    coutTree(head, cout);

    return 0;
}