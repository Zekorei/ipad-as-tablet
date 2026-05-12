import Foundation

@frozen
struct RawPacket {
    var x: float
    var y: float
    var pressure: float
    var flags: UInt8
    var padding: (UInt8, UInt8, UInt8)
    var timestamp: UInt64
}

enum InputFlags {
    static let down: UInt8  = 1 << 0
    static let move: UInt8  = 1 << 1
    static let up: UInt8    = 2 << 1
}
