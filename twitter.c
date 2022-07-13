#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//all users who signed up and all messages which sent
int usersNum=0,messagesNum=0;

//
const char* UserFormatOut = "username:%s password:%s id:%d editcheck:%d\n";
const char* MessageFormatOut = "%s,%d %d %d\n";
//const char* MessageFormatin = "%[^,], %d, %d, %d\n";

//all users
typedef struct{


       char username[100];
       char password[100];


}User;
User users[100];

//all messages
typedef struct{


       int sender_id;
       char message[100];


}Messages;
Messages messages[100];


void welcome(char user[100]){

    system("cls");
    printf("\n   Welcome %s", user);
    sleep(1);
    system("cls");
}
void error(){

    system("cls");
    printf("\n   Error try again");
    sleep(1);
    system("cls");
}

//login menu
int login(FILE* file_users,FILE* file_messages)
{
 /*   char usercheck[100],passcheck[100];
    printf("Username:");
    scanf("%s",usercheck);
    printf("Password:");
    scanf("%s",passcheck);

    int id=0;

    if(usersNum==0){

        strcpy(users[0].username, usercheck);
        strcpy(users[0].password, passcheck);
        usersNum++;
        //

            fprintf_s(file_users, UserFormatOut, users[0].username, users[0].password );
            fseek(file_users, 0, SEEK_CUR);

        //
        welcome(users[0].username);
        mainmenu(id,file_users);
    }
    else{
        for(id = 0; id <= usersNum; id++){


            if(id == usersNum){   //new username


                strcpy(users[id].username, usercheck);
                strcpy(users[id].password, passcheck);
                //

                  fprintf_s(file_users, UserFormatOut, users[id].username, users[id].password );
                  fseek(file_users, 0, SEEK_CUR);


                //
                usersNum++;


                welcome(users[id].username);
                mainmenu(id,file_users);

            }
            else if(strcmp(usercheck, users[id].username) == 0){  //compare entered usernames with stored ones

                    if(strcmp(passcheck, users[id].password) == 0){ //compare entered password with stored ones

                        welcome(users[id].username);
                        mainmenu(id,file_users);

                      }
                    else{     //entered password is incorrect

                       error();
                       login(file_users);

                     }


            }
        }
    }
    */
    char usercheck[100],passcheck[100];
    printf("Username:");
    scanf("%s",usercheck);
    printf("Password:");
    scanf("%s",passcheck);
    printf("1.Login\n");
    printf("2.Register\n");
    int actNum;
    printf("Enter the number of action:");
    scanf("%d",&actNum);
    if(actNum == 1){

        int id=0;
        for(id; id <= usersNum; id++){

            if(id == usersNum){

                printf("no username matches '%s'",usercheck);
                sleep(2);
                system("cls");
                login(file_users,file_messages);

            }else if(strcmp(usercheck, users[id].username) == 0){

                if(strcmp(passcheck, users[id].password) == 0){

                    welcome(users[id].username);
                    mainmenu(id,file_users,file_messages);

                }else{

                    printf("username & password dont match!");
                    sleep(2);
                    system("cls");
                    login(file_users,file_messages);

                }
            }
        }
    }else if(actNum == 2){

        int id=0;
        for(id; id <= usersNum; id++){

            if(id == usersNum){

                strcpy(users[id].username, usercheck);
                strcpy(users[id].password, passcheck);

                fprintf_s(file_users, UserFormatOut, users[id].username, users[id].password ,id , 0);
                fseek(file_users, 0, SEEK_CUR);
                usersNum++;


                system("cls");
                printf("\nRegister succesful %s,Welcome", users[id].username);
                sleep(2);
                system("cls");

                mainmenu(id,file_users,file_messages);

            }else if(strcmp(usercheck, users[id].username) == 0){

                printf("username '%s' already exists",users[id].username);
                sleep(2);
                system("cls");
                login(file_users,file_messages);


            }
        }
    }else{

        error();
        login(file_users,file_messages);

    }




}


int mainmenu(int id,FILE* file_users,FILE* file_messages){
    int menuNum;
    printf("1.send message\n");
    printf("2.edit message\n");
    printf("3.view all message\n");
    printf("4.change password\n");
    printf("5.exit\n");
    printf("Enter number of menu:");
    scanf("%d",&menuNum);

    switch(menuNum){

        case 1:
            system("cls");
            SendMessagesMenu(id,file_users,file_messages);

        case 2:
            system("cls");
            EditMessageMenu(id,file_users,file_messages);

        case 3:
            system("cls");
            ViewAllMessages(id,file_users,file_messages);

        case 4:
            system("cls");
            ChangePassMenu(id,file_users,file_messages);

        case 5:
            system("cls");
            login(file_users,file_messages);

        default:
            system("cls");
            error();
            mainmenu(id,file_users,file_messages);

    }
}


//changing passwords all
int ChangePassMenu(int id,FILE* file_users,FILE* file_messages){
    int menuNum;
    printf("1.change password\n");
    printf("2.exit\n");
    printf("Enter number of menu:");
    scanf("%d",&menuNum);

    switch(menuNum){

        case 1:
            system("cls");
            ChangePass(id,file_users,file_messages);

        case 2:
            system("cls");
            mainmenu(id,file_users,file_messages);

        default:
            system("cls");
            error();
            ChangePassMenu(id,file_users,file_messages);

    }
}
int ChangePass(int id,FILE* file_users,FILE* file_messages){

    int newpass[100];
    printf("Enter new password: ");
    scanf("%s",newpass);

    strcpy(users[id].password, newpass);  //change entered pass with the old one

    fprintf_s(file_users, UserFormatOut, users[id].username, users[id].password ,id , 1);
    fseek(file_users, 0, SEEK_CUR);

    system("cls");
    ChangePassMenu(id,file_users,file_messages);
}

