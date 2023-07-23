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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Network.h"

using std::string;
using std::vector;

Network::Network()
{
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName)
{
  // TODO(student): load user and post information from file
  std::ifstream inputFile(fileName);
  if (!inputFile.is_open())
  {
    throw std::invalid_argument("Coud not open file");
  }
  string userInput;
  string infoType;
  string inputUsername;
  unsigned int inputId;
  string inputPost;
  string postTextInput;
  while (!inputFile.eof())
  {
    getline(inputFile, userInput);
    if (userInput == "") {
      break;
    }
    std::istringstream ss(userInput);
    ss >> infoType;
    // start with input type "user" and adding the userName
    if (infoType == "User")
    {
      // take input for the userName and try adding the user
      // catch any invalid arguments that occur when trying to add user in respective method
      // throw runtime error if the format isn't correct when reading in User
      ss >> inputUsername;
      try
      {
        addUser(inputUsername);
      }
      catch (const std::invalid_argument)
      {
        throw std::runtime_error("Error adding user");
      }
      if (ss >> inputUsername)
      {
        throw std::runtime_error("User entry not following specified format");
      }
    }

    // take input for post and try adding post
    // catch any invalid arguments that occur when trying to add post in respective method
    // catch invalid argument error and throw runtime error if the format isn't correct when reading in Post
    else if (infoType == "Post")
    {
      ss >> inputId;
      if (ss.fail())
      {
        throw std::runtime_error("Post entry not following specified format");
      }
      ss >> inputUsername;
      if (ss.fail())
      {
        throw std::runtime_error("Post entry not following specified format");
      }
      ss >> inputPost;
      if (ss.fail())
      {
        throw std::runtime_error("Post entry not following specified format");
      }
      postTextInput.append(inputPost);
      while (ss >> inputPost) {
        postTextInput.append(" ");
        postTextInput.append(inputPost);
        
      }
      // if (ss >> inputPost)
      // {
      //   throw std::runtime_error("Post entry not following specified format");
      // }
        try
        {
          addPost(inputId, inputUsername, postTextInput);
        }
        catch (const std::invalid_argument)
        {
          throw std::runtime_error("Error adding post");
        }
        //users.back()->addUserPost(posts.back());
        postTextInput.clear();
    }
    else
    {
      throw std::runtime_error("Unknown entry (neither user or post");
    }
  }
}

void Network::addUser(string userName)
{
  // TODO(student): create user and add it to network
  bool isException;
  isException = false;
  for (unsigned int i = 0; i < users.size(); ++i)
  {
    if (users.at(i)->getUserName() == userName)
    {
      throw std::invalid_argument("Username not available");
      isException = true;
    }
    // else
    // {
    //   User *newUser = new User(userName);
    //   users.push_back(newUser);
    // }
  }
  if (!isException) {
  User *newUser = new User(userName);
  users.push_back(newUser);
  std::cout << "Added User " << userName << std::endl;
  }
}

void Network::addPost(unsigned int postId, string userName, string postText)
{
  // TODO(student): create post and add it to network
  bool userFound;
  bool tagFound;
  bool canPush;
  bool isException;
  // bool caughtTagException;
  int index;
  string tempText;
  Post *newPost = new Post(postId, userName, postText);
  userFound = false;

  // iterate through posts to see if the post ID already exists
  // make sure user exists before adding post
  for (unsigned int i = 0; i < posts.size(); ++i)
  {
    if (posts.at(i)->getPostId() == newPost->getPostId())
    {
      throw std::invalid_argument("Post ID already exists");
    }
  }
  for (unsigned int i = 0; i < users.size(); ++i)
  {
    if (users.at(i)->getUserName() == newPost->getPostUser())
    {
      userFound = true;
      index = i;
      break;
    }
  }
  if (!userFound)
  {
    throw std::invalid_argument("User not found");
  }
  // if (users.back()->getUserName() == newPost->getPostUser())
  else
  {
    // posts.insert(posts.begin() + index, newPost);
    // users.insert(users.begin() + index, newPost);
    posts.push_back(newPost);
    users.at(index)->addUserPost(newPost);
    // users.back()->addUserPost(newPost);
  }

  // loop through any tags and compare to tags in "tags" before creating a new tag
  // and adding to "tags"
  // caughtTagException = false;
  isException = false;
  for (unsigned int i = 0; i < newPost->findTags().size(); ++i)
  {
    tagFound = false;
    for (unsigned int k = 0; k < tags.size(); ++k)
    {
      if (newPost->findTags().at(i) == tags.at(k)->getTagName())
      {
        tagFound = true;
        // index = k;
        tags.at(k)->addTagPost(newPost);
        //std::cout << "Added Post " << postId << " by " << userName << std::endl;
        break;
      }
    }
    
    if (!tagFound)
    {
      canPush = true;
      Tag *newTag;
      try
      {

        newTag = new Tag(newPost->findTags().at(i));
        
      }
      catch (const std::invalid_argument)
      {
        // caughtTagException = true;
        canPush = false;
        isException = true;
      }
      if (canPush)
      {
        tags.push_back(newTag);
        tags.back()->addTagPost(newPost);
        //std::cout << "Added Post " << postId << " by " << userName << std::endl;
      }
    }
    // else
    // {
    //   tags.at(index)->addTagPost(newPost);
    //   std::cout << "Added Post " << postId << " by " << userName << std::endl;
    // }
  }

  if (!isException)
  {
    std::cout << "Added Post " << postId << " by " << userName << std::endl;
  }
}

