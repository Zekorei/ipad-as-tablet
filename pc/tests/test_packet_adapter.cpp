#include"transport/packet_adapter.h"
#include"protocol.h"

#include<catch2/catch_test_macros.hpp>
#include"utils/test_utils.h"

using namespace Input::Transport;

TEST_CASE("valid_packet", "[adapter]") {
    PacketAdapter adapter;

    Protocol::RawPacket raw {
        0.5f, 0.6f,
        0.8f,
        1u,
        123.0
    };

    auto packet = adapter.convert(raw);

    REQUIRE(packet.has_value());
    REQUIRE(packet->x == 0.5f);
    REQUIRE(packet->y == 0.6f);
    REQUIRE(packet->pressure == 0.8f);
    REQUIRE(packet->flags == 1u);
    REQUIRE(packet->timestamp == 123.0);
}

TEST_CASE("NaN_is_rejected", "[adapter]") {
    PacketAdapter adapter;

    Protocol::RawPacket raw {
        NAN, 0.6f,
        0.8f,
        1u,
        123.0
    };

    auto packet = adapter.convert(raw);

    REQUIRE_FALSE(packet.has_value());
}

TEST_CASE("non_finite_is_rejected", "[adapter]") {
    PacketAdapter adapter;

    Protocol::RawPacket raw {
        0.5f, INFINITY,
        0.8f,
        1u,
        123.0
    };

    auto packet = adapter.convert(raw);

    REQUIRE_FALSE(packet.has_value());
}

TEST_CASE("pressure_bounds", "[adapter]") {
    PacketAdapter adapter;

    Protocol::RawPacket raw {
        0.5f, 0.6f,
        1.1f,
        1u,
        123.0
    };

    auto packet = adapter.convert(raw);

    REQUIRE(packet.has_value());
}

TEST_CASE("coordinates_are_unclamped", "[adapter]") {
    PacketAdapter adapter;

    Protocol::RawPacket raw {
        -0.2f, 1.6f,
        1.1f,
        1u,
        123.0
    };

    auto packet = adapter.convert(raw);

    REQUIRE(packet.has_value());
    REQUIRE(packet->x == -0.2f);
    REQUIRE(packet->y == 1.6f);
}

TEST_CASE("flags_are_preserved", "[adapter]") {
    PacketAdapter adapter;

    Protocol::RawPacket raw {
        0.5f, 0.6f,
        1.1f,
        0xABCD1234u,
        123.0
    };

    auto packet = adapter.convert(raw);

    REQUIRE(packet.has_value());
    REQUIRE(packet->flags == 0xABCD1234u);
}
