#pragma once

#ifndef Q_MOC_RUN
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#endif

#include "base/inode.h"
#include "base/threadactivity.h"
#include "base/protectedqueue.h"
#include <map>
#include <QGraphicsScene>

namespace picsym {

class NodeThread : public INode, public ThreadActivity
{
private:
    mutable boost::mutex mutex;    

private:
    CellRange my_cells;      
    size_t id;    

private:
    typedef std::map<size_t, INode*> NeighNodeMap;
    typedef std::map<size_t, LoadType> NeighLoadMap;
    typedef std::pair<size_t, LoadType> LoadPair;

    NeighNodeMap neighbours;
    NeighLoadMap neighbours_load;

    ProtectedQueue<LoadPair> incoming_load_info;
    ProtectedQueue<LoadPair> incoming_cell_requests;
    ProtectedQueue<CellRange> incoming_cells;

private:
    void threadFunction();

private:
    void compute();
    void balance();
    void update();
    void processIncoming();

    void processIncomingLoad();
    void processIncomingRequests();
    void processIncomingCells();

    size_t getMaxLoadedNode();

    CellRange takeCells(const LoadType& load, const bool& from_back = true);

    void processRequest(const LoadPair& p);
    void setLoadInfo(const LoadPair& p);
    void addCells(const CellRange& range);

public:
    NodeThread(const size_t& i) : id(i) {}
    NodeThread(const size_t &i, const CellRange& cells) : id(i) {
        sendCells(id, cells);
    }  
    ~NodeThread() {}

    size_t getId() const {
        return id;
    }

    void addNeighbour(INode *neighbour);
    void sendLoadInfo(const size_t& src_id, const LoadType& load);
    void requestCells(const size_t& src_id, const LoadType& load);
    void sendCells(const size_t& src_id, const CellRange& cells);        
    void getStat(NodeStat& stat);

    LoadType getCurrentLoad() const;
    size_t getCurrentNumOfCells() const;
    size_t getCurrentNumOfParticles() const;
    size_t getMaxNumOfParticlesInCell() const;    

    void drawCells(QGraphicsScene& scene, const QColor& base_color, const size_t& mesh_size, const size_t& max_num) const;
};

}
