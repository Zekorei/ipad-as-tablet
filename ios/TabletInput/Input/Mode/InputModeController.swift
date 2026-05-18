//
//  InputModeController.swift
//  ipad-as-tablet
//
//  Created by bill on 2026-05-17.
//

import Foundation

final class InputModeController: ObservableObject {
    
    @Published
    private(set) var mode: InputMode = .writing
    
    func toggleMode() {
        mode = (mode == .writing) ? .movement : .writing
        print("[mode] switched to \(mode)")
    }
    
    var isWritingEnabled: Bool {
        mode == .writing
    }
}
