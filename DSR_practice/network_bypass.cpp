#include "network_bypass.h"

using namespace nwbp;

std::string nwbp::Network_bypass::hint(uint32_t& out_start_idx)
{
	return std::string();
}

void nwbp::Network_bypass::add(const char* dev_id, uint8_t start_idx, uint8_t total_cnt, std::vector<nwkmap_dev_t> devices)
{
}

void nwbp::Network_bypass::save_dot(const std::string& out_filename)
{
}
