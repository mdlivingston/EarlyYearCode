//
//  FriendCollectionViewCell.swift
//  FBMessenger
//
//  Created by Max Livingston on 8/10/17.
//  Copyright © 2017 Max Livingston. All rights reserved.
//

import UIKit
class FriendCollectionViewCell: UICollectionViewCell {
    
    @IBOutlet weak var view: UIView!
    @IBOutlet weak var profileImageView: UIImageView!
    @IBOutlet weak var nameLabel: UILabel!
    @IBOutlet weak var messageLabel: UILabel!
    @IBOutlet weak var timeLabel: UILabel!
    
    fileprivate var separator: CALayer!
    
    override func awakeFromNib() {
        super.awakeFromNib()
        
        //Rounds Friend Images in Nib
        let cornerRadius = profileImageView.frame.width / 2
        profileImageView.layer.cornerRadius = cornerRadius
        
        addSeparator()
    }
    
    //Adds Separator lines
    func addSeparator() {
        separator = CALayer()
        let nameLabelXPos = nameLabel.frame.origin.x
        let borderWidth = frame.width - nameLabelXPos
        separator.frame = CGRect(x: nameLabelXPos, y: 0, width: borderWidth, height: 1.0)
        separator.frame.origin = CGPoint(x: separator.frame.origin.x, y: frame.height - 1)
        separator.backgroundColor = UIColor.lightGray.cgColor
        layer.addSublayer(separator)
    }
    
    //Highlights Friend Cells if touched
    override var isHighlighted: Bool{
        didSet{
            view.backgroundColor = isHighlighted ? UIColor.init(red: 0, green: 134/225, blue: 249/255, alpha: 1) : UIColor.white
            nameLabel.textColor = isHighlighted ? UIColor.white : UIColor.black
            timeLabel.textColor = isHighlighted ? UIColor.white : UIColor.black
            messageLabel.textColor = isHighlighted ? UIColor.white : UIColor.black
        }
        
    }
    
    //Sets and formats friend cells
    func setupCell(with data: Message) {
        
        if (data.friend?.profileImageName) != nil{
            profileImageView.image = UIImage(named: (data.friend?.profileImageName)!)
        }
        
        nameLabel.text = data.friend?.name
        messageLabel.text = data.text
        
        if data.date != nil {
            let dateFormatter = DateFormatter()
            dateFormatter.dateFormat = "h:mm a"
            
            let elapsedTimeInSeconds = NSDate().timeIntervalSince(data.date! as Date)
            
            let secondInDays: TimeInterval = 60 * 60 * 24
            if elapsedTimeInSeconds > 7 * secondInDays {
                dateFormatter.dateFormat = "MM/dd/yy"
            }
            else if elapsedTimeInSeconds > secondInDays {
                dateFormatter.dateFormat = "EEE"
            }
            
            timeLabel.text = dateFormatter.string(from: data.date! as Date)
        }
        
    }
    
    //Hides Separator
    func separator(_ isHidden: Bool) {
        separator.isHidden = isHidden
    }
}
