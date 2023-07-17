#include "c_library.h"


/* Additional functions */

/*
* Converts a device object from a C interface to a C++ interface
*
* @param[in] _device The device object in C representation
* @return The device object in C++ representation
*/
inwmap::nwkmap_dev_t converting_C_device_to_c_plus_plus(const c_nwkmap_dev_t& _device);

/*
* Converts relationship from C interface to C++ interface
*
* @param[in] _relation The relationship object in C representation
* @return The relationship object in C++ representation
*/

inwmap::nwkmap_relation_t converting_C_relationship_to_c_plus_plus(const c_nwkmap_relation_t& _relation);
/*
* Converts device type from C interface to C++ interface
*
* @param[in] _type The device type object in C representation
* @return The device type object in C++ representation
*/
inwmap::nwkmap_dev_type_t converting_C_type_to_c_plus_plus(const nwkmap_type_t& _type);

/* C interface functions */

void nwkmap_init(unsigned int& context_id)
{
    /* Create net_bypass */
    nwbp::Network_bypass* net{new nwbp::Network_bypass{}};
    {
        std::lock_guard<std::mutex> g{mutex};
        auto iter = std::find_if(begin(net_bypasses), end(net_bypasses), 
            [](const std::pair<nwbp::Network_bypass*, std::string>& _obj) -> bool {
                return !_obj.first;
            });
        if (iter == end(net_bypasses)) {
            net_bypasses.push_back(std::make_pair(net, ""));
        }
        context_id = std::distance(begin(net_bypasses), iter) - 1;
    }
}

const char* nwkmap_hint(const unsigned int& context_id, uint32_t& out_start_idx)
{
    std::lock_guard<std::mutex> g{mutex};
    if (context_id < net_bypasses.size() && net_bypasses[context_id].first) {
        net_bypasses[context_id].second = net_bypasses[context_id].first->hint(out_start_idx);
        return net_bypasses[context_id].second.c_str();
    }
    return mistake;
}

void nwkmap_add(const unsigned int& context_id, const char* dev_id, uint8_t start_idx, uint8_t total_cnt, c_nwkmap_dev_t* devices, uint8_t size)
{
    std::lock_guard<std::mutex> g{mutex};
    if (context_id < net_bypasses.size() && net_bypasses[context_id].first) {
        /* Converting devices */
        std::vector<inwmap::nwkmap_dev_t> vect_devices{};
        for (size_t i = 0; i < size; ++i) {
            inwmap::nwkmap_dev_t device{std::move(converting_C_device_to_c_plus_plus(devices[i]))};
            vect_devices.push_back(std::move(device));
        }

        net_bypasses[context_id].first->add(dev_id, start_idx, total_cnt, vect_devices);
    }
}

void nwkmap_save_dot(const unsigned int& context_id, const char out_filename)
{
    std::lock_guard<std::mutex> g{mutex};
    if (context_id < net_bypasses.size() && net_bypasses[context_id].first) {
        std::string o_filename{out_filename};
        net_bypasses[context_id].first->save_dot(o_filename);
    }
}

void nwkmap_exit(const unsigned int& context_id)
{
    std::lock_guard<std::mutex> g{mutex};
    if (context_id < net_bypasses.size() && net_bypasses[context_id].first) {
        delete net_bypasses[context_id].first;
        net_bypasses[context_id].first = nullptr;
        net_bypasses[context_id].second.clear();
    }
}
inwmap::nwkmap_dev_t converting_C_device_to_c_plus_plus(const c_nwkmap_dev_t& _device) {
    std::string dev_id{_device.dev_id};
    uint8_t lqi{ _device.lqi };
    uint16_t nwk_addr{ _device.nwk_addr };
    inwmap::nwkmap_relation_t relationship{converting_C_relationship_to_c_plus_plus(_device.relationship)};
    inwmap::nwkmap_dev_type_t device_type{converting_C_type_to_c_plus_plus(_device.device_type)};

    inwmap::nwkmap_dev_t result{std::move(dev_id), lqi, nwk_addr, relationship, device_type};
    return result;
}

inwmap::nwkmap_relation_t converting_C_relationship_to_c_plus_plus(const c_nwkmap_relation_t& _relation) {
    inwmap::nwkmap_relation_t result{};
    switch (_relation) {
    case NWKMAP_RELATION_PARENT:
        result = inwmap::nwkmap_relation_t::PARENT;
        break;
    case NWKMAP_RELATION_CHILD:
        result = inwmap::nwkmap_relation_t::CHILD;
        break;
    case NWKMAP_RELATION_SIBLING:
        result = inwmap::nwkmap_relation_t::SIBLING;
        break;
    case NWKMAP_RELATION_PREV_CHILD:
        result = inwmap::nwkmap_relation_t::PREV_CHILD;
        break;
    case NWKMAP_RELATION_UNKNOWN:
        result = inwmap::nwkmap_relation_t::UNKNOWN;
    }
    return result;
}

inwmap::nwkmap_dev_type_t converting_C_type_to_c_plus_plus(const nwkmap_type_t& _type) {
    inwmap::nwkmap_dev_type_t result{};
    switch (_type) {
    case NWKMAP_DEV_COORDINATOR:
        result = inwmap::nwkmap_dev_type_t::COORDINATOR;
        break;
    case NWKMAP_DEV_ROUTER:
        result = inwmap::nwkmap_dev_type_t::ROUTER;
        break;
    case NWKMAP_DEV_END_DEVICE:
        result = inwmap::nwkmap_dev_type_t::END_DEVICE;
        break;
    case NWKMAP_DEV_UNKNOWN:
        result = inwmap::nwkmap_dev_type_t::UNKNOWN;
    }
    return result;
}