#include "treenode.h"
#include <cmath>
#include <algorithm>

void TreeNode::insertBody(Body *new_body) {
    if (is_empty) { // node contains no bodies
        is_empty = false;
        body = new_body; // insert single body
    } else {
        if (body) { // node contains single body (external node)
            Body *prev_body = body;
            body = 0;
            if (new_body->coordinate == prev_body->coordinate) { 
                new_body->coordinate += Vector2D(1e-5, 1e-5); // fix equal coordinates
            }
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

bool TreeNode::computeMassCenter() {
    if (is_empty)
        return false;
    if (body) { // single body - set mass center to this body
        mass_center.mass = body->mass;
        mass_center.coordinate = body->coordinate;
    } else { // sum mass center from children
        mass_center.mass = 0.0;
        mass_center.coordinate = 0.0;
        for (int i = 0; i < NUM_OF_CHILDREN; i++) {
            if (children[i] && children[i]->computeMassCenter()) {
                const Body &mc = children[i]->getMassCenter();
                mass_center.mass += mc.mass;
                mass_center.coordinate.x += mc.coordinate.x*mc.mass;
                mass_center.coordinate.y += mc.coordinate.y*mc.mass;
            }
        }
        mass_center.coordinate.x /= mass_center.mass;
        mass_center.coordinate.y /= mass_center.mass;
    }
    return true;
}

Vector2D TreeNode::computeForce(Body *target, const double &theta) const {
    if (is_empty || (body == target))
        return Vector2D(0.0, 0.0);
    if (body) {
        return target->computeForce(*body); // return force between two single bodies
    } else {
        const double dx = target->coordinate.x - mass_center.coordinate.x;
        const double dy = target->coordinate.y - mass_center.coordinate.y;
        const double dist = sqrt(dx*dx + dy*dy) + 1e-12; // try to avoid zero distance
        if (domain.width() / dist < theta) { // check approximation condition
            return target->computeForce(mass_center); // make approximation with mass center
        } else {
            Vector2D force;
            for (int i = 0; i < NUM_OF_CHILDREN; i++) {
                if (children[i])
                    force += children[i]->computeForce(target, theta); // sum force from children
            }
            return force;
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
