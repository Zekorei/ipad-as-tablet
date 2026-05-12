import SwiftUI
import UIKit

struct CanvasViewRepresentable: UIViewRepresetable {
    func makeUIView(context: context) -> TouchView {
        TouchView()
    }

    func updateUIView(_ uiView: TouchView, context: context) {}
}

final class TouchView: UIView {

    override init(frame: CGRect) {
        super.init(frame: frame)
        backgroundColor = .black
    }

    required init?(coder: NSCoder) {
        fatalError()
    }

    override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        guard let t = touches.first else { return }
        let p = t.location(in: self)

        print("x:", p.x, "y:", p.y)
    }
}
