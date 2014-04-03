#pragma once

#include "treenode.h"

/**
 * @brief Quad tree for Barnes-Hut algorithm
 */
class Tree {
private:
    TreeNode *root;

public:
    Tree(const Domain2D &domain) {
        root = new TreeNode(domain);
    }
    Tree(Body *bodies, const int &num_of_bodies, const Domain2D &domain) {
        root = new TreeNode(domain);
        populate(bodies, num_of_bodies);
    }
    ~Tree() {
        if (root)
            delete root;
    }

    int getHeight() const {
        return root->getHeight();
    }

    int getSize() const {
        return root->getSize();
    }

    void populate(Body *bodies, const int &num_of_bodies);
    Vector2D computeForce(Body *body, const double &theta) const;
};