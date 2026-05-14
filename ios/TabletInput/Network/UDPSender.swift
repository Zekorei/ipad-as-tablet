//
//  UDPSender.swift
//  ipad-as-tablet
//
//  Created by bill on 2026-05-13.
//

import Foundation
import Network

final class UDPSender: TransportClient {
    
    private let connection: NWConnection
    
    init(host: String, port: UInt16) {
        let nwHost = NWEndpoint.Host(host)
        let nwPort = NWEndpoint.Port(rawValue: port)!
        
        connection = NWConnection(
            host: nwHost,
            port: nwPort,
            using: .udp
        )
        
        connection.start(queue: .global())
        print("Connected to: \(host):\(port)")
    }
    
    convenience init(endpoint: Endpoint) {
        self.init(
            host: endpoint.host,
            port: endpoint.port
        )
    }
    
    func send(_ data: Data) {
//        PacketLogger.logBytes(data)
        
        connection.send(
            content: data,
            completion: .contentProcessed { error in
                if let error {
                    print("UDP send error:", error)
                }
            }
        )
    }
}
