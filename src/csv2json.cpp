#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <boost/program_options.hpp>
#include <pincushion/csv.hpp>

using namespace std;
namespace po = boost::program_options;
namespace csv = pincushion::csv;

// Quote JSON string and escape double quote character
std::string quote(std::string raw) {
    std::string quoted;
    quoted += '"';
    for (auto it = raw.begin(); it != raw.end(); it++) {
        if (*it == '"') {
            quoted += '\\';
        }
        quoted += *it;
    }
    quoted += '"';
    return quoted;
}

// Create a JSON object and print it
void zip_json(
    const csv::row& header, const csv::row& values,
    int indentation = 4, std::ostream &output = std::cout
) {
    int header_cols = header.size();
    int row_cols = values.size();
    auto indent = std::string(indentation, ' ');
    output << indent << "{" << std::endl;
    for (int i=0; i<header_cols; i++) {
        auto key = quote(header[i]);
        auto value = quote(values[i]);
        output << indent << indent << key << ": " << value;
        if (i < header_cols-1) {
            output << ",";
        }
        output << std::endl;
    }
    output << indent << "}";
}


// Write JSON from CSV file contents
void to_json(std::string inputfile,
             int indentation = 4, std::ostream& output = std::cout
) {
    fstream fd;
    fd.open(inputfile, std::ios::in);
    if (!fd.is_open()) {
        std::cerr << "Unable to open file: " << inputfile << std::endl;
        return;
    }
    std::string header_line;
    getline(fd, header_line);
    const auto header = csv::readCSVRow(header_line);
    output << "[";
    std::string line;
    bool first_element = true;
    while( getline(fd, line) ) {
        if (!first_element) {
            output << ",";
        }
        output << std::endl;
        zip_json(header, csv::readCSVRow(line), indentation, output);
        first_element = false;
    }
    output << std::endl << "]" << std::endl;
}


int main(int argc, char *argv[])
{
    // Declare the supported options.
    po::options_description desc("usage");
    desc.add_options()
        ("help,h", "display this help message")
    ;

    std::string inputfile;
    po::options_description hidden;
    hidden.add_options()
        (
            "inputfile", po::value<std::string>(&inputfile),
            "CSV input file: must have header row"
        )
    ;
    po::positional_options_description pd;
    pd.add("inputfile", 1);

    po::options_description all_options;
    all_options.add(desc);
    all_options.add(hidden);

    po::variables_map vm;
    po::store(
        po::command_line_parser(argc, argv)
            .options(all_options)
            .positional(pd)
            .run(),
        vm);

    if ( vm.count("help") )
    {
        cerr << desc << "\n";
        return 1;
    }

    if (!vm.count("inputfile"))
    {
        cerr << "Input file name required." << "\n\n" << desc << "\n";
        return 1;
    }
    vm.notify();

    to_json(inputfile);
    return 0;
}
