#include "parquet_utils.h"

struct parquet_string_to_type_mapping {
  ::parquet::Type::type type;
  std::string type_str;
};

static std::vector<parquet_string_to_type_mapping> mapping_s{
  {parquet::Type::BOOLEAN,              "BOOLEAN"},
  {parquet::Type::INT32,                "INT32"},
  {parquet::Type::INT64,                "INT64"},
  {parquet::Type::INT96,                "INT96"},
  {parquet::Type::FLOAT,                "FLOAT"},
  {parquet::Type::DOUBLE,               "DOUBLE"},
  {parquet::Type::BYTE_ARRAY,           "BYTE_ARRAY"},
  {parquet::Type::FIXED_LEN_BYTE_ARRAY, "FIXED_LEN_BYTE_ARRAY"},
  {parquet::Type::UNDEFINED,            "UNDEFINED"}
};


struct parquet_string_to_converted_type_mapping {
  ::parquet::ConvertedType::type type;
  std::string type_str;
};

static std::vector<parquet_string_to_converted_type_mapping> converted_type_mapping_s = {
  {::parquet::ConvertedType::NONE,             "NONE"},
  {::parquet::ConvertedType::UTF8,             "UTF8"},
  {::parquet::ConvertedType::MAP,              "MAP"},
  {::parquet::ConvertedType::MAP_KEY_VALUE,    "MAP_KEY_VALUE"},
  {::parquet::ConvertedType::LIST,             "LIST"},
  {::parquet::ConvertedType::ENUM,             "ENUM"},
  {::parquet::ConvertedType::DECIMAL,          "DECIMAL"},
  {::parquet::ConvertedType::DATE,             "DATE"},
  {::parquet::ConvertedType::TIME_MILLIS,      "TIME_MILLIS"},
  {::parquet::ConvertedType::TIME_MICROS,      "TIME_MICROS"},
  {::parquet::ConvertedType::TIMESTAMP_MILLIS, "TIMESTAMP_MILLIS"},
  {::parquet::ConvertedType::TIMESTAMP_MICROS, "TIMESTAMP_MICROS"},
  {::parquet::ConvertedType::UINT_8,           "UINT_8"},
  {::parquet::ConvertedType::UINT_16,          "UINT_16"},
  {::parquet::ConvertedType::UINT_32,          "UINT_32"},
  {::parquet::ConvertedType::UINT_64,          "UINT_64"},
  {::parquet::ConvertedType::INT_8,            "INT_8"},
  {::parquet::ConvertedType::INT_16,           "INT_16"},
  {::parquet::ConvertedType::INT_32,           "INT_32"},
  {::parquet::ConvertedType::INT_64,           "INT_64"},
  {::parquet::ConvertedType::JSON,             "JSON"},
  {::parquet::ConvertedType::BSON,             "BSON"},
  {::parquet::ConvertedType::INTERVAL,         "INTERVAL"},
  {::parquet::ConvertedType::NA,               "NA"},
  {::parquet::ConvertedType::UNDEFINED,        "UNDEFINED"}
};

struct parquet_string_to_logic_type_mapping {
  ::parquet::LogicalType::Type::type type;
  std::string type_str;
};

static std::vector<parquet_string_to_logic_type_mapping> logic_type_mapping_s = {
  {::parquet::LogicalType::Type::UNKNOWN, "UNKNOWN"},
  {::parquet::LogicalType::Type::STRING, "STRING"},
  {::parquet::LogicalType::Type::MAP, "MAP"},
  {::parquet::LogicalType::Type::LIST, "LIST"},
  {::parquet::LogicalType::Type::ENUM, "ENUM"},
  {::parquet::LogicalType::Type::DECIMAL, "DECIMAL"},
  {::parquet::LogicalType::Type::DATE, "DATE"},
  {::parquet::LogicalType::Type::TIME, "TIME"},
  {::parquet::LogicalType::Type::TIMESTAMP, "TIMESTAMP"},
  {::parquet::LogicalType::Type::INTERVAL, "INTERVAL"},
  {::parquet::LogicalType::Type::INT, "INT"},
  {::parquet::LogicalType::Type::NIL, "NIL"},
  {::parquet::LogicalType::Type::JSON, "JSON"},
  {::parquet::LogicalType::Type::BSON, "BSON"},
  {::parquet::LogicalType::Type::UUID, "UUID"},
  {::parquet::LogicalType::Type::NONE, "NONE"}
};

namespace bb {
  parquet::Type::type to_parquet_type(std::string s) {
    for (auto const &i : mapping_s) {
      if (s == i.type_str)
        return i.type;
    }
    std::string what = "unknown arrow type: " + s;
    throw (std::runtime_error(what));
  }

  std::string to_string(parquet::Type::type t) {
    for (auto const &i : mapping_s) {
      if (t == i.type)
        return i.type_str;
    }
    std::string what = "unknown arrow type: " + t;
    throw (std::runtime_error(what));
  }

  ::parquet::ConvertedType::type to_parquet_converted_type(std::string s) {
    for (auto const &i : converted_type_mapping_s) {
      if (s == i.type_str)
        return i.type;
    }
    std::string what = "unknown parquet_converted_type: " + s;
    throw (std::runtime_error(what));
  }

  std::string to_string(parquet::ConvertedType::type t) {
    for (auto const &i : converted_type_mapping_s) {
      if (t == i.type)
        return i.type_str;
    }
    std::string what = "unknown ConvertedType type: " + t;
    throw (std::runtime_error(what));
  }

  ::parquet::LogicalType::Type::type to_parquet_logic_type(std::string s) {
    for (auto const &i : logic_type_mapping_s) {
      if (s == i.type_str)
        return i.type;
    }
    std::string what = "unknown parquet_converted_type: " + s;
    throw (std::runtime_error(what));
  }

  std::string to_string(::parquet::LogicalType::Type::type t) {
    for (auto const &i : logic_type_mapping_s) {
      if (t == i.type)
        return i.type_str;
    }
    std::string what = "unknown LogicType type: " + t;
    throw (std::runtime_error(what));
  }


}

