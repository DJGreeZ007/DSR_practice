#ifndef NODE_AND_LINK_H
#define NODE_AND_LINK_H
#include <vector>
#include <string>

namespace nal {

    enum class Nwk_type {
        NWKMAP_DEV_COORDINATOR,
        NWKMAP_DEV_ROUTER,
        NWKMAP_DEV_END_DEVICE,
        NWKMAP_DEV_UNKNOWN
    };

    enum class Nwk_relation {
        NWKMAP_RELATION_PARENT,
        NWKMAP_RELATION_CHILD,
        NWKMAP_RELATION_SIBLING,
        NWKMAP_RELATION_PREV_CHILD,
        NWKMAP_RELATION_UNKNOWN
    };

    struct Link;

    struct Node {
        bool completed{ false };                                         /* Was the node completely full? */
        std::string id{};                                                /* Name to display */
        std::uint16_t addr{};                                            /* Network address */
        Nwk_type device_type{ Nwk_type::NWKMAP_DEV_UNKNOWN };
        std::string label{};
        std::vector<Link> links{};
        Node();
        Node(std::string _id, std::uint16_t _addr, Nwk_type _device_type, std::string _label);
        bool operator == (const std::string& id) const;
    };
    struct Link {
        Node* node{};
        std::uint8_t lqi{};                                              /* Link Quality Indication */
        Nwk_relation relation{ Nwk_relation::NWKMAP_RELATION_UNKNOWN };	 /* Type of relationship */
    };
}

#endif /* NODE_AND_LINK_H */
