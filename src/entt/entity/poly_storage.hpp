#ifndef ENTT_ENTITY_POLY_STORAGE_HPP
#define ENTT_ENTITY_POLY_STORAGE_HPP


#include "../core/type_info.hpp"
#include "../core/utility.hpp"
#include "../poly/poly.hpp"
#include "fwd.hpp"


namespace entt {


/**
 * @brief Basic storage concept.
 * @tparam Entity A valid entity type.
 */
template<typename Entity, typename = void>
struct Storage {
    /*! @brief Underlying entity identifier. */
    using entity_type = Entity;

    /**
     * @brief Concept declaration.
     * @tparam Base Injected class.
     */
    template<typename Base>
    struct type: Base {
        /*! @brief Type of the objects associated with the entities. */
        using value_type = void;

        /**
         * @brief Returns the type info for the underlying value type.
         * @return The type info for the underlying value type.
         */
        [[nodiscard]] type_info info() const ENTT_NOEXCEPT {
            return entt::poly_call<0>(*this);
        }

        /**
         * @brief Removes entities from a storage.
         * @param owner The registry that issued the request.
         * @param first An iterator to the first element of the range of
         * entities.
         * @param last An iterator past the last element of the range of
         * entities.
         */
        void remove(basic_registry<entity_type> &owner, const entity_type *first, const entity_type *last) {
            entt::poly_call<1>(*this, owner, first, last);
        }
    };

    /**
     * @brief Concept definition.
     * @tparam Type Type for which to generate a virtual table.
     */
    template<typename Type>
    using vtable = value_list<
        &type_id<typename Type::value_type>,
        entt::overload<void(basic_registry<entity_type> &, const entity_type *, const entity_type *), Type>(&Type::remove)
    >;
};


/**
 * @brief Alias template to facilitate the definition of a poly storage.
 * @tparam Entity A valid entity type.
 */
template<typename Entity>
using poly_storage = entt::poly<Storage<Entity>>;


}


#endif
