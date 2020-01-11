#ifndef CENGRAM_H
#define CENGRAM_H

#define MAX_USERNAME_LENGTH 20

typedef struct Date
{
    int day, month, year;
} Date;

typedef struct Post
{
    int postId;
    char *content;
    struct User *author;
} Post;

typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

typedef struct User
{
    int userId;
    char *username;
    Date *birthday;
    Node *followers;
    Node *posts;

    int numOfFollowers;
    int numOfPosts;
} User;

/*
    - Register new user with given parameters to "userProfiles".
    - Do required memory allocations. Make sure that you allocated new memory 
    for username and copy contents of newUsername inside of newly allocated memory
    region. Do not do direct assignment with "char* newUsername".
    - Return newly created User*.
*/
User *registerUser(int newUserId, char *newUsername, int birthdayDay, int birthdayMonth, int birthdayYear);

/*
    - Find users with userId1 and userId2 inside "userProfiles".
    - Create a new node for user2's followers and add user1 to followers of user2.
    - Just insert new follower node to the end.
*/
void followUser(int userId1, int userId2);

/*
    - Add new post with given parameters to "allPosts" and related owner user's "posts".
    - Do required memory allocations. Make sure that you allocated new memory 
    for newContent and copy newContent inside of newly allocated memory
    region. Do not do direct assignment with "char* newContent".
    - Make sure you insert new post to "allPosts" according to "postId". "allPosts" should
    be ordered by "postId" at the end. Keep in mind that you can preserve order in
    every add post operation, as long as you insert posts at the correct place.
    - While adding post to user's "posts", you don't need to have sorted "posts"
    collection at the end, you can append new post to the end of "posts". Check outputs
    for better understanding.
    - Return newly created Post*.
*/
Post *createPost(int postId, int ownerUserId, char *newContent);

/*
    - If you can come this far, you can do this too.
    - Before you remove User from "userProfiles", you need to do the following:
        - Remove posts of user from "allPosts" and "posts" of User
        - Remove follower node from other users, in case deleted user follows them.
        - Remove follower nodes from deleted user.
        - Remove User object
        - Remove user node from "userProfiles".
    
    - While removing, free pointers in members first, then move to the containers.
    That is the best practice for freeing previously allocated memory.
*/
void removeUserAccount(int deletedUserId);

#endif
