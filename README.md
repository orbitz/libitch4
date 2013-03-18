This is just an amateur hobby project, I don't actually have access to a NASDAQ
feed, this is just based off reading the pdf located:

http://nasdaqtrader.com/content/technicalsupport/specifications/dataproducts/NQTV-ITCH-V4_1.pdf

The goal of this is to be deterministic, therefore I try to avoid any heap
allocation in the library, the memory consumption for parsing a message should
be the same regardless of message (so parsing is always as expensive as parsing
the largest message). I also attempt to avoid any system calls in the library,
so times are not translated to the system time.

Testing on my MacBook Pro, for parsing and incrementing a trade counter gives me
about 2.7 million parsed messages per second, while decompressing the trade file
at the same time (via gzip), so I presume I could beat this if I decompressed
the file first.

DISCLAIMER: I am not a professional C++ developer or even that experienced in
it. If I am doing something ridiculous, feel free to correct me.