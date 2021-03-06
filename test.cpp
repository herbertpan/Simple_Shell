#include <iostream>
#include "bst.h"
#include <vector>
using namespace std;

int main(int argc, char * argv[]) {
	int arr[] = {10, 20, 5, 30, 15, 1, 7};
	vector<int> myvec(arr, arr + 7);
	for (int x : myvec) cout << x << " "; cout << endl;
	TreeNode *root = build_tree(myvec);
	vector<vector<int>> res = levelorder_traverse(root);
	for (auto x : res) {
		for (int y : x) {
			cout << y << " ";
		}
		cout << endl;
	}
	cout << endl;
	inorder_traverse(root); cout << endl;
	preorder_traverse(root); cout << endl;
	postorder_traverse(root);
	getchar();
}