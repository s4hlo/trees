#include <stdio.h>
#include <stdlib.h>

struct Node {

  int data;
  struct Node *left;
  struct Node *right;
};

struct Node *createNode(int data) {
  struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
  if (newNode == NULL) {
    printf("Memory error\n");
    return NULL;
  }

  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

void insert(struct Node *root, int data) {
  if (root == NULL) {
    root = createNode(data);
    return;
  }
  struct Node *queue[100];
  int front = 0, rear = 0;
  queue[rear++] = root;

  while (front < rear) {
    struct Node *current = queue[front++];

    if (current->left == NULL) {
      current->left = createNode(data);
      return;
    } else {
      queue[rear++] = current->left;
    }

    if (current->right == NULL) {
      current->right = createNode(data);
      return;
    } else {
      queue[rear++] = current->right;
    }
  }
}

void inorderTraversal(struct Node *root) {
  if (root != NULL) {
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
  }
}

void preorderTraversal(struct Node *root) {
  if (root != NULL) {
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
  }
}

void postorderTraversal(struct Node *root) {
  if (root != NULL) {
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
  }
}

struct Node *findMin(struct Node *root) {
  while (root && root->left != NULL) {
    root = root->left;
  }
  return root;
}

struct Node *deleteNode(struct Node *root, int key) {
  if (root == NULL)
    return root;

  // If the key to be deleted is smaller than the root's key, then it lies in
  // the left subtree
  if (key < root->data) {
    root->left = deleteNode(root->left, key);
  }
  // If the key to be deleted is greater than the root's key, then it lies in
  // the right subtree
  else if (key > root->data) {
    root->right = deleteNode(root->right, key);
  }
  // If key is the same as root's key, then this is the node to be deleted
  else {
    // Node with only one child or no child
    if (root->left == NULL) {
      struct Node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct Node *temp = root->left;
      free(root);
      return temp;
    }

    // Node with two children: get the inorder successor (smallest in the right
    // subtree)
    struct Node *temp = findMin(root->right);

    // Copy the inorder successor's content to this node
    root->data = temp->data;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->data);
  }
  return root;
}

int main() {
  struct Node *root = createNode(1);

  insert(root, 2);
  insert(root, 3);
  insert(root, 4);
  insert(root, 5);
  insert(root, 6);
  insert(root, 7);

  printf("In-order traversal: ");
  inorderTraversal(root);
  printf("\n");

  printf("Pre-order traversal: ");
  preorderTraversal(root);
  printf("\n");

  printf("Post-order traversal: ");
  postorderTraversal(root);
  printf("\n");

  // Deleting a node
  printf("Deleting node 3\n");
  root = deleteNode(root, 3);
  printf("In-order traversal after deletion: ");
  inorderTraversal(root);
  printf("\n");

  return 0;
}
