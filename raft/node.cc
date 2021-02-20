#include "node.h"

#include "utility/atomic.h"
#include "utility/log.h"
#include "utility/thread.h"

namespace raft {


Node::Node(const Peer& peer, FSM* fsm, const Options& options) : peer_(peer), is_running_(false),
    is_stopping_(false), role_(ROLE_FOLLOWER), state_(STATE_NORMAL), fsm_(fsm) {
    storage_.reset(GenStorage(options.type_, options.raft_log_dir_));
    consensus_.reset(new Consensus(options.peers_));
}

Status Node::Start(const Options& options) {
    if (options.from_checkpoint_) {
        // TODO(caoge)
        LOG(ERROR) << "Not support!";
        return NotSupport();
    }
    if (!is_running_.ComapreAndExchange(false, true)) {
        LOG(ERROR) << "Had Running..";
        return HadRunning();
    }
    ticker_ = Thread([this]{tick();});
    advancer_ = Thread([this]{advance();});
    LOG(INFO) << "raft node:" ToString() << " start success.";
}

void Node::Stop() {
    is_stopping.CompareAndExchange(false, true);
}

void Node::Propose(std::string* data) {
    auto entry = new Entry();
    entry.type_ = EntryType_Commit;
    entry.data = data;
    scop_lock_.lock();
    entrys_.push(entry);
}

void Node::advance() {
    while (true) {
        if (is_stopping_) {
            LOG(INFO) << "advance exit normal. for is_stopping is true.";
            return;
        }
        std::deque<Entry*> entrys;
        {
            scop_lock_.lock();
            swap(entrys, entrys_);
        }
        if (entrys.empty()) {
            cv_.Wait();
        }
        for (auto& entry : entrys) {
            switch (entry.type_) {
                case EntryType_Commit:
                    consensus->Commit(entry);
                    if (commit_ack_num_ >= quorm()) {
                        commit_ack_num_ = 0;
                        apply();
                        ++apply_index_;
                    }
                    break;
                case EntryType_CommitResp:
                    if (entry->index_ == commit_index_) {
                        ++commit_ack_num_;
                    }
                    break;
                case EntryType_Election:
                    handleElection();
                    break;
                case Entry_Leader:
                    toFollower();
                    break;
                case Entry_Snapshot:
                    sendSnapshot(entry);
                    break;
                default:
                    LOG(ERROR) << "invalid entry. type:" << entry->type_;
                    break;
            }
        }
        recycle(entrys);
    }
}

void Node::Step(Entry* entry) {
    scop_lock_.lock();
    entrys_.push(entry);
}

void Node::Checkpoint() {

}

void Node::tick() {
    while (true) {
        if (is_stopping_) {
            break;
        }
        uint64_t sleep_time = 0UL;
        switch (role_) {
            case ROLE_LEADER:
                heartbeat();
                break;
            case ROLE_CANDIDATE:
                if (!checkHeartbeat()) {
                    toCandidate();
                    continue;
                }
                break;
            case ROLE_LEANER:
                // TODO(caoge)
                break;
            default:
                LOG(FATAL) << "unkonw role:" << role_;
                return;
        }
        ThisThread::SleepTimeInUs(sleep_time);
    }
}

void Node::heartbeat() {

}

bool Node::checkHeartbeat() {

}

void Node::toCandidate() {

}

void Node::toFollower() {

}

uint8_t Node::quorom() {

}

void Node::handleElection() {

}

void Node::sendSnapshot() {
    // TODO(caoge)
}

void Node::apply() {

}

}  // end of namespace raft
