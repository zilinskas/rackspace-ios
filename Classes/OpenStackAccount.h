//
//  Account.h
//  OpenStack
//
//  Created by Mike Mayo on 10/1/10.
//  The OpenStack project is provided under the Apache 2.0 license.
//

#import <Foundation/Foundation.h>

@class Provider;

@class AccountManager;

@interface OpenStackAccount : NSObject <NSCoding, NSCopying> {
    id getLimitsObserver;
    id getServersObserver;
    id getImagesObserver;
    id getFlavorsObserver;
    @private
    BOOL serversUnarchived;
}

@property (nonatomic, assign) BOOL hasBeenRefreshed;
@property (nonatomic, retain) NSString *uuid;
@property (nonatomic, retain) Provider *provider;
@property (nonatomic, retain) NSString *username;
@property (nonatomic, retain) NSString *apiKey;
@property (nonatomic, retain) NSString *projectId;
@property (nonatomic, retain) NSString *authToken;
@property (nonatomic, retain) NSMutableDictionary *images;
@property (nonatomic, retain) NSDictionary *flavors;
@property (nonatomic, retain) NSMutableDictionary *servers;
@property (nonatomic, retain) NSMutableDictionary *serversByPublicIP;
@property (nonatomic, retain) NSURL *serversURL;
@property (nonatomic, retain) NSURL *filesURL;
@property (nonatomic, retain) NSURL *cdnURL;
@property (nonatomic, retain) NSArray *rateLimits;
@property (nonatomic, retain) AccountManager *manager;
@property (nonatomic, retain) NSString *lastUsedFlavorId;
@property (nonatomic, retain) NSString *lastUsedImageId;
@property (nonatomic, assign) NSInteger containerCount;
@property (nonatomic, assign) unsigned long long totalBytesUsed;
@property (nonatomic, retain) NSMutableDictionary *containers;
@property (nonatomic, assign) BOOL flaggedForDelete;
@property (nonatomic, retain) NSString *apiVersion;

// this is a dictionary of dictionaries:
// { "endpoint1": { "123": { ... }, "456": { ... } },
//   "endpoint2": { "789": { ... }, "321": { ... } }}
@property (nonatomic, retain) NSMutableDictionary *loadBalancers;
@property (nonatomic, retain) NSMutableArray *lbProtocols;

+ (NSArray *)accounts;
- (void)persist;
+ (void)persist:(NSArray *)accountArray;
- (void)refreshCollections;
- (NSArray *)loadBalancerURLs;
- (NSArray *)loadBalancerRegions;

- (NSString *)loadBalancerEndpointForRegion:(NSString *)region;
- (NSString *)loadBalancerRegionForEndpoint:(NSString *)endpoint;
- (NSString *)accountNumber;

- (NSArray *)sortedServers;
- (NSArray *)sortedImages;
- (NSArray *)sortedFlavors;
- (NSArray *)sortedRateLimits;
- (NSArray *)sortedContainers;
- (NSArray *)sortedLoadBalancers;

@end
