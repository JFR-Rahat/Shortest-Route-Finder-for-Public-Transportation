#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
#define      Infinity     1000000

bool Open[2];
bool Home_Locked = false;
bool Exit_Locked = true;
char district[64][20];
double cost[64][64][2];
char vehicle_name[2][10] = {"Car", "Train"};
int best_match;

void House1();

void House2();

void Road();

void move_cursor_space(int i);

void move_cursor_space_tab(int n);

void Logo_page();

void Home_Page();

void Set_Up();

bool district_assign();

bool cost_assign();

void vehicle_cost(FILE *vehicle, int k);

void first_view();

bool district_verified(char location[]);

void show_suggestion(char location[]);

void dijkstra(char current_location[], char destination[]);

void print_shortest_path(int source, int target, int previous_district[], int previous_district_vehicle[]);

void balance_distance(char string[]);

bool Quit_attempt(char string[]);

bool Quit();

bool Back_to_Home();

bool Enter_press(char ch);


int main()
{
    Logo_page();

    char current_location[100], destination[100];
    bool fresh_start = true, fresh_destination = true;

    while(1)
    {
        if(Home_Locked == false)
        {
            Home_Locked = true;
            system("color f0");
            Home_Page();
            Set_Up();
            fresh_start = true, fresh_destination = true;
            printf("\n\n");
        }

        system("color f4");
        first_view();

        if(fresh_start == true)
        {
            gets(current_location);

            if(Quit_attempt(current_location) == true)
            {
                if(Home_Locked == false)
                {
                    continue;
                }
                else if(Exit_Locked == false)
                {
                    break;
                }
                else
                {
                    system("cls");
                    printf("\n\n");
                    continue;
                }
            }
            else
            {
                if(district_verified(current_location) == false)
                {
                    system("cls");
                    show_suggestion(current_location);
                    continue;
                }
                else
                {
                    system("cls");
                    fresh_start = false;
                    printf("\n\n");
                    continue;
                }
            }
        }
        else
        {
            printf("%s\n", current_location);
            fresh_start = true;
        }


        printf("\nEnter the destination: ");

        if(fresh_destination == true)
        {
            gets(destination);

            if(Quit_attempt(destination) == true)
            {
                if(Home_Locked == false)
                {
                    continue;
                }
                else if(Exit_Locked == false)
                {
                    break;
                }
                else
                {
                    fresh_start = false;
                    printf("\n\n");
                    continue;
                }
            }


            else if(district_verified(destination) == false)
            {
                system("cls");
                show_suggestion(destination);
                fresh_start = false;
                continue;
            }
            else
            {
                system("cls");
                fresh_start = false;
                fresh_destination = false;
                printf("\n\n");
                continue;
            }
        }
        else
        {
            printf("%s\n", destination);
            fresh_start = true;
            fresh_destination = true;
        }

        dijkstra(current_location, destination);

        printf("Press Enter key to continue...\n");

        char ch;
        ch = getchar();
        if(Enter_press(ch) == true)
        {

        }
        else
        {
            if(Home_Locked == false)
            {
                continue;
            }
            else if(Exit_Locked == false)
            {
                break;
            }
            else
            {
                fresh_start = false;
                fresh_destination = false;
                printf("\n\n");
                continue;
            }
        }

        system("cls");
        printf("\n\n");
    }
    return 0;
}

void Logo_page()
{
    system("color 4f");
    system("cls");
    printf("\n\n\n");
    move_cursor_space(60);
    printf("Shortest Route Finder for Public Transportation\n\n\n");
    Sleep(1000);
    House1();
    printf("\n");
    Road();
    House2();
    system("cls");
}

void House1()
{

    printf("     /\\\n");
    printf("    /  \\\n");
    printf("   /    \\\n");
    printf("  /      \\\n");
    printf(" /        \\\n");
    printf("/_ _ _ _ _ \\\n");
    printf("|          |\n");
    printf("|    __    |\n");
    printf("|   |  |   |\n");
    printf("|_ _|__|_ _|\n");
}

