// Copyright (c) 2016, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#ifndef NULL_STREAMS_H_
#define NULL_STREAMS_H_

#include <iostream>

namespace std_extensions {

// Null stream buffer.
class nullstreambuf : public std::streambuf {
 public:
  int_type overflow(int_type c = traits_type::eof()) override { return c; }
};

// Null ostream.
class nullostream : public std::ostream {
 public:
  nullostream() : std::ostream(&m_sb) {}

 private:
  nullstreambuf m_sb;
};

}  // namespace std_extensions

#endif  // !NULL_STREAMS_H_
