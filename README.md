# StoreLibrary
After cloning the repository, use the .sln file to open it in VS. I used VS 2022.
All dependencies should pull up.

DatabaseStorage - we store the database in memory. A thread-safe singleton was created.
Main functions - add item, update item, delete item, get stored items.
DatabaseStorage doesn't update the .json, it only updates the in_memory data.
DatabaseStorage is thread safe.

DatabaseWorker is a very simple scheduler which updates .json data every 100ms.
Reads the data in memory, and updates the .json with new data. Runs in a separate, detached thread.
Products.h - interface for .dll. 
Purchase - working directly with the purchase of goods, printing a receipt.
StoreItem - 1 object of our store + methods-assistants for reading/writing into json.

So far everything is built for Windows for all configurations.
As for cmake - unfortunately I'm not an expert in it, as I said, I used to fix some parts in CMake, but I've never written full projects in it.
So for now everything is set up in Visual Studio, json library is a Git's submodule.

If I still have some time, I can figure out Cmake and remember what needs to be finished.

In terms of time it took a whole day to complete.
The project is not complicated, but it is very cumbersome.
And of course that's possible to spend weeeks to implement everything
