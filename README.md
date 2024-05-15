# Read me
My homework
## something
This's the last time I rewrite code I wrote in Java to C.
1. Part of code
```C
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
```
