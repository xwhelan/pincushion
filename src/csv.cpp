/* CSV reading.
 * Starting point:
 * https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
 *
 */

#include <istream>
#include <string>
#include <vector>

#include "pincushion/csv.hpp"

namespace csv = pincushion::csv;

csv::row csv::readCSVRow(const std::string &row) {
    CSVState state = csv::CSVState::UnquotedField;
    std::vector<std::string> fields {""};
    size_t i = 0; // index of the current field
    for (char c : row) {
        switch (state) {
            case csv::CSVState::UnquotedField:
                switch (c) {
                    case ',': // end of field
                              fields.push_back(""); i++;
                              break;
                    case '"': state = csv::CSVState::QuotedField;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedField:
                switch (c) {
                    case '"': state = csv::CSVState::QuotedQuote;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedQuote:
                switch (c) {
                    case ',': // , after closing quote
                              fields.push_back(""); i++;
                              state = csv::CSVState::UnquotedField;
                              break;
                    case '"': // "" -> "
                              fields[i].push_back('"');
                              state = csv::CSVState::QuotedField;
                              break;
                    default:  // end of quote
                              state = csv::CSVState::UnquotedField;
                              break; }
                break;
        }
    }
    return fields;
}

/// Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
std::vector<csv::row> readCSV(std::istream &in) {
    std::vector<std::vector<std::string>> table;
    std::string row;
    while (!in.eof()) {
        std::getline(in, row);
        if (in.bad() || in.fail()) {
            break;
        }
        auto fields = csv::readCSVRow(row);
        table.push_back(fields);
    }
    return table;
}
