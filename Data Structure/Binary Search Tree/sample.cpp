// sample.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "CBinaryTree.h"
#include <list>
#include <vector>

using namespace std;
void Check(ST_NODE* root);
void Test(int startNum, int range, int insertNum);
int getDepth(ST_NODE* root, int depth);

int keyList[1000];

static list<int>::iterator iter;

int main()
{
    Test(50, 10, 20);
}

void setKeyList(ST_NODE* root, int idx)
{
    if (!root)
        return;

    keyList[idx] = root->key;

    if (root->left)
        setKeyList(root->left, idx * 2);
    else keyList[idx * 2] = -1;
    if (root->right)
        setKeyList(root->right, idx * 2 + 1);
    else keyList[idx * 2 + 1] = -1;
}

void Test(int startNum, int range, int insertNum)
{
    int randNum, testNum, i;
    for (int j = startNum; j <= startNum + range; j++) {
        CBinaryTree tree;
        list<int> testNumList;
        int randNum = j;
        for (i = 0; i < insertNum; i++) {
            testNum = rand() % randNum;
            tree.insertNode(testNum);
            testNumList.push_back(testNum);
        }
        cout << " >> inserted " << i << " numbers" << endl;

#ifdef __VISUALIZE__
        int depth = getDepth(tree.getRoot(), 0);
        cout << " >> BST depth is :: " << depth << endl;

        memset(keyList, 0xffffffff, sizeof(keyList));
        setKeyList(tree.getRoot(), 1);

        int idx = 1;
        for (int i = 0; i < depth + 1; i++) {
            int t = pow(2, i);
            int size = (40 / t);
            for (int j = 0; j < t; j++) {
                for (int k = 0; k < size; k++) printf(" ");
                cout << "[";
                if (keyList[idx + j] == -1)
                    cout << "  ";
                else
                    printf("%2d", keyList[idx + j]);
                cout << "]";
                for (int k = 0; k < size - 1; k++) printf(" ");
            }
            idx += t;
            cout << endl;
        }
#endif

        testNumList.sort();


        ST_NODE* treeRoot = tree.getRoot();
        iter = testNumList.begin();

        Check(treeRoot);

        cout << " >> checked inordered numbers" << endl;

        iter = testNumList.begin();
        for (i = 0; i < insertNum; i++) {
            if (!(tree.deleteNode(*iter)))
            {
                cout << "## DELETE TEST :: " << i << " :: Error!" << endl;
                break;
            }
            //cout << " >> Deleted :: " << *iter << endl;
            iter = testNumList.erase(iter);
        }

        cout << " >> deleted " << i << " numbers" << endl;
        cout << "## TEST " << j - (startNum - 1) << " CLEAR";
        cout << endl << endl;
    }

    cout << endl << "## TEST ALL CLEAR" << endl;
}

int getDepth(ST_NODE* root, int depth) {

    int depthRight = depth;
    int depthLeft = depth;
    if (root->left || root->right) {
        depth++;
        if (root->right)
            depthRight = getDepth(root->right, depth);
        if (root->left)
            depthLeft = getDepth(root->left, depth);
    }
    if (depthRight >= depth && depthRight >= depthLeft) return depthRight;
    if (depthLeft >= depth && depthLeft >= depthRight) return depthLeft;
    return depth;
}

void Check(ST_NODE* root) {

    if (!root)
        return;

    if (root->left)
        Check(root->left);
    if (root->key != *iter)
    {
        cout << "Error!" << endl;
        return;
    }
    iter++;
    if (root->right)
        Check(root->right);
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
