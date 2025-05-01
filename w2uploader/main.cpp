#include <chrono>
#include <cstring>
#include <fstream>
#include <iostream>

#include "CSerialPort/SerialPort.h"
using namespace std;
using namespace itas109;

#ifdef __DEBUG
auto SUCCESS = "\033[32m";
auto FAIL = "\033[31m";
auto WARNING = "\033[33m";
auto RESET = "\033[0m";
#else
auto SUCCESS = "";
auto FAIL = "";
auto WARNING = "";
auto RESET = "";
#endif

#ifdef __DEBUG
auto TIMEOUT = 5;
#else
auto TIMEOUT = 1;
#endif
auto NO_TIMEOUT = -1;

bool DelayForResponse(CSerialPort* serial_port, const string& message, const int timeout, const bool is_visible)
{
    const auto start_time = chrono::high_resolution_clock::now();
    while (true)
    {
        const auto data = new char[8196];
        serial_port->readAllData(data);

        if (string(data).find(message) != string::npos)
        {
            if (is_visible)
            {
                cout << data << endl;
            }
            delete[] data;
            return true;
        }

        delete[] data;

        auto duration = chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start_time);
        if (timeout != NO_TIMEOUT && duration.count() > timeout)
        {
            return false;
        }
    }
}

void ReadAll(CSerialPort* serial_port)
{
    const auto data = new char[64];
    serial_port->readAllData(data);
    delete[] data;
}

void MemoryWriteWord(CSerialPort* serial_port, const string& address, const string& value)
{
    serial_port->writeData("1", 1);
    DelayForResponse(serial_port, "Address in hex>", TIMEOUT, false);
    serial_port->writeData(address.c_str(), static_cast<int>(address.size()));
    serial_port->writeData("\n", 1);
    DelayForResponse(serial_port, "Value in hex>", TIMEOUT, false);
    serial_port->writeData(value.c_str(), static_cast<int>(value.size()));
    serial_port->writeData("\n", 1);
    DelayForResponse(serial_port, " > ", 2 * TIMEOUT, false);
}

int GetSerialPort(CSerialPort* serial_port, const char* port_name, const bool is_reset)
{
    for (int i = 1; i < 6; ++i)
    {
        string order;
        switch (i)
        {
        case 1:
            order = "st";
            break;
        case 2:
            order = "nd";
            break;
        case 3:
            order = "rd";
            break;
        default:
            order = "th";
            break;
        }
        cout << endl << "The " << i << order << " try to open the serial port" << endl;

        serial_port->init(port_name,
                          BaudRate9600,
                          ParityNone,
                          DataBits8,
                          StopOne,
                          FlowNone,
                          8192);

        serial_port->open();
        serial_port->writeData("\n", 1);

        if (is_reset)
        {
            auto start_time = chrono::high_resolution_clock::now();
            while (!serial_port->isOpen())
            {
                serial_port->open();
                serial_port->writeData("\n", 1);
                auto duration = chrono::duration_cast<chrono::seconds>(
                    chrono::high_resolution_clock::now() - start_time);
                if (duration.count() > TIMEOUT)
                {
                    cout << WARNING << "Failed to open the serial port, please check if it is occupied"
                        << RESET << endl;
                    start_time = chrono::high_resolution_clock::now();
                }
            }
            cout << "Port opened, waiting for resetting the board..." << endl;
            DelayForResponse(serial_port, " > ", NO_TIMEOUT, false);
            cout << SUCCESS << "Board is ready" << RESET << endl;
        }

        if (serial_port->isOpen())
        {
            if (DelayForResponse(serial_port, " > ", TIMEOUT, false))
            {
                serial_port->close();
                cout << SUCCESS << "Serial port " << serial_port->getPortName() << " connected successfully"
                    << RESET << endl;
                return 0;
            }
            cout << "Fail to initialize the serial port " << serial_port->getPortName() << endl;
            serial_port->close();
            if (i == 5)
            {
                cerr << "Please check if the board is reset or connected" << endl;
                return 1;
            }
        }
        else
        {
            cout << "Failed to open the serial port " << serial_port->getPortName() << endl;
            if (i == 5)
            {
                cerr << "Please check the serial port name or if it is occupied" << endl;
                return 1;
            }
            cout << "Retrying..." << endl;
        }
    }

    return 1;
}

