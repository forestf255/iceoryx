// Copyright (c) 2020 by Apex.AI Inc. All rights reserved.
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

#ifndef IOX_POSH_POPO_TRIGGER_INL
#define IOX_POSH_POPO_TRIGGER_INL

#include <type_traits>
namespace iox
{
namespace popo
{
template <typename T>
inline Trigger::Trigger(T* const origin,
                        ConditionVariableData* conditionVariableDataPtr,
                        const cxx::ConstMethodCallback<bool>& hasTriggeredCallback,
                        const cxx::MethodCallback<void, const Trigger&>& resetCallback,
                        const uint64_t triggerId,
                        const Callback<T> callback) noexcept
    : TriggerState(origin, triggerId, callback)
    , m_conditionVariableDataPtr(conditionVariableDataPtr)
    , m_hasTriggeredCallback(hasTriggeredCallback)
    , m_resetCallback(resetCallback)
    , m_uniqueId(uniqueIdCounter.fetch_add(1U))
{
}

template <typename T>
inline void Trigger::updateOrigin(T* const newOrigin) noexcept
{
    if (newOrigin != m_origin)
    {
        if (m_hasTriggeredCallback && m_hasTriggeredCallback.getClassPointer<T>() == m_origin)
        {
            m_hasTriggeredCallback.setClassPointer(newOrigin);
        }

        if (m_resetCallback && m_resetCallback.getClassPointer<T>() == m_origin)
        {
            m_resetCallback.setClassPointer(newOrigin);
        }

        m_origin = newOrigin;
    }
}


} // namespace popo
} // namespace iox

#endif
