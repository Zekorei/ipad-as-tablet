//
//  PacketLogger.swift
//  ipad-as-tablet
//
//  Created by bill on 2026-05-13.
//

import Foundation

struct PacketLogger {
    
    static func log(_ packet: RawPacket) {
        print(
            "SEND | x:", packet.x,
            "y:", packet.y,
            "p:", packet.pressure,
            "f:", packet.flags,
            "t:", packet.timestamp
        )
    }
    
    static func logBytes(_ data: Data) {
        let preview = data.prefix(24).map { String(format: "%02x", $0) }.joined(separator: " ")
        
        print("BYTES |", preview)
    }
}
