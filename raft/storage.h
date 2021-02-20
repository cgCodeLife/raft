/*
 * @Author: your name
 * @Date: 2021-02-17 09:30:54
 * @LastEditTime: 2021-02-17 09:45:41
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /distributed-storage/engineering-technology/lib/raft/raft/storage.h
 */
#pragma once

#include <string>

enum StoreType {
    STORE_TYPE_LOCAL = uint8_t(0),
    STORE_TYPE_NUM,
};
namespace raft {

class Storage {
};

Storage* GenStorage(const StorageType& type, const std::string& dir);

}  // end of namespace raft
