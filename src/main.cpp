#include <filesystem>
#include <string>
#include <set>
#include <exception>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/endian/conversion.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>

#include "project_content.hpp"
#include "server.hpp"

namespace fs = std::filesystem;

std::string displayHash(const std::array<unsigned int, 5>&);

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " PROJECT_DIR" << std::endl;
        ::exit(EXIT_FAILURE);
    }
    fs::path projectDir{argv[1]};
    ProjectContent project(projectDir);

    for (const auto& file: project.files())
    {
        std::cerr << "Found " << file.first << std::endl;
        std::cerr << displayHash(file.second) << std::endl;
    }

    for(auto it = project.files().begin();
            it != project.files().end(); it++) {
        std::cerr << "Test: " << it->first << std::endl;
        std::cerr << displayHash(it->second) << std::endl;
    }

    boost::asio::io_service ioservice;

    Server svr(ioservice, 8087, project);
    ioservice.run();

    return 0;
}


std::string displayHash(const std::array<unsigned int, 5>& hash)
{
    std::ostringstream buf;
    for (int i = 0; i < 5; i++)
    {
        buf << std::hex << boost::endian::endian_reverse(hash[i]);
    }
    return buf.str();
}
