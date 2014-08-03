//
//  FileReader_Mac.h
//  particle-editor
//
//  Created by Jonathan Leang on 22/7/14.
//
//

#ifndef __particle_editor__FileReader_Mac__
#define __particle_editor__FileReader_Mac__

#ifdef USE_MAC

#include <string>

using namespace std;

string browseFolder();
bool makeDirectory(std::string name);
void openSavedFolder(std::string path);

#endif
#endif /* defined(__particle_editor__FileReader_Mac__) */
