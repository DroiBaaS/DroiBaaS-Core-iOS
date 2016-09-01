/*
 * Copyright (c) 2016-present Shanghai Droi Technology Co., Ltd.
 * All rights reserved.
 */

#import <Foundation/Foundation.h>

typedef NS_ENUM(int, AuthType) {
    AUTH_TYPE_QQ,
    AUTH_TYPE_SINA,
    AUTH_TYPE_WEIXIN,
    AUTH_TYPE_FACEBOOK
};

@interface DroiOAuthProvider : NSObject
+ (BOOL) registerProviderType:(AuthType) type class:(Class) clazz;
+ (instancetype) providerWithType:(AuthType) type;
+ (BOOL) handleOpenUrl:(NSURL*) url sourceApplication:(NSString*) sourceApplication annotation:(id) annotation;
- (BOOL) handleOpenUrl:(NSURL*) url sourceApplication:(NSString*) sourceApplication annotation:(id) annotation;
@property NSString* userId;
@property NSString* password;
@property (readonly) NSString* id;
@property (readonly) NSString* code;
@property (readonly) NSString* accessToken;
@property (readonly, getter=getProviderName) NSString* name;
@property (readonly, getter=getProviderVersion) NSString* providerVersion;
@end
