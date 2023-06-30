#ifndef NETWORK_BYPASS_H
#define NETWORK_BYPASS_H

/* Libs */
#include "interface_nw_map.h"

/* C++ libs */
#include <vector>
#include <fstream>
#include <iostream>


namespace nwbp {
	enum network_bypass_error {
		NO_ERROR
	};

	struct Node {
		std::string id{};                                               /* Name to display */
		std::uint16_t addr{};                                           /* Network address */
		nwkmap_dev_type_t device_type{ nwkmap_dev_type_t::UNKNOWN };
		Node(const std::string& _id, const std::uint16_t& _addr, const nwkmap_dev_type_t& _device_type);
	};

	struct Link {
		std::string from{};
		std::string to{};
		std::uint8_t lqi{};
		nwkmap_relation_t relation{ nwkmap_relation_t::UNKNOWN };
		Link(const std::string& _from, const std::string& _to, const std::uint8_t& _lqi, const nwkmap_relation_t& _relation);
	};

	class Network_bypass:public INwkMap {
	public:
		/* Interface */
		std::string hint(uint32_t& out_start_idx);

		void add(const char* dev_id,
			uint8_t start_idx, uint8_t total_cnt,
			std::vector<nwkmap_dev_t> devices);

		void save_dot(const std::string& out_filename);


		/* TMP */
		void print() {
			std::cout << "Nodes" << std::endl;
			for (auto it : nodes) {
				std::cout << "    # " << it.id << std::endl;
			}

			std::cout << std::endl << "Links" << std::endl;
			for (auto it : links) {
				std::cout << "    # " << it.from << " -> " << it.to <<  std::endl;
			}
		}
	private:
		std::string converting_data_to_dot (const Node& node);
		std::string converting_data_to_dot(const Link& link);
		std::uint32_t start_idx_cur_node{};
		std::string label{};
		int cur_iter{-1};
		std::vector<Node> nodes{};
		std::vector<Link> links{};
		std::string head_id{};
	};
}

#endif /* NETWORK_BYPASS_H */