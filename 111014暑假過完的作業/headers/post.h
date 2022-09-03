#pragma once

#include <time.h>

#include <string>
#include <unordered_map>
#include <vector>

#include "account.h"
#include "comment.h"

struct Post {
    time_t id;
    time_t authorId;
    std::string title;
    std::string content;
    std::vector<Comment> comments;
    std::vector<time_t> likes;
};

std::unordered_map<time_t, Post> posts = {};
// 其實用map也行啦，為了那個酷酷的O(1)

void addPost(Post post) {
    posts[post.id] = post;
}

void addComment(time_t postId, Comment comment) {
    posts[postId].comments.push_back(comment);
}

bool addLike(time_t postId, time_t userId) {
    std::vector<time_t> likes = posts[postId].likes;
    auto it = find(likes.begin(), likes.end(), userId);

    if (it == likes.end()) {
        posts[postId].likes.push_back(userId);
        return true;
    }

    return false;
}

std::vector<Post> getAllPosts() {
    std::vector<Post> allPost;
    allPost.reserve(posts.size());

    for (auto kv : posts) {
        allPost.push_back(kv.second);
    }

    return allPost;
}
