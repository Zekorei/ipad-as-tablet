//
//  TransportClient.swift
//  ipad-as-tablet
//
//  Created by bill on 2026-05-13.
//

import Foundation

protocol TransportClient {
    func send(_ data: Data)
}
