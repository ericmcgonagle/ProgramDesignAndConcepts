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
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tagName) : tagName(tagName)/* TODO(student): initialize */
{
  // TODO(student): implement constructor checks
  // error check and then throw any errors

  if (tagName.length() < 2)
  {
    throw std::invalid_argument("invalid length");
  }
  if (tagName.at(0) != '#')
  {
    throw std::invalid_argument("invalid start of tag name");
  }
  if ((int(tagName.at(1)) < int('a')) || (int(tagName.at(1)) > int('z')))
  {
    throw std::invalid_argument("");
  }
  if (tagName.back() == '!' || tagName.back() == '.' || tagName.back() == '?' || tagName.back() == ',')
  {
    throw std::invalid_argument("");
  }
  for (unsigned int i = 0; i < tagName.length(); ++i)
  {
    if ((int(tagName.at(i))) >= int('A') && (int(tagName.at(i)) <= int('Z')))
    {
      throw std::invalid_argument("");
    }
  }

  //this->tagName = tagName;
}

string Tag::getTagName()
{
  // TODO(student): implement getter
  return tagName;
}

vector<Post *> &Tag::getTagPosts()
{
  // TODO(student): implement getter
  return tagPosts;
}

void Tag::addTagPost(Post *post)
{
  // TODO(student): add post to tag posts
  if (post == nullptr)
  {
    throw std::invalid_argument("");
  }
  else
  {
    tagPosts.push_back(post);
  }
}
