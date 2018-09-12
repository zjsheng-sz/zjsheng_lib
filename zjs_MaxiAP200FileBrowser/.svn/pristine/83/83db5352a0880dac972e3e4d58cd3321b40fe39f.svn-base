//
//  ViewController.swift
//  MaxiAP200FileBrowser
//
//  Created by Autel_Ling on 2018/5/21.
//  Copyright © 2018年 Autel_Ling. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        
        let shareButton = UIButton(type: .system)
        shareButton.setTitle("共享文件目录", for: .normal)
        shareButton.frame = CGRect(x: UIScreen.main.bounds.width * 0.5 - 100, y: UIScreen.main.bounds.height*0.5 - 50, width: 200, height: 80)
        shareButton.addTarget(self, action: #selector(shareButtonClick), for: .touchUpInside)
        
        let sandBoxButton = UIButton(type: .system)
        sandBoxButton.setTitle("沙盒文件目录", for: .normal)
        sandBoxButton.frame = CGRect(x: UIScreen.main.bounds.width * 0.5 - 100, y: UIScreen.main.bounds.height*0.5 + 50, width: 200, height: 80)
        sandBoxButton.addTarget(self, action: #selector(sandBoxButtonClick), for: .touchUpInside)
        
        view.addSubview(shareButton)
        view.addSubview(sandBoxButton)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

extension ViewController {
    
    @objc func shareButtonClick() {
        
        let sandboxBrowser = SandboxBrowser()
        sandboxBrowser.didSelectFile = { file, vc in
            print(file.name, file.type)
        }
        present(sandboxBrowser, animated: true, completion: nil)

    }
    
    
    @objc func sandBoxButtonClick() {
        
        let sandboxBrowser = SandboxBrowser(initialPath: URL(fileURLWithPath: NSHomeDirectory()))
        sandboxBrowser.didSelectFile = { file, vc in
            print(file.name, file.type)
        }
        present(sandboxBrowser, animated: true, completion: nil)

    }
}

