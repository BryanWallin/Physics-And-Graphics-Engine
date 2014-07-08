//============================================================================//
//                                                                            //
//  AssetLoader.mm                                                            //
//                                                                            //
//  The AssetLoader class allows for easier loading of assets.                //
//                                                                            //
//  Original author: Bryan Wallin                                             //
//  Last modified on 02/06/2014 by Bryan Wallin.                              //
//                                                                            //
//============================================================================//

#include "AssetLoader.h"

namespace GraphicsEngine
{
    //This method gets the full file path of the file name and type requested.
    std::string getFilePath(std::string fileName, std::string fileType)
    {
        NSString *NSFileName = [NSString stringWithCString:fileName.c_str()
                                encoding:[NSString defaultCStringEncoding]];
        NSString *NSFileType = [NSString stringWithCString:fileType.c_str()
                                encoding:[NSString defaultCStringEncoding]];
        
        NSString* filePath = [[NSBundle mainBundle]pathForResource:NSFileName
                              ofType:NSFileType];
        
        return [filePath cStringUsingEncoding:
                [NSString defaultCStringEncoding]];
    }
    
    //This method gets the file contents of the file name and type requested.
    GLchar * getFileContents(std::string fileName, std::string fileType)
    {
        NSString *NSFileName = [NSString stringWithCString:fileName.c_str()
                                                  encoding:[NSString defaultCStringEncoding]];
        NSString *NSFileType = [NSString stringWithCString:fileType.c_str()
                                                  encoding:[NSString defaultCStringEncoding]];
        
        NSString* filePath = [[NSBundle mainBundle]pathForResource:NSFileName
                                                            ofType:NSFileType];
        
        return (GLchar *) [[NSString stringWithContentsOfFile:filePath
                            encoding:NSUTF8StringEncoding
                            error:nil] UTF8String];
    }
}