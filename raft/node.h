#pragma once

#include <deque>
#include <string>

#include "options.h"
#include "utility/atomic.h"
#include "utility/conditionvar.h"
#include "utility/thread.h"
#include "utility/scop_lock.h"

namespace raft {

class FSM {

};

class Node {
pulibc:
    explicit Node(const Peer& peer, FSM* fsm, const Options& options);

    ~Node() {
        ticker_.Stop();
        advancer_.Stop();
        ticker_.Join();
        advancer_.Join();
    }

    void Porpose();

    void Checkpoint();

    void Start();

    void Stop();

    std::string ToString() {
        return peer_.ToString();
    }

private:
    void advance();

    void tick();

    void heartbeat();

    bool checkHeartbeat();

    void toCandidate();

    void toFollower();

    uint8_t quorom();

    void handleElection();

    void sendSnapshot();

    void apply();

private:
    Peer peer_;
    Atomic<bool> is_running_;
    Atomic<bool> is_stopping_;
    Atomic<Role> role_;
    Atomic<STATE> state_;
    Atomic<uint64_t> commit_index_;
    Atomic<uint64_t> apply_index_;
    FSM* fsm_;
    std::unique_ptr<Storage> storage_;
    std::unique_ptr<Consensus> consensus_;
    Thread ticker_;
    Thread advancer_;
    std::deque<Entry*> entrys_;
    ScopLock scop_lock_;
    ConditionVar cv_;
};
}  // end of namespace raft
