//
//  ViewController.swift
//  FBMessenger
//
//  Created by Max Livingston on 8/10/17.
//  Copyright © 2017 Max Livingston. All rights reserved.
//

import UIKit
import CoreData

class FriendsController: UICollectionViewController, UICollectionViewDelegateFlowLayout, NSFetchedResultsControllerDelegate {
    
    private let cellId = "FriendCell"
    
    lazy var fetchedResultsController: NSFetchedResultsController = { () -> NSFetchedResultsController<NSFetchRequestResult> in
        
        let fetchRequest = NSFetchRequest<NSFetchRequestResult>(entityName: "Friend")
        fetchRequest.sortDescriptors = [NSSortDescriptor.init(key: "lastMessage.date", ascending: false)]
        fetchRequest.predicate = NSPredicate(format: "lastMessage != nil")
        let delegate = UIApplication.shared.delegate as? AppDelegate
        let context = delegate?.persistentContainer.viewContext
        
        let frc = NSFetchedResultsController(fetchRequest: fetchRequest, managedObjectContext: context!, sectionNameKeyPath: nil, cacheName: nil)
        
        frc.delegate = self
        return frc
    }()

    //Add Grey button (Allows two messages to be added at once)
    var blockOperations = [BlockOperation]()
    func controller(_ controller: NSFetchedResultsController<NSFetchRequestResult>, didChange anObject: Any, at indexPath: IndexPath?, for type: NSFetchedResultsChangeType, newIndexPath: IndexPath?) {
        if type == .insert {
            blockOperations.append(BlockOperation(block: {
                self.collectionView?.insertItems(at: [newIndexPath!])
            }))
            
        }
    }
    func controllerDidChangeContent(_ controller: NSFetchedResultsController<NSFetchRequestResult>) {
        collectionView?.performBatchUpdates({
            
            for operation in self.blockOperations {
                operation.start()
            }
        }, completion: {_ in
            let lastItem = (self.fetchedResultsController.sections?[0].numberOfObjects)! - 1
            let indexPath = NSIndexPath(item: lastItem, section: 0)
            self.collectionView?.scrollToItem(at: indexPath as IndexPath, at: .bottom, animated: true)
        })
    }
    
    //Tab bar reappears when backing into friend page
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        tabBarController?.tabBar.isHidden = false
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        navigationItem.title = "Chats"
        collectionView?.backgroundColor = UIColor.white
        collectionView?.alwaysBounceVertical = true
        
        //Registers Nib of friends page
        collectionView?.register(UINib(nibName: "FriendCollectionViewCell", bundle: nil), forCellWithReuseIdentifier: cellId)
        
       
        setupData()
        do{
         try fetchedResultsController.performFetch()
        }
        catch let err {
            print(err)
        }
        
        //Adds Button to top right of friend view
        navigationItem.rightBarButtonItem = UIBarButtonItem(title: "Add Messages", style: .plain, target: self, action: #selector(addGrey))
    }
    
    //Adds two messages from 'Add Messages' button
    func addGrey() {
        
        let delegate = UIApplication.shared.delegate as? AppDelegate
        let context = delegate?.persistentContainer.viewContext

        let grey = NSEntityDescription.insertNewObject(forEntityName: "Friend", into: context!) as! Friend
        grey.name = "Greyson Wright"
        grey.profileImageName = "GreyPic"
        
        FriendsController.createMessageWithText(text: "Hello, my name is Greyson and I write programs.", friend: grey, minutesAgo: 0, context: context! )
        
        let max = NSEntityDescription.insertNewObject(forEntityName: "Friend", into: context!) as! Friend
        max.name = "Max Livingston"
        max.profileImageName = "MaxPic"
        
        FriendsController.createMessageWithText(text: "I program brah.", friend: max, minutesAgo: 0, context: context! )
    }
   
    
    //Returns number of friends
    override func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        guard let count = fetchedResultsController.sections?[0].numberOfObjects else {
            return 0
        }
        return count
    }
    
    override func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell {
        //Grabs cells
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: cellId, for: indexPath) as! FriendCollectionViewCell
        
        //Retrieves last message info
        let friend = fetchedResultsController.object(at: indexPath) as! Friend
        cell.messageLabel.text = friend.lastMessage?.text
        
        //Sets friend data to cells
        cell.setupCell(with: friend.lastMessage!)
        
        //Hides line separator if last friend
        let count = fetchedResultsController.sections?[0].numberOfObjects
        let separatorHidden = indexPath.row < count! - 1
        cell.separator(!separatorHidden)
        
        return cell
    }
    
    //Sets width of the cells
    func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> CGSize {
        return CGSize.init(width: view.frame.width, height: 100)
    }
    
    //Select a chat/friend
    override func collectionView(_ collectionView: UICollectionView, didSelectItemAt indexPath: IndexPath) {
        
        let layout = UICollectionViewFlowLayout()
        
        let controller = ChatLogController(collectionViewLayout: layout)
        let friend = fetchedResultsController.object(at: indexPath) as! Friend

        controller.friend = friend
        navigationController?.pushViewController(controller, animated: true)

        
    }
    
}
extension UIView{
    
    //Adds Constraints
    func addConstraintsWithFormat(format: String, views: UIView...){
        
        var viewsDictionary = [String: UIView]()
        for(index,view) in views.enumerated(){
            let key = "v\(index)"
            viewsDictionary[key] = view
            view.translatesAutoresizingMaskIntoConstraints = false
        }
        
        addConstraints(NSLayoutConstraint.constraints(withVisualFormat: format, options: NSLayoutFormatOptions(), metrics: nil, views: viewsDictionary))
        
    }
    
}

class BaseCell: UICollectionViewCell{
    
    override init(frame: CGRect){
        super.init(frame: frame)
        setupViews()
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func setupViews(){
    }
}
