#ifndef NETWORK_BYPASS_H
#define NETWORK_BYPASS_H

/* Interface */
#include "interface_nw_map.h"

/* C++ libs */
#include <vector>
#include <limits> /* max() */
#include <map>

namespace nwbp { /* NetWorkByPass */
    /**
     * @brief A structure containing information about a node
    */
    struct Node {
        /* Name to display */
        std::string id{};
        /* Network address */
        std::uint16_t addr{};
        /* Device type from the nwkmap_dev_type_t enumeration @see inwmap::nwkmap_dev_type_t */
        inwmap::nwkmap_dev_type_t device_type{ inwmap::nwkmap_dev_type_t::UNKNOWN }; 

        /**
         * Constructor
         * 
         * @param[in] _id - Name to display. @see Node::id
         * @param[in] _addr - Network address. @see Node::addr
         * @param[in] _device_type - Device type from the nwkmap_dev_type_t enumeration. @see Node::device_type
        */
        Node(const std::string& _id, const std::uint16_t& _addr, const inwmap::nwkmap_dev_type_t& _device_type);
    };

    /**
     * @brief A structure containing information about a link.
    */
    struct Link {
        /* The address of the node from which the message is sent. */
        std::string from{};
        /* The address of the node to which the message is sent. */
        std::string to{};
        /* Communication quality indication. */
        std::uint8_t lqi{};
        /** 
         * The type of connection from the nwkmap_relation_t enumeration.
         * @see inwmap::nwkmap_relation_t 
        */
        inwmap::nwkmap_relation_t relation{ inwmap::nwkmap_relation_t::UNKNOWN };

        /**
         * @brief Overloaded equality operator.
         * 
         * Objects are equal if and only if the corresponding
         * to and from fields of two objects are equal. @see Link::from and @see Link::to
         * 
         * @param[in] _link - Reference to the object being compared. @see Link
        */
        bool operator== (const Link& _link);

        /**
         * @brief Constructor
         *
         * @param[in] _from - The address of the node from which the message is sent. @see Link::from
         * @param[in] _to - The address of the node to which the message is sent. @see Link::to
         * @param[in] _lqi - Communication quality indication. @see Link::lqi
         * @param[in] _relation - The type of connection from the nwkmap_relation_t enumeration. @see Link::relation
        */
        Link(const std::string& _from, const std::string& _to, const std::uint8_t& _lqi, const inwmap::nwkmap_relation_t& _relation);
    };
    /**
     * @brief A class that includes the interface interface_nw_map.h 
     * and can store information about nodes and connections after traversing the network. 
     * It also has the output of the network bypass result in a dot file.
    */
    class Network_bypass : public inwmap::INwkMap {
    public:
        /**
         * @brief Function from the interface interface_nw_map.h.
         * @see INwkMap::hint()
        */
        std::string hint(uint32_t& out_start_idx) override;

        /**
         * @brief Function from the interface interface_nw_map.h.
         * @see INwkMap::add()
        */
        void add(const char* dev_id,
            uint8_t start_idx, uint8_t total_cnt,
            std::vector<inwmap::nwkmap_dev_t> devices) override;

        /**
         * @brief Function from the interface interface_nw_map.h.
         * @see INwkMap::save_dot()
        */
        void save_dot(const std::string& out_filename) override;

        /* Default constructors */
        Network_bypass() = default;
        Network_bypass(const Network_bypass&) = default;
        Network_bypass(Network_bypass&&) = default;
        Network_bypass& operator= (const Network_bypass&) = default;
        Network_bypass& operator= (Network_bypass&&) = default;

    private:
        /* Iterator indicating the process of traversing the capital node */
        size_t iterator_per_neighbor_for_head{};
        /* The maximum value will go away after adding the last neighbor head */
        size_t idx_cur_node{std::numeric_limits<size_t>::max()};
        /* List of nodes passed */
        std::vector<Node> nodes{};
        /* List of links passed */
        std::vector<Link> links{};
        /* Storage next to the traversed node is the progress of traversing its neighbors */
        std::map<const std::string, size_t> iterators_per_neighbor{};
        /* Label for the main node */
        std::string label{};
    };
}

#endif /* NETWORK_BYPASS_H */