#include <ctime>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct PERSON {
  int sex, age, birthdayYear, birthdayMonth, birthdayDay;
  string name, password, nickname, introduction;
  vector<string> posts;
};

struct POST {
  bool deleted = false, timeLimit = false;
  int postYear, postMonth, postDay, postHour, postMinute, postSecond;
  string accountName, person, topic, content;
  vector<string> likes;
  vector<pair<string, string>> comments;
};

PERSON *currentUser, *watchingPerson;
vector<PERSON> accounts = {};
vector<POST> posts = {};
bool isLogin = false;

int Input() {
  int input;
  cin >> input;
  return input;
}

int Welcome() {
  cout << "\n歡迎來到小克社群軟體\n";
  cout << "==========================================\n\n";
  cout << "1 登入\n";
  cout << "2 註冊\n";

  return Input();
}

void Login() {
  string accountName;
  cout << "帳號名稱:";
  cin >> accountName;
  bool accountExist = false;
  for (int i = 0; i < accounts.size(); i++) {
    if (accountName == accounts[i].name) {
      currentUser = &(accounts[i]);
      accountExist = true;
      break;
    }
  }

  string password;
  cout << "密碼:";
  cin >> password;
  if (accountExist) {
    if (password == currentUser->password) {
      isLogin = true;
      cout << "\n~~歡迎，" << currentUser->nickname << "~~\n";
      return;
    }
  }
  cout << "帳號密碼錯誤，請重新輸入\n\n";
}

int Choosing() {
  cout << "\n功能選擇:\n";
  cout << "1 查看自己的個人資訊\n";
  cout << "2 查看大家的貼文\n";
  cout << "3 Po文\n";
  cout << "4 Po限時貼文\n";
  cout << "5 登出\n";

  return Input();
}

void Info(PERSON *person) {
  cout << "\n" << person->nickname << "的個人資訊\n";
  cout << "-----------------------------------\n";
  switch (person->sex) {
  case 1:
    cout << "性別:男  ";
    break;
  case 2:
    cout << "性別:女  ";
    break;
  case 3:
    cout << "性別:其他  ";
    break;
  }
  cout << "生日:" << person->birthdayYear << "/" << person->birthdayMonth
       << "/" << person->birthdayDay << "(" << person->age
       << "歲)\n\n";
  if (person->introduction != "") {
    cout << "關於" << person->nickname << ":" << person->introduction << "\n";
  }
  cout << "-----------------------------------\n";
}

int YourInfo() {
  Info(&(*currentUser));
  cout << "1 編輯個人資訊\n";
  cout << "2 查看你的貼文\n";
  cout << "3 更改密碼\n";
  cout << "4 回到首頁\n";

  return Input();
}

void Age(PERSON *person) {
  bool pass = false;

  while (pass != true) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "出生年:";
    cin >> person->birthdayYear;
    if (person->birthdayYear > (1900 + ltm->tm_year)) {
      cout << "錯誤，請重新輸入\n\n";
      continue;
    }

    cout << "出生月:";
    cin >> person->birthdayMonth;
    if (person->birthdayMonth > 12 || person->birthdayMonth < 0) {
      cout << "錯誤，請重新輸入\n\n";
      continue;
    }
    if (person->birthdayYear == (1900 + ltm->tm_year)) {
      if (person->birthdayMonth > (1 + ltm->tm_mon)) {
        cout << "錯誤，請重新輸入\n\n";
        continue;
      }
    }

    cout << "出生日:";
    cin >> person->birthdayDay;
    if (person->birthdayYear == (1900 + ltm->tm_year)) {
      if (person->birthdayMonth == (1 + ltm->tm_mon)) {
        if (person->birthdayDay > (ltm->tm_mday)) {
          cout << "錯誤，請重新輸入\n\n";
          continue;
        }
      }
    }

    bool leap = false, dayUnPass = false;
    switch (person->birthdayMonth) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
      if (person->birthdayDay > 31 || person->birthdayDay < 0) {
        dayUnPass = true;
      }
      break;

    case 4: case 6: case 9: case 11:
      if (person->birthdayDay > 30 || person->birthdayDay < 0) {
        dayUnPass = true;
      }
      break;

    case 2:
      if (person->birthdayYear % 4 == 0) {
        if (person->birthdayYear % 100 == 0) {
          if (person->birthdayYear % 400 == 0) {
            leap = !leap;
          }
          leap = !leap;
        }
        leap = !leap;
      }

      if (leap) {
        if (person->birthdayDay > 29 || person->birthdayDay < 0) {
          dayUnPass = true;
        }
      } else {
        if (person->birthdayDay > 28 || person->birthdayDay < 0) {
          dayUnPass = true;
        }
      }
    }
    if (dayUnPass) {
      cout << "錯誤，請重新輸入\n\n";
      continue;
    }

    person->age = (1900 + ltm->tm_year) - person->birthdayYear;
    if (person->birthdayMonth >= (1 + ltm->tm_mon) &&
        person->birthdayDay > (ltm->tm_mday)) {
      person->age--;
    }

    if (person->age < 0) {
      cout << "哪裡怪怪的，請重新輸入\n\n";
      continue;
    } else if (person->age > 118) {
      cout << "你比世界上最長壽的人還老，請重新輸入\n\n";
      continue;
    }
    pass = true;
  }
}

