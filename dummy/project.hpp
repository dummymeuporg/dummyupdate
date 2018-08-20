#pragma once

#include <map>

namespace boost {
    namespace filesystem {
        class path;
    }
}

namespace Dummy {
    class Project {
    public:
        Project(const boost::filesystem::path&);
        const std::map<std::string, std::string>& files() const {
            return m_files;
        }

    private:
        // Keys are filenames, values are sha1 sums.
        std::map<std::string, std::string> m_files;
    };
}