int main(const int argc, char* argv[])
{
    bool is_help = false;
    bool is_visible = false;
    bool is_run = false;
    bool is_reset = true;
    const string help_message = "Usage:\n"
        "w2uploader <bin_path> <port_name> [OPTIONS]\n"
        "OPTIONS:\n"
        "  -h, --help       Show this help message\n"
        "  -v, --visible    Show detailed information\n"
        "  -r, --run        Run the program immediately after the upload\n"
        "      --no-reset   Upload the program immediately without waiting for the reset of the board\n";

#ifdef __DEBUG
    cout << "Debug mode enabled" << endl;
    for (int i = 0; i < argc; ++i)
    {
        cout << "argv[" << i << "]: " << argv[i] << endl;
    }
#endif

    if (argc < 3)
    {
        cout << help_message << endl;
        return 1;
    }

    for (int i = 0; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            is_help = true;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--visible") == 0)
        {
            is_visible = true;
        }
        else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--run") == 0)
        {
            is_run = true;
        }
        else if (strcmp(argv[i], "--no-reset") == 0)
        {
            is_reset = false;
        }
    }

    if (is_help)
    {
        cout << help_message << endl;
        return 1;
    }

    const char* bin_path = argv[1];
    const char* port_name = argv[2];

    ifstream bin_file(bin_path, ios::in | ios::binary | ios::ate);
    if (!bin_file || !bin_file.good())
    {
        cerr << "Failed to open the file " << bin_path << endl;
        return 1;
    }

    auto* serial_port = new CSerialPort();
    if (GetSerialPort(serial_port, port_name, is_reset))
    {
        cerr << "Failed to connect the serial port " << port_name << endl;
        return 1;
    }
    serial_port->open();
    serial_port->readAllData(nullptr);

    serial_port->writeData("\n", 1);
    cout << "Wait for the response from the board" << endl;
    if (DelayForResponse(serial_port, " > ", 5 * TIMEOUT, is_visible))
    {
        cout << SUCCESS << "Success" << RESET << endl;
    }

    cout << "Unlock the Flash" << endl;
    MemoryWriteWord(serial_port, "1F800B07", "A5");
    cout << "Erase the Flash" << endl;
    MemoryWriteWord(serial_port, "10300000", "A5");
    cout << "Do some previous actions before upload" << endl;
    MemoryWriteWord(serial_port, "1f800004", "40");

    const auto f_size = bin_file.tellg();
    char buffer[static_cast<size_t>(f_size)];
    bin_file.seekg(0, ios::beg);
    if (!bin_file.read(buffer, static_cast<int>(f_size)))
    {
        cerr << "Failed to read the file " << bin_path << endl;
    }

    serial_port->writeData("5", 1);
    DelayForResponse(serial_port, "Address in hex> ", TIMEOUT, is_visible);
    serial_port->writeData("10000000\n", 9);
    DelayForResponse(serial_port, "Waiting for binary image linked at 10000000", TIMEOUT, is_visible);
    cout << "Uploading..." << endl;
    serial_port->writeData(buffer, static_cast<int>(f_size));

    DelayForResponse(serial_port, " > ", TIMEOUT, is_visible);

    cout << f_size << " bytes code loaded to 0x10000000" << endl;
    MemoryWriteWord(serial_port, "1f800004", "0");

    if (is_run)
    {
        cout << "Jumping to the code" << endl;
        serial_port->writeData("3", 1);
        DelayForResponse(serial_port, "Address in hex> ", 1, is_visible);
        serial_port->writeData("10000000\n", 9);
    }

    serial_port->close();
    cout << "Serial port closed \nSystem resources disposed" << endl;
    cout << SUCCESS << "All done!" << RESET << endl;
    return 0;
}
