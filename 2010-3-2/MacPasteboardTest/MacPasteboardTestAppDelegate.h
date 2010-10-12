//
//  MacPasteboardTestAppDelegate.h
//  MacPasteboardTest
//
//  Created by JTianling on 3/3/10.
//  Copyright 2010 JTianling. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#define TEXTUTIL_CMD @"/usr/bin/textutil"
//#define MAC_VIM_CMD @"/Applications/MacVim.app/Contents/MacOS/Vim"
#define MAC_VIM_CMD @"/usr/bin/vim"

@interface MacPasteboardTestAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
	NSTextField *textField;
	
	NSPipe *pipe;
	NSTask *task;
}

@property (nonatomic, retain) IBOutlet NSWindow *window;
@property (nonatomic, retain) IBOutlet NSTextField *textField;
@property (nonatomic, retain) NSPipe *pipe;
@property (nonatomic, retain) NSTask *task;

- (IBAction) cut:(id)sender;
- (IBAction) copy:(id)sender;
- (IBAction) paste:(id)sender;

//- (void)writeToPasteboard:(NSPasteboard *)pb withString:string;
//- (BOOL)readFromPasteboard:(NSPasteboard *)pb;
@end
