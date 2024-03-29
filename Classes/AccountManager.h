//
//  AccountManager.h
//  OpenStack
//
//  Created by Mike Mayo on 10/21/10.
//  The OpenStack project is provided under the Apache 2.0 license.
//

#import <Foundation/Foundation.h>

// this class performs API calls on accounts and broadcasts NSNotifications to any other
// object that chooses to observe the notification

@class OpenStackAccount, Server, Flavor, Image, Container, StorageObject, OpenStackRequest, ASINetworkQueue, APICallback, LoadBalancer, LoadBalancerNode;

@interface AccountManager : NSObject {
    OpenStackAccount *account;
    ASINetworkQueue *queue;
}

@property (nonatomic, retain) ASINetworkQueue *queue;

@property (nonatomic, assign) OpenStackAccount *account;

- (NSString *)notificationName:(NSString *)key identifier:(NSString *)identifier;
- (void)notify:(NSString *)name request:(OpenStackRequest *)request;
- (void)notify:(NSString *)name request:(OpenStackRequest *)request object:(id)object;
    
- (APICallback *)authenticate;

// compute

- (void)getLimits;
- (void)softRebootServer:(Server *)server;
- (void)hardRebootServer:(Server *)server;
- (void)changeAdminPassword:(Server *)server password:(NSString *)password;
- (APICallback *)renameServer:(Server *)server name:(NSString *)name;
- (void)deleteServer:(Server *)server;
- (void)createServer:(Server *)server;
- (void)resizeServer:(Server *)server flavor:(Flavor *)flavor;
- (void)confirmResizeServer:(Server *)server;
- (void)revertResizeServer:(Server *)server;
- (void)rebuildServer:(Server *)server image:(Image *)image;
- (void)getBackupSchedule:(Server *)server;
- (void)updateBackupSchedule:(Server *)server;

- (void)getServers;
- (APICallback *)getServersWithCallback;
- (void)getImages;
- (void)getFlavors;
- (void)getImage:(Server *)server;

// object storage

- (void)getStorageAccountInfo;
- (void)getContainers;
- (APICallback *)getContainersWithCallback;
- (void)createContainer:(Container *)container;
- (void)deleteContainer:(Container *)container;

- (void)getObjects:(Container *)container;
- (void)getObjectInfo:(Container *)container object:(StorageObject *)object;
- (void)getObject:(Container *)container object:(StorageObject *)object downloadProgressDelegate:(id)downloadProgressDelegate;
- (void)writeObject:(Container *)container object:(StorageObject *)object downloadProgressDelegate:(id)downloadProgressDelegate;
- (void)writeObjectMetadata:(Container *)container object:(StorageObject *)object;
- (void)deleteObject:(Container *)container object:(StorageObject *)object;
  
- (void)updateCDNContainer:(Container *)container;

// load balancing

- (APICallback *)getLoadBalancers:(NSString *)endpoint;
- (APICallback *)getLoadBalancerDetails:(LoadBalancer *)loadBalancer endpoint:(NSString *)endpoint;
- (APICallback *)getLoadBalancerProtocols:(NSString *)endpoint;
- (APICallback *)createLoadBalancer:(LoadBalancer *)loadBalancer;
- (APICallback *)updateLoadBalancer:(LoadBalancer *)loadBalancer;
- (APICallback *)deleteLoadBalancer:(LoadBalancer *)loadBalancer;
- (APICallback *)updateLoadBalancerConnectionLogging:(LoadBalancer *)loadBalancer;

- (APICallback *)getLoadBalancerConnectionThrottling:(LoadBalancer *)loadBalancer;
- (APICallback *)updateLoadBalancerConnectionThrottling:(LoadBalancer *)loadBalancer;
- (APICallback *)deleteLoadBalancerConnectionThrottling:(LoadBalancer *)loadBalancer;


- (APICallback *)getLoadBalancerUsage:(LoadBalancer *)loadBalancer endpoint:(NSString *)endpoint;
- (APICallback *)addLBNodes:(NSArray *)nodes loadBalancer:(LoadBalancer *)loadBalancer endpoint:(NSString *)endpoint;
- (APICallback *)updateLBNode:(LoadBalancerNode *)node loadBalancer:(LoadBalancer *)loadBalancer endpoint:(NSString *)endpoint;
- (APICallback *)deleteLBNode:(LoadBalancerNode *)node loadBalancer:(LoadBalancer *)loadBalancer endpoint:(NSString *)endpoint;

@end
