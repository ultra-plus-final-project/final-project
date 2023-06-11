# final-project
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

----------------------------------------------------------------------------------------------------</br>
How to use this porgram?</br>

First, Enter the data for year, month, and day. If the input is incorrect, prompt for re-entering.</br>

Second, Enter the action to be performed. Action 1 is to add a new event, Action 2 is to search for a specific event, Action 3 is to delete a specified event, Action 4 is to print the calendar, Action 5 is to move to the next day, and Action 6 is to move to the next month.</br>
