//
//  FileReader_Win.h
//  particle-editor
//
//  Created by Jonathan Leang on 22/7/14.
//
//

#ifndef __particle_editor__FileReader_Win__
#define __particle_editor__FileReader_Win__

#ifdef USE_WINDOWS

#include <string>
#include <boost/shared_ptr.hpp>

using namespace std;

#include <windows.h>
#include <Shlobj.h>

string browseFolder();

#endif
#endif /* defined(__particle_editor__FileReader_Win__) */