void House2()
{
    move_cursor_space(141);
    printf("     /\\\n");
    move_cursor_space(141);
    printf("    /  \\\n");
    move_cursor_space(141);
    printf("   /    \\\n");
    move_cursor_space(141);
    printf("  /      \\\n");
    move_cursor_space(141);
    printf(" /        \\\n");
    move_cursor_space(141);
    printf("/_ _ _ _ _ \\\n");
    move_cursor_space(141);
    printf("|          |\n");
    move_cursor_space(141);
    printf("|    __    |\n");
    move_cursor_space(141);
    printf("|   |  |   |\n");
    move_cursor_space(141);
    printf("|_ _|__|_ _|\n");
    Sleep(250);
}

void Road()
{

    for(int i=0; i<6; i++)
    {
        Sleep(50);
        printf("   | . |");
        if(i < 5)
        {
            Sleep(50);
            printf("\n");
        }
        else
        {
            Sleep(25);
            printf("_ ");
        }
    }

    for(int i=0; i<45; i++)
    {
        Sleep(25);
        printf("__ ");
        if(i == 44)
        {
            Sleep(25);
            printf("__\n   ");
            printf("| .  ");

        }
    }

    for(int i=0; i<70; i++)
    {
        Sleep(25);
        printf(". ");
        if(i == 69)
        {
            Sleep(25);
            printf("|\n   ");
            printf("|__ ");

        }
    }
    for(int i=0; i<46; i++)
    {
        Sleep(25);
        printf("__ ");
        if(i == 45)
        {
            Sleep(25);
            printf(" . |\n   ");
        }
    }

    move_cursor_space(141);
    for(int i=0; i<3; i++)
    {
        Sleep(50);
        printf("| . |");
        printf("\n");
        if(i < 2)
            move_cursor_space(144);
    }
}

void move_cursor_space(int i)
{
    for(int n=0; n<i; n++)
    {
        printf(" ");
    }
}

void Home_Page()
{
    char Key[10000];
    printf("\n\n\n");
    printf("Home");
    move_cursor_space_tab(9);
    printf("How would you like to travel?");
    move_cursor_space_tab(8);
    printf("0. Exit\n");
    move_cursor_space_tab(9);
    printf("Enter 1 or 2 or 3 to proceed.\n\n");
    move_cursor_space_tab(9);
    printf("1. Car\n");
    move_cursor_space_tab(9);
    printf("2. Train\n");
    move_cursor_space_tab(9);
    printf("3. Best Route\n\n");
    move_cursor_space_tab(9);
    gets(Key);

    if(strcmp(Key, "1") == 0)
    {
        Open[0] = true;
        Open[1] = false;
        system("cls");
    }
    else if(strcmp(Key, "2") == 0)
    {
        Open[1] = true;
        Open[0] = false;
        system("cls");
    }
    else if(strcmp(Key, "3") == 0)
    {
        Open[0] = true;
        Open[1] = true;
        system("cls");
    }
    else if(strcmp(Key, "0") == 0)
    {
        system("color f4");
        if(Quit() == true)
        {
            exit(0);
        }
        else
        {
            system("cls");
            system("color f0");
            Home_Page();
        }
    }
    else
    {
        system("cls");
        system("color 4f");
        Home_Page();
    }
}

void Set_Up()
{
    if(district_assign() == false)
    {
        exit(101);
    }
    if(cost_assign() == false)
    {
        exit(102);
    }

}

void first_view()
{
    printf("\n\n");
    printf("1. Home");
    move_cursor_space_tab(10);
    if(Open[0] == true && Open[1] == false)
    {
        printf("Car");
        move_cursor_space_tab(10);
    }
    else if(Open[1] == true && Open[0] == false)
    {
        printf("Train");
        move_cursor_space_tab(10);
    }
    else if(Open[0] == true && Open[1] == true)
    {
        printf("Best Route");
        move_cursor_space_tab(9);
    }
    printf("0. Exit");
    printf("\n\n");
    printf("Enter the current location: ");
}

