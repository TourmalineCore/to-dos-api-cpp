#include "simple-model.h"

person::person(const std::string& first,
               const std::string& last,
               const std::string& gender,
               const bool& simple_bool1,
               const std::string& simple_string1,
               unsigned short age)
    : first_(first), last_(last), gender_(gender), 
      simple_bool1_(simple_bool1), simple_string1_(simple_string1), age_(age)
{
}

const std::string& person::first() const 
{
    return first_;
}

const std::string& person::last() const 
{
    return last_;
}

const std::string& person::gender() const 
{
    return gender_;
}

const bool& person::simple_bool1() const 
{
    return simple_bool1_;
}

const std::string& person::simple_string1() const 
{
    return simple_string1_;
}

unsigned short person::age() const 
{
    return age_;
}

void person::age(unsigned short age) 
{
    age_ = age;
}