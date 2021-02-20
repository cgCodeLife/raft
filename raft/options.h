/*
 * @Author: your name
 * @Date: 2021-02-17 09:30:54
 * @LastEditTime: 2021-02-17 09:45:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /distributed-storage/engineering-technology/lib/raft/raft/options.h
 */
#pragma once

#include <string>
#include <vector>

#include "common.h"

namespace raft {

struct Options {
    StoreType type_;
    std::string raft_log_dir_;
    std::vector<Peer*> peers_;
};

}  // end of namespace raft
