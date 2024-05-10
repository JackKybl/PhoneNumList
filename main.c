#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Person
{
    char lastName[32];
    char firstName[32];
    char tellCode[16];
    char tell[16];
} Person;

Person *new_Person(char *lastName, char *firstName, char *tellCode, char *tell)
{
    Person *p = malloc(sizeof(Person));

    strcpy(p->lastName, lastName);
    strcpy(p->firstName, firstName);
    strcpy(p->tellCode, tellCode);
    strcpy(p->tell, tell);
    return p;
}

char *person_toString(Person *p)
{
    char *result = malloc(100 * sizeof(char));

    if (strlen(p->lastName) > 0)
    {
        strcat(result, p->lastName);
        strcat(result, " ");
    }
    strcat(result, p->firstName);
    strcat(result, "  |  ");

    if (strlen(p->tellCode) > 0)
    {
        strcat(result, "+");
        strcat(result, p->tellCode);
        strcat(result, " ");
    }
    strcat(result, p->tell);
    return result;
}

void personPrint(Person *record)
{
    printf("%s ", record->lastName);
    printf("%s  |  ", record->firstName);
    printf("+%s ", record->tellCode);
    printf("%s\n", record->tell);
}

typedef struct ArrayList
{
    int Lenght;
    int Capacity;
    Person *Arr;
} ArrayList;

ArrayList *new_ArrayList()
{
    ArrayList *Arr = malloc(sizeof(ArrayList));
    Arr->Arr = malloc(sizeof(Person) * 10);
    Arr->Capacity = 10;
    Arr->Lenght = 0;
    return Arr;
}

void increaseCapacity(ArrayList *arr)
{
    arr->Arr = realloc(arr->Arr, 2 * arr->Capacity * sizeof(Person));
    arr->Capacity *= 2;
}

void add(ArrayList *arr, Person *p)
{
    if (arr->Lenght == arr->Capacity)
    {
        increaseCapacity(arr);
    }
    arr->Arr[arr->Lenght] = *p;
    arr->Lenght++;
}

void removeAt(ArrayList *arr, int index)
{
    if (index < 0 || index >= arr->Lenght)
    {
        printf("Index mimo rozsah\n");
        return;
    }
    // free(&arr->Arr[index]);
    for (int i = index; i < arr->Lenght - 1; i++)
    {
        arr->Arr[i] = arr->Arr[i + 1];
    }
    arr->Lenght--;
}
// end of structs

char *getOnlyNums(char *mess)
{
    printf("%s", mess);
    char s[16];
    scanf("%s", s);
    char *SB = malloc(16);
    SB[0] = '\0';
    for (int i = 0; i < strlen(s); i++)
    {
        char c = s[i];
        if (c >= '0' && c <= '9')
        {
            strncat(SB, &c, 1);
        }
    }
    return SB;
}

void updatePerson(Person *p)
{
    printf("--- Enter code for update ---\n");
    printf("    1) First name\n");
    printf("    2) Last name\n");
    printf("    3) Dial code\n");
    printf("    4) Phone number\n");
    printf("---------------------------\n");

    char code;
    scanf(" %c", &code);
    switch (code)
    {
    case '1':
        printf("First name: ");
        char name[32];
        scanf("%s", name);
        strcpy(p->firstName, name);
        break;
    case '2':
        printf("Last name: ");
        char lname[32];
        scanf("%s", lname);
        strcpy(p->lastName, lname);
        break;
    case '3':
        char *tellCode = getOnlyNums("Dial code: ");
        strcpy(p->tellCode, tellCode);
        break;
    case '4':
        char *tel = getOnlyNums("Phone number: ");
        strcpy(p->tell, tel);
        break;
    default:
        printf("Bad Code\n");
        break;
    }
}

