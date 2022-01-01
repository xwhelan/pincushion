#include <string>
#include <vector>

#ifndef PINCUSHION_CSV
#define PINCUSHION_CSV

namespace pincushion { namespace csv {
    typedef std::vector<std::string> row;
    row readCSVRow(const std::string &);

    // Private members via anonymous namespace
    // cf. <https://www.internalpointers.com/post/c-namespaces-private-members>
    namespace {
        enum class CSVState {
            UnquotedField,
            QuotedField,
            QuotedQuote
        };
    }
}}

#endif
