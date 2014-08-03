//
//  FileReader_Mac.cpp
//  particle-editor
//
//  Created by Jonathan Leang on 22/7/14.
//
//

#include "FileReader_Mac.h"

#import <Cocoa/Cocoa.h>
#include <string>

std::string browseFolder() {
    NSOpenPanel *op = [NSOpenPanel openPanel];
    if ([op runModal] == NSOKButton) {
        NSURL *path = [[op URLs] objectAtIndex:0];
        return std::string([[path absoluteString] UTF8String]);
    }
    return "";
}

bool makeDirectory(std::string name)
{
    NSString* nsStr = [NSString stringWithUTF8String:name.c_str()];
    
    if (![[NSFileManager defaultManager] fileExistsAtPath:nsStr])
    {
        NSError* error;
        
        if( [[NSFileManager defaultManager] createDirectoryAtPath:nsStr withIntermediateDirectories:YES attributes:nil error:&error]){
            return true;
        }else{
            return false;
        }
    }
    return true;
}

std::string getFolderURL(const std::string& str) {
    unsigned found = str.find_last_of("/\\");
    return str.substr(0,found);
}

void openSavedFolder(std::string path)
{
    path = getFolderURL(path);
    NSString *fileUrl = [NSString stringWithCString: path.c_str()
                                  encoding:[NSString defaultCStringEncoding]];
    [[NSWorkspace sharedWorkspace] selectFile:nil inFileViewerRootedAtPath:fileUrl];
}