void EditYourInfo() {
  int input;
  while (true) {
    cout << "選擇你要編輯的地方:\n";
    cout << "1 名字\n";
    cout << "2 性別\n";
    cout << "3 生日\n";
    cout << "4 簡介\n";
    cout << "5 回上頁\n";

    cin >> input;
    if (input != 1 && input != 2 && input != 3 && input != 4 && input != 5) {
      cout << "無效的選項，請重新輸入\n\n";
      continue;
    }
    break;
  }
  if (input == 5)
    return;

  cout << "請輸入密碼:";
  string verifyPassword;
  cin >> verifyPassword;
  if (verifyPassword != currentUser->password) {
    cout << "密碼有誤\n\n";
    return;
  }

  switch (input) {
  case 1: {
    string newNickname;
    while (true) {
      cout << "名字(15字以內):";
      cin >> newNickname;
      if (newNickname.length() > 15) {
        cout << "超過字數限制，請重新輸入\n\n";
        continue;
      }
      break;
    }
    for (int i = 0; i < posts.size(); i++) {
      if (posts[i].person == currentUser->nickname) {
        posts[i].person = newNickname;
      }
    }

    currentUser->nickname = newNickname;
    cout << "\n更改成功\n";
    break;
  }
  case 2:
    while (true) {
      cout << "性別(男:1 女:2 其他:3):";
      cin >> currentUser->sex;
      if (currentUser->sex != 1 && currentUser->sex != 2 &&
          currentUser->sex != 3) {
        cout << "無效的選項，請重新輸入\n\n";
        continue;
      }
      cout << "\n更改成功\n";
      break;
    }
    break;

  case 3:
    Age(&(*currentUser));
    break;

  case 4:
    cout << "簡介:";
    cin.ignore();
    getline(cin, currentUser->introduction);
    cout << "\n更改成功\n";
  }
}

void ShowPost(POST *post) {
  if (post->deleted) {
    cout << "\n[這則貼文已被刪除]\n\n";
    return;
  }

  time_t now = time(0);
  tm *ltm = localtime(&now);
  if (post->timeLimit) {
    if (((ltm->tm_mday) - post->postDay) >= 1) {
      post->deleted = true;
      cout << "\n[這則貼文已被刪除]\n\n";
      return;
    } else {
      cout << "\n*限時*  ";
    }
  }

  cout << post->person << " [" << post->topic << "] ";
  if (((1900 + ltm->tm_year) - post->postYear) == 0) {
    if (((1 + ltm->tm_mon) - post->postMonth) == 0) {
      if (((ltm->tm_mday) - post->postDay) == 0) {
        if (((1 + ltm->tm_hour) - post->postHour) == 0) {
          if (((1 + ltm->tm_min) - post->postMinute) == 0) {
            cout << ((1 + ltm->tm_sec) - post->postSecond) << "秒前";
          } else {
            cout << ((1 + ltm->tm_min) - post->postMinute) << "分鐘前";
          }
        } else {
          cout << ((1 + ltm->tm_hour) - post->postHour) << "小時前";
        }
      } else {
        cout << ((ltm->tm_mday) - post->postDay) << "天前";
      }
    } else {
      cout << ((1 + ltm->tm_mon) - post->postMonth) << "個月前";
    }
  } else {
    cout << ((1900 + ltm->tm_year) - post->postYear) << "年前";
  }
  cout << "\n" << post->content << "\n";
  cout << "-----------------------------------\n";
  cout << post->likes.size()
       << "喜歡     " << post->comments.size() << "留言\n\n";
}

void Like(POST *post) {
  bool haveLike = false;
  for (int i = 0; i < post->likes.size(); i++) {
    if (post->likes[i] == currentUser->nickname) {
      haveLike = true;
      post->likes[i] = post->likes.back();
      post->likes.pop_back();
      break;
    }
  }

  if (haveLike == false) {
    post->likes.push_back(currentUser->nickname);
  }
}

