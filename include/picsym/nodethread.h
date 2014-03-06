#pragma once

#ifndef Q_MOC_RUN
#include <boost/thread/mutex.hpp>
#endif

#include "base/inode.h"
#include "base/threadactivity.h"
#include <map>
#include <queue>
#include <QGraphicsScene>

namespace picsym {

class NodeThread : public INode, public ThreadActivity
{
private:
    mutable boost::mutex mutex;
    mutable boost::mutex lmutex, rmutex, cmutex;

private:
    CellRange my_cells;      
    size_t id;    

private:
    typedef std::map<size_t, INode*> NeighNodeMap;
    typedef std::map<size_t, size_t> NeighLoadMap;
    typedef std::pair<size_t, size_t> UIntPair;
    NeighNodeMap neighbours;
    NeighLoadMap neighbours_load;

    std::queue<UIntPair> incoming_load_info;
    std::queue<UIntPair> incoming_cell_requests;
    std::queue<CellRange> incoming_cells;

private:
    void threadFunction();

private:
    void balance();
    void update();
    void processIncoming();

    void processIncomingLoad();
    void processIncomingRequests();
    void processIncomingCells();

    size_t getMaxLoadedNode();

    CellRange takeCells(const size_t& load, const bool& from_back = true);

    void processRequest(const size_t& src_id, const size_t& load);

public:
    NodeThread(const size_t& i) : id(i) {}
    NodeThread(const size_t &i, const CellRange& cells) : id(i) {
        sendCells(id, cells);
    }  
    ~NodeThread() {}

    const size_t& getId() const {
        return id;
    }

    void addNeighbour(INode *neighbour);
    void sendLoadInfo(const size_t& src_id, const size_t& load);
    void sendCells(const size_t& src_id, const CellRange& cells);
    void requestCells(const size_t& src_id, const size_t& load);

    size_t getCurrentLoad() const;
    size_t getMaxNumOfParticles() const; // get num of particles in max loaded cell

    void drawCells(QGraphicsScene& scene, const QColor& base_color, const size_t& mesh_size, const size_t& max_num_of_particles) const;
};

}
