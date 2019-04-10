//
//  FriendsControllerHelper.swift
//  FBMessenger
//
//  Created by Max Livingston on 8/14/17.
//  Copyright © 2017 Max Livingston. All rights reserved.
//

import UIKit
import CoreData

extension FriendsController {
    
    //Clears duplicate data
       func clearData() {
        
        let delegate = UIApplication.shared.delegate as? AppDelegate
        if let context = delegate?.persistentContainer.viewContext {
            do{
                let entityNames = ["Friend", "Message"]
                
                for entityName in entityNames {
                    let fetchRequest = NSFetchRequest<NSFetchRequestResult>(entityName: entityName)
                    
                    let objects = try(context.fetch(fetchRequest)) as? [NSManagedObject]
                    
                    for object in objects! {
                        context.delete(object)
                    }
                }
                try(context.save())
            }
            catch let err {
                print(err)
            }
        }
    }
    
    //Creates Friends
    func setupData() {
        
        clearData()
        
        let delegate = UIApplication.shared.delegate as? AppDelegate
        if let context = delegate?.persistentContainer.viewContext {
    
            createRussMessagesWithContext(context: context)
            
            let mac = NSEntityDescription.insertNewObject(forEntityName: "Friend", into: context) as! Friend
            mac.name = "Maclane May"
            mac.profileImageName = "MacPic"
            
            FriendsController.createMessageWithText(text: "You boolin'?", friend: mac, minutesAgo: 5, context: context)
            
            let ellie = NSEntityDescription.insertNewObject(forEntityName: "Friend", into: context) as! Friend
            ellie.name = "Ellie Wright"
            ellie.profileImageName = "ElliePic"

            FriendsController.createMessageWithText(text: "I love you!", friend: ellie, minutesAgo: 60 * 24, context: context)
            
            
            let leah = NSEntityDescription.insertNewObject(forEntityName: "Friend", into: context) as! Friend
            leah.name = "Leah"
            leah.profileImageName = "LeahPic"
            
            FriendsController.createMessageWithText(text: "Hehe", friend: leah, minutesAgo: 8 * 60 * 24, context: context)

            
            do{
                try(context.save())
            }
            catch let err {
                print(err)
            }
        }
    }
    
    //Creates response friend chat
    private func createRussMessagesWithContext(context: NSManagedObjectContext) {
        let russ = NSEntityDescription.insertNewObject(forEntityName: "Friend", into: context) as! Friend
        russ.name = "Russell Pendley"
        russ.profileImageName = "RussPic"
        
        FriendsController.createMessageWithText(text: "Good Morning.", friend: russ, minutesAgo: 3, context: context)
        FriendsController.createMessageWithText(text: "Hello how are you? Hope you are having a good morning!", friend: russ, minutesAgo: 2, context: context)
        FriendsController.createMessageWithText(text: "Pick up your phone! This is only a test. Please calm down. It is not a big deal at all. Please be on your guard at all times for the enemy is vigilant and ruthless.", friend: russ, minutesAgo: 1, context: context)

        //response messages 
        FriendsController.createMessageWithText(text: "I tried calling you back, bruh!", friend: russ, minutesAgo: 1, context: context, isSender: true)
        
        FriendsController.createMessageWithText(text: "Totally understand tyou want the Iphone 7 but you'll have to wait until September for the new release. Sorry that's just how apple likes to do things!", friend: russ, minutesAgo: 1, context: context)
        
        FriendsController.createMessageWithText(text: "You're weird...", friend: russ, minutesAgo: 1, context: context, isSender: true)

    }
    
    //Create message function
    static func createMessageWithText(text: String, friend: Friend, minutesAgo: Double, context: NSManagedObjectContext, isSender: Bool = false) {
        let message = NSEntityDescription.insertNewObject(forEntityName: "Message", into: context) as! Message
        message.date = NSDate().addingTimeInterval(-minutesAgo * 60)
        message.friend = friend
        message.text = text
        message.isSender = NSNumber(booleanLiteral: isSender) as! Bool
        
        friend.lastMessage = message
    }
}
