#include "Customers.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::postgres;

// Column information, column names
const std::string Customers::Cols::_id = "id";
const std::string Customers::Cols::_firstName = "firstName";
const std::string Customers::Cols::_age = "age";

// Table information
const std::string Customers::primaryKeyName = "id";
const bool Customers::hasPrimaryKey = true;
const std::string Customers::tableName = "customers";
const int Customers::primaryKeyNumber = 1;

// Constructor
Customers::Customers(const Row &r, const ssize_t indexOffset) noexcept
{
    size_t offset = (size_t)indexOffset;
    if(offset + getColumnNumber() > r.size())
    {
        LOG_FATAL << "Invalid SQL result for this model";

        return;
    }
    
    size_t index = offset;
    if(!r[index++].isNull())
        id_ = r[index-1].as<PrimaryKeyType>();
    if(!r[index++].isNull())
        firstName_ = r[index-1].as<std::string>();
    if(!r[index++].isNull())
        age_ = r[index-1].as<int32_t>();
};

// // Serialization
// Json::Value Users::toJson() const
// {
//     Json::Value ret;
//     ret["id"] = (Json::Int64)id_;
//     ret["firstName"] = firstName_;
//     ret["age"] = (Json::Int64)age_;

//     return ret;
// }

// Json::Value Users::toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const
// {
//     Json::Value ret;
//     if(pMasqueradingVector.size() == 3)
//     {
//         ret[pMasqueradingVector[0]] = (Json::Int64)id_;
//         ret[pMasqueradingVector[1]] = firstName_;
//         ret[pMasqueradingVector[2]] = (Json::Int64)age_;

//         return ret;
//     }

//     LOG_ERROR << "Masquerade failed";
//     ret["id"] = (Json::Int64)id_;
//     ret["firstName"] = firstName_;
//     ret["age"] = (Json::Int64)age_;

//     return ret;
// }

// // Information about the structure
// const std::string &Customers::getColumnName(size_t index) noexcept
// {
//     switch(index)
//     {
//         case 0: return Cols::_id;
//         case 1: return Cols::_firstName;
//         case 2: return Cols::_age;
//         default: 
//         {
//             static std::string invalidColumnName;

//             return invalidColumnName;
//         }
//     }
// }



// void Customers::updateByPrimaryKey(const DbClientPtr &clientPtr,
//                               const std::function<void(const drogon::orm::Result &)> &rcb,
//                               const std::function<void(const drogon::orm::DrogonDbException &)> &ecb) const
// {
//     static const std::string sql = "UPDATE customers SET firstname=$1,age=$2 WHERE id=$3";
    
//     *clientPtr << sql
//                << firstName_
//                << age_
//                << id_
//                >> [rcb](const Result &r) { rcb(r); }
//                >> [ecb](const DrogonDbException &e, const std::string &) { ecb(e); };
// }

// void Customers::updateByPrimaryKey(const DbClientPtr &clientPtr,
//                               const std::function<void(const drogon::orm::Result &)> &rcb) const
// {
//     updateByPrimaryKey(clientPtr, rcb, [](const DrogonDbException &e) {
//         LOG_ERROR << e.base().what();
//     });
// }

// void Customers::findByPrimaryKey(const DbClientPtr &clientPtr,
//                            const PrimaryKeyType &key,
//                            const std::function<void(Customers)> &rcb,
//                            const std::function<void(const drogon::orm::DrogonDbException &)> &ecb)
// {
//     static const std::string sql = "SELECT * FROM customers WHERE id=$1";
    
//     *clientPtr << sql
//                << key
//                >> [rcb](const Result &r) {
//                    if (r.size() == 0)
//                    {
//                        rcb(Customers());
//                    }
//                    else
//                    {
//                        rcb(Customers(r[0]));
//                    }
//                }
//                >> [ecb](const DrogonDbException &e, const std::string &) { ecb(e); };
// }

// void Customers::findAll(const DbClientPtr &clientPtr,
//                    const std::function<void(std::vector<Customers>)> &rcb,
//                    const std::function<void(const drogon::orm::DrogonDbException &)> &ecb)
// {
//     static const std::string sql = "SELECT * FROM customers";
    
//     *clientPtr << sql
//                >> [rcb](const Result &r) {
//                    std::vector<Customers> ret;
//                    ret.reserve(r.size());
//                    for (auto const &row : r)
//                    {
//                        ret.emplace_back(Customers(row));
//                    }
//                    rcb(std::move(ret));
//                }
//                >> [ecb](const DrogonDbException &e, const std::string &) { ecb(e); };
// }

std::string Customers::sqlForInserting(bool &needSelection) const
{
    std::string sql = "INSERT INTO ";
    sql += tableName;
    sql += " (";
    
    sql += "firstName,age";
    sql += ") VALUES (";
    
    sql += "$1,$2";
    sql += ")";

    if (hasPrimaryKey) {
        sql += " RETURNING ";
        sql += primaryKeyName;
        needSelection = true;
    } else {
        needSelection = false;
    }
    
    return sql;
};

void Customers::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    binder << firstName_;
    binder << age_;
};

// const std::vector<std::string> &Customers::insertColumns() const
// {
//     static const std::vector<std::string> columns = {
//         "firstName", 
//         "age"
//     };

//     return columns;
// }