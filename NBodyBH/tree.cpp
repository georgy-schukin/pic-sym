#include "tree.h"
#include <cstdio>

void Tree::populate(Body *bodies, const int &num_of_bodies) {
    for (int i = 0; i < num_of_bodies; i++) {
        root->insertBody(&bodies[i]); // insert bodies in the tree
    }
}

