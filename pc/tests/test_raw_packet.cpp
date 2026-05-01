#include"shared/protocol.h"

#include<catch2/catch_test_macros.hpp>

#include<cstddef>

TEST_CASE("layout_is_packed_tightly", "[raw_packet]") {
    REQUIRE(offsetof(Protocol::RawPacket, x) == 0);
    REQUIRE(offsetof(Protocol::RawPacket, y) == 4);
    REQUIRE(offsetof(Protocol::RawPacket, pressure) == 8);
    REQUIRE(offsetof(Protocol::RawPacket, flags) == 12);
    REQUIRE(offsetof(Protocol::RawPacket, timestamp) == 16);
}
