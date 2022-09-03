#pragma once

#include <string>
#include <unordered_map>

struct Account {
    time_t id;
    std::string name;
    std::string password;
};

std::unordered_map<time_t, Account> accounts = {};
std::vector<time_t> accountIds = {};

void addAccount(Account account) {
    accounts[account.id] = account;
    accountIds.push_back(account.id);
}

Account* getAccountByName(const std::string& name) {
    for (const auto& kv : accounts) {
        if (kv.second.name == name) {
            return &accounts[kv.first];
        }
    }

    return (Account*)NULL;
}

Account* getAccountById(const time_t& id) {
    if (!accounts.count(id)) return NULL;

    return &accounts[id];
}
