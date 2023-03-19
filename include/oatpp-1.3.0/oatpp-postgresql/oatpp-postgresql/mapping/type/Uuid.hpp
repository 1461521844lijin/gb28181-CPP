/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#ifndef oatpp_postgresql_mapping_type_Uuid_hpp
#define oatpp_postgresql_mapping_type_Uuid_hpp

#include "oatpp/core/Types.hpp"

namespace oatpp { namespace postgresql { namespace mapping { namespace type {

namespace __class {
  class Uuid;
}

class UuidObject {
public:
  /**
   * Size of UUID data in bytes.
   */
  static constexpr v_buff_size DATA_SIZE = 16;
private:
  v_char8 m_data[DATA_SIZE];
public:

  /**
   * Constructor.
   * @param data
   */
  UuidObject(v_char8 data[DATA_SIZE]);

  /**
   * Constructor.
   * @param text
   */
  UuidObject(const oatpp::String& text);

  /**
   * Get raw data of ObjectId.
   * @return
   */
  const p_char8 getData() const;

  /**
   * Get size of ObjectId data.
   * @return - &l:ObjectId::DATA_SIZE;.
   */
  v_buff_size getSize() const;

  /**
   * To hex string.
   * @return
   */
  oatpp::String toString() const;

  bool operator==(const UuidObject &other) const;
  bool operator!=(const UuidObject &other) const;

};

/**
 * UUID type to store UUID data.
 */
typedef oatpp::data::mapping::type::Primitive<UuidObject, __class::Uuid> Uuid;

namespace __class {

class Uuid {
public:

  class Inter : public oatpp::Type::Interpretation<type::Uuid, oatpp::String>  {
  public:

    oatpp::String interpret(const type::Uuid& value) const override {
      return value->toString();
    }

    type::Uuid reproduce(const oatpp::String& value) const override {
      return std::make_shared<UuidObject>(value);
    }

  };

private:
  static oatpp::Type* createType();
public:

  static const oatpp::ClassId CLASS_ID;
  static oatpp::Type* getType();

};

}

}}}}

#endif // oatpp_postgresql_mapping_type_Uuid_hpp
