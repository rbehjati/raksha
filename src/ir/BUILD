#-------------------------------------------------------------------------------
# Copyright 2021 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#-------------------------------------------------------------------------------

load("//build_defs:test_helpers.bzl", "extracted_datalog_string_test")

licenses(["notice"])

package(default_visibility = ["//src:__subpackages__"])

cc_library(
    name = "new_ir",
    hdrs = [
        "block.h",
        "data_decl.h",
        "operation.h",
        "operator.h",
        "storage.h",
        "value.h",
    ],
    deps = [
        "//src/ir/types",
        "@absl//absl/container:flat_hash_map",
    ],
)

cc_library(
    name = "attribute",
    hdrs = ["attribute.h"],
    deps = [
        "//src/utils:intrusive_ptr",
        "@absl//absl/container:flat_hash_map",
        "@absl//absl/strings",
    ],
)

cc_test(
    name = "attribute_test",
    srcs = ["attribute_test.cc"],
    deps = [
        ":attribute",
        "//src/common/testing:gtest",
    ],
)

cc_library(
    name = "data_decl",
    hdrs = ["data_decl.h"],
    deps = [
        "//src/ir/types",
        "@absl//absl/strings",
    ],
)

cc_test(
    name = "data_decl_test",
    srcs = ["data_decl_test.cc"],
    deps = [
        ":data_decl",
        "//src/common/testing:gtest",
        "//src/ir/types",
    ],
)

cc_library(
    name = "operator",
    hdrs = ["operator.h"],
    deps = [
        "@absl//absl/strings",
    ],
)

cc_test(
    name = "operator_test",
    srcs = ["operator_test.cc"],
    deps = [
        ":operator",
        "//src/common/testing:gtest",
    ],
)

cc_library(
    name = "ir",
    srcs = [
        "access_path_root.cc",
        "particle_spec.cc",
    ],
    hdrs = [
        "datalog_print_context.h",
        "derives_from_claim.h",
        "edge.h",
        "handle_connection_spec.h",
        "particle_spec.h",
        "predicate.h",
        "system_spec.h",
        "tag_check.h",
        "tag_claim.h",
    ],
    deps = [
        ":access_path",
        "//src/common/logging",
        "//src/ir/proto:access_path",
        "//src/ir/types",
        "@absl//absl/container:flat_hash_map",
        "@absl//absl/strings",
        "@absl//absl/strings:str_format",
    ],
)

cc_library(
    name = "access_path",
    hdrs = [
        "access_path.h",
        "access_path_root.h",
        "access_path_selectors.h",
        "access_path_selectors_set.h",
        "field_selector.h",
        "selector.h",
    ],
    deps = [
        "//src/common/logging",
        "@absl//absl/container:flat_hash_map",
        "@absl//absl/container:flat_hash_set",
        "@absl//absl/hash",
        "@absl//absl/strings",
        "@absl//absl/types:variant",
    ],
)

cc_test(
    name = "access_path_selectors_test",
    srcs = ["access_path_selectors_test.cc"],
    deps = [
        ":access_path",
        "//src/common/testing:gtest",
        "@absl//absl/hash:hash_testing",
        "@absl//absl/status:statusor",
        "@absl//absl/strings",
    ],
)

cc_test(
    name = "access_path_selectors_set_test",
    srcs = ["access_path_selectors_set_test.cc"],
    deps = [
        ":access_path",
        "//src/common/testing:gtest",
        "@absl//absl/container:btree",
        "@absl//absl/container:flat_hash_set",
        "@absl//absl/strings",
    ],
)

cc_test(
    name = "field_selector_test",
    srcs = ["field_selector_test.cc"],
    deps = [
        ":access_path",
        "//src/common/testing:gtest",
        "@absl//absl/hash:hash_testing",
    ],
)

cc_test(
    name = "selector_test",
    srcs = ["selector_test.cc"],
    deps = [
        ":access_path",
        "//src/common/testing:gtest",
        "@absl//absl/hash:hash_testing",
    ],
)

cc_test(
    name = "access_path_test",
    srcs = ["access_path_test.cc"],
    deps = [
        ":access_path",
        "//src/common/testing:gtest",
        "@absl//absl/hash:hash_testing",
    ],
)

cc_test(
    name = "edge_test",
    srcs = ["edge_test.cc"],
    deps = [
        ":access_path",
        ":ir",
        "//src/common/testing:gtest",
    ],
)

cc_test(
    name = "system_spec_test",
    srcs = ["system_spec_test.cc"],
    deps = [
        ":ir",
        "//src/common/logging",
        "//src/common/testing:gtest",
    ],
)

cc_test(
    name = "tag_claim_test",
    srcs = ["tag_claim_test.cc"],
    deps = [
        ":access_path",
        ":ir",
        "//src/common/testing:gtest",
        "//src/ir/proto:tag_claim",
        "@absl//absl/strings:str_format",
    ],
)

cc_test(
    name = "tag_check_test",
    srcs = ["tag_check_test.cc"],
    deps = [
        ":access_path",
        ":ir",
        "//src/common/testing:gtest",
        "//src/ir/proto:predicate",
        "//src/ir/proto:tag_check",
        "@absl//absl/strings",
        "@absl//absl/strings:str_format",
    ],
)

cc_test(
    name = "access_path_root_test",
    srcs = ["access_path_root_test.cc"],
    deps = [
        ":access_path",
        "//src/common/testing:gtest",
        "@absl//absl/hash:hash_testing",
    ],
)

cc_test(
    name = "derives_from_claim_test",
    srcs = ["derives_from_claim_test.cc"],
    deps = [
        ":ir",
        "//src/common/testing:gtest",
        "//src/ir/proto:access_path",
        "//src/ir/proto:derives_from_claim",
        "@absl//absl/strings",
        "@absl//absl/strings:str_format",
    ],
)

cc_library(
    name = "predicate_textproto_to_rule_body_testdata",
    testonly = True,
    srcs = ["predicate_textproto_to_rule_body_testdata.cc"],
    hdrs = ["predicate_textproto_to_rule_body_testdata.h"],
    deps = [
        "//src/test_utils/dl_string_extractor:datalog_string",
        "@absl//absl/strings",
    ],
)

cc_test(
    name = "predicate_test",
    srcs = ["predicate_test.cc"],
    deps = [
        ":ir",
        ":predicate_textproto_to_rule_body_testdata",
        "//src/common/testing:gtest",
        "//src/ir/proto:predicate",
        "//third_party/arcs/proto:manifest_cc_proto",
        "@absl//absl/strings",
    ],
)

cc_test(
    name = "handle_connection_spec_test",
    srcs = ["handle_connection_spec_test.cc"],
    deps = [
        ":ir",
        "//src/common/testing:gtest",
        "//src/ir/proto:handle_connection_spec",
        "//src/ir/types",
        "//third_party/arcs/proto:manifest_cc_proto",
    ],
)

cc_test(
    name = "particle_spec_test",
    srcs = ["particle_spec_test.cc"],
    deps = [
        ":ir",
        "//src/common/logging",
        "//src/common/testing:gtest",
        "//src/ir/proto:particle_spec",
        "//src/ir/types",
    ],
)

extracted_datalog_string_test(
    name = "predicate_extraction_test",
    dl_string_lib = ":predicate_textproto_to_rule_body_testdata",
)
