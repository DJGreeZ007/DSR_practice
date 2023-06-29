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

    class Link;

    class Node {
    public:
        static const size_t number_of_devices_to_return = 2;

        /* Getters */
        std::string get_id() const;
        std::uint16_t get_addr() const;
        Nwk_type get_type() const;
        const std::vector<Link>& get_links() const;

        void add_link(const Link& link);

        Node(const std::string& _id, const std::uint16_t& _addr, const Nwk_type& _device_type);

    private:
        std::string id{};                                                /* Name to display */
        std::uint16_t addr{};                                            /* Network address */
        Nwk_type device_type{ Nwk_type::NWKMAP_DEV_UNKNOWN };
        std::vector<Link> links{};                                       /* Devices connected to the node */
    };


    class Link {
    public:
        /* Getters */
        Node* const get_node() const;
        std::uint8_t get_lqi() const;
        Nwk_relation get_relation() const;

        Link(Node* _node, const std::uint8_t& _lqi, const Nwk_relation& _relation);
    private:
        Node* node{};                                                    /* Link to the node */
        std::uint8_t lqi{};                                              /* Link Quality Indication */
        Nwk_relation relation{ Nwk_relation::NWKMAP_RELATION_UNKNOWN };	 /* Type of relationship */
    };
}

#endif /* NODE_AND_LINK_H */
