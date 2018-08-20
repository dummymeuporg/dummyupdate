#include <string>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
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
}
