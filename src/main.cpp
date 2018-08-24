#define BOOST_LOG_DYN_LINK 1
#include <string>
#include <set>
#include <exception>
#include <iostream>

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>

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
        BOOST_LOG_TRIVIAL(debug) << "Found " << it->first;
    }

    boost::asio::io_service io_service;
    boost::asio::ip::tcp::endpoint tcp_endpoint{boost::asio::ip::tcp::v4(),
                                                8087};
    boost::asio::ip::tcp::acceptor tcp_acceptor{io_service, tcp_endpoint};

    tcp_acceptor.listen();
    ioservice.run();

    return 0;
}