//sending messages all
int SendMessagesMenu(int id,FILE* file_users,FILE* file_messages){
    int menuNum;
    printf("send message menu:\n");
    printf("1.send message\n");
    printf("2.exit\n");
    printf("Enter number of menu:");
    scanf("%d",&menuNum);
    switch(menuNum){

        case 1:
            system("cls");
            SendMessages(id,file_users,file_messages);

        case 2:
            system("cls");
            mainmenu(id,file_users,file_messages);

        default:
            system("cls");
            error();
            SendMessagesMenu(id,file_users,file_messages);
    }
}
int SendMessages(int id,FILE* file_users,FILE* file_messages){
    char newMess[100];
    printf("Enter message:");

    scanf("\n");
    scanf("%[^\n]%c",newMess);  // read new messages until enter clicked

    strcpy(messages[messagesNum].message,newMess);
    messages[messagesNum].sender_id = id;               //store the id of sender
                                         //amount of messages increased

    //
    fprintf_s(file_messages, MessageFormatOut,newMess,id ,messagesNum,0);
    fseek(file_messages, 0, SEEK_CUR);

    //
    messagesNum++;

    //
    fseek(file_users, 0, SEEK_SET);
    fprintf_s(file_users,"last tweet id:%d",messagesNum);
    fseek(file_users, 0, SEEK_END);

    //

    system("cls");
    SendMessagesMenu(id,file_users,file_messages);
}

//edit messages all
int EditMessageMenu(int id,FILE* file_users,FILE* file_messages){
    int menuNum;
    printf("edit message menu:\n");
    printf("1.edit message\n");
    printf("2.view your messages\n");
    printf("3.exit\n");
    printf("Enter number of menu:");
    scanf("%d",&menuNum);
    switch(menuNum){

        case 1:
            system("cls");
            EditMessage(id,file_users,file_messages);

        case 2:
            system("cls");
            YoursList(id,file_users,file_messages);


        case 3:
            system("cls");
            mainmenu(id,file_users,file_messages);

        default:
            system("cls");
            error();
            EditMessageMenu(id,file_users,file_messages);

    }
}
int EditMessage(int id,FILE* file_users,FILE* file_messages){
    int mess_id;
    printf("Enter message id:");
    scanf("%d",&mess_id);

    if(messages[mess_id-1].sender_id == id){

       system("cls");
       printf("Enter new message:");
       char newMess[100];

       scanf("\n");
       scanf("%[^\n]%c",newMess);

       strcpy(messages[mess_id-1].message,newMess);
       //
       fprintf_s(file_messages, MessageFormatOut, newMess, id,mess_id-1,1);
       fseek(file_messages, 0, SEEK_CUR);
       //
       system("cls");
       EditMessageMenu(id,file_users,file_messages);

    }
    else{
        error();
        EditMessageMenu(id,file_users,file_messages);
    }
}
int YoursList(int id,FILE* file_users,FILE* file_messages){
    int allme;
    for(allme = 0; allme < messagesNum; allme++){

        if(messages[allme].sender_id == id){

        printf("%d.%s\n",allme+1,messages[allme].message);

        }

    }
    printf("press Enter to return");
    getch();
    system("cls");
    EditMessageMenu(id,file_users,file_messages);
}

//all messages all
int ViewAllMessages(int id,FILE* file_users,FILE* file_messages){

    int allme;
    for(allme = 0; allme < messagesNum; allme++){

        printf("%d.%s\n",allme+1,messages[allme].message);


    }

    printf("press Enter to return");
    getch();
    system("cls");
    mainmenu(id,file_users,file_messages);
}


int main(){

    FILE* file_users;
    FILE* file_messages;


    fopen_s(&file_users, "userpass.txt","r+");

    if(file_users == NULL){

        fopen_s(&file_users, "userpass.txt","w+");

        fprintf_s(file_users,"last tweet id:%d\n",messagesNum);


    }else{


    char inputUser[200];
    fgets(inputUser, 200, file_users);
    fgets(inputUser, 200, file_users);

    int userid=0,editcheck=0;
    char olduser[200],oldpass[200];


    while(!feof(file_users)){
     //   User* uf = users + usersNum;
        sscanf(inputUser, "username:%s password:%s id:%d editcheck:%d\n", olduser, oldpass, &userid, &editcheck);

        strcpy(users[userid].username,olduser);
        strcpy(users[userid].password,oldpass);
        fgets(inputUser, 200, file_users);
        usersNum = usersNum + 1 - editcheck;

    }
    }




    fopen_s(&file_messages, "messages&id.txt","r+");

    if(file_messages == NULL){

        fopen_s(&file_messages, "messages&id.txt","w+");

    }
    char inputMess[200],oldMess[200];
    int senderId=0,editCheck=0,tweetId=0;
    fgets(inputMess, 200, file_messages);
    while(!feof(file_messages)){

        sscanf(inputMess, "%[^,],%d %d %d\n",oldMess,&senderId,&tweetId,&editCheck);
        strcpy(messages[tweetId].message,oldMess);
        messages[messagesNum].sender_id = senderId;
        messagesNum = messagesNum + 1 - editCheck;

        fgets(inputMess, 200, file_messages);
    }

    login(file_users,file_messages);
    fclose(file_users);
    fclose(file_messages);

    return 0;



}
