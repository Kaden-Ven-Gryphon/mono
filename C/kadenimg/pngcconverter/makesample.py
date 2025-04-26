import zlib

out = zlib.compress(b"This is a test of the zlib compression method.  In the Beginning there was a programmer who hated zlib compression.  After working on it for many weeks, he still hated it.  For the love of all that is holy just work please.  I have rewritten so many functions and read through so many documents.", level=4)
f = open("samplecomp.zlib", "wb")
f.write(out)
f.close()