void addRecord(ArrayList *arr)
{
    printf("First name: ");
    char name[32];
    scanf("%s", name);

    printf("Last name: ");
    char lname[32];
    scanf("%s", lname);

    char *tellCode = getOnlyNums("Dial code: ");

    char *tel = getOnlyNums("Phone number: ");

    add(arr, new_Person(
                 lname,
                 name,
                 tellCode,
                 tel));
}

void printList(ArrayList *arr, Person *filter)
{
    if (arr->Lenght > 0)
        for (int i = 0; i < arr->Lenght; i++)
        {
            Person *record = &arr->Arr[i];
            char *fnameLwr = strdup(record->firstName);
            char *lnameLwr = strdup(record->lastName);
            strlwr(fnameLwr);
            strlwr(lnameLwr);

            char *FilFnameLwr = strdup(filter->firstName);
            char *FilLnameLwr = strdup(filter->lastName);
            strlwr(FilFnameLwr);
            strlwr(FilLnameLwr);
            if (
                strstr(fnameLwr, FilFnameLwr) != NULL &&
                strstr(lnameLwr, FilLnameLwr) != NULL &&
                strstr(record->tellCode, filter->tellCode) != NULL &&
                strstr(record->tell, filter->tell) != NULL)
            {
                printf("id: %d, ", i);
                personPrint(record);
            }
            free(fnameLwr);
            free(lnameLwr);
            free(FilFnameLwr);
            free(FilLnameLwr);
        }
    else
        printf("List is empty\n");
}

void updateRecord(ArrayList *arr, Person *filter)
{
    if (arr->Lenght > 0)
    {
        printList(arr, filter);
        printf("Record id: ");
        int index;
        scanf("%d", &index);

        if (index < 0 || index >= arr->Lenght)
        {
            printf("Index mimo rozsah\n");
            return;
        }

        updatePerson(&arr->Arr[index]);
    }
    else
        printf("List is empty\n");
}

void removeRecord(ArrayList *arr, Person *filter)
{
    if (arr->Lenght > 0)
    {
        printList(arr, filter);
        printf("Record id: ");
        int index;
        scanf("%d", &index);
        removeAt(arr, index);
    }
    else
        printf("List is empty\n");
}

void setFilter(Person *filter)
{
    printf("--- Filter ---\n");
    printf("  First name:%s\n", filter->firstName);
    printf("  Last name:%s\n", filter->lastName);
    printf("  Dial code:%s\n", filter->tellCode);
    printf("  Phone number:%s\n", filter->tell);
    printf("\n");

    printf("--- Enter code of operation ---\n");
    printf("    e) Edit filter\n");
    printf("    r) Reset filter\n");
    printf("---------------------------\n");
    personPrint(filter);
    char code;
    scanf(" %c", &code);
    switch (code)
    {
    case 'e':
        updatePerson(filter);
        break;
    case 'r':
        strcpy(filter->lastName, "");
        strcpy(filter->firstName, "");
        strcpy(filter->tellCode, "");
        strcpy(filter->tell, "");
        break;
    default:
        printf("Bad Code\n");
        break;
    }
}

int main()
{
    ArrayList *arr = new_ArrayList();
    Person *filter = new_Person("", "", "", "");
    add(arr, new_Person(
                 "Cirkle",
                 "Jan",
                 "420",
                 "741268793"));
    int run = 1;
    while (run)
    {
        printf("--- Enter code of operation ---\n");
        printf("    1) Add record\n");
        printf("    2) Show list\n");
        printf("    3) Update record\n");
        printf("    4) Remove from list\n");
        printf("    5) Set filter\n");
        printf("    6) End\n");
        printf("---------------------------\n");
        char code;
        scanf(" %c", &code);
        switch (code)
        {
        case '1':
            addRecord(arr);
            break;
        case '2':
            printList(arr, filter);
            break;
        case '3':
            updateRecord(arr, filter);
            break;
        case '4':
            removeRecord(arr, filter);
            break;
        case '5':
            setFilter(filter);
            break;
        case '6':
            run = 0;
            break;
        default:
            printf("Bad Code\n");
            break;
        }
    }
    return 0;
}