//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2014 Eran Ifrah
// file name            : includepathlocator.cpp
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#include "editor_config.h"
#include "environmentconfig.h"
#include "file_logger.h"
#include "fileutils.h"
#include "globals.h"
#include "GCCMetadata.hpp"
#include "procutils.h"
#include <wx/dir.h>
#include <wx/fileconf.h>
#include <wx/tokenzr.h>
#include <wx/utils.h>

GCCMetadata::GCCMetadata()
{
}

GCCMetadata::~GCCMetadata()
{
}

void GCCMetadata::Locate(const wxString& rootDir, const wxString& tool, wxArrayString& paths, wxString& target)
{
    // Common compiler paths - should be placed at top of the include path!
    wxString tmpfile1 = wxFileName::CreateTempFileName(wxT("codelite"));
    wxString command;
    wxString tmpfile = tmpfile1;
    tmpfile += wxT(".cpp");

    wxString bin = tool;
    if(bin.IsEmpty()) {
        bin = wxT("gcc");
    }

    wxRenameFile(tmpfile1, tmpfile);

    // GCC prints parts of its output to stdout and some to stderr
    // redirect all output to stdout
    wxString working_directory;
#ifdef __WXMSW__
    if(::clIsCygwinEnvironment()) {
        command << bin << " -v -x c++ /dev/null -fsyntax-only";
    } else {
        wxFileName cxx(bin);

        // execute the command from the tool directory
        working_directory = cxx.GetPath();
        command << "echo |" << bin << " -xc++ -E -v - -fsyntax-only";
    }
#else
    command << bin << " -v -x c++ /dev/null -fsyntax-only";
#endif

    clDEBUG() << "Running command:" << command << endl;
    wxString outputStr;
    IProcess::Ptr_t proc(::CreateSyncProcess(command, IProcessCreateDefault | IProcessWrapInShell, working_directory));
    if(proc) {
        proc->WaitForTerminate(outputStr);
    }
    clDEBUG() << "Output is:" << outputStr << endl;

    clRemoveFile(tmpfile);

    wxArrayString outputArr = wxStringTokenize(outputStr, wxT("\n\r"), wxTOKEN_STRTOK);
    // Analyze the output
    bool collect(false);
    for(wxString& line : outputArr) {
        line.Trim().Trim(false);

        // store the target
        if(target.empty() && line.StartsWith("Target:")) {
            target = line.AfterFirst(':');
            target.Trim().Trim(false);
        }

        // search the scan starting point
        if(line.Contains(wxT("#include <...> search starts here:"))) {
            collect = true;
            continue;
        }

        if(line.Contains(wxT("End of search list."))) {
            break;
        }

        if(collect) {
            line.Replace("(framework directory)", wxEmptyString);
#ifdef __WXMSW__
            if(line.StartsWith("/")) {
                // probably MSYS2 or Cygwin
                // replace the "/" with the root folder
                line.Prepend(rootDir);
            }
#endif
            // on Mac, (framework directory) appears also,
            // but it is harmless to use it under all OSs
            wxFileName includePath(line, wxEmptyString);
            includePath.Normalize();
            paths.Add(includePath.GetPath());
        }
    }
}
