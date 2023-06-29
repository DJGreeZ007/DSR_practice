#ifndef NETWORK_H
#define NETWORK_H

/* Libs */
#include "map_parser.h"

/* C++ libs */
#include <vector>

namespace nw {

	enum network_error {
		NO_ERRORS
	};

	class Network {
	public:
		/* Сreating a graph (network model) from the values returned by map_parser */
		network_error init(std::vector<mp::Node> _nodes, std::vector<mp::Link> _links);

	private:
		std::string label{};			/* Name ZC */
		nal::Node* head;				/* Pointer to the coordinator */
		std::vector <nal::Node*> nodes  /* All nodes of the network */
	};
}
#endif /* NETWORK_H */

