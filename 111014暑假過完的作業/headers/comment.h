#pragma once

#include <string>

struct Comment {
    time_t id;
    time_t postId;
    time_t authorId;
    std::string content;
};
