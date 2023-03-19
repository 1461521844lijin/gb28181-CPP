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

#ifndef oatpp_postgresql_mapping_ResultMapper_hpp
#define oatpp_postgresql_mapping_ResultMapper_hpp

#include "Deserializer.hpp"
#include "oatpp/core/data/mapping/TypeResolver.hpp"
#include "oatpp/core/Types.hpp"
#include <libpq-fe.h>

namespace oatpp { namespace postgresql { namespace mapping {

/**
 * Mapper from PostgreSQL result to oatpp objects.
 */
class ResultMapper {
public:

  /**
   * Result data.
   */
  struct ResultData {

    /**
     * Constructor.
     * @param pDbResult
     * @param pTypeResolver
     */
    ResultData(PGresult* pDbResult, const std::shared_ptr<const data::mapping::TypeResolver>& pTypeResolver);

    /**
     * PGResult.
     */
    PGresult* dbResult;

    /**
     * &id:oatpp::data::mapping::TypeResolver;.
     */
    std::shared_ptr<const data::mapping::TypeResolver> typeResolver;

    /**
     * Column names.
     */
    std::vector<oatpp::String> colNames;

    /**
     * Column indices.
     */
    std::unordered_map<data::share::StringKeyLabel, v_int32> colIndices;

    /**
     * Column count.
     */
    v_int64 colCount;

    /**
     * Current row index.
     */
    v_int64 rowIndex;

    /**
     * Row count.
     */
    v_int64 rowCount;

  };

private:
  typedef oatpp::data::mapping::type::Type Type;
  typedef oatpp::Void (*ReadOneRowMethod)(ResultMapper*, ResultData*, const Type*, v_int64);
  typedef oatpp::Void (*ReadRowsMethod)(ResultMapper*, ResultData*, const Type*, v_int64);
private:

  static oatpp::Void readOneRowAsCollection(ResultMapper* _this, ResultData* dbData, const Type* type, v_int64 rowIndex);
  static oatpp::Void readOneRowAsMap(ResultMapper* _this, ResultData* dbData, const Type* type, v_int64 rowIndex);
  static oatpp::Void readOneRowAsObject(ResultMapper* _this, ResultData* dbData, const Type* type, v_int64 rowIndex);

  static oatpp::Void readRowsAsCollection(ResultMapper* _this, ResultData* dbData, const Type* type, v_int64 count);

private:
  Deserializer m_deserializer;
  std::vector<ReadOneRowMethod> m_readOneRowMethods;
  std::vector<ReadRowsMethod> m_readRowsMethods;
public:

  /**
   * Default constructor.
   */
  ResultMapper();

  /**
   * Set "read one row" method for class id.
   * @param classId
   * @param method
   */
  void setReadOneRowMethod(const data::mapping::type::ClassId& classId, ReadOneRowMethod method);

  /**
   * Set "read rows" method for class id.
   * @param classId
   * @param method
   */
  void setReadRowsMethod(const data::mapping::type::ClassId& classId, ReadRowsMethod method);

  /**
   * Read one row to oatpp object or collection. <br>
   * Allowed output type classes are:
   *
   * - &id:oatpp::Vector;
   * - &id:oatpp::List;
   * - &id:oatpp::UnorderedSet;
   * - &id:oatpp::Fields;
   * - &id:oatpp::UnorderedFields;
   * - &id:oatpp::Object;
   *
   * @param dbData
   * @param type
   * @return
   */
  oatpp::Void readOneRow(ResultData* dbData, const Type* type, v_int64 rowIndex);

  /**
   * Read `count` of rows to oatpp collection. <br>
   * Allowed collections to store rows are:
   *
   * - &id:oatpp::Vector;
   * - &id:oatpp::List;
   * - &id:oatpp::UnorderedSet;.
   *
   * @param dbData
   * @param type
   * @param count
   * @return
   */
  oatpp::Void readRows(ResultData* dbData, const Type* type, v_int64 count);

};

}}}

#endif //oatpp_postgresql_mapping_ResultMapper_hpp
