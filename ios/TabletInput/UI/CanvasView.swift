//
//  CanvasView.swift
//  ipad-as-tablet
//
//  Created by bill on 2026-05-13.
//

import SwiftUI
import UIKit

struct CanvasViewRepresentable: UIViewRepresentable {
    
    func makeUIView(context: Context) -> TouchView {
        TouchView()
    }
    
    func updateUIView(_ uiView: TouchView, context: Context) {}
}

final class TouchView: UIView {
    
    private let sender = UDPSender(
        host: "192.168.2.21",
        port: 5000
    )
    
    override init(frame: CGRect) {1
        super.init(frame: frame)
        
        backgroundColor = .black
    }
    
    required init?(coder: NSCoder) {
        fatalError()
    }
    
    override func touchesBegan(
        _ touches: Set<UITouch>,
        with event: UIEvent?
    ) {
        handle(touches, flags: [.down, .move])
    }
    
    override func touchesMoved(
        _ touches: Set<UITouch>,
        with event: UIEvent?
    ) {
        handle(touches, flags: InputFlags.move)
    }
    
    override func touchesEnded(
        _ touches: Set<UITouch>,
        with event: UIEvent?
    ) {
        handle(touches, flags: InputFlags.up)
    }
    
    override func touchesCancelled(
        _ touches: Set<UITouch>,
        with event: UIEvent?
    ) {
        handle(touches, flags: InputFlags.up)
    }
    
    private func handle(
        _ touches: Set<UITouch>,
        flags: InputFlags
    ) {
        guard let touch = touches.first else { return }
        
        let point = touch.location(in: self)
        
        let pressure: Float
        if touch.type == .pencil {
            pressure = Float(touch.force / touch.maximumPossibleForce)
        } else {
            pressure = 1.0
        }
        
        var packet = RawPacket(
            x: Float(point.x / self.bounds.width),
            y: Float(point.y / self.bounds.height),
            pressure: pressure,
            flags: flags.rawValue,
            padding: (0, 0, 0),
            timestamp: UInt64(ProcessInfo.processInfo.systemUptime * 1000)
        )
        
//        PacketLogger.log(packet)
        
        let data = withUnsafeBytes(of: &packet) { Data($0) }
        
        sender.send(data)
    }
}
