/*
 * Copyright (C) 2017 E.S.R.Labs
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDROID_IO_FILEOUTPUTSTREAM_H_
#define MINDROID_IO_FILEOUTPUTSTREAM_H_

#include <mindroid/io/OutputStream.h>
#include <fstream>

namespace mindroid {

class File;

class FileOutputStream : public OutputStream {
public:
    FileOutputStream(const sp<File>& file);
    FileOutputStream(const sp<File>& file, bool append);
    FileOutputStream(const sp<String>& file);
    FileOutputStream(const sp<String>& file, bool append);

    void close() override;

    void flush() override;

    void write(int32_t b) override;

    void write(const sp<ByteArray>& buffer) override;

    void write(const sp<ByteArray>& buffer, size_t offset, size_t count) override;

private:
    std::ofstream mOutputFileStream;
};

} /* namespace mindroid */

#endif /* MINDROID_IO_FILEOUTPUTSTREAM_H_ */
