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
    using entity_type = Entity;

    template<typename Base>
    struct type: Base {
        using value_type = void;

        [[nodiscard]] type_info component() const ENTT_NOEXCEPT {
            return entt::poly_call<0>(*this);
        }

        void remove(basic_registry<entity_type> &reg, const entity_type *first, const entity_type *last) {
            entt::poly_call<1>(*this, reg, first, last);
        }
    };

    template<typename Type>
    using vtable = value_list<
        entt::overload<type_info()>(&type_id<typename Type::value_type>),
        entt::overload<void(basic_registry<entity_type> &, const entity_type *, const entity_type *), Type>(&Type::remove)
    >;
};


template<typename Entity>
using poly_storage = entt::poly<Storage<Entity>>;


}


#endif
