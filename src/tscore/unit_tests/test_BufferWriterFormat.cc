/** @file

    Unit tests for BufferFormat and bwprint.

    @section license License

    Licensed to the Apache Software Foundation (ASF) under one
    or more contributor license agreements.  See the NOTICE file
    distributed with this work for additional information
    regarding copyright ownership.  The ASF licenses this file
    to you under the Apache License, Version 2.0 (the
    "License"); you may not use this file except in compliance
    with the License.  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
 */

#include "catch.hpp"
#include "../../../tests/include/catch.hpp"
#include <chrono>
#include <iostream>
#include <netinet/in.h>
#include "tscore/BufferWriter.h"
#include "tscore/bwf_std_format.h"
#include "swoc/MemSpan.h"
#include "tscore/ink_config.h"
#if TS_ENABLE_FIPS == 0
#include "tscore/MD5.h"
#endif
#include "tscore/CryptoHash.h"

using namespace std::literals;

TEST_CASE("Buffer Writer << operator", "[bufferwriter][stream]")
{
  ts::LocalBufferWriter<50> bw;

  bw << "The" << ' ' << "quick" << ' ' << "brown fox";

  REQUIRE(bw.view() == "The quick brown fox");

  bw.reduce(0);
  bw << "x=" << bw.capacity();
  REQUIRE(bw.view() == "x=50");
}

TEST_CASE("bwprint basics", "[bwprint]")
{
  ts::LocalBufferWriter<256> bw;
  std::string_view fmt1{"Some text"sv};

  bw.print(fmt1);
  REQUIRE(bw.view() == fmt1);
  bw.reduce(0);
  bw.print("Arg {}", 1);
  REQUIRE(bw.view() == "Arg 1");
  bw.reduce(0);
  bw.print("arg 1 {1} and 2 {2} and 0 {0}", "zero", "one", "two");
  REQUIRE(bw.view() == "arg 1 one and 2 two and 0 zero");
  bw.reduce(0);
  bw.print("args {2}{0}{1}", "zero", "one", "two");
  REQUIRE(bw.view() == "args twozeroone");
  bw.reduce(0);
  bw.print("left |{:<10}|", "text");
  REQUIRE(bw.view() == "left |text      |");
  bw.reduce(0);
  bw.print("right |{:>10}|", "text");
  REQUIRE(bw.view() == "right |      text|");
  bw.reduce(0);
  bw.print("right |{:.>10}|", "text");
  REQUIRE(bw.view() == "right |......text|");
  bw.reduce(0);
  bw.print("center |{:.^10}|", "text");
  REQUIRE(bw.view() == "center |...text...|");
  bw.reduce(0);
  bw.print("center |{:.^11}|", "text");
  REQUIRE(bw.view() == "center |...text....|");
  bw.reduce(0);
  bw.print("center |{:^^10}|", "text");
  REQUIRE(bw.view() == "center |^^^text^^^|");
  bw.reduce(0);
  bw.print("center |{:%3A^10}|", "text");
  REQUIRE(bw.view() == "center |:::text:::|");
  bw.reduce(0);
  bw.print("left >{0:<9}< right >{0:>9}< center >{0:^9}<", 956);
  REQUIRE(bw.view() == "left >956      < right >      956< center >   956   <");

  bw.reduce(0);
  bw.print("Format |{:>#010x}|", -956);
  REQUIRE(bw.view() == "Format |0000-0x3bc|");
  bw.reduce(0);
  bw.print("Format |{:<#010x}|", -956);
  REQUIRE(bw.view() == "Format |-0x3bc0000|");
  bw.reduce(0);
  bw.print("Format |{:#010x}|", -956);
  REQUIRE(bw.view() == "Format |-0x00003bc|");

  bw.reduce(0);
  bw.print("{{BAD_ARG_INDEX:{} of {}}}", 17, 23);
  REQUIRE(bw.view() == "{BAD_ARG_INDEX:17 of 23}");

  bw.reduce(0);
  bw.print("Arg {0} Arg {3}", 1, 2);
  REQUIRE(bw.view() == "Arg 1 Arg {BAD_ARG_INDEX:3 of 2}");

  bw.reduce(0);
  bw.print("{{stuff}} Arg {0} Arg {}", 1, 2);
  REQUIRE(bw.view() == "{stuff} Arg 1 Arg 2");
  bw.reduce(0);
  bw.print("Arg {0} Arg {} and {{stuff}}", 3, 4);
  REQUIRE(bw.view() == "Arg 3 Arg 4 and {stuff}");
  bw.reduce(0);
  bw.print("Arg {{{0}}} Arg {} and {{stuff}}", 5, 6);
  REQUIRE(bw.view() == "Arg {5} Arg 6 and {stuff}");
  bw.reduce(0);
  bw.print("Arg {0} Arg {{}}{{}} {} and {{stuff}}", 7, 8);
  REQUIRE(bw.view() == "Arg 7 Arg {}{} 8 and {stuff}");
  bw.reduce(0);
  bw.print("Arg {0} Arg {{{{}}}} {}", 9, 10);
  REQUIRE(bw.view() == "Arg 9 Arg {{}} 10");

  bw.reduce(0);
  bw.print("Arg {0} Arg {{{{}}}} {}", 9, 10);
  REQUIRE(bw.view() == "Arg 9 Arg {{}} 10");
  bw.reduce(0);

  bw.reset().print("{leif}");
  REQUIRE(bw.view() == "{~leif~}"); // expected to be missing.

  bw.reset().print("Thread: {thread-name} [{thread-id:#x}] - Tick: {tick} - Epoch: {now} - timestamp: {timestamp} {0}\n", 31267);
  // std::cout << bw;
  /*
  std::cout << ts::LocalBufferWriter<256>().print(
    "Thread: {thread-name} [{thread-id:#x}] - Tick: {tick} - Epoch: {now} - timestamp: {timestamp} {0}{}", 31267, '\n');
  */
}

