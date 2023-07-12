#ifndef C_LIBRARY_H
#define C_LIBRARY_H


/* libs */
#include "network_bypass.h"
#include "c_interface_nw_map.h"

/* c++ libs */
#include <vector>
#include <algorithm>	/* std::find */
#include <mutex>

static std::vector<nwbp::Network_bypass *> net_bypasses{};
static std::mutex mutex;        /* Thread-safe access to map */

void nwkmap_init(unsigned int& context_id);

char* nwkmap_hint(const unsigned int& context_id, uint32_t& out_start_idx);

void nwkmap_add(const unsigned int& context_id, const char* dev_id,
    uint8_t start_idx, uint8_t total_cnt,
    c_nwkmap_dev_t* devices, uint8_t size);
    

void nwkmap_save_dot(const unsigned int& context_id, const char out_filename);

#endif /* C_LIBRARY_H */
