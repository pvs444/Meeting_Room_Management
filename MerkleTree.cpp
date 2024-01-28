#include<bits/stdc++.h>
#include <openssl/sha.h>

class MerkleTree {
public:
    std::vector<std::string> leaves;  // Vector to store leaf nodes
    std::string root;  // Root node of the Merkle tree

    void createTree(const std::vector<std::string>& data) {
        leaves.clear();
        for (const auto& d : data) {
            leaves.push_back(hashLeaf(d));
        }
        root = buildTree(leaves);
    }

    bool verify(const std::vector<std::string>& data, const std::string& rootHash) {
        std::string computedRoot = computeRootHash(data);
        return computedRoot == rootHash;
    }

private:
    std::string hashLeaf(const std::string& data) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, data.c_str(), data.length());
        SHA256_Final(hash, &sha256);

        char hashString[2 * SHA256_DIGEST_LENGTH + 1];
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            sprintf(&hashString[i * 2], "%02x", hash[i]);
        }

        return std::string(hashString);
    }

    std::string buildTree(const std::vector<std::string>& nodes) {
        if (nodes.size() == 1) {
            return nodes[0];
        }

        std::vector<std::string> nextLevel;
        for (size_t i = 0; i < nodes.size(); i += 2) {
            std::string left = nodes[i];
            std::string right = (i + 1 < nodes.size()) ? nodes[i + 1] : left;
            std::string combinedHash = combineHashes(left, right);
            nextLevel.push_back(combinedHash);
        }

        return buildTree(nextLevel);
    }

    std::string combineHashes(const std::string& left, const std::string& right) {
        return hashLeaf(left + right);
    }

    std::string computeRootHash(const std::vector<std::string>& data) {
        std::vector<std::string> leafHashes;
        for (const auto& d : data) {
            leafHashes.push_back(hashLeaf(d));
        }

        return buildTree(leafHashes);
    }
};

// int main() {
//     std::vector<std::string> data = {"Data Chunk 1", "Data Chunk 2", "Data Chunk 3", "Data Chunk 4"};
//     MerkleTree merkleTree;
//     merkleTree.createTree(data);
//     std::string rootHash = merkleTree.root;
//     bool isValid = merkleTree.verify(data, rootHash);

//     std::cout << "Data integrity is valid: " << (isValid ? "true" : "false") << std::endl;

//     return 0;
// }
