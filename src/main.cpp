#include <config.h>

#include <iostream>
#include <memory>
#include <fstream>
#include <cassert>
#include <array>

#include <archive.h>
#include <archive_entry.h>

int main()
{
	using UniqueArchive = std::unique_ptr<struct archive, decltype(&archive_free)>;
	using UniqueEntry = std::unique_ptr<struct archive_entry, decltype(&archive_entry_free)>;
	UniqueArchive archive(archive_write_new(), &archive_free);
	UniqueArchive archiveReadDisk(archive_read_disk_new(), &archive_free);
	UniqueEntry entry(archive_entry_new(), &archive_entry_free);
	if(!archive || !archiveReadDisk || !entry) {
		throw std::bad_alloc();
	}
	if(auto res = archive_write_set_format_zip(archive.get()); res != ARCHIVE_OK) {
		throw std::runtime_error(archive_error_string(archive.get()));
	}
	if(auto res = archive_write_set_option(archive.get(), "zip", "compression", "deflate"); res != ARCHIVE_OK) {
		throw std::runtime_error(archive_error_string(archive.get()));
	}
	if(auto res = archive_write_set_option(archive.get(), "zip", "compression-level", "9"); res != ARCHIVE_OK) {
		throw std::runtime_error(archive_error_string(archive.get()));
	}
	if(auto res = archive_write_open_filename(archive.get(), TEST_FILE_DIR "output.zip"); res != ARCHIVE_OK) {
		throw std::runtime_error(archive_error_string(archive.get()));
	}
	archive_entry_copy_sourcepath(entry.get(), TEST_FILE_PATH);
	archive_entry_set_pathname(entry.get(), TEST_FILE_NAME);
	if(auto res = archive_read_disk_entry_from_file(archiveReadDisk.get(), entry.get(), -1, nullptr); res != ARCHIVE_OK) {
		throw std::runtime_error(archive_error_string(archiveReadDisk.get()));
	}
	if(auto res = archive_write_header(archive.get(), entry.get()); res != ARCHIVE_OK) {
		throw std::runtime_error(archive_error_string(archive.get()));
	}
	std::ifstream ifstrm;
	ifstrm.exceptions(std::ios_base::failbit | std::ios_base::badbit);
	ifstrm.open(TEST_FILE_PATH, std::ios_base::in | std::ios_base::binary);
	assert(ifstrm.is_open());
	std::array<char, 4096> buffer{};
	while(!ifstrm.eof())
	{
		try {
			ifstrm.read(buffer.data(), buffer.size());
		}
		catch(std::ifstream::failure&)
		{
			if(!ifstrm.eof()) {
				throw;
			}
		}
		std::streamsize readCount = ifstrm.gcount();
		if (readCount > 0)
		{
			if (archive_write_data(archive.get(), buffer.data(), readCount) == -1) {
				throw std::runtime_error(archive_error_string(archive.get()));
			}
		}
	}
}