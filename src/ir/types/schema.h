#ifndef SRC_IR_TYPES_SCHEMA_H_
#define SRC_IR_TYPES_SCHEMA_H_

#include <optional>

#include "absl/container/flat_hash_map.h"
#include "absl/container/flat_hash_set.h"
#include "src/ir/access_path_selectors_set.h"
#include "src/ir/types/type.h"

namespace raksha::ir::types {

class Schema {
 public:
  raksha::ir::AccessPathSelectorsSet GetAccessPathSelectorsSet() const;

  const std::optional<std::string>& name() const { return name_; }

  const absl::flat_hash_map<std::string, Type>& fields() const {
    return fields_;
  }

  friend class TypeFactory;

 private:
  explicit Schema(std::optional<std::string> name,
                  absl::flat_hash_map<std::string, Type> fields)
      : name_(std::move(name)), fields_(std::move(fields)) {}

  std::optional<std::string> name_;
  absl::flat_hash_map<std::string, Type> fields_;
};

}  // namespace raksha::ir::types

#endif  // SRC_IR_TYPES_SCHEMA_H_
