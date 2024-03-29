//
//  DetailViewController.swift
//  MaxiAP200FileBrowser
//
//  Created by autel on 2018/7/7.
//  Copyright © 2018年 Autel_Ling. All rights reserved.
//

import UIKit
import WebKit

class DetailViewController: UIViewController {
    
    
    lazy var webView:WKWebView = {

        let view = WKWebView.init(frame: self.view.bounds)
        view.navigationDelegate = self
        view.uiDelegate = self
        view.backgroundColor = UIColor.gray

        return view
    }()

    var fileItem:FileItem?

    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
        self.view .addSubview(self.webView)
        
        
        self.showDocument(fileItem: fileItem!)
        
        
        
        let rightButtomItem = UIBarButtonItem.init(title: "第三发打开", style: .plain, target: self, action: #selector(thirdOpenAciton))
        self.navigationItem.rightBarButtonItem = rightButtomItem
        
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    func showDocument(fileItem:FileItem) -> Void {
        

        if fileItem.type == .xml || fileItem.type == .ini{
        
            let data = NSData.init(contentsOfFile: fileItem.path)
            self.webView.load(data! as Data, mimeType: "text/html/xml/ini", characterEncodingName: "UTF-8", baseURL: URL.init(fileURLWithPath: fileItem.path));
            
        }else{

            self.webView.loadFileURL(URL(fileURLWithPath: fileItem.path), allowingReadAccessTo: URL(fileURLWithPath: fileItem.path))
        }
    

    }

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

    @objc func thirdOpenAciton() {
        
        let documentController = UIDocumentInteractionController.init(url: URL(fileURLWithPath: (fileItem?.path)!))
        
        documentController.presentOpenInMenu(from: self.navigationItem.rightBarButtonItem!, animated: true)
        
        
//            self.documentController = [UIDocumentInteractionController interactionControllerWithURL:url];
//
//            [self.documentController presentOptionsMenuFromRect:self.view.bounds inView:self.view animated:YES];

    }
    

    
}


extension DetailViewController:WKNavigationDelegate,WKUIDelegate{


}
