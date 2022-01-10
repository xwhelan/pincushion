project(pincushion)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)
set (CMAKE_CXX_STANDARD 11)

include(CTest)

# These tests can use the Catch2-provided main
add_executable(tests test_csv.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain pincushion)
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

# These tests need their own main
# add_executable(custom-main-tests test.cpp test-main.cpp)
# target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)

add_test(NAME tests COMMAND tests)
