//
//  Archiver.m
//  OpenStack
//
//  Created by Mike Mayo on 10/4/10.
//  The OpenStack project is provided under the Apache 2.0 license.
//

#import "Archiver.h"

@implementation Archiver

+ (id)retrieve:(NSString *)key {
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *filePath = [documentsDirectory stringByAppendingString:[NSString stringWithFormat:@"/%@.archive", key]];
//    NSLog(@"filepath: %@", filePath);
    return [[NSKeyedUnarchiver unarchiveObjectWithFile:filePath] retain];
    /* TODO: fixme on potential leak - "retrieve" doesn't match copy or alloc pattern, and hence should be returning autoreleased object
     * Not changing right now, but documenting for later fixing - need to see how and where [Archiver.. retrieve:key] is used to make sure 
     * switching this won't cause a crash
     */
}

+ (void)persist:(id)object key:(NSString *)key {
//    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0);
//    dispatch_async(queue, ^{        
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];
        NSString *filePath = [documentsDirectory stringByAppendingString:[NSString stringWithFormat:@"/%@.archive", key]];
        [NSKeyedArchiver archiveRootObject:object toFile:filePath];
//    });
}

+ (BOOL)delete:(NSString *)key {
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *filePath = [documentsDirectory stringByAppendingString:[NSString stringWithFormat:@"/%@.archive", key]];
    return [fileManager removeItemAtPath:filePath error:NULL];    
}

+ (BOOL)deleteEverything {
    BOOL result = YES;
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    NSArray *files = [fileManager contentsOfDirectoryAtPath:documentsDirectory error:NULL];
    
    for (int i = 0; i < [files count]; i++) {
        NSString *path = [files objectAtIndex:i];
        result = result && [fileManager removeItemAtPath:path error:NULL];
    }
    
    return result;
}

@end
