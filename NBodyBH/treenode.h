#pragma once

#include "body.h"
#include "domain2d.h"

#define NUM_OF_CHILDREN 4

/**
 * @brief Node of a quad tree for Barnes-Hut algorithm
 */
class TreeNode {
private:    
    Domain2D domain; // node's domain

    bool is_empty; // if node contains bodies

    TreeNode *children[NUM_OF_CHILDREN]; // child nodes

    Body *body; // pointer to single body
    Body center_of_mass; // center of mass body

private:
    void nullChildren() {
        for (int i = 0; i < NUM_OF_CHILDREN; i++) {
            children[i] = 0;            
        }
    }

    TreeNode* getChild(const int &num);

public:    
    TreeNode(const Domain2D &dm) : domain(dm), is_empty(true), body(0) {
        nullChildren();
    }
    ~TreeNode() {        
        for (int i = 0; i < NUM_OF_CHILDREN; i++)
            if (children[i])
                delete children[i];
    }    

    void insertBody(Body *new_body);

    int getHeight() const;
    int getSize() const;
};
