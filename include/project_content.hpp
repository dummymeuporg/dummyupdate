#pragma once

#include <boost/filesystem.hpp>

#include "core/project.hpp"

namespace fs = boost::filesystem;

class ProjectContent : public Dummy::Core::Project {
public:
    ProjectContent(const fs::path& projectPath);

    const std::map<std::string, std::array<uint32_t, 5>>& files() const {
        return m_files;
    }

    bool hasFile(const std::string&) const;


private:
    void _getMaps();
    void _getResources();
    static std::array<uint32_t, 5> _sha1sum(const fs::path&);
    std::map<std::string, std::array<uint32_t, 5>> m_files;
};
