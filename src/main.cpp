// Created on Fri Jan 03 2025
// © 2025 BLACKHAND Studio. All rights reserved.
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//      http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "App.h"

#include <SFML/Audio.hpp>

#include <thread>
#include <chrono>
#include <iostream>

int main()
{
    sf::SoundBuffer buffer;

    if(!buffer.loadFromFile("../assets/white-ashes.wav"))
    {
        std::cout << "Can not open WAV\n" << std::endl;
        return -1;
    }

    sf::Sound sound(buffer);
    sound.play();

    auto print = []() -> void {
        for(int i = 0; i < 50; ++i)
            std::cout << std::endl;
        
        std::cout << "\tOne" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << " late" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << " night," << std::endl;

        for(int i = 0; i < 5; ++i)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "\tI"<< std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << " realized" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << " that" << std::flush;

        std::this_thread::sleep_for(std::chrono::seconds(3));

        for(int i = 0; i < 3; ++i)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << " . " << std::flush;
        }


        std::this_thread::sleep_for(std::chrono::seconds(2));

        for(int i = 0; i < 5; ++i)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << std::endl;
        }

        std::cout << "\t" << std::flush;

        for(int i = 0; i < 3; ++i)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << " . " << std::flush;
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "I" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << " am" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << " alone.\n" << std::flush;
        
        for(int i = 0; i < 5; ++i)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << std::endl;
        }

        std::cout << "\tSad.\n" << std::flush;

        std::this_thread::sleep_for(std::chrono::seconds(5));
        for(int i = 0; i < 100; ++i)
            std::cout << std::endl;
    };

    App app;
    if(!app.Init())
        return -1;

    std::thread print_th(print);

    while(app.IsRunning())
        app.Run();
    
    if (print_th.joinable())
        print_th.join();

    for(int i = 0; i < 50; ++i)
        printf("\n");

    printf("\n<Music>\n");
    printf("\n\t\"White ashes\"");
    printf("\n\tFROM the EP album <Noises.> (_Grammer, 2025)\n");
    printf("\tCompose - Jiwon Nam\n");
    printf("\tArrange - Jiwon Nam\n");

    printf("\n<Film>\n");
    printf("\n\tDirecting - Jiwon Nam\n");
    printf("\tProgramming - Jiwon Nam\n");

    printf("\nThank you.\n");

    for(int i = 0; i < 20; ++i)
        printf("\n");
    return 0;
}