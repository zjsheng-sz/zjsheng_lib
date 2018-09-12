//
//  AUTNetworking.m
//  MobVDT
//
//  Created by Autel_Ling on 2017/3/1.
//  Copyright © 2017年 Autel. All rights reserved.
//

#import "AUTNetworking.h"
#import <AFNetworking.h>
#import <arpa/inet.h>


static AFHTTPSessionManager *pt_shareManager = nil;

@implementation AUTNetworking


+ (instancetype)sharedManager {
    static dispatch_once_t onceToken;
    static AUTNetworking *instance;
    dispatch_once(&onceToken, ^{
        instance = [[AUTNetworking alloc] init];
    });

    return instance;
}


+ (void)getWithUrl:(NSString *)url params:(NSDictionary *)params success:(responseSuccess)success failed:(responseFailed)failed {

    AFHTTPSessionManager *manager = [self manager];
    
    //2.发送Get请求
    [manager GET:url parameters:params progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        if (success) {
            success(task,responseObject);
        }
    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        if (failed) {
            failed(task,error);
        }
    }];
}



+ (void)postWithHost:(NSString *)host subUrl:(NSString *)subUrl params:(NSDictionary *)params success:(responseSuccess)success failed:(responseFailed)failed {
    
    AFHTTPSessionManager *manager = [self manager];
    
    NSString *url = [NSString stringWithFormat:@"%@%@",host,subUrl];
    
    NSLog(@"URL=%@",url);
    NSLog(@"PARAMES=%@",params);
    
    manager.requestSerializer.timeoutInterval = 15;
    
    [manager POST:url parameters:params progress:nil success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
        
        if (success) {
            
            NSLog(@"responseObject = %@",responseObject);
            
            success(task, responseObject);

        }
        

    } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
        
        if (error) {
            
            NSLog(@"提示错误信息: %@",error.userInfo [@"NSLocalizedDescription"]);
            failed(task, error);
        }
    }];
    
    
}


/*
    下载
 */

+ (void)downLoadWithUrl:(NSString *)url
               progress:(void (^)(NSProgress *downloadProgress))downloadProgressBlock
            destination:(NSURL * (^)(NSURL *targetPath, NSURLResponse *response))destination
      completionHandler:(void (^)(NSURLResponse *response, NSURL *filePath, NSError *error))completionHandler{

    NSURLSessionConfiguration *configuration = [NSURLSessionConfiguration defaultSessionConfiguration];
    AFURLSessionManager *manager = [[AFURLSessionManager alloc] initWithSessionConfiguration:configuration];
    NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL URLWithString:url]];
    
    NSURLSessionDownloadTask *downloadTask = [manager downloadTaskWithRequest:request progress:^(NSProgress * _Nonnull downloadProgress) {

        downloadProgressBlock(downloadProgress);
        
    } destination:^NSURL *(NSURL *targetPath, NSURLResponse *response) {
        
        NSLog(@"targetPath = %@, response = %@",targetPath,response);
        
        return destination(targetPath,response);
        
    } completionHandler:^(NSURLResponse *response, NSURL *filePath, NSError *error) {
        
        NSLog(@"filePath = %@, response = %@, error = %@",filePath,response,error);

        completionHandler(response,filePath,error);
    }];
    
    [downloadTask resume];
    
}

/*
/// 服务器可达返回true
+ (BOOL)isNetConnected; {
    // 客户端 AF_INET:ipv4  SOCK_STREAM:TCP链接
    int socketNumber = socket(AF_INET, SOCK_STREAM, 0);
    // 配置服务器端套接字
    struct sockaddr_in serverAddress;
    // 设置服务器ipv4
    serverAddress.sin_family = AF_INET;
    // 百度的ip
    serverAddress.sin_addr.s_addr = inet_addr("202.108.22.5");
    // 设置端口号，HTTP默认80端口
    serverAddress.sin_port = htons(80);
    if (connect(socketNumber, (const struct sockaddr *)&serverAddress, sizeof(serverAddress)) == 0) {
        close(socketNumber);
        return true;
    }
    close(socketNumber);;
    return false;
}
*/


- (void)afnReachabilityCheck {
    
    [[AFNetworkReachabilityManager sharedManager] setReachabilityStatusChangeBlock:^(AFNetworkReachabilityStatus status) {
        NSLog(@"%@",[NSThread currentThread]);
        
        _netStatus = (AUTNetworkReachabilityStatus)status;
        // 一共有四种状态
        switch (status) {
                case AFNetworkReachabilityStatusNotReachable:
                _isNetConnected = NO;
                NSLog(@"AFNetworkReachability Not Reachable");
                break;
                case AFNetworkReachabilityStatusReachableViaWWAN:
                _isNetConnected = YES;
                NSLog(@"AFNetworkReachability Reachable via WWAN");
                break;
                case AFNetworkReachabilityStatusReachableViaWiFi:
                _isNetConnected = YES;
                NSLog(@"AFNetworkReachability Reachable via WiFi");
                break;
                case AFNetworkReachabilityStatusUnknown:
                _isNetConnected = NO;
            default:
                _isNetConnected = NO;
                NSLog(@"AFNetworkReachability Unknown");
                break;
        }
    }];
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        [[AFNetworkReachabilityManager sharedManager] startMonitoring];
        [[NSRunLoop currentRunLoop] run];
    });
}



#pragma mark - Private
+ (AFHTTPSessionManager *)manager {
    AFHTTPSessionManager *manager = [AFHTTPSessionManager manager];
    manager.responseSerializer.acceptableContentTypes = [NSSet setWithObjects:@"application/json", @"text/json", @"text/javascript",@"text/html", nil];
    pt_shareManager = manager;
    return pt_shareManager;
}


@end
