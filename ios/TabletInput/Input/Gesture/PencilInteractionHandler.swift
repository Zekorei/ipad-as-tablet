//
//  Gesture.swift
//  ipad-as-tablet
//
//  Created by bill on 2026-05-17.
//

import UIKit

final class PencilInteractionHandler: NSObject, UIPencilInteractionDelegate {
    
    private let modeController: InputModeController
    
    init(modeController: InputModeController) {
        self.modeController = modeController
    }
    
    func pencilInteractionDidTap(_ interaction: UIPencilInteraction) {
        modeController.toggleMode()
    }
}
