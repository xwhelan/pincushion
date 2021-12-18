#include <string>
#include <vector>

#include "csv.cpp"

#ifndef PINCUSHION_CSV
#define PINCUSHION_CSV

namespace pincushion::csv {
    typedef std::vector<std::string> row;
    row readCSVRow(const std::string &);
}

# endif
