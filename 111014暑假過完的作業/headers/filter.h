#pragma once

#include <vector>
#include <algorithm>

#include "post.h"
#include "user.h"

using namespace std;

#define FILTER_USER 0x001
#define FILTER_OTHER 0x002

bool isUser(Post post) {
    return (post.authorId == currentUser->id);
}

bool isNotUser(Post post) {
    return (post.authorId != currentUser->id);
}

void toggleMask(int& mask, int flag) {
    if ((mask & flag) != 0) {
        mask &= ~flag;
    } else {
        mask |= flag;
    }
    // bitwise is sick
}

void filterPosts(vector<Post>& posts, int mask) {
    if ((mask & FILTER_USER) != 0) {
        auto it = remove_if(posts.begin(), posts.end(), isUser);
        posts.erase(it, posts.end());
    }

    if ((mask & FILTER_OTHER) != 0) {
        auto it = remove_if(posts.begin(), posts.end(), isNotUser);
        posts.erase(it, posts.end());
    }
}
