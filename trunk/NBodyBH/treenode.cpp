#include "treenode.h"
#include <cstdio>
#include <vector>
#include <algorithm>

void TreeNode::insertBody(Body *new_body) {
    if (is_empty) { // node contains no bodies
        is_empty = false;
        body = new_body; // insert single body
    } else {
        if (body) { // node contains single body (external node)
            Body *prev_body = body;
            body = 0;
            const int quad_1 = domain.detectQuadrant(prev_body->coordinate);
            const int quad_2 = domain.detectQuadrant(new_body->coordinate);
            getChild(quad_1)->insertBody(prev_body); // subdivide domain and insert bodies to subdomains
            getChild(quad_2)->insertBody(new_body);
        } else { // node is an internal node
            const int quad = domain.detectQuadrant(new_body->coordinate);
            getChild(quad)->insertBody(new_body); // insert to subdomain
        }
    }
}

TreeNode* TreeNode::getChild(const int &num) {
    if (!children[num]) {
        children[num] = new TreeNode(domain.getQuadrant(num)); // create new child
    }
    return children[num];
}

int TreeNode::getHeight() const {
    int height[NUM_OF_CHILDREN];
    for (int i = 0; i < NUM_OF_CHILDREN; i++)
        height[i] = (children[i]) ? 1 + children[i]->getHeight() : 1;
    return *std::max_element(height, height + NUM_OF_CHILDREN);
}

int TreeNode::getSize() const {
    int size = 1;
    for (int i = 0; i < NUM_OF_CHILDREN;i++)
        if (children[i])
            size += children[i]->getSize();
    return size;
}
