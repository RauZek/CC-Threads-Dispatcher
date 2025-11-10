#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "ibase_thread.h"
#include "dispatcher.h"

using cc_threads::Dispatcher;
using cc_threads::IBaseThread;

static int ValidateArgs(int argc, char** argv,
                        const std::vector<uint32_t>& supported_msgs,
                        std::vector<uint32_t>* out_valid_msgs) {
    for (int i = 1; i < argc; i++) {
        uint32_t msg_id = 0;

        try {
            msg_id = std::stoul(argv[i]);
        } catch (const std::exception& e) {
            std::cerr << "[APP] [ERROR] Invalid input argument: " << argv[i]
                      << std::endl;

            return -1;
        }

        if (msg_id == 0) {
            std::cerr << "[APP] [ERROR] The message '0' is reserved for "
                         "internal use.\n";

            return -1;
        }

        auto iterator =
            std::find(supported_msgs.begin(), supported_msgs.end(), msg_id);

        if (iterator == supported_msgs.end()) {
            std::cerr << "[APP] [ERROR] Unsupported message: " << msg_id
                      << std::endl;

            return -1;
        }
        out_valid_msgs->push_back(msg_id);
    }

    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "The usage is: " << argv[0] << " <msg1> [msg2] [...] \n";

        return 1;
    }

    std::unique_ptr<IBaseThread> dispatcher;

    try {
        dispatcher = std::make_unique<Dispatcher>();

    } catch (const std::exception& e) {
        std::cerr << "[APP] [FATAL] Failed to initialize dispatcher: "
                  << e.what() << std::endl;

        return 1;
    }

    const std::vector<uint32_t>& supported_msgs_dispatcher =
        dispatcher->GetSupportedMsg();

    std::cout << "[APP] [INFO] The dispatcher supports: "
              << supported_msgs_dispatcher.size() << " unique messages.\n";

    std::vector<uint32_t> valid_msgs_to_send;
    if (ValidateArgs(argc, argv, supported_msgs_dispatcher,
                     &valid_msgs_to_send) != 0) {
        std::cerr << "[APP] [FATAL] Invalid arguments detected. Exiting."
                  << std::endl;
        return 1;
    }

    std::cout << "[APP] [INFO] Sending " << valid_msgs_to_send.size()
              << " messages..." << std::endl;
    for (uint32_t msg_id : valid_msgs_to_send) {
        std::cout << "[APP] [INFO] Sending message: " << msg_id << std::endl;
        dispatcher->SendMsg(msg_id);
    }

    std::cout << "[APP] [INFO] All messages sent. Shutting down." << std::endl;

    return 0;
}
