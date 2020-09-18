#include <parquet/arrow/schema.h>
//#include "parquet_transformation_spec.h"
#pragma once

namespace tickup{
  std::shared_ptr<::parquet::schema::GroupNode> toGroupNode(std::shared_ptr<arrow::Schema>);

  std::shared_ptr<::parquet::schema::GroupNode> toGroupNode(const parquet::SchemaDescriptor*);


  //std::shared_ptr<::parquet::schema::GroupNode> toGroupNode(const std::vector<tickup::parquet_column_spec>& columns);
  //tickup::parquet_transformation_spec toColumnSpec(std::shared_ptr<arrow::Schema>);
}