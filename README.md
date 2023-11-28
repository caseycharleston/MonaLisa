# Using the Server

### Running the Server
In your terminal, starting from the repo folder root, run the following:
```bash
cd Server
dotnet build
dotnet run
```
This will start the server. If it throws an error due to a .NET version mismatch, simply open up Server/Server.csproj and edit the "net7.0" to your version of .NET.

### Running the Unity Client
The code to connect to the server is already written within the `Controller.cs` file. To get the UnityRobotHead project into unity, do the following:
1. Open the UnityRobotHead folder in the repo as a unity project
2. Once it opens, navigate to `Scenes` and open the `b2b` scene (this contains the necessary objects and code).
3. Press start to run the project. It may freeze up due to the Update() function in Controller constantly calling TestServer() by default which stalls the program to ask for messages from the server.

### Testing the current Scheme
To test that everything is working properly, a test file is provided in the `cpp` folder. In your terminal, starting from the repo folder root, do the following:
```bash
cd cpp/build
cmake ..
make
./test
```
This will run the testing file. It will prompt your terminal for a 'y' to send a message and a 'n' to terminate the program. While sending in a 'y', have the unity head client connected to the server as well.
The server should send in the message from the test file to the Unity project, making the eyes change position (feel free to edit the default values in test.cpp for better clarity).

### Editing the Send/Receive Scheme
Within `server.cs` is the HandleClient() function. This function is put onto a thread every time a client is connected to the server. See the example code in this file to get a better idea of how to execute different
code for different clients (if that is necessary for your implementation).
