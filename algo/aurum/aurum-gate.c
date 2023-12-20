#include "aurum-gate.h"

static void aurum_hash(void *state, const void *input)
{
    unsigned int t_cost = 2;
    unsigned int m_cost = 8;

    uint32_t header[20];
    memcpy(header, input, 80);
    uint32_t nonce = (uint32_t)header[19];

    PHS(state, 32, input, 80, &nonce, 4, t_cost, m_cost);
}

int scanhash_aurum(struct work* work, uint32_t max_nonce,
                   uint64_t* hashes_done, struct thr_info* mythr)
{
    uint32_t _ALIGN(64) hash[8];
    uint32_t _ALIGN(64) endiandata[20];
    uint32_t* pdata = work->data;
    uint32_t* ptarget = work->target;
    const uint32_t Htarg = ptarget[7];
    const uint32_t first_nonce = pdata[19];
    uint32_t nonce = first_nonce;
    int thr_id = mythr->id;

    if (opt_benchmark)
        ptarget[7] = 0x0000ff;

    for (int i = 0; i < 19; i++) {
        be32enc(&endiandata[i], pdata[i]);
    }

    do {
        be32enc(&endiandata[19], nonce);
        aurum_hash(hash, endiandata);
        if (hash[7] <= Htarg) {
            if (valid_hash(hash, ptarget) && !opt_benchmark) {
                pdata[19] = nonce;
                submit_solution(work, hash, mythr);
            }
        }
        nonce++;
    } while (nonce < max_nonce && !work_restart[thr_id].restart);

    pdata[19] = nonce;
    *hashes_done = pdata[19] - first_nonce + 1;
    return 0;
}

bool register_aurum_algo(algo_gate_t* gate)
{
    gate->hash     = (void*)&aurum_hash;
    gate->scanhash = (void*)&scanhash_aurum;
    opt_target_factor = 4096.0;

    return true;
}
