#pragma once

#include "..\Common\Types.h"
#include "..\System\Error.h"
#include <string>
#include <fstream>
#include <vector>

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

	template<typename T>
	static std::vector<T>& ToVector ( T *data, size_t length ) {
		std::vector<T> result;
		for ( size_t i = 0; i < length; i++ ) {
			result.push_back( data[i] );
		}
		return result;
	}

	template<typename T>
	static std::vector<T>& ToExplicitVector ( T *data, size_t length ) {
		std::vector<T> result;
		result.reserve( length );
		for ( size_t i = 0; i < length; i++ ) {
			result.push_back( data[i] );
		}
		return result;
	}

}