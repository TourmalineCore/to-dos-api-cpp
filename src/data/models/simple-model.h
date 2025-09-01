// #pragma once

// #include <string>

// #include <odb/core.hxx>

// #pragma db model version(1, 2)
// #pragma db object table("person") schema("public")
// class person
// {
// public:
//   person (const std::string& first,
//           const std::string& last,
//           const std::string& gender,
//           const bool& simple_bool1,
//           const std::string& simple_string1,
//           unsigned short age);

//   const std::string& first () const;
//   const std::string& last () const;
//   const std::string& gender () const;
//   const bool& simple_bool1 () const;
//   const std::string& simple_string1 () const;

//   unsigned short age () const;
//   void age (unsigned short);

// private:
//   person () {}

//   friend class odb::access;

//   #pragma db id auto
//   unsigned long long id_;

//   std::string first_;
//   std::string last_;

//   std::string gender_;
//   bool simple_bool1_;
//   std::string simple_string1_;
//   unsigned short age_;
// };