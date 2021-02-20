#pragma ocne

#include <string>

namespace raft {

enum ERROR_CODE {
    ERROR_OK = 2000,
    ERROR_NOT_SUPPORT = 2001,
    ERROR_HAD_RUNNING = 2002,
};

class Status {
public:
    bool OK() {
        return code_ == ERROR_OK;
    }

    std::string ToString() {
        std::string ans = "";
        switch (code_) {
            case ERROR_OK:
                ans = "success";
                break;
            case ERROR_NOT_SUPPORT:
                ans = "not support";
                break;
            default:
                ans = "unknow error code";
                break;
        }
        return ans;
    }
public:
    ERROR_CODE code_;
};

static Status NotSupport() {

}

static Status HadRunning() {

}

struct Peer {
    std::string addr_;
    bool operator==(const Peer& r) {
        return addr_ == r.addr_;
    }

    std::string ToString() {
        return addr_;
    }
};

enum STATE {
    STATE_NORMAL = uint8_t(0),
    STATE_REPLICATING,
    STATE_SNAPSHOTING,
    STATE_PROBE,
    STATE_NUM,
};

enum Role {
    ROLE_LEADER = uint8_t(0),
    ROLE_FOLLOWER,
    ROLE_CANDIDATE,
    ROLE_LEANER,
    ROLE_NUM,
};

}  // end of namespace raft
