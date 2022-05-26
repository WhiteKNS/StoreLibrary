#include "pch.h"

#include <iostream>
#include <ws2tcpip.h>
#include <winsock2.h>

#include "Products.h"
#include "Request.h"
#include "DatabaseStorage.h"
#include "DatabaseWorker.h"

#pragma comment(lib, "ws2_32.lib")


void RunCommand(const Request& request)
{
    std::string response;
    if (request.command == "GetAllFamilies")
    {
        response = GetAllProductFamilies();
    }
    else if (request.command == "GetAllProducts")
    {
        response = GetAllProducts(request.args.c_str());
    }
    else if (request.command == "GetProduct")
    {
        response = GetProductInformation(request.args.c_str());
    }
    else if (request.command == "Purchase")
    {
        response = PurchaseProduct(request.args.c_str());
    }

    // we would send the respons here
}

void RunDatabaseSheduler()
{
    DatabaseWorker db_worker;

    db_worker.Update();
}


void Run()
{
    const int clients_number = 2;
    const int port_number = 8083;

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_IPVAddr;
    server_IPVAddr.sin_addr.s_addr = INADDR_ANY;
    server_IPVAddr.sin_family = AF_INET;
    server_IPVAddr.sin_port = htons(port_number);

    struct sockaddr_storage addr_storage;

    bind(server_socket,
        (struct sockaddr*)&server_IPVAddr,
        sizeof(server_IPVAddr));

    if (listen(server_socket, 50) == 0)
        std::cout << "Listening..." << std::endl;
    else
        std::cerr << "An error occured while listening to the socket" << std::endl;

    int i = 0;
    std::vector<std::thread> clients_threads(clients_number);
    while (true) {
        socklen_t addr_size = sizeof(addr_storage);

        // Extract the first connection in the queue
        SOCKET child_socket = accept(server_socket,
            (struct sockaddr*)&addr_storage,
            &addr_size);

        std::string strData;

        int bytes = recv(child_socket, (char*)&strData, static_cast<int>(strData.size()), 0);
        if (bytes < 0) {
            std::string msg = "Unable to read from socket";
            //std::cerr << msg << std::endl;
            continue;
        }


        auto request = reinterpret_cast<Request*>(&strData);


        std::thread client_thread(RunCommand, *request);
        clients_threads.push_back(std::move(client_thread));
        i++;

        if (i >= clients_number) {
            i = 0;
            while (i < clients_number) {
                clients_threads[i++].join();
            }

            i = 0;
        }

    }
}

void InitAndRun()
{
    std::thread db_thread(RunDatabaseSheduler);
    db_thread.detach();
    //Run();
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        InitAndRun();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
