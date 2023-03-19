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

#ifndef oatpp_postgresql_mapping_PgArray_hpp
#define oatpp_postgresql_mapping_PgArray_hpp

#include "oatpp/core/data/stream/Stream.hpp"
#include "oatpp/core/Types.hpp"

#include <libpq-fe.h>

namespace oatpp { namespace postgresql { namespace mapping {

// after https://stackoverflow.com/questions/4016412/postgresqls-libpq-encoding-for-binary-transport-of-array-data
struct PgArrayHeader {

  v_int32 ndim = 0;   // Number of dimensions
  //v_int32 _ign;   // offset for data, removed by libpq
  Oid oid = InvalidOid;        // type of element in the array

  // Start of array (1st dimension)
  v_int32 size = 0;   // Number of elements
  // v_int32 index;  // Index of first element

};

template<typename T, int dim>
struct MultidimensionalArray {

  typedef oatpp::Vector<typename MultidimensionalArray<T, dim - 1>::type> type;

  static const oatpp::Type *getClassType() {
    return type::Class::getType();
  }

};

template<typename T>
struct MultidimensionalArray<T, 0> {
  typedef T type;
};

class ArrayUtils {
public:

  static void writeArrayHeader(data::stream::ConsistentOutputStream* stream,
                               Oid itemOid,
                               const std::vector<v_int32>& dimensions);

  static void readArrayHeader(data::stream::InputStream* stream,
                              PgArrayHeader& arrayHeader,
                              std::vector<v_int32>& dimensions);

};

}}}

#endif // oatpp_postgresql_mapping_PgArray_hpp
