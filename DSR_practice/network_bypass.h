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
	class Network_bypass:public I  {
	public:
		network_bypass_error init(nal::Node* _head);

		/* Getters */
		const nal::Node* hint();

		void add(std::vector<nal::Link> _nodes);
		bool next();

		void print() {
			for (auto& it : nodes) {
				std::cout << it->get_id() << std::endl;
			}
		}

	private:
		size_t cur_iter{};
		std::vector<nal::Node*> nodes;
	};
}

#endif /* NETWORK_BYPASS_H */