#include <string>
#include <vector>
#ifndef NWKMAP_H_
#define NWKMAP_H_

enum class nwkmap_relation_t {
   PARENT,
   CHILD,
   SIBLING,
   PREV_CHILD,
   UNKNOWN,
};

enum class nwkmap_dev_type_t {
   COORDINATOR,
   ROUTER,
   END_DEVICE,
   UNKNOWN,
};

struct nwkmap_dev_t
{
  std::string dev_id;   /* Name to display */
  uint8_t lqi;          /* Link Quality Indication */
  uint16_t nwk_addr;    /* Network address */
  nwkmap_relation_t relationship;
  nwkmap_dev_type_t device_type;
};


class INwkMap {
   /**
    * @brief Provides a hint for the next device to be queried for network topology information.
    *
    * @param[out] out_start_idx A pointer to the starting index of the next device to be queried.
    *
    * @return A string containing the ID of the next device to be queried, or NULL if:
    *   - There is no information about the network yet, and any device can be queried first.
    *   - All devices have been queried, and the topology map is complete.
    *
    * @note The returned device ID should be used to establish the relationship between the
    * devices added to the map using `nwkmap_add`.
    */
   virtual std::string hint(uint32_t &out_start_idx) = 0;

   /**
    * @brief Adds information about network devices to the topology map.
    *
    * @param[in] dev_id    The ID of the device that provided information about the other devices.
    * @param[in] start_idx The starting index of the devices provided.
    * @param[in] total_cnt The total number of devices that could be provided by this dev_id.
    * @param[in] devices   An array of network devices to be added to the map.
    * @param[in] size      The size of the devices array.
    */
   virtual void add(const char *dev_id,
                    uint8_t start_idx, uint8_t total_cnt,
                    std::vector<nwkmap_dev_t> devices) = 0;

   /**
    * @brief Saves the network topology map in the DOT format to a file.
    * @param[in] out_filename The name of the file to save the DOT representation of the topology map to.
    */
   virtual void save_dot(const std::string &out_filename) = 0;
};

#endif /* NWKMAP_H_ */