void SeeWhoLike(POST *post) {
  cout << "\n";
  if (post->likes.empty()) {
    cout << "沒有任何喜歡:(\n\n";
  } else {
    for (int i = 0; i < post->likes.size(); i++) {
      cout << post->likes[i] << "\n";
    }
    cout << "\n";
  }
}

void Comment(vector<pair<string, string>> *commentVector) {
  COMMENTRELOAD:
  string comment;
  if (commentVector->empty()) {
    REASK:
    cout << "這裡還沒有留言\n\n";
    cout << "1 留言\n";
    cout << "2 回到貼文\n";
    switch (Input()) {
    case 1:
      cout << "留言:";
      cin.ignore();
      getline(cin, comment);
      commentVector->push_back({currentUser->nickname, comment});
      cout << "\n";
      goto COMMENTRELOAD;

    case 2:
      break;

    default:
      cout << "無效的選項，請重新輸入\n\n";
      goto REASK;
    }
  }

  bool stay = true;
  for (int i = commentVector->size() - 1; i >= 0; i--) {
    cout << (*commentVector)[i].first << ":" << (*commentVector)[i].second
         << "\n";
    while ((commentVector->size() - i) == 10 || i == 0) {
      cout << "1 查看更舊的留言\n";
      cout << "2 留言\n";
      cout << "3 回到貼文\n";
      switch (Input()) {
      case 1:
        stay = false;
        if (i == 0) {
          cout << "沒有更多的留言了\n\n";
        }
        break;

      case 2:
        cout << "留言:";
        cin.ignore();
        getline(cin, comment);
        commentVector->push_back({currentUser->nickname, comment});
        cout << "\n";
        goto COMMENTRELOAD;

      case 3:
        return;

      default:
        cout << "無效的選項，請重新輸入\n\n";
      }

      if (stay) {
        continue;
      } else {
        break;
      }
    }
  }
  return;
}

void SeeYourPosts() {
  vector<int> userPosts = {};
  for (int i = posts.size() - 1; i >= 0; i--) {
    if (posts[i].person == currentUser->nickname) {
      userPosts.push_back(i);
    }
  }
  if (userPosts.empty()) {
    cout << "你還沒有任何貼文!\n\n";
    return;
  }

  int number = 0;
  bool stay = true;
  while (stay) {
    POST *currentUserPost = &posts[userPosts[number]];
    ShowPost(&(*currentUserPost));
    REASK:
    cout << "1 喜歡/取消喜歡\n";
    cout << "2 查看喜歡的人\n";
    cout << "3 查看留言\n";
    cout << "4 查看更舊的貼文\n";
    cout << "5 查看更新的貼文\n";
    cout << "6 刪除這則貼文\n";
    cout << "7 回到個人資訊\n";

    switch (Input()) {
    case 1:
      if (currentUserPost->deleted) {
        cout << "錯誤\n\n";
        goto REASK;
      }

      Like(&(*currentUserPost));
      break;

    case 2:
      if (currentUserPost->deleted) {
        cout << "錯誤\n\n";
        goto REASK;
      }

      SeeWhoLike(&(*currentUserPost));
      break;

    case 3:
      if (currentUserPost->deleted) {
        cout << "錯誤錯誤\n\n";
        goto REASK;
      }

      Comment(&(currentUserPost->comments));
      break;

    case 4:
      if (number == userPosts.size() - 1) {
        cout << "這已經是最舊的!\n\n";
        goto REASK;
      } else {
        number++;
        break;
      }

    case 5:
      if (number == 0) {
        cout << "這已經是最新的!\n\n";
        goto REASK;
      } else {
        number--;
        break;
      }

    case 6: {
      if (currentUserPost->deleted) {
        cout << "錯誤錯誤\n\n";
        goto REASK;
      }

      cout << "請輸入密碼:";
      string verifyPassword;
      cin >> verifyPassword;
      if (verifyPassword != currentUser->password) {
        cout << "密碼錯誤\n\n";
        break;
      }

      currentUserPost->deleted = true;
      break;
    }
    case 7:
      stay = false;
      break;

    default:
      cout << "無效的選項，請重新輸入\n\n";
      goto REASK;
    }
  }
}

