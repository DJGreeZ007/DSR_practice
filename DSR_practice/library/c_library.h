#ifndef C_LIBRARY_H
#define C_LIBRARY_H


/* libs */
#include "network_bypass.h"
#include "c_interface_nw_map.h"

/* c++ libs */
#include <vector>
#include <algorithm>	/* std::find */
#include <mutex>

/* The second element is the ID of the initial node (storing the C-string) */
static std::vector<std::pair<nwbp::Network_bypass *, std::string>> net_bypasses{};
static std::mutex mutex;                /* Thread-safe access to map */
static const char* mistake = "";        /* nwkmap_hint returns this string in case of an error */

void nwkmap_init(unsigned int& context_id);

const char* nwkmap_hint(const unsigned int& context_id, uint32_t& out_start_idx);

void nwkmap_add(const unsigned int& context_id, const char* dev_id,
    uint8_t start_idx, uint8_t total_cnt,
    c_nwkmap_dev_t* devices, uint8_t size);
    

void nwkmap_save_dot(const unsigned int& context_id, const char out_filename);

void nwkmap_exit(const unsigned int& context_id);

#endif /* C_LIBRARY_H */
