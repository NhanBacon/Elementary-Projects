#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void xor_encrypt(char *text, char key){
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] ^= key;
    }
}

int main(){ //Password Save & Encrypt
    char web[100];
    char pass[100];
    char key = '6';
    int choice = 0;

    while (choice != 3){
    printf("1. Add new password\n2. View saved password\n3. Exit\n");
    scanf("%d%*c", &choice);
    if (choice == 1){
        //Website Name Input
        printf("Enter Website: ");
        fgets(web, sizeof(web), stdin);
        web[strcspn(web, "\n")] = 0;

        
        //Password Input
        printf("Enter Password: ");
        fgets(pass, sizeof(pass), stdin);
        pass[strcspn(pass, "\n")] = 0;

        xor_encrypt(web, key);
        xor_encrypt(pass, key);

        //Declare FILE pointer
        FILE *passwordwrite;

        //Opens a .txt file for appending
        passwordwrite = fopen("password.txt", "a");
        
        //Check for opening error in file
        if (passwordwrite == NULL) {
            perror("Error opening file!");
            return 1;
        }

        fprintf(passwordwrite, "\n-----------------------------\n");
        fprintf(passwordwrite, "\nWebsite: %s\nPassword: %s\n", web, pass);
        fclose(passwordwrite);
        
        printf("\nSaved:\nWebsite: %s\nPassword: %s\n", web, pass);
    }

    if (choice == 2){ //Password Read & Decrypt
        char passwordString[500];
        
        FILE *passwordread;

        passwordread = fopen("password.txt", "r");
        
        if (passwordread == NULL)
        {
            perror("Error opening file!");
            return 1;
        }
        
        while (fgets(passwordString, sizeof(passwordString), passwordread) != NULL)
        {
            if (strncmp(passwordString, "Website: ", 8) == 0)
            {
                char encryptedWeb[256];
                strcpy(encryptedWeb, passwordString + 8);

                encryptedWeb[strcspn(encryptedWeb, "\n")] = 0;
                xor_encrypt(encryptedWeb, key);

                printf("Website: %s\n", encryptedWeb);
            }
            
            else if (strncmp(passwordString, "Password: ", 9) == 0)
            {
                char encryptedPass[256];
                strcpy(encryptedPass, passwordString + 9);
                
                encryptedPass[strcspn(encryptedPass, "\n")] = 0;
                xor_encrypt(encryptedPass,key);

                printf("Password: %s\n", encryptedPass);
            }
            
            else{
                printf("%s", passwordString);
            }
        }
        
        fclose(passwordread);
    }
    }

    printf("Session terminated!");

    return 0;
}