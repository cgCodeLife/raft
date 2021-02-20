#include "consensus.h"

#include <vector>

namespace raft {

Consensus::Consensus(const std::vector<Peer*> peers) {
    for (const auto& it : peers) {
        peers_.emplace_back(it);
    }
}

}  // end of namespace raft