vector<Post *> Network::getPostsByUser(string userName)
{
  // TODO(student): return posts created by the given user
  bool userPresent;
  unsigned int index;
  vector<Post *> userPosts;
  userPresent = false;
  if (userName.empty())
  {
    throw std::invalid_argument("username is empty");
  }
  for (unsigned int i = 0; i < users.size(); ++i)
  {
    if (users.at(i)->getUserName() == userName)
    {
      userPresent = true;
      index = i;
      // return users.at(i)->getUserPosts();
    }
  }
  if (userPresent == false)
  {
    throw std::invalid_argument("user does not exist");
  }
  else
  {
    return users.at(index)->getUserPosts();
  }
}

vector<Post *> Network::getPostsWithTag(string tagName)
{
  // TODO(student): return posts containing the given tag
  bool tagPresent;
  unsigned int index;
  tagPresent = false;
  if (tagName.empty())
  {
    throw std::invalid_argument("tag name is empty");
  }
  for (unsigned int i = 0; i < tags.size(); ++i)
  {
    if (tags.at(i)->getTagName() == tagName)
    {
      tagPresent = true;
      index = i;
    }
  }
  if (tagPresent == false)
  {
    throw std::invalid_argument("tag does not exist");
  }
  else
  {
    return tags.at(index)->getTagPosts();
  }
}

vector<string> Network::getMostPopularHashtag()
{
  // TODO(student): return the tag occurring in most posts
  unsigned int maxSize;
  unsigned int index;
  string maxName;
  vector<string> mostPopular;
  if (tags.size() < 1)
  {
    return mostPopular;
  }
  else
  {

    // iterate through each tag and check to see which tag returns the vector with the most posts
    maxSize = tags.at(0)->getTagPosts().size();
    index = 0;
    for (unsigned int i = 1; i < tags.size(); ++i)
    {
      if (tags.at(i)->getTagPosts().size() > maxSize)
      {
        maxSize = tags.at(i)->getTagPosts().size();
        maxName = tags.at(i)->getTagName();
        index = i;
      }
    }

    // add tag name of the most popular tag name
    // iterate through the tags again to see if there are any ties
    mostPopular.push_back(tags.at(index)->getTagName());
    for (unsigned int i = 0; i < tags.size(); ++i)
    {
      if (tags.at(i)->getTagPosts().size() == maxSize && tags.at(i)->getTagName() != maxName)
      {
        mostPopular.push_back(tags.at(i)->getTagName());
      }
    }

    return mostPopular;
  }
}

/**
 * Destructor
 * Do not change; already implemented.
 */
Network::~Network()
{
  for (unsigned int i = 0; i < users.size(); ++i)
  {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i)
  {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i)
  {
    delete posts.at(i);
  }
}

// vector<Post *> Network::getPostsTest()
// {
//   return posts;
// }
// int main()
// {
//   Network program;
//   program.addUser("eric");
//   program.addPost(6969, "eric", "L #rizz");
//   program.addUser("ethan");
//   program.addPost(1234, "ethan", "w #letsgo #aggie");
//   std::cout << program.getPostsTest()[0]->findTags().at(0) << std::endl;
//   std:: cout << program.getPostsTest()[1]->findTags().at(0) << " " << program.getPostsTest()[1]->findTags().at(1) << std::endl;
//   return 0;
// }
