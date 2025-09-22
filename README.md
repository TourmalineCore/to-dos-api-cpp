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

To build this project, open the VS Code terminal (`Ctrl + Shift + ~`) and run `conan install . --build=missing`.
After the Conan install process, open the CMake extension and click Configure. 
<p style="text-align: center;"><img src="docs/images/cmakeConfigure.png" alt="cmakeConfigure" width="400"/></p>
In the configuration options, select the `'conan-debug' config`.

When the project configuration is finished, click Build to build the project.
<p style="text-align: center;"><img src="docs/images/cmakeBuild.png" alt="cmakeBuild" width="400"/></p>

### Project run

#### Before launching web server:
- Run the database container via docker compose command `docker compose -f docker-compose.dev.yaml up -d` from workspace.
- Import environment variables declared in the `.env.dev` file while in the dev container and using the command `export $(grep -v '^#' .env.dev | xargs)`. If the file containing the environment variables is named something other than .env.dev, you should modify the command to specify the correct name.

To launch the executable, click Launch in the CMake extension.
<p style="text-align: center;"><img src="docs/images/cmakeLaunch.png" alt="cmakeLaunch" width="400"/></p>

## How to run clang-tidy static code analyzer

To run clang-tidy, run the following command:
```
find ./src -name "*.cpp" -not -path "*/build/*" -exec echo "Checking {}..." \; -exec clang-tidy --config-file=.clang-tidy {} -- -I./include -std=c++20 \;
```

## Working with ORM+Migration.

### ORM:

After creating the database or model, it is necessary to generate the auxiliary ODB files with the command `odb --std c++20 -d pgsql --generate-query -o odb-gen <model header file>` from the folder `src/data/models`.

After executing the command, files will be created or updated in the folder `src/data/models/odb-gen'. Please do not modify or transfer these files for the correct operation of the application.

### Migrations:

The alembic tool is used to work with migrations. To work with it, you need to modify or create a python model according to the cpp version of the model.

- Create/change python model according declared cpp model.
- Change terminal workspace to `src/data`.
- Use the alembic command `alembic revision --autogenerate -m '<name of migration>'` for create new migration to database.
- If its needed upgrade local database with latest migration with commnd `alembic upgrade head`.