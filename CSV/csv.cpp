/* CSV reading.
 * Starting point:
 * https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
 *
 */

#include <istream>
#include <string>
#include <vector>

#include "csv.hpp"

pincushion::csvRow pincushion::readCSVRow(const std::string &row) {
    CSVState state = pincushion::CSVState::UnquotedField;
    std::vector<std::string> fields {""};
    size_t i = 0; // index of the current field
    for (char c : row) {
        switch (state) {
            case pincushion::CSVState::UnquotedField:
                switch (c) {
                    case ',': // end of field
                              fields.push_back(""); i++;
                              break;
                    case '"': state = pincushion::CSVState::QuotedField;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedField:
                switch (c) {
                    case '"': state = pincushion::CSVState::QuotedQuote;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedQuote:
                switch (c) {
                    case ',': // , after closing quote
                              fields.push_back(""); i++;
                              state = pincushion::CSVState::UnquotedField;
                              break;
                    case '"': // "" -> "
                              fields[i].push_back('"');
                              state = pincushion::CSVState::QuotedField;
                              break;
                    default:  // end of quote
                              state = pincushion::CSVState::UnquotedField;
                              break; }
                break;
        }
    }
    return fields;
}

/// Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
std::vector<pincushion::csvRow> readCSV(std::istream &in) {
    std::vector<std::vector<std::string>> table;
    std::string row;
    while (!in.eof()) {
        std::getline(in, row);
        if (in.bad() || in.fail()) {
            break;
        }
        auto fields = pincushion::readCSVRow(row);
        table.push_back(fields);
    }
    return table;
}