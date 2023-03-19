/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Don Smyth <don.smyth@gmail.com>
 *                         Leonid Stryzhevskyi <lganzzzo@gmail.com>
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

#ifndef oatpp_postgresql_mapping_Serializer_hpp
#define oatpp_postgresql_mapping_Serializer_hpp

#include "PgArray.hpp"
#include "oatpp/core/data/stream/BufferStream.hpp"
#include "oatpp/core/Types.hpp"

#include <libpq-fe.h>

#if defined(WIN32) || defined(_WIN32)
  #include <WinSock2.h>
#else
  #include <arpa/inet.h>
#endif

namespace oatpp { namespace postgresql { namespace mapping {

/**
 * Mapper of oatpp values to PostgreSQL values.
 */
class Serializer {
public:

  struct OutputData {
    Oid oid = InvalidOid;
    std::unique_ptr<char[]> dataBuffer;
    char* data = nullptr;
    int dataSize = -1;
    int dataFormat = 1;
  };

public:
  typedef void (*SerializerMethod)(const Serializer*, OutputData&, const oatpp::Void&);
  typedef Oid (*TypeOidMethod)(const Serializer*, const oatpp::Type*);
private:

  static void serNull(OutputData& outData);
  static void serInt2(OutputData& outData, v_int16 value);
  static void serInt4(OutputData& outData, v_int32 value);
  static void serInt8(OutputData& outData, v_int64 value);

private:

  void setSerializerMethods();
  void setTypeOidMethods();

private:
  std::vector<SerializerMethod> m_methods;
  std::vector<TypeOidMethod> m_typeOidMethods;
  std::vector<TypeOidMethod> m_arrayTypeOidMethods;
public:

  Serializer();

  void setSerializerMethod(const data::mapping::type::ClassId& classId, SerializerMethod method);
  void setTypeOidMethod(const data::mapping::type::ClassId& classId, TypeOidMethod method);
  void setArrayTypeOidMethod(const data::mapping::type::ClassId& classId, TypeOidMethod method);

  void serialize(OutputData& outData, const oatpp::Void& polymorph) const;

  Oid getTypeOid(const oatpp::Type* type) const;
  Oid getArrayTypeOid(const oatpp::Type* type) const;

private:

  static void serializeString(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);

  static void serializeInt8(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);
  static void serializeUInt8(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);

  static void serializeInt16(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);
  static void serializeUInt16(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);

  static void serializeInt32(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);
  static void serializeUInt32(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);

  static void serializeInt64(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);
  static void serializeUInt64(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);

  static void serializeFloat32(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);
  static void serializeFloat64(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);

  static void serializeBoolean(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);

  static void serializeEnum(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);

  static void serializeUuid(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);

  struct ArraySerializationMeta {

    const Serializer* _this;
    std::vector<v_int32> dimensions;

  };

  static const oatpp::Type* getArrayItemTypeAndDimensions(const oatpp::Void& polymorph, std::vector<v_int32>& dimensions);

  static void serializeSubArray(data::stream::ConsistentOutputStream* stream,
                                const oatpp::Void& polymorph,
                                ArraySerializationMeta& meta,
                                v_int32 dimension);

  static void serializeArray(const Serializer* _this, OutputData& outData, const oatpp::Void& polymorph);

private:

  template<Oid OID>
  static Oid getTypeOid(const Serializer* _this, const oatpp::Type* type) {
    (void) _this;
    (void) type;
    return OID;
  }

  static Oid getEnumTypeOid(const Serializer* _this, const oatpp::Type* type);

  static Oid getEnumArrayTypeOid(const Serializer* _this, const oatpp::Type* type);

  static Oid get1DCollectionOid(const Serializer* _this, const oatpp::Type* type);

};

}}}

#endif // oatpp_postgresql_mapping_Serializer_hpp