bool district_assign()
{
    FILE *name;
    name = fopen("District_name.txt", "r");
    if(name == NULL)
    {
        printf("Error: District_name is empty\n");
        return false;;
    }
    int n = 0;
    while(feof(name) == 0)
    {
        fscanf(name, "%s", district[n]);
        n++;
    }
    return true;
}

void vehicle_cost(FILE *vehicle, int k)
{
    int decimal_checker;
    int i = 0, j = 0;
    while((decimal_checker = fscanf(vehicle, "%lf", &cost[i][j][k])) != EOF)
    {
        if(decimal_checker == 1)
        {
            j++;
            if(j == 64)
            {
                j = 0;
                i++;
            }
        }
        else
        {
            fgetc(vehicle);
        }
    }
}

bool cost_assign()
{
    FILE *car_info, *train_info;
    int k = 0;
    if(Open[k] == true)
    {
        car_info = fopen("Car_info.txt", "r");
        if(car_info == NULL)
        {
            printf("Error: Car_info is empty\n");
            return false;
        }
        vehicle_cost(car_info, k);
        fclose(car_info);
    }
    if(Open[k+1] == true)
    {
        train_info = fopen("Train_info.txt", "r");
        if(train_info == NULL)
        {
            printf("Error: Train_info is empty\n");
            return false;
        }
        vehicle_cost(train_info, k+1);
        fclose(train_info);
    }
    return true;
}

bool district_verified(char location[])
{
    bool matched = false;
    char upper_location[100];
    int i = 0, point[64] = {0};

    strcpy(upper_location, location);


    if(strcmp(strupr(upper_location), strupr(district[i])) == 0)
    {
        matched = true;
    }


    for(int j=0; upper_location[j] != '\0' && district[i][j] != '\0'; j++)
    {
        if(upper_location[j] == district[i][j])
        {
            point[i]++;
        }
    }

    best_match = i;

    for(i = 1; i<64; i++)
    {
        if(strcmp(strupr(upper_location), strupr(district[i])) == 0)
        {
            matched = true;
        }

        for(int j=0; upper_location[j] != '\0' && district[i][j] != '\0'; j++)
        {
            if(upper_location[j] == district[i][j])
            {
                point[i]++;
            }
        }


        if(point[i] > point[best_match])
        {
            best_match = i;
        }
    }
    if(matched == false)
    {
        return false;
    }
    else
        return true;
}

void show_suggestion(char location[])
{
    printf("No such district as %s.\n", location);
    printf("Type instead: \n");
    printf("%s", district[best_match]);
}

