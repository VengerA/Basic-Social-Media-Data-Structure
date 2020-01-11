#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cengram.h"

/* GLOBALS */

Node *userProfiles = NULL;
int totalUserCount = 0;
Node *allPosts = NULL;
int totalPostCount = 0;

/* GLOBALS END */

/* PRINT FUNCTIONS BEGIN */

void printDate(Date *date)
{
    printf("%d.%d.%d\n", date->day, date->month, date->year);
}

void printPost(Post *post)
{
    printf("\tPostId: %d\n\t\tAuthor: %s\n\t\tContent: %s\n", post->postId, post->author->username, post->content);
}

void printUser(User *user, int showUserPosts)
{
    printf("--------------------\n");
    printf("UserId: %d\tUsername: %s", user->userId, user->username);
    printf("\tBirthday: ");
    printDate(user->birthday);
    printf("Followers: %d\tPosts: %d\n", user->numOfFollowers, user->numOfPosts);

    if (user->numOfFollowers > 0)
    {
        Node *tempNode = user->followers;
        printf("Followers:\n");

        while (tempNode != NULL)
        {
            User *tempUser = (User *)tempNode->data;
            printf("\tUsername: %s\n", tempUser->username);
            tempNode = tempNode->next;
        }
    }

    if (showUserPosts && user->numOfPosts > 0)
    {
        Node *tempNode = user->posts;
        printf("Posts:\n");

        while (tempNode != NULL)
        {
            Post *tempPost = (Post *)tempNode->data;
            printPost(tempPost);
            tempNode = tempNode->next;
        }
    }
}

void printUserProfiles(int showUserPosts)
{
    Node *tempNode = userProfiles;

    printf("##### USER COLLECTION #####\n");
    printf("Number of users: %d\n", totalUserCount);

    while (tempNode != NULL)
    {
        User *tempUser = tempNode->data;

        printUser(tempUser, showUserPosts);

        tempNode = tempNode->next;
    }
}

void printAllPosts()
{
    Node *tempNode = allPosts;

    printf("##### ALL POSTS #####\n");
    printf("Number of posts: %d\n", totalPostCount);

    while (tempNode != NULL)
    {
        Post *tempPost = (Post *)tempNode->data;

        printPost(tempPost);

        tempNode = tempNode->next;
    }
}

/* PRINT FUNCTIONS END */

int main()
{
    char *tempPtr1 = (char *)malloc(MAX_USERNAME_LENGTH * sizeof(char));
    int day, month, year, id1, id2;
    int numOfUsers, numOfFollows, numOfPosts, numOfDeleted;
    int i = 0, j = 0;

    scanf("%d ", &numOfUsers);

    for (i = 0; i < numOfUsers; i++)
    {
        char *username;
        scanf("%d", &id1);
        scanf(" %s ", tempPtr1);
        scanf("%d %d %d", &day, &month, &year);

        /* copy string */
        username = (char *)malloc(sizeof(char) * strlen(tempPtr1));
        strcpy(username, tempPtr1);

        registerUser(id1, username, day, month, year);
    }

    scanf("%d ", &numOfFollows);

    for (i = 0; i < numOfFollows; i++)
    {
        scanf("%d %d", &id1, &id2);

        followUser(id1, id2);
    }

    scanf("%d ", &numOfPosts);

    for (i = 0; i < numOfPosts; i++)
    {
        int postId, authorId, charCount;
        char newChar;
        char *content;

        scanf("%d %d %d ", &postId, &authorId, &charCount);

        content = (char *)malloc((charCount + 1) * sizeof(char));
        for (j = 0; j < charCount; j++)
        {
            scanf("%c", &newChar);
            content[j] = newChar;
        }

        content[j] = '\0';
        createPost(postId, authorId, content);
    }

    scanf("%d ", &numOfDeleted); 


    for (i = 0; i < numOfDeleted; i++)
    {
        int deletedUserId;
        scanf("%d ", &deletedUserId);
        removeUserAccount(deletedUserId);
    }

    printUserProfiles(1);
    printAllPosts();

    return 0;
}