TEST_CASE("BWFormat numerics", "[bwprint][bwformat]")
{
  ts::LocalBufferWriter<256> bw;
  ts::BWFormat fmt("left >{0:<9}< right >{0:>9}< center >{0:^9}<");
  std::string_view text{"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

  bw.reduce(0);
  static const ts::BWFormat bad_arg_fmt{"{{BAD_ARG_INDEX:{} of {}}}"};
  bw.print(bad_arg_fmt, 17, 23);
  REQUIRE(bw.view() == "{BAD_ARG_INDEX:17 of 23}");

  bw.reduce(0);
  bw.print(fmt, 956);
  REQUIRE(bw.view() == "left >956      < right >      956< center >   956   <");

  bw.reduce(0);
  bw.print("Text: _{0:.10,20}_", text);
  REQUIRE(bw.view() == "Text: _abcdefghijklmnopqrst_");
  bw.reduce(0);
  bw.print("Text: _{0:-<20.52,20}_", text);
  REQUIRE(bw.view() == "Text: _QRSTUVWXYZ----------_");

  void *ptr = reinterpret_cast<void *>(0XBADD0956);
  bw.reduce(0);
  bw.print("{}", ptr);
  REQUIRE(bw.view() == "0xbadd0956");
  bw.reduce(0);
  bw.print("{:X}", ptr);
  REQUIRE(bw.view() == "0XBADD0956");
  int *int_ptr = static_cast<int *>(ptr);
  bw.reduce(0);
  bw.print("{}", int_ptr);
  REQUIRE(bw.view() == "0xbadd0956");
  char char_ptr[] = "good";
  bw.reduce(0);
  bw.print("{:x}", static_cast<char *>(ptr));
  REQUIRE(bw.view() == "0xbadd0956");
  bw.reduce(0);
  bw.print("{}", char_ptr);
  REQUIRE(bw.view() == "good");

  swoc::MemSpan span{ptr, 0x200};
  bw.reduce(0);
  bw.print("{}", span);
  REQUIRE(bw.view() == "0x200@0xbadd0956");

  bw.reduce(0);
  bw.print("{:x}", swoc::MemSpan(char_ptr, 4));
  REQUIRE(bw.view() == "676f6f64");
  bw.reduce(0);
  bw.print("{:#x}", swoc::MemSpan(char_ptr, 4));
  REQUIRE(bw.view() == "0x676f6f64");
  bw.reduce(0);
  bw.print("{:x}", swoc::MemSpan<void>(char_ptr, 4));
  REQUIRE(bw.view() == "676f6f64");
  bw.reduce(0);
  bw.print("{:#x}", swoc::MemSpan<void>(char_ptr, 4));
  REQUIRE(bw.view() == "0x676f6f64");

  std::string_view sv{"abc123"};
  bw.reduce(0);
  bw.print("{}", sv);
  REQUIRE(bw.view() == sv);
  bw.reduce(0);
  bw.print("{:x}", sv);
  REQUIRE(bw.view() == "616263313233");
  bw.reduce(0);
  bw.print("{:#x}", sv);
  REQUIRE(bw.view() == "0x616263313233");
  bw.reduce(0);
  bw.print("|{:16x}|", sv);
  REQUIRE(bw.view() == "|616263313233    |");
  bw.reduce(0);
  bw.print("|{:>16x}|", sv);
  REQUIRE(bw.view() == "|    616263313233|");
  bw.reduce(0);
  bw.print("|{:^16x}|", sv);
  REQUIRE(bw.view() == "|  616263313233  |");
  bw.reduce(0);
  bw.print("|{:>16.2x}|", sv);
  REQUIRE(bw.view() == "|        63313233|");
  bw.reduce(0);
  bw.print("|{:<0.2,5x}|", sv);
  REQUIRE(bw.view() == "|63313|");
  bw.reset().print("|{:<.2,5x}|", sv);
  REQUIRE(bw.view() == "|63313|");

  bw.reduce(0);
  bw.print("|{}|", true);
  REQUIRE(bw.view() == "|1|");
  bw.reduce(0);
  bw.print("|{}|", false);
  REQUIRE(bw.view() == "|0|");
  bw.reduce(0);
  bw.print("|{:s}|", true);
  REQUIRE(bw.view() == "|true|");
  bw.reduce(0);
  bw.print("|{:S}|", false);
  REQUIRE(bw.view() == "|FALSE|");
  bw.reduce(0);
  bw.print("|{:>9s}|", false);
  REQUIRE(bw.view() == "|    false|");
  bw.reduce(0);
  bw.print("|{:^10s}|", true);
  REQUIRE(bw.view() == "|   true   |");

  // Test clipping a bit.
  ts::LocalBufferWriter<20> bw20;
  bw20.print("0123456789abc|{:^10s}|", true);
  REQUIRE(bw20.view() == "0123456789abc|   tru");
  bw20.reduce(0);
  bw20.print("012345|{:^10s}|6789abc", true);
  REQUIRE(bw20.view() == "012345|   true   |67");

#if TS_ENABLE_FIPS == 0
  INK_MD5 md5;
  bw.reduce(0);
  bw.print("{}", md5);
  REQUIRE(bw.view() == "00000000000000000000000000000000");
  CryptoContext().hash_immediate(md5, sv.data(), sv.size());
  bw.reduce(0);
  bw.print("{}", md5);
  REQUIRE(bw.view() == "e99a18c428cb38d5f260853678922e03");
#endif

  bw.reset().print("Char '{}'", 'a');
  REQUIRE(bw.view() == "Char 'a'");
  bw.reset().print("Byte '{}'", uint8_t{'a'});
  REQUIRE(bw.view() == "Byte '97'");
}

TEST_CASE("bwstring", "[bwprint][bwstring]")
{
  std::string s;
  ts::TextView fmt("{} -- {}");
  std::string_view text{"e99a18c428cb38d5f260853678922e03"};

  ts::bwprint(s, fmt, "string", 956);
  REQUIRE(s.size() == 13);
  REQUIRE(s == "string -- 956");

  ts::bwprint(s, fmt, 99999, text);
  REQUIRE(s == "99999 -- e99a18c428cb38d5f260853678922e03");
  REQUIRE(strlen(s.c_str()) == text.size() + 9);

  ts::bwprint(s, "{} .. |{:,20}|", 32767, text);
  REQUIRE(s == "32767 .. |e99a18c428cb38d5f260|");
  REQUIRE(strlen(s.c_str()) == 31);

  ts::LocalBufferWriter<128> bw;
  char buff[128];
  snprintf(buff, sizeof(buff), "|%s|", bw.print("Deep Silent Complete by {}\0", "Nightwish"sv).data());
  REQUIRE(std::string_view(buff) == "|Deep Silent Complete by Nightwish|");
  snprintf(buff, sizeof(buff), "|%s|", bw.reset().print("Deep Silent Complete by {}\0elided junk", "Nightwish"sv).data());
  REQUIRE(std::string_view(buff) == "|Deep Silent Complete by Nightwish|");

  // Special tests for clang analyzer failures - special asserts are needed to make it happy but
  // those can break functionality.
  fmt = "Did you know? {}{} is {}"sv;
  s.resize(0);
  ts::bwprint(s, fmt, "Lady "sv, "Persia"sv, "not mean");
  REQUIRE(s == "Did you know? Lady Persia is not mean");
  s.resize(0);
  ts::bwprint(s, fmt, ""sv, "Phil", "correct");
  REQUIRE(s == "Did you know? Phil is correct");
  s.resize(0);
  ts::bwprint(s, fmt, std::string_view(), "Leif", "confused");
  REQUIRE(s == "Did you know? Leif is confused");

  {
    std::string out;
    ts::bwprint(out, fmt, ""sv, "Phil", "correct");
    REQUIRE(out == "Did you know? Phil is correct");
  }
  {
    std::string out;
    ts::bwprint(out, fmt, std::string_view(), "Leif", "confused");
    REQUIRE(out == "Did you know? Leif is confused");
  }

  char const *null_string{nullptr};
  ts::bwprint(s, "Null {0:x}.{0}", null_string);
  REQUIRE(s == "Null 0x0.");
  ts::bwprint(s, "Null {0:X}.{0}", nullptr);
  REQUIRE(s == "Null 0X0.");
  ts::bwprint(s, "Null {0:p}.{0:P}.{0:s}.{0:S}", null_string);
  REQUIRE(s == "Null 0x0.0X0.null.NULL");
}

TEST_CASE("BWFormat integral", "[bwprint][bwformat]")
{
  ts::LocalBufferWriter<256> bw;
  ts::BWFSpec spec;
  uint32_t num = 30;
  int num_neg  = -30;

  // basic
  bwformat(bw, spec, num);
  REQUIRE(bw.view() == "30");
  bw.reduce(0);
  bwformat(bw, spec, num_neg);
  REQUIRE(bw.view() == "-30");
  bw.reduce(0);

  // radix
  ts::BWFSpec spec_hex;
  spec_hex._radix_lead_p = true;
  spec_hex._type         = 'x';
  bwformat(bw, spec_hex, num);
  REQUIRE(bw.view() == "0x1e");
  bw.reduce(0);

  ts::BWFSpec spec_dec;
  spec_dec._type = '0';
  bwformat(bw, spec_dec, num);
  REQUIRE(bw.view() == "30");
  bw.reduce(0);

  ts::BWFSpec spec_bin;
  spec_bin._radix_lead_p = true;
  spec_bin._type         = 'b';
  bwformat(bw, spec_bin, num);
  REQUIRE(bw.view() == "0b11110");
  bw.reduce(0);

  int one     = 1;
  int two     = 2;
  int three_n = -3;
  // alignment
  ts::BWFSpec left;
  left._align = ts::BWFSpec::Align::LEFT;
  left._min   = 5;
  ts::BWFSpec right;
  right._align = ts::BWFSpec::Align::RIGHT;
  right._min   = 5;
  ts::BWFSpec center;
  center._align = ts::BWFSpec::Align::CENTER;
  center._min   = 5;

  bwformat(bw, left, one);
  bwformat(bw, right, two);
  REQUIRE(bw.view() == "1        2");
  bwformat(bw, right, two);
  REQUIRE(bw.view() == "1        2    2");
  bwformat(bw, center, three_n);
  REQUIRE(bw.view() == "1        2    2 -3  ");

  std::atomic<int> ax{0};
  bw.reset().print("ax == {}", ax);
  REQUIRE(bw.view() == "ax == 0");
  ++ax;
  bw.reset().print("ax == {}", ax);
  REQUIRE(bw.view() == "ax == 1");
}

TEST_CASE("BWFormat floating", "[bwprint][bwformat]")
{
  ts::LocalBufferWriter<256> bw;
  ts::BWFSpec spec;

  bw.reduce(0);
  bw.print("{}", 3.14);
  REQUIRE(bw.view() == "3.14");
  bw.reduce(0);
  bw.print("{} {:.2} {:.0} ", 32.7, 32.7, 32.7);
  REQUIRE(bw.view() == "32.70 32.70 32 ");
  bw.reduce(0);
  bw.print("{} neg {:.3}", -123.2, -123.2);
  REQUIRE(bw.view() == "-123.20 neg -123.200");
  bw.reduce(0);
  bw.print("zero {} quarter {} half {} 3/4 {}", 0, 0.25, 0.50, 0.75);
  REQUIRE(bw.view() == "zero 0 quarter 0.25 half 0.50 3/4 0.75");
  bw.reduce(0);
  bw.print("long {:.11}", 64.9);
  REQUIRE(bw.view() == "long 64.90000000000");
  bw.reduce(0);

  double n   = 180.278;
  double neg = -238.47;
  bwformat(bw, spec, n);
  REQUIRE(bw.view() == "180.28");
  bw.reduce(0);
  bwformat(bw, spec, neg);
  REQUIRE(bw.view() == "-238.47");
  bw.reduce(0);

  spec._prec = 5;
  bwformat(bw, spec, n);
  REQUIRE(bw.view() == "180.27800");
  bw.reduce(0);
  bwformat(bw, spec, neg);
  REQUIRE(bw.view() == "-238.47000");
  bw.reduce(0);

  float f    = 1234;
  float fneg = -1;
  bwformat(bw, spec, f);
  REQUIRE(bw.view() == "1234");
  bw.reduce(0);
  bwformat(bw, spec, fneg);
  REQUIRE(bw.view() == "-1");
  bw.reduce(0);
  f          = 1234.5667;
  spec._prec = 4;
  bwformat(bw, spec, f);
  REQUIRE(bw.view() == "1234.5667");
  bw.reduce(0);

  bw << 1234 << .567;
  REQUIRE(bw.view() == "12340.57");
  bw.reduce(0);
  bw << f;
  REQUIRE(bw.view() == "1234.57");
  bw.reduce(0);
  bw << n;
  REQUIRE(bw.view() == "180.28");
  bw.reduce(0);
  bw << f << n;
  REQUIRE(bw.view() == "1234.57180.28");
  bw.reduce(0);

  double edge = 0.345;
  spec._prec  = 3;
  bwformat(bw, spec, edge);
  REQUIRE(bw.view() == "0.345");
  bw.reduce(0);
  edge = .1234;
  bwformat(bw, spec, edge);
  REQUIRE(bw.view() == "0.123");
  bw.reduce(0);
  edge = 1.0;
  bwformat(bw, spec, edge);
  REQUIRE(bw.view() == "1");
  bw.reduce(0);

  // alignment
  double first  = 1.23;
  double second = 2.35;
  double third  = -3.5;
  ts::BWFSpec left;
  left._align = ts::BWFSpec::Align::LEFT;
  left._min   = 5;
  ts::BWFSpec right;
  right._align = ts::BWFSpec::Align::RIGHT;
  right._min   = 5;
  ts::BWFSpec center;
  center._align = ts::BWFSpec::Align::CENTER;
  center._min   = 5;

  bwformat(bw, left, first);
  bwformat(bw, right, second);
  REQUIRE(bw.view() == "1.23  2.35");
  bwformat(bw, right, second);
  REQUIRE(bw.view() == "1.23  2.35 2.35");
  bwformat(bw, center, third);
  REQUIRE(bw.view() == "1.23  2.35 2.35-3.50");
  bw.reduce(0);

  double over = 1.4444444;
  ts::BWFSpec over_min;
  over_min._prec = 7;
  over_min._min  = 5;
  bwformat(bw, over_min, over);
  REQUIRE(bw.view() == "1.4444444");
  bw.reduce(0);

  // Edge
  bw.print("{}", (1.0 / 0.0));
  REQUIRE(bw.view() == "Inf");
  bw.reduce(0);

  double inf = std::numeric_limits<double>::infinity();
  bw.print("  {} ", inf);
  REQUIRE(bw.view() == "  Inf ");
  bw.reduce(0);

  double nan_1 = std::nan("1");
  bw.print("{} {}", nan_1, nan_1);
  REQUIRE(bw.view() == "NaN NaN");
  bw.reduce(0);

  double z = 0.0;
  bw.print("{}  ", z);
  REQUIRE(bw.view() == "0  ");
  bw.reduce(0);
}

TEST_CASE("bwstring std formats", "[libts][bwprint]")
{
  ts::LocalBufferWriter<120> w;

  w.print("{}", ts::bwf::Errno(13));
  REQUIRE(w.view() == "EACCES: Permission denied [13]"sv);
  w.reset().print("{}", ts::bwf::Errno(134));
  REQUIRE(w.view().substr(0, 9) == "Unknown: "sv);

  time_t t = 1528484137;
  // default is GMT
  w.reset().print("{} is {}", t, ts::bwf::Date(t));
  REQUIRE(w.view() == "1528484137 is 2018 Jun 08 18:55:37");
  w.reset().print("{} is {}", t, ts::bwf::Date(t, "%a, %d %b %Y at %H.%M.%S"));
  REQUIRE(w.view() == "1528484137 is Fri, 08 Jun 2018 at 18.55.37");
  // OK to be explicit
  w.reset().print("{} is {::gmt}", t, ts::bwf::Date(t));
  REQUIRE(w.view() == "1528484137 is 2018 Jun 08 18:55:37");
  w.reset().print("{} is {::gmt}", t, ts::bwf::Date(t, "%a, %d %b %Y at %H.%M.%S"));
  REQUIRE(w.view() == "1528484137 is Fri, 08 Jun 2018 at 18.55.37");
  // Local time - set it to something specific or the test will be geographically sensitive.
  setenv("TZ", "CST6", 1);
  tzset();
  w.reset().print("{} is {::local}", t, ts::bwf::Date(t));
  REQUIRE(w.view() == "1528484137 is 2018 Jun 08 12:55:37");
  w.reset().print("{} is {::local}", t, ts::bwf::Date(t, "%a, %d %b %Y at %H.%M.%S"));
  REQUIRE(w.view() == "1528484137 is Fri, 08 Jun 2018 at 12.55.37");

  // Verify these compile and run, not really much hope to check output.
  w.reset().print("|{}|   |{}|", ts::bwf::Date(), ts::bwf::Date("%a, %d %b %Y"));

  w.reset().print("name = {}", ts::bwf::FirstOf("Persia"));
  REQUIRE(w.view() == "name = Persia");
  w.reset().print("name = {}", ts::bwf::FirstOf("Persia", "Evil Dave"));
  REQUIRE(w.view() == "name = Persia");
  w.reset().print("name = {}", ts::bwf::FirstOf("", "Evil Dave"));
  REQUIRE(w.view() == "name = Evil Dave");
  w.reset().print("name = {}", ts::bwf::FirstOf(nullptr, "Evil Dave"));
  REQUIRE(w.view() == "name = Evil Dave");
  w.reset().print("name = {}", ts::bwf::FirstOf("Persia", "Evil Dave", "Leif"));
  REQUIRE(w.view() == "name = Persia");
  w.reset().print("name = {}", ts::bwf::FirstOf("Persia", nullptr, "Leif"));
  REQUIRE(w.view() == "name = Persia");
  w.reset().print("name = {}", ts::bwf::FirstOf("", nullptr, "Leif"));
  REQUIRE(w.view() == "name = Leif");

  const char *empty{nullptr};
  std::string s1{"Persia"};
  std::string_view s2{"Evil Dave"};
  ts::TextView s3{"Leif"};
  w.reset().print("name = {}", ts::bwf::FirstOf(empty, s3));
  REQUIRE(w.view() == "name = Leif");
  w.reset().print("name = {}", ts::bwf::FirstOf(s2, s3));
  REQUIRE(w.view() == "name = Evil Dave");
  w.reset().print("name = {}", ts::bwf::FirstOf(s1, empty, s2));
  REQUIRE(w.view() == "name = Persia");
  w.reset().print("name = {}", ts::bwf::FirstOf(empty, s2, s1, s3));
  REQUIRE(w.view() == "name = Evil Dave");
  w.reset().print("name = {}", ts::bwf::FirstOf(empty, empty, s3, empty, s2, s1));
  REQUIRE(w.view() == "name = Leif");

  unsigned v = ntohl(0xdeadbeef);
  w.reset().print("{}", ts::bwf::Hex_Dump(v));
  REQUIRE(w.view() == "deadbeef");
  w.reset().print("{:x}", ts::bwf::Hex_Dump(v));
  REQUIRE(w.view() == "deadbeef");
  w.reset().print("{:X}", ts::bwf::Hex_Dump(v));
  REQUIRE(w.view() == "DEADBEEF");
  w.reset().print("{:#X}", ts::bwf::Hex_Dump(v));
  REQUIRE(w.view() == "0XDEADBEEF");
  w.reset().print("{} bytes {} digits {}", sizeof(double), std::numeric_limits<double>::digits10, ts::bwf::Hex_Dump(2.718281828));
  REQUIRE(w.view() == "8 bytes 15 digits 9b91048b0abf0540");

#if TS_ENABLE_FIPS == 0
  INK_MD5 md5;
  w.reset().print("{}", ts::bwf::Hex_Dump(md5));
  REQUIRE(w.view() == "00000000000000000000000000000000");
  CryptoContext().hash_immediate(md5, s2.data(), s2.size());
  w.reset().print("{}", ts::bwf::Hex_Dump(md5));
  REQUIRE(w.view() == "f240ccd7a95c7ec66d6c111e2925b23e");
#endif
}

// Normally there's no point in running the performance tests, but it's worth keeping the code
// for when additional testing needs to be done.
#if 0
TEST_CASE("bwperf", "[bwprint][performance]")
{
  // Force these so I can easily change the set of tests.
  auto start            = std::chrono::high_resolution_clock::now();
  auto delta = std::chrono::high_resolution_clock::now() - start;
  constexpr int N_LOOPS = 1000000;

  static constexpr const char * FMT = "Format |{:#010x}| '{}'";
  static constexpr ts::TextView fmt{FMT, strlen(FMT)};
  static constexpr std::string_view text{"e99a18c428cb38d5f260853678922e03"sv};
  ts::LocalBufferWriter<256> bw;

  ts::BWFSpec spec;

  bw.reduce(0);
  bw.print(fmt, -956, text);
  REQUIRE(bw.view() == "Format |-0x00003bc| 'e99a18c428cb38d5f260853678922e03'");

  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N_LOOPS; ++i) {
    bw.reduce(0);
    bw.print(fmt, -956, text);
  }
  delta = std::chrono::high_resolution_clock::now() - start;
  std::cout << "bw.print() " << delta.count() << "ns or " << std::chrono::duration_cast<std::chrono::milliseconds>(delta).count()
            << "ms" << std::endl;

  ts::BWFormat pre_fmt(fmt);
  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N_LOOPS; ++i) {
    bw.reduce(0);
    bw.print(pre_fmt, -956, text);
  }
  delta = std::chrono::high_resolution_clock::now() - start;
  std::cout << "Preformatted: " << delta.count() << "ns or "
            << std::chrono::duration_cast<std::chrono::milliseconds>(delta).count() << "ms" << std::endl;

  char buff[256];
  start = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < N_LOOPS; ++i) {
    snprintf(buff, sizeof(buff), "Format |%#0x10| '%.*s'", -956, static_cast<int>(text.size()), text.data());
  }
  delta = std::chrono::high_resolution_clock::now() - start;
  std::cout << "snprint Timing is " << delta.count() << "ns or "
            << std::chrono::duration_cast<std::chrono::milliseconds>(delta).count() << "ms" << std::endl;
}
#endif