void ChangePassword() {
  string verifyPassword, newPassword;
  cout << "原本密碼:";
  cin >> verifyPassword;
  if (verifyPassword != currentUser->password) {
    cout << "密碼錯誤\n\n";
    return;
  }

  bool pass = false;
  while (pass != true) {
    cout << "新密碼:";
    cin >> newPassword;
    cout << "再輸入一次:";
    cin >> verifyPassword;
    if (newPassword != verifyPassword) {
      cout << "密碼不一致，請重新輸入\n\n";
      continue;
    }
    pass = true;
  }

  currentUser->password = newPassword;
  cout << "\n更改成功\n";
}

bool ViewPosts() {
  vector<int> otherPosts = {};
  for (int i = posts.size() - 1; i >= 0; i--) {
    if (posts[i].person != currentUser->nickname) {
      otherPosts.push_back(i);
    }
  }
  if (otherPosts.empty()) {
    cout << "這裡還很空:(\n\n";
    return false;
  }

  bool stay = true;
  int number = 0;
  while (stay) {
    POST *watchingPersonPost = &posts[otherPosts[number]];
    ShowPost(&(*watchingPersonPost));
    REASK:
    cout << "1 喜歡/取消喜歡\n";
    cout << "2 查看喜歡的人\n";
    cout << "3 查看留言\n";
    cout << "4 查看更舊的貼文\n";
    cout << "5 查看更新的貼文\n";
    cout << "6 查看他/她的個人資訊\n";
    cout << "7 回到首頁\n";

    switch (Input()) {
    case 1:
      if (watchingPersonPost->deleted) {
        cout << "錯誤\n\n";
        goto REASK;
      }

      Like(&(*watchingPersonPost));
      break;

    case 2:
      if (watchingPersonPost->deleted) {
        cout << "錯誤\n\n";
        goto REASK;
      }

      SeeWhoLike(&(*watchingPersonPost));
      break;

    case 3:
      if (watchingPersonPost->deleted) {
        cout << "錯誤錯誤\n\n";
        goto REASK;
      }

      Comment(&(watchingPersonPost->comments));
      break;

    case 4:
      if (number == posts.size() - 1) {
        cout << "這已經是最舊的!\n\n";
        goto REASK;
      } else {
        number++;
        break;
      }

    case 5:
      if (number == 0) {
        cout << "這已經是最新的!\n\n";
        goto REASK;
      } else {
        number--;
        break;
      }

    case 6:
      if (watchingPersonPost->deleted) {
        cout << "錯誤\n\n";
        goto REASK;
      }

      for (int i = 0; i < accounts.size(); i++) {
        if (watchingPersonPost->accountName == accounts[i].name) {
          watchingPerson = &(accounts[i]);
        }
      }

      return true;

    case 7:
      return false;

    default:
      cout << "無效的選項，請重新輸入\n\n";
      goto REASK;
    }
  }
}

bool SeePersonInfo() {
  Info(&(*watchingPerson));
  while (true) {
    cout << "1 察看他/她的貼文\n";
    cout << "2 回到上頁\n";

    switch (Input()) {
    case 1:
      return true;

    case 2:
      return false;

    default:
      cout << "無效的選項，請重新輸入\n\n";
      break;
    }
  }
}

void SeePersonPost() {
  vector<int> PersonPosts = {};
  for (int i = posts.size() - 1; i >= 0; i--) {
    if (posts[i].person == watchingPerson->nickname) {
      PersonPosts.push_back(i);
    }
  }

  int number = 0;
  bool stay = true;
  while (stay) {
    POST *currentPersonPost = &posts[PersonPosts[number]];
    ShowPost(&(*currentPersonPost));
    REASK:
    cout << "1 喜歡/取消喜歡\n";
    cout << "2 查看喜歡的人\n";
    cout << "3 查看留言\n";
    cout << "4 查看更舊的貼文\n";
    cout << "5 查看更新的貼文\n";
    cout << "6 回到上頁\n";

    switch (Input()) {
    case 1:
      if (currentPersonPost->deleted) {
        cout << "錯誤\n\n";
        goto REASK;
      }

      Like(&(*currentPersonPost));
      break;

    case 2:
      if (currentPersonPost->deleted) {
        cout << "錯誤\n\n";
        goto REASK;
      }

      SeeWhoLike(&(*currentPersonPost));
      break;

    case 3:
      if (currentPersonPost->deleted) {
        cout << "錯誤錯誤\n\n";
        goto REASK;
      }

      Comment(&(currentPersonPost->comments));
      break;

    case 4:
      if (number == PersonPosts.size() - 1) {
        cout << "這已經是最舊的!\n\n";
        goto REASK;
      } else {
        number++;
        break;
      }

    case 5:
      if (number == 0) {
        cout << "這已經是最新的!\n\n";
        goto REASK;
      } else {
        number--;
        break;
      }

    case 6:
      stay = false;
      break;

    default:
      cout << "無效的選項，請重新輸入\n\n";
      goto REASK;
    }
  }
}

