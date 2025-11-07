# CC-Threads-Dispatcher

- Language Standard: C++ 17
- Build System: CMake
- Platform: Linux (tested with GCC, -Wall -Wextra -Werror -Wpedantic)

# 1. Project Overview
This project implements a modular, object-oriented, threaded message dispatching system in C++. It consists of:

- A static library (base_thread) providing an abstract base class for threading, using RAII for the program's resources lifecycle management.

- Two shared libraries (simple_process, advanced_process) that implement the base class to provide concrete message handling.

- A shared library (dispatcher) that inherits from the base class and dynamically loads, queries, and routes messages to the process libraries.

- A test application that links only to the dispatcher and uses it to validate and send messages from CLI arguments.

The solution uses C++ inheritance, virtual functions, and RAII to ensure separation of concerns and a clean, safe shutdown.

# 2. Workspace Layout
The project uses a clean, multi-directory CMake layout:

cc_threads/
- test.sh
- cmake_helper.sh
- CMakeLists.txt          
- base_thread/
- simple_process/
- advanced_process/
- dispatcher/
- app/

# 3. Base Thread Library (base_thread)
Library Type: Static (libcc_base_thread.a)

Responsibilities: 
- Provides a generic, object-oriented, thread-safe message-passing framework.

Implementation:
- IBaseThread (Interface): A virtual interface defining the public POV for the user: using SendMsg() and GetSupportedMsg().

- BaseThread (Abstract Class): Implements the IBaseThread interface.

- Constructor: Spawns a std::thread, which immediately begins executing the private Loop() method.

- Destructor: Automatically handles thread shutdown.

- SendMsg(): A thread-safe method that pushes a uint32_t message onto a private Thread_Safe_Queue.

- Loop(): A private function that runs on its own thread and it waits for incoming messages.

- Process(): A virtual function that is called by Loop(). This will be implemented by all derived classes (Simple Proces, Advanced Process and Dispatcher).

# 4. Simple Process Library (simple_process)
Library Type: Shared (libcc_simple_process.so)

Message Range: 10–20 and 50–60 (inclusive).

Implementation:
- SimpleProcess (Class): Which inherits from BaseThread.

- Constructor: Populates its internal supported_msgs_ vector with its message ranges.

- Process() (Override): Implements the virtual Process() function. It validates the incoming message ID and logs it.

- Factory Function: Exports a C-mangled function (extern "C" IBaseThread* Create()) that the Dispatcher can find using dlsym.

# 5. Advanced Process Library (advanced_process)
Library Type: Shared (libcc_advanced_process.so)

Message Range: 30–40 and 50–60 (inclusive).

Implementation:
- Identical in structure to SimpleProcess, but implements its own message ranges.

# 6. Dispatcher Library (dispatcher)
Library Type: Shared (libcc_dispatcher.so)

Responsibilities:
- Acts as the central router and the concrete BaseThread implementation.

Implementation:
- Dispatcher (Class): Inherits from BaseThread.

Constructor:
- Dynamically loads libcc_simple_process.so and libcc_advanced_process.so using dlopen.
- Finds their Create() factory functions using dlsym.
- Calls Create() to instantiate Simple_Process and Advanced_Process, storing them in std::unique_ptrs for automatic memory management (RAII).
- Calls GetSupportedMsg() on both process instances.
- Builds a master routing table to map message IDs to the processes that handle them.
- Builds a merged, unique std::vector of all 33 supported messages for the test app.
- Process() (Override): Implements its own Process() function. When its Loop() receives a message, this function looks up the message in the routing table and calls SendMsg() on the corresponding process/es.
- Correctly routes messages in the 50-60 range to both libraries.

# 7. Test Application (app)
Executable Name: app

Responsibilities:
- Links dynamically only with the dispatcher library (libcc_dispatcher.so).
- Instantiates the Dispatcher within a std::unique_ptr<IBaseThread> and a try catch block to handle any dlopen or dlsym failures eventually.
- Calls dispatcher->GetSupportedMsg() to get the merged 33-message set.
- Parses all CLI arguments.
- Validates each argument against the supported set. If an unsupported message (or 0) is found, it prints an error and exits with a non-zero code.
- For all valid messages, calls dispatcher->SendMsg().
- After the last message is sent, main() simply exits.

# 8. End Condition (RAII)
The end condition is handled automatically via RAII (Resource Acquisition Is Initialization).

- When main() exits (either normally or via an occured error), the std::unique_ptr managing the Dispatcher is destroyed.
- This triggers the Dispatcher's destructor, which in turn triggers the destructors of the Simple_Process and Advanced_Process unique_ptrs.
- The BaseThread destructor in each class is called.

# 9. Testing
A shell script (test.sh) is impplemented to stress-test the application. It runs the app 10000 times, each time with a large, random set of CLI arguments (both valid and invalid) to verify correct handling and shutdown of all the resources connected to the program.

# 10. CMake Setup
The root CMakeLists.txt encapsulates the build using add_subdirectory() for each component.
Modern CMake is used (target_link_libraries, target_include_directories) to manage dependencies.
