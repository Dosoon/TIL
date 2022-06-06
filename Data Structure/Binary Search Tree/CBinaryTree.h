#pragma once
#include <iostream>

struct ST_NODE {
	int key;
	//int value;
	ST_NODE* parent;
	ST_NODE* left;
	ST_NODE* right;
};

class CBinaryTree {

private:
	ST_NODE* _pRoot = nullptr;
	ST_NODE* initNode(int key, ST_NODE* parent /*, int value*/) {
		ST_NODE* newNode = (ST_NODE*)malloc(sizeof(ST_NODE));
		newNode->key = key;
		//newNode->value = value;
		newNode->left = nullptr;
		newNode->right = nullptr;
		newNode->parent = parent;
		return newNode;
	}
	unsigned int iSize = 0;

public:

	~CBinaryTree() {
		clear(_pRoot);
	}

	void clear(ST_NODE* root) {
		if (!root)
			return;

		if (root->left)
			clear(root->left);
		if (root->right)
			clear(root->right);
		free(root);
	}

	bool insertNode(int key, ST_NODE* curr = nullptr) {
		if (!curr)
			curr = _pRoot;

		// ��Ʈ�� ���ٸ�
		// ù ��带 ��Ʈ�� ����

		if (!_pRoot) {
			_pRoot = initNode(key, nullptr);
			iSize++;
			return true;
		}

		// �θ� �ִٸ�, ���� curr�� �� ����� �θ� �ȴ�
		// �θ��� key���� ���� ���� Ȥ�� ������ �ڽ����� ���Ѵ�

		if (curr->key > key)
			if (!(curr->left)) {
				// �θ� key���� �۰�, �θ� ���ڽ��� ������ ���� ������ �װ����� ���Ѵ�
				curr->left = initNode(key, curr);
				iSize++;
				return true;
			}
			else return insertNode(key, curr->left); // ���ڽ��� ������ �ش� ���ڽ����� curr�� �Ѱ� �ٽ� �˻�
		else {
			if (!(curr->right)) {
				// �θ� key���� ũ�ų� ����, �����ڽ��� ������ ���� ������ �װ����� ���Ѵ�
				curr->right = initNode(key, curr);
				iSize++;
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