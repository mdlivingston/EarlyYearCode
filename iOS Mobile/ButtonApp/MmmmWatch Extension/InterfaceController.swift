//
//  InterfaceController.swift
//  MmmmWatch Extension
//
//  Created by Max Livingston on 8/14/17.
//  Copyright © 2017 Max Livingston. All rights reserved.
//

import WatchKit
import Foundation
import AVFoundation


class InterfaceController: WKInterfaceController {

    var player : AVAudioPlayer?
    var player2 : AVAudioPlayer?
    var player3 : AVAudioPlayer?
    var player4 : AVAudioPlayer?
    var player5 : AVAudioPlayer?
    var player6 : AVAudioPlayer?
    var player7 : AVAudioPlayer?

    override func awake(withContext context: Any?) {
        super.awake(withContext: context)
        
        // Configure interface objects here.
    }
    @IBAction func grey() {
        let path = Bundle.main.path(forResource: "Grey", ofType:"m4a")!
        let url = URL(fileURLWithPath: path)
        
        do {
            let sound = try AVAudioPlayer(contentsOf: url)
            self.player7 = sound
            sound.numberOfLoops = 0
            sound.prepareToPlay()
            sound.play()
        } catch {
            print("error loading file")
        }

    }
    @IBAction func mac() {
        let path = Bundle.main.path(forResource: "Mac", ofType:"m4a")!
        let url = URL(fileURLWithPath: path)
        
        do {
            let sound = try AVAudioPlayer(contentsOf: url)
            self.player3 = sound
            sound.numberOfLoops = 0
            sound.prepareToPlay()
            sound.play()
        } catch {
            print("error loading file")
        }

    }
    @IBAction func russ() {
        let path = Bundle.main.path(forResource: "Russ", ofType:"m4a")!
        let url = URL(fileURLWithPath: path)
        
        do {
            let sound = try AVAudioPlayer(contentsOf: url)
            self.player4 = sound
            sound.numberOfLoops = 0
            sound.prepareToPlay()
            sound.play()
        } catch {
            print("error loading file")
        }

    }
    @IBAction func leah() {
        let path = Bundle.main.path(forResource: "Leah", ofType:"m4a")!
        let url = URL(fileURLWithPath: path)
        
        do {
            let sound = try AVAudioPlayer(contentsOf: url)
            self.player5 = sound
            sound.numberOfLoops = 0
            sound.prepareToPlay()
            sound.play()
        } catch {
            print("error loading file")
        }

    }
    @IBAction func chattanooga() {
        let path = Bundle.main.path(forResource: "Chattanooga", ofType:"m4a")!
        let url = URL(fileURLWithPath: path)
        
        do {
            let sound = try AVAudioPlayer(contentsOf: url)
            self.player6 = sound
            sound.numberOfLoops = 0
            sound.prepareToPlay()
            sound.play()
        } catch {
            print("error loading file")
        }

    }
    
    @IBAction func ellie() {
        let path = Bundle.main.path(forResource: "Ellie", ofType:"m4a")!
        let url = URL(fileURLWithPath: path)
        
        do {
            let sound = try AVAudioPlayer(contentsOf: url)
            self.player = sound
            sound.numberOfLoops = 0
            sound.prepareToPlay()
            sound.play()
        } catch {
            print("error loading file")
        }

    }
    
    @IBAction func max(_ sender: Any) {
        let path = Bundle.main.path(forResource: "Max", ofType:"m4a")!
        let url = URL(fileURLWithPath: path)
        
        do {
            let sound = try AVAudioPlayer(contentsOf: url)
            self.player2 = sound
            sound.numberOfLoops = 0
            sound.prepareToPlay()
            sound.play()
        } catch {
            print("error loading file")
        }

    }
    override func willActivate() {
        // This method is called when watch view controller is about to be visible to user
        super.willActivate()
    }
    
    override func didDeactivate() {
        // This method is called when watch view controller is no longer visible
        super.didDeactivate()
    }
    
}
