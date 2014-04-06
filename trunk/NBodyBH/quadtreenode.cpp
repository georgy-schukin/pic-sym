#include "quadtreenode.h"
#include <cmath>
#include <algorithm>

void QuadTreeNode::insertBody(Body *new_body) {
    if (is_empty) { // node contains no bodies
        is_empty = false;
        body = new_body; // insert single body
    } else {
        if (body) { // node contains single body (external node)
            Body *old_body = body;
            body = 0;
            if (new_body->coordinate == old_body->coordinate) { 
                new_body->coordinate += Vector2D(1e-7, 1e-7); // fix equal coordinates
            }            
            getChild(old_body->coordinate)->insertBody(old_body); // subdivide domain and insert bodies to subdomains
            getChild(new_body->coordinate)->insertBody(new_body);
        } else { // node is an internal node            
            getChild(new_body->coordinate)->insertBody(new_body); // insert to subdomain
        }
    }
}

bool QuadTreeNode::computeMassCenter() {
    if (is_empty)
        return false;
    if (body) { // single body - set mass center to this body
        mass_center.mass = body->mass;
        mass_center.coordinate = body->coordinate;
    } else { // sum mass center from children
        mass_center.mass = 0.0;
        mass_center.coordinate = 0.0;
        for (int i = 0; i < NUM_OF_CHILDREN; i++) {
            if (children[i].get() && children[i]->computeMassCenter()) {
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

Vector2D QuadTreeNode::computeForce(Body *target, const double &theta) const {
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
                if (children[i].get())
                    force += children[i]->computeForce(target, theta); // sum force from children
            }
            return force;
        }
    }
}

QuadTreeNode* QuadTreeNode::getChild(const Vector2D &coord) {
	const int quad = domain.detectQuadrant(coord);
	return getChild(quad);
}

QuadTreeNode* QuadTreeNode::getChild(const int &num) {
    if (!children[num].get()) {
        children[num].reset(new QuadTreeNode(domain.getQuadrant(num))); // create new child
    }
    return children[num].get();
}

int QuadTreeNode::getHeight() const {
    int height[NUM_OF_CHILDREN];
    for (int i = 0; i < NUM_OF_CHILDREN; i++)
        height[i] = (children[i].get()) ? 1 + children[i]->getHeight() : 1;
    return *std::max_element(height, height + NUM_OF_CHILDREN);
}

int QuadTreeNode::getSize() const {
    int size = 1;
    for (int i = 0; i < NUM_OF_CHILDREN;i++)
        if (children[i].get())
            size += children[i]->getSize();
    return size;
}
