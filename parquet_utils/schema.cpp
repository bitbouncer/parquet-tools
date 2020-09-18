#include "schema.h"
#include <arrow/type.h>
#include <glog/logging.h>

namespace tickup {
  std::shared_ptr<parquet::schema::GroupNode> toGroupNode(std::shared_ptr<arrow::Schema> schema) {
    LOG(INFO) << "schema: " << schema->ToString();

    for (auto i : schema->fields()) {
      LOG(INFO) << "name: " << i->name() << " type: " << i->type()->name() << " " << i->type()->id();
    }

    parquet::schema::NodeVector fields;

    for (auto i : schema->fields()) {
      LOG(INFO) << "name: " << i->name() << " type: " << i->type()->name() << " " << i->type()->id();

      switch (i->type()->id()) {
        /// A NULL type having no physical storage
        case arrow::Type::NA:
          assert(false);
          // how do we represent a NULL column??
          /*fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::NULL,
            parquet::ConvertedType::UINT_8)); // the converted type seems wrong??
          */
          break;

          /// Boolean as 1 bit, LSB bit-packed ordering
        case arrow::Type::BOOL:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::BOOLEAN,
            parquet::ConvertedType::NONE));
          break;

          /// Unsigned 8-bit little-endian integer
        case arrow::Type::UINT8:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT32,
            parquet::ConvertedType::UINT_8));
          break;

          /// Signed 8-bit little-endian integer
        case arrow::Type::INT8:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT32,
            parquet::ConvertedType::INT_8));

          /// Unsigned 16-bit little-endian integer
        case arrow::Type::UINT16:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT32,
            parquet::ConvertedType::UINT_16));
          break;

          /// Signed 16-bit little-endian integer
        case arrow::Type::INT16:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT32,
            parquet::ConvertedType::INT_16));
          break;

          /// Unsigned 32-bit little-endian integer
        case arrow::Type::UINT32:
          // is this even remotely right??
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT32,
            parquet::ConvertedType::UINT_32));
          break;

          /// Signed 32-bit little-endian integer
        case arrow::Type::INT32:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT32,
            parquet::ConvertedType::INT_32));
          break;

          /// Unsigned 64-bit little-endian integer
        case arrow::Type::UINT64:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT64,
            parquet::ConvertedType::UINT_64));
          break;

          /// Signed 64-bit little-endian integer
        case arrow::Type::INT64:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT64,
            parquet::ConvertedType::INT_64));
          break;

          /// 2-byte floating point value
        case arrow::Type::HALF_FLOAT:
          // is converted type right?
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::FLOAT,
            parquet::ConvertedType::NONE));
          break;

          /// 4-byte floating point value
        case arrow::Type::FLOAT:
          // is converted type right?
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::FLOAT,
            parquet::ConvertedType::NONE));
          break;

          /// 8-byte floating point value
        case arrow::Type::DOUBLE:
          // is converted type right?
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::DOUBLE,
            parquet::ConvertedType::NONE));
          break;

          /// UTF8 variable-length string as List<Char>
        case arrow::Type::STRING:
          fields.push_back(parquet::schema::PrimitiveNode::Make(i->name(), parquet::Repetition::OPTIONAL,
                                                                  parquet::Type::BYTE_ARRAY, parquet::ConvertedType::UTF8));
          break;

          /// Variable-length bytes (no guarantee of UTF8-ness)
        case arrow::Type::BINARY:
          fields.push_back(parquet::schema::PrimitiveNode::Make(i->name(), parquet::Repetition::OPTIONAL,
                                                                  parquet::Type::BYTE_ARRAY, parquet::ConvertedType::UTF8));
          break;

          /// Fixed-size binary. Each value occupies the same number of bytes
        case arrow::Type::FIXED_SIZE_BINARY:
          assert(false);
          //fields.push_back(parquet::schema::PrimitiveNode::Make(
          //  i->name(), parquet::Repetition::REQUIRED, parquet::Type::FIXED_LEN_BYTE_ARRAY,
          //  parquet::ConvertedType::NONE, i->type()->layout()->));
          // how do we get length of field here???
          break;

          /// int32_t days since the UNIX epoch
        case arrow::Type::DATE32:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT32,
            parquet::ConvertedType::INT_32));
          break;

          /// int64_t milliseconds since the UNIX epoch
        case arrow::Type::DATE64:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT64,
            parquet::ConvertedType::INT_64));
          break;

          /// Exact timestamp encoded with int64 since UNIX epoch
          /// Default unit millisecond
        case arrow::Type::TIMESTAMP:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT64,
            parquet::ConvertedType::INT_64));
          break;

          /// Time as signed 32-bit integer, representing either seconds or
          /// milliseconds since midnight
        case arrow::Type::TIME32:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT32,
            parquet::ConvertedType::INT_32));
          break;

          /// Time as signed 64-bit integer, representing either microseconds or
          /// nanoseconds since midnight
        case arrow::Type::TIME64:
          fields.push_back(parquet::schema::PrimitiveNode::Make(
            i->name(), parquet::Repetition::REQUIRED, parquet::Type::INT64,
            parquet::ConvertedType::INT_64));
          break;

        case arrow::Type::INTERVAL_MONTHS:
          assert(false);
          break;

        case arrow::Type::INTERVAL_DAY_TIME:
          assert(false);
          break;

        /// YEAR_MONTH or DAY_TIME interval in SQL style
        //case arrow::Type::INTERVAL:
        //  assert(false);
        //  break;

          /// Precision- and scale-based decimal type. Storage type depends on the
          /// parameters.
        case arrow::Type::DECIMAL:
          assert(false);
          break;
          /// A list of some logical data type
        case arrow::Type::LIST:
          assert(false);
          break;
          /// Struct of logical types
        case arrow::Type::STRUCT:
          assert(false);
          break;

          /// Unions of logical types
          case arrow::Type::SPARSE_UNION:
            assert(false);
            break;

          case arrow::Type::DENSE_UNION:
            assert(false);
            break;

          /// Dictionary-encoded type, also called "categorical" or "factor"
          /// in other programming languages. Holds the dictionary value
          /// type but not the dictionary itself, which is part of the
          /// ArrayData struct
        case arrow::Type::DICTIONARY:
          assert(false);
          break;
          /// Map, a repeated struct logical type
        case arrow::Type::MAP:
          assert(false);
          break;
          /// Custom data type, implemented by user
        case arrow::Type::EXTENSION:
          assert(false);
          break;
          /// Fixed size list of some logical type
        case arrow::Type::FIXED_SIZE_LIST:
          assert(false);
          break;
          /// Measure of elapsed time in either seconds, milliseconds, microseconds
          /// or nanoseconds.
        case arrow::Type::DURATION:
          assert(false);
          break;
          /// Like STRING, but with 64-bit offsets
        case arrow::Type::LARGE_STRING:
          assert(false);
          break;
          /// Like BINARY, but with 64-bit offsets
        case arrow::Type::LARGE_BINARY:
          assert(false);
          break;
          /// Like LIST, but with 64-bit offsets
        case arrow::Type::LARGE_LIST:
          assert(false);
          break;

        case arrow::Type::MAX_ID:
          assert(false);
          break;
      }
    }

    return std::static_pointer_cast<parquet::schema::GroupNode>(
      parquet::schema::GroupNode::Make("schema", parquet::Repetition::REQUIRED, fields));
  }

  std::shared_ptr<::parquet::schema::GroupNode> toGroupNode(const parquet::SchemaDescriptor* schema_descriptor){
    parquet::schema::NodeVector fields;
    schema_descriptor->num_columns();
    for (int i=0; i!=schema_descriptor->num_columns(); ++i){
    const auto root = schema_descriptor->GetColumnRoot(i);
    const parquet::ColumnDescriptor* column_descriptor = schema_descriptor->Column(i);
    assert(root->is_primitive());
      fields.push_back(parquet::schema::PrimitiveNode::Make(
        root->name(),
        root->repetition(),
        column_descriptor->physical_type(),
        root->converted_type()
        ));
    }
      return std::static_pointer_cast<parquet::schema::GroupNode>(
      parquet::schema::GroupNode::Make("schema", parquet::Repetition::REQUIRED, fields));
  }


/*
 * BOOLEAN = 0,
    INT32 = 1,
    INT64 = 2,
    INT96 = 3,
    FLOAT = 4,
    DOUBLE = 5,
    BYTE_ARRAY = 6,
    FIXED_LEN_BYTE_ARRAY = 7,
 */


}