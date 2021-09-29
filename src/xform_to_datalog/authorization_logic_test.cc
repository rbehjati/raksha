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
//-----------------------------------------------------------------------------
#include "src/xform_to_datalog/authorization_logic.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <vector>

#include "src/common/testing/gtest.h"

namespace fs = std::filesystem;

namespace raksha::xform_to_datalog {

class AuthorizationLogicTest : public ::testing::Test {
public:
  static fs::path GetTestDataDir() {
    const char* test_srcdir_env = std::getenv("TEST_SRCDIR");
    const char* test_workspace_env = std::getenv("TEST_WORKSPACE");
    EXPECT_NE(test_srcdir_env,  nullptr);
    EXPECT_NE(test_workspace_env, nullptr);
    return fs::path(test_srcdir_env) / fs::path(test_workspace_env) /
      "src" / "xform_to_datalog" / "testdata";
  }

  static std::vector<std::string> ReadFileLines(const fs::path& file) {
    // Probably not quite efficient, but should serve the purpose for tests.
    std::ifstream file_stream(file);
    EXPECT_TRUE(file_stream) << "Unable to open file " << file;

    std::vector<std::string> result;
    for (std::string line; std::getline(file_stream, line);) {
      result.push_back(line);
    }    
    return result;
  }
};

TEST_F(AuthorizationLogicTest, InvokesRustToolAndGeneratesOutput) {
  const fs::path& test_data_dir = GetTestDataDir();
  fs::path output_dir = fs::temp_directory_path();
  int res = generate_datalog_facts_from_authorization_logic(
    "simple_auth_logic", test_data_dir.c_str(), output_dir.c_str());

  ASSERT_EQ(res, 0) << "Invoking authorization logic compiler failed.";

  std::vector<std::string> actual_datalog =
    ReadFileLines(output_dir / "simple_auth_logic.dl");
  std::vector<std::string> expected_datalog =
    ReadFileLines(test_data_dir / "simple_auth_logic.dl");

  // Need to compare individual lines as the output order is non-deterministic.
  ASSERT_THAT(actual_datalog,
	      testing::UnorderedElementsAreArray(expected_datalog));
}

TEST_F(AuthorizationLogicTest, ErrorsInRustToolReturnsNonZeroValue) {
  // Force the tool to return error by specifying non-existent files.
  int res = generate_datalog_facts_from_authorization_logic(
    "simple_auth_logic", "blah", "blah");
  ASSERT_EQ(res, 1);
}
  
}  // namespace raksha::xform_to_datalog