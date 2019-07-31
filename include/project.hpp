#pragma once
#include <filesystem>
#include <dummy/core/project.hpp>

class Project : public Dummy::Core::Project {
public:
    Project(const fs::path&);
    void load();
protected:
    void onMapFound(const std::string&) override;
    bool mapExists(const std::string&) override;

};
