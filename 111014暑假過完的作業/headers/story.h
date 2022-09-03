#pragma once

#include <time.h>

#include <string>
#include <unordered_map>
#include <vector>

#include "account.h"
#include "comment.h"

struct Story {
    time_t id;
    time_t authorId;
    time_t expireTime;
    std::string title;
    std::string content;
    std::vector<Comment> comments;
    std::vector<time_t> likes;
};

std::unordered_map<time_t, Story> stories = {};

void addStory(Story story) {
    stories[story.id] = story;
}

void addComment(time_t storyId, Comment comment) {
    stories[storyId].comments.push_back(comment);
}

bool addLike(time_t storyId, time_t userId) {
    std::vector<time_t> likes = stories[storyId].likes;
    auto it = find(likes.begin(), likes.end(), userId);

    if (it == likes.end()) {
        stories[storyId].likes.push_back(userId);
        return true;
    }

    return false;
}

bool isExpired(const Story& story) {
    if (time(NULL) > story.expireTime) {
        return true;
    }

    return false;
}

void removeExpiredStories() {
    for (auto kv : stories) {
        if (isExpired(kv.second)) {
            stories.erase(kv.first);
        }
    }
}

std::vector<Story> getAllStories() {
    std::vector<Story> allStory;
    allStory.reserve(stories.size());

    for (auto kv : stories) {
        allStory.push_back(kv.second);
    }

    return allStory;
}

// 雖然實作了現實動態
// 但我實在懶得把它做成UI
// 還有lv7感覺好麻煩
// 摯友啥的，我根本沒朋友 qwq
