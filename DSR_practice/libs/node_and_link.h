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
        /* Getters */
        bool get_completed_node() const;
        bool get_label_is_installed() const;
        std::string get_id() const;
        std::string get_label() const;
        std::vector<Link> get_links() const;

        /* Setters */
        void set_node(const std::string& _id, const std::uint16_t& _addr, const Nwk_type& _device_type);
        void set_label(const std::string& _label);
        bool add_links(const Link& _link);                               /* False - if such an element already exists */

        Node();
        Node(const std::string& _id);
        Node(const std::string& _id, const std::uint16_t& _addr, const Nwk_type& _device_type);
        ~Node();
        bool operator == (const std::string& _id) const;

    private:
        bool completed_node{ false };                                    /* Was the node completely full? */
        bool label_is_installed{ false };                                /* The label is installed */
        std::string id{};                                                /* Name to display */
        std::uint16_t addr{};                                            /* Network address */
        Nwk_type device_type{ Nwk_type::NWKMAP_DEV_UNKNOWN };
        std::string label{};                                             /* Only for the coordinator */
        std::vector<Link> links{};                                       /* Devices connected to the node */
    };


    class Link {
    public:
        /* Getters */
        std::string get_id() const;

        Link(Node* _node, const std::uint8_t _lqi, const Nwk_relation& _relation);
        ~Link();
        bool operator == (const Link& _link);
    private:
        Node* node{};                                                    /* Link to the node */
        std::uint8_t lqi{};                                              /* Link Quality Indication */
        Nwk_relation relation{ Nwk_relation::NWKMAP_RELATION_UNKNOWN };	 /* Type of relationship */
    };
}

#endif /* NODE_AND_LINK_H */
