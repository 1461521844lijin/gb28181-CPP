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

#ifndef oatpp_postgresql_ql_template_TemplateValueProvider_hpp
#define oatpp_postgresql_ql_template_TemplateValueProvider_hpp

#include "oatpp/orm/Executor.hpp"
#include "oatpp/core/data/stream/BufferStream.hpp"

namespace oatpp { namespace postgresql { namespace ql_template {

/**
 * &id:oatpp::data::share::StringTemplate::ValueProvider;
 */
class TemplateValueProvider : public data::share::StringTemplate::ValueProvider {
private:
  data::stream::BufferOutputStream m_buffStream;
public:
  oatpp::String getValue(const data::share::StringTemplate::Variable& variable, v_uint32 index) override;
};

}}}

#endif // oatpp_postgresql_ql_template_TemplateValueProvider_hpp
