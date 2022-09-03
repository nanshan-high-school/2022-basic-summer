#include <iostream>
#include<vector>
using namespace std;
int go,check1,ch,wrong;
string ids,posts,dates,usernames,passwords,accounts,comments,dd;
vector<string> account; //帳號
vector<string> username; //使用者名稱
vector<string> password; //密碼
vector<string> post; //發文
vector<string> date;  //發布日
vector<string> justpost; //已經發文的人
vector<string> becommandedpost; //有被留言的貼文
vector<string> commandd; //留言
vector<string> justcommand; //已經留言的人
vector<string> commentdate; //留言發布日
vector<string> begoodpost; //有被按讚的貼文
vector<string> good; //已經按讚的人
int login() {
  if(account.size()==0){ //沒有帳號亂登入
    cout<<"喜勒考這個地方根本就沒有半個帳號!"<<"\n"<<"\n";
    check1=3;
  }else{
    cout<<"使用facebook帳號登入"<<"\n"<<"輸入帳號:";
    cin>>accounts;
    cout<<"輸入密碼:";
    cin>>passwords;
    for(int i=0;i<=account.size();i++){
      if(account[i]==accounts){ //驗證帳號
        if(password[i]==passwords){ //驗證密碼
          cout<<username[i];
          ids=username[i];
          cout<<",登入成功!"<<"\n"<<"\n";
          wrong=0;
          check1=2;
          break;
        }else{
          wrong=1;
        }
      }else{
        wrong=1;
      }
    }
    if(wrong==1){
      cout<<"帳號或密碼錯誤 請重新輸入!"<<"\n"<<"\n";
      check1=3;
    }
  }
  return 0;
} //登入
int regist() {
  //註冊
  cout<<"創建一個帳號:";
  cin>>accounts;
  if(account.size()!=0){
    for(int i=0;i<=account.size();i++){
      //判斷帳號是否重複註冊
      if(accounts==account[i]){
        cout<<"已經有相同的帳號了!";
        cout<<"\n";
        cout<<"\n";
        check1=3;
        break;
      }else{
        check1=0;
      }
    }
  }else{
    check1=0;
  }
  if(check1==0){
    account.push_back(accounts);
    cout<<"輸入密碼:";
    cin>>passwords;
    password.push_back(passwords);
    cout<<"輸入暱稱:";
    cin>>usernames;
    username.push_back(usernames);
    cout<<"註冊成功!";
    cout<<"\n";
    cout<<"\n";
    check1=3;
  }
  return 0;
} //註冊
int welcome() {
  cout<<"歡迎來到facebook，我們不會竊取你所有的隱私"<<"\n"<<"按1登入(沒有帳號? 按2註冊):";
  cin>>go;
  if(go==2){
    regist();
  }else if(go==1){
    login();
  }else{
    cout<<"輸入1或2好嗎"<<"\n"<<"\n";
    check1=3;
  }
  return 0;
}  //起始介面
int postArticles() {
  if(go==1){ //發文
    cout<<"輸入文章(按enter發布):";
    cin>>posts;
    post.push_back(posts);
    cout<<"日期(yyyy/mm/dd):";
    cin>>dates;
    date.push_back(dates);
    justpost.push_back(ids);
  }else if(go==2){ //刪文
    cout<<"你所有的貼文:"<<"\n";
    int youinjustpost=0; //判斷你有沒有發文
    if(post.size()==0){
        cout<<"你目前沒有貼文!"<<"\n";
    }else{
      for(int i=0;i<post.size();i++){
        if(justpost[i]==ids){
          youinjustpost=1;
          cout<<date[i]<<"\n"<<post[i]<<"\n";
        }
      }
    }
    if(youinjustpost!=0){
      string d;
      int check1;
      cout<<"要刪除哪一天的貼文:";
      cin>>d;
      for(int i=0;i<=post.size();i++){
        if(date[i]==d and justpost[i]==ids){
          check1=i;
        }
      }
      post.erase(post.begin()+check1);
      date.erase(date.begin()+check1);
      justpost.erase(justpost.begin()+check1);
      cout<<"您的文章已刪除!"<<"\n"<<"\n";
    }
  }else if(go==3){ //瀏覽貼文
    if(post.size()==0){
      cout<<"尚無貼文!"<<"\n"<<"\n";
      check1=1;
    }else{
      for(int i=0;i<post.size();i++){   
        if(justpost[i]==ids and post.size()==1){
          cout<<"尚無貼文!"<<"\n"<<"\n";
          break;
        }else if(justpost[i]==ids and post.size()!=1){
          cout<<"\n";
        }else{
          cout<<date[i]<<"\n"<<justpost[i]<<"\n"<<post[i]<<"\n";
          int goods=0;
          if(good.size()==0){
            goods=0;
          }else{
            for(int j=0;j<good.size();j++){
              if(post[i]==begoodpost[j]){
                goods++;
              }
            }
          }
          cout<<goods<<"個讚";
          int commentts=0;
          if(justcommand.size()==0){
            commentts=0;
          }else{
            for(int j=0;j<justcommand.size();j++){
              if(post[i]==becommandedpost[j]){
                commentts++;
              }
            }
          }
          cout<<commentts<<"則留言"<<"\n";
          cout<<"按讚(按1)留言(按2)看留言(按3)掠過(按4):";
          cin>>ch;
          if(ch==1){ //按讚
            good.push_back(ids);
            begoodpost.push_back(post[i]);
            cout<<"已按讚!"<<"\n";
          }else if(ch==2){ //留言
            cout<<"輸入留言:";
            cin>>comments;
            commandd.push_back(comments);
            cout<<"輸入日期(yyyy/mm/dd):";
            cin>>dd;
            commentdate.push_back(dd);
            cout<<"已發布!"<<"\n";
            justcommand.push_back(ids);
            becommandedpost.push_back(post[i]);
          }else if(ch==3){ //看留言
            cout<<"\n"<<"所有留言:"<<"\n";
            for(int j=0;j<justcommand.size();j++){
              if(post[i]==becommandedpost[j]){
                cout<<commentdate[j]<<"\n"<<justcommand[j]<<"\n"<<commandd[j]<<"\n"<<"\n";
              }
            }
          }else if(ch==4){ //掠過
            cout<<"\n";
          }
        }
      }
    }
    check1=1;
  }else if(go==4){
    int change,j;
    string accounts,newpassword;
    cout<<"更改密碼請按1"<<"\n"<<"更改暱稱請按2"<<"\n"<<"查看個人資料請按3"<<"\n"<<"查看自己的貼文請按4:";
    cin>>change;
    if(change==1){
      cout<<"帳號:";
      cin>>accounts;
      cout<<"原密碼:";
      cin>>passwords;
      for(int i=0;i<account.size();i++){
        if(accounts==account[i]){
          if(passwords==password[i]){
            wrong=0;
            j=i;
            break;
          }else{
            wrong=1;
          }
        }else{
          wrong=1;
        }
      }
      if(wrong==1){
        cout<<"帳號或密碼錯誤 請重新輸入!";
        check1=2;
      }else{
        cout<<"新密碼:";
        cin>>newpassword;
        if(newpassword==passwords){
          cout<<"新密碼不可與舊密碼相同!";
          check1=2;
        }else{
          password[j]=newpassword;
          cout<<"你的密碼已更改!"<<"\n"<<"\n";
        }
      }
    }else if(change==2){
      string newname;
      int j;
      cout<<"輸入新暱稱:";
      cin>>newname;
      for(int i=0;i<username.size();i++){
        if(usernames==username[i]){
          j=i;
          break;
        }
      }
      username[j]=newname;
      cout<<"你的暱稱已更改!"<<"\n"<<"\n";
    }else if(change==3){
      int j;
      for(int i=0;i<account.size();i++){
        if(accounts==account[i]){
          j=i;
        }
      }
      cout<<"你的個人資料"<<"\n"<<"帳號:";
      cout<<account[j]<<"\n";
      cout<<"密碼:";
      cout<<passwords<<"\n";
      cout<<"暱稱:";
      cout<<usernames<<"\n";
      cout<<"按1離開:";
      int exit;
      cin>>exit;
      if(exit==1){
        check1=2;
        cout<<"\n"<<"\n";
      }
    }else if(change==4){
      cout<<"你所有的貼文:"<<"\n";
      int youinjustpost=0; //判斷你有沒有發文
      if(post.size()==0){
        cout<<"你目前沒有貼文!"<<"\n";
      }else{
        for(int i=0;i<post.size();i++){
          if(justpost[i]==ids){
            youinjustpost=1;
            cout<<date[i]<<"\n"<<post[i]<<"\n";
          }
        }
      }
      cout<<"按1離開:";
      int exit;
      cin>>exit;
      if(exit==1){
        check1=2;
        cout<<"\n"<<"\n";
      }
    }
  }else if(go==5){
    cout<<"馬克祖刻薄感謝您的使用"<<"\n"<<"\n";
    check1=3;
  }
  return 0;
}//主要功能
int choose() {
  cout<<"發文請按1"<<"\n"<<"刪除貼文請按2"<<"\n"<<"瀏覽貼文的話請按3"<<"\n"<<"設定請按4"<<"\n"<<"登出請按5"<<"\n"<<"請輸入你想執行的功能:";
  cin>>go;
  postArticles();
  return 0;
} //功能選擇
int main() {
  while(true){
  welcome();
    while(true){
      if(check1==2 or check1==1){
        choose();
      }else if(check1==3){
        break;
      }
    }
  }
}
//check1=0註冊成功跳login check1=1無貼文且跳choose check1=2登入成功且跳choose check1=3跳welcome