//-----------------------------------------------------------------------------
// Copyright 2021 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//----------------------------------------------------------------------------

#ifndef SRC_IR_TAG_CHECK_H_
#define SRC_IR_TAG_CHECK_H_

#include "absl/strings/str_format.h"
#include "absl/strings/substitute.h"
#include "src/ir/access_path.h"
#include "src/ir/datalog_print_context.h"
#include "src/ir/predicate.h"

namespace raksha::ir {

// A class representing a check of some predicate involving tags on a
// particular AccessPath.
class TagCheck {
 public:
  TagCheck(AccessPath access_path, std::unique_ptr<Predicate> predicate)
      : access_path_(std::move(access_path)),
        predicate_(std::move(predicate)) {}

  // Print out the tag check as datalog facts. Note that this emits two
  // facts: an isCheck fact and a check fact. We produce a unique label for
  // each check using the DatalogPrintContext. We unconditionally add that
  // label to isCheck and add that label to check only if the check's
  // predicate passes. This allows us, in a driver, to assert that the
  // elements of isCheck and check are equal. If that is the case, all checks
  // passed. If it is not, at least one check failed.
  std::string ToDatalog(DatalogPrintContext &ctxt) const {
    constexpr absl::string_view kCheckHasTagFormat =
        R"(isCheck("$0", "$1"). check("$0", owner, "$1") :-
  ownsAccessPath(owner, "$1"), $2.)";
    std::string check_label = ctxt.GetUniqueCheckLabel();
    return absl::Substitute(kCheckHasTagFormat, check_label,
                            access_path_.ToDatalog(ctxt),
                            predicate_->ToDatalogRuleBody(access_path_, ctxt));
  }

  bool operator==(const TagCheck &other) const {
    return (access_path_ == other.access_path_) &&
    // If the two predicates are pointer equal, they are necessarily equal.
    // If they are not pointer equal, they may still be equal if they are
    // fully structurally equal.
        ((predicate_ == other.predicate_) ||
         (*predicate_ == *other.predicate_));
  }

  const AccessPath& access_path() const { return access_path_; }

 private:
  // The access path which is the subject of the check.
  AccessPath access_path_;
  // The predicate being checked upon `access_path`. Note that this is a
  // non-owning pointer: while it is tempting to make this `Predicate` owned
  // by this `TagCheck`, this is incompatible with our current method of
  // having separate copies of a `TagCheck` for the spec and the
  // implementation. `Predicate`s are currently owned by the `ParticleSpec`
  // which created the spec version of the `TagCheck` via the
  // `PredicateDecoder`.
  std::unique_ptr<Predicate> predicate_;
};

}  // namespace raksha::ir

#endif  // SRC_IR_TAG_CHECK_H_
