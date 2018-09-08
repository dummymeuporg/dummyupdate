#pragma once

#include <map>

#include <boost/filesystem/path.hpp>


namespace Dummy {
    class Project {
    public:
        Project(const boost::filesystem::path&);

        const boost::filesystem::path& projectPath() const {
            return m_projectPath;
        }

        const std::map<std::string, std::array<unsigned int, 5>>&
        files() const
        {
            return m_files;
        }

        bool hasFile(const std::string&) const;

    private:
        static std::array<unsigned int, 5> _getHashFile(
            const boost::filesystem::path&);
        // Base project path
        boost::filesystem::path m_projectPath;
        // Keys are filenames, values are sha1 sums.
        std::map<std::string, std::array<unsigned int, 5>> m_files;
    };
}
