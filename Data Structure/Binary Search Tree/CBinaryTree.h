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

		// 루트가 없다면
		// 첫 노드를 루트로 설정

		if (!_pRoot) {
			_pRoot = initNode(key, nullptr);
			iSize++;
			return true;
		}

		// 부모가 있다면, 현재 curr가 새 노드의 부모가 된다
		// 부모의 key값과 비교해 왼쪽 혹은 오른쪽 자식으로 정한다

		if (curr->key > key)
			if (!(curr->left)) {
				// 부모 key보다 작고, 부모가 왼자식을 가지고 있지 않으면 그곳으로 정한다
				curr->left = initNode(key, curr);
				iSize++;
				return true;
			}
			else return insertNode(key, curr->left); // 왼자식이 있으면 해당 왼자식으로 curr을 넘겨 다시 검사
		else {
			if (!(curr->right)) {
				// 부모 key보다 크거나 같고, 오른자식을 가지고 있지 않으면 그곳으로 정한다
				curr->right = initNode(key, curr);
				iSize++;
				return true;
			}
			else return insertNode(key, curr->right); // 오른자식이 있으면 해당 오른자식으로 curr을 넘겨 다시 검사
		}
	}

	ST_NODE* getNode(int key, ST_NODE* curr = nullptr) {
		if (!curr)
			curr = _pRoot;

		// 루트 노드가 없으면 빈 트리
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

		// 루트 노드가 없으면 빈 트리이므로 삭제할 수 있는 노드 부재
		if (!_pRoot)
			return false;

		ST_NODE* target = getNode(key);
		
		// 찾는 노드가 존재할 경우
		if (target)
		{
			// 삭제 노드가 루트 노드일 경우
			if (target == _pRoot)
			{
				// 루트 노드만 있을 경우
				if (!(target->left || target->right)) {
					_pRoot = nullptr;
					free(target);
					return true;
				}

				// 루트 노드에게 자식이 있는 경우
				if (target->left) {
					ST_NODE* instead = getMaxSubTree(target->left);
					
					// 서브 트리 중 최대값이 루트 노드의 왼쪽 자식이라면
					// 왼쪽 자식에게는 오른쪽 자식이 없음이 자명하므로 해당 노드 자체를 루트로 삼는다
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

			// 삭제 노드의 자식이 없는 경우
			if (!(target->left || target->right)) {
				if (target->parent->left == target)
					target->parent->left = nullptr;
				else if (target->parent->right == target)
					target->parent->right = nullptr;
				else return false;
				free(target);
				return true;
			}

			// 삭제 노드의 자식이 1개인 경우
			// 삭제 노드의 자식이 2개인 경우
			// 구분하지 않고 왼자식이 있으면 max값을 우선적으로 가져와 대치
			// 왼자식이 없으면 오른자식에서 min값 가져와서 대치

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