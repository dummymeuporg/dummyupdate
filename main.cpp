#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>

namespace pt = boost::property_tree;

void load_file(const std::string& filename)
{
    pt::ptree tree;

    pt::read_xml(filename, tree);

    BOOST_FOREACH(pt::ptree::value_type& v, tree.get_child("project.maps"))
    {
        std::cout << v.first.data() << std::endl;
        BOOST_FOREACH(pt::ptree::value_type& w, v.second.get_child("<xmlattr>"))
        {
            std::cout << w.second.data() << std::endl;
        }
    }
}

int main(void)
{
    load_file("project.xml");
    return 0;
}
