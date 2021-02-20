#pragma once

#include <unordered_map>

namespace raft {

class Consensus {
public:
    explicit Consensus(const std::vector<Peer*> peers);

    ~Consensus() {
        for (auto& it : peers_) {
            delete it;
        }
    }

    void Commit();

    void Apply();

    void MakeCheckPoint();

    void DownloadCheckpoint();

private:
    uint64_t lasted_commit_index_;
    uint64_t lasted_apply_index_;
    std::vector<uint64_t> next_indexs_;
    std::vector<Peer*> peers_;
};

}  // end of namespace raft
