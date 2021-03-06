
/**
 * TypeInfo
 * @version 1.0
 * @since 1.0
 * <p>
 * Created by Murphy at 2020/6/11 23:56
 **/

#pragma once

#include "Stitches.hpp"

NS_STITCHES_BEGIN
using TypeId = std::size_t;

template<typename T>
class TypeInfo {
public:
    TypeInfo() = delete;

    /**
     * Get the type ID of K which is a base of T.
     * @tparam K The type ID K.
     * @return The type ID.
     */
    template<typename K>
    static TypeId GetTypeId() noexcept {
        std::type_index typeIndex(typeid(K));
        if (auto it = typeMap.find(typeIndex); it != typeMap.end())
            return it->second;
        const auto id = NextTypeId();
        typeMap[typeIndex] = id;
        return id;
    }

private:
    /**
     * Get the next type ID for T
     * @return The next type ID for T.
     */
    static TypeId NextTypeId() noexcept {
        const auto id = nextTypeId;
        ++nextTypeId;
        return id;
    }

    // Next type ID for T.
    static TypeId nextTypeId;
    static std::unordered_map<std::type_index, TypeId> typeMap;
};

template<typename K>
TypeId TypeInfo<K>::nextTypeId = 0;

template<typename K>
std::unordered_map<std::type_index, TypeId> TypeInfo<K>::typeMap = {};
NS_STITCHES_END
