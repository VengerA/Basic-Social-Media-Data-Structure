#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cengram.h"

extern Node *userProfiles;
extern int totalUserCount;
extern Node *allPosts;
extern int totalPostCount;

Node *makeNode(){
    Node *to_allocate = (Node*) malloc(sizeof(Node));
    return to_allocate;
}

void appendUser(Node **head, Node *node){
    Node* current = *head;
    while(current->next){
        current = current->next;
    }
    current->next = node;
}

User *findUser(int userId){
    Node *current = userProfiles;
    while(current){
        User *mamen = current->data;

        if(mamen->userId == userId){
            return mamen;
            
        }
        current = current->next;
    }
    return NULL;
}


User *makeUser(int userId, char *userName, int bd, int bm, int by){
    User *newUser = (User*) malloc(sizeof(User));
    Date* birthDate = (Date*) malloc(sizeof(Date));
    int length = strlen(userName) + 1;

    birthDate->day = bd;
    birthDate->month = bm;
    birthDate->year = by;

    newUser->userId = userId;

    if(length <= MAX_USERNAME_LENGTH){
        newUser->username = (char*) malloc(length*sizeof(char));
    }

    strcpy(newUser->username, userName); 
    newUser->birthday = birthDate;

    return newUser;
}

Post *createPost2(int postId, char *content, struct User* author){
    Post *newPost = (Post*) malloc(sizeof(Post));
    int length = strlen(content)+1;

    newPost->postId = postId;
    newPost->author = author;  

    newPost->content = (char*)malloc(sizeof(char)*length);

    strcpy(newPost->content, content);
    return newPost;
}


User *registerUser(int newUserId, char *newUsername, int birthdayDay, int birthdayMonth, int birthdayYear)
{
    /* TODO: Implement this function */
    
    Node *temp = makeNode();
    User * newUser = makeUser(newUserId, newUsername, birthdayDay, birthdayMonth, birthdayYear);
    temp->data = newUser;

    if(!userProfiles){
        userProfiles = temp;
    }
    else {
        appendUser(&userProfiles, temp);
    }

    totalUserCount++;
    return newUser;
}

void followUser(int userId1, int userId2)
{
    /* TODO: Implement this function */
    User *mainUser = NULL;
    User *follower = NULL;
    Node *followerNode = makeNode();

    follower = findUser(userId1);
    mainUser = findUser(userId2);

    followerNode->data = follower;

    if(!mainUser->followers){
         mainUser->followers = followerNode;
         mainUser->numOfFollowers++;
    }
    else {
        appendUser(&(mainUser->followers), followerNode);
        mainUser->numOfFollowers++;
    }
}

void insertInOrder(Node **head ,Node *newPost){
    Node *current = *head;
    Node *prev = current;
    Post *Poster = newPost->data;
    while(current){
        Post *temp = current->data;

        if(Poster->postId < temp->postId){
            break;
        }
        prev = current;
        current = current->next;
    }

    if(prev == current){
        newPost->next = current;
        *head = newPost;
    }
    else {
        prev->next = newPost;
        newPost->next = current;
    }
}

Post *createPost(int postId, int ownerUserId, char *newContent)
{
    /* TODO: Implement this function */
    User *author =  NULL;
    Post *newPost = NULL;
    Node *forUser = NULL;
    Node *forAllPosts  = NULL;
    forUser = makeNode();
    forAllPosts = makeNode();
    author = findUser(ownerUserId);

    newPost = createPost2(postId , newContent, author);
    forUser->data = newPost;
    forAllPosts->data = newPost;

    if(!author->posts){
        author->posts = forUser;
        author->numOfPosts++;
    }
    else{
        appendUser(&author->posts, forUser);
        author->numOfPosts++;
    }

    if(!allPosts){
        allPosts = forAllPosts;
        totalPostCount++;
    }
    else{
        insertInOrder(&allPosts, forAllPosts);
        totalPostCount++;
    }
    return NULL;
}

void removeNode(Node **head, int index){
    Node *current = *head;
    if(current){
        if(index == 0){
            *head = current->next;
            free(current);
        }
        else{
            int i;
            Node *prev = current;
            for(i=0;i<index;i++){
                prev = current;
                current = current->next;
            }
            prev->next = current->next;
            free(current);
        }
    }
}

void removeUserAccount(int deletedUserId)
{
    /* TODO: Implement this function */
    int i = 0;
    Node *current = userProfiles;
    while(current){
        User *mamen = current->data;
        if(mamen->userId == deletedUserId){
            removeNode(&userProfiles, i);
            totalUserCount--;
            break;
        }
        i++;
        current = current->next;
    }
    i = 0;
    current = allPosts;
    while(current){
        Post *post = current->data;
        if(post->author->userId == deletedUserId){
            removeNode(&allPosts, i);
            totalPostCount--;
            i--;

        }
        current = current->next;
        i++;
    }
    current = userProfiles;
    while(current){
        User *user = current->data;
        Node *current2 = user->followers;
        i = 0;
        while(current2){
            User *mamen = current2->data;
            if(mamen->userId == deletedUserId){
                removeNode(&user->followers, i);
                user->numOfFollowers--;
                break;
            }
            current2 = current2->next;
            i++;
        }
        current = current->next;
    }
}
