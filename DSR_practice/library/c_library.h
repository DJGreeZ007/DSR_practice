#ifndef C_LIBRARY_H
#define C_LIBRARY_H


/* libs */
#include "network_bypass.h"

/* Interface */
#include "c_interface_nw_map.h"

/* C++ libs */
#include <vector>
#include <algorithm>	/* std::find */
#include <mutex>


/* The second element is the ID of the initial node (storing the C-string) */
static std::vector<std::pair<std::unique_ptr<nwbp::Network_bypass>, std::string>> net_bypasses{};
/* Thread-safe access to vector */
static std::mutex mutex;
/* nwkmap_hint returns this string in case of an error */
static const char* mistake = "";

/**
 * @brief Function from the interface c_interface_nw_map.h.
 * Initializes the network topology map context.
 * @see nwkmap_init()
 * 
 * @param[out] context_id - Id per context.
*/
void nwkmap_init(unsigned int& context_id);

/**
 * @brief Function from the interface c_interface_nw_map.h.
 * Provides a hint for the next device to be queried for network topology information.
 * @see nwkmap_hint()
 * 
 * @param[in] context_id     - Id per context.
 * @param[out] out_start_idx - A pointer to the starting index of the next device to be queried.
 *
 * @return A string containing the ID of the next device to be queried, or NULL if:
 *   - There is no information about the network yet, and any device can be queried first.
 *   - All devices have been queried, and the topology map is complete.
 *
 * @note The returned device ID should be used to establish the relationship between the
 * devices added to the map using `nwkmap_add`.
 */
const char* nwkmap_hint(const unsigned int& context_id, uint32_t& out_start_idx);

/**
 * @brief Function from the interface c_interface_nw_map.h.
 * Adds information about network devices to the topology map.
 * @see nwkmap_add()
 *
 * @param[in] context_id - Id per context.
 * @param[in] dev_id     - The ID of the device that provided information about the other devices.
 * @param[in] start_idx  - The starting index of the devices provided.
 * @param[in] total_cnt  - The total number of devices that could be provided by this dev_id.
 * @param[in] devices    - An array of network devices to be added to the map.
 * @param[in] size       - The size of the devices array.
 */
void nwkmap_add(const unsigned int& context_id, const char* dev_id,
    uint8_t start_idx, uint8_t total_cnt,
    c_nwkmap_dev_t* devices, uint8_t size);
    
/**
 * @brief Function from the interface c_interface_nw_map.h.
 * Saves the network topology map in the DOT format to a file.
 * @see nwkmap_save_dot()
 * 
 * @param[in] context_id   - Id per context.
 * @param[in] out_filename - The name of the file to save the DOT representation of the topology map to.
 */
void nwkmap_save_dot(const unsigned int& context_id, const char out_filename);


/**
 * @brief Deleting the selected context
 *
 * @param[in] context_id - Id per context.
 */
void nwkmap_exit(const unsigned int& context_id);

#endif /* C_LIBRARY_H */
