//##########################################################################
//#                                                                        #
//#                              CLOUDCOMPARE                              #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 or later of the License.      #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#          COPYRIGHT: EDF R&D / TELECOM ParisTech (ENST-TSI)             #
//#                     Tobias Neumann                                     #
//#                                                                        #
//##########################################################################

#ifndef CC_MAPIT_FILTER_HEADER
#define CC_MAPIT_FILTER_HEADER

#include "FileIOFilter.h"

#include <memory>

namespace mapit {
namespace msgs {
class Entity;
}
namespace tf2 {
class BufferCore;
}
typedef std::string Path;
class Workspace;
}

//! Calibrated images and cloud meta-file I/O filter
class /*QCC_IO_LIB_API*/ MapitFilter : public FileIOFilter
{
public:

	//static accessors
	static inline QString GetFileFilter() { return "mapit repository (*.cc-mapit)"; }
	static inline QString GetDefaultExtension() { return "cc-mapit"; }

	//inherited from FileIOFilter
	virtual bool importSupported() const override { return true; }
	virtual CC_FILE_ERROR loadFile(const QString& filename, ccHObject& container, LoadParameters& parameters) override;
	virtual QStringList getFileFilters(bool onImport) const override { return QStringList(GetFileFilter()); }
	virtual QString getDefaultExtension() const override { return GetDefaultExtension(); }
	virtual bool canLoadExtension(const QString& upperCaseExt) const override;
	virtual bool canSave(CC_CLASS_ENUM type, bool& multiple, bool& exclusive) const override;
	virtual CC_FILE_ERROR saveToFile(ccHObject* entity, const QString& filename, const SaveParameters& parameters);

private:
	const std::string _PREFIX_WORKSPACE_ = "workspace_";
	std::string name_workspace_;
	std::vector<std::string> name_files_;
	std::string frame_id_;
	std::string cc_mapit_file_name_ = "";
	std::shared_ptr<mapit::Workspace> workspace_;
	std::shared_ptr<mapit::tf2::BufferCore> tf_buffer_ = nullptr;

	CC_FILE_ERROR load_pointcloud(std::shared_ptr<mapit::msgs::Entity> obj, const mapit::Path &path, ccHObject* container);
	CC_FILE_ERROR store_transform(ccHObject* entity, std::string mapit_entity_name);
};

#endif //CC_MAPIT_FILTER_HEADER
