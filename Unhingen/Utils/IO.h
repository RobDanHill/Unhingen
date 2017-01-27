#pragma once

#include "..\System\Error.h"
#include <string>
#include <fstream>

namespace utils {

	static std::string LoadFile ( const std::string& fileName ) {
		std::string out, line;
		std::ifstream file;
		file.open( fileName.c_str() );
		if ( file.is_open() ) {
			while ( file.good() ) {
				std::getline( file, line );
				out.append( line + "\n" );
			}
		} else err::ErrMsg( "Unable to load file \"" + fileName + "\"!" );
		return out;
	}

}