//
//  ViewController.swift
//  ButtonApp
//
//  Created by Max Livingston on 4/10/17.
//  Copyright © 2017 Max Livingston. All rights reserved.
//

import UIKit
import AVFoundation

class ViewController: UIViewController {
    var player : AVAudioPlayer?
    var player2 : AVAudioPlayer?
    var player3 : AVAudioPlayer?
    var player4 : AVAudioPlayer?
    var player5 : AVAudioPlayer?
    var player6 : AVAudioPlayer?
    var player7 : AVAudioPlayer?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        try! AVAudioSession.sharedInstance().setCategory(AVAudioSessionCategoryAmbient)
        // Do any additional setup after loading the view, typically from a nib.
    }
       override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    @IBAction func Chattanooga(_ sender: Any) {
        let path = Bundle.main.path(forResource: "Chattanooga", ofType:"m4a")!
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
    @IBAction func russ(_ sender: Any) {
        let path = Bundle.main.path(forResource: "Russ", ofType:"m4a")!
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
    
    @IBAction func ellie(_ sender: Any) {
        let path2 = Bundle.main.path(forResource: "Ellie", ofType:"m4a")!
        let url2 = URL(fileURLWithPath: path2)
        
        do {
            let sound = try AVAudioPlayer(contentsOf: url2)
            self.player3 = sound
            sound.numberOfLoops = 0
            sound.prepareToPlay()
            sound.play()
        } catch {
            print("error loading file")
        }

    }
    
    @IBAction func grey(_ sender: Any) {
        let path2 = Bundle.main.path(forResource: "Grey", ofType:"m4a")!
        let url2 = URL(fileURLWithPath: path2)
        
        do {
            let sound = try AVAudioPlayer(contentsOf: url2)
            self.player4 = sound
            sound.numberOfLoops = 0
            sound.prepareToPlay()
            sound.play()
        } catch {
            print("error loading file")
        }

    }
    @IBAction func mac(_ sender: Any) {
        let path2 = Bundle.main.path(forResource: "Mac", ofType:"m4a")!
        let url2 = URL(fileURLWithPath: path2)
        
        do {
            let sound = try AVAudioPlayer(contentsOf: url2)
            self.player5 = sound
            sound.numberOfLoops = 0
            sound.prepareToPlay()
            sound.play()
        } catch {
            print("error loading file")
        }

    }
    @IBAction func leah(_ sender: Any) {
        let path2 = Bundle.main.path(forResource: "Leah", ofType:"m4a")!
        let url2 = URL(fileURLWithPath: path2)
        
        do {
            let sound = try AVAudioPlayer(contentsOf: url2)
            self.player6 = sound
            sound.numberOfLoops = 0
            sound.prepareToPlay()
            sound.play()
        } catch {
            print("error loading file")
        }

    }
    
}

