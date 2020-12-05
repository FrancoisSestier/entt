#ifndef ENTT_ENTITY_POLY_STORAGE_HPP
#define ENTT_ENTITY_POLY_STORAGE_HPP


#include <cstddef>
#include "../core/type_info.hpp"
#include "../core/utility.hpp"
#include "../poly/poly.hpp"
#include "fwd.hpp"
#include "storage.hpp"


namespace entt {


template<typename Entity, typename = void>
struct Storage {
    template<typename Base>
    struct type: Base {
        using size_type = std::size_t;
        using entity_type = Entity;
        using value_type = void;

        [[nodiscard]] type_info component() const ENTT_NOEXCEPT {
    	    return entt::poly_call<0>(*this);
        }

        void remove(basic_registry<entity_type> &registry, const entity_type *first, const entity_type *last) {
            entt::poly_call<1>(*this, registry, first, last);
        }
    };
};


template<typename Entity, typename Type>
inline constexpr const auto poly_impl<Storage<Entity>, Type> =
    std::make_tuple(
        entt::overload<type_info()>(&type_id<typename Type::value_type>),
        entt::overload<void(basic_registry<Entity> &, const Entity *, const Entity *), Type>(&Type::remove)
    );


template<typename Entity>
using poly_storage = entt::poly<Storage<Entity>>;


}


#endif
