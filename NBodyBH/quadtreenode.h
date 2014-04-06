#pragma once

#include "body.h"
#include "domain2d.h"
#include <memory>
#include <cstdio>

#define NUM_OF_CHILDREN 4

/**
 * @brief Node of a quad tree for Barnes-Hut algorithm
 */
class QuadTreeNode {
private:    
    Domain2D domain; // node's domain

    bool is_empty; // if node contains bodies

    std::auto_ptr<QuadTreeNode> children[NUM_OF_CHILDREN]; // child nodes

    Body *body; // pointer to single body
    Body mass_center; // center of mass

private:    
    QuadTreeNode* getChild(const int &num);
	QuadTreeNode* getChild(const Vector2D &coord);

public:    
    QuadTreeNode(const Domain2D &dm) : domain(dm), is_empty(true), body(0) {}
    ~QuadTreeNode() {}

    const Body& getMassCenter() const {
        return mass_center;
    }

    void insertBody(Body *new_body);
    bool computeMassCenter();

    Vector2D computeForce(Body *target, const double &theta) const;

    int getHeight() const;
    int getSize() const;
};
