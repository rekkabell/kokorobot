#!/bin/sh -e

cat links/img.xml | sed -E '
  /^<\?xml version="1.0" encoding="UTF-8"\?>$/d;
  s/<!\[CDATA\[//g;
  s/\]\]>//g;
  s|<pubDate>.*?</pubDate>||g;
  s|<link>.*?</link>||g;
  s|<title>.*?</title>||g;
  s|<rss version="2.0">||g;
  s|</rss>||g;
  s|<channel>||g;
  s|</channel>||g;' | sed 's|<description>Rek'\''s image feed</description>||g' > src/inc/pics.htm
