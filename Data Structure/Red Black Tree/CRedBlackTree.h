#pragma once
#include <iostream>

enum NODE_COLOR {
	RED = 0,
	BLACK = 1
};

struct ST_NODE {
	int key;
	//int value;
	ST_NODE* parent;
	ST_NODE* left;
	ST_NODE* right;

	NODE_COLOR color;
};

class CRedBlackTree {

private:
	ST_NODE* _pRoot = nullptr;
	ST_NODE NIL;
	ST_NODE* initNode(int key, ST_NODE* parent /*, int value*/) {
		ST_NODE* newNode = (ST_NODE*)malloc(sizeof(ST_NODE));
		newNode->key = key;
		//newNode->value = value;
		newNode->left = &NIL;
		newNode->right = &NIL;
		newNode->parent = parent;
		newNode->color = RED;
		return newNode;
	}
	unsigned int iSize = 0;

public:
	CRedBlackTree() {
		NIL.left = nullptr;
		NIL.right = nullptr;
		NIL.parent = nullptr;
		NIL.color = BLACK;
	}

	~CRedBlackTree() {
		clear(_pRoot);
	}

	void clear(ST_NODE* root) {
		if (!root)
			return;

		if (root->left != &NIL)
			clear(root->left);
		if (root->right != &NIL)
			clear(root->right);
		free(root);
	}

	void balance(ST_NODE* curr) {
		ST_NODE* ParentNode = curr->parent;
		// ������ node�� �θ� RED���
		if (ParentNode->color == RED && curr->color == RED)
		{
			// �θ��� ���� ����� ���� Ȯ��
			ST_NODE* PSiblingNode = &NIL;
			ST_NODE* PParentNode = ParentNode->parent;
			if (PParentNode->left == ParentNode)
				PSiblingNode = PParentNode->right;
			else if (PParentNode->right == ParentNode)
				PSiblingNode = PParentNode->left;

			// �θ��� ���� ��尡 RED���
			if (PSiblingNode->color == RED)
			{
				ParentNode->color = BLACK;
				PSiblingNode->color = BLACK;
				PParentNode->color = RED;

				if (PParentNode != _pRoot)
					if (PParentNode->parent->color == RED)
						balance(PParentNode);
			} // �θ��� ���� ��尡 BLACK�̶��
			else {
				// �θ� ���θ��� ���� �����
				if (PParentNode->left = ParentNode) {
					// ���� ��尡 �θ��� ������ �����
					if (ParentNode->right == curr) {
						// �θ� ���� ��ȸ��
						rotateLeft(ParentNode);
						curr = ParentNode; // ���� Parent�� curr��
						ParentNode = ParentNode->parent; // ���� Curr
						PParentNode = ParentNode->parent; // ���� Curr�� �θ� ���θ� �Ǿ����Ƿ�
					}
					// �ٽ� ��ȸ��
					rotateRight(ParentNode);
					NODE_COLOR temp = ParentNode->color;
					ParentNode->color = PParentNode->color;
					PParentNode->color = temp;

				}
				// �θ� ���θ��� ������ �����
				else if (PParentNode->right = ParentNode) {
					// ���� ��尡 �θ��� ���� �����
					if (ParentNode->left == curr) {
						// �θ� ���� ��ȸ��
						rotateRight(ParentNode);
						curr = ParentNode; // ���� Parent�� curr��
						ParentNode = ParentNode->parent; // ���� Curr
						PParentNode = ParentNode->parent; // ���� Curr�� �θ� ���θ� �Ǿ����Ƿ�
					}
					// �ٽ� ��ȸ��
					rotateLeft(ParentNode);
					NODE_COLOR temp = ParentNode->color;
					ParentNode->color = PParentNode->color;
					PParentNode->color = temp;
				}
			}
		}
		// ��Ʈ ��带 ������ ����
		_pRoot->color = BLACK;
	}

	void rotateLeft(ST_NODE* curr) {
		ST_NODE* currLeftNode = curr->left;
		ST_NODE* currRightNode = curr->right;
		ST_NODE* currParentNode = curr->parent;

		if (currParentNode->left == curr)
		{
			// curr ��尡 ��������
			currParentNode->left = currRightNode;
			curr->parent = currRightNode;
			curr->right = currRightNode->left;
			currRightNode->parent = currParentNode;
			currRightNode->left = curr;
		}
		if (currParentNode->right == curr)
		{
			// curr ��尡 �ö󰣴�
			currParentNode->right = currLeftNode;
			currLeftNode->parent = currParentNode;
			curr->parent = currParentNode->parent;
			curr->left = currParentNode;
			currParentNode->parent = curr;
			
			if (_pRoot == currParentNode)
				_pRoot = curr;
		}
	}

	void rotateRight(ST_NODE* curr) {
		ST_NODE* currRightNode = curr->right;
		ST_NODE* currLeftNode = curr->left;
		ST_NODE* currParentNode = curr->parent;

		if (currParentNode->left == curr)
		{
			// curr ��尡 �ö󰣴�
			currParentNode->left = currRightNode;
			currRightNode->parent = currParentNode;
			curr->parent = currParentNode->parent;
			curr->right = currParentNode;
			currParentNode->parent = curr;

			if (_pRoot == currParentNode)
				_pRoot = curr;
		}
		if (currParentNode->right == curr)
		{
			// curr ��尡 ��������
			currParentNode->right = currLeftNode;
			curr->parent = currLeftNode;
			curr->left = currLeftNode->right;
			currLeftNode->parent = currParentNode;
			currLeftNode->right = curr;
		}
	}

