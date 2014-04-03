#include "tree.h"

void Tree::populate(Body *bodies, const int &num_of_bodies) {
    for (int i = 0; i < num_of_bodies; i++) {
        root->insertBody(&bodies[i]); // insert bodies in the tree
    }
    root->computeMassCenter(); // compute mass distribution for all tree nodes
}

Vector2D Tree::computeForce(Body *body, const double &theta) const {
    return root->computeForce(body, theta);
}
