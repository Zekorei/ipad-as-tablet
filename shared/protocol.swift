struct RawPacket {
    var x: Float
    var y: Float
    var pressure: Float
    var flags: UInt8
    var padding: (UInt8, UInt8, UInt8)
    var timestamp: UInt64
}

struct InputFlags: OptionSet {
    let rawValue: UInt8
    
    static let down = InputFlags(rawValue: 1 << 0)
    static let move = InputFlags(rawValue: 1 << 1)
    static let up   = InputFlags(rawValue: 1 << 2)
}
