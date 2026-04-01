#pragma once

#include <ctime>
#include <odb/core.hxx>
#include <odb/nullable.hxx>
#include <string>

#pragma db object table("todo")
class ToDo
{
public:
    ToDo() = default;
    ToDo(const std::string& name, std::time_t createdAtUtc)
    : name_(name),
      createdAtUtc_(createdAtUtc),
      deletedAtUtc_()
    {}

    std::uint64_t id() const { return id_; }
    const std::string& name() const { return name_; }
    std::time_t createdAtUtc() const { return createdAtUtc_; }
    const odb::nullable<std::time_t>& deletedAtUtc() const { return deletedAtUtc_; }

    void name(const std::string& n) { name_ = n; }
    void createdAtUtc(std::time_t t) { createdAtUtc_ = t; }
    void deletedAtUtc(std::time_t t) { deletedAtUtc_ = t; }

private:
    friend class odb::access;

#pragma db id auto
    std::uint64_t id_;

    std::string name_;
#pragma db type("BIGINT")
    std::time_t createdAtUtc_;

#pragma db null
#pragma db type("BIGINT")
    odb::nullable<std::time_t> deletedAtUtc_;
};