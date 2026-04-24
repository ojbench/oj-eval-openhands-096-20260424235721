
#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    unordered_map<int, pair<int, int>> nodeInfo; // value -> {depth, parent}
    vector<TreeNode*> nodes; // Store all nodes for cleanup
    
    // Parse extended binary tree from preorder traversal
    TreeNode* buildTree(vector<int>& values, int& index) {
        if (index >= values.size() || values[index] == -1) {
            index++;
            return nullptr;
        }
        
        TreeNode* root = new TreeNode(values[index]);
        nodes.push_back(root); // Store for cleanup
        index++;
        root->left = buildTree(values, index);
        root->right = buildTree(values, index);
        return root;
    }
    
    // Traverse tree to record depth and parent information
    void recordNodeInfo(TreeNode* root, int depth, int parent) {
        if (!root) return;
        
        nodeInfo[root->val] = {depth, parent};
        recordNodeInfo(root->left, depth + 1, root->val);
        recordNodeInfo(root->right, depth + 1, root->val);
    }
    
    // Clean up allocated memory
    void cleanup() {
        for (TreeNode* node : nodes) {
            delete node;
        }
        nodes.clear();
    }
    
public:
    void solve() {
        int q;
        cin >> q;
        
        vector<pair<int, int>> queries;
        for (int i = 0; i < q; i++) {
            int x, y;
            cin >> x >> y;
            queries.push_back({x, y});
        }
        
        // Read the entire line for tree values
        string line;
        cin.ignore(); // Clear the newline
        getline(cin, line);
        
        // Parse tree values
        vector<int> treeValues;
        stringstream ss(line);
        int value;
        while (ss >> value) {
            treeValues.push_back(value);
        }
        
        // Build tree
        int index = 0;
        TreeNode* root = buildTree(treeValues, index);
        
        // Record node information
        recordNodeInfo(root, 0, -1);
        
        // Process queries
        for (auto& query : queries) {
            int x = query.first;
            int y = query.second;
            
            if (nodeInfo.find(x) == nodeInfo.end() || nodeInfo.find(y) == nodeInfo.end()) {
                cout << 0 << endl;
                continue;
            }
            
            auto infoX = nodeInfo[x];
            auto infoY = nodeInfo[y];
            
            if (infoX.first == infoY.first && infoX.second != infoY.second) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
        }
        
        // Clean up memory
        cleanup();
    }
};

int main() {
    Solution sol;
    sol.solve();
    return 0;
}
