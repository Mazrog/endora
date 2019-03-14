//
// Created by mazrog on 14/03/19.
//

#ifndef ENDORA_UNIFORM_BLOCK_HPP
#define ENDORA_UNIFORM_BLOCK_HPP

#include <array>
#include <type_traits>
#include <endora/utils.hpp>

#ifndef ENDORA_CUSTOM_TYPES
#include <glm/glm.hpp>

namespace {
    using vec2 = glm::vec2;
    using vec3 = glm::vec3;
    using mat4 = glm::mat4;
}

#endif // ENDORA_CUSTOM_TYPES

template < typename Enum >
constexpr auto enumvalue(Enum value) { return static_cast<std::underlying_type_t<Enum>>(value); }

template < typename ... Types >
struct types_wrapper {};

namespace impl {
    template < typename ... > struct packsize;

    template < template < class ... > typename C, typename ... Types >
    struct packsize<C<Types...>> { static constexpr size_t value = sizeof...(Types); };
}

template < typename T >
constexpr size_t packsizeV = impl::packsize<T>::value;

template < typename T >
constexpr size_t packsize() { return packsizeV<T>; }

template < typename T >
constexpr size_t padding = 0;

template <> constexpr size_t padding<float> = 4;
template <> constexpr size_t padding<glm::vec2> = 8;
template <> constexpr size_t padding<glm::vec3> = 16;
template <> constexpr size_t padding<glm::mat4> = 16;

using Pair = std::pair<size_t, size_t>;

template < size_t N >
using Infos = std::array<Pair, N>; // pair -> (data size, field offset)

template < typename T >
constexpr Pair get_type_data() {
    return Pair{sizeof(T), padding<T>};
}

template < typename ... > struct helper;
template < typename ... Types > struct helper<types_wrapper<Types...>> {
    static constexpr Pair value[sizeof...(Types)] { get_type_data<Types>() ... };
};

template < typename T >
struct UniformBlock {
    unsigned id;
    T block;

    UniformBlock() {
        glGenBuffers(1, &id); endora_error("gen unif buffer");
        glBindBuffer(GL_UNIFORM_BUFFER, id); endora_error("bind ubo");

        constexpr size_t pack_size = packsize<typename T::types>();

        size_t offset = 0;

        for (size_t i = 0; i < pack_size; ++i) {
            Pair const& type_info = helper<typename T::types>::value[i]; // first -> sizeof / second -> alignment
            const size_t ind = std::log2(type_info.second);

            if (block.size & (type_info.second - 1)) {
                offset = ((block.size >> ind) + 1) << ind;
                block.fields_info[i] = { type_info.first, offset };
                block.size = offset + type_info.first;
            } else {
                block.fields_info[i] = { type_info.first, block.size };
                block.size += type_info.first;
                offset = block.size;
            }
        }

        glBufferData(GL_UNIFORM_BUFFER, block.size, nullptr, GL_STATIC_DRAW); endora_error("buffer data");

        glBindBufferBase(GL_UNIFORM_BUFFER, 0, id);    endora_error("bind ubo binding point 0");
    }

    ~UniformBlock() {
        glDeleteBuffers(1, &id);
    }

    template < typename U >
    void set(typename T::fields field, U && value) {
        Pair & pair = block.fields_info[enumvalue(field)];
        glBindBuffer(GL_UNIFORM_BUFFER, id); endora_error("bind ubo");
        glBufferSubData(GL_UNIFORM_BUFFER, pair.second, pair.first, value);
    }
};

#define UnifBlock(block_name, type_block, ...) \
namespace ubo { \
struct block_name { \
    using types = type_block; \
    enum class fields { __VA_ARGS__, field_count }; \
    \
    std::array<std::pair<size_t, size_t>, enumvalue(fields::field_count)> fields_info; \
    size_t size = 0; \
}; \
}

#endif // ENDORA_UNIFORM_BLOCK_HPP