void print_shortest_path(int source, int target, int previous_district[], int previous_district_vehicle[])
{
    int rev_path[128], path[128], rev_vehicle_path[128], vehicle_path[128], count = 0, x = 0, y;
    int end = target;

    while(previous_district[end] != -1)
    {
        rev_path[count] = end;
        rev_vehicle_path[count] = previous_district_vehicle[end];
        end = previous_district[end];
        count++;
    }
    rev_path[count] = source;
    printf("\n\n");
    printf("The shortest path is: ");
    int count2 = count;

    while(count >= 0)
    {
        path[x] = rev_path[count];
        y = count - 1;
        vehicle_path[x] = rev_vehicle_path[y];
        printf("%s", district[path[x]]);
        if(count > 0)
            printf("-(%.2lfkm on %s)-", cost[path[x]][rev_path[y]][vehicle_path[x]], vehicle_name[vehicle_path[x]]);
        x++;
        count--;
    }
    printf("\n\n");
    x = 0;
    while(count2 > 0)
    {
        path[x] = rev_path[count2];
        y = count2 - 1;
        vehicle_path[x] = rev_vehicle_path[y];
        {
            move_cursor_space_tab(6);
            printf("%s", district[path[x]]);
            balance_distance(district[path[x]]);
            printf("-\t");
            printf("%s", district[path[x+1]]);
            balance_distance(district[path[x+1]]);
            printf("-\t");
            printf("%s(%.2lfkm)\n", vehicle_name[vehicle_path[x]], cost[path[x]][rev_path[y]][vehicle_path[x]]);
        }
        x++;
        count2--;
    }
}
void dijkstra(char current_location[], char destination[])
{
    int source, target, start, vehicle;
    bool current[64] = {false};
    double shortest_distance[64], distance;
    char source_name[100], target_name[100];
    double minimum;
    int next_location, next_vehicle, previous_district[128], previous_district_vehicle[128];
    int i, j, k;

    for(i=0; i<64; i++)
    {
        for(k=0; k<2; k++)
            shortest_distance[i] = Infinity;
    }

    strcpy(source_name, current_location);
    for(i = 0; i<64; i++)
    {
        if(strcmp(strupr(source_name), strupr(district[i])) == 0)
        {
            source = i;
        }
    }

    strcpy(target_name, destination);
    for(i = 0; i<64; i++)
    {
        if(strcmp(strupr(target_name), strupr(district[i])) == 0)
        {
            target = i;
        }
    }
    start = source;
    vehicle = 0;
    previous_district[start] = -1;
    previous_district_vehicle[start] = -1;
    shortest_distance[start] = 0;
    current[start] = true;

    while(current[target] == false)
    {
        minimum = Infinity;
        next_location = 0;
        next_vehicle = 0;
        for(i=0; i<64; i++)
        {
            for(k=0; k<2; k++)
            {
                if(Open[k] == true)
                {
                    distance = shortest_distance[start] + cost[start][i][k];

                    if(distance < shortest_distance[i] && current[i] == 0)
                    {
                        shortest_distance[i] = distance;
                        previous_district[i] = start;
                        previous_district_vehicle[i] = k;
                    }
                    if(minimum > shortest_distance[i]  && current[i] == 0)
                    {
                        minimum = shortest_distance[i];
                        next_location = i;
                        next_vehicle = k;
                    }
                }
            }
        }

        start = next_location;
        vehicle = next_vehicle;
        if(current[start] == false)
        {
            current[start] = true;
        }
        else
        {
            shortest_distance[target] == Infinity;
            break;
        }
    }
    if(shortest_distance[target] == 0)
    {
        system("cls");
        move_cursor_space_tab(10);
        printf("\n\n\n\n");
        printf("1. Home");
        move_cursor_space_tab(10);
        if(Open[0] == true && Open[1] == false)
        {
            printf("Car");
            move_cursor_space_tab(10);
        }
        else if(Open[1] == true && Open[0] == false)
        {
            printf("Train");
            move_cursor_space_tab(10);
        }
        else if(Open[0] == true && Open[1] == true)
        {
            printf("Best Route");
            move_cursor_space_tab(9);
        }
        printf("0. Exit\n\n\n\n");
        move_cursor_space_tab(7);
        printf("Your current location(%s) & destination(%s) are same\n\n", source_name, target_name);
    }
    else if(shortest_distance[target] >= 1000000)
    {
        system("cls");
        move_cursor_space_tab(10);
        printf("\n\n\n\n");
        printf("1. Home");
        move_cursor_space_tab(10);
        if(Open[0] == true && Open[1] == false)
        {
            printf("Car");
            move_cursor_space_tab(10);
        }
        else if(Open[1] == true && Open[0] == false)
        {
            printf("Train");
            move_cursor_space_tab(10);
        }
        else if(Open[0] == true && Open[1] == true)
        {
            printf("Best Route");
            move_cursor_space_tab(9);
        }
        printf("0. Exit\n\n\n\n");
        move_cursor_space_tab(10);
        printf("Sorry...\n");
        move_cursor_space_tab(7);
        printf("We couldn't find any route for you from %s to %s\n\n", source_name, target_name);
    }
    else
    {
        print_shortest_path(source, target, previous_district, previous_district_vehicle);
        printf("\n");
        move_cursor_space_tab(8);
        printf("And the distance is: %.2fkm\n\n\n\n", shortest_distance[target]);
    }
}

