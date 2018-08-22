#define BOOST_LOG_DYN_LINK 1
#include <array>
#include <string>
#include <iostream>

#include <boost/foreach.hpp>
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/range/iterator_range.hpp>

#include "dummy/project.hpp"

namespace pt = boost::property_tree;
namespace fs = boost::filesystem;

Dummy::Project::Project(const fs::path& projectDirectory)
{
    pt::ptree tree;

    pt::read_xml((projectDirectory / "project.xml").string(), tree);

    BOOST_FOREACH(pt::ptree::value_type& v, tree.get_child("project.maps"))
    {
        BOOST_FOREACH(pt::ptree::value_type& w,
                      v.second.get_child("<xmlattr>"))
        {
            m_files["maps/" + w.second.data() + ".map"] = "";
        }
    }

    // Browse chipsets and sounds
    for (auto& folder: {"chipsets", "sounds"})
    {
       BOOST_LOG_TRIVIAL(debug) << "Folder " << folder;
       try {
           for (auto& entry: boost::make_iterator_range(
                    fs::directory_iterator(projectDirectory / folder), {}))
           {
                BOOST_LOG_TRIVIAL(debug) << "\tFile " << entry;
                m_files[fs::relative(entry.path(),
                                     projectDirectory).string()] = "";
           }
       } catch (const boost::filesystem::filesystem_error& e) {
            BOOST_LOG_TRIVIAL(error) << "Could not list folder " << folder
                << "! Skipping.";
       }
    }
}
