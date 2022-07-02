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
		// 삽입한 node의 부모가 RED라면
		if (ParentNode->color == RED && curr->color == RED)
		{
			// 부모의 형제 노드의 색을 확인
			ST_NODE* PSiblingNode = &NIL;
			ST_NODE* PParentNode = ParentNode->parent;
			if (PParentNode->left == ParentNode)
				PSiblingNode = PParentNode->right;
			else if (PParentNode->right == ParentNode)
				PSiblingNode = PParentNode->left;

			// 부모의 형제 노드가 RED라면
			if (PSiblingNode->color == RED)
			{
				ParentNode->color = BLACK;
				PSiblingNode->color = BLACK;
				PParentNode->color = RED;

				if (PParentNode != _pRoot)
					if (PParentNode->parent->color == RED)
						balance(PParentNode);
			} // 부모의 형제 노드가 BLACK이라면
			else {
				// 부모가 조부모의 왼쪽 노드라면
				if (PParentNode->left == ParentNode) {
					// 현재 노드가 부모의 오른쪽 노드라면
					if (ParentNode->right == curr) {
						// 부모 기준 좌회전
						rotateLeft(ParentNode);
						curr = ParentNode; // 기존 Parent를 curr로
						ParentNode = ParentNode->parent; // 기존 Curr
						PParentNode = ParentNode->parent; // 기존 Curr의 부모가 조부모가 되었으므로
					}
					// 다시 우회전
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
				// 부모가 조부모의 오른쪽 노드라면
				else if (PParentNode->right == ParentNode) {
					// 현재 노드가 부모의 왼쪽 노드라면
					if (ParentNode->left == curr) {
						// 부모 기준 우회전
						rotateRight(ParentNode);
						curr = ParentNode; // 기존 Parent를 curr로
						ParentNode = ParentNode->parent; // 기존 Curr
						PParentNode = ParentNode->parent; // 기존 Curr의 부모가 조부모가 되었으므로
					}
					// 다시 좌회전
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
		// 루트 노드를 블랙으로 설정
		_pRoot->color = BLACK;
	}

	void rotateLeft(ST_NODE* curr) {
		ST_NODE* currLeftNode = curr->left;
		ST_NODE* currRightNode = curr->right;
		ST_NODE* currParentNode = curr->parent;

		if (!currParentNode)
		{
			// 루트 노드일 경우
			curr->right = currRightNode->left;
			currRightNode->left->parent = curr;

			currRightNode->left = curr;
			curr->parent = currRightNode;

			_pRoot = currLeftNode;
			return;
		}
		if (currParentNode->left == curr)
		{
			// curr 노드가 내려간다
			currParentNode->left = currRightNode;
			curr->parent = currRightNode;
			curr->right = currRightNode->left;
			currRightNode->left->parent = curr;
			currRightNode->parent = currParentNode;
			currRightNode->left = curr;
		}
		else if (currParentNode->right == curr)
		{
			// curr 노드가 올라간다
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
			// 루트 노드일 경우
			curr->left = currLeftNode->right;
			currLeftNode->right->parent = curr;

			currLeftNode->right = curr;
			curr->parent = currLeftNode;

			_pRoot = currLeftNode;
			return;
		}

		if (currParentNode->right == curr)
		{
			// curr 노드가 내려간다
			currParentNode->right = currLeftNode;
			curr->parent = currLeftNode;
			curr->left = currLeftNode->right;
			currLeftNode->right->parent = curr;
			currLeftNode->parent = currParentNode;
			currLeftNode->right = curr;
		}
		else if (currParentNode->left == curr)
		{
			// curr 노드가 올라간다
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

		// 루트가 없다면
		// 첫 노드를 루트로 설정

		if (!_pRoot) {
			_pRoot = initNode(key, nullptr);
			_pRoot->color = BLACK;
			iSize++;
			return true;
		}

		// 부모가 있다면, 현재 curr가 새 노드의 부모가 된다
		// 부모의 key값과 비교해 왼쪽 혹은 오른쪽 자식으로 정한다

		if (curr->key > key)
			if (curr->left == &NIL) {
				// 부모 key보다 작고, 부모가 왼자식을 가지고 있지 않으면 그곳으로 정한다
				curr->left = initNode(key, curr);
				iSize++;
				balance(curr->left);
				return true;
			}
			else return insertNode(key, curr->left); // 왼자식이 있으면 해당 왼자식으로 curr을 넘겨 다시 검사
		else {
			if (curr->right == &NIL) {
				// 부모 key보다 크거나 같고, 오른자식을 가지고 있지 않으면 그곳으로 정한다
				curr->right = initNode(key, curr);
				iSize++;
				balance(curr->right);
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
				if (!(target->left != &NIL || target->right != &NIL)) {
					_pRoot = nullptr;
					free(target);
					return true;
				}

				// 자식이 1개라면 (왼쪽 혹은 오른쪽 자식만 있다면)
				// 왼쪽 자식
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
				// 삭제 노드의 자식이 2개라면
				if (target->left != &NIL && target->right != &NIL)
				{
					// 삭제하려는 노드의 왼쪽 서브트리 최대값을 대체 노드로
					ST_NODE* instead = getMaxSubTree(target->left);

					// 선조건 체크
					// 최종 삭제 노드의 자식이 두개라면 삭제할 수 없음
					if (instead->left != &NIL && instead->right != &NIL)
						return false;

					// 값 복사
					target->key = instead->key;

					// instead 노드를 기준으로 밸런싱 시작

					balancingDelete(instead);
					return true;
				}

				// 루트 노드에게 자식이 있는 경우
				/*if (target->left != &NIL) {
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


			// 삭제 노드가 자식이 없거나 1개
			// 없다면
			if (!(target->left != &NIL || target->right != &NIL)) {
				/*if (target->parent->left == target)
					target->parent->left = &NIL;
				else if (target->parent->right == target)
					target->parent->right = &NIL;
				else return false;*/
				balancingDelete(target);
				return true;
			}
			// 자식이 1개라면 (왼쪽 혹은 오른쪽 자식만 있다면)
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

			// 삭제 노드의 자식이 2개라면
			if (target->left != &NIL && target->right != &NIL)
			{
				// 삭제하려는 노드의 왼쪽 서브트리 최대값을 대체 노드로
				ST_NODE* instead = getMaxSubTree(target->left);

				// 선조건 체크
				// 최종 삭제 노드의 자식이 두개라면 삭제할 수 없음
				if (instead->left != &NIL && instead->right != &NIL)
					return false;

				// 값 복사
				target->key = instead->key;

				// instead 노드를 기준으로 밸런싱 시작

				balancingDelete(instead);
				return true;
			}



			/*// 삭제 노드의 자식이 없는 경우
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
			*/
		}

		return false;
	}

	void balancingDelete(ST_NODE* curr) {
		ST_NODE* parentNode = curr->parent;

		// 1. 삭제하려는 노드가 RED라면
		if (curr->color == RED)
		{
			// 자식이 없다면
			if (curr->left == &NIL && curr->right == &NIL)
			{
				if (parentNode->left == curr)
					parentNode->left = &NIL;
				else if (parentNode->right == curr)
					parentNode->right = &NIL;
				free(curr);
				return;
			}
			// 왼쪽 자식이 있다면
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
			// 오른쪽 자식이 있다면
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

		// 2. 삭제하려는 노드가 BLACK이라면
		if (curr->color == BLACK) {
			// 이외 case는 반복문으로 체크

			// 우선 노드를 삭제한다


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

			// 불균형 발생
			// curr에서부터 검사를 시작한다

			ST_NODE* pNode = curr;

			while (pNode != _pRoot)
			{
				// 2-1. 유일한 자식이 RED라면
				// 연결해주고 자식을 BLACK으로 바꿔 해결 완료
				if (childNode->color == RED) {
					childNode->color = BLACK;
					break;
				}
				/*if (pNode->left->color == RED || pNode->right->color == RED) {
					// 왼쪽 자식이라면
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
					// 오른쪽 자식이라면
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

				// 2-2. 형제 노드가 레드 :: 형제를 블랙으로 바꿔준다
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
				// 2-3. 형제 블랙, 형제의 모든 자식 블랙 :: 형제를 레드로 해서 밸런싱을 맞춰주고, 부모 노드로 재검사
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
				// 2-4. 형제 블랙, 형제의 왼자식(혹은 오른자식)이 레드 :: 왼자식(혹은 오른자식)을 블랙,
				//														  그 부모인 형제를 레드, 형제 기준 우회전(혹은 좌회전)
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
				// 2-5. 형제 블랙, 형제의 오른자식(혹은 왼자식)이 레드
				// :: 오른자식(혹은 왼자식)을 블랙, 형제를 부모 컬러로, 부모를 블랙으로, 부모 기준 좌회전(혹은 우회전)
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