void move_cursor_space_tab(int n)
{
    for(int i=0; i<n; i++)
    {
        printf("\t");
    }

}

void balance_distance(char string[])
{
    for(int i=0; i<15-strlen(string); i++)
        printf(" ");
}

bool Quit_attempt(char string[])
{
    if(strcmp(string, "0") == 0)
    {
        if(Quit() == false)
        {
            system("cls");
            return true;
        }
        else
        {
            Exit_Locked = false;
            return true;
        }
    }
    else if(strcmp(string, "1") == 0)
    {
        if(Back_to_Home() == false)
        {
            system("cls");
            return true;
        }
        else
        {
            Home_Locked = false;
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool Quit()
{
    char assurance[10000];
    bool quit = true;

    move_cursor_space_tab(9);
    printf("Really want to quit?\n");
    move_cursor_space_tab(9);
    printf("Enter 1 or 0 to proceed.\n\n");
    move_cursor_space_tab(9);
    printf("1. Yes\n");
    move_cursor_space_tab(9);
    printf("0. No\n\n");
    move_cursor_space_tab(9);

    scanf("%s", assurance);
    getchar();
    if(strcmp(assurance, "1") == 0)
    {
        system("cls");
        quit = true;
    }
    else if(strcmp(assurance, "0") == 0)
    {
        system("cls");
        quit = false;
    }
    else
    {
        system("color 4f");
        do
        {
            move_cursor_space_tab(9);
            scanf("%s", assurance);
            getchar();
            if(strcmp(assurance, "1") == 0)
            {
                quit = true;
            }
            else if (strcmp(assurance, "0") == 0)
            {
                system("cls");
                quit = false;
            }
        }

        while((strcmp(assurance, "1") != 0) && strcasecmp(assurance, "0") != 0);
    }
    return quit;
}

bool Enter_press(char ch)
{
    bool enter;
    char string[1000];

    while(ch != '\n' && ch != '1' && ch != '0')
    {
        system("color 4f");
        gets(string);
        ch = getchar();
    }

    if(ch == '\n')
    {
        enter = true;
    }

    else
    {
        string[0] = ch;
        string[1] = '\0';
        Quit_attempt(string);
        enter = false;
    }

    return enter;
}

bool Back_to_Home()
{
    char assurance[10000];
    bool back = true;

    move_cursor_space_tab(9);
    printf("Really want to go to Home?\n");
    move_cursor_space_tab(9);
    printf("Enter 1 or 0 to proceed.\n\n");
    move_cursor_space_tab(9);
    printf("1. Yes\n");
    move_cursor_space_tab(9);
    printf("0. No\n\n");
    move_cursor_space_tab(9);

    scanf("%s", assurance);
    getchar();
    if(strcmp(assurance, "1") == 0)
    {
        system("cls");
        back = true;
    }
    else if(strcmp(assurance, "0") == 0)
    {
        system("cls");
        back = false;
    }
    else
    {
        system("color 4f");
        do
        {
            move_cursor_space_tab(9);
            scanf("%s", assurance);
            getchar();
            if(strcmp(assurance, "1") == 0)
            {
                back = true;
            }
            else if (strcmp(assurance, "0") == 0)
            {
                system("cls");
                back = false;
            }
        }
        while((strcmp(assurance, "1") != 0) && strcasecmp(assurance, "0") != 0);
    }

    return back;
}
