#include "network_bypass.h"

using namespace nwbp;

network_bypass_error nwbp::Network_bypass::init(nal::Node* _head)
{	
	if (!_head) {
		return ERROR_HEAD_IS_EMPTY;
	}
	nodes.push_back(_head);
	return NO_ERROR;
}

const nal::Node* nwbp::Network_bypass::hint()
{
	return nodes[cur_iter];
}

void nwbp::Network_bypass::add(std::vector<nal::Link> _links)
{
	for (auto& it : _links) {
		auto iter_find = std::find_if(begin(nodes), end(nodes), [&it](nal::Node*& _node) {
			return _node->get_id() == it.get_node()->get_id();
			});
		if (iter_find == end(nodes)) {
			nodes.push_back(it.get_node());
		}
	}
}

bool nwbp::Network_bypass::next()
{
	++cur_iter;
	return cur_iter < nodes.size();
}
