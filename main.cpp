#include <cerrno>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <termios.h>
#include <unistd.h>

bool restoreTerminal(const termios &original)
{
    int result;
    do
    {
        result = tcsetattr(STDIN_FILENO, TCSANOW, &original);
    } while (result == -1 && errno == EINTR);

    return result == 0;
}

int main()
{
    termios original;
    if (tcgetattr(STDIN_FILENO, &original) == -1)
    {
        std::perror("Could not read terminal settings");
        return 1;
    }

    termios experiment = original;
    experiment.c_lflag &= ~(ECHO | ICANON);
    experiment.c_cc[VMIN] = 1;
    experiment.c_cc[VTIME] = 0;

    int exitStatus = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &experiment) == -1)
    {
        std::perror("Could not disable terminal echo and canonical mode");
        exitStatus = 1;
    }
    else
    {
        std::cout << "ICANON: disabled\nECHO: disabled\n"
                  << std::flush;

        while (true)
        {
            char character;
            const ssize_t bytesRead = read(STDIN_FILENO, &character, 1);

            if (bytesRead == -1)
            {
                std::perror("Could not read terminal input");
                exitStatus = 1;
                break;
            }
            if (bytesRead == 0)
                break;
            if (character == 'q')
                break;

            const unsigned char byte = static_cast<unsigned char>(character);
            std::cout << static_cast<int>(byte);
            if (std::isprint(byte))
                std::cout << " ('" << character << "')";
            std::cout << '\n' << std::flush;
        }
    }

    // All paths after the settings-change attempt reach this cleanup.
    if (!restoreTerminal(original))
    {
        std::perror("Could not restore terminal settings");
        exitStatus = 1;
    }

    return exitStatus;
}
