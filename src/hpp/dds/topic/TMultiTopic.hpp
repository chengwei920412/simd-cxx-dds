#ifndef OMG_DDS_T_TOPIC_MULTI_TOPIC_HPP_
#define OMG_DDS_T_TOPIC_MULTI_TOPIC_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Inc.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
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
 */

#include <vector>

#include <dds/core/detail/conformance.hpp>
#include <dds/core/types.hpp>
#include <dds/topic/TopicDescription.hpp>
#include <dds/core/Query.hpp>

namespace dds { namespace topic {

#ifdef OMG_DDS_MULTI_TOPIC_SUPPORT

template <typename T, template <typename Q> class DELEGATE>
class MultiTopic : public TopicDescription <T, DELEGATE> {
public:
    OMG_DDS_REF_TYPE_T(MultiTopic, TopicDescription, T, DELEGATE)

public:
    MultiTopic(const dds::domain::DomainParticipant& dp,
    		   const std::string& name,
    		   const dds::core::Query& query)
    : dds::topic::TopicDescription<T, DELEGATE>(new DELEGATE<T>(dp, name, query)) { }

    virtual ~MultiTopic() { }

public:
	public:

	const dds::core::Query& query() {
		return this->delegate()->query();
	}

	void expression_parameters(const dds::core::StringSeq& params) {
		this->delegate()->parameters(params);
	}

};

#endif  // OMG_DDS_MULTI_TOPIC_SUPPORT

} }


#endif /* OMG_DDS_T_TOPIC_CONTENT_FILTERED_TOPIC_HPP_ */
