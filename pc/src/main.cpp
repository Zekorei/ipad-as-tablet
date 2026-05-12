#include<iostream>

#include"transport/udp_receiver.h"
#include"transport/packet_adapter.h"

#include"pipeline/input_pipeline.h"

#include"output/mouse_controller.h"

#include"types/screen_info.h"
#include"config/pipeline_config.h"

#pragma comment(lib, "ws2_32.lib")

/// @brief UDP port number
constexpr int PORT = 5000;

int main() {
    try {
        // Configs
        Common::ScreenInfo screenInfo;
        Config::PipelineConfig config;


        // Build modules
        Input::Transport::UDPReceiver receiver{PORT};
        Input::Transport::PacketAdapter adapter{};
        Pipeline::InputPipeline mapper{config, screenInfo};
        Output::MouseController mouse{};

        // Main loop
        while (true) {
            auto raw_packet = receiver.receive();
            auto potential_packet = adapter.convert(raw_packet);

            if (!potential_packet) {
                continue;
            } else {
                auto packet = potential_packet.value();
                auto point = mapper.process({ packet.x, packet.y });
                mouse.handle(packet, point);
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Fatal error: "
                  << ex.what()
                  << '\n';

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
