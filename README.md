# to-dos-api-cpp

## How to build this project

It is recommended to build library and run tests using [Dev containers](https://code.visualstudio.com/docs/devcontainers/containers) in Visual Studio Code.
For development purposes use a devcontainer named `developing`.

### Prerequisites

- Install [WSL](https://ubuntu.com/desktop/wsl) 
- Install the Docker client ([Windows](https://docs.docker.com/desktop/setup/install/windows-install/) / [Mac](https://docs.docker.com/desktop/setup/install/mac-install/) / [Linux](https://docs.docker.com/desktop/setup/install/linux-install/)) 
  - Make sure Docker client is the latest version 
   <p style="text-align: center;"><img src="docs/images/dockerVersion.png" alt="dockerVersion" width="400"/></p>
   - Make sure Docker uses WSL 2 based engine 
   <p style="text-align: center;"><img src="docs/images/dockerSettings.png" alt="dockerSettings" width="400"/></p>
- Microsoft VS Code
  - VS Code should also have the "Dev Containers" extension installed. To check it, open "View: Extensions" with `Ctrl + Shift + X` or as shown in the screenshot below:
  <p style="text-align: center;"><img src="docs/images/vscodeExtensions.png" alt="vscodeExtensions" width="400"/></p>
- Make sure Docker daemon is running before opening the dev container (`Ctrl + Shift + P` -> "Reopen in container" or click here + "Reopen in container")
 <p style="text-align: center;"><img src="docs/images/vscodeContainer.png" alt="vscodeContainer" width="400"/></p>

### Project building

To build this project, open the VS Code terminal (`Ctrl + Shift + ~`) and run `conan install .`.
After the Conan install process, open the CMake extension and click Configure. 
<p style="text-align: center;"><img src="docs/images/cmakeConfigure.png" alt="cmakeConfigure" width="400"/></p>
In the configuration options, select the `'conan-debug' config`.

When the project configuration is finished, click Build to build the project.
<p style="text-align: center;"><img src="docs/images/cmakeBuild.png" alt="cmakeBuild" width="400"/></p>

To launch the executable, click Launch in the CMake extension.
<p style="text-align: center;"><img src="docs/images/cmakeLaunch.png" alt="cmakeLaunch" width="400"/></p>