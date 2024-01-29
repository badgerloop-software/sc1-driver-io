# Solar Car 1 Driver IO Program

## Solar Car Dashboard

### Libraries/Frameworks

- [Qt](https://www.qt.io/) - Development framework
- [RapidJSON](https://rapidjson.org/) - JSON parsing library

### Cloning the Data Format Repository and Initializing the Submodule

0. If you don't already have an SSH key, [generate a new SSH key](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent) (only the steps under "Generating a new SSH key" are required) and [add it to your GitHub account](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account).
1. Once you have an SSH key, clone the [sc1-data-format repository](https://github.com/badgerloop-software/sc1-data-format) to your computer. Make sure to clone it using SSH (when you go to copy the clone link, there will be an SSH option above the link).
2. Next, `cd` into the `sc1-driver-io` repository and run `git submodule update --init`.

### Running with CMake

CMake is a more popular project make system, it allows you to edit the project with your ide of choice and enables features like autocomplete while not bounded to using qtcreator.

0. If you are using windows, install Ubuntu via WSL, you can use any other distribution if you're experienced with linux.
1. Ensure you have cmake and build-essentials installed you can do so by `sudo apt install build-essential cmake`
2. Install qt packages with `sudo apt install qt5-doc qtbase5-examples qtbase5-doc-html qtdeclarative5-dev qml-module-qtquick-controls2`
3. `cd`into your project directory and `mkdir build` to create a new build folder then `cd build`
4. Run `cmake ..` to generate make file for the project, then run `make` to compile the project.
5. To execute the program run `./solar-car-dashboard`.

### Contributing to the Dashboard

0. Again, make sure you have [Qt](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5) installed on your computer.
1. Clone the repository to your computer (see steps 0-1 of "Cloning the Data Format Repository and Initializing the Submodule" for instructions on cloning a repo using SSH).
2. If you have not already, clone the `sc1-data-format` repository and initialize the submodule (see instructions above).
3. Open the repository in Qt Creator and, if necessary, configure the project using the appropriate kit for your environment.
4. Run `git submodule update --remote` to update necessary submodules. You should also do this any time the submodule might have changed (i.e. whenever the [data format](https://github.com/badgerloop-software/sc1-data-format/blob/main/format.json) has been modified).
   1. To avoid pushing changes that use obsolete data, update the submodule before you `git push` your changes. If there are changes to the data format, run the dashboard to make sure your code still works.
5. To run the dashboard on your computer, simply press the green arrow in the bottom-left corner of the Qt Creator window. To run the project on a Raspberry Pi, see "Compiling and Running the Project on a Rapberry Pi" below.
6. Once you have finished making your necessary changes to your code, switch to a new branch that has a good name for the feature or names the Jira issue (e.g. `SW-23/skeleton`).
7. Commit related changes to that branch and push to this repository. (Do this often so that it is easy to finely revert to a previous state!)
   1. When committing and pushing changes, do not add your solar-car-dashboard.pro.user file to the version control, as this is specific to your computer.
8. Once you are happy with the state of your code, open a pull request and request someone to conduct a code review. It may be kicked back with some suggestions or edits, but when it is accepted, it will be merged with `main`. Congrats! Now it's just time to rinse and repeat.

### Compiling and Running the Project on a Rapberry Pi

0. If running the project on the driver IO board, skip this step, as the necessary dependencies have already been installed on it. Otherwise, if you have not already, install the dependencies on the Raspberry Pi:
   ```
   sudo apt-get install build-essential
   sudo apt-get install qt5-doc qtbase5-examples qtbase5-doc-html qtdeclarative5-dev qml-module-qtquick-controls2
   ```
1. Copy the project to the Raspberry Pi.
2. Make and run the project on the Raspberry Pi by running the following commands:
   ```
   qmake solar-car-dashboard.pro
   make
   ./solar-car-dashboard
   ```
