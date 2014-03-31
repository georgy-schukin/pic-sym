#include "picsym/parallelmachine.h"
#include "picsym/base/slicer.h"
#include "picsym/base/algorithms.h"
#include <QGraphicsTextItem>
#include <QFontMetrics>
#include <numeric>

namespace picsym {

void ParallelMachine::start(const size_t& num_of_nodes, const CellMesh2D& mesh) {
    mesh_size = mesh.getWidth();
    total_num_of_cells = mesh.getNumOfCells();
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

template<class T>
T min(const std::vector<T>& v) {
    return *(std::min_element(v.begin(), v.end()));
}

template<class T>
T max(const std::vector<T>& v) {
    return *(std::max_element(v.begin(), v.end()));
}

template<class T>
T diff(const std::vector<T>& v) {
    return max<T>(v) - min<T>(v);
}

template<class T>
size_t len(const T& val, const T& max_val, const size_t& length) {
    return length*(float(val)/float(max_val));
}

const size_t NUM_OF_COLORS = 13;
const QColor colors[NUM_OF_COLORS] = {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::cyan, Qt::magenta,
                                Qt::darkRed, Qt::darkGreen, Qt::darkBlue, Qt::darkYellow, Qt::darkCyan, Qt::darkMagenta, Qt::gray};

void ParallelMachine::drawCells(QGraphicsScene &scene) {
    const size_t max_num = getMaxNumOfParticlesInCell();

    for (NodeThreadArray::const_iterator it = threads.begin(); it != threads.end(); it++) { // draw cells of each node/thread
        const size_t& node_id = it->getId();
        const QColor& node_color = colors[node_id % NUM_OF_COLORS];

        it->drawCells(scene, node_color, mesh_size, max_num);

        QGraphicsRectItem *rect = scene.addRect(QRectF(node_id*20, (mesh_size + 2)*10, 10, 10), QPen(Qt::black), QBrush(node_color));
        QGraphicsTextItem *text = scene.addText(QString::number(node_id));
        text->setPos(rect->boundingRect().left(), rect->boundingRect().bottom());
    }
}

QRectF drawRect(QGraphicsScene &scene, const size_t& x, const size_t& y, const size_t& w, const size_t& h, const QColor& color) {
    return scene.addRect(QRectF(x, y, w, h), QPen(), QBrush(color))->boundingRect();
}

QRectF drawText(QGraphicsScene &scene, const QString& string, const size_t& x, const size_t& y) {
    QGraphicsTextItem *text = scene.addText(string);
    text->setPos(x, y);
    return text->boundingRect();
}

void ParallelMachine::drawLoad(QGraphicsScene &scene) {
    std::vector<LoadType> load;
    std::vector<size_t> n_cells, n_particles;
    for (NodeThreadArray::iterator it = threads.begin(); it != threads.end(); it++) {
        load.push_back(it->getCurrentLoad());
        n_cells.push_back(it->getCurrentNumOfCells());
        n_particles.push_back(it->getCurrentNumOfParticles());
    }

    QFontMetrics metrics(scene.font());
    const size_t elem_height = (metrics.height() > 20) ? metrics.height() : 20;
    const LoadType total_load = std::accumulate(load.begin(), load.end(), 0.0);

    size_t pos_x = 0, pos_y = 0;
    for (size_t i = 0; i < threads.size(); i++) {
        pos_x = drawText(scene, QString("%1").arg(i, -3), 0, pos_y).right();
        pos_x = drawRect(scene, pos_x, pos_y, len(load[i], total_load, 100), elem_height, Qt::red).right();
        pos_x = drawRect(scene, pos_x, pos_y, len(n_cells[i], total_num_of_cells, 100), elem_height, Qt::green).right();
        pos_x = drawRect(scene, pos_x, pos_y, len(n_particles[i], total_num_of_particles, 100), elem_height, Qt::blue).right();
        pos_x = drawText(scene, QString("L: %1, C: %2, P: %3").
                         arg(load[i]).arg(n_cells[i]).arg(n_particles[i]), pos_x, pos_y).right();
        pos_y += elem_height + 2;
    }
    drawText(scene, QString("Max diff: L: %1, C: %2, P: %3").
             arg(diff(load)).arg(diff(n_cells)).arg(diff(n_particles)), 0, pos_y).right();
}

size_t _getMaxNumOfParticlesInCell(const NodeThread& n) {
    return n.getMaxNumOfParticlesInCell();
}

size_t ParallelMachine::getMaxNumOfParticlesInCell() const {
    return alg::max<size_t>(threads.begin(), threads.end(), 0, _getMaxNumOfParticlesInCell);
}

}
