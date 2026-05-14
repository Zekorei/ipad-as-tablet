//
//  ipad_as_tabletApp.swift
//  ipad-as-tablet
//
//  Created by bill on 2026-05-13.
//

import SwiftUI

@main
struct ipad_as_tabletApp: App {
    private let discovery =
        BonjourDiscoveryService()
    
    init() {
        discovery.start()
    }
    
    var body: some Scene {
        WindowGroup {
            ContentView()
        }
    }
}
