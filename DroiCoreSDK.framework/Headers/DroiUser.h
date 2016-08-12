/*
 * Copyright (c) 2016-present Shanghai Droi Technology Co., Ltd.
 * All rights reserved.
 */

#import "DroiObject.h"
#import "DroiError.h"
@import UIKit;

@class DroiUser;
typedef void(^DroiSignUpCallback)(BOOL result, DroiError* error);
typedef void(^DroiLoginCallback)(DroiUser* user, DroiError* error);

@class UIView;
@protocol IOAuthProvider <NSObject>

@required
- (BOOL) isTokenValid;
- (NSString*) sessionToken;
- (NSString*) OAuthProviderName;
@end

DroiObjectName(@"_User")
@interface DroiUser : DroiObject

DroiExpose
@property NSString* UserId;

DroiExpose
@property NSString* Email;

DroiExpose
@property NSString* PhoneNum;

DroiExpose
@property BOOL EmailVerified;

DroiExpose
@property BOOL PhoneNumVerified;

DroiExpose
@property BOOL Enabled;

@property NSString* Password;

#pragma mark - Properties

@property (readonly, getter=getSessionToken) NSString* sessionToken;

#pragma mark - Static Methods
+ (instancetype) getCurrentUser;
+ (id) getCurrentUserByUserClass:(Class) userClazz;

+ (instancetype) login: (NSString*) userId password:(NSString*) password error:(DroiError**) error;
+ (BOOL) loginInBackground:(NSString*) userId password:(NSString*) password callback:(DroiLoginCallback) callback;
+ (id) loginByUserClass : (NSString*) userId password:(NSString*) password userClass:(Class) userClazz error:(DroiError**) error;
+ (BOOL) loginByUserClassInBackground : (NSString*) userId password:(NSString*) password userClass:(Class) userClazz callback:(DroiLoginCallback) callback;

// TODO: OAuth
+ (instancetype) loginWithOAuth : (UIView*) view oauth:(id<IOAuthProvider>) provider userClass:(Class) userClazz error:(DroiError**) error;
+ (instancetype) loginWithOAuth : (UIView*) view oauth:(id<IOAuthProvider>) provider error:(DroiError**) error;
+ (instancetype) loginWithAnonymous:(DroiError**) error;

#pragma mark - Login/Logout
- (DroiError*) signUp;
- (NSString*) signUpInBackground:(DroiSignUpCallback) callback;
- (void) cancelBackgroundTask : (NSString*) taskId;
- (DroiError*) logout;
- (BOOL) logoutInBackground:(DroiObjectCallback) callback;
- (DroiError*) changePassword:(NSString*) oldPassword newPassword:(NSString*) newPassword;
- (BOOL) changePasswordInBackground:(NSString*) oldPassword newPassword:(NSString*) newPassword callback:(DroiObjectCallback) callback;

#pragma mark - Save methods
- (DroiError*) save;
- (NSString*) saveInBackground:(DroiObjectCallback)callback;
- (void) saveEventually;

#pragma mark - Status
+ (BOOL) autoAnonymousUser;
+ (void) setAutoAnonymousUser:(BOOL) autoAnonymousUser;
- (BOOL) isEmailVerified;
- (BOOL) isAuthorized;
- (BOOL) isLoggedIn;
- (BOOL) isAnonymous;

#pragma mark - Validation

/**
 * Validate user email.
 *
 * @return DroiError DroiError object. Developer should use isOk to check whether this result is OK.
 */
- (DroiError*) validateEmail;

/**
 * Validate user phone number.
 *
 * @return DroiError DroiError object. Developer should use isOk to check whether this result is OK.
 */
- (DroiError*) validatePhoneNumber;

/**
 * Confirm pin code sent to user phone.
 *
 * @param pinCode Pic code
 *
 * @return DroiError DroiError object. Developer should use isOk to check whether this result is OK.
 */
- (DroiError*) confirmPhoneNumberPinCode:(NSString*) pinCode;

/**
 * Refersh EmailVerified / PhoneNumVerified field status. After refreshed, check verification via isEmailVerified or isPhoneNumVerified.
 *
 * @return YES to successfully refreshed.
 */
- (BOOL) refreshValidationStatus;

/**
 * Refersh EmailVerified / PhoneNumVerified field status in the background thread. After refreshed, check verification via isEmailVerified or isPhoneNumVerified.
 *
 * @param callback Callback
 *
 * @return YES to successfully push to background task to execute.
 */
- (BOOL) refreshValidationStatusInBackground:(DroiObjectCallback) callback;
@end
