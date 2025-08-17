#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

// Link to documentation where you can read about DTO (Data Transfer Object)
// https://oatpp.io/docs/components/dto/
#include OATPP_CODEGEN_BEGIN(DTO)

class Task : public oatpp::DTO {

  // Link to documentation where you can read about Codegen macoro
  // https://oatpp.io/api/latest/oatpp/codegen/dto/base_define/
  DTO_INIT(Task, DTO)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, description);
  DTO_FIELD(Boolean, status);

};

#include OATPP_CODEGEN_END(DTO)