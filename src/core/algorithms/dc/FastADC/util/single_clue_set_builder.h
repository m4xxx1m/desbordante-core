#pragma once

#include <stddef.h>
#include <vector>

#include "dc/FastADC/model/pli_shard.h"
#include "dc/FastADC/util/common_clue_set_builder.h"
#include "dc/FastADC/util/evidence_aux_structures_builder.h"

namespace algos::fastadc {

/**
 * Constructs a clue set for a single PLI shard.
 */
class SingleClueSetBuilder {
public:
    SingleClueSetBuilder(PliShard const& shard);
    SingleClueSetBuilder(SingleClueSetBuilder const& other) = delete;
    SingleClueSetBuilder& operator=(SingleClueSetBuilder const& other) = delete;
    SingleClueSetBuilder(SingleClueSetBuilder&& other) noexcept = default;
    SingleClueSetBuilder& operator=(SingleClueSetBuilder&& other) noexcept = delete;

    void BuildClueSet(PredicatePacks const& packs, std::vector<Clue>& clues, ClueSet& clue_set);

private:
    std::vector<Pli> const& plis_;
    size_t tid_beg_;
    size_t tid_range_;
    size_t evidence_count_;

    void SetSingleEQ(std::vector<Clue>& clues, Pli::Cluster const& cluster, Clue const& mask);
    void CorrectStrSingle(std::vector<Clue>& clues, Pli const& pli, Clue const& mask);
    void SetCrossEQ(std::vector<Clue>& clues, Pli::Cluster const& pivotCluster,
                    Pli::Cluster const& probeCluster, Clue const& mask);
    void CorrectStrCross(std::vector<Clue>& clues, Pli const& pivotPli, Pli const& probePli,
                         Clue const& mask);
    void SetGT(std::vector<Clue>& clues, Pli::Cluster const& pivotCluster, Pli const& probePli,
               size_t from, Clue const& mask);
    void CorrectNumSingle(std::vector<Clue>& clues, Pli const& pli, Clue const& eqMask,
                          Clue const& gtMask);
    void CorrectNumCross(std::vector<Clue>& clues, Pli const& pivotPli, Pli const& probePli,
                         Clue const& eqMask, Clue const& gtMask);
};

}  // namespace algos::fastadc
