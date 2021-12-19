#include <string>
#include <vector>

#ifndef PINCUSHION_CSV
#define PINCUSHION_CSV

namespace pincushion {
    enum class CSVState {
        UnquotedField,
        QuotedField,
        QuotedQuote
    };

    typedef std::vector<std::string> csvRow;
    csvRow readCSVRow(const std::string &);
}

#endif
