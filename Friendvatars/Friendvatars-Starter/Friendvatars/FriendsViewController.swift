/// Copyright (c) 2017 Razeware LLC
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
///
/// Notwithstanding the foregoing, you may not use, copy, modify, merge, publish,
/// distribute, sublicense, create a derivative work, and/or sell copies of the
/// Software in any work that is designed, intended, or marketed for pedagogical or
/// instructional purposes related to programming, coding, application development,
/// or information technology.  Permission for such use, copying, modification,
/// merger, publication, distribution, sublicensing, creation of derivative works,
/// or sale is expressly withheld.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.

import UIKit
import CryptoSwift

final class FriendsViewController: UITableViewController {
  
  var friends: [User] = []
  var imageCache = NSCache<NSString, UIImage>()
  
  init() {
    super.init(style: .grouped)
  }
  
  required init?(coder aDecoder: NSCoder) {
    fatalError("init(coder:) has not been implemented")
  }
  
  override func viewDidLoad() {
    super.viewDidLoad()
    
    title = "Friendvatars"
    
    let reuseIdentifier = String(describing: FriendCell.self)
    tableView.register(
      UINib(nibName: reuseIdentifier, bundle: nil),
      forCellReuseIdentifier: reuseIdentifier
    )
    
    navigationItem.leftBarButtonItem = UIBarButtonItem(
      title: "Sign Out",
      style: .plain,
      target: self,
      action: #selector(signOut)
    )
    
    friends = [
      User(name: "Bob Appleseed", email: "ryha26+bob@gmail.com"),
      User(name: "Linda Lane", email: "ryha26+linda@gmail.com"),
      User(name: "Todd Watch", email: "ryha26+todd@gmail.com"),
      User(name: "Mark Towers", email: "ryha26+mark@gmail.com")
    ]
  }
  
  // MARK: - Actions
  
  @objc private func signOut() {
    // sign out
  }
  
  override func numberOfSections(in tableView: UITableView) -> Int {
    return friends.isEmpty ? 1 : 2
  }
  
  override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
    return section == 0 ? 1 : friends.count
  }
  
  override func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
    return 64
  }
  
  override func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
    return section == 0 ? "Me" : "Friends"
  }
  
  override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
    guard let cell = tableView.dequeueReusableCell(withIdentifier: String(describing: FriendCell.self)) as? FriendCell else {
      fatalError()
    }
    
    let user = indexPath.section == 0 ? Settings.currentUser! : friends[indexPath.row]
    cell.nameLabel.text = user.name
    
    if let image = imageCache.object(forKey: user.email as NSString) {
      cell.avatarImageView.image = image
    } else {
      // request the avatar from Gravatar
    }
    
    return cell
  }
  
  override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
    tableView.deselectRow(at: indexPath, animated: true)
  }
  
}
