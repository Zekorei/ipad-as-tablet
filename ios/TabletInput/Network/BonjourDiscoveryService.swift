//
//  BonjourDiscoveryService.swift
//  ipad-as-tablet
//
//  Created by bill on 2026-05-13.
//

import Foundation
import Network

final class BonjourDiscoveryService {
    private var browser: NWBrowser?
    
    func start() {
        let parameters = NWParameters()
        
        let browser = NWBrowser(
            for: .bonjour(
                type: "_tabletinput._udp",
                domain: nil
            ),
            using: parameters
        )
        
        self.browser = browser
        
        browser.stateUpdateHandler = { state in
            switch state {
            case .ready:
                print("Bonjour browser ready")
            case .failed(let error):
                print("Bonjour browser failed:", error)
            default:
                break
            }
        }
        
        browser.browseResultsChangedHandler = {
            results, changes in
            
            for result in results {
                switch result.endpoint {
                case let .service(
                    name,
                    type,
                    domain,
                    interface
                ):
                    print("Found service:")
                    print("name:", name)
                    print("type:", type)
                    print("domain:", domain)
                    
                    if let interface {
                        print("interface:", interface.debugDescription)
                    }
                default:
                    break
                }
            }
        }
        
        browser.start(queue: .main)
    }
    
    func stop() {
        browser?.cancel()
        browser = nil
    }
}
