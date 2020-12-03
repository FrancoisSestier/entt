#ifndef ENTT_ENTITY_POLY_STORAGE_HPP
#define ENTT_ENTITY_POLY_STORAGE_HPP


#include <cstddef>
#include "../core/type_info.hpp"
#include "../core/utility.hpp"
#include "../poly/poly.hpp"
#include "fwd.hpp"
#include "storage.hpp"


namespace entt {


template<typename Entity>
struct Storage {
    template<typename Base>
    struct type: Base {
        using size_type = std::size_t;
        using entity_type = Entity;
        using value_type = void;
    
        [[nodiscard]] type_info component() const ENTT_NOEXCEPT {
    	    return entt::poly_call<0>(*this);
        }

        [[nodiscard]] size_type size() const ENTT_NOEXCEPT {
            return entt::poly_call<1>(*this);
        }

        [[nodiscard]] const entity_type * data() const ENTT_NOEXCEPT {
            return entt::poly_call<2>(*this);
        }

        [[nodiscard]] const void * raw() const ENTT_NOEXCEPT {
            return entt::poly_call<3>(*this);
        }
    
        [[nodiscard]] bool contains(const entity_type entt) const {
            return entt::poly_call<4>(*this, entt);
        }

        void clear() {
            entt::poly_call<5>(*this);
        }

        void remove(basic_registry<Entity> &, Entity) {}
    };
};


template<typename Entity, typename Type>
inline constexpr const auto poly_impl<Storage<Entity>, Type> =
    entt::value_list<
        entt::overload<type_info()>(&type_id<typename Type::value_type>),
        &Type::size,
        &Type::data,
        entt::overload<const typename Type::value_type *() const>(&Type::raw),
        &Type::contains,
        &Type::clear,
        entt::overload<void(basic_registry<Entity> &, Entity), Type>(&Type::remove)
    >{};


template<typename Entity>
using poly_storage = entt::poly<Storage<Entity>>;


}


#endif
