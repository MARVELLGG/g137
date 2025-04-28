#include <iostream>
#include <fstream>
#include <future>
#include <thread>
#include <chrono>
#include "corefunc.h"
#include "userfunc.h"
#include <string>
#include <unistd.h>
#include <stdint.h>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;
vector<GrowtopiaBot> bots;

int main() {
    ifstream i("config.json");
    json j;
    i >> j;
    init();
    system("clear");
    cout << "GrowtopiaBot v1.0 [Not included QT]! by GrowtopiaNoobs and DrOreo002" << endl;
    
    if (j["ip"] == "Ip Target")
    {
        cout << "Please change the \"Ip Target\" to ip gtps on config.json" << endl;
        return 0;
    }
    
    GrowtopiaBot bot = {
        j["username"], j["password"], j["ip"], j["port"]
    };
    cout << "------------------------" << endl;
    cout << "Bot loaded!. Using username " << j["username"].get<string>() << ", With owner " + j["ownerUsername"].get<string>() << endl;

    bot.gameVersion = j["gameVersion"].get<string>();
    bot.worldName = j["targetWorld"].get<string>();
    bot.ownerUsername = j["ownerUsername"].get<string>();

    bot.userInit();
    bots.push_back(bot);

    bool running = true; // Flag untuk mengontrol loop utama

    std::thread inputThread([&]() {
        while (running) {
            string userInput;
            cout << "Masukkan perintah untuk dikirimkan sebagai paket: ";
            std::getline(cin, userInput);
            if (!userInput.empty()) {
                if (userInput == "exit") {
                    running = false; // Hentikan loop saat input "exit"
                    break;
                }
                bot.SendPacket(2, userInput, bot.peer);
                cout << "Paket dikirim: " << userInput << endl;
            }
        }
    });

    // Loop utama untuk bot
    while (running) {
        bot.eventLoop();
        bot.userLoop();
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Hindari penggunaan CPU tinggi
    }

    // Tunggu inputThread selesai
    if (inputThread.joinable()) {
        inputThread.join();
    }

    cout << "Program dihentikan." << endl;
    return 0;
}
