#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

void recog(char *buffer)
{
    char outp[1024];
    printf("Listening...\n");
    FILE *rec = popen("python -u src/recog.py", "r");
    while (fgets(outp, sizeof(outp), rec) != 0)
    {
    }
    strcpy(buffer, outp);
    printf("%s\n", outp);
}
void speak(char text[])
{
    char phrase[410];
    strcpy(phrase, "espeak -s 175 -v en+m7 \"");
    strcat(phrase, text);
    strcat(phrase, "\"");
    printf("%s\n", text);
    system(phrase);
}

void give_weather(char *buffer)
{
    char outp[1024];

    FILE *rec = popen("python -u src/weather.py", "r");
    while (fgets(outp, sizeof(outp), rec) != 0)
    {
    }
    strcpy(buffer, outp);
    speak(outp);
}

void take_command(char *query)
{
    int n = 0;
    recog(query);
    while (query[n] != 0)
    {
        query[n] = tolower(query[n]);
        n++;
    }
}
int take_number()
{
    char query[100];
    take_command(query);
    return atoi(query);
}
void wishme()
{
    time_t now;
    struct tm *now_tm;
    int t;
    now = time(NULL);
    now_tm = localtime(&now);
    t = now_tm->tm_hour;

    if (t > 0 && t < 12)
    {

        printf("Hello,good morning sir\n");
        system("vlc -I dummy --dummy-quiet morning.wav vlc://quit");
    }
    else if (t >= 12 && t < 18)
    {
        printf("Hello,good afternoon sir\n");
        system("vlc -I dummy --dummy-quiet afternoon.wav vlc://quit");
    }
    else
    {
        printf("Hello,good evening sir\n");
        system("vlc -I dummy --dummy-quiet evening.wav vlc://quit");
    }
    printf("How may I help you sir?\n");
    system("vlc -I dummy --dummy-quiet help.wav vlc://quit");
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
    time_t now;
    struct tm *now_tm;
    int hr, min;
    int n1, n2, n3, n4, con;
    float div;
    char query[100], search[100], sgk[100], tempstr[100], numstr[10];
    int exit_p = 0;
    wishme();
    while (!exit_p)
    {
        take_command(query);
        if (check(query, "jimmy\0") == 1)
        {
            wishme();
        }
        if (check(query, "add\0") == 1 || check(query, "sum\0") == 1 || check(query, "addition\0") == 1)
        {
            printf("Enter the first number:");
            system("vlc -I dummy --dummy-quiet first.wav vlc://quit");
            n1 = take_number();
            printf("Enter the second number:");
            system("vlc -I dummy --dummy-quiet second.wav vlc://quit");
            n2 = take_number();
            printf("The sum is ");
            system("vlc -I dummy --dummy-quiet sum.wav vlc://quit ");
            n3 = n1 + n2;
            itoa(n3, numstr, 10);
            speak(numstr);
        }

        if (check(query, "difference\0") == 1 || check(query, "subtract\0") == 1)
        {
            printf("Enter the first number:");
            system("vlc -I dummy --dummy-quiet first.wav vlc://quit");
            n1 = take_number();
            printf("Enter the second number:");
            system("vlc -I dummy --dummy-quiet second.wav vlc://quit");
            n2 = take_number();
            printf("The difference is ");
            system("vlc -I dummy --dummy-quiet difference.wav vlc://quit ");
            n3 = n1 - n2;
            itoa(n3, numstr, 10);
            speak(numstr);
        }
        if (check(query, "multiply\0") == 1 || check(query, "product\0") == 1)
        {
            printf("Enter the first number:");
            system("vlc -I dummy --dummy-quiet first.wav vlc://quit");
            n1 = take_number();
            printf("Enter the second number:");
            system("vlc -I dummy --dummy-quiet second.wav vlc://quit");
            n2 = take_number();
            printf("The product is ");
            system("vlc -I dummy --dummy-quiet product.wav vlc://quit ");
            n3 = n1 * n2;
            itoa(n3, numstr, 10);
            speak(numstr);
        }
        if (check(query, "divide\0") == 1)
        {
            printf("Enter the first number:");
            system("vlc -I dummy --dummy-quiet first.wav vlc://quit");
            n1 = take_number();
            printf("Enter the second number:");
            system("vlc -I dummy --dummy-quiet second.wav vlc://quit");
            n2 = take_number();
            printf("The quotient is ");
            system("vlc -I dummy --dummy-quiet quotient.wav vlc://quit ");
            div = n1 * 1.0 / n2;
            gcvt(div, 4, numstr);
            speak(numstr);
        }
        if (strcmp("hey jarvis", query) == 0)
        {
            wishme();
        }
        if (check(query, "thank") == 1 || check("thanks", query) == 1)
        {
            printf("Its my pleasure sir");
            system("vlc -I dummy --dummy-quiet pleasure.wav vlc://quit");
        }

        if (check(query, "time\0"))
        {
            now = time(NULL);
            now_tm = localtime(&now);
            hr = now_tm->tm_hour;
            min = now_tm->tm_min;
            printf("The current time is : ");
            system("vlc -I dummy --dummy-quiet time.wav vlc://quit");
            if (hr < 12)
            {
                itoa(hr, numstr, 10);
                strcpy(tempstr, numstr);
                strcat(tempstr, ":");
                itoa(min, numstr, 10);
                strcat(tempstr, numstr);
                speak(tempstr);
                printf(" AM");
                system("vlc -I dummy --dummy-quiet am.wav vlc://quit");
            }
            else
            {
                itoa(hr - 12, numstr, 10);
                strcpy(tempstr, numstr);
                strcat(tempstr, ":");
                itoa(min, numstr, 10);
                strcat(tempstr, numstr);
                speak(tempstr);
                printf(" PM");
                system("vlc -I dummy --dummy-quiet pm.wav vlc://quit");
            }
        }
        if (check(query, "youtube\0") == 1 && check(query, "open\0") == 1)
        {
            system("vlc -I dummy --dummy-quiet open_youtube.wav vlc://quit");
            system("start www.youtube.com");
            exit_p = 1;
        }
        else if (check(query, "search") == 1 && check(query, "youtube\0") == 1)
        {
            n2 = 0;
            for (n1 = 7; n1 < strlen(query) - 12; n1++)
            {
                sgk[n2] = query[n1];
                n2++;
            }
            system("vlc -I dummy --dummy-quiet search_youtube.wav vlc://quit");
            strcpy(search, "start www.youtube.com/results?search_query=\"");
            strcat(search, sgk);
            strcat(search, "\"");
            system(search);
            exit_p = 1;
        }
        else if (check(query, "play") == 1 && check(query, "youtube\0") == 1)
        {
            n2 = 0;
            for (n1 = 5; n1 <= strlen(query) - 13; n1++)
            {
                sgk[n2] = query[n1];
                n2++;
            }
            system("vlc -I dummy --dummy-quiet play_youtube.wav vlc://quit");
            strcpy(search, "start www.youtube.com/results?search_query=\"");
            strcat(search, sgk);
            strcat(search, "\"");
            system(search);
            system("python src/clicker.py");
            exit_p = 1;
        }
        if (check(query, "google\0") == 1 && check(query, "open\0") == 1)
        {
            system("vlc -I dummy --dummy-quiet open_google.wav vlc://quit");
            system("start www.google.com");
            exit_p = 1;
        }
        else if (check(query, "google\0") == 1 && check(query, "in\0") == 1 && check(query, "search\0") == 1)
        {
            n2 = 0;
            for (n1 = 7; n1 < strlen(query) - 11; n1++)
            {
                sgk[n2] = query[n1];
                n2++;
            }
            system("vlc -I dummy --dummy-quiet search_google.wav vlc://quit");
            strcpy(search, "start www.google.com/search?q=\"");
            strcat(search, sgk);
            strcat(search, "\"");

            system(search);
            exit_p = 1;
        }
        else if (check(query, "google\0") == 1)
        {
            n2 = 0;
            for (n1 = 7; n2 < strlen(query); n1++)
            {
                sgk[n2] = query[n1];
                n2++;
            }
            system("vlc -I dummy --dummy-quiet search_google.wav vlc://quit");
            strcpy(search, "start www.google.com/search?q=\"");
            strcat(search, sgk);
            strcat(search, "\"");

            system(search);
            exit_p = 1;
        }
        if (check(query, "weather\0"))
        {
            give_weather(query);
        }
        if (check(query, "dice\0") == 1)
        {
            srand(time(NULL));
            n1 = rand() % 6;
            system("vlc -I dummy --dummy-quiet dice.mp3 vlc://quit");
            n2 = n1 + 1;
            itoa(n2, numstr, 10);
            speak(numstr);
        }
        if (check(query, "coin\0") == 1)
        {
            srand(time(NULL));
            n1 = rand() % 2;
            system("vlc -I dummy --dummy-quiet coin.mp3 vlc://quit");
            if (n1 == 0)
            {
                system("vlc -I dummy --dummy-quiet heads.wav vlc://quit");
                printf("Heads\n");
            }
            else
            {
                printf("Tails\n");
                system("vlc -I dummy --dummy-quiet tails.wav vlc://quit");
            }
        }
        if (check(query, "stop\0") || check(query, "exit\0") == 1)
        {
            printf("Have a good day sir");
            system("vlc -I dummy --dummy-quiet wish.wav vlc://quit");
            exit_p = 1;
        }
    }
}