/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include "User.h"

using std::string;
using std::vector;

User::User(string userName) : userName(userName)/* TODO(student): initialize */
{
  // TODO(student): implement constructor checks
  if (userName.empty())
  {
    throw std::invalid_argument("empty userName");
  }
  if ((int(userName.at(0)) < int('a')) || (int(userName.at(0)) > int('z')))
  {
    throw std::invalid_argument("invalid username characters");
  }
  for (unsigned int i = 0; i < userName.length(); ++i)
  {
    if ((int(userName.at(i)) > int('A')) && (int(userName.at(i)) < int('Z')))
    {
      throw std::invalid_argument("no caps letters");
    }
    }
    // this->userName = userName;
}

string User::getUserName()
{
  // TODO(student): implement getter
  return userName;
}

vector<Post *> &User::getUserPosts()
{
  // TODO(student): implement getter
  return userPosts;
}

void User::addUserPost(Post *post)
{
  // TODO(student): add post to user posts
  // error check and add post to userPosts
  if (post == nullptr) {
    throw std::invalid_argument("");
  }
  else {
      userPosts.push_back(post);
  }
}
