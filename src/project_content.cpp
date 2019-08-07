#include <iostream>

#include <boost/endian/conversion.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/uuid/detail/sha1.hpp>

#include "project_content.hpp"

ProjectContent::ProjectContent(const fs::path& projectPath) :
    Dummy::Core::Project(projectPath)
{
    _getMaps();
    _getResources();
}

void ProjectContent::_getMaps() {
    for (const auto& map: maps()) {
        std::string filename(map + ".map");
        fs::path filePath(fs::path("maps") / filename);
        fs::path fullPath(projectPath() / filePath);

        if (!fs::exists(fullPath)) {
            // throw an exception?
            std::cerr << "Could not find " << filePath << std::endl;
        } else {
            m_files[filePath.string()] = _sha1sum(fullPath);
        }
    }
}

void ProjectContent::_getResources() {
    for (const auto& folder: {"chipsets", "sounds"}) {
        try {
            for (auto& entry: boost::make_iterator_range(
                    fs::directory_iterator(projectPath() / folder), {})) {
                std::string key(
                    fs::relative(entry.path(), projectPath()).string()
                );
                m_files[key] = _sha1sum(entry);
            }
        } catch(const fs::filesystem_error& e) {
            std::cerr << "Could not list folder " << folder << "!";
        }
    }
}

std::array<uint32_t, 5> ProjectContent::_sha1sum(const fs::path& path) {
    boost::uuids::detail::sha1 s;
    std::ifstream file(path.string());

    const int chunkSize = 512;
    unsigned int _hash[5];

    while (!file.eof())
    {
        char chunk[chunkSize] = {'\0'};
        file.read(chunk, chunkSize);
        std::streamsize n = file.gcount();

        if (n != 0)
        {
            s.process_bytes(chunk, n);
        }
    }
    s.get_digest(_hash);

    std::array<uint32_t, 5> hash;
    for (int i = 0; i < 5; i++)
    {
        hash[i] = boost::endian::endian_reverse(_hash[i]);
    }

    return hash;
}

bool ProjectContent::hasFile(const std::string& filename) const {
    return m_files.find(filename) != m_files.end();
}

