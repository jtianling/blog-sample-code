//
//  MacPasteboardTestAppDelegate.m
//  MacPasteboardTest
//
//  Created by JTianLing on 3/3/10.
//  Copyright 2010 JTianLing. All rights reserved.
//

#import "MacPasteboardTestAppDelegate.h"
#import <Carbon/Carbon.h>
#include <stdlib.h>

void writeToPasteboard(NSPasteboard * pb, NSData* data) {
	[pb declareTypes:[NSArray arrayWithObject:NSPasteboardTypeHTML]
			   owner:nil];
	[pb setData:data forType:NSPasteboardTypeHTML];
}

NSData * readFromPasteboard( NSPasteboard * pb) {
	NSArray *types = [pb types];
	if ([types containsObject:NSPasteboardTypeRTF]) {
		return [pb dataForType:NSPasteboardTypeRTF];
	}
	else if ([types containsObject:NSPasteboardTypeString]) {
		return [pb dataForType:NSPasteboardTypeString];
	}

	return nil;
}


void convertRtfToHtml() {
	NSLog(@"convertRtfToHtml called");
	
	NSPasteboard *pb = [NSPasteboard generalPasteboard];
	
	NSTask *task = [[NSTask alloc] init];
	[task setLaunchPath:TEXTUTIL_CMD];
	
	NSMutableArray *args = [NSMutableArray array];
	[args addObject:@"-excludedelements"];
	//[args addObject:@"(text/css)"];
	[args addObject:@"(Apple-converted-space)"];
	[args addObject:@"-convert"];
    [args addObject:@"html"];
	[args addObject:@"-stdin"];
	[args addObject:@"temp.html"];
	[task setArguments:args];
	
	//NSPipe *outPipe = [NSPipe pipe];
	//[task setStandardOutput: outPipe];
	
	NSPipe *inPipe = [NSPipe pipe];
	[task setStandardInput: inPipe];
	
	NSData *inData = readFromPasteboard(pb);
	if (inData == nil) {
		NSLog(@"There is no data in pasteboard.");
		return;
	}
	
	NSFileHandle *writeHandle = [inPipe fileHandleForWriting];

	[task launch];
	[writeHandle writeData: inData];
	[writeHandle closeFile];
	[task waitUntilExit];
	
	//NSFileHandle *readHandle = [outPipe fileHandleForReading];
	//NSData *outData = [readHandle readDataToEndOfFile];
	//writeToPasteboard(pb, outData);

	[task release];
}

void addCArg(NSMutableArray* array) {
	[array addObject:@"-c"];
}

void convertTextToHtml() {
	NSLog(@"convertTextToHtml called");

	NSPasteboard *pb = [NSPasteboard generalPasteboard];
	
	//system("/Applications/MacVim.app/Contents/MacOS/Vim -c ':set clipboard+=unnamed|:norm p |:syntax on |:set syn=objc |:TOhtml |:norm ggVGy |:qa!'");
	system("/Applications/MacVim.app/Contents/MacOS/Vim -c ':set clipboard+=unnamed|:norm p' -c ':syntax on|:set syn=objc|:colo delek|:TOhtml' -c ':norm ggVGy' -c ':qa!'");
	
	NSData *data = readFromPasteboard(pb);
	writeToPasteboard(pb, data);
}


OSStatus MyHotKeyHandler(EventHandlerCallRef nextHandler,EventRef theEvent,
						 void *userData) {
	EventHotKeyID hkCom;
	GetEventParameter(theEvent,kEventParamDirectObject,typeEventHotKeyID,NULL,
					  sizeof(hkCom),NULL,&hkCom);
	int l = hkCom.id;
	
	switch (l) {
		case 1: //do something
			convertRtfToHtml();
			break;
		case 2: //do something
			convertTextToHtml();
			break;
	}
	return noErr;
}

@implementation MacPasteboardTestAppDelegate

@synthesize window;
@synthesize textField;
@synthesize task;
@synthesize pipe;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
	// Insert code here to initialize your application
	//Register the Hotkeys

	EventTypeSpec eventType;
	eventType.eventClass=kEventClassKeyboard;
	eventType.eventKind=kEventHotKeyPressed;
	InstallApplicationEventHandler(MyHotKeyHandler, 1, &eventType,NULL, NULL);
	
	EventHotKeyRef gMyHotKeyRef;
	EventHotKeyID gMyHotKeyID;
	gMyHotKeyID.signature='rt2h';
	gMyHotKeyID.id=1;
	
	RegisterEventHotKey(6, controlKey, gMyHotKeyID,
						GetApplicationEventTarget(), 0, &gMyHotKeyRef);
	
	gMyHotKeyID.signature='te2h';
	gMyHotKeyID.id=2;
	
	RegisterEventHotKey(7, controlKey, gMyHotKeyID,
						GetApplicationEventTarget(), 0, &gMyHotKeyRef);
}

- (IBAction)cut:(id)sender {
	//[self copy:sender];
	//[textField setStringValue:@""];
}

- (IBAction)copy:(id)sender {
	//NSPasteboard *pb = [NSPasteboard generalPasteboard];
	//[self writeToPasteboard:pb withString:[textField stringValue]];
}

- (IBAction)paste:(id)sender {
	//NSPasteboard *pb = [NSPasteboard generalPasteboard];
	//[textField setStringValue:[self readFromPasteboard:pb]];
}

@end
