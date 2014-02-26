#include "picsym/cellarray.h"

namespace picsym {

void CellArray::resize(const size_t& size) {
    cells.resize(size, Cell());
}

}
