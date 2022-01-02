#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>
#include "csv.cpp"

namespace csv = pincushion::csv;

TEST_CASE( "Unquoted CSV line", "[unquoted]" ) {
    const auto unquoted_line = "foo,bar,baz";
    auto row = csv::readCSVRow(unquoted_line);
    REQUIRE( row[0] == "foo" );
}

TEST_CASE( "Quoted CSV line", "[quoted]" ) {
    const auto quoted_line = "\"foo\",bar,\"baz\"";
    auto row = csv::readCSVRow(quoted_line);
    REQUIRE( row[0] == "foo");
    REQUIRE( row[1] == "bar");
    REQUIRE( row[2] == "baz" );
}

TEST_CASE( "Quoted CSV with escaped quote character", "[escaped]" ) {
    // This one is tricky due to multiple layers of escapes

    /* NB: example code from Stack Overflow does quotes inside quoted fields
     * as doubled-up quotes
     * Refer to https://datatracker.ietf.org/doc/html/rfc4180
     */
    const auto escaped_line = "foo,\"bar \"\"baz\",bing";
    auto row = csv::readCSVRow(escaped_line);
    const std::vector<std::string> expected = { "foo", "bar \"baz", "bing" };
    REQUIRE( row == expected );
}
