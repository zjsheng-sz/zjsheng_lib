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

final class AuthViewController: UIViewController {
  
  override var prefersStatusBarHidden: Bool {
    return true
  }
  
  private enum TextFieldTag: Int {
    case email
    case password
  }
  
  @IBOutlet weak var containerView: UIView!
  @IBOutlet weak var emailField: UITextField!
  @IBOutlet weak var passwordField: UITextField!
  @IBOutlet weak var titleLabel: UILabel!
  @IBOutlet weak var signInButton: UIButton!
  @IBOutlet weak var bottomConstraint: NSLayoutConstraint!
  
  override func viewDidLoad() {
    super.viewDidLoad()
    
    containerView.transform = CGAffineTransform(scaleX: 0, y: 0)
    containerView.backgroundColor = .rwGreen
    containerView.layer.cornerRadius = 7
    
    emailField.delegate = self
    emailField.tintColor = .rwGreen
    emailField.tag = TextFieldTag.email.rawValue
    
    passwordField.delegate = self
    passwordField.tintColor = .rwGreen
    passwordField.tag = TextFieldTag.password.rawValue
    
    titleLabel.isHidden = true
    
    view.addGestureRecognizer(
      UITapGestureRecognizer(
        target: self,
        action: #selector(handleTap(_:))
      )
    )
    
    registerForKeyboardNotifications()
  }
  
  override func viewDidAppear(_ animated: Bool) {
    super.viewDidAppear(animated)
    
    let animation = CABasicAnimation(keyPath: "transform.scale")
    
    animation.duration = 0.3
    animation.fromValue = 0
    animation.toValue = 1
    
    CATransaction.begin()
    CATransaction.setCompletionBlock {
      self.emailField.becomeFirstResponder()
      self.titleLabel.isHidden = false
    }
    containerView.layer.add(animation, forKey: "scale")
    containerView.transform = CGAffineTransform(scaleX: 1, y: 1)
    CATransaction.commit()
  }
  
  // MARK: - Actions
  
  @objc private func handleTap(_ gesture: UITapGestureRecognizer) {
    view.endEditing(true)
  }
  
  @IBAction func signInButtonPressed() {
    // sign in
  }
  
  // MARK: - Helpers
  
  private func registerForKeyboardNotifications() {
    NotificationCenter.default.addObserver(
      self,
      selector: #selector(keyboardWillShow(_:)),
      name: NSNotification.Name.UIKeyboardWillShow,
      object: nil
    )
    NotificationCenter.default.addObserver(
      self,
      selector: #selector(keyboardWillHide(_:)),
      name: NSNotification.Name.UIKeyboardWillHide,
      object: nil
    )
  }
  
  // MARK: - Notifications
  
  @objc internal func keyboardWillShow(_ notification: Notification) {
    guard let userInfo = notification.userInfo else {
      return
    }
    guard let keyboardHeight = (userInfo[UIKeyboardFrameEndUserInfoKey] as? NSValue)?.cgRectValue.height else {
      return
    }
    guard let keyboardAnimationDuration = (userInfo[UIKeyboardAnimationDurationUserInfoKey] as? NSNumber)?.doubleValue else {
      return
    }
    guard let keyboardAnimationCurve = (userInfo[UIKeyboardAnimationCurveUserInfoKey] as? NSNumber)?.uintValue else {
      return
    }
    
    let options = UIViewAnimationOptions(rawValue: keyboardAnimationCurve << 16)
    bottomConstraint.constant = keyboardHeight + 32
    
    UIView.animate(withDuration: keyboardAnimationDuration, delay: 0, options: options, animations: {
      self.view.layoutIfNeeded()
    }, completion: nil)
  }
  
  @objc internal func keyboardWillHide(_ notification: Notification) {
    guard let userInfo = notification.userInfo else {
      return
    }
    guard let keyboardAnimationDuration = (userInfo[UIKeyboardAnimationDurationUserInfoKey] as? NSNumber)?.doubleValue else {
      return
    }
    guard let keyboardAnimationCurve = (userInfo[UIKeyboardAnimationCurveUserInfoKey] as? NSNumber)?.uintValue else {
      return
    }
    
    let options = UIViewAnimationOptions(rawValue: keyboardAnimationCurve << 16)
    bottomConstraint.constant = 0
    
    UIView.animate(withDuration: keyboardAnimationDuration, delay: 0, options: options, animations: {
      self.view.layoutIfNeeded()
    }, completion: nil)
  }

}

extension AuthViewController: UITextFieldDelegate {
  
  func textFieldShouldReturn(_ textField: UITextField) -> Bool {
    guard let text = textField.text, text.count > 0 else {
      return false
    }
    
    switch textField.tag {
    case TextFieldTag.email.rawValue:
      passwordField.becomeFirstResponder()
    case TextFieldTag.password.rawValue:
      break
    default:
      return false
    }
    
    return true
  }
  
}

