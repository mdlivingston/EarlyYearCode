//
//  TabBarController.swift
//  FBMessenger
//
//  Created by Max Livingston on 8/15/17.
//  Copyright © 2017 Max Livingston. All rights reserved.
//

import UIKit

class TabBarController: UITabBarController {
    //Create bottom tab buttons on friends page
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let layout = UICollectionViewFlowLayout()
        let friendsController = FriendsController(collectionViewLayout: layout)
        let recentMessagesNavController = UINavigationController(rootViewController: friendsController)
        recentMessagesNavController.tabBarItem.title = "Recent"
        recentMessagesNavController.tabBarItem.image = UIImage(named: "clock")
        viewControllers = [recentMessagesNavController, createDummyNacController(title: "Calls", imageName: "phone"), createDummyNacController(title: "Groups", imageName: "drama"),createDummyNacController(title: "People", imageName: "man"),createDummyNacController(title: "Settings", imageName: "gear") ]
    }
    
    private func createDummyNacController(title: String, imageName: String) -> UINavigationController {
        
        let viewController = UIViewController()
        let navController = UINavigationController(rootViewController: viewController)
        navController.tabBarItem.title = title
        navController.tabBarItem.image = UIImage(named: imageName)
        
        return navController
    }
}