void Post() {
  POST newPost;
  cout << "主題:";
  cin.ignore();
  getline(cin, newPost.topic);
  cout << "內容:";
  getline(cin, newPost.content);
  newPost.person = currentUser->nickname;
  newPost.accountName = currentUser->name;

  time_t now = time(0);
  tm *ltm = localtime(&now);
  newPost.postYear = (1900 + ltm->tm_year);
  newPost.postMonth = (1 + ltm->tm_mon);
  newPost.postDay = (ltm->tm_mday);
  newPost.postHour = (1 + ltm->tm_hour);
  newPost.postMinute = (1 + ltm->tm_min);
  newPost.postSecond = (1 + ltm->tm_sec);

  posts.push_back(newPost);
  cout << "貼文成功\n";
}

void Story() {
  POST newStory;
  cout << "主題:";
  cin.ignore();
  getline(cin, newStory.topic);
  cout << "內容:";
  getline(cin, newStory.content);
  newStory.person = currentUser->nickname;
  newStory.accountName = currentUser->name;

  time_t now = time(0);
  tm *ltm = localtime(&now);
  newStory.postYear = (1900 + ltm->tm_year);
  newStory.postMonth = (1 + ltm->tm_mon);
  newStory.postDay = (ltm->tm_mday);
  newStory.postHour = (1 + ltm->tm_hour);
  newStory.postMinute = (1 + ltm->tm_min);
  newStory.postSecond = (1 + ltm->tm_sec);

  newStory.timeLimit = true;

  posts.push_back(newStory);
  cout << "貼文成功\n";
}

void CreateAccount() {
  bool pass = false;
  PERSON newPerson;
  while (pass != true) {
    string accountName;
    cout << "\n帳號名稱(15字以內):";
    cin >> accountName;
    if (accountName.length() > 15) {
      cout << "超過字數限制，請重新輸入\n\n";
      continue;
    }
    bool same = false;
    for (int i = 0; i < accounts.size(); i++) {
      if (accountName == accounts[i].name) {
        cout << "這個名稱已被用過，請重新輸入\n\n";
        same = true;
        break;
      }
    }
    if (same) {
      continue;
    }

    string password, password2;
    cout << "密碼:";
    cin >> password;
    cout << "再輸入一次:";
    cin >> password2;
    if (password != password2) {
      cout << "密碼不一致，請重新輸入\n\n";
      continue;
    }

    newPerson.name = accountName;
    newPerson.password = password;
    cout << "創建成功，接著請填個人基本資料\n\n";
    pass = true;
  }

  while (true) {
    cout << "名字(15字以內):";
    cin >> newPerson.nickname;
    if (newPerson.nickname.length() > 15) {
      cout << "超過字數限制，請重新輸入\n\n";
      continue;
    }
    break;
  }

  pass = false;
  while (pass != true) {
    cout << "性別(男:1 女:2 其他:3):";
    cin >> newPerson.sex;
    if (newPerson.sex != 1 && newPerson.sex != 2 && newPerson.sex != 3) {
      cout << "無效的選項，請重新輸入\n\n";
      continue;
    }
    pass = true;
  }

  Age(&newPerson);

  accounts.push_back(newPerson);
  cout << "已輸入完成，將回到「歡迎介面」\n\n";
}

int main() {
  while (true) {
    switch (Welcome()) {
    case 1:
      Login();

      while (isLogin) {
        switch (Choosing()) {
        case 1:
        AGAIN:
          switch (YourInfo()) {
          case 1:
            EditYourInfo();
            goto AGAIN;

          case 2:
            SeeYourPosts();
            goto AGAIN;

          case 3:
            ChangePassword();
            goto AGAIN;

          case 4:
            break;

          default:
            cout << "無效的選項，請重新輸入\n\n";
            goto AGAIN;
          }
          break;

        case 2:
          while (ViewPosts()) {
            while (SeePersonInfo()) {
              SeePersonPost();
            }
          }
          break;

        case 3:
          Post();
          break;

        case 4:
          Story();
          break;

        case 5:
          isLogin = false;
          break;

        default:
          cout << "無效的選項，請重新輸入\n\n";
        }
      }
      break;

    case 2:
      CreateAccount();
      break;

    default:
      cout << "無效的選項，請重新輸入\n\n";
    }
  }
}