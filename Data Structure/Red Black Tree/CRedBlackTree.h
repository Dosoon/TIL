#pragma once
#include <iostream>
#include <vector>

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
				if (PParentNode->left == ParentNode) {
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
					if (PParentNode)
					{
						ParentNode->color = PParentNode->color;
						PParentNode->color = temp;
					}
					else
						ParentNode->color = BLACK;

				}
				// �θ� ���θ��� ������ �����
				else if (PParentNode->right == ParentNode) {
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
					if (PParentNode)
					{
						ParentNode->color = PParentNode->color;
						PParentNode->color = temp;
					}
					else ParentNode->color = BLACK;
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

		if (!currParentNode)
		{
			// ��Ʈ ����� ���
			curr->right = currRightNode->left;
			currRightNode->left->parent = curr;

			currRightNode->left = curr;
			curr->parent = currRightNode;

			_pRoot = currLeftNode;
			return;
		}
		if (currParentNode->left == curr)
		{
			// curr ��尡 ��������
			currParentNode->left = currRightNode;
			curr->parent = currRightNode;
			curr->right = currRightNode->left;
			currRightNode->left->parent = curr;
			currRightNode->parent = currParentNode;
			currRightNode->left = curr;
		}
		else if (currParentNode->right == curr)
		{
			// curr ��尡 �ö󰣴�
			currParentNode->right = currLeftNode;
			currLeftNode->parent = currParentNode;
			curr->parent = currParentNode->parent;
			if (currParentNode->parent)
			{
				if (currParentNode->parent->left == currParentNode)
					currParentNode->parent->left = curr;
				if (currParentNode->parent->right == currParentNode)
					currParentNode->parent->right = curr;
			}
			curr->left = currParentNode;
			currParentNode->parent = curr;

			if (_pRoot == currParentNode)
				_pRoot = curr;
		}
		else {
			throw;
		}
	}

	void rotateRight(ST_NODE* curr) {
		ST_NODE* currRightNode = curr->right;
		ST_NODE* currLeftNode = curr->left;
		ST_NODE* currParentNode = curr->parent;

		if (!currParentNode)
		{
			// ��Ʈ ����� ���
			curr->left = currLeftNode->right;
			currLeftNode->right->parent = curr;

			currLeftNode->right = curr;
			curr->parent = currLeftNode;

			_pRoot = currLeftNode;
			return;
		}

		if (currParentNode->right == curr)
		{
			// curr ��尡 ��������
			currParentNode->right = currLeftNode;
			curr->parent = currLeftNode;
			curr->left = currLeftNode->right;
			currLeftNode->right->parent = curr;
			currLeftNode->parent = currParentNode;
			currLeftNode->right = curr;
		}
		else if (currParentNode->left == curr)
		{
			// curr ��尡 �ö󰣴�
			currParentNode->left = currRightNode;
			currRightNode->parent = currParentNode;
			curr->parent = currParentNode->parent;
			if (currParentNode->parent)
			{
				if (currParentNode->parent->left == currParentNode)
					currParentNode->parent->left = curr;
				if (currParentNode->parent->right == currParentNode)
					currParentNode->parent->right = curr;
			}
			curr->right = currParentNode;
			currParentNode->parent = curr;

			if (_pRoot == currParentNode)
				_pRoot = curr;
		}
		else {
			throw;
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

		if (curr->left != &NIL)
			if (curr->left->key == key)
				return getNode(key, curr->left);
		if (curr->right != &NIL)
			if (curr->right->key == key)
				return getNode(key, curr->right);
		if (curr->key == key)
			return curr;
		else {
			if (curr->key > key)
				if (curr->left != &NIL)
					return getNode(key, curr->left);
				else return nullptr;
			else
				if (curr->right != &NIL)
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
				if (!(target->left != &NIL || target->right != &NIL)) {
					_pRoot = nullptr;
					free(target);
					return true;
				}

				// �ڽ��� 1����� (���� Ȥ�� ������ �ڽĸ� �ִٸ�)
				// ���� �ڽ�
				if (target->left != &NIL && target->right == &NIL)
				{
					ST_NODE* childNode = target->left;
					childNode->parent = nullptr;
					_pRoot = childNode;
					_pRoot->color = BLACK;

					free(target);
					return true;
				}
				if (target->left == &NIL && target->right != &NIL)
				{
					ST_NODE* childNode = target->right;
					childNode->parent = nullptr;
					_pRoot = childNode;
					_pRoot->color = BLACK;

					free(target);
					return true;
				}
				// ���� ����� �ڽ��� 2�����
				if (target->left != &NIL && target->right != &NIL)
				{
					// �����Ϸ��� ����� ���� ����Ʈ�� �ִ밪�� ��ü ����
					ST_NODE* instead = getMaxSubTree(target->left);

					// ������ üũ
					// ���� ���� ����� �ڽ��� �ΰ���� ������ �� ����
					if (instead->left != &NIL && instead->right != &NIL)
						return false;

					// �� ����
					target->key = instead->key;

					// instead ��带 �������� �뷱�� ����

					balancingDelete(instead);
					return true;
				}

				// ��Ʈ ��忡�� �ڽ��� �ִ� ���
				/*if (target->left != &NIL) {
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
							instead->parent->left = &NIL;
						else if (instead->parent->right == instead)
							instead->parent->right = &NIL;
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
				}*/
			}


			// ���� ��尡 �ڽ��� ���ų� 1��
			// ���ٸ�
			if (!(target->left != &NIL || target->right != &NIL)) {
				/*if (target->parent->left == target)
					target->parent->left = &NIL;
				else if (target->parent->right == target)
					target->parent->right = &NIL;
				else return false;*/
				balancingDelete(target);
				return true;
			}
			// �ڽ��� 1����� (���� Ȥ�� ������ �ڽĸ� �ִٸ�)
			if (target->left != &NIL && target->right == &NIL)
			{
				//ST_NODE* childNode = target->left;

				/*if (target->parent->left == target)
					target->parent->left = childNode;
				else if (target->parent->right == target)
					target->parent->right = childNode;
				else return false;*/

				//childNode->parent = target->parent;

				balancingDelete(target);
				return true;
			}
			if (target->left == &NIL && target->right != &NIL)
			{
				//ST_NODE* childNode = target->right;

				/*if (target->parent->left == target)
					target->parent->left = childNode;
				else if (target->parent->right == target)
					target->parent->right = childNode;
				else return false;*/

				//childNode->parent = target->parent;

				balancingDelete(target);
				return true;
			}

			// ���� ����� �ڽ��� 2�����
			if (target->left != &NIL && target->right != &NIL)
			{
				// �����Ϸ��� ����� ���� ����Ʈ�� �ִ밪�� ��ü ����
				ST_NODE* instead = getMaxSubTree(target->left);

				// ������ üũ
				// ���� ���� ����� �ڽ��� �ΰ���� ������ �� ����
				if (instead->left != &NIL && instead->right != &NIL)
					return false;

				// �� ����
				target->key = instead->key;

				// instead ��带 �������� �뷱�� ����

				balancingDelete(instead);
				return true;
			}



			/*// ���� ����� �ڽ��� ���� ���
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
			*/
		}

		return false;
	}

	void balancingDelete(ST_NODE* curr) {
		ST_NODE* parentNode = curr->parent;

		// 1. �����Ϸ��� ��尡 RED���
		if (curr->color == RED)
		{
			// �ڽ��� ���ٸ�
			if (curr->left == &NIL && curr->right == &NIL)
			{
				if (parentNode->left == curr)
					parentNode->left = &NIL;
				else if (parentNode->right == curr)
					parentNode->right = &NIL;
				free(curr);
				return;
			}
			// ���� �ڽ��� �ִٸ�
			if (curr->left != &NIL && curr->right == &NIL)
			{
				if (parentNode->left == curr)
					parentNode->left = curr->left;
				else if (parentNode->right == curr)
					parentNode->right = curr->left;

				curr->left->parent = parentNode;
				free(curr);
				return;
			}
			// ������ �ڽ��� �ִٸ�
			if (curr->right != &NIL && curr->left == &NIL) {
				if (parentNode->left == curr)
					parentNode->left = curr->right;
				else if (parentNode->right == curr)
					parentNode->right = curr->right;

				curr->right->parent = parentNode;
				free(curr);
				return;
			}
		}

		// 2. �����Ϸ��� ��尡 BLACK�̶��
		if (curr->color == BLACK) {
			// �̿� case�� �ݺ������� üũ

			// �켱 ��带 �����Ѵ�


			ST_NODE* sibling = &NIL;
			ST_NODE* childNode = &NIL;
			bool onLeftSide = false;


			if (curr->left != &NIL && curr->right == &NIL)
				childNode = curr->left;
			if (curr->right != &NIL && curr->left == &NIL)
				childNode = curr->right;

			if (curr->color == RED)
				std::cout << "curr->color RED Error" << std::endl;

			if (parentNode->left == curr)
			{
				onLeftSide = true;
				sibling = parentNode->right;
				parentNode->left = childNode;
			}
			else if (parentNode->right == curr)
			{
				onLeftSide = false;
				sibling = parentNode->left;
				parentNode->right = childNode;
			}

			childNode->parent = parentNode;

			// �ұ��� �߻�
			// curr�������� �˻縦 �����Ѵ�

			ST_NODE* pNode = curr;

			while (pNode != _pRoot)
			{
				// 2-1. ������ �ڽ��� RED���
				// �������ְ� �ڽ��� BLACK���� �ٲ� �ذ� �Ϸ�
				if (childNode->color == RED) {
					childNode->color = BLACK;
					break;
				}
				/*if (pNode->left->color == RED || pNode->right->color == RED) {
					// ���� �ڽ��̶��
					if (pNode->left != &NIL && pNode->right == &NIL)
					{
						/*if (parentNode->left == pNode)
							parentNode->left = pNode->left;
						else if (parentNode->right == pNode)
							parentNode->right = pNode->left;

						pNode->left->parent = parentNode;
						pNode->left->color = BLACK;
						free(pNode);
						pNode->left->color = BLACK;
						return;
					}
					// ������ �ڽ��̶��
					if (pNode->right != &NIL && pNode->left == &NIL) {
						/*if (parentNode->left == pNode)
							parentNode->left = pNode->right;
						else if (parentNode->right == pNode)
							parentNode->right = pNode->right;

						pNode->right->parent = parentNode;
						pNode->right->color = BLACK;
						free(pNode);
						pNode->right->color = BLACK;
						return;
					}
				}*/

				// 2-2. ���� ��尡 ���� :: ������ ������ �ٲ��ش�
				if (sibling->color == RED)
				{
					sibling->color = BLACK;
					if (onLeftSide)
						rotateLeft(sibling);
					else
						rotateRight(sibling);
					parentNode->color = RED;
					if (onLeftSide)
						sibling = parentNode->right;
					else sibling = parentNode->left;
					continue;
				}
				// 2-3. ���� ��, ������ ��� �ڽ� �� :: ������ ����� �ؼ� �뷱���� �����ְ�, �θ� ���� ��˻�
				if (sibling->color == BLACK && ((sibling == &NIL) || (sibling->left->color == BLACK && sibling->right->color == BLACK)))
				{
					sibling->color = RED;
					pNode = parentNode;
					parentNode = pNode->parent;
					childNode = pNode;
					if (pNode == _pRoot)
						break;
					if (parentNode->left == pNode)
					{
						onLeftSide = true;
						sibling = parentNode->right;
					}
					if (parentNode->right == pNode)
					{
						onLeftSide = false;
						sibling = parentNode->left;
					}
					continue;
				}
				// 2-4. ���� ��, ������ ���ڽ�(Ȥ�� �����ڽ�)�� ���� :: ���ڽ�(Ȥ�� �����ڽ�)�� ��,
				//														  �� �θ��� ������ ����, ���� ���� ��ȸ��(Ȥ�� ��ȸ��)
				if (onLeftSide && sibling->color == BLACK && sibling->left->color == RED && sibling->right->color == BLACK)
				{
					sibling->left->color = BLACK;
					sibling->color = RED;
					rotateRight(sibling);

					sibling = parentNode->right;
				}
				if (!onLeftSide && sibling->color == BLACK && sibling->right->color == RED && sibling->left->color == BLACK) {
					sibling->right->color = BLACK;
					sibling->color = RED;
					rotateLeft(sibling);

					sibling = parentNode->left;
				}
				// 2-5. ���� ��, ������ �����ڽ�(Ȥ�� ���ڽ�)�� ����
				// :: �����ڽ�(Ȥ�� ���ڽ�)�� ��, ������ �θ� �÷���, �θ� ������, �θ� ���� ��ȸ��(Ȥ�� ��ȸ��)
				if (onLeftSide && sibling->color == BLACK && sibling->right->color == RED)
				{
					sibling->right->color = BLACK;
					sibling->color = parentNode->color;
					parentNode->color = BLACK;
					rotateLeft(sibling);
					break;
				}
				if (!onLeftSide && sibling->color == BLACK && sibling->left->color == RED)
				{
					sibling->left->color = BLACK;
					sibling->color = parentNode->color;
					parentNode->color = BLACK;
					rotateRight(sibling);
					break;
				}
			}
		}
		free(curr);
		_pRoot->color = BLACK;
	}

	ST_NODE* getMaxSubTree(ST_NODE* root) {
		if (root->right != &NIL)
			return getMaxSubTree(root->right);
		else {
			return root;
		}
	}

	void printPreorder(ST_NODE* root) {
		if (!root)
			return;

		std::cout << root->key << " ";
		if (root->left != &NIL)
			printPreorder(root->left);
		if (root->right != &NIL)
			printPreorder(root->right);
	}

	void printInorder(ST_NODE* root) {
		if (!root)
			return;

		if (root->left != &NIL)
			printInorder(root->left);
		std::cout << root->key << " ";
		if (root->right != &NIL)
			printInorder(root->right);
	}

	void printPostorder(ST_NODE* root) {
		if (!root)
			return;

		if (root->left != &NIL)
			printPostorder(root->left);
		if (root->right != &NIL)
			printPostorder(root->right);
		std::cout << root->key << " ";
	}

	void getLevelorder(std::vector<ST_NODE*> &nodeList) {
		nodeList.clear();

		nodeList.push_back(_pRoot);
		std::vector<ST_NODE*>::iterator iter = nodeList.begin();
		//++iter;

		while (iter != nodeList.end()) {
			if (*iter && (*iter)->left)
			{
				nodeList.push_back((*iter)->left);
			}
			else
			{
				nodeList.push_back(nullptr);
			}
			if (*iter && (*iter)->right)
			{
				nodeList.push_back((*iter)->right);
			}
			else
			{
				nodeList.push_back(nullptr);
			}

			std::vector<ST_NODE*>::iterator iter2 = iter;
			bool keep = false;
			iter2++;
			for (; iter2 != nodeList.end(); iter2++)
			{
				if ((*iter2 != &NIL) && (*iter2 != nullptr))
					keep = true;
			}

			if (!keep) return;

			iter++;
		}

		return;
	}

	ST_NODE* getRoot()
	{
		return _pRoot;
	}

	bool isNIL(ST_NODE* node)
	{
		return node == &NIL;
	}
};