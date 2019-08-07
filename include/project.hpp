#pragma once
#include <filesystem>
#include <dummy/core/project.hpp>

namespace fs = std::filesystem;

class Project : public Dummy::Core::Project {
public:
    Project(const fs::path&);
    void load();
protected:
    void onMapFound(const std::string&) override;
    bool mapExists(const std::string&) override;
private:
    // Methods
    void getMaps();
    void getResources();
    static std::array<uint32_t, 5> sha1sum(const fs::path&);

    // Attributes
    std::map<std::string, std::array<uint32_t, 5>> m_files;

};
