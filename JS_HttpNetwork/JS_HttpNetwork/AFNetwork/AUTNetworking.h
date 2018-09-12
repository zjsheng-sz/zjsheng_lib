//
//  AUTNetworking.h
//  MobVDT
//
//  Created by Autel_Ling on 2017/3/1.
//  Copyright © 2017年 Autel. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, AUTNetworkReachabilityStatus) {
    AUTNetworkReachabilityStatusUnknown          = -1,
    AUTNetworkReachabilityStatusNotReachable     = 0,
    AUTNetworkReachabilityStatusReachableViaWWAN = 1,
    AUTNetworkReachabilityStatusReachableViaWiFi = 2,
};


//请求成功的回调block
typedef void(^responseSuccess)(NSURLSessionDataTask *task, NSDictionary *  responseObject);

//请求失败的回调block
typedef void(^responseFailed)(NSURLSessionDataTask *task, NSError *error);

//文件下载的成功回调block
typedef void(^downloadSuccess)(NSURLResponse *response, NSURL *filePath);

//文件下载的失败回调block
typedef void(^downloadFailed)(NSError *error);

//文件上传下载的进度block
typedef void (^progress)(NSProgress *progress);

@interface AUTNetworking : NSObject

//单例
+ (instancetype)sharedManager;

//检测网路是否连接
@property (nonatomic, assign, readonly) BOOL isNetConnected;
@property (nonatomic, assign, readonly) AUTNetworkReachabilityStatus netStatus;

//开始检测网络状态
- (void)afnReachabilityCheck;

/**
 *  发送一个GET请求
 *
 *  @param url     请求路径
 *  @param params  请求参数
 *  @param success 请求成功后的回调（请将请求成功后想做的事情写到这个block中）
 *  @param failed 请求失败后的回调（请将请求失败后想做的事情写到这个block中）
 */
+ (void)getWithUrl:(NSString *)url params:(NSDictionary *)params success:(responseSuccess)success failed:(responseFailed)failed;

/**
 *  发送一个POST请求
 *
 *  @param host     请求路径
 *  @param subUrl   请求路径
 *  @param params  请求参数
 *  @param success 请求成功后的回调（请将请求成功后想做的事情写到这个block中）
 *  @param failed 请求失败后的回调（请将请求失败后想做的事情写到这个block中）
 */

+ (void)postWithHost:(NSString *)host subUrl:(NSString *)subUrl params:(NSDictionary *)params success:(responseSuccess)success failed:(responseFailed)failed;

/**
 下载请求

 @param url 下载地址
 @param downloadProgressBlock 进度
 @param destination 存放路径
 @param completionHandler 完成后的处理
 */
+ (void)downLoadWithUrl:(NSString *)url
               progress:(void (^)(NSProgress *downloadProgress))downloadProgressBlock
            destination:(NSURL * (^)(NSURL *targetPath, NSURLResponse *response))destination
      completionHandler:(void (^)(NSURLResponse *response, NSURL *filePath, NSError *error))completionHandler;



/**
 @param errorCode 错误码
 */
+ (void)handleErrorWithCode:(NSString *)errorCode;

@end
