#ifndef ALGO_AURUM_AURUMGATE_H
#define ALGO_AURUM_AURUMGATE_H

#include "algo-gate-api.h"
#include "aurum.h"

#include <assert.h>
#include <stdint.h>

int scanhash_aurum(struct work* work, uint32_t max_nonce,
                   uint64_t* hashes_done, struct thr_info* mythr);
bool register_aurum_algo(algo_gate_t* gate);

#endif // ALGO_AURUM_AURUMGATE_H
