#ifndef NETWORK_BYPASS_H
#define NETWORK_BYPASS_H

/* Libs */
#include "libs/node_and_link.h"
#include "interface_nw_map.h"

/* C++ libs */
#include <vector>
#include <iostream>

namespace nwbp {
	enum network_bypass_error {
		NO_ERROR,
		ERROR_HEAD_IS_EMPTY					/* Head is empty */
	};
	class Network_bypass:public INwkMap {
	public:
		/* Interface */
		std::string hint(uint32_t& out_start_idx);

		void add(const char* dev_id,
			uint8_t start_idx, uint8_t total_cnt,
			std::vector<nwkmap_dev_t> devices);

		void save_dot(const std::string& out_filename);
	private:
		size_t cur_iter{};
		std::vector<nal::Node*> nodes;
	};
}

#endif /* NETWORK_BYPASS_H */