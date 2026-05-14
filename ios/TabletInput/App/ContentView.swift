//
//  ContentView.swift
//  ipad-as-tablet
//
//  Created by bill on 2026-05-13.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        CanvasViewRepresentable()
            .ignoresSafeArea()
    }
}

#Preview {
    ContentView()
}
