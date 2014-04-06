#pragma once

#include "quadtreenode.h"

/**
 * @brief Quad tree for Barnes-Hut algorithm
 */
class QuadTree {
private:
    std::auto_ptr<QuadTreeNode> root;

private:	
	void populate(Body *bodies, const int &num_of_bodies, const Domain2D &domain);
	Domain2D getExpandedDomain(Body *bodies, const int &num_of_bodies, const Domain2D &domain) const;

public:	
    QuadTree(Body *bodies, const int &num_of_bodies, const Domain2D &domain) : root(0) {        
        populate(bodies, num_of_bodies, domain);
    }
    ~QuadTree() {
        /*if (root)
            delete root;*/
    }

    int getHeight() const {
        return root->getHeight();
    }

    int getSize() const {
        return root->getSize();
    }
    
    Vector2D computeForce(Body *body, const double &theta) const;
};
