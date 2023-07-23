/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include "Post.h"

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
    : postId(postId), userName(userName), postText(postText)
{
  if (postId == 0 || userName == "" || postText == "")
  {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId()
{
  return postId;
}

string Post::getPostUser()
{
  return userName;
}

string Post::getPostText()
{
  return postText;
}

vector<string> Post::findTags()
{
  // TODO(student): extracts candidate tags based on occurrences of # in the post
  // create a temporary string to hold the hashtag post from postText to then
  // be added in to the findTags vector
  std::vector<std::string> tagsList;
  std::string tempString;
  tempString = "";

  // iterate through postText to see if there is a case of '#'
  // if there is '#', then add each successive character to tempString until there is a space
  // and then add tempString to tagsList vector after performing proper error checks
  for (unsigned int i = 0; i < postText.length(); ++i)
  {
    if (postText.at(i) == '#')
    {
      while ((!std::isspace(postText.at(i))) && !(i == postText.length()))
      {
        tempString.push_back(postText.at(i));
        if (i < postText.length() - 1)
        {
          ++i;
        }
        else
        {
          break;
        }
      }
    }
    else
    {
      continue;
    }
    while (tempString.back() == '!' || tempString.back() == '?' || tempString.back() == '.' || tempString.back() == ',')
    {
      tempString.pop_back();
    }
    for (unsigned int k = 0; k < tempString.length(); ++k)
    {
      tempString.at(k) = tolower(tempString.at(k));
    }

    tagsList.push_back(tempString);

    tempString.clear();
  }

  return tagsList;
}
