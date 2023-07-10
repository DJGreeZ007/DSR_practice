#ifndef C_LIBRARY_H
#define C_LIBRARY_H

#ifdef __cplusplus
extern "C" {
#endif

	/* libs */
	#include "network_bypass.h"
	#include "c_interface_nw_map.h"

	static nwbp::Network_bypass net_by{};

	void nwkmap_init(nwkmap_ctx_t* ctx);

	char* nwkmap_hint(nwkmap_ctx_t* ctx, uint32_t* out_start_idx);

	void nwkmap_add(nwkmap_ctx_t* ctx, const char* dev_id,
		uint8_t start_idx, uint8_t total_cnt,
		nwkmap_dev_t* devices, uint8_t size);

	void nwkmap_save_dot(const char out_filename);

#ifdef __cplusplus
}
#endif

#endif /* C_LIBRARY_H */
