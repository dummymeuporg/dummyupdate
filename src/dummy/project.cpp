#define BOOST_LOG_DYN_LINK 1
#include <array>
#include <fstream>
#include <iostream>
#include <string>

#include <boost/foreach.hpp>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/uuid/sha1.hpp>

#include "dummy/project.hpp"

namespace pt = boost::property_tree;
namespace fs = boost::filesystem;

Dummy::Project::Project(const fs::path& projectDirectory)
    : m_projectPath(projectDirectory)
{
    pt::ptree tree;

    pt::read_xml((m_projectPath / "project.xml").string(), tree);

    BOOST_FOREACH(pt::ptree::value_type& v, tree.get_child("project.maps"))
    {
        BOOST_FOREACH(pt::ptree::value_type& w,
                      v.second.get_child("<xmlattr>"))
        {
            fs::path mapPath(fs::path("maps/" + w.second.data() + ".map"));
            if (!fs::exists(m_projectPath / mapPath))
            {
                BOOST_LOG_TRIVIAL(error) << "Map " << mapPath
                    << " does not exist.";
            }
            else
            {
                m_files["maps/" + w.second.data() + ".map"] =
                    _getHashFile(m_projectPath / mapPath);
            }
        }
    }

    // Browse chipsets and sounds
    for (auto& folder: {"chipsets", "sounds"})
    {
       BOOST_LOG_TRIVIAL(debug) << "Folder " << folder;
       try {
           for (auto& entry: boost::make_iterator_range(
                    fs::directory_iterator(m_projectPath / folder), {}))
           {
                BOOST_LOG_TRIVIAL(debug) << "\tFile " << entry;
                m_files[fs::relative(entry.path(),
                                     m_projectPath).string()] = 
                    _getHashFile(entry);
           }
       } catch (const boost::filesystem::filesystem_error& e) {
            BOOST_LOG_TRIVIAL(error) << "Could not list folder " << folder
                << "! Skipping.";
       }
    }
}

std::array<unsigned int, 5>
Dummy::Project::_getHashFile(const boost::filesystem::path& path)
{
    boost::uuids::detail::sha1 s;
    std::ifstream file(path.string());

    const int chunkSize = 512;
    unsigned int _hash[5];

    while (!file.eof())
    {
        char chunk[chunkSize];
        file.read(chunk, chunkSize);
        s.process_bytes(chunk, chunkSize);
    }
    s.get_digest(_hash);

    std::array<unsigned int, 5> hash;
    for (int i = 0; i < 5; i++)
    {
        hash[i] = _hash[i];
    }

    return hash;
}
