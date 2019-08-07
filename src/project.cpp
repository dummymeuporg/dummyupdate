#include <iostream>
#include "project.hpp"

Project::Project(const fs::path& path)
    : Dummy::Core::Project(path)
{}

void Project::load() {
    Dummy::Core::Project::load();
    // Load resources (chipsets, maps)...
}

void Project::getMaps() {
    for (const auto& map: maps()) {
        std::string filename(map + ".map");
        fs::path filePath(fs::path("maps") / filename);
        fs::path fullPath(projectPath() / filePath);

        if (!fs::exists(fullPath)) {
            // throw an exception?
            std::cerr << "Could not find " << filePath << std::endl;
        } else {
            m_files[filePath.string()] = sha1sum(fullPath);
        }
    }
}

void Project::getResources() {

}

std::array<uint32_t, 5> Project::sha1sum(const fs::path& path) {

}

void Project::onMapFound(const std::string&) {

}

bool Project::mapExists(const std::string&) {

}

