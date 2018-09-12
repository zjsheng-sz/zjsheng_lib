//
//  AppDelegate.swift
//  MaxiAP200FileBrowser
//
//  Created by Autel_Ling on 2018/5/21.
//  Copyright © 2018年 Autel_Ling. All rights reserved.
//

import UIKit
import SVProgressHUD

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    var sourcefileItem:FileItem?

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        
        
        do {
            try createVehicleFiles()
        } catch  {
            print("创建失败:" + error.localizedDescription)
        }
        

        SVProgressHUD.setForegroundColor(UIColor.white)
        SVProgressHUD.setBackgroundColor(UIColor.black)
        SVProgressHUD.setMaximumDismissTimeInterval(1.5)

        return true
    }

    func applicationWillResignActive(_ application: UIApplication) {
        // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
        // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    }

    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    }

    func applicationWillEnterForeground(_ application: UIApplication) {
        // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    }

    func applicationDidBecomeActive(_ application: UIApplication) {
        // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    }

    func applicationWillTerminate(_ application: UIApplication) {
        // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    }


}

extension AppDelegate{
    
    func createVehicleFiles() throws {
        
        
        let documentPath:String = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true).first!
        
        let vehiclepath = documentPath + "/Vehicle"

        // 创建Vehicle文件夹
        if FileManager.default.fileExists(atPath: vehiclepath) == false {
            try FileManager.default.createDirectory(atPath: vehiclepath, withIntermediateDirectories: true, attributes: nil)
        }
        
        //创建洲系文件夹
        for stateName in ContinentsArr {
            
            let statePath = documentPath + "/Vehicle/" + stateName
            
            if FileManager.default.fileExists(atPath: statePath) == false {
                
                    try FileManager.default.createDirectory(atPath: statePath, withIntermediateDirectories: true, attributes: nil)
            }
        }
    }
}






