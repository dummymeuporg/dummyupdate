#include <string>
#include <set>
#include <exception>
#include <iostream>

#include <boost/filesystem.hpp>

#include "dummy/project.hpp"

namespace fs = boost::filesystem;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " PROJECT_DIR" << std::endl;
        ::exit(EXIT_FAILURE);
    }
    fs::path projectDir{argv[1]};
    Dummy::Project project(projectDir);
    for (auto it = project.files().begin(); it != project.files().end(); ++it)
    {
        std::cout << it->first << std::endl;
    }
    return 0;
}
