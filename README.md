<h1 style="text-align: center;">final-project</h1>
--SDL part-- </br>
The Simple DirectMedia Layer library source code is available from:</br>
https://www.libsdl.org/</br>
</br>
/* DEPENDENCIES */</br>
SDL2.h, SDL_image.h, stdio.h, stdbool.h, math.h</br> 
</br>
/* initialize() */ </br>
initializes sdl2, defines/creates a window, renderer, yes_texture, oops_texture, yesRect, oopsRect and also draws to the front buffer by calling SDL_RenderPresent().</br>
</br>

1.Download the development package: Visit the official SDL website (https://www.libsdl.org/) and download the latest development package. Make sure to choose the package that matches your system architecture (32-bit or 64-bit).</br>

2.Extract the package: Unzip the downloaded package into the directory where you want to install SDL.</br>

3.Set up environment variables: To allow the compiler to find the SDL headers and libraries, you need to set up the corresponding environment variables. On Windows 11, press Win + X and select "System". In the System settings, click on "About" and then "Advanced system settings" on the right side. In the System Properties window, click the "Environment Variables" button. In the list under System variables, look for the variable named PATH, click on it, and then click "Edit". In the Edit Environment Variable window, click "New" and enter the paths to the SDL headers and libraries, for example: C:\SDL2\include and C:\SDL2\lib. Make sure to provide the correct paths that correspond to the location where you extracted the SDL package.</br>

4.Install development tools: SDL itself is just a multimedia library, and you need a development tool (such as GCC, MinGW, or Visual Studio) to compile and link your code. Install the appropriate development tool based on your choice.</br>

5.Compile and link your code: In your development environment, create a new project or source file and add your SDL code to it. During the compilation and linking process, make sure your development tool can find the SDL headers and libraries. If everything is set up correctly, you should be able to successfully compile and run your SDL code.</br>

6.Or you can refer this link. --> https://lazyfoo.net/SDL_tutorials/index.php

----------------------------------------------------------------------------------------------------</br>
How to use this porgram?</br>

This program is designed to assist the user in memorizing their schedule for the year.</br>

In the initial section of the program, the user will be prompted to input personal information such as their name and the current time. Once the information is entered, the program will proceed to inquire about various actions to be performed. These actions include the following:</br>

Action 1 - Create a new event: The user will be required to input relevant details about the new event, such as the starting month, day, and any necessary memos. This information will then be inserted into the schedule.</br>

Action 2 - Search for an event: The user can search for free time or scheduled events according to their preferred criteria.</br>

Action 3 - Search through the hash table: This action allows the user to search for events using a hash table, offering an alternative method of finding specific information.</br>

Action 4 - Delete an event: By providing the month, date, and event name, the user can delete a specific event from the schedule.</br>

Action 5 - Print the schedule: The program provides an option to print the entire schedule, allowing the user to review their planned events.</br>

Action 6 - Terminate the month: By selecting this action, the user can move on to the first day of the next month.</br>

Action 7 - Terminate the day: This action allows the user to proceed to the next day.</br>

By running the program repeatedly in a loop, the schedule gradually becomes more complete and comprehensive. This program serves as a valuable tool for assisting the user in organizing their time effectively and maximizing productivity.
