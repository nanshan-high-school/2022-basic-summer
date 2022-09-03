#pragma once

#include <iostream>
#include <vector>

#include "ConsoleStyle.h"
#include "account.h"
#include "filter.h"
#include "post.h"
#include "user.h"
#include "console.h"

using namespace std;

void mainUI();

void signInUI();
void signOutUI();
void signUpUI();

void browsePostUI();
void addPostUI();
void setPostFilterUI();
void commentPostUI(Post&);

string stopWord(1, (char)4);
string input() {
    string result = "";
    while (true) {
        string line;
        cin >> line;

        if (line == stopWord) {
            break;
        } else {
            result += line + "\n";
        }
    }
    return result;
}

void mainUI() {
    int ch = 0;

    if (isSignedIn) {
        system("cls");

        cout << "1. 查看貼文\n"
             << "2. 新增貼文\n"
             << "3. 設定篩選\n"
             << "4. 登出\n";
        cout << "選擇: ";
        cin >> ch;

        if (ch == 1) browsePostUI();
        if (ch == 2) addPostUI();
        if (ch == 3) setPostFilterUI();
        if (ch == 4) signOutUI();
        return;
    }

    cout << "1. 登入\n"
         << "2. 註冊\n"
         << "3. 離開\n";
    cout << "選擇: ";
    cin >> ch;

    system("cls");

    if (ch == 1) signInUI();
    if (ch == 2) signUpUI();
    if (ch == 3) exit(0);
}

void signInUI() {
    system("cls");

    string name;
    cout << "名稱:";
    cin >> name;

    string password;
    hideInputEcho(true);
    cout << "密碼(隱藏):";
    cin >> password;
    hideInputEcho(false);
    cout << "\n"; // 不加的話排版會爛掉，我也不知道為啥

    Account* acc = getAccountByName(name);
    if (acc) {
        if (acc->password == password) {
            currentUser = acc;
            isSignedIn = true;
        } else {
            cout << "密碼錯誤，請重試\n";
        }
    } else {
        cout << "未找到對應的帳號，註冊後重試\n";
    }

    filterMask = 0;  // 我實在找不到其他地方可以放了
    // 放這裡真的好醜
}

void signUpUI() {
    system("cls");

    string name;
    cout << "名稱:";
    cin >> name;

    if (getAccountByName(name)) {
        cout << "帳號名稱已經有人用過了\n";
        return;
    }

    string password;
    hideInputEcho(true);
    cout << "密碼(隱藏):";
    cin >> password;
    hideInputEcho(false);
    cout << "\n"; // 不加的話排版會爛掉，我也不知道為啥

    time_t id = time(NULL);
    Account acc = {id, name, password};
    addAccount(acc);
    currentUser = &accounts[id];
}

void signOutUI() {
    currentUser = NULL;
    isSignedIn = false;
    system("cls");
}

void browsePostUI() {
    vector<Post> allPost = getAllPosts();
    filterPosts(allPost, filterMask);
    int postIndex = (int)allPost.size() - 1;

    while (true) {
        system("cls");

        if (allPost.size() == 0) {
            cout << "目前沒有貼文\n"
                 << "說點甚麼吧\n";
            break;
        }

        // post
        cout << BOLD << UNDERLINE
             << allPost[postIndex].title << "\n"
             << RESET_COLOR;
        cout << allPost[postIndex].content << "\n";

        // author
        cout << "by "
             << UNDERLINE
             << getAccountById(allPost[postIndex].authorId)->name
             << RESET_COLOR;
        cout << " at "
             << ctime(&allPost[postIndex].id)
             << "\n";

        // likes
        vector<time_t>& postLikes = allPost[postIndex].likes;
        cout << "喜歡(" << postLikes.size() << "): ";
        for (const auto& id : postLikes) {
            cout << UNDERLINE
                 << (getAccountById(id)->name)
                 << RESET_COLOR
                 << ", ";
            // 不是，聽我解釋，我只是懶得檢查最後一個，請不要打我
            // 還有這樣不就變得很長嗎:3
        }
        cout << "\n";

        // comments
        if (allPost[postIndex].comments.empty()) {
            cout << "還沒有人留言\n\n";
        } else {
            cout << "留言:\n";
            for (auto it = allPost[postIndex].comments.rbegin();
                 it != allPost[postIndex].comments.rend();
                 it++) {
                cout << UNDERLINE
                     << getAccountById((*it).authorId)->name
                     << RESET_COLOR;
                cout << " at "
                     << ctime(&((*it).id));
                cout << (*it).content
                     << "\n";
            }
        }

        // controls
        int ch = 0;
        cout << "1. 下一篇\n"
             << "2. 上一篇\n"
             << "3. 留言\n"
             << "4. 打心\n"
             << "5. 離開\n";
        cout << "選擇: ";
        cin >> ch;

        if (ch == 1) {
            postIndex = postIndex - 1 >= 0 ? postIndex - 1 : postIndex;
        }

        if (ch == 2) {
            postIndex = postIndex + 1 < allPost.size() ? postIndex + 1 : postIndex;
        }

        if (ch == 3) commentPostUI(allPost[postIndex]);

        if (ch == 4) {
            if (addLike(allPost[postIndex].id, currentUser->id)) {
                allPost[postIndex].likes.push_back(currentUser->id);
                // 很麻煩，除了資料庫要更新，本地也要更新
                // 如果做成每次刷新都更新一次感覺很浪費效能
            }
        }

        if (ch == 5) break;
    }
}

void addPostUI() {
    system("cls");

    string title;
    cout << "標題:";
    cin >> title;

    cout << "內容(^D離開):\n";
    string content = input();

    Post p = {time(NULL),
              currentUser->id,
              title, content,
              vector<Comment>(0),
              vector<time_t>(0)};
    addPost(p);
}

void setPostFilterUI() {
    system("cls");

    cout << "自己的貼文: ";
    if ((filterMask & FILTER_USER) == 0)
        cout << "開啟\n";
    else
        cout << "關閉\n";

    cout << "他人的貼文: ";
    if ((filterMask & FILTER_OTHER) == 0)
        cout << "開啟\n";
    else
        cout << "關閉\n";

    cout << "\n";

    int ch;
    cout << "1. 切換自己的貼文顯示狀態\n"
         << "2. 切換他人的貼文顯示狀態\n"
         << "3. 離開\n"
         << "選擇: ";
    cin >> ch;

    if (ch == 1) toggleMask(filterMask, FILTER_USER);
    if (ch == 2) toggleMask(filterMask, FILTER_OTHER);
    if (ch == 3) return;

    // bitwise很好玩欸
}

void commentPostUI(Post& post) {
    cout << "\n\n"
         << "留言(^D離開):\n";
    string content = input();

    Comment com = {time(NULL), post.id, currentUser->id, content};
    addComment(post.id, com);
    post.comments.push_back(com);
}