	bool insertNode(int key, ST_NODE* curr = nullptr) {
		if (!curr)
			curr = _pRoot;

		// ��Ʈ�� ���ٸ�
		// ù ��带 ��Ʈ�� ����

		if (!_pRoot) {
			_pRoot = initNode(key, nullptr);
			_pRoot->color = BLACK;
			iSize++;
			return true;
		}

		// �θ� �ִٸ�, ���� curr�� �� ����� �θ� �ȴ�
		// �θ��� key���� ���� ���� Ȥ�� ������ �ڽ����� ���Ѵ�

		if (curr->key > key)
			if (curr->left == &NIL) {
				// �θ� key���� �۰�, �θ� ���ڽ��� ������ ���� ������ �װ����� ���Ѵ�
				curr->left = initNode(key, curr);
				iSize++;
				balance(curr->left);
				return true;
			}
			else return insertNode(key, curr->left); // ���ڽ��� ������ �ش� ���ڽ����� curr�� �Ѱ� �ٽ� �˻�
		else {
			if (curr->right == &NIL) {
				// �θ� key���� ũ�ų� ����, �����ڽ��� ������ ���� ������ �װ����� ���Ѵ�
				curr->right = initNode(key, curr);
				iSize++;
				balance(curr->right);
				return true;
			}
			else return insertNode(key, curr->right); // �����ڽ��� ������ �ش� �����ڽ����� curr�� �Ѱ� �ٽ� �˻�
		}
	}

	ST_NODE* getNode(int key, ST_NODE* curr = nullptr) {
		if (!curr)
			curr = _pRoot;

		// ��Ʈ ��尡 ������ �� Ʈ��
		if (!_pRoot)
			return nullptr;

		if (curr->right)
			if (curr->right->key == key)
				return getNode(key, curr->right);
		if (curr->key == key)
			return curr;
		else {
			if (curr->key > key)
				if (curr->left)
					return getNode(key, curr->left);
				else return nullptr;
			else
				if (curr->right)
					return getNode(key, curr->right);
				else return nullptr;
		}
	}

	bool deleteNode(int key, ST_NODE* curr = nullptr) {
		if (!curr)
			curr = _pRoot;

		// ��Ʈ ��尡 ������ �� Ʈ���̹Ƿ� ������ �� �ִ� ��� ����
		if (!_pRoot)
			return false;

		ST_NODE* target = getNode(key);

		// ã�� ��尡 ������ ���
		if (target)
		{
			// ���� ��尡 ��Ʈ ����� ���
			if (target == _pRoot)
			{
				// ��Ʈ ��常 ���� ���
				if (!(target->left || target->right)) {
					_pRoot = nullptr;
					free(target);
					return true;
				}

				// ��Ʈ ��忡�� �ڽ��� �ִ� ���
				if (target->left) {
					ST_NODE* instead = getMaxSubTree(target->left);

					// ���� Ʈ�� �� �ִ밪�� ��Ʈ ����� ���� �ڽ��̶��
					// ���� �ڽĿ��Դ� ������ �ڽ��� ������ �ڸ��ϹǷ� �ش� ��� ��ü�� ��Ʈ�� ��´�
					if (instead == target->left)
					{
						instead->right = target->right;
						_pRoot = instead;
						free(target);
						return true;
					}
					else {
						if (instead->parent->left == instead)
							instead->parent->left = nullptr;
						else if (instead->parent->right == instead)
							instead->parent->right = nullptr;
						else return false;

						target->key = instead->key;
						free(instead);
						return true;
					}
				}
				else {
					_pRoot = target->right;
					free(target);
					return true;
				}
			}

			// ���� ����� �ڽ��� ���� ���
			if (!(target->left || target->right)) {
				if (target->parent->left == target)
					target->parent->left = nullptr;
				else if (target->parent->right == target)
					target->parent->right = nullptr;
				else return false;
				free(target);
				return true;
			}

			// ���� ����� �ڽ��� 1���� ���
			// ���� ����� �ڽ��� 2���� ���
			// �������� �ʰ� ���ڽ��� ������ max���� �켱������ ������ ��ġ
			// ���ڽ��� ������ �����ڽĿ��� min�� �����ͼ� ��ġ

			if (target->left)
			{
				ST_NODE* instead = getMaxSubTree(target->left);

				if (instead->parent->left == instead)
					instead->parent->left = nullptr;
				else if (instead->parent->right == instead)
					instead->parent->right = nullptr;
				else return false;

				target->key = instead->key;
				free(instead);
				return true;

			}
			else if (target->right) {

				ST_NODE* temp = target;

				if (target->parent->left == target)
					target->parent->left = target->right;
				else if (target->parent->right == target)
					target->parent->right = target->right;

				target->right->parent = target->parent;
				target = target->right;

				free(temp);
				return true;

			}
			else return false;
		}

		return false;
	}

	ST_NODE* getMaxSubTree(ST_NODE* root) {
		if (root->right)
			return getMaxSubTree(root->right);
		else {
			return root;
		}
	}

	void printPreorder(ST_NODE* root) {
		if (!root)
			return;

		std::cout << root->key << " ";
		if (root->left)
			printPreorder(root->left);
		if (root->right)
			printPreorder(root->right);
	}

	void printInorder(ST_NODE* root) {
		if (!root)
			return;

		if (root->left)
			printInorder(root->left);
		std::cout << root->key << " ";
		if (root->right)
			printInorder(root->right);
	}

	void printPostorder(ST_NODE* root) {
		if (!root)
			return;

		if (root->left)
			printPostorder(root->left);
		if (root->right)
			printPostorder(root->right);
		std::cout << root->key << " ";
	}

	ST_NODE* getRoot()
	{
		return _pRoot;
	}
};