// this is for emacs file handling -*- mode: c++; indent-tabs-mode: nil -*-

// -- BEGIN LICENSE BLOCK ----------------------------------------------
// Copyright 2019 FZI Forschungszentrum Informatik
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// -- END LICENSE BLOCK ------------------------------------------------

//----------------------------------------------------------------------
/*!\file
 *
 * \author  Lea Steffen steffen@fzi.de
 * \date    2019-04-01
 *
 */
//----------------------------------------------------------------------

#ifndef UR_RTDE_DRIVER_DATA_PACKAGE_H_INCLUDED
#define UR_RTDE_DRIVER_DATA_PACKAGE_H_INCLUDED

#include <unordered_map>

#include "ur_rtde_driver/types.h"
#include "ur_rtde_driver/rtde/rtde_package.h"
#include <boost/variant.hpp>

namespace ur_driver
{
namespace rtde_interface
{
struct ParseVisitor : public boost::static_visitor<>
{
  template <typename T>
  void operator()(T& d, comm::BinParser& bp) const
  {
    bp.parse(d);
  }
};
struct StringVisitor : public boost::static_visitor<std::string>
{
  template <typename T>
  std::string operator()(T& d) const
  {
    std::stringstream ss;
    ss << d;
    return ss.str();
  }
};


class DataPackage : public RTDEPackage
{
public:
  using _rtde_type_variant = boost::variant<bool, uint8_t, uint32_t, uint64_t, int32_t, double, vector3d_t, vector6d_t,
                                            vector6int32_t, vector6uint32_t, std::string>;

  DataPackage() = delete;
  DataPackage(const std::vector<std::string>& recipe) : recipe_(recipe)
  {
  }
  virtual ~DataPackage() = default;

  virtual bool parseWith(comm::BinParser& bp);
  virtual std::string toString() const;

private:
  // Const would be better here
  static std::unordered_map<std::string, _rtde_type_variant> type_list_;
  std::unordered_map<std::string, _rtde_type_variant> data_;
  std::vector<std::string> recipe_;
};

}  // namespace rtde_interface
}  // namespace ur_driver

#endif  // ifndef UR_RTDE_DRIVER_DATA_PACKAGE_H_INCLUDED