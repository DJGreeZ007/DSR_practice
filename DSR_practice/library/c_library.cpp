#include "c_library.h"

void nwkmap_init(unsigned int& context_id)
{
	/* Create net_bypass */
	nwbp::Network_bypass* net{new nwbp::Network_bypass{}};
	{
		std::lock_guard<std::mutex> g{mutex};
		auto iter = std::find(begin(net_bypasses), end(net_bypasses), nullptr);
		if (iter == end(net_bypasses)) {
			net_bypasses.push_back(net);
		}
		else {
			*iter = net;
		}
		context_id = std::distance(begin(net_bypasses), iter) - 1;

		//context_id = 0;
		//while (context_id < net_bypasses.size() && net_bypasses[context_id]) {
		//	++context_id;
		//}
		//if (context_id == net_bypasses.size()) {
		//	net_bypasses.push_back(net);
		//}
		//else {
		//	net_bypasses[context_id] = net;
		//}
	}
}

char* nwkmap_hint(const unsigned int& context_id, uint32_t& out_start_idx)
{
	std::lock_guard<std::mutex> g{mutex};
	if (context_id < net_bypasses.size() && net_bypasses[context_id]) {
		std::string id = net_bypasses[context_id]->hint(out_start_idx);
		if (!id.empty()) {
			
		}
	}
	return nullptr;
}
