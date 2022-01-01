#include <iostream>
#include <string>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

int main(int argc, char *argv[])
{
    // Declare the supported options.
    po::options_description desc("usage:");
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
    pd.add("inputfile", -1);

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
        cerr << "Input file name required." << "\n";
        return 1;
    }

    std::cout << "I would have read from " << inputfile << "\n";
    return 0;
}
