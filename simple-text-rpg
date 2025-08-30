#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int roll_dice(int sides){
    return rand() % sides + 1;
}

void loading(){
    printf("Loading"); //
    for (int cycle = 0; cycle < 3; cycle++)
    {
        int dots = 0;
        
        for (int i = 0; i < 3; i++)
        {
            printf(".");
            fflush(stdout);
            usleep(125000);
        }
        
        if (cycle != 2)
        {
            printf("\b\b\b   \b\b\b");
            fflush(stdout);
        } else{
            printf("\r            \r");
            fflush(stdout);
            printf("Loading complete!\n");   
        }
        usleep(125000);
    }
}

void clear_terminal(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void display_diff(int multiplier, char diff[32]){
    if (multiplier == 1)
    {
        diff = "Easy";
        printf("Chosen difficulty: %s\n", diff);
    } else if (multiplier == 2)
    {
        diff = "Medium";
        printf("Chosen difficulty: %s\n", diff);
    } else if(multiplier >= 3)
    {
        diff = "Hard";
        printf("Chosen difficulty: ");
        for (int i = 0; i < (multiplier - 3); i++)
        {
            printf("Very ");
        }
        
        printf("%s\n", diff);
    }
}

typedef struct
{
    int id;
    char name[50];
    int hp;
    int atk;
} Enemy;

Enemy enemy(int id, int hp, int atk, int weight){
    Enemy e;
    e.id = id;
    e.hp = hp + (hp * (weight - 1)) / 4;
    e.atk = atk + (atk * (weight - 1)) / 8;
    return e; 
}

typedef struct
{
    char name[100];
    int hp;
    int atk;
} Player;

int check_player_hp(Player player, char current_enemy[], int current_enemy_hp, int current_enemy_atk){
    if (player.hp < 0) {
        clear_terminal();
        printf("Player: %s (DEFEATED!)    |    Enemy: %s (Hp: %d Atk: %d)\n", 
               player.name, current_enemy, current_enemy_hp, current_enemy_atk);
        printf("You have been defeated.\n");
        return 1; // defeated
    }
    return 0; // not defeated
}

#define MAX_ENEMIES 10

int main(){
    char current_enemy[32], diff[32];
    int  current_enemy_atk, current_enemy_hp, multiplier = 0, choice = 0, rng_dodge = 0, rng_retreat = 0;

    srand(time(NULL));
    
    Player player;

    printf("Enter player name: ");
    fgets(player.name, sizeof(player.name), stdin);
    player.name[strcspn(player.name, "\n")] = 0;

    player.hp = 100; //PLAYER STATS
    player.atk = 15;

    while (multiplier < 1 || multiplier > 3)
    {        
        printf("Choose difficulty:\n1. Easy\n2. Medium\n3. Hard\n");

        if (scanf("%d", &multiplier) == 1)
        {
            break;
        }else printf("Invalid Input!\n");
    }
    
    
    clear_terminal();

    display_diff(multiplier, diff);

    loading(); //Artificial Loading Sequence For Awesome Anticipation Points!

    //ID, HP, ATK, WEIGHT of Enemies
    Enemy Slime = enemy(1, 10, 1, multiplier); // SLIME
    strcpy(Slime.name, "Slime");                                                
    Enemy Goblin = enemy(2, 50, 5, multiplier); // GOBLIN
    strcpy(Goblin.name, "Goblin");
    Enemy Giant = enemy(3, 150, 10, multiplier); // GIANT
    strcpy(Giant.name, "Giant");
    Enemy Dragon = enemy(4, 500, 30, multiplier); // DRAGON
    strcpy(Dragon.name, "Dragon");

    Enemy enemies_list[MAX_ENEMIES] = {Slime, Goblin, Giant, Dragon};
    
    int enemy_id = rand() % 4 + 1;

    for (int i = 0; i < 4; i++)
    {
        if (enemies_list[i].id == enemy_id)
        {
            strcpy(current_enemy, enemies_list[i].name);
            current_enemy_atk = enemies_list[i].atk;
            current_enemy_hp = enemies_list[i].hp;
        }
    }

    while (1)
    {
        usleep(750000);
        printf("Player: %s (Hp: %d Atk: %d)    |    Enemy: %s (Hp: %d Atk: %d)\n", 
            player.name, player.hp, player.atk, current_enemy, current_enemy_hp, current_enemy_atk);
        
        usleep(750000);
        printf("\nWhat should you do?\n1. Attack\n2. Dodge\n3. Retreat\n");
        scanf("%d", &choice);

        if (choice == 1)
        {
            clear_terminal();
            current_enemy_hp = current_enemy_hp - player.atk;
            usleep(250000);
            printf("You dealt %d dmg\n", player.atk);
            if (current_enemy_hp < 0)
            {
                clear_terminal();
                printf("Player: %s (Hp: %d Atk: %d)    |    Enemy: %s (DEFEATED!)\n\n", 
            player.name, player.hp, player.atk, current_enemy);
                
                printf("You defeated a %s\n!", current_enemy);
                break;
            }
            
            player.hp = player.hp - current_enemy_atk;
            usleep(250000);
            printf("You took %d dmg\n", current_enemy_atk);
            usleep(250000);
            
            if(check_player_hp(player, current_enemy, current_enemy_hp, current_enemy_atk)){
                break;
            }

            
            
        }
        
        else if (choice == 2)
        {
            rng_dodge = roll_dice(20);
            if (rng_dodge > 10)
            {
                usleep(750000);
                printf("You evaded the enemy's attack and gained %d HP.\n", ((rng_dodge - 8) * rng_dodge / 10));
                usleep(750000);
                player.hp += ((rng_dodge - 8) * rng_dodge / 10);
            }
            else
            {
                usleep(750000);
                printf("Failed to dodge!\n");
                
                player.hp = player.hp - current_enemy_atk;
                usleep(750000);
                printf("You took %d dmg.\n", current_enemy_atk);
                
                if(check_player_hp(player, current_enemy, current_enemy_hp, current_enemy_atk))
                {
                break;
                }
            }
        }

        else if(choice == 3)
        {
            rng_retreat = roll_dice(20);
            if (rng_retreat > 8)
            {
                usleep(750000);
                printf("Successfully retreated!\n");
                break;
            } 

            else if (rng_retreat < 8)
            {
                printf("You failed to retreat.\n");
                player.hp = player.hp - current_enemy_atk;
                usleep(500000);
                printf("You took %d dmg.\n", current_enemy_atk);
            } 
                        
            if(check_player_hp(player, current_enemy, current_enemy_hp, current_enemy_atk))
            {
            break;
            }
        }
        
        else printf("Invalid Input\n");
    }

    return 0;
}
