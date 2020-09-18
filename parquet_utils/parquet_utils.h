#include <parquet/types.h>
#pragma once

namespace bb {
  ::parquet::Type::type to_parquet_type(std::string s);
  std::string to_string(parquet::Type::type t);

  ::parquet::ConvertedType::type to_parquet_converted_type(std::string s);
  std::string to_string(parquet::ConvertedType::type t);

  ::parquet::LogicalType::Type::type to_parquet_logic_type(std::string s);
  std::string to_string(::parquet::LogicalType::Type::type t);
}
