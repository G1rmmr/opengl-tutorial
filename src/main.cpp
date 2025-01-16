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

int main()
{
    sf::SoundBuffer buffer;

    if(!buffer.loadFromFile("../assets/white-ashes.wav"))
    {
        fprintf(stderr, "Can not open WAV\n");
        return -1;
    }

    sf::Sound sound(buffer);
    sound.play();

    App app;
    if(!app.Init())
        return -1;

    for(int i = 0; i < 50; ++i)
        printf("\n");
    
    printf("\tWhite ashes\n");

    for(int i = 0; i < 30; ++i)
        printf("\n");

    while(app.IsRunning())
        app.Run();
    
    
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