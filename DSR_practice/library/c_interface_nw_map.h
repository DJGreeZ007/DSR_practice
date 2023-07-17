#ifndef C_NWKMAP_H_
#define C_NWKMAP_H_

#include <cstdint>

typedef enum {
   NWKMAP_RELATION_PARENT,
   NWKMAP_RELATION_CHILD,
   NWKMAP_RELATION_SIBLING,
   NWKMAP_RELATION_PREV_CHILD,
   NWKMAP_RELATION_UNKNOWN,
} c_nwkmap_relation_t;

typedef enum {
   NWKMAP_DEV_COORDINATOR,
   NWKMAP_DEV_ROUTER,
   NWKMAP_DEV_END_DEVICE,
   NWKMAP_DEV_UNKNOWN,
} nwkmap_type_t;

typedef struct
{
  const char* dev_id;   /* Name to display */
  uint8_t lqi;          /* Link Quality Indication */
  uint16_t nwk_addr;    /* Network address */
  c_nwkmap_relation_t relationship;
  nwkmap_type_t device_type;
} c_nwkmap_dev_t;


/**
 * @brief Initializes the network topology map context.
 * @param[in,out] context_id Id per context.
 */
void nwkmap_init(unsigned int& context_id);

/**
 * @brief Provides a hint for the next device to be queried for network topology information.
 *
 * @param      ctx           The context of the network topology map.
 * @param[out] out_start_idx A pointer to the starting index of the next device to be queried.
 *
 * @return A string containing the ID of the next device to be queried, or NULL if:
 *   - There is no information about the network yet, and any device can be queried first.
 *   - All devices have been queried, and the topology map is complete.
 *
 * @note The returned device ID should be used to establish the relationship between the
 * devices added to the map using `nwkmap_add`.
 */
const char *nwkmap_hint(const unsigned int& context_id, uint32_t &out_start_idx);

/**
 * @brief Adds information about network devices to the topology map.
 *
 * @param     ctx       The context of the network topology map.
 * @param[in] dev_id    The ID of the device that provided information about the other devices.
 * @param[in] start_idx The starting index of the devices provided.
 * @param[in] total_cnt The total number of devices that could be provided by this dev_id.
 * @param[in] devices   An array of network devices to be added to the map.
 * @param[in] size      The size of the devices array.
 */
void nwkmap_add(const unsigned int& context_id, const char *dev_id,
                uint8_t start_idx, uint8_t total_cnt,
                c_nwkmap_dev_t *devices, uint8_t size);


void nwkmap_exit(const unsigned int& context_id);


/**
 * @brief Saves the network topology map in the DOT format to a file.
 * @param[in] out_filename The name of the file to save the DOT representation of the topology map to.
 */

void nwkmap_save_dot(const unsigned int& context_id, const char out_filename);

#endif /* C_NWKMAP_H_ */
