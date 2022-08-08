#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void espeak(char text[])
{
    char phrase[410];
    strcpy(phrase, "espeak \"");
    strcat(phrase, text);
    strcat(phrase, "\"");
    puts(text);
    system(phrase);
}
void take_command(char query[])
{
    gets(query);
}
void wishme()
{
    time_t now;
    struct tm *now_tm;
    int t;
    now = time(NULL);
    now_tm = localtime(&now);
    t = now_tm->tm_hour;
    espeak("Hello,");
    if (t > 0 && t < 12)
        espeak("good morning sir\n");
    else if (t >= 12 && t < 18)
        espeak("good afternoon sir\n");
    else
        espeak("good evening sir\n");
    espeak("How may I help you?\n");
}
int check(char query[], char par[])
{
    int i = 0, pl, count = 0;
    char temp[20];
    pl = strlen(par);

    while (query[i] != '\0')
    {
        if (query[i] == ' ')
        {
            temp[count] = '\0';
            if (strcmp(temp, par) == 0)
            {
                return 1;
            }
            else
                count = 0;
        }
        else
        {
            temp[count] = query[i];
            count++;
        }
        i++;
    }
    i = 0;
    temp[count] = '\0';
    while (par[i] != '\0')
    {
        if (par[i] != temp[i])
            return 0;
        i++;
    }
    return 1;
}

void main()
{
    int n1, n2, n3, n4, con;
    char query[100];
    char tempStr[100];
    int exit_p = 0;
    wishme();
    while (!exit_p)
    {
        take_command(query);
        if (check(query, "add\0") == 1)
        {
            espeak("Enter the first number:");
            scanf("%d", &n1);
            espeak("Enter the second number:");
            scanf("%d", &n2);
            n3 = n1+n2;
            strcpy(tempStr,"The sum is ");
            sprintf(tempStr, "%d", n3);
            espeak(tempStr);
        }

        if (check(query, "sum\0") == 1)
        {
            espeak("Enter the first number:");
            scanf("%d", &n1);
            espeak("Enter the second number:");
            scanf("%d", &n2);
            sprintf(tempStr, "The sum is %d\n", n1 + n2);
            espeak(tempStr);
        }

        if (check(query, "difference\0") == 1)
        {
            espeak("Enter the first number:");
            scanf("%d", &n1);
            espeak("Enter the second number:");
            scanf("%d", &n2);
            sprintf("The difference is %d\n", n1 - n2);
            espeak(tempStr);
        }
        if (check(query, "subtract\0") == 1)
        {
            espeak("Enter the first number:");
            scanf("%d", &n1);
            espeak("Enter the second number:");
            scanf("%d", &n2);
            sprintf(tempStr, "The difference is %d\n", n1 - n2);
            espeak(tempStr);
        }
        if (check(query, "multiply\0") == 1 || check(query, "product\0") == 1)
        {
            espeak("Enter the first number:");
            scanf("%d", &n1);
            espeak("Enter the second number:");
            scanf("%d", &n2);
            sprintf(tempStr, "The product is %d\n", n1 * n2);
            espeak(tempStr);
        }
        if (check(query, "divide\0") == 1)
        {
            espeak("Enter the first number:");
            scanf("%d", &n1);
            espeak("Enter the second number:");
            scanf("%d", &n2);
            sprintf(tempStr, "The product is %.3f\n", n1 * 1.0 / n2);
            espeak(tempStr);
        }
        if (strcmp("hey jarvis", query) == 0)
        {
            wishme();
        }
        if (check(query, "stop\0"))
        {
            exit_p = 1;
            espeak("Have a good day, sir.");
        }
    }
}