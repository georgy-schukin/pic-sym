#include "picsym/parallelmachine.h"
#include "picsym/base/slicer.h"
#include <QGraphicsTextItem>
#include <numeric>

namespace picsym {

void ParallelMachine::start(const size_t& num_of_nodes, const CellMesh2D& mesh) {
    mesh_size = mesh.getWidth();
    total_num_of_particles = mesh.getNumOfParticles();

    std::vector<size_t> part_sizes;    
    Slicer::slice(mesh.getNumOfCells(), num_of_nodes, part_sizes);

    threads.clear();

    size_t start = 0;
    for (size_t node = 0; node < num_of_nodes; node++) {
        threads.push_back(new NodeThread(node, mesh.getRange(start, start + part_sizes[node])));
        start += part_sizes[node];
    }

    for (size_t node = 0; node < threads.size(); node++) { // build linear topology
        if (node > 0)
            threads[node].addNeighbour(&threads[node - 1]); // left neighbour
        if (node < threads.size() - 1)
            threads[node].addNeighbour(&threads[node + 1]); // right neighbour
    }

    for (NodeThreadArray::iterator it = threads.begin(); it != threads.end(); it++)
        it->start();
}

void ParallelMachine::stop() {
    for (NodeThreadArray::iterator it = threads.begin(); it != threads.end(); it++)
        it->stop();
}

void ParallelMachine::drawLoad(QGraphicsScene &scene) {
    std::vector<size_t> loads;
    for (NodeThreadArray::iterator it = threads.begin(); it != threads.end(); it++)
        loads.push_back(it->getCurrentLoad());

    const size_t min = *(std::min_element(loads.begin(), loads.end()));
    const size_t max = *(std::max_element(loads.begin(), loads.end()));

    QString text = "";
    for (size_t i = 0; i < loads.size(); i++) {
        text += QString("%1 : %2\n").arg(i).arg(loads[i]);
    }    
    text += QString("Total : %1\n").arg(std::accumulate(loads.begin(), loads.end(), 0));
    text += QString("Max diff : %1\n").arg(max - min);

    scene.addText(text);
}

void ParallelMachine::drawCells(QGraphicsScene &scene) {
    const static size_t numOfColors = 13;
    const static QColor colors[numOfColors] = {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta,
                                    Qt::darkRed, Qt::darkGreen, Qt::darkBlue, Qt::darkYellow, Qt::darkCyan, Qt::darkMagenta, Qt::gray};

    const size_t max_num = getMaxNumOfParticles();

    for (NodeThreadArray::const_iterator it = threads.begin(); it != threads.end(); it++) { // draw cells of each node/thread
        const size_t& node_id = it->getId();
        const QColor& node_color = colors[node_id % numOfColors];

        it->drawCells(scene, node_color, mesh_size, max_num);

        QGraphicsRectItem *rect = scene.addRect(QRectF(node_id*20, (mesh_size + 2)*10, 10, 10), QPen(Qt::black), QBrush(node_color));
        QGraphicsTextItem *text = scene.addText(QString::number(node_id));
        text->setPos(rect->boundingRect().left(), rect->boundingRect().bottom());
    }
}

size_t ParallelMachine::getMaxNumOfParticles() const {
    size_t max_num = 0;
    for (NodeThreadArray::const_iterator it = threads.begin(); it != threads.end(); it++) {
        const size_t num = it->getMaxNumOfParticles();
        if (num > max_num)
            max_num = num;
    }
    return max_num;
}

}
