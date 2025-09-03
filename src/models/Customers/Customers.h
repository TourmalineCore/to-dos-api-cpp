#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <trantor/utils/Date.h>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

using namespace drogon::orm;

namespace drogon_model 
{
namespace postgres
{

class Customers {
  public:
    // Column information, column names
    struct Cols
    {
        static const std::string _id;
        static const std::string _firstName;
        static const std::string _age;
    };

    // Table information
    static const std::string tableName;           // Name of the table in the DB
    static const bool hasPrimaryKey;              // Is there a primary key?
    static const std::string primaryKeyName;      // Primary key column name
    static const int primaryKeyNumber;            // Number of columns in the primary key

    using PrimaryKeyType = int32_t;               // Primary Key Type

    // Constructors
    Customers() noexcept = default; 
    explicit Customers(const Row &r, const ssize_t indexOffset = 0) noexcept;

    // Destructor
    ~Customers() = default;

    // // Getters (for each field)
    // const PrimaryKeyType &getValueOfId() const noexcept { return id_; };
    // const std::string &getValueOfFirstName() const noexcept { return firstName_; };
    // const int32_t &getValueOfAge() const noexcept { return age_; };

    // Setters (for each field)
    void setId(const PrimaryKeyType &pId) noexcept { id_ = pId; };
    void setFirstName(const std::string &pFirstName) noexcept { firstName_ = pFirstName; };
    void setFirstName(std::string &&pFirstName) noexcept { firstName_ = std::move(pFirstName); }; // Move version for strings
    void setAge(const int32_t &pAge) noexcept { age_ = pAge; };

    // // Methods for working with NULL values (for each field)
    // void setIdToNull() noexcept { id_ = PrimaryKeyType(); };
    // void setFirstNameToNull() noexcept { firstName_.clear(); };
    // void setAgeToNull() noexcept { age_.clear(); };

    // // Serialization
    // Json::Value toJson() const;
    // Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;

    // Information about the structure
    static size_t getColumnNumber() noexcept { return 3; };          // Number of columns
    // static const std::string &getColumnName(size_t index) noexcept;  // Column name by index


    
    // void updateByPrimaryKey(const DbClientPtr &clientPtr,
    //                        const std::function<void(const drogon::orm::Result &)> &rcb,
    //                        const std::function<void(const drogon::orm::DrogonDbException &)> &ecb) const;
    
    // void updateByPrimaryKey(const DbClientPtr &clientPtr,
    //                        const std::function<void(const drogon::orm::Result &)> &rcb) const;
    
    // static void findByPrimaryKey(const DbClientPtr &clientPtr,
    //                             const PrimaryKeyType &key,
    //                             const std::function<void(Customers)> &rcb,
    //                             const std::function<void(const drogon::orm::DrogonDbException &)> &ecb);
    
    // static void findAll(const DbClientPtr &clientPtr,
    //                    const std::function<void(std::vector<Customers>)> &rcb,
    //                    const std::function<void(const drogon::orm::DrogonDbException &)> &ecb);

    std::string sqlForInserting(bool &needSelection) const;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    // const std::vector<std::string> &insertColumns() const;

  private:
    // Table fields
    PrimaryKeyType id_ = 0;
    std::string firstName_;
    int32_t age_;

};
  
} // namespace postgres
} // namespace drogon_model