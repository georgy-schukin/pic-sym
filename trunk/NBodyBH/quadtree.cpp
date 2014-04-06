#include "quadtree.h"

void QuadTree::populate(Body *bodies, const int &num_of_bodies, const Domain2D &domain) {	
	root.reset(new QuadTreeNode(getExpandedDomain(bodies, num_of_bodies, domain)));
    for (int i = 0; i < num_of_bodies; i++) {
        root->insertBody(&bodies[i]); // insert bodies in the tree
    }
    root->computeMassCenter(); // compute mass distribution for all tree nodes
}

Vector2D QuadTree::computeForce(Body *body, const double &theta) const {
    return root->computeForce(body, theta);
}

Domain2D QuadTree::getExpandedDomain(Body *bodies, const int &num_of_bodies, const Domain2D &domain) const {
	Domain2D expanded_domain = domain;
	for (int i = 0; i < num_of_bodies; i++) {
		expanded_domain.expand(bodies[i].coordinate);
	}
	return expanded_domain;
}